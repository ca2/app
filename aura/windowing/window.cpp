// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "aura/user/_user.h"
#include "acme/operating_system/_user.h"


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

      //m_puserinteractionimpl = nullptr;

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


   void window::on_initialize_object()
   {

      //auto estatus = 
      
      ::channel::on_initialize_object();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psession = get_session();

      auto puser = psession->user();

      puser->on_initialize_window_object();

      //return estatus;

   }


   void window::assert_ok() const
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
      
      if(pmessage->m_atom == e_message_post_user)
      {

         auto pobject = pmessage->m_union.m_pobject;

         __pointer(::message::message) pmessagePost = pobject->m_pelement;

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

      throw ::interface_only();
      
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

   ::color::color window::screen_pixel(int x, int y) const
{

   return m_puserinteractionimpl->screen_pixel(x, y);

}


   ::windowing::display * window::display()
   {

      return m_pdisplay;

   }


   ::user::copydesk * window::copydesk()
   {

      if (!m_pcopydesk)
      {

         __raw_compose(m_pcopydesk);

         if (m_pcopydesk)
         {

            //auto estatus = 
            
            m_pcopydesk->initialize_copydesk(this);

            //if (!estatus)
            //{

            //   __release(m_pcopydesk);

            //}

         }

      }

      return m_pcopydesk;

   }


   void window::set_mouse_capture()
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   //void window::get_capture()
   //{

   //   throw ::interface_only();

   //   return m_pcapture;;

   //}



   //void window::set_capture()
   //{

   //   throw ::interface_only();

   //   throw ::interface_only();

   //}


   void window::destroy_window()
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   void window::on_destroy()
   {

      try
      {

         if (m_pcopydesk.is_set())
         {

            m_pcopydesk->destroy();

            __release(m_pcopydesk);

         }

      }
      catch (...)
      {

      }

      //return ::success;

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




   void window::set_window_text(const ::string & pszString)
   {

      throw ::interface_only();

   }


   strsize window::get_window_text(char * pszStringBuf, strsize nMaxCount)
   {

      throw ::interface_only();

      return 0;

   }

   void window::get_window_text(string & rectangleString)
   {

      throw ::interface_only();

   }



   strsize window::get_window_text_length()
   {

      throw ::interface_only();

      return 0;

   }


   void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      throw ::interface_only();

   }



   //bool window::window_is_iconic()
   //{
   //
   //   throw ::interface_only();
   //
   //   return false;
   //
   //}


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


   bool window::window_rect_from_os(RECTANGLE_I32 * prectangle)
   {

      return false;

   }


   bool window::client_rect_from_os(RECTANGLE_I32 * prectangle)
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


   void window::set_oswindow(oswindow oswindow)
   { 
      
      set_os_data(oswindow); 

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


   bool window::GetUpdateRect(RECTANGLE_I32 * prectangle, bool bErase)
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

      //return false;

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


   __pointer(::windowing::icon) window::load_icon(const ::payload& payloadFile)
   {

      auto picon = __create < icon >();

      if (!picon)
      {

         return nullptr;

      }

      //auto estatus = 
      
      picon->load_file(payloadFile);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return picon;

   }


   void window::set_icon(::windowing::icon * picon)
   {

      m_picon = picon;

      //return ::success;

   }
    
    
   __pointer(::windowing::icon) window::get_icon() const
   {

      //throw ::interface_only();

      ///return nullptr;

      return m_picon;

   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   ::point_i32 window::get_mouse_cursor_position()
   {

      return ::point_i32(0, 0);

   }


   void window::set_tool_window(bool bSet)
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   void window::on_set_parent(::user::interaction * pinteraction) 
   {

      throw ::interface_only();

   }


   bool window::get_rect_normal(RECTANGLE_I32 * prectangle)
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


   void window::show_window(const ::e_display &edisplay, const ::e_activation &eactivation)
   {

      windowing_output_debug_string("\n::window::show_window 1");

      //return ::success;

   }


   void window::full_screen(const ::rectangle_i32 &rectangle)
   {

      //return ::success_none;

   }


   void window::exit_iconify()
   {

      //return ::success_none;

   }


   void window::exit_full_screen()
   {

      //return ::success_none;

   }


   void window::exit_zoomed()
   {

      //return ::success_none;

   }


   void window::set_keyboard_focus()
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   void window::set_active_window()
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   void window::bring_to_front()
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   void window::graphics_lock()
   {


   }


   void window::graphics_unlock()
   {



   }


   bool window::client_to_screen(POINT_I32 *ppoint)
   {

      return true;

   }


   bool window::screen_to_client(POINT_I32 *ppoint)
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
   
      m_pwindowing->windowing_post(__routine([this]()
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

                                             }));
      
   }

   void window::frame_toggle_restore()
   {
    
      //auto estatus= 
      
      m_puserinteractionimpl->m_puserinteraction->frame_toggle_restore();
    
      //if(!estatus)
      //{
      // 
      //   return estatus;
    
      //}

      //return estatus;
    
   }


   void window::window_send(const ::routine & routine)
   {

      //auto estatus = 
      
      __send_routine(this, &window::window_post, routine);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void window::window_post(const ::routine & routine)
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

               pthread->post_routine(routine);

               return;

            }

         }

      }

      throw_status(error_failed);

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

         itask = puserinteraction->m_pthreadUserInteraction->get_ithread();

      }
      else
      {

         itask = get_current_itask();

      }

      return itask;

   }


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
