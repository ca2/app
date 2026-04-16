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


#include "subsystem/_common_header.h"
//#include "win-system/WindowsEvent.h"
#include "acme/input_output/Channel.h"
////#include "remoting/remoting_common/thread/LocalMutex.h"

namespace subsystem
{
   // This class is not an interface but is a class that contain common
   // methods/source codes for derived classes to work with pipe handles.
   class PipeInterface :
   virtual public ::particle_base
   {
   public:

      //protected:
      //Pipe(unsigned int maxPortionSize);
      //Pipe();
      //virtual ~PipeInterface() = 0 ;


      virtual unsigned int getMaxPortionSize() = 0;

      virtual void initialize_pipe(unsigned int maxPortionSize) = 0;

      // This read and write functions is common way to read and write
      // by pipe handles asynchronously.

      // The pointer uses because the functions must have access to
      // the same variable as in a derived class to rich a thread safe
      // handle usage.
      virtual memsize readByFile(void *buffer, memsize len, ::subsystem::FileInterface * pfilePipe) = 0;
      virtual memsize writeByFile(const void *buffer, memsize len, ::subsystem::FileInterface * pfilePipe) = 0;

      // This mutex is to use for pipe handles that uses in the above functions.
      // The mutex protect collision accesses to handle fields of derived classes.
      //LocalMutex m_hPipeMutex;

      //WindowsEvent m_readEvent;
      //WindowsEvent m_writeEvent;

      //private:
      virtual void checkPipeFile(::subsystem::FileInterface * pfilePipe) = 0;
      //
      // unsigned long long m_totalWrote;
      // unsigned long long m_totalRead;
      // unsigned int m_maxPortionSize;
   };

   ///using PipeInterface = particle_interface<PipeInterface>;


   // This class is not an interface but is a class that contain common
   // methods/source codes for derived classes to work with pipe handles.
   class CLASS_DECL_SUBSYSTEM PipeComposite :
      virtual public composite< PipeInterface>
   {
   public:


      implement_compositeø(Pipe, pipe)


      //protected:
      //Pipe(unsigned int maxPortionSize);
      //Pipe();
      //~Pipe() override;

         void initialize_pipe(unsigned int maxPortionSize) override
      {

         m_ppipe->initialize_pipe(maxPortionSize);

      }


      unsigned int getMaxPortionSize() override
      {

         return m_ppipe->getMaxPortionSize();

      }



      // This read and write functions is common way to read and write
      // by pipe handles asynchronously.

      // The pointer uses because the functions must have access to
      // the same variable as in a derived class to rich a thread safe
      // handle usage.
      memsize readByFile(void* buffer, memsize len, ::subsystem::FileInterface* pfilePipe) override
      {

         return m_ppipe->readByFile(buffer, len, pfilePipe);

      }
      memsize writeByFile(const void* buffer, memsize len, ::subsystem::FileInterface* pfilePipe) override
      {

         return m_ppipe->writeByFile(buffer, len, pfilePipe);

      }

      // This mutex is to use for pipe handles that uses in the above functions.
      // The mutex protect collision accesses to handle fields of derived classes.
      //LocalMutex m_hPipeMutex;

      //WindowsEvent m_readEvent;
      //WindowsEvent m_writeEvent;

      //private:
      void checkPipeFile(::subsystem::FileInterface* pfilePipe) override
      {

         return m_ppipe->checkPipeFile(pfilePipe);

      }

      //unsigned long long m_totalWrote;
      //unsigned long long m_totalRead;
      //unsigned int m_maxPortionSize;
   };

   class CLASS_DECL_SUBSYSTEM Pipe :
   virtual public aggregate< PipeComposite>
   {
   public:

      implement_baseø(Pipe)

   };


   //// __PIPE_H__
} // namespace subsystem



