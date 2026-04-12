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

namespace subsystem
{
   // This class is not an interface but is a class that contain common
   // methods/source codes for derived classes to work with pipe handles.
   class PipeInterface :
   virtual public ::subsystem::particle_interface<PipeInterface>
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
      virtual size_t readByFile(void *buffer, size_t len, ::subsystem::FileInterface * pfilePipe) = 0;
      virtual size_t writeByFile(const void *buffer, size_t len, ::subsystem::FileInterface * pfilePipe) = 0;

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




   // This class is not an interface but is a class that contain common
   // methods/source codes for derived classes to work with pipe handles.
   class CLASS_DECL_ACME Pipe :
      virtual public ::subsystem::composite< PipeInterface>
   {
   public:

      //protected:
      //Pipe(unsigned int maxPortionSize);
      Pipe();
      ~Pipe() override;

      void initialize_pipe(unsigned int maxPortionSize) override;


      unsigned int getMaxPortionSize() override;



      // This read and write functions is common way to read and write
      // by pipe handles asynchronously.

      // The pointer uses because the functions must have access to
      // the same variable as in a derived class to rich a thread safe
      // handle usage.
      size_t readByFile(void *buffer, size_t len, ::subsystem::FileInterface * pfilePipe) override;
      size_t writeByFile(const void *buffer, size_t len, ::subsystem::FileInterface * pfilePipe) override;

      // This mutex is to use for pipe handles that uses in the above functions.
      // The mutex protect collision accesses to handle fields of derived classes.
      //LocalMutex m_hPipeMutex;

      //WindowsEvent m_readEvent;
      //WindowsEvent m_writeEvent;

      //private:
      void checkPipeFile(::subsystem::FileInterface * pfilePipe) override;

      //unsigned long long m_totalWrote;
      //unsigned long long m_totalRead;
      //unsigned int m_maxPortionSize;
   };

   //// __PIPE_H__
} // namespace subsystem



