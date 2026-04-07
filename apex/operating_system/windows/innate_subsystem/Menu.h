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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#ifndef _MENU_H_
#define _MENU_H_

#include "util/CommonHeader.h"
#include <crtdbg.h>

class Menu
{
public:
  Menu();
  virtual ~Menu();

  HMENU getMenu();
  void setMenu(HMENU hmenu);
  bool getWindowMenu(HWND hwnd);
  void getSystemMenu(HWND hwnd);
  void create();
  bool loadMenu(LPCTSTR lpMenuName);
  void createPopupMenu();
  bool getSubMenu(int nPos, Menu *menu);
  void termMenu();
  
  int getMenuItemCount();
  bool appendMenu(StringStorage strVal, unsigned int uID); 
  bool appendSeparator();
  bool appendSubMenu(StringStorage strVal, Menu *pMenu);

  bool insertMenuItem(unsigned int uItem, StringStorage strVal, unsigned int uID);
  bool insertCheckMenuItem(unsigned int uItem, StringStorage strVal, unsigned int uID);
  bool insertSeparator(unsigned int uItem);
  bool insertSubMenu(unsigned int uItem, StringStorage strVal, Menu *pMenu);

  bool enableMenuItem(unsigned int uID, unsigned int uEnable);
  bool checkedMenuItem(unsigned int uID, bool bEnable);
  bool deleteMenu(unsigned int uPosition);

  int findMenuItem(unsigned int uID);

  bool setDefaultItem(unsigned int uID);

  void operator= (HMENU hmenu)
  {
    setMenu(hmenu);
  }

private:
  bool appendMenu(unsigned int uFlags, unsigned int_PTR uIDNewItem, LPCTSTR lpNewItem);
  bool insertMenuItem(unsigned int uItem, BOOL fByPosition, LPCMENUITEMINFO lpmii);
  bool modifyMenu(unsigned int uPosition, unsigned int uFlags, LONG_PTR uIDNewItem, LPCTSTR lpNewItem);
  bool setMenuItem(unsigned int uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);

protected:
  HMENU m_menu;
  bool m_bCreated;
};

#endif
