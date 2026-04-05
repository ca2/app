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
#include "DynamicLibrary.h"

#include <crtdbg.h>

DynamicLibrary::DynamicLibrary(const ::scoped_string & scopedstrFilename)
: m_module(0)
{
  init(scopedstrFilename);
}

DynamicLibrary::DynamicLibrary()
: m_module(0)
{
}

DynamicLibrary::~DynamicLibrary()
{
  if (m_module != 0) {
    FreeLibrary(m_module);
  }
}

void DynamicLibrary::init(const ::scoped_string & scopedstrFilename)
{
  m_module = LoadLibrary(::wstring(scopedstrFilename));

  if (m_module == 0) {
    ::string errMsg;

    errMsg.format("{} library not found", scopedstrFilename);

    throw ::remoting::Exception(errMsg);
  }
}

FARPROC DynamicLibrary::getProcAddress(const char *procName)
{
  _ASSERT(m_module != 0);

  return ::GetProcAddress(m_module, procName);
}
