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


#include "acme/subsystem/node/Shell.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"


//#include "SystemException.h"
namespace windows
{
   namespace subsystem

   {
      /**
       * Wrapper over WinAPI shell functions.
       *
       * @author enikey.
       */
      class CLASS_DECL_ACME Shell :
      virtual public ::subsystem::Shell
      {
      public:


         //private:
         /**
          * Don't allow instanizing of class.
          */
         Shell();
         ~Shell() override;

         /**
          * Runs application as administrator and waits until execution finished.
          * @param pathToFile path to executable.
          * @param parameters execute parameters.
          * @throws SystemException on fail.
          */
         void runAsAdmin(const ::file::path & pathToFile, const ::scoped_string & scopedstrParameters) override;

         /**
          * Opens file with default action specified in Windows.
          * @param file target file.
          * @param parameters parameters.
          * @param workDirectory working directory.
          * @throws SystemException on fail.
          */
         void open(const ::scoped_string & scopedstrFile,
                          const ::scoped_string & scopedstrParameters,
                          const ::scoped_string & scopedstrworkDirectory) override;
      };
   } // namespace windows
} // namespace windows