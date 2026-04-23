// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

//#ifndef SOCKET_STREAM_H
#pragma once
//#define SOCKET_STREAM_H

#include "acme/input_output/Channel.h"

//#include "subsystem/socket/SocketAddressIPv4.h"
//#include "remoting/remoting/network/socket/SocketIPv4.h"
//#include "remoting/remoting/network/socket/SocketAddressIPv4.h"

//#include "acme/exception/io.h"

namespace subsystem
{


   class CLASS_DECL_SUBSYSTEM SocketStream : public Channel
   {
   public:



      SocketStream(SocketIPv4Interface * psocket);
      SocketStream();
      virtual ~SocketStream();

      //
      // Inherited from Channel.
      //


      //virtual void initialize_socket_stream(SocketIPv4Interface * psocket);

      virtual memsize read(void *, memsize);

      virtual memsize defer_write(const void *, memsize);

      // Closes connection and break all blocked operation.
      // @throw ::subsystem::Exception on error.
      virtual void close();

      virtual memsize available();

   //protected:
      ::pointer < SocketIPv4Interface > m_psocket;

      //friend class SocketIPv4;

   };


} // namespace subsystem