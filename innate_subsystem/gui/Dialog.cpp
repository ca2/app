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

#include "_common_header.h"

// //#include <CommCtrl.h>
// #include <crtdbg.h>


namespace innate_subsystem
{

// Dialog::Dialog()
// //: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
// {
// }
//
// // Dialog::Dialog(unsigned int resourceId)
// // : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
// // {
// // }
// //
// // Dialog::Dialog(const char *resourceName)
// // : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
// // {
// //   setResourceName(resourceName);
// // }
//
// Dialog::~Dialog()
// {
//   // if (m_hicon) {
//   //   DeleteObject(m_hicon);
//   // }
//   // if (m_resourceName != 0) {
//   //   free(m_resourceName);
//   // }
// }
//
//
//    /*void Dialog::initialize_dialog(unsigned int resourceId)
// ///: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
// {
//    m_pparticleThis->initialize_dialog(resourceId);
// }
//
//    void Dialog::initialize_dialog(const char *resourceName)
//    //: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
// {
//    //setResourceName(resourceName);
//    m_pparticleThis->initialize_dialog(resourceName);
// }
//
//
// void Dialog::setResourceName(const char *resourceName)
// {
//   // if (m_resourceName != 0) {
//   //   free(m_resourceName);
//   // }
//   //
//   // m_resourceName = _tcsdup(resourceName);
//
//    m_pparticleThis->setResourceName(resourceName);
// }
//
// void Dialog::setResourceId(unsigned int id)
// {
//   //m_resourceId = id;
//    m_pparticleThis->setResourceId(id);
// }
//
//
// // ControlInterface *Dialog::getControl()
// // {
// //
// //    return m_pparticleThis->getControl();
// //
// // }
//
//
// void Dialog::setDefaultPushButton(unsigned int buttonId)
// {
//   //SendMessage(this->getWindow(), DM_SETDEFID, buttonId, 0);
//    m_pparticleThis->setDefaultPushButton(buttonId);
// }
//
// // void Dialog::setParent(ControlInterface *ctrlParent)
// // {
// //   //m_ctrlParent = ctrlParent;
// //    m_pparticleThis->setParent(ctrlParent);
// // }
//
// void Dialog::show()
// {
//   // if (this->getWindow() == NULL) {
//   //   create();
//   // } else {
//   //   this->setForeground();
//   // }
//   m_pparticleThis->show();
// }
//
// void Dialog::hide()
// {
//   //this->setVisible(false);
//
//    m_pparticleThis->hide();
// }
//
// void Dialog::closeDialog(int code)
// {
//   // // Destroy dialog
//   // if (!m_isModal) {
//   //   DestroyWindow(this->getWindow());
//   // } else {
//   //   EndDialog(this->getWindow(), code);
//   // }
//   // // We have no valid hwnd, so forse set hwnd to NULL
//   // this->setWindow(NULL);
//
//    m_pparticleThis->closeDialog(code);
// }
//
// void Dialog::create()
// {
//   // HWND window, parentWindow = NULL;
//   //
//   // if (m_ctrlParent != NULL) {
//   //   parentWindow = m_ctrlParent->getWindow();
//   // }
//   //
//   // window = CreateDialogParam(GetModuleHandle(NULL), getResouceName(),
//   //                            parentWindow, dialogProc, (::lparam)this);
//   //
//   // m_isModal = false;
//   //
//   // _ASSERT(window != NULL);
//    m_pparticleThis->create();
// }
//
// int Dialog::showModal()
// {
//   // int result = 0;
//   // if (this->getWindow() == NULL) {
//   //   m_isModal = true;
//   //   HWND parentWindow = (m_ctrlParent != NULL) ? m_ctrlParent->getWindow() : NULL;
//   //   result = (int)DialogBoxParam(GetModuleHandle(NULL),
//   //                                getResouceName(),
//   //                                parentWindow, dialogProc, (::lparam)this);
//   // } else {
//   //   this->setVisible(true);
//   //   this->setForeground();
//   // }
//   //
//   // //
//   // // TODO: Place error notification here
//   // //
//   //
//   // if (result == -1) {
//   // }
//   //
//   // return result;
//    return m_pparticleThis->showModal();
// }
//
// bool Dialog::isCreated()
// {
//   // bool isInit = this->getWindow() != 0;
//   //
//   // if (!isInit) {
//   //   return false;
//   // }
//   //
//   // return !!IsWindow(this->getWindow());
//
//    return m_pparticleThis->isCreated();
// }
//
// bool Dialog::onDrawItem(::wparam controlID, draw_item_t * pdrawitem)
// {
// //  return TRUE;
//    return m_pparticleThis->onDrawItem(controlID, pdrawitem);
// }
//
// void Dialog::onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam)
// {
//    m_pparticleThis->onMessageReceived(uMsg, wparam, lparam);
// }
//
// bool Dialog::dialog_procedure(iptr & result, unsigned int uMsg, ::wparam wparam, ::lparam lparam)
// {
//
//    return m_pparticleThis->dialog_procedure(result, uMsg, wparam, lparam);
//   // Dialog *_this;
//   // bool bResult;
//   //
//   // bResult = FALSE;
//   // if (uMsg == WM_INITDIALOG) {
//   //   _this = (Dialog *)::lparam;
//   //   SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)_this);
//   //   _this->this->setWindow(hwnd);
//   //   _this->updateIcon();
//   // } else {
//   //   _this = (Dialog *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//   //   if (_this == 0) {
//   //     return FALSE;
//   //   }
//   // }
//   //
//   // _this->onMessageReceived(uMsg, ::wparam, ::lparam);
//   //
//   // switch (uMsg) {
//   // case WM_INITDIALOG:
//   //   bResult = _this->onInitDialog();
//   //   break;
//   // case WM_NOTIFY:
//   //   bResult = _this->onNotify(LOWORD(::wparam), ::lparam);
//   //   break;
//   // case WM_COMMAND:
//   //   bResult =_this->onCommand(LOWORD(::wparam), HIWORD(::wparam));
//   //   break;
//   // case WM_CLOSE:
//   //   bResult = _this->onClose();
//   //   break;
//   // case WM_DESTROY:
//   //   bResult = _this->onDestroy();
//   //   break;
//   // case WM_DRAWITEM:
//   //   bResult = _this->onDrawItem(::wparam, (LPDRAWITEMSTRUCT)::lparam);
//   //   break;
//   // }
//
// //  return bResult;
// }
//
// char *Dialog::getResouceName()
// {
//   // if (m_resourceId != 0) {
//   //   return MAKEINTRESOURCE(m_resourceId);
//   // }
//   // return m_resourceName;
//    return m_pparticleThis->getResouceName();
// }
//
// // void Dialog::subclassControlById(ControlInterface * pcontrol, unsigned int id)
// // {
// //   // control = GetDlgItem(this->getWindow(), id);
// //    m_pparticleThis->subclassControlById(pcontrol, id);
// // }
//
// void Dialog::updateIcon()
// {
//   // if (m_hicon) {
//   //   SetClassLongPtr(this->getWindow(), GCLP_HICON, (LONG_PTR)m_hicon);
//   // }
//    m_pparticleThis->updateIcon();
// }
//
// void Dialog::loadIcon(unsigned int id)
// {
//   // if (m_hicon) {
//   //   DeleteObject(m_hicon);
//   // }
//   // m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
//    m_pparticleThis->loadIcon(id);
// }
//
// bool Dialog::setForeground()
// {
//   //return this->setForeground();
//
//    return m_pparticleThis->setForeground();
// }
//
// bool Dialog::onInitDialog()
// {
//   //return FALSE;
//
//    return m_pparticleThis->onInitDialog();
// }
//
// // bool Dialog::onNotify(unsigned int controlID, ::lparam data)
// // {
// //   //return FALSE;
// //    return m_pparticleThis->onNotify(controlID, data);
// // }
//
// bool Dialog::onCommand(unsigned int controlID, unsigned int notificationID)
// {
//   //return FALSE;
//
//    return m_pparticleThis->onCommand(controlID, notificationID);
// }
//
// bool Dialog::onDestroy()
// {
//   //return FALSE;
//    return m_pparticleThis->onDestroy();
// }
//
// bool Dialog::onClose()
// {
//   //return FALSE;
//    return m_pparticleThis->onClose();
// }
//
//
// // bool Dialog::dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam)
// // {
// //
// //    return m_pparticleThis->dialog_procedure(iptrResult,message, wparam, lparam);
// //
// // }
// */

} // namespace innate_subsystem
