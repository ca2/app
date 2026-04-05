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
#include "WTS.h"
#include "SystemException.h"
#include "remoting/remoting_common/thread/AutoLock.h"
//#include "Environment.h"
#include "PipeImpersonatedThread.h"
#include "acme/platform/node.h"
#include <crtdbg.h>


DynamicLibrary *WTS::m_kernel32Library = 0;
DynamicLibrary *WTS::m_wtsapi32Library = 0;
pWTSGetActiveConsoleSessionId WTS::m_WTSGetActiveConsoleSessionId = 0;
pWTSQueryUserToken WTS::m_WTSQueryUserToken = 0;
pWTSQuerySessionInformation WTS::m_WTSQuerySessionInformation = 0;
pWTSEnumerateSessions WTS::m_WTSEnumerateSessions = 0;
pWTSFreeMemory WTS::m_WTSFreeMemory = 0;

volatile bool WTS::m_initialized = false;

HANDLE WTS::m_userProcessToken = INVALID_HANDLE_VALUE;

LocalMutex WTS::m_mutex;

DWORD WTS::getActiveConsoleSessionId(LogWriter *log)
{
  AutoLock l(&m_mutex);
  DWORD id;

  if (!m_initialized) {
    initialize(log);
  }

  if (m_WTSGetActiveConsoleSessionId == 0) {
    return 0;
  }
  id = m_WTSGetActiveConsoleSessionId();

  log->debug("Active console session Id: {}", id);

  return id;
}

DWORD WTS::getRdpSessionId(LogWriter *log)
{
  AutoLock l(&m_mutex);

  if (!m_initialized) {
    initialize(log);
  }

  if (m_WTSEnumerateSessions == 0) {
    return 0;
  }
  
  PWTS_SESSION_INFO sessionInfo = 0;
  DWORD count = 0;
  DWORD sessionId = 0;

  if (m_WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfo, &count)) {
    for (DWORD i = 0; i < count; i++) {
      if (sessionInfo[i].State == WTSActive) {
        ::string sessionName(sessionInfo[i].pWinStationName);
        log->debug("Enumerate Sessions, Id: {}, Name: {}", sessionInfo[i].SessionId, sessionName);
        sessionName.make_lower();
        if (sessionName.find("rdp") != 0) {
          sessionId = (DWORD)sessionInfo[i].SessionId;
          log->debug("RDP Session selected, Id: {}", sessionId);
        }
      }
    }
    wtsFreeMemory(sessionInfo);
  }
  return sessionId;
}


bool WTS::SessionIsRdpSession(DWORD sessionId, LogWriter *log)
{
  {
    AutoLock l(&m_mutex);

    if (!m_initialized) {
      initialize(log);
    }
  }
  bool res = false;
  if (m_WTSQuerySessionInformation == 0) {
    return res;
  }

  LPWSTR *buffer;
  DWORD byteCount(0);

  if (m_WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionId,
    WTSWinStationName, &buffer, &byteCount) == 0) {
    return res;
  }
  ::string sessionName((TCHAR *)buffer);
  sessionName.make_lower();
  if (sessionName.find("rdp") != 0) {
    res = true;
  }
  wtsFreeMemory(buffer);
  return res;
}


HANDLE WTS::queryConsoleUserToken(LogWriter *log)
{
  DWORD sessionId = getActiveConsoleSessionId(log);
  return sessionUserToken(sessionId, log);
}

HANDLE WTS::sessionUserToken(DWORD sessionId, LogWriter* log)
{
  HANDLE token = NULL;
  {
    AutoLock l(&m_mutex);

    if (!m_initialized) {
      initialize(log);
    }
  }

  AutoLock l(&m_mutex);

  if (m_WTSQueryUserToken != 0) {
    if (!m_WTSQueryUserToken(sessionId, &token)) {
      throw SystemException("WTSQueryUserToken error:");
    }
  }
  else {
    if (m_userProcessToken == INVALID_HANDLE_VALUE) {
      throw SystemException("No console user process id specified");
    }
    if (!DuplicateTokenEx(m_userProcessToken, 0, NULL, SecurityImpersonation,
      TokenPrimary, &token)) {
      throw SystemException("Could not duplicate token");
    }
  }
  return token;
}


::string WTS::getCurrentUserName(LogWriter *log)
{

  DWORD sessionId = getActiveConsoleSessionId(log);
  return getUserName(sessionId, log);
}

::string WTS::getUserName(DWORD sessionId, LogWriter* log)
{
  ::string userName;
  if (m_WTSQuerySessionInformation == 0) {
    return userName;
  }

  LPTSTR* buffer;
  DWORD byteCount;
  if (m_WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionId,
    WTSUserName, &buffer, &byteCount) != 0) {
    userName= (TCHAR*)buffer;
    wtsFreeMemory(buffer);
  }
  return userName;
}

