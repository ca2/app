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

#pragma once


#include "acme/subsystem/_common_header.h"
//#include "win-system/WindowsEvent.h"
#include "acme/subsystem/io/Channel.h"
////#include "remoting/remoting_common/thread/LocalMutex.h"
#include "acme/subsystem/node/Pipe.h"


namespace subsystem
{


   /**
 * NamedPipe transport.
 *
 * @author yuri, enikey.
 */
   class NamedPipeInterface :
   virtual public ::subsystem::particle_interface<NamedPipeInterface>,
      virtual public Channel,
      virtual public Pipe
   {
   public:
      /**
       * Creates pipe transport.
       */
      //NamedPipeInterface(HANDLE hPipe, unsigned int maxPortionSize, bool asServer);
      //NamedPipe();
      /**
       * Destroys instance.
       */
      //virtual ~NamedPipeInterface() =0;


      virtual void initialize_named_pipe(::subsystem::FileInterface * pfilePipe, unsigned int maxPortionSize, bool asServer) = 0;

      /**
       * Closes transport.
       *
       * @throws ::remoting::Exception on fail.
       */
      virtual void close() = 0;

      /**
       * Reads data from pipe.
       * Implemented from Channel interface.
       * @param buffer buffer to receive data.
       * @param len count of bytes to read.
       * @throws ::io_exception on io error.
       */
      virtual size_t read(void *buffer, size_t len) = 0;

      /**
       * Writes data to pipe.
       * Implemented from Channel interface.
       * @param buffer buffer with data to write.
       * @param len count of bytes to write.
       * @throws ::io_exception on io error.
       */
      virtual memsize defer_write(const void *buffer, memsize len) = 0;

      virtual size_t available() = 0 ; //{ return 0; };

      virtual ::subsystem::FileInterface * getFile() const = 0;

      //private:
      virtual void checkPipeFile() = 0;

      // HANDLE m_hPipe;
      // LocalMutex m_hPipeMutex;
      // ::string m_pipeName;
      //
      // WindowsEvent m_readEvent;
      // WindowsEvent m_writeEvent;
      // bool m_asServer;
   };


   /**
    * NamedPipe transport.
    *
    * @author yuri, enikey.
    */
   class CLASS_DECL_ACME NamedPipe :
      virtual public ::subsystem::composite< NamedPipeInterface>
   {
   public:
      /**
       * Creates pipe transport.
       */
      NamedPipe(::subsystem::FileInterface * pfilePipe, unsigned int maxPortionSize, bool asServer);
      NamedPipe();
      /**
       * Destroys instance.
       */
      ~NamedPipe() override;


      void initialize_named_pipe(::subsystem::FileInterface * pfilePipe, unsigned int maxPortionSize, bool asServer) override;

      /**
       * Closes transport.
       *
       * @throws ::remoting::Exception on fail.
       */
      void close() override;

      /**
       * Reads data from pipe.
       * Implemented from Channel interface.
       * @param buffer buffer to receive data.
       * @param len count of bytes to read.
       * @throws ::io_exception on io error.
       */
      size_t read(void *buffer, size_t len) override;

      /**
       * Writes data to pipe.
       * Implemented from Channel interface.
       * @param buffer buffer with data to write.
       * @param len count of bytes to write.
       * @throws ::io_exception on io error.
       */
      memsize defer_write(const void *buffer, memsize len) override;

      size_t available() override { return 0; };

      //virtual HANDLE getHandle() const;

   //private:
      void checkPipeFile() override;

      // HANDLE m_hPipe;
      // LocalMutex m_hPipeMutex;
      // ::string m_pipeName;
      //
      // WindowsEvent m_readEvent;
      // WindowsEvent m_writeEvent;
      // bool m_asServer;
   };

   //// __NAMEDPIPE_H__
} // namespace subsystem



