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
#include "TabControl.h"
#include "Tab.h"
//#include "util/CommonHeader.h"
//#include <CommCtrl.h>

namespace innate_subsystem
{


   int TabControlInterface::getTabCount()
   {
      return (int) getTabs().count();
   }

   void TabControlInterface::showTab(DialogInterface *pdialog)
   {
      for (int i = 0; i < getTabCount(); i++) {
         if (getTab(i)->getDialog() == pdialog) {
            showTab(i);
            return;
         }
      }
      throw ::exception(error_not_found);

      //m_pparticleThis->showTab(pdialog);
   }

   TabControl::TabControl()
   {
   }

   TabControl::~TabControl()
   {
      //deleteAllTabs();
   }


   TabContainer &TabControl::getTabs()
   {

      return m_pparticleThis->getTabs();

   }


   TabInterface *TabControl::getTab(int index)
   {
      // if ((index < 0) || ((size_t)index > m_tabContainer.size() - 1)) {
      //    return NULL;
      // }
      // return m_tabContainer.at(index);
      return m_pparticleThis->getTab(index);
   }

   void TabControl::addTab(DialogInterface *pdialog, const char *caption)
   {

      m_pparticleThis->addTab(pdialog, caption);
      // Tab *tab = new Tab(dialog, caption);
      // m_tabContainer.push_back(tab);
      // TCITEM tcitem = {0};
      // tcitem.mask = TCIF_TEXT;
      // char fixedCaption[255];
      // _tcscpy(&fixedCaption[0], tab->getCaption());
      // tcitem.pszText = fixedCaption;
      // if (TabCtrl_InsertItem(getWindow(), m_tabContainer.size() - 1, &tcitem) == FALSE) {
      //    //
      //    // Handle error
      //    // ...
      //    //
      // }
   }

   void TabControl::showTab(int index)
   {
      // int selectedIndex = getSelectedTabIndex();
      // if (selectedIndex >= 0) {
      //    getTab(selectedIndex)->setVisible(false);
      // }
      // TabCtrl_SetCurSel(m_hwnd, index);
      // getTab(index)->setVisible(true);

      m_pparticleThis->showTab(index);
   }

   // void TabControl::showTab(DialogInterface *pdialog)
   // {
   //    for (size_t i = 0; i < m_tabContainer.size(); i++) {
   //        if (m_tabContainer.at(i)->getDialog() == dialog) {
   //           showTab((int)i);
   //           return;
   //        }
   //     }
   //    // _ASSERT(FALSE);
   //
   //    m_pparticleThis->showTab(pdialog);
   // }

   void TabControl::deleteAllTabs()
   {
      m_pparticleThis->deleteAllTabs();
      // for (size_t i = 0; i < m_tabContainer.size(); i++) {
      //    Tab *tab = m_tabContainer.at(i);
      //    delete tab;
      // }
      // m_tabContainer.clear();
      // TabCtrl_DeleteAllItems(getWindow());
   }

   void TabControl::removeTab(int index)
   {
      m_pparticleThis->removeTab(index);
      // int i = 0;
      // for (TabContainer::iterator it = m_tabContainer.begin(); it != m_tabContainer.end(); it++) {
      //    if (i == index) {
      //       delete *it;
      //       m_tabContainer.erase(it);
      //       TabCtrl_DeleteItem(m_hwnd, index);
      //       break;
      //    }
      //    i++;
      // }
   }

   int TabControl::getSelectedTabIndex()
   {
      // int page = TabCtrl_GetCurSel(getWindow());
      // return page;
      return m_pparticleThis->getSelectedTabIndex();
   }

   void TabControl::adjustRect(::int_rectangle &rect)
   {
      // GetClientRect(m_hwnd, rect);
      // TabCtrl_AdjustRect(m_hwnd, FALSE, rect);
      m_pparticleThis->adjustRect(rect);
   }
} // namespace innate_subsystem


