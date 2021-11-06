/** \file IEventHandler.h
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


namespace sockets
{


   class IEventOwner;


   /** timer event handler pure virtual axis class.
      \ingroup timer */
   class IEventHandler
   {
   public:
      virtual ~IEventHandler() {}

      /** Return time left until next event.
         \lparam tv time struct that will be filled by method
         \return true if time is set for next event */
      virtual bool GetTimeUntilNextEvent(struct timeval *) = 0;
      /** Will fire events whose time has come. */
      virtual void CheckEvents() = 0;
      /** Schedule event for an owner.
         \lparam from Event owner
         \lparam sec Seconds until event
         \lparam usec Microseconds until event */
      virtual long AddEvent(IEventOwner *,long sec,long usec) = 0;
      /** clear all events for a specific owner. */
      virtual void ClearEvents(IEventOwner *) = 0;
      /** erase one specific event for an event owner. */
      virtual void RemoveEvent(IEventOwner *,long) = 0;

   };


} // namespace sockets


