// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "cursor.h"
#include "display.h"
#include "placement_log.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/nano/user/display.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/_text_stream.h"
#include "aura/windowing/window.h"
//#include "windowing_gtk3/window.h"

#include "aura/windowing/windowing.h"
#include "aura/windowing/icon.h"
#include "aura/user/user/user.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/user/user/interaction_graphics_thread.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/copydesk.h"
#include "aura/user/user/interaction.h"


namespace windowing
{


   window::window()
   {

      m_psandboxwindowingwindow = nullptr;

      m_pWindow4 = nullptr;

      //set_oswindow(nullptr);

      m_bMessageOnlyWindow = false;

      m_bUpdateScreenSynchronously = true;

      m_bActiveWindow = false;

      m_bKeyboardFocus = false;

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

      m_pparticleChildrenSynchronization = node()->create_mutex();

   }


   void window::destroy()
   {

      ::channel::destroy();

      ::windowing::window_base::destroy();


   }

   void window::window_on_activate()
   {

      m_bActiveWindow = true;

   }


   void window::window_on_deactivate()
   {

      m_bActiveWindow = false;

   }


   void window::window_on_set_keyboard_focus()
   {

      m_bKeyboardFocus = true;

   }


   void window::window_on_kill_keyboard_focus()
   {

      m_bKeyboardFocus = false;

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

      if (pmessage->m_atom == e_message_post_user)
      {

         auto pparticle = pmessage->m_union.m_pparticle;

         ::pointer<::message::message> pmessagePost = pparticle->m_pparticle;

         if (::is_null(pmessagePost))
         {

            return;

         }

         if (pmessagePost->m_atom == e_message_scroll_y)
         {

            ::acme::get()->platform()->informationf("e_message_scroll_y");


         } 
         else if (pmessagePost->m_atom == e_message_text_composition)
         {

            ::acme::get()->platform()->informationf("message text composition");

         }

         m_puserinteractionimpl->message_handler(pmessagePost);

         return;

      }

      m_puserinteractionimpl->message_handler(pmessage);

   }


   void window::call_create_window(::user::interaction_impl *puserinteractionimpl)
   {
      
      
      //if (::is_window(get_handle()))
      //{
      
      //   DestroyWindow();
      
      //}
      
      //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
      //       __is_valid_atom(lpszClassName));
      //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));
      
      // allow modification of several common create parameters
      //::user::system createstruct;
      //      pusersystem->m_createstruct.hwndParent = hWndParent;
      //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
      
      auto puserinteraction = puserinteractionimpl->m_puserinteraction;
      
      auto pusersystem = puserinteraction->m_pusersystem;
      
      //pusersystem->m_createstruct.hMenu = nullptr;
      //      pusersystem->m_createstruct.hInstance = ::aura::get_system()->m_hInstance;
      //pusersystem->m_createstruct.lpCreateParams = lpParam;
      
      //hook_window_create(puserinteraction);
      
      //CGRect rectangle_i32;
      
      //      rectangle_i32 rectParam;
      
      //      rectParam.left = m_pusersystem->m_createstruct.x;
      //      rectParam.top = pusersystem->m_createstruct.y;
      //      rectParam.right = pusersystem->m_createstruct.x + pusersystem->m_createstruct.cx();
      //      rectParam.bottom = pusersystem->m_createstruct.y + pusersystem->m_createstruct.cy();
      
      //      copy(rectangle, rectParam);
      //
      //      if (pusersystem->m_createstruct.hwndParent == MESSAGE_WINDOW_PARENT)
      //      {
      //
      //         return true;
      //
      //      }
      //      else
      //      {
      
      unsigned uStyle = 0;
      
//      if(puserinteraction->m_ewindowflag & ::e_window_flag_miniaturizable)
//      {
//         
//#define NSWindowStyleMaskMiniaturizable (1 << 2)
//         
//         uStyle |= NSWindowStyleMaskMiniaturizable;
//         
//      }
//      
//      auto rectangle = puserinteraction-> const_layout().sketch().parent_raw_rectangle();
//      
//      CGRect cgrect;
//      
//      copy(cgrect, rectangle);
      
      //__todo?
      //windowing()->copy(cgrect, rectangle);
      //or
      //display()->copy(cgrect, rectangle);
      //because rectangle origin is top-left
      //and because cgrect origin is bottom-left and,
      //the origin of screen is at bottom.
      
      m_puserinteractionimpl = puserinteractionimpl;
      
      puserinteraction->m_puserinteractionTopLevel = puserinteraction;
      
      puserinteraction->m_pwindow = this;
      
      puserinteractionimpl->m_pwindow = this;
      
      m_puserinteractionimpl->install_message_routing(puserinteraction);
      
      auto psession = m_pcontext->m_pacmesession->m_paurasession;
      
      auto puser = psession->user();
      
      auto pwindowing = (::windowing::windowing *) puser->windowing();
//      
//      m_pmacoswindowing = dynamic_cast < class windowing * >(pwindowing);
      
      m_pwindowing = pwindowing;
      
      puserinteractionimpl->m_pwindowing = pwindowing;
      
      create_window();

      puserinteraction->m_ewindowflag |= e_window_flag_window_created;

      puserinteraction->set_flag(e_flag_task_started);

      on_finished_window_creation();

   }


