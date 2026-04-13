// Copyright (C) 2011,2012 GlavSoft LLC.
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
#include "Toolbar.h"
//#include <CommCtrl.h>

namespace innate_subsystem
{
   Toolbar::Toolbar()
   {
      // INITCOMMONCONTROLSEX initCtrlEx;
      //
      // initCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
      // initCtrlEx.dwICC  = ICC_BAR_CLASSES;
      // InitCommonControlsEx(&initCtrlEx);
      //
      // m_hWndToolbar = 0;
      // m_initialStr = -1;
   }

   Toolbar::~Toolbar()
   {
      // if (m_hWndToolbar) {
      //    DestroyWindow(m_hWndToolbar);
      // }
   }

   bool Toolbar::create(int _tbID, const ::operating_system::window & operatingsystemwindowParent, unsigned int dwStyle)
   {

      return m_pparticleThis->create(_tbID, operatingsystemwindowParent, dwStyle);
      // dwStyle |= WS_CHILD;
      //
      // _ASSERT(m_hWndToolbar == 0);
      // // Create the Toolbar window
      // m_hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, 0, dwStyle,
      //                                0, 0, 0, 0,
      //                                _parentHwnd,
      //                                reinterpret_cast<HMENU>(_tbID),
      //                                GetModuleHandle(0),
      //                                0);
      // if (m_hWndToolbar) {
      //    // It's required for backward compatibility
      //    SendMessage(m_hWndToolbar,
      //                TB_BUTTONSTRUCTSIZE,
      //                static_cast<::wparam>(sizeof(TBBUTTON)),
      //                0);
      // }
      // return !!m_hWndToolbar;
   }

   void Toolbar::setViewAutoButtons(int iButton, int style)
   {
      //m_autoButtons[iButton] = style;
      return m_pparticleThis->setViewAutoButtons(iButton, style);
   }

   void Toolbar::loadToolbarfromRes(unsigned int id)
   {
      // BITMAP bmp;
      //
      // HBITMAP hbmp = LoadBitmap(GetModuleHandle(NULL),
      //                           MAKEINTRESOURCE(id));
      // GetObject(hbmp, sizeof(BITMAP), &bmp);
      // m_width = bmp.bmWidth;
      // m_height = bmp.bmHeight;
      // m_numberTB = m_width / m_height;
      // m_id = id;
      // DeleteObject(hbmp);
      m_pparticleThis->loadToolbarfromRes(id);
   }


   void Toolbar::loadToolbarFromMatter(const file::path &pathMatter)
   {

      // BITMAP bmp;
      //
      // HBITMAP hbmp = LoadBitmap(GetModuleHandle(NULL),
      //                           MAKEINTRESOURCE(id));
      // GetObject(hbmp, sizeof(BITMAP), &bmp);
      // m_width = bmp.bmWidth;
      // m_height = bmp.bmHeight;
      // m_numberTB = m_width / m_height;
      // m_id = id;
      // DeleteObject(hbmp);
      m_pparticleThis->loadToolbarFromMatter(pathMatter);
   }


   void Toolbar::setButtonsRange(unsigned int id)
   {
      //m_initialStr = id;
      m_pparticleThis->setButtonsRange(id);
   }

   void Toolbar::attachToolbar(const ::operating_system::window & operatingsystemwindow)
   {
      m_pparticleThis->attachToolbar(operatingsystemwindow);
      // std::vector<TBBUTTON> tbuttons;
      //
      // for (int i=0; i < m_numberTB; i++) {
      //    TBBUTTON tbutton;
      //
      //    ZeroMemory(&tbutton, sizeof(tbutton));
      //    if (m_autoButtons.find(i) != m_autoButtons.end()) {
      //       // TODO: paste here all your variants of possible
      //       // toolbar buttons
      //       switch(m_autoButtons[i]) {
      //          case TB_Style_sep:
      //             tbutton.fsStyle = TBSTYLE_SEP;
      //             tbuttons.push_back(tbutton);
      //             break;
      //          case TB_Style_gap:
      //             tbutton.iBitmap = I_IMAGENONE;
      //             tbuttons.push_back(tbutton);
      //             break;
      //       }
      //    }
      //    tbutton.iBitmap = i;
      //    tbutton.idCommand = m_initialStr == 0 ? 0 : m_initialStr + i;
      //    tbutton.fsState   = TBSTATE_ENABLED;
      //    tbutton.fsStyle   = TBSTYLE_BUTTON;
      //    tbuttons.push_back(tbutton);
      // }
      // m_autoButtons.clear();
      //
      // m_hWndToolbar = CreateToolbarEx(hwnd,
      //    WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS | WS_CLIPSIBLINGS | TBSTYLE_FLAT | WS_BORDER,
      //    m_id,
      //    static_cast<int>(tbuttons.size()),
      //    GetModuleHandle(NULL),
      //    m_id,
      //    &tbuttons.front(),
      //    static_cast<int>(tbuttons.size()),
      //    0, 0, 0, 0,
      //    sizeof(TBBUTTON));
      // SendMessage(m_hWndToolbar, TB_SETINDENT, 4, 0);
   }

