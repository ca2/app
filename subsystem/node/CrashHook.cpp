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
//#include "CrashHook.h"
//#include "subsystem/node/DynamicLibrary.h"
//#include "subsystem/node/OperatingSystem.h"
//#include "subsystem/platform/RegistryKey.h"
////#include "subsystem/thread/critical_section.h"
//#include "remoting/node_desktop/NamingDefs.h"
//
//typedef bool (WINAPI *MINIDUMPWRITEDUMP)(__in  HANDLE hProcess,
//                                       __in  DWORD ProcessId,
//                                       __in  HANDLE hFile,
//                                       __in  MINIDUMP_TYPE DumpType,
//                                       __in  PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
//                                       __in  PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
//                                       __in  PMINIDUMP_CALLBACK_INFORMATION CallbackParam);
//
//bool CrashHook::m_guiEnabled = false;
//::subsystem::registry CrashHook::m_rootHkey = HKEY_CURRENT_USER;
//critical_section CrashHook::m_guiEnabledMutex;
//ApplicationCrashEvents *CrashHook::m_notifier = 0;
//
//CrashHook::CrashHook(ApplicationCrashEvents *notifier)
//{
//  m_notifier = notifier;
//  ::SetUnhandledExceptionFilter(topLevelExceptionFilter);
//}
//
//CrashHook::~CrashHook()
//{
//}
//
//LONG WINAPI CrashHook::topLevelExceptionFilter(_EXCEPTION_POINTERS *pExceptionInfo)
//{
//  bool guiEnabled;
//  {
//    critical_section_lock al(&m_guiEnabledMutex);
//    guiEnabled = m_guiEnabled;
//  }
//
//  LONG retValue = EXCEPTION_CONTINUE_SEARCH;
//
//  DynamicLibrary dbgLib;
//  MINIDUMPWRITEDUMP miniDumpWriteDump = 0;
//  try {
//    // Try load the library from this exe mofule folder
//    ::string libName, moduleFolder;
//    moduleFolder = MainSubsystem().OperatingSystem().getCurrentModuleFolderPath();;
//    libName.formatf("{}\\DbgHelp.dll", moduleFolder);
//
//    dbgLib.init(libName);
//    miniDumpWriteDump = (MINIDUMPWRITEDUMP)
//                          dbgLib.getProcAddress("MiniDumpWriteDump");
//  } catch (...) {
//    try {
//      // Try load the library by default path
//      dbgLib.init("DbgHelp.dll");
//      miniDumpWriteDump = (MINIDUMPWRITEDUMP)
//                            dbgLib.getProcAddress("MiniDumpWriteDump");
//    } catch (...) {
//      return retValue;
//    }
//  }
//  if (miniDumpWriteDump == 0) {
//    return retValue;
//  }
//
//  ::string specFolder, dumpPath;
//  if (!Environment::getSpecialFolderPath(
//         Environment::APPLICATION_DATA_SPECIAL_FOLDER, &specFolder)) {
//    return retValue;
//  }
//  dumpPath.formatf("{}\\{}\\crash.dmp", specFolder,
//                                           ProductNames::PRODUCT_NAME);
//
//  if (guiEnabled && MainSubsystem().message_box({},
//                               "Apllication crashing. Do you"
//                               " want save debug information?",
//                               ProductNames::PRODUCT_NAME,
//                               ::user::e_message_box_yes_no)
//                               != ::innate_subsystem::IDYES)
//  {
//    return retValue;
//  }
//  HANDLE hFile = 0;
//  try {
//    // Store path to the registry.
//    try {
//      ::subsystem::registry root;
//      {
//        critical_section_lock al(&m_guiEnabledMutex);
//        root = m_rootHkey;
//      }
//      RegistryKey regKey(root, RegistryPaths::SERVER_PATH);
//      regKey.setValueAsString("CrashDumpPath", dumpPath);
//    } catch (::subsystem::Exception &) {
//    }
//
//    // FIXME: use the "file_lib" project from the trunk hive.
//    hFile = ::CreateFile(dumpPath,
//                         GENERIC_WRITE,
//                         FILE_SHARE_WRITE,
//                         0,
//                         CREATE_ALWAYS,
//                         FILE_ATTRIBUTE_NORMAL,
//                         0);
//    if (hFile == INVALID_HANDLE_VALUE) {
//      throw ::subsystem::Exception("Cannot create file to save a debug information");
//    }
//
//    _MINIDUMP_EXCEPTION_INFORMATION exInfo;
//
//    exInfo.ThreadId = ::GetCurrentThreadId();
//    exInfo.ExceptionPointers = pExceptionInfo;
//    exInfo.ClientPointers = 0;
//
//    bool result = miniDumpWriteDump(GetCurrentProcess(),
//                                    GetCurrentProcessId(),
//                                    hFile,
//                                    MiniDumpNormal,
//                                    &exInfo,
//                                    0,
//                                    0);
//    if (result == 0) {
//      throw ::subsystem::Exception("Cannot create the crash dump file");
//    }
//    if (guiEnabled) {
//      ::string succMess;
//      succMess.formatf("The debug information has been successfully"
//                      " saved to the {} file", dumpPath);
//      MainSubsystem().message_box({}, succMess, ProductNames::PRODUCT_NAME, ::user::e_message_box_ok);
//    }
//    m_notifier->onCrash(&dumpPath);
//
//    retValue = EXCEPTION_EXECUTE_HANDLER;
//  } catch (::exception &e) {
//    if (guiEnabled) {
//      MainSubsystem().message_box(NULL, e.get_message(), ProductNames::PRODUCT_NAME, ::user::e_message_box_ok);
//    }
//  }
//  if (hFile != 0) {
//    CloseHandle(hFile);
//  }
//
//  return retValue;
//}
//
//void CrashHook::setGuiEnabled()
//{
//  critical_section_lock al(&m_guiEnabledMutex);
//  m_guiEnabled = true;
//}
//
//void CrashHook::setHklmRoot()
//{
//  critical_section_lock al(&m_guiEnabledMutex);
//  m_rootHkey = HKEY_LOCAL_MACHINE;
//}
