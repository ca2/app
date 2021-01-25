#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/message.h"
#include "apex/message/simple_command.h"
#include "aura/message/timer.h"


namespace user
{


   primitive::primitive()
   {

   }


   primitive::~primitive()
   {

   }


   ::user::callback* primitive::get_user_callback()
   {

      return nullptr;

   }


   void primitive::install_message_routing(::channel * pchannel)
   {

      channel::install_message_routing(pchannel);

   }


   ::e_status primitive::show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd)
   {

      return error_interface_only;

   }


   ::e_status primitive::hide_software_keyboard(::user::primitive * pprimitive)
   {

      return error_interface_only;


   }


   //void primitive::TwfGetWndArray(::user::interaction_pointer_array & wndpa)
   //{

   //   wndpa = *dynamic_cast < ::user::interaction_pointer_array * >(get_object());

   //}


//   void primitive::TwfGetWndArray(::user::oswindow_array & oswindowa)
//   {
//
//      ::user::interaction_pointer_array & wndpa = *dynamic_cast < ::user::interaction_pointer_array * >(get_object());
//
//      oswindowa = wndpa.get_hwnda();
//
//   }
//
//
//   void primitive::RedrawOptimize(rect_array &array)
//   {
//
//      ::rect rect;
//
//Restart:
//
//      for(i32 i = 0; i < array.get_size(); i++)
//      {
//         for(i32 j = i + 1; j < array.get_size(); j++)
//         {
//            if(RedrawOptimize(
//                  rect,
//                  array[i],
//                  array[j]))
//            {
//               array[i] = rect;
//               array.remove_at(j);
//               goto Restart;
//
//            }
//
//         }
//
//      }
//
//   }
//
//
//   bool primitive::RedrawOptimize(RECT32 * prectOut, const rect & rect1Param, const rect & rect2Param)
//   {
//
//      ::rect rect1(rect1Param);
//
//      ::rect rect2(rect2Param);
//
//      ::rect rect3;
//
//      i32 iArea1 = rect1.width() * rect1.height();
//      i32 iArea2 = rect2.width() * rect2.height();
//      rect3.unite(rect1, rect2);
//      i32 iArea3 = rect3.width() * rect3.height();
//
//      if(iArea3 < (110 * (iArea1 + iArea2) / 100))
//      {
//
//         *prectOut = rect3;
//
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }
//
//   }


   void primitive::PreSubClassWindow()
   {

      //_001BaseWndInterfaceMap();

   }




   //void primitive::_001BaseWndInterfaceMap()
   //{

   //}


   ::user::interaction * primitive::get_wnd() const
   {

      return nullptr;

   }


   ::thread * primitive::get_task() const
   {

      auto pwnd = get_wnd();

      if (::is_null(pwnd))
      {

         return get_context_application();

      }

      return pwnd->m_pthreadUserInteraction;

   }



   ::user::interaction_impl * primitive::get_impl() const
   {

      ::user::interaction * pinteraction = get_wnd();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      if (pinteraction->m_pimpl.is_null())
      {

         return nullptr;

      }

      try
      {

         return pinteraction->m_pimpl->get_impl();

      }
      catch (...)
      {

      }

      return nullptr;

   }


   bool primitive::is_window_enabled() const
   {

      auto puiParent = get_parent();

      if (puiParent != nullptr)
      {

         if (!puiParent->is_window_enabled())
         {

            return false;

         }

      }

      return is_this_enabled();

   }


   bool primitive::is_this_enabled() const
   {

      return true;

   }


   ::user::interaction* primitive::get_host_window() const
   {

      if (get_context_session() == nullptr
         || get_context_session()->m_paurasession == nullptr)
      {

         return nullptr;

      }

      if (get_context_session()->m_paurasession->m_puiHost)
      {

         return __user_interaction(get_context_session()->m_paurasession->m_puiHost);

      }
      else
      {

         return get_wnd();

      }

   }


   bool primitive::enable_window(bool bEnable)
   {

      UNREFERENCED_PARAMETER(bEnable);

      return false;

   }


   void primitive::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void primitive::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      _001OnDraw(pgraphics);
      _008OnDraw(pgraphics);

   }


   void primitive::UpdateWindow()
   {

      //ASSERT(::IsWindow(GetHandle()));
      //::UpdateWindow(GetHandle());

   }


   void primitive::Invalidate(bool bErase)
   {

      UNREFERENCED_PARAMETER(bErase);

      //ASSERT(::IsWindow(GetHandle()));
      //::InvalidateRect(GetHandle(), nullptr, bErase);

   }

   bool primitive::has_pending_redraw_flags()
   {

      return false;

   }


   //bool primitive::Redraw(rect_array & recta)
   //{

   //   bool bOk = true;

   //   for(i32 i = 0; i < recta.get_size(); i++)
   //   {

   //      if(!get_wnd()->RedrawWindow(recta[i]))
   //         bOk = false;

   //   }

   //   return bOk;

   //}


   //bool primitive::Redraw(const ::rect & rect, ::draw2d::region * prgn)
   //{

   //   if (get_wnd() == nullptr)
   //   {

   //      return false;

   //   }

   //   return get_wnd()->RedrawWindow(rect, prgn, RDW_INVALIDATE);

   //}


   //bool primitive::Redraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   UNREFERENCED_PARAMETER(pgraphics);

   //   if(get_wnd() == nullptr)
   //      return false;

   //   return get_wnd()->RedrawWindow();

   //}


   /*bool primitive::_001ClientToScreen(RECT32 * prect)
   {

      ::offset_rect(prect, client_screen_top_left());

      return true;

   }


   bool primitive::_001ClientToScreen(RECTD * prect)
   {

      ::offset_rect(prect, client_screen_top_left());

      return true;

   }
*/

   //bool primitive::_001ClientToScreen(POINT32 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ClientToScreen(POINTD * ppoint)
   //{

   //   ::offset(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ClientToScreen(RECT64 * prect)
   //{

   //   ::offset_rect(prect, point64(client_screen_top_left()));

   //   return true;

   //}


   //bool primitive::_001ClientToScreen(POINT64 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ScreenToClient(RECT32 * prect)
   //{

   //   ::offset_rect(prect, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ScreenToClient(RECTD * prect)
   //{

   //   ::offset_rect(prect, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ScreenToClient(POINT32 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ScreenToClient(POINTD * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ScreenToClient(RECT64 * prect)
   //{

   //   ::offset_rect(prect, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::_001ScreenToClient(POINT64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::GetWindowPos(RECT32 * prect)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::get_window_rect(RECT32 * prect)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //pointd primitive::client_screen_top_left()
   //{

   //   return nullptr;

   //}


   //bool primitive::get_client_rect(RECT32 * prect)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::get_client_rect(RECT64 * prect)

   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::get_window_rect(RECT64 * prect)

   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}












