#include "framework.h"
#include "check.h"
#include "text.h"
#include "element.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/handler/item.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/platform/node.h"


namespace user
{


   element::element()
   {

   
   }


   element::~element()
   {

   }


   void element::show_software_keyboard(::user::element* pprimitive)
   {


   }


   void element::hide_software_keyboard(::user::element * pprimitive)
   {


   }


   void element::PreSubClassWindow()
   {

      //_001BaseWndInterfaceMap();

   }


   ::user::interaction * element::get_wnd()
   {

      return nullptr;

   }


   ::task * element::get_task()
   {

      return nullptr;

      //auto puserinteraction = get_wnd();

      //if (::is_null(puserinteraction))
      //{

      //   return get_app();

      //}

      //return puserinteraction->m_pthreadUserInteraction;

   }



   //::user::interaction_impl * element::get_impl() const
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


   //bool element::is_window_enabled() const
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


   //bool element::is_this_enabled() const
   //{

   //   return true;

   //}


   ::user::interaction* element::get_host_window()
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


   ::user::form * element::get_form()
   {

      return nullptr;

   }


   ::user::form * element::get_parent_form()
   {

      return nullptr;

   }


   ::user::element * element::get_form_user_element()
   {

      return nullptr;

   }


   ::user::element * element::get_parent_form_user_element()
   {

      return nullptr;

   }


   void element::enable_window(bool bEnable)
   {

      __UNREFERENCED_PARAMETER(bEnable);

      //return false;

   }


   //void element::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


   //void element::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   _001OnDraw(pgraphics);
   //   _008OnDraw(pgraphics);

   //}


   void element::UpdateWindow()
   {

      //ASSERT(::IsWindow(GetHandle()));
      //::UpdateWindow(GetHandle());

   }


   void element::Invalidate(bool bErase)
   {

      __UNREFERENCED_PARAMETER(bErase);

      //ASSERT(::IsWindow(GetHandle()));
      //::InvalidateRect(GetHandle(), nullptr, bErase);

   }

   bool element::has_pending_redraw_flags()
   {

      return false;

   }


   //bool element::Redraw(rectangle_i32_array & recta)
   //{

   //   bool bOk = true;

   //   for(i32 i = 0; i < recta.get_size(); i++)
   //   {

   //      if(!get_wnd()->RedrawWindow(recta[i]))
   //         bOk = false;

   //   }

   //   return bOk;

   //}


   //bool element::Redraw(const ::rectangle_i32 & rectangle, ::draw2d::region * prgn)
   //{

   //   if (get_wnd() == nullptr)
   //   {

   //      return false;

   //   }

   //   return get_wnd()->RedrawWindow(rectangle, prgn, RDW_INVALIDATE);

   //}


   //bool element::Redraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   __UNREFERENCED_PARAMETER(pgraphics);

   //   if(get_wnd() == nullptr)
   //      return false;

   //   return get_wnd()->RedrawWindow();

   //}


   /*bool element::client_to_screen(RECTANGLE_I32 * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }


   bool element::client_to_screen(RECTANGLE_F64 * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }
*/

   //bool element::client_to_screen(POINT_I32 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool element::client_to_screen(POINT_F64 * ppoint)
   //{

   //   ::offset(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool element::client_to_screen(RECTANGLE_I64 * prectangle)
   //{

   //   ::offset_rect(prectangle, point_i64(client_screen_top_left()));

   //   return true;

   //}


   //bool element::client_to_screen(POINT_I64 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool element::screen_to_client(RECTANGLE_I32 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool element::screen_to_client(RECTANGLE_F64 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool element::screen_to_client(POINT_I32 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool element::screen_to_client(POINT_F64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool element::screen_to_client(RECTANGLE_I64 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool element::screen_to_client(POINT_I64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool element::GetWindowPos(RECTANGLE_I32 * prectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::window_rectangle(RECTANGLE_I32 * prectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //point_f64 element::client_screen_top_left()
   //{

   //   return nullptr;

   //}


   //bool element::client_rectangle(RECTANGLE_I32 * prectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::client_rectangle(RECTANGLE_I64 * prectangle)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::window_rectangle(RECTANGLE_I64 * prectangle)

   //{

   //   throw ::interface_only();

   //   return false;

   //}












/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


   bool element::is_host_top_level()
   {

      return false;

   }


