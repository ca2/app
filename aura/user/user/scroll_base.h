#pragma once


#include "scroll_base_x.h"
#include "scroll_base_y.h"


namespace user
{


   class CLASS_DECL_AURA scroll_base :
      virtual public ::user::scroll_base_x,
      virtual public ::user::scroll_base_y
   {
   public:


      bool                                      m_bUsesDraggingScrolling;
      //::double_size            m_sizeaTotal[::user::e_layout_maximum_count];


      scroll_base();
      ~scroll_base() override; void destroy() override;


      void on_initialize_particle() override;

      void install_message_routing(::channel * pchannel) override;

      void defer_setup_default_client_area_user_item() override;

      DECLARE_MESSAGE_HANDLER(on_message_create);


      bool on_drag_start(::int_point & pointStart, ::user::mouse * pmouse, ::item * pitem) override;
      bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;

      void sketch_to_lading() override;
      void lading_to_layout(bool & bUpdateBuffer, bool & bUpdateWindow) override;
      void layout_to_design() override;

      //virtual bool on_drag_shift_element_client(::item * pitem, ::user::mouse * pmouse);

      void on_change_scroll_state(::user::enum_layout elayout = ::user::e_layout_sketch) override;
      ::double_point get_context_offset(::user::enum_layout elayout = ::user::e_layout_design) override;
      //void on_change_context_offset(::draw2d::graphics_pointer & pgraphics) override;
      void constrain_context_offset(double_point & point, ::user::enum_layout elayout = ::user::e_layout_sketch) override;
      //void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      void layout_scroll_bar(::user::enum_layout elayout = ::user::e_layout_sketch) override;


      //void install_message_routing(::channel * pchannel) override;
      void set_context_offset(const ::double_point & pointOffset, ::user::enum_layout elayout = ::user::e_layout_sketch) override;

      virtual ::int_rectangle client2_rectangle(enum_layout elayout = e_layout_design) override;


      bool GetFocusRect(::int_rectangle & rectangle) override;


      ::double_size get_total_size(::user::enum_layout elayout = ::user::e_layout_sketch) override;


      void set_total_size(const ::double_size& size, ::user::enum_layout = ::user::e_layout_sketch) override;
      void set_page_size(const ::double_size& size, ::user::enum_layout = ::user::e_layout_sketch) override;


      virtual void defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics);


      bool scroll_bar_x_visible(enum_layout elayout = e_layout_design) override;
      bool scroll_bar_y_visible(enum_layout elayout = e_layout_design) override;


      bool get_element_rectangle(::int_rectangle & rectangle, enum_element eelement) override;

      ::int_point drag_point(::item * pitem, ::user::mouse * pmouse) override;

   };


} // namespace user




