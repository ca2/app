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
#include "framework.h"
#include "Menu.h"

namespace subsystem_apex
{
   Menu::Menu()
   // : m_menu(0),
   //   m_bCreated(false)
   {
   }
   Menu::~Menu()
   {
      
   }
   // Menu::~Menu()
   // {
   //    if (m_menu && m_bCreated) {
   //       DestroyMenu(m_menu);
   //    }
   // }

   

    void * Menu::_HMENU()
    {
       //return m_menu;
      return m_pparticleThis->_HMENU();
    }

   void Menu::_setHMENU(void * pHMENU)
   {
      // _ASSERT(m_menu == 0);
      //
      //m_menu = hmenu;
      m_pparticleThis->_setHMENU(pHMENU);
   }

   bool Menu::getWindowMenu(WindowInterface * pwindow)
   {
      //_ASSERT(m_menu == 0);
      //m_menu = GetMenu(hwnd);//
      //return (m_menu == 0 ? false : true);

      return m_pparticleThis->getWindowMenu(pwindow);
   }

   void Menu::getSystemMenu(WindowInterface * pwindow)
   {
      //_ASSERT(m_menu == 0);

      //m_menu = GetSystemMenu(hwnd, FALSE);

      m_pparticleThis->getSystemMenu(pwindow);
   }

   void Menu::create()
   {
      // _ASSERT(m_menu == 0);
      //
      // m_menu = CreateMenu();
      // m_bCreated = true;
      m_pparticleThis->create();
   }

   bool Menu::loadMenu(const char * lpMenuName)
   {
      // _ASSERT(m_menu == 0);
      //
      // m_menu = LoadMenu(GetModuleHandle(0), lpMenuName);
      // m_bCreated = true;
      // return (!m_menu?false:true);

      return m_pparticleThis->loadMenu(lpMenuName);
   }

   void Menu::createPopupMenu()
   {
      // _ASSERT(m_menu == 0);
      //
      // m_menu = CreatePopupMenu();
      // m_bCreated = true;

      m_pparticleThis->createPopupMenu();
   }

   int Menu::getMenuItemCount()
   {
      // _ASSERT(m_menu != 0);
      //
      // return GetMenuItemCount(m_menu);

      return m_pparticleThis->getMenuItemCount();
   }

   // bool Menu::appendMenu(unsigned int uFlags, unsigned int_PTR uIDNewItem, LPCTSTR lpNewItem)
   // {
   //    // _ASSERT(m_menu != 0);
   //    //
   //    // return !!AppendMenu(m_menu, uFlags, uIDNewItem, lpNewItem);
   //    return m_pparticleThis->appendMenu()
   // }

   // bool Menu::insertMenuItem(unsigned int uItem, bool fByPosition, LPCMENUITEMINFO lpmii)
   // {
   //    _ASSERT(m_menu != 0);
   //
   //    return !!InsertMenuItem(m_menu, uItem, fByPosition, lpmii);
   // }

   // bool Menu::modifyMenu(unsigned int uPosition, unsigned int uFlags, LONG_PTR uIDNewItem, LPCTSTR lpNewItem)
   // {
   //    _ASSERT(m_menu != 0);
   //
   //    return !!ModifyMenu(m_menu, uPosition, uFlags, uIDNewItem, lpNewItem);
   // }

   bool Menu::deleteMenu(unsigned int uPosition)
   {
      // _ASSERT(m_menu != 0);
      //
      // return !!DeleteMenu(m_menu, uPosition, MF_BYPOSITION);
      return m_pparticleThis->deleteMenu(uPosition);
   }

   bool Menu::getSubMenu(int nPos, MenuInterface *pmenu)
   {

      return m_pparticleThis->getSubMenu(nPos, pmenu);
      // MenuInterface * tmenu;
      //
      // _ASSERT(m_menu != 0 && menu);
      // tmenu = GetSubMenu(m_menu, nPos);
      // if (tmenu) {
      //    menu->setMenu(tmenu);
      // }
      // return (!tmenu?false:true);
   }

   bool Menu::enableMenuItem(unsigned int uID, unsigned int uEnable)
   {
      //    _ASSERT(m_menu != 0);
      //
      //    return !!EnableMenuItem(m_menu, uID, uEnable);
      // }

      return m_pparticleThis->enableMenuItem(uID, uEnable);
   }