/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





































   bool primitive::is_ascendant(const primitive * puiIsAscendant, bool bIncludeSelf) const
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::is_parent(const primitive * puiIsParent) const
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::is_child(const primitive * puiIsChild) const
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::is_descendant(const primitive * puiIsDescendant, bool bIncludeSelf) const
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::is_descendant_of_or_owned_by(const ::user::primitive * puiAscendantCandidate, bool bIncludeSelf) const
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::is_ascendant_or_owner_of(const ::user::primitive * puiDescendantCandidate, bool bIncludeSelf) const
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::is_ascendant_of(const primitive * puiIsDescendant, bool bIncludeSelf) const
   {
      
      return ::is_set(puiIsDescendant) && puiIsDescendant->is_ascendant(this, bIncludeSelf); 
   
   }


   bool primitive::is_parent_of(const primitive * puiIsChild) const
   {
      
      return ::is_set(puiIsChild) && puiIsChild->is_parent(this); 
   
   }


   bool primitive::is_child_of(const primitive * puiIsParent) const
   {
      
      return ::is_set(puiIsParent) && puiIsParent->is_child(this); 
   
   }

   
   bool primitive::is_descendant_of(const primitive * puiIsAscendant, bool bIncludeSelf) const
   { 
      
      return ::is_set(puiIsAscendant) && puiIsAscendant->is_descendant(this, bIncludeSelf); 
   
   }


   void primitive::_008GetWindowText(::message::message * pmessage)
   {

   }


   void primitive::_008GetWindowTextLength(::message::message * pmessage)
   {

   }


#ifdef WINDOWS
   strsize primitive::_009GetWindowText(wchar_t * pwsz, int n)
#else
   strsize primitive::_009GetWindowText(char * psz, int n)
#endif
   {

      return -1;

   }


   strsize primitive::_009GetWindowTextLength()
   {

      return -1;

   }



   //bool primitive::SetPlacement(const ::rect & rect,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   bool primitive::add_prodevian(::context_object * pobject)
   {

      return false;

   }


   bool primitive::remove_prodevian(::context_object * pobject)
   {

      return false;

   }


   string primitive::get_title()
   {

      return get_window_text();

   }


   //i32 primitive::sync_message_box(::payload payload)
   //{

   //   if (payload.get_type() == e_type_string)
   //   {

   //      payload["message"] = payload;

   //   }

   //   payload["parent"] = this;
   //   payload["title"] = get_title();

   //   return message_box(payload);

   //}


   //i32 primitive::sync_message_box_timeout(const char * pszMessage, ::duration durationTimeOut, ::u32 fuStyle)
   //{

   //   return Application.sync_message_box_timeout(this, pszMessage, get_title(), durationTimeOut, fuStyle);

   //}


   //::e_status primitive::message_box(const ::payload& varParam)
   //{

   //   ::payload payload;

   //   if (varParam.get_type() == e_type_propset)
   //   {

   //      payload = varParam;

   //   }
   //   else
   //   {

   //      string strMessage;

   //      strMessage = varParam.get_string();

   //      payload["message"] = strMessage;

   //   }

   //   payload["owner"] = this;

   //   payload["title"] = get_title();

   //   return Application.message_box(payload);

   //}


   //void primitive::message_box_timeout(string strMessage, ::duration durationTimeout, ::u32 fuStyle)
   //{

   //   fork([=]()
   //      {

   //         sync_message_box_timeout(strMessage, durationTimeout, fuStyle);

   //      });

   //}
   //bool primitive::place(const ::rect & rect)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::RepositionWindow(i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::MoveWindow(i32 x,i32 y,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::move_to(const ::point & point)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::SizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::set_size(const size & sz)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::ResizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::ResizeWindow(const size & sz,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::set_window_pos(class zorder zorder, const ::rect & rect, ::u32 nFlags)

   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}

   //bool primitive::defer_set_window_pos(iptr z, const  const rect & & rect, ::u32 nFlags) // only set_windows_pos if get_parent()->_001ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::defer_set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags) // only set_windows_pos if get_parent()->_001ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   void primitive::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::_001PrintBuffer(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::_001Print(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   ::user::interaction * primitive::_001FromPoint(::point point,bool bTestedIfParentVisible)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool primitive::_001IsPointInside(::point point)
   {


      return false;

   }


   ::user::interaction * primitive::get_child_by_name(const char * lpszName,i32 iLevel)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::get_child_by_id(id id,i32 iLevel)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }



   ::e_status primitive::main_async(const ::promise::routine & routine, e_priority epriority)
   {

      __throw(interface_only_exception());

      return error_interface_only;

   }


   LRESULT primitive::send(::message::base * pbase)
   {

      if(pbase->userprimitive() == nullptr)
      {

         pbase->m_playeredUserPrimitive = this;

      }

      message_handler(pbase);

      return pbase->m_lresult;

   }


   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   bool primitive::post(::message::base * pbase)
   {

      ::exception::throw_interface_only();

      return false;

   }


   LRESULT primitive::send_message(const ::id & id,WPARAM wparam,lparam lparam)
   {

      return message_call(id, wparam, lparam);

   }


   LRESULT primitive::message_call(const ::id & id, WPARAM wparam, lparam lparam)
   {

      return 0;

   }


   LRESULT primitive::message_call(::message::base * pbase)
   {

      return 0;

   }


#ifdef LINUX


   LRESULT primitive::send_x11_event(void * pevent)
   {

      ::exception::throw_interface_only();

      return 0;

   }


