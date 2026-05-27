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
//#ifndef _COMBOBOX_H_
//#define _COMBOBOX_H_

//#include "acCommonHeader.h"
#include "innate_subsystem/gui/Control.h"


namespace innate_subsystem
{


    class ComboBoxInterface :
      virtual public ::Particle
    {
    public:


        //ComboBox();
        //virtual ~ComboBoxInterface() = 0;

        // Adds new item to the end of combo box items list.
        virtual ::i32 addItem(const_char_pointer text) = 0;

        // Adds new item to the end of combo box items list.
        virtual ::i32 addItem(const_char_pointer text, void *tag) = 0;

        // Inserts new item to the specified position
        virtual void insertItem(::i32 index, const_char_pointer text) = 0;

        // Inserts new item to the specified position
        virtual void insertItem(::i32 index, const_char_pointer text, void *tag) = 0;

        // Returns count of combo box items
        virtual ::i32 getItemsCount() = 0;

        // Sets user data (tag) associated with combo box item with specified index
        virtual void setItemData(::i32 index, void *tag) = 0;

        // Returns user data associated with combo box item with specified index
        virtual void *getItemData(::i32 index) = 0;

        // Sets text associated with combo box item with specified index
        virtual ::string getItemText(::i32 index) = 0;

        // Returns current selected item index
        virtual ::i32 getSelectedItemIndex() = 0;

        // Selects item with specified index
        virtual void setSelectedItem(::i32 index) = 0;

        // Deletes item from specified location
        virtual void deleteItem(::i32 index) = 0;

        // Removes all combo box items
        virtual void removeAllItems() = 0;


    };


//   using ComboBoxInterface = ::particle_interface<ComboBoxInterface, ControlInterface>;


   class CLASS_DECL_INNATE_SUBSYSTEM ComboBoxComposite :
     virtual public Composite<ComboBoxInterface>
   {
   public:

      ImplementCompositeø(ComboBox, combobox)

      //ComboBox();
      //~ComboBox();

      // Adds new item to the end of combo box items list.
         ::i32 addItem(const_char_pointer text) override
      {
         return m_pcombobox->addItem(text);
      }

      // Adds new item to the end of combo box items list.
      ::i32 addItem(const_char_pointer text, void* tag) override
      {

         return m_pcombobox->addItem(text, tag);
      }

      // Inserts new item to the specified position
      void insertItem(::i32 index, const_char_pointer text) override 
      { return m_pcombobox->insertItem(index, text);

      }

      // Inserts new item to the specified position
      void insertItem(::i32 index, const_char_pointer text, void* tag)  override{ return m_pcombobox->insertItem(index, text, tag);

      }

      // Returns count of combo box items
      ::i32 getItemsCount() override
      {

         return m_pcombobox->getItemsCount();
      }

      // Sets user data (tag) associated with combo box item with specified index
      void setItemData(::i32 index, void* tag) override { m_pcombobox->setItemData(index, tag);

      }

      // Returns user data associated with combo box item with specified index
      void* getItemData(::i32 index) override { return m_pcombobox->getItemData(index);

      }

      // Sets text associated with combo box item with specified index
      ::string getItemText(::i32 index) override      {

         return m_pcombobox->getItemText(index);
      }

      // Returns current selected item index
      ::i32 getSelectedItemIndex() override
      {

         return m_pcombobox->getSelectedItemIndex();
      }

      // Selects item with specified index
      void setSelectedItem(::i32 index) override{ m_pcombobox->setSelectedItem(index);
      }

      // Deletes item from specified location
      void deleteItem(::i32 index) override
      {

         m_pcombobox->deleteItem(index);
      }

      // Removes all combo box items
      void removeAllItems() override
      {

         m_pcombobox->removeAllItems();

      }


   };


   class CLASS_DECL_INNATE_SUBSYSTEM ComboBoxAggregate :
      virtual public Aggregate<ComboBoxComposite, ControlAggregate>
   {
   public:

      ImplementAggregateø(ComboBox, Control)

   };

   class CLASS_DECL_INNATE_SUBSYSTEM ComboBox :
   virtual public Object<ComboBoxAggregate>
   {
   public:

      ImplementObjectø(ComboBox)

   };

    //#endif
} // namespace innate_subsystem




