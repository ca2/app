// From scroll.h by camilo on 2022-08-26 <3ThomasBorregaardSorensen!!
// Renamed to scroll_base_x from scroll_base_x on 2023-10-22 11:42 <3ThomasBorregaardSorensen!!
#pragma once


#include "interaction.h"
#include "scroll_state.h"
//#include "scroll_design.h"


namespace user
{


   class CLASS_DECL_AURA scroll_base_x :
      virtual public interaction
   {
   public:


      ::pointer<scroll_bar>      m_pscrollbarX;
      ::pointer<scroll_layout>   m_pscrolllayoutX;
      //scroll_state               m_scrollstateaX[::user::e_layout_maximum_count];
      //scroll_design              m_scrolldesignX;


      scroll_base_x();
      ~scroll_base_x() override;


      void destroy() override;


      virtual void sketch_to_lading_x();
      virtual void lading_to_layout_x(bool & bUpdateBuffer, bool & bUpdateWindow);
      virtual void layout_to_design_x();


      

      scroll_bar* get_scroll_bar_x() override;
      
      scroll_state get_scroll_state_x(::user::enum_layout elayout = ::user::e_layout_sketch) override;
      void set_scroll_state_x(const scroll_state & scrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void send_scroll_x_message(enum_scroll_command ecommand, ::f64 dPosition = F64_MOST_NEGATIVE);

      //virtual void GetScrollRect(::rectangle_i32 * prectangle);

      void on_change_scroll_state(::user::enum_layout elayout = ::user::e_layout_sketch) override;
      //virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool create_scroll_bar_x();
      //void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void layout_scroll_bar_x(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void defer_create_scroll_bar_x(::user::enum_layout elayout = ::user::e_layout_sketch);
      //virtual void on_create_scroll_bar_x();
      void set_scroll_tracking_x(::f64 x, ::user::enum_layout = ::user::e_layout_sketch) override;
      ::f64 get_context_offset_x(::user::enum_layout = ::user::e_layout_sketch) override;
      void set_context_offset_x(::f64 x, ::user::enum_layout = ::user::e_layout_sketch) override;
      virtual void constrain_context_offset_x(::f64 & x, ::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void scroll_left_line();
      virtual void scroll_right_line();
      virtual void scroll_left_page();
      virtual void scroll_right_page();
      virtual void scroll_x(int nPos);


      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);

      virtual int get_final_scroll_bar_x_thickness(::user::enum_layout elayout = ::user::e_layout_sketch) override;

   };



} // namespace user




