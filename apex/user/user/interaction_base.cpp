#include "framework.h"
#include "interaction_base.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/single_lock.h"
#include "apex/message/simple_command.h"
#include "apex/platform/application.h"
#include "apex/platform/session.h"


namespace user
{


   interaction_base::interaction_base()
   {

   }


   interaction_base::~interaction_base()
   {

   }


   //::handler* interaction_base::get_user_callback()
   //{

   //   return nullptr;

   //}


   void interaction_base::install_message_routing(::channel * pchannel)
   {

      channel::install_message_routing(pchannel);

   }


   void interaction_base::show_software_keyboard(::user::element * pelement)
   {

      throw ::interface_only();

   }


   void interaction_base::hide_software_keyboard(::user::element * pelement)
   {

      throw ::interface_only();


   }


   //void interaction_base::TwfGetWndArray(::user::interaction_pointer_array & wndpa)
   //{

   //   wndpa = *dynamic_cast < ::user::interaction_pointer_array * >(this);

   //}


//   void interaction_base::TwfGetWndArray(::user::oswindow_array & oswindowa)
//   {
//
//      ::user::interaction_pointer_array & wndpa = *dynamic_cast < ::user::interaction_pointer_array * >(this);
//
//      oswindowa = wndpa.get_hwnda();
//
//   }
//
//
//   void interaction_base::RedrawOptimize(rectangle_i32_array &array)
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
//   bool interaction_base::RedrawOptimize(::rectangle_i32 * prectOut, const rectangle_i32 & rect1Param, const rectangle_i32 & rect2Param)
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


   void interaction_base::PreSubClassWindow()
   {

      //_001BaseWndInterfaceMap();

   }




   //void interaction_base::_001BaseWndInterfaceMap()
   //{

   //}


   ::user::interaction * interaction_base::get_wnd()
   {

      return nullptr;

   }


   ::task * interaction_base::get_task()
   {

      return nullptr;

      //auto puserinteraction = get_wnd();

      //if (::is_null(puserinteraction))
      //{

      //   return get_app();

      //}

      //return puserinteraction->m_pthreadUserInteraction;

   }



   //::windowing::window * interaction_base::get_impl() const
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


   //bool interaction_base::is_window_enabled() const
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


   //bool interaction_base::is_this_enabled() const
   //{

   //   return true;

   //}


   ::user::interaction* interaction_base::get_host_user_interaction()
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


   ::user::form * interaction_base::get_form()
   {

      return nullptr;

   }


   ::user::form * interaction_base::get_parent_form()
   {

      return nullptr;

   }


   void interaction_base::enable_window(bool bEnable)
   {

      __UNREFERENCED_PARAMETER(bEnable);

      //return false;

   }


   //void interaction_base::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


   //void interaction_base::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   _001OnDraw(pgraphics);
   //   _008OnDraw(pgraphics);

   //}


   //void interaction_base::UpdateWindow()
   //{

   //   //ASSERT(::IsWindow(GetHandle()));
   //   //::UpdateWindow(GetHandle());

   //}


   //void interaction_base::Invalidate(bool bErase)
   //{

   //   __UNREFERENCED_PARAMETER(bErase);

   //   //ASSERT(::IsWindow(GetHandle()));
   //   //::InvalidateRect(GetHandle(), nullptr, bErase);

   //}

   bool interaction_base::has_pending_redraw_flags()
   {

      return false;

   }


   //bool interaction_base::Redraw(rectangle_i32_array & recta)
   //{

   //   bool bOk = true;

   //   for(i32 i = 0; i < recta.get_size(); i++)
   //   {

   //      if(!get_wnd()->RedrawWindow(recta[i]))
   //         bOk = false;

   //   }

   //   return bOk;

   //}


   //bool interaction_base::Redraw(const ::rectangle_i32 & rectangle, ::draw2d::region * prgn)
   //{

   //   if (get_wnd() == nullptr)
   //   {

   //      return false;

   //   }

   //   return get_wnd()->RedrawWindow(rectangle, prgn, RDW_INVALIDATE);

   //}


   //bool interaction_base::Redraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   __UNREFERENCED_PARAMETER(pgraphics);

   //   if(get_wnd() == nullptr)
   //      return false;

   //   return get_wnd()->RedrawWindow();

   //}


   /*bool interaction_base::client_to_screen(::rectangle_i32 * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }


   bool interaction_base::client_to_screen(::rectangle_f64 * prectangle)
   {

      ::offset_rect(prectangle, client_screen_top_left());

      return true;

   }
*/

   //bool interaction_base::client_to_screen(::point_i32 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::client_to_screen(::point_f64 * ppoint)
   //{

   //   ::offset(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::client_to_screen(::rectangle_i64 * prectangle)
   //{

   //   ::offset_rect(prectangle, point_i64(client_screen_top_left()));

   //   return true;

   //}


   //bool interaction_base::client_to_screen(::point_i64 * ppoint)
   //{

   //   ::offset_point(ppoint, client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::screen_to_client(::rectangle_i32 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::screen_to_client(::rectangle_f64 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::screen_to_client(::point_i32 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::screen_to_client(::point_f64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::screen_to_client(::rectangle_i64 * prectangle)
   //{

   //   ::offset_rect(prectangle, -client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::screen_to_client(::point_i64 * ppoint)
   //{

   //   ::offset_point(ppoint, -client_screen_top_left());

   //   return true;

   //}


   //bool interaction_base::GetWindowPos(::rectangle_i32 * prectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::window_rectangle(::rectangle_i32 * prectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //point_f64 interaction_base::client_screen_top_left()
   //{

   //   return nullptr;

   //}


   //bool interaction_base::this->rectangle(::rectangle_i32 * prectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::this->rectangle(::rectangle_i64 * prectangle)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::window_rectangle(::rectangle_i64 * prectangle)

   //{

   //   throw ::interface_only();

   //   return false;

   //}












/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





































