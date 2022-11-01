/** \file EventHandler.h
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
#pragma once


#include "apex/networking/sockets/basic/socket_handler.h"
#include "ievent_handler.h"
#include "acme/primitive/collection/list.h"


namespace sockets
{


   class logger;
   class IEventOwner;
   class Event;
   class tcp_socket;


   /** socket_handler implementing the IEventHandler interface.
      \ingroup timer */
   class EventHandler : public socket_handler,public IEventHandler
   {
      public:


         list < Event * >              m_eventplist;
         bool                          m_bQuit;
         tcp_socket *                  m_ptcpsocket;
         ::networking::port_t          m_port;



         EventHandler(::particle * pparticle, ::apex::log * plogger = nullptr);
         ~EventHandler();

         bool GetTimeUntilNextEvent(struct timeval *tv);
         void CheckEvents();
         long AddEvent(IEventOwner *from,long sec,long usec);
         void ClearEvents(IEventOwner *from);
         void RemoveEvent(IEventOwner *from,long eid);

         /** socket_handler while() loop implemented with event functionality. */
         void EventLoop();
         /** Stop event loop. */
         void SetQuit(bool = true);

         void add(base_socket *);


   };


} // namespace sockets



