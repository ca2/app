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
#include "Control.h"


namespace innate_subsystem
{

//   IMPLEMENT_COMPOSITE(Control, Window, control)

   // void ControlInterface::setVisible(bool visible)
   // {
   //
   //    if (visible)
   //    {
   //
   //       show();
   //
   //    }
   //    else
   //    {
   //
   //       hide();
   //
   //    }
   //    //ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
   // }


// ControlComposite::ControlComposite()
// //: m_hwnd(NULL)
// {
// }
// //
// // ControlComposite::ControlComposite(const ::operating_system::window & operatingsystemwindow)
// // : m_hwnd(hwnd)
// // {
// // }
//
// ControlComposite::~ControlComposite()
// {
// }
//
// //    void ControlComposite::initialize_control(const ::operating_system::window & operatingsystemwindow)
// // //: m_hwnd(hwnd)
// // {
// //    m_pparticleThis->initialize_control(operatingsystemwindow);
// // }
//
// //void ControlComposite::setWindow(const ::operating_system::window & operatingsystemwindow)
// //
// //   {
// //   m_pparticleThis->setWindow(operatingsystemwindow);
// //  // Save handle
// //  // m_hwnd = hwnd;
// //  // // Save pointer to default window proc
// //  // m_defWindowProc = (WNDPROC)GetWindowLongPtr(m_hwnd, GWLP_WNDPROC);
// //}
//
//
// //    void ControlComposite::setEnabled(bool enabled)
// //    {
// //
// //       m_pparticleThis->setEnabled(enabled);
// //   // if (enabled) {
// //   //   SendMessage(m_hwnd, WM_ENABLE, TRUE, NULL);
// //   //   removeStyle(WS_DISABLED);
// //   // } else {
// //   //   if (isStyleEnabled(WS_DISABLED)) {
// //   //     return ;
// //   //   } // if already disabled
// //   //   SendMessage(m_hwnd, WM_ENABLE, FALSE, NULL);
// //   //   addStyle(WS_DISABLED);
// //   // }
// //   // invalidate();
// // }
//
// /*void ControlComposite::setText(const char *text)
// {
//
//    m_pparticleThis->setText(text);
//   ///SetWindowText(m_hwnd, text);
// }
//
// void ControlComposite::setSignedInt(int value)
// {
//    m_pparticleThis->setSignedInt(value);
//   // ::string text;
//   // text.format(_T("%d"), value);
//   // setText(text.getString());
// }
//
// void ControlComposite::setUnsignedInt(unsigned int value)
// {
//    m_pparticleThis->setUnsignedInt(value);
//   //::string text;
//   //text.format(_T("%u"), value);
//   //setText(text.getString());
// }
//
// //
// // FIXME: Stub
// //
//
// void ControlComposite::setTextVerticalAlignment(VerticalAlignment align)
// {
//    m_pparticleThis->setTextVerticalAlignment(align);
// }
//
// // void ControlComposite::setFocus()
// // {
// //   //::SetFocus(m_hwnd);
// //    m_pparticleThis->setFocus();
// // }
// //
// // bool ControlComposite::hasFocus()
// // {
// //   ///return (::GetFocus() == m_hwnd) || (GetForegroundWindow() == m_hwnd);
// //   return m_pparticleThis->hasFocus();
// // }
// //
// // bool ControlComposite::setForeground()
// // {
// //   //return SetForegroundWindow(getWindow()) != 0;
// //
// //    return m_pparticleThis->setForeground();
// // }
//
// void ControlComposite::setVisible(bool visible)
// {
//   //ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
//    m_pparticleThis->setVisible(visible);
// }
//
// // bool ControlComposite::isEnabled()
// // {
// //   ///return (!isStyleEnabled(WS_DISABLED));
// //   return m_pparticleThis->isEnabled();
// // }
// //
// // void ControlComposite::invalidate()
// // {
// //   //InvalidateRect(m_hwnd, NULL, TRUE);
// //    m_pparticleThis->invalidate();
// // }
//
// //::string ControlComposite::getText()
// //{
// //  // int length = (int)SendMessage(m_hwnd, WM_GETTEXTLENGTH, 0, 0);
// //  // std::vector<char> buf(length + 1);
// //  // GetWindowText(m_hwnd, &buf.front(), length + 1);
// //  // storage->setString(&buf.front());
// //
// //   return m_pparticleThis->getText();
// //}
//
// //
// // FIXME: Stub
// //
//
// VerticalAlignment ControlComposite::getTextVerticalAlignment()
// {
//   return m_pparticleThis->getTextVerticalAlignment();
// }
//
// //::operating_system::window ControlComposite::operating_system_window()
// //{
// //  return m_pparticleThis->operating_system_window();
// //}
//
//
// //void ControlComposite::subclassWindow()
// //{
// //
// //   m_pparticleThis->subclassWindow();
// //
// //}
// */
//
//
// // void ControlComposite::setStyle(unsigned int style)
// // {
// //   ::SetWindowLong(m_hwnd, GWL_STYLE, style);
// // }
// //
// // unsigned int ControlComposite::getStyle()
// // {
// //   return ::GetWindowLong(m_hwnd, GWL_STYLE);
// // }
// //
// // void ControlComposite::addStyle(unsigned int styleFlag)
// // {
// //   unsigned int flags = getStyle();
// //   flags |= styleFlag;
// //   setStyle(flags);
// // }
// //
// // void ControlComposite::removeStyle(unsigned int styleFlag)
// // {
// //   unsigned int flags = getStyle();
// //   flags &= ~styleFlag;
// //   setStyle(flags);
// // }
// //
// // bool ControlComposite::isStyleEnabled(unsigned int styleFlag)
// // {
// //   unsigned int flags = getStyle();
// //   return (flags & styleFlag) == styleFlag;
// // }
// //
// // void ControlComposite::setExStyle(unsigned int style)
// // {
// //   SetWindowLong(m_hwnd, GWL_EXSTYLE, style);
// // }
// //
// // unsigned int ControlComposite::getExStyle()
// // {
// //   return (unsigned int)GetWindowLong(m_hwnd, GWL_EXSTYLE);
// // }
// //
// // void ControlComposite::addExStyle(unsigned int styleFlag)
// // {
// //   unsigned int flags = getExStyle();
// //   flags |= styleFlag;
// //   setExStyle(flags);
// // }
// //
// // void ControlComposite::removeExStyle(unsigned int styleFlag)
// // {
// //   unsigned int flags = getExStyle();
// //   flags &= ~styleFlag;
// //   setExStyle(flags);
// // }
// //
// // bool ControlComposite::isExStyleEnabled(unsigned int styleFlag)
// // {
// //   unsigned int flags = getExStyle();
// //   return (flags & styleFlag) == styleFlag;
// // }
//
// // void ControlComposite::replaceWindowProc(WNDPROC wndProc)
// // {
// //   SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
// //   SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)wndProc);
// // }
//
//
// // void ControlComposite::postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam)
// // {
// //
// //    m_pparticleThis->postUserMessage(uMessage, wparam, lparam);
// //
// // }
//


} // namespace innate_subsystem