   bool interaction_base::is_ascendant(::user::element * puiIsAscendant, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::is_parent(::user::element * puiIsParent)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::is_child(::user::element * puiIsChild)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::is_descendant(::user::element * puiIsDescendant, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::is_descendant_of_or_owned_by(::user::element * puiAscendantCandidate, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::is_ascendant_or_owner_of(::user::element * puiDescendantCandidate, bool bIncludeSelf)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::is_ascendant_of(::user::element * puiIsDescendant, bool bIncludeSelf)
   {
      
      return ::is_set(puiIsDescendant) && puiIsDescendant->is_ascendant(this, bIncludeSelf); 
   
   }


   bool interaction_base::is_parent_of(::user::element * puiIsChild)
   {
      
      return ::is_set(puiIsChild) && puiIsChild->is_parent(this); 
   
   }


   bool interaction_base::is_child_of(::user::element * puiIsParent)
   {
      
      return ::is_set(puiIsParent) && puiIsParent->is_child(this); 
   
   }

   
   bool interaction_base::is_descendant_of(::user::element * puiIsAscendant, bool bIncludeSelf)
   { 
      
      return ::is_set(puiIsAscendant) && puiIsAscendant->is_descendant(this, bIncludeSelf); 
   
   }


   void interaction_base::_008GetWindowText(::message::message * pmessage)
   {

   }


   void interaction_base::_008GetWindowTextLength(::message::message * pmessage)
   {

   }


//#ifdef WINDOWS
//   strsize interaction_base::_009GetWindowText(wchar_t * pwsz, int n)
//#else
//   strsize interaction_base::_009GetWindowText(char * psz, int n)
//#endif
//   {
//
//      return -1;
//
//   }
//
//
//   strsize interaction_base::_009GetWindowTextLength()
//   {
//
//      return -1;
//
//   }



   //bool interaction_base::SetPlacement(const ::rectangle_i32 & rectangle,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_base::add_fps_interest(::particle * pparticle)
   //{

   //   //return false;

   //}


   //void interaction_base::erase_fps_interest(::particle * pparticle)
   //{

   //   //return false;

   //}


   //bool interaction_base::is_fps_interest(const ::particle * pparticle) const
   //{

   //   return false;

   //}


   string interaction_base::get_title()
   {

      return get_window_text();

   }


   //i32 interaction_base::sync_message_box(::payload payload)
   //{

   //   if (payload.get_type() == e_type_string)
   //   {

   //      payload["message"] = payload;

   //   }

   //   payload["parent"] = this;
   //   payload["title"] = get_title();

   //   return message_box(payload);

   //}


   //i32 interaction_base::sync_message_box_timeout(const ::string & pszMessage, ::time timeTimeOut, ::u32 fuStyle)
   //{

   //   return papp->sync_message_box_timeout(this, pszMessage, get_title(), timeTimeOut, fuStyle);

   //}


   //void interaction_base::message_box(const ::payload& varParam)
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


   //void interaction_base::message_box_timeout(string strMessage, ::time timeTimeout, ::u32 fuStyle)
   //{

   //   fork([=]()
   //      {

   //         sync_message_box_timeout(strMessage, timeTimeout, fuStyle);

   //      });

   //}
   //bool interaction_base::place(const ::rectangle_i32 & rectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::RepositionWindow(i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::MoveWindow(i32 x,i32 y,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::move_to(const ::point_i32 & point)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::SizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::set_size(const size_i32 & sz)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::ResizeWindow(i32 cx,i32 cy,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::ResizeWindow(const size_i32 & sz,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::set_window_position(class zorder zorder, const ::rectangle_i32 & rectangle, ::u32 nFlags)

   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //bool interaction_base::defer_set_window_pos(iptr z, const  const rectangle_i32 & & rectangle, ::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of rectangle_i32(x, y, cx, cy)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::defer_set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags) // only set_windows_pos if get_parent()->screen_to_client(window_rectangle) different of rectangle_i32(x, y, cx, cy)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_base::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::_001PrintBuffer(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::_001Print(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   ::user::interaction * interaction_base::_001FromPoint(::point_i32 point,bool bTestedIfParentVisible)
   {

      throw ::interface_only();

      return nullptr;

   }


   bool interaction_base::_001IsPointInside(const ::point_i32 & point)
   {

      return false;

   }


   ::user::interaction * interaction_base::get_child_by_name(const ::string & strName, ::collection::index iItem, i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::get_child_by_id(const atom & atom, ::collection::index iItem, i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::element* interaction_base::get_primitive_by_id(const atom & atom, ::collection::index iItem, i32 iLevel)
   {

      throw ::interface_only();

      return nullptr;

   }


   void interaction_base::host_post(const ::procedure & procedure)
   {

      throw ::interface_only();

   }


   lresult interaction_base::send_message(::message::message * pmessage)
   {

      on_message(pmessage);

      return pmessage->m_lresult;

   }


   // pmessage object should be allocated with ___new in
   // base or derived object and will be delete after
   // handling
   void interaction_base::post_message(::message::message * pmessage)
   {

      throw ::interface_only();

      //return false;

   }


   lresult interaction_base::send_message(const ::atom & atom,wparam wparam,lparam lparam, const ::point_i32& point)
   {

      return message_call(atom, wparam, lparam, point);

   }


//   lresult interaction_base::send_message(::message::message * pmessage)
//   {
//
//      return message_call(pmessage);
//
//   }


   lresult interaction_base::message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      return 0;

   }


   lresult interaction_base::message_call(::message::message * pmessage)
   {

      return 0;

   }


   void interaction_base::on_message(::message::message * pmessage)
   {
   
   
   }


#ifdef LINUX


   lresult interaction_base::send_x11_event(void * pevent)
   {

      throw ::interface_only();

      return 0;

   }


#endif


   //bool interaction_base::_is_window_visible()
   //{

   //   return false;

   //}


   //bool interaction_base::is_this_visible()
   //{

   //   return (GetStyle() & WS_VISIBLE) != 0 && m_bUserElementOk;

   //}


   //bool interaction_base::ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::display(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   // void interaction_base::SetWindowDisplayChanged()
   // {


   // }


   //::user::frame_interaction * interaction_base::top_level_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void interaction_base::send_message_to_descendants(const ::atom & atom,wparam wparam,lparam lparam,bool bDeep,bool bOnlyPerm)

   {

      throw ::interface_only();

   }

   void interaction_base::route_message_to_descendants(::message::message * pmessage)
   {

      throw ::interface_only();

   }

   void interaction_base::pre_translate_message(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   ::windowing::window * interaction_base::window()
   {

      return nullptr;

   }


   string interaction_base::get_class_name()
   {

      return "";

   }


   void interaction_base::subclass_window(oswindow posdata)
   {

      throw ::interface_only();

      //return false;

   }


   oswindow interaction_base::unsubclass_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_base::create_child(::user::interaction * puserinteractionParent)
   //{

   //   throw ::interface_only();

   //   //return ::success;

   //}

   //
   //void interaction_base::create_control(::user::interaction * puserinteractionParent, const ::atom & atom)
   //{

   //   m_atom = atom;

   //   //auto estatus =
   //   
   //   create_child(puserinteractionParent);

   //   //if(!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}


   enum_control_type interaction_base::get_control_type()
   {

      return e_control_type_none;

   }


   //bool interaction_base::create_interaction(::user::interaction * puiParent, ::request * prequest, ::u32 uExStyle, ::u32 uStyle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_base::create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom)
   //{

   //   if (!atom.is_empty())
   //   {

   //      m_atom = atom;

   //   }

   //   //::e_status estatus;

   //   if (!puserinteractionParent)
   //   {

   //      //estatus =
   //      //create_host(e_parallelization_synchronous);
   //      create_host();

   //   }
   //   else
   //   {

   //      //estatus = 
   //      create_child(puserinteractionParent);

   //   }

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}


   ////bool interaction_base::create_window_ex(::pointer<::user::system>pcs, ::user::interaction * puiParent, const ::atom & atom)
   ////void interaction_base::create_host(enum_parallelization eparallelization)
   //void interaction_base::create_host()
   //{

   //   throw ::interface_only();

   //   //return ::error_no_interface;

   //}


   //void interaction_base::BringToTop(::e_display edisplay)
   //{

   //}


   //bool interaction_base::BringWindowToTop()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool interaction_base::_is_window() const
   {

      return m_bUserElementOk;

   }


   ::user::interaction* interaction_base::first_child()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::last_child()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::last_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::next_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::previous_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::first_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::next_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::previous_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }

   
   ::user::interaction* interaction_base::bottom_child()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::top_child()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::bottom_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::under_sibling()
   {

      return nullptr;

   }



   ::user::interaction* interaction_base::above_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::top_sibling()
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::above_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }


   ::user::interaction* interaction_base::under_sibling(::user::interaction* pinteraction)
   {

      return nullptr;

   }



   //::i32 interaction_base::get_window_long(i32 nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //::i32 interaction_base::set_window_long(i32 nIndex,::i32 lValue)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //iptr interaction_base::get_window_long_ptr(i32 nIndex) const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_base::set_window_long_ptr(i32 nIndex, iptr lValue)
   //{

   //   throw ::interface_only();

   //   throw ::interface_only();

   //}


   //bool interaction_base::RedrawWindow(const ::rectangle_i32& rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   ::user::interaction * interaction_base::ChildWindowFromPoint(const ::point_i32 & point)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::get_next_window(bool bIgnoreChildren, ::user::interaction * puiInteractionStop)
   {

      return nullptr;

   }

   
   ::user::interaction * interaction_base::get_window(enum_next enext)
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


//   ::user::interaction * interaction_base::get_next_window(bool bIgnoreChildren)
//   {
//
//      throw ::interface_only();
//
//      return nullptr;
//
//   }


   bool interaction_base::is_message_only_window()
   {

      throw ::interface_only();

      return false;

   }


   ::user::interaction * interaction_base::get_wnd(::u32 nCmd)
   {

      throw ::interface_only();

      return nullptr;

   }


   //bool interaction_base::is_active() const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * interaction_base::GetActiveWindow()
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if(pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetActiveWindow();

   //}


   //bool interaction_base::XXXSetFocus()
   //{

   //   ::pointer<::user::interaction>pinteraction = get_wnd();

   //   if(pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   return get_wnd()->XXXSetFocus();

   //}


   //interaction * interaction_base::set_active_window()
   //{

   //   //throw ::interface_only();

   //   return nullptr;

   //}


   //bool interaction_base::XXXSetForegroundWindow()
   //{

   //   return true;

   //}


   ::user::interaction * interaction_base::GetLastActivePopup()
   {

      throw ::interface_only();

      return nullptr;

   }


   void interaction_base::edit_on_set_focus(::user::interaction* pinteraction)
   {

   }


   void interaction_base::edit_on_kill_focus(::user::interaction* pinteraction)
   {

   }


   void interaction_base::set_window_text(const ::string & pszString)
   {

   }


   void interaction_base::set_window_text_source(const ::a_string_function & astringfunction)
   {

   }


   strsize interaction_base::get_window_text(char * pszStringBuf, strsize nMaxCount)

   {

      throw ::interface_only();

      return 0;

   }


   string interaction_base::get_window_text()
   {

      throw ::interface_only();

      return "";

   }


   void interaction_base::get_window_text(string & rString)
   {

      throw ::interface_only();

   }


   strsize interaction_base::get_window_text_length()
   {

      throw ::interface_only();

      return 0;

   }


   //::user::interaction * interaction_base::EnsureTopLevel()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_base::EnsureParentTopLevel()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_base::GetParentTopLevel() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_interaction * interaction_base::GetParentTopLevelFrame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_interaction * interaction_base::EnsureParentFrame()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //lresult interaction_base::default_window_procedure()
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //u32 interaction_base::GetStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //u32 interaction_base::GetExStyle() const
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_base::start_destroying_window()
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   void interaction_base::destroy_window()
   {

   }


   //void interaction_base::post_non_client_destroy()
   //{

   //   destroy();

   //}


   ::user::interaction * interaction_base::get_parent()
   {

      throw ::interface_only();

      return nullptr;

   }


   //::user::frame_interaction * interaction_base::get_parent_frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void interaction_base::CalcWindowRect(::rectangle_i32 * prectangle,::u32 nAdjustType)

   //{

   //   throw ::interface_only();

   //}


   void interaction_base::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeftOver, ::u32 nFlag, ::rectangle_i32 * prectParam, const ::rectangle_i32 & rectangleX, bool bStretch)
   {

      throw ::interface_only();

   }


   ::user::interaction_base * interaction_base::set_owner(::user::interaction_base * pinteraction)
   {

      //throw ::interface_only();

      return nullptr;

   }


   ::user::interaction_base * interaction_base::set_parent(::user::interaction_base * pinteraction)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::get_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   /*::user::frame_interaction * interaction_base::get_owner_frame() const
   {

      throw ::interface_only();

      return nullptr;

   }*/


   bool interaction_base::is_top_level_window()
   {

     auto puiParent = get_parent_primitive();

     if (::is_null(puiParent))
     {

        return true;

     }

     if (::is_set(session()))
     {

        if (this == session()->m_puserprimitiveHost)
        {

           return true;

        }
        else if (puiParent == session()->m_puserprimitiveHost)
        {

           return true;

        }

     }

     return false;

   }


   //interaction * interaction_base::get_parent() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::frame_interaction * interaction_base::frame() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   ::user::interaction * interaction_base::get_parent_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::get_parent_or_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::get_top_level_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_base::_top_level()
   {

      throw ::interface_only();

      return nullptr;

   }


   void interaction_base::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      throw ::interface_only();

   }


   void interaction_base::viewport_client_to_screen(::sequence2_i32 & sequence)
   {

      throw ::interface_only();

   }


   void interaction_base::viewport_screen_to_client(::sequence2_i32 & sequence)
   {

      throw ::interface_only();

   }


   void interaction_base::viewport_client_to_screen(::rectangle_i32 & rectangle)
   {

      throw ::interface_only();
    
   }


   void interaction_base::viewport_screen_to_client(::rectangle_i32 & rectangle)
   {

      throw ::interface_only();

   }


   //i32 interaction_base::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //i32 interaction_base::GetWindowRgn(HRGN hRgn)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //bool interaction_base::layout().is_zoomed()
   //{

   //   return false;

   //}


   //bool interaction_base::layout().is_full_screen()
   //{

   //   return false;

   //}


   //bool interaction_base::layout().is_iconic()
   //{

   //   return false;

   //}


   //void interaction_base::CheckAutoCenter()
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   void interaction_base::CenterWindow(::user::interaction * pAlternateOwner)
   {

      throw ::interface_only();

   }


   void interaction_base::default_message_handler(::message::message * pmessage)
   {


   }


   void interaction_base::message_handler(::message::message * pmessage)
   {

      throw ::interface_only();

      //return false;

   }


   //lresult interaction_base::message_handler(MESSAGE * pmessage)
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   bool interaction_base::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
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
//   bool interaction_base::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
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


   //bool interaction_base::pre_create_window(::user::system * pusersystem)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::IsTopParentActive()
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


   void interaction_base::ActivateTopParent()
   {

   }


   void interaction_base::update_dialog_controls(channel * ptarget)
   {

      //throw ::interface_only();

   }


   //void interaction_base::SetRedraw(bool bRedraw)
   //{

   //   throw ::interface_only();

   //}


   //bool interaction_base::GetUpdateRect(::rectangle_i32 * prectangle,bool bErase)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //i32 interaction_base::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //void interaction_base::InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase)

   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::ValidateRect(const ::rectangle_i32 & rectangle)

   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::ValidateRgn(::draw2d::region* pRgn)
   //{

   //   throw ::interface_only();

   //}


   void interaction_base::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

   }


