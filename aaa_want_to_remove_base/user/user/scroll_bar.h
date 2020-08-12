#pragma once


#include "base/user/user/control.h"


namespace user
{

   class CLASS_DECL_BASE scroll_bar :
      virtual public ::user::control
   {
   public:

      e_orientation  m_eorientation;
      scroll_info    m_scrollinfo;
      bool           m_bTracking;


      scroll_bar();
      virtual ~scroll_bar();

      virtual i32 _001GetScrollPos() = 0;
      virtual i32 _001SetScrollPos(i32 iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;


      virtual bool create_window(e_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id);

      virtual void send_scroll_message(UINT nSBCode);

      virtual ::point get_parent_viewport_offset() override;
      virtual ::point get_ascendant_viewport_offset() override;
      
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

   };

} // namespace user
