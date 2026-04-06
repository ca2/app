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


    class ComboBox : public Control
    {
    public:


        ComboBox();
        ~ComboBox();

        // Adds new item to the end of combo box items list.
        virtual int addItem(const char *text);

        // Adds new item to the end of combo box items list.
        virtual int addItem(const char *text, void *tag);

        // Inserts new item to the specified position
        virtual void insertItem(int index, const char *text);

        // Inserts new item to the specified position
        virtual void insertItem(int index, const char *text, void *tag);

        // Returns count of combo box items
        virtual int getItemsCount() const;

        // Sets user data (tag) associated with combo box item with specified index
        virtual void setItemData(int index, void *tag);

        // Returns user data associated with combo box item with specified index
        virtual void *getItemData(int index) const;

        // Sets text associated with combo box item with specified index
        virtual ::string getItemText(int index) const;

        // Returns current selected item index
        virtual int getSelectedItemIndex();

        // Selects item with specified index
        virtual void setSelectedItem(int index);

        // Deletes item from specified location
        virtual void deleteItem(int index);

        // Removes all combo box items
        virtual void removeAllItems();


    };

    //#endif
} // namespace innate_subsystem




