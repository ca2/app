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


#include "apex/innate_subsystem/Control.h"
//#include "apex/innate_subsystem/Tab.h"
//#include "apex/innate_subsystem/TabContainer.h"

//using namespace std;

namespace innate_subsystem
{
   class TabControlInterface :
   virtual public ::subsystem::particle_interface<TabControlInterface>,
   public Control
   {
   public:

       //TabContainer m_tabContainer;
      //TabControl();
      //virtual ~TabControlInterface() = 0;

      //
      // Tab access members
      //

      virtual TabContainer &getTabs() = 0;
      virtual int getTabCount() ;
      virtual TabInterface *getTab(int index)= 0;
      virtual void addTab(DialogInterface *pdialog, const char *caption)= 0;
      virtual void showTab(int index);
      virtual void showTab(DialogInterface *pdialog);
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


   class CLASS_DECL_APEX TabControl : public ::subsystem::composite <TabControlInterface >
   {
   public:
      TabControl();
       ~TabControl() override;

      //
      // Tab access members
      //

      TabContainer &getTabs() override;
      TabInterface *getTab(int index)override;
      void addTab(DialogInterface *dialog, const char *caption)override;
      void showTab(int index)override;
      //void showTab(DialogInterface *pdialog)override;
      void deleteAllTabs()override;
      void removeTab(int index)override;

      //
      // Return selected tab number
      //

      int getSelectedTabIndex()override;

      //
      // Tab work rect methods
      //

      void adjustRect(::int_rectangle &rect)override;

   //protected:
//      TabContainer m_tabContainer;
   };


} //
