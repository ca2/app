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

//#ifndef _SECURITY_IDENTIFIER_H_
//#define _SECURITY_IDENTIFIER_H_
#pragma once


#include "acme/subsystem/node/security/SecurityIdentifier.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"


namespace windows
{
   namespace subsystem
   {
      // /**
      //  * Top-level authority of a security identifier (SID).
      //  */
      // enum Authority {
      //    /**
      //     * It only defines the Everyone well-known-SID.
      //     */
      //    Everyone,
      //    /**
      //     * It defines only the Local well-known-SID.
      //     */
      //    Local,
      //    /**
      //     * Specifies the Creator SID authority.
      //     * It defines the Creator Owner, Creator Group, and Creator Owner Server
      //     * well-known-SIDs.
      //     * These SIDs are used as placeholders in an access control list (ACL) and are replaced by the user,
      //     * group, and machine SIDs of the security principal.
      //     */
      //    Creator,
      //    /**
      //     * Specifies the Windows NT security subsystem SID authority. It defines all other SIDs in the forest.
      //     */
      //    Nt
      //  };

      /**
       * A SID consists of the following components:
       * The revision level of the SID structure;
       * A 48-bit identifier authority value that identifies the authority that issued the SID.
       * variable number of subauthority or relative identifier (RID) values that uniquely
       * identify the trustee relative to the authority that issued the SID.
       */
      class SecurityIdentifier :
         virtual public ::subsystem::implementation< ::subsystem::SecurityIdentifierInterface >
      {
      public:
         /**
          * Creates security identifier from WinAPI SID struct.
          * @throws SystemException if copy failed.
          */
         //SecurityIdentifier(SID *sid);
         /**
          * Creates security identifier by a string.
          * @throws SystemException if copy failed.
          */
         //SecurityIdentifier(const ::scoped_string & scopedstr);

         SecurityIdentifier();

         /**
          * Destructor.
          */
         ~SecurityIdentifier() override;

         void initialize_security_identifier(const scoped_string& scopedstr) override;

         virtual void initialize_security_identifier(SID *sid);

         /**
          * Validates a security identifier (SID) by verifying that the revision number is within a known range,
          * and that the number of subauthorities is less than the maximum.
          * @return true if the SID structure is valid, false otherwise.
          */
         bool isValid() override;

         /**
          * Converts a security identifier (SID) to a string.
          * @param sidString string storage where result will be stored.
          * @throws SystemException if error occurs.
          */
         void toString(::string & str) override;

         /**
          * Returns SID of process owner.
          * @param processHandle handle of process.
          * @return SID of owner of specified process.
          * @throws SystemException if operation failed.
          * @fixme stub (returns invalid SID).
          */
         static SecurityIdentifier *getProcessOwner(HANDLE processHandle);


         /**
          * Returns pointer to WinAPI SID structure.
          */
         SID *getSid() const;

         //private:
         /**
          * Don't allow to create security identifiers by using default constructor.
          */
         //SecurityIdentifier();

         // Returned pointer to a sid must be freed by the LocalFree() function calls
         static void getSidByString(const ::scoped_string & scopedstr, PSID *sid);

      //private:
         SID *m_sid;
      };
   }// namespace subsystem

   //#endif
} // namespace windows
