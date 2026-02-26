#include "framework.h"
#include "interaction_thread.h"
#include "prototype_impl.h"
#include "interaction.h"
#include "aaa_interaction_impl.h"
#include "call_message_handler_task.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/include/_c_swap.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/platform/timer_array.h"
#include "aura/platform/session.h"
#include "aura/message/timer.h"
#include "aura/message/user.h"
#include "aura/user/user/user.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"


namespace user
{


   iptr_map < string > * g_p = nullptr;


   prototype_impl::prototype_impl()
   {

      m_bUserImplCreated = false;
      m_pinteractionimpl = nullptr;
      m_pinteractionchild = nullptr;
      //m_bDestroying = false;
      m_bDestroyImplOnly = false;
      m_iPendingRectMatch = -1;
      m_bPendingRedraw = false;
      m_puserinteraction = nullptr;
      m_bIgnoreSizeEvent = false;
      m_bIgnoreMoveEvent = false;
      //m_bUserElementOk = true;

   }


   prototype_impl::~prototype_impl()
   {

   }


   void prototype_impl::create_message_queue(::user::interaction * pinteraction, const ::scoped_string & scopedstrName)
   {

      throw ::interface_only();

      //return true;

   }


   //void prototype_impl::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * pparent)
   //{

   //   throw ::interface_only();

   //   return true;

   //}


   //void prototype_impl::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * puiParent)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void prototype_impl::create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pcs, ::user::interaction_base * puiParent, atom atom)
   //{

   //   throw ::interface_only();

   //   return true;

   //}


   //void prototype_impl::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * pparent)
   //{

   //   throw ::interface_only();

   //   return true;

   //}

   ::windowing::window * prototype_impl::get_user_interaction_impl()
   {

      return nullptr;

   }


   ::user::interaction_child * prototype_impl::get_user_interaction_child()
   {

      return nullptr;

   }


   void prototype_impl::defer_do_graphics(::draw2d::graphics_pointer & pgraphics)
   {

      m_puserinteraction->_000CallOnDraw(pgraphics);

   }


   void prototype_impl::top_down_prefix()
   {

      m_puserinteraction->top_down_prefix();

   }


   void prototype_impl::set_need_layout()
   {

      m_puserinteraction->set_need_layout();

      if (m_puserinteraction->m_puserinteractionParent != nullptr)
      {

         m_puserinteraction->m_puserinteractionParent->set_need_layout();

      }

   }


   void prototype_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //m_puserinteraction->message_call(::user::e_message_size, 0, process_state().m_size.lparam());

      //m_puserinteraction->m_timeLastVisualChange.Now();

      //m_puserinteraction->m_bSizeMove = true;


   }


   void prototype_impl::on_reposition()
   {

   }


   void prototype_impl::on_show_window()
   {

   }


   oswindow prototype_impl::detach_window()
   {

      return nullptr;

   }


   void prototype_impl::destroy()
   {

      ::channel::destroy();

      //::source::destroy();

      ::manager::destroy();

      //auto estatus = 
      m_puserinteraction.release();

      //return estatus;

   }


   //void prototype_impl::finish()
   //{

   //   ::user::interaction_base::finish();

   //}


//   void prototype_impl::graphics_thread_update_screen()
//   {
//
//      //return true;
//
//   }


   //void prototype_impl::RepositionBars(unsigned int nIDFirst, unsigned int nIDLast, atom idLeft, unsigned int nFlags, ::int_rectangle * prectParam, const int_rectangle & rectangleX, bool bStretch)
   //{

   //   if (!_is_window())
   //   {

   //      return;

   //   }

   //   __UNREFERENCED_PARAMETER(nIDFirst);

   //   __UNREFERENCED_PARAMETER(nIDLast);

   //   ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery || (nFlags & ~reposNoPosLeftOver) == reposExtra);

   //   SIZEPARENTPARAMS sizeparentparams;

   //   ::pointer<::user::interaction>puiLeft;

   //   sizeparentparams.bStretch = bStretch;

   //   sizeparentparams.sizeTotal.cx = sizeparentparams.sizeTotal.cy = 0;

   //   if (rectangleX != nullptr)
   //   {

   //      sizeparentparams.rectangle = rectangleX;

   //   }
   //   else
   //   {

   //      m_puserinteraction->rectangle(&sizeparentparams.rectangle);

   //   }

   //   if (::is_empty(sizeparentparams.rectangle))
   //   {

   //      return;

   //   }

   //   ::pointer<::user::interaction>pinteraction;

   //   while (m_puserinteraction->get_child(pinteraction))
   //   {

   //      atom atom = pinteraction->GetDlgCtrlId();

   //      if (atom == idLeft)
   //      {

   //         puiLeft = pinteraction;

   //      }
   //      else
   //      {

   //         pinteraction->send_message(::user::e_message_size_parent, 0, (lparam)& sizeparentparams);

   //      }

   //   }

   //   if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
   //   {

   //      ASSERT(prectParam != nullptr);

   //      if (bStretch)
   //      {

   //         ::copy(prectParam, &sizeparentparams.rectangle);

   //      }
   //      else
   //      {

   //         prectParam->left = prectParam->top = 0;

   //         prectParam->right = sizeparentparams.sizeTotal.cx;

   //         prectParam->bottom = sizeparentparams.sizeTotal.cy;


   //      }

   //      return;

   //   }


   //   if (!idLeft.is_empty() && puiLeft != nullptr)
   //   {

   //      if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
   //      {

   //         ASSERT(prectParam != nullptr);


   //         sizeparentparams.rectangle.left += prectParam->left;

   //         sizeparentparams.rectangle.top += prectParam->top;

   //         sizeparentparams.rectangle.right -= prectParam->right;

   //         sizeparentparams.rectangle.bottom -= prectParam->bottom;


   //      }

   //      if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
   //      {

   //         //puiLeft->CalcWindowRect(&sizeparentparams.rectangle);

   //         puiLeft->place(sizeparentparams.rectangle);

   //         puiLeft->display();

   //         puiLeft->set_need_layout();

   //      }

   //   }

   //}


   void prototype_impl::window_move(int x, int y)
   {

      //return true;

   }


   void prototype_impl::on_configure(const ::int_rectangle & rectangle)
   {


   }


