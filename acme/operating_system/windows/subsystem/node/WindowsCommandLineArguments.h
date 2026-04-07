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


#include "acme/subsystem/CommandLineArguments.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"

namespace windows
{


   class CLASS_DECL_ACME WindowsCommandLineArguments :
   virtual public ::subsystem::CommandLineArguments
   {
   public:

      //WindowsCommandLineArguments(const ::scoped_string & scopedstrCmdLineInWinFormat);

      WindowsCommandLineArguments();
      ~WindowsCommandLineArguments() override;

      virtual void initialize_windows_command_line_arguments(const ::scoped_string & scopedstrCommandLineInWindowsFormat);

      virtual void parse_windows_commnad_line_arguments(const ::scoped_string & scopedstrCommandLineInWindowsFormat);


   };

   //// __WINCOMMANDLINEARGS_H__
} // namespace windows