bool WTS::sessionIsLocked(DWORD sessionId, LogWriter* log)
{
#ifndef UNICODE
  return false;
#endif

  if (m_WTSQuerySessionInformation == 0) {
    return false;
  }

  PWTSINFOEXW buffer = 0;
  DWORD byteCount;
  if (m_WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionId,
    WTSSessionInfoEx, (LPWSTR**)&buffer, &byteCount) == 0) {
    return false;
  }
  if (buffer->Level != 1) {
    wtsFreeMemory(buffer);
    return false;
  }
  WTSINFOEX_LEVEL1_W info = buffer->Data.WTSInfoExLevel1;
  LONG locked = info.SessionFlags;
  wtsFreeMemory(buffer);
  // reverse for Windows Server 2008 R2 and Windows 7
  if (::system()->node()->_windows_isWin7()) {
    if (locked == WTS_SESSIONSTATE_UNLOCK) {
      return true;
    } 
	  return false;
  }
  if (locked == WTS_SESSIONSTATE_LOCK) {
    return true;
  }
  return false;
}

void WTS::wtsFreeMemory(void *buffer)
{
  m_WTSFreeMemory(buffer);
}

void WTS::defineConsoleUserProcessId(DWORD userProcessId)
{
  HANDLE procHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, userProcessId);

  if (procHandle == 0) {
    throw SystemException();
  }

  HANDLE userProcessToken;

  if (!OpenProcessToken(procHandle, TOKEN_ALL_ACCESS, &userProcessToken)) {
    CloseHandle(procHandle);
    throw SystemException();
  }

  CloseHandle(procHandle);

  AutoLock l(&m_mutex);

  if (m_userProcessToken != 0) {
    CloseHandle(m_userProcessToken);
  }

  m_userProcessToken = userProcessToken;
}

void WTS::duplicatePipeClientToken(HANDLE pipeHandle)
{
  PipeImpersonatedThread impThread(pipeHandle);
  impThread.resume();
  impThread.waitUntilImpersonated();
  if (!impThread.getImpersonationSuccess()) {
    ::string faultReason, errMessage;
    faultReason = impThread.getFaultReason();
    errMessage.format("Can't impersonate thread by pipe handle: {}",
                      faultReason);
    throw ::remoting::Exception(errMessage);
  }

  HANDLE threadHandle = OpenThread(THREAD_QUERY_INFORMATION, FALSE,
                                   impThread.getThreadId());
  if (threadHandle == 0) {
    throw SystemException("Can't open thread to duplicate"
                          " impersonate token");
  }
  try {
    HANDLE userThreadToken;
    if (OpenThreadToken(threadHandle, TOKEN_ALL_ACCESS, TRUE, &userThreadToken) == 0) {
      throw SystemException("Can't open process token to duplicate"
                            " impersonate token");
    }
    try {
      HANDLE userThreadDuplicatedToken;
      if (DuplicateTokenEx(userThreadToken, 0, 0, SecurityImpersonation,
                           TokenPrimary, &userThreadDuplicatedToken) == 0) {
        throw SystemException("Can't duplicate token from impersonated"
                              " to a named pipe client token");
      }
      if (m_userProcessToken != INVALID_HANDLE_VALUE) {
        CloseHandle(m_userProcessToken);
      }
      m_userProcessToken = userThreadDuplicatedToken;
    } catch (...) {
      CloseHandle(userThreadToken);
      throw;
    }
    CloseHandle(userThreadToken);
  } catch (...) {
    CloseHandle(threadHandle);
    throw;
  }
  CloseHandle(threadHandle);
}

void WTS::initialize(LogWriter *log)
{
  _ASSERT(!m_initialized);

  try {
    m_kernel32Library = new DynamicLibrary("Kernel32.dll");
    m_WTSGetActiveConsoleSessionId = (pWTSGetActiveConsoleSessionId)m_kernel32Library->getProcAddress("WTSGetActiveConsoleSessionId");
  } catch (::exception &e) {
    log->error("Can't load the Kernel32.dll library: {}", e.get_message());
  }
  try {
    m_wtsapi32Library = new DynamicLibrary("Wtsapi32.dll");
    m_WTSQueryUserToken = (pWTSQueryUserToken)m_wtsapi32Library->getProcAddress("WTSQueryUserToken");
#ifdef UNICODE
    m_WTSQuerySessionInformation = (pWTSQuerySessionInformation)m_wtsapi32Library->getProcAddress("WTSQuerySessionInformationW");
    m_WTSEnumerateSessions = (pWTSEnumerateSessions)m_wtsapi32Library->getProcAddress("WTSEnumerateSessionsW");
#else
    m_WTSQuerySessionInformation = (pWTSQuerySessionInformation)m_wtsapi32Library->getProcAddress("WTSQuerySessionInformationA");
    m_WTSEnumerateSessions = (pWTSEnumerateSessions)m_wtsapi32Library->getProcAddress("WTSEnumerateSessionsA");
#endif
    m_WTSFreeMemory = (pWTSFreeMemory)m_wtsapi32Library->getProcAddress("WTSFreeMemory");
  } catch (::exception &e) {
    log->error("Can't load the Wtsapi32.dll library: {}", e.get_message());
  }

  m_initialized = true;
}

