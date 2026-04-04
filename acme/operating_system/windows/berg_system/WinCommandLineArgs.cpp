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
#include "acme/_operating_system.h"
#include "WinCommandLineArgs.h"
#include "remoting/remoting_common/util/Exception.h"

#include <shellapi.h>


WinCommandLineArgs::WinCommandLineArgs(const ::scoped_string & scopedstrCmdLineInWinFormat)
{
   ::string strstorage(scopedstrCmdLineInWinFormat);
  ::wstring uniCmdLine(strstorage);
  size_t cmdLen = uniCmdLine.length();
  if (cmdLen > 0) {
    int nArgs;
    LPWSTR *argList = CommandLineToArgvW(uniCmdLine, &nArgs);
    if(argList == 0) {
      throw ::remoting::Exception("Invalid command line");
    }
    for(int i = 0; i < nArgs; i++) {
      ::wstring uniArg(argList[i]);
      ::string arg;
      arg = uniArg;
      if (arg.length() > 0) {
        m_args.add(arg);
      }
    }

    LocalFree(argList);
  }
}

WinCommandLineArgs::~WinCommandLineArgs()
{
}
