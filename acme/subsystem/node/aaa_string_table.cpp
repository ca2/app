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
#include "string_table.h"
#include "resource_loader.h"
#include "subsystem/subsystem.h"


namespace subsystem
{
   //::iptr_map<::string> StringTable::s_mapString;

   string_table::string_table() {}

   ::string string_table::getString(::iptr i)
   {

      ::string str;

      auto p = m_mapString.find(i);

      if (!p)
      {
         p = m_mapString.get(i);
         p->element2() = ::main_subsystem()->resource_loader()->loadString(i);
      }

      return p->element2();
   }
} // namespace subsystem