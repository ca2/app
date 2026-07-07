#include "framework.h"
#include "element.h"
#include "item.h"
#include "interaction.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/constant/simple_command.h"
#include "acme/handler/item.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/user/user/element.h"
#include "acme/windowing/window.h"
#include "acme/windowing/windowing.h"


namespace user
{


   element::element()
   {


   }


   element::~element()
   {

   }


   void element::show_software_keyboard(::user::element * pprimitive)
   {


   }


   void element::hide_software_keyboard(::user::element * pprimitive)
   {


   }


   void element::PreSubClassWindow()
   {

      //_001BaseWndInterfaceMap();

   }

   
   bool element::is_waiting_for_dialog_response()
   {

      return false;

   }


   ::payload element::wait_for_dialog_response(const class ::time & timeTimeout)
   {

      return {};

   }


   void element::set_dialog_response(const ::payload & payloadResult)
   {


   }


   ::payload element::get_dialog_response()
   {

      return {};

   }


   ::acme::user::interaction *element::acme_get_wnd() 
   {
      
      return nullptr; 
   
   }


   ::user::interaction * element::get_wnd()
   {

      return nullptr;

   }

   //
   // ::task * element::get_task()
   // {
   //
   //    return nullptr;
   //
   //    //auto puserelement = get_wnd();
   //
   //    //if (::is_null(puserelement))
   //    //{
   //
   //    //   return get_app();
   //
   //    //}
   //
   //    //return puserelement->m_pthreadUserInteraction;
   //
   // }
   //


   //::windowing::window * element::get_impl() const
   //{

   //   ::user::element * pelement = get_wnd();

   //   if (pelement == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   if (pelement->m_pimpl.is_null())
   //   {

   //      return nullptr;

   //   }

   //   try
   //   {

   //      return pelement->m_pimpl->get_impl();

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

   void element::destroy()
   {

      ::user::command_update_target::destroy();

   }


   ::acme::user::interaction *element::acme_host_interaction()
   {

      // if (get_session() == nullptr
      //    || get_session() == nullptr)
      //{

      //   return nullptr;

      //}

      // if (get_session()->m_puserelementHost)
      //{

      //   return __user_element(get_session()->m_puserelementHost);

      //}
      // else
      //{

      return acme_get_wnd();

      //}
   }


   ::user::interaction * element::host_interaction()
   {

      //if (get_session() == nullptr
      //   || get_session() == nullptr)
      //{

      //   return nullptr;

      //}

      //if (get_session()->m_puserelementHost)
      //{

      //   return __user_element(get_session()->m_puserelementHost);

      //}
      //else
      //{

      return get_wnd();

      //}

   }

   
   ::acme::windowing::window *element::acme_host_window()
   {

      return acme_get_wnd()->acme_windowing_window();

   }


   ::windowing::window *element::host_window() 
   {
      
      return nullptr; 
   
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


   //void element::UpdateWindow()
   //{

   //   //ASSERT(::IsWindow(GetHandle()));
   //   //::UpdateWindow(GetHandle());

   //}


   //void element::Invalidate(bool bErase)
   //{

   //   __UNREFERENCED_PARAMETER(bErase);

   //   //ASSERT(::IsWindow(GetHandle()));
   //   //::InvalidateRect(GetHandle(), nullptr, bErase);

   //}

   bool element::has_pending_redraw_flags()
   {

      return false;

   }


   //bool element::Redraw(i32_rectangle_array_base & recta)
   //{

   //   bool bOk = true;

   //   for(::i32 i = 0; i < recta.get_size(); i++)
   //   {

   //      if(!get_wnd()->RedrawWindow(recta[i]))
   //         bOk = false;

   //   }

   //   return bOk;

   //}


   //bool element::Redraw(const ::i32_rectangle & rectangle, ::draw2d::region * prgn)
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


   /*bool element::client_to_screen(::i32_rectangle * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }


   bool element::client_to_screen(::f64_rectangle * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }
*/

//bool element::client_to_screen(::i32_point * ppoint)
//{

//   ::offset_point(ppoint, client_screen_top_left());

//   return true;

//}


//bool element::client_to_screen(::f64_point * ppoint)
//{

//   ::offset(ppoint, client_screen_top_left());

//   return true;

//}


//bool element::client_to_screen(::i64_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, i64_point(client_screen_top_left()));

//   return true;

//}


//bool element::client_to_screen(::i64_point * ppoint)
//{

//   ::offset_point(ppoint, client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::i32_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::f64_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::i32_point * ppoint)
//{

//   ::offset_point(ppoint, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::f64_point * ppoint)
//{

//   ::offset_point(ppoint, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::i64_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::i64_point * ppoint)
//{

//   ::offset_point(ppoint, -client_screen_top_left());

//   return true;

//}


//bool element::GetWindowPos(::i32_rectangle * prectangle)
//{

//   throw ::interface_only();

//   return false;

//}


//bool element::window_rectangle(::i32_rectangle * prectangle)
//{

//   throw ::interface_only();

//   return false;

//}


//::f64_point element::client_screen_top_left()
//{

//   return nullptr;

//}


//bool element::this->rectangle(::i32_rectangle * prectangle)
//{

//   throw ::interface_only();

//   return false;

//}


//bool element::this->rectangle(::i64_rectangle * prectangle)

//{

//   throw ::interface_only();

//   return false;

//}


//bool element::window_rectangle(::i64_rectangle * prectangle)

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


   bool element::is_descendant(element * puiIsDescendant, bool bIncludeSelf)
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
//   character_count element::_009GetWindowText(wchar_t * pwsz, ::i32 n)
//#else
//   character_count element::_009GetWindowText(char_pointer psz, ::i32 n)
//#endif
//   {
//
//      return -1;
//
//   }
//
//
//   character_count element::_009GetWindowTextLength()
//   {
//
//      return -1;
//
//   }



   //bool element::SetPlacement(const ::i32_rectangle & rectangle,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::add_fps_interest(::particle * pparticle)
   {

      //return false;

   }


   void element::erase_fps_interest(::particle * pparticle)
   {

      //return false;

   }


   bool element::is_fps_interest(::particle * pparticle)
   {

      return false;

   }


   string element::get_title()
   {

      return get_window_text();

   }


   //::i32 element::sync_message_box(::payload payload)
   //{

   //   if (payload.get_type() == e_type_string)
   //   {

   //      payload["message"] = payload;

   //   }

   //   payload["parent"] = this;
   //   payload["title"] = get_title();

   //   return message_box(payload);

   //}


   //::i32 element::sync_message_box_timeout(const ::scoped_string & scopedstrMessage, ::time timeTimeOut, ::u32 fuStyle)
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


   //void element::message_box_timeout(const ::scoped_string & scopedstrMessage, ::time timeTimeout, ::u32 fuStyle)
   //{

   //   fork([=]()
   //      {

   //         sync_message_box_timeout(strMessage, timeTimeout, fuStyle);

   //      });

   //}
   //bool element::place(const ::i32_rectangle & rectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::RepositionWindow(::i32 x,::i32 y,::i32 cx,::i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::MoveWindow(::i32 x,::i32 y,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::move_to(const ::i32_point & point)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::SizeWindow(::i32 cx,::i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_size(const i32_size & sz)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ResizeWindow(::i32 cx,::i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ResizeWindow(const i32_size & sz,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_window_position(class zorder zorder, const ::i32_rectangle & rectangle, ::u32 nFlags)

   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //bool element::defer_set_window_pos(iptr z, const  const i32_rectangle & & rectangle, ::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of i32_rectangle(x, y, cx, cy)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::defer_set_window_pos(iptr z,::i32 x,::i32 y,::i32 cx,::i32 cy,::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of i32_rectangle(x, y, cx, cy)
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


   ::user::interaction * element::_001FromPoint(::i32_point point, bool bTestedIfParentVisible)
   {

      throw ::interface_only();

      return nullptr;

   }


   bool element::_001IsPointInside(const ::i32_point & point)
   {

      return false;

   }


   ::user::interaction * element::get_child_by_name(const ::scoped_string & scopedstrName, ::collection::index iItem, ::i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_child_by_id(const atom & atom, ::collection::index iItem, ::i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::element * element::get_primitive_by_id(const atom & atom, ::collection::index iItem, ::i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::host_post(const ::procedure & procedure)
   {

      //throw ::interface_only();

      throw ::interface_only();

   }


   //lresult element::send(::message::message * pmessage)
   //{

   //   message_handler(pmessage);

   //   return pmessage->m_lresult;

   //}


   //// pmessage object should be allocated with ___new in
   //// base or derived object and will be delete after
   //// handling
   //bool element::post(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   lresult element::send_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, const ::i32_point & point)
   {

      return message_call(eusermessage, wparam, lparam, point);

   }


   lresult element::send_message(::message::message * pmessage)
   {

      return message_call(pmessage);

   }


   lresult element::message_call(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, const ::i32_point & point)
   {

      return 0;

   }


   lresult element::message_call(::message::message * pmessage)
   {

      return 0;

   }


   void element::on_message(::message::message * pmessage)
   {
      
      
   }

#ifdef LINUX


   lresult element::send_x11_event(void * phappening)
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


   //bool element::ModifyStyle(::u32 dwRemove,::u32 dwAdd,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ModifyStyleEx(::u32 dwRemove,::u32 dwAdd,::u32 nFlags)
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


   //::user::frame_element * element::top_level_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void element::send_message_to_descendants(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, bool bDeep, bool bOnlyPerm)
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


   // void element::subclass_window(oswindow posdata)
   // {
   //
   //    throw ::interface_only();
   //
   // }
   //
   //
   // oswindow element::unsubclass_window()
   // {
   //
   //    throw ::interface_only();
   //
   //    return nullptr;
   //
   // }


   void element::create_child(::user::interaction * puserelementParent)
   {

      //throw ::interface_only();

      throw ::interface_only();

      //return ::success;

   }


   enum_control_type element::get_control_type()
   {

      return e_control_type_none;

   }


   //bool element::create_element(::user::element * puiParent, ::request * prequest, ::u32 uExStyle, ::u32 uStyle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::on_before_create_window(::acme::windowing::window * pwindowbase)
   {


   }


   // void element::on_create_window()
   // {
   //
   //
   //
   // }



   ////bool element::create_window_ex(::pointer<::user::system>pcs, ::user::element * puiParent, const ::atom & atom)
   ////void element::create_host(enum_parallelization eparallelization)
   //void element::create_host()
   //{

   //   //throw ::interface_only();

   //   //return ::error_no_interface;

   //   throw ::interface_only();

   //}


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

      return this->_is_this_window();

   }


   bool element::_is_this_window() const 
   {
         
      return m_bUserElementOk; 
      
   }


   ::user::interaction * element::first_child()
   {

      return nullptr;

   }


   ::user::interaction * element::last_child()
   {

      return nullptr;

   }


   ::user::interaction * element::last_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::next_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::previous_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::first_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::next_sibling(::user::interaction * puserinteraction)
   {

      return nullptr;

   }


   ::user::interaction * element::previous_sibling(::user::interaction * puserinteraction)
   {

      return nullptr;

   }


   ::user::interaction * element::bottom_child()
   {

      return nullptr;

   }


   ::user::interaction * element::top_child()
   {

      return nullptr;

   }


   ::user::interaction * element::bottom_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::under_sibling()
   {

      return nullptr;

   }



   ::user::interaction * element::above_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::top_sibling()
   {

      return nullptr;

   }


   ::user::interaction * element::above_sibling(::user::interaction * puserinteraction)
   {

      return nullptr;

   }


   ::user::interaction * element::under_sibling(::user::interaction * puserinteraction)
   {

      return nullptr;

   }



   //::i32 element::get_window_long(::i32 nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //::i32 element::set_window_long(::i32 nIndex,::i32 lValue)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //iptr element::get_window_long_ptr(::i32 nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //void element::set_window_long_ptr(::i32 nIndex, iptr lValue)
   //{

   //   throw ::interface_only();

   //   throw ::interface_only();

   //}


   //bool element::RedrawWindow(const ::i32_rectangle& rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   ::user::interaction * element::ChildWindowFromPoint(const ::i32_point & point)
   {

      throw ::interface_only();

   }


   ::user::interaction * element::ChildWindowFromPoint(const ::i32_point & point, ::u32 nFlags)
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


//   ::user::element * element::get_next_window(bool bIgnoreChildren)
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


   //::user::element * element::GetActiveWindow()
   //{

   //   ::user::element * pelement = get_wnd();

   //   if(pelement == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pelement->GetActiveWindow();

   //}


   //bool element::XXXSetFocus()
   //{

   //   ::pointer<::user::element>pelement = get_wnd();

   //   if(pelement.is_null())
   //   {

   //      return false;

   //   }

   //   return get_wnd()->XXXSetFocus();

   //}


   //element * element::set_active_window()
   //{

   //   //throw ::interface_only();

   //   return nullptr;

   //}


   //bool element::set_foreground_window()
   //{

   //   return true;

   //}


   ::user::interaction * element::GetLastActivePopup()
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::set_rectangle(const ::i32_rectangle & rectangle)
   {

   }



   void element::set_position(const ::i32_point & point)
   {


   }


   void element::set_size(const ::i32_size & size)
   {


   }


   void element::set_interaction_rectangle(const ::i32_rectangle & rectangle)
   {


   }


   ::i32_rectangle element::get_rectangle()
   {

      return acme_user_interaction()->get_rectangle();

   }


   ::i32_rectangle element::get_window_rectangle()
   {

      return acme_windowing_window()->get_window_rectangle();

   }


   void element::redraw()
   {


   }


   // void element::set_mouse_capture()
   // {


   // }



   void element::edit_on_set_focus(::user::interaction * puserinteraction)
   {


   }


   void element::edit_on_kill_focus(::user::interaction * puserinteraction)
   {

   }


   character_count element::get_window_text(char_pointer pszStringBuf, character_count nMaxCount)
   {

      throw ::interface_only();

      return 0;

   }


   string element::get_window_text()
   {

      //throw ::interface_only();

      return "";

   }


   void element::get_window_text(string & rString)
   {

      throw ::interface_only();

   }


   character_count element::get_window_text_length()
   {

      throw ::interface_only();

      return 0;

   }


   //::user::element * element::EnsureTopLevel()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::element * element::EnsureParentTopLevel()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::element * element::GetParentTopLevel() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_element * element::GetParentTopLevelFrame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_element * element::EnsureParentFrame()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //lresult element::default_window_procedure()
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //::u32 element::GetStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //::u32 element::GetExStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //void element::start_destroying_window()
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   void element::destroy_window()
   {

   }


   //void element::post_non_client_destroy()
   //{

   //   destroy();

   //}


   ::user::interaction * element::get_parent()
   {

      throw ::interface_only();

      return nullptr;

   }


   //::user::frame_element * element::get_parent_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void element::CalcWindowRect(::i32_rectangle * prectangle,::u32 nAdjustType)

   //{

   //   throw ::interface_only();

   //}


   void element::RepositionBars(::draw2d::graphics_pointer & pgraphics, ::u32 nIDFirst, ::u32 nIDLast, ::atom idLeftOver, ::u32 nFlag, ::i32_rectangle * prectParam, const ::i32_rectangle & rectangleX, bool bStretch)
   {

      throw ::interface_only();

   }


   ::user::element * element::set_owner(::user::element * pelement)
   {

      //throw ::interface_only();

      return nullptr;

   }


   ::user::element * element::set_parent(::user::element * pelement)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   /*::user::frame_element * element::get_owner_frame() const
   {

      throw ::interface_only();

      return nullptr;

   }*/


   bool element::is_top_level_window()
   {

      return false;

   }


   //element * element::get_parent() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_element * element::frame() const
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


   void element::viewport_client_to_screen(::i32_sequence2 & sequence)
   {

      throw ::interface_only();

   }


   void element::viewport_screen_to_client(::i32_sequence2 & sequence)
   {

      throw ::interface_only();

   }


   void element::viewport_client_to_screen(::i32_rectangle & rectangle)
   {

      throw ::interface_only();

   }


   void element::viewport_screen_to_client(::i32_rectangle & rectangle)
   {

      throw ::interface_only();

   }


   //::i32 element::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //::i32 element::GetWindowRgn(HRGN hRgn)
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

   }


   //lresult element::message_handler(MESSAGE * pmessage)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   bool element::GetWindowPlacement(WINDOWPLACEMENT* puserelementpl)
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
//   bool element::SetWindowPlacement(const WINDOWPLACEMENT* puserelementpl)
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

   //   ::user::element * puiTopLevel = get_top_level();

   //   if (puiTopLevel == nullptr)
   //   {

   //      return true;

   //   }

   //   //::user::element * puiActive = puiTopLevel->GetActiveWindow();

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


   //void element::SetRedraw(bool bRedraw)
   //{

   //   throw ::interface_only();

   //}


   //bool element::GetUpdateRect(::i32_rectangle * prectangle, bool bErase)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::i32 element::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //void element::InvalidateRect(const ::i32_rectangle & rectangle,bool bErase)

   //{

   //   throw ::interface_only();

   //}


   //void element::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //}


   //void element::ValidateRect(const ::i32_rectangle & rectangle)

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


   //void element::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   void element::on_reposition()
   {

      //throw ::interface_only();

   }


   void element::on_size()
   {

      //throw ::interface_only();

   }


   bool element::is_this_visible(enum_layout elayout)
   {

      return true;

   }


   // void element::on_show_window()
   // {
   //
   //    throw ::interface_only();
   //
   // }


   //void element::window_show_change_visibility()
   //{


   //}


   //void element::ShowOwnedPopups(bool bShow)
   //{

   //   throw ::interface_only();

   //}


   //bool element::attach(::acme::windowing::window * pacmewindowingwindow)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void * element::detach_win32_HWND()
   {

      throw ::interface_only();

      return nullptr;

   }


   void element::pre_subclass_window()
   {

      throw ::interface_only();

   }


   //atom element::run_modal_loop(::user::element * pelement, ::u32 dwFlags)
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom element::RunModalLoop(::u32 dwFlags)
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom element::_001RunModalLoop(::u32 dwFlags)
   //{

   //   throw ::interface_only();

   //   return atom();

   //}


   //bool element::ContinueModal()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void element::EndModalLoop(atom nResult)
   //{

   //   throw ::interface_only();

   //}


   //void element::_run_modal_loop()
   //{


   //}


   lresult element::message_handler(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
   {

      throw ::interface_only();

      return {};

   }


   void element::post_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
   {

      throw ::interface_only();

   }


   //void element::set_timer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pdata)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //void element::kill_timer(uptr uEvent)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //bool element::has_keyboard_focus() const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_mouse_capture(::user::element * pelement)
   //{

   //   return false;

   //}


   //::user::element * element::get_capture() const
   //{

   //   return nullptr;

   //}



   //bool element::set_keyboard_focus(::user::element * pelement)
   //{

   //   return false;

   //}


   //::user::element * element::get_keyboard_focus() const
   //{

   //   return nullptr;

   //}




   void element::_000OnMouseLeave(::message::message * pmessage)
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


   //void element::sketch_to_layout()
   //{

   //}


   //void element::layout_to_design(bool & bUpdateBuffer, bool & bUpdateWindow)
   //{

   //}


   void element::_001UpdateWindow()
   {

   }


   void element::queue_selection_synchronization()
   {


   }


   // void element::window_apply_visual(const window_state & windowstate)
   // {

   // }


   //void element::design_window_minimize(const ::user::activation & useractivation)
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_maximize()
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_full_screen(const ::i32_rectangle & rectangleHint)
   //{

   //   throw ::interface_only();

   //}


   //void element::design_window_normal(::e_display edisplay)
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


   void element::OnLinkClick(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTarget)
   {

      throw ::interface_only();

   }


   //void element::set_config_per_second(::frequency dConfigFps)
   //{

   //   //get_host_user_element()->m_pimpl->set_config_per_second(dConfigFps);

   //}


   //::frequency element::get_config_per_second()
   //{

   //   //return get_host_user_element()->m_pimpl->get_config_per_second();

   //}


   //::frequency element::get_output_per_second()
   //{

   //   //auto pelement = get_host_user_element();

   //   //if (pelement == nullptr)
   //   //{

   //   //   return 0.0;

   //   //}

   //   //auto pimpl = pelement->m_pimpl;

   //   //if (pimpl.is_null())
   //   //{

   //   //   return 0.0;

   //   //}

   //   //return pimpl->get_output_per_second();
   //   return 0.0;

   //}


   void element::create_message_queue(const ::scoped_string & scopedstrName)
   {

      throw ::interface_only();

      //return false;

   }


   ::acme::user::interaction * element::acme_user_interaction()
   {

      return nullptr;

   }


   ::acme::windowing::window * element::acme_windowing_window()
   {

      return nullptr;

   }


   ::operating_system::window element::operating_system_window()
   {

      return {};

   }


   ::user::interaction_base * element::user_interaction_base()
   {

      return nullptr;

   }


   ::windowing::window_base * element::windowing_window_base()
   {

      return nullptr;

   }



   ::user::interaction * element::user_interaction()
   {

      return nullptr;

   }


   ::windowing::window * element::windowing_window()
   {

      auto pacmewindowingwindow = acme_windowing_window();

      if (::is_null(pacmewindowingwindow))
      {

         return nullptr;

      }

      return pacmewindowingwindow->windowing_window();

   }

   //::user::element_base * element::user_prototype()
   //{

   //   return nullptr;

   //}


   //::user::element * element::user_element()
   //{

   //   return nullptr;

   //}


   void element::on_select()
   {

      throw ::interface_only();

   }


   bool element::is_place_holder()
   {

      throw ::interface_only();

      return false;

   }


   ::f64 element::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      return 0.0;

   }


   //::windowing::cursor * element::get_mouse_cursor()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void element::aaa_set_mouse_cursor(::windowing::cursor * pcursor)
   //{

   //   return success_none;

   //}


   //void element::set_cursor(::windowing::/*cursor * pcursor)
   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //::i32_point element::get_cursor_position() const
   //{

   //   return ::i32_point();

   //}


   //::f64_size element::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   return { 0.0, 0.0 };

   //}


   //::f64_size element::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::f64_rectangle rectanglePadding(2.0, 2.0, 2.0, 2.0);

   //   auto sizeFitting = _001CalculateFittingSize(pgraphics);

   //   ::f64_size sizePaddedFitting;

   //   sizePaddedFitting.cx = rectanglePadding.left + sizeFitting.cx + rectanglePadding.right;

   //   sizePaddedFitting.cy = rectanglePadding.top + sizeFitting.cy + rectanglePadding.bottom;

   //   return sizePaddedFitting;

   //}


   //bool element::can_merge(::user::element * pelement)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::merge(::user::element * pelement)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::element * element::top_child()
   //{

   //   return last_child();

   //}


   //::user::element * element::bottom_child()
   //{

   //   return first_child();

   //}


   //::user::element * element::above_sibling(::user::element * pelement)
   //{

   //   return next_sibling(pelement);

   //}


   //::user::element * element::above_sibling()
   //{

   //   return next_sibling();

   //}


   //::user::element * element::under_sibling(::user::element * pelement)
   //{

   //   return previous_sibling(pelement);

   //}


   //::user::element * element::under_sibling()
   //{

   //   return previous_sibling();

   //}

   //::user::element * element::top_sibling()
   //{

   //   return last_sibling();

   //}


   //::user::element * element::bottom_sibling()
   //{

   //   return first_sibling();

   //   return nullptr;

   //}

   //::user::element * element::first_child()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::element * element::last_child()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}

   //::user::element * element::first_sibling()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::element * element::last_sibling()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::element * element::previous_sibling()
   //{

   //   return nullptr;

   //}

   //::user::element * element::previous_sibling(::user::element * pelement)
   //{

   //   __UNREFERENCED_PARAMETER(pelement);

   //   return nullptr;

   //}

   //::user::element * element::next_sibling()
   //{

   //   return nullptr;

   //}

   //::user::element * element::next_sibling(::user::element * pelement)
   //{

   //   __UNREFERENCED_PARAMETER(pelement);

   //   return nullptr;

   //}


   //void element::mouse_hover_add(::user::element * pinterface)
   //{

   //   throw ::interface_only();

   //}


   //bool element::mouse_hover_erase(::user::element * pinterface)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void element::_task_transparent_mouse_event()
   //{


   //}


   //void element::on_set_keyboard_focus()
   //{

   //}


   //void element::on_kill_keyboard_focus()
   //{

   //}


   bool element::GetFocusRect(::i32_rectangle & rectangle)
   {

      return false;

   }




   void element::window_minimize()
   {


   }


   void element::window_maximize()
   {


   }


   void element::window_full_screen()
   {


   }


   void element::window_restore()
   {


   }


   void element::window_close()
   {


   }


   void element::on_window_deiconified()
   {


   }


   void element::on_window_activated()
   {


   }


   void element::on_window_iconified()
   {


   }


   void element::on_window_deactivated()
   {


   }


   void element::on_window_shown()
   {


   }


   void element::on_window_hidden()
   {


   }


   ::e_display element::defer_window_get_best_display_deduction()
   {

      if(is_window_visible())
      {

         if(is_window_full_screen())
         {

            return e_display_full_screen;

         }
         else if(is_window_zoomed())
         {

            return e_display_zoomed;

         }
         else if(is_window_active())
         {

            return e_display_normal;

         }
         else
         {

            return e_display_iconic;

         }

      }
      else
      {

         return e_display_hide;

      }

   }


   void element::_on_window_simple_action(const_char_pointer pszActionName, ::user::activation_token * puseractivationtoken)
   {


   }


   void element::on_window_close()
   {


   }

   
   void element::set_cursor(enum_cursor ecursor)
   {


   }


   void element::set_mouse_capture()
   {


   }


   bool element::is_mouse_captured()
   {

      return false;

   }


   bool element::has_mouse_capture()
   {

      return false;

   }


   void element::release_mouse_capture()
   {



   }


   bool element::defer_release_mouse_capture()
   {

      if(!has_mouse_capture())
      {

         debug() << "::user::element::defer_release_mouse_capture !has_mouse_capture";

         return false;

      }

      debug() << "::user::element::defer_release_mouse_capture has_mouse_capture going to release_mouse_capture";

      release_mouse_capture();

      return true;

   }


   bool element::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

      return false;

   }


   bool element::defer_perform_entire_resizing_process(const ::experience::e_frame & eframeSizing, ::user::mouse * pmouse)
   {

      return false;

   }


   void element::defer_update_display()
   {


   }


   //::user::element * element::get_keyboard_focus()
   //{

   //   auto puserelementHost = get_host_user_element();

   //   if (::is_null(puserelementHost))
   //   {

   //      return nullptr;

   //   }

   //   ::user::element * pprimitive = puserelementHost->get_keyboard_focus();

   //   if(pprimitive == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return dynamic_cast < ::user::element * > (pprimitive);

   //}


   ::i32 element::get_descendant_level(::user::element * pelement)
   {

      throw ::interface_only();

      return -1;

   }


   //bool element::is_descendant(const ::user::element * pelement,bool bIncludeSelf) const
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


//   void element::_001OnTriggerMouseInside()
//   {
//
//      throw ::interface_only();
//
//   }


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


   ::u32 element::get_window_default_style()
   {

      throw ::interface_only();

      return 0;

   }


   ::user::enum_window_type element::get_window_type()
   {

      return e_window_type_window;

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


   bool element::is_selected(::item * pitem)
   {

      throw ::interface_only();

      return false;

   }


   //bool element::has_command_handler(::message::command * pcommand)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {


   }





   bool element::_001OnBeforeEnterIconic()
   {

      return true;

   }


   bool element::_001OnBeforeEnterNormal()
   {

      return true;

   }


   bool element::_001OnBeforeEnterZoomed()
   {

      return true;

   }


   bool element::_001OnBeforeEnterFullScreen()
   {

      return true;

   }


   bool element::_001OnBeforeEnterAppearance()
   {

      return true;

   }


   void element::_001OnAfterEnterIconic()
   {

   }


   void element::_001OnAfterEnterNormal()
   {

   }


   void element::_001OnAfterEnterZoomed()
   {

   }


   void element::_001OnAfterEnterFullScreen()
   {

   }


   void element::_001OnAfterEnterAppearance()
   {

   }


   bool element::_001OnBeforeExitIconic()
   {

      return true;

   }


   bool element::_001OnBeforeExitNormal()
   {

      return true;

   }


   bool element::_001OnBeforeExitZoomed()
   {

      return true;

   }


   bool element::_001OnBeforeExitFullScreen()
   {

      return true;

   }


   bool element::_001OnBeforeExitAppearance()
   {

      return true;

   }


   void element::_001OnAfterExitIconic()
   {

   }


   void element::_001OnAfterExitNormal()
   {

   }


   void element::_001OnAfterExitZoomed()
   {

   }


   void element::_001OnAfterExitFullScreen()
   {

   }


   void element::_001OnAfterExitAppearance()
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




   //void element::ping(::object * pobjectPinger)
   //{

   //   throw ::interface_only();

   //}


   //bool element::set_window_position(class zorder zorder, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy, ::u32 nFlags)
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

      //void element::operator()(::timer * ptimer)
      //{



      //}


//   bool element::has_pending_graphical_update()
//   {
//
//      return false;
//
//   }


   void element::on_after_graphical_update()
   {

   }


   void element::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource)
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


   //void element::graphics_thread_post_redraw(bool bUpdateBuffer)
   //{

   //}


   void element::fps_interest_stop()
   {


   }


} // namespace user









namespace user
{


   void element::post_simple_command(const enum_simple_command & ecommand, const ::lparam & lparam)
   {

      post_message(::user::e_message_simple_command, ecommand, lparam);

      //return true;

   }


   void element::add_child_handler(::particle * pparticle, const ::atom & atomChild, bool bPriority)
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


//   ::pointer<::message::message>element::get_message(const ::atom & atom, const ::wparam & wparam, const ::lparam & lparam)
//   {
//
//      ::pointer<::message::message>pmessage;
//
//      auto eprototype = ::message::get_message_prototype((enum_message) atom.i64, 0);
//
//      switch (eprototype)
//      {
//      case ::message::PrototypeNone:
//      {
//
//         pmessage = allocateø ::user::message();
//
//      }
//      break;
//      case ::message::PrototypeCreate:
//      {
//         pmessage = allocateø ::message::create();
//      }
//      break;
//      case ::message::PrototypeEnable:
//      {
//         pmessage = allocateø ::message::enable();
//      }
//      break;
//      case ::message::PrototypeNcActivate:
//      {
//         pmessage = allocateø ::message::nc_activate();
//      }
//      break;
//      case ::message::PrototypeKey:
//      {
//         pmessage = allocateø ::message::key();
//      }
//      break;
//      case ::message::PrototypeTimer:
//      {
//         
//         //throw ::exception(::exception("do not use ::user::e_message_timer or Windows set_timer/kill_timer"));
//         
//         pmessage = allocateø ::message::timer();
//
//      }
//      break;
//      case ::message::PrototypeShowWindow:
//      {
//         pmessage = allocateø ::message::show_window();
//      }
//      break;
//      case ::message::PrototypeSetCursor:
//      {
//         pmessage = allocateø ::message::set_cursor();
//      }
//      break;
//      case ::message::PrototypeNcHitTest:
//      {
//         pmessage = allocateø ::message::nc_hit_test();
//      }
//      break;
//      case ::message::PrototypeMove:
//      {
//         pmessage = allocateø ::message::transfer();
//      }
//      break;
//      case ::message::PrototypeEraseBkgnd:
//      {
//         pmessage = allocateø ::message::erase_bkgnd();
//      }
//      break;
//      case ::message::PrototypeScroll:
//      {
//         pmessage = allocateø ::message::scroll();
//      }
//      break;
//      case ::message::PrototypeSetFocus:
//      {
//         pmessage = allocateø ::message::set_keyboard_focus();
//      }
//      break;
//      case ::message::PrototypeKillFocus:
//      {
//         pmessage = allocateø ::message::kill_keyboard_focus();
//      }
//      break;
//#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__)
//      case ::message::PrototypeWindowPos:
//      {
//         pmessage = allocateø ::message::window_pos();
//      }
//      break;
//      case ::message::PrototypeNcCalcSize:
//      {
//         pmessage = allocateø ::message::nc_calc_size();
//      }
//      break;
//#endif
//      case ::message::PrototypeMouse:
//      {
//         pmessage = allocateø ::message::mouse();
//      }
//      break;
//      case ::message::PrototypeMouseWheel:
//      {
//         pmessage = allocateø ::message::mouse_wheel();
//      }
//      break;
//      case ::message::PrototypeSize:
//      {
//         pmessage = allocateø ::message::size();
//      }
//      break;
//      case ::message::PrototypeActivate:
//      {
//         pmessage = allocateø ::message::activate();
//      }
//      break;
//      case ::message::PrototypeMouseActivate:
//      {
//         pmessage = allocateø ::message::mouse_activate();
//      }
//      break;
//      case ::message::PrototypeSimpleCommand:
//      {
//         pmessage = allocateø ::message::simple_command();
//      }
//      break;
//      default:
//      {
//         pmessage = allocateø ::message::message();
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
//      pmessage->set(get_oswindow(), get_window(), eusermessage, wparam, lparam);
//
//      return pmessage;
//
//   }


   // bool element::call_message_handler(const ::atom & atom, const ::wparam & wparam, const ::lparam & lparam, const ::i32_point & point, lresult * plresult)
   // {

   //    //auto pmessage = get_message(eusermessage, wparam, lparam);

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


//bool element::GetWindowPlacement(WINDOWPLACEMENT * puserelementpl)

//{

//   __UNREFERENCED_PARAMETER(puserelementpl);


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


//   bool element::SetPlacement(const ::i32_rectangle & rectangle, ::u32 nFlags)
//   {
//
//      __UNREFERENCED_PARAMETER(rectangle);
//      __UNREFERENCED_PARAMETER(nFlags);
//
//      return false;
//
//   }


   ::i32 element::get_total_page_count(::handler_context * pcontext)
   {

      return 1;

   }



   //void element::operator()(::timer * ptimer)
   //{

   //   __UNREFERENCED_PARAMETER(ptimer);

   //}

   //void element::add_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   m_threadptra.add(pthread);

   //}


   //void element::erase_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   m_threadptra.erase(pthread);

   //}

   //bool element::enable_window(bool bEnableWindow)
   //{

   //   return true;

   //}



   void element::keyboard_focus_OnTimer(::i32 iTimer)
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


   //void element::route(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   handle(ptopic, phandlercontext);

   //}


   //void element::handle_event(control_event * phappening)
   //{

   //   __UNREFERENCED_PARAMETER(phappening);

   //}


   bool element::keyboard_focus_is_focusable()
   {

      //return papp->keyboard_focus_is_focusable(this);
      return false;

   }


   bool element::keyboard_focus_OnKillFocus(::acme::windowing::window * pacmewindowingwindow)
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
      //      
      //
      //      if (pprimitive == nullptr || pprimitive == this)
      //      {
      //
      //         aaa_clear_keyboard_focus();
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

      //   pprimitive = puiThis->first_child_user_element();

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

      //   pprimitive = puiThis->next_user_element();

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

      //      pprimitive = pprimitive->next_user_element();

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

      //   pprimitive = puiThis->first_child_user_element();

      //   if (pprimitive != puiThis)
      //   {

      //      while (pprimitive != nullptr && pprimitive != puiFocus)
      //      {

      //         if (pprimitive->keyboard_focus_is_focusable())
      //            return pprimitive;

      //         pfocusTry = pprimitive->keyboard_get_next_focusable(puiFocus, false, true, true);

      //         if (pfocusTry != nullptr)
      //            return pfocusTry;

      //         pprimitive = pprimitive->next_user_element();

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

      auto pwindow = acme_windowing_window();

      if (::is_null(pwindow))
      {

         return;

      }

      ::cast < ::acme::user::interaction > pacmeuserinteractionFocus = this;

      if (::is_null(pacmeuserinteractionFocus))
      {

         throw ::exception(error_wrong_state, "element should be at least a acme::user::element to get focus");

      }

      pwindow->set_keyboard_focus(pacmeuserinteractionFocus);

   }


   //void element::erase_keyboard_focus()
   //{

   //   auto pwindow = acme_windowing_window();

   //   if (::is_null(pwindow))
   //   {

   //      return;

   //   }

   //   ::cast < ::acme::user::element > pacmeuserinteractionFocus = this;

   //   if (::is_null(pacmeuserinteractionFocus))
   //   {

   //      throw ::exception(error_wrong_state, "element should be at least a acme::user::element to get focus (and then to loose it)");

   //   }

   //   pwindow->erase_keyboard_focus(pacmeuserinteractionFocus);

   //}


   //void element::clear_keyboard_focus(::user::element * pelementGainingFocusIfAny)
   //{

   //   throw ::interface_only();

   //}


   void element::mouse_focus_OnLButtonUp(::message::message * pmessage)
   {


   }


   bool element::_001CanEnterScreenSaver()
   {

      return false;

   }




   ::user::element * element::first_child_user_element()
   {

      return nullptr;

   }


   ::user::element * element::top_user_element()
   {

      return nullptr;

   }


   ::user::element * element::under_user_element()
   {

      return nullptr;

   }


   ::user::element * element::above_user_element()
   {

      return nullptr;

   }


   ::user::element * element::next_user_element()
   {

      return nullptr;

   }


   ::user::element * element::previous_user_element()
   {

      return nullptr;

   }


   ::windowing::window * element::window_get_parent()
   {

      return nullptr;

   }


   ::user::element * element::get_parent_primitive()
   {

      return nullptr;

   }


   ::user::prototype_impl * element::get_primitive_impl()
   {

      return nullptr;

   }


   //::user::element * element::get_wnd_primitive() const
   //{

   //   return nullptr;

   //}
   
   void element::create_window()
   {


   }


   void element::_create_window()
   {


   }

   
   ::user::check & element::check()
   {

      return m_check;

   }


   ::user::text & element::text()
   {

      return m_text;

   }


   void element::operator()(::timer * ptimer)
   {

//      return false;

   }


   //void element::operator()(::timer * ptimer)
   //{

   //   __UNREFERENCED_PARAMETER(ptimer);

   //}


   void element::on_reset_focus_start_tick()
   {

   }


   ::f32 element::preferred_dpi_x()
   {

      return 96.0f;

   }


   ::f32 element::preferred_dpi_y()
   {

      return 96.0f;

   }


   ::f32 element::preferred_density()
   {

      return 1.0f;

   }



   void element::set_need_redraw(
      const ::i32_rectangle_array_base & rectangleaNeedRedraw,
      ::draw2d::graphics * pgraphics,
      function<void()> function, 
      bool bAscendants)
   {

      __UNREFERENCED_PARAMETER(rectangleaNeedRedraw);
      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(function);
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


   //void element::hide()
   //{

   //   //return false;

   //}



   void element::edit_on_text(const ::scoped_string & scopedstr)
   {

   }


   void element::edit_on_sel(character_count iBeg, character_count iEnd)
   {

   }


   void element::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context)
   {

   }


   void element::on_text_composition(const ::scoped_string & scopedstr)
   {

   }


   void element::on_text_commit(const ::scoped_string & scopedstr)
   {

   }


   void element::on_text_composition_done()
   {

   }


   //bool element::is_text_composition_active()
   //{

   //   return false;

   //}


   void element::set_input_content_rect(const i32_rectangle & rectangle)
   {

   }


   void element::set_input_selection_rect(const i32_rectangle & rectangle)
   {

   }


   i32_rectangle element::get_input_content_rect()
   {

      return i32_rectangle();

   }


   i32_rectangle element::get_input_selection_rect()
   {

      return i32_rectangle();

   }


   bool element::InputConnectionBeginBatchEdit(bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionEndBatchEdit(bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionCommitText(const ::scoped_string & scopedstr, character_count iNewCursorPosition, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionDeleteSurroundingText(character_count iBeforeLength, character_count iAfterLength, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetComposingText(const ::scoped_string & scopedstr, character_count iNewCursorPosition, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetComposingRegion(character_count iStart, character_count iEnd, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetSelection(character_count iStart, character_count iEnd, bool bSuper)
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


   void element::display(::e_display edisplay, const ::user::activation & useractivation)
   {


   }


   void element::pick_single_file_to_save(const ::file::file_dialog_filter & filedialogfilter, const ::function < void(::file::file_dialog * pdialog) > & procedureResponse)
   {

      auto pfiledialog = node()->node_file_dialog();

      pfiledialog->m_bSave = true;

      pfiledialog->m_filedialogfilter.copy(filedialogfilter);

      pfiledialog->m_procedureResponse = procedureResponse;
      //{

      //      function(pdialog);
      //   //if (pdialog && pdialog->m_patha.has_element())
      //   //{

      //     // function(pdialog->m_patha.first(), pdialog->m_strExtension);

      //   //}
      //   //else
      //   //{

      //     // function({}, {});

      //   //}

      //};

      pfiledialog->call();

   }


void element::pick_single_file_to_open(const ::file::file_dialog_filter & filedialogfilter, const ::function < void(::file::file_dialog* pdialog) > & procedureResponse)
{

   auto pfiledialog = node()->node_file_dialog();

   pfiledialog->m_bSave = false;

   pfiledialog->m_filedialogfilter.copy(filedialogfilter);

   pfiledialog->m_procedureResponse = procedureResponse;

   //pfiledialog->m_function = [function](auto pdialog)
   //{


   //   if (pdialog && pdialog->m_patha.has_element())
   //   {

   //      function(pdialog->m_patha.first());

   //   }
   //   else
   //   {

   //      function({});

   //   }

   //};

   pfiledialog->call();

}


void element::pick_multiple_file(const ::file::file_dialog_filter & filedialogfiltera, const ::function < void(::file::file_dialog * pdialog) > & procedureResponse)
   {

      auto pfiledialog = node()->node_file_dialog();

      pfiledialog->m_procedureResponse = procedureResponse;

      //pfiledialog->m_function = [function](auto pdialog)
      //{


      //   if (pdialog && pdialog->m_patha.has_element())
      //   {

      //      function(pdialog->m_patha);

      //   }
      //   else
      //   {

      //      function({});

      //   }


      //};

      pfiledialog->call();

   }


   void element::pick_single_folder(const ::function < void(::file::file_dialog * pdialog) > & procedureResponse)
   {

      auto pfiledialog = node()->node_file_dialog();

      pfiledialog->m_procedureResponse = procedureResponse;

      //pfiledialog->m_function = [function](auto pdialog)
      //{


      //   if (pdialog && pdialog->m_patha.has_element())
      //   {

      //      function(pdialog->m_patha.first());

      //   }
      //   else
      //   {

      //      function({});

      //   }


      //};

      pfiledialog->call();

   }


   bool element::update_impact()
   {

      try
      {

         if (!on_before_impact_update())
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      try
      {

         if (!on_impact_update())
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      try
      {

         on_after_impact_update();

         return true;

      }
      catch (...)
      {


      }

      return false;

   }


   bool element::on_impact_update()
   {

      return true;

   }


   bool element::on_before_impact_update()
   {
      
      return true;

   }
   
   
   void element::on_after_impact_update()
   {


   }


   bool element::scroll_bar_x_visible(enum_layout elayout)
   {

      return false;

   }


   bool element::scroll_bar_y_visible(enum_layout elayout)
   {

      return false;

   }


   ::trace_statement & element::raw_trace_statement_prefix(::trace_statement & statement) const
   {

      ::string strType = ::platform::type(this).name();

      statement << strType;

      // ::string strAtom = id().as_string();
      //
      // if(strAtom.has_character() && strAtom != strType)
      // {
      //
      //    statement << "=" << strAtom;
      //
      // }

      //statement << "  ";

      return statement;

   }


   ::trace_statement & element::trace_statement_prefix(::trace_statement & statement) const
   {

      statement << "usrintr ";

      return raw_trace_statement_prefix(statement);

   }

   // bool element::has_mouse_capture()
   // {

   //    return false;
   // }


   // void element::release_mouse_capture()
   // {


   // }


   bool element::on_window_create(void * pCREATESTRUCT)
   {

      information("::acme::user::element::on_window_create()");

      return true;

   }


   void element::on_window_position(const ::i32_point & point)
   {

      information("::acme::user::element::on_window_position()");

   }


      void element::on_window_size(const ::i32_size & size)
      {

         information("::acme::user::element::on_window_size()");


      }



      void element::on_window_set_focus()
      {

         information("::acme::user::element::on_window_set_focus()");

      }


      void element::set_foreground_window(::user::activation_token *puseractivationtoken)
      {



      }


      void element::on_window_show(bool bShow, int iDetail)
      {


      }


      bool element::on_window_activate(::i32 iActivate, bool bMinimized,
                                           const operating_system::window &operatingsystemwindow)
      {

         return false;

      }


      bool element::on_window_mouse_activate(::i32 & iResult, const ::operating_system::window & operatingsystemwindowTop,
   ::i32 iHitTest, ::i32 iMessage)
      {

         information("::acme::user::element::on_window_mouse_activate");

         return false;

      }


      bool element::is_window_active()
      {

         return true;

      }


      bool element::is_window_zoomed()
      {

         return false;

      }


      bool element::is_window_full_screen()
      {

         return false;

      }


      bool element::is_window_visible()
      {

         return false;

      }


      bool element::is_window_stored_iconic()
      {

         return false;

      }


      bool element::is_window_iconic()
      {

         return false;

      }


      ::f32 element::get_window_scale()
      {

         return 1.0f;

      }


      ::i32_point element::screen_to_window_client(const ::i32_point & point)
      {

         return {};

      }


      ::i32_rectangle element::screen_to_window_client(const ::i32_rectangle & rectangle)
      {

         return {};

      }


      ::i32_point element::window_client_to_screen(const ::i32_point & point)
      {

         return {};

      }


      ::i32_rectangle element::window_client_to_screen(const ::i32_rectangle & rectangle)
      {

         return {};

      }


      void element::set_active_window()
      {



      }


      void element::set_window_text(const ::scoped_string & scopedstrString)
      {

         //m_pacmewindowingwindow->set_window_text(scopedstrString);

      }


      void element::set_window_text_source(const ::a_string_function & astringfunction)
      {

      }


      void element::set_window_style(::i32 iStyle)
      {

         //m_pacmewindowingwindow->set_window_style(iStyle);

      }


      ::i64 element::get_window_style()
      {

         return -1;

      }


      void element::show_window(::user_interface::enum_show_window eshowwindow)
      {

         //m_pacmewindowingwindow->show_window(iShowFlags);

      }


      void element::set_window_position(const ::operating_system::window & operatingsystemwindow, const ::i32_point & point, const ::i32_size & size, ::i32 iSetWindowPosFlags)
      {

         //m_pacmewindowingwindow->set_window_position(operatingsystemwindow, point, size, iSetWindowPosFlags);

      }


      void element::window_invalidate_rect(const ::i32_rectangle * prectangle, bool bErase)
      {

         //m_pacmewindowingwindow->window_invalidate_rect(prectangle, bErase);

      }


      void element::update_window()
      {

         //m_pacmewindowingwindow->update_window();

      }


      void element::redraw_window(const i32_rectangle *prectangle, void *pHRGN, ::i32 iRedrawFlags)
      {

         //m_pacmewindowingwindow->redraw_window(prectangle, pHRGN, iRedrawFlags);

      }


      void element::window_set_focus()
      {

         //m_pacmewindowingwindow->window_set_focus();

      }



      ::i32_rectangle element::window_get_client_rect()
      {

         //return m_pacmewindowingwindow->window_get_client_rect();

      return {};

      }


      ::i32_rectangle element::get_window_rect()
      {

         //return m_pacmewindowingwindow->get_window_rect();
      return {};

      }


      bool element::defer_update_system_menu()
      {

         return false;

      }


      void element::dump_operating_system_child_window_hierarchy()
      {

         //m_pacmewindowingwindow->dump_operating_system_child_window_hierarchy();

      }

   

   

} // namespace user



