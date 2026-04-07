// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "NamedPipe.h"
#include "acme/subsystem/Exception.h"
#include "acme/operating_system/windows/subsystem/node/File.h"
#include <crtdbg.h>
//#include "remoting/remoting_common/win_system/Environment.h"
//#include "remoting/remoting_common/thread/AutoLock.h"

#define MAX_PORTION_SIZE 512 * 1024

namespace windows
{
   namespace subsystem
   {
//      NamedPipe::NamedPipe(::subsystem::File * pfilePipe, unsigned int maxPortionSize, bool asServer):
  //      m_asServer(false)

      NamedPipe::NamedPipe():
            m_asServer(false)
      {
      }

      NamedPipe::~NamedPipe(void)
      {
         try {
            close();
         } catch (...) {
         }
      }

      void NamedPipe::initialize_pipe(unsigned int maxPortionSize)
      {

         ::windows::subsystem::Pipe::initialize_pipe(maxPortionSize);

      }

      void NamedPipe::initialize_named_pipe(::subsystem::FileInterface * pfilePipe, unsigned int maxPortionSize, bool asServer)
      {
         initialize_pipe(maxPortionSize);
       m_pfilePipe = pfilePipe;
       m_asServer = asServer;
      }

      void NamedPipe::close()
      {
         critical_section_lock al(&m_criticalsectionPipe);
         if (m_asServer) {
            if (DisconnectNamedPipe(::as_HANDLE(m_pfilePipe)) == 0) {
               DWORD errCode = GetLastError();
               ::string errMess;
               errMess.formatf("DisconnectNamedPipe failed, error code = %u", errCode);
               throw ::subsystem::Exception(errMess);
            }
         }

         if (::as_HANDLE(m_pfilePipe) != INVALID_HANDLE_VALUE) {
            CloseHandle(::as_HANDLE(m_pfilePipe));
            m_pfilePipe = nullptr;
         }
         // Unblock a blocked operation
         m_readEvent.notify();
         m_writeEvent.notify();
      }

      memsize NamedPipe::defer_write(const void *buffer, memsize len)
      {
         return writeByFile(buffer, len, m_pfilePipe);
      }

      size_t NamedPipe::read(void *buffer, size_t len)
      {
         return readByFile(buffer, len, m_pfilePipe);
      }


      size_t NamedPipe::available()
      {
         return 0;
      }



      ::subsystem::FileInterface * NamedPipe::getFile() const
      {
         return m_pfilePipe;
      }

      void NamedPipe::checkPipeFile()
      {
         if (::is_null(m_pfilePipe) || ::as_HANDLE(m_pfilePipe) == INVALID_HANDLE_VALUE) {
            throw ::io_exception(error_io, "Invalid pipe handle");
         }
      }
   } // namespace  subsystem
} // namespace windows