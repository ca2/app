// Copyright (C) 2010,2011,2012 GlavSoft LLC.
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


#include "acme/filesystem/file/string_buffer.h"
#include "acme/subsystem/io/Channel.h"
#include "acme/subsystem/node/Pipe.h"
#include "acme/subsystem/_common_header.h"

//#include "acme/remoting_common/win_system/WindowsEvent.h"
//#include "remoting/remoting_common/thread/LocalMutex.h"
//#include "log_writer/LogWriter.h"

namespace subsystem
{


   class CLASS_DECL_ACME AnonymousPipeInterface :
   virtual public ::subsystem::particle_interface<AnonymousPipeInterface>,
   virtual public Pipe,
   virtual public Channel
   {
   public:
      // @param hWrite is a write handle getting by the CreatePipe()
      // function calling.
      // @param hRead is a read handle getting by the CreatePipe()
      // function calling but is not the same as for hWrite.
      //AnonymousPipe(HANDLE hWrite, HANDLE hRead, unsigned int maxPortionSize, LogWriter *plogwriter);
      //AnonymousPipe();
      virtual ~AnonymousPipeInterface() = 0;

      virtual void initialize_anonymous_pipe(::subsystem::FileInterface * pfileWrite, ::subsystem::FileInterface * pfileRead, unsigned int maxPortionSize, LogWriter *plogwriter) = 0;
      /**
       * Closes transport.
       *
       * @throws ::subsystem::Exception on fail.
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

      virtual size_t available() = 0;

      // Returns pipe handle to write
      virtual ::subsystem::FileInterface * getWriteFile() const = 0;

      // Returns pipe handle to read
      virtual ::subsystem::FileInterface * getReadFile() const = 0;

      // This function assigns the handles for another process.
      // @param hTargetProc is a handle to the other process.
      // If neededToClose parameter set to true then after calling this function
      // the destructor will try to close the assigned handles. If the handles
      // assigned for another process then set neededToClose flag to false.
      // If keepCloseRight is true then source process keeps the right to close
      // the new handles.
      // @throw ::subsystem::Exception on a fail.
      //void assignHandlesFor(HANDLE hTargetProc, bool neededToClose,
                            //bool keepCloseRight = false);

      virtual void setTimeOut(unsigned int timeOut) = 0;

   //private:
      virtual void checkPipeFile(::subsystem::FileInterface * pfile) = 0;

      // HANDLE m_hWrite;
      // HANDLE m_hRead;
      // bool m_neededToClose;
      // unsigned int m_timeOut;
      //
      // LocalMutex m_hPipeMutex;
      // WindowsEvent m_readEvent;
      // WindowsEvent m_writeEvent;
      //
      // LogWriter *m_plogwriter;
   };




   class CLASS_DECL_ACME AnonymousPipe :
   virtual public ::subsystem::composite < AnonymousPipeInterface >
   {
   public:
      // @param hWrite is a write handle getting by the CreatePipe()
      // function calling.
      // @param hRead is a read handle getting by the CreatePipe()
      // function calling but is not the same as for hWrite.
      //AnonymousPipe(HANDLE hWrite, HANDLE hRead, unsigned int maxPortionSize, LogWriter *plogwriter);
      AnonymousPipe();
      ~AnonymousPipe() override;

      void initialize_anonymous_pipe(::subsystem::FileInterface * pfileWrite, ::subsystem::FileInterface * pfileRead, unsigned int maxPortionSize, ::subsystem::LogWriter *plogwriter) override;
      /**
       * Closes transport.
       *
       * @throws ::subsystem::Exception on fail.
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

      size_t available() override;

      // Returns pipe handle to write
      ::subsystem::FileInterface * getWriteFile() const override;

      // Returns pipe handle to read
      ::subsystem::FileInterface * getReadFile() const override;

      // This function assigns the handles for another process.
      // @param hTargetProc is a handle to the other process.
      // If neededToClose parameter set to true then after calling this function
      // the destructor will try to close the assigned handles. If the handles
      // assigned for another process then set neededToClose flag to false.
      // If keepCloseRight is true then source process keeps the right to close
      // the new handles.
      // @throw ::subsystem::Exception on a fail.
      //void assignHandlesFor(HANDLE hTargetProc, bool neededToClose,
                            //bool keepCloseRight = false);

      void setTimeOut(unsigned int timeOut) override;

   //private:
      void checkPipeFile(::subsystem::FileInterface * pfile) override;

      // HANDLE m_hWrite;
      // HANDLE m_hRead;
      // bool m_neededToClose;
      // unsigned int m_timeOut;
      //
      // LocalMutex m_hPipeMutex;
      // WindowsEvent m_readEvent;
      // WindowsEvent m_writeEvent;
      //
      // LogWriter *m_plogwriter;
   };


   //// __ANONYMOUSPIPE_H__
} // namespace subsystem


