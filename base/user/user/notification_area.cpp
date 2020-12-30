/*
Copyright(C) Nishant Sivakumar.
URLs - http://blog.voidnish.com and http://www.voidnish.com
Contact : nish@voidnish.com
*/
// ShellTrayInfoView.cpp : implementation of the notification_area class
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "acme/os/windows/process_data.h"


namespace user
{

   // notification_area

   notification_area::notification_area()
#ifdef WINDOWS_DESKTOP
   :
      m_hfontHidden(nullptr),
      m_hfontRegular(nullptr)
#endif
   {
      // TODO: add construction code here

   }

   notification_area::~notification_area()
   {
#ifdef WINDOWS_DESKTOP
      ::DeleteObject(m_hfontHidden);
      ::DeleteObject(m_hfontRegular);
#else
//      __throw(todo());
#endif
   }

   void notification_area::Initialize(::layered * pobjectContext)
   {

#ifdef WINDOWS_DESKTOP

      LOGFONTW lf = {0};
      wcscpy(lf.lfFaceName, wstring(os_font_name(e_font_sans)));

      lf.lfHeight = 16;
      m_hfontRegular = CreateFontIndirectW(&lf);

      lf.lfItalic = TRUE;
      m_hfontHidden = CreateFontIndirectW(&lf);

      m_oswindowTray = FindTrayToolbarWindow();

      m_pil16 = __new(image_list);

      m_pil16->create(16,16,ILC_COLOR24,16,16);

#endif

      ListTrayIcons();

   }

   void notification_area::ListTrayIcons(i32 defindex /*= 0*/)
   {
#ifdef WINDOWS_DESKTOP
      UNREFERENCED_PARAMETER(defindex);
      m_infoa.remove_all();

      m_pil16->remove_all();

      if(m_oswindowTray == nullptr)
      {
         m_oswindowTray = FindTrayToolbarWindow();
         if(m_oswindowTray == nullptr)
         {
            return;
         }
      }

      DWORD dwTrayPid = 0;

      if (!GetWindowThreadProcessId(m_oswindowTray, &dwTrayPid))
      {

         return;

      }

      if(dwTrayPid == 0)
         return;

      i32 count = (i32)::SendMessage(m_oswindowTray, TB_BUTTONCOUNT, 0, 0);

      process_data<TBBUTTON> data(dwTrayPid);
      TBBUTTON tb = {0};
      TRAYDATA tray = {0};
      TrayItemInfo info;

      for(i32 i=0; i<count; i++)
      {
         ::SendMessage(m_oswindowTray, TB_GETBUTTON, i, (LPARAM)data.get_data());
         data.ReadData(&tb);
         data.ReadData<TRAYDATA>(&tray,(const void *)tb.dwData);

         DWORD dwProcessId = 0;

         GetWindowThreadProcessId(tray.m_oswindow,&dwProcessId);

         info.sProcessPath = module_path_from_pid(dwProcessId);

         unichar TipChar;
         unichar sTip[1024] = {0};
         unichar* pTip = (unichar*)tb.iString;

         if(!(tb.fsState & TBSTATE_HIDDEN))
         {
            i32 x = 0;
            do
            {
               if(x == 1023)
               {
                  wcscpy(sTip,L"[ToolTip was either too long or not set]");
                  break;
               }
               data.ReadData<unichar>(&TipChar, (const void *)pTip++);
            }
            while(sTip[x++] = TipChar);
         }
         else
            wcscpy(sTip,L"[Hidden icon]");

         info.sTip = ::str::international::unicode_to_utf8(sTip);

         info.m_oswindow = tray.m_oswindow;
         info.uCallbackMessage = tray.uCallbackMessage;
         info.uID = tray.uID;

         info.bVisible = !(tb.fsState & TBSTATE_HIDDEN);

         i32 iconindex = 0;
         ICONINFO  iinfo;
         if(GetIconInfo(tray.hIcon,&iinfo) != 0)
         {
            iconindex = m_pil16->add_icon_os_data(tray.hIcon);
         }
         ::DestroyIcon(tray.hIcon);
         ::DeleteObject(iinfo.hbmColor);
         ::DeleteObject(iinfo.hbmMask);

         //LVITEM lv = {0};
         //lv.iItem = GetListCtrl().get_item_count();
         //lv.iSubItem = 0;
         //lv.mask = LVIF_IMAGE;
         //lv.iImage = iconindex;

         m_infoa.add(new TrayItemInfo(info));
         //i32 index = GetListCtrl().InsertItem(&lv);
         //GetListCtrl().set_item_text(index,1,info.sTip);
         //GetListCtrl().set_item_text(index,2,info.sProcessPath);
      }

      //if( (count>0) && (defindex>=0) && (defindex<count) )
      //   GetListCtrl().SetItemState(defindex,
      //      LVIS_FOCUSED|LVIS_SELECTED,
      //      LVIS_FOCUSED|LVIS_SELECTED);
#else
      __throw(todo());
#endif
   }