#endif


   //bool primitive::_is_window_visible()
   //{

   //   return false;

   //}


   //bool primitive::is_this_visible()
   //{

   //   return (GetStyle() & WS_VISIBLE) != 0 && m_bUserPrimitiveOk;

   //}


   bool primitive::ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   {

      ::exception::throw_interface_only();

      return false;

   }


   //bool primitive::display(::e_display edisplay)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   // void primitive::SetWindowDisplayChanged()
   // {


   // }


   ::user::frame * primitive::top_level_frame() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   void primitive::send_message_to_descendants(const ::id & id,WPARAM wparam,lparam lparam,bool bDeep,bool bOnlyPerm)

   {

      ::exception::throw_interface_only();

   }

   void primitive::route_message_to_descendants(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

   }

   void primitive::pre_translate_message(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   oswindow primitive::get_handle() const
   {

      return nullptr;

   }


   string primitive::get_class_name()
   {

      auto econtroltype = get_control_type();

      string strClassName = Application.get_window_class_name(econtroltype);

      return strClassName;

   }


   bool primitive::subclass_window(oswindow posdata)
   {

      ::exception::throw_interface_only();

      return false;

   }


   oswindow primitive::unsubclass_window()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool primitive::create_child(::user::interaction * puserinteractionParent)
   {

      ::exception::throw_interface_only();

      return true;

   }

   
   bool primitive::create_control(::user::interaction * puserinteractionParent, const ::id & id)
   {

      m_id = id;

      if (!create_child(puserinteractionParent))
      {

         return false;

      }

      return true;

   }


   enum_control_type primitive::get_control_type() const
   {

      return e_control_type_none;

   }


   //bool primitive::create_interaction(::user::interaction * puiParent, ::create * pcreate, ::u32 uExStyle, ::u32 uStyle)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   bool primitive::create_interaction(::user::interaction * puserinteractionParent, const ::id & id)
   {

      if (!id.is_empty())
      {

         m_id = id;

      }

      if (!puserinteractionParent)
      {

         if (!create_host())
         {

            return false;

         }

      }
      else
      {

         if (!create_child(puserinteractionParent))
         {

            return false;

         }

      }

      return true;

   }


   //bool primitive::create_window_ex(__pointer(::user::system_struct) pcs, ::user::interaction * puiParent, const ::id & id)
   bool primitive::create_host()
   {

      //::exception::throw_interface_only();

      return true;

   }


   //void primitive::BringToTop(::e_display edisplay)
   //{

   //}


   //bool primitive::BringWindowToTop()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   bool primitive::_is_window() const
   {

      return m_bUserPrimitiveOk;

   }


   ::i32 primitive::get_window_long(i32 nIndex) const
   {

      ::exception::throw_interface_only();

      return 0;

   }


   ::i32 primitive::set_window_long(i32 nIndex,::i32 lValue)
   {

      ::exception::throw_interface_only();

      return 0;

   }


   iptr primitive::get_window_long_ptr(i32 nIndex) const
   {

      ::exception::throw_interface_only();

      return 0;

   }


   iptr primitive::set_window_long_ptr(i32 nIndex, iptr lValue)
   {

      ::exception::throw_interface_only();

      return 0;

   }


   bool primitive::RedrawWindow(const ::rect& rectUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      ::exception::throw_interface_only();

      return false;

   }


   ::user::interaction * primitive::ChildWindowFromPoint(const ::point & point)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::ChildWindowFromPoint(const ::point & point,::u32 nFlags)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::get_next_window(bool bIgnoreChildren, const  ::user::interaction * puiInteractionStop) const
   {

      return nullptr;

   }

   
   ::user::interaction * primitive::get_window(enum_next enext) const
   {

      return nullptr;

   }


   //      if(nFlag == GW_HWNDNEXT)
//      {
//
//         return get_next(true, nullptr);
//
//      }
//      else
//      {
//
//         ::exception::throw_interface_only();
//
//         return nullptr;
//
//      }

   ///}


//   ::user::interaction * primitive::get_next_window(bool bIgnoreChildren)
//   {
//
//      ::exception::throw_interface_only();
//
//      return nullptr;
//
//   }


   bool primitive::is_message_only_window() const
   {

      ::exception::throw_interface_only();

      return false;

   }


   ::user::interaction * primitive::get_wnd(::u32 nCmd) const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool primitive::is_active()
   {

      throw interface_only_exception();

      return false;

   }


   ::user::interaction * primitive::GetActiveWindow()
   {

      ::user::interaction * pinteraction = get_wnd();

      if(pinteraction == nullptr)
      {

         return nullptr;

      }

      return pinteraction->GetActiveWindow();

   }


   bool primitive::SetFocus()
   {

      __pointer(::user::interaction) pinteraction = get_wnd();

      if(pinteraction.is_null())
      {

         return false;

      }

      return get_wnd()->SetFocus();

   }


   interaction * primitive::SetActiveWindow()
   {

      //::exception::throw_interface_only();

      return nullptr;

   }


   bool primitive::SetForegroundWindow()
   {

      return true;

   }


   ::user::interaction * primitive::GetLastActivePopup()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   void primitive::edit_on_set_focus(::user::interaction* pinteraction)
   {

   }


   void primitive::edit_on_kill_focus(::user::interaction* pinteraction)
   {

   }


   void primitive::set_window_text(const char * pszString)
   {

   }


   strsize primitive::get_window_text(char * pszStringBuf, strsize nMaxCount)

   {

      ::exception::throw_interface_only();

      return 0;

   }


   string primitive::get_window_text()
   {

      ::exception::throw_interface_only();

      return "";

   }


   void primitive::get_window_text(string & rString)
   {

      ::exception::throw_interface_only();

   }


   strsize primitive::get_window_text_length()
   {

      ::exception::throw_interface_only();

      return 0;

   }


   //::user::interaction * primitive::EnsureTopLevel()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::interaction * primitive::EnsureParentTopLevel()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   ::user::interaction * primitive::get_top_level() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   //::user::interaction * primitive::GetParentTopLevel() const
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::frame * primitive::GetParentTopLevelFrame() const
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::frame * primitive::EnsureParentFrame()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //LRESULT primitive::default_window_procedure()
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   u32 primitive::GetStyle() const
   {

      ::exception::throw_interface_only();

      return 0;

   }


   u32 primitive::GetExStyle() const
   {

      ::exception::throw_interface_only();

      return 0;

   }


   bool primitive::DestroyWindow()
   {

      ::exception::throw_interface_only();

      return false;

   }


   void primitive::destroy_window()
   {

   }


   void primitive::PostNcDestroy()
   {

      finalize();

   }


   ::user::interaction * primitive::get_parent() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::frame * primitive::get_parent_frame() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   void primitive::CalcWindowRect(RECT32 * prect,::u32 nAdjustType)

   {

      ::exception::throw_interface_only();

   }


   void primitive::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::id idLeftOver, ::u32 nFlag, RECT32 * prectParam, const ::rect & rectClient, bool bStretch)
   {

      ::exception::throw_interface_only();

   }


   ::user::primitive * primitive::set_owner(::user::primitive * pinteraction)
   {

      //::exception::throw_interface_only();

      return nullptr;

   }


   ::user::primitive * primitive::set_parent(::user::primitive * pinteraction)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::get_owner() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::frame * primitive::get_owner_frame() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool primitive::is_top_level_window() const
   {

      auto puiParent = get_parent();

      if (::is_null(puiParent))
      {

         return true;

      }

      if (::is_set(get_context_session()))
      {

         if (this == __user_primitive(get_context_session()->m_puiHost))
         {

            return true;

         }
         else if (puiParent == __user_primitive(get_context_session()->m_puiHost))
         {

            return true;

         }

      }

      return false;

   }


   //interaction * primitive::get_parent() const
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   ::user::frame * primitive::frame() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::get_parent_owner() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::get_parent_or_owner() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::get_top_level_owner() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   void primitive::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_client_to_screen(POINT32 * ppt)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_screen_to_client(POINT32 * ppt)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_client_to_screen(RECT32 * prect)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_screen_to_client(RECT32 * prect)
   {

      ::exception::throw_interface_only();

   }


   //i32 primitive::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   ::exception::throw_interface_only();

   //   return -1;

   //}


   //i32 primitive::GetWindowRgn(HRGN hRgn)
   //{

   //   ::exception::throw_interface_only();

   //   return -1;

   //}


   //bool primitive::layout().is_zoomed()
   //{

   //   return false;

   //}


   //bool primitive::layout().is_full_screen()
   //{

   //   return false;

   //}


   //bool primitive::layout().is_iconic()
   //{

   //   return false;

   //}


   bool primitive::CheckAutoCenter()
   {

      ::exception::throw_interface_only();

      return false;

   }


   void primitive::CenterWindow(::user::interaction * pAlternateOwner)
   {

      ::exception::throw_interface_only();

   }


   void primitive::default_message_handler(::message::message * pmessage)
   {


   }


   void primitive::message_handler(::message::base * pbase)
   {

      ::exception::throw_interface_only();

   }


   LRESULT primitive::message_handler(LPMESSAGE pmessage)

   {

      ::exception::throw_interface_only();

      return 0;

   }


