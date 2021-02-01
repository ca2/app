#pragma once


namespace user
{


   class CLASS_DECL_AURA scroll_bar :
      virtual public ::user::interaction
   {
   public:


      e_orientation                    m_eorientation;
      scroll_info                      m_scrollinfo;
      bool                             m_bTracking;
      ::size_i32                           m_sizeTrackOffset;


      scroll_bar();
      virtual ~scroll_bar();

      virtual i32 _001GetScrollPos() = 0;
      virtual i32 _001SetScrollPos(i32 iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;

      
      //using ::user::interaction::create_interaction;
      //virtual bool create_interaction(e_orientation eorientation, ::user::interaction * puiParent);


      virtual void post_scroll_message(::u32 nSBCode);

      virtual ::point_i32 get_parent_viewport_offset() const override;
      virtual ::point_i32 get_ascendant_viewport_offset() const override;
      
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool GetTrackRect(RECTANGLE_I32* prectangle, ::draw2d::graphics_pointer & pgraphics);


      virtual ::color scrollbar_color_strong(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_color(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_border_color(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_lite_border_color(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_draw_color(::user::style* pstyle, ::user::enum_element eelement);

   };


} // namespace user



