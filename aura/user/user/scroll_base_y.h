// From scroll.h by camilo on 2022-08-26 <3ThomasBorregaardSorensen!!
// Renamed to scroll_base_y from scroll_base_vertical on 2023-10-22 11:41 <3ThomasBorregaardSorensen!!
#pragma once


#include "interaction.h"
#include "scroll_state.h"


namespace user
{


   class CLASS_DECL_AURA scroll_base_y :
      virtual public interaction
   {
   public:


      ::pointer<scroll_bar>         m_pscrollbarY;
      //scroll_state                  m_scrollstateaY[::user::e_layout_maximum_count];
      ::pointer<scroll_layout>      m_pscrolllayoutY;
      //scroll_design                 m_scrolldesignY;
      i16                           m_iWheelDelta;
      //i16                           m_iWheelDeltaScroll;


      scroll_base_y();
      ~scroll_base_y() override;


      virtual void sketch_to_lading_y();
      virtual void lading_to_layout_y(bool & bUpdateBuffer, bool & bUpdateWindow);
      virtual void layout_to_design_y();



      scroll_bar * get_scroll_bar_y() override;

      scroll_state get_scroll_state_y(::user::enum_layout elayout = ::user::e_layout_sketch) override;
      void set_scroll_state_y(const scroll_state & scrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch) override;


      virtual void send_scroll_y_message(enum_scroll_command ecommand, ::f64 dPosition = F64_MOST_NEGATIVE);

      void install_message_routing(::channel * pchannel) override;

      virtual void on_change_scroll_state(::user::enum_layout elayout = ::user::e_layout_sketch) override;
      //virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual i32 get_wheel_scroll_delta() override;
      virtual bool create_scroll_bar_y();
      //virtual void layout_scroll_bar_x(::draw2d::graphics_pointer & pgraphics) override;
      virtual void layout_scroll_bar_y(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void defer_create_scroll_bar_y(::user::enum_layout elayout = ::user::e_layout_sketch);
      //virtual void on_create_scroll_bar_y();
      void set_scroll_tracking_y(::f64 y, ::user::enum_layout = ::user::e_layout_sketch) override;
      ::f64 get_context_offset_y(::user::enum_layout elayout) override;
      void set_context_offset_y(::f64 x, ::user::enum_layout = ::user::e_layout_sketch) override;
      virtual void constrain_context_offset_y(::f64 & y, ::user::enum_layout elayout = ::user::e_layout_sketch);


      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_wheel);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);


      virtual void scroll_up_line();
      virtual void scroll_down_line();
      virtual void scroll_up_page();
      virtual void scroll_down_page();
      virtual void scroll_y(int nPos);

      virtual int get_final_scroll_bar_y_thickness(::user::enum_layout elayout = ::user::e_layout_sketch) override;


   };




} // namespace user