   void interaction_base::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {

   }


   void interaction_base::on_configuration_change(::user::interaction_base * pprimitiveSource)
   {


   }


   //void interaction_base::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   void interaction_base::on_reposition()
   {

      throw ::interface_only();

   }


   bool interaction_base::is_this_visible(enum_layout elayout)
   {

      return true;

   }


   // void interaction_base::on_show_window()
   // {
   //
   //    throw ::interface_only();
   //
   // }


   //void interaction_base::window_show_change_visibility()
   //{


   //}


   //void interaction_base::ShowOwnedPopups(bool bShow)
   //{

   //   throw ::interface_only();

   //}


   //bool interaction_base::attach(oswindow oswindow)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   oswindow interaction_base::detach_window()
   {

      return nullptr;

   }


   void interaction_base::pre_subclass_window()
   {

      throw ::interface_only();

   }


   //atom interaction_base::run_modal_loop(::user::interaction * pinteraction,u32 dwFlags)
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom interaction_base::RunModalLoop(u32 dwFlags)
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom interaction_base::_001RunModalLoop(u32 dwFlags)
   //{

   //   throw ::interface_only();

   //   return atom();

   //}


   //bool interaction_base::ContinueModal()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_base::EndModalLoop(atom nResult)
   //{

   //   throw ::interface_only();