   //void window::create_window(::user::interaction_impl * puserinteractionimpl)
   void window::create_window()
   {

      //__UNREFERENCED_PARAMETER(puserinteractionimpl);

      throw ::interface_only();

   }


   void window::on_finished_window_creation()
   {

      auto pimpl = m_puserinteractionimpl;

      auto puserinteraction = pimpl->m_puserinteraction;

      puserinteraction->send_message(e_message_pos_create, 0, 0);


   }

   void window::set_context_org(draw2d::graphics_pointer& pgraphics)
   {


   }



//   void window::set_cursor_position(const ::point_i32 & pointCursor)
//   {
//
//      m_pointCursor = pointCursor;
//
//   }
//
//
//   void window::get_cursor_position(::point_i32 * ppointCursor)
//   {
//
//      *ppointCursor = m_pointCursor;
//
//   }


   //bool window::defer_set_icon()
   //{

   //   return false;

   //}


   class placement_log * window::placement_log()
   {

      __defer_construct_new(m_pplacementlog);

      return m_pplacementlog;

   }


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

      return m_bKeyboardFocus;

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

      return m_pnanouserdisplay.cast < ::windowing::display>();

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

      auto pthread = m_puserinteractionimpl->m_puserinteraction->m_pthreadUserInteraction;

      windowing()->set_mouse_capture(pthread, this);

      //::pointer < ::windowing_wayland::display > pwaylanddisplay = m_pnanouserdisplay;

      //pwaylanddisplay->__capture_mouse(this, pwaylanddisplay->m_uLastButtonSerial);


//      m_pwindowing->windowing_post([this]()
//                                   {
//
//                                      synchronous_lock synchronouslock(user_synchronization());
//
////                                      display_lock displaylock(x11_display()->Display());
//
//                                      information() << "XGrabPointer";
////
////                                      auto grabStatus = XGrabPointer(Display(), Window(), False,
////                                                                     ButtonPressMask | ButtonReleaseMask |
////                                                                     PointerMotionMask,
////                                                                     GrabModeAsync, GrabModeAsync, None, None,
////                                                                     CurrentTime);
//
////                                      if (grabStatus != GrabSuccess)
////                                      {
////
////                                         windowing_output_debug_string("\noswindow_data::SetCapture 2.1");
////
////                                         return;
////
////                                      }
//
////                                      auto pdisplay = x11_display();
////
////                                      if (pdisplay)
////                                      {
////
////                                         pdisplay->_on_capture_changed_to(this);
////
////                                      }
//
//                                      windowing_output_debug_string("\noswindow_data::SetCapture 2");
//
//                                   });
//
//      //return ::success;

   }


   bool window::defer_release_mouse_capture()
   {

      auto pthread = m_puserinteractionimpl->m_puserinteraction->m_pthreadUserInteraction;

      return windowing()->defer_release_mouse_capture(pthread, this);

   }


   void window::destroy_window()
   {

      if (::is_set(m_pwindowing))
      {

         m_pwindowing->erase_window(this);

      }

      m_pwindowParent.release();

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


   void window::on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem)
   {

      ::string strActionName(psystemmenuitem->m_strAtom);

      if(strActionName == "minimize")
      {

         window_minimize();

      }
      else if(strActionName == "maximize")
      {

         window_maximize();

      }
      else if(strActionName == "maximize")
      {

         window_maximize();

      }
      else if(strActionName == "about_box")
      {

         application()->show_about_box();

      }
      else if(strActionName == "close")
      {

         m_puserinteractionimpl->m_puserinteraction->post_message(e_message_close);

      }
      else if(strActionName == "")
      {

         print_line("reaching here?!");
         //defer_perform_entire_reposition_process(nullptr);

      }
      else if(strActionName == "")
      {

         print_line("also here");

         //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

      }


   }


   void window::activate_top_parent()
   {


   }




