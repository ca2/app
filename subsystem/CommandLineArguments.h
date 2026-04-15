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
//// #include aaa_<vector>

namespace subsystem
{

   // This class produce initial parse of a command line.
   // Each word or expression will be saved at self index.
   class CommandLineArgumentsSlice :
      virtual public ::particle_base
   {
   public:

      //::string_array m_straArguments;

      //CommandLineArguments();
      //virtual ~CommandLineArgumentsInterface() = 0;

      virtual void initialize_command_line_arguments(const ::scoped_string & scopedstrCommandLineInOperatingSystemFormat) = 0;

      // Copies internal argument ::array_base to the out variable.
      virtual ::string_array_base getArguments() const = 0;

//   protected:

   };


   using CommandLineArgumentsInterface = particle_interface<CommandLineArgumentsSlice>;

   // This class produce initial parse of a command line.
   // Each word or expression will be saved at self index.
   class CLASS_DECL_SUBSYSTEM CommandLineArgumentsComposite :
      virtual public composite<CommandLineArgumentsSlice>
   {
   public:

      implement_compositeø(CommandLineArguments, commandlinearguments)

      ///::string_array m_straArguments;

      //CommandLineArguments();
      //~CommandLineArguments() override;


      void initialize_command_line_arguments(const ::scoped_string & scopedstrCommandLineInOperatingSystemFormat) override;

      // Copies internal argument ::array_base to the out variable.
      ::string_array_base getArguments() const override;

      //   protected:

   };

   
} // namespace subsystem

