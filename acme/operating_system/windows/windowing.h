//
// Created by camilo on 2024-12-05 17:05 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing.h"
#include "acme/_operating_system.h"


namespace windows
{



   struct os_window_handle
   {

      HWND m_hwnd;

   };

   class window;


   class CLASS_DECL_ACME windowing :
      virtual public ::acme::windowing::windowing
   {
   public:

      
      map_base < HWND, ::pointer < ::windows::window > >     m_windowmap;


      windowing();
      ~windowing() override;



   };


} // namespace windows


CLASS_DECL_ACME HWND get_task_main_hwnd(::task *ptask);
CLASS_DECL_ACME HWND get_main_hwnd();