//   void window::on_visual_applied()
//   {
//
//      throw ::interface_only();
//
//   }


   // bool window::is_window_zoomed()
   // {
   //
   //    return false;
   //
   // }


   void window::_on_configure_notify_unlocked(const ::rectangle_i32 & rectangle)
   {

      m_pointWindow = rectangle.top_left();

      m_sizeWindow = rectangle.size();

      m_puserinteractionimpl->m_puserinteraction->_on_configure_notify_unlocked(rectangle);

   }


   void window::_on_reposition_notify_unlocked(const ::point_i32 & point)
   {

      m_pointWindow = point;

      m_puserinteractionimpl->m_puserinteraction->_on_reposition_notify_unlocked(point);

   }


   void window::win_update_graphics()
   {

      throw ::interface_only();

   }


   lresult window::send_message(const ::atom & atom, wparam wParam, lparam lParam)
   {

      return 0;

   }


   void window::post_message(const ::atom & atom, wparam wParam, lparam lParam)
   {

      //return false;

   }


   void window::set_window_text(const ::scoped_string & scopedstr)
   {

      throw ::interface_only();

   }


//   ::string window::get_window_text()
//   {
//
//      return {};
//
//   }


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


   void window::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      throw ::interface_only();

   }


   void window::present()
   {

      throw ::interface_only();

   }


