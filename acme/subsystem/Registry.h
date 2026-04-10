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


#include "RegistryKey.h"


namespace subsystem
{


   // enum enum_windows_registry
   // {
   //
   //    e_registry_string = 1,
   //    e_registry_expand_string = 2,
   //    e_registry_binary = 3,
   //    e_registry_dword = 4,
   //    e_registry_qword = 5,
   //
   // };


   class CLASS_DECL_ACME Registry :
      virtual public ::particle
   {
   public:


      ::pointer<::platform::registry> m_pregistryCurrentUser;
      ::pointer<::platform::registry> m_pregistryLocalMachine;


      //private:
      Registry();
      ~Registry() override;


      //public:
      virtual ::platform::registry * getCurrentUserKey();
      virtual ::platform::registry *getLocalMachineKey();


   };


} // namespace subsystem




