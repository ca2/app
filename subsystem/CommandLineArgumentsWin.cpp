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
#include "framework.h"
#include "subsystem_windows/_common_header.h"
#include "CommandLineArguments.h"
#include "subsystem/Exception.h"

#include <shellapi.h>

namespace subsystem_windows
{
   CommandLineArguments::CommandLineArguments()
   {



   }


   CommandLineArguments::~CommandLineArguments()
   {}





   void CommandLineArguments::initialize_command_line_arguments(const scoped_string& scopedstrCommandLineInWindowsFormat)
   {

      _parse_windows_command_line_arguments(scopedstrCommandLineInWindowsFormat);

   }

   void CommandLineArguments::_parse_windows_command_line_arguments(const scoped_string& scopedstrCommandLineInWindowsFormat)
   {
      ::string strstorage(scopedstrCommandLineInWindowsFormat);
      ::wstring uniCmdLine(strstorage);
      size_t cmdLen = uniCmdLine.length();
      if (cmdLen > 0) {
         int nArgs;
         LPWSTR *argList = CommandLineToArgvW(uniCmdLine, &nArgs);
         if(argList == 0) {
            throw ::subsystem::Exception("Invalid command line");
         }
         for(int i = 0; i < nArgs; i++) {
            ::wstring uniArg(argList[i]);
            ::string arg;
            arg = uniArg;
            if (arg.length() > 0) {
               m_straArguments.add(arg);
            }
         }

         LocalFree(argList);
      }
   }

   ::string_array_base CommandLineArguments::getArguments() const
   {

      return m_straArguments;

   }

   // WindowsCommandLineArguments::~WindowsCommandLineArguments()
   // {
   // }
} // namespace subsystem_windows


