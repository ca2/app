// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
#include "DesktopSelector.h"
//#include <vector>

HDESK DesktopSelector::getInputDesktop()
{
  return OpenInputDesktop(0, TRUE,
                          DESKTOP_CREATEMENU |
                          DESKTOP_CREATEWINDOW |
                          DESKTOP_ENUMERATE |
                          DESKTOP_HOOKCONTROL |
                          DESKTOP_WRITEOBJECTS |
                          DESKTOP_READOBJECTS |
                          DESKTOP_SWITCHDESKTOP |
                          GENERIC_WRITE);
}

HDESK DesktopSelector::getDesktop(const ::scoped_string & scopedstrName)
{
  return OpenDesktop(::wstring(scopedstrName), 0, TRUE,
                     DESKTOP_CREATEMENU |
                     DESKTOP_CREATEWINDOW |
                     DESKTOP_ENUMERATE |
                     DESKTOP_HOOKCONTROL |
                     DESKTOP_WRITEOBJECTS |
                     DESKTOP_READOBJECTS |
                     DESKTOP_SWITCHDESKTOP |
                     GENERIC_WRITE);
}

bool DesktopSelector::closeDesktop(HDESK hdesk)
{
  return CloseDesktop(hdesk) != 0;
}

bool DesktopSelector::setDesktopToCurrentThread(HDESK newDesktop)
{
  return SetThreadDesktop(newDesktop) != 0;
}

bool DesktopSelector::selectDesktop(const ::scoped_string & name)
{
  HDESK desktop;
  if (name.is_empty()) {
    desktop = getDesktop(name);
  } else {
    desktop = getInputDesktop();
  }

  bool result = setDesktopToCurrentThread(desktop) != 0;
  closeDesktop(desktop);

  return result;
}


::string DesktopSelector::getDesktopName(HDESK desktop)
{
//  desktopName-= "";

  DWORD nameLength = 0;
  // Do not check returned value because the function will return FALSE always.
  GetUserObjectInformation(desktop, UOI_NAME, 0, 0, &nameLength);

  if (nameLength != 0) {
    ::array_base<TCHAR> name(nameLength);
    bool result = !!GetUserObjectInformation(desktop,
                                             UOI_NAME,
                                             &name[0],
                                             nameLength,
                                             0);
    if (result) {
      return name.data();
      //return true;
    }
  }
   throw ::exception(error_io);
  //return false;
}

::string DesktopSelector::getCurrentDesktopName()
{
  HDESK inputDesktop = getInputDesktop();
  auto str = getDesktopName(inputDesktop);
  closeDesktop(inputDesktop);
  return str;
}

::string DesktopSelector::getThreadDesktopName()
{
  return getDesktopName(GetThreadDesktop(GetCurrentThreadId()));
}
