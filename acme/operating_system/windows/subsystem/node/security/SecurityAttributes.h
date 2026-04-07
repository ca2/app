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
#pragma once


#include "acme/subsystem/node/security/SecurityAttributes.h"
#include "acme/operating_system/windows/subsystem/node/security/SecurityIdentifier.h"
#include "acme/operating_system/windows/subsystem/node/security/SecurityDescriptor.h"


namespace windows
{
   namespace subsystem
   {
      class CLASS_DECL_ACME SecurityAttributes :
      virtual  public ::subsystem::implementation<::subsystem::SecurityAttributesInterface>
      {
      public:
         SecurityAttributes();
          ~SecurityAttributes() override;

         // Sets the security attributes to default values. After calling this
         // function the getSecurityAttributes() function will to return zero until
         // attributes was changed by another functions.
         void setDefaultAttributes() override;

         // Sets security attributes that allow all access to all.
         void shareToAllUsers() override;

         // If immediately before was called the setDefaultAttributes() function
         // returns zero otherwise returns pointer to SECURITY_ATTRIBUTES structure.
         SECURITY_ATTRIBUTES *_getSecurityAttributes();

         // Set inheritable flag of the SECURITY_ATTRIBUTES structure to true
         void setInheritable() override;

      //private:
         SECURITY_ATTRIBUTES m_securityAttributes;

         bool m_isDefaultAttributes;

         /**
          * Members that needed for shareToAllUsers() method.
          */
         SecurityDescriptor m_sd;
      };

      //// __SECURITYATTRIBUTES_H__
   } // namespace subsystem
} // namespace windows

