#pragma once


#include "interaction.h"
#include "scroll_state.h"


namespace user
{


   class CLASS_DECL_AURA scroll_bar :
      virtual public ::user::interaction
   {
   public:


      enum_orientation                    m_eorientation;
      //scroll_state                      m_scrollstatea[::user::e_layout_maximum_count];
      ::pointer < scroll_layout >         m_pscrolllayout;
      bool                                m_bTracking;
      ::size_i32                          m_sizeTrackOffset;
      ::pointer < ::user::interaction >   m_puserinteractionScrollBase;


      scroll_bar();
      ~scroll_bar() override;


      //virtual int _001GetScrollPos() = 0;
      //virtual int _001SetScrollPos(int iPos) = 0;
      //virtual bool _001GetScrollState(scroll_state * pscrollstate) = 0;
      //virtual bool _001SetScrollState(scroll_state * pscrollstate, bool bRedraw = true) = 0;

      
      //using ::user::interaction::create_interaction;
      //virtual bool create_interaction(enum_orientation eorientation, ::user::interaction * puiParent);

      ::point_f64 get_parent_accumulated_scroll(enum_layout elayout = e_layout_design) override;

      virtual void post_scroll_message(enum_scroll_command ecommand, double dPosition = F64_MOST_NEGATIVE);

      virtual ::point_f64 get_parent_context_offset() override;
      virtual ::point_f64 get_ascendant_context_offset() override;
      
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      //virtual ::status < ::rectangle_i32 > get_track_rectangle(::draw2d::graphics_pointer & pgraphics);

      
      virtual ::status < ::rectangle_f64 > get_track_rectangle(::user::enum_layout elayout);


      virtual ::color::color scrollbar_color_strong(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_color(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_border_color(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_lite_border_color(::user::style* pstyle, ::enum_element eelement);
      virtual ::color::color scrollbar_draw_color(::user::style* pstyle, ::enum_element eelement);


      virtual double scroll_bar_thickness(::user::enum_layout elayout = ::user::e_layout_design);


   };


} // namespace user



