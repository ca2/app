//
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/geometry2d/size.h"
#include "acme/nano/user/window_implementation.h"


namespace windowing
{


   class CLASS_DECL_ACME window_base :
      virtual public ::nano::user::window_implementation
   {
   public:


      ::point_i32                               m_pointWindow;
      ::size_i32                                m_sizeWindow;
      ::point_i32                               m_pointCursor2;



      window_base();
      ~window_base() override;


      virtual bool is_windowing_popup();
      virtual ::point_i32 windowing_popup_origin();
      virtual ::size_i32 windowing_popup_size();
      virtual void _on_windowing_close_window();
      virtual bool is_satellite_window();
      virtual window_base * owner_window();
      virtual ::string get_window_text();


      ::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true) override;

      bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

      bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;



   };


} // namespace windowing