/** \file resolv_server.h
**   \date  2005-03-24
**   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

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


#include "apex/parallelization/thread.h"


namespace sockets
{

   /** \defgroup async Asynchronous DNS */
   /** Async DNS resolver thread.
   \ingroup async */
   class CLASS_DECL_APEX resolv_server :
      virtual public ::thread
   {
   public:


      resolv_server();
      ~resolv_server();


      virtual void     initialize_resolv_server(::object * pobjectParent, ::networking::port_t);

      virtual void go();
      void Quit();

      bool Ready();


      bool m_quit;
      ::networking::port_t m_port;
      bool m_ready;


   };


} // namespace sockets



