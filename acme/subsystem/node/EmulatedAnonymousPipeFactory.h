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


#include "acme/subsystem/node/NamedPipe.h"
#include "subsystem/subsystem.h"
//#include "log_writer/LogWriter.h"

namespace subsystem
{
   // The EmulatedAnonymousPipeFactory class generates a chanel based on named pipe.
   // This is similar to anonymous pipe generation.
   class CLASS_DECL_ACME EmulatedAnonymousPipeFactory :
   virtual public ::subsystem::particle
   {
   public:
      //EmulatedAnonymousPipeFactory(unsigned int bufferSize, LogWriter *log);
      EmulatedAnonymousPipeFactory();
      virtual ~EmulatedAnonymousPipeFactory() = 0;

      virtual void initialize_emulated_anonymous_pipe_factory(unsigned int bufferSize, LogWriter *log) = 0;

      virtual void generatePipes(NamedPipe **serverPipe, bool serverInheritable,
                         NamedPipe **clientPipe, bool clientInheritable) = 0;

      //private:
      virtual ::string getUniqPipeName() = 0;

      // LogWriter *m_log;
      // unsigned int m_bufferSize;
   };

   // class CLASS_DECL_ACME EmulatedAnonymousPipeFactory :
   // virtual public ::subsystem::composite< EmulatedAnonymousPipeFactoryInterface>
   // {
   // public:
   //
   //
   //    EmulatedAnonymousPipeFactory(unsigned int bufferSize, LogWriter *log);
   //     ~EmulatedAnonymousPipeFactory() override;
   //
   //
   //    void initialize_emulated_anonymous_pipe_factory(unsigned int bufferSize, LogWriter *log) override;
   //
   //    void generatePipes(NamedPipe **serverPipe, bool serverInheritable,
   //                       NamedPipe **clientPipe, bool clientInheritable) override;
   //
   //    //private:
   //    ::string getUniqPipeName() override;
   //
   //    //LogWriter *m_log;
   //    //unsigned int m_bufferSize;
   // };
   //
   //// __EMULATEDANONYMOUSPIPEFACTORY_H__
} // namespace subsystem


