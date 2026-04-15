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
#pragma once


#include "subsystem/_common_header.h"
#include "subsystem/node/SystemException.h"
////#include "subsystem/particle.h"
//// #include aaa_<AccCtrl.h>

namespace subsystem
{
   /**
    * Contains the security information associated with an object.
    */
   class SecurityDescriptorSlice :
        virtual public ::particle_base
   {
   public:
      /**
       * Creates new security descriptor.
       * @remark created security descriptor have no system access control list (SACL),
       * no discretionary access control list (DACL), no owner, no primary group,
       * and all control flags set to FALSE (NULL). Thus, except for its revision level, it is empty
       */
      //SecurityDescriptor();
      //virtual ~SecurityDescriptorInterface() = 0;

      /**
       * Sets rules list for security descriptor.
       * It creates dalc from specified rules and link created dalc with security
       * descriptor using setUserDacl method.
       * @param count count of rules in rules array.
       * @param rules rules array.
       * @throws SystemException on fail.
       */
      //void setRulesAsDacl(size_t count,
        //                  EXPLICIT_ACCESS *rules) throw(SystemException);

      /**
       * Sets information in a discretionary access control list (DACL).
       * Built-in DACL value in acl param cannot be passed.
       * @param acl access control list.
       * @throws SystemException on fail.
       */
      //void setUserDacl(ACL *acl) throw(SystemException);

      /**
      Marks the security descriptor as having no owner.
      */
      virtual void clearOwner() = 0;

      /**
       * Determines whether the components of a security descriptor are valid.
       */
      virtual bool isValid() =0;

      /**
       Returns pointer to WinAPI security descriptor.
       */
   //    SECURITY_DESCRIPTOR *getSD();
   //
   // private:
   //    SECURITY_DESCRIPTOR m_sd;
   };

    using SecurityDescriptorInterface = particle_interface<SecurityDescriptorSlice>;

   /**
 * Contains the security information associated with an object.
 */
   class CLASS_DECL_SUBSYSTEM SecurityDescriptorComposite :
   virtual public composite<SecurityDescriptorSlice>
   {
   public:


       implement_compositeø(SecurityDescriptor, securitydescriptor)

      /**
       * Creates new security descriptor.
       * @remark created security descriptor have no system access control list (SACL),
       * no discretionary access control list (DACL), no owner, no primary group,
       * and all control flags set to FALSE (NULL). Thus, except for its revision level, it is empty
       */
        //SecurityDescriptor();
       //~SecurityDescriptor() override;

      /**
       * Sets rules list for security descriptor.
       * It creates dalc from specified rules and link created dalc with security
       * descriptor using setUserDacl method.
       * @param count count of rules in rules array.
       * @param rules rules array.
       * @throws SystemException on fail.
       */
      //void setRulesAsDacl(size_t count,
      //                  EXPLICIT_ACCESS *rules) throw(SystemException);

      /**
       * Sets information in a discretionary access control list (DACL).
       * Built-in DACL value in acl param cannot be passed.
       * @param acl access control list.
       * @throws SystemException on fail.
       */
      //void setUserDacl(ACL *acl) throw(SystemException);

      /**
      Marks the security descriptor as having no owner.
      */
      void clearOwner() override;

      /**
       * Determines whether the components of a security descriptor are valid.
       */
      bool isValid() override;

      /**
       Returns pointer to WinAPI security descriptor.
       */
      //    SECURITY_DESCRIPTOR *getSD();
      //
      // private:
      //    SECURITY_DESCRIPTOR m_sd;
   };

    class SecurityDescriptor :
    virtual public aggregate < SecurityDescriptorComposite >
    {
    public:

        implement_baseø(SecurityDescriptor);

    };


} // namespace subsystem



