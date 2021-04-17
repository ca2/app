// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "aura/user/_user.h"
#include "acme/os/_user.h"


namespace windowing
{


   window::window()
   {

      m_pWindow = nullptr;

      m_pWindow2 = nullptr;

      set_oswindow(nullptr);

      //set_oswindow(oswindow);

      //m_plongmap  = new iptr_to_iptr;

//      m_iXic = 0;
//
//      m_xic = nullptr;
//
//      for (auto &i : m_iaNetWmState)
//      {
//
//         i = -1;
//
//      }
//
//      m_hcursorLast = 0;
//
//      m_htask = 0;
//
//      m_window = None;

      m_pimpl = nullptr;

      m_bMessageOnlyWindow = false;

//      m_osdisplay = nullptr;
//
//      __zero(m_visual);
//
//      m_iDepth = -1;
//
//      m_iScreen = -1;
//
//      m_colormap = None;
//
//      m_iXic = 0;

   }


   window::~window()
   {

      //::acme::del(m_plongmap);

   }


   void window::assert_valid() const
   {


   }


   void window::dump(dump_context & dumpcontext) const
   {



   }


   void window::install_message_routing(channel * pchannel)
   {


   }


   void window::message_handler(::message::message * pmessage)
   {

      m_pimpl->message_handler(pmessage);

   }


   ::e_status window::create_window(::user::interaction_impl * pimpl)
   {

      UNREFERENCED_PARAMETER(pimpl);

      __throw(error_interface_only);

      return ::error_interface_only;
      
   }


   //void * window::get_os_data() const
   //{

   //   return nullptr;

   //}


   bool window::has_mouse_capture() const
   {

      return false;

   }


   bool window::has_keyboard_focus() const
   {

      return false;

   }


   ::windowing::display * window::display()
   {

      return m_pdisplay;

   }


   ::e_status window::set_mouse_capture()
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   //::e_status window::get_capture()
   //{

   //   __throw(error_interface_only);

   //   return m_pcapture;;

   //}



   //::e_status window::set_capture()
   //{

   //   __throw(error_interface_only);

   //   return error_interface_only;

   //}


