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


#include "subsystem/_common_header.h"
///#include "subsystem/node/EmulatedAnonymousPipeFactory.h.h"
//#include "subsystem/subsystem.h"
//#include "log_writer/LogWriter.h"

namespace subsystem
{
   // The EmulatedAnonymousPipeFactory class generates a chanel based on named pipe.
   // This is similar to anonymous pipe generation.
   class EmulatedAnonymousPipeFactoryInterface :
   virtual public ::subsystem::particle_interface<EmulatedAnonymousPipeFactoryInterface>
   {
   public:
      //EmulatedAnonymousPipeFactory(unsigned int bufferSize, LogWriter *plogwriter);
      //EmulatedAnonymousPipeFactory();
      //virtual ~EmulatedAnonymousPipeFactoryInterface() = 0 ;

      virtual void initialize_emulated_anonymous_pipe_factory(unsigned int bufferSize, LogWriter *plogwriter) = 0;

      virtual void generatePipes(
         ::pointer < NamedPipeInterface > & serverPipe, bool serverInheritable,
         ::pointer < NamedPipeInterface > & clientPipe, bool clientInheritable) = 0;

      //private:
      virtual ::string getUniqPipeName() = 0;

      // LogWriter *m_plogwriter;
      // unsigned int m_bufferSize;
   };

    class CLASS_DECL_ACME EmulatedAnonymousPipeFactory :
    virtual public ::subsystem::composite< EmulatedAnonymousPipeFactoryInterface >
    {
    public:


       //EmulatedAnonymousPipeFactory(unsigned int bufferSize, LogWriter *plogwriter);
       EmulatedAnonymousPipeFactory();
        ~EmulatedAnonymousPipeFactory() override;


       void initialize_emulated_anonymous_pipe_factory(unsigned int bufferSize, LogWriter *plogwriter) override;

       void generatePipes(::pointer < NamedPipeInterface > & serverPipe, bool serverInheritable,
                          ::pointer < NamedPipeInterface > & clientPipe, bool clientInheritable) override;

       //private:
       ::string getUniqPipeName() override;

       //LogWriter *m_plogwriter;
       //unsigned int m_bufferSize;
    };

   // __EMULATEDANONYMOUSPIPEFACTORY_H__
} // namespace subsystem


