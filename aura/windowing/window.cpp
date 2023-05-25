// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/platform/system.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/icon.h"
#include "aura/user/user/user.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/copydesk.h"
#include "aura/user/user/interaction.h"


namespace windowing
{


   window::window()
   {

      m_psandboxwindowingwindow = nullptr;

      m_pWindow4 = nullptr;

      set_oswindow(nullptr);

      m_bMessageOnlyWindow = false;

   }


   window::~window()
   {

   }


   void window::on_initialize_particle()
   {

      ::channel::on_initialize_particle();

      auto psession = get_session();

      auto puser = psession->user();

      puser->on_initialize_window_object();

   }


//   void window::assert_ok() const
//   {
//
//
//   }
//
//
//   void window::dump(dump_context & dumpcontext) const
//   {
//
//
//   }


   void window::install_message_routing(channel * pchannel)
   {


   }


   void window::message_handler(::message::message * pmessage)
   {
      
      if(pmessage->m_atom == e_message_post_user)
      {

         auto pparticle = pmessage->m_union.m_pparticle;

         ::pointer<::message::message>pmessagePost = pparticle->m_pparticle;

         if (::is_null(pmessagePost))
         {

            return;

         }

         if(pmessagePost->m_atom==e_message_vscroll)
         {

            ::output_debug_string("vscroll");

         }
         else if(pmessagePost->m_atom == e_message_text_composition)
         {

            ::output_debug_string("message text composition");

         }

         m_puserinteractionimpl->message_handler(pmessagePost);

         return;

      }

      m_puserinteractionimpl->message_handler(pmessage);

   }


   void window::create_window(::user::interaction_impl * puserinteractionimpl)
   {

      __UNREFERENCED_PARAMETER(puserinteractionimpl);

      throw ::interface_only();
      
   }


   void window::set_cursor_position(const ::point_i32 & pointCursor)
   {

      m_pointCursor = pointCursor;

   }


   void window::get_cursor_position(::point_i32 * ppointCursor)
   {

      *ppointCursor = m_pointCursor;

   }


   //bool window::defer_set_icon()
   //{

   //   return false;

   //}


   double window::get_top_margin()
   {
      
      return 0.;
      
   }
   

   bool window::has_mouse_capture() const
   {

      return false;

   }


   bool window::has_keyboard_focus() const
   {

      return false;

   }

   
   ::color::color window::screen_pixel(int x, int y) const
   {

      return m_puserinteractionimpl->screen_pixel(x, y);

   }


   bool window::is_full_screen() const
   {

      return false;

   }


   ::windowing::display * window::display()
   {

      return m_pdisplay;

   }


   ::user::copydesk * window::copydesk()
   {

      if (!m_pcopydesk)
      {

         __raw_construct(m_pcopydesk);

         if (m_pcopydesk)
         {
            
            m_pcopydesk->initialize_copydesk(this);

         }

      }

      return m_pcopydesk;

   }


   void window::set_mouse_capture()
   {

      throw ::interface_only();

   }


   void window::destroy_window()
   {

      throw ::interface_only();

   }


   void window::on_destroy()
   {

      try
      {

         if (m_pcopydesk.is_set())
         {

            m_pcopydesk->destroy();

            m_pcopydesk.release();

         }

      }
      catch (...)
      {

      }

   }

   
   void window::set_user_interaction(::user::interaction * pinteraction)
   {


   }

   
   void window::activate_top_parent()
   {


   }


   void window::on_visual_applied()
   {

      throw ::interface_only();

   }


   void window::win_update_graphics()
   {

      throw ::interface_only();

   }


   lresult window::send_message(const ::atom & atom, wparam wParam, lparam lParam)
   {

      return 0;

   }


   bool window::post_message(const ::atom & atom, wparam wParam, lparam lParam)
   {

      return false;

   }


   void window::set_window_text(const ::scoped_string & scopedstr)
   {

      throw ::interface_only();

   }


   ::string window::get_window_text()
   {

      return {};

   }


//   strsize window::get_window_text(char * pszStringBuf, strsize nMaxCount)
//   {
//
//      throw ::interface_only();
//
//      return 0;
//
//   }
//
//
//   void window::get_window_text(string & rectangleString)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   strsize window::get_window_text_length()
//   {
//
//      throw ::interface_only();
//
//      return 0;
//
//   }