   bool Toolbar::enableButton(int idButton, bool enable)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_ENABLEBUTTON,
      //                              idButton, MAKELONG(enable, 0));
      // return !!result;
      return m_pparticleThis->enableButton(idButton, enable);
   }

   bool Toolbar::pressButton(int idButton, bool press)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_PRESSBUTTON,
      //                              idButton, MAKELONG(press, 0));
      // return !!result;
      return m_pparticleThis->pressButton(idButton, press);
   }

   bool Toolbar::getButtonRect(int nIndex, ::int_rectangle & buttonRect)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_GETITEMRECT,
      //                              nIndex, (::lparam)buttonRect);
      // return !!result;

      return m_pparticleThis->getButtonRect(nIndex, buttonRect);
   }

   bool Toolbar::setButtonsSize(const ::int_size & size)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_SETBUTTONSIZE,
      //                              0, MAKELONG(width, height));
      // if (result) {
      //    SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      //    return true;
      // }
      // return false;
      return m_pparticleThis->setButtonsSize(size);
   }

   void Toolbar::autoSize()
   {
      // LRESULT style = SendMessage(m_hWndToolbar, TB_GETSTYLE,  0, 0);
      // if (style & CCS_NORESIZE) {
      //    RECT r, btnRect;
      //    GetClientRect(GetParent(m_hWndToolbar), &r);
      //    getButtonRect(0, &btnRect);
      //    int height = getButtonsHeight() + btnRect.top * 2 + 2;
      //    SetWindowPos(m_hWndToolbar, HWND_TOP, 0, 0, r.right - r.left, height,
      //                 SWP_NOMOVE);
      // } else {
      //    SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);


      // }

      m_pparticleThis->autoSize();
   }

   int Toolbar::getButtonsHeight()
   {
      // return HIWORD(SendMessage(m_hWndToolbar, TB_GETBUTTONSIZE, 0, 0));
      return m_pparticleThis->getButtonsHeight();
   }

   int Toolbar::getButtonsWidth()
   {
      // return LOWORD(SendMessage(m_hWndToolbar, TB_GETBUTTONSIZE, 0, 0));
      return m_pparticleThis->getButtonsWidth();
   }

   int Toolbar::getHeight()
   {
      // RECT r;
      // GetWindowRect(m_hWndToolbar, &r);
      // return r.bottom - r.top;
      return m_pparticleThis->getHeight();
   }

   int Toolbar::getTotalWidth()
   {
      // SIZE size;
      // SendMessage(m_hWndToolbar, TB_GETMAXSIZE, 0, reinterpret_cast<::lparam>(&size));
      // return size.cx;
      return m_pparticleThis->getTotalWidth();
   }

   void Toolbar::show()
   {
      // ShowWindow(m_hWndToolbar, SW_SHOW);

      return m_pparticleThis->show();
   }

   void Toolbar::hide()
   {
      // ShowWindow(m_hWndToolbar, SW_HIDE);
      return m_pparticleThis->hide();
   }

   bool Toolbar::isVisible()
   {
      // LRESULT style = GetWindowLong(m_hWndToolbar, GWL_STYLE);
      // return !!(style & WS_VISIBLE);

      return m_pparticleThis->isVisible();
   }

   bool Toolbar::checkButton(int idButton, bool check)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_CHECKBUTTON,
      //         idButton, MAKELONG(check, 0));
      // return !!result;
      return m_pparticleThis->checkButton(idButton, check);
   }

   ::lresult Toolbar::getState(int idButton)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_GETSTATE,
      //                  idButton, 0);
      // return result;
      return m_pparticleThis->getState(idButton);
   }

   ::lresult Toolbar::addBitmap(int nButtons, unsigned int bitmapID)
   {
      // TBADDBITMAP resBitmap;
      //
      // resBitmap.hInst = GetModuleHandle(0);
      // resBitmap.nID = bitmapID;
      // return SendMessage(m_hWndToolbar, TB_ADDBITMAP, nButtons, reinterpret_cast<::lparam>(&resBitmap));

      return m_pparticleThis->addBitmap(nButtons, bitmapID);
   }

   ::lresult Toolbar::addSystemBitmap(unsigned int stdBitmapID)
   {
      // TBADDBITMAP resBitmap;
      //
      // resBitmap.hInst = HINST_COMMCTRL;
      // resBitmap.nID = stdBitmapID;
      // return SendMessage(m_hWndToolbar, TB_ADDBITMAP, 0, (::lparam)&resBitmap);
      return m_pparticleThis->addSystemBitmap(stdBitmapID);
   }

   bool Toolbar::addButton(int iBitmap, int idCommand, unsigned char state, unsigned char style, unsigned int dwData, int iString)
   {
      // TBBUTTON tbb;
      //
      // tbb.iBitmap = iBitmap;
      // tbb.idCommand = idCommand;
      // tbb.fsState = state;
      // tbb.fsStyle = style;
      // tbb.dwData = dwData;
      // tbb.iString = iString;
      //
      // LRESULT result = SendMessage(m_hWndToolbar, TB_ADDBUTTONS, 1, reinterpret_cast<::lparam>(&tbb));
      // if (result) {
      //    SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      // }
      // return !!result;
      return m_pparticleThis->addButton(iBitmap, idCommand, state, style, dwData, iString);
   }

   bool Toolbar::addNButton(int nButtons, toolbar_button_t * ptoolbarbutton)
   {
      // LRESULT result = SendMessage(m_hWndToolbar, TB_ADDBUTTONS, nButtons, reinterpret_cast<::lparam>(tbb));
      // if (result) {
      //    SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      // }
      // return !!result;

      return m_pparticleThis->addNButton(nButtons, ptoolbarbutton);
   }
} // namespace innate_subsystem
