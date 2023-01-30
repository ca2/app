#include "framework.h"
#include "interaction_thread.h"
#include "primitive_impl.h"
#include "interaction.h"
#include "interaction_impl.h"
#include "call_message_handler_task.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/include/_c_swap.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/context.h"
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


   primitive_impl::primitive_impl()
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


   primitive_impl::~primitive_impl()
   {

   }


   void primitive_impl::create_message_queue(::user::interaction * pinteraction, const ::string & lpszName)
   {

      throw ::interface_only();

      //return true;

   }


   //void primitive_impl::create_interaction(::user::interaction * pinteraction, ::user::primitive * pparent)
   //{

   //   throw ::interface_only();

   //   return true;

   //}


   //void primitive_impl::create_interaction(::user::interaction * pinteraction, ::user::primitive * puiParent)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void primitive_impl::create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pcs, ::user::primitive * puiParent, atom atom)
   //{

   //   throw ::interface_only();

   //   return true;

   //}


   //void primitive_impl::create_interaction(::user::interaction * pinteraction, ::user::primitive * pparent)
   //{

   //   throw ::interface_only();

   //   return true;

   //}

   ::user::interaction_impl * primitive_impl::get_user_interaction_impl()
   {

      return nullptr;

   }


   ::user::interaction_child * primitive_impl::get_user_interaction_child()
   {

      return nullptr;

   }



   void primitive_impl::set_need_layout()
   {

      m_puserinteraction->set_need_layout();

      if (m_puserinteraction->m_puserinteractionParent != nullptr)
      {

         m_puserinteraction->m_puserinteractionParent->set_need_layout();

      }

   }


   void primitive_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //m_puserinteraction->message_call(e_message_size, 0, process_state().m_size.lparam());

      //m_puserinteraction->m_timeLastVisualChange.Now();

      //m_puserinteraction->m_bSizeMove = true;


   }


   void primitive_impl::on_reposition()
   {

   }


   void primitive_impl::on_show_window()
   {

   }


   oswindow primitive_impl::detach_window()
   {

      return nullptr;

   }


   void primitive_impl::destroy()
   {

      ::channel::destroy();

      ::source::destroy();

      ::manager::destroy();

      //auto estatus = 
      m_puserinteraction.release();

      //return estatus;

   }


   //void primitive_impl::finish()
   //{

   //   ::user::primitive::finish();

   //}


   void primitive_impl::prodevian_update_screen()
   {

      //return true;

   }


   //void primitive_impl::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, atom idLeft, ::u32 nFlags, RECTANGLE_I32 * prectParam, const rectangle_i32 & rectangleClient, bool bStretch)
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

   //   if (rectangleClient != nullptr)
   //   {

   //      sizeparentparams.rectangle = rectangleClient;

   //   }
   //   else
   //   {

   //      m_puserinteraction->client_rectangle(&sizeparentparams.rectangle);

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

   //         pinteraction->send_message(e_message_size_parent, 0, (lparam)& sizeparentparams);

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


   void primitive_impl::window_move(i32 x, i32 y)
   {

      //return true;

   }


   //void primitive_impl::main_async(const promise::procedure & routine, enum_priority epriority)
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


   void primitive_impl::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void primitive_impl::_001Print(::draw2d::graphics_pointer & pgraphics)
   {

      if (!m_puserinteraction)
      {

         return;

      }

      string strType = __type_name(m_puserinteraction);

//      if (strType.contains("list_box"))
//      {
//
//         output_debug_string("list_box");
//
//      }

      windowing_output_debug_string("\ninteraction_impl_base::_001Print");

      m_puserinteraction->_001Print(pgraphics);

   }


   void primitive_impl::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->_000CallOnDraw(pgraphics);

      }

   }


   void primitive_impl::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->_001DrawThis(pgraphics);

      }

   }


   void primitive_impl::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->_001DrawChildren(pgraphics);

      }

   }


   void primitive_impl::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->draw_control_background(pgraphics);

      }

   }


   void primitive_impl::set_origin(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void primitive_impl::viewport_client_to_screen(POINT_I32 & point)
   {

      if (m_puserinteraction)
      {

         ::add(point, m_puserinteraction->const_layout().design().origin());

      }

   }


   void primitive_impl::viewport_screen_to_client(POINT_I32 & point)
   {

      if (m_puserinteraction)
      {

         ::subtract(point, m_puserinteraction->const_layout().design().origin());

      }

   }


   void primitive_impl::viewport_client_to_screen(RECTANGLE_I32 & rectangle)
   {

      viewport_client_to_screen((POINT_I32 &)rectangle.left);
      viewport_client_to_screen((POINT_I32 &)rectangle.right);

   }


   void primitive_impl::viewport_screen_to_client(RECTANGLE_I32 & rectangle)
   {

      viewport_screen_to_client((POINT_I32 &)rectangle.left);
      viewport_screen_to_client((POINT_I32 &)rectangle.right);

   }


   void primitive_impl::post(::message::message* pusermessage)
   {


   }


   void primitive_impl::set_bitmap_source(const string& strBitmapSource)
   {


   }


   void primitive_impl::clear_bitmap_source()
   {


   }


   void primitive_impl::set_tool_window(bool bSet)
   {


   }


   void primitive_impl::interaction_post(const ::procedure& procedure)
   {


   }


   void primitive_impl::_000OnMouseLeave(::message::message* pmessage)
   {


   }


   void primitive_impl::track_mouse_hover()
   {


   }


   void primitive_impl::track_mouse_leave()
   {


   }


   void primitive_impl::add_prodevian(::matter* pmatter)
   {


   }


   void primitive_impl::erase_prodevian(::matter* pmatter)
   {


   }


   bool primitive_impl::is_prodevian(const ::matter* pmatter) const
   {

      return false;

   }


   void primitive_impl::prodevian_stop()
   {


   }


   ::user::primitive* primitive_impl::set_owner(::user::primitive* pprimitiveOwner)
   {

      return nullptr;

   }


   bool primitive_impl::has_pending_redraw_flags()
   {

      return false;

   }


   void primitive_impl::pre_subclass_window()
   {


   }


   //void primitive_impl::destroy_impl_only()
   //{


   //}


   //void primitive_impl::start_destroying_window()
   //{


   //}


   void primitive_impl::destroy_window()
   {


   }


   bool primitive_impl::_is_window()
   {

      return false;

   }


   lresult primitive_impl::send_message(const ::atom& atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      return message_call(atom, wparam, lparam, point);

   }


#define _NEW_MESSAGE(TYPE) \
   auto pmessage = __create_new<TYPE>(); \
   pmessage->m_oswindow = oswindow; \
   pmessage->m_pwindow = pwindow; \
   pmessage->m_atom = atom; \
   pmessage->m_wparam = wparam; \
   pmessage->m_lparam = lparam; \
   pmessageBase = pmessage


   ::pointer<::message::message>primitive_impl::get_message(const ::atom & atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype)
   {

      ::pointer<::message::message>pmessageBase;

      if (eprototype == ::message::e_prototype_none)
      {

         eprototype = ::message::get_message_prototype(atom.as_emessage(), 0);

      }

      auto pwindow = this->window();

      auto oswindow = pwindow->oswindow();

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

            //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

            pmessage->m_bActive = wparam != false;

         }
      }
      break;
      case ::message::e_prototype_key:
      {
         _NEW_MESSAGE(::message::key);
         //void key::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
         {

            // ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

            pmessage->m_nChar = static_cast<::u32>(wparam);

            pmessage->m_nRepCnt = first_u16(lparam);

            pmessage->m_nFlags = HIWORD(lparam);

            pmessage->m_iVirtualKey = (int)wparam;

            pmessage->m_nScanCode = ((lparam >> 16) & 0xff);

            pmessage->m_bExt = (lparam & (1 << 24)) != 0;

         }

      }
      break;
      case ::message::e_prototype_timer:
      {

         //throw ::exception(::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));

         _NEW_MESSAGE(::message::timer);

         pmessage->m_uEvent = static_cast<::u32>(wparam);

      }
      break;
      case ::message::e_prototype_show_window:
      {
         _NEW_MESSAGE(::message::show_window);
         pmessage->m_bShow = wparam != false;

         pmessage->m_nStatus = static_cast<::u32>(lparam);

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
         pmessage->m_point.x = GET_X_LPARAM(lparam);

         pmessage->m_point.y = GET_Y_LPARAM(lparam);
      }
      break;
      case ::message::e_prototype_move:
      {
         _NEW_MESSAGE(::message::reposition);
         pmessage->m_point = ::point_i32(lparam);
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

         pmessage->m_oswindowScrollBar = (::oswindow)(::iptr)(lparam);

         //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

         pmessage->m_ecommand = (enum_scroll_command)(i16)first_u16(wparam);

         pmessage->m_nPos = (i16)HIWORD(wparam);

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
#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)
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
         pmessage->m_nFlags = wparam;

         if ((pmessage->m_nFlags & 0x80000000) == (0x80000000))
         {

            output_debug_string("(m_nFlags & 0x80000000) == (0x80000000)");

         }

         pmessage->m_point = ::point_i32(lparam);

         _raw_client_to_screen(pmessage->m_point);

      }
      break;
      case ::message::e_prototype_object:
      {
         _NEW_MESSAGE(::message::particle);
         //void particle::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
         {

            //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

            ::pointer < ::particle > pparticle(lparam);

            pmessage->m_pparticle = pparticle;

            pmessage->m_lparam = 0;

         }
      }
      break;
      case ::message::e_prototype_mouse_wheel:
      {
         _NEW_MESSAGE(::message::mouse_wheel);

         pmessage->m_nFlags = first_u16(wparam);

         pmessage->m_point = ::point_i32(lparam);

         pmessage->m_Δ = second_i16(wparam);

         _raw_client_to_screen(pmessage->m_point);

      }
      break;
      case ::message::e_prototype_size:
      {
         _NEW_MESSAGE(::message::size);

         pmessage->m_nType = static_cast <::u32> (wparam);

         pmessage->m_size = ::size_i32(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
      }
      break;
      case ::message::e_prototype_activate:
      {
         _NEW_MESSAGE(::message::activate);
         //pmessage = p;
         //default_set(pmessage, atom, wparam, lparam)
         //void activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
         //{

            //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

         pmessage->m_eactivate = (enum_activate)(first_u16(wparam));

         if (lparam == 0)
         {

            pmessage->m_pWndOther = nullptr;

         }
         else
         {

            auto paurasession = m_pcontext->m_pacmesession->m_paurasession;

            auto puser = paurasession->m_puser;

            auto pwindowing = puser->m_pwindowing;

            pmessage->m_pWndOther = __interaction(pwindowing->window(lparam.raw_cast <::oswindow>()));

         }

         pmessage->m_bMinimized = HIWORD(wparam) != false;

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
         
         auto pmessage = ::channel::get_message(atom, wparam, lparam, eprototype);
         
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



   //void primitive_impl::post_message(const ::atom& atom, ::wparam wParam, ::lparam lParam)
   //{


   //}


   void primitive_impl::set_window_text(const ::string& pszString)
   {


   }


   strsize primitive_impl::get_window_text(char* pszStringBuf, strsize nMaxCount)
   {

      return 0;

   }


   void primitive_impl::get_window_text(string& rString)
   {


   }


   strsize primitive_impl::get_window_text_length()
   {

      return 0;

   }


   void primitive_impl::UpdateWindow()
   {


   }


   void primitive_impl::SetRedraw(bool bRedraw)
   {


   }


   void primitive_impl::prodevian_redraw(bool bUpdateBuffer)
   {


   }


   void primitive_impl::set_mouse_cursor(::windowing::cursor* pcursor)
   {


   }


   ::user::interaction* primitive_impl::ChildWindowFromPoint(const ::point_i32& point)
   {

      return nullptr;

   }


   ::user::interaction* primitive_impl::ChildWindowFromPoint(const ::point_i32& point, ::u32 nFlags)
   {

      return nullptr;

   }


   ::user::interaction* primitive_impl::GetLastActivePopup()
   {

      return nullptr;

   }


   void primitive_impl::update_data(bool bSaveAndValidate)
   {


   }


   void primitive_impl::CenterWindow(::user::interaction* pAlternateOwner)
   {


   }


   bool primitive_impl::OnChildNotify(::message::message* pusermessage)
   {

      return false;

   }


   void primitive_impl::ActivateTopParent()
   {


   }


   void primitive_impl::_001UpdateWindow()
   {


   }


   void primitive_impl::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {


   }


   void primitive_impl::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {


   }


   void primitive_impl::on_configuration_change(::user::primitive* pprimitiveSource)
   {


   }


   //::user::element* primitive_impl::get_keyboard_focus()
   //{

   //   return nullptr;

   //}

   
   void primitive_impl::_001OnExitIconic()
   {


   }


   void primitive_impl::_001OnExitFullScreen()
   {


   }


   void primitive_impl::_001OnExitZoomed()
   {


   }


   void primitive_impl::default_message_handler(::message::message * pmessage)
   {


   }


   void primitive_impl::_001OnTriggerMouseInside()
   {


   }


   bool primitive_impl::has_pending_graphical_update()
   {

      return false;

   }


   void primitive_impl::on_after_graphical_update()
   {


   }


   bool primitive_impl::is_this_visible(enum_layout elayout)
   {

      return false;

   }


   void primitive_impl::post_redraw(bool bAscendants)
   {



   }


   double primitive_impl::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      return 0.;

   }


//   ::windowing::window* primitive_impl::get_window() const
//   {
//
//      return nullptr;
//
//   }


   bool primitive_impl::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      return false;

   }


   bool primitive_impl::keyboard_focus_OnChildKillFocus()
   {

      return false;

   }


   void primitive_impl::edit_on_set_focus(::user::interaction* pinteraction)
   {


   }


   void primitive_impl::edit_on_kill_focus(::user::interaction* pinteraction)
   {


   }


   void primitive_impl::show_software_keyboard(::user::element * pelement)
   {
      
      throw interface_only();
      
   }


   void primitive_impl::hide_software_keyboard(::user::element * pelement)
   {
   
      throw interface_only();
   
   }


   ::user::interaction* primitive_impl::get_child_by_id(const ::atom& atom, ::index iItem, i32 iLevel)
   {

      return nullptr;

   }


   void primitive_impl::set_need_redraw(bool bAscendants)
   {


   }


   void primitive_impl::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      if (!m_puserinteraction)
      {

         //return false;

         return;

      }

      return m_puserinteraction->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   }


   //u32 primitive_impl::GetStyle() const
   //{

   //   return get_window_long(GWL_STYLE);

   //}


   //u32 primitive_impl::GetExStyle() const
   //{

   //   return get_window_long(GWL_EXSTYLE);

   //}


   //void primitive_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   //{

   //   ::i32 l = GetStyle();

   //   l |= dwAdd;

   //   ::i32 lRemove = ~dwRemove;

   //   l &= lRemove;

   //   set_window_long(GWL_STYLE, l);

   //   return true;

   //}


   //void primitive_impl::ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   //{

   //   set_window_long(GWL_EXSTYLE, (GetExStyle() | dwAdd) & ~dwRemove);

   //   return true;

   //}


