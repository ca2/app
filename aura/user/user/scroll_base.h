#pragma once


#include "horizontal_scroll_base.h"
#include "vertical_scroll_base.h"


namespace user
{


   class CLASS_DECL_AURA scroll_base :
      virtual public ::user::horizontal_scroll_base,
      virtual public ::user::vertical_scroll_base
   {
   public:


      ::size_f64            m_sizeTotal;


      scroll_base();
      ~scroll_base() override;


      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool validate_context_offset(point_i32 & point) override;
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;


      void install_message_routing(::channel * pchannel) override;


      virtual bool GetActiveClientRect(RECTANGLE_I32  & rectangle);


      virtual bool GetFocusRect(RECTANGLE_I32 & rectangle) override;


      virtual ::size_f64 get_total_size() override;


      virtual void set_total_size(const ::size_f64& size) override;
      virtual void set_page_size(const ::size_f64& size) override;


      virtual void defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user