//   bool window::presentation_complete()
//   {
//
//      return true;
//
//   }

   ::oswindow window::oswindow() const
   {

      throw interface_only();

      return nullptr;

   }




   void window::set_oswindow(::oswindow oswindow)
   {

      _set_oswindow(oswindow);

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


   void window::_set_oswindow(::oswindow oswindow)
   {

      throw interface_only();

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


   void window::enable_window(bool bEnable)
   {

      throw ::interface_only();

      //return false;

   }


   // the active interaction_impl applies only to top-level (frame windows)
   ::user::interaction * window::get_active_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   void window::set_active_window()
   {

      throw ::interface_only();

      //return nullptr;

   }


   void window::_set_active_window_unlocked()
   {

      throw ::interface_only();

      //return nullptr;

   }


   // the foreground interaction_impl applies only to top-level windows (frame windows)
   void window::set_foreground_window()
   {

      throw ::interface_only();

   }


   void window::_set_foreground_window_unlocked()
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

      return m_bActiveWindow;

//      if(m_pwindowing->get_active_window(m_puserinteractionimpl->m_puserinteraction->m_pthreadUserInteraction) != this)
//      {
//
//         return false;
//
//      }
//
//      return true;

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

      return {};

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


   ::pointer<::windowing::icon> window::load_icon(const ::payload & payloadFile)
   {

      auto picon = __create<icon>();

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


   ::pointer<::windowing::icon> window::get_icon() const
   {

      return m_picon;

   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      m_pcursor = pcursor;

   }


   ::windowing::cursor * window::get_mouse_cursor()
   {

      return m_pcursor;

   }


//   ::point_i32 window::get_mouse_cursor_host_position()
//   {
//
//      return ::point_i32(0, 0);
//
//   }
//
//
//   ::point_i32 window::get_mouse_cursor_absolute_position()
//   {
//
//      return ::point_i32(0, 0);
//
//   }


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


   void window::_window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

      throw ::interface_only();

   }


   void window::non_top_most_upper_window_rects(::rectangle_i32_array & recta)
   {

      throw ::interface_only();

   }


   void window::post_non_client_destroy()
   {

      m_pplacementlog.release();
      m_pparticleChildrenSynchronization.release();
      m_pcursor.release();
      m_pcopydesk.release();
      m_pwindowing.release();
      m_picon.release();
      m_pwindowParent.release();
      m_pmessagequeue.release();
      m_puserinteractionimpl.release();
      m_pnanouserdisplay.release();

      ::channel::destroy();

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


//   /// this function should be called in user/main thread
//   void window::show_window(const ::e_display & edisplay, const ::e_activation & eactivation)
//   {
//
//      windowing_output_debug_string("::window::show_window 1");
//
//   }
//
//
//   void window::_show_window_unlocked(const ::e_display & edisplay, const ::e_activation & eactivation)
//   {
//
//
//   }


   void window::full_screen(const ::rectangle_i32 & rectangle)
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


   void window::_set_keyboard_focus_unlocked()
   {

      throw ::interface_only();

   }


   /*void window::set_active_window()
   {

      throw ::interface_only();

   }*/


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


   bool window::client_to_screen(::point_i32 * ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::point_i32 * ppoint)
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

      windowing_output_debug_string("::window::is_window_visible 1");

      return false;

   }


   bool window::_is_iconic_unlocked()
   {

      windowing_output_debug_string("::window::_is_iconic_unlocked 1");

      return false;

   }


   bool window::_is_window_visible_unlocked()
   {

      windowing_output_debug_string("::window::_is_window_visible_unlocked 1");

      return false;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }
      
      auto puserinteractionimpl = m_puserinteractionimpl;

      if (!puserinteractionimpl)
      {

         return true;

      }

      auto puserinteraction = puserinteractionimpl->m_puserinteraction;
      
      if (!puserinteraction)
      {

         return true;

      }
      
      if (!puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


   bool window::on_set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                       const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                       ::e_display edisplay)
   {

      return set_window_position(zorder, x, y, cx, cy, eactivation, bNoZorder, bNoMove, bNoSize, edisplay);

   }


   bool window::set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                    const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                    ::e_display edisplay)
   {

      bool bOk = false;

      return bOk;

   }


   bool window::_set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                     const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                     ::e_display edisplay, ::u32 nOverrideFlags)
   {

      return true;

   }


   bool window::configure_window_unlocked()
   {

      // Request / Incoming changes / Prepare Internal Buffer
      auto & stateOutput = m_puserinteractionimpl->m_puserinteraction->layout().m_statea[::user::e_layout_design];

      // Current/Previous Window State
      auto & stateWindow = m_puserinteractionimpl->m_puserinteraction->layout().m_statea[::user::e_layout_window];

      //bool bSetWindowPosition = true;

      //if (stateOutput == stateWindow)
      //{

      //   bSetWindowPosition = false;

      //}

      auto eactivationOutput = stateOutput.activation();

      auto eactivationWindow = stateWindow.activation();

      auto edisplayOutput = stateOutput.display();

      auto edisplayWindow = stateWindow.display();

      auto zOutput = stateOutput.zorder();

      auto zWindow = stateWindow.zorder();

      bool bVisibilityChange = edisplayOutput != edisplayWindow;

      bool bZ = zOutput.is_change_request();

      if (bVisibilityChange || bZ || eactivationOutput != e_activation_default)
      {

         informationf("::windowing::window::configure_window_unlocked bVisibilityChange(%d) bZ(%d) bActivation(%d)",
                     (int)bVisibilityChange,
                     (int)bZ,
                     (int) (eactivationOutput != e_activation_default));

         information() << "::windowing::window::configure_window_unlocked displayRequest : " << edisplayOutput;

         if(_configure_window_unlocked(
            zOutput,
            eactivationOutput,
            !bZ,
            edisplayOutput))
         {

            stateWindow.display() = stateOutput.display();

            stateOutput.m_eactivation.clear();

            stateOutput.m_zorder.clear_request();

         }

      }

      return true;

   }


   bool window::strict_set_window_position_unlocked(bool & bChangedPosition, bool & bChangedSize)
   {

      if(!m_puserinteractionimpl || !m_puserinteractionimpl->m_puserinteraction)
      {

         return false;

      }

      auto rectangle = m_puserinteractionimpl->m_puserinteraction->const_layout().parent_raw_rectangle(::user::e_layout_design);

      return strict_set_window_position_unlocked(bChangedPosition, bChangedSize, rectangle);

   }


   bool window::strict_set_window_position_unlocked(bool & bChangedPosition, bool & bChangedSize, const ::rectangle_i32 & rectangle)
   {

      auto pointOutput= rectangle.origin();

      auto pointWindow = m_pointWindow;

      bChangedPosition = pointWindow != pointOutput;

      if (bChangedPosition)
      {

         //information() << "Design.point != Window.point " << pointDesign << ", " << pointWindow;

      }

      auto sizeOutput = rectangle.size();

      auto sizeWindow = m_sizeWindow;

      bChangedSize = sizeWindow != sizeOutput;

      if(bChangedSize)
      {

         //information() << "Design.size != Window.size " << sizeOutput << ", " << sizeWindow;

      }

      if (bChangedPosition || bChangedSize)
      {

         ::rectangle_i32 rectangleOutput(pointOutput, sizeOutput);

         //information() << "::windowing::window::_set_window_position_unlocked l:" << r.left() << ", t:" << r.top()
         //              << ", r:" << r.right() << ", b:" << r.bottom() << ", thrd:" << ::task_index();

         static ::point_i32 s_pointInitialTopRight;

         if(s_pointInitialTopRight.is_null())
         {

            s_pointInitialTopRight = rectangleOutput.top_right();

         }

         auto offset = rectangleOutput.top_right() - s_pointInitialTopRight;

         information() << "TopRightOffsetFromInitial : " << offset;

         if(offset.cx() != 0 || offset.cy() != 0)
         {

//            information() << "Offset is Not Null";

         }

         _strict_set_window_position_unlocked(
            pointOutput.x(),
            pointOutput.y(),
            sizeOutput.cx(),
            sizeOutput.cy(),
            !bChangedPosition, !bChangedSize);

         //stateWindow = stateDesign;

      }

      return true;

   }


   bool window::full_set_window_position_unlocked()
   {

      auto & stateDesign = m_puserinteractionimpl->m_puserinteraction->layout().m_statea[::user::e_layout_design];

      auto pointDesign = stateDesign.origin();

      auto pointWindow = m_pointWindow;

      bool bMove = pointWindow != pointDesign;

      if (bMove)
      {

         //information() << "Design.point != Window.point " << pointDesign << ", " << pointWindow;

      }

      auto sizeOutput = stateDesign.size();

      auto sizeWindow = m_sizeWindow;

      bool bSize = sizeWindow != sizeOutput;

      if (bSize)
      {

         //information() << "Design.size != Window.size " << sizeOutput << ", " << sizeWindow;

      }

      // Request / Incoming changes / Prepare Internal Buffer
      auto & stateOutput = m_puserinteractionimpl->m_puserinteraction->layout().m_statea[::user::e_layout_design];

      // Current/Previous Window State
      auto & stateWindow = m_puserinteractionimpl->m_puserinteraction->layout().m_statea[::user::e_layout_window];

      //bool bSetWindowPosition = true;

      //if (stateOutput == stateWindow)
      //{

      //   bSetWindowPosition = false;

      //}

      auto eactivationOutput = stateOutput.activation();

      auto eactivationWindow = stateWindow.activation();

      auto edisplayOutput = stateOutput.display();

      auto edisplayWindow = stateWindow.display();

      auto zOutput = stateOutput.zorder();

      auto zWindow = stateWindow.zorder();

      bool bVisibilityChange = edisplayOutput != edisplayWindow;

      bool bZ = zOutput.is_change_request();

      if (bMove || bSize
         || bVisibilityChange || bZ || eactivationOutput != e_activation_default)
      {

         ::rectangle_i32 r(pointDesign, sizeOutput);

         //information() << "::windowing::window::_set_window_position_unlocked l:" << r.left() << ", t:" << r.top()
         //              << ", r:" << r.right() << ", b:" << r.bottom() << ", thrd:" << ::task_index();

         static ::point_i32 s_pointInitialTopRight;

         if (s_pointInitialTopRight.is_null())
         {

            s_pointInitialTopRight = r.top_right();

         }

         auto offset = r.top_right() - s_pointInitialTopRight;

         information() << "TopRightOffsetFromInitial : " << offset;

         if (offset.cx() != 0 || offset.cy() != 0)
         {

            //            information() << "Offset is Not Null";

         }

         _set_window_position_unlocked(
            zOutput,
            pointDesign.x(),
            pointDesign.y(),
            sizeOutput.cx(),
            sizeOutput.cy(),
            eactivationOutput,
            !bZ, !bMove, !bSize,
            edisplayOutput);

         bool bConsiderPositionAsSetOnConfigure = true;

         if (bConsiderPositionAsSetOnConfigure)
         {

            stateWindow.m_point2 = stateOutput.m_point2;

            stateWindow.m_size = stateOutput.m_size;

         }

         stateWindow.display() = stateOutput.display();

         stateOutput.m_eactivation.clear();

         stateOutput.m_zorder.clear_request();

      }

      return true;

   }



   bool window::_set_window_position_unlocked(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                              const ::e_activation & eactivation, bool bNoZorder, bool bNoMove,
                                              bool bNoSize, ::e_display edisplay)
   {

      bool bOk1 = _configure_window_unlocked(zorder, eactivation, bNoZorder, edisplay);

      bool bOk2 = _strict_set_window_position_unlocked(x, y, cx, cy, bNoMove, bNoSize);

      return bOk1 && bOk2;

   }


   bool
   window::_configure_window_unlocked(const class ::zorder & zorder, const ::e_activation & eactivation, bool bNoZorder,
                                      ::e_display edisplay)
   {

      bool bOk = false;

      return bOk;

   }


   bool window::_strict_set_window_position_unlocked(i32 x, i32 y, i32 cx, i32 cy, bool bNoMove, bool bNoSize)
   {

      bool bOk = false;

      return bOk;

   }


   void window::__update_graphics_buffer()
   {

   }


