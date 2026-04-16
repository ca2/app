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


#include "innate_subsystem/gui/Control.h"
//#include "innate_subsystem/gui/Tab.h"
//#include "innate_subsystem/gui/TabContainer.h"

//using namespace std;

namespace innate_subsystem
{
   class TabControlInterface :
   virtual public ::particle_base
   {
   public:

       //TabContainer m_tabContainer;
      //TabControl();
      //virtual ~TabControlInterface() = 0;

      //
      // Tab access members
      //

      virtual TabContainer &getTabs() = 0;
      virtual int getTabCount() = 0;
      virtual TabInterface *getTab(int index)= 0;
      virtual void addTab(DialogInterface *pdialog, const char *caption)= 0;
      virtual void showTab(int index) = 0;
      virtual void showTab(DialogInterface *pdialog) = 0;
      virtual void deleteAllTabs()= 0;
virtual       void removeTab(int index)= 0;

      //
      // Return selected tab number
      //

virtual       int getSelectedTabIndex()= 0;

      //
      // Tab work rect methods
      //

      virtual void adjustRect(::int_rectangle &rect)= 0;

   //protected:

   };


   //using TabControlInterface = particle_interface<TabControlInterface, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM TabControlComposite :
   virtual public composite <TabControlInterface >
   {
   public:


      implement_compositeø(TabControl, tabcontrol)


      //TabControl();
       //~TabControl() override;

      //
      // Tab access members
      //

      TabContainer &getTabs() override { return m_ptabcontrol->getTabs(); }
      TabInterface *getTab(int index)override { return m_ptabcontrol->getTab(index); }
      void addTab(DialogInterface *dialog, const char *caption)override { m_ptabcontrol->addTab(dialog, caption); }
      void showTab(int index)override { m_ptabcontrol->showTab(index); }
      //void showTab(DialogInterface *pdialog)override;
      void deleteAllTabs()override { m_ptabcontrol->deleteAllTabs(); }
      void removeTab(int index)override { m_ptabcontrol->removeTab(index); }

      //
      // Return selected tab number
      //

      int getSelectedTabIndex()override { return m_ptabcontrol->getSelectedTabIndex(); }

      //
      // Tab work rect methods
      //

      void adjustRect(::int_rectangle &rect)override { m_ptabcontrol->adjustRect(rect); }

   //protected:
//      TabContainer m_tabContainer;
   };

   class CLASS_DECL_INNATE_SUBSYSTEM TabControl :
   virtual public aggregate < TabControlComposite, Control >
   {
   public:
   };

} //