   //}


   lresult interaction_base::message_handler(const ::atom & atom, wparam wparam, lparam lparam)
   {

      throw ::interface_only();

      return {};

   }


   void interaction_base::post_message(const ::atom & atom,wparam wparam,lparam lparam)
   {

      throw ::interface_only();

   }


   //bool interaction_base::user_post(const ::atom& atom, wparam wparam, lparam lparam)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_base::SetTimer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer, bool bPeriodic, void* pdata)
   {

      throw ::interface_only();

      //return false;

   }


   void interaction_base::KillTimer(uptr uEvent)
   {

      throw ::interface_only();

      //return false;

   }


   //bool interaction_base::has_keyboard_focus() const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::set_capture(::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   //::user::interaction * interaction_base::get_capture() const
   //{

   //   return nullptr;

   //}



   //bool interaction_base::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   //::user::interaction * interaction_base::get_keyboard_focus() const
   //{

   //   return nullptr;

   //}




   void interaction_base::_000OnMouseLeave(::message::message* pmessage)
   {

   }


   void interaction_base::track_mouse_leave()
   {

      throw ::interface_only();

   }


   void interaction_base::track_mouse_hover()
   {

      throw ::interface_only();

   }


   //void interaction_base::sketch_to_layout()
   //{


   //}


   //void interaction_base::layout_to_design(bool & bUpdateBuffer, bool & bUpdateWindow)
   //{

