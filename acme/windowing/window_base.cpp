//
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window_base.h"


namespace windowing
{


   window_base::window_base() :
      m_pointCursor2(I32_MINIMUM)
   {


   }


   window_base::~window_base()
   {


   }


   bool window_base::is_windowing_popup()
   {

      return false;

   }


   ::point_i32 window_base::windowing_popup_origin()
   {

      return {};

   }


   ::size_i32 window_base::windowing_popup_size()
   {

      return {};

   }


   void window_base::_on_windowing_close_window()
   {


   }


   bool window_base::is_satellite_window()
   {

      return false;

   }


   window_base * window_base::owner_window()
   {

      return nullptr;

   }


   ::string window_base::get_window_text()
   {

      return {};

   }


   ::pointer < ::operating_system::a_system_menu > window_base::create_system_menu(bool bContextual)
   {

      return ::nano::user::window_implementation::create_system_menu(bContextual);

   }


   bool window_base::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

      return false;

   }


   bool window_base::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      return false;

   }



} // namespace windowing




