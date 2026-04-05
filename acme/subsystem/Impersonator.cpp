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
#include "framework.h"
#include "acme/_operating_system.h"
#include "Impersonator.h"

#include <crtdbg.h>

#include "remoting/remoting_common/win_system/WTS.h"

Impersonator::Impersonator(LogWriter *log)
: m_token(INVALID_HANDLE_VALUE),
  m_dupToken(INVALID_HANDLE_VALUE),
  m_log(log)
{
}

Impersonator::~Impersonator()
{
}

void Impersonator::impersonateAsLoggedUser()
{
  HANDLE token = WTS::queryConsoleUserToken(m_log);
  impersonateAsUser(token);
}

void Impersonator::impersonateAsUser(HANDLE token)
{
  if (m_token != INVALID_HANDLE_VALUE) {
    CloseHandle(m_token);
  }
  m_token = token;

  ::string name = WTS::getTokenUserName(m_token);
  m_log->debug("impersonate as user: {}", name);

  if ((!DuplicateToken(m_token, SecurityImpersonation, &m_dupToken))) {
    throw SystemException("could not DuplicateToken");
  }
  if (!ImpersonateLoggedOnUser(m_dupToken)) {
    throw SystemException("could not ImpersonateLoggedOnUser");
  }

}

void Impersonator::impersonateAsCurrentProcessUser(bool rdpEnabled)
{
  HANDLE token = WTS::duplicateCurrentProcessUserToken(rdpEnabled, m_log);
  impersonateAsUser(token);
}


void Impersonator::revertToSelf()
{
  if (m_dupToken != INVALID_HANDLE_VALUE) {
    CloseHandle(m_dupToken);
  }

  if (m_token != INVALID_HANDLE_VALUE) {
    CloseHandle(m_token);
  }

  m_dupToken = INVALID_HANDLE_VALUE;
  m_token = INVALID_HANDLE_VALUE;

  if (!RevertToSelf()) {
    throw SystemException("could not RevertToSelf");
  }
}

bool Impersonator::sessionIsLocked(bool rdpEnabled)
{
  DWORD id = 0;
  if (rdpEnabled) {
    id = WTS::getRdpSessionId(m_log);
  }
  if (id == 0) {
    id = WTS::getActiveConsoleSessionId(m_log);
  }
  return WTS::sessionIsLocked(id, m_log);
}