   //}


   void interaction_base::_001UpdateWindow()
   {

   }


   // void interaction_base::window_apply_visual(const window_state & windowstate)
   // {

   // }


   void interaction_base::design_window_minimize(::e_activation eactivation)
   {

      throw ::interface_only();

   }


   void interaction_base::design_window_maximize()
   {

      throw ::interface_only();

   }


   void interaction_base::design_window_full_screen(const ::rectangle_i32 & rectangleHint)
   {

      throw ::interface_only();

   }


   void interaction_base::design_window_normal(e_display edisplay)
   {

      throw ::interface_only();

   }


   void interaction_base::design_window_dock(::e_display edisplayDock)
   {

      throw ::interface_only();

   }


   //void interaction_base::GuieProc(::message::message * pmessage)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   //void interaction_base::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   //{

   //   throw ::interface_only();

   //}


   void interaction_base::OnLinkClick(const ::string & psz,const ::string & pszTarget)
   {

      throw ::interface_only();

   }


   //void interaction_base::set_config_per_second(double dConfigFps)
   //{

   //   //get_host_user_interaction()->m_pimpl->set_config_per_second(dConfigFps);

   //}


   //::frequency interaction_base::get_config_per_second()
   //{

   //   //return get_host_user_interaction()->m_pimpl->get_config_per_second();

   //}


   //::frequency interaction_base::get_output_per_second()
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


   void interaction_base::create_message_queue(const ::string & lpszName)
   {

      throw ::interface_only();

      //return false;

   }


   void interaction_base::on_select()
   {

      throw ::interface_only();

   }


   bool interaction_base::is_place_holder()
   {

      throw ::interface_only();

      return false;

   }


   double interaction_base::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      return 0.0;

   }


   ::windowing::cursor * interaction_base::get_mouse_cursor()
   {

      throw ::interface_only();

      return nullptr;

   }


   void interaction_base::set_default_mouse_cursor(::windowing::cursor * pcursor)
   {

      //return success_none;

   }


   //void interaction_base::set_cursor(::windowing::/*cursor * pcursor)
   //{

   //   throw ::interface_only();

   //   return false;

   //}

   //::point_i32 interaction_base::get_cursor_position() const
   //{

   //   return ::point_i32();

   //}

   
   //::size_f64 interaction_base::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   return { 0.0, 0.0 };

   //}


   //::size_f64 interaction_base::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::rectangle_f64 rectanglePadding(2.0, 2.0, 2.0, 2.0);

   //   auto sizeFitting = _001CalculateFittingSize(pgraphics);

   //   ::size_f64 sizePaddedFitting;

   //   sizePaddedFitting.cx() = rectanglePadding.left() + sizeFitting.cx() + rectanglePadding.right();

   //   sizePaddedFitting.cy() = rectanglePadding.top() + sizeFitting.cy() + rectanglePadding.bottom();

   //   return sizePaddedFitting;

   //}


   //bool interaction_base::can_merge(::user::interaction * pinteraction)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::merge(::user::interaction * pinteraction)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * interaction_base::top_child()
   //{

   //   return last_child();

   //}


   //::user::interaction * interaction_base::bottom_child()
   //{

   //   return first_child();

   //}


   //::user::interaction * interaction_base::above_sibling(::user::interaction * pinteraction)
   //{

   //   return next_sibling(pinteraction);

   //}


   //::user::interaction * interaction_base::above_sibling()
   //{

   //   return next_sibling();

   //}


   //::user::interaction * interaction_base::under_sibling(::user::interaction * pinteraction)
   //{

   //   return previous_sibling(pinteraction);

   //}


   //::user::interaction * interaction_base::under_sibling()
   //{

   //   return previous_sibling();

   //}

   //::user::interaction * interaction_base::top_sibling()
   //{

   //   return last_sibling();

   //}


   //::user::interaction * interaction_base::bottom_sibling()
   //{

   //   return first_sibling();

   //   return nullptr;

   //}

   //::user::interaction * interaction_base::first_child()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_base::last_child()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}

   //::user::interaction * interaction_base::first_sibling()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_base::last_sibling()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_base::previous_sibling()
   //{

   //   return nullptr;

   //}

   //::user::interaction * interaction_base::previous_sibling(::user::interaction * pinteraction)
   //{

   //   __UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}

   //::user::interaction * interaction_base::next_sibling()
   //{

   //   return nullptr;

   //}

   //::user::interaction * interaction_base::next_sibling(::user::interaction * pinteraction)
   //{

   //   __UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}


   //void interaction_base::mouse_hover_add(::user::interaction * pinterface)
   //{

   //   throw ::interface_only();

   //}


   //bool interaction_base::mouse_hover_erase(::user::interaction * pinterface)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_base::_task_transparent_mouse_event()
   //{


   //}


   void interaction_base::on_set_keyboard_focus()
   {

   }


   void interaction_base::on_kill_keyboard_focus()
   {

   }


   bool interaction_base::GetFocusRect(::rectangle_i32 & rectangle)
   {

      return element::GetFocusRect(rectangle);

   }


   void interaction_base::defer_update_display()
   {


   }


   //::user::interaction_base * interaction_base::get_keyboard_focus()
   //{

   //   auto puserinteractionHost = get_host_user_interaction();

   //   if (::is_null(puserinteractionHost))
   //   {

   //      return nullptr;

   //   }

   //   ::user::interaction_base * pprimitive = puserinteractionHost->get_keyboard_focus();

   //   if(pprimitive == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return dynamic_cast < ::user::interaction * > (pprimitive);

   //}


   i32 interaction_base::get_descendant_level(::user::element * puserelement)
   {

      throw ::interface_only();

      return -1;

   }


   //bool interaction_base::is_descendant(const ::user::interaction_base * pinteraction,bool bIncludeSelf) const
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_base::set_tool_window(bool bSet)
   {

      __UNREFERENCED_PARAMETER(bSet);

      throw ::interface_only();

      //return error_not_implemented;

   }


   ::user::interaction * interaction_base::get_first_child_window()
   {

      return nullptr;

   }


   ::user::interaction * interaction_base::get_next_sibling_window()
   {

      return nullptr;

   }


   ::user::interaction * interaction_base::get_focusable_descendant()
   {

      throw ::interface_only();

      return nullptr;

   }


