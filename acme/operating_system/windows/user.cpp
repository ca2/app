// Created by camilo on 2023-04-17 15:16 <3ThomasBorregaardSorensen!!
#include "framework.h"


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
         auto psz = (const char *)pwsz;
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


} // namespace windows