#ifdef WINDOWS_DESKTOP


   bool primitive::GetWindowPlacement(WINDOWPLACEMENT* pwndpl)

   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::SetWindowPlacement(const WINDOWPLACEMENT* pwndpl)

   {

      ::exception::throw_interface_only();

      return false;

   }


#endif


   bool primitive::pre_create_window(::user::system * pusersystem)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::IsTopParentActive()
   {

      ::user::interaction * puiTopLevel = get_top_level();

      if (puiTopLevel == nullptr)
      {

         return true;

      }

      //::user::interaction * puiActive = puiTopLevel->GetActiveWindow();

      return puiTopLevel->is_active();

      //return  puiActive == puiTopLevel;

   }


   void primitive::ActivateTopParent()
   {

   }


   void primitive::update_dialog_controls(channel * ptarget)
   {

      //::exception::throw_interface_only();

   }


   void primitive::SetRedraw(bool bRedraw)
   {

      ::exception::throw_interface_only();

   }


   bool primitive::GetUpdateRect(RECT32 * prect,bool bErase)

   {

      ::exception::throw_interface_only();

      return false;

   }


   i32 primitive::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {

      ::exception::throw_interface_only();

      return -1;

   }


   void primitive::InvalidateRect(const ::rect & rect,bool bErase)

   {

      ::exception::throw_interface_only();

   }


   void primitive::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {

      ::exception::throw_interface_only();

   }


   void primitive::ValidateRect(const ::rect & rect)

   {

      ::exception::throw_interface_only();

   }


   void primitive::ValidateRgn(::draw2d::region* pRgn)
   {

      ::exception::throw_interface_only();

   }


   void primitive::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

   }


   void primitive::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {

   }


   void primitive::on_configuration_change(::user::primitive * pprimitiveSource)
   {


   }


   void primitive::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::on_reposition()
   {

      ::exception::throw_interface_only();

   }


   bool primitive::is_this_visible(enum_layout elayout)
   {

      return true;

   }


   void primitive::on_show_window()
   {

      ::exception::throw_interface_only();

   }


   //void primitive::window_show_change_visibility()
   //{


   //}


   void primitive::ShowOwnedPopups(bool bShow)
   {

      ::exception::throw_interface_only();

   }


   bool primitive::attach(oswindow oswindow_New)
   {

      ::exception::throw_interface_only();

      return false;

   }


   oswindow primitive::detach()
   {

      return nullptr;

   }


   void primitive::pre_subclass_window()
   {

      ::exception::throw_interface_only();

   }


   id primitive::run_modal_loop(::user::interaction * pinteraction,u32 dwFlags)
   {

      ::exception::throw_interface_only();

      return ::id();

   }


   id primitive::RunModalLoop(u32 dwFlags)
   {

      ::exception::throw_interface_only();

      return ::id();

   }


   id primitive::_001RunModalLoop(u32 dwFlags)
   {

      ::exception::throw_interface_only();

      return id();

   }


   bool primitive::ContinueModal()
   {

      ::exception::throw_interface_only();

      return false;

   }


   void primitive::EndModalLoop(id nResult)
   {

      ::exception::throw_interface_only();

   }


   bool primitive::post_message(const ::id & id,WPARAM wparam,lparam lparam)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::SetTimer(uptr uEvent, ::millis millisElapse, PFN_TIMER pfnTimer)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::KillTimer(uptr uEvent)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::has_focus()
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::SetCapture(::user::interaction * pinteraction)
   {

      return false;

   }


   ::user::interaction * primitive::GetCapture()
   {

      return nullptr;

   }


   bool primitive::ReleaseCapture()
   {

      return false;

   }


   void primitive::_000OnMouseLeave(::message::message* pmessage)
   {

   }


   void primitive::track_mouse_leave()
   {

      ::exception::throw_interface_only();

   }


   void primitive::track_mouse_hover()
   {

      ::exception::throw_interface_only();

   }


   void primitive::sketch_to_design(::draw2d::graphics_pointer & pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow)
   {

   }


   void primitive::_001UpdateWindow()
   {

   }


   // void primitive::window_apply_visual(const window_state & windowstate)
   // {

   // }


   void primitive::sketch_prepare_window_minimize(::e_activation eactivation)
   {

      ::exception::throw_interface_only();

   }


   void primitive::sketch_prepare_window_maximize()
   {

      ::exception::throw_interface_only();

   }


   void primitive::sketch_prepare_window_full_screen(const ::rect & rectHint)
   {

      ::exception::throw_interface_only();

   }


   void primitive::sketch_prepare_window_restore(edisplay edisplay)
   {

      ::exception::throw_interface_only();

   }


   void primitive::sketch_prepare_window_dock(::e_display edisplayDock)
   {

      ::exception::throw_interface_only();

   }


   void primitive::GuieProc(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

   }


   void primitive::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      ::exception::throw_interface_only();

   }


   void primitive::OnLinkClick(const char * psz,const char * pszTarget)
   {

      ::exception::throw_interface_only();

   }


   void primitive::set_config_fps(double dConfigFps)
   {

      get_host_window()->m_pimpl->set_config_fps(dConfigFps);

   }


   double primitive::get_config_fps()
   {

      return get_host_window()->m_pimpl->get_config_fps();

   }


   double primitive::get_output_fps()
   {

      auto pinteraction = get_host_window();

      if (pinteraction == nullptr)
      {

         return 0.0;

      }

      auto pimpl = pinteraction->m_pimpl;

      if (pimpl.is_null())
      {

         return 0.0;

      }

      return pimpl->get_output_fps();

   }


   bool primitive::create_message_queue(const char * lpszName)
   {

      ::exception::throw_interface_only();

      return false;

   }


   void primitive::on_select()
   {

      ::exception::throw_interface_only();

   }


   bool primitive::is_place_holder()
   {

      ::exception::throw_interface_only();

      return false;

   }


   double primitive::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      return 0.0;

   }


   e_cursor primitive::get_cursor()
   {

      ::exception::throw_interface_only();

      return cursor_none;

   }


   bool primitive::set_cursor(e_cursor ecursor)
   {

      ::exception::throw_interface_only();

      return false;

   }


   ::point primitive::get_cursor_pos() const
   {

      return ::point();

   }

   
   ::sized primitive::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      return { 0.0, 0.0 };

   }


   ::sized primitive::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectd rectPadding(2.0, 2.0, 2.0, 2.0);

      auto sizeFitting = _001CalculateFittingSize(pgraphics);

      ::sized sizePaddedFitting;

      sizePaddedFitting.cx = rectPadding.left + sizeFitting.cx + rectPadding.right;

      sizePaddedFitting.cy = rectPadding.top + sizeFitting.cy + rectPadding.bottom;

      return sizePaddedFitting;

   }


   bool primitive::can_merge(::user::interaction * pinteraction)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::merge(::user::interaction * pinteraction)
   {

      ::exception::throw_interface_only();

      return false;

   }


   ::user::interaction * primitive::top_child()
   {

      return last_child();

   }


   ::user::interaction * primitive::bottom_child()
   {

      return first_child();

   }


   ::user::interaction * primitive::above_sibling(::user::interaction * pinteraction)
   {

      return next_sibling(pinteraction);

   }


   ::user::interaction * primitive::above_sibling()
   {

      return next_sibling();

   }


   ::user::interaction * primitive::under_sibling(::user::interaction * pinteraction)
   {

      return previous_sibling(pinteraction);

   }


   ::user::interaction * primitive::under_sibling()
   {

      return previous_sibling();

   }

   ::user::interaction * primitive::top_sibling()
   {

      return last_sibling();

   }


   ::user::interaction * primitive::bottom_sibling()
   {

      return first_sibling();

      return nullptr;

   }

   ::user::interaction * primitive::first_child()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::last_child()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }

   ::user::interaction * primitive::first_sibling()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::last_sibling()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::previous_sibling()
   {

      return nullptr;

   }

   ::user::interaction * primitive::previous_sibling(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

      return nullptr;

   }

   ::user::interaction * primitive::next_sibling()
   {

      return nullptr;

   }

   ::user::interaction * primitive::next_sibling(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

      return nullptr;

   }


   void primitive::mouse_hover_add(::user::interaction * pinterface)
   {

      ::exception::throw_interface_only();

   }


   bool primitive::mouse_hover_remove(::user::interaction * pinterface)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::on_keyboard_focus(::user::primitive * pfocus)
   {

      //set_need_redraw();

      return true;

   }


   bool primitive::GetFocusRect(RECT32* prect)
   {

      return false;

   }


   void primitive::defer_update_display()
   {


   }


   ::user::primitive * primitive::get_keyboard_focus()
   {

      auto puserinteractionHost = get_host_window();

      if (::is_null(puserinteractionHost))
      {

         return nullptr;

      }

      ::user::primitive * pprimitive = puserinteractionHost->get_keyboard_focus();

      if(pprimitive == nullptr)
      {

         return nullptr;

      }

      return dynamic_cast < ::user::interaction * > (pprimitive);

   }


   i32 primitive::get_descendant_level(const ::user::primitive * pinteraction) const
   {

      ::exception::throw_interface_only();

      return -1;

   }


   //bool primitive::is_descendant(const ::user::primitive * pinteraction,bool bIncludeSelf) const
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   ::e_status primitive::set_tool_window(bool bSet)
   {

      UNREFERENCED_PARAMETER(bSet);

      __throw(interface_only_exception);

      return error_not_implemented;

   }


   ::user::interaction * primitive::get_first_child_window() const
   {

      return nullptr;

   }


   ::user::interaction * primitive::get_next_sibling_window()
   {

      return nullptr;

   }


   ::user::interaction * primitive::get_focusable_descendant() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   void primitive::_001OnTriggerMouseInside()
   {

      ::exception::throw_interface_only();

   }


   bool primitive::update_data(bool bSaveAndValidate)
   {

      ::exception::throw_interface_only();

      return false;

   }


   string primitive::get_window_default_matter()
   {

      ::exception::throw_interface_only();

      return "";

   }


   string primitive::get_window_icon_matter()
   {

      ::exception::throw_interface_only();

      return get_window_default_matter();

   }


   u32 primitive::get_window_default_style()
   {

      ::exception::throw_interface_only();

      return 0;

   }


   ::user::primitive::enum_type primitive::get_window_type()
   {

      return type_window;

   }





   bool primitive::OnCommand(::message::base * pbase)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::OnNotify(::message::base * pbase)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::OnChildNotify(::message::base * pbase)
   {

      ::exception::throw_interface_only();

      return false;

   }





   void primitive::on_command(::user::command * pcommand)
   {

      channel::on_command(pcommand);

   }


   bool primitive::is_selected(::data::item * pitem)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::has_command_handler(::user::command * pcommand)
   {

      ::exception::throw_interface_only();

      return false;

   }


   //bool primitive::track_popup_menu(::user::menu_item * pitem,i32 iFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_menu_text(string strXml,i32 iFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}



   //bool primitive::track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_menu_text(string strXml,i32 iFlags,::message::message * pmessage)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags,::message::message * pmessage)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //bool primitive::track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point & point)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_menu(const ::payload & varXml,i32 iFlags, const ::point & point, const size & size)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags, const ::point & point)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_menu_file(::payload varFile, i32 iFlags, const ::point & point, const ::size & sizeMinimum)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   void primitive::_001OnExitIconic()
   {

   }


   void primitive::_001OnExitFullScreen()
   {

   }


   void primitive::_001OnExitZoomed()
   {

   }


   void primitive::on_add_owned(::user::primitive * pprimitive)
   {


   }


   //void primitive::window_enable_full_screen(bool bEnable)
   //{

   //   ::exception::throw_interface_only();

   //}


   //bool primitive::window_is_full_screen_enabled()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //edisplay primitive::get_display()
   //{

   //   return e_display_none;

   //}


   //edisplay primitive::get_previous_display()
   //{

   //   return e_display_none;

   //}


   //bool primitive::defer_set_appearance(edisplay edisplay)
   //{

   //   if (get_display() == edisplay)
   //   {

   //      return false;

   //   }

   //   return set_appearance(edisplay);

   //}

   //bool primitive::set_appearance(edisplay edisplay)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::set_previous_display(edisplay edisplay)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   void primitive::show_keyboard(bool bShow)
   {

      UNREFERENCED_PARAMETER(bShow);

   }




   void primitive::keep_alive(::object * pliveobject)
   {

      ::exception::throw_interface_only();

   }


   //bool primitive::set_window_pos(class zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   id primitive::GetDlgCtrlId() const
   {

      ::exception::throw_interface_only();

      return id();

   }


   id primitive::SetDlgCtrlId(id id)
   {

      ::exception::throw_interface_only();

      return ::id();

   }


