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

// #include aaa_<crtdbg.h>

namespace subsystem
{
   SystemException::SystemException()
   : ::subsystem::Exception(),m_errorcode(::operating_system::last_error_code())
   {
      createMessage(0, m_errorcode);
   }

   SystemException::SystemException(const ::error_code & errorcode)
   : ::subsystem::Exception(), m_errorcode(errorcode)
   {
      createMessage(0, m_errorcode);
   }

   SystemException::SystemException(const ::scoped_string & scopedstrUserMessage)
   : ::subsystem::Exception(), m_errorcode(::operating_system::last_error_code())
   {
      createMessage(scopedstrUserMessage, m_errorcode);
   }

   SystemException::SystemException(const ::scoped_string & scopedstrUserMessage, const ::error_code & errorcode)
   : ::subsystem::Exception(), m_errorcode(errorcode)
   {
      createMessage(scopedstrUserMessage, m_errorcode);
   }

   SystemException::~SystemException()
   {
   }

   ::error_code SystemException::getErrorCode() const
   {
      return m_errorcode;
   }

   ::string SystemException::getSystemErrorDescription() const
   {
      return m_strSystemMessage;
   }

   void SystemException::createMessage(const ::scoped_string & scopedstrUserMessage, const ::error_code & errorcode)
   {

      ::string strMessage(scopedstrUserMessage);
      if (scopedstrUserMessage.is_empty()  && errorcode.is_clear()) {
         strMessage = "Thrown a system exception but the program"
                       " cannot identify the corresponding system error.";
      }

      // Get description of windows specific error.

      ::string strErrorMessage = errorcode.get_error_message();

      bool formatMessageOk = strErrorMessage.has_character();

      // Remove bad characters.

      const char badCharacters[] = { 10, 13, '\n', '\t', '\0' };

      strErrorMessage.erase_any_character_in(badCharacters);

      strErrorMessage.ends_eat(".");

      // Create system error part of scopedstrMessage.

      if (formatMessageOk) {
         m_strSystemMessage.format("{} (error code {})",
           strErrorMessage,
           errorcode.m_iOsError);
      } else {
         m_strSystemMessage.format("Error code {}", errorcode.m_iOsError);
      }

      // Use user scopedstrMessage if specified.

      if (m_errorcode.is_set()) {
         if (strErrorMessage.is_empty()) {
            m_strMessage = m_strSystemMessage;
         } else {
            m_strMessage.format("{} (system error: {})",
              scopedstrUserMessage,
              m_strSystemMessage);
         }
      } else {
         m_strMessage = scopedstrUserMessage;
         m_strSystemMessage = scopedstrUserMessage;
      }
   }
} // namespace subsystem
