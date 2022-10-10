// From scroll.h by camilo on 2022-08-26 <3ThomasBorregaardSorensen!!
#pragma once


#include "interaction.h"


namespace user
{


   class CLASS_DECL_AURA vertical_scroll_base :
      virtual public interaction
   {
   public:


      ::pointer<scroll_bar>        m_pscrollbarVertical;
      ::pointer<scroll_data>       m_pscrolldataVertical;
      i16                           m_iWheelDelta;
      i16                           m_iWheelDeltaScroll;


      vertical_scroll_base();
      ~vertical_scroll_base() override;


      virtual scroll_bar* get_vertical_scroll_bar() override;
      virtual scroll_data* get_vertical_scroll_data() override;


      virtual void send_yscroll_message(enum_scroll_command ecommand);

      void install_message_routing(::channel * pchannel) override;

      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual i32 get_wheel_scroll_delta() override;
      virtual bool create_vertical_scroll_bar();
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void defer_create_vertical_scroll_bar();
      //virtual void on_create_vertical_scroll_bar();
      virtual bool validate_context_offset(point_i32 & point) override;


      DECLARE_MESSAGE_HANDLER(on_message_vertical_scroll);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_wheel);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);


      virtual int get_final_y_scroll_bar_width() override;

      virtual void scroll_up_line();
      virtual void scroll_down_line();
      virtual void scroll_up_page();
      virtual void scroll_down_page();
      virtual void scroll_vert(int nPos);


   };




} // namespace user




