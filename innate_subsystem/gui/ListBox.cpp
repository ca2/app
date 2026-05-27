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
#include "framework.h"
#include "ListBox.h"

namespace innate_subsystem
{
//    ListBox::ListBox()
//    {
//    }
//
//    ListBox::~ListBox()
//    {
//    }
//
//    /*void ListBox::addString(const_char_pointer str)
//    {
//       //addString(str, 0);
//       m_pparticleThis->addString(str);
//    }
//
//    void ListBox::addString(const_char_pointer str, void *tag)
//    {
//       // LRESULT lresult = SendMessage(m_hwnd, LB_ADDSTRING, 0, (::lparam)str);
//       // ::i32 i = (::i32)lresult;
//       // _ASSERT(i == lresult);
//       // setItemData(i, (::lparam)tag);
//       m_pparticleThis->addString(str, tag);
//    }
//
//    void ListBox::removeString(::i32 index)
//    {
//       // ::i32 top = getTopIndex();
//       // SendMessage(m_hwnd, LB_DELETESTRING, index, NULL);
//       // setTopIndex(top);
//       m_pparticleThis->removeString(index);
//    }
//
//    ::i32 ListBox::getTopIndex()
//    {
//       //return (::i32)SendMessage(m_hwnd, LB_GETTOPINDEX, NULL, NULL);
//       return m_pparticleThis->getTopIndex();
//    }
//
//    void ListBox::setTopIndex(::i32 index)
//    {
//       //SendMessage(m_hwnd, LB_SETTOPINDEX, index, NULL);
//       m_pparticleThis->setTopIndex(index);
//    }
//
//    ::string ListBox::getItemText(::i32 index)
//    {
//       // size_t length = SendMessage(m_hwnd, LB_GETTEXTLEN, index, NULL);
//       // _ASSERT(length <= 65536);
//       // std::vector<::i8> buffer(length + 1);
//       // SendMessage(m_hwnd, LB_GETTEXT, index, (::lparam)&buffer.front());
//       // storage->setString(&buffer.front());
//
//       return m_pparticleThis->getItemText(index);
//    }
//
//    void ListBox::setItemText(::i32 index, const_char_pointer str)
//    {
//       m_pparticleThis->setItemText(index, str);
//       // ::i32 si = getSelectedIndex();
//       // ::i32 top = getTopIndex();
//       // LRESULT lresult = SendMessage(m_hwnd, LB_GETTOPINDEX, NULL, NULL);
//       // ::u32 topIndex = (::u32)lresult;
//       // _ASSERT(topIndex == lresult);
//       // ::lparam data = getItemData(index);
//       // removeString(index);
//       // insertString(index, str, data);
//       // if (si == index) {
//       //    setSelectedIndex(si);
//       // }
//       // setTopIndex(top);
//    }
//
//    void ListBox::appendString(const_char_pointer str, ::lparam data)
//    {
//       // LRESULT lresult = SendMessage(m_hwnd, LB_ADDSTRING, 0, (::lparam)str);
//       // ::i32 index = (::i32)lresult;
//       // _ASSERT(index == lresult);
//       // setItemData(index, data);
//       m_pparticleThis->appendString(str, data);
//    }
//
//    void ListBox::insertString(::i32 index, const_char_pointer str)
//    {
//       //SendMessage(m_hwnd, LB_INSERTSTRING, index, (::lparam)str);
//       m_pparticleThis->insertString(index, str);
//    }
//
//    void ListBox::insertString(::i32 index, const_char_pointer str, ::lparam data)
//    {
//       // LRESULT lresult = SendMessage(m_hwnd, LB_INSERTSTRING, index, (::lparam)str);
//       // ::i32 i = (::i32)lresult;
//       // _ASSERT(i == lresult);
//       // setItemData(i, data);
//       m_pparticleThis->insertString(index, str, data);
//    }
//
//    void ListBox::setItemData(::i32 index, ::lparam data)
//    {
//       //SendMessage(m_hwnd, LB_SETITEMDATA, index, data);
//       m_pparticleThis->setItemData(index, data);
//    }
//
//    ::lparam ListBox::getItemData(::i32 index)
//    {
//       //return SendMessage(m_hwnd, LB_GETITEMDATA, index, NULL);
//       return m_pparticleThis->getItemData(index);
//    }
//
//    ::i32 ListBox::getCount()
//    {
//       // LRESULT lresult = SendMessage(m_hwnd, LB_GETCOUNT, NULL, NULL);
//       // ::i32 result = (::i32)lresult;
//       // _ASSERT(result == lresult);
//       // return result;
//       return m_pparticleThis->getCount();
//    }
//
//    void ListBox::clear()
//    {
//    ///   SendMessage(m_hwnd, LB_RESETCONTENT, NULL, NULL);
//       m_pparticleThis->getCount();
//    }
//
//    ::i32 ListBox::getSelectedIndex()
//    {
// //      LRESULT lresult = SendMessage(m_hwnd, LB_GETCURSEL, NULL, NULL);
//       // ::i32 index = (::i32)lresult;
//       // _ASSERT(index == lresult);
//       // return (index == LB_ERR) ? -1 : index;
//       return m_pparticleThis->getSelectedIndex();
//    }
//
//    void ListBox::setSelectedIndex(::i32 index)
//    {
//       ///SendMessage(m_hwnd, LB_SETCURSEL, index, NULL);
//       m_pparticleThis->setSelectedIndex(index);
//    }
//    */
} // namespace innate_subsystem

