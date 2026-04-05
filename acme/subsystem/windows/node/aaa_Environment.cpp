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
#include "framework.h"#include "Environment.h"
#include "CtrlAltDelSimulator.h"

#include <shlobj.h>
#include <crtdbg.h>
#include "remoting/win_system/AutoImpersonator.h"
#include "remoting/win_system/WTS.h"
#include "remoting/win_system/ProcessHandle.h"
#include "Shell.h"
#include "DynamicLibrary.h"
//#include <vector>
#include <algorithm>

// OSVERSIONINFO Environment::m_osVerInfo = { 0 };
// typedef VOID (WINAPI *SendSas)(BOOL asUser);
// typedef HRESULT (WINAPI *DwmIsCompositionEnabled)(BOOL *pfEnabled);
//
// Environment::Environment()
// {
// }
//
// Environment::~Environment()
// {
// }
//
// void Environment::getErrStr(::string & out)
// {
//   DWORD errCode = GetLastError();
//   TCHAR buffer[1024];
//
//   // FIXME: Remove "new line" character from buffer.
//   if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//                     NULL, errCode,
//                     MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
//                     (LPTSTR)&buffer[0],
//                     sizeof(buffer), NULL) == 0) {
//     out->format("<<Cannot get text error describing>> (%u)", errCode);
//   } else {
//     out->format("{} (%u)", buffer, errCode);
//   }
// }
//
// void Environment::getErrStr(const ::scoped_string & scopedstrSpecification, ::string & out)
// {
//   ::string sysErrText;
//   getErrStr(&sysErrText);
//   out->format("{} ({})", specification, sysErrText);
// }
//
// bool Environment::getSpecialFolderPath(int specialFolderId, ::string & out)
// {
//   _ASSERT(out != NULL);
//
//   int csidl = 0;
//
//   switch (specialFolderId) {
//   case APPLICATION_DATA_SPECIAL_FOLDER:
//     csidl = CSIDL_APPDATA;
//     break;
//   case COMMON_APPLICATION_DATA_SPECIAL_FOLDER:
//     csidl = CSIDL_COMMON_APPDATA;
//     break;
//   default:
//     _ASSERT(FALSE);
//     return false;
//   } // switch
//
//   bool returnVal = false;
//
//   TCHAR path[MAX_PATH + 1];
//   if (SHGetSpecialFolderPath(NULL, &path[0], csidl, TRUE) == TRUE) {
//     out-= &path[0];
//     returnVal = true;
//   }
//
//   return returnVal;
// }
//
// bool Environment::getCurrentModulePath(::string & out)
// {
//   ::array_base<TCHAR> buffer;
//   DWORD size = MAX_PATH;
//
//   while (true) {
//     // Allocate buffer
//     buffer.resize(size + 1);
//     // Try to get file name
//     DWORD ret = GetModuleFileName(NULL, &buffer[0], size);
//
//     if (ret == 0) {
//       return false;
//     } else if (ret == size || GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
//       size += 128;
//     } else {
//       break;
//     }
//   } // while
//
//   out-= &buffer[0];
//
//   return true;
// } // void
//
// bool Environment::isItTheSamePathAsCurrent(unsigned int pId)
// {
//   ::string currModulePath, testedModulePath;
//   ProcessHandle pHandle;
//
//   pHandle.openProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
//                       0, pId);
//   pHandle.getProcessModulePath(&testedModulePath);
//   getCurrentModulePath(&currModulePath);
//
//   return currModulePath.isEqualTo(testedModulePath);
// }
//
// bool Environment::getCurrentModuleFolderPath(::string & out)
// {
//   if (!getCurrentModulePath(out)) {
//     return false;
//   }
//
//   size_t lastPos = out->findLast(_T('\\'));
//
//   if (lastPos != (size_t)-1) {
//     out->getSubstring(out, 0, ::maximum(lastPos - 1, (size_t) 0));
//   }
//
//   return true;
// }
//
// bool Environment::getCurrentUserName(::string & out, LogWriter *log)
// {
//   *out = WTS::getCurrentUserName(log);
//   return !out->is_empty();
// }
//
// bool Environment::getComputerName(::string & out)
// {
//   TCHAR compName[MAX_COMPUTERNAME_LENGTH + 1];
//   DWORD length = MAX_COMPUTERNAME_LENGTH + 1;
//   if (GetComputerName(compName, &length) == 0) {
//     return false;
//   }
//   out-= compName;
//   out->make_lower();
//   return true;
// }
//
//
// void Environment::init()
// {
//   if (m_osVerInfo.dwOSVersionInfoSize == 0) {
//     m_osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//     if (!GetVersionEx(&m_osVerInfo)) {
//       m_osVerInfo.dwOSVersionInfoSize = 0;
//     }
//   }
// }
//
// bool Environment::isWinNTFamily()
// {
//   init();
//   return m_osVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT;
// }
//
// bool Environment::isWin2000()
// {
//   init();
//   return m_osVerInfo.dwMajorVersion == 5 && m_osVerInfo.dwMinorVersion == 0;
// }
//
// bool Environment::isWinXP()
// {
//   init();
//   return ((m_osVerInfo.dwMajorVersion == 5) && (m_osVerInfo.dwMinorVersion == 1) && isWinNTFamily());
// }
//
// bool Environment::isWin2003Server()
// {
//   init();
//   return ((m_osVerInfo.dwMajorVersion == 5) && (m_osVerInfo.dwMinorVersion == 2) && isWinNTFamily());
// }
//
// bool Environment::isVistaOrLater()
// {
//   init();
//   return m_osVerInfo.dwMajorVersion >= 6;
// }
//
// bool Environment::isWin7()
// {
//   init();
//   return ((m_osVerInfo.dwMajorVersion == 6) && (m_osVerInfo.dwMinorVersion == 1) && isWinNTFamily());
// }
//
// void Environment::simulateCtrlAltDel(LogWriter *log)
// {
//   // FIXME: Do not use log here.
//   log->information("Requested Ctrl+Alt+Del simulation");
//
//   // Are we running on Windows NT OS family?
//   if (!isVistaOrLater() && isWinNTFamily()) {
//     CtrlAltDelSimulator cadSim;
//     cadSim.wait();
//   }
// }
//
// void Environment::simulateCtrlAltDelUnderVista(LogWriter *log)
// {
//   // FIXME: Do not use log here.
//   log->information("Requested Ctrl+Alt+Del simulation under Vista or later");
//
//   try {
//     DynamicLibrary sasLib("sas.dll");
//     SendSas sendSas = (SendSas)sasLib.getProcAddress("SendSAS");
//     if (sendSas == 0) {
//       throw ::remoting::Exception("The SendSAS function has not been found");
//     }
//     sendSas(FALSE); // Try only under service
//   } catch (::exception &e) {
//     log->error("The simulateCtrlAltDelUnderVista() function failed: {}",
//                e.get_message());
//   }
// }
//
// bool Environment::isAeroOn(LogWriter *log)
// {
//   try {
//     DynamicLibrary dwmLib("Dwmapi.dll");
//     DwmIsCompositionEnabled dwmIsEnabled =
//       (DwmIsCompositionEnabled)dwmLib.getProcAddress("DwmIsCompositionEnabled");
//     if (dwmIsEnabled == 0) {
//       throw ::remoting::Exception("The DwmIsCompositionEnabled() has not been found in the Dwmapi.dll");
//     }
//     BOOL result = FALSE;
//     HRESULT dwmIsEnabledResult = dwmIsEnabled(&result);
//     if (dwmIsEnabledResult != S_OK) {
//       ::string errMess;
//       errMess.formatf("The DwmIsCompositionEnabled() error code is {}",
//                      (int)dwmIsEnabledResult);
//       throw ::remoting::Exception("");
//     }
//     return result != FALSE;
//   } catch (::exception &e) {
//     log->error("The DwmIsCompositionEnabled() function failed: {}",
//                e.get_message());
//     throw;
//   }
// }