//   void prototype_impl::on_resize(const ::int_size & size)
//   {
//
//
//   }


   //void prototype_impl::main_async(const promise::procedure & routine, enum_priority epriority)
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return ::error_failed;

   //   }

   //   auto puserinteraction = m_puserinteraction->get_wnd();

   //   if (!puserinteraction)
   //   {

   //       return ::error_failed;

   //   }

   //   return puserinteraction->post_procedure(routine, epriority);

   //}


   void prototype_impl::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      m_puserinteraction->_001OnTopNcClip(pgraphics);

   }


//   void prototype_impl::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//   }
//
//
//   void prototype_impl::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      string strType = ::platform::type(m_puserinteraction).name();
//
////      if (strType.contains("list_box"))
////      {
////
////         informationf("list_box");
////
////      }
//
//      windowing_output_debug_string("\ninteraction_impl_base::_001Print");
//
//      m_puserinteraction->_000CallOnDraw(pgraphics);
//
//   }
//
//
//   void prototype_impl::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      if (m_puserinteraction)
//      {
//
//         m_puserinteraction->_000CallOnDraw(pgraphics);
//
//      }
//
//   }
//
//
//   void prototype_impl::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      if (m_puserinteraction)
//      {
//
//         m_puserinteraction->_001DrawThis(pgraphics);
//
//      }
//
//   }
//
//
//   void prototype_impl::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      if (m_puserinteraction)
//      {
//
//         m_puserinteraction->_001DrawChildren(pgraphics);
//
//      }
//
//   }
//
//
//   void prototype_impl::draw_control_background(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      if (m_puserinteraction)
//      {
//
//         m_puserinteraction->draw_control_background(pgraphics);
//
//      }
//
//   }


   void prototype_impl::set_origin(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void prototype_impl::viewport_client_to_screen(::int_sequence2 & sequence)
   {

      if (m_puserinteraction)
      {

         ::add(sequence, m_puserinteraction->const_layout().design().origin());

      }

   }


   void prototype_impl::viewport_screen_to_client(::int_sequence2 & sequence)
   {

      if (m_puserinteraction)
      {

         ::subtract(sequence, m_puserinteraction->const_layout().design().origin());

      }

   }


   void prototype_impl::viewport_client_to_screen(::int_rectangle & rectangle)
   {

      viewport_client_to_screen(rectangle.top_left());

      viewport_client_to_screen(rectangle.bottom_right());

   }


   void prototype_impl::viewport_screen_to_client(::int_rectangle & rectangle)
   {

      viewport_screen_to_client((::int_point &)rectangle.left);
      viewport_screen_to_client((::int_point &)rectangle.right);

   }


   void prototype_impl::post_message(::message::message* pmessage)
   {

      if (!m_puserinteraction)
      {

         throw ::exception(error_wrong_state);

      }

      m_puserinteraction->post_message(pmessage);

   }


   void prototype_impl::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource)
   {


   }


   void prototype_impl::clear_bitmap_source()
   {


   }


   void prototype_impl::set_tool_window(bool bSet)
   {


   }


   void prototype_impl::interaction_post(const ::procedure& procedure)
   {


   }


   void prototype_impl::_000OnMouseLeave(::message::message* pmessage)
   {


   }


   void prototype_impl::track_mouse_hover()
   {


   }


   void prototype_impl::track_mouse_leave()
   {


   }


//   void prototype_impl::add_fps_interest(::particle * pparticle)
//   {
//
//
//   }
//
//
//   void prototype_impl::erase_fps_interest(::particle * pparticle)
//   {
//
//
//   }
//
//
//   bool prototype_impl::is_fps_interest(const ::particle * pparticle) const
//   {
//
//      return false;
//
//   }


//   void prototype_impl::fps_interest_stop()
//   {
//
//
//   }


   ::user::interaction_base* prototype_impl::set_owner(::user::interaction_base* pprimitiveOwner)
   {

      return nullptr;

   }


   bool prototype_impl::has_pending_redraw_flags()
   {

      return false;

   }


   void prototype_impl::add(::graphics::output_purpose * poutputpurpose)
   {



   }


   void prototype_impl::erase(::graphics::output_purpose * poutputpurpose)
   {



   }



   void prototype_impl::add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose)
   {


   }



   void prototype_impl::erase_graphical_output_purpose(::particle * pparticle)
   {


   }


   bool prototype_impl::does_particle_has_fps_purpose(const ::particle * pparticle) const
   {

      return false;

   }


//   ::graphics::enum_output_purpose prototype_impl::most_demanding_graphical_output_purpose() const
//   {
//
//      return ::graphics::e_output_purpose_none;
//
//   }


   bool prototype_impl::has_screen_output_purpose() const
   {

      return false;

   }


   bool prototype_impl::has_graphical_output_purpose() const
   {

      return false;

   }


//   bool prototype_impl::has_graphical_output_purpose() const
//   {
//
//      return false;
//
//   }


   bool prototype_impl::has_fps_output_purpose() const
   {

      return false;

   }



//   bool prototype_impl::has_graphical_output_purpose() const
//   {
//
//      return false;
//
//   }


   void prototype_impl::pre_subclass_window()
   {


   }


   //void prototype_impl::destroy_impl_only()
   //{


   //}


   //void prototype_impl::start_destroying_window()
   //{


   //}


   void prototype_impl::destroy_window()
   {


   }


   bool prototype_impl::_is_window()
   {

      return false;

   }


   lresult prototype_impl::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point& point)
   {

      return message_call(emessage, wparam, lparam, point);

   }


   lresult prototype_impl::send_message(::message::message * pmessage)
   {

      return message_call(pmessage);

   }


#define _NEW_MESSAGE(TYPE) \
   auto pmessage = øcreate_new<TYPE>(); \
   pmessage->m_pchannel = this; \
   pmessage->m_pacmewindowingwindow = oswindow; \
   pmessage->m_pwindow = pwindow; \
   pmessage->m_emessage = atom; \
   pmessage->m_wparam = wparam; \
   pmessage->m_lparam = lparam; \
   pmessageBase = pmessage


