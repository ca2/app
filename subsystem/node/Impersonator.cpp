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

// #include aaa_<crtdbg.h>

//#include "remoting/remoting/win_system/WTS.h"

namespace subsystem
{



   //Impersonator::Impersonator()
   //// : m_token(INVALID_HANDLE_VALUE),
   ////   m_dupToken(INVALID_HANDLE_VALUE),
   ////   m_plogwriter(plogwriter)
   //{
   //}

   //Impersonator::~Impersonator()
   //{
   //}

   ////    Impersonator::Impersonator(LogWriter *plogwriter)
   //// : m_token(INVALID_HANDLE_VALUE),
   ////   m_dupToken(INVALID_HANDLE_VALUE),
   ////   m_plogwriter(plogwriter)
   //// {
   //// }

   //void Impersonator::impersonateAsLoggedUser()
   //{
   //   m_pparticleThis->impersonateAsLoggedUser();
   //   //
   //   // HANDLE token = WTS::queryConsoleUserToken(m_plogwriter);
   //   // impersonateAsUser(token);
   //}


   //void Impersonator::initialize_impersonator(LogWriter *plogwriter)
   //{

   //   return m_pparticleThis->initialize_impersonator(plogwriter);

   //}


   //// void Impersonator::impersonateAsUser(HANDLE token)
   //// {
   ////   if (m_token != INVALID_HANDLE_VALUE) {
   ////     CloseHandle(m_token);
   ////   }
   ////   m_token = token;
   ////
   ////   ::string name = WTS::getTokenUserName(m_token);
   ////   m_plogwriter->debug("impersonate as user: {}", name);
   ////
   ////   if ((!DuplicateToken(m_token, SecurityImpersonation, &m_dupToken))) {
   ////     throw SystemException("could not DuplicateToken");
   ////   }
   ////   if (!ImpersonateLoggedOnUser(m_dupToken)) {
   ////     throw SystemException("could not ImpersonateLoggedOnUser");
   ////   }
   ////
   //// }

   //void Impersonator::impersonateAsCurrentProcessUser(bool rdpEnabled)
   //{
   //   m_pparticleThis->impersonateAsCurrentProcessUser(rdpEnabled);
   //   //}
   //   // HANDLE token = WTS::duplicateCurrentProcessUserToken(rdpEnabled, m_plogwriter);
   //   // impersonateAsUser(token);
   //}


   //void Impersonator::revertToSelf()
   //{
   //   m_pparticleThis->revertToSelf();
   //   // }
   //   //   if (m_dupToken != INVALID_HANDLE_VALUE) {
   //   //     CloseHandle(m_dupToken);
   //   //   }
   //   //
   //   //   if (m_token != INVALID_HANDLE_VALUE) {
   //   //     CloseHandle(m_token);
   //   //   }
   //   //
   //   //   m_dupToken = INVALID_HANDLE_VALUE;
   //   //   m_token = INVALID_HANDLE_VALUE;
   //   //
   //   //   if (!RevertToSelf()) {
   //   //     throw SystemException("could not RevertToSelf");
   //   //   }
   //}

   //bool Impersonator::sessionIsLocked(bool rdpEnabled)
   //{
   //   return m_pparticleThis->sessionIsLocked(rdpEnabled);
   //   //}
   //   // DWORD id = 0;
   //   // if (rdpEnabled) {
   //   //   id = WTS::getRdpSessionId(m_plogwriter);
   //   // }
   //   // if (id == 0) {
   //   //   id = WTS::getActiveConsoleSessionId(m_plogwriter);
   //   // }
   //   // return WTS::sessionIsLocked(id, m_plogwriter);
   //}



} // namespace subsystem



