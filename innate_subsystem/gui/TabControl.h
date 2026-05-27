// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
   virtual public ::Particle
   {
   public:

       //TabContainer m_tabContainer;
      //TabControl();
      //virtual ~TabControlInterface() = 0;

      //
      // Tab access members
      //

      virtual TabContainer &getTabs() = 0;
      virtual ::i32 getTabCount() = 0;
      virtual TabInterface *getTab(::i32 index)= 0;
      virtual void addTab(WindowInterface *pwindow, const_char_pointer caption)= 0;
      virtual void showTab(::i32 index) = 0;
      virtual void showTab(WindowInterface *pwindow) = 0;
      virtual void deleteAllTabs()= 0;
virtual       void removeTab(::i32 index)= 0;


      virtual void moveWindowToTabControl(::innate_subsystem::WindowInterface * pwindow) = 0;
      //
      // Return selected tab number
      //

virtual       ::i32 getSelectedTabIndex()= 0;

      //
      // Tab work rect methods
      //

      virtual void adjustRect(::i32_rectangle &rect)= 0;

   //protected:

   };


   //using TabControlInterface = particle_interface<TabControlInterface, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM TabControlComposite :
   virtual public Composite <TabControlInterface >
   {
   public:


      ImplementCompositeø(TabControl, tabcontrol)


      //TabControl();
       //~TabControl() override;

      //
      // Tab access members
      //

      TabContainer &getTabs() override { return m_ptabcontrol->getTabs(); }
      virtual ::i32 getTabCount() override {return m_ptabcontrol->getTabCount();};
      TabInterface *getTab(::i32 index)override { return m_ptabcontrol->getTab(index); }
      void addTab(WindowInterface *pwindow, const_char_pointer caption)override { m_ptabcontrol->addTab(pwindow, caption); }
      void showTab(::i32 index)override { m_ptabcontrol->showTab(index); }
      void showTab(WindowInterface *pwindow) override { m_ptabcontrol->showTab(pwindow); }
      void deleteAllTabs()override { m_ptabcontrol->deleteAllTabs(); }
      void removeTab(::i32 index)override { m_ptabcontrol->removeTab(index); }


      void moveWindowToTabControl(::innate_subsystem::WindowInterface * pwindow) override {m_ptabcontrol->moveWindowToTabControl(pwindow);}

      //
      // Return selected tab number
      //

      ::i32 getSelectedTabIndex()override { return m_ptabcontrol->getSelectedTabIndex(); }

      //
      // Tab work rect methods
      //

      void adjustRect(::i32_rectangle &rect)override { m_ptabcontrol->adjustRect(rect); }

   //protected:
//      TabContainer m_tabContainer;
   };



   class CLASS_DECL_INNATE_SUBSYSTEM TabControlAggregate :
      virtual public Aggregate < TabControlComposite, ControlAggregate >
   {
   public:

      ImplementAggregateø(TabControl, Control)

   };

   class CLASS_DECL_INNATE_SUBSYSTEM  TabControl:
      virtual public WindowObject<TabControlAggregate>
   {
   public:

      ImplementObjectø(TabControl)

   };


} //