//#define _NEW_MESSAGE(TYPE) \
//   auto pmessage = øcreate_new<TYPE>(); \
//   pmessage->m_pchannel = this; \
//   pmessage->m_emessage = atom; \
//   pmessage->m_wparam = wparam; \
//   pmessage->m_lparam = lparam; \
//   pmessageBase = pmessage


   ::pointer<::message::message>prototype_impl::get_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, ::message::enum_prototype eprototype)
   {

      ::pointer<::message::message>pmessageBase;

      if (eprototype == ::message::e_prototype_none)
      {

         eprototype = ::message::get_message_prototype(atom.as_emessage(), 0);

      }

      auto pwindow = this->window();

      auto oswindow = pwindow ? pwindow->oswindow() : nullptr;

      switch (eprototype)
      {
      case ::message::e_prototype_none:
      {

         _NEW_MESSAGE(::user::message);

      }
      break;
      case ::message::e_prototype_create:
      {
         _NEW_MESSAGE(::message::create);

      }
      break;
      case ::message::e_prototype_enable:
      {
         _NEW_MESSAGE(::message::enable);

      }
      break;
      case ::message::e_prototype_non_client_activate:
      {
         _NEW_MESSAGE(::message::nc_activate);
         {

            //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);

            pmessage->m_bActive = wparam != false;

         }
      }
      break;
      case ::message::e_prototype_key:
      {
         _NEW_MESSAGE(::message::key);
         //void key::set(::acme::windowing::window * pacmewindowingwindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
         {

            // ::user::message::set(oswindow, pwindow, emessage, wparam, lparam);

            pmessage->m_nChar = static_cast<unsigned int>(wparam);

            pmessage->m_nRepCnt = lower_unsigned_short(lparam);

            pmessage->m_nFlags = upper_unsigned_short(lparam);

            pmessage->m_iVirtualKey = (int)wparam;

            pmessage->m_nScanCode = ((lparam >> 16) & 0xff);

            pmessage->m_bExt = (lparam & (1 << 24)) != 0;

         }

      }
      break;
      case ::message::e_prototype_timer:
      {

         //throw ::exception(::exception("do not use ::user::e_message_timer or Windows set_timer/kill_timer"));

         _NEW_MESSAGE(::message::timer);

         pmessage->m_uTimer = static_cast<unsigned int>(wparam);

      }
      break;
      case ::message::e_prototype_show_window:
      {
         _NEW_MESSAGE(::message::show_window);
         pmessage->m_bShow = wparam != false;

         pmessage->m_nStatus = static_cast<unsigned int>(lparam);

      }
      break;
      case ::message::e_prototype_set_cursor:
      {
         _NEW_MESSAGE(::message::set_cursor);
      }
      break;
      case ::message::e_prototype_non_client_hit_test:
      {
         _NEW_MESSAGE(::message::nc_hit_test);
         pmessage->m_point.x = lparam_int_x(lparam);

         pmessage->m_point.y = lparam_int_y(lparam);
      }
      break;
      case ::message::e_prototype_move:
      {
         _NEW_MESSAGE(::message::reposition);
         pmessage->m_point = lparam.point();
      }
      break;
      case ::message::e_prototype_erase_background:
      {
         _NEW_MESSAGE(::message::erase_bkgnd);
      }
      break;
      case ::message::e_prototype_scroll:
      {
         _NEW_MESSAGE(::message::scroll);

#ifdef WINDOWS_DESKTOP
         pmessage->m_oswindowScrollBar = (::oswindow)(::iptr)(lparam);
         
#endif

         //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);

         pmessage->m_ecommand = (enum_scroll_command)(short)lower_unsigned_short(wparam);

         pmessage->m_dPosition = (double) (short)upper_unsigned_short(wparam);

      }
      break;
      case ::message::e_prototype_set_focus:
      {
         _NEW_MESSAGE(::message::set_keyboard_focus);
      }
      break;
      case ::message::e_prototype_kill_focus:
      {
         _NEW_MESSAGE(::message::kill_keyboard_focus);
         pmessage->m_oswindowNew = (::oswindow)wparam.m_number;
      }
      break;
#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__) && !defined(__BSD__)
      case ::message::e_prototype_window_pos:

      {
         _NEW_MESSAGE(::message::window_pos);
         pmessage->m_pWINDOWPOS = reinterpret_cast<void *>(lparam.m_lparam);
      }
      break;
      case ::message::e_prototype_non_client_calc_size:
      {
         _NEW_MESSAGE(::message::nc_calc_size);
         pmessage->m_pNCCALCSIZE_PARAMS = reinterpret_cast<void *>(lparam.m_lparam);
      }
      break;
#endif
      case ::message::e_prototype_mouse:
      {
         _NEW_MESSAGE(::message::mouse);
         pmessage->m_ebuttonstate = (::user::enum_button_state ) wparam.m_number;

//         if ((pmessage->m_ebuttonstate & I32_MINIMUM) == (I32_MINIMUM))
//         {
//
//            informationf("(m_ebuttonstate & I32_MINIMUM) == (I32_MINIMUM)");
//
//         }

         pmessage->m_pointHost = lparam.point();

         pmessage->m_pointAbsolute = lparam.point();

         _raw_client_to_screen(pmessage->m_pointAbsolute);

      }
      break;
      case ::message::e_prototype_object:
      {
         _NEW_MESSAGE(::message::particle);
         //void particle::set(::acme::windowing::window * pacmewindowingwindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
         {

            //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);

            ::particle_pointer pparticle(lparam);

            pmessage->m_pparticle = pparticle;

            pmessage->m_lparam = 0;

         }
      }
      break;
      case ::message::e_prototype_mouse_wheel:
      {
         _NEW_MESSAGE(::message::mouse_wheel);

         pmessage->m_ebuttonstate = (::user::enum_button_state) lower_unsigned_short(wparam);

         pmessage->m_pointAbsolute = lparam.point();

         pmessage->m_Δ = upper_short(wparam);

         pmessage->m_pointHost = pmessage->m_pointAbsolute;

         _raw_screen_to_client(pmessage->m_pointHost);

      }
      break;
      case ::message::e_prototype_size:
      {
         _NEW_MESSAGE(::message::size);

         pmessage->m_nType = static_cast <unsigned int> (wparam);

         pmessage->m_size = ::int_size(lparam_int_x(lparam), lparam_int_y(lparam));
      }
      break;
      case ::message::e_prototype_activate:
      {
         _NEW_MESSAGE(::message::activate);
         //pmessage = p;
         //default_set(pmessage, emessage, wparam, lparam)
         //void activate::set(::acme::windowing::window * pacmewindowingwindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
         //{

            //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);

         pmessage->m_eactivate = (enum_activate)(lower_unsigned_short(wparam));

         if (lparam == 0)
         {

            pmessage->m_pWndOther = nullptr;

         }
         else
         {

            auto paurasession = m_papplication->m_psession;

            auto puser = paurasession->m_puser;

            auto pwindowing = system()->windowing();

            pmessage->m_pWndOther = __interaction(pwindowing->window(lparam.raw_cast <::oswindow>()));

         }

         pmessage->m_bMinimized = upper_unsigned_short(wparam) != false;

         //}

      }
      break;
      case ::message::e_prototype_mouse_activate:
      {
         _NEW_MESSAGE(::message::mouse_activate);
      }
      break;
      default:
      {
         
         auto pmessage = ::channel::get_message(emessage, wparam, lparam, eprototype);
         
         pmessageBase = pmessage;

      }
      break;
      }

      if (pmessageBase.is_null())
      {

         return nullptr;

      }

      //auto estatus =




      //if (!estatus)
      //{

      //   return nullptr;

      //}

      return pmessageBase;

   }



   //void prototype_impl::post_message(const ::atom& atom, ::wparam wParam, ::lparam lParam)
   //{


   //}


