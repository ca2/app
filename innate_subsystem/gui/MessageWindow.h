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

//#include "util/CommonHeader.h"
//#include "WindowMessageHandler.h"

//
// namespace innate_subsystem
// {
//
// class MessageWindow
// {
// public:
//   // messageHandler is an external message handler that replace the
//   // wndProc() function on message processing. If
//   // messageHandler == 0 the wndProc() function will be used.
//   MessageWindow(const HINSTANCE hinst, const_char_pointer windowClassName,
//                 WindowMessageHandler *messageHandler = 0);
//   virtual ~MessageWindow(void);
//
//   virtual bool createWindow(WindowMessageHandler *messageHandler = 0);
//   virtual void destroyWindow();
//
//   HWND getHWND() const { return m_hwnd; }
//
// protected:
//   // Function must return true value if the message has been processed.
//   virtual bool wndProc(::u32 message, ::wparam wparam, ::lparam lparam) { return true; }
//
//   HWND m_hwnd;
//   WindowMessageHandler *m_pwindowmessagehandler;
//
//   HINSTANCE m_hinst;
//   char_pointer m_windowClassName;
//
// private:
//   ATOM regClass(HINSTANCE hinst, char_pointer windowClassName);
//
//   static LRESULT CALLBACK staticWndProc(const ::operating_system::window & operatingsystemwindow,
//                                         ::u32 message,
//                                         ::wparam wparam,
//                                         ::lparam lparam);
// };
//
// #endif // __WINDOW_H__
