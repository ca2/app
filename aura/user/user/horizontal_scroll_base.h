// From scroll.h by camilo on 2022-08-26 <3ThomasBorregaardSorensen!!
#pragma once


#include "interaction.h"


namespace user
{


   class CLASS_DECL_AURA horizontal_scroll_base :
      virtual public interaction
   {
   public:


      ::pointer<scroll_bar>     m_pscrollbarHorizontal;
      ::pointer<scroll_data>    m_pscrolldataHorizontal;


      horizontal_scroll_base();
      ~horizontal_scroll_base() override;


      virtual scroll_bar* get_horizontal_scroll_bar() override;

      virtual scroll_data* get_horizontal_scroll_data() override;

      void install_message_routing(::channel * pchannel) override;

      virtual void send_xscroll_message(enum_scroll_command ecommand);

      //virtual void GetScrollRect(RECTANGLE_I32 * prectangle);

      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool create_horizontal_scroll_bar();
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void defer_create_horizontal_scroll_bar();
      //virtual void on_create_horizontal_scroll_bar();
      virtual bool validate_context_offset(point_i32 & point) override;
      virtual void scroll_left_line();
      virtual void scroll_right_line();
      virtual void scroll_left_page();
      virtual void scroll_right_page();
      virtual void scroll_horz(int nPos);


      DECLARE_MESSAGE_HANDLER(_001OnHScroll);

      virtual int get_final_x_scroll_bar_width() override;

   };



} // namespace user