   // bool Menu::setMenuItem(unsigned int uItem, bool fByPosition, LPMENUITEMINFO lpmii)
   // {
   //    // _ASSERT(m_menu != 0);
   //    //
   //    // return !!SetMenuItemInfo(m_menu, uItem, fByPosition, lpmii);
   // }

   void Menu::termMenu()
   {
      m_pparticleThis->termMenu();
      // if (m_menu && m_bCreated) {
      //    DestroyMenu(m_menu);
      // }
      // m_menu = 0;
      // m_bCreated = false;
   }


   int Menu::findMenuItem(unsigned int uID)
   {
      return m_pparticleThis->findMenuItem(uID);
      // _ASSERT(m_menu != 0);
      //
      // for (int i = 0; i < getMenuItemCount(); i++) {
      //    if (GetMenuItemID(m_menu, i) == uID) {
      //       return i;
      //    }
      // }
      // return -1;
   }

   bool Menu::appendMenu(const ::scoped_string & scopedstr, unsigned int uID)
   {
      //return appendMenu(MF_STRING, uID, strVal.getString());
      return m_pparticleThis->appendMenu(scopedstr, uID);
   }

   bool Menu::appendSeparator()
   {
      //return appendMenu(MF_MENUBREAK, 0, 0);

      return m_pparticleThis->appendSeparator();
   }

   bool Menu::appendSubMenu(const ::scoped_string & scopedstr, MenuInterface *pmenu)
   {
      return m_pparticleThis->appendSubMenu(scopedstr, pmenu);
      //return appendMenu(MF_POPUP, (unsigned int_PTR)pMenu->getMenu(), strVal.getString());
   }

   bool Menu::insertMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID)
   {

      return m_pparticleThis->insertMenuItem(uItem, scopedstr, uID);
      // MENUITEMINFO mii;
      //
      // ZeroMemory(&mii, sizeof(MENUITEMINFO));
      // mii.cbSize = sizeof(MENUITEMINFO);
      // mii.fMask = MIIM_STRING | MIIM_ID;
      // mii.dwTypeData = (LPTSTR)strVal.getString();
      // mii.fState = MFS_DEFAULT;
      // mii.wID = uID;
      // return insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::insertCheckMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID)
   {

      return m_pparticleThis->insertCheckMenuItem(uItem, scopedstr, uID);
      // MENUITEMINFO mii;
      //
      // ZeroMemory(&mii, sizeof(MENUITEMINFO));
      // mii.cbSize = sizeof(MENUITEMINFO);
      // mii.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE;
      // mii.dwTypeData = (LPTSTR)strVal.getString();
      // mii.fState = MFS_UNCHECKED;
      // mii.wID = uID;
      // return insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::checkedMenuItem(unsigned int uID, bool bEnable)
   {
      // _ASSERT(m_menu != 0);
      //
      // int pos = findMenuItem(uID);
      // if (pos == -1) {
      //    return false;
      // }
      // unsigned int command = bEnable ? MF_CHECKED : MF_UNCHECKED;
      // unsigned int res = CheckMenuItem(m_menu, pos, MF_BYPOSITION | command);
      // return (res == -1) ? false : true;

      return m_pparticleThis->checkedMenuItem(uID, bEnable);
   }

   bool Menu::insertSeparator(unsigned int uItem)
   {
      // MENUITEMINFO mii;
      //
      // ZeroMemory(&mii, sizeof(MENUITEMINFO));
      // mii.cbSize = sizeof(MENUITEMINFO);
      // mii.fType = MFT_SEPARATOR;
      // return insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
      return m_pparticleThis->insertSeparator(uItem);
   }

   bool Menu::insertSubMenu(unsigned int uItem, const ::scoped_string & scopedstr, MenuInterface *pmenu)
   {

      return m_pparticleThis->insertSubMenu(uItem, scopedstr, pmenu);
      // MENUITEMINFO mii;
      //
      // ZeroMemory(&mii, sizeof(MENUITEMINFO));
      // mii.cbSize = sizeof(MENUITEMINFO);
      // mii.fMask = MIIM_SUBMENU;
      // mii.hSubMenu = pMenu->getMenu();
      // return insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::setDefaultItem(unsigned int uID)
   {
      //_ASSERT(m_menu != 0);

      //return !!SetMenuDefaultItem(m_menu, uID, FALSE);

      return m_pparticleThis->setDefaultItem(uID);
   }
} // namespace subsystem_apex


