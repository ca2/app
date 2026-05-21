// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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


 #include "subsystem/_common_header.h"

 #include "NamedPipe.h"
 //#include "remoting/remoting/thread/LocalMutex.h"
 //#include "SecurityAttributes.h"
 //#include "DynamicLibrary.h"


namespace subsystem
{

//#ifdef WINDOWS
  // typedef BOOL(WINAPI *pGetNamedPipeClientProcessId)(HANDLE Pipe, PULONG ClientProcessId);
//#endif
   /**
    * Server fabric of pipes.
    *
    * @author yuri, enikey.
    * @fixme not thread-safe, undone, strange code inside.
    */
   class CLASS_DECL_SUBSYSTEM PipeServer :
      virtual public ::particle
   {
   public:
      /**
       * Creates new pipe server ready to accept connections.
       *
       * @param pipeName name of pipe to bind.
       * @throws PipeException on fail.
       *
       * @fixme stub.
       */
      //PipeServer(const ::scoped_string &scopedstrName, ::u32 bufferSize, SecurityAttributes *secAttr = 0,
        //         DWORD milliseconds = INFINITE);

      PipeServer();
      /**
       * Destroys pipe server.
       */
      ~PipeServer();


      virtual void initialize_pipe_server(const ::scoped_string &scopedstrName, ::u32 bufferSize,
         ::subsystem::SecurityAttributesInterface * psecurityattributes = nullptr,
                 const class ::time & time = ::time::infinity());

      /**
       * Waits until pipe client connects.
       * @return connected pipe.
       * @throws PipeException on fail.
       * @note accept() method can be breaked by call of close() method.
       *
       * @fixme stub.
       */
      virtual ::pointer < NamedPipeInterface>accept();

      /**
       * Closes pipe server.
       * @throws PipeException on fail.
       */
      virtual void close();

      virtual void waitForConnect(const class ::time & time = time::infinity());
      virtual void closeConnection();

   //private:
      virtual void createServerPipe();

      // returns True on every error
      virtual bool checkOtherSideBinaryName(::subsystem::FileInterface * pfilePipe);

      // loads GetNamedPipeClientProcessId (Vista or later) from kernel32
      //static void initialize();
      virtual void initialize_pipe_server();
      //static volatile bool m_initialized;

   //private:
      //static DynamicLibrary *m_kernel32Library;
      //static pGetNamedPipeClientProcessId m_GetNamedPipeClientProcessId;

   //private:
   //   ::string m_pipeName;
   //   ::happening m_winEvent;
   //   DWORD m_milliseconds;
   //   SecurityAttributes *m_secAttr;
   //   HANDLE m_serverPipe;
   //   ::u32 m_bufferSize;
   };

   //// __PIPESERVER_H__


} // namespace subsystem
 
