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
      ::size                           m_sizeTrackOffset;


      scroll_bar();
      virtual ~scroll_bar();

      virtual i32 _001GetScrollPos() = 0;
      virtual i32 _001SetScrollPos(i32 iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;


      virtual bool create_window(e_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id);

      virtual void send_scroll_message(::u32 nSBCode);

      virtual ::point get_parent_viewport_offset() const override;
      virtual ::point get_ascendant_viewport_offset() const override;
      
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool GetTrackRect(RECT32* prect, ::draw2d::graphics_pointer & pgraphics);


      virtual ::color scrollbar_color_strong(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_color(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_border_color(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_lite_border_color(::user::style* pstyle, ::user::enum_element eelement);
      virtual ::color scrollbar_draw_color(::user::style* pstyle, ::user::enum_element eelement);

   };


} // namespace user



