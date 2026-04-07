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


#include "acme/subsystem/node/AnonymousPipeFactory.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"

//#include "log_writer/LogWriter.h"
namespace windows
{
   namespace  subsystem
   {
      // The AnonymousPipeFactory class generates the ::pair of the AnonymousPipe
      // objects that connected to each other.
      class CLASS_DECL_ACME AnonymousPipeFactory :
      virtual public ::subsystem::implementation<::subsystem::AnonymousPipeFactoryInterface>
      {
      public:
         //AnonymousPipeFactory(unsigned int bufferSize, ::subsystem::LogWriter *log);
         AnonymousPipeFactory();
         ~AnonymousPipeFactory() override;


         void initialize_anonymous_pipe_factory(unsigned int bufferSize, ::subsystem::LogWriter *log) override;

         // This function generates the ::pair of the AnonymousPipe
         // objects that connected to each other.
         // @param the fistSide and the secondSide is a pointer to an AnonymousPipe
         // pointers that receive new the AnonymousPipe objects.
         // @param If fistSideIsInheritable is true then allows to inherit the
         // firstSide pipe handles by child('s) processes.
         // @param If secondSideIsInheritable is true then allows to inherit the
         // secondSide pipe handles by child('s) processes.
         // @throw ::remoting::Exception if an error occured.
         // After use the firstSide and secondSide object the caller must
         // destroy it by delete operator.
         void generatePipes(::pointer < ::subsystem::AnonymousPipe >& firstSide,
                            bool firstSideIsInheritable,
                            ::pointer < ::subsystem::AnonymousPipe > &secondSide,
                            bool secondSideIsInheritable);

      //private:
         ::subsystem::LogWriter *m_plogwriter;
         unsigned int m_bufferSize;
      };

      //// __ANONYMOUSPIPEFACTORY_H__
   } //namespace subsystem
} // namespace windows