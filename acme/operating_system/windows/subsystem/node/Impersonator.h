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

#pragma once


#include "acme/subsystem/node/Impersonator.h"
#include "acme/subsystem/node/SystemException.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"



namespace windows
{
   namespace subsystem
   {

      /**
      Class for impersonating current process as user that logged on current
      console session.
      @remark: can work only in XP and later cause it uses WTSQueryUserToken function.
      */
      class CLASS_DECL_ACME Impersonator :
      virtual public ::subsystem::Impersonator
      {
      public:
         //Impersonator(LogWriter *log);
         Impersonator();
         ~Impersonator() override;

         void initialize_impersonator(::subsystem::LogWriter *log) override;

         /**
         Impersonates calling process as user that logged on current console session.
         @throws SystemException if impersonation fails.
         */
         void impersonateAsLoggedUser() override;

         /**
         Impersonates calling process as user with given token.
         @throws SystemException if impersonation fails.
         */
         void impersonateAsCurrentProcessUser(bool rdpEnabled) override;

         /**
         Cancels effect of impersonateAsLoggedUser method call.
         @throws SystemException on fail.
         */
         void revertToSelf() override;

         bool sessionIsLocked(bool rdpEnabled) override;

         //protected:
         virtual void impersonateAsUser(HANDLE token);

         HANDLE m_token;
         HANDLE m_dupToken;
         //
         ::pointer < ::subsystem::LogWriter > m_plogwriter;
      };


   } // namespace subsystem
}// namespace windows


