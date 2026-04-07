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

#pragma once
#include "acme/subsystem/particle.h"


///#include "util/CommonHeader.h"
//#include <crtdbg.h>


namespace innate_subsystem
{
   class CLASS_DECL_ACME MenuInterface :
      virtual public ::subsystem::particle_interface
   {
   public:
      //Menu();
      virtual ~MenuInterface() = 0;

      //HMENU getMenu();
      virtual void setMenu(MenuInterface * pmenu) = 0;
      virtual bool getWindowMenu(WindowInterface * pwindowinterface) = 0;
      virtual void getSystemMenu(WindowInterface hwnd) = 0;
      virtual void create() = 0;
      virtual bool loadMenu(const char * lpMenuName) = 0;
      virtual void createPopupMenu() = 0;
      virtual bool getSubMenu(int nPos, MenuInterface *pmenu) = 0;
      virtual void termMenu() = 0;

      virtual int getMenuItemCount() = 0;
      virtual bool appendMenu(const ::scoped_string & scopedstr, unsigned int uID) = 0;
      virtual bool appendSeparator() = 0;
      virtual bool appendSubMenu(const ::scoped_string & scopedstr, MenuInterface *pMenu) = 0;

      virtual bool insertMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) = 0;
      virtual bool insertCheckMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) = 0;
      virtual bool insertSeparator(unsigned int uItem) = 0;
      virtual bool insertSubMenu(unsigned int uItem, const ::scoped_string & scopedstr, MenuInterface *pmenu) = 0;

      virtual bool enableMenuItem(unsigned int uID, unsigned int uEnable) = 0;
      virtual bool checkedMenuItem(unsigned int uID, bool bEnable) = 0;
      virtual bool deleteMenu(unsigned int uPosition) = 0;

      virtual int findMenuItem(unsigned int uID) = 0;

      virtual bool setDefaultItem(unsigned int uID) = 0;

      void operator= (MenuInterface * pmenu)
      {
         setMenu(pmenu);
      }

      // ///sprivate:
      //   virtual bool _appendMenu(unsigned int uFlags, ::uptr uIDNewItem, const char* lpNewItem) = 0;
      //   virtual bool _insertMenuItem(unsigned int uItem, bool fByPosition, LPCMENUITEMINFO lpmii) = 0;
      //   virtual bool _modifyMenu(unsigned int uPosition, unsigned int uFlags, ::iptr uIDNewItem, const char * lpNewItem) = 0;
      //   virtual bool _setMenuItem(unsigned int uItem, bool fByPosition, LPMENUITEMINFO lpmii) = 0;

      // protected:
      //   HMENU m_menu;
      //   bool m_bCreated;
   };
   
class CLASS_DECL_ACME Menu :
      virtual public ::subsystem::composite< MenuInterface>
   {
   public:
      Menu();
      ~Menu() override;

      //HMENU getMenu();
      void setMenu(MenuInterface * phmenu) override;
      bool getWindowMenu(WindowInterface * pwindow) override;
      void getSystemMenu(WindowInterface * pwindow) override;
      void create() override;
      bool loadMenu(const char * lpMenuName) override;
      void createPopupMenu() override;
      bool getSubMenu(int nPos, MenuInterface *menu) override;
      void termMenu() override;

      int getMenuItemCount() override;
      bool appendMenu(const ::scoped_string & scopedstr, unsigned int uID) override;
      bool appendSeparator() override;
      bool appendSubMenu(const ::scoped_string & scopedstr, MenuInterface *pMenu) override;

      bool insertMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) override;
      bool insertCheckMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) override;
      bool insertSeparator(unsigned int uItem) override;
      bool insertSubMenu(unsigned int uItem, const ::scoped_string & scopedstr, MenuInterface *pMenu) override;

      bool enableMenuItem(unsigned int uID, unsigned int uEnable) override;
      bool checkedMenuItem(unsigned int uID, bool bEnable) override;
      bool deleteMenu(unsigned int uPosition) override;

      int findMenuItem(unsigned int uID) override;

      bool setDefaultItem(unsigned int uID) override;

      void operator= (MenuInterface * pmenu)
      {
         setMenu(pmenu);
      }

      // ///sprivate:
      //   bool _appendMenu(unsigned int uFlags, ::uptr uIDNewItem, const char* lpNewItem) override;
      //   bool _insertMenuItem(unsigned int uItem, bool fByPosition, LPCMENUITEMINFO lpmii) override;
      //   bool _modifyMenu(unsigned int uPosition, unsigned int uFlags, ::iptr uIDNewItem, const char * lpNewItem) override;
      //   bool _setMenuItem(unsigned int uItem, bool fByPosition, LPMENUITEMINFO lpmii) override;

      // protected:
      //   HMENU m_menu;
      //   bool m_bCreated;
   };
   
      
   
} // namespace innate_subsystem