//   void prototype_impl::set_window_text(const ::scoped_string & scopedstrString)
//   {
//
//
//   }


   void prototype_impl::on_set_window_text()
   {


   }

//   character_count prototype_impl::get_window_text(char* pszStringBuf, character_count nMaxCount)
//   {
//
//      return 0;
//
//   }


//   void prototype_impl::get_window_text(string& rString)
//   {
//
//
//   }


//   character_count prototype_impl::get_window_text_length()
//   {
//
//      return 0;
//
//   }


   //void prototype_impl::UpdateWindow()
   //{


   //}


   //void prototype_impl::SetRedraw(bool bRedraw)
   //{


   //}


//   void prototype_impl::graphics_thread_redraw(bool bUpdateBuffer)
//   {
//
//
//   }


   void prototype_impl::set_mouse_cursor(::windowing::cursor* pcursor)
   {


   }


   ::user::interaction* prototype_impl::ChildWindowFromPoint(const ::int_point& point)
   {

      return nullptr;

   }


   ::user::interaction* prototype_impl::ChildWindowFromPoint(const ::int_point& point, unsigned int nFlags)
   {

      return nullptr;

   }


   ::user::interaction* prototype_impl::GetLastActivePopup()
   {

      return nullptr;

   }


   void prototype_impl::update_data(bool bSaveAndValidate)
   {


   }


   void prototype_impl::CenterWindow(::user::interaction* pAlternateOwner)
   {


   }


   bool prototype_impl::OnChildNotify(::message::message* pusermessage)
   {

      return false;

   }


   void prototype_impl::ActivateTopParent()
   {


   }


   void prototype_impl::_001UpdateWindow()
   {


   }


   void prototype_impl::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {


   }


   void prototype_impl::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {


   }


   void prototype_impl::on_configuration_change(::user::interaction_base* pprimitiveSource)
   {


   }


   //::user::element* prototype_impl::get_keyboard_focus()
   //{

   //   return nullptr;

   //}

   
   void prototype_impl::_001OnAfterExitIconic()
   {

   }


   void prototype_impl::_001OnAfterExitNormal()
   {

   }


   void prototype_impl::_001OnAfterExitZoomed()
   {


   }


   void prototype_impl::_001OnAfterExitFullScreen()
   {


   }


   void prototype_impl::default_message_handler(::message::message * pmessage)
   {


   }


//   void prototype_impl::_001OnTriggerMouseInside()
//   {
//
//
//   }


   bool prototype_impl::has_pending_graphical_update()
   {

      return false;

   }


   void prototype_impl::on_after_graphical_update()
   {


   }


   bool prototype_impl::is_this_visible(enum_layout elayout)
   {

      return false;

   }


   void prototype_impl::post_redraw(bool bAscendants)
   {



   }


   double prototype_impl::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      return 0.;

   }