//   ::i32 primitive_impl::get_window_long(i32 nIndex) const
//   {
//
//      return (::i32)get_window_long_ptr(nIndex);
//
//   }
//
//
//   ::i32 primitive_impl::set_window_long(i32 nIndex, ::i32 lValue)
//   {
//
//      return (::i32)set_window_long_ptr(nIndex, lValue);
//
//   }
//
//
//   iptr primitive_impl::get_window_long_ptr(i32 nIndex) const
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
//////      synchronous_lock synchronouslock(&((primitive_impl *)this)->m_pmutexLongPtr);
//////
//////      return (LONG_PTR)m_longptr[nIndex];
////
//      return m_iptrmap[nIndex];
//
//   }
//
//
//   void primitive_impl::set_window_long_ptr(i32 nIndex, iptr lValue)
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
////      synchronous_lock synchronouslock(m_pmutexLongPtr);
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


   atom primitive_impl::GetDlgCtrlId() const
   {

      if (!m_puserinteraction)
      {

         return ::atom::e_type_null;

      }

      return m_puserinteraction->GetDlgCtrlId();

   }


   atom primitive_impl::SetDlgCtrlId(atom atom)
   {

      if (!m_puserinteraction)
      {

         return atom::e_type_null;

      }

      return m_puserinteraction->SetDlgCtrlId(atom);

   }



   ::user::interaction * primitive_impl::first_child()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->first_child();

   }


   ::user::interaction * primitive_impl::top_child()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->first_child();

   }


   ::user::interaction * primitive_impl::under_sibling()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->under_sibling();

   }


   ::user::interaction * primitive_impl::above_sibling()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->above_sibling();

   }


   ::user::interaction * primitive_impl::above_sibling(::user::interaction * pinteraction)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->above_sibling(pinteraction);

   }


   ::user::interaction * primitive_impl::under_sibling(::user::interaction * pinteraction)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->under_sibling(pinteraction);

   }


   ::u32 primitive_impl::ArrangeIconicWindows()
   {

      //      return m_puserinteraction->ArrangeIconicWindows();
      return 0;

   }


   bool primitive_impl::is_ascendant(::user::element * puiIsAscendant, bool bIncludeSelf)
   {

      if (::is_null(puiIsAscendant))
      {

         return false;

      }

      return puiIsAscendant->is_descendant(m_puserinteraction, bIncludeSelf);

   }


   bool primitive_impl::is_parent(::user::element * puiIsParent)
   {

      if (puiIsParent == nullptr)
      {

         return false;

      }

      return puiIsParent->is_child(m_puserinteraction);

   }


   bool primitive_impl::is_child(::user::element * puiIsChild)
   {

      if (puiIsChild == nullptr)
      {

         return false;

      }

      ::user::interaction * puiProbe = puiIsChild->get_parent();

      return puiProbe == m_puserinteraction;

   }


   bool primitive_impl::is_descendant(::user::element * puiIsDescendant, bool bIncludeSelf)
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


   ::user::interaction * primitive_impl::get_wnd()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_wnd();

   }


   ::user::interaction * primitive_impl::get_wnd(::u32 nCmd)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_wnd(nCmd);

   }


   //::user::interaction * primitive_impl::GetTopWindow() const
   //{

   //   auto pinteraction = get_wnd();

   //   if (!pinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetTopWindow();

   //}


   ::user::interaction * primitive_impl::get_parent()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent();

   }


   ::user::interaction * primitive_impl::get_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->m_puserinteractionOwner;

   }


   ::user::frame * primitive_impl::frame()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->frame();

   }


   //::user::frame * primitive_impl::get_parent_frame() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteraction->parent_frame();

   //}


   ::user::interaction * primitive_impl::get_parent_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_owner();

   }


   ::user::interaction * primitive_impl::get_parent_or_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_or_owner();

   }


   ::user::interaction * primitive_impl::get_top_level_owner()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_top_level_owner();

   }


   ::user::frame * primitive_impl::top_level_frame()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->top_level_frame();

   }


   //::user::interaction * primitive_impl::get_top_level() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteraction->top_level();

   //}


   lresult primitive_impl::message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      ::pointer<::message::message>pmessage;

      if (m_puserinteraction)
      {

         pmessage = m_puserinteraction->get_message(atom, wparam, lparam);

      }
      else
      {

         pmessage = get_message(atom, wparam, lparam);

      }

      pmessage->m_pchannel = m_puserinteraction;

      return message_call(pmessage);

   }


   lresult primitive_impl::message_call(::message::message * pmessage)
   {

      if (m_puserinteraction == nullptr)
      {

         message_handler(pmessage);

         return pmessage->m_lresult;

      }

      if (m_puserinteraction->layout().is_moving())
      {
         
         TRACE("moving: skip walk pre translate tree");

      }
      else if (m_puserinteraction->layout().is_sizing())
      {
         
         TRACE("sizing: skip walk pre translate tree");

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


   void primitive_impl::send_message_to_descendants(const ::atom & atom, wparam wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {

      return m_puserinteraction->send_message_to_descendants(atom, wparam, lparam, bDeep, bOnlyPerm);

   }


   void primitive_impl::pre_translate_message(::message::message * pmessage)
   {

      m_puserinteraction->pre_translate_message(pmessage);

   }


   //void primitive_impl::set_capture(::user::interaction * pinteraction)
   //{

   //   return get_host_window()->set_capture(pinteraction);

   //}


   //::user::interaction * primitive_impl::get_capture() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_capture();

   //}


   //void primitive_impl::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return get_host_window()->set_keyboard_focus(pinteraction);

   //}


   //::user::interaction * primitive_impl::get_keyboard_focus() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_keyboard_focus();

   //}


   void primitive_impl::get_rect_normal(RECTANGLE_I32 * prectangle)
   {

      *prectangle = m_puserinteraction->screen_rect();

      //return true;

   }


   void primitive_impl::SetTimer(uptr uEvent, const class ::time & timeEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void* pdata)
   {

      if (timeEllapse < 500_ms)
      {

         //         string str;
         //
         //         str.format("creating fast timer: %d\n", nEllapse);
         //
         //         ::output_debug_string(str);

      }

      if (m_ptimerarray.is_null())
      {

         __construct_new(m_ptimerarray);

         m_ptimerarray->m_pcallback = m_puserinteraction;

         //m_ptimerarray->set_context_thread(m_puserinteraction->m_pthreadUserInteraction);

      }

      m_ptimerarray->create_timer(this, uEvent, timeEllapse, pfnTimer, bPeriodic, pdata);

   }


   void primitive_impl::KillTimer(uptr uEvent)
   {

      if (m_ptimerarray.is_null())
      {

         return;

      }

      m_ptimerarray->delete_timer(uEvent);

   }


   void primitive_impl::_001OnTimer(::timer * ptimer)
   {

      if (m_puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteraction->_001OnTimer(ptimer);

   }


   //void primitive_impl::defer_start_prodevian()
   //{

   //   m_puserinteraction->post_simple_command(e_simple_command_defer_start_prodevian);

   //}


   //void primitive_impl::_defer_start_prodevian()
   //{

   //}

   void primitive_impl::destroy_impl_only()
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

            auto pinteractionimpl = puserinteraction->m_pinteractionimpl;

            if (pinteractionimpl)
            {

               synchronous_lock synchronouslock(pinteractionimpl->synchronization());

               pinteractionimpl->m_userinteractionaMouseHover.erase(m_puserinteraction);

            }

         }

         m_puserinteraction->m_puserinteractionParent = nullptr;

      }

      m_puserinteraction = nullptr;

      start_destroying_window();

      //FORMATTED_TRACE("destroy_impl_only DestroyWindow %d", bOk != false);

      //return bOk;

   }


   void primitive_impl::start_destroying_window()
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

      ::pointer<::user::primitive_impl>pimplThis = this;

      ::pointer<::user::interaction>puiThis = m_puserinteraction;

      if(puiThis)
      {

         try
         {

            puiThis->send_message(e_message_destroy);

         }
         catch (...)
         {

         }

         try
         {

            puiThis->send_message(e_message_non_client_destroy);

         }
         catch (...)
         {

         }

      }

      //return true;

   }


   void primitive_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      auto puserinteraction = m_puserinteraction;

      if (!puserinteraction)
      {

         return;

      }

      ::user::interaction * pinteraction = puserinteraction->get_host_window();

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


   bool primitive_impl::mouse_hover_erase(::user::interaction * pinterface)
   {

      auto puserinteraction = m_puserinteraction;

      if (!puserinteraction)
      {

         return false;

      }

      ::user::interaction * pinteraction = puserinteraction->get_host_window();

      if (pinteraction != nullptr)
      {

         return pinteraction->mouse_hover_erase(pinterface);

      }

      return false;

   }


   void primitive_impl::register_drop_target()
   {

   }