HANDLE currentProcessUserToken(LogWriter* log)
{
  HANDLE token = NULL;
  HANDLE procHandle = GetCurrentProcess();
  log->debug("Try OpenProcessToken(%p, , )", (void*)procHandle);
  if (OpenProcessToken(procHandle, TOKEN_DUPLICATE, &token) == 0) {
    throw SystemException();
  }
  return token;
}


HANDLE WTS::duplicateCurrentProcessUserToken(bool rdpEnabled, LogWriter* log)
{
  DWORD rdpSession = 0;
  DWORD activeSession = 0;
  DWORD sessionId = 0;
  bool rdp = false;

  if (rdpEnabled) {
    rdpSession = getRdpSessionId(log);
    if (rdpSession) {
      rdp = true;
    }
  }
  activeSession = getActiveConsoleSessionId(log);

  log->debug("rdpSession user name: {}", getUserName(rdpSession, log));
  log->debug("activeSession user name: {}", getUserName(activeSession, log));

  if (rdp) {
    sessionId = rdpSession;
    log->information("Connect as RDP user at {} session", sessionId);
  } else {
    sessionId = getActiveConsoleSessionId(log);
    log->information("Connect as current user at {} session", sessionId);
  }
  log->debug("Session user name: {}", getUserName(sessionId, log));

  HANDLE token;

  if (rdp && !sessionIsLocked(sessionId, log)) {
    token = sessionUserToken(sessionId, log);
  } else {
    token = currentProcessUserToken(log);
  }

  HANDLE userToken = duplicateUserImpersonationToken(token, sessionId, log);
  CloseHandle(token);

  return userToken;
}

HANDLE WTS::duplicateUserImpersonationToken(HANDLE token, DWORD sessionId, LogWriter* log)
{
  HANDLE userToken;

  log->debug("Try DuplicateTokenEx(%p, , , , , )", (void*)token);
  if (DuplicateTokenEx(token,
    MAXIMUM_ALLOWED,
    0,
    SecurityImpersonation,
    TokenPrimary,
    &userToken) == 0) {
    throw SystemException();
  }

  log->debug("Try SetTokenInformation(%p, , , )", (void*)userToken);
  if (SetTokenInformation(userToken,
    (TOKEN_INFORMATION_CLASS)TokenSessionId,
    &sessionId,
    sizeof(sessionId)) == 0) {
    throw SystemException();
  }
  // Fix Windows 8/8.1 UIAccess restrictions (Alt-Tab) for server as service
  // http://stackoverflow.com/questions/13972165/pressing-winx-alt-tab-programatically
  // For application we need to set /uiAccess='true' in linker manifest, sign binary 
  // and run from "Program Files/"

  DWORD uiAccess = 1; // Nonzero enables UI control
  log->debug("Try SetTokenInformation(%p, , , ) with UIAccess=1", (void*)userToken);

  if (SetTokenInformation(userToken,
    (TOKEN_INFORMATION_CLASS)TokenUIAccess,
    &uiAccess,
    sizeof(uiAccess)) == 0) {
    log->information("Can't set UIAccess=1, ignore it");
  }
  ::string name = getTokenUserName(userToken);
  log->debug("duplicate user token for user: {}, session ID: {}", name, sessionId);

  return userToken;
}

::string WTS::getTokenUserName(HANDLE token) {
  ::string name;
  DWORD tokenSize = 0;
  GetTokenInformation(token, TokenUser, NULL, 0, &tokenSize);

  if (tokenSize <= 0) {
    return name;
  }

  BYTE* data = new BYTE[tokenSize];
  GetTokenInformation(token, TokenUser, data, tokenSize, &tokenSize); // 3- GetTokenInformation
  TOKEN_USER* pUser = (TOKEN_USER*)data;
  PSID pSID = pUser->User.Sid;
  DWORD userSize = 0;
  DWORD domainSize = 0;
  SID_NAME_USE sidName;
  LookupAccountSid(NULL, pSID, NULL, &userSize, NULL, &domainSize, &sidName);
  TCHAR* user = new TCHAR[userSize + 1];
  TCHAR* domain = new TCHAR[domainSize + 1];
  LookupAccountSid(NULL, pSID, user, &userSize, domain, &domainSize, &sidName); 
  user[userSize] = _T('\0');
  name= user;
  delete[] data;
  delete[] domain;
  delete[] user;
  return name;
}

WTS::WTS()
{
}
