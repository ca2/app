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


#include "subsystem/_common_header.h"
////#include <CommCtrl.h>
#include "innate_subsystem/gui/Control.h"



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

   class ListViewInterface : virtual public ::particle_base
   {
   public:


      //typedef int (ListView:: *PFUNCTION_list_data_compare)(::lparam lparamData1, ::lparam lparamData2, void * pCompare);



      //virtual ~ListViewInterface()= 0;

      //
      // Adds new column to list view
      //

      virtual void addColumn(int index, const char *caption, int width, int fmt)= 0;
      virtual void addColumn(int index, const char *caption, int width)= 0;

      //
      // Returns list view item structure with specified index
      //

      virtual ListViewItem getItem(int index)= 0;

      //
      // Returns list view items count
      //

      virtual int getCount()= 0;

      //
      // Inserts new item to list view with specified index and caption
      //

      virtual void addItem(int index, const char *caption)= 0;

      //
      // Inserts new item to list view with specified index, caption
      // and user data(tag)
      //

      virtual void addItem(int index, const char *caption, ::lparam tag)= 0;

      //
      // Inserts new item to list view
      //

      virtual void addItem(int index, const char *caption, ::lparam tag, int imageIndex)= 0;

      //
      // Removes item with specified index from list view
      //

      virtual void removeItem(int i)= 0;

      //
      // Removes all list view items from list view
      //

      virtual void clear()= 0;

      //
      // Changes text of list view item subitem
      //

      virtual void setSubItemText(int index, int subIndex, const char *caption)= 0;

      //
      // Changes user data (tag) of list view item with specified index
      //

      virtual void setItemData(int index, ::lparam tag)= 0;

      //
      // Returns user data of list view item with specified index
      //

      virtual ::lparam getItemData(int index)= 0;

      //
      // Returns first selected list view item
      //

      virtual ListViewItem getSelectedItem()= 0;

      //
      // Returns index of first selected list view item
      //

      virtual int getSelectedIndex()= 0;

      //
      // Selectes list view item with specified index
      //

      virtual void selectItem(int index)= 0;

      //
      // Changes full row select style of list view
      //

      virtual void setFullRowSelectStyle(bool fullRowSelect)= 0;

      //
      // Enabled or disables multi selection on list view
      //

      virtual void allowMultiSelection(bool allow)= 0;

      //
      // Returns count of selected items in list view
      //

      virtual unsigned int getSelectedItemsCount()= 0;

      //
      // Sets selected list view index to output indexes array
      //

      //virtual void getSelectedItemsIndexes(int *indexes)= 0;
       virtual ::int_array getSelectedItemsIndexes() = 0;

   //protected:

       virtual void setListViewExtendedStyle(unsigned int style)= 0;
       virtual unsigned int getListViewExtendedStyle()= 0;

       virtual void addListViewExtendedStyle(unsigned int style)= 0;
       virtual void removeListViewExtendedStyle(unsigned int style)= 0;

      //
      // This method sort list of item by column "columnIndex".
      // For comparing elements using function compareItem().
      //
      // Pointer to compareItem() must be not 0.
      // After add or changing elements, list may be not sorted.
      //
      // For example, you need to call this method, if user changed parameters of sorting.
      //
      virtual void set_sort(int columnIndex, const ::function < int(::lparam, ::lparam) > & compare)= 0;

      //
      // This method sort list of item by column m_sortColumIndex.
      // After add and removing elements, list may be not sorted.
      // For example, you need to call this method after add new element.
      //
      virtual void sort()= 0;


      virtual ::lparam lparam_sort() = 0;


      /// onAction
      /// at Windows double click/enter key
      virtual void onAction() = 0;

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

   //using ListViewInterface = particle_interface<ListViewInterface, ControlInterface>;
      //
   // ListView class can be used only for listviews
   // that view data as report.
   //

   class CLASS_DECL_INNATE_SUBSYSTEM ListViewComposite :
   virtual public composite<ListViewInterface>
   {
   public:

      implement_compositeø(ListView, listview)
      //typedef int (ListView:: *PFUNCTION_list_data_compare)(::lparam lparamData1, ::lparam lparamData2, void * pCompare);

      // ListView();
      //
      // ~ListView();

      //
      // Adds new column to list view
      //

      void addColumn(int index, const char *caption, int width, int fmt) { m_plistview->addColumn(index, caption, width, fmt); }
      void addColumn(int index, const char *caption, int width) { m_plistview->addColumn(index, caption, width); }

      //
      // Returns list view item structure with specified index
      //

      ListViewItem getItem(int index) { return m_plistview->getItem(index); }

      //
      // Returns list view items count
      //

      int getCount() { return m_plistview->getCount(); }

      //
      // Inserts new item to list view with specified index and caption
      //

      void addItem(int index, const char *caption) { m_plistview->addItem(index, caption); }

      //
      // Inserts new item to list view with specified index, caption
      // and user data(tag)
      //

      void addItem(int index, const char *caption, ::lparam tag) { m_plistview->addItem(index, caption, tag); }

      //
      // Inserts new item to list view
      //

      void addItem(int index, const char *caption, ::lparam tag, int imageIndex) { m_plistview->addItem(index, caption, tag, imageIndex); }

      //
      // Removes item with specified index from list view
      //

      void removeItem(int i) { m_plistview->removeItem(i); }

      //
      // Removes all list view items from list view
      //

      void clear() { m_plistview->clear(); }

      //
      // Changes text of list view item subitem
      //

      void setSubItemText(int index, int subIndex, const char *caption) { m_plistview->setSubItemText(index, subIndex, caption); }

      //
      // Changes user data (tag) of list view item with specified index
      //

      void setItemData(int index, ::lparam tag) { m_plistview->setItemData(index, tag); }

      //
      // Returns user data of list view item with specified index
      //

      ::lparam getItemData(int index) { return m_plistview->getItemData(index); }

      //
      // Returns first selected list view item
      //

      ListViewItem getSelectedItem() { return m_plistview->getSelectedItem(); }

      //
      // Returns index of first selected list view item
      //

      int getSelectedIndex() { return m_plistview->getSelectedIndex(); }

      //
      // Selectes list view item with specified index
      //

      void selectItem(int index) { m_plistview->selectItem(index); }

      //
      // Changes full row select style of list view
      //

      void setFullRowSelectStyle(bool fullRowSelect) { m_plistview->setFullRowSelectStyle(fullRowSelect); }

      //
      // Enabled or disables multi selection on list view
      //

      void allowMultiSelection(bool allow) { m_plistview->allowMultiSelection(allow); }

      //
      // Returns count of selected items in list view
      //

      unsigned int getSelectedItemsCount() { return m_plistview->getSelectedItemsCount(); }

      //
      // Sets selected list view index to output indexes array
      //

      ::int_array getSelectedItemsIndexes() { return m_plistview->getSelectedItemsIndexes(); }

   //protected:

       void setListViewExtendedStyle(unsigned int style) { m_plistview->setListViewExtendedStyle(style); }
       unsigned int getListViewExtendedStyle() { return m_plistview->getListViewExtendedStyle(); }

       void addListViewExtendedStyle(unsigned int style) { m_plistview->addListViewExtendedStyle(style); }
       void removeListViewExtendedStyle(unsigned int style) { m_plistview->removeListViewExtendedStyle(style); }

      //
      // This method sort list of item by column "columnIndex".
      // For comparing elements using function compareItem().
      //
      // Pointer to compareItem() must be not 0.
      // After add or changing elements, list may be not sorted.
      //
      // For example, you need to call this method, if user changed parameters of sorting.
      //
      void set_sort(int columnIndex, const ::function < int(::lparam, ::lparam) > & compare) { m_plistview->set_sort(columnIndex, compare); }

      //
      // This method sort list of item by column m_sortColumIndex.
      // After add and removing elements, list may be not sorted.
      // For example, you need to call this method after add new element.
      //
      void sort() { m_plistview->sort(); }



      // overridables
      void onAction() { m_plistview->onAction(); }

      //virtual bool _onNotifyReflect(::wparam wparam, ::lparam lparam);


      ::lparam lparam_sort() { return m_plistview->lparam_sort(); }

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


   class CLASS_DECL_INNATE_SUBSYSTEM ListView :
      virtual public aggregate< ListViewComposite, Control >
   {

   };

} // namespace innate_subsystem