//   void interaction_base::_001OnTriggerMouseInside()
//   {
//
//      throw ::interface_only();
//
//   }


   void interaction_base::update_data(bool bSaveAndValidate)
   {

      throw ::interface_only();

      //return false;

   }


   string interaction_base::get_window_default_matter()
   {

      throw ::interface_only();

      return "";

   }


   string interaction_base::get_window_icon_matter()
   {

      throw ::interface_only();

      return get_window_default_matter();

   }


   u32 interaction_base::get_window_default_style()
   {

      throw ::interface_only();

      return 0;

   }


   //::user::interaction_base::enum_type interaction_base::get_window_type()
   //{

   //   return type_window;

   //}





   bool interaction_base::OnCommand(::message::message * pmessage)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::OnNotify(::message::message * pmessage)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::OnChildNotify(::message::message * pmessage)
   {

      throw ::interface_only();

      return false;

   }





   void interaction_base::on_command(::message::command * pcommand)
   {

      channel::on_command(pcommand);

   }


   bool interaction_base::is_selected(::data::item * pitem)
   {

      throw ::interface_only();

      return false;

   }


   bool interaction_base::has_command_handler(::message::command * pcommand)
   {

      throw ::interface_only();

      return false;

   }


   void interaction_base::handle(::topic * ptopic, ::context * pcontext)
   {


   }



   //bool interaction_base::_001OnExitIconic()
   //{

   //   return ::user::element::_001OnExitIconic();

   //}


   //bool interaction_base::_001OnExitFullScreen()
   //{

   //   return ::user::element::_001OnExitFullScreen();

   //}


   //bool interaction_base::_001OnExitZoomed()
   //{

   //   return ::user::element::_001OnExitZoomed();

   //}


   void interaction_base::on_add_owned(::user::interaction_base * pprimitive)
   {


   }


   //void interaction_base::window_enable_full_screen(bool bEnable)
   //{

   //   throw ::interface_only();

   //}


   //bool interaction_base::window_is_full_screen_enabled()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //edisplay interaction_base::get_display()
   //{

   //   return e_display_none;

   //}


   //edisplay interaction_base::get_previous_display()
   //{

   //   return e_display_none;

   //}


   //bool interaction_base::defer_set_appearance(::e_display edisplay)
   //{

   //   if (get_display() == edisplay)
   //   {

   //      return false;

   //   }

   //   return set_appearance(edisplay);

   //}

   //bool interaction_base::set_appearance(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //bool interaction_base::set_previous_display(::e_display edisplay)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_base::show_keyboard(bool bShow)
   //{

   //   __UNREFERENCED_PARAMETER(bShow);

   //}




   void interaction_base::keep_alive(::object * pliveobject)
   {

      throw ::interface_only();

   }


   //bool interaction_base::set_window_position(class zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   atom interaction_base::GetDlgCtrlId() const
   {

      throw ::interface_only();

      return atom();

   }


   atom interaction_base::SetDlgCtrlId(const atom & atom)
   {

      throw ::interface_only();

      return ::atom();

   }


//#ifdef WINDOWS_DESKTOP
//
//   bool interaction_base::open_clipboard()
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   bool interaction_base::close_clipboard()
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


   //oswindow interaction_base::get_safe_handle() const
   //{

   //   if(::is_null(this))
   //      return nullptr;

   //   return get_handle();

   //}


   //::graphics::graphics * interaction_base::get_window_graphics()
   //{

   //   return nullptr;

   //}


   //bool interaction_base::is_composite()
   //{

   //   return true; // optimistic response, assume always true alpha blendable

   //}


   //void interaction_base::_user_message_handler(::message::message * pmessage)
   //{
   //}

   //::message::PFN_DISPATCH_MESSAGE_HANDLER interaction_base::_calc_user_message_handler()
   //{
   //   return &::user::interaction_base::_user_message_handler;
   //}

   //void interaction_base::_001OnTimer(::timer * ptimer)
   //{



   //}