   void notification_area::EditCopy(i32 iItem)
   {
      UNREFERENCED_PARAMETER(iItem);
      /*   POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
         if(pos)
         {
            i32 index = GetListCtrl().GetNextSelectedItem(pos);
            OpenClipboard();
            EmptyClipboard();
            HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE, sizeof char * 512);
            char * pStr = (char *)GlobalLock(hText);
            _stprintf(pStr, "Tray Tip : %s\r\nOwner : %s",
               m_infoa[index].sTip, m_infoa[index].sProcessPath);
            GlobalUnlock(hText);
            SetClipboardData(CF_TEXT, hText);
            CloseClipboard();
         }*/
   }

   void notification_area::DoubleClick(i32 iItem)
   {
      PostMessageToTrayIcon(iItem, e_message_left_button_double_click);
   }

   void notification_area::LeftClick(i32 iItem)
   {
      PostMessageToTrayIcon(iItem, e_message_left_button_down);
      PostMessageToTrayIcon(iItem, e_message_left_button_up);
   }

   void notification_area::RightClick(i32 iItem)
   {
      PostMessageToTrayIcon(iItem, e_message_right_button_down);
      PostMessageToTrayIcon(iItem, e_message_right_button_up);
   }

   void notification_area::PostMessageToTrayIcon(i32 iItem, LPARAM lParam)
   {
#ifdef WINDOWS_DESKTOP
      ::PostMessage(m_infoa[iItem]->m_oswindow, m_infoa[iItem]->uCallbackMessage, m_infoa[iItem]->uID, lParam);
#endif
   }

   void notification_area::MoveLeft(i32 iItem)
   {
#ifdef WINDOWS_DESKTOP
      if(iItem > 0)
      {
         ::SendMessage(m_oswindowTray, TB_MOVEBUTTON, iItem, iItem-1);
         ListTrayIcons(iItem - 1);
      }
#else
      __throw(todo());
#endif
   }

   void notification_area::MoveRight(i32 iItem)
   {
#ifdef WINDOWS_DESKTOP
      if(iItem < (m_infoa.get_size() - 1))
      {
         ::SendMessage(m_oswindowTray, TB_MOVEBUTTON, iItem, iItem+1);
         ListTrayIcons(iItem + 1);
      }
#else
      __throw(todo());
#endif
   }


   void notification_area::Refresh()
   {
      ListTrayIcons();
   }

   /*
      Copyright(C) Nishant Sivakumar.
      URLs - http://blog.voidnish.com and http://www.voidnish.com
      Contact : nish@voidnish.com
   */



   oswindow FindTrayToolbarWindow()
   {
      oswindow oswindow = nullptr;
#ifdef WINDOWS_DESKTOP
      oswindow = ::FindWindowW(L"Shell_TrayWnd", nullptr);
      if(oswindow != nullptr)
      {
         oswindow = ::FindWindowExW(oswindow,nullptr,L"TrayNotifyWnd", nullptr);
         if(oswindow != nullptr)
         {
            oswindow = ::FindWindowExW(oswindow,nullptr,L"SysPager", nullptr);
            if(oswindow != nullptr)
            {
               oswindow = ::FindWindowExW(oswindow, nullptr,L"ToolbarWindow32", nullptr);
            }
         }
      }
#endif
      return oswindow;
   }


} // namespace user
