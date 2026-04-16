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
#include "framework.h"
#include "SocketIPv4.h"
#include "SocketStream.h"

#include "sockdefs.h"

//#include aaa_<crtdbg.h>


namespace subsystem
{
    SocketStream::SocketStream(::subsystem::SocketIPv4Interface *psocket)
    : m_psocket(psocket)
    {
       _ASSERT(m_psocket != NULL);
    }

   // SocketStream::SocketStream()
   // {
   // }

   SocketStream::~SocketStream()
   {
   }

   // void SocketStream::initialize_socket_stream(::subsystem::SocketIPv4Interface *sock)
   //
   // {
   //    m_psocket = sock;
   //    _ASSERT(m_psocket != NULL);
   // }


   memsize SocketStream::read(void *buf, memsize wanted)
   {
      if ((int)wanted < 0) {
         throw ::io_exception(error_io, "Wanted size too big.");
      }

      return (memsize)m_psocket->recv((char *)buf, (int)wanted);
   }

   memsize SocketStream::defer_write(const void *buf, memsize size)
   {
      if ((int)size < 0) {
         throw ::io_exception(error_io, "Size of buffer is too big.");
      }

      return (memsize)m_psocket->send((char *)buf, (int)size);

   }

   void SocketStream::close()
   {
      try {
         m_psocket->shutdown(e_socket_shutdown_both);
      } catch (...) {
      }
      m_psocket->close();
   }

   memsize SocketStream::available() {
      return m_psocket->available();
   }
} // namespace subsystem