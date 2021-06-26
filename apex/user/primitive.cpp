#include "framework.h"
//#include "apex/user/_user.h"
//#include "aura/message.h"
#include "acme/const/simple_command.h"
#include "apex/message/simple_command.h"
//#include "aura/message/timer.h"


namespace user
{


   primitive::primitive()
   {

   }


   primitive::~primitive()
   {

   }


   //::user::callback* primitive::get_user_callback()
   //{

   //   return nullptr;

   //}


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

   //   wndpa = *dynamic_cast < ::user::interaction_pointer_array * >(this);

   //}


//   void primitive::TwfGetWndArray(::user::oswindow_array & oswindowa)
//   {
//
//      ::user::interaction_pointer_array & wndpa = *dynamic_cast < ::user::interaction_pointer_array * >(this);
//
//      oswindowa = wndpa.get_hwnda();
//
//   }
//
//
//   void primitive::RedrawOptimize(rectangle_i32_array &array)
//   {
//
//      ::rectangle_i32 rectangle;
//
//Restart:
//
//      for(i32 i = 0; i < array.get_size(); i++)
//      {
//         for(i32 j = i + 1; j < array.get_size(); j++)
//         {
//            if(RedrawOptimize(
//                  rectangle,
//                  array[i],
//                  array[j]))
//            {
//               array[i] = rectangle;
//               array.erase_at(j);
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
//   bool primitive::RedrawOptimize(RECTANGLE_I32 * prectOut, const rectangle_i32 & rect1Param, const rectangle_i32 & rect2Param)
//   {
//
//      ::rectangle_i32 rect1(rect1Param);
//
//      ::rectangle_i32 rect2(rect2Param);
//
//      ::rectangle_i32 rect3;
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

      return nullptr;

      //auto puserinteraction = get_wnd();

      //if (::is_null(puserinteraction))
      //{

      //   return get_application();

      //}

      //return puserinteraction->m_pthreadUserInteraction;

   }



   //::user::interaction_impl * primitive::get_impl() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   if (pinteraction->m_pimpl.is_null())
   //   {

   //      return nullptr;

   //   }

   //   try
   //   {

   //      return pinteraction->m_pimpl->get_impl();

   //   }
   //   catch (...)
   //   {

   //   }

   //   return nullptr;

   //}


   //bool primitive::is_window_enabled() const
   //{

   //   auto puiParent = get_parent();

   //   if (puiParent != nullptr)
   //   {

   //      if (!puiParent->is_window_enabled())
   //      {

   //         return false;

   //      }

   //   }

   //   return is_this_enabled();

   //}


   //bool primitive::is_this_enabled() const
   //{

   //   return true;

   //}


   ::user::interaction* primitive::get_host_window() const
   {

      //if (get_session() == nullptr
      //   || get_session()->m_paurasession == nullptr)
      //{

      //   return nullptr;

      //}

      //if (get_session()->m_paurasession->m_puserinteractionHost)
      //{

      //   return __user_interaction(get_session()->m_paurasession->m_puserinteractionHost);

      //}
      //else
      //{

         return get_wnd();

      //}

   }


   bool primitive::enable_window(bool bEnable)
   {

      UNREFERENCED_PARAMETER(bEnable);

      return false;

   }


   //void primitive::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


   //void primitive::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   _001OnDraw(pgraphics);
   //   _008OnDraw(pgraphics);

   //}


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


   //bool primitive::Redraw(rectangle_i32_array & recta)
   //{

   //   bool bOk = true;

   //   for(i32 i = 0; i < recta.get_size(); i++)
   //   {

   //      if(!get_wnd()->RedrawWindow(recta[i]))
   //         bOk = false;

   //   }

   //   return bOk;

   //}


   //bool primitive::Redraw(const ::rectangle_i32 & rectangle, ::draw2d::region * prgn)
   //{

   //   if (get_wnd() == nullptr)
   //   {

   //      return false;

   //   }

   //   return get_wnd()->RedrawWindow(rectangle, prgn, RDW_INVALIDATE);

   //}


   //bool primitive::Redraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   UNREFERENCED_PARAMETER(pgraphics);

   //   if(get_wnd() == nullptr)
   //      return false;

   //   return get_wnd()->RedrawWindow();

   //}


   /*bool primitive::client_to_screen(RECTANGLE_I32 * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }


   bool primitive::client_to_screen(RECTANGLE_F64 * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }
*/

   //bool primitive::client_to_screen(POINT_I32 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool primitive::client_to_screen(POINT_F64 * ppoint)
   //{

   //   ::offset(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool primitive::client_to_screen(RECTANGLE_I64 * prectangle)
   //{

   //   ::offset_rect(prectangle, point_i64(client_screen_top_left()));

   //   return true;

   //}


   //bool primitive::client_to_screen(POINT_I64 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool primitive::screen_to_client(RECTANGLE_I32 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::screen_to_client(RECTANGLE_F64 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::screen_to_client(POINT_I32 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::screen_to_client(POINT_F64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::screen_to_client(RECTANGLE_I64 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::screen_to_client(POINT_I64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool primitive::GetWindowPos(RECTANGLE_I32 * prectangle)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::get_window_rect(RECTANGLE_I32 * prectangle)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //point_f64 primitive::client_screen_top_left()
   //{

   //   return nullptr;

   //}


   //bool primitive::get_client_rect(RECTANGLE_I32 * prectangle)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::get_client_rect(RECTANGLE_I64 * prectangle)

   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::get_window_rect(RECTANGLE_I64 * prectangle)

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



   //bool primitive::SetPlacement(const ::rectangle_i32 & rectangle,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   bool primitive::add_prodevian(::matter * pmatter)
   {

      return false;

   }


   bool primitive::erase_prodevian(::matter * pmatter)
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

   //   return papplication->sync_message_box_timeout(this, pszMessage, get_title(), durationTimeOut, fuStyle);

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

   //   return message_box(payload);

   //}


   //void primitive::message_box_timeout(string strMessage, ::duration durationTimeout, ::u32 fuStyle)
   //{

   //   fork([=]()
   //      {

   //         sync_message_box_timeout(strMessage, durationTimeout, fuStyle);

   //      });

   //}
   //bool primitive::place(const ::rectangle_i32 & rectangle)
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


   //bool primitive::move_to(const ::point_i32 & point)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::SizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::set_size(const size_i32 & sz)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::ResizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::ResizeWindow(const size_i32 & sz,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::set_window_position(class zorder zorder, const ::rectangle_i32 & rectangle, ::u32 nFlags)

   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}

   //bool primitive::defer_set_window_pos(iptr z, const  const rectangle_i32 & & rectangle, ::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(get_window_rect) different of rectangle_i32(x, y, cx, cy)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::defer_set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(get_window_rect) different of rectangle_i32(x, y, cx, cy)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //void primitive::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::_001PrintBuffer(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::_001Print(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   ::user::interaction * primitive::_001FromPoint(::point_i32 point,bool bTestedIfParentVisible)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool primitive::_001IsPointInside(const ::point_i32 & point)
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


   ::e_status primitive::interaction_branch(const ::routine & routine)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   lresult primitive::send(::message::message * pmessage)
   {

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   // pmessage object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   bool primitive::post(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

      return false;

   }


   lresult primitive::send_message(const ::id & id,wparam wparam,lparam lparam, const ::point_i32& point)
   {

      return message_call(id, wparam, lparam, point);

   }


   lresult primitive::message_call(const ::id & id, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      return 0;

   }


   lresult primitive::message_call(::message::message * pmessage)
   {

      return 0;

   }