//   void window::window_request_presentation()
//   {
//
//      m_pwindowing->windowing_post([this]()
//                                   { _window_request_presentation_locked(); });
//
////      auto window_show = [this]()
////      {
////
////         auto puserinteractionimpl = m_puserinteractionimpl;
////
////         if (::is_set(puserinteractionimpl))
////         {
////
////            auto puserinteraction = puserinteractionimpl->m_puserinteraction;
////
////            if (::is_set(puserinteraction))
////            {
////
////               auto puserinteractionimpl2 = puserinteraction->m_pinteractionimpl;
////
////               if (::is_set(puserinteractionimpl2))
////               {
////
////                  puserinteractionimpl2->window_show();
////
////               }
////
////            }
////
////         }
////
////      };
////
////      m_pwindowing->windowing_post(window_show);
//
//   }


   //void window::_window_request_presentation_locked()
   //{


   //}


//   void window::_window_request_presentation_set_window_position_unlocked(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
//   {
//
//
//   }


   void window::frame_toggle_restore()
   {

      m_puserinteractionimpl->m_puserinteraction->frame_toggle_restore();

   }


   void window::user_send(const ::procedure & procedure)
   {

      auto puserinteractionimpl = m_puserinteractionimpl;

      if (puserinteractionimpl)
      {

         auto puserinteraction = puserinteractionimpl->m_puserinteraction;

         if (puserinteraction)
         {

            puserinteraction->user_send(procedure);

            return;

//            auto pthread = puserinteraction->m_pthreadUserInteraction;
//
//            if (pthread)
//            {
//
//               pthread->post_procedure(procedure);
//
//               return;
//
//            }

         }

      }

      throw ::exception(error_failed);

   }


   void window::user_post(const ::procedure & procedure)
   {

      auto puserinteractionimpl = m_puserinteractionimpl;

      if (puserinteractionimpl)
      {

         auto puserinteraction = puserinteractionimpl->m_puserinteraction;

         if (puserinteraction)
         {

            puserinteraction->user_post(procedure);

            return;

//            auto pthread = puserinteraction->m_pthreadUserInteraction;
//
//            if (pthread)
//            {
//
//               pthread->post_procedure(procedure);
//
//               return;
//
//            }

         }

      }

      throw ::exception(error_failed);

   }


   void window::main_send(const ::procedure & procedure)
   {

#ifdef WINDOWS_DESKTOP

      user_send(procedure);

#else

      node()->main_send(procedure);

#endif

   }


   void window::main_post(const ::procedure & procedure)
   {

#ifdef WINDOWS_DESKTOP

      user_post(procedure);

#else

      node()->main_post(procedure);

#endif

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

      } else
      {

         itask = current_itask();

      }

      return itask;

   }


   void window::on_touch_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
   {

      ::lparam lparam(xHost, yHost);

      m_pointCursor2.x() = xHost;

      m_pointCursor2.y() = yHost;

      m_pnanouserdisplay->m_pointCursor2.x() = xAbsolute;

      m_pnanouserdisplay->m_pointCursor2.y() = yAbsolute;

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_left_button_down, 0, lparam);

   }


   void window::on_touch_drag(int xHost, int yHost, int xAbsolute, int yAbsolute)
   {

      ::lparam lparam(xHost, yHost);

      m_pointCursor2.x() = xHost;

      m_pointCursor2.y() = yHost;

      m_pnanouserdisplay->m_pointCursor2.x() = xAbsolute;

      m_pnanouserdisplay->m_pointCursor2.y() = yAbsolute;

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_mouse_move, 0, lparam);

   }


   void window::on_touch_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
   {

      ::lparam lparam(xHost, yHost);

      m_pointCursor2.x() = xHost;

      m_pointCursor2.y() = yHost;

      m_pnanouserdisplay->m_pointCursor2.x() = xAbsolute;

      m_pnanouserdisplay->m_pointCursor2.y() = yAbsolute;

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_left_button_up, 0, lparam);

   }


   void window::on_size(int w, int h)
   {

      ::lparam lparam(w, h);

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_size, 0, lparam);

   }


   void window::on_text(const ::ansi_character * pansisz, strsize length)
   {


   }


   void window::on_text(const ::wd16_character * pwd16sz, strsize length)
   {


   }


   void window::on_text(const ::wd32_character * pwd32sz, strsize length)
   {


   }


   ::aura::application * window::get_app()
   {

      return m_pcontext && m_pcontext->m_pacmeapplication ? m_pcontext->m_pacmeapplication->m_pauraapplication
                                                          : nullptr;

   }


   ::aura::session * window::get_session()
   {

      return m_pcontext && m_pcontext->m_pacmesession ? m_pcontext->m_pacmesession->m_paurasession : nullptr;

   }


   //::aura::system* windowacmesystem()
   //{

   //   return system() ? system()->m_paurasystem : nullptr;

   //}


   void window::window_update_screen()
   {

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if (!(puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update))
      {

         //#ifdef LINUX

         //if (bStartWindowVisual)
         //{

         //puserinteraction->_window_request_presentation_locked();

         //m_pimpl->window_show();

         //}

         //#endif
         ////END IFDEF LINUX

      }

      // if (m_bVisualUpdated)
      // {

      //    m_bVisualUpdated = false;

      //    if (::is_set(m_pimpl->m_puserthread))
      //    {

      //       m_pimpl->m_puserthread->m_evApplyVisual.wait(15_s);

      //    }

      // }

      if (!this->task_get_run())
      {

         //return false;
         return;

      }

      bool bWindowsApplyVisual = true;

      auto & edisplayOutput = puserinteraction->const_layout().output().m_edisplay;

      auto & edisplayDesign = puserinteraction->const_layout().design().m_edisplay;

      if (edisplayOutput != edisplayDesign)
      {

         puserinteraction->send_message(e_message_show_window, ::is_screen_visible(edisplayDesign) ? 1 : 0);

      }


#if TIME_REPORTING

      auto e1 = g_timeBetweenUpdateBufferAndUpdateScreen.elapsed();

      ::time timeUpdateScreenPost;

      timeUpdateScreenPost.Now();

      informationf("timeBetweenUpdateBufferAndUpdateScreen "+as_string(e1.floating_millisecond().m_d) +"ms\n");

#endif

      //if (m_bUpdateScreen && (bWindowsApplyVisual || !bStartWindowVisual))
      {


         m_puserinteractionimpl->m_pgraphicsthread->graphics_thread_update_screen();

      }
      //else
      //{

      //   information() << "no update screen";

      //}

#if TIME_REPORTING

      auto e2 = timeUpdateScreenPost.elapsed();

      informationf("timeUpdateScreenPost " + as_string(e2.floating_millisecond().m_d) + "ms\n");

#endif

      puserinteraction->set_display(edisplayDesign, ::user::e_layout_output);

      if (!puserinteraction)
      {

         return;

      }

      if ((puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update))
      {
         // IFDEF WINDOWS
         //if (bStartWindowVisual)
         //{

         //puserinteraction->_window_request_presentation_locked();

         //m_pimpl->m_pwindow->window_show();
         //m_puserinteraction->post_procedure(m_procedureWindowShow);

         //}
         // ENDIF WINDOWS
      }


   }


   bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

      return false;

   }


   bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      return false;

   }


   void window::on_destruct_mouse_message(::message::mouse * pmouse)
   {

      //information() << "on_destruct_mouse_message";

      if(::is_null(pmouse))
      {

         return;

      }

      //information() << "pmouse set";

      try
      {

         ::windowing::cursor * pcursor = nullptr;

         auto pimpl = m_puserinteractionimpl;

         if(::is_set(pimpl))
         {

            auto puserinteraction = pimpl->m_puserinteraction;

            if(::is_set(puserinteraction))
            {

               pcursor = puserinteraction->user_mouse_get_cursor(pmouse);

            }

         }

         if(!pcursor)
         {

            pcursor = get_mouse_cursor();

            if(pcursor)
            {

               //information() << "got window cursor : " << pcursor->m_ecursor;

            }

         }
         else
         {

            //information() << "got mouse cursor : " << pcursor->m_ecursor;

         }

         if(pcursor)
         {
            
            //information() << "pcursor set";

            set_mouse_cursor(pcursor);
            
         }

      }
      catch(...)
      {

      }


//      if(::is_null(pmouse))
//      {
//
//         return;
//
//      }
//
//      try
//      {
//
//         aaaset_mouse_cursor(pmouse->m_pcursor);
//
//      }
//      catch(...)
//      {
//
//      }

   }


   ::trace_statement & window::trace_statement_prefix(::trace_statement & statement) const
   {

      statement << "window  ";

      if(m_puserinteractionimpl)
      {

         if(m_puserinteractionimpl->m_puserinteraction)
         {

            m_puserinteractionimpl->m_puserinteraction->raw_trace_statement_prefix(statement);

         }

      }

      return statement;

   }


   bool window::is_windowing_popup()
   {

      return ::is_set(m_puserinteractionimpl->m_puserinteraction->m_puserinteractionOwner);

   }


   ::point_i32 window::windowing_popup_origin()
   {

      auto p = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin();

      if (m_puserinteractionimpl->m_puserinteraction)
      {

         if (m_puserinteractionimpl->m_puserinteraction->get_parent())
         {

            m_puserinteractionimpl->m_puserinteraction->get_parent()->client_to_host()(p);

         }

      }

      return p;

   }


   ::size_i32 window::windowing_popup_size()
   {

      auto s = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().size();

      return s;

   }


   void window::_on_windowing_close_window()
   {

      m_puserinteractionimpl->m_puserinteraction->post_message(e_message_close);

   }


   bool window::is_satellite_window()
   {

      return m_puserinteractionimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window;

   }


   ::windowing::window_base * window::owner_window()
   {

      return m_puserinteractionimpl->m_puserinteraction->m_puserinteractionOwner->window();

   }


   ::string window::get_window_text()
   {

      return m_puserinteractionimpl->m_puserinteraction->get_window_text();

   }


   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

   }


//   ::message_queue * window::get_message_queue()
//   {
//
//      return m_pmessagequeue;
//
//   }
void window::pick_browse(const ::function < void(const ::file::path & path) > & callback)
{
}
void window::pick_media(const char * pszMediaType)
{
}
void window::on_prompt_write_file(::user::controller *pusercontroller)
{
   
}

void window::set_opacity(double dOpacity)
{


}

   // void window::window_restore()
   // {
   //
   //
   // }
   //
   //
   // void window::window_minimize()
   // {
   //
   //
   // }
   //
   //
   // void window::window_maximize()
   // {
   //
   //
   // }


} // namespace windowing


CLASS_DECL_AURA ::user::interaction * __user_interaction(::windowing::window * pwindow)
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