   ::e_status window::destroy_window()
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }

   
   void window::set_user_interaction(::user::interaction * pinteraction)
   {


   }

   
   void window::activate_top_parent()
   {


   }



   void window::on_visual_applied()
   {

      __throw(error_interface_only);

   }


   void window::win_update_graphics()
   {

      __throw(error_interface_only);

   }


   lresult window::send_message(const ::id & id, wparam wParam, lparam lParam)
   {

      return 0;

   }


   bool window::post_message(const ::id & id, wparam wParam, lparam lParam)
   {

      return false;

   }




   void window::set_window_text(const char * pszString)
   {

      __throw(error_interface_only);

   }


   strsize window::get_window_text(char * pszStringBuf, strsize nMaxCount)
   {

      __throw(error_interface_only);

      return 0;

   }

   void window::get_window_text(string & rectString)
   {

      __throw(error_interface_only);

   }



   strsize window::get_window_text_length()
   {

      __throw(error_interface_only);

      return 0;

   }


   void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      __throw(error_interface_only);

   }



   //bool window::window_is_iconic()
   //{
   //
   //   __throw(error_interface_only);
   //
   //   return false;
   //
   //}


   bool window::is_zoomed()
   {

      __throw(error_interface_only);

      return false;

   }


   ::u32 window::ArrangeIconicWindows()
   {

      __throw(error_interface_only);

      return 0;

   }

   void window::rects_from_os()
   {


   }


   bool window::window_rect_from_os(RECTANGLE_I32 * prectangle)
   {

      return false;

   }


   bool window::client_rect_from_os(RECTANGLE_I32 * prectangle)
   {

      return false;

   }


   void window::route_command_message(class ::message::command *)
   {

      __throw(error_interface_only);

   }


   void window::present()
   {

      __throw(error_interface_only);

   }


   void window::set_oswindow(oswindow oswindow)
   { 
      
      set_os_data(oswindow); 

      auto pimpl = m_pimpl;
   
      if (pimpl)
      {

         auto puserinteraction = pimpl->m_puserinteraction;

         if (puserinteraction)
         {

            puserinteraction->m_oswindow = oswindow;

         }

      }



   }


   void window::UpdateWindow()
   {


   }


   void window::SetRedraw(bool)
   {


   }


   bool window::GetUpdateRect(RECTANGLE_I32 * prectangle, bool bErase)
   {

      __throw(error_interface_only);

      return false;

   }


   i32 window::GetUpdateRgn(::draw2d::region * pRgn, bool bErase)
   {

      return 0;

   }


   void window::Invalidate(bool bErase)
   {


   }


   void window::InvalidateRect(const RECTANGLE_I32 * rectangle, bool bErase)
   {


   }


   void window::InvalidateRgn(::draw2d::region * pRgn, bool bErase)
   {


   }


   void window::ValidateRect(const RECTANGLE_I32 * prectangle)
   {


   }


   void window::ValidateRgn(::draw2d::region * pRgn)
   {


   }


   void window::ShowOwnedPopups(bool)
   {

   }


   bool window::LockWindowUpdate()
   {

      __throw(error_interface_only);

      return false;

   }


   void window::UnlockWindowUpdate()
   {


   }


   bool window::RedrawWindow(const ::rectangle_i32 & rectUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      __throw(error_interface_only);

      return false;

   }


   bool window::is_this_enabled()
   {

      __throw(error_interface_only);

      return false;

   }


   bool window::enable_window(bool bEnable)
   {

      __throw(error_interface_only);

      return false;

   }


   // the active interaction_impl applies only to top-level (frame windows)
   ::user::interaction * window::GetActiveWindow()
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::user::interaction * window::SetActiveWindow()
   {

      __throw(error_interface_only);

      return nullptr;

   }


   // the foreground interaction_impl applies only to top-level windows (frame windows)
   ::e_status window::set_foreground_window()
   {

      __throw(error_interface_only);

      return false;

   }


   ::user::interaction * window::get_foreground_window()
   {

      __throw(error_interface_only);

      return nullptr;

   }


   bool window::is_active_window() const
   {

      __throw(error_interface_only);

      return false;

   }



   ::user::interaction * window::get_desktop_window()
   {

      __throw(error_interface_only);

      return nullptr;

   }

   ::windowing::window * window::get_next_window(::u32 nFlag)
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::windowing::window * window::get_top_window() const 
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::windowing::window * window::get_window(::u32 nCmd) const 
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::windowing::window * window::get_last_active_popup() const 
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::windowing::window * window::get_parent() const 
   {

      __throw(error_interface_only);

      return nullptr;

   }


   oswindow window::get_parent_oswindow() const
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::e_status window::set_parent(::windowing::window * pwindowNewParent) 
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }


   ::windowing::window * window::get_owner() const
   {

      __throw(error_interface_only);

      return nullptr;

   }


   oswindow window::get_owner_oswindow() const
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::e_status window::set_owner(::windowing::window * pwindowNewOwner)
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }


   point_i32 window::GetCaretPos()
   {

      __throw(error_interface_only);

      return nullptr;

   }


   void window::SetCaretPos(const ::point_i32 & point)
   {

      __throw(error_interface_only);

   }


   void window::HideCaret() 
   {

      __throw(error_interface_only);

   }
     

   void window::ShowCaret() 
   {

      __throw(error_interface_only);

   }


   void window::DragAcceptFiles(bool bAccept)
   {

      __throw(error_interface_only);

   }


   ::e_status window::set_icon(::windowing::icon * picon)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }
    
    
   __pointer(::windowing::icon) window::get_icon() const
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::e_status window::set_cursor(::windowing::cursor * pcursor)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status window::set_tool_window(bool bSet)
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }


   void window::on_set_parent(::user::interaction * pinteraction) 
   {

      __throw(error_interface_only);

   }


   bool window::get_rect_normal(RECTANGLE_I32 * prectangle)
   {

      __throw(error_interface_only);
      
      return false;
   
   }


   void window::show_task(bool bShow)
   {

      __throw(error_interface_only);

   }


   void window::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

      __throw(error_interface_only);

   }

   
   void window::non_top_most_upper_window_rects(::rectangle_i32_array & recta)
   {

      __throw(error_interface_only);

   }


   void window::post_nc_destroy()
   {

   }


   void window::default_message_handler(::message::message * pmessage)
   {

   }


   void window::track_mouse_hover()
   {

   }


   void window::_task_transparent_mouse_event()
   {

   }


   float window::get_dpi_for_window()
   {

      return 96.0f;

   }



   float window::dpiy(float y)
   {

      float fDpi = get_dpi_for_window();

      return y * fDpi / 96.f;

   }


   float window::dpix(float x)
   {

      float fDpi = get_dpi_for_window();

      return x * fDpi / 96.f;

   }


   float window::point_dpi(float points)
   {

      float fDpi = get_dpi_for_window();

      return points * fDpi / 72.f;

   }


   float window::y_dpi(float y)
   {

      float fDpi = get_dpi_for_window();

      return y / fDpi;

   }


   float window::x_dpi(float x)
   {

      float fDpi = get_dpi_for_window();

      return x / fDpi;

   }


   void window::on_redraw_window(::u32 flags)
   {

   }


   bool window::is_child_of(const ::windowing::window * pwindowAscendantCandidate) const
   {

      return false;

   }


   ::e_status window::show_window(const ::e_display &edisplay, const ::e_activation &eactivationi)
   {

      windowing_output_debug_string("\n::window::show_window 1");

      return ::success;

   }


   ::e_status window::full_screen(const ::rectangle_i32 &rectangle)
   {

      return ::success_none;

   }


   ::e_status window::exit_iconify()
   {

      return ::success_none;

   }


   ::e_status window::exit_full_screen()
   {

      return ::success_none;

   }


   ::e_status window::exit_zoomed()
   {

      return ::success_none;

   }


   ::e_status window::set_keyboard_focus()
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }


   ::e_status window::set_active_window()
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }

   bool window::_001ClientToScreen(POINT_I32 *ppoint)
   {

      return true;

   }


   bool window::_001ScreenToClient(POINT_I32 *ppoint)
   {

      return true;

   }


   bool window::is_iconic()
   {

       return false;

   }


   bool window::is_window()
   {

      return false;

   }


   bool window::is_window_visible()
   {

      windowing_output_debug_string("\n::window::is_window_visible 1");

      return false;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      if (m_pimpl == nullptr)
      {

         return true;

      }

      if (!m_pimpl->m_puserinteraction->m_bUserPrimitiveOk)
      {

         return true;

      }

      return false;

   }

   
   bool window::on_set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   {

      return set_window_position(zorder, x, y, cx, cy, nFlags);

   }


   bool window::set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   {

      bool bOk = false;

      return bOk;

   }


   bool window::_set_window_pos(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   {

      return true;

   }


   void window::update_screen()
   {

   }


   void window::window_show()
   {

   }


} // namespace windowing



