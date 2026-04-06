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


#include "acme/subsystem/_common_header.h"
//#include <commctrl.h>
#include "apex/innate_subsystem/Control.h"

//
// TODO: Maybe use class for this?
//

namespace innate_subsystem
{
   typedef struct
   {
      int index;
      unsigned long long tag;
   } ListViewItem;

   //
   // ListView class can be used only for listviews
   // that view data as report.
   //

   class ListView : public Control
   {
   public:

      ListView();

      //
      // Adds new column to list view
      //

      virtual void addColumn(int index, const char *caption, int width, int fmt);
      virtual void addColumn(int index, const char *caption, int width);

      //
      // Returns list view item structure with specified index
      //

      virtual ListViewItem getItem(int index);

      //
      // Returns list view items count
      //

      virtual int getCount();

      //
      // Inserts new item to list view with specified index and caption
      //

      virtual void addItem(int index, const char *caption);

      //
      // Inserts new item to list view with specified index, caption
      // and user data(tag)
      //

      virtual void addItem(int index, const char *caption, ::lparam tag);

      //
      // Inserts new item to list view
      //

      virtual void addItem(int index, const char *caption, ::lparam tag, int imageIndex);

      //
      // Removes item with specified index from list view
      //

      virtual void removeItem(int i);

      //
      // Removes all list view items from list view
      //

      virtual void clear();

      //
      // Changes text of list view item subitem
      //

      virtual void setSubItemText(int index, int subIndex, const char *caption);

      //
      // Changes user data (tag) of list view item with specified index
      //

      virtual void setItemData(int index, ::lparam tag);

      //
      // Returns user data of list view item with specified index
      //

      virtual ::lparam getItemData(int index);

      //
      // Returns first selected list view item
      //

      virtual ListViewItem getSelectedItem();

      //
      // Returns index of first selected list view item
      //

      virtual int getSelectedIndex();

      //
      // Selectes list view item with specified index
      //

      virtual void selectItem(int index);

      //
      // Changes full row select style of list view
      //

      virtual void setFullRowSelectStyle(bool fullRowSelect);

      //
      // Enabled or disables multi selection on list view
      //

      virtual void allowMultiSelection(bool allow);

      //
      // Returns count of selected items in list view
      //

      virtual unsigned int getSelectedItemsCount();

      //
      // Sets selected list view index to output indexes array
      //

      virtual void getSelectedItemsIndexes(int *indexes);

   //protected:

      virtual void setExStyle(unsigned int style);
      virtual unsigned int getExStyle();

      virtual void addExStyle(unsigned int style);
      virtual void removeExStyle(unsigned int style);

      //
      // This method sort list of item by column "columnIndex".
      // For comparing elements using function compareItem().
      //
      // Pointer to compareItem() must be not 0.
      // After add or changing elements, list may be not sorted.
      //
      // For example, you need to call this method, if user changed parameters of sorting.
      //
      //virtual void sort(int columnIndex, PFNLVCOMPARE compareItem);

      //
      // This method sort list of item by column m_sortColumIndex.
      // After add and removing elements, list may be not sorted.
      // For example, you need to call this method after add new element.
      //
      virtual void sort();

   // private:
   //    // Kind of sorting: ascending or descending
   //    bool m_sortAscending;
   //
   //    //
   //    // Is list view not sorted, then m_sortClumnIndex is negative,
   //    // else him contained index of column.
   //    //
   //    int m_sortColumnIndex;
   //
   //    //
   //    // This pointer to compareFunction. By default is 0.
   //    //
   //    PFNLVCOMPARE m_compareItem;
   };

} // namespace innate_subsystem



