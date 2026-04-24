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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "Clipboard2.h"
//#include "remoting/node_desktop/NamingDefs.h"


namespace subsystem
{


   //Clipboard2::Clipboard2(::subsystem::ClipboardListener *clipboardListener, ::subsystem::LogWriter *log) :
   //    MessageWindow(m_hinst, "subsystem::Clipboard2::MessageWindow"), 
   //   m_hwndNextViewer(0),
   //    m_clipboardListener(clipboardListener), m_plogwriter(log)
   //{
   //   resume();
   //}


   Clipboard2::Clipboard2()
   {


   }

   Clipboard2::~Clipboard2()
   {
      //terminate();
      //wait();
   }


   void Clipboard2::initialize_clipboard2(::subsystem::ClipboardListener *clipboardListener, ::subsystem::LogWriter *log) 
   {
       /*MessageWindow(m_hinst, "subsystem::Clipboard2::MessageWindow"), m_hwndNextViewer(0),
       m_clipboardListener(clipboardListener), m_plogwriter(log)*/
   //{
     // resume();
   }


   bool Clipboard2::writeToClipBoard(const ::scoped_string &scopedstrText)
   {

      ::string clipboard;

      convertFromRfbFormat(scopedstrText, clipboard);

      _writeToClipBoard(clipboard);
         //{
         //      if (OpenClipboard(m_hwnd))
//      {
//         EmptyClipboard();
//
//         size_t clipSize = clipboard.length();
//         HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, clipSize);
//         if (hglb)
//         {
//            TCHAR *buff = (TCHAR *)GlobalLock(hglb);
//            memcpy(buff, clipboard, clipSize);
//            GlobalUnlock(hglb);
//
//#ifdef _UNICODE
//            SetClipboardData(CF_UNICODETEXT, hglb);
//#else
//            SetClipboardData(CF_TEXT, hglb);
//
//            // Store locale information in the clipboard as well.
//            HGLOBAL hmemLocale = GlobalAlloc(GMEM_MOVEABLE, sizeof(LCID));
//            if (hmemLocale != NULL)
//            {
//               LCID *pLocale = (LCID *)GlobalLock(hmemLocale);
//               *pLocale = GetSystemDefaultLCID(); // or maybe GetUserDefaultLCID()?
//               GlobalUnlock(hmemLocale);
//               if (SetClipboardData(CF_LOCALE, hmemLocale) == NULL)
//               {
//                  GlobalFree(hmemLocale);
//               }
//            }
//#endif
//         }
//
//         CloseClipboard();
//      }

      return false;

   }


   bool Clipboard2::_writeToClipBoard(const ::scoped_string& scopedstrText)
   {

      return false;

   }


   void Clipboard2::readFromClipBoard(::string &clipDest)
   {
//// NOTE: In non-Unicode version, conversion correctness may depend on current
////       input language. We should always use Unicode in all programs.
//#ifdef _UNICODE
//      const unsigned int CF_TCTEXT = CF_UNICODETEXT;
//#else
//      const unsigned int CF_TCTEXT = CF_TEXT;
//#endif
//
//      clipDest.clear();
//
//      if (!IsClipboardFormatAvailable(CF_TCTEXT) || !OpenClipboard(m_hwnd))
//      {
//
//         return;
//
//      }
//
//      HANDLE hglb = GetClipboardData(CF_TCTEXT);
//
//      if (hglb != NULL)
//      {
//         
//         auto psz = (char *)GlobalLock(hglb);
//
//         if (psz != 0)
//         {
//            
//            clipDest = psz;
//            
//            GlobalUnlock(psz);
//
//         }
//
//      }
//
//      CloseClipboard();

   }


   //bool WindowsClipboard::wndProc(unsigned int message, ::wparam wparam, ::lparam lparam)
   //{
   //   
   //   int fake = 3;

   //   switch (message)
   //   {
   //      case WM_CREATE:
   //      {

   //         m_hwndNextViewer = SetClipboardViewer(wparam.raw_cast < HWND> ());

   //      }
   //      break;
   //      case WM_CHANGECBCHAIN:
   //      {

   //         if (m_hwndNextViewer == wparam.raw_cast < HWND >())
   //         {

   //            m_hwndNextViewer = wparam.raw_cast<HWND>();

   //         }
   //         else if (m_hwndNextViewer != NULL)
   //         {

   //            SendMessage(m_hwndNextViewer, message, wparam, lparam);

   //         }

   //      }
   //      break;

   //      case WM_DESTROY:
   //      {
   //
   //         ChangeClipboardChain(m_hwnd, m_hwndNextViewer);

   //      }
   //      break;

   //      case WM_DRAWCLIPBOARD: // clipboard contents changed.
   //      {

   //         ::string winClip, rfbClip;

   //         readFromClipBoard(winClip);

   //         convertToRfbFormat(winClip, rfbClip);

   //         m_clipboardListener->onClipboardUpdate(rfbClip);

   //         SendMessage(m_hwndNextViewer, message, wparam, lparam);

   //      }
   //      break;
   //      default:
   //         return false; // Message not processing
   //   }

   //   return true;

   //}


   /*void WindowsClipboard::onTerminate()
   {

      if (m_hwnd != 0)
      {

         PostMessage(m_hwnd, WM_QUIT, 0, 0);

      }

   }*/


   //void WindowsClipboard::execute()
   //{

   //   m_plogwriter->information("clipboard thread id = {}", (::iptr) getThreadId());

   //   if (!createWindow())
   //   {

   //      return;

   //   }

   //   MSG msg;

   //   while (!isTerminating())
   //   {

   //      if (GetMessage(&msg, m_hwnd, 0, 0))
   //      {

   //         DispatchMessage(&msg);

   //      }
   //      else
   //      {

   //         break;

   //      }

   //   }

   //   destroyWindow();

   //}


   void Clipboard2::convertToRfbFormat(const ::scoped_string &scopedstrSource, ::string & strDst)
   {

      ::string strSrcText = scopedstrSource;

      auto length = strSrcText.length();

      auto rfbText = strDst.get_buffer(length);

      character_count j = 0;

      for (character_count i = 0; i < length; i++)
      {

         if (!(strSrcText[i] == 0x0d && strSrcText[i + 1] == 0x0a))
         {

            rfbText[j] = strSrcText[i];

            j++;

         }

      }
      
      rfbText[j] = 0;
      
      strDst.release_buffer();
      
   }


   void Clipboard2::convertFromRfbFormat(const ::scoped_string &scopedstrSource, ::string &dest)
   {
      // Count of 'LF' symbols.
      character_count lfCount = 0;
      auto sourceLen = scopedstrSource.length();
      for (character_count i = 0; i < sourceLen; i++)
      {
         if (scopedstrSource[i] == 0x0a)
         {
            lfCount++;
         }
      }

      auto destLen = sourceLen + lfCount;
      auto destText = dest.get_buffer(destLen);
      int j = 0;
      for (character_count i = 0; i < sourceLen; i++)
      {
         if (scopedstrSource[i] == 0x0a)
         {
            destText[j] = 0x0d;
            j++;
         }
         destText[j] = scopedstrSource[i];
         j++;
      }
      destText[j] = 0;

      dest.release_buffer();

   }


} // namespace subsystem_windows
 


