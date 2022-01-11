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
#include "axis/networking/_networking.h"


namespace sockets
{


   EventHandler::EventHandler(::object * pobject, ::apex::log * plog) :
      socket_handler(plog),
      m_bQuit(false), m_ptcpsocket(nullptr)
   {

      initialize(pobject);

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

      if(p)
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

      for(; p.ok(); p = m_eventplist.begin())
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

         for (p = m_eventplist.begin(); p.ok(); p++)
         {

            Event * peventItem = *p;

            if (peventItem == pevent)
            {

               break;

            }

         }

         ::acme::del(pevent);

         if (p != nullptr)
         {

            m_eventplist.erase(p);

         }

      }

   }


   long EventHandler::AddEvent(IEventOwner *from,long sec,long usec)
   {

      Event * peventNew = new Event(from, sec, usec);

      auto pevent = m_eventplist.begin();

      for(;pevent; pevent++)
      {

         if (!(**pevent < *peventNew))
         {

            break;

         }

      }

      m_eventplist.insert_before(pevent, peventNew);

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

         auto ppevent = m_eventplist.begin();

         for(; ppevent; ppevent++)
         {

            if((*ppevent)->GetFrom() == from)
            {

               delete * ppevent;

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
      while (!m_bQuit)
      {
         struct timeval tv;
         if (GetTimeUntilNextEvent(&tv))
         {
            select(&tv);
            CheckEvents();
         }
         else
         {
            select();
         }
      }
   }


   void EventHandler::SetQuit(bool x)
   {
      m_bQuit = x;
   }


   void EventHandler::RemoveEvent(IEventOwner * pownerFrom, long lEid)
   {

      auto pevent = ::deref(m_eventplist.begin());

      for(; pevent; pevent++)
      {

         if(pownerFrom == pevent->GetFrom() && lEid == pevent->GetID())
         {

            ::delete_erase(pevent);

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

         socket_handler::add2(plistensocket);

         m_ptcpsocket = __new(tcp_socket());
         m_ptcpsocket -> SetDeleteByHandler();
         m_ptcpsocket -> set_maximum_connection_time(5_s);
         m_ptcpsocket -> SetRetryClientConnect(-1);
#ifdef ENABLE_RECONNECT
         m_ptcpsocket -> SetReconnect(true);
#endif
         m_ptcpsocket -> open(::net::address("127.0.0.1", m_port));

         socket_handler::add2(m_ptcpsocket);

      }

      socket_handler::add2( psocket );

   }

}



