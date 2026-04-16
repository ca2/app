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


#include "subsystem/_common_header.h"

#include "subsystem/node/security/SecurityIdentifier.h"
#include "subsystem/node/security/SecurityDescriptor.h"
//// #include aaa_<vector>

namespace subsystem
{

   class SecurityAttributesInterface :
   virtual public ::particle_base
   {
   public:
      //SecurityAttributes();
      //virtual ~SecurityAttributesInterface() = 0;

      // Sets the security attributes to default values. After calling this
      // function the getSecurityAttributes() function will to return zero until
      // attributes was changed by another functions.
      virtual void setDefaultAttributes()=0;

      // Sets security attributes that allow all access to all.
      virtual void shareToAllUsers()=0;

      // If immediately before was called the setDefaultAttributes() function
      // returns zero otherwise returns pointer to SECURITY_ATTRIBUTES structure.
      //SECURITY_ATTRIBUTES *getSecurityAttributes();

      // Set inheritable flag of the SECURITY_ATTRIBUTES structure to true
      virtual void setInheritable() = 0;

   // private:
   //    SECURITY_ATTRIBUTES m_securityAttributes;
   //
   //    bool m_isDefaultAttributes;
   //
   //    /**
   //     * Members that needed for shareToAllUsers() method.
   //     */
      //SecurityDescriptor m_sd;
   };

   //using SecurityAttributesInterface = particle_interface<SecurityAttributesInterface>;

   class CLASS_DECL_SUBSYSTEM SecurityAttributesComposite :
   virtual public composite<SecurityAttributesInterface>
   {
   public:

      implement_compositeø(SecurityAttributes, securityattributes)

      //SecurityAttributes();
      //~SecurityAttributes() override;

      // Sets the security attributes to default values. After calling this
      // function the getSecurityAttributes() function will to return zero until
      // attributes was changed by another functions.
      void setDefaultAttributes() override
      {

         m_psecurityattributes->setDefaultAttributes();

      }



      // Sets security attributes that allow all access to all.
      void shareToAllUsers() override
      {

         m_psecurityattributes->shareToAllUsers();

      }

      // If immediately before was called the setDefaultAttributes() function
      // returns zero otherwise returns pointer to SECURITY_ATTRIBUTES structure.
      //SECURITY_ATTRIBUTES *getSecurityAttributes();

      // Set inheritable flag of the SECURITY_ATTRIBUTES structure to true
      void setInheritable() override
      {

         m_psecurityattributes->setInheritable();

      }

      // private:
      //    SECURITY_ATTRIBUTES m_securityAttributes;
      //
      //    bool m_isDefaultAttributes;
      //
      //    /**
      //     * Members that needed for shareToAllUsers() method.
      //     */
      //SecurityDescriptor m_sd;
   };

   //// __SECURITYATTRIBUTES_H__
} // namespace subsystem


