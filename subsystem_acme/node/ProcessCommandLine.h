// Copyright (C) 2012 GlavSoft LLC.
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
// Changed by camilo on 2026-04-07 15:37 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem_acme/CommandLineArguments.h"


namespace subsystem
{

   // This class is an interface for a primitive command line parser
   class ProcessCommandLineInterface :
      virtual public ::subsystem::particle_interface<ProcessCommandLineInterface>
   {
   public:

      //protected:
      //::pointer < CommandLineArgumentsInterface > m_pwindowscommandlinearguments;


      //ProcessCommandLineInterface();
      //virtual ~ProcessCommandLineInterface()  = 0;


      virtual void initialize_process_command_line() = 0;

      // returns the number of arguments in command line
      // for example, program: help
      virtual ::collection::count getArgumentsCount() = 0;

      // returns the number of options in command line
      // for example, -V=123456
      virtual ::collection::count getOptionsCount() = 0;

      // returns the value of parameter by valName
      virtual bool findOptionValue(const ::scoped_string & scopedstrOptionName, ::string & strOut) = 0;

      // returns the argument value with index
      virtual bool getArgument(::collection::index index, ::string & strOut) = 0;

      // returns the option value with index
      virtual bool getOption(::collection::index index, ::string & strOut) = 0;


      //private:
      virtual void optionParser(::string & out) = 0;

   };

      // This class is an interface for a primitive command line parser
   class CLASS_DECL_ACME ProcessCommandLine :
      virtual public ::subsystem::composite < ProcessCommandLineInterface >
   {
   public:

      ProcessCommandLine();
      ~ProcessCommandLine() override;

      // returns the number of arguments in command line
      // for example, program: help
      ::collection::count getArgumentsCount() override;

      // returns the number of options in command line
      // for example, -V=123456
      ::collection::count getOptionsCount() override;

      // returns the value of parameter by valName
      bool findOptionValue(const ::scoped_string & scopedstrOptionName, ::string & strOut) override;

      // returns the argument value with index
      bool getArgument(::collection::index index, ::string & strOut) override;

      // returns the option value with index
      bool getOption(::collection::index index, ::string & strOut) override;


      //private:
      void optionParser(::string & out) override;

   };

} // namespace subsystem


