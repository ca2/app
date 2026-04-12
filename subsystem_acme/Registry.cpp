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
#include "Registry.h"

#include "filesystem/filesystem/directory_context.h"


namespace subsystem
{
   
   
   Registry::Registry()
   {
   
   
   }


   Registry::~Registry()
   {


   }


   ::platform::registry* Registry::registry()
   {

      if (!m_pregistry)
      {

         auto pathRegistry = directory()->config() / "registry.network_payload";

         m_pregistry = ::platform::registry::create_from_file(pathRegistry);

      }

      return m_pregistry;

   }


   ::subsystem::RegistryKey *Registry::getCurrentUserKey()
   {

      if (!m_pregistrykeyCurrentUser)
      {

         auto pregistrykeyCurrentUser = this->registry()->create_key(REGX_HKCU);

         m_pregistrykeyCurrentUser = allocateø ::subsystem::RegistryKey(pregistrykeyCurrentUser);

      }

      return m_pregistrykeyCurrentUser;
      //return HKEY_CURRENT_USER;
   }


   ::subsystem::RegistryKey *Registry::getLocalMachineKey()
   {

      if (!m_pregistrykeyLocalMachine)
      {

         auto pregistrykeyLocalMachine = this->registry()->create_key(REGX_HKLM);

         m_pregistrykeyLocalMachine = allocateø ::subsystem::RegistryKey(pregistrykeyLocalMachine);

      }
      return m_pregistrykeyLocalMachine;
      //return HKEY_LOCAL_MACHINE;
   }


} // namespace subsystem