//   ::windowing::window* prototype_impl::get_window() const
//   {
//
//      return nullptr;
//
//   }


   bool prototype_impl::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      return false;

   }


   bool prototype_impl::keyboard_focus_OnChildKillFocus()
   {

      return false;

   }


   void prototype_impl::edit_on_set_focus(::user::interaction* pinteraction)
   {


   }


   void prototype_impl::edit_on_kill_focus(::user::interaction* pinteraction)
   {


   }


   void prototype_impl::show_software_keyboard(::user::element * pelement)
   {
      
      throw interface_only();
      
   }


   void prototype_impl::hide_software_keyboard(::user::element * pelement)
   {
   
      throw interface_only();
   
   }


   ::user::interaction* prototype_impl::get_child_by_id(const ::atom& atom, ::collection::index iItem, int iLevel)
   {

      return nullptr;

   }


   void prototype_impl::set_need_redraw(const ::int_rectangle_array & rectangleaNeedRedraw, function<void()> function, bool bAscendants)
   {


   }


   void prototype_impl::RedrawWindow(const ::int_rectangle & rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
   {

      if (!m_puserinteraction)
      {

         //return false;

         return;

      }

      return m_puserinteraction->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   }


   //unsigned int prototype_impl::GetStyle() const
   //{

   //   return get_window_long(GWL_STYLE);

   //}


   //unsigned int prototype_impl::GetExStyle() const
   //{

   //   return get_window_long(GWL_EXSTYLE);

   //}


   //void prototype_impl::ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   int l = GetStyle();

   //   l |= dwAdd;

   //   int lRemove = ~dwRemove;

   //   l &= lRemove;

   //   set_window_long(GWL_STYLE, l);

   //   return true;

   //}


   //void prototype_impl::ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   set_window_long(GWL_EXSTYLE, (GetExStyle() | dwAdd) & ~dwRemove);

   //   return true;

   //}


//   int prototype_impl::get_window_long(int nIndex) const
//   {
//
//      return (int)get_window_long_ptr(nIndex);
//
//   }
//
//
//   int prototype_impl::set_window_long(int nIndex, int lValue)
//   {
//
//      return (int)set_window_long_ptr(nIndex, lValue);
//
//   }
//
//
//   iptr prototype_impl::get_window_long_ptr(int nIndex) const
//   {
//
////      return 0;
//////
//////      if (nIndex == GWL_STYLE)
//////      {
//////
//////         return  m_uStyle;
//////
//////      }
//////      else if (nIndex == GWL_EXSTYLE)
//////      {
//////
//////         return  m_uExStyle;
//////
//////      }
//////
//////      synchronous_lock synchronouslock(&((prototype_impl *)this)->m_pmutexLongPtr);
//////
//////      return (LONG_PTR)m_longptr[nIndex];
////
//      return m_iptrmap[nIndex];
//
//   }
//
//
//   void prototype_impl::set_window_long_ptr(int nIndex, iptr lValue)
//   {
//
////      if (nIndex == GWL_STYLE)
////      {
////
////         return m_uStyle = lValue;
////
////      }
////      else if (nIndex == GWL_EXSTYLE)
////      {
////
////         return m_uExStyle = lValue;
////
////      }
////
////      synchronous_lock synchronouslock(m_pmutexLongPtr, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
////
////      m_longptr[nIndex] = lValue;
////
////      return lValue;
//
//      //return lValue;
//
//      return m_iptrmap[nIndex] = lValue;
//
//   }


   atom prototype_impl::GetDlgCtrlId() const
   {

      if (!m_puserinteraction)
      {

         return ::atom::e_type_null;

      }

      return m_puserinteraction->GetDlgCtrlId();

   }


   atom prototype_impl::SetDlgCtrlId(atom atom)
   {

      if (!m_puserinteraction)
      {

         return atom::e_type_null;

      }

      return m_puserinteraction->SetDlgCtrlId(atom);

   }



   ::user::interaction * prototype_impl::first_child()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->first_child();

   }


   ::user::interaction * prototype_impl::top_child()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->first_child();

   }


   ::user::interaction * prototype_impl::under_sibling()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->under_sibling();

   }


   ::user::interaction * prototype_impl::above_sibling()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->above_sibling();

   }


   ::user::interaction * prototype_impl::above_sibling(::user::interaction * pinteraction)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->above_sibling(pinteraction);

   }


   ::user::interaction * prototype_impl::under_sibling(::user::interaction * pinteraction)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->under_sibling(pinteraction);

   }


   unsigned int prototype_impl::ArrangeIconicWindows()
   {

      //      return m_puserinteraction->ArrangeIconicWindows();
      return 0;

   }


   bool prototype_impl::is_ascendant(::user::element * puiIsAscendant, bool bIncludeSelf)
   {

      if (::is_null(puiIsAscendant))
      {

         return false;

      }

      return puiIsAscendant->is_descendant(m_puserinteraction, bIncludeSelf);

   }


   bool prototype_impl::is_parent(::user::element * puiIsParent)
   {

      if (puiIsParent == nullptr)
      {

         return false;

      }

      return puiIsParent->is_child(m_puserinteraction);

   }


   bool prototype_impl::is_child(::user::element * puiIsChild)
   {

      if (puiIsChild == nullptr)
      {

         return false;

      }

      ::user::interaction * puiProbe = puiIsChild->get_parent();

      return puiProbe == m_puserinteraction;

   }


   bool prototype_impl::is_descendant(::user::element * puiIsDescendant, bool bIncludeSelf)
   {

      ::user::element * puiProbe;

      if (bIncludeSelf)
      {

         puiProbe = puiIsDescendant;

      }
      else
      {

         puiProbe = puiIsDescendant->get_parent();

      }

      if (::is_null(puiProbe))
      {

         return false;

      }

      do
      {

         if (puiProbe == m_puserinteraction.m_p)
         {

            return true;

         }

         puiProbe = puiProbe->get_parent();

      } while (puiProbe != nullptr);

      return false;

   }


   ::user::interaction * prototype_impl::get_wnd()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_wnd();

   }


   ::user::interaction * prototype_impl::get_wnd(unsigned int nCmd)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_wnd(nCmd);

   }


   //::user::interaction * prototype_impl::GetTopWindow() const
   //{

   //   auto pinteraction = get_wnd();

   //   if (!pinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetTopWindow();

   //}


   ::user::interaction * prototype_impl::get_parent()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent();

   }


   ::user::interaction * prototype_impl::get_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->m_puserinteractionOwner;

   }


   ::user::frame_interaction * prototype_impl::frame()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->frame();

   }


   //::user::frame_interaction * prototype_impl::get_parent_frame() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteraction->parent_frame();

   //}


   ::user::interaction * prototype_impl::get_parent_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_owner();

   }


   ::user::interaction * prototype_impl::get_parent_or_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_or_owner();

   }


   ::user::interaction * prototype_impl::get_top_level_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_top_level_owner();

   }


   ::user::frame_interaction * prototype_impl::top_level_frame()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->top_level_frame();

   }


   //::user::interaction * prototype_impl::get_top_level() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteraction->top_level();

   //}


   void prototype_impl::message_handler(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      // if (::is_null(m_puserinteraction))
      // {

      //    throw ::exception(error_wrong_state);

      // }

      // m_puserinteraction->interaction_post(øallocate call_message_handler_task(m_puserinteraction, emessage, wparam, lparam));

      //auto pmessage

      //get_message()

      ::pointer<::message::message>pmessage;

      if (m_puserinteraction)
      {

         pmessage = m_puserinteraction->get_message(emessage, wparam, lparam);

      }
      else
      {

         pmessage = get_message(emessage, wparam, lparam);

      }

      pmessage->m_pchannel = this;

      //return message_call(pmessage);

      message_handler(pmessage);

   }


   lresult prototype_impl::message_call(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point& point)
   {

      ::pointer<::message::message>pmessage;

      if (m_puserinteraction)
      {

         pmessage = m_puserinteraction->get_message(emessage, wparam, lparam);

      }
      else
      {

         pmessage = get_message(emessage, wparam, lparam);

      }

      pmessage->m_pchannel = m_puserinteraction;

      return message_call(pmessage);

   }


   lresult prototype_impl::message_call(::message::message * pmessage)
   {

      if (m_puserinteraction == nullptr)
      {

         message_handler(pmessage);

         return pmessage->m_lresult;

      }

      if (m_puserinteraction->layout().is_moving())
      {
         
         informationf("moving: skip walk pre translate tree");

      }
      else if (m_puserinteraction->layout().is_sizing())
      {
         
         informationf("sizing: skip walk pre translate tree");

      }
      else
      {

         m_puserinteraction->walk_pre_translate_tree(pmessage);

         if (pmessage->m_bRet)
         {

            return pmessage->m_lresult;

         }

      }

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   void prototype_impl::send_message_to_descendants(::enum_message emessage, ::wparam wparam, ::lparam lparam, bool bDeep, bool bOnlyPerm)
   {

      return m_puserinteraction->send_message_to_descendants(emessage, wparam, lparam, bDeep, bOnlyPerm);

   }


   void prototype_impl::pre_translate_message(::message::message * pmessage)
   {

      m_puserinteraction->pre_translate_message(pmessage);

   }


   //void prototype_impl::set_capture(::user::interaction * pinteraction)
   //{

   //   return get_host_user_interaction()->set_capture(pinteraction);

   //}


   //::user::interaction * prototype_impl::get_capture() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_capture();

   //}


   //void prototype_impl::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return get_host_user_interaction()->set_keyboard_focus(pinteraction);

   //}


   //::user::interaction * prototype_impl::get_keyboard_focus() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_keyboard_focus();

   //}


   void prototype_impl::get_rect_normal(::int_rectangle * prectangle)
   {

      *prectangle = m_puserinteraction->screen_rectangle();

   }


   void prototype_impl::set_timer(uptr uEvent, const class ::time & timeEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void* pdata)
   {

      if (timeEllapse < 500_ms)
      {

         //         string str;
         //
         //         str.formatf("creating fast timer: %d\n", nEllapse);
         //
         //         ::information(str);

      }

      if (m_ptimerarray.is_null())
      {

         øconstruct_new(m_ptimerarray);

         m_ptimerarray->m_pcallback = m_puserinteraction;

         //m_ptimerarray->set_context_thread(m_puserinteraction->m_pthreadUserInteraction);

      }

      m_ptimerarray->create_timer(this, uEvent, timeEllapse, pfnTimer, bPeriodic, pdata);

   }


   void prototype_impl::kill_timer(uptr uEvent)
   {

      if (m_ptimerarray.is_null())
      {

         return;

      }

      m_ptimerarray->delete_timer(uEvent);

   }


   void prototype_impl::on_timer(::timer * ptimer)
   {

      if (m_puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteraction->on_timer(ptimer);

   }


   //void prototype_impl::defer_start_fps_interest()
   //{

   //   m_puserinteraction->post_simple_command(e_simple_command_defer_start_fps_interest);

   //}


   //void prototype_impl::_defer_start_fps_interest()
   //{

   //}

   void prototype_impl::destroy_impl_only()
   {

      auto pinteraction = m_puserinteraction;

      m_bDestroyImplOnly = true;

      if (::is_set(m_puserinteraction))
      {

//         m_puserinteraction->transfer_receiver(m_idroute, this);
//
         auto puserinteraction = m_puserinteraction->get_wnd();

         if (::is_set(puserinteraction))
         {

            auto pwindow = puserinteraction->m_pinteractionimpl;

            if (pwindow)
            {

               synchronous_lock synchronouslock(pwindow->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

               pwindow->m_userinteractionaMouseHover.erase(m_puserinteraction);

            }

         }

         m_puserinteraction->m_puserinteractionParent = nullptr;

      }

      m_puserinteraction = nullptr;

      start_destroying_window();

      //informationf("destroy_impl_only DestroyWindow %d", bOk != false);

      //return bOk;

   }


   void prototype_impl::start_destroying_window()
   {

      if (!m_bUserImplCreated)
      {

         return;

      }

      m_bUserImplCreated = false;

      if (m_puserinteraction == nullptr && !m_bDestroyImplOnly)
      {

         return;

      }

      ::pointer<::user::prototype_impl>pimplThis = this;

      ::pointer<::user::interaction>puiThis = m_puserinteraction;

      if(puiThis)
      {

         try
         {

            puiThis->send_message(::user::e_message_destroy);

         }
         catch (...)
         {

         }

         try
         {

            puiThis->send_message(::user::e_message_non_client_destroy);

         }
         catch (...)
         {

         }

      }

      //return true;

   }


   void prototype_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      auto puserinteraction = m_puserinteraction;

      if (!puserinteraction)
      {

         return;

      }

      ::user::interaction * pinteraction = puserinteraction->get_host_user_interaction();

      if (!pinteraction)
      {

         //return false;

         return;

      }

      //auto bOk = 
      
      pinteraction->mouse_hover_add(pinterface);

      //if (!bOk)
      //{

      //   return false;

      //}

      //return true;

   }


   bool prototype_impl::mouse_hover_erase(::user::interaction * pinterface)
   {

      auto puserinteraction = m_puserinteraction;

      if (!puserinteraction)
      {

         return false;

      }

      ::user::interaction * pinteraction = puserinteraction->get_host_user_interaction();

      if (pinteraction != nullptr)
      {

         return pinteraction->mouse_hover_erase(pinterface);

      }

      return false;

   }


   void prototype_impl::register_drop_target()
   {

   }


//   ::windowing::window* prototype_impl::window()
//   {
//
//      auto puserinteraction = m_puserinteraction;
//
//      if (!puserinteraction)
//      {
//
//         return nullptr;
//
//      }
//
//      auto pwindow = puserinteraction->window();
//
//      if (!pwindow)
//      {
//
//         return nullptr;
//
//      }
//
//      return pwindow;
//
//   }


   ::user::element * prototype_impl::get_keyboard_focus()
   {

      return nullptr;

   }


   void prototype_impl::set_keyboard_focus(::user::prototype_impl * pprimitiveimpl)
   {

      __UNREFERENCED_PARAMETER(pprimitiveimpl);

      //return ::error_failed;

   }


   //void prototype_impl::erase_keyboard_focus(::user::prototype_impl * pprimitiveimpl)
   //{

   //   __UNREFERENCED_PARAMETER(pprimitiveimpl);

   //}


   void prototype_impl::aaa_clear_keyboard_focus(::user::prototype_impl * pprimitiveimplGainingFocusIfAny)
   {


   }


   void prototype_impl::impl_set_keyboard_focus(::user::prototype_impl * pprimitiveimpl)
   {


   }


   void prototype_impl::impl_erase_keyboard_focus(::user::prototype_impl * pprimitiveimpl)
   {


   }


   void prototype_impl::aaa_impl_clear_keyboard_focus()
   {


   }


   void prototype_impl::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      // if (::is_null(m_puserinteraction))
      // {

      //    throw ::exception(error_wrong_state);

      // }

      // m_puserinteraction->interaction_post(øallocate call_message_handler_task(m_puserinteraction, emessage, wparam, lparam));

      //auto pmessage

      //get_message()

      ::pointer<::message::message>pmessage;

      if (m_puserinteraction)
      {

         pmessage = m_puserinteraction->get_message(emessage, wparam, lparam);

      }
      else
      {

         pmessage = get_message(emessage, wparam, lparam);

      }

      pmessage->m_pchannel = m_puserinteraction;

      //return message_call(pmessage);

      post_message(pmessage);

   }


   void prototype_impl::post_non_client_destroy()
   {

      ::pointer<prototype_impl>pimpl = this;

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         try
         {

            erase_all_routes();

         }
         catch (...)
         {

         }

      }

      //::channel::on_finish();

      if (!m_bDestroyImplOnly && m_puserinteraction)
      {

         m_puserinteraction->post_non_client_destroy();

      }

      //::user::prototype_impl::post_non_client_destroy();



      //if (m_puserinteraction->m_pthreadUserInteraction)
      //{

      //   auto pthread = m_puserinteraction->m_pthreadUserInteraction.cast < thread >();
      //
      //   if (pthread)
      //   {

      //      if (pthread->m_pimpl == this)
      //      {

      //         pthread->m_pimpl.release();

      //         pthread->finish();

      //      }

      //   }

      //}

      if (!m_bDestroyImplOnly)
      {

         m_puserinteraction.release();

      }

   }


   void prototype_impl::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      //if (m_puserinteraction)
      //{

      //   m_puserinteraction->set_need_redraw();

      //}

   }


   void prototype_impl::_001OnPrioCreate(::message::message * pmessage)
   {

      if (!m_puserinteraction)
      {

         return;

      }

//      if(::is_null(m_puserinteraction->m_pwindow))
//      {
//
//         printf("m_puserinteraction->m_pwindow is null!! (8) (0x%" PRI0xPTR ")\n", (uptr) m_puserinteraction->m_pwindow);
//
//      }
//      else
//      {
//
//         printf("m_puserinteraction->m_pwindow is set!! (8) (0x%" PRI0xPTR ")\n", (uptr) m_puserinteraction->m_pwindow);
//
//      }
//
//      fflush(stdout);

      m_puserinteraction->defer_run_property(id_create);

//      if(::is_null(m_puserinteraction->m_pwindow))
//      {
//
//         printf("m_puserinteraction->m_pwindow is null!! (9) (0x%" PRI0xPTR ")", (uptr) m_puserinteraction->m_pwindow);
//
//      }
//      else
//      {
//
//         printf("m_puserinteraction->m_pwindow is set!! (9) (0x%" PRI0xPTR ")", (uptr) m_puserinteraction->m_pwindow);
//
//      }
//
//      fflush(stdout);

      //m_puserinteraction->call_procedures(CREATE_ROUTINE);

//      if(::is_null(m_puserinteraction->m_pwindow))
//      {
//
//         printf("m_puserinteraction->m_pwindow is null!! (10) (0x%" PRI0xPTR ")", (uptr) m_puserinteraction->m_pwindow);
//
//      }
//      else
//      {
//
//         printf("m_puserinteraction->m_pwindow is set!! (10) (0x%" PRI0xPTR ")", (uptr) m_puserinteraction->m_pwindow);
//
//      }
//
//      fflush(stdout);


   }


   void prototype_impl::on_message_destroy(::message::message * pmessage)
   {

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //try
      //{

      //   if (m_ptimerarray)
      //   {

      //      m_ptimerarray->destroy();

      //      m_ptimerarray.release(REFERENCING_DEBUGGING_THIS_NOTE(""));

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   void prototype_impl::on_message_non_client_destroy(::message::message * pmessage)
   {

      if (m_puserinteraction && ::platform::type(m_puserinteraction).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

      post_non_client_destroy();

   }


   void prototype_impl::prio_install_message_routing(::channel * pchannel)
   {

      //if (g_p == nullptr)
      //{

      //   g_p = aaa_memory_new iptr_map < string >;

      //}

      //g_p->set_at((iptr)this, ::type(m_puserinteraction).name()) + "xxx" + ::type(this).name();
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &prototype_impl::on_message_show_window);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &prototype_impl::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_non_client_destroy, pchannel, this, &prototype_impl::on_message_non_client_destroy);
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &prototype_impl::_001OnPrioCreate);

      if (m_puserinteraction && ::platform::type(m_puserinteraction).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

   }


   void prototype_impl::last_install_message_routing(::channel * pchannel)
   {


   }


   void prototype_impl::show_task(bool bShow)
   {

      __UNREFERENCED_PARAMETER(bShow);

   }


   void prototype_impl::redraw_add(::particle * pparticle)
   {

   }


   void prototype_impl::redraw_erase(::particle * pparticle)
   {

   }


   bool prototype_impl::has_redraw()
   {

      return false;

   }


   void prototype_impl::queue_message_handler(::message::message * pmessage)
   {

      m_puserinteraction->message_handler(pmessage);

      //if (pmessage->m_bRet)
      //{

      //   return true;

      //}

      //return false;

   }


   //void prototype_impl::has_keyboard_focus() const
   //{

   //   if (m_puserinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   ::pointer<::user::interaction>pinteraction = m_puserinteraction->get_host_user_interaction();

   //   if (pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   if (pinteraction == this)
   //   {

   //      return false;

   //   }

   //   if (!pinteraction->has_keyboard_focus())
   //   {

   //      return false;

   //   }

   //   ::pointer<::windowing::window>pimpl = pinteraction->m_pimpl;

   //   if (pimpl.is_null())
   //   {

   //      return false;

   //   }

   //   return pimpl->m_pprimitiveFocus == m_puserinteraction;

   //}


   //void prototype_impl::is_active()
   //{

   //   if (m_puserinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_puserinteraction == m_puserinteraction->GetActiveWindow();

   //}


   //void prototype_impl::create_host(::user::interaction * puserinteraction, enum_parallelization eparallelization)
   void prototype_impl::create_host(::user::interaction * puserinteraction)
   {

      //return false;

   }


   void prototype_impl::create_child(::user::interaction * puserinteraction, ::user::interaction_base * puserprimitiveParent)
   {

      //return false;

   }


   //void prototype_impl::is_this_enabled() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return false;

   //   }

   //   return m_puserinteraction->m_ewindowflag & e_window_flag_enable;

   //}


   // void prototype_impl::SetWindowDisplayChanged()
   // {

   // }


