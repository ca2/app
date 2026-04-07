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
#include "framework.h"
#include "ListBox.h"

namespace innate_subsystem
{
   ListBox::ListBox()
   {
   }

   ListBox::~ListBox()
   {
   }

   void ListBox::addString(const char *str)
   {
      addString(str, 0);
   }

   void ListBox::addString(const char *str, void *tag)
   {
      LRESULT lresult = SendMessage(m_hwnd, LB_ADDSTRING, 0, (::lparam)str);
      int i = (int)lresult;
      _ASSERT(i == lresult);
      setItemData(i, (::lparam)tag);
   }

   void ListBox::removeString(int index)
   {
      int top = getTopIndex();
      SendMessage(m_hwnd, LB_DELETESTRING, index, NULL);
      setTopIndex(top);
   }

   int ListBox::getTopIndex()
   {
      return (int)SendMessage(m_hwnd, LB_GETTOPINDEX, NULL, NULL);
   }

   void ListBox::setTopIndex(int index)
   {
      SendMessage(m_hwnd, LB_SETTOPINDEX, index, NULL);
   }

   void ListBox::getItemText(int index, ::string *storage)
   {
      size_t length = SendMessage(m_hwnd, LB_GETTEXTLEN, index, NULL);
      _ASSERT(length <= 65536);
      std::vector<char> buffer(length + 1);
      SendMessage(m_hwnd, LB_GETTEXT, index, (::lparam)&buffer.front());
      storage->setString(&buffer.front());
   }

   void ListBox::setItemText(int index, const char *str)
   {
      int si = getSelectedIndex();
      int top = getTopIndex();
      LRESULT lresult = SendMessage(m_hwnd, LB_GETTOPINDEX, NULL, NULL);
      unsigned int topIndex = (unsigned int)lresult;
      _ASSERT(topIndex == lresult);
      ::lparam data = getItemData(index);
      removeString(index);
      insertString(index, str, data);
      if (si == index) {
         setSelectedIndex(si);
      }
      setTopIndex(top);
   }

   void ListBox::appendString(const char *str, ::lparam data)
   {
      LRESULT lresult = SendMessage(m_hwnd, LB_ADDSTRING, 0, (::lparam)str);
      int index = (int)lresult;
      _ASSERT(index == lresult);
      setItemData(index, data);
   }

   void ListBox::insertString(int index, const char *str)
   {
      SendMessage(m_hwnd, LB_INSERTSTRING, index, (::lparam)str);
   }

   void ListBox::insertString(int index, const char *str, ::lparam data)
   {
      LRESULT lresult = SendMessage(m_hwnd, LB_INSERTSTRING, index, (::lparam)str);
      int i = (int)lresult;
      _ASSERT(i == lresult);
      setItemData(i, data);
   }

   void ListBox::setItemData(int index, ::lparam data)
   {
      SendMessage(m_hwnd, LB_SETITEMDATA, index, data);
   }

   ::lparam ListBox::getItemData(int index)
   {
      return SendMessage(m_hwnd, LB_GETITEMDATA, index, NULL);
   }

   int ListBox::getCount()
   {
      LRESULT lresult = SendMessage(m_hwnd, LB_GETCOUNT, NULL, NULL);
      int result = (int)lresult;
      _ASSERT(result == lresult);
      return result;
   }

   void ListBox::clear()
   {
      SendMessage(m_hwnd, LB_RESETCONTENT, NULL, NULL);
   }

   int ListBox::getSelectedIndex()
   {
      LRESULT lresult = SendMessage(m_hwnd, LB_GETCURSEL, NULL, NULL);
      int index = (int)lresult;
      _ASSERT(index == lresult);
      return (index == LB_ERR) ? -1 : index;
   }

   void ListBox::setSelectedIndex(int index)
   {
      SendMessage(m_hwnd, LB_SETCURSEL, index, NULL);
   }
} // namespace innate_subsystem