//   bool interaction_base::has_pending_graphical_update()
//   {
//
//      return false;
//
//   }


   void interaction_base::on_after_graphical_update()
   {

   }


   void interaction_base::set_bitmap_source(const string & strBitmapSource)
   {

      //auto estatus = 
      
      ::user::element::set_bitmap_source(strBitmapSource);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   
   void interaction_base::clear_bitmap_source()
   {

      //auto estatus = 
      
      ::user::element::clear_bitmap_source();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   bool interaction_base::WfiOnStartDock()
   {

      return true;

   }


   void interaction_base::WfiOnDock(e_display edisplay)
   {

   }


   void interaction_base::design_down()
   {

   }


   void interaction_base::design_up()
   {

   }


   void interaction_base::WfiOnRestore()
   {

   }


   void interaction_base::WfiOnMinimize(bool bNoActivate)
   {

   }


   void interaction_base::WfiOnMaximize()
   {

   }


   void interaction_base::WfiOnFullScreen()
   {

   }


   //void interaction_base::WfiOnExitFullScreen()
   //{

   //}


   void interaction_base::WfiOnClose()
   {

   }


   void interaction_base::WfiOnNotifyIcon()
   {

   }


   //void interaction_base::graphics_thread_post_redraw(bool bUpdateBuffer)
   //{

   //}


   void interaction_base::fps_interest_stop()
   {


   }


} // namespace user









namespace user
{


   void interaction_base::post_simple_command(const enum_simple_command & ecommand, lparam lparam)
   {

      post_message(e_message_simple_command, (wparam)ecommand, lparam);

      //return true;

   }


   ::user::interaction_base * interaction_base::user_interaction_base()
   {

      return this;

   }


   void interaction_base::add_child_handler(::particle * pparticle, const ::atom & atomChild, bool bPriority)
   {

      auto pchild = get_primitive_by_id(atomChild);

      if (::is_null(pchild))
      {

         throw ::exception(error_not_found);

      }

      //auto estatus = 
      pchild->user_interaction_base()->add_handler(pparticle, bPriority);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void interaction_base::on_simple_command(::message::simple_command * psimplecommand)
   {

      if (psimplecommand->command() == e_simple_command_full_screen)
      {

         //get_wnd()->display(e_display_full_screen);

         psimplecommand->m_bRet = true;

      }

   }


//   ::pointer<::message::message>interaction_base::get_message(const ::atom & atom, wparam wparam, lparam lparam)
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
//      pmessage->set(get_oswindow(), get_window(), atom, wparam, lparam);
//
//      return pmessage;
//
//   }


   // bool interaction_base::call_message_handler(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point, lresult * plresult)
   // {
      
   //    if(atom == e_message_post_user)
   //    {

   //       if(wparam==1)
   //       {

   //          ::pointer<::message::message>pmessage(lparam);

   //          lparam = 0;

   //          if(pmessage)
   //          {

   //             message_handler(pmessage);

   //             //if (pmessage->m_bRet)
   //             //{

   //                return true;

   //             //}

   //          }

   //       }

   //    }

   //    auto pmessage = get_message(atom, wparam, lparam);

   //    try
   //    {

   //       message_handler(pmessage);

   //       if (pmessage->m_bRet)
   //       {

   //          return true;

   //       }

   //    }
   //    catch (const ::exception & e)
   //    {

   //       handle_exception(e);

   //       //if (::get_task()->handle_exception(e))
   //       //{

   //       //   return false;

   //       //}

   //    }
   //    catch (...)
   //    {

   //    }

   //    if (!pmessage->m_bRet)
   //    {

   //       //return;
   //       return false;

   //    }

   //    if (plresult)
   //    {

   //       try
   //       {

   //          *plresult = pmessage->m_lresult;

   //       }
   //       catch (...)
   //       {

   //       }

   //    }

   //    return true;

   // }

/*
   interaction_base::interaction_base()
   {

      m_puiThis = nullptr;

   }


   interaction_base::~interaction_base()
   {


   }
*/

#ifdef WINDOWS_DESKTOP


   //bool interaction_base::GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl)

   //{

   //   __UNREFERENCED_PARAMETER(puserinteractionpl);


   //   return false;

   //}

   //bool interaction_base::SetWindowPlacement(const WINDOWPLACEMENT * pcwndpl)

   //{

   //   __UNREFERENCED_PARAMETER(pcwndpl);


   //   return false;

   //}


#endif // WINDOWS_DESKTOP


   //::form_property_set * interaction_base::get_form_property_set()
   //{

   //   auto pformpropertyset = get_typed_parent < ::form_property_set >();

   //   if (::is_set(pformpropertyset))
   //   {

   //      return pformpropertyset->get_form_property_set();

   //   }

   //   return get_app();

   //}


//   bool interaction_base::SetPlacement(const ::rectangle_i32 & rectangle, ::u32 nFlags)
//   {
//
//      __UNREFERENCED_PARAMETER(rectangle);
//      __UNREFERENCED_PARAMETER(nFlags);
//
//      return false;
//
//   }


   i32 interaction_base::get_total_page_count(::context * pcontext)
   {

      return 1;

   }



   //void interaction_base::_001OnTimer(::timer * ptimer)
   //{

   //   __UNREFERENCED_PARAMETER(ptimer);

   //}

   //void interaction_base::add_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   m_threadptra.add(pthread);

   //}


   //void interaction_base::erase_thread(::thread * pthread)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   m_threadptra.erase(pthread);

   //}

   //bool interaction_base::enable_window(bool bEnableWindow)
   //{

   //   return true;

   //}


   //// Text Edit
   //void interaction_base::get_text_selection(strsize & iBeg, strsize & iEnd)
   //{


   //}


   ::collection::index interaction_base::plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   ::collection::index interaction_base::plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x)
   {

      return -1;

   }


   ::collection::index interaction_base::plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   ::collection::index interaction_base::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   {

      return -1;

   }


   strsize interaction_base::plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn)
   {

      return -1;

   }


   strsize interaction_base::plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, i32 x)
   {

      return -1;

   }


   ::collection::index interaction_base::plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      return -1;

   }


   //void interaction_base::on_check_change()
   //{

   //   get_app()->signal(m_linkedpropertyCheck->m_atom);

   //}


   void interaction_base::keyboard_focus_OnTimer(i32 iTimer)
   {

      __UNREFERENCED_PARAMETER(iTimer);

   }


   void interaction_base::keyboard_focus_OnChar(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction_base::keyboard_focus_OnSysChar(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction_base::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

   }


   void interaction_base::keyboard_focus_OnKeyUp(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   bool interaction_base::keyboard_focus_is_focusable()
   {

      return false;

   }


   bool interaction_base::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      return true;

   }


   bool interaction_base::keyboard_focus_OnChildKillFocus()
   {

      return true;

   }


   element* interaction_base::keyboard_set_focus_next(bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

//      interaction_base * pprimitive = keyboard_get_next_focusable(nullptr, bSkipChild, bSkipSiblings, bSkipParent);
//
//      
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


   element * interaction_base::keyboard_get_next_focusable(element * pfocus, bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

     ::pointer<interaction_base>puiThis = this;

     ::pointer<interaction_base>puiFocus = pfocus != nullptr ? pfocus : this;

     element * pfocusTry;

     if (puiFocus == nullptr)
     {

        return nullptr;

     }

     if (puiThis == nullptr)
     {

        return nullptr;

     }

     single_lock(puiThis->get_app()->synchronization(), true);

     ::pointer<interaction_base>pprimitive;

     if (!bSkipChild)
     {

        pprimitive = puiThis->first_child_user_element();

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

        pprimitive = puiThis->next_user_element();

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

           pprimitive = pprimitive->next_user_element();

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

        pprimitive = puiThis->first_child_user_element();

        if (pprimitive != puiThis)
        {

           while (pprimitive != nullptr && pprimitive != puiFocus)
           {

              if (pprimitive->keyboard_focus_is_focusable())
                 return pprimitive;

              pfocusTry = pprimitive->keyboard_get_next_focusable(puiFocus, false, true, true);

              if (pfocusTry != nullptr)
                 return pfocusTry;

              pprimitive = pprimitive->next_user_element();

           }

        }

     }


     return nullptr;

   }


   element * interaction_base::get_keyboard_focus()
   {

      return nullptr;

   }


   void interaction_base::set_keyboard_focus()
   {

      throw ::interface_only();

   }


   void interaction_base::erase_keyboard_focus()
   {

      throw ::interface_only();

   }


   void interaction_base::clear_keyboard_focus(::user::element * pelementGainingFocusIfAny)
   {

      //throw ::interface_only();

   }


   // mouse focus

   void interaction_base::mouse_focus_OnLButtonUp(::message::message * pmessage)
   {
   }


   bool interaction_base::_001CanEnterScreenSaver()
   {
   
      return false;
   
   }


   ::user::element * interaction_base::first_child_user_element()
   {

      return nullptr;

   }


   ::user::element * interaction_base::top_user_element()
   {

      return nullptr;

   }


   ::user::element * interaction_base::under_user_element()
   {

      return nullptr;

   }


   ::user::element * interaction_base::above_user_element()
   {

      return nullptr;

   }


   ::user::element * interaction_base::next_user_element()
   {

      return nullptr;

   }


   ::user::element * interaction_base::previous_user_element()
   {

      return nullptr;

   }


   //::user::interaction * interaction_base::get_parent_window()
   //{

   //   return nullptr;

   //}


   ::user::element * interaction_base::get_parent_primitive()
   {

      return nullptr;

   }


   //::user::interaction_base * interaction_base::get_wnd_primitive() const
   //{

   //   return nullptr;

   //}


   void interaction_base::destroy()
   {

      ::acme::user::interaction::destroy();
      ::channel::destroy();
      ::source::destroy();
      ::manager::destroy();
           
   }


   void interaction_base::_001OnTimer(::timer * ptimer)
   {

      __UNREFERENCED_PARAMETER(ptimer);

   }


   void interaction_base::on_reset_focus_start_tick()
   {

      m_timeFocusStart.Now();

   }


   //void interaction_base::set_need_redraw(bool bAscendants)
   //{

   //   __UNREFERENCED_PARAMETER(bAscendants);

   //}


   void interaction_base::set_need_load_form_data()
   {


   }


   void interaction_base::set_need_save_form_data()
   {


   }


   void interaction_base::post_redraw(bool bAscendants)
   {

      __UNREFERENCED_PARAMETER(bAscendants);

   }


   void interaction_base::hide()
   {

      //return false;

   }



   void interaction_base::edit_on_text(string str)
   {

   }


   void interaction_base::edit_on_sel(strsize iBeg, strsize iEnd)
   {

   }


   void interaction_base::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context)
   {

   }


   void interaction_base::on_text_composition(string str)
   {

   }


   void interaction_base::on_text_commit(string str)
   {

   }


   void interaction_base::on_text_composition_done()
   {

   }


   //bool interaction_base::is_text_composition_active()
   //{

   //   return false;

   //}


   void interaction_base::set_input_content_rect(const rectangle_i32& rectangle)
   {

   }


   void interaction_base::set_input_selection_rect(const rectangle_i32& rectangle)
   {

   }


   rectangle_i32 interaction_base::get_input_content_rect()
   {

      return rectangle_i32();

   }


   rectangle_i32 interaction_base::get_input_selection_rect()
   {

      return rectangle_i32();

   }


   //void interaction_base::InputConnectionBeginBatchEdit()
   //{


   //}


   //void interaction_base::InputConnectionEndBatchEdit()
   //{


   //}


   //void interaction_base::InputConnectionCommitText(const ::string & str, strsize iNewCursorPosition)
   //{


   //}


   //void interaction_base::InputConnectionDeleteSurroundingText(strsize iBeforeLength, strsize iAfterLength)
   //{


   //}


   //void interaction_base::InputConnectionSetComposingText(const ::string & str, strsize iNewCursorPosition)
   //{


   //}


   //void interaction_base::InputConnectionSetComposingRegion(strsize iStart, strsize iEnd)
   //{

   //}


   //void interaction_base::InputConnectionSetSelection(strsize iStart, strsize iEnd)
   //{

   //}


   //void interaction_base::InputConnectionFinishComposingText()
   //{


   //}


   //void interaction_base::set_icon(::windowing::icon * picon)
   //{

   //   return false;

   //}


   void interaction_base::display(::e_display edisplay, ::e_activation eactivation)
   {

      //return true;

   }

} // namespace user