//   void prototype_impl::_window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation)
//   {
//
//   }
//
//
//   void prototype_impl::_window_show_change_visibility_locked()
//   {
//
//   }
//
//
//   void prototype_impl::_window_request_presentation_locked()
//   {
//
//   }
//
//
//   void prototype_impl::_window_request_presentation_unlocked()
//   {
//
//   }


   void prototype_impl::enable_window(bool bEnable)
   {

      //bool bWasDisabled = !(m_puserinteraction->m_ewindowflag & e_window_flag_enable);

      m_puserinteraction->m_ewindowflag.set(e_window_flag_enable, bEnable);

      m_puserinteraction->set_need_redraw();

      m_puserinteraction->post_redraw();

      //return bWasDisabled;

   }


   void prototype_impl::user_interaction_on_hide()
   {


   }


   //int prototype_impl::GetUpdateRgn(class draw2d::region *,bool)
   //{

   //   return 0;

   //}


   //void prototype_impl::Invalidate(bool)
   //{


   //}


   //void prototype_impl::InvalidateRect(::int_rectangle const &,bool)
   //{


   //}


   //void prototype_impl::InvalidateRgn(class draw2d::region *,bool)
   //{


   //}


   //void prototype_impl::ValidateRect(::int_rectangle const &)
   //{


   //}


   //void prototype_impl::ValidateRgn(class draw2d::region *)
   //{


   //}


   //void prototype_impl::ShowOwnedPopups(bool)
   //{


   //}


   ::graphics::graphics * prototype_impl::get_window_graphics(void)
   {

      return nullptr;

   }


   bool prototype_impl::is_composite()
   {

      return false;

   }

   
   void prototype_impl::_task_transparent_mouse_event()
   {

   }


   bool prototype_impl::IsTopParentActive()
   {

      return false;

   }


