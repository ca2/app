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


#include "acme/subsystem/_common_header.h"

#include "acme/subsystem/Exception.h"

namespace subsystem
{
   /**
   Dynamic library class.
   */
   class CLASS_DECL_ACME DynamicLibraryInterface :
      virtual public ::subsystem::particle_interface

   {
   public:
      /**
      Load dynamic library with specified filename.
      @param filename path to library file.
      @throws ::remoting::Exception on error.
      */
      //DynamicLibraryInterface(const ::scoped_string & scopedstrFilename);
      //DynamicLibrary();
      virtual ~DynamicLibraryInterface() = 0;


      virtual void initialize_dynamic_library(const ::scoped_string & scopedstrFilename) = 0;

      // Use the init() function after default constructor calling to load
      // a library before the getProcAddress() function calling.
      virtual void init(const ::scoped_string & scopedstrFilename) =0;

      /**
      Gets procedure address.
      @param procName procedure name.
      @return address of procedure or 0 if failed.
      */
      //FARPROC getProcAddress(const char *procName);
      virtual void * getProcAddress(const char *procName) = 0;

   // protected:
   //    HMODULE m_module;
   };


   /**
Dynamic library class.
*/
   class CLASS_DECL_ACME DynamicLibrary :
   virtual public ::subsystem::composite< DynamicLibraryInterface>
   {
   public:
      /**
      Load dynamic library with specified filename.
      @param filename path to library file.
      @throws ::remoting::Exception on error.
      */
      //DynamicLibrary(const ::scoped_string & scopedstrFilename);
      DynamicLibrary();
      ~DynamicLibrary() override;


      void initialize_dynamic_library(const ::scoped_string & scopedstrFilename) override;

      // Use the init() function after default constructor calling to load
      // a library before the getProcAddress() function calling.
      void init(const ::scoped_string & scopedstrFilename) override;

      /**
      Gets procedure address.
      @param procName procedure name.
      @return address of procedure or 0 if failed.
      */
      void * getProcAddress(const char *procName) override;

   // protected:
   //    HMODULE m_module;
   };



} // namespace subsystem


