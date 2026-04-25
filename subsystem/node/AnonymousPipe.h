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
#include "acme/input_output/Channel.h"
#include "subsystem/node/Pipe.h"
#include "subsystem/_common_header.h"

//#include "acme/remoting_common/win_system/::happening.h"
//#include "remoting/remoting/thread/LocalMutex.h"
//#include "log_writer/LogWriter.h"

namespace subsystem
{


   class AnonymousPipeInterface :
   virtual public Channel,
   virtual public ::Particle
   {
   public:
      // @param hWrite is a write handle getting by the CreatePipe()
      // function calling.
      // @param hRead is a read handle getting by the CreatePipe()
      // function calling but is not the same as for hWrite.
      //AnonymousPipe(HANDLE hWrite, HANDLE hRead, unsigned int maxPortionSize, LogWriter *plogwriter);
      //AnonymousPipe();
      ///virtual ~AnonymousPipeInterface() = 0;

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
      virtual memsize read(void *buffer, memsize len) = 0;

      /**
       * Writes data to pipe.
       * Implemented from Channel interface.
       * @param buffer buffer with data to write.
       * @param len count of bytes to write.
       * @throws ::io_exception on io error.
       */
      virtual memsize defer_write(const void *buffer, memsize len) = 0;

      virtual memsize available() = 0;

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
      virtual void assignHandlesFor(::subsystem::ProcessHandleInterface * pprocesshandle, bool neededToClose, bool keepCloseRight = false) = 0;

      virtual void setTimeOut(unsigned int timeOut) = 0;

   //private:
      virtual void checkPipeFile(::subsystem::FileInterface * pfile) = 0;

      // HANDLE m_hWrite;
      // HANDLE m_hRead;
      // bool m_neededToClose;
      // unsigned int m_timeOut;
      //
      // LocalMutex m_hPipeMutex;
      // ::happening m_readEvent;
      // ::happening m_writeEvent;
      //
      // LogWriter *m_plogwriter;
   };

    //using AnonymousPipeInterface = particle_interface<AnonymousPipeInterface, PipeInterface>;



   class CLASS_DECL_SUBSYSTEM AnonymousPipeComposite :
   virtual public Composite < AnonymousPipeInterface >
   {
   public:

      ImplementCompositeø(AnonymousPipe, anonymouspipe)

      // @param hWrite is a write handle getting by the CreatePipe()
      // function calling.
      // @param hRead is a read handle getting by the CreatePipe()
      // function calling but is not the same as for hWrite.
      //AnonymousPipe(HANDLE hWrite, HANDLE hRead, unsigned int maxPortionSize, LogWriter *plogwriter);
      //AnonymousPipe();
      //~AnonymousPipe() override;

      void initialize_anonymous_pipe(::subsystem::FileInterface * pfileWrite, ::subsystem::FileInterface * pfileRead, unsigned int maxPortionSize, ::subsystem::LogWriter *plogwriter) override
      {

         m_panonymouspipe->initialize_anonymous_pipe(pfileWrite, pfileRead, maxPortionSize, plogwriter);

      }
      /**
       * Closes transport.
       *
       * @throws ::subsystem::Exception on fail.
       */
      void close() override {m_panonymouspipe->close();}

      /**
       * Reads data from pipe.
       * Implemented from Channel interface.
       * @param buffer buffer to receive data.
       * @param len count of bytes to read.
       * @throws ::io_exception on io error.
       */
      memsize read(void *buffer, memsize len) override {return m_panonymouspipe->read(buffer, len);}

      /**
       * Writes data to pipe.
       * Implemented from Channel interface.
       * @param buffer buffer with data to write.
       * @param len count of bytes to write.
       * @throws ::io_exception on io error.
       */
      memsize defer_write(const void *buffer, memsize len) override{return m_panonymouspipe->defer_write(buffer, len);}

      memsize available() override
      {
         
         return m_panonymouspipe->available();
      
      }

      // Returns pipe handle to write
      ::subsystem::FileInterface * getWriteFile() const override {return m_panonymouspipe->getWriteFile();}

      // Returns pipe handle to read
      ::subsystem::FileInterface * getReadFile() const override {return m_panonymouspipe->getReadFile();}

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

      void assignHandlesFor(::subsystem::ProcessHandleInterface * pprocesshandle, bool neededToClose, bool keepCloseRight = false) override
      {

      m_panonymouspipe->assignHandlesFor(pprocesshandle, neededToClose, keepCloseRight);
      }

      void setTimeOut(unsigned int timeOut) override{return m_panonymouspipe->setTimeOut(timeOut);}

   //private:
      void checkPipeFile(::subsystem::FileInterface* pfile) override
      {

         m_panonymouspipe->checkPipeFile(pfile);


      }

      // HANDLE m_hWrite;
      // HANDLE m_hRead;
      // bool m_neededToClose;
      // unsigned int m_timeOut;
      //
      // LocalMutex m_hPipeMutex;
      // ::happening m_readEvent;
      // ::happening m_writeEvent;
      //
      // LogWriter *m_plogwriter;
   };


   class CLASS_DECL_SUBSYSTEM AnonymousPipeAggregate :
      virtual public Aggregate < AnonymousPipeComposite, PipeAggregate >
   {
   public:

      ImplementAggregateø(AnonymousPipe, Pipe);

   };



   class CLASS_DECL_SUBSYSTEM AnonymousPipe :
    virtual public Object < AnonymousPipeAggregate >
   {
   public:

      ImplementObjectø(AnonymousPipe)

   };



} // namespace subsystem


