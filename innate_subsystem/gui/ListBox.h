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

#include "innate_subsystem/gui/Control.h"
//#include "util/::string.h"

namespace innate_subsystem
{

   class ListBoxInterface : virtual public ::particle_base
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

   //using ListBoxInterface = particle_interface<ListBoxInterface, ControlInterface>;

      class CLASS_DECL_INNATE_SUBSYSTEM ListBoxComposite :
      virtual public composite<ListBoxInterface >
{
      public:

         implement_compositeø(ListBox, listbox)
         
         public:
  //ListBox();
  //~ListBox() override;
//public:
   void addString(const char *str) override { m_plistbox->addString(str); }
   void addString(const char *str, void *tag) override { m_plistbox->addString(str, tag); }
   ::string getItemText(int index) override { return m_plistbox->getItemText(index); }
   void setItemText(int index, const char *str) override { m_plistbox->setItemText(index, str); }
   void insertString(int index, const char *str) override { m_plistbox->insertString(index, str); }
   void insertString(int index, const char *str, ::lparam data) override { m_plistbox->insertString(index, str, data); }
   void appendString(const char *str, ::lparam data) override { m_plistbox->appendString(str, data); }
   void setItemData(int index, ::lparam data) override { m_plistbox->setItemData(index, data); }
   void removeString(int index) override { m_plistbox->removeString(index); }
   int getSelectedIndex() override { return m_plistbox->getSelectedIndex(); }
   int getTopIndex() override { return m_plistbox->getTopIndex(); }
   void setTopIndex(int index) override { m_plistbox->setTopIndex(index); }
   void setSelectedIndex(int index) override { m_plistbox->setSelectedIndex(index); }
   ::lparam getItemData(int index) override { return m_plistbox->getItemData(index); }
   int getCount() override { return m_plistbox->getCount(); }
   void clear() override { m_plistbox->clear(); }
};


   class CLASS_DECL_INNATE_SUBSYSTEM ListBox :
  virtual public aggregate<ListBoxComposite , Control>
   {
   public:


      implement_aggregateø(ListBox, Control)
   };

} // namespace innate_subsystem