#ifdef WINDOWS_DESKTOP

   bool primitive::open_clipboard()
   {

      __throw(interface_only_exception);

      return false;

   }


   bool primitive::close_clipboard()
   {

      __throw(interface_only_exception);

      return false;

   }


#endif


   //oswindow primitive::get_safe_handle() const
   //{

   //   if(::is_null(this))
   //      return nullptr;

   //   return get_handle();

   //}


   ::graphics::graphics * primitive::get_window_graphics()
   {

      return nullptr;

   }


   bool primitive::is_composite()
   {

      return true; // optimistic response, assume always true alpha blendable

   }


   //void primitive::_user_message_handler(::message::message * pmessage)
   //{
   //}

   //::message::PFN_DISPATCH_MESSAGE_HANDLER primitive::_calc_user_message_handler()
   //{
   //   return &::user::primitive::_user_message_handler;
   //}

   //void primitive::_001OnTimer(::timer * ptimer)
   //{



   //}


   bool primitive::has_pending_graphical_update()
   {

      return false;

   }


   void primitive::on_after_graphical_update()
   {

   }


   void primitive::set_bitmap_source(string strBitmapSource)
   {

   }

   void primitive::clear_bitmap_source()
   {

   }


   bool primitive::WfiOnStartDock()
   {

      return true;

   }


   void primitive::WfiOnDock(edisplay edisplay)
   {

   }


   void primitive::design_down()
   {

   }


   void primitive::design_up()
   {

   }


   void primitive::WfiOnRestore()
   {

   }


   void primitive::WfiOnMinimize(bool bNoActivate)
   {

   }


   void primitive::WfiOnMaximize()
   {

   }


   void primitive::WfiOnFullScreen()
   {

   }


   //void primitive::WfiOnExitFullScreen()
   //{

   //}


   void primitive::WfiOnClose()
   {

   }


   void primitive::WfiOnNotifyIcon()
   {

   }


   void primitive::prodevian_redraw(bool bUpdateBuffer)
   {

   }


   void primitive::prodevian_stop()
   {


   }


} // namespace user









