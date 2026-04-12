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
#include "framework.h"
#include "ComboBox.h"

//#include <Windowsx.h>

namespace innate_subsystem
{
   ComboBox::ComboBox()
   {
   }

   ComboBox::~ComboBox()
   {
   }

   int ComboBox::addItem(const char *text)
   {
      //return ComboBox_AddString(m_hwnd, text);
      return m_pparticleThis->addItem(text);
   }

   int ComboBox::addItem(const char *text, void *tag)
   {
      // int index = addItem(text);
      // setItemData(index, tag);
      // return index;
      return m_pparticleThis->addItem(text, tag);
   }

   void ComboBox::insertItem(int index, const char *text)
   {
      //ComboBox_InsertString(m_hwnd, index, text);
      m_pparticleThis->insertItem(index, text);
   }

   void ComboBox::insertItem(int index, const char *text, void *tag)
   {
      // insertItem(index, text);
      //setItemData(index, tag);
      m_pparticleThis->insertItem(index, text, tag);
   }

   int ComboBox::getItemsCount()
   {
      //return ComboBox_GetCount(m_hwnd);
      return m_pparticleThis->getItemsCount();
   }

   void ComboBox::setItemData(int index, void *tag)
   {
      //ComboBox_SetItemData(m_hwnd, index, (::lparam)tag);
      m_pparticleThis->setItemData(index, tag);
   }

   void *ComboBox::getItemData(int index)
   {
      //return (void *)ComboBox_GetItemData(m_hwnd, index);
      return m_pparticleThis->getItemData(index);
   }

   ::string  ComboBox::getItemText(int index)
   {
      // size_t length = ComboBox_GetLBTextLen(m_hwnd, index);
      // std::vector<char> buf(length + 1);
      // ComboBox_GetLBText(m_hwnd, index, &buf.front());
      // storage->setString(&buf.front());
      return m_pparticleThis->getItemText(index);
   }

   int ComboBox::getSelectedItemIndex()
   {
      //return ComboBox_GetCurSel(m_hwnd);
      return m_pparticleThis->getSelectedItemIndex();
   }

   void ComboBox::setSelectedItem(int index)
   {
      //ComboBox_SetCurSel(m_hwnd, index);
      m_pparticleThis->setSelectedItem(index);
   }

   void ComboBox::deleteItem(int index)
   {
      //ComboBox_DeleteString(m_hwnd, index);
      m_pparticleThis->deleteItem(index);
   }

   void ComboBox::removeAllItems()
   {
      //ComboBox_ResetContent(m_hwnd);
      m_pparticleThis->removeAllItems();
   }
} // namespace innate_subsystem