   bool element::is_ascendant(element * puiIsAscendant, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool element::is_parent(element * puiIsParent)
   {

      throw ::interface_only();

      return false;

   }


   bool element::is_child(element * puiIsChild)
   {

      throw ::interface_only();

      return false;

   }


   bool element::is_descendant( element * puiIsDescendant, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool element::is_descendant_of_or_owned_by(::user::element * puiAscendantCandidate, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool element::is_ascendant_or_owner_of(::user::element * puiDescendantCandidate, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool element::is_ascendant_of(element * puiIsDescendant, bool bIncludeSelf)
   {
      
      return ::is_set(puiIsDescendant) && puiIsDescendant->is_ascendant(this, bIncludeSelf); 
   
   }


   bool element::is_parent_of(element * puiIsChild)
   {
      
      return ::is_set(puiIsChild) && puiIsChild->is_parent(this); 
   
   }


   bool element::is_child_of(element * puiIsParent)
   {
      
      return ::is_set(puiIsParent) && puiIsParent->is_child(this); 
   
   }

   
   bool element::is_descendant_of(element * puiIsAscendant, bool bIncludeSelf)
   { 
      
      return ::is_set(puiIsAscendant) && puiIsAscendant->is_descendant(this, bIncludeSelf); 
   
   }


   //void element::_008GetWindowText(::message::message * pmessage)
   //{

   //}


   //void element::_008GetWindowTextLength(::message::message * pmessage)
   //{

   //}


//#ifdef WINDOWS
//   strsize element::_009GetWindowText(wchar_t * pwsz, int n)
//#else
//   strsize element::_009GetWindowText(char * psz, int n)
//#endif
//   {
//
//      return -1;
//
//   }
//
//
//   strsize element::_009GetWindowTextLength()
//   {
//
//      return -1;
//
//   }



   //bool element::SetPlacement(const ::rectangle_i32 & rectangle,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::add_prodevian(::matter * pmatter)
   {

      //return false;

   }


   void element::erase_prodevian(::matter * pmatter)
   {

      //return false;

   }


   bool element::is_prodevian(const ::matter * pmatter) const
   {

      return false;

   }


   string element::get_title()
   {

      return get_window_text();

   }


   //i32 element::sync_message_box(::payload payload)
   //{

   //   if (payload.get_type() == e_type_string)
   //   {

   //      payload["message"] = payload;

   //   }

   //   payload["parent"] = this;
   //   payload["title"] = get_title();

   //   return message_box(payload);

   //}


   //i32 element::sync_message_box_timeout(const ::string & pszMessage, ::time timeTimeOut, ::u32 fuStyle)
   //{

   //   return papp->sync_message_box_timeout(this, pszMessage, get_title(), timeTimeOut, fuStyle);

   //}


   //void element::message_box(const ::payload& varParam)
   //{

   //   ::payload payload;

   //   if (varParam.get_type() == e_type_property_set)
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


   //void element::message_box_timeout(string strMessage, ::time timeTimeout, ::u32 fuStyle)
   //{

   //   fork([=]()
   //      {

   //         sync_message_box_timeout(strMessage, timeTimeout, fuStyle);

   //      });

   //}
   //bool element::place(const ::rectangle_i32 & rectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::RepositionWindow(i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::MoveWindow(i32 x,i32 y,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::move_to(const ::point_i32 & point)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::SizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_size(const size_i32 & sz)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ResizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ResizeWindow(const size_i32 & sz,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_window_position(class zorder zorder, const ::rectangle_i32 & rectangle, ::u32 nFlags)

   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //bool element::defer_set_window_pos(iptr z, const  const rectangle_i32 & & rectangle, ::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of rectangle_i32(x, y, cx, cy)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::defer_set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of rectangle_i32(x, y, cx, cy)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void element::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void element::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void element::_001PrintBuffer(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void element::_001Print(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void element::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void element::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   ::user::interaction * element::_001FromPoint(::point_i32 point,bool bTestedIfParentVisible)
   {

      throw ::interface_only();

      return nullptr;

   }


   bool element::_001IsPointInside(const ::point_i32 & point)
   {

      return false;

   }


   ::user::interaction * element::get_child_by_name(const ::string & strName, ::index iItem, i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_child_by_id(const atom & atom, ::index iItem, i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::element * element::get_primitive_by_id(const atom & atom, ::index iItem, i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::interaction_post(const ::procedure & procedure)
   {

      //throw ::interface_only();

      throw ::interface_only();

   }


   //lresult element::send(::message::message * pmessage)
   //{

   //   message_handler(pmessage);

   //   return pmessage->m_lresult;

   //}


   //// pmessage object should be allocated with memory_new in
   //// base or derived object and will be delete after
   //// handling
   //bool element::post(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   lresult element::send_message(const ::atom & atom,wparam wparam,lparam lparam, const ::point_i32& point)
   {

      return message_call(atom, wparam, lparam, point);

   }


   lresult element::message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      return 0;

   }


   lresult element::message_call(::message::message * pmessage)
   {

      return 0;

   }


#ifdef LINUX


   lresult element::send_x11_event(void * pevent)
   {

      throw ::interface_only();

      return 0;

   }


#endif


   //bool element::_is_window_visible()
   //{

   //   return false;

   //}


   //bool element::is_this_visible()
   //{

   //   return (GetStyle() & WS_VISIBLE) != 0 && m_bUserElementOk;

   //}


   //bool element::ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::display(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   // void element::SetWindowDisplayChanged()
   // {


   // }


   //::user::frame * element::top_level_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void element::send_message_to_descendants(const ::atom & atom,wparam wparam,lparam lparam,bool bDeep,bool bOnlyPerm)

   {

      throw ::interface_only();

   }

   void element::route_message_to_descendants(::message::message * pmessage)
   {

      throw ::interface_only();

   }

   void element::pre_translate_message(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   ::windowing::window * element::window()
   {

      return nullptr;

   }


   string element::get_class_name()
   {

      return "";

   }


   void element::subclass_window(oswindow posdata)
   {

      throw ::interface_only();

   }


   oswindow element::unsubclass_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::create_child(::user::interaction * puserinteractionParent)
   {

      //throw ::interface_only();

      throw ::interface_only();

      //return ::success;

   }

   
   void element::create_control(::user::interaction * puserinteractionParent, const ::atom & atom)
   {

      m_atom = atom;

      /*auto estatus =*/ create_child(puserinteractionParent);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      ///return estatus;

   }


   enum_control_type element::get_control_type() const
   {

      return e_control_type_none;

   }


   //bool element::create_interaction(::user::interaction * puiParent, ::request * prequest, ::u32 uExStyle, ::u32 uStyle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom)
   {

      if (!atom.is_empty())
      {

         m_atom = atom;

      }

      ::e_status estatus;

      if (!puserinteractionParent)
      {

         //estatus = create_host();

         create_host();

      }
      else
      {

         create_child(puserinteractionParent);

      }

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //bool element::create_window_ex(::pointer<::user::system>pcs, ::user::interaction * puiParent, const ::atom & atom)
   void element::create_host()
   {

      //throw ::interface_only();

      //return ::error_no_interface;

      throw ::interface_only();

   }


   //void element::BringToTop(::e_display edisplay)
   //{

   //}


   //bool element::BringWindowToTop()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool element::_is_window() const
   {

      return m_bUserElementOk;

   }


   ::user::interaction* element::first_child()
   {

      return nullptr;

   }


   ::user::interaction* element::last_child()
   {

      return nullptr;

   }


   ::user::interaction* element::last_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::next_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::previous_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::first_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::next_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }


   ::user::interaction* element::previous_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }

   
   ::user::interaction* element::bottom_child()
   {

      return nullptr;

   }


   ::user::interaction* element::top_child()
   {

      return nullptr;

   }


   ::user::interaction* element::bottom_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::under_sibling()
   {

      return nullptr;

   }



   ::user::interaction* element::above_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::top_sibling()
   {

      return nullptr;

   }


   ::user::interaction* element::above_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }


   ::user::interaction* element::under_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }



   //::i32 element::get_window_long(i32 nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //::i32 element::set_window_long(i32 nIndex,::i32 lValue)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //iptr element::get_window_long_ptr(i32 nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //void element::set_window_long_ptr(i32 nIndex, iptr lValue)
   //{

   //   throw ::interface_only();

   //   throw ::interface_only();

   //}


   //bool element::RedrawWindow(const ::rectangle_i32& rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   ::user::interaction * element::ChildWindowFromPoint(const ::point_i32 & point)
   {

      throw ::interface_only();

   }


   ::user::interaction * element::ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags)
   {

      throw ::interface_only();

   }


   ::user::interaction * element::get_next_window(bool bIgnoreChildren, ::user::interaction * puiInteractionStop)
   {

      return nullptr;

   }

   
   ::user::interaction * element::get_window(enum_next enext)
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
//         throw ::interface_only();
//
//         return nullptr;
//
//      }

   ///}


//   ::user::interaction * element::get_next_window(bool bIgnoreChildren)
//   {
//
//      throw ::interface_only();
//
//      return nullptr;
//
//   }


   bool element::is_message_only_window()
   {

      throw ::interface_only();

      return false;

   }


   ::user::interaction * element::get_wnd(::u32 nCmd)
   {

      throw ::interface_only();

      return nullptr;

   }


   //bool element::is_active() const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * element::GetActiveWindow()
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if(pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetActiveWindow();

   //}


   //bool element::SetFocus()
   //{

   //   ::pointer<::user::interaction>pinteraction = get_wnd();

   //   if(pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   return get_wnd()->SetFocus();

   //}


   //interaction * element::SetActiveWindow()
   //{

   //   //throw ::interface_only();

   //   return nullptr;

   //}


   //bool element::SetForegroundWindow()
   //{

   //   return true;

   //}


   ::user::interaction * element::GetLastActivePopup()
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::edit_on_set_focus(::user::interaction* pinteraction)
   {

   }


   void element::edit_on_kill_focus(::user::interaction* pinteraction)
   {

   }


   void element::set_window_text(const ::string & pszString)
   {

   }


   void element::set_window_text_source(const ::a_string_function & astringfunction)
   {

   }


   strsize element::get_window_text(char * pszStringBuf, strsize nMaxCount)

   {

      throw ::interface_only();

      return 0;

   }


   string element::get_window_text()
   {

      throw ::interface_only();

      return "";

   }


   void element::get_window_text(string & rString)
   {

      throw ::interface_only();

   }


   strsize element::get_window_text_length()
   {

      throw ::interface_only();

      return 0;

   }


   //::user::interaction * element::EnsureTopLevel()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * element::EnsureParentTopLevel()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * element::GetParentTopLevel() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame * element::GetParentTopLevelFrame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame * element::EnsureParentFrame()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //lresult element::default_window_procedure()
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //u32 element::GetStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //u32 element::GetExStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   void element::start_destroying_window()
   {

      throw ::interface_only();

      //return false;

   }


   void element::destroy_window()
   {

   }


   void element::post_non_client_destroy()
   {

      destroy();

   }


   ::user::interaction * element::get_parent()
   {

      throw ::interface_only();

      return nullptr;

   }


   //::user::frame * element::get_parent_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void element::CalcWindowRect(RECTANGLE_I32 * prectangle,::u32 nAdjustType)

   //{

   //   throw ::interface_only();

   //}


   void element::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeftOver, ::u32 nFlag, RECTANGLE_I32 * prectParam, const ::rectangle_i32 & rectangleClient, bool bStretch)
   {

      throw ::interface_only();

   }


   ::user::element * element::set_owner(::user::element * pinteraction)
   {

      //throw ::interface_only();

      return nullptr;

   }


   ::user::element * element::set_parent(::user::element * pinteraction)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   /*::user::frame * element::get_owner_frame() const
   {

      throw ::interface_only();

      return nullptr;

   }*/


   bool element::is_top_level_window()
   {

      return false;

   }


   //interaction * element::get_parent() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame * element::frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   ::user::interaction * element::get_parent_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_parent_or_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_top_level_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::_top_level()
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      throw ::interface_only();

   }


   void element::viewport_client_to_screen(POINT_I32 & point)
   {

      throw ::interface_only();

   }


   void element::viewport_screen_to_client(POINT_I32 & point)
   {

      throw ::interface_only();

   }


   void element::viewport_client_to_screen(RECTANGLE_I32 & rectangle)
   {

      throw ::interface_only();

   }


   void element::viewport_screen_to_client(RECTANGLE_I32 & rectangle)
   {

      throw ::interface_only();

   }


   //i32 element::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //i32 element::GetWindowRgn(HRGN hRgn)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //bool element::layout().is_zoomed()
   //{

   //   return false;

   //}


   //bool element::layout().is_full_screen()
   //{

   //   return false;

   //}


   //bool element::layout().is_iconic()
   //{

   //   return false;

   //}


   void element::CheckAutoCenter()
   {

      throw ::interface_only();

      //return false;

   }


   void element::CenterWindow(::user::interaction * pAlternateOwner)
   {

      throw ::interface_only();

   }


   void element::default_message_handler(::message::message * pmessage)
   {


   }


   void element::message_handler(::message::message * pmessage)
   {

      throw ::interface_only();

      //return false;

   }


   //lresult element::message_handler(MESSAGE * pmessage)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   bool element::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   bool element::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   //bool element::pre_create_window(::user::system * pusersystem)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::IsTopParentActive()
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


   void element::ActivateTopParent()
   {

   }


   void element::update_dialog_controls(channel * ptarget)
   {

      //throw ::interface_only();

   }


   void element::SetRedraw(bool bRedraw)
   {

      throw ::interface_only();

   }


   bool element::GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase)

   {

      throw ::interface_only();

      return false;

   }


   //i32 element::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //void element::InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase)

   //{

   //   throw ::interface_only();

   //}


   //void element::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //}


   //void element::ValidateRect(const ::rectangle_i32 & rectangle)

   //{

   //   throw ::interface_only();

   //}


   //void element::ValidateRgn(::draw2d::region* pRgn)
   //{

   //   throw ::interface_only();

   //}


   //void element::on_start_layout_experience(enum_layout_experience elayoutexperience)
   //{

   //}


   //void element::on_end_layout_experience(enum_layout_experience elayoutexperience)
   //{

   //}


   void element::on_configuration_change(::user::element * pprimitiveSource)
   {


   }


   void element::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      throw ::interface_only();

   }


   void element::on_reposition()
   {

      throw ::interface_only();

   }


   bool element::is_this_visible(enum_layout elayout)
   {

      return true;

   }


   void element::on_show_window()
   {

      throw ::interface_only();

   }


   //void element::window_show_change_visibility()
   //{


   //}


   //void element::ShowOwnedPopups(bool bShow)
   //{

   //   throw ::interface_only();

   //}


   //bool element::attach(oswindow oswindow)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   oswindow element::detach_window()
   {

      return nullptr;

   }


   void element::pre_subclass_window()
   {

      throw ::interface_only();

   }


   atom element::run_modal_loop(::user::interaction * pinteraction,u32 dwFlags)
   {

      throw ::interface_only();

      return ::atom();

   }


   atom element::RunModalLoop(u32 dwFlags)
   {

      throw ::interface_only();

      return ::atom();

   }


   atom element::_001RunModalLoop(u32 dwFlags)
   {

      throw ::interface_only();

      return atom();

   }


   bool element::ContinueModal()
   {

      throw ::interface_only();

      return false;

   }


   void element::EndModalLoop(atom nResult)
   {

      throw ::interface_only();

   }


   void element::post_message(const ::atom & atom,wparam wparam,lparam lparam)
   {

      throw ::interface_only();

      //return false;

   }


   void element::SetTimer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer, bool bPeriodic, void* pdata)
   {

      throw ::interface_only();

      //return false;

   }


   void element::KillTimer(uptr uEvent)
   {

      throw ::interface_only();

      //return false;

   }


   //bool element::has_keyboard_focus() const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_capture(::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   //::user::interaction * element::get_capture() const
   //{

   //   return nullptr;

   //}



   //bool element::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   //::user::interaction * element::get_keyboard_focus() const
   //{

   //   return nullptr;

   //}




   void element::_000OnMouseLeave(::message::message* pmessage)
   {

   }


   void element::track_mouse_leave()
   {

      throw ::interface_only();

   }


   void element::track_mouse_hover()
   {

      throw ::interface_only();

   }


   void element::sketch_to_design(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

   }


   void element::_001UpdateWindow()
   {

   }

   
   void element::queue_selection_synchronization()
   {


   }


   // void element::window_apply_visual(const window_state & windowstate)
   // {

   // }


   //void element::design_window_minimize(::e_activation eactivation)
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_maximize()
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_full_screen(const ::rectangle_i32 & rectangleHint)
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_restore(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_dock(::e_display edisplayDock)
   //{

   //   throw ::interface_only();

   //}


   //void element::GuieProc(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //}


   //void element::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void element::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   void element::OnLinkClick(const ::string & psz,const ::string & pszTarget)
   {

      throw ::interface_only();

   }


   //void element::set_config_per_second(::frequency dConfigFps)
   //{

   //   //get_host_window()->m_pimpl->set_config_per_second(dConfigFps);

   //}


   //::frequency element::get_config_per_second()
   //{

   //   //return get_host_window()->m_pimpl->get_config_per_second();

   //}


   //::frequency element::get_output_per_second()
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

   //   //return pimpl->get_output_per_second();
   //   return 0.0;

   //}


   void element::create_message_queue(const ::string & lpszName)
   {

      throw ::interface_only();

      //return false;

   }


   void element::on_select()
   {

      throw ::interface_only();

   }


   bool element::is_place_holder()
   {

      throw ::interface_only();

      return false;

   }


   double element::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      return 0.0;

   }


   //::windowing::cursor * element::get_mouse_cursor()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void element::set_mouse_cursor(::windowing::cursor * pcursor)
   //{

   //   return success_none;

   //}


   //void element::set_cursor(::windowing::/*cursor * pcursor)
   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //::point_i32 element::get_cursor_position() const
   //{

   //   return ::point_i32();

   //}

   
   //::size_f64 element::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   return { 0.0, 0.0 };

   //}


   //::size_f64 element::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::rectangle_f64 rectanglePadding(2.0, 2.0, 2.0, 2.0);

   //   auto sizeFitting = _001CalculateFittingSize(pgraphics);

   //   ::size_f64 sizePaddedFitting;

   //   sizePaddedFitting.cx = rectanglePadding.left + sizeFitting.cx + rectanglePadding.right;

   //   sizePaddedFitting.cy = rectanglePadding.top + sizeFitting.cy + rectanglePadding.bottom;

   //   return sizePaddedFitting;

   //}


   //bool element::can_merge(::user::interaction * pinteraction)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::merge(::user::interaction * pinteraction)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * element::top_child()
   //{

   //   return last_child();

   //}


   //::user::interaction * element::bottom_child()
   //{

   //   return first_child();

   //}


   //::user::interaction * element::above_sibling(::user::interaction * pinteraction)
   //{

   //   return next_sibling(pinteraction);

   //}


   //::user::interaction * element::above_sibling()
   //{

   //   return next_sibling();

   //}


   //::user::interaction * element::under_sibling(::user::interaction * pinteraction)
   //{

   //   return previous_sibling(pinteraction);

   //}


   //::user::interaction * element::under_sibling()
   //{

   //   return previous_sibling();

   //}

   //::user::interaction * element::top_sibling()
   //{

   //   return last_sibling();

   //}


   //::user::interaction * element::bottom_sibling()
   //{

   //   return first_sibling();

   //   return nullptr;

   //}

   //::user::interaction * element::first_child()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * element::last_child()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}

   //::user::interaction * element::first_sibling()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * element::last_sibling()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * element::previous_sibling()
   //{

   //   return nullptr;

   //}

   //::user::interaction * element::previous_sibling(::user::interaction * pinteraction)
   //{

   //   __UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}

   //::user::interaction * element::next_sibling()
   //{

   //   return nullptr;

   //}

   //::user::interaction * element::next_sibling(::user::interaction * pinteraction)
   //{

   //   __UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}


   //void element::mouse_hover_add(::user::interaction * pinterface)
   //{

   //   throw ::interface_only();

   //}


   //bool element::mouse_hover_erase(::user::interaction * pinterface)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void element::_task_transparent_mouse_event()
   //{


   //}


   void element::on_set_keyboard_focus()
   {

   }


   void element::on_kill_keyboard_focus()
   {

   }


   bool element::GetFocusRect(RECTANGLE_I32 & rectangle)
   {

      return false;

   }


   void element::defer_update_display()
   {


   }


   ::index element::item_index(const ::atom & atom) const
   {

      auto iIndex = atom.as_index();

      if(!m_pitema->is_index_ok(iIndex))
      {

         iIndex = m_pitema->predicate_find_first([&atom](auto & pitem)
         {

            return pitem->m_atom == atom;

         });
         
         if(iIndex < 0)
         {

            // still not ok? couldn't find then, right?!...;

            return -1;
      
         }

      }
      
      return iIndex;

   }


   bool element::is_index_item_pressed(::index iIndex) const
   {

      return ::is_item_index(m_pitemPressed, iIndex);

   }


   bool element::is_index_item_hover(::index iIndex) const
   {
   
      return ::is_item_index(m_pitemHover, iIndex);
   
   }


   bool element::is_item_pressed(const ::atom & atom) const
   {

      auto iIndex = item_index(atom);
   
      return is_index_item_pressed(iIndex);

   }


   bool element::is_item_hover(const ::atom & atom) const
   {
      
      auto iIndex = item_index(atom);

      return is_index_item_hover(iIndex);

   }


   //::user::element * element::get_keyboard_focus()
   //{

   //   auto puserinteractionHost = get_host_window();

   //   if (::is_null(puserinteractionHost))
   //   {

   //      return nullptr;

   //   }

   //   ::user::element * pprimitive = puserinteractionHost->get_keyboard_focus();

   //   if(pprimitive == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return dynamic_cast < ::user::interaction * > (pprimitive);

   //}


   i32 element::get_descendant_level(::user::element * pinteraction)
   {

      throw ::interface_only();

      return -1;

   }


   //bool element::is_descendant(const ::user::element * pinteraction,bool bIncludeSelf) const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::set_tool_window(bool bSet)
   {

      __UNREFERENCED_PARAMETER(bSet);

      throw ::interface_only();

      //return error_not_implemented;

   }


   ::user::interaction * element::get_first_child_window()
   {

      return nullptr;

   }


   ::user::interaction * element::get_next_sibling_window()
   {

      return nullptr;

   }


   ::user::interaction * element::get_focusable_descendant()
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::_001OnTriggerMouseInside()
   {

      throw ::interface_only();

   }


   void element::update_data(bool bSaveAndValidate)
   {

      throw ::interface_only();

      ///return false;

   }


   string element::get_window_default_matter()
   {

      throw ::interface_only();

      return "";

   }


   string element::get_window_icon_matter()
   {

      throw ::interface_only();

      return get_window_default_matter();

   }


   u32 element::get_window_default_style()
   {

      throw ::interface_only();

      return 0;

   }


   ::user::element::enum_type element::get_window_type()
   {

      return type_window;

   }





   //bool element::OnCommand(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::OnNotify(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::OnChildNotify(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return false;

   //}





   //void element::on_command(::message::command * pcommand)
   //{

   //   channel::on_command(pcommand);

   //}


   bool element::is_selected(::data::item * pitem)
   {

      throw ::interface_only();

      return false;

   }


   //bool element::has_command_handler(::message::command * pcommand)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::handle(::topic * ptopic, ::context * pcontext)
   {


   }


   //bool element::track_popup_menu(::user::menu_item * pitem,i32 iFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::pointer<::user::menu>element::track_popup_xml_menu_text(string strXml,i32 iFlags)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::pointer<::user::menu>element::track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}



   //bool element::track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::pointer<::user::menu>element::track_popup_xml_menu_text(string strXml,i32 iFlags,::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::pointer<::user::menu>element::track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags,::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //bool element::track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point_i32 & point)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::pointer<::user::menu>element::track_popup_xml_menu(const ::payload & varXml,i32 iFlags, const ::point_i32 & point, const size_i32 & size)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::pointer<::user::menu>element::track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags, const ::point_i32 & point)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::pointer<::user::menu>element::track_popup_xml_menu_file(::payload payloadFile, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void element::_001OnExitIconic()
   {

   }


   void element::_001OnExitNormal()
   {


   }


   void element::_001OnExitZoomed()
   {

   }


   void element::_001OnExitFullScreen()
   {

   }


   void element::on_add_owned(::user::element * pprimitive)
   {


   }


   //void element::window_enable_full_screen(bool bEnable)
   //{

   //   throw ::interface_only();

   //}


   //bool element::window_is_full_screen_enabled()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //edisplay element::get_display()
   //{

   //   return e_display_none;

   //}


   //edisplay element::get_previous_display()
   //{

   //   return e_display_none;

   //}


   //bool element::defer_set_appearance(::e_display edisplay)
   //{

   //   if (get_display() == edisplay)
   //   {

   //      return false;

   //   }

   //   return set_appearance(edisplay);

   //}

   //bool element::set_appearance(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_previous_display(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void element::show_keyboard(bool bShow)
   //{

   //   __UNREFERENCED_PARAMETER(bShow);

   //}




   void element::keep_alive(::object * pliveobject)
   {

      throw ::interface_only();

   }


   //bool element::set_window_position(class zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   atom element::GetDlgCtrlId() const
   {

      throw ::interface_only();

      return atom();

   }


   atom element::SetDlgCtrlId(const atom & atom)
   {

      throw ::interface_only();

      return ::atom();

   }


//#ifdef WINDOWS_DESKTOP
//
//   bool element::open_clipboard()
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   bool element::close_clipboard()
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   //oswindow element::get_safe_handle() const
   //{

   //   if(::is_null(this))
   //      return nullptr;

   //   return get_handle();

   //}


   //::graphics::graphics * element::get_window_graphics()
   //{

   //   return nullptr;

   //}


   //bool element::is_composite()
   //{

   //   return true; // optimistic response, assume always true alpha blendable

   //}


   //void element::_user_message_handler(::message::message * pmessage)
   //{
   //}

   //::message::PFN_DISPATCH_MESSAGE_HANDLER element::_calc_user_message_handler()
   //{
   //   return &::user::element::_user_message_handler;
   //}

   //void element::_001OnTimer(::timer * ptimer)
   //{



   //}


   bool element::has_pending_graphical_update()
   {

      return false;

   }


   void element::on_after_graphical_update()
   {

   }


   void element::set_bitmap_source(const string & strBitmapSource)
   {

      throw ::interface_only();

   }


   void element::clear_bitmap_source()
   {

      throw ::interface_only();

   }


   void element::design_down()
   {

   }


   void element::design_up()
   {

   }


   void element::prodevian_redraw(bool bUpdateBuffer)
   {

   }


   void element::prodevian_stop()
   {


   }


} // namespace user









namespace user
{


   void element::post_simple_command(const enum_simple_command & ecommand, lparam lparam)
   {

      post_message(e_message_simple_command, (wparam)ecommand, lparam);

      //return true;

   }


   void element::add_child_handler(const ::signal_handler& signalhandler, const ::atom & idChild, bool bPriority)
   {

      throw ::interface_only();

      //throw ::interface_only();

      //auto pchild = get_primitive_by_id(idChild);

      //if (::is_null(pchild))
      //{

      //   return error_not_found;

      //}

      //auto estatus = pchild->add_handler(pmatter, bPriority);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //void element::on_simple_command(::message::simple_command * psimplecommand)
   //{

   //   if (psimplecommand->command() == e_simple_command_full_screen)
   //   {

   //      //get_wnd()->display(e_display_full_screen);

   //      psimplecommand->m_bRet = true;

   //   }

   //}


//   ::pointer<::message::message>element::get_message(const ::atom & atom, wparam wparam, lparam lparam)
//   {
//
//      ::pointer<::message::message>pmessage;
//
//      auto eprototype = ::message::get_message_prototype((enum_message) atom.i64(), 0);
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
//         //throw ::exception(::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));
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
//         pmessage = __new(::message::transfer);
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
//#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
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
//      pmessage->set(get_oswindow(), get_window(), atom, wparam, lparam);
//
//      return pmessage;
//
//   }


   // bool element::call_message_handler(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point, lresult * plresult)
   // {

   //    //auto pmessage = get_message(atom, wparam, lparam);

   //    //try
   //    //{

   //    //   message_handler(pmessage);

   //    //}
   //    //catch (const ::exception & e)
   //    //{

   //    //   if (::get_task()->handle_exception(e))
   //    //   {

   //    //      return false;

   //    //   }

   //    //}
   //    //catch (...)
   //    //{

   //    //}

   //    //if (!pmessage->m_bRet)
   //    //{

   //    //   return false;

   //    //}

   //    //if (plresult)
   //    //{

   //    //   try
   //    //   {

   //    //      *plresult = pmessage->m_lresult;

   //    //   }
   //    //   catch (...)
   //    //   {

   //    //   }

   //    //}

   //    //return true;

   //    throw ::interface_only();

   //    return false;

   // }

/*
   element::element()
   {

      m_puiThis = nullptr;

   }


   element::~element()
   {


   }
*/

#ifdef WINDOWS_DESKTOP


   //bool element::GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl)

   //{

   //   __UNREFERENCED_PARAMETER(puserinteractionpl);


   //   return false;

   //}

   //bool element::SetWindowPlacement(const WINDOWPLACEMENT * pcwndpl)

   //{

   //   __UNREFERENCED_PARAMETER(pcwndpl);


   //   return false;

   //}


#endif // WINDOWS_DESKTOP


   //::form_property_set * element::get_form_property_set()
   //{

   //   auto pformpropertyset = get_typed_parent < ::form_property_set >();

   //   if (::is_set(pformpropertyset))
   //   {

   //      return pformpropertyset->get_form_property_set();

   //   }

   //   return get_app();

   //}


//   bool element::SetPlacement(const ::rectangle_i32 & rectangle, ::u32 nFlags)
//   {
//
//      __UNREFERENCED_PARAMETER(rectangle);
//      __UNREFERENCED_PARAMETER(nFlags);
//
//      return false;
//
//   }


   i32 element::get_total_page_count(::context * pcontext)
   {

      return 1;

   }



   //void element::_001OnTimer(::timer * ptimer)
   //{

   //   __UNREFERENCED_PARAMETER(ptimer);

   //}

   //void element::add_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   m_threadptra.add(pthread);

   //}


   //void element::erase_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   m_threadptra.erase(pthread);

   //}

   //bool element::enable_window(bool bEnableWindow)
   //{

   //   return true;

   //}


   // Text Edit
   void element::_001GetSel(strsize & iBeg, strsize & iEnd)
   {


   }


   void element::_001GetSel(strsize& iBeg, strsize& iEnd, strsize& iComposingStart, strsize& iComposingEnd)
   {


   }


   index element::plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   index element::plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x)
   {

      return -1;

   }


   index element::plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   index element::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   {

      return -1;

   }


   strsize element::plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn)
   {

      return -1;

   }


   strsize element::plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x)
   {

      return -1;

   }


   index element::plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }




   void element::keyboard_focus_OnTimer(i32 iTimer)
   {
      __UNREFERENCED_PARAMETER(iTimer);
   }

   void element::keyboard_focus_OnChar(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void element::keyboard_focus_OnSysChar(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void element::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

   }


   void element::keyboard_focus_OnKeyUp(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   //void element::route(::topic * ptopic, ::context * pcontext)
   //{

   //   handle(ptopic, pcontext);

   //}


   //void element::handle_event(control_event * pevent)
   //{

   //   __UNREFERENCED_PARAMETER(pevent);

   //}


   bool element::keyboard_focus_is_focusable()
   {

      //return papp->keyboard_focus_is_focusable(this);
      return false;

   }


   bool element::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      return true;

   }


   bool element::keyboard_focus_OnChildKillFocus()
   {

      return true;

   }


   element * element::keyboard_set_focus_next(bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

//      element * pprimitive = keyboard_get_next_focusable(nullptr, bSkipChild, bSkipSiblings, bSkipParent);
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


   element * element::keyboard_get_next_focusable(element * pfocus, bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

     //::pointer<element>puiThis = this;

     //::pointer<element>puiFocus = pfocus != nullptr ? pfocus : this;

     //element * pfocusTry;

     //if (puiFocus == nullptr)
     //{

     //   return nullptr;

     //}

     //if (puiThis == nullptr)
     //{

     //   return nullptr;

     //}

     //single_lock(puiThis->get_app()->mutex(), true);

     //::pointer<element>pprimitive;

     //if (!bSkipChild)
     //{

     //   pprimitive = puiThis->first_child_user_primitive();

     //   if (pprimitive != nullptr)
     //   {

     //      if (pprimitive->keyboard_focus_is_focusable())
     //      {

     //         return pprimitive;

     //      }

     //      pprimitive = pprimitive->keyboard_get_next_focusable(puiFocus, false, false, true);

     //      if (pprimitive != nullptr)
     //      {

     //         return pprimitive;

     //      }

     //   }

     //}

     //if (!bSkipSiblings)
     //{

     //   pprimitive = puiThis->next_user_primitive();

     //   while (pprimitive != nullptr)
     //   {

     //      if (pprimitive->keyboard_focus_is_focusable())
     //      {

     //         return pprimitive;

     //      }

     //      pfocusTry = pprimitive->keyboard_get_next_focusable(puiFocus, false, true, true);

     //      if (pfocusTry != nullptr)
     //      {

     //         return pfocusTry;

     //      }

     //      pprimitive = pprimitive->next_user_primitive();

     //   }

     //}

     //if (!bSkipParent)
     //{

     //   auto pprimitiveParent = get_parent_primitive();

     //   if (pprimitiveParent)
     //   {

     //      pprimitive = pprimitiveParent->keyboard_get_next_focusable(puiFocus, true);

     //      if (pprimitive.is_set())
     //      {

     //         return pprimitive;

     //      }

     //   }

     //}

     //if (!bSkipSiblings)
     //{

     //   pprimitive = puiThis->first_child_user_primitive();

     //   if (pprimitive != puiThis)
     //   {

     //      while (pprimitive != nullptr && pprimitive != puiFocus)
     //      {

     //         if (pprimitive->keyboard_focus_is_focusable())
     //            return pprimitive;

     //         pfocusTry = pprimitive->keyboard_get_next_focusable(puiFocus, false, true, true);

     //         if (pfocusTry != nullptr)
     //            return pfocusTry;

     //         pprimitive = pprimitive->next_user_primitive();

     //      }

     //   }

     //}


     return nullptr;

   }


   element * element::get_keyboard_focus()
   {

      return nullptr;

   }


   void element::set_keyboard_focus()
   {

      throw ::interface_only();

      //return false;

   }


   void element::erase_keyboard_focus()
   {

      throw ::interface_only();

   }


   void element::clear_keyboard_focus(::user::element * pelementGainingFocusIfAny)
   {

      throw ::interface_only();

   }


   void element::mouse_focus_OnLButtonUp(::message::message * pmessage)
   {


   }


   bool element::_001CanEnterScreenSaver()
   {
   
      return false;
   
   }


   

   ::user::element * element::first_child_user_primitive()
   {

      return nullptr;

   }


   ::user::element * element::top_user_primitive()
   {

      return nullptr;

   }


   ::user::element * element::under_user_primitive()
   {

      return nullptr;

   }


   ::user::element * element::above_user_primitive()
   {

      return nullptr;

   }


   ::user::element * element::next_user_primitive()
   {

      return nullptr;

   }


   ::user::element * element::previous_user_primitive()
   {

      return nullptr;

   }


   ::user::interaction * element::get_parent_window()
   {

      return nullptr;

   }


   ::user::element* element::get_parent_primitive()
   {

      return nullptr;

   }


   ::user::primitive_impl* element::get_primitive_impl()
   {

      return nullptr;

   }


   //::user::element * element::get_wnd_primitive() const
   //{

   //   return nullptr;

   //}


   void element::_001OnTimer(::timer * ptimer)
   {

      __UNREFERENCED_PARAMETER(ptimer);

   }


   void element::on_reset_focus_start_tick()
   {
//
  //    m_timeFocusStart.Now();

   }


   //bool element::_is_window() const
   //{

   //   return m_bUserElementOk;

   //}

   
   float element::preferred_dpi_x()
   {

      return 96.0f;

   }

   
   float element::preferred_dpi_y()
   {

      return 96.0f;

   }

   
   float element::preferred_density()
   {

      return 1.0f;

   }



   void element::set_need_redraw(bool bAscendants)
   {

      __UNREFERENCED_PARAMETER(bAscendants);

   }


   void element::set_need_load_form_data()
   {


   }


   void element::set_need_save_form_data()
   {


   }


   void element::post_redraw(bool bAscendants)
   {

      __UNREFERENCED_PARAMETER(bAscendants);

   }


   void element::hide()
   {

      //return false;

   }



   void element::edit_on_text(string str)
   {

   }


   void element::edit_on_sel(strsize iBeg, strsize iEnd)
   {

   }


   void element::insert_text(string str, bool bForceNewStep, const ::action_context & context)
   {

   }


   void element::on_text_composition(string str)
   {

   }


   void element::on_text_commit(string str)
   {

   }


   void element::on_text_composition_done()
   {

   }


   //bool element::is_text_composition_active()
   //{

   //   return false;

   //}


   void element::set_input_content_rect(const rectangle_i32& rectangle)
   {

   }


   void element::set_input_selection_rect(const rectangle_i32& rectangle)
   {

   }


   rectangle_i32 element::get_input_content_rect()
   {

      return rectangle_i32();

   }


   rectangle_i32 element::get_input_selection_rect()
   {

      return rectangle_i32();

   }


   bool element::InputConnectionBeginBatchEdit(bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionEndBatchEdit(bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionCommitText(const ::string & str, strsize iNewCursorPosition, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionDeleteSurroundingText(strsize iBeforeLength, strsize iAfterLength, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetComposingText(const ::string & str, strsize iNewCursorPosition, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetComposingRegion(strsize iStart, strsize iEnd, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetSelection(strsize iStart, strsize iEnd, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionFinishComposingText(bool bSuper)
   {

      return bSuper;

   }


   //void element::set_icon(::windowing::icon * picon)
   //{

   //   return false;

   //}


   void element::display(::e_display edisplay, ::e_activation eactivation)
   {

      //return true;

   }



   void element::pick_single_file(const ::array < ::file::file_dialog_filter >& filedialogfiltera, const ::function < void(const ::file::path&) >& function, bool bSave)
   {

      auto pfiledialog = acmenode()->node_file_dialog();

      pfiledialog->m_bSave = bSave;

      pfiledialog->m_function = [this, function](auto pdialog)
      {


         if (pdialog && pdialog->m_patha.has_element())
         {

            function(pdialog->m_patha.first());

         }
         else
         {

            function({});

         }


      };

      pfiledialog->call_run();

   }


   void element::pick_multiple_file(const ::array < ::file::file_dialog_filter >& filedialogfiltera, const ::function < void(const ::file::path_array&) >& function)
   {

      auto pfiledialog = acmenode()->node_file_dialog();

      pfiledialog->m_function = [this, function](auto pdialog)
      {


         if (pdialog && pdialog->m_patha.has_element())
         {

            function(pdialog->m_patha);

         }
         else
         {

            function({});

         }


      };

      pfiledialog->call_run();

   }



   void element::pick_single_folder(const ::function < void(const ::file::path&) >& function)
   {

      auto pfiledialog = acmenode()->node_file_dialog();

      pfiledialog->m_function = [this, function](auto pdialog)
      {


         if (pdialog && pdialog->m_patha.has_element())
         {

            function(pdialog->m_patha.first());

         }
         else
         {

            function({});

         }


      };

      pfiledialog->call_run();

   }


} // namespace user



