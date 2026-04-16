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
//#include "../SystemException.h"

namespace subsystem
{
   /**
    * Contains information about executable file version info.
    */
   class VersionInfoInterface :
      virtual public ::particle_base
   {
   public:


      /**
       * Creates version info of specified file.
       * @param pathToFile path to executable file to get version info from.
       * @throws SystemException on fail.
       */
      //VersionInfo(const ::file::path & pathToFile);
      //virtual ~VersionInfoInterface() = 0;


      virtual void initialize_version_info(const ::file::path & pathToFile) = 0;
      /**
       * Returns product version info string.
       * @return product version info string.
       */
      virtual ::string getProductVersionString() const = 0;

   //private:
      /**
       * Product version as string.
       */
     // ::string m_productVersionString;
   };


    //using VersionInfoInterface= particle_interface<VersionInfoInterface>;

   /**
 * Contains information about executable file version info.
 */
   class CLASS_DECL_SUBSYSTEM VersionInfoComposite :
      virtual public composite<VersionInfoInterface >
   {
   public:

       implement_compositeø(VersionInfo)




      /**
       * Creates version info of specified file.
       * @param pathToFile path to executable file to get version info from.
       * @throws SystemException on fail.
       */
      //VersionInfo(const ::file::path & pathToFile);
      //VersionInfo();
      //~VersionInfo() override;


      void initialize_version_info(const ::file::path & pathToFile) override;
      /**
       * Returns product version info string.
       * @return product version info string.
       */
      ::string getProductVersionString() const override;

      //private:
      /**
       * Product version as string.
       */
      // ::string m_productVersionString;
   };


    class CLASS_DECL_SUBSYSTEM VersionInfo :
    virtual public aggregate< VersionInfoComposite >
    {
    public:

        implement_baseø(VersionInfo);

    };




} // namespace subsystem




