// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
//#include "util/::string.h"

namespace innate_subsystem
{

   class ListBoxInterface : virtual public ::Particle
   {
public:
  //ListBox();
  //virtual ~ListBoxInterface() = 0;
//public:
  virtual void addString(const_char_pointer str) = 0;
  virtual void addString(const_char_pointer str, void *tag) = 0;
  virtual ::string getItemText(::i32 index) = 0;
  virtual void setItemText(::i32 index, const_char_pointer str) = 0;
  virtual void insertString(::i32 index, const_char_pointer str) = 0;
  virtual void insertString(::i32 index, const_char_pointer str, ::lparam data) = 0;
  virtual void appendString(const_char_pointer str, ::lparam data) = 0;
  virtual void setItemData(::i32 index, ::lparam data) = 0;
  virtual void removeString(::i32 index) = 0;
  virtual ::i32 getSelectedIndex() = 0;
  virtual ::i32 getTopIndex() = 0;
  virtual void setTopIndex(::i32 index) = 0;
  virtual void setSelectedIndex(::i32 index) = 0;
  virtual ::lparam getItemData(::i32 index) = 0;
  virtual ::i32 getCount() = 0;
  virtual void clear() = 0;
};

   //using ListBoxInterface = particle_interface<ListBoxInterface, ControlInterface>;

      class CLASS_DECL_INNATE_SUBSYSTEM ListBoxComposite :
      virtual public Composite<ListBoxInterface >
{
      public:

         ImplementCompositeø(ListBox, listbox)
         
         public:
  //ListBox();
  //~ListBox() override;
//public:
   void addString(const_char_pointer str) override { m_plistbox->addString(str); }
   void addString(const_char_pointer str, void *tag) override { m_plistbox->addString(str, tag); }
   ::string getItemText(::i32 index) override { return m_plistbox->getItemText(index); }
   void setItemText(::i32 index, const_char_pointer str) override { m_plistbox->setItemText(index, str); }
   void insertString(::i32 index, const_char_pointer str) override { m_plistbox->insertString(index, str); }
   void insertString(::i32 index, const_char_pointer str, ::lparam data) override { m_plistbox->insertString(index, str, data); }
   void appendString(const_char_pointer str, ::lparam data) override { m_plistbox->appendString(str, data); }
   void setItemData(::i32 index, ::lparam data) override { m_plistbox->setItemData(index, data); }
   void removeString(::i32 index) override { m_plistbox->removeString(index); }
   ::i32 getSelectedIndex() override { return m_plistbox->getSelectedIndex(); }
   ::i32 getTopIndex() override { return m_plistbox->getTopIndex(); }
   void setTopIndex(::i32 index) override { m_plistbox->setTopIndex(index); }
   void setSelectedIndex(::i32 index) override { m_plistbox->setSelectedIndex(index); }
   ::lparam getItemData(::i32 index) override { return m_plistbox->getItemData(index); }
   ::i32 getCount() override { return m_plistbox->getCount(); }
   void clear() override { m_plistbox->clear(); }
};


   class CLASS_DECL_INNATE_SUBSYSTEM ListBoxAggregate :
  virtual public Aggregate<ListBoxComposite , Control>
   {
   public:


      ImplementAggregateø(ListBox, Control)
   };


   class CLASS_DECL_INNATE_SUBSYSTEM ListBox :
virtual public Object<ListBoxAggregate>
   {
   public:

      ImplementObjectø(ListBox)

   };


} // namespace innate_subsystem


