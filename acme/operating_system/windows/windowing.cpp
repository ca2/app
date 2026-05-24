//
// Created by camilo on 2024-12-05 17:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/window.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows/windows.h"
#include "acme/platform/user_interaction_sink.h"

BOOL CALLBACK windows_dump_child_window_hierarchy_EnumChildProc(HWND hwnd, LPARAM);


namespace windows
{


   
   windowing * g_pwindowing = nullptr;


   windowing::windowing()
   {

      if (!g_pwindowing)
      {

         g_pwindowing = this;

      }

   }


   windowing::~windowing()
   {



   }


   ::acme::windowing::window * windowing::acme_windowing_window(const ::operating_system::window & operatingsystemwindow)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto hwnd = ::as_HWND(operatingsystemwindow);

      auto pacmewindowingwindow = m_windowmap[hwnd];

      return pacmewindowingwindow;

   }


   void windowing::add_window(::acme::windowing::window *pacmewindowingwindow) 
   {

      _synchronous_lock synchronouslock(this->synchronization()); 

      auto operatingsystemwindow = pacmewindowingwindow->operating_system_window();

      auto hwnd = ::as_HWND(operatingsystemwindow);
      
      m_windowmap[hwnd] = pacmewindowingwindow;
   
   }



   
   void windowing::each_window(const ::function<void(::acme::windowing::window *)> &function)
   {

      for (auto &pair: m_windowmap)
      {

         auto pacmewindowingwindow = pair.element2();

         if (::is_set(pacmewindowingwindow))
         {

            function(pacmewindowingwindow);

         }
      }

   }


   ::operating_system::window windowing::operating_system_window(const ::wparam &wparam)
   {

      ::operating_system::windows_window windowswindow(wparam.raw_cast<HWND>());

      return windowswindow.as_operating_system_window();
   
   }


   ::operating_system::window windowing::operating_system_window(const ::lparam &lparam)
   {

      ::operating_system::windows_window windowswindow(lparam.raw_cast<HWND>());

      return windowswindow.as_operating_system_window();

   }






   void _dump_child_window_hierarchy(HWND hwnd)
   {

      OutputDebugString(L"\n=== WINDOW HIERARCHY ===\n");

      EnumChildWindows(
          hwnd,
          &::windows_dump_child_window_hierarchy_EnumChildProc,
          0);

      OutputDebugString(L"========================\n");

   }


   void dump_child_window_hierarchy(const ::operating_system::window & operatingsystemwindow)
   {

      auto hwnd = ::as_HWND(operatingsystemwindow);

      _dump_child_window_hierarchy(hwnd);

   }


} // namespace windows


HWND get_task_main_hwnd(::task * ptask)
{

   if (::is_set(ptask))
   {

      auto pacmeuserinteractionMain = ptask->m_pacmeuserinteractionMain;

      if (::is_set(pacmeuserinteractionMain))
      {

         auto pacmewindowingwindowMain = pacmeuserinteractionMain->acme_windowing_window();

         if (::is_set(pacmewindowingwindowMain))
         {

            ::windows::os_window_handle oswindowhandle{};

            pacmewindowingwindowMain->get_os_window_handle(&oswindowhandle, sizeof(oswindowhandle));

            if (oswindowhandle.m_hwnd)
            {

               return oswindowhandle.m_hwnd;
            }
         }
      }
   }

   return nullptr;

}


HWND get_main_hwnd()
{

   auto ptask = ::get_task();

   HWND hwndMain = get_task_main_hwnd(ptask);

   if (::is_set(hwndMain))
   {

      return hwndMain;

   }

   auto papplication = ::system()->application();

   if (::is_set(papplication) && papplication != ptask)
   {

      hwndMain = get_task_main_hwnd(ptask);

      if (::is_set(hwndMain))
      {

         return hwndMain;
      }
   }

   return nullptr;


}




CLASS_DECL_ACME enum_dialog_result simple_ui_message_box(
   const ::user_interaction_sink& userinteractionsink,
   const ::scoped_string& scopedstrMessage,
   const ::scoped_string& scopedstrCaption,
   const ::user::e_message_box& emessagebox)
{

   ::u32 uType = 0;
   
   uType = ::windows::message_box_to_windows_message_box(emessagebox);

   auto operatingsystemwindow = userinteractionsink.best_effort_operating_system_window();

   auto hwnd = ::as_HWND(operatingsystemwindow);

   auto iResult = ::MessageBox(hwnd, ::wstring(scopedstrMessage), ::wstring(scopedstrCaption), uType);

   auto edialogresult = ::windows::windows_message_box_result_to_dialog_result(iResult);

   return edialogresult;

}


BOOL CALLBACK windows_dump_child_window_hierarchy_EnumChildProc(HWND hwnd, LPARAM)
{
   wchar_t className[256] = {};
   wchar_t windowText[256] = {};

   GetClassName(hwnd, className, 256);
   GetWindowText(hwnd, windowText, 256);

   RECT rc;
   GetWindowRect(hwnd, &rc);

   wchar_t buffer[1024];

   swprintf_s(
       buffer,
       L"HWND=%p\nClass=%s\nText=%s\nRect=(%ld,%ld)-(%ld,%ld)\nVisible=%d\n\n",
       hwnd,
       className,
       windowText,
       rc.left,
       rc.top,
       rc.right,
       rc.bottom,
       IsWindowVisible(hwnd));

   OutputDebugString(buffer);

   ::windows::_dump_child_window_hierarchy(hwnd);

   return TRUE;
}

