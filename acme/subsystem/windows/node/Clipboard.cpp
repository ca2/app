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
#include "framework.h"
#include "acme/_operating_system.h"
#include "WinClipboard.h"

WinClipboard::WinClipboard(HWND hwnd) 
  : m_hndClipboard(0), m_hwnd(hwnd)
{
}

WinClipboard::~WinClipboard() 
{
  if (m_hndClipboard) {
    EmptyClipboard();
    GlobalFree(m_hndClipboard);
  }
}

void WinClipboard::setHWnd(HWND hwnd)
{
  m_hwnd = hwnd;
  SetClipboardViewer(m_hwnd);
}

bool WinClipboard::getString(::string & str)
{
  UINT strType = CF_UNICODETEXT;

  if (sizeof(TCHAR) == 1) {
    strType = CF_TEXT;
  }
  int uFormat = GetPriorityClipboardFormat(&strType, sizeof(UINT));

  if (uFormat == 0 || uFormat == -1) {
     return false;
  }
  if (OpenClipboard(m_hwnd)) {
     HANDLE hndData = GetClipboardData(uFormat); 

     if (hndData) {
        TCHAR *szData = (TCHAR *)GlobalLock(hndData); 
        ::string nativeClipboard = szData;
        //str= szData;
        GlobalUnlock(hndData); 
        CloseClipboard();
        str = removeCR(nativeClipboard);
        return true;
      }
    CloseClipboard();
    return false;
  }
  return false;
}

bool WinClipboard::setString(const ::scoped_string & serverClipboard)
{
  ::string nativeClipboard = addCR(serverClipboard);

  int dataType = CF_UNICODETEXT;

  if (sizeof(TCHAR) == 1) {
     dataType = CF_TEXT;
  }
  int strLength = static_cast<int>(nativeClipboard.length()) + 1;
  int dataSize = strLength * sizeof(TCHAR);

  if (OpenClipboard(m_hwnd)) {
     if (m_hndClipboard) {
         EmptyClipboard();
         GlobalFree(m_hndClipboard);
      }
      m_hndClipboard = GlobalAlloc(GMEM_MOVEABLE, dataSize);
      CopyMemory(GlobalLock(m_hndClipboard), nativeClipboard, dataSize);
      GlobalUnlock(m_hndClipboard);
      SetClipboardData(dataType, m_hndClipboard);
      CloseClipboard();
      return true;
  }
  return false;
}

::string WinClipboard::addCR(const ::scoped_string & scopedstr)
{

   ::string chars(scopedstr);
   ::string newChars;
   size_t countLF = 0;
   auto p = newChars.get_buffer(chars.length() * 2 + 1);
   for (size_t i = 0; i < chars.size(); i++)
   {
      // if is first byte or previous byte not CR, then add CR
      if ((i == 0 || chars[i-1] != CR) && chars[i] == LF)
      {
         p[i + countLF] = CR;
         ++countLF;
      }
      p[i + countLF] = chars[i];
   }
   newChars.release_buffer(chars.size() + countLF);

   return newChars;

}

::string WinClipboard::removeCR(const ::scoped_string & scopedstr)
{
   ::string chars(scopedstr);
   ::string newChars;
   size_t countLF = 0;
   auto p = newChars.get_buffer(chars.length() + 1);
   size_t j = 0;
   for (size_t i = 0; i < chars.size(); i++)
   {
      if (chars[i] != CR || i + 1 == chars.size() || chars[i+1] != LF)
      {
         p[j] = chars[i];
         j++;
      }
   }
   newChars.release_buffer(j);
   return newChars;

}
