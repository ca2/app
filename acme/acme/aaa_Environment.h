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

// #pragma once
//
//
// //////#include "remoting/remoting_common/util/::string.h"
// //#include "log_writer/LogWriter.h"
//
// #include <winnt.h>
//
// namespace remoting
// {
//    class Environment :
//    virtual public ::particle
//    {
//    public:
//       static const int APPLICATION_DATA_SPECIAL_FOLDER = 0x0;
//       static const int COMMON_APPLICATION_DATA_SPECIAL_FOLDER = 0x1;
//    //public:
//       Environment();
//       ~Environment();
//
//       // Formates string from last system error code.
//       // @return false on an error.
//       virtual ::string getErrStr();
//
//       // Formates string from last system error code with specification before.
//       // @return ::string object that contain error describing with
//       // secificatioin.
//       virtual ::string getErrStr(const ::scoped_string & scopedstrSpecification);
//
//       //
//       // Sets path to special folder value to out argument.
//       //
//       // Valid values for specialFolderId argument are:
//       //  - Environment::APPLICATION_DATA_SPECIAL_FOLDER
//       //  - Environment::COMMON_APPLICATION_DATA_SPECIAL_FOLDER
//       //
//       // Remark: if caller set invalid value into specialFolderId assertion
//       // will be failed.
//       //
//
//       virtual ::string getSpecialFolderPath(int specialFolderId);
//
//       // Sets full path to current executing process file to out argument
//       virtual ::string getCurrentModulePath();
//
//       // pId - the process id that be tested
//       // return true if tested process has the same path as current process
//       // else return false
//       // throw ::remoting::Exception an error.
//       virtual bool isItTheSamePathAsCurrent(unsigned int pId);
//
//       // Sets full path to folder (without last directory separator character)
//       // where current executing process file is located to out argument.
//       virtual ::string getCurrentModuleFolderPath();
//
//       // Returns user name of the current desktop
//       //virtual bool getCurrentUserName(::string & out, LogWriter *log);
//       virtual ::string getCurrentUserName();
//
//      // Fills "out" by computer name string.
//      // Returns true if success.
//       virtual ::string getComputerName();
//
//       // Returns true if run under a windows NT family
//       virtual bool isWinNTFamily();
//       // Returns true if run under windows XP
//       virtual bool isWin2000();
//       // Returns true if run under windows XP
//       virtual bool isWinXP();
//       // Returns true if run windows 2003 server.
//       virtual bool isWin2003Server();
//       // Returns true if run under Windows Vista or later
//       virtual bool isVistaOrLater();
//       // Returns true if run Windows7 or Win2008 R2 server.
//       virtual bool isWin7();
//
//       // Simulates the "ctrl + alt + del" combination under WindowsXP.
//       virtual void simulateCtrlAltDel(LogWriter *log);
//
//       // Simulates the "ctrl + alt + del" combination by using the "SAS" lib.
//       virtual void simulateCtrlAltDelUnderVista(LogWriter *log);
//
//       // Returns true if the Aero is On.
//       virtual bool isAeroOn(LogWriter *log);
//
//    //private:
//       virtual void init();
//       // Operation system version info.
//       OSVERSIONINFO m_osVerInfo;
//    };
//
//
// } // namespace remoting
//
//