namespace user
{


   bool primitive::post_simple_command(const e_simple_command & ecommand, lparam lparam)
   {

      post_message(e_message_simple_command, (WPARAM)ecommand, lparam);

      return true;

   }


   void primitive::on_simple_command(::message::simple_command * psimplecommand)
   {

      if (psimplecommand->m_esimplecommand == simple_command_full_screen)
      {

         get_wnd()->display(e_display_full_screen);

         psimplecommand->m_bRet = true;

      }

   }


   __pointer(::message::base) primitive::get_message_base(oswindow oswindow, const ::id & id, WPARAM wparam, lparam lparam)
   {

      __pointer(::message::base) pbase;

      auto eprototype = ::message::get_message_prototype((enum_message) id.i64(), 0);

      switch (eprototype)
      {
      case ::message::PrototypeNone:
      {

         pbase = __new(::message::base);

      }
      break;
      case ::message::PrototypeCreate:
      {
         pbase = __new(::message::create);
      }
      break;
      case ::message::PrototypeEnable:
      {
         pbase = __new(::message::enable);
      }
      break;
      case ::message::PrototypeNcActivate:
      {
         pbase = __new(::message::nc_activate);
      }
      break;
      case ::message::PrototypeKey:
      {
         pbase = __new(::message::key);
      }
      break;
      case ::message::PrototypeTimer:
      {
         
         //__throw(::exception::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));
         
         pbase = __new(::message::timer);

      }
      break;
      case ::message::PrototypeShowWindow:
      {
         pbase = __new(::message::show_window);
      }
      break;
      case ::message::PrototypeSetCursor:
      {
         pbase = __new(::message::set_cursor);
      }
      break;
      case ::message::PrototypeNcHitTest:
      {
         pbase = __new(::message::nchittest);
      }
      break;
      case ::message::PrototypeMove:
      {
         pbase = __new(::message::move);
      }
      break;
      case ::message::PrototypeEraseBkgnd:
      {
         pbase = __new(::message::erase_bkgnd);
      }
      break;
      case ::message::PrototypeScroll:
      {
         pbase = __new(::message::scroll);
      }
      break;
      case ::message::PrototypeSetFocus:
      {
         pbase = __new(::message::set_focus);
      }
      break;
      case ::message::PrototypeKillFocus:
      {
         pbase = __new(::message::kill_focus);
      }
      break;
#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
      case ::message::PrototypeWindowPos:
      {
         pbase = __new(::message::window_pos);
      }
      break;
      case ::message::PrototypeNcCalcSize:
      {
         pbase = __new(::message::nc_calc_size);
      }
      break;
#endif
      case ::message::PrototypeMouse:
      {
         pbase = __new(::message::mouse);
      }
      break;
      case ::message::PrototypeMouseWheel:
      {
         pbase = __new(::message::mouse_wheel);
      }
      break;
      case ::message::PrototypeSize:
      {
         pbase = __new(::message::size);
      }
      break;
      case ::message::PrototypeActivate:
      {
         pbase = __new(::message::activate);
      }
      break;
      case ::message::PrototypeMouseActivate:
      {
         pbase = __new(::message::mouse_activate);
      }
      break;
      case ::message::PrototypeSimpleCommand:
      {
         pbase = __new(::message::simple_command);
      }
      break;
      default:
      {
         pbase = __new(::message::base);
      }
      break;
      }

      if (pbase.is_null())
      {

         return nullptr;

      }

      pbase->set(oswindow, this, id, wparam, lparam);

      return pbase;

   }


