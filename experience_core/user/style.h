#pragma once


#include "base/user/user/style.h"


namespace experience_core
{


   class CLASS_DECL_APP_EXPERIENCE_CORE style:
      virtual public ::base::style
   {
   public:



      style();
      ~style() override;

      
      void on_initialize_particle() override;


      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate) override;
      bool _001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab) override;

      ::color::color get_color(::user::interaction * pinteraction, ::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) override;

      bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;



   };


} // namespace experience_core