//   ::windowing::window* primitive_impl::window()
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


   ::user::element * primitive_impl::get_keyboard_focus()
   {

      return nullptr;

   }


   void primitive_impl::set_keyboard_focus(::user::primitive_impl * pprimitiveimpl)
   {

      __UNREFERENCED_PARAMETER(pprimitiveimpl);

      //return ::error_failed;

   }


   void primitive_impl::erase_keyboard_focus(::user::primitive_impl * pprimitiveimpl)
   {

      __UNREFERENCED_PARAMETER(pprimitiveimpl);

   }


   void primitive_impl::clear_keyboard_focus(::user::primitive_impl * pprimitiveimplGainingFocusIfAny)
   {


   }


   void primitive_impl::impl_set_keyboard_focus(::user::primitive_impl * pprimitiveimpl)
   {


   }


   void primitive_impl::impl_erase_keyboard_focus(::user::primitive_impl * pprimitiveimpl)
   {


   }


   void primitive_impl::impl_clear_keyboard_focus()
   {


   }


   void primitive_impl::post_message(const ::atom & atom, wparam wparam, lparam lparam)
   {

      if (::is_null(m_puserinteraction))
      {

         throw ::exception(error_wrong_state);

      }

      m_puserinteraction->interaction_post(__new(call_message_handler_task(m_puserinteraction, atom, wparam, lparam)));

   }


   void primitive_impl::post_non_client_destroy()
   {

      ::pointer<primitive_impl>pimpl = this;

      {

         synchronous_lock synchronouslock(this->synchronization());

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

      //::user::primitive_impl::post_non_client_destroy();



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


   void primitive_impl::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      m_puserinteraction->set_need_redraw();

   }


   void primitive_impl::_001OnPrioCreate(::message::message * pmessage)
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

      m_puserinteraction->run_property(ID_CREATE);

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


   void primitive_impl::on_message_destroy(::message::message * pmessage)
   {

      //synchronous_lock synchronouslock(this->synchronization());

      //try
      //{

      //   if (m_ptimerarray)
      //   {

      //      m_ptimerarray->destroy();

      //      m_ptimerarray.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(""));

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   void primitive_impl::on_message_non_client_destroy(::message::message * pmessage)
   {

      if (m_puserinteraction && __type_name(m_puserinteraction).contains("notify_icon"))
      {

         INFORMATION("notify_icon");

      }

      post_non_client_destroy();

   }


   void primitive_impl::prio_install_message_routing(::channel * pchannel)
   {

      //if (g_p == nullptr)
      //{

      //   g_p = memory_new iptr_map < string >;

      //}

      //g_p->set_at((iptr)this, __type_name(m_puserinteraction)) + "xxx" + __type_name(this);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &primitive_impl::on_message_show_window);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &primitive_impl::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_destroy, pchannel, this, &primitive_impl::on_message_non_client_destroy);
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &primitive_impl::_001OnPrioCreate);

      if (m_puserinteraction && __type_name(m_puserinteraction).contains("notify_icon"))
      {

         INFORMATION("notify_icon");

      }

   }


   void primitive_impl::last_install_message_routing(::channel * pchannel)
   {


   }


   void primitive_impl::show_task(bool bShow)
   {

      __UNREFERENCED_PARAMETER(bShow);

   }


   void primitive_impl::redraw_add(::particle * pparticle)
   {

   }


   void primitive_impl::redraw_erase(::particle * pparticle)
   {

   }


   bool primitive_impl::has_redraw()
   {

      return false;

   }


   void primitive_impl::queue_message_handler(::message::message * pmessage)
   {

      m_puserinteraction->message_handler(pmessage);

      //if (pmessage->m_bRet)
      //{

      //   return true;

      //}

      //return false;

   }


   //void primitive_impl::has_keyboard_focus() const
   //{

   //   if (m_puserinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   ::pointer<::user::interaction>pinteraction = m_puserinteraction->get_host_window();

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

   //   ::pointer<::user::interaction_impl>pimpl = pinteraction->m_pimpl;

   //   if (pimpl.is_null())
   //   {

   //      return false;

   //   }

   //   return pimpl->m_pprimitiveFocus == m_puserinteraction;

   //}


   //void primitive_impl::is_active()
   //{

   //   if (m_puserinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_puserinteraction == m_puserinteraction->GetActiveWindow();

   //}


   void primitive_impl::create_host(::user::interaction * puserinteraction)
   {

      //return false;

   }


   void primitive_impl::create_child(::user::interaction * puserinteraction, ::user::primitive * puserprimitiveParent)
   {

      //return false;

   }


   //void primitive_impl::is_this_enabled() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return false;

   //   }

   //   return m_puserinteraction->m_ewindowflag & e_window_flag_enable;

   //}


   // void primitive_impl::SetWindowDisplayChanged()
   // {

   // }


   void primitive_impl::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

   }


   void primitive_impl::start_window_visual()
   {

      //return true;

   }


   void primitive_impl::enable_window(bool bEnable)
   {

      //bool bWasDisabled = !(m_puserinteraction->m_ewindowflag & e_window_flag_enable);

      m_puserinteraction->m_ewindowflag.set(e_window_flag_enable, bEnable);

      //return bWasDisabled;

   }


   void primitive_impl::user_interaction_on_hide()
   {


   }


   i32 primitive_impl::GetUpdateRgn(class draw2d::region *,bool)
   {

      return 0;

   }


   void primitive_impl::Invalidate(bool)
   {


   }


   void primitive_impl::InvalidateRect(class rectangle_type<struct RECTANGLE_I32,struct POINT_I32,struct SIZE_I32> const &,bool)
   {


   }


   void primitive_impl::InvalidateRgn(class draw2d::region *,bool)
   {


   }


   void primitive_impl::ValidateRect(class rectangle_type<struct RECTANGLE_I32,struct POINT_I32,struct SIZE_I32> const &)
   {


   }


   void primitive_impl::ValidateRgn(class draw2d::region *)
   {


   }


   void primitive_impl::ShowOwnedPopups(bool)
   {


   }


   ::graphics::graphics * primitive_impl::get_window_graphics(void)
   {

      return nullptr;

   }


   bool primitive_impl::is_composite()
   {

      return false;

   }

   
   void primitive_impl::_task_transparent_mouse_event()
   {

   }


   bool primitive_impl::IsTopParentActive()
   {

      return false;

   }


#ifdef LINUX


   lresult primitive_impl::send_x11_event(void * pevent)
   {

      throw interface_only();

      return 0;

   }


#endif


   ::user::interaction * primitive_impl::top_level()
   {
      
      return m_puserinteraction->m_puserinteractionTopLevel;

   }


   ::user::frame * primitive_impl::parent_frame()
   {
      
      return m_puserinteraction->m_puserframeParent;

   }


   ::windowing::window* primitive_impl::window()
   {

      return m_puserinteraction->m_pwindow;

   }


   ::aura::application * primitive_impl::get_app()
   {

      return m_pcontext ? m_pcontext->m_pacmeapplication->m_pauraapplication : nullptr;

   }


   ::aura::session * primitive_impl::get_session()
   {

      return m_pcontext ? m_pcontext->m_pacmesession->m_paurasession : nullptr;

   }


   //::aura::system * primitive_implacmesystem()
   //{

   //   return acmesystem() ? acmesystem()->m_paurasystem : nullptr;

   //}

   void primitive_impl::_raw_client_to_screen(::point_i32 & point)
   {

      point += m_puserinteraction->client_to_screen(e_layout_design);

   }


} // namespace user



