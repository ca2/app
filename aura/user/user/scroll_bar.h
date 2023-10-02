#pragma once


#include "interaction.h"
#include "scroll_info.h"


namespace user
{


   class CLASS_DECL_AURA scroll_bar :
      virtual public ::user::interaction
   {
   public:


      enum_orientation                 m_eorientation;
      scroll_info                      m_scrollinfo;
      bool                             m_bTracking;
      ::size_i32                       m_sizeTrackOffset;


      scroll_bar();
      ~scroll_bar() override;


      virtual i32 _001GetScrollPos() = 0;
      virtual i32 _001SetScrollPos(i32 iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;

      
      //using ::user::interaction::create_interaction;
      //virtual bool create_interaction(enum_orientation eorientation, ::user::interaction * puiParent);

      ::point_i32 get_parent_accumulated_scroll(enum_layout elayout = e_layout_design) override;

      virtual void post_scroll_message(enum_scroll_command ecommand);

      virtual ::point_i32 get_parent_context_offset() override;
      virtual ::point_i32 get_ascendant_context_offset() override;
      
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      //virtual ::status < ::rectangle_i32 > get_track_rectangle(::draw2d::graphics_pointer & pgraphics);

      virtual ::status < ::rectangle_i32 > get_track_rectangle();


      virtual ::color::color scrollbar_color_strong(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_color(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_border_color(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_lite_border_color(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_draw_color(::user::style* pstyle, ::enum_element eelement);


      virtual ::i32 scrollbar_width();


   };


} // namespace user



