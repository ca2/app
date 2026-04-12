// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

#include "innate_subsystem/Control.h"
//#include "util/::string.h"

namespace subsystem_apex
{

   class ListBoxInterface :
   virtual public ::subsystem::particle_interface<ListBoxInterface>,
   virtual public Control
{
public:
  //ListBox();
  //virtual ~ListBoxInterface() = 0;
//public:
  virtual void addString(const char *str) = 0;
  virtual void addString(const char *str, void *tag) = 0;
  virtual ::string getItemText(int index) = 0;
  virtual void setItemText(int index, const char *str) = 0;
  virtual void insertString(int index, const char *str) = 0;
  virtual void insertString(int index, const char *str, ::lparam data) = 0;
  virtual void appendString(const char *str, ::lparam data) = 0;
  virtual void setItemData(int index, ::lparam data) = 0;
  virtual void removeString(int index) = 0;
  virtual int getSelectedIndex() = 0;
  virtual int getTopIndex() = 0;
  virtual void setTopIndex(int index) = 0;
  virtual void setSelectedIndex(int index) = 0;
  virtual ::lparam getItemData(int index) = 0;
  virtual int getCount() = 0;
  virtual void clear() = 0;
};


      class CLASS_DECL_APEX ListBox : virtual public ::subsystem::composite<ListBoxInterface >
{
         public:
  ListBox();
  ~ListBox() override;
//public:
   void addString(const char *str) override;
   void addString(const char *str, void *tag) override;
   ::string getItemText(int index) override;
   void setItemText(int index, const char *str) override;
   void insertString(int index, const char *str) override;
   void insertString(int index, const char *str, ::lparam data) override;
   void appendString(const char *str, ::lparam data) override;
   void setItemData(int index, ::lparam data) override;
   void removeString(int index) override;
   int getSelectedIndex() override;
   int getTopIndex() override;
   void setTopIndex(int index) override;
   void setSelectedIndex(int index) override;
   ::lparam getItemData(int index) override;
   int getCount() override;
   void clear() override;
};

} // namespace subsystem_apex


