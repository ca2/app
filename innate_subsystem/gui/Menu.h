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
//#include <winrt/impl/Windows.Foundation.0.h>

#include "subsystem/particle.h"


///#include "util/CommonHeader.h"
//#include <crtdbg.h>


namespace innate_subsystem
{

   class MenuInterface :
      virtual public ::Particle
   {
   public:
      //Menu();
      //virtual ~MenuInterface() = 0;

      virtual void * _HMENU() = 0;
      virtual void _setHMENU(void * pHMENU) = 0;
      virtual bool getWindowMenu(WindowInterface * pwindow) = 0;
      virtual void getSystemMenu(WindowInterface * pwindow) = 0;
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

      virtual void trackPopupMenuOnCursorPosition(::innate_subsystem::WindowInterface * pwindowNotify, const ::function< void(int) > & onCommand) = 0;

      // void operator= (MenuInterface * pmenu)
      // {
      //    setMenu(pmenu);
      // }

      // ///sprivate:
      //   virtual bool _appendMenu(unsigned int uFlags, ::uptr uIDNewItem, const char* lpNewItem) = 0;
      //   virtual bool _insertMenuItem(unsigned int uItem, bool fByPosition, LPCMENUITEMINFO lpmii) = 0;
      //   virtual bool _modifyMenu(unsigned int uPosition, unsigned int uFlags, ::iptr uIDNewItem, const char * lpNewItem) = 0;
      //   virtual bool _setMenuItem(unsigned int uItem, bool fByPosition, LPMENUITEMINFO lpmii) = 0;

      // protected:
      //   HMENU m_menu;
      //   bool m_bCreated;
   };
   
   class CLASS_DECL_INNATE_SUBSYSTEM MenuComposite :
      virtual public Composite< MenuInterface>
   {
   public:

      ImplementCompositeø(Menu, menu)

      //Menu();
      //~Menu() override;

      void * _HMENU() override { return m_pmenu->_HMENU(); }

      //HMENU getMenu();
      void _setHMENU(void * pHMENU) override { m_pmenu->_setHMENU(pHMENU); }
      bool getWindowMenu(WindowInterface * pwindow) override { return m_pmenu->getWindowMenu(pwindow); }
      void getSystemMenu(WindowInterface * pwindow) override { m_pmenu->getSystemMenu(pwindow); }
      void create() override { m_pmenu->create(); }
      bool loadMenu(const char * lpMenuName) override { return m_pmenu->loadMenu(lpMenuName); }
      void createPopupMenu() override { m_pmenu->createPopupMenu(); }
      bool getSubMenu(int nPos, MenuInterface *menu) override { return m_pmenu->getSubMenu(nPos, menu); }
      void termMenu() override { m_pmenu->termMenu(); }

      int getMenuItemCount() override { return m_pmenu->getMenuItemCount(); }
      bool appendMenu(const ::scoped_string & scopedstr, unsigned int uID) override { return m_pmenu->appendMenu(scopedstr, uID); }
      bool appendSeparator() override { return m_pmenu->appendSeparator(); }
      bool appendSubMenu(const ::scoped_string & scopedstr, MenuInterface *pMenu) override { return m_pmenu->appendSubMenu(scopedstr, pMenu); }

      bool insertMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) override { return m_pmenu->insertMenuItem(uItem, scopedstr, uID); }
      bool insertCheckMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) override { return m_pmenu->insertCheckMenuItem(uItem, scopedstr, uID); }
      bool insertSeparator(unsigned int uItem) override { return m_pmenu->insertSeparator(uItem); }
      bool insertSubMenu(unsigned int uItem, const ::scoped_string & scopedstr, MenuInterface *pMenu) override { return m_pmenu->insertSubMenu(uItem, scopedstr, pMenu); }

      bool enableMenuItem(unsigned int uID, unsigned int uEnable) override { return m_pmenu->enableMenuItem(uID, uEnable); }
      bool checkedMenuItem(unsigned int uID, bool bEnable) override { return m_pmenu->checkedMenuItem(uID, bEnable); }
      bool deleteMenu(unsigned int uPosition) override { return m_pmenu->deleteMenu(uPosition); }

      int findMenuItem(unsigned int uID) override { return m_pmenu->findMenuItem(uID); }

      bool setDefaultItem(unsigned int uID) override { return m_pmenu->setDefaultItem(uID); }


   void trackPopupMenuOnCursorPosition(::innate_subsystem::WindowInterface * pwindowNotify, const function<void(int)> &onCommand) override { m_pmenu->trackPopupMenuOnCursorPosition(pwindowNotify, onCommand); }

      // void operator= (MenuInterface * pmenu)
      // {
      //    setMenu(pmenu);
      // }

      // ///sprivate:
      //   bool _appendMenu(unsigned int uFlags, ::uptr uIDNewItem, const char* lpNewItem) override;
      //   bool _insertMenuItem(unsigned int uItem, bool fByPosition, LPCMENUITEMINFO lpmii) override;
      //   bool _modifyMenu(unsigned int uPosition, unsigned int uFlags, ::iptr uIDNewItem, const char * lpNewItem) override;
      //   bool _setMenuItem(unsigned int uItem, bool fByPosition, LPMENUITEMINFO lpmii) override;

      // protected:
      //   HMENU m_menu;
      //   bool m_bCreated;
   };
   
   class CLASS_DECL_INNATE_SUBSYSTEM MenuAggregate :
         virtual public Aggregate<MenuComposite>
   {
   public:

      ImplementBaseø(Menu)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM Menu :
virtual public Object<MenuAggregate>
   {
   public:

      ImplementObjectø(Menu)

   };

   
} // namespace innate_subsystem