#ifdef LINUX


   lresult primitive::send_x11_event(void * pevent)
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


   //bool primitive::ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::display(::e_display edisplay)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   // void primitive::SetWindowDisplayChanged()
   // {


   // }


   //::user::frame * primitive::top_level_frame() const
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   void primitive::send_message_to_descendants(const ::id & id,wparam wparam,lparam lparam,bool bDeep,bool bOnlyPerm)

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


   //oswindow primitive::get_oswindow() const
   //{

   //   return nullptr;

   //}


   ::windowing::window * primitive::get_window() const
   {

      return nullptr;

   }


   string primitive::get_class_name()
   {

      return "";

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


   ::e_status primitive::create_child(::user::interaction * puserinteractionParent)
   {

      ::exception::throw_interface_only();

      return ::success;

   }

   
   ::e_status primitive::create_control(::user::interaction * puserinteractionParent, const ::id & id)
   {

      m_id = id;

      auto estatus = create_child(puserinteractionParent);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

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


   ::e_status primitive::create_interaction(::user::interaction * puserinteractionParent, const ::id & id)
   {

      if (!id.is_empty())
      {

         m_id = id;

      }

      ::e_status estatus;

      if (!puserinteractionParent)
      {

         estatus = create_host();

      }
      else
      {

         estatus = create_child(puserinteractionParent);

      }

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //bool primitive::create_window_ex(__pointer(::user::system) pcs, ::user::interaction * puiParent, const ::id & id)
   ::e_status primitive::create_host()
   {

      __throw(error_interface_only);

      return ::error_no_interface;

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


   ::user::interaction* primitive::first_child()
   {

      return nullptr;

   }


   ::user::interaction* primitive::last_child()
   {

      return nullptr;

   }


   ::user::interaction* primitive::last_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::next_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::previous_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::first_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::next_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }


   ::user::interaction* primitive::previous_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }

   
   ::user::interaction* primitive::bottom_child()
   {

      return nullptr;

   }


   ::user::interaction* primitive::top_child()
   {

      return nullptr;

   }


   ::user::interaction* primitive::bottom_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::under_sibling()
   {

      return nullptr;

   }



   ::user::interaction* primitive::above_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::top_sibling()
   {

      return nullptr;

   }


   ::user::interaction* primitive::above_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }


   ::user::interaction* primitive::under_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }



   //::i32 primitive::get_window_long(i32 nIndex) const
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //::i32 primitive::set_window_long(i32 nIndex,::i32 lValue)
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //iptr primitive::get_window_long_ptr(i32 nIndex) const
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //::e_status primitive::set_window_long_ptr(i32 nIndex, iptr lValue)
   //{

   //   ::exception::throw_interface_only();

   //   return ::error_interface_only;

   //}


   //bool primitive::RedrawWindow(const ::rectangle_i32& rectUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   ::user::interaction * primitive::ChildWindowFromPoint(const ::point_i32 & point)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * primitive::ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags)
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


   //bool primitive::is_active() const
   //{

   //   throw interface_only_exception();

   //   return false;

   //}


   //::user::interaction * primitive::GetActiveWindow()
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if(pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetActiveWindow();

   //}


   //bool primitive::SetFocus()
   //{

   //   __pointer(::user::interaction) pinteraction = get_wnd();

   //   if(pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   return get_wnd()->SetFocus();

   //}


   //interaction * primitive::SetActiveWindow()
   //{

   //   //::exception::throw_interface_only();

   //   return nullptr;

   //}


   //bool primitive::SetForegroundWindow()
   //{

   //   return true;

   //}


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


   //lresult primitive::default_window_procedure()
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //u32 primitive::GetStyle() const
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //u32 primitive::GetExStyle() const
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   bool primitive::start_destroying_window()
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


   //::user::frame * primitive::get_parent_frame() const
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //void primitive::CalcWindowRect(RECTANGLE_I32 * prectangle,::u32 nAdjustType)

   //{

   //   ::exception::throw_interface_only();

   //}


   void primitive::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::id idLeftOver, ::u32 nFlag, RECTANGLE_I32 * prectParam, const ::rectangle_i32 & rectangleClient, bool bStretch)
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


   /*::user::frame * primitive::get_owner_frame() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }*/


   bool primitive::is_top_level_window() const
   {

     auto puiParent = get_parent_primitive();

     if (::is_null(puiParent))
     {

        return true;

     }

     if (::is_set(get_session()))
     {

        if (this == get_session()->m_puserprimitiveHost)
        {

           return true;

        }
        else if (puiParent == get_session()->m_puserprimitiveHost)
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


   //::user::frame * primitive::frame() const
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


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


   void primitive::viewport_client_to_screen(POINT_I32 * ppt)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_screen_to_client(POINT_I32 * ppt)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_client_to_screen(RECTANGLE_I32 * prectangle)
   {

      ::exception::throw_interface_only();

   }


   void primitive::viewport_screen_to_client(RECTANGLE_I32 * prectangle)
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


   void primitive::message_handler(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

   }


   //lresult primitive::message_handler(MESSAGE * pmessage)
   //{

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   bool primitive::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }
//
//
//   bool primitive::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   //bool primitive::pre_create_window(::user::system * pusersystem)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::IsTopParentActive()
   //{

   //   ::user::interaction * puiTopLevel = get_top_level();

   //   if (puiTopLevel == nullptr)
   //   {

   //      return true;

   //   }

   //   //::user::interaction * puiActive = puiTopLevel->GetActiveWindow();

   //   return puiTopLevel->is_active_window();

   //   //return  puiActive == puiTopLevel;

   //}


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


   bool primitive::GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase)

   {

      ::exception::throw_interface_only();

      return false;

   }


   //i32 primitive::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   ::exception::throw_interface_only();

   //   return -1;

   //}


   //void primitive::InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase)

   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::ValidateRect(const ::rectangle_i32 & rectangle)

   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::ValidateRgn(::draw2d::region* pRgn)
   //{

   //   ::exception::throw_interface_only();

   //}


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


   //void primitive::ShowOwnedPopups(bool bShow)
   //{

   //   ::exception::throw_interface_only();

   //}


   //bool primitive::attach(oswindow oswindow)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


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


   bool primitive::post_message(const ::id & id,wparam wparam,lparam lparam)
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


   //bool primitive::has_keyboard_focus() const
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::set_capture(::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   //::user::interaction * primitive::get_capture() const
   //{

   //   return nullptr;

   //}



   //bool primitive::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   //::user::interaction * primitive::get_keyboard_focus() const
   //{

   //   return nullptr;

   //}




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


   void primitive::sketch_prepare_window_full_screen(const ::rectangle_i32 & rectHint)
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


   //void primitive::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   //void primitive::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::exception::throw_interface_only();

   //}


   void primitive::OnLinkClick(const char * psz,const char * pszTarget)
   {

      ::exception::throw_interface_only();

   }


   //void primitive::set_config_fps(double dConfigFps)
   //{

   //   //get_host_window()->m_pimpl->set_config_fps(dConfigFps);

   //}


   //double primitive::get_config_fps()
   //{

   //   //return get_host_window()->m_pimpl->get_config_fps();

   //}


   //double primitive::get_output_fps()
   //{

   //   //auto pinteraction = get_host_window();

   //   //if (pinteraction == nullptr)
   //   //{

   //   //   return 0.0;

   //   //}

   //   //auto pimpl = pinteraction->m_pimpl;

   //   //if (pimpl.is_null())
   //   //{

   //   //   return 0.0;

   //   //}

   //   //return pimpl->get_output_fps();
   //   return 0.0;

   //}


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


   ::windowing::cursor * primitive::get_mouse_cursor()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::e_status primitive::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      return success_none;

   }


   //::e_status primitive::set_cursor(::windowing::/*cursor * pcursor)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}

   //::point_i32 primitive::get_cursor_position() const
   //{

   //   return ::point_i32();

   //}

   
   //::size_f64 primitive::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   return { 0.0, 0.0 };

   //}


   //::size_f64 primitive::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::rectangle_f64 rectPadding(2.0, 2.0, 2.0, 2.0);

   //   auto sizeFitting = _001CalculateFittingSize(pgraphics);

   //   ::size_f64 sizePaddedFitting;

   //   sizePaddedFitting.cx = rectPadding.left + sizeFitting.cx + rectPadding.right;

   //   sizePaddedFitting.cy = rectPadding.top + sizeFitting.cy + rectPadding.bottom;

   //   return sizePaddedFitting;

   //}


   //bool primitive::can_merge(::user::interaction * pinteraction)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool primitive::merge(::user::interaction * pinteraction)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //::user::interaction * primitive::top_child()
   //{

   //   return last_child();

   //}


   //::user::interaction * primitive::bottom_child()
   //{

   //   return first_child();

   //}


   //::user::interaction * primitive::above_sibling(::user::interaction * pinteraction)
   //{

   //   return next_sibling(pinteraction);

   //}


   //::user::interaction * primitive::above_sibling()
   //{

   //   return next_sibling();

   //}


   //::user::interaction * primitive::under_sibling(::user::interaction * pinteraction)
   //{

   //   return previous_sibling(pinteraction);

   //}


   //::user::interaction * primitive::under_sibling()
   //{

   //   return previous_sibling();

   //}

   //::user::interaction * primitive::top_sibling()
   //{

   //   return last_sibling();

   //}


   //::user::interaction * primitive::bottom_sibling()
   //{

   //   return first_sibling();

   //   return nullptr;

   //}

   //::user::interaction * primitive::first_child()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::interaction * primitive::last_child()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}

   //::user::interaction * primitive::first_sibling()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::interaction * primitive::last_sibling()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::interaction * primitive::previous_sibling()
   //{

   //   return nullptr;

   //}

   //::user::interaction * primitive::previous_sibling(::user::interaction * pinteraction)
   //{

   //   UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}

   //::user::interaction * primitive::next_sibling()
   //{

   //   return nullptr;

   //}

   //::user::interaction * primitive::next_sibling(::user::interaction * pinteraction)
   //{

   //   UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}


   //void primitive::mouse_hover_add(::user::interaction * pinterface)
   //{

   //   ::exception::throw_interface_only();

   //}


   //bool primitive::mouse_hover_erase(::user::interaction * pinterface)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //void primitive::_task_transparent_mouse_event()
   //{


   //}


   void primitive::on_set_keyboard_focus()
   {

   }


   void primitive::on_kill_keyboard_focus()
   {

   }


   bool primitive::GetFocusRect(RECTANGLE_I32* prectangle)
   {

      return false;

   }


   void primitive::defer_update_display()
   {


   }


   //::user::primitive * primitive::get_keyboard_focus()
   //{

   //   auto puserinteractionHost = get_host_window();

   //   if (::is_null(puserinteractionHost))
   //   {

   //      return nullptr;

   //   }

   //   ::user::primitive * pprimitive = puserinteractionHost->get_keyboard_focus();

   //   if(pprimitive == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return dynamic_cast < ::user::interaction * > (pprimitive);

   //}


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

      __throw(error_interface_only);

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





   bool primitive::OnCommand(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::OnNotify(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::OnChildNotify(::message::message * pmessage)
   {

      ::exception::throw_interface_only();

      return false;

   }





   void primitive::on_command(::message::command * pcommand)
   {

      channel::on_command(pcommand);

   }


   bool primitive::is_selected(::data::item * pitem)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool primitive::has_command_handler(::message::command * pcommand)
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


   //bool primitive::track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point_i32 & point)
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_menu(const ::payload & varXml,i32 iFlags, const ::point_i32 & point, const size_i32 & size)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags, const ::point_i32 & point)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //__pointer(::user::menu) primitive::track_popup_xml_menu_file(::payload varFile, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum)
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


   //bool primitive::set_window_position(class zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
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


//#ifdef WINDOWS_DESKTOP
//
//   bool primitive::open_clipboard()
//   {
//
//      __throw(error_interface_only);
//
//      return false;
//
//   }
//
//
//   bool primitive::close_clipboard()
//   {
//
//      __throw(error_interface_only);
//
//      return false;
//
//   }
//
//
//#endif


   //oswindow primitive::get_safe_handle() const
   //{

   //   if(::is_null(this))
   //      return nullptr;

   //   return get_handle();

   //}


   //::graphics::graphics * primitive::get_window_graphics()
   //{

   //   return nullptr;

   //}


   //bool primitive::is_composite()
   //{

   //   return true; // optimistic response, assume always true alpha blendable

   //}


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


   bool primitive::post_simple_command(const enum_simple_command & ecommand, lparam lparam)
   {

      post_message(e_message_simple_command, (wparam)ecommand, lparam);

      return true;

   }


   void primitive::on_simple_command(::message::simple_command * psimplecommand)
   {

      if (psimplecommand->command() == e_simple_command_full_screen)
      {

         //get_wnd()->display(e_display_full_screen);

         psimplecommand->m_bRet = true;

      }

   }


//   __pointer(::message::message) primitive::get_message(const ::id & id, wparam wparam, lparam lparam)
//   {
//
//      __pointer(::message::message) pmessage;
//
//      auto eprototype = ::message::get_message_prototype((enum_message) id.i64(), 0);
//
//      switch (eprototype)
//      {
//      case ::message::PrototypeNone:
//      {
//
//         pmessage = __new(::user::message);
//
//      }
//      break;
//      case ::message::PrototypeCreate:
//      {
//         pmessage = __new(::message::create);
//      }
//      break;
//      case ::message::PrototypeEnable:
//      {
//         pmessage = __new(::message::enable);
//      }
//      break;
//      case ::message::PrototypeNcActivate:
//      {
//         pmessage = __new(::message::nc_activate);
//      }
//      break;
//      case ::message::PrototypeKey:
//      {
//         pmessage = __new(::message::key);
//      }
//      break;
//      case ::message::PrototypeTimer:
//      {
//         
//         //__throw(::exception::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));
//         
//         pmessage = __new(::message::timer);
//
//      }
//      break;
//      case ::message::PrototypeShowWindow:
//      {
//         pmessage = __new(::message::show_window);
//      }
//      break;
//      case ::message::PrototypeSetCursor:
//      {
//         pmessage = __new(::message::set_cursor);
//      }
//      break;
//      case ::message::PrototypeNcHitTest:
//      {
//         pmessage = __new(::message::nc_hit_test);
//      }
//      break;
//      case ::message::PrototypeMove:
//      {
//         pmessage = __new(::message::move);
//      }
//      break;
//      case ::message::PrototypeEraseBkgnd:
//      {
//         pmessage = __new(::message::erase_bkgnd);
//      }
//      break;
//      case ::message::PrototypeScroll:
//      {
//         pmessage = __new(::message::scroll);
//      }
//      break;
//      case ::message::PrototypeSetFocus:
//      {
//         pmessage = __new(::message::set_keyboard_focus);
//      }
//      break;
//      case ::message::PrototypeKillFocus:
//      {
//         pmessage = __new(::message::kill_keyboard_focus);
//      }
//      break;
//#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//      case ::message::PrototypeWindowPos:
//      {
//         pmessage = __new(::message::window_pos);
//      }
//      break;
//      case ::message::PrototypeNcCalcSize:
//      {
//         pmessage = __new(::message::nc_calc_size);
//      }
//      break;
//#endif
//      case ::message::PrototypeMouse:
//      {
//         pmessage = __new(::message::mouse);
//      }
//      break;
//      case ::message::PrototypeMouseWheel:
//      {
//         pmessage = __new(::message::mouse_wheel);
//      }
//      break;
//      case ::message::PrototypeSize:
//      {
//         pmessage = __new(::message::size);
//      }
//      break;
//      case ::message::PrototypeActivate:
//      {
//         pmessage = __new(::message::activate);
//      }
//      break;
//      case ::message::PrototypeMouseActivate:
//      {
//         pmessage = __new(::message::mouse_activate);
//      }
//      break;
//      case ::message::PrototypeSimpleCommand:
//      {
//         pmessage = __new(::message::simple_command);
//      }
//      break;
//      default:
//      {
//         pmessage = __new(::message::message);
//      }
//      break;
//      }
//
//      if (pmessage.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      pmessage->set(get_oswindow(), get_window(), id, wparam, lparam);
//
//      return pmessage;
//
//   }


   bool primitive::call_message_handler(const ::id & id, wparam wparam, lparam lparam, const ::point_i32 & point, lresult * plresult)
   {

      auto pmessage = get_message(id, wparam, lparam, point);

      try
      {

         message_handler(pmessage);

      }
      catch (const ::exception::exception & e)
      {

         if (::get_task()->handle_exception(e))
         {

            return false;

         }

      }
      catch (...)
      {

      }

      if (!pmessage->m_bRet)
      {

         return false;

      }

      if (plresult)
      {

         try
         {

            *plresult = pmessage->m_lresult;

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


   //bool primitive::GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl)

   //{

   //   UNREFERENCED_PARAMETER(puserinteractionpl);


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

   //   return get_application();

   //}


//   bool primitive::SetPlacement(const ::rectangle_i32 & rectangle, ::u32 nFlags)
//   {
//
//      UNREFERENCED_PARAMETER(rectangle);
//      UNREFERENCED_PARAMETER(nFlags);
//
//      return false;
//
//   }


   i32 primitive::get_total_page_count(::subject::context * pcontext)
   {

      return 1;

   }



   //void primitive::_001OnTimer(::timer * ptimer)
   //{

   //   UNREFERENCED_PARAMETER(ptimer);

   //}

   //void primitive::add_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   m_threadptra.add(pthread);

   //}


   //void primitive::erase_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   m_threadptra.erase(pthread);

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


   //void primitive::route_control_event(::user::control_event* pevent)
   //{

   //   on_control_event(pevent);

   //}


   //void primitive::on_control_event(control_event * pevent)
   //{

   //   UNREFERENCED_PARAMETER(pevent);

   //}


   bool primitive::keyboard_focus_is_focusable() const
   {

      //return papplication->keyboard_focus_is_focusable(this);
      return false;

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

//      primitive * pprimitive = keyboard_get_next_focusable(nullptr, bSkipChild, bSkipSiblings, bSkipParent);
//
//      auto psession = get_session();
//
//      if (pprimitive == nullptr || pprimitive == this)
//      {
//
//         clear_keyboard_focus();
//
//      }
//      else
//      {
//
//         pprimitive->set_keyboard_focus();
//
//      }
//
//      return get_keyboard_focus(pthread);

         return nullptr;

   }


   primitive * primitive::keyboard_get_next_focusable(primitive * pfocus, bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

     __pointer(primitive) puiThis = this;

     __pointer(primitive) puiFocus = pfocus != nullptr ? pfocus : this;

     primitive * pfocusTry;

     if (puiFocus == nullptr)
     {

        return nullptr;

     }

     if (puiThis == nullptr)
     {

        return nullptr;

     }

     single_lock(puiThis->get_application()->mutex(), true);

     __pointer(primitive) pprimitive;

     if (!bSkipChild)
     {

        pprimitive = puiThis->first_child_user_primitive();

        if (pprimitive != nullptr)
        {

           if (pprimitive->keyboard_focus_is_focusable())
           {

              return pprimitive;

           }

           pprimitive = pprimitive->keyboard_get_next_focusable(puiFocus, false, false, true);

           if (pprimitive != nullptr)
           {

              return pprimitive;

           }

        }

     }

     if (!bSkipSiblings)
     {

        pprimitive = puiThis->next_user_primitive();

        while (pprimitive != nullptr)
        {

           if (pprimitive->keyboard_focus_is_focusable())
           {

              return pprimitive;

           }

           pfocusTry = pprimitive->keyboard_get_next_focusable(puiFocus, false, true, true);

           if (pfocusTry != nullptr)
           {

              return pfocusTry;

           }

           pprimitive = pprimitive->next_user_primitive();

        }

     }

     if (!bSkipParent)
     {

        auto pprimitiveParent = get_parent_primitive();

        if (pprimitiveParent)
        {

           pprimitive = pprimitiveParent->keyboard_get_next_focusable(puiFocus, true);

           if (pprimitive.is_set())
           {

              return pprimitive;

           }

        }

     }

     if (!bSkipSiblings)
     {

        pprimitive = puiThis->first_child_user_primitive();

        if (pprimitive != puiThis)
        {

           while (pprimitive != nullptr && pprimitive != puiFocus)
           {

              if (pprimitive->keyboard_focus_is_focusable())
                 return pprimitive;

              pfocusTry = pprimitive->keyboard_get_next_focusable(puiFocus, false, true, true);

              if (pfocusTry != nullptr)
                 return pfocusTry;

              pprimitive = pprimitive->next_user_primitive();

           }

        }

     }


     return nullptr;

   }


   primitive * primitive::get_keyboard_focus()
   {

      return nullptr;

   }


   ::e_status primitive::set_keyboard_focus()
   {

      return ::error_interface_only;

   }


   ::e_status primitive::erase_keyboard_focus()
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


   ::user::primitive* primitive::get_parent_primitive() const
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


   //bool primitive::is_text_composition_active()
   //{

   //   return false;

   //}


   void primitive::set_input_content_rect(const rectangle_i32& rectangle)
   {

   }


   void primitive::set_input_selection_rect(const rectangle_i32& rectangle)
   {

   }


   rectangle_i32 primitive::get_input_content_rect()
   {

      return rectangle_i32();

   }


   rectangle_i32 primitive::get_input_selection_rect()
   {

      return rectangle_i32();

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


   //::e_status primitive::set_icon(::windowing::icon * picon)
   //{

   //   return false;

   //}


   bool primitive::display(::e_display edisplay, ::e_activation eactivation)
   {

      return true;

   }

} // namespace user



