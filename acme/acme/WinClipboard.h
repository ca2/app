// Copyright (C) 2012 GlavSoft LLC.
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


#include "remoting/remoting_common/util/CommonHeader.h"

class CLASS_DECL_REMOTING_COMMON WinClipboard
{
public:

  WinClipboard(HWND hwnd);
  virtual ~WinClipboard();

  void setHWnd(HWND hwnd);
  
  // get string from windows clipboard
  bool getString(::string & str);

  // update windows clipboard
  bool setString(const ::scoped_string & str);

//protected:
  static const char CR = '\r';
  static const char LF = '\n';

//protected:
  // function removed CR before LF
  ::string removeCR(const ::scoped_string & str);

  // function replaced LF to CR+LF. If before LF already is CR, this not added second
  ::string addCR(const ::scoped_string & str);

  HANDLE m_hndClipboard;
  HWND m_hwnd;
};


