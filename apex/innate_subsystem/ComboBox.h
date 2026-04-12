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
//#ifndef _COMBOBOX_H_
//#define _COMBOBOX_H_

//#include "acCommonHeader.h"
#include "apex/innate_subsystem/Control.h"


namespace innate_subsystem
{


    class ComboBoxInterface :
   virtual public ::subsystem::particle_interface<ComboBoxInterface>,
         virtual public Control
    {
    public:


        //ComboBox();
        //virtual ~ComboBoxInterface() = 0;

        // Adds new item to the end of combo box items list.
        virtual int addItem(const char *text) = 0;

        // Adds new item to the end of combo box items list.
        virtual int addItem(const char *text, void *tag) = 0;

        // Inserts new item to the specified position
        virtual void insertItem(int index, const char *text) = 0;

        // Inserts new item to the specified position
        virtual void insertItem(int index, const char *text, void *tag) = 0;

        // Returns count of combo box items
        virtual int getItemsCount() = 0;

        // Sets user data (tag) associated with combo box item with specified index
        virtual void setItemData(int index, void *tag) = 0;

        // Returns user data associated with combo box item with specified index
        virtual void *getItemData(int index) = 0;

        // Sets text associated with combo box item with specified index
        virtual ::string getItemText(int index) = 0;

        // Returns current selected item index
        virtual int getSelectedItemIndex() = 0;

        // Selects item with specified index
        virtual void setSelectedItem(int index) = 0;

        // Deletes item from specified location
        virtual void deleteItem(int index) = 0;

        // Removes all combo box items
        virtual void removeAllItems() = 0;


    };

   class CLASS_DECL_APEX ComboBox :
     virtual public ::subsystem::composite<ComboBoxInterface>
   {
   public:


      ComboBox();
      ~ComboBox() override;

      // Adds new item to the end of combo box items list.
      int addItem(const char *text) override;

      // Adds new item to the end of combo box items list.
      int addItem(const char *text, void *tag) override;

      // Inserts new item to the specified position
      void insertItem(int index, const char *text) override;

      // Inserts new item to the specified position
      void insertItem(int index, const char *text, void *tag) override;

      // Returns count of combo box items
      int getItemsCount() override;

      // Sets user data (tag) associated with combo box item with specified index
      void setItemData(int index, void *tag) override;

      // Returns user data associated with combo box item with specified index
      void *getItemData(int index) override;

      // Sets text associated with combo box item with specified index
      ::string getItemText(int index) override;

      // Returns current selected item index
      int getSelectedItemIndex() override;

      // Selects item with specified index
      void setSelectedItem(int index) override;

      // Deletes item from specified location
      void deleteItem(int index) override;

      // Removes all combo box items
      void removeAllItems() override;


   };

    //#endif
} // namespace innate_subsystem