#ifdef LINUX


   lresult prototype_impl::send_x11_event(void * phappening)
   {

      throw interface_only();

      return 0;

   }


#endif


   ::user::interaction * prototype_impl::top_level()
   {
      
      return m_puserinteraction->top_level();

   }


   ::user::frame_interaction * prototype_impl::parent_frame()
   {
      
      return m_puserinteraction->parent_frame();

   }


   ::windowing::window* prototype_impl::window()
   {

      if (::is_null(m_puserinteraction))
      {

         return nullptr;

      }

      return m_puserinteraction->m_pwindow;

   }


   ::aura::application * prototype_impl::get_app()
   {

      return m_papplication ? m_papplication->m_papplication : nullptr;

   }


   ::aura::session * prototype_impl::get_session()
   {

      return m_papplication ? m_papplication->m_psession : nullptr;

   }


   //::aura::system * prototype_implacmesystem()
   //{

   //   return system() ? system() : nullptr;

   //}

   void prototype_impl::_raw_client_to_screen(::int_point & point)
   {

      m_puserinteraction->client_to_screen(e_layout_design)(point);

   }

   void prototype_impl::_raw_screen_to_client(::int_point& point)
   {

      m_puserinteraction->screen_to_client(e_layout_design)(point);

   }

   ::trace_statement & prototype_impl::trace_statement_prefix(::trace_statement & statement) const
   {

      statement << "usrimpl ";

      if(m_puserinteraction)
      {

         m_puserinteraction->raw_trace_statement_prefix(statement);

      }

      return statement;

   }

   
   void prototype_impl::user_send(const ::procedure & procedure)
   {

      if (!m_puserinteraction)
      {

         ::channel::user_send(procedure);

         return;

      }

      m_puserinteraction->user_send(procedure);

   }


   void prototype_impl::user_post(const ::procedure & procedure)
   {

      if (!m_puserinteraction)
      {

         ::channel::user_post(procedure);

         return;

      }

      m_puserinteraction->user_post(procedure);

   }


    void prototype_impl::main_send(const ::procedure & procedure)
    {

        if (!m_puserinteraction)
        {

            ::channel::main_send(procedure);

            return;

        }

        m_puserinteraction->main_send(procedure);

    }


    void prototype_impl::main_post(const ::procedure & procedure)
    {

        if (!m_puserinteraction)
        {

            ::channel::main_post(procedure);

            return;

        }

        m_puserinteraction->main_post(procedure);

    }


   void prototype_impl::set_opacity(double dOpacity)
   {


   }


} // namespace user



