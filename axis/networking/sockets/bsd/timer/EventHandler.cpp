/** \file EventHandler.cpp
 **   \date  2005-12-07
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2005,2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"
#include "event_handler.h"
#include "event_time.h"
#include "event.h"
#include "ievent_owner.h"
#include "acme/platform/system.h"
#include "apex/networking/sockets/basic/tcp_socket.h"
#include "apex/networking/sockets/basic/listen_socket.h"
#include "apex/networking/networking.h"
#include "apex/platform/system.h"


#if defined(FREEBSD)
#define __XSI_VISIBLE 1
#include <sys/time.h>
#endif


namespace sockets
{


   EventHandler::EventHandler(::particle * pparticle, ::apex::log * plog) :
      //socket_handler(plog),
      m_bQuit(false), m_ptcpsocket(nullptr)
   {

      initialize(pparticle);

   }


   EventHandler::~EventHandler()
   {

      m_eventplist.each([](auto & pevent)
         {

            pevent->GetFrom()->SetHandlerInvalid();

            ::acme::del(pevent);

         });

      m_eventplist.erase_all();

   }


   bool EventHandler::GetTimeUntilNextEvent(struct timeval * tv)
   {

      if (!m_eventplist.get_size())
      {

         return false;

      }

      auto p = m_eventplist.begin();

      if(p.is_ok())
      {

         Event * pe = *p;

         EventTime now;

         mytime_t diff = pe->get_time() - now;

         if (diff < 1)
         {

            diff = 1;

         }

         tv -> tv_sec = static_cast<long>(diff / 1000000);

         tv -> tv_usec = static_cast<i32>(diff % 1000000);

         return true;

      }

      return false;

   }


   void EventHandler::CheckEvents()
   {

      EventTime now;

      auto p = m_eventplist.begin();

      for(; p.is_ok(); p++)
      {

         Event * pevent = *p;

         if (!(pevent->get_time() < now))
         {

            break;

         }

         socket * psocket = dynamic_cast < socket * > (pevent->GetFrom());

         /*
         s == nullptr    This is another object implementing 'IEventOwner' and not a socket.
         s != nullptr    This is a socket implementing IEventOwner, and we can check that the
                 object instance still is valid using socket_handler::Valid.
         */
         if (!psocket || (psocket && Valid(psocket)))
         {

            pevent->GetFrom()->OnEvent(pevent->GetID());

         }

         for (p = m_eventplist.begin(); p.is_ok(); p++)
         {

            Event * peventItem = *p;

            if (peventItem == pevent)
            {

               break;

            }

         }

         ::acme::del(pevent);

         if (p)
         {

            m_eventplist.erase(p);

         }

      }

   }


   long EventHandler::AddEvent(IEventOwner *from,long sec,long usec)
   {

      Event * peventNew = memory_new Event(from, sec, usec);

      auto p = m_eventplist.begin();

      for(;p.is_ok(); p++)
      {

         if (!(**p < *peventNew))
         {

            break;

         }

      }

      m_eventplist.insert_before(p, peventNew);

      if (m_ptcpsocket)
      {

         m_ptcpsocket->print("\n");

      }

      return peventNew->GetID();

   }


   void EventHandler::ClearEvents(IEventOwner *from)
   {

      bool repeat;

      do
      {

         repeat = false;

         auto p = m_eventplist.begin();

         for(; p.is_ok(); p++)
         {

            if((*p)->GetFrom() == from)
            {

               delete *p;

               repeat = true;

               break;

            }

         }

         m_eventplist.erase_all();
      }
      while (repeat);
   }


   void EventHandler::EventLoop()
   {
//      while (!m_bQuit)
//      {
//         struct timeval tv;
//         if (GetTimeUntilNextEvent(&tv))
//         {
//            select(&tv);
//            CheckEvents();
//         }
//         else
//         {
//            select();
//         }
//      }
   }


   void EventHandler::SetQuit(bool x)
   {
      m_bQuit = x;
   }


   void EventHandler::RemoveEvent(IEventOwner * pownerFrom, long lEid)
   {

      auto p = m_eventplist.begin();

      for(; p.is_ok(); p++)
      {

         if(pownerFrom == (*p)->GetFrom() && lEid == (*p)->GetID())
         {

            delete (*p);

            break;

         }

      }

   }


   void EventHandler::add(base_socket *psocket)
   {
      if (!m_ptcpsocket)
      {
         auto plistensocket = __new(listen_socket<tcp_socket>());
         plistensocket-> SetDeleteByHandler();
         plistensocket-> Bind("127.0.0.1", 0);
         m_port = plistensocket-> GetPort();

         socket_handler::add(plistensocket);

         m_ptcpsocket = __new(tcp_socket());
         m_ptcpsocket -> SetDeleteByHandler();
         m_ptcpsocket -> set_maximum_connection_time(5_s);
         m_ptcpsocket -> SetRetryClientConnect(-1);
#ifdef ENABLE_RECONNECT
         m_ptcpsocket -> SetReconnect(true);
#endif
         
         auto paddress = system()->m_papexsystem->networking()->create_address("127.0.0.1", m_port);
//         m_ptcpsocket -> open(::networking::address("127.0.0.1", m_port));
         
         m_ptcpsocket -> open(paddress);

         socket_handler::add(m_ptcpsocket);

      }

      socket_handler::add( psocket );

   }

}