   void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      throw ::interface_only();

   }


   bool window::is_zoomed()
   {

      throw ::interface_only();

      return false;

   }


   ::u32 window::ArrangeIconicWindows()
   {

      throw ::interface_only();

      return 0;

   }


   void window::rects_from_os()
   {


   }


   bool window::window_rect_from_os(::rectangle_i32 * prectangle)
   {

      return false;

   }


   bool window::client_rect_from_os(::rectangle_i32 * prectangle)
   {

      return false;

   }


   void window::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      throw ::interface_only();

   }


   void window::present()
   {

      throw ::interface_only();

   }


   void window::set_oswindow(::oswindow oswindow)
   { 

      m_oswindow = oswindow;

      auto puserinteractionimpl = m_puserinteractionimpl;
   
      if (puserinteractionimpl)
      {

         auto puserinteraction = puserinteractionimpl->m_puserinteraction;

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


   bool window::GetUpdateRect(::rectangle_i32 * prectangle, bool bErase)
   {

      throw ::interface_only();

      return false;

   }


   i32 window::GetUpdateRgn(::draw2d::region * pRgn, bool bErase)
   {

      return 0;

   }


   void window::Invalidate(bool bErase)
   {


   }


   void window::InvalidateRect(const ::rectangle_i32 * rectangle, bool bErase)
   {


   }


   void window::InvalidateRgn(::draw2d::region * pRgn, bool bErase)
   {


   }


   void window::ValidateRect(const ::rectangle_i32 * prectangle)
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

      throw ::interface_only();

      return false;

   }


   void window::UnlockWindowUpdate()
   {


   }


   bool window::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      throw ::interface_only();

      return false;

   }


   bool window::is_this_enabled()
   {

      throw ::interface_only();

      return false;

   }


   bool window::enable_window(bool bEnable)
   {

      throw ::interface_only();

      return false;

   }


   // the active interaction_impl applies only to top-level (frame windows)
   ::user::interaction * window::GetActiveWindow()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * window::SetActiveWindow()
   {

      throw ::interface_only();

      return nullptr;

   }


   // the foreground interaction_impl applies only to top-level windows (frame windows)
   void window::set_foreground_window()
   {

      throw ::interface_only();

   }


   ::user::interaction * window::get_foreground_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   bool window::is_active_window() const
   {

      if(m_pwindowing->get_active_window(m_puserinteractionimpl->m_puserinteraction->m_pthreadUserInteraction) != this)
      {

         return false;

      }

      return true;

   }


   ::user::interaction * window::get_desktop_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window * window::get_next_window(::u32 nFlag)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window * window::get_top_window() const 
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window * window::get_window(::u32 nCmd) const 
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window * window::get_last_active_popup() const 
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window * window::get_parent() const 
   {

      throw ::interface_only();

      return nullptr;

   }


   oswindow window::get_parent_oswindow() const
   {

      throw ::interface_only();

      return nullptr;

   }


   void window::set_parent(::windowing::window * pwindowNewParent) 
   {

      throw ::interface_only();

   }


   ::windowing::window * window::get_owner() const
   {

      throw ::interface_only();

      return nullptr;

   }


   oswindow window::get_owner_oswindow() const
   {

      throw ::interface_only();

      return nullptr;

   }


   void window::set_owner(::windowing::window * pwindowNewOwner)
   {

      throw ::interface_only();

   }


   point_i32 window::GetCaretPos()
   {

      throw ::interface_only();

      return nullptr;

   }


   void window::SetCaretPos(const ::point_i32 & point)
   {

      throw ::interface_only();

   }


   void window::HideCaret() 
   {

      throw ::interface_only();

   }
     

   void window::ShowCaret() 
   {

      throw ::interface_only();

   }


   void window::DragAcceptFiles(bool bAccept)
   {

      throw ::interface_only();

   }


   ::pointer<::windowing::icon>window::load_icon(const ::payload& payloadFile)
   {

      auto picon = __create < icon >();

      if (!picon)
      {

         return nullptr;

      }

      picon->load_file(payloadFile);

      return picon;

   }


   void window::set_icon(::windowing::icon * picon)
   {

      m_picon = picon;

   }
    
    
   ::pointer<::windowing::icon>window::get_icon() const
   {

      return m_picon;

   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      throw ::interface_only();

   }


   ::point_i32 window::get_mouse_cursor_position()
   {

      return ::point_i32(0, 0);

   }


   void window::set_tool_window(bool bSet)
   {

      throw ::interface_only();

   }


   void window::on_set_parent(::user::interaction * pinteraction) 
   {

      throw ::interface_only();

   }


   bool window::get_rect_normal(::rectangle_i32 * prectangle)
   {

      throw ::interface_only();
      
      return false;
   
   }


   void window::show_task(bool bShow)
   {

      throw ::interface_only();

   }


   void window::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

      throw ::interface_only();

   }

   
   void window::non_top_most_upper_window_rects(::rectangle_i32_array & recta)
   {

      throw ::interface_only();

   }


   void window::post_non_client_destroy()
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


   float window::get_density_for_window()
   {

      return 1.0f;

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


    /// this function should be called in user/main thread
   void window::show_window(const ::e_display &edisplay, const ::e_activation &eactivation)
   {

      windowing_output_debug_string("\n::window::show_window 1");

   }


   void window::full_screen(const ::rectangle_i32 &rectangle)
   {

   }


   void window::exit_iconify()
   {

   }


   void window::exit_full_screen()
   {

   }


   void window::exit_zoomed()
   {

   }


   void window::set_keyboard_focus()
   {

      throw ::interface_only();

   }


   void window::set_active_window()
   {

      throw ::interface_only();

   }


   void window::bring_to_front()
   {

      throw ::interface_only();

   }


   void window::switch_to_this_window(bool b)
   {

      throw ::interface_only();

   }


   void window::graphics_lock()
   {


   }


   void window::graphics_unlock()
   {



   }


   bool window::client_to_screen(::point_i32 *ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::point_i32 *ppoint)
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

      if (m_puserinteractionimpl == nullptr)
      {

         return true;

      }

      if (!m_puserinteractionimpl->m_puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }

   
   bool window::on_set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   {

      return set_window_position(zorder, x, y, cx, cy, eactivation, bNoZorder, bNoMove, bNoSize, bShow, bHide);

   }


   bool window::set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   {

      bool bOk = false;

      return bOk;

   }


   bool window::_set_window_pos(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   {

      return true;

   }


   void window::update_screen()
   {

   }


   void window::window_show()
   {

      auto window_show = [this]()
      {

         auto puserinteractionimpl = m_puserinteractionimpl;

         if (::is_set(puserinteractionimpl))
         {

            auto puserinteraction = puserinteractionimpl->m_puserinteraction;

            if (::is_set(puserinteraction))
            {

               auto puserinteractionimpl2 = puserinteraction->m_pinteractionimpl;

               if (::is_set(puserinteractionimpl2))
               {

                  puserinteractionimpl2->window_show();

               }

            }

         }

      };
   
      m_pwindowing->windowing_post(window_show);
      
   }


   void window::frame_toggle_restore()
   {
    
      m_puserinteractionimpl->m_puserinteraction->frame_toggle_restore();
    
   }


   void window::window_send(const ::procedure & procedure)
   {

      __matter_send_procedure(this, this, &window::window_post, procedure);

   }


   void window::window_post(const ::procedure & procedure)
   {

      auto puserinteractionimpl = m_puserinteractionimpl;

      if(puserinteractionimpl)
      {

         auto puserinteraction = puserinteractionimpl->m_puserinteraction;

         if (puserinteraction)
         {

            auto pthread = puserinteraction->m_pthreadUserInteraction;

            if (pthread)
            {

               pthread->post_procedure(procedure);

               return;

            }

         }

      }

      throw ::exception(error_failed);

   }
   
   
   bool window::is_branch_current() const
   {

      return false;

   }


   itask_t window::get_itask() const
   {

      itask_t itask = 0;

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if (puserinteraction && puserinteraction->m_pthreadUserInteraction)
      {

         itask = puserinteraction->m_pthreadUserInteraction->get_itask();

      }
      else
      {

         itask = get_current_itask();

      }

      return itask;

   }


   void window::on_touch_down(int x, int y)
   {

      ::lparam lparam(x, y);

      m_pointCursor.x() = x;

      m_pointCursor.y() = y;

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_left_button_down, 0, lparam);

   }


   void window::on_touch_drag(int x, int y)
   {

      ::lparam lparam(x, y);

      m_pointCursor.x() = x;

      m_pointCursor.y() = y;

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_mouse_move, 0, lparam);

   }


   void window::on_touch_up(int x, int y)
   {

      ::lparam lparam(x, y);

      m_pointCursor.x() = x;

      m_pointCursor.y() = y;

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_left_button_up, 0, lparam);

   }


   void window::on_size(int w, int h)
   {

      ::lparam lparam(w, h);

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_size, 0, lparam);

   }


   void window::on_text(const ::ansi_character* pansisz, strsize length)
   {


   }


   void window::on_text(const ::wd16_character* pwd16sz, strsize length)
   {


   }


   void window::on_text(const ::wd32_character* pwd32sz, strsize length)
   {


   }


   ::aura::application* window::get_app()
   {

      return m_pcontext && m_pcontext->m_pacmeapplication ? m_pcontext->m_pacmeapplication->m_pauraapplication : nullptr;

   }


   ::aura::session* window::get_session()
   {

      return m_pcontext && m_pcontext->m_pacmesession ? m_pcontext->m_pacmesession->m_paurasession : nullptr;

   }


   //::aura::system* windowacmesystem()
   //{

   //   return acmesystem() ? acmesystem()->m_paurasystem : nullptr;

   //}


} // namespace windowing


CLASS_DECL_AURA ::user::interaction* __user_interaction(::windowing::window* pwindow)
{

   if (::is_null(pwindow))
   {

      return nullptr;

   }

   auto puserinteractionimpl = pwindow->m_puserinteractionimpl;

   if (::is_null(puserinteractionimpl))
   {

      return nullptr;

   }

   auto puserinteraction = puserinteractionimpl->m_puserinteraction;

   if (::is_null(puserinteraction))
   {

      return nullptr;

   }

   return puserinteraction;

}



