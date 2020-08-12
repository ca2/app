#include "framework.h"


namespace user
{


   frame::frame()
   {
      
      m_bDefaultNotifyIcon = false;
      m_bCloseApplicationIfLastVisibleFrame = true;
      m_pframe = this;

   }


   frame::~frame()
   {

   }


   style * frame::_get_style() const
   {

      return m_puserstyle;

   }


   ::color frame::get_border_main_body_color()
   {

      return 0;

   }


   void frame::set_frame_title(const string& strFrameTitle)
   {

      m_strFrameTitle = strFrameTitle;

      auto pparent = get_parent();

      if (pparent && pparent->is < ::user::place_holder >())
      {

         set_place_child_title(m_strFrameTitle);

      }

   }


   string frame::get_frame_title() const
   {

      return m_strFrameTitle;

   }


   ::userex::font_format_tool * frame::font_format_tool(bool bCreate)
   {

      return nullptr;

   }


   bool frame::is_frame_window()
   {

      return true;

   }


   void frame::InitialFramePosition(bool bForceRestore)
   {


   }


   size frame::get_window_minimum_size()
   {

      if (m_sizeMinimum.area() > 0)
      {

         return m_sizeMinimum;

      }
      else if (display_state() == ::display_minimal)
      {

         return ::size(8, 8);

      }
      else
      {

         return Session.get_window_minimum_size();

      }

   }
   

} // namespace user



