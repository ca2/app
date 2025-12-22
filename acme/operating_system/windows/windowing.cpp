//
// Created by camilo on 2024-12-05 17:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/window.h"
#include "acme/_operating_system.h"



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



