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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "acme/subsystem/node/SystemException.h"
#include "acme/operating_system/windows/subsystem/subsystem.h"
#include "SecurityIdentifier.h"
#include "../ProcessHandle.h"
#include <Sddl.h>
#include <crtdbg.h>
#include <winnt.h>


namespace windows
{
   namespace subsystem
   {
      // SecurityIdentifier::SecurityIdentifier(SID *sid)
      // {
      //    initialize_security_identifier(sid);
      // }
      //
      // SecurityIdentifier::SecurityIdentifier(const ::scoped_string & scopedstr)
      // : m_sid(0)
      // {
      //    initialize_security_identifier(scopedstr);
      // }

      SecurityIdentifier::SecurityIdentifier():
      m_sid{}

      {

      }


      SecurityIdentifier::~SecurityIdentifier()
      {
         LocalFree(m_sid);
      }

      void SecurityIdentifier::initialize_security_identifier(SID * sid)
      {
         m_sid = (SID *)LocalAlloc(LPTR, SECURITY_MAX_SID_SIZE);

         memset(m_sid, 0, SECURITY_MAX_SID_SIZE);

         if (!CopySid(SECURITY_MAX_SID_SIZE, m_sid, sid)) {
            throw ::subsystem::SystemException();
         }

      }

      void SecurityIdentifier::initialize_security_identifier(const ::scoped_string & scopedstr)
      {
         getSidByString(scopedstr, (PSID *)&m_sid);
      }

      bool SecurityIdentifier::isValid()
      {
         return IsValidSid(m_sid) == TRUE;
      }

      void SecurityIdentifier::toString(::string &sidString)
      {
         TCHAR *localAllocatedSidString;

         if (ConvertSidToStringSid(m_sid, &localAllocatedSidString) == FALSE) {
            throw ::subsystem::SystemException();
         }

         sidString = localAllocatedSidString;

         LocalFree(localAllocatedSidString);
      }

      // FIXME: refactor this method.
      ::pointer < ::subsystem::SecurityIdentifier>ProcessHandle::getProcessOwner()
      {

         HANDLE processHandle = this->m_hProcess;
         HANDLE procToken;

         if (OpenProcessToken(processHandle, TOKEN_QUERY, &procToken)) {
            try {
               char buffer[1024];
               DWORD retLen = 0;
               if (!GetTokenInformation(procToken, TokenUser, &buffer, sizeof(buffer), &retLen)) {
                  throw ::subsystem::SystemException();
               }
               CloseHandle(procToken);
               auto psecurityidentifier = create_newø< SecurityIdentifier>();

               psecurityidentifier->initialize_security_identifier((SID *)((TOKEN_USER *)buffer)->User.Sid);

               //psecurityidentifier->initialize(this);

               return psecurityidentifier;
            } catch (...) {
               CloseHandle(procToken);
               throw;
            }
            CloseHandle(procToken);
         } else {
            throw ::subsystem::SystemException();
         }
      }

      ::pointer < ::subsystem::SecurityIdentifier> subsystem::createSidFromString(const ::scoped_string & scopedstr)
      {
         auto psecurityidentifier = create_newø <SecurityIdentifier>();

         psecurityidentifier->initialize_security_identifier(scopedstr);

         return psecurityidentifier;

      }

      SID *SecurityIdentifier::getSid() const
      {
         return m_sid;
      }

      void SecurityIdentifier::getSidByString(const ::scoped_string & scopedstrSid, PSID *sid)
      {
         ::wstring wstrSid(scopedstrSid);
         if (ConvertStringSidToSid(wstrSid, sid) == FALSE) {
            throw ::subsystem::SystemException();
         }

         _ASSERT(IsValidSid(*sid));
      }
   } // namespace subsystem
} // namespace windows