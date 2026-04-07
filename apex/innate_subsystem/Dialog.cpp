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
#include "Dialog.h"

// #include <commctrl.h>
// #include <crtdbg.h>


namespace innate_subsystem
{

Dialog::Dialog()
//: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
{
}

Dialog::Dialog(DWORD resourceId)
: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
{
}

Dialog::Dialog(const char *resourceName)
: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
{
  setResourceName(resourceName);
}

Dialog::~Dialog()
{
  if (m_hicon) {
    DeleteObject(m_hicon);
  }
  if (m_resourceName != 0) {
    free(m_resourceName);
  }
}


   void Dialog::initialize_dialog(DWORD resourceId)
///: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
{
   m_pparticleThis
}

   Dialog::Dialog(const char *resourceName)
   : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
{
   setResourceName(resourceName);
}


void Dialog::setResourceName(const char *resourceName)
{
  if (m_resourceName != 0) {
    free(m_resourceName);
  }

  m_resourceName = _tcsdup(resourceName);
}

void Dialog::setResourceId(DWORD id)
{
  m_resourceId = id;
}

void Dialog::setDefaultPushButton(unsigned int buttonId)
{
  SendMessage(m_ctrlThis.getWindow(), DM_SETDEFID, buttonId, 0);
}

void Dialog::setParent(Control *ctrlParent)
{
  m_ctrlParent = ctrlParent;
}

int Dialog::show()
{
  if (m_ctrlThis.getWindow() == NULL) {
    create();
  } else {
    m_ctrlThis.setForeground();
  }
  return 0;
}

void Dialog::hide()
{
  m_ctrlThis.setVisible(false);
}

void Dialog::kill(int code)
{
  // Destroy dialog
  if (!m_isModal) {
    DestroyWindow(m_ctrlThis.getWindow());
  } else {
    EndDialog(m_ctrlThis.getWindow(), code);
  }
  // We have no valid hwnd, so forse set hwnd to NULL
  m_ctrlThis.setWindow(NULL);
}

void Dialog::create()
{
  HWND window, parentWindow = NULL;

  if (m_ctrlParent != NULL) {
    parentWindow = m_ctrlParent->getWindow();
  }

  window = CreateDialogParam(GetModuleHandle(NULL), getResouceName(),
                             parentWindow, dialogProc, (::lparam)this);

  m_isModal = false;

  _ASSERT(window != NULL);
}

int Dialog::showModal()
{
  int result = 0;
  if (m_ctrlThis.getWindow() == NULL) {
    m_isModal = true;
    HWND parentWindow = (m_ctrlParent != NULL) ? m_ctrlParent->getWindow() : NULL;
    result = (int)DialogBoxParam(GetModuleHandle(NULL),
                                 getResouceName(),
                                 parentWindow, dialogProc, (::lparam)this);
  } else {
    m_ctrlThis.setVisible(true);
    m_ctrlThis.setForeground();
  }

  //
  // TODO: Place error notification here
  //

  if (result == -1) {
  }

  return result;
}

bool Dialog::isCreated()
{
  bool isInit = m_ctrlThis.getWindow() != 0;

  if (!isInit) {
    return false;
  }

  return !!IsWindow(m_ctrlThis.getWindow());
}

BOOL Dialog::onDrawItem(::wparam controlID, LPDRAWITEMSTRUCT dis)
{
  return TRUE;
}

void Dialog::onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam)
{
}

INT_PTR CALLBACK Dialog::dialogProc(const ::operating_system::window & operatingsystemwindow, unsigned int uMsg, ::wparam wparam, ::lparam lparam)
{
  Dialog *_this;
  BOOL bResult;

  bResult = FALSE;
  if (uMsg == WM_INITDIALOG) {
    _this = (Dialog *)::lparam;
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)_this);
    _this->m_ctrlThis.setWindow(hwnd);
    _this->updateIcon();
  } else {
    _this = (Dialog *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (_this == 0) {
      return FALSE;
    }
  }

  _this->onMessageReceived(uMsg, ::wparam, ::lparam);

  switch (uMsg) {
  case WM_INITDIALOG:
    bResult = _this->onInitDialog();
    break;
  case WM_NOTIFY:
    bResult = _this->onNotify(LOWORD(::wparam), ::lparam);
    break;
  case WM_COMMAND:
    bResult =_this->onCommand(LOWORD(::wparam), HIWORD(::wparam));
    break;
  case WM_CLOSE:
    bResult = _this->onClose();
    break;
  case WM_DESTROY:
    bResult = _this->onDestroy();
    break;
  case WM_DRAWITEM:
    bResult = _this->onDrawItem(::wparam, (LPDRAWITEMSTRUCT)::lparam);
    break;
  }

  return bResult;
}

char *Dialog::getResouceName()
{
  if (m_resourceId != 0) {
    return MAKEINTRESOURCE(m_resourceId);
  }
  return m_resourceName;
}

void Dialog::setControlById(Control &control, DWORD id) 
{
  control = GetDlgItem(m_ctrlThis.getWindow(), id);
}

void Dialog::updateIcon()
{
  if (m_hicon) {
    SetClassLongPtr(m_ctrlThis.getWindow(), GCLP_HICON, (LONG_PTR)m_hicon);
  }
}

void Dialog::loadIcon(DWORD id)
{
  if (m_hicon) {
    DeleteObject(m_hicon);
  }
  m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
}

bool Dialog::setForeground()
{
  return m_ctrlThis.setForeground();
}

BOOL Dialog::onInitDialog()
{
  return FALSE;
}

BOOL Dialog::onNotify(unsigned int controlID, ::lparam data)
{
  return FALSE;
}

BOOL Dialog::onCommand(unsigned int controlID, unsigned int notificationID)
{
  return FALSE;
}

BOOL Dialog::onDestroy()
{
  return FALSE;
}

BOOL Dialog::onClose()
{
  return FALSE;
}


bool Dialog::dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam)
{

   return false;

}

} // namespace innate_subsystem