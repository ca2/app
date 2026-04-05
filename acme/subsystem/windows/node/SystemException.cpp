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
#include "SystemException.h"

#include <crtdbg.h>

SystemException::SystemException()
: ::remoting::Exception(), m_errcode(GetLastError())
{
  createMessage(0, m_errcode);
}

SystemException::SystemException(int errcode)
: ::remoting::Exception(), m_errcode(errcode)
{
  createMessage(0, m_errcode);
}

SystemException::SystemException(const ::scoped_string & scopedstrUserMessage)
: ::remoting::Exception(), m_errcode(GetLastError())
{
  createMessage(scopedstrUserMessage, m_errcode);
}

SystemException::SystemException(const ::scoped_string & scopedstrUserMessage, int errcode)
: ::remoting::Exception(), m_errcode(errcode)
{
  createMessage(scopedstrUserMessage, m_errcode);
}

SystemException::~SystemException()
{
}

int SystemException::getErrorCode() const
{
  return m_errcode;
}

::string SystemException::getSystemErrorDescription() const
{
  return m_systemMessage;
}

void SystemException::createMessage(const ::scoped_string & scopedstrUserMessage, int errcode)
{

   ::string strMessage(scopedstrUserMessage);
  if (scopedstrUserMessage.is_empty()  && errcode == ERROR_SUCCESS) {
    strMessage = "Thrown a system exception but the program"
                  " cannot identify the corresponding system error.";
  }

  // Get description of windows specific error.

  bool formatMessageOk = true;

  TCHAR buffer[1024 * 10] = {0};

  if (FormatMessage(
    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    errcode,
    MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
    (LPTSTR)&buffer[0],
    sizeof(buffer),
    NULL) == 0) {
     formatMessageOk = false;
  }

  ::string windowsErrorDescription(buffer);

  // Remove bad characters.

  const TCHAR badCharacters[] = { 10, 13, '\n', '\t', '\0' };

  windowsErrorDescription.erase_any_character_in(badCharacters);

  if (windowsErrorDescription.ends(".")) {
    windowsErrorDescription.rear_truncate(1);
  }

  // Create system error part of scopedstrMessage.

  if (formatMessageOk) {
    m_systemMessage.format("{} (error code {})",
      windowsErrorDescription,
      errcode);
  } else {
    m_systemMessage.format("Error code {}", errcode);
  }

  // Use user scopedstrMessage if specified.

  if (errcode != 0) {
    if (scopedstrUserMessage.is_empty()) {
      m_strMessage = m_systemMessage;
    } else {
      m_strMessage.format("{} (system error: {})",
        scopedstrUserMessage,
        m_systemMessage);
    }
  } else {
    m_strMessage = scopedstrUserMessage;
    m_systemMessage = scopedstrUserMessage;
  }
}