   bool primitive::call_message_handler(const ::id & id, WPARAM wparam, lparam lparam, LRESULT * plresult)
   {

      auto pbase = get_message_base(get_handle(), id, wparam, lparam);

      try
      {

         message_handler(pbase);

      }
      catch (exception_pointer pe)
      {

         if (::get_thread()->handle_exception(pe))
         {

            return false;

         }

      }
      catch (...)
      {

      }

      if (!pbase->m_bRet)
      {

         return false;

      }

      if (plresult)
      {

         try
         {

            *plresult = pbase->m_lresult;

         }
         catch (...)
         {

         }

      }

      return true;

   }

/*
   primitive::primitive()
   {

      m_puiThis = nullptr;

   }


   primitive::~primitive()
   {


   }
*/

#ifdef WINDOWS_DESKTOP


   //bool primitive::GetWindowPlacement(WINDOWPLACEMENT * pwndpl)

   //{

   //   UNREFERENCED_PARAMETER(pwndpl);


   //   return false;

   //}

   //bool primitive::SetWindowPlacement(const WINDOWPLACEMENT * pcwndpl)

   //{

   //   UNREFERENCED_PARAMETER(pcwndpl);


   //   return false;

   //}


#endif // WINDOWS_DESKTOP


   //::form_property_set * primitive::get_form_property_set()
   //{

   //   auto pformpropertyset = GetTypedParent < ::form_property_set >();

   //   if (::is_set(pformpropertyset))
   //   {

   //      return pformpropertyset->get_form_property_set();

   //   }

   //   return get_context_application();

   //}


//   bool primitive::SetPlacement(const ::rect & rect, ::u32 nFlags)
//   {
//
//      UNREFERENCED_PARAMETER(rect);
//      UNREFERENCED_PARAMETER(nFlags);
//
//      return false;
//
//   }


   i32 primitive::get_total_page_count(::promise::context * pcontext)
   {

      return 1;

   }



   //void primitive::_001OnTimer(::timer * ptimer)
   //{

   //   UNREFERENCED_PARAMETER(ptimer);

   //}

   //void primitive::add_thread(::thread * pthread)
   //{

   //   sync_lock sl(mutex());

   //   m_threadptra.add(pthread);

   //}


   //void primitive::remove_thread(::thread * pthread)
   //{

   //   sync_lock sl(mutex());

   //   m_threadptra.remove(pthread);

   //}

   //bool primitive::enable_window(bool bEnableWindow)
   //{

   //   return true;

   //}


   // Text Edit
   void primitive::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {


   }


