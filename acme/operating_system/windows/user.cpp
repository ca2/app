// Created by camilo on 2023-04-17 15:16 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/constant/user_key.h"

#include "acme/_operating_system.h"


namespace windows
{

   ::string get_window_text_timeout(HWND hwnd, const class time & timeSendMessageMax)
   {

      DWORD_PTR dw = 0;

      //if (!SendMessageTimeoutW(hwnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 100, &dw))
      if (!SendMessageTimeoutW(hwnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, ::windows::wait(timeSendMessageMax), &dw))
      {

         return "";

      }

      if (!dw)
      {

         return "";

      }

      wstring wstr;

      auto pwsz = wstr.get_buffer(dw);

      if (!SendMessageTimeoutW(hwnd, WM_GETTEXT, dw + 1, (LPARAM)pwsz, SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, ::windows::wait(timeSendMessageMax), &dw))
      {

         return "";

      }

      if (dw > wcslen(pwsz))
      {
         ::string str;
         auto psz = (const_char_pointer )pwsz;
         str = psz;
         wstr.release_buffer();
         wstr = str;

      }

      wstr.release_buffer();

      return wstr;

   }

   
   HWND child_at(HWND hwnd, iptr i)
   {

      auto hwndChild = ::GetWindow(hwnd, GW_CHILD);

      while (i > 0)
      {

         hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);

         i--;

      }

      return hwndChild;

   }


   ::user::enum_key virtual_key_code_to_user_key(int iVirtualKey)
   {

      char ch;

      ch = (char)iVirtualKey;

      if (ch >= '0' && ch <= '9')
      {

         return (::user::enum_key)(::user::e_key_0 + (ch - '0'));

      }

      if (ch >= 'A' && ch <= 'Z')
      {

         return (::user::enum_key) (::user::e_key_a + (ch - 'A'));

      }

      if (ch == ' ')
      {

         return ::user::e_key_space;

      }

      switch (iVirtualKey)
      {
         case VK_LEFT:
            return ::user::e_key_left;
         case VK_RIGHT:
            return ::user::e_key_right;
         case VK_UP:
            return ::user::e_key_up;
         case VK_DOWN:
            return ::user::e_key_down;
         case VK_TAB:
            return ::user::e_key_tab;
         case VK_RETURN:
            return ::user::e_key_return;
         case VK_LSHIFT:
            return ::user::e_key_left_shift;
         case VK_RSHIFT:
            return ::user::e_key_right_shift;
         case VK_LCONTROL:
            return ::user::e_key_left_control;
         case VK_RCONTROL:
            return  ::user::e_key_right_control;
         case VK_LMENU:
            return ::user::e_key_left_alt;
         case VK_RMENU:
            return ::user::e_key_right_alt;
         case VK_LWIN:
            return ::user::e_key_left_command;
         case VK_RWIN:
            return ::user::e_key_right_command;
         case VK_BACK:
            return ::user::e_key_back;
         case VK_DELETE:
            return ::user::e_key_delete;
         case VK_HOME:
            return ::user::e_key_home;
         case VK_END:
            return ::user::e_key_end;
         case VK_PRIOR:
            return ::user::e_key_page_up;
         case VK_NEXT:
            return ::user::e_key_page_down;
      }

      return ::user::e_key_none;

   }


    CLASS_DECL_ACME TCHAR * get_system_cursor(enum_cursor ecursor)
    {

       switch (ecursor)
       {
       case e_cursor_arrow:
          return IDC_ARROW;
       case e_cursor_text_select:
          return IDC_IBEAM;
       case e_cursor_hand:
          return IDC_HAND;
       case e_cursor_move:
          return IDC_SIZEALL;
       case e_cursor_size_bottom_right:
          return IDC_SIZENWSE;
       case e_cursor_size_top_left:
          return IDC_SIZENWSE;
       case e_cursor_size_bottom_left:
          return IDC_SIZENESW;
       case e_cursor_size_top_right:
          return IDC_SIZENESW;
       case e_cursor_size_left:
          return IDC_SIZEWE;
       case e_cursor_size_right:
          return IDC_SIZEWE;
       case e_cursor_size_top:
          return IDC_SIZENS;
       case e_cursor_size_bottom:
          return IDC_SIZENS;
       case e_cursor_wait:
          return IDC_WAIT;
       case e_cursor_wait_arrow:
          return IDC_WAIT;
       default:
          return IDC_ARROW;
       }

    }


} // namespace windows








static HWND s_hwndMain = nullptr;

CLASS_DECL_ACME void acme_set_main_hwnd(HWND hwnd)
{

   s_hwndMain = hwnd;

}


CLASS_DECL_ACME HWND acme_get_main_hwnd()
{

   return s_hwndMain;

}