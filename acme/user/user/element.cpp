#include "framework.h"
#include "element.h"
#include "item.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/handler/item.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/user/user/interaction.h"
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

   
   bool element::is_waiting_for_dialog_result()
   {

      return false;

   }


   ::payload element::wait_for_dialog_result(const class ::time & timeTimeout)
   {

      return {};

   }


   void element::set_dialog_result(const ::payload & payloadResult)
   {


   }


   ::payload element::get_dialog_result()
   {

      return {};

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
   //    //auto puserinteraction = get_wnd();
   //
   //    //if (::is_null(puserinteraction))
   //    //{
   //
   //    //   return get_app();
   //
   //    //}
   //
   //    //return puserinteraction->m_pthreadUserInteraction;
   //
   // }
   //


   //::windowing::window * element::get_impl() const
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

   void element::destroy()
   {

      ::user::command_update_target::destroy();

   }


   ::user::interaction * element::get_host_user_interaction()
   {

      //if (get_session() == nullptr
      //   || get_session() == nullptr)
      //{

      //   return nullptr;

      //}

      //if (get_session()->m_puserinteractionHost)
      //{

      //   return __user_interaction(get_session()->m_puserinteractionHost);

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


   //bool element::Redraw(int_rectangle_array & recta)
   //{

   //   bool bOk = true;

   //   for(int i = 0; i < recta.get_size(); i++)
   //   {

   //      if(!get_wnd()->RedrawWindow(recta[i]))
   //         bOk = false;

   //   }

   //   return bOk;

   //}


   //bool element::Redraw(const ::int_rectangle & rectangle, ::draw2d::region * prgn)
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


   /*bool element::client_to_screen(::int_rectangle * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }


   bool element::client_to_screen(::double_rectangle * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }
*/

//bool element::client_to_screen(::int_point * ppoint)
//{

//   ::offset_point(ppoint, client_screen_top_left());

//   return true;

//}


//bool element::client_to_screen(::double_point * ppoint)
//{

//   ::offset(ppoint, client_screen_top_left());

//   return true;

//}


//bool element::client_to_screen(::long_long_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, long_long_point(client_screen_top_left()));

//   return true;

//}


//bool element::client_to_screen(::long_long_point * ppoint)
//{

//   ::offset_point(ppoint, client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::int_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::double_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::int_point * ppoint)
//{

//   ::offset_point(ppoint, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::double_point * ppoint)
//{

//   ::offset_point(ppoint, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::long_long_rectangle * prectangle)
//{

//   ::offset_rect(prectangle, -client_screen_top_left());

//   return true;

//}


//bool element::screen_to_client(::long_long_point * ppoint)
//{

//   ::offset_point(ppoint, -client_screen_top_left());

//   return true;

//}


//bool element::GetWindowPos(::int_rectangle * prectangle)
//{

//   throw ::interface_only();

//   return false;

//}


//bool element::window_rectangle(::int_rectangle * prectangle)
//{

//   throw ::interface_only();

//   return false;

//}


//double_point element::client_screen_top_left()
//{

//   return nullptr;

//}


//bool element::this->rectangle(::int_rectangle * prectangle)
//{

//   throw ::interface_only();

//   return false;

//}


//bool element::this->rectangle(::long_long_rectangle * prectangle)

//{

//   throw ::interface_only();

//   return false;

//}


//bool element::window_rectangle(::long_long_rectangle * prectangle)

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
//   character_count element::_009GetWindowText(wchar_t * pwsz, int n)
//#else
//   character_count element::_009GetWindowText(char * psz, int n)
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



   //bool element::SetPlacement(const ::int_rectangle & rectangle,unsigned int nFlags)
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


   //int element::sync_message_box(::payload payload)
   //{

   //   if (payload.get_type() == e_type_string)
   //   {

   //      payload["message"] = payload;

   //   }

   //   payload["parent"] = this;
   //   payload["title"] = get_title();

   //   return message_box(payload);

   //}


   //int element::sync_message_box_timeout(const ::string & pszMessage, ::time timeTimeOut, unsigned int fuStyle)
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


   //void element::message_box_timeout(string strMessage, ::time timeTimeout, unsigned int fuStyle)
   //{

   //   fork([=]()
   //      {

   //         sync_message_box_timeout(strMessage, timeTimeout, fuStyle);

   //      });

   //}
   //bool element::place(const ::int_rectangle & rectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::RepositionWindow(int x,int y,int cx,int cy,unsigned int nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::MoveWindow(int x,int y,unsigned int nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::move_to(const ::int_point & point)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::SizeWindow(int cx,int cy,unsigned int nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_size(const int_size & sz)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ResizeWindow(int cx,int cy,unsigned int nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ResizeWindow(const int_size & sz,unsigned int nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_window_position(class zorder zorder, const ::int_rectangle & rectangle, unsigned int nFlags)

   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //bool element::defer_set_window_pos(iptr z, const  const int_rectangle & & rectangle, unsigned int nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of int_rectangle(x, y, cx, cy)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::defer_set_window_pos(iptr z,int x,int y,int cx,int cy,unsigned int nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of int_rectangle(x, y, cx, cy)
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


   ::user::interaction * element::_001FromPoint(::int_point point, bool bTestedIfParentVisible)
   {

      throw ::interface_only();

      return nullptr;

   }


   bool element::_001IsPointInside(const ::int_point & point)
   {

      return false;

   }


   ::user::interaction * element::get_child_by_name(const ::string & strName, ::collection::index iItem, int iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * element::get_child_by_id(const atom & atom, ::collection::index iItem, int iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::element * element::get_primitive_by_id(const atom & atom, ::collection::index iItem, int iLevel)
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


   lresult element::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point & point)
   {

      return message_call(emessage, wparam, lparam, point);

   }


   lresult element::send_message(::message::message * pmessage)
   {

      return message_call(pmessage);

   }


   lresult element::message_call(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point & point)
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


   //bool element::ModifyStyle(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::ModifyStyleEx(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags)
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


   //::user::frame_interaction * element::top_level_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void element::send_message_to_descendants(::enum_message emessage, ::wparam wparam, ::lparam lparam, bool bDeep, bool bOnlyPerm)
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




   enum_control_type element::get_control_type()
   {

      return e_control_type_none;

   }


   //bool element::create_interaction(::user::interaction * puiParent, ::request * prequest, unsigned int uExStyle, unsigned int uStyle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void element::on_before_create_window(::acme::windowing::window * pwindowbase)
   {


   }


   void element::on_create_window()
   {



   }



   ////bool element::create_window_ex(::pointer<::user::system>pcs, ::user::interaction * puiParent, const ::atom & atom)
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


   ::user::interaction * element::next_sibling(::user::interaction * pinteraction)
   {

      return nullptr;

   }


   ::user::interaction * element::previous_sibling(::user::interaction * pinteraction)
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


   ::user::interaction * element::above_sibling(::user::interaction * pinteraction)
   {

      return nullptr;

   }


   ::user::interaction * element::under_sibling(::user::interaction * pinteraction)
   {

      return nullptr;

   }



   //int element::get_window_long(int nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //int element::set_window_long(int nIndex,int lValue)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //iptr element::get_window_long_ptr(int nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //void element::set_window_long_ptr(int nIndex, iptr lValue)
   //{

   //   throw ::interface_only();

   //   throw ::interface_only();

   //}


   //bool element::RedrawWindow(const ::int_rectangle& rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   ::user::interaction * element::ChildWindowFromPoint(const ::int_point & point)
   {

      throw ::interface_only();

   }


   ::user::interaction * element::ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags)
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


   ::user::interaction * element::get_wnd(unsigned int nCmd)
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


   //bool element::XXXSetFocus()
   //{

   //   ::pointer<::user::interaction>pinteraction = get_wnd();

   //   if(pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   return get_wnd()->XXXSetFocus();

   //}


   //interaction * element::set_active_window()
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


   void element::set_rectangle(const ::int_rectangle & rectangle)
   {

   }



   void element::set_position(const ::int_point & point)
   {


   }


   void element::set_size(const ::int_size & size)
   {


   }


   void element::set_interaction_rectangle(const ::int_rectangle & rectangle)
   {


   }


   ::int_rectangle element::get_rectangle()
   {

      return acme_user_interaction()->get_rectangle();

   }


   ::int_rectangle element::get_window_rectangle()
   {

      return acme_windowing_window()->get_window_rectangle();

   }


   void element::redraw()
   {


   }


   // void element::set_mouse_capture()
   // {


   // }



   void element::edit_on_set_focus(::user::interaction * pinteraction)
   {


   }


   void element::edit_on_kill_focus(::user::interaction * pinteraction)
   {

   }


   void element::set_window_text(const ::string & pszString)
   {

   }


   void element::set_window_text_source(const ::a_string_function & astringfunction)
   {

   }


   character_count element::get_window_text(char * pszStringBuf, character_count nMaxCount)

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


   character_count element::get_window_text_length()
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


   //::user::frame_interaction * element::GetParentTopLevelFrame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_interaction * element::EnsureParentFrame()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //lresult element::default_window_procedure()
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //unsigned int element::GetStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //unsigned int element::GetExStyle() const
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


   //::user::frame_interaction * element::get_parent_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void element::CalcWindowRect(::int_rectangle * prectangle,unsigned int nAdjustType)

   //{

   //   throw ::interface_only();

   //}


   void element::RepositionBars(unsigned int nIDFirst, unsigned int nIDLast, ::atom idLeftOver, unsigned int nFlag, ::int_rectangle * prectParam, const ::int_rectangle & rectangleX, bool bStretch)
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


   /*::user::frame_interaction * element::get_owner_frame() const
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


   //::user::frame_interaction * element::frame() const
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


   void element::viewport_client_to_screen(::sequence2_int & sequence)
   {

      throw ::interface_only();

   }


   void element::viewport_screen_to_client(::sequence2_int & sequence)
   {

      throw ::interface_only();

   }


   void element::viewport_client_to_screen(::int_rectangle & rectangle)
   {

      throw ::interface_only();

   }


   void element::viewport_screen_to_client(::int_rectangle & rectangle)
   {

      throw ::interface_only();

   }


   //int element::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //int element::GetWindowRgn(HRGN hRgn)
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


   //void element::SetRedraw(bool bRedraw)
   //{

   //   throw ::interface_only();

   //}


   //bool element::GetUpdateRect(::int_rectangle * prectangle, bool bErase)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //int element::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //void element::InvalidateRect(const ::int_rectangle & rectangle,bool bErase)

   //{

   //   throw ::interface_only();

   //}


   //void element::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //}


   //void element::ValidateRect(const ::int_rectangle & rectangle)

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


   //atom element::run_modal_loop(::user::interaction * pinteraction, unsigned int dwFlags)
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom element::RunModalLoop(unsigned int dwFlags)
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom element::_001RunModalLoop(unsigned int dwFlags)
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


   lresult element::message_handler(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      throw ::interface_only();

      return {};

   }


   void element::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      throw ::interface_only();

   }


   //void element::SetTimer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pdata)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //void element::KillTimer(uptr uEvent)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //bool element::has_keyboard_focus() const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool element::set_mouse_capture(::user::interaction * pinteraction)
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


   //void element::design_window_full_screen(const ::int_rectangle & rectangleHint)
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


   void element::OnLinkClick(const ::string & psz, const ::string & pszTarget)
   {

      throw ::interface_only();

   }


   //void element::set_config_per_second(::frequency dConfigFps)
   //{

   //   //get_host_user_interaction()->m_pimpl->set_config_per_second(dConfigFps);

   //}


   //::frequency element::get_config_per_second()
   //{

   //   //return get_host_user_interaction()->m_pimpl->get_config_per_second();

   //}


   //::frequency element::get_output_per_second()
   //{

   //   //auto pinteraction = get_host_user_interaction();

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


   ::acme::user::interaction * element::acme_user_interaction()
   {

      return nullptr;

   }


   ::acme::windowing::window * element::acme_windowing_window()
   {

      return nullptr;

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

   //::user::interaction_base * element::user_prototype()
   //{

   //   return nullptr;

   //}


   //::user::interaction * element::user_interaction()
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


   double element::_001GetTopLeftWeightedOccludedOpaqueRate()
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

   //::int_point element::get_cursor_position() const
   //{

   //   return ::int_point();

   //}


   //::double_size element::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   return { 0.0, 0.0 };

   //}


   //::double_size element::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::double_rectangle rectanglePadding(2.0, 2.0, 2.0, 2.0);

   //   auto sizeFitting = _001CalculateFittingSize(pgraphics);

   //   ::double_size sizePaddedFitting;

   //   sizePaddedFitting.cx() = rectanglePadding.left() + sizeFitting.cx() + rectanglePadding.right();

   //   sizePaddedFitting.cy() = rectanglePadding.top() + sizeFitting.cy() + rectanglePadding.bottom();

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


   //void element::on_set_keyboard_focus()
   //{

   //}


   //void element::on_kill_keyboard_focus()
   //{

   //}


   bool element::GetFocusRect(::int_rectangle & rectangle)
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


   void element::_on_window_simple_action(const char * pszActionName, ::user::activation_token * puseractivationtoken)
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


   bool element::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      return false;

   }


   void element::defer_update_display()
   {


   }


   //::user::element * element::get_keyboard_focus()
   //{

   //   auto puserinteractionHost = get_host_user_interaction();

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


   int element::get_descendant_level(::user::element * pinteraction)
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


   unsigned int element::get_window_default_style()
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


   //bool element::set_window_position(class zorder zorder, int x, int y, int cx, int cy, unsigned int nFlags)
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

      //void element::on_timer(::timer * ptimer)
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

      post_message(e_message_simple_command, (wparam)ecommand, lparam);

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
//      auto eprototype = ::message::get_message_prototype((enum_message) atom.long_long, 0);
//
//      switch (eprototype)
//      {
//      case ::message::PrototypeNone:
//      {
//
//         pmessage = __allocate ::user::message();
//
//      }
//      break;
//      case ::message::PrototypeCreate:
//      {
//         pmessage = __allocate ::message::create();
//      }
//      break;
//      case ::message::PrototypeEnable:
//      {
//         pmessage = __allocate ::message::enable();
//      }
//      break;
//      case ::message::PrototypeNcActivate:
//      {
//         pmessage = __allocate ::message::nc_activate();
//      }
//      break;
//      case ::message::PrototypeKey:
//      {
//         pmessage = __allocate ::message::key();
//      }
//      break;
//      case ::message::PrototypeTimer:
//      {
//         
//         //throw ::exception(::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));
//         
//         pmessage = __allocate ::message::timer();
//
//      }
//      break;
//      case ::message::PrototypeShowWindow:
//      {
//         pmessage = __allocate ::message::show_window();
//      }
//      break;
//      case ::message::PrototypeSetCursor:
//      {
//         pmessage = __allocate ::message::set_cursor();
//      }
//      break;
//      case ::message::PrototypeNcHitTest:
//      {
//         pmessage = __allocate ::message::nc_hit_test();
//      }
//      break;
//      case ::message::PrototypeMove:
//      {
//         pmessage = __allocate ::message::transfer();
//      }
//      break;
//      case ::message::PrototypeEraseBkgnd:
//      {
//         pmessage = __allocate ::message::erase_bkgnd();
//      }
//      break;
//      case ::message::PrototypeScroll:
//      {
//         pmessage = __allocate ::message::scroll();
//      }
//      break;
//      case ::message::PrototypeSetFocus:
//      {
//         pmessage = __allocate ::message::set_keyboard_focus();
//      }
//      break;
//      case ::message::PrototypeKillFocus:
//      {
//         pmessage = __allocate ::message::kill_keyboard_focus();
//      }
//      break;
//#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//      case ::message::PrototypeWindowPos:
//      {
//         pmessage = __allocate ::message::window_pos();
//      }
//      break;
//      case ::message::PrototypeNcCalcSize:
//      {
//         pmessage = __allocate ::message::nc_calc_size();
//      }
//      break;
//#endif
//      case ::message::PrototypeMouse:
//      {
//         pmessage = __allocate ::message::mouse();
//      }
//      break;
//      case ::message::PrototypeMouseWheel:
//      {
//         pmessage = __allocate ::message::mouse_wheel();
//      }
//      break;
//      case ::message::PrototypeSize:
//      {
//         pmessage = __allocate ::message::size();
//      }
//      break;
//      case ::message::PrototypeActivate:
//      {
//         pmessage = __allocate ::message::activate();
//      }
//      break;
//      case ::message::PrototypeMouseActivate:
//      {
//         pmessage = __allocate ::message::mouse_activate();
//      }
//      break;
//      case ::message::PrototypeSimpleCommand:
//      {
//         pmessage = __allocate ::message::simple_command();
//      }
//      break;
//      default:
//      {
//         pmessage = __allocate ::message::message();
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
//      pmessage->set(get_oswindow(), get_window(), emessage, wparam, lparam);
//
//      return pmessage;
//
//   }


   // bool element::call_message_handler(const ::atom & atom, const ::wparam & wparam, const ::lparam & lparam, const ::int_point & point, lresult * plresult)
   // {

   //    //auto pmessage = get_message(emessage, wparam, lparam);

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


//   bool element::SetPlacement(const ::int_rectangle & rectangle, unsigned int nFlags)
//   {
//
//      __UNREFERENCED_PARAMETER(rectangle);
//      __UNREFERENCED_PARAMETER(nFlags);
//
//      return false;
//
//   }


   int element::get_total_page_count(::context * pcontext)
   {

      return 1;

   }



   //void element::on_timer(::timer * ptimer)
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



   void element::keyboard_focus_OnTimer(int iTimer)
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


   //void element::handle_event(control_event * phappening)
   //{

   //   __UNREFERENCED_PARAMETER(phappening);

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

         throw ::exception(error_wrong_state, "element should be at least a acme::user::interaction to get focus");

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

   //   ::cast < ::acme::user::interaction > pacmeuserinteractionFocus = this;

   //   if (::is_null(pacmeuserinteractionFocus))
   //   {

   //      throw ::exception(error_wrong_state, "element should be at least a acme::user::interaction to get focus (and then to loose it)");

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


   ::user::primitive_impl * element::get_primitive_impl()
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



   void element::on_timer(::timer * ptimer)
   {

      __UNREFERENCED_PARAMETER(ptimer);

   }


   void element::on_reset_focus_start_tick()
   {

   }


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



   void element::set_need_redraw(
      const ::int_rectangle_array & rectangleaNeedRedraw,
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


   void element::hide()
   {

      //return false;

   }



   void element::edit_on_text(string str)
   {

   }


   void element::edit_on_sel(character_count iBeg, character_count iEnd)
   {

   }


   void element::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context)
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


   void element::set_input_content_rect(const int_rectangle & rectangle)
   {

   }


   void element::set_input_selection_rect(const int_rectangle & rectangle)
   {

   }


   int_rectangle element::get_input_content_rect()
   {

      return int_rectangle();

   }


   int_rectangle element::get_input_selection_rect()
   {

      return int_rectangle();

   }


   bool element::InputConnectionBeginBatchEdit(bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionEndBatchEdit(bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionCommitText(const ::string & str, character_count iNewCursorPosition, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionDeleteSurroundingText(character_count iBeforeLength, character_count iAfterLength, bool bSuper)
   {

      return bSuper;

   }


   bool element::InputConnectionSetComposingText(const ::string & str, character_count iNewCursorPosition, bool bSuper)
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

      //return true;

   }



   void element::pick_single_file(const ::array < ::file::file_dialog_filter > & filedialogfiltera, const ::function < void(const ::file::path &) > & function, bool bSave)
   {

      auto pfiledialog = node()->node_file_dialog();

      pfiledialog->m_bSave = bSave;

      pfiledialog->m_filedialogfiltera = filedialogfiltera;

      pfiledialog->m_function = [function](auto pdialog)
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

      pfiledialog->call();

   }


   void element::pick_multiple_file(const ::array < ::file::file_dialog_filter > & filedialogfiltera, const ::function < void(const ::file::path_array &) > & function)
   {

      auto pfiledialog = node()->node_file_dialog();

      pfiledialog->m_function = [function](auto pdialog)
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

      pfiledialog->call();

   }


   void element::pick_single_folder(const ::function < void(const ::file::path &) > & function)
   {

      auto pfiledialog = node()->node_file_dialog();

      pfiledialog->m_function = [function](auto pdialog)
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

      ::string strType = ::type(this).name();

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

   

} // namespace user



