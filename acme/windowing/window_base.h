//
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/geometry2d/size.h"


namespace windowing
{


   class CLASS_DECL_ACME window_base :
      virtual public ::particle
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


   };


} // namespace windowing