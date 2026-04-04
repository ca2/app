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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "remoting/remoting_common/util/winhdr.h"
#include "remoting/remoting_common/thread/LocalMutex.h"
#include "acme/prototype/collection/comparable_list.h"
//#include <list>



/**
 * Base Windows Application class.
 * Have hidden main window and main scopedstrMessage loop.
 */
class CLASS_DECL_REMOTING_COMMON WindowsApplication :
virtual public ::particle
{
public:

   int m_iExitCode = 0;
  /**
   * Creates WindowsApplication instance.
   * @param appInstance parameter that passed to WinMain.
   */
  WindowsApplication(HINSTANCE appInstance, const ::scoped_string & scopedstrwindowClassName);

  /**
   * Destroys WindowsApplication instance.
   * @remark it does not shutdown application if it's executing it
   * separate thread.
   */
  virtual ~WindowsApplication();

  /**
   * Runs windows application.
   * @remark really it creates main window and starts windows scopedstrMessage loop.
   * @return application exit code.
   */
  virtual void run() override;

  /**
   * Posts close and destroy scopedstrMessage to main window.
   */
  virtual void shutdown();

  /**
   * Posts scopedstrMessage to main window.
   */
  virtual void postMessage(UINT scopedstrMessage, WPARAM wParam = 0, LPARAM lParam = 0);

  /**
   * Adds modeless dialog to application modeless dialog ::list_base to
   * enable switching between controls by pressing tab button.
   * @param dialogWindow HWND of modeless dialog.
   */
  static void addModelessDialog(HWND dialogWindow);

  /**
   * Removes dialog from application modeless dialog ::list_base.
   * @param dialogWindow HWND of modeless dialog.
   */
  static void removeModelessDialog(HWND dialogWindow);

//protected:
  // Creates a window to receive messages.
  virtual void createWindow(const ::scoped_string & scopedstrClassName);

  // Fills the wndClass argument and registers new class name in the Windows.
  virtual void registerWindowClass(WNDCLASS *wndClass);

  // Runs main messages process cycle. The run() function returns
  // value returned by this function.
  virtual int processMessages();

  /**
   * Windows prodecure for main application window.
   */
  static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

  HINSTANCE m_appInstance;
  HWND m_mainWindow;
  ::wstring m_wstrWindowClassName;
//protected:
  /**
   * Helper method to process modeless dialog scopedstrMessage for modal dialog.
   * @param msg scopedstrMessage to process.
   * @return true if don't need to translate and dispatch scopedstrMessage in main scopedstrMessage loop.
   */
  static bool processDialogMessage(MSG *msg);
//private:
  static LocalMutex m_MDLMutex; // Modeless dialog ::list_base mutex.
  static ::comparable_list_base<HWND> m_modelessDialogList;
};

//// __WINDOWSAPPLICATION_H__