   index primitive::plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   index primitive::plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x)
   {

      return -1;

   }


   index primitive::plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   index primitive::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   {

      return -1;

   }


   strsize primitive::plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn)
   {

      return -1;

   }


   strsize primitive::plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x)
   {

      return -1;

   }


   index primitive::plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }




   void primitive::keyboard_focus_OnTimer(i32 iTimer)
   {
      UNREFERENCED_PARAMETER(iTimer);
   }

   void primitive::keyboard_focus_OnChar(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void primitive::keyboard_focus_OnSysChar(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void primitive::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

   }


   void primitive::keyboard_focus_OnKeyUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void primitive::route_control_event(::user::control_event* pevent)
   {

      on_control_event(pevent);

   }


   void primitive::on_control_event(control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


   bool primitive::keyboard_focus_is_focusable() const
   {

      return Application.keyboard_focus_is_focusable(this);

   }


   bool primitive::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      return true;

   }


   bool primitive::keyboard_focus_OnChildKillFocus()
   {

      return true;

   }


   primitive * primitive::keyboard_set_focus_next(bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

      primitive * pprimitive = keyboard_get_next_focusable(nullptr, bSkipChild, bSkipSiblings, bSkipParent);

      auto psession = Session;

      if (pprimitive == nullptr || pprimitive == this)
      {

         clear_keyboard_focus();

      }
      else
      {

         pprimitive->set_keyboard_focus();

      }

      return get_keyboard_focus();

   }


   primitive * primitive::keyboard_get_next_focusable(primitive * pfocus, bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

      __pointer(primitive) puiThis = this;

      __pointer(primitive) puiFocus = pfocus != nullptr ? pfocus : this;



      primitive * pfocusTry;

      if (puiFocus == nullptr)
         return nullptr;

      if (puiThis == nullptr)
         return nullptr;

      single_lock(puiThis->get_context_application()->mutex(), TRUE);

      __pointer(primitive) pinteraction;

      if (!bSkipChild)
      {

         pinteraction = puiThis->first_child_user_primitive();

         if (pinteraction != nullptr)
         {

            if (pinteraction->keyboard_focus_is_focusable())
               return pinteraction;

            pinteraction = pinteraction->keyboard_get_next_focusable(puiFocus, false, false, true);

            if (pinteraction != nullptr)
               return pinteraction;

         }

      }

      if (!bSkipSiblings)
      {

         pinteraction = puiThis->next_user_primitive();

         while (pinteraction != nullptr)
         {

            if (pinteraction->keyboard_focus_is_focusable())
               return pinteraction;

            pfocusTry = pinteraction->keyboard_get_next_focusable(puiFocus, false, true, true);

            if (pfocusTry != nullptr)
               return pfocusTry;

            pinteraction = pinteraction->next_user_primitive();

         }

      }

      if (!bSkipParent)
      {


         if (puiThis->get_parent() != nullptr)
         {

            pinteraction = puiThis->get_parent_window()->keyboard_get_next_focusable(puiFocus, true);

            if (pinteraction.is_set())
               return pinteraction;

         }

      }

      if (!bSkipSiblings)
      {

         pinteraction = puiThis->first_child_user_primitive();

         if (pinteraction != puiThis)
         {

            while (pinteraction != nullptr && pinteraction != puiFocus)
            {

               if (pinteraction->keyboard_focus_is_focusable())
                  return pinteraction;

               pfocusTry = pinteraction->keyboard_get_next_focusable(puiFocus, false, true, true);

               if (pfocusTry != nullptr)
                  return pfocusTry;

               pinteraction = pinteraction->next_user_primitive();

            }

         }

      }


      return nullptr;

   }


   primitive * primitive::get_keyboard_focus() const
   {

      return nullptr;

   }


   ::e_status primitive::set_keyboard_focus()
   {

      return ::error_interface_only;

   }


   ::e_status primitive::remove_keyboard_focus()
   {

      return ::error_interface_only;

   }


   ::e_status primitive::clear_keyboard_focus()
   {

      return ::error_interface_only;

   }


   // mouse focus

   void primitive::mouse_focus_OnLButtonUp(::message::message * pmessage)
   {
   }


   bool primitive::_001CanEnterScreenSaver()
   {
   
      return false;
   
   }


   ::user::primitive * primitive::first_child_user_primitive()
   {

      return nullptr;

   }


   ::user::primitive * primitive::top_user_primitive()
   {

      return nullptr;

   }


   ::user::primitive * primitive::under_user_primitive()
   {

      return nullptr;

   }


   ::user::primitive * primitive::above_user_primitive()
   {

      return nullptr;

   }


   ::user::primitive * primitive::next_user_primitive()
   {

      return nullptr;

   }


   ::user::primitive * primitive::previous_user_primitive()
   {

      return nullptr;

   }


   ::user::interaction * primitive::get_parent_window() const
   {

      return nullptr;

   }


   //::user::primitive * primitive::get_wnd_primitive() const
   //{

   //   return nullptr;

   //}


   void primitive::_001OnTimer(::timer * ptimer)
   {

      UNREFERENCED_PARAMETER(ptimer);

   }


   void primitive::on_reset_focus_start_tick()
   {

      m_millisFocusStart.Now();

   }


   //bool primitive::_is_window() const
   //{

   //   return m_bUserPrimitiveOk;

   //}


   void primitive::set_need_redraw(bool bAscendants)
   {

      UNREFERENCED_PARAMETER(bAscendants);

   }


   void primitive::set_need_load_form_data()
   {


   }


   void primitive::set_need_save_form_data()
   {


   }


   void primitive::post_redraw(bool bAscendants)
   {

      UNREFERENCED_PARAMETER(bAscendants);

   }


   bool primitive::hide()
   {

      return false;

   }



   void primitive::edit_on_text(string str)
   {

   }


   void primitive::edit_on_sel(strsize iBeg, strsize iEnd)
   {

   }


   void primitive::insert_text(string str, bool bForceNewStep, const ::action_context & context)
   {

   }


   void primitive::on_text_composition(string str)
   {

   }


   void primitive::on_text_commit(string str)
   {

   }


   void primitive::on_text_composition_done()
   {

   }


   bool primitive::is_text_composition_active()
   {

      return false;

   }


   void primitive::set_input_content_rect(const rect& rect)
   {

   }


   void primitive::set_input_selection_rect(const rect& rect)
   {

   }


   rect primitive::get_input_content_rect()
   {

      return rect();

   }


   rect primitive::get_input_selection_rect()
   {

      return rect();

   }


   void primitive::InputConnectionBeginBatchEdit()
   {


   }


   void primitive::InputConnectionEndBatchEdit()
   {


   }


   void primitive::InputConnectionCommitText(const string & str, strsize iNewCursorPosition)
   {


   }


   void primitive::InputConnectionSetComposingText(const string & str, strsize iNewCursorPosition)
   {


   }


   void primitive::InputConnectionSetComposingRegion(strsize iStart, strsize iEnd)
   {

   }


   void primitive::InputConnectionSetSelection(strsize iStart, strsize iEnd)
   {

   }


   void primitive::InputConnectionFinishComposingText()
   {


   }


   bool primitive::set_icon(::draw2d::icon * picon, bool bSmall)
   {

      return false;

   }


   bool primitive::display(::e_display edisplay, ::e_activation eactivation)
   {

      return true;

   }

} // namespace user



