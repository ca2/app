#include "framework.h"
#include "_ios.h"
////#include "aura/user/user/_component.h"
#include "aura/user/user.h"
#include "aura/os/ios/oswindow_data.h"

double status_bar_height();

class raw_key :
   virtual public ::object
{
public:
   raw_key() {}

   ~raw_key() {}

};

void ns_main_async(dispatch_block_t block);


strsize str_begins_common(const ::string & str1, const ::string & str2)
{

   strsize i = 0;

   for(i = 0; i < str1.length() && i < str2.length(); i++)
   {

      if(str1[i] != str2[i])
      {

         break;

      }

   }

   return i;

}

strsize str_begins_eat_common(string & str1, string & str2, string & str)
{

   strsize i = 0;

   for(i = 0; i < str1.length() && i < str2.length(); i++)
   {

      if(str1[i] != str2[i])
      {

         break;

      }

   }

   str = str1.left(i);

   str1 = str1.substr(i);

   str2 = str2.substr(i);

   return i;

}


strsize str_ends_common(const ::string & str1, const ::string & str2)
{

   strsize i = 0;

   strsize i1 = str1.length() - 1;

   strsize i2 = str2.length() - 1;

   for(; i1 >= 0 && i2 >= 0; i1--, i2--)
   {

      if(str1[i1] != str2[i2])
      {

         break;

      }

      i++;

   }

   return i;

}


strsize str_ends_eat_common(string & str1, string & str2, string & str)
{

   strsize i = 0;

   strsize i1 = str1.length() - 1;

   strsize i2 = str2.length() - 1;

   for(; i1 >= 0 && i2 >= 0; i1--, i2--)
   {

      if(str1[i1] != str2[i2])
      {

         break;

      }

      i++;

   }

   if(i1 >= 0)
   {

      str = str1.substr(i1 + 1);

      str1 = str1.left(i1 + 1);

      str2 = str2.substr(i2 + 1);

   }

   return i;

}


void process_process_new_text(
string & strInsert,
strsize & iInsBeg,
strsize & iInsEnd,
strsize & iSelBeg,
strsize & iSelEnd,
string strPrevious,
string strNow)
{

   string str;

   strsize iBeg = str_begins_common(strPrevious, strNow);

   strsize iEnd = str_ends_common(strPrevious, strNow);

   iSelBeg = iBeg;

   iInsBeg = iBeg;

   iInsEnd = strPrevious.length() - iEnd;

   strInsert = strNow.substr(iBeg, strNow.length() - iEnd - iBeg);

   iSelEnd = iBeg + strInsert.length();

   const ::scoped_string & scopedstr = unicode_next(strInsert);

   if(psz == nullptr || *psz == '\0')
   {

      iSelBeg = iSelEnd;

   }

}

int_bool SetWindowRect(oswindow hwnd, RECTANGLE_I32 * lprect);

// int_bool PeekMessage(
// MESSAGE * lpMsg,
// oswindow hWnd,
// ::u32 wMsgFilterMin,
// ::u32 wMsgFilterMax,
// ::u32 wRemoveMsg);


// int_bool GetMessage(
// MESSAGE * lpMsg,
// oswindow hWnd,
// ::u32 wMsgFilterMin,
// ::u32 wMsgFilterMax);

namespace ios
{




   interaction_impl::interaction_impl()
   {

      //set_handle(nullptr);
      //      m_puserinteraction->m_nFlags    = 0;
      //m_pfnSuper         = nullptr;
      //m_bMouseHover        = false;
      m_oswindow           = nullptr;
      m_proundwindow = nullptr;

   }


   void interaction_impl::construct(oswindow hWnd)
   {

      set_handle(hWnd);
      //m_bMouseHover        = false;
      m_oswindow           = nullptr;
      m_proundwindow = nullptr;
      m_bCanBecomeFirstResponder = false;

   }


   interaction_impl::~interaction_impl()
   {


   }


::user::interaction_impl *  interaction_impl::from_os_data(void * pdata)
   {

      return from_handle((oswindow) pdata);

   }


   void * interaction_impl::get_os_data() const
   {

      return ((oswindow &) m_oswindow);

   }



   // Change a window's style

   /*__STATIC bool CLASS_DECL_BASE __modify_style(oswindow hWnd, i32 nStyleOffset,
    ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags)
    {
    ASSERT(hWnd != nullptr);
    ::u32 uStyle = ::GetWindowLong(hWnd, nStyleOffset);
    ::u32 dwNewStyle = (uStyle & ~dwRemove) | dwAdd;
    if (uStyle == dwNewStyle)
    return false;

    ::SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
    if (nFlags != 0)
    {
    ::set_window_position(hWnd, nullptr, 0, 0, 0, 0,
    SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
    }
    return true;
    }*/

   /*
      bool  interaction_impl::ModifyStyle(oswindow hWnd, ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags)
      {

         //      throw ::exception(todo);

         if(!::is_window(hWnd))
            return false;

         ::u32 dw = hWnd->get_window_long(GWL_STYLE);

         dw &= ~dwRemove;

         dw |= dwAdd;

         hWnd->set_window_long(GWL_STYLE, dw);

         //return __modify_style(hWnd, GWL_STYLE, dwRemove, dwAdd, nFlags);

         return true;

      }


      bool interaction_impl::ModifyStyleEx(oswindow hWnd, ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags)
      {

         //      throw ::exception(todo);

         if(!::is_window(hWnd))
            return false;

         ::u32 dw = hWnd->get_window_long(GWL_EXSTYLE);

         dw &= ~dwRemove;

         dw |= dwAdd;

         hWnd->set_window_long(GWL_EXSTYLE, dw);

         return true;

         //      return __modify_style(hWnd, GWL_EXSTYLE, dwRemove, dwAdd, nFlags);

      }

   */

   const MESSAGE* PASCAL interaction_impl::GetCurrentMessage()
   {

      return nullptr;

   }

//   LRESULT interaction_impl::Default()
//   {
//
//      return 0;
//
//   }


   ::user::interaction_impl * interaction_impl::from_handle(oswindow oswindow)
   {

      if(oswindow == nullptr)
         return nullptr;

      return oswindow->m_pimpl;

   }


   ::user::interaction_impl * PASCAL interaction_impl::FromHandlePermanent(oswindow oswindow)
   {

      if(oswindow == nullptr)
         return nullptr;

      return oswindow->m_pimpl;

   }


   bool interaction_impl::Attach(oswindow hWndNew)
   {

      ASSERT(get_handle() == nullptr);     // only attach once, detach on destroy
      //  ASSERT(FromHandlePermanent(hWndNew) == nullptr);
      // must not already be in permanent ::collection::map

      if (hWndNew == nullptr)
         return false;
      //single_lock synchronouslock(::windows_definition::MutexHwnd(), true);
      //hwnd_map * pMap = ::windows_definition::MapHWND(true); // create ::collection::map if not exist
      //ASSERT(pMap != nullptr);

      //pMap->set_permanent(set_handle(hWndNew), this);
      //if(m_puserinteraction == nullptr)
      {
         //m_puserinteraction = this;
      }

      m_oswindow = hWndNew;

      return true;

   }

   oswindow interaction_impl::Detach()
   {
      oswindow hWnd = (oswindow) get_handle();
      if (hWnd != nullptr)
      {
         //         single_lock synchronouslock(::windows_definition::MutexHwnd(), true);
         //  ;;       hwnd_map * pMap = ::windows_definition::MapHWND(); // don't create if not exist
         //     if (pMap != nullptr)
         //      pMap->erase_handle(get_handle());
         //         set_handle(nullptr);
         m_oswindow = nullptr;
      }

      return hWnd;
   }

   void interaction_impl::pre_subclass_window()
   {
      // no default processing
   }


   /////////////////////////////////////////////////////////////////////////////
   // user::interaction creation

   bool interaction_impl::create_window_ex(
   ::user::interaction * pinteraction,
   ::pointer<::user::system>pusersystem,
   ::user::interaction * puiParent,
   atom atom)
   {

      if(!native_create_window_ex(pinteraction, cs,
                                  puiParent == nullptr ? nullptr : puiParent->get_safe_handle(), atom))
      {

         return false;

      }


      return true;

   }


   bool interaction_impl::_native_create_window_ex(::pointer<::user::system>pusersystem)
   {

      if(::is_window(get_handle()))
      {

         DestroyWindow();

      }

      //m_puserinteraction = pinteraction;

      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || is_string_ok(pusersystem->m_createstruct.lpszName));

      if(m_puserinteraction != nullptr)
      {

         if(!m_puserinteraction->pre_create_window(pusersystem))
         {

            post_non_client_destroy();

            return false;

         }

      }
      else
      {

         if (!pre_create_window(pusersystem))
         {

            post_non_client_destroy();

            return false;

         }

      }

      if(pusersystem->m_createstruct.hwndParent == nullptr)
      {

         pusersystem->m_createstruct.style &= ~WS_CHILD;

      }

      ::rectangle_i32 rectangleCreate;

      pusersystem->m_createstruct.get_rect(rectangleCreate);

      CGRect rectangle_i32;

      copy(rectangle, rectangleCreate);
      
      install_message_routing(m_puserinteraction);

      if(pusersystem->m_createstruct.hwndParent != HWND_MESSAGE)
      {

         m_oswindow = oswindow_get(new_round_window(this, rectangle));
         
         copy(rectangleCreate, rectangle);

         m_puserinteraction->place(rectangleCreate);

         __construct(m_pgraphics, __new(::graphics::double_buffer));

         m_pgraphics->initialize_graphics_graphics(this);
         
         m_oswindow->set_user_interaction_impl(this);

      }

      m_puserinteraction->send_message(e_message_create, 0, (LPARAM) &cs);

      m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
      
      return true;

   }


   // for child windows
   bool interaction_impl::pre_create_window(::user::system * pusersystem)
   {
      /*      if (pusersystem->m_createstruct.lpszClass == nullptr)
       {
       // make sure the default user::interaction class is registered
       VERIFY(__end_defer_register_class(__WND_REG, &pusersystem->m_createstruct.lpszClass));

       // no WNDCLASS provided - use child user::interaction default
       ASSERT(pusersystem->m_createstruct.style & WS_CHILD);
       }*/
      return true;
   }


   bool interaction_impl::create_window(::user::interaction * pinteraction, const ::string & pszClassName, const ::string & pszWindowName,u32 uStyle,const ::rectangle_i32 & rectangle,::user::interaction * puiParent,atom atom, ::request * prequest)
   {
      
      // can't use for desktop or pop-up windows (use CreateEx instead)
      ASSERT(puiParent != nullptr);
      
      ASSERT((uStyle & WS_POPUP) == 0);

      ::user::system createstruct(0, pszClassName, pszWindowName, uStyle | WS_CHILD,
                               rectangle_i32);

      return create_window_ex(pinteraction, createstruct, puiParent, atom);
      
   }



   bool interaction_impl::_is_window() const
   {
   
      return m_oswindow && m_puserinteraction && m_puserinteraction->m_ewindowflag & e_window_flag_is_window
      && m_puserinteraction->m_ewindowflag & e_window_flag_window_created;
   
   }


//   bool interaction_impl::native_create_window_ex(::user::system & createstruct)
//   {
//
//      CGRect rectangle_i32;
//
//      rectangle.origin.x = pinitialize->m_rectangle.left;
//      rectangle.origin.y = pinitialize->m_rectangle.top;
//      rectangle.size.width = width(pinitialize->m_rectangle);
//      rectangle.size.height = height(pinitialize->m_rectangle);
//
//      m_rectangleParentClientRequest = pinitialize.m_rectangle;
//
//      m_oswindow = oswindow_get(new_round_window(this, rectangle));
//
//      install_message_routing(this);
//
//      m_spgraphics.create(this);
//
//      m_spgraphics->on_create_window(this);
//
//      m_oswindow->set_user_interaction_impl(this);
//
//      m_puserinteraction->ModifyStyle(0, WS_VISIBLE);
//
//      m_puserinteraction->send_message(e_message_create);
//
//      m_puserinteraction->send_message(e_message_size);
//
//      m_puserinteraction->send_message(e_message_reposition);
//
//      m_puserinteraction->send_message(e_message_show_window, 1);
//
//      return true;
//
//   }


   // bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const ::string & pszName)
   // {

   //    if(IsWindow())
   //    {

   //       set_window_text(pszName);

   //    }
   //    else
   //    {

   //       ::user::system createstruct(0, nullptr, pszName, WS_CHILD);

   //       if(!native_create_window_ex(pinteraction, cs, HWND_MESSAGE, pszName))
   //       {

   //          return false;

   //       }

   //    }

   //    return true;

   // }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      
            last_install_message_routing(pchannel);

            ::user::interaction_impl::install_message_routing(pchannel);

            if (!m_puserinteraction->m_bMessageWindow)
            {

               MESSAGE_LINK(e_message_paint, pchannel, this, &interaction_impl::_001OnPaint);
               MESSAGE_LINK(WM_PRINT, pchannel, this, &interaction_impl::_001OnPrint);

            }

            m_puserinteraction->install_message_routing(pchannel);

            MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &interaction_impl::on_message_create);

            if (!m_puserinteraction->m_bMessageWindow)
            {

      //         MESSAGE_LINK(e_message_set_cursor, pchannel, this, &interaction_impl::on_message_set_cursor);
      //         MESSAGE_LINK(e_message_erase_background, pchannel, this,&interaction_impl::_001OnEraseBkgnd);
               //         MESSAGE_LINK(e_message_non_client_calc_size, pchannel, this,&interaction_impl::on_message_non_client_calculate_size);
      //         MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::on_message_size);
               //         MESSAGE_LINK(e_message_window_position_changing, pchannel, this,&interaction_impl::_001OnWindowPosChanging);
               //         MESSAGE_LINK(e_message_window_position_changed, pchannel, this,&interaction_impl::_001OnWindowPosChanged);
               //         MESSAGE_LINK(WM_GETMINMAXINFO, pchannel, this,&interaction_impl::_001OnGetMinMaxInfo);
               //         MESSAGE_LINK(e_message_set_focus, pchannel, this,&interaction_impl::on_message_set_focus);
               //         MESSAGE_LINK(e_message_kill_focus, pchannel, this,&interaction_impl::on_message_kill_focus);
               //MESSAGE_LINK(ca2m_PRODEVIAN_SYNCH, pchannel, this,&interaction_impl::_001OnProdevianSynch);
            }
            prio_install_message_routing(pchannel);
            MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &interaction_impl::on_message_destroy);

            //      ::user::interaction_impl::install_message_routing(pchannel);
            //      //m_pbuffer->InstallMessageHandling(pinterface);
            //      MESSAGE_LINK(MESSAGE_DESTROY           , pchannel, this, &interaction_impl::on_message_destroy);
            //      MESSAGE_LINK(e_message_paint             , pchannel, this, &interaction_impl::_001OnPaint);
            //      MESSAGE_LINK(WM_PRINT             , pchannel, this, &interaction_impl::_001OnPrint);
            //      if(m_puserinteraction != nullptr)
            //      {
            //         m_puserinteraction->install_message_routing(pchannel);
            //      }
            //      MESSAGE_LINK(MESSAGE_CREATE            , pchannel, this, &interaction_impl::on_message_create);
            //      MESSAGE_LINK(e_message_set_cursor         , pchannel, this, &interaction_impl::on_message_set_cursor);
            //      MESSAGE_LINK(e_message_erase_background        , pchannel, this, &interaction_impl::_001OnEraseBkgnd);
            //      MESSAGE_LINK(e_message_reposition              , pchannel, this, &interaction_impl::on_message_move);
            //      MESSAGE_LINK(e_message_size              , pchannel, this, &interaction_impl::on_message_size);
            MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_impl::on_message_show_window);
            //      MESSAGE_LINK(ca2m_PRODEVIAN_SYNCH , pchannel, this, &interaction_impl::_001OnProdevianSynch);
            ////      //MESSAGE_LINK(e_message_timer             , pchannel, this, &interaction_impl::_001OnTimer);

      last_install_message_routing(pchannel);

//      ::user::interaction_impl::install_message_routing(pchannel);
//      //m_pbuffer->InstallMessageHandling(pinterface);
//      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &interaction_impl::on_message_destroy);
//      MESSAGE_LINK(e_message_paint, pchannel, this, &interaction_impl::_001OnPaint);
//      MESSAGE_LINK(WM_PRINT, pchannel, this, &interaction_impl::_001OnPrint);
//
//      if(m_puserinteraction != nullptr)
//      {
//
//         m_puserinteraction->install_message_routing(pchannel);
//
//      }
//
//      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &interaction_impl::on_message_create);
//      MESSAGE_LINK(e_message_set_cursor, pchannel, this, &interaction_impl::on_message_set_cursor);
//      MESSAGE_LINK(e_message_erase_background, pchannel, this, &interaction_impl::_001OnEraseBkgnd);
//      MESSAGE_LINK(e_message_reposition, pchannel, this, &interaction_impl::on_message_move);
//      MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::on_message_size);
//      MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::on_message_set_focus);
//      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::on_message_kill_focus);
////      MESSAGE_LINK(e_message_show_window        , pchannel, this, &interaction_impl::on_message_show_window);
////      MESSAGE_LINK(ca2m_PRODEVIAN_SYNCH , pchannel, this, &interaction_impl::_001OnProdevianSynch);
//      //      //MESSAGE_LINK(e_message_timer             , pchannel, this, &interaction_impl::_001OnTimer);
//
//      prio_install_message_routing(pchannel);

   }


   void interaction_impl::on_message_move(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction_impl::on_message_size(::message::message * pmessage)
   {
      
      __UNREFERENCED_PARAMETER(pmessage);

//      size_i32 sizeRequest = m_rectangleParentClientRequest.size();
//
//      for(auto & pinteraction : m_puserinteraction->m_uiptraChild)
//      {
//
//         pinteraction->ResizeWindow(sizeRequest);
//
//      }



   }



   void interaction_impl::on_message_destroy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //Default();

   }


   void interaction_impl::post_non_client_destroy()
   {

      single_lock synchronouslock(get_app() == nullptr ? nullptr : get_app()->mutex(), true);

      //pmessage->m_bRet = true;

      ::thread* pThread = ::get_task();

      if (pThread != nullptr)
      {

         if (pThread->get_active_ui() == m_puserinteraction)
         {

            pThread->set_active_ui(nullptr);

         }

      }

      round_window_destroy();

      Detach();

      ASSERT(get_handle() == nullptr);

      ::user::interaction_impl::post_non_client_destroy();

   }


   void interaction_impl::on_final_release()
   {
      
      if (get_handle() != nullptr)
      {
         
         DestroyWindow();    // will call post_non_client_destroy
         
      }
      else
      {
         
         post_non_client_destroy();
         
      }
      
   }


   void interaction_impl::assert_ok() const
   {
      
      if (get_handle() == nullptr)
      {
         
         return;     // null (unattached) windows are valid
         
      }

      // check for special wnd??? values
      //      ASSERT(oswindow_TOP == nullptr);       // same as desktop
      /*      if (get_handle() == oswindow_BOTTOM)
       {
       }
       else if (get_handle() == oswindow_TOPMOST)
       {
       }
       else if (get_handle() == oswindow_NOTOPMOST)
       {
       }
       else
       {
       // should be a normal user::interaction
       ASSERT(::is_window(get_handle()));

       // should also be in the permanent or temporary handle ::collection::map
       single_lock synchronouslock(::windows_definition::MutexHwnd(), true);
       hwnd_map * pMap = ::windows_definition::MapHWND();
       if(pMap == nullptr) // inside thread not having windows
       return; // let go
       ASSERT(pMap != nullptr);

       //         ::ca2::object* p=nullptr;
       if(pMap)
       {
       ASSERT( (p = pMap->lookup_permanent(get_handle())) != nullptr ||
       (p = pMap->lookup_temporary(get_handle())) != nullptr);
       }*/

      //ASSERT(dynamic_cast < ::user::interaction *  > (p) == this);   // must be us

      // Note: if either of the above asserts fire and you are
      // writing a multitasked application, it is likely that
      // you have passed a C++ object from one thread to another
      // and have used that object in a way that was not intended.
      // (only simple inline wrapper functions should be used)
      //
      // In general, user::interaction objects should be passed by oswindow from
      // one thread to another.  The receiving thread can wrap
      // the oswindow with a user::interaction object by using ::macos::interaction_impl::from_handle.
      //
      // It is dangerous to pass C++ objects from one thread to
      // another, unless the objects are designed to be used in
      // such a manner.
      //      }*/
      
   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      
      ::object::dump(dumpcontext);

      dumpcontext << "\nm_hWnd = " << (void *)get_handle();

      /*      if (get_handle() == nullptr || get_handle() == oswindow_BOTTOM ||
       get_handle() == oswindow_TOPMOST || get_handle() == oswindow_NOTOPMOST)
       {
       // not a normal user::interaction - nothing more to dump
       return;
       }*/

      /*      if (!::is_window(get_handle()))
       {
       // not a valid user::interaction
       dumpcontext << " (illegal oswindow)";
       return; // don't do anything more
       }*/

      ::user::interaction_impl * pWnd = (::user::interaction_impl *) this;
      if (pWnd != this)
         dumpcontext << " (Detached or temporary user::interaction)";
      else
         dumpcontext << " (permanent user::interaction)";

      // dump out user::interaction specific statistics
      char szBuf [64];
      dumpcontext << "\ncaption = \"" << szBuf << "\"";

      //      ::GetClassName(get_handle(), szBuf, _countof(szBuf));
      //    dumpcontext << "\nclass name = \"" << szBuf << "\"";

      ::rectangle_i32 rectangle;
      m_puserinteraction->window_rectangle(&rectangle);
      dumpcontext << "\nrect = " << rectangle_i32;
      dumpcontext << "\nparent ::user::interaction * = " << (void *)((::user::interaction_impl *) this)->get_parent();

      //      dumpcontext << "\nstyle = " << (void *)(dword_ptr)::GetWindowLong(get_handle(), GWL_STYLE);
      //    if (::GetWindowLong(get_handle(), GWL_STYLE) & WS_CHILD)
      //     dumpcontext << "\nid = " << __get_dialog_control_id(get_handle());

      dumpcontext << "\n";
      
   }


   bool interaction_impl::DestroyWindow()
   {

      single_lock synchronouslock(get_app() == nullptr ? nullptr : get_app()->mutex(), true);

      if(get_handle() == nullptr)
         return false;

      bool bResult = ::user::interaction_impl::DestroyWindow();

      return bResult;

   }


//   LRESULT interaction_impl::DefWindowProc(::u32 nMsg, wparam wparam, ::lparam lparam)
//   {
//      /*  if (m_pfnSuper != nullptr)
//       return ::CallWindowProc(m_pfnSuper, get_handle(), nMsg, wparam, lparam);
//
//       WNDPROC pfnWndProc;
//       if ((pfnWndProc = *GetSuperWndProcAddr()) == nullptr)
//       return ::DefWindowProc(get_handle(), nMsg, wparam, lparam);
//       else
//       return ::CallWindowProc(pfnWndProc, get_handle(), nMsg, wparam, lparam);*/
//
//      return 0;
//   }

   /*
    WNDPROC* interaction_impl::GetSuperWndProcAddr()
    {
    // Note: it is no longer necessary to override GetSuperWndProcAddr
    //  for each control class with a different WNDCLASS.
    //  This implementation now uses instance data, such that the previous
    //  WNDPROC can be anything.

    return &m_pfnSuper;
    }
    */
   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      // no default processing
   }


   void interaction_impl::get_window_text(string & rString)
   {

      rString = m_strWindowText;

   }


   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpuserinteractionpl)
   {

      return false;

   }


   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpuserinteractionpl)
   {

      return false;

   }


   /////////////////////////////////////////////////////////////////////////////
   // user::interaction will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
   // /*   void interaction_impl::OnDrawItem(i32 /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
   // {

   // reflect notification to child user::interaction control
   //  if (ReflectLastMsg(lpDrawItemStruct->hwndItem))
   //   return;     // eat it

   // not handled - do default
   //      Default();
   // }

   // Drawing: for all 4 control types
   //   i32 interaction_impl::OnCompareItem(i32 /*nIDCtl*/, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   // {
   //  // reflect notification to child user::interaction control
   //LRESULT lResult;
   //      if (ReflectLastMsg(lpCompareItemStruct->hwndItem, &lResult))
   //       return (i32)lResult;        // eat it

   // not handled - do default
   //  return (i32)Default();
   //   }

   // void interaction_impl::OnDeleteItem(i32 /*nIDCtl*/, LPDELETEITEMSTRUCT lpDeleteItemStruct)
   //{
   // reflect notification to child user::interaction control
   // if (ReflectLastMsg(lpDeleteItemStruct->hwndItem))
   //  return;     // eat it
   // not handled - do default
   //      Default();
   // }

   bool interaction_impl::_EnableToolTips(bool bEnable, ::u32 nFlag)
   {
      __UNREFERENCED_PARAMETER(bEnable);
      __UNREFERENCED_PARAMETER(nFlag);
      return false;
   }

   LRESULT interaction_impl::OnNTCtlColor(wparam wparam, lparam lparam)
   {
      return 0;
   }


   void interaction_impl::PrepareForHelp()
   {
      /*if (IsFrameWnd())
       {
       // frame_window windows should be allowed to exit help mode first
       frame_window* pFrameWnd = dynamic_cast < frame_window * >(this);
       pFrameWnd->ExitHelpMode();
       }

       // cancel any tracking modes
       send_message(WM_CANCELMODE);
       send_message_to_descendants(WM_CANCELMODE, 0, 0, true, true);

       // need to use top level parent (for the case where get_handle() is in DLL)
       ::user::interaction * pWnd = EnsureTopLevelParent();
       IOS_WINDOW(pWnd)->send_message(WM_CANCELMODE);
       IOS_WINDOW(pWnd)->send_message_to_descendants(WM_CANCELMODE, 0, 0, true, true);

       // attempt to cancel capture
       oswindow hWndCapture = ::GetCapture();
       if (hWndCapture != nullptr)
       ::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);*/
   }


   /*void interaction_impl::WinHelpInternal(dword_ptr dwData, ::u32 nCmd)
    {
    __UNREFERENCED_PARAMETER(dwData);
    __UNREFERENCED_PARAMETER(nCmd);
    throw ::not_implemented();

    application* pApp = System;
    ASSERT_VALID(pApp);
    if (pApp->m_eHelpType == ::windows_definition::HTMLHelp)
    {
    // translate from WinHelp commands and data to to HtmlHelp
    ASSERT((nCmd == HELP_CONTEXT) || (nCmd == HELP_CONTENTS) || (nCmd == HELP_FINDER));
    if (nCmd == HELP_CONTEXT)
    nCmd = HH_HELP_CONTEXT;
    else if (nCmd == HELP_CONTENTS)
    nCmd = HH_DISPLAY_TOC;
    else if (nCmd == HELP_FINDER)
    nCmd = HH_HELP_FINDER;
    HtmlHelp(dwData, nCmd);
    }
    else
    WinHelp(dwData, nCmd);*/
   //}


   void interaction_impl::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      channel::route_command(pcommand);

   }


   void interaction_impl::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(pevent);

      //return false;

   }

   void interaction_impl::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //      ::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));

   }


   void interaction_impl::message_handler(::user::message * pusermessage)
   {


      if(pusermessage->m_atom == e_message_size || pusermessage->m_atom == e_message_reposition)
      {

         //         win_update_graphics();

      }

      if(pusermessage->m_atom == e_message_key_down || pusermessage->m_atom == e_message_key_up || pusermessage->m_atom == e_message_char)
      {

         ::pointer<::message::key>pkey(pusermessage);

         psession->translate_os_key_message(pkey);

         if(pusermessage->m_atom == e_message_key_down)
         {

            try
            {

               psession->set_key_pressed(pkey->m_ekey, true);

            }
            catch(...)
            {

            }

         }
         else if(pusermessage->m_atom == e_message_key_up)
         {

            try
            {

               psession->set_key_pressed(pkey->m_ekey, false);

            }
            catch(...)
            {

            }

         }

      }

      if(m_puserinteraction != nullptr)
      {

         m_puserinteraction->pre_translate_message(pusermessage);

         if(pusermessage->m_bRet)
            return;

      }

      if(pusermessage->m_atom == e_message_timer)
      {
         //         get_app()->get_app()->step_timer();
      }
      else if(pusermessage->m_atom == e_message_left_button_down)
      {
         //  g_puserinteractionLastLButtonDown = this;
      }
      else if(pusermessage->m_atom == e_message_size)
      {
         m_bUpdateGraphics = true;
      }
      /*      else if(pusermessage->m_atom == CA2M_BERGEDGE)
       {
       if(pusermessage->m_wparam == BERGEDGE_GETAPP)
       {
       ::application ** ppapp= (::apex::application **) pusermessage->m_lparam;
       *ppapp = get_app();
       pusermessage->m_bRet = true;
       return;
       }
       }*/
      pusermessage->set_lresult(0);

      if(pusermessage->m_atom == e_message_mouse_leave)
      {

         _000OnMouseLeave(pusermessage);

         return;

      }

      if(pusermessage->m_atom == e_message_left_button_down ||
            pusermessage->m_atom == e_message_left_button_up ||
            pusermessage->m_atom == e_message_middle_button_down ||
            pusermessage->m_atom == e_message_middle_button_up ||
            pusermessage->m_atom == e_message_right_button_down ||
            pusermessage->m_atom == e_message_right_button_up ||
            pusermessage->m_atom == e_message_mouse_move ||
            pusermessage->m_atom == e_message_mouse_move)
         //         pusermessage->m_atom == e_message_mouse_wheel)
      {
         if(pusermessage->m_atom == e_message_left_button_down)
         {

            //            TRACE("e_message_left_button_down");

         }

         ::message::mouse * pmouse = (::message::mouse *) pusermessage;


         // user presence status activity reporting

         psession->on_ui_mouse_message(pmouse);


         if(get_session() != nullptr)
         {

            psession->m_pointCursor = pmouse->m_point;

         }

         /*         if(m_puserinteraction != nullptr && m_puserinteraction != this && m_puserinteraction->get_app()->m_psession != nullptr && m_puserinteraction->get_app()->m_psession != get_app()->m_psession)
          {

          BaseSess(m_puserinteraction->get_app()->m_psession).m_pointCursor = pmouse->m_point;

          }
          */

         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {

            pmouse->m_bTranslated = true;

            rectangle_i32 rectangleWindow;

            ((::user::interaction_impl *)this)->m_puserinteraction->window_rectangle(rectangleWindow);

            if(psystem->get_monitor_count() > 0)
            {
               ::rectangle_i32 rcMonitor;
               psystem->get_monitor_rectangle(0, &rcMonitor);
               if(rectangleWindow.left >= rcMonitor.left)
                  pmouse->m_point.x += (::i32) rectangleWindow.left;
               if(rectangleWindow.top >= rcMonitor.top)
                  pmouse->m_point.y += (::i32) rectangleWindow.top;
            }
            else
            {
               if(rectangleWindow.left >= 0)
                  pmouse->m_point.x += (::i32) rectangleWindow.left;
               if(rectangleWindow.top >= 0)
                  pmouse->m_point.y += (::i32) rectangleWindow.top;
            }
         }

         if(pusermessage->m_atom == e_message_mouse_move)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse transfer events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;

         }

         _008OnMouse(pmouse);

         return;

      }
      else if(pusermessage->m_atom == e_message_key_down ||
              pusermessage->m_atom == e_message_key_up ||
              pusermessage->m_atom == e_message_char)
      {

         ::message::key * pkey = (::message::key *) pusermessage;

         //         papp->keyboard().translate_os_key_message(pkey);
         /*
          if(pusermessage->m_atom == e_message_key_down)
          {
          try
          {
          papp->set_key_pressed(pkey->m_ekey, true);
          }
          catch(...)
          {
          }
          }
          else if(pusermessage->m_atom == e_message_key_up)
          {
          try
          {
          papp->set_key_pressed(pkey->m_ekey, false);
          }
          catch(...)
          {
          }
          }
          */

         ::user::interaction * puiFocus = dynamic_cast < ::user::interaction * > (psession->get_keyboard_focus());
         if(puiFocus != nullptr
               && puiFocus->is_window()
               && puiFocus->get_top_level() != nullptr)
         {
            puiFocus->send(pkey);
            if(pusermessage->m_bRet)
               return;
         }
         else if(!pkey->m_bRet)
         {
            if(m_puserinteraction != nullptr)
            {
               m_puserinteraction->_000OnKey(pkey);
               if(pusermessage->m_bRet)
                  return;
            }
         }
         
         default_window_procedure(pusermessage);

         return;

      }

      if(pusermessage->m_atom == e_message_event)
      {

         if(m_puserinteraction != nullptr)
         {

            m_puserinteraction->handle_event(pusermessage->m_lparam.cast < ::user::control_event >());

         }
         else
         {

            handle_event(pusermessage->m_lparam.cast < ::user::control_event > ());

         }

      }

      m_puserinteraction->route_message(pusermessage);

      if(pusermessage->m_bRet)
         return;

      default_window_procedure(pusermessage);

   }


   bool interaction_impl::OnCommand(wparam wparam, lparam lparam)
   // return true if command invocation was attempted
   {
      
      __UNREFERENCED_PARAMETER(wparam);
      __UNREFERENCED_PARAMETER(lparam);

      return false;

   }


   bool interaction_impl::OnNotify(WPARAM, lparam lparam, LRESULT* pResult)
   {
      /*    ASSERT(pResult != nullptr);
       NMHDR* pNMHDR = (NMHDR*)lparam;
       oswindow hWndCtrl = pNMHDR->hwndFrom;

       // get the child ID from the user::interaction itself
       //      uptr nID = __get_dialog_control_id(hWndCtrl);
       //      i32 nCode = pNMHDR->code;

       ASSERT(hWndCtrl != nullptr);
       ASSERT(::is_window(hWndCtrl));

       if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
       return true;        // locked out - ignore control notification

       // reflect notification to child user::interaction control
       if (ReflectLastMsg(hWndCtrl, pResult))
       return true;        // eaten by child

       //      __NOTIFY notify;
       //    notify.pResult = pResult;
       //  notify.pNMHDR = pNMHDR;
       //xxx   return _001OnCommand((::u32)nID, MAKELONG(nCode, WM_NOTIFY), &notify, nullptr);*/
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // user::interaction extensions

   /*

    ::pointer<::user::frame_window>interaction_impl::get_parent_frame()
    {
    if (get_handle() == nullptr) // no oswindow attached
    {
    return nullptr;
    }

    ASSERT_VALID(this);

    ::user::interaction * puiParent = get_parent();  // start with one parent up
    while (puiParent != nullptr)
    {
    if (puiParent->is_frame_window())
    {
    return dynamic_cast < ::user::frame_window * > (puiParent);
    }
    puiParent = puiParent->get_parent();
    }
    return nullptr;
    }

    */

   /* trans oswindow CLASS_DECL_BASE __get_parent_owner(::user::interaction * hWnd)
    {
    // check for permanent-owned user::interaction first
    ::user::interaction * pWnd = ::macos::interaction_impl::FromHandlePermanent(hWnd);
    if (pWnd != nullptr)
    return IOS_WINDOW(pWnd)->get_owner();

    // otherwise, return parent in the oswindows sense
    return (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) ?
    ::get_parent(hWnd) : ::GetWindow(hWnd, GW_OWNER);
    }*/


   /*

    ::user::interaction *  interaction_impl::get_top_level() const
    {
    if (get_handle() == nullptr) // no oswindow attached
    return nullptr;

    ASSERT_VALID(this);
    //
    //      ::user::interaction * hWndParent = this;
    //      ::user::interaction * hWndT;
    //while ((hWndT = __get_parent_owner(hWndParent)) != nullptr)
    // hWndParent = hWndT;

    //      return hWndParent;
    return m_puserinteraction;

    }


    ::user::interaction *  interaction_impl::GetTopLevelOwner()
    {
    if (get_handle() == nullptr) // no oswindow attached
    return nullptr;

    ASSERT_VALID(this);

    //      oswindow hWndOwner = get_handle();
    //    oswindow hWndT;
    //  while ((hWndT = ::GetWindow(hWndOwner, GW_OWNER)) != nullptr)
    //   hWndOwner = hWndT;

    //      return ::macos::interaction_impl::from_handle(hWndOwner);
    return nullptr;
    }

    ::user::interaction *  interaction_impl::GetParentOwner()
    {
    if (get_handle() == nullptr) // no oswindow attached
    return nullptr;

    ASSERT_VALID(this);

         oswindow hWndParent = get_handle();
    oswindow hWndT;
    while ((::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) &&
    (hWndT = ::get_parent(hWndParent)) != nullptr)
    {
    hWndParent = hWndT;
    }

    return ::macos::interaction_impl::from_handle(hWndParent);*/

   //      return nullptr;
   // }

   bool interaction_impl::IsTopParentActive()
   {
      ASSERT(get_handle() != nullptr);
      ASSERT_VALID(this);

      ::user::interaction *pWndTopLevel=EnsureTopLevel();

      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
   }

   void interaction_impl::ActivateTopParent()
   {
      // special activate logic for floating toolbars and palettes
      //      ::user::interaction * pActiveWnd = GetForegroundWindow();
      //      if (pActiveWnd == nullptr || !(IOS_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(IOS_WINDOW(pActiveWnd)->get_handle(), get_handle())))
      {
         // clicking on floating frame when it does not have
         // focus itself -- activate the toplevel frame instead.
         EnsureTopLevel()->SetForegroundWindow();
      }
   }


   /*

    ::pointer<::user::frame_window>interaction_impl::top_level_frame()
    {
    if (get_handle() == nullptr) // no oswindow attached
    return nullptr;

    ASSERT_VALID(this);

    ::user::frame_window* pFrameWnd = nullptr;
    if(m_puserinteraction != nullptr)
    pFrameWnd = dynamic_cast < ::user::frame_window * > (m_puserinteraction);
    if (pFrameWnd == nullptr || !pFrameWnd->is_frame_window())
    pFrameWnd = get_parent_frame();

    if (pFrameWnd != nullptr)
    {
    ::user::frame_window* pTemp;
    while ((pTemp = pFrameWnd->get_parent_frame()) != nullptr)
    pFrameWnd = pTemp;
    }
    return pFrameWnd;
    }


    */




//   i32 interaction_impl::message_box(const ::string & lpszText, const ::string & lpszCaption, ::u32 nType)
//   {
//
//      string strCaption;
//
//      if (lpszCaption == nullptr)
//         lpszCaption = papp->m_strAppName;
//      else
//         lpszCaption = strCaption;
//      
//      payload = payload;
//      
//      payload["oswindow"] = (i64) get_handle();
//      payload["message"] = lpszText;
//      payload["caption"] = lpszCaption;
//      payload["message_box_type"] = (i64) nType;
//
//      i32 nResult = message_box((oswindow)get_handle(), lpszText, lpszCaption, nType);
//
//      return nResult;
//
//   }



   i32 interaction_impl::SetScrollPos(i32 nBar, i32 nPos, bool bRedraw)
   {
      //      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
      return 0;
   }

   i32 interaction_impl::GetScrollPos(i32 nBar) const
   {
      //return ::GetScrollPos(get_handle(), nBar);
      return 0;
   }

   void interaction_impl::SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos, bool bRedraw)
   {
      //::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
   }

   void interaction_impl::GetScrollRange(i32 nBar, LPINT lpMinPos, LPINT lpMaxPos) const
   {
      //::GetScrollRange(get_handle(), nBar, lpMinPos, lpMaxPos);
   }

   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(i32 nBar, bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar, bEnable);
   }

   /*
    bool interaction_impl::SetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo, bool bRedraw)
    {
    ASSERT(lpScrollInfo != nullptr);

    oswindow hWnd = get_handle();
    lpScrollInfo->cbSize = sizeof(*lpScrollInfo);
    ::SetScrollInfo(hWnd, nBar, lpScrollInfo, bRedraw);
    return true;
    }

    bool interaction_impl::GetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo, ::u32 nMask)
    {
    __UNREFERENCED_PARAMETER(nMask);
    ASSERT(lpScrollInfo != nullptr);

    oswindow hWnd = get_handle();
    return ::GetScrollInfo(hWnd, nBar, lpScrollInfo) != false;
    }
    */
   i32 interaction_impl::GetScrollLimit(i32 nBar)
   {
      i32 nMin, nMax;
      GetScrollRange(nBar, &nMin, &nMax);
      /*      SCROLLINFO info;
       if (GetScrollInfo(nBar, &info, SIF_PAGE))
       {
       nMax -= maximum(info.nPage-1,0);
       }*/
      return nMax;
   }

//   void interaction_impl::ScrollWindow(i32 xAmount, i32 yAmount,
//                                       const ::rectangle_i32 & rectangle, const RECTANGLE_I32 * lpClipRect)
//   {
//      /*      ASSERT(::is_window(get_handle()));
//
//       if (is_window_visible() || lpRect != nullptr || lpClipRect != nullptr)
//       {
//       // When visible, let oswindows do the scrolling
//       ::ScrollWindow(get_handle(), xAmount, yAmount, lpRect, lpClipRect);
//       }
//       else
//       {
//       // oswindows does not perform any scrolling if the user::interaction is
//       // not visible.  This leaves child windows unscrolled.
//       // To account for this oversight, the child windows are moved
//       // directly instead.
//       oswindow hWndChild = ::GetWindow(get_handle(), GW_CHILD);
//       if (hWndChild != nullptr)
//       {
//       for (; hWndChild != nullptr;
//       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
//       {
//       ::rectangle_i32 rectangle;
//       ::window_rectangle(hWndChild, &rectangle);
//       screen_to_client(&rectangle);
//       ::set_window_position(hWndChild, nullptr,
//       rectangle.left+xAmount, rectangle.top+yAmount, 0, 0,
//       SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
//       }
//       }
//       }
//       */
//   }



   void interaction_impl::CalcWindowRect(RECTANGLE_I32 * lpClientRect, ::u32 nAdjustType)
   {
      /*::u32 dwExStyle = GetExStyle();
       if (nAdjustType == 0)
       dwExStyle &= ~WS_EX_CLIENTEDGE;
       ::AdjustWindowRectEx(lpClientRect, GetStyle(), false, dwExStyle);*/
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(::u32 nID, lparam lparam)
   {
      /*      ::user::interaction* pParent = GetTopLevelParent();
       switch (nID & 0xfff0)
       {
       case SC_PREVWINDOW:
       case SC_NEXTWINDOW:
       if (LOWORD(lparam) == VK_F6 && pParent != nullptr)
       {
       pParent->SetFocus();
       return true;
       }
       break;

       case SC_CLOSE:
       case SC_KEYMENU:
       // Check lparam.  If it is 0L, then the ::account::user may have done
       // an Alt+Tab, so just ignore it.  This breaks the ability to
       // just press the Alt-key and have the first menu selected,
       // but this is minor compared to what happens in the Alt+Tab
       // case.
       if ((nID & 0xfff0) == SC_CLOSE || lparam != 0L)
       {
       if (pParent != nullptr)
       {
       // Sending the above WM_SYSCOMMAND may destroy the cast,
       // so we have to be careful about restoring activation
       // and focus after sending it.
       oswindow hWndSave = get_handle();
       oswindow hWndFocus = ::GetFocus();
       pParent->SetActiveWindow();
       pParent->send_message(WM_SYSCOMMAND, nID, lparam);

       // be very careful here...
       if (::is_window(hWndSave))
       ::set_active_window(hWndSave);
       if (::is_window(hWndFocus))
       ::SetFocus(hWndFocus);
       }
       }
       return true;
       }
       return false;*/
      return false;
   }

   void interaction_impl::WalkPreTranslateTree(::user::interaction *  puiStop, ::message::message * pmessage)
   {
      ASSERT(puiStop == nullptr || puiStop->is_window());
      ASSERT(pmessage != nullptr);

      ::pointer<::user::message>pusermessage(pmessage);
      // walk from the target user::interaction up to the hWndStop user::interaction checking
      //  if any user::interaction wants to translate this message

      for (::pointer<::user::interaction>pinteraction = pusermessage->m_puserinteraction; pinteraction != nullptr; pinteraction->get_parent())
      {

         pinteraction->pre_translate_message(pmessage);

         if(pmessage->m_bRet)
            return; // trapped by target user::interaction (eg: accelerators)

         // got to hWndStop user::interaction without interest
         if(pinteraction == puiStop)
            break;

      }
      // no special processing
   }


   bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
   {

      return false;

   }

   bool PASCAL interaction_impl::ReflectLastMsg(oswindow hWndChild, LRESULT* pResult)
   {
      // get the ::collection::map, and if no ::collection::map, then this message does not need reflection
      /*      single_lock synchronouslock(::windows_definition::MutexHwnd(), true);
       hwnd_map * pMap = ::windows_definition::MapHWND();
       if (pMap == nullptr)
       return false;

       // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
       ::user::interaction * pWnd = dynamic_cast < ::user::interaction * > (pMap->lookup_permanent(hWndChild)); */
      ::user::interaction * pWnd = dynamic_cast < ::user::interaction * > (FromHandlePermanent(hWndChild));
      ASSERT(pWnd == nullptr || pWnd->get_handle() == hWndChild);
      if (pWnd == nullptr)
      {
         return false;
      }

      // only OLE controls and permanent windows will get reflected msgs
      ASSERT(pWnd != nullptr);
      //return IOS_WINDOW(pWnd)->SendChildNotifyLastMsg(pResult);
      return false;
   }

   bool interaction_impl::OnChildNotify(::u32 uMsg, wparam wparam, lparam lparam, LRESULT* pResult)
   {

      return ReflectChildNotify(uMsg, wparam, lparam, pResult);
   }

   bool interaction_impl::ReflectChildNotify(::u32 uMsg, wparam wparam, lparam lparam, LRESULT* pResult)
   {
      __UNREFERENCED_PARAMETER(wparam);
      // Note: reflected messages are send directly to interaction_impl::OnWndMsg
      //  and interaction_impl::_001OnCommand for speed and because these messages are not
      //  routed by normal _001OnCommand routing (they are only dispatched)

      switch (uMsg)
      {
      // normal messages (just wparam, lparam through OnWndMsg)
      case e_message_hscroll:
      case e_message_vscroll:
      case WM_PARENTNOTIFY:
      case WM_DRAWITEM:
      case e_message_measure_item:
      case WM_DELETEITEM:
      case WM_VKEYTOITEM:
      case WM_CHARTOITEM:
      case WM_COMPAREITEM:
         // reflect the message through the message ::collection::map as WM_REFLECT_BASE+uMsg
         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wparam, lparam, pResult);
         return false;

      // special case for e_message_command
      case e_message_command:
      {
         // reflect the message through the message ::collection::map as OCM_COMMAND
         /* xxx         i32 nCode = HIWORD(wparam);
          if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+e_message_command), nullptr, nullptr))
          {
          if (pResult != nullptr)
          *pResult = 1;
          return true;
          } */
      }
      break;

      // special case for WM_NOTIFY
      /*      case WM_NOTIFY:
       {
       // reflect the message through the message ::collection::map as OCM_NOTIFY
       NMHDR* pNMHDR = (NMHDR*)lparam;
       //            i32 nCode = pNMHDR->code;
       //            __NOTIFY notify;
       //          notify.pResult = pResult;
       //        notify.pNMHDR = pNMHDR;
       // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
       }

       // other special cases (WM_CTLCOLOR family)*/
      default:
         if (uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
         {
            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
            /*__CTLCOLOR ctl;
             ctl.hDC = (HDC)wparam;
             ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
             //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
             ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);

             // reflect the message through the message ::collection::map as OCM_CTLCOLOR
             bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
             if ((HBRUSH)*pResult == nullptr)
             bResult = false;
             return bResult;*/
            return false;
         }
         break;
      }

      return false;   // let the parent handle it
   }

   void interaction_impl::OnParentNotify(const ::atom & atom, lparam lparam)
   {
      if ((LOWORD(message) == e_message_create || LOWORD(message) == e_message_destroy))
      {
         if (ReflectLastMsg((oswindow)lparam))
            return;     // eat it
      }
      // not handled - do default
      //Default();
   }

   void interaction_impl::OnSetFocus(::user::interaction *)
   {
      bool bHandled;

//      bHandled = false;
//      if( !bHandled )
//      {
//         Default();
//      }
   }


   LRESULT interaction_impl::OnActivateTopLevel(wparam wparam, LPARAM)
   {

      return 0;

   }

   void interaction_impl::OnSysColorChange()
   {
      throw ::not_implemented();

      /*      application* pApp = System;
       if (pApp != nullptr && pApp->GetMainWnd() == this)
       {
       // recolor global brushes used by control bars
       ::windows_definition::Data.UpdateSysColors();
       }

       // forward this message to all other child windows
       if (!(GetStyle() & WS_CHILD))
       send_message_to_descendants(WM_SYSCOLORCHANGE, 0, 0L, true, true);

       Default();*/
   }

   bool gen_GotScrollLines;

   void interaction_impl::OnSettingChange(::u32 uFlags, const ::string & lpszSection)
   {
      //      UNUSED_ALWAYS(uFlags);
      //    UNUSED_ALWAYS(lpszSection);

      // force refresh of settings that we cache
      gen_GotScrollLines = false;


      interaction_impl::OnDisplayChange(0, 0);    // to update system metrics, etc.
   }

   /*   void interaction_impl::OnDevModeChange(__in char * lpDeviceName)
    {
    __UNREFERENCED_PARAMETER(lpDeviceName);
    throw ::not_implemented();
    application* pApp = System;
    if (pApp != nullptr && pApp->GetMainWnd() == this)
    pApp->DevModeChange(lpDeviceName);

    // forward this message to all other child windows
    if (!(GetStyle() & WS_CHILD))
    {
    const MESSAGE* pMsg = GetCurrentMessage();
    send_message_to_descendants(pMsg->message, pMsg->wparam, pMsg->lparam,
    true, true);
    }*/
   //}


   //
   //   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   //   {
   //      if (!(GetStyle() & WS_CHILD))
   //      {
   //         ::user::interaction* pMainWnd = psystem->GetMainWnd();
   //         if (pMainWnd != nullptr &&
   //            GetKeyState(VK_SHIFT) >= 0 &&
   //            GetKeyState(VK_CONTROL) >= 0 &&
   //            GetKeyState(VK_MENU) >= 0)
   //         {
   //            //            pMainWnd->SendMessage(e_message_command, ID_HELP);
   //            return true;
   //         }
   //      }
   //      return Default() != 0;
   //   }
   //
   LRESULT interaction_impl::OnDisplayChange(WPARAM, LPARAM)
   {
      if (!(GetStyle() & WS_CHILD))
      {
         const MESSAGE* pMsg = GetCurrentMessage();
         send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam, true, true);
      }
      return 0;
      //return Default();
   }

   LRESULT interaction_impl::OnDragList(WPARAM, lparam lparam)
   {

      throw ::not_implemented();
      //
      //      LPDRAGLISTINFO lpInfo = (LPDRAGLISTINFO)lparam;
      //      ASSERT(lpInfo != nullptr);
      //
      //      LRESULT lResult;
      //      if (ReflectLastMsg(lpInfo->hWnd, &lResult))
      //         return (i32)lResult;    // eat it
      //
      //      // not handled - do default
      //      return (i32)Default();
   }


//   void interaction_impl::prodevian_task()
//   {
//
//      ::user::interaction_impl::prodevian_task();
//
////      if (m_pthreadProDevian.is_null())
////      {
////
////         m_pthreadProDevian = fork([&]()
////                                   {
////
////                                      ::u32 tickStart;
////
////                                      bool bUpdateScreen = false;
////
////                                      while (::task_get_run())
////                                      {
////
////                                         try
////                                         {
////
//// auto tickStart = ::time::now();
////
////                                            if(m_puserinteraction == nullptr)
////                                            {
////
////                                               break;
////
////                                            }
////
//////                                            if(m_oswindow != nullptr)
//////                                            {
//////
//////                                               m_oswindow->m_bNsWindowRect = false;
//////
//////                                            }
////
////                                            if (!m_puserinteraction->m_bLockWindowUpdate)
////                                            {
////
////                                               bool bUpdateBuffer =
////                                               m_puserinteraction->m_bProDevian ||
////                                               m_puserinteraction->check_need_layout()||
////                                               m_puserinteraction->check_need_zorder() ||
////                                               m_puserinteraction->check_show_flags();
////
////                                               if(bUpdateBuffer)
////                                               {
////
////                                               }
////                                               else if(m_puserinteraction->is_window_visible())
////                                               {
////
////                                                  bUpdateBuffer = m_puserinteraction->has_pending_graphical_update();
////
////                                               }
////
////                                               if(bUpdateBuffer)
////                                               {
////
////                                                  _001UpdateBuffer();
////
////                                                  if(m_puserinteraction == nullptr)
////                                                  {
////
////                                                     break;
////
////                                                  }
////
////                                                  m_puserinteraction->on_after_graphical_update();
////
////                                                  bUpdateScreen = true;
////
////                                               }
////
////                                            }
////
////                                            if(bUpdateScreen)
////                                            {
////
////                                               u64 now = get_nanos();
////
////                                               u64 delta1 = now - m_uiLastUpdateBeg;
////
////                                               i64 delta2 = (i64) m_uiLastUpdateBeg - (i64) m_uiLastUpdateEnd;
////
////                                               u64 frameNanos = 1000000000LL / m_frequencyFramesPerSecond;
////
////                                               if(delta1 < frameNanos || (delta2 > 0 && delta2 < 10000000000LL))
////                                               {
////
////                                                  output_debug_string("opt_out set need redraw");
////
////                                               }
////                                               else
////                                               {
////
////                                                  bUpdateScreen = false;
////
////                                                  _001UpdateScreen();
////
////                                               }
////
////                                            }
////
////                                            ::u32 dwSpan = tickStart.elapsed();
////
////                                            if (dwSpan < 50)
////                                            {
////
////                                               sleep(50 - dwSpan);
////
////                                            }
////
////                                         }
////                                         catch(...)
////                                         {
////
////                                            break;
////
////                                         }
////
////                                      }
////
////                                      output_debug_string("m_pthreadDraw has finished!");
////
////                                   });
////
////      }
//
//
////   if(m_pthreadProDevian.is_null())
////   {
////
////      m_pthreadProDevian = m_puserinteraction->fork([&]()
////                                       {
////
////                                          ::u32 tickStart;
////
////                                          bool bUpdateScreen = false;
////
////                                          while (::task_get_run())
////                                          {
////
////                                             try
////                                             {
////
//// auto tickStart = ::time::now();
////
////                                                if(m_puserinteraction == nullptr)
////                                                {
////
////                                                   break;
////
////                                                }
////
////                                                if (!m_puserinteraction->m_bLockWindowUpdate)
////                                                {
////
////                                                   bool bUpdateBuffer = m_puserinteraction->check_need_layout()
////                                                   || m_puserinteraction->check_need_zorder() || m_puserinteraction->check_show_flags();
////
////                                                   if(bUpdateBuffer)
////                                                   {
////
////                                                   }
////                                                   else if(m_puserinteraction->is_window_visible())
////                                                   {
////
////                                                      bUpdateBuffer = m_puserinteraction->has_pending_graphical_update();
////
////                                                   }
////
////                                                   if(bUpdateBuffer)
////                                                   {
////
////                                                      _001UpdateBuffer();
////
////                                                      m_puserinteraction->on_after_graphical_update();
////
////                                                      bUpdateScreen = true;
////
////                                                   }
////
////                                                }
////
////                                                if(bUpdateScreen)
////                                                {
////
////                                                   bUpdateScreen = false;
////
////                                                   _001UpdateScreen();
////
////                                                }
////
////                                                ::u32 dwSpan = tickStart.elapsed();
////
////                                                if (dwSpan < 20)
////                                                {
////
////                                                   sleep(20 - dwSpan);
////
////                                                }
////
////                                             }
////                                             catch(...)
////                                             {
////
////                                                break;
////
////                                             }
////
////                                          }
////
////                                          output_debug_string("m_pthreadDraw has finished!");
////
////                                          m_pthreadProDevian.release();
////
////                                          //release_graphics_resources();
////
////
////                                       });
////
////   }
//
//   }


   void interaction_impl::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //Default();

      //{
      // SetTimer(2049, 184, nullptr);
      //}


      if(m_puserinteraction->is_message_only_window())
      {

         TRACE("good : opt out!");

      }
      else
      {

      }

   }


   void interaction_impl::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
   
   }


   void interaction_impl::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction_impl::_001OnTimer(ptimer);;

//      if(ptimer->m_uEvent == 2049)
//      {
//
//         set_need_redraw();
//
//      }

   }


//   void interaction_impl::set_need_redraw()
//   {

   //set_need_redraw();

//   }


//   bool interaction_impl::round_window_key_down(::user::enum_key ekey)
//   {
//
//      return false;
//
//   }


//   bool interaction_impl::round_window_key_up(::user::enum_key ekey)
//   {
//
//      return false;
//
//   }


//   bool interaction_impl::round_window_on_text(const ::string & pszText)
//   {
//
//      return false;
//
//   }

   /*


    void interaction_impl::OnHScroll(::u32, ::u32, CScrollBar* pScrollBar)
    {
    __UNREFERENCED_PARAMETER(pScrollBar);
    Default();
    }

    void interaction_impl::OnVScroll(::u32, ::u32, CScrollBar* pScrollBar)
    {
    __UNREFERENCED_PARAMETER(pScrollBar);
    Default();
    }
    */
   bool CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow hwnd, lparam lparam)
   {
      user::oswindow_array * phwnda = (user::oswindow_array *) lparam;
      phwnda->add(hwnd);
      return true;
   }

   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   {
      throw ::not_implemented();
      //      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
   }


   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

//      ::rectangle_i32 rectangleClient;
//
//      client_rectangle(rectangleClient);
//
//      ::rectangle_i32 rectangleUpdate;
//      
//      window_rectangle(rectangleUpdate);
//      
//      ::rectangle_i32 rectanglePaint;
//      
//      rectanglePaint = rectangleUpdate;
//      
//      screen_to_client(rectanglePaint);
//      
//      user::oswindow_array wndaApp;
//
//      throw ::not_implemented();
      
   }


   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
   {
      
      __UNREFERENCED_PARAMETER(pmessage);
      
   }


   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {

      //lock lock(m_puserinteraction, 2000);

      throw ::not_implemented();

   }


   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {
      throw ::not_implemented();
      //      ::pointer<::user::message>pusermessage(pmessage);
      //
      //      if(pusermessage->m_wparam == nullptr)
      //         return;
      //
      //      ::draw2d::graphics_pointer graphics(this);
      //      WIN_DC(graphics.m_p)->Attach((HDC) pusermessage->m_wparam);
      //      ::rectangle_i32 rectx;
      //      ::draw2d::bitmap * pbitmap = &pgraphics->GetCurrentBitmap();
      //      ::GetCurrentObject((HDC) pusermessage->m_wparam, OBJ_BITMAP);
      //      //      ::u32 dw = ::get_last_error();
      //      ::size_i32 size = pbitmap->get_size();
      //      rectx.left = 0;
      //      rectx.top = 0;
      //      rectx.right = size.cx;
      //      rectx.bottom = size.cy;
      //      try
      //      {
      //         ::rectangle_i32 rectangleWindow;
      //         window_rectangle(rectangleWindow);
      //
      //         ::image_pointer pimage(this);
      //         if(!pimage = create_image(rectangleWindow.bottom_right()))
      //            return;
      //
      //         ::draw2d::graphics_pointer & pgraphics = pimage->get_graphics();
      //
      //         if(pgraphics->get_handle() == nullptr)
      //            return;
      //
      //         ::rectangle_i32 rectanglePaint;
      //         ::rectangle_i32 rectangleUpdate;
      //         rectangleUpdate = rectangleWindow;
      //         rectanglePaint = rectangleWindow;
      //         rectanglePaint.offset(-rectanglePaint.top_left());
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         if(m_puserinteraction != nullptr && m_puserinteraction != this)
      //         {
      //            m_puserinteraction->_001OnDeferPaintLayeredWindowBackground(pgraphics);
      //         }
      //         else
      //         {
      //            _001OnDeferPaintLayeredWindowBackground(pgraphics);
      //         }
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->set_origin(::point_i32());
      //         _000OnDraw(pgraphics);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->set_origin(::point_i32());
      //         //(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->FillSolidRect(rectangleUpdate.left, rectangleUpdate.top, 100, 100, 255);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->set_origin(::point_i32());
      //
      //         pgraphics->SelectClipRgn( nullptr);
      //         pgraphics->BitBlt(rectanglePaint.left, rectanglePaint.top,
      //            rectanglePaint.width(), rectanglePaint.height(),
      //            pgraphics, rectangleUpdate.left, rectangleUpdate.top,
      //            SRCCOPY);
      //
      //         pgraphics->text_out(0, 0, "Te Amo Carlinhos!!", 11);
      //      }
      //      catch(...)
      //      {
      //      }
      //      pgraphics->FillSolidRect(rectx, rgb(255, 255, 255));
      //      WIN_DC(graphics.m_p)->Detach();
      //      pmessage->m_bRet = true;
      //      pusermessage->set_lresult(0);
   }


   void interaction_impl::OnEnterIdle(::u32 /*nWhy*/, ::user::interaction * /*pWho*/)
   {
      // In some OLE inplace active scenarios, OLE will post a
      // message instead of sending it.  This causes so many WM_ENTERIDLE
      // messages to be sent that tasks running in the background stop
      // running.  By dispatching the pending WM_ENTERIDLE messages
      // when the first one is received, we trick oswindows into thinking
      // that only one was really sent and dispatched.
      {
         //         MESSAGE msg;
         throw ::not_implemented();
         //while (PeekMessage(&msg, nullptr, WM_ENTERIDLE, WM_ENTERIDLE, PM_REMOVE))
         //while (PeekMessage(&msg, ::caNULL, WM_ENTERIDLE, WM_ENTERIDLE, true))
         // DispatchMessage(&msg);
      }

      //Default();
   }

   HBRUSH interaction_impl::OnCtlColor(::draw2d::graphics *, ::user::interaction * pWnd, ::u32)
   {
      ASSERT(pWnd != nullptr && get_handle() != nullptr);
      LRESULT lResult;
//      if (IOS_WINDOW(pWnd)->SendChildNotifyLastMsg(&lResult))
      //       return (HBRUSH)lResult;     // eat it
      //return (HBRUSH)Default();
      return nullptr;
   }

   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any user::interaction containing controls)
   //  return value of false means caller must call DefWindowProc's default
   //  true means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
   bool PASCAL interaction_impl::GrayCtlColor(HDC hDC, oswindow hWnd, ::u32 nCtlColor,
         HBRUSH hbrGray, color32_t clrText)
   {
      throw ::not_implemented();
      //      if (hDC == nullptr)
      //      {
      //         // sometimes Win32 passes a nullptr hDC in the WM_CTLCOLOR message.
      //         //         TRACE(::ca2::trace::category_AppMsg, 0, "Warning: hDC is nullptr in interaction_impl::GrayCtlColor; WM_CTLCOLOR not processed.\n");
      //         return false;
      //      }
      //
      //      if (hbrGray == nullptr ||
      //         nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX ||
      //         nCtlColor == CTLCOLOR_SCROLLBAR)
      //      {
      //         return false;
      //      }
      //
      //      if (nCtlColor == CTLCOLOR_LISTBOX)
      //      {
      //         // only handle requests to draw the space between edit and drop button
      //         //  in a drop-down combo (not a drop-down list)
      //         if (!__is_combo_box_control(hWnd, (::u32)CBS_DROPDOWN))
      //            return false;
      //      }
      //
      //      // set background color and return handle to brush
      //      LOGBRUSH logbrush;
      //      VERIFY(::GetObject(hbrGray, sizeof(LOGBRUSH), (LPVOID)&logbrush));
      //      ::SetBkColor(hDC, logbrush.lbColor);
      //      if (clrText == (color32_t)-1)
      //         clrText = ::GetSysColor(COLOR_WINDOWTEXT);  // normal text
      //      ::SetTextColor(hDC, clrText);
      //      return true;
   }



   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child user::interaction)

   void interaction_impl::CenterWindow(::user::interaction *  pAlternateOwner)
   {
      throw ::not_implemented();
   }

   bool interaction_impl::CheckAutoCenter()
   {
      return true;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const ::string & lpszResourceName)
   {
      // find resource handle
      LPVOID lpResource = nullptr;
      HGLOBAL hResource = nullptr;
      if (lpszResourceName != nullptr)
      {
         //         HINSTANCE hInst = ::ca2::FindResourceHandle(lpszResourceName, RT_DLGINIT);
         //       HRSRC hDlgInit = ::FindResource(hInst, lpszResourceName, RT_DLGINIT);
         /*     if (hDlgInit != nullptr)
          {
          // load it
          hResource = LoadResource(hInst, hDlgInit);
          if (hResource == nullptr)
          return false;
          // lock it
          lpResource = LockResource(hResource);
          ASSERT(lpResource != nullptr);
          }*/
      }

      // execute it
      bool bResult = ExecuteDlgInit(lpResource);

      // cleanup
      if (lpResource != nullptr && hResource != nullptr)
      {
         throw ::not_implemented();
      }
      return bResult;
   }


   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {

      throw ::not_implemented();

   }


   void interaction_impl::UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler)
   {
      __UNREFERENCED_PARAMETER(pTarget);
      __UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      //::message::command state(this);
      //user::interaction wndTemp;       // very temporary user::interaction just for CmdUI update

   }


   bool interaction_impl::IsFrameWnd()
   {

      return false;

   }


   bool interaction_impl::SubclassWindow(oswindow hWnd)
   {
      if (!Attach(hWnd))
         return false;

      // allow any other subclassing to occur
      pre_subclass_window();

      throw ::not_implemented();

   }


   oswindow interaction_impl::UnsubclassWindow()
   {

      ASSERT(::is_window(get_handle()));

      throw ::not_implemented();

   }


//   bool interaction_impl::IsChild(::user::interaction *  pWnd)
//   {
//      ASSERT(::is_window(get_handle()));
//      if(get_handle() == nullptr)
//      {
//         return ::user::interaction_impl::IsChild(pWnd);
//      }
//      else
//      {
//         //         return ::IsChild(get_handle(), IOS_WINDOW(pWnd)->get_handle()) != false;
//         return false;
//      }
//   }


//   bool interaction_impl::is_window() const
//   {
//
//      return ::is_window(m_oswindow) != false;
//
//   }


   ::user::interaction * interaction_impl::get_wnd() const
   {

      return m_puserinteraction;

   }

//
//   void interaction_impl::MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight, bool bRepaint)
//   {
//
//      ASSERT(::is_window(get_handle()));
//
//      set_window_position(0, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);
//
//   }


//   bool interaction_impl::client_to_screen(RECTANGLE_I32 * lprect)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      lprect->left   += (::i32) rectangleWindow.left;
//      lprect->right  += (::i32) rectangleWindow.left;
//      lprect->top    += (::i32) rectangleWindow.top;
//      lprect->bottom += (::i32) rectangleWindow.top;
//
//      return true;
//
//   }


//   bool interaction_impl::client_to_screen(POINT_I32 * lppoint)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      lppoint->x     += (::i32) rectangleWindow.left;
//      lppoint->y     += (::i32) rectangleWindow.top;
//
//      return true;
//
//   }
//
//
//   bool interaction_impl::client_to_screen(RECTANGLE_I64 * lprect)
//   {
//
//      ::rectangle_i32 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      lprect->left   += rectangleWindow.left;
//      lprect->right  += rectangleWindow.left;
//      lprect->top    += rectangleWindow.top;
//      lprect->bottom += rectangleWindow.top;
//
//      return true;
//
//   }


//   bool interaction_impl::client_to_screen(POINT_I64 * lppoint)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//      }
//
//      lppoint->x     += rectangleWindow.left;
//      lppoint->y     += rectangleWindow.top;
//
//      return true;
//
//   }
//
//
//   bool interaction_impl::screen_to_client(RECTANGLE_I32 * lprect)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      lprect->left   -= (::i32) rectangleWindow.left;
//      lprect->right  -= (::i32) rectangleWindow.left;
//      lprect->top    -= (::i32) rectangleWindow.top;
//      lprect->bottom -= (::i32) rectangleWindow.top;
//
//      return true;
//
//   }


//   bool interaction_impl::screen_to_client(POINT_I32 * lppoint)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      lppoint->x     -= (::i32) rectangleWindow.left;
//      lppoint->y     -= (::i32) rectangleWindow.top;
//
//
//      return true;
//
//   }
//
//
//   bool interaction_impl::screen_to_client(RECTANGLE_I64 * lprect)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//
//      lprect->left   -= rectangleWindow.left;
//      lprect->right  -= rectangleWindow.left;
//      lprect->top    -= rectangleWindow.top;
//      lprect->bottom -= rectangleWindow.top;
//
//      return true;
//
//   }
//
//   bool interaction_impl::screen_to_client(POINT_I64 * lppoint)
//   {
//
//      ::rectangle_i64 rectangleWindow;
//
//      if(!m_puserinteraction->window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      lppoint->x     -= rectangleWindow.left;
//      lppoint->y     -= rectangleWindow.top;
//
//      return true;
//
//   }


//   bool interaction_impl::window_rectangle(RECTANGLE_I64 * lprect)
//   {
//      //      if(!::is_window(get_handle()))
//      //       throw ::exception(::exception("no more a user::interaction"));
//      if(!::is_window(get_handle()))
//      {
//
//         return false;
//
//      }
//
//      return ::user::interaction_impl::window_rectangle(lprect);
//
//      // if it is temporary user::interaction - probably not ca2 wrapped user::interaction
//
////      ::rectangle_i32 rect32;
////
////      if(m_puserinteraction == get_app()->acmesystem()->m_possystemwindow->m_puserinteraction)
////      {
////
////         if(!get_main_screen_rectangle(rect32))
////         {
////
////            return false;
////
////         }
////
////      }
////      else
////      {
////
////         if(!::window_rectangle(get_handle(), rect32))
////         {
////
////            return false;
////
////         }
////
////      }
////
////      ::copy(lprect, rect32);
////
////      return true;
//
//   }

//   bool interaction_impl::client_rectangle(RECTANGLE_I64 * lprect)
//   {
//
//      if(!::is_window(get_handle()))
//         return false;
//
////      ASSERT(::is_window(get_handle()));
//
//      ::rectangle_i32 rect32;
//
//      if(m_puserinteraction == get_app()->acmesystem()->m_possystemwindow->m_puserinteraction)
//      {
//
//         if(!get_main_screen_rectangle(rect32))
//         {
//
//            return false;
//
//         }
//
//      }
//      else
//      {
//
//         if(!::window_rectangle(get_handle(), rect32))
//         {
//
//            return false;
//
//         }
//
//      }
//
//      ::copy(lprect, rect32);
//
//      lprect->top += 16;
//
//      return true;
//
//   }


   atom interaction_impl::SetDlgCtrlId(atom atom)
   {

      return m_puserinteraction->SetDlgCtrlId((atom));

   }


   atom interaction_impl::GetDlgCtrlId()
   {

      return m_puserinteraction->GetDlgCtrlId();

   }


//   void interaction_impl::_001WindowMaximize()
//   {
//      ::user::interaction_impl::_001WindowMaximize();
//   }

//   void interaction_impl::_001WindowRestore()
//   {
//      m_puserinteraction->m_edisplay = user::e_display_restored;
//      if(m_puserinteraction != nullptr)
//         m_puserinteraction->m_edisplay = user::e_display_restored;
//      //      ::ShowWindow(get_handle(), SW_RESTORE);
//   }


   bool interaction_impl::ShowWindow(i32 nCmdShow)
   {

      if(!::is_window(m_oswindow))
      {

         return false;

      }

      bool bOk = m_oswindow->show_window(nCmdShow);
      
      return bOk;

   }


//   bool interaction_impl::layout().is_iconic()
//   {
//      ASSERT(::is_window(get_handle()));
//      if(GetExStyle() & WS_EX_LAYERED)
//      {
//         return m_puserinteraction->m_edisplay == user::e_display_iconic;
//      }
//      else
//      {
//         return ::IsIconic(get_handle()) != false;
//      }
//   }

   
   ::user::interaction * interaction_impl::get_parent() const
   {
      return nullptr;
      //      if(!::is_window(get_handle()))
      //       return nullptr;
      //  if(get_handle() == nullptr)
      //   return nullptr;
      // return ::macos::interaction_impl::from_handle(::get_parent(get_handle()));
   }


   ::i32 interaction_impl::GetWindowLong(i32 nIndex)
   {

      return ::GetWindowLong(get_handle(), nIndex);

   }


   ::i32 interaction_impl::SetWindowLong(i32 nIndex, ::i32 lValue)
   {

      return ::SetWindowLong(get_handle(), nIndex, lValue);

   }


   /*


      ::u32 interaction_impl::GetStyle() const
      {
         ASSERT(::is_window(get_handle()));
         return (::u32)::GetWindowLong(get_handle(), GWL_STYLE);
      }

      ::u32 interaction_impl::GetExStyle() const
      {
         ASSERT(::is_window(get_handle()));
         return (::u32)::GetWindowLong(get_handle(), GWL_EXSTYLE);
      }

      bool interaction_impl::ModifyStyle(::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags)
      {
         ASSERT(::is_window(get_handle()));
         return ModifyStyle(get_handle(), dwRemove, dwAdd, nFlags);
      }

      bool interaction_impl::ModifyStyleEx(::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags)
      {
         ASSERT(::is_window(get_handle()));
         return ModifyStyleEx(get_handle(), dwRemove, dwAdd, nFlags);
      }
   */

   ::user::interaction *  interaction_impl::SetOwner(::user::interaction *  pOwnerWnd)
   {
      //      m_puiOwner = pOwnerWnd;
      return nullptr;
   }

//   LRESULT interaction_impl::send_message(const ::atom & atom, wparam wparam, lparam lparam)
//   {
//
//      return ::user::interaction_impl::send_message(message, wparam, lparam);
//
//      //      ::pointer<::user::message> spbase;
//
//      //    spbase = get_base(message, wparam, lparam);
//
//      /*      try
//       {
//       ::user::interaction * pinteraction = m_puserinteraction;
//       while(pinteraction != nullptr)
//       {
//       try
//       {
//       pinteraction->pre_translate_message(spbase);
//       }
//       catch(...)
//       {
//       break;
//       }
//       if(spbase->m_bRet)
//       return spbase->get_lresult();
//       try
//       {
//       pinteraction = pinteraction->get_parent();
//       }
//       catch(...)
//       {
//       break;
//       }
//       }
//       }
//       catch(...)
//       {
//       }*/
//      //      message_handler(spbase);
//      //    return spbase->get_lresult();
//
//      //throw ::exception(todo);
//
//      ////ASSERT(::is_window(get_handle()));
//      //return ::SendMessage(get_handle(), message, wParam, lParam);
//   }

//   bool interaction_impl::post_message(const ::atom & atom, wparam wparam, lparam lparam)
//   {
//      if(get_app() != nullptr)
//      {
//         return get_app()->post_message(m_puserinteraction, message, wparam, lparam);
//      }
//      else
//      {
//         return false;
//      }
//   }
//
//   bool interaction_impl::DragDetect(POINT_I32 point_i32) const
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window(get_handle()));
//
//      //return ::DragDetect(get_handle(), point_i32) != false;
//
//   }


   void interaction_impl::set_window_text(const ::string & lpszString)
   {

      m_strWindowText = lpszString;

   }

   /*
   strsize interaction_impl::get_window_text(char * lpszString, strsize nMaxCount)
   {

      strncpy(lpszString, m_strWindowText, nMaxCount);

      return minimum(nMaxCount, m_strWindowText.length());

   }

   strsize interaction_impl::get_window_text_length()()
   {

      return m_strWindowText.length();

   }

   */



   /*

    void interaction_impl::SetFont(::write_text::font* pfont, bool bRedraw)
    {
    __UNREFERENCED_PARAMETER(bRedraw);
    ASSERT(::is_window(get_handle())); m_pfont = memory_new ::write_text::font(*pfont);
    }

    ::write_text::font* interaction_impl::GetFont()
    {
    ASSERT(::is_window(get_handle()));
    return m_pfont;
    }

    */

   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      throw ::not_implemented();

      //ASSERT(::is_window(get_handle()));
      //::DragAcceptFiles(get_handle(), bAccept);

   }

   /*

    ::pointer<::user::frame_window>interaction_impl::EnsureParentFrame()
    {
    ::user::frame_window * pFrameWnd=get_parent_frame();
    ENSURE_VALID(pFrameWnd);
    return pFrameWnd;

    }


    ::user::interaction *  interaction_impl::EnsureTopLevelParent()
    {

    ::user::interaction * pWnd = GetTopLevelParent();

    ENSURE_VALID(pWnd);

    return pWnd;

    }

    */

//   void interaction_impl::MoveWindow(const ::rectangle_i32 & rectangle, bool bRepaint)
//   {
//      MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
//   }

   ::u32 interaction_impl::ArrangeIconicWindows()
   {
      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle())); return ::ArrangeIconicWindows(get_handle());
   }

   i32 interaction_impl::SetWindowRgn(HRGN hRgn, bool bRedraw)
   {
      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle())); return ::SetWindowRgn(get_handle(), hRgn, bRedraw);
   }

   i32 interaction_impl::GetWindowRgn(HRGN hRgn)
   {
      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()) && hRgn != nullptr); return ::GetWindowRgn(get_handle(), hRgn);
   }

//
//   void interaction_impl::bring_to_top(::e_display edisplay)
//   {
//
//      if(nCmdShow > SW_HIDE && nCmdShow != SW_MINIMIZE)
//      {
//
//         BringWindowToTop();
//
//         round_window_show();
//
//      }
//
//   }


//   bool interaction_impl::BringWindowToTop()
//   {
//
//      bool b = ::BringWindowToTop(get_handle()) != false;
//
//      return b;
//
//   }


   void interaction_impl::MapWindowPoints(::user::interaction * puserinteractionTo, POINT_I32 * lpPoint, ::u32 nCount)
   {
      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::MapWindowPoints(get_handle(), (oswindow) puserinteractionTo->get_handle(), lpPoint, nCount);
   }

   void interaction_impl::MapWindowPoints(::user::interaction * puserinteractionTo, RECTANGLE_I32 * lpRect)
   {
      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::MapWindowPoints(get_handle(), (oswindow) puserinteractionTo->get_handle(), (POINT_I32 *)lpRect, 2);
   }

   ::draw2d::graphics * interaction_impl::GetDC()
   {
      ::draw2d::graphics_pointer g(e_create);
      oswindow oswindow;
      if(get_handle() == nullptr)
      {
         //         oswindow = ::get_desktop_window();

      }
      else
      {
         oswindow = (::oswindow) get_handle();
      }
      ::rectangle_i32 rectangleClient;
      //oswindow.client_rectangle(rectangleClient);
      rectangleClient.left = 0;
      rectangleClient.top = 0;
      rectangleClient.right = 500;
      rectangleClient.bottom = 500;
      //      (dynamic_cast < ::draw2d_quartz2d::graphics * >(g.m_p))->attach(cairo_create(cairo_xlib_surface_create(oswindow.display(), oswindow.user::interaction(), DefaultVisual(oswindow.display(), 0), rectangleClient.width(), rectangleClient.height())));
      return g.detach();
   }

   ::draw2d::graphics * interaction_impl::GetWindowDC()
   {
      //ASSERT(::is_window(get_handle()));
      //::draw2d::graphics_pointer g(e_create);
      //g->attach(::GetWindowDC(get_handle()));
      //return g.detach();

      return nullptr;

   }

   bool interaction_impl::ReleaseDC(::draw2d::graphics_pointer & pgraphics)
   {

      if(pgraphics == nullptr)
         return false;

      //      cairo_t * pcairo = (cairo_t *) pgraphics->get_handle();
      //
      //      cairo_surface_t * psurface = cairo_get_target(pcairo);
      //
      //      cairo_destroy(pcairo);
      //
      //      cairo_surface_destroy(psurface);

      //      if(((Gdiplus::Graphics *)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle()) == nullptr)
      //       return false;

      //::ReleaseDC(get_handle(), (dynamic_cast < ::draw2d_quartz2d::graphics * > (pgraphics))->detach());

      //      (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->m_hdc = nullptr;

      //      pgraphics->release();

      return true;

   }

   void interaction_impl::UpdateWindow()
   {
      throw ::not_implemented();
      //::UpdateWindow(get_handle());
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
   }

   bool interaction_impl::GetUpdateRect(RECTANGLE_I32 * lpRect, bool bErase)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //return ::GetUpdateRect(get_handle(), lpRect, bErase) != false;
   }

   i32 interaction_impl::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
   }

   void interaction_impl::Invalidate(bool bErase)
   {
      m_bNeedsUpdate = true;
      //      round_window_invalidate();
      //      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::InvalidateRect(get_handle(), nullptr, bErase);
   }

   void interaction_impl::InvalidateRect(const ::rectangle_i32 & rectangle, bool bErase)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::InvalidateRect(get_handle(), lpRect, bErase);
   }

   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
   }

   void interaction_impl::ValidateRect(const ::rectangle_i32 & rectangle)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::ValidateRect(get_handle(), lpRect);
   }

   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {
      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::ValidateRgn(get_handle(), (HRGN)pRgn->get_handle());
   }

//   bool interaction_impl::is_window_visible()
//   {
//
//      if(!::is_window(get_handle()))
//         return false;
//
//      if(m_puserinteraction != nullptr)
//      {
//
//         if(!m_puserinteraction->is_this_visible())
//            return false;
//
//         if(m_puserinteraction->get_parent() != nullptr && !m_puserinteraction->get_parent()->is_window_visible())
//            return false;
//
//      }
//
//      if(!::IsWindowVisible(get_handle()))
//         return false;
//
//      return true;
//
//   }


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::ShowOwnedPopups(get_handle(), bShow);

   }

//   void interaction_impl::send_message_to_descendants(const ::atom & atom, wparam wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
//   {
//      ASSERT(::is_window(get_handle()));
//      //interaction_impl::send_message_to_descendants(get_handle(), message, wparam, lparam, bDeep, bOnlyPerm);
//
//      // walk through oswindows to avoid creating temporary user::interaction objects
//      // unless we need to call this function recursively
//      user::interaction * pinteraction = m_puserinteraction->top_child();
//      while(pinteraction != nullptr)
//      {
//         try
//         {
//            pinteraction->send_message(message, wparam, lparam);
//         }
//         catch(...)
//         {
//         }
//         if (bDeep)
//         {
//            // send to child windows after parent
//            try
//            {
//               pinteraction->send_message_to_descendants(message, wparam, lparam, bDeep, bOnlyPerm);
//            }
//            catch(...)
//            {
//            }
//         }
//         try
//         {
//            pinteraction = pinteraction->under_sibling();
//         }
//         catch(...)
//         {
//            break;
//         }
//      }
//   }



//   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region* prgnClip, ::u32 flags)
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window(get_handle()));
//      //::draw2d::graphics_pointer g(this);
//      //g->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_handle(), flags));
//      //return g.detach();
//
//   }

   bool interaction_impl::LockWindowUpdate()
   {

      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //return ::LockWindowUpdate(get_handle()) != false;

   }

   void interaction_impl::UnlockWindowUpdate()
   {

      throw ::not_implemented();
      //ASSERT(::is_window(get_handle()));
      //::LockWindowUpdate(nullptr);

   }


//   bool interaction_impl::RedrawWindow(const ::rectangle_i32& rectangleUpdate, ::draw2d::region* prgnUpdate, ::u32 flags)
//   {
//
//      if(flags & RDW_UPDATENOW)
//      {
//
//         //debug_break();
//
//         if(m_bShowFlags)
//         {
//
//            if(!is_window_visible() && (m_iShowFlags & SWP_SHOWWINDOW))
//            {
//
//               round_window_show();
//
//            }
//            else if(is_window_visible() && (m_iShowFlags & SWP_HIDEWINDOW))
//            {
//
//               round_window_hide();
//
//            }
//
//         }
//
//         if (m_rectangleLastPos != m_rectangleParentClientRequest)
//         {
//
//            ::set_window_position(m_oswindow, nullptr,
//                           (int) m_rectangleParentClientRequest.left,
//                           (int) m_rectangleParentClientRequest.top,
//                           (int) m_rectangleParentClientRequest.width(),
//                           (int) m_rectangleParentClientRequest.height(),
//                           SWP_NOZORDER
//                           | SWP_NOREDRAW
//                           | SWP_NOCOPYBITS
//                           | SWP_NOACTIVATE
//                           | SWP_NOOWNERZORDER
//                           | SWP_NOSENDCHANGING
//                           | SWP_DEFERERASE);
//
//            m_rectangleLastPos = m_rectangleParentClientRequest;
//
//         }
//
//         if (is_window_visible())
//         {
//
//            round_window_redraw();
//
//         }
//         else
//         {
//
////            _001UpdateWindow();
//
//         }
//
//
//      }
//      else
//      {
//
//         //debug_break();
//
//         m_puserinteraction->m_bRedraw = true;
//
//      }
//
//      return true;
//
//   }

   /*
    bool interaction_impl::EnableScrollBar(i32 nSBFlags, ::u32 nArrowFlags)
    {

    ASSERT(::is_window(get_handle()));

    return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != false;

    }
    */

//   bool interaction_impl::DrawAnimatedRects(i32 idAni, const RECTANGLE_I32 *lprcFrom, const RECTANGLE_I32 *lprcTo)
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window(get_handle()));
//      //return ::DrawAnimatedRects(get_handle(), idAni, lprcFrom, lprcTo) != false;
//
//   }

//   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 * lprc, ::u32 uFlags)
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window(get_handle()));
//      //return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), lprc, uFlags) != false;
//
//   }

   bool interaction_impl::SetTimer(uptr uEvent, ::u32 nElapse, PFN_TIMER pfnTimer)
   {
      return ::user::interaction_impl::SetTimer(uEvent, nElapse, pfnTimer);
      /*
       __UNREFERENCED_PARAMETER(lpfnTimer);

       m_puserinteraction->get_app()->set_timer(m_puserinteraction, uEvent, nElapse);

       return uEvent;

       //throw ::not_implemented();
       //ASSERT(::is_window(get_handle()));
       //return ::SetTimer(get_handle(), uEvent, nElapse, lpfnTimer);
       //return true;*/

   }

   bool interaction_impl::KillTimer(uptr uEvent)
   {
      return ::user::interaction_impl::KillTimer(uEvent);

      /*
       //throw ::not_implemented();
       //ASSERT(::is_window(get_handle()));
       //return ::KillTimer(get_handle(), uEvent)  != false;

       m_puserinteraction->get_app()->unset_timer(m_puserinteraction, uEvent);


       return true;*/

   }

   bool interaction_impl::IsWindowEnabled()
   {

      return true;

      /*      if(!::is_window(get_handle()))
       return false;

       return ::IsWindowEnabled(get_handle()) != false;
       */

   }


   bool interaction_impl::EnableWindow(bool bEnable)
   {

      /*      ASSERT(::is_window(get_handle()));

       return ::EnableWindow(get_handle(), bEnable) != false;
       */

      return true;

   }

   ::user::interaction *  interaction_impl::GetActiveWindow()
   {

      oswindow oswindow = ::get_active_window();

      if(oswindow == nullptr)
      {

         return nullptr;

      }

      ::user::interaction_impl * pimpl = ::ios::interaction_impl::from_handle(oswindow);

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }

   ::user::interaction *  interaction_impl::SetActiveWindow()
   {

      ASSERT(::is_window(get_handle()));

      oswindow oswindow = ::set_active_window(get_handle());

      if(oswindow == nullptr)
      {

         return nullptr;

      }

      ::user::interaction_impl * pimpl = ::ios::interaction_impl::from_handle(oswindow);

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }





   ::user::interaction *  interaction_impl::GetFocus()
   {

      oswindow oswindow = ::get_focus();

      if(oswindow == nullptr)
      {

         return nullptr;

      }

      ::user::interaction_impl * pimpl = ::ios::interaction_impl::from_handle(oswindow);

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   bool interaction_impl::SetFocus()
   {

      if(!::is_window(get_handle()))
         return nullptr;

      oswindow oswindow = ::set_focus(get_handle());

      if(oswindow == nullptr)
      {

         return nullptr;

      }

      ::user::interaction_impl * pimpl = ::ios::interaction_impl::from_handle(oswindow);

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::user::interaction *  interaction_impl::get_desktop_window()
   {

      return nullptr;

   }


   // Helper for radio buttons
   i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton)
   {

      for (i32 nID = nIDFirstButton; nID <= nIDLastButton; nID++)
      {
         if (IsDlgButtonChecked(nID))
            return nID; // atom that matched
      }
      return 0; // invalid ID
   }

   void interaction_impl::CheckDlgButton(i32 nIDButton, ::u32 nCheck)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::CheckDlgButton(get_handle(), nIDButton, nCheck);

   }

   void interaction_impl::CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);

   }

   i32 interaction_impl::DlgDirList(char * lpPathSpec, i32 nIDListBox, i32 nIDStaticPath, ::u32 nFileType)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::DlgDirList(get_handle(), lpPathSpec, nIDListBox, nIDStaticPath, nFileType);

   }

   i32 interaction_impl::DlgDirListComboBox(char * lpPathSpec, i32 nIDComboBox, i32 nIDStaticPath, ::u32 nFileType)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::DlgDirListComboBox(get_handle(), lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);

   }

   bool interaction_impl::DlgDirSelect(char * lpString, i32 nSize, i32 nIDListBox)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::DlgDirSelectEx(get_handle(), lpString, nSize, nIDListBox) != false;

   }

   bool interaction_impl::DlgDirSelectComboBox(char * lpString, i32 nSize, i32 nIDComboBox)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::DlgDirSelectComboBoxEx(get_handle(), lpString, nSize, nIDComboBox) != false;

   }

   /*
    void interaction_impl::GetDlgItem(atom atom, oswindow* phWnd) const
    {

    ASSERT(::is_window(get_handle()));
    ASSERT(phWnd != nullptr);
    *phWnd = ::GetDlgItem(get_handle(), (i32) atom);

    }
    */

   /*
    ::u32 interaction_impl::GetDlgItemInt(i32 nID, int_bool * lpTrans, bool bSigned) const
    {

    ASSERT(::is_window(get_handle()));

    return ::GetDlgItemInt(get_handle(), nID, lpTrans, bSigned);

    }
    */

   //   i32 interaction_impl::GetDlgItemText(i32 nID, char * lpStr, i32 nMaxCount) const
   //   {
   //
   //      throw ::not_implemented();
   //      ASSERT(::is_window(get_handle())); return ::GetDlgItemText(get_handle(), nID, lpStr, nMaxCount);}

   ::user::interaction * interaction_impl::GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious) const
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::macos::interaction_impl::from_handle(::GetNextDlgGroupItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));

   }

   ::user::interaction * interaction_impl::GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious) const
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::macos::interaction_impl::from_handle(::GetNextDlgTabItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));

   }

   ::u32 interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::IsDlgButtonChecked(get_handle(), nIDButton);

   }

   LPARAM interaction_impl::SendDlgItemMessage(i32 nID, const ::atom & atom, wparam wparam, lparam lparam)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::SendDlgItemMessage(get_handle(), nID, message, wparam, lparam);

   }

   void interaction_impl::SetDlgItemInt(i32 nID, ::u32 nValue, bool bSigned)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);

   }

   void interaction_impl::SetDlgItemText(i32 nID, const ::string & lpszString)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::SetDlgItemText(get_handle(), nID, lpszString);

   }

//   i32 interaction_impl::ScrollWindowEx(i32 Δx, i32 Δy, const ::rectangle_i32 & rectangleScroll, const ::rectangle_i32 & rectangleClip, ::draw2d::region* prgnUpdate, RECTANGLE_I32 * lpRectUpdate, ::u32 flags)
//   {
//
//      throw ::not_implemented();
//      //      ASSERT(::is_window(get_handle()));
//      //      return ::ScrollWindowEx(get_handle(), Δx, Δy, lpRectScroll, lpRectClip, (HRGN)prgnUpdate->get_handle(), lpRectUpdate, flags);
//
//   }

   void interaction_impl::ShowScrollBar(::u32 nBar, bool bShow)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::ShowScrollBar(get_handle(), nBar, bShow);

   }

//   ::user::interaction *  interaction_impl::ChildWindowFromPoint(POINT_I32 point_i32)
//   {
//
//
//      throw ::not_implemented();
//      //      ASSERT(::is_window(get_handle()));
//      //      return ::macos::interaction_impl::from_handle(::ChildWindowFromPoint(get_handle(), point_i32));
//
//   }

//   ::user::interaction *  interaction_impl::ChildWindowFromPoint(POINT_I32 point, ::u32 nFlags)
//   {
//
//      throw ::not_implemented();
//      //      ASSERT(::is_window(get_handle()));
//      //      return ::macos::interaction_impl::from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));
//
//   }



   ::user::interaction *  interaction_impl::GetNextWindow(::u32 nFlag)
   {

      return nullptr;

   }

   ::user::interaction *  interaction_impl::GetTopWindow()
   {

      if(m_puserinteraction->m_uiptraChild.get_size() <= 0)
         return nullptr;

      return m_puserinteraction->m_uiptraChild[0];

   }

   ::user::interaction *  interaction_impl::GetWindow(::u32 nCmd)
   {

      ASSERT(::is_window(get_handle()));
      //      return ::macos::interaction_impl::from_handle(::GetWindow(get_handle(), nCmd));
      return nullptr;

   }

   ::user::interaction *  interaction_impl::GetLastActivePopup()
   {


      throw ::exception(todo);
      //      ASSERT(::is_window(get_handle()));
      //      return ::macos::interaction_impl::from_handle(::GetLastActivePopup(get_handle()));

   }

   ::user::interaction * interaction_impl::SetParent(::user::interaction * pWndNewParent)
   {

      ASSERT(::is_window(get_handle()));
      return from_handle(::SetParent(get_handle(), (oswindow) pWndNewParent->get_handle()))->m_puserinteraction;

   }

   ::user::interaction * PASCAL interaction_impl::oswindowFromPoint(POINT_I32 point_i32)
   {


      throw ::not_implemented();
      //      return ::macos::interaction_impl::from_handle(::oswindowFromPoint(point));

   }

   bool interaction_impl::FlashWindow(bool bInvert)
   {


      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::FlashWindow(get_handle(), bInvert) != false;

   }

   bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::ChangeClipboardChain(get_handle(), hWndNext) != false;

   }

   oswindow interaction_impl::SetClipboardViewer()
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::SetClipboardViewer(get_handle());

   }

   bool interaction_impl::OpenClipboard()
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::OpenClipboard(get_handle()) != false;

   }

   ::user::interaction * PASCAL interaction_impl::GetOpenClipboardWindow()
   {

      throw ::not_implemented();
      //      return ::macos::interaction_impl::from_handle(::GetOpenClipboardWindow());

   }

   ::user::interaction * PASCAL interaction_impl::GetClipboardOwner()
   {

      throw ::not_implemented();
      //      return ::macos::interaction_impl::from_handle(::GetClipboardOwner());

   }

   ::user::interaction * PASCAL interaction_impl::GetClipboardViewer()
   {

      throw ::not_implemented();
      //      return ::macos::interaction_impl::from_handle(::GetClipboardViewer());

   }


   point_i32 PASCAL interaction_impl::GetCaretPos()
   {

      throw ::not_implemented();
      //      ::point_i32 point;
      //      ::GetCaretPos((POINT_I32 *)&point); return point;

   }

   void PASCAL interaction_impl::SetCaretPos(POINT_I32 point_i32)
   {

      throw ::not_implemented();
      //      ::SetCaretPos(point.x, point.y);

   }

   void interaction_impl::HideCaret()
   {

      throw ::not_implemented();
      //      ::HideCaret(get_handle());

   }

   void interaction_impl::ShowCaret()
   {

      throw ::not_implemented();
      //    ::ShowCaret(get_handle());

   }

   bool interaction_impl::SetForegroundWindow()
   {

      bool b = ::SetForegroundWindow(get_handle()) != false;

      //      round_window_show();

      return b;

   }

   ::user::interaction * PASCAL interaction_impl::GetForegroundWindow()
   {

      return nullptr;
      // return ::macos::interaction_impl::from_handle(::GetForegroundWindow());

   }

   bool interaction_impl::SendNotifyMessage(const ::atom & atom, wparam wparam, lparam lparam)
   {

      throw ::not_implemented();
      //      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != false;

   }


   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, ::u32 dwFlags) const
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      const_cast < user::interaction * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);

   }

   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, ::u32 dwFlags) const
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      const_cast < user::interaction * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);

   }

   bool interaction_impl::SetWindowContextHelpId(::u32 dwContextHelpId)
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != false;

   }

   ::u32 interaction_impl::GetWindowContextHelpId() const
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::GetWindowContextHelpId(get_handle());

   }


   // Default message ::collection::map implementations
   void interaction_impl::OnActivateApp(bool, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnActivate(::u32, ::user::interaction *, bool)
   {
      //Default();
      
      
   }
   void interaction_impl::OnCancelMode()
   {
      //Default();
      
      
   }
   void interaction_impl::OnChildActivate()
   {
      //Default();
      
      
   }
   void interaction_impl::OnClose()
   {
      //Default();
      
      
   }
   void interaction_impl::OnContextMenu(::user::interaction *, point_i32)
   {
      //Default();
      
      
   }

   bool interaction_impl::OnCopyData(::user::interaction *, COPYDATASTRUCT*)
   {

      //return Default() != false;
      
      return true;

   }

   void interaction_impl::OnEnable(bool)
   {
      //Default();
      
      
   }
   void interaction_impl::OnEndSession(bool)
   {
      //Default();
      
      
   }

   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   {
      //Default();
      return false;
      
   }

   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   {
      //Default();
      
      
   }
   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   {
      //Default();
      
      
   }

   LRESULT interaction_impl::OnMenuChar(::u32, ::u32, ::user::menu*)
   {
      //Default();
      return 0;
      
   }

   void interaction_impl::OnMenuSelect(::u32, ::u32, HMENU)
   {
      //Default();
      
      
   }
   void interaction_impl::OnMove(i32, i32)
   {
      //Default();
      
      
   }


   HCURSOR interaction_impl::OnQueryDragIcon()
   {
      
      return (HCURSOR)nullptr;
      
   }


   bool interaction_impl::OnQueryEndSession()
   {
      //Default();
      
      return true;
      
      
   }


   bool interaction_impl::OnQueryNewPalette()
   {
      //Default();
      return true;
      
   }


   bool interaction_impl::OnQueryOpen()
    {
      //Default();
       return true;
      
   }

   // void interaction_impl::on_message_set_cursor(::message::message * pmessage)
   // {
   //    ::pointer<::user::message>pusermessage(pmessage);
   //    if(psession->get_cursor() != nullptr
   //          && psession->get_cursor()->m_ecursor != cursor_system)
   //    {

   //       throw ::not_implemented();
   //       //         ::SetCursor(nullptr);
   //    }
   //    pusermessage->set_lresult(1);
   //    pusermessage->m_bRet = true;
   //    //(bool)Default();
   // }
   void interaction_impl::OnShowWindow(bool, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnSize(::u32, i32, i32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnTCard(::u32, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
   {
      //Default();
      
      
   }
   void interaction_impl::OnWindowPosChanged(WINDOWPOS*)
   {
      //Default();
      
      
   }
   void interaction_impl::OnDropFiles(HDROP)   {
      //Default();
      
      
   }
   void interaction_impl::OnPaletteIsChanging(::user::interaction *)
   {
      //Default();
      
      
   }
   bool interaction_impl::OnNcActivate(bool)
   {
      //Default();
      return true;
      
   }

   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
   {
      //Default();
      
      
   }
   bool interaction_impl::OnNcCreate(::user::system *)
   {

      return true;

   }

//   LRESULT interaction_impl::OnNcHitTest(point)
//     {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcLButtonDblClk(::u32, point_i32)
//     {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcLButtonDown(::u32, point_i32)   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcLButtonUp(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcMButtonDblClk(::u32, point_i32)
//     {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcMButtonDown(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcMButtonUp(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcMouseMove(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcPaint()
//   {
//      //Default();
//      
//      
//   }   void interaction_impl::OnNcRButtonDblClk(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcRButtonDown(::u32, point_i32)
//    {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnNcRButtonUp(::u32, point_i32)
//    {
//      //Default();
//      
//      
//   }
   void interaction_impl::OnSysChar(::u32, ::u32, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnSysCommand(::u32, LPARAM)   {
      //Default();
      
      
   }
   void interaction_impl::OnSysDeadChar(::u32, ::u32, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnSysKeyDown(::u32, ::u32, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnSysKeyUp(::u32, ::u32, ::u32)
    {
      //Default();
      
      
   }
   void interaction_impl::OnCompacting(::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnFontChange()
    {
      //Default();
      
      
   }
   void interaction_impl::OnPaletteChanged(::user::interaction *)
   {
      //Default();
      
      
   }
   void interaction_impl::OnSpoolerStatus(::u32, ::u32)
      {
      //Default();
      
      
   }
   void interaction_impl::OnTimeChange()
     {
      //Default();
      
      
   }
   void interaction_impl::OnChar(::u32, ::u32, ::u32)
      {
      //Default();
      
      
   }
   void interaction_impl::OnDeadChar(::u32, ::u32, ::u32)
     {
      //Default();
      
      
   }
   void interaction_impl::OnKeyDown(::u32, ::u32, ::u32)
     {
      //Default();
      
      
   }
   void interaction_impl::OnKeyUp(::u32, ::u32, ::u32)
   {
      //Default();
      
      
   }
//   void interaction_impl::OnLButtonDblClk(::u32, point_i32)
//     {
//      //Default();
//
//
//   }
//   void interaction_impl::OnLButtonDown(::u32, point_i32)
//     {
//      //Default();
//
//
//   }
//   void interaction_impl::OnLButtonUp(::u32, point_i32)
//     {
//      //Default();
//
//
//   }
//   void interaction_impl::OnMButtonDblClk(::u32, point_i32)
//      {
//      //Default();
//
//
//   }
//   void interaction_impl::OnMButtonDown(::u32, point_i32)
//      {
//      //Default();
//
//
//   }
//   void interaction_impl::OnMButtonUp(::u32, point_i32)
//     {
//      //Default();
//
//
//   }
   i32 interaction_impl::OnMouseActivate(::user::interaction *, ::u32, ::u32)
      {
      //Default();
         return 1;
      
   }
//   void interaction_impl::OnMouseMove(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//
//   bool interaction_impl::OnMouseWheel(::u32, short, point_i32)
//   {
//
//      return true;
//
//   }
//
//   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnRButtonDblClk(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
//   void interaction_impl::OnRButtonDown(::u32, point_i32)
//     {
//         //Default();
//         
//         
//      }
//   void interaction_impl::OnRButtonUp(::u32, point_i32)
//   {
//      //Default();
//      
//      
//   }
   void interaction_impl::OnTimer(uptr)
   {
      //Default();
      
      
   }
   void interaction_impl::OnInitMenu(::user::menu*)
   {
      //Default();
      
      
   }
   void interaction_impl::OnInitMenuPopup(::user::menu*, ::u32, bool)
    {
      //Default();
      
      
   }
   void interaction_impl::OnAskCbFormatName(::u32 nMaxCount, char * pszName)
   {
      //Default();
      
      
   }
   void interaction_impl::OnChangeCbChain(oswindow, oswindow)
   {
      //Default();
      
      
   }
   void interaction_impl::OnDestroyClipboard()
   {
      //Default();
      
      
   }
   void interaction_impl::OnDrawClipboard()
   {
      //Default();
      
      
   }
   void interaction_impl::OnHScrollClipboard(::user::interaction *, ::u32, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnPaintClipboard(::user::interaction *, HGLOBAL)
   {
      //Default();
      
      
   }
   void interaction_impl::OnRenderAllFormats()
   {
      //Default();
      
      
   }
   void interaction_impl::OnRenderFormat(::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnSizeClipboard(::user::interaction *, HGLOBAL)
   {
      //Default();
      
      
   }
   void interaction_impl::OnVScrollClipboard(::user::interaction *, ::u32, ::u32)
   {
      //Default();
      
      
   }
   ::u32 interaction_impl::OnGetDlgCode()
   {
      //Default();
      return 0;
      
   }
   void interaction_impl::OnMDIActivate(bool, ::user::interaction *, ::user::interaction *)
   {
      //Default();
      
      
   }
   void interaction_impl::OnEnterMenuLoop(bool)
   {
      //Default();
      
      
   }
   void interaction_impl::OnExitMenuLoop(bool)
   {
      //Default();
      
      
   }
   // Win4 support
   //   void interaction_impl::OnStyleChanged(i32, LPSTYLESTRUCT)
   //   { Default(); }
   //   void interaction_impl::OnStyleChanging(i32, LPSTYLESTRUCT)
   //   { Default(); }
   void interaction_impl::OnSizing(::u32, RECTANGLE_I32 *)
   {
      //Default();
      
      
   }
   void interaction_impl::OnMoving(::u32, RECTANGLE_I32 *)
     {
      //Default();
      
      
   }
   void interaction_impl::OnCaptureChanged(::user::interaction *)   {
      //Default();
      
      
   }

   bool interaction_impl::OnDeviceChange(::u32, uptr)
   {

      return true;

   }

   void interaction_impl::OnWinIniChange(const ::string &)
   {
      //Default();
      
      
   }
   void interaction_impl::OnChangeUIState(::u32, ::u32)
   {
      //Default();
      
      
   }
   void interaction_impl::OnUpdateUIState(::u32, ::u32)
   {
      //Default();
      
      
   }

   ::u32 interaction_impl::OnQueryUIState()
   {

      return 0;

   }

   // user::interaction dialog data support
   //    void interaction_impl::DoDataExchange(CDataExchange*)
   //   { } // default does nothing

   // user::interaction modality support

   void interaction_impl::BeginModalState()
   {

      throw ::exception(todo);

      //::EnableWindow(get_handle(), false);

   }

   void interaction_impl::EndModalState()
   {

      throw ::exception(todo);

      //::EnableWindow(get_handle(), true);

   }

   // frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
    { m_nIdleFlags |= idleTitle; }
    void frame_window::DelayRecalcLayout(bool bNotify)
    { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
    bool frame_window::InModalState() const
    { return m_cModalStack != 0; }
    void frame_window::set_title(const ::string & lpszTitle)
    { m_strTitle = lpszTitle; }
    string frame_window::get_title() const
    { return m_strTitle; }
    */



   void interaction_impl::CloseWindow()
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      ::CloseWindow(get_handle());

   }

   bool interaction_impl::OpenIcon()
   {

      throw ::not_implemented();
      //      ASSERT(::is_window(get_handle()));
      //      return ::OpenIcon(get_handle()) != false;

   }

   ////////////////////////////////////////////////////////////////////////////
   // UI related ::user::interaction functions

   oswindow PASCAL interaction_impl::GetSafeOwner_(oswindow hParent, oswindow* pWndTop)
   {
      // get ::user::interaction to start with
      oswindow hWnd = hParent;
      if (hWnd == nullptr)
      {
         /* trans      frame_window* pFrame = channel::GetRoutingFrame_();
          if (pFrame != nullptr)
          hWnd = pFrame->get_handle();
          else
          hWnd = psystem->GetMainWnd()->get_handle();*/
      }

      // a popup ::user::interaction cannot be owned by a child ::user::interaction
      while (hWnd != nullptr && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
         hWnd = ::get_parent(hWnd);

      // determine toplevel ::user::interaction to disable as well
      oswindow hWndTop = hWnd, hWndTemp = hWnd;
      for (;;)
      {
         if (hWndTemp == nullptr)
            break;
         else
            hWndTop = hWndTemp;
         hWndTemp = ::get_parent(hWndTop);
      }

      throw ::exception(todo);
      // get last active popup of first non-child that was found
      //    if (hParent == nullptr && hWnd != nullptr)
      //       hWnd = ::GetLastActivePopup(hWnd);

      // disable and store top level parent ::user::interaction if specified
//      if (pWndTop != nullptr)
//      {
//         /*         if (hWndTop != nullptr && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
//          {
//          *pWndTop = hWndTop;
//          ::EnableWindow(hWndTop, false);
//          }
//          else
//          *pWndTop = ::caNULL;*/
//      }
//
//      return hWnd;    // return the owner as oswindow
   }





   // void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
   // {
   //    ::pointer<::message::erase_bkgnd>perasebkgnd(pmessage);
   //    perasebkgnd->m_bRet = true;
   //    perasebkgnd->set_result(true);
   // }


   void interaction_impl::_001BaseWndInterfaceMap()
   {

      //psystem->window_map().set((iptr)get_handle(), this);

   }


//   void interaction_impl::_001OnTriggerMouseInside()
//   {
//
//
//      //throw ::not_implemented();
//      //      m_bMouseHover = true;
//      //      TRACKMOUSEEVENT tme = { sizeof(tme) };
//      //      tme.dwFlags = TME_LEAVE;
//      //      tme.hwndTrack = get_handle();
//      //      TrackMouseEvent(&tme);
//
//   }


//   void interaction_impl::_001UpdateWindow(bool bUpdateBuffer)
//   {
//
//      ::user::interaction_impl::_001UpdateWindow(bUpdateBuffer);
//
//   }


   void interaction_impl::_001UpdateScreen()
   {

      
      if (m_puserinteraction->is_window_visible())
      {

         round_window_redraw();

      }

   }



   void interaction_impl::edit_on_set_focus(::user::interaction* pinteraction)
   {
      
      auto puserinteraction = pinteraction->get_parent_frame();
      
      ::rectangle_i32 rWindowFrame;
      
      puserinteraction->window_rectangle(rWindowFrame);

      ::rectangle_i32 r1;
      
      pinteraction->window_rectangle(r1);
      
      ::size_i32 size = m_puserinteraction->get_client_size();
      
      int iSoftwareKeyboardTop = size.cy / 2;
      
      if(r1.top > iSoftwareKeyboardTop)
      {
         
         m_iSoftwareKeyboardScroll = r1.bottom - iSoftwareKeyboardTop;
           
         puserinteraction->m_pointScroll.y = m_iSoftwareKeyboardScroll;
         
      }

      puserinteraction->set_need_redraw();
      
      puserinteraction->post_redraw();
      
      ::rectangle_i32 r2;
      
      pinteraction->window_rectangle(r2);
      
      string strText;
      
      pinteraction->_001GetText(strText);
      
      strsize iBeg = 0;
      
      strsize iEnd = 0;
      
      pinteraction->_001GetSel(iBeg, iEnd);
      
      round_window_edit_on_set_focus(r2.left, r2.top, r2.right, r2.bottom, strText, iBeg, iEnd);
      
   }


   void interaction_impl::edit_on_kill_focus(::user::interaction* pinteraction)
   {
   
      auto puserinteraction = pinteraction->get_parent_frame();
      
      ::rectangle_i32 rWindowFrame;
      
      puserinteraction->window_rectangle(rWindowFrame);

      if(m_iSoftwareKeyboardScroll > 0)
      {
         
         puserinteraction->m_pointScroll.y -= m_iSoftwareKeyboardScroll;
         
         m_iSoftwareKeyboardScroll = 0;
         
      }

      round_window_edit_on_kill_focus();
      
   }


////      if(m_bShowFlags)
////      {
////
////         if(!is_window_visible() && (m_iShowFlags & SWP_SHOWWINDOW))
////         {
////
////            round_window_show();
////
////         }
////         else if(is_window_visible() && (m_iShowFlags & SWP_HIDEWINDOW))
////         {
////
////            round_window_hide();
////
////         }
////
////      }
////
////      if (m_rectangleLastPos != m_rectangleParentClientRequest)
////      {
////
////         ::set_window_position(m_oswindow, nullptr,
////                        (int) m_rectangleParentClientRequest.left,
////                        (int) m_rectangleParentClientRequest.top,
////                        (int) m_rectangleParentClientRequest.width(),
////                        (int) m_rectangleParentClientRequest.height(),
////                        SWP_NOZORDER
////                        | SWP_NOREDRAW
////                        | SWP_NOCOPYBITS
////                        | SWP_NOACTIVATE
////                        | SWP_NOOWNERZORDER
////                        | SWP_NOSENDCHANGING
////                        | SWP_DEFERERASE);
////
////         m_rectangleLastPos = m_rectangleParentClientRequest;
////
////      }
////
////      if (is_window_visible())
////      {
////
////         round_window_redraw();
////
////      }
//
//   }


   void interaction_impl::offset_context_org(RECTANGLE_I32 * lprectScreen)
   {

   }


   void interaction_impl::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      // graphics will be already set its impact port to the user::interaction for linux - cairo with xlib

      pgraphics->set_origin(::point_i32());

   }


   bool interaction_impl::round_window_become_first_responder()
   {

      return true;
      
   }


   void interaction_impl::round_window_draw(CGContextRef cgc, int cx, int cy)
   {

      {

         single_lock synchronouslock(m_puserinteraction->mutex(), true);

         double sh = status_bar_height();
         
         m_rectangleClientScreen.left = 0;
         m_rectangleClientScreen.top = sh;
         m_rectangleClientScreen.right = m_rectangleWindowScreen.right;
         m_rectangleClientScreen.top = m_rectangleWindowScreen.bottom - sh;

         if(m_bUpdateGraphics)
         {

            update_graphics_resources();

         }

      }

      critical_section_lock slDisplay(cs_display());
      
      auto pbuffer = m_pgraphics;

      if(!pbuffer)
      {

         return;

      }
      
      synchronous_lock sl1(pbuffer->get_screen_sync());
      
      auto & pimage = pbuffer->get_screen_image();

      if(!pimage)
      {

         return;

      }

      if(pimage.nok())
      {

         return;

      }

      ::draw2d::graphics_pointer g(e_create);

      g->attach(cgc);

      ::rectangle_i32 r = m_rectangleClientScreen;
      
      int w = pimage->width();
      
      int h = pimage->height();

      g->BitBlt(0, 0, w, h, pimage->get_graphics(), 0, 0);

   }


   int interaction_impl::round_window_get_x()
   {

      return m_puserinteraction->m_stateWindow3.m_point.x;

   }

   int interaction_impl::round_window_get_y()
   {

      return m_puserinteraction->m_stateWindow3.m_point.y;

   }


   void interaction_impl::round_window_become_key()
   {
   
   
   }


   bool interaction_impl::round_window_key_down(::user::enum_key ekey)
   {

      ::pointer<::user::message>spbase;

      auto pkey  = __new(::message::key());

      pkey->m_atom = e_message_key_down;

      pkey->m_ekey = ekey;

      spbase = pkey;

      on_host_message_handler(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_up(::user::enum_key ekey)
   {

      ::pointer<::user::message>spbase;

      auto pkey  = __new(::message::key());

      pkey->m_atom = e_message_key_up;
      pkey->m_ekey = ekey;

      spbase = pkey;

      on_host_message_handler(spbase);

      return spbase->m_bRet;

   }


   void interaction_impl::defer_update_text_impact()
   {

      ::pointer<::user::text>ptext = psession->get_keyboard_focus();

      if(ptext.is_null())
      {

         return;

      }

      string strTextPrevious;

      long iSelBegPrevious = -1;

      long iSelEndPrevious = -1;

      string strText;

      strsize iSelBeg = -1;

      strsize iSelEnd = -1;

      {

         long iSize = round_window_get_text_length();

         char * psz = strTextPrevious.get_buffer(iSize);

         round_window_get_text(psz, iSize);

         strTextPrevious.release_buffer(iSize);

      }

      ptext->_001GetText(strText);

      if(strText != strTextPrevious)
      {

         round_window_set_text(strText);

      }

      round_window_get_sel(iSelBegPrevious, iSelEndPrevious);

      ptext->_001GetSel(iSelBeg, iSelEnd);

      if(iSelEndPrevious != iSelEnd || iSelBegPrevious != iSelBeg)
      {

         round_window_set_sel(iSelBeg, iSelEnd);

      }

   }


   bool interaction_impl::round_window_on_text(const ::string & pszText, long iSelBeg, long iSelEnd)
   {

      ::pointer<raw_key>prawkey = psession->get_keyboard_focus();

      ::pointer<::user::plain_edit>pedit = psession->get_keyboard_focus();

      if(pedit.is_set() && !prawkey.is_set())
      {
         
         pedit->edit_on_text(pszText);
         
         pedit->edit_on_sel(iSelBeg, iSelEnd);

//         string strText;
//
//         long iSize = round_window_get_text_length();
//
//         char * pszText = strText.get_buffer(iSize);
//
//         round_window_get_text(pszText, iSize);
//
//         strText.release_buffer(iSize);
//
//         ptext->_001SetText(strText, ::e_source_user);
//
//         long iSelBeg = -1;
//
//         long iSelEnd = -1;
//
//         round_window_get_sel(iSelBeg, iSelEnd);
//
//         ptext->_001SetSel(iSelBeg, iSelEnd);

         return true;

      }
      else
      {

         ::pointer<::user::message>spbase;

         auto pkey  = __new(::message::key());

         pkey->m_atom = e_message_key_down;

         string strText(pszText);

         if(strText.is_empty())
         {

            pkey->m_ekey = ::user::e_key_back;

         }
         else if(strText == '\t')
         {

            pkey->m_ekey = ::user::e_key_tab;

         }
         else if(strText == '\n')
         {

            pkey->m_ekey = ::user::e_key_return;

         }
         else if(strText[0] >= 'a' && strText[0] <= 'z')
         {

            pkey->m_ekey = (::user::enum_key)(::user::e_key_a + strText[0] - 'a');

         }
         else if(strText[0] >= '0' && strText[0] <= '9')
         {

            pkey->m_ekey = (::user::enum_key)(::user::e_key_0 + strText[0] - '0');

         }
         else if(strText[0] >= 'A' && strText[0] <= 'Z')
         {

            pkey->m_ekey = ::user::e_key_left_shift;

            spbase = pkey;

            on_host_message_handler(spbase);

            sleep(100_ms);

            pkey->m_ekey = (::user::enum_key)(::user::e_key_a + strText[0] - 'A');

            on_host_message_handler(spbase);

            sleep(100_ms);

            pkey->m_atom = e_message_key_up;

            on_host_message_handler(spbase);

            pkey->m_ekey = ::user::e_key_left_shift;

            on_host_message_handler(spbase);

            round_window_set_text("");

            return true;

         }

         round_window_set_text("");

         spbase = pkey;

         on_host_message_handler(spbase);

         sleep(100_ms);

         pkey->m_atom = e_message_key_up;

         on_host_message_handler(spbase);

         return spbase->m_bRet;

      }

      return true;

   }


   long interaction_impl::round_window_edit_hit_test(int x, int y)
   {

      ::pointer<raw_key>prawkey = psession->get_keyboard_focus();

      ::pointer<::user::plain_edit>pedit = psession->get_keyboard_focus();

      if(pedit.is_set() && !prawkey.is_set())
      {
         
         return pedit->char_hit_test(x, y);
         
      }

      return -1;

   }


   bool interaction_impl::round_window_edit_caret_rect(CGRect * prectangle, long iSel)
   {
      
      ::pointer<raw_key>prawkey = psession->get_keyboard_focus();

     ::pointer<::user::plain_edit>pedit = psession->get_keyboard_focus();

     if(pedit.is_set() && !prawkey.is_set())
     {
        
        ::rectangle_i32 rectangle;
        
        if(!pedit->caret_rect(rectangle, iSel))
        {
           
           return false;
           
        }
        
        prectangle->origin.x = rectangle.left;
        prectangle->origin.y = rectangle.top;
        prectangle->size.width = rectangle.width();
        prectangle->size.height = rectangle.height();
        
        return true;
        
     }

     return false;

   }


   bool interaction_impl::round_window_on_sel_text(long iBeg, long iEnd)
   {

      ::pointer<::user::interaction>pinteraction = psession->get_keyboard_focus();

      ::pointer<::user::text>pedit = pinteraction;

      if(pedit.is_set())
      {

         pedit->MacroBegin();

         pedit->_001SetSel(iBeg, iEnd);

         pedit->MacroEnd();

         return true;

      }

      return true;

   }


   void interaction_impl::show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd)
   {

      ns_main_async(
      ^
      {

         if(bShow)
         {

            round_window_set_text(str);

            round_window_set_sel(iBeg, iEnd);

         }

         round_window_show_keyboard(bShow);

      });

   }


   void interaction_impl::on_message_set_focus(::message::message * pmessage)
   {

   }


   void interaction_impl::on_message_kill_focus(::message::message * pmessage)
   {

   }


   void interaction_impl::queue_message_handler(::user::message * pbaseParam)
   {

      defer_create_thread(this);
      
      ::pointer<::user::message>pusermessage = pbaseParam;

      post(pusermessage);

   }


   void interaction_impl::on_host_message_handler(::user::message * pusermessage)
   {

      m_puserinteraction->message_handler(pusermessage);

   }


   void interaction_impl::round_window_mouse_down(double x, double y)
   {

      ::pointer<::user::message>spbase;

      if(!is_active())
      {

         try
         {

            auto pmouseactivate = __new(::message::mouse_activate());

            pmouseactivate->m_atom = e_message_mouse_activate;

            spbase = pmouseactivate;

            on_host_message_handler(spbase);

            if(spbase->m_lresult == MA_ACTIVATE || spbase->m_lresult == MA_ACTIVATEANDEAT)
            {

               auto pactivate  = __new(::message::activate());

               pactivate->m_atom = e_message_activate;
               pactivate->m_wparam = WA_CLICKACTIVE;
               pactivate->m_nState = WA_CLICKACTIVE;
               pactivate->m_bMinimized = false;

               spbase = pactivate;

               on_host_message_handler(spbase);

            }

         }
         catch(...)
         {
         }

      }

      {

         auto pmouse = __new(::message::mouse());

         pmouse->m_atom = e_message_left_button_down;
         pmouse->m_point.x = (::i32) x;
         pmouse->m_point.y = (::i32) y;
         pmouse->m_bTranslated = true;
         //pmouse->m_bTranslateMouseMessageCursor = true;

         spbase = pmouse;

         on_host_message_handler(spbase);
         
      }

   }


   void interaction_impl::round_window_mouse_up(double x, double y)
   {

      ::pointer<::user::message>spbase;

      auto pmouse = __new(::message::mouse());

      pmouse->m_atom = e_message_left_button_up;
      pmouse->m_point.x = (::i32) x;
      pmouse->m_point.y = (::i32) y;
      pmouse->m_bTranslated = true;
      //      pmouse->m_bTranslateMouseMessageCursor = true;

      spbase = pmouse;

      on_host_message_handler(spbase);
      
   }


   void interaction_impl::round_window_mouse_moved(double x, double y)
   {

      ::pointer<::user::message>spbase;

      auto pmouse = __new(::message::mouse());

      pmouse->m_atom = e_message_mouse_move;
      pmouse->m_point.x = (::i32) x;
      pmouse->m_point.y = (::i32) y;
      pmouse->m_bTranslated = true;
      //      pmouse->m_bTranslateMouseMessageCursor = true;

      spbase = pmouse;

      on_host_message_handler(spbase);

   }


   void interaction_impl::round_window_mouse_dragged(double x, double y)
   {

      ::pointer<::user::message>spbase;

      auto pmouse = __new(::message::mouse());

      pmouse->m_atom = e_message_mouse_move;
      pmouse->m_point.x = (::i32) x;
      pmouse->m_point.y = (::i32) y;
      pmouse->m_bTranslated = true;
      //      pmouse->m_bTranslateMouseMessageCursor = true;

      spbase = pmouse;

      on_host_message_handler(spbase);

   }


   void interaction_impl::round_window_resized(int cx, int cy)
   {
      
      m_rectangleWindowScreen.left = 0;
      m_rectangleWindowScreen.top = 0;
      m_rectangleWindowScreen.right = cx;
      m_rectangleWindowScreen.bottom = cy;
      
      ::point_i32 p(0, 0);
      
      ::size_i32 s(cx, cy);

      m_puserinteraction->m_statePrevious2.m_point = p;
      m_puserinteraction->m_stateRequest2.m_point = p;
      m_puserinteraction->m_stateProcess2.m_point = p;
      m_puserinteraction->m_state2.m_point = p;
      m_puserinteraction->m_stateWindow3.m_point = p;
      
      m_puserinteraction->m_statePrevious2.m_size = s;
      m_puserinteraction->m_stateRequest2.m_size = s;
      m_puserinteraction->m_stateProcess2.m_size = s;
      m_puserinteraction->m_state2.m_size = s;
      m_puserinteraction->m_stateWindow3.m_size = s;

      for(auto & puserinteraction : m_puserinteraction->m_uiptraChild)
      {

         try
         {

            puserinteraction->send_message(e_message_display_change);

         }
         catch(...)
         {
            
         }

      }

   }


   bool interaction_impl::has_keyboard_focus()
   {

      return get_handle() == ::get_focus();

   }

   bool interaction_impl::is_active()
   {

      return get_handle() == ::get_active_window();

   }

   void interaction_impl::round_window_moved(CGPoint point_i32)
   {

      ::point_i32 pointMove(point.x, point.y);

      {

         synchronous_lock synchronouslock(m_puserinteraction->synchronization());

         m_puserinteraction->m_stateRequest2.m_point = pointMove;

      }

      m_puserinteraction->send_message(e_message_reposition, 0, pointMove.lparam());

   }


   void interaction_impl::round_window_on_show()
   {

      m_puserinteraction->message_call(e_message_show_window, 1);

   }


   void interaction_impl::round_window_on_hide()
   {

      m_puserinteraction->message_call(e_message_show_window, 0);

   }


   void interaction_impl::round_window_activate()
   {

      ::set_active_window(get_handle());

      m_puserinteraction->set_need_redraw();
      
      m_timeLastExposureAddUp.Now();

   }


   void interaction_impl::round_window_deactivate()
   {

      ::deactivate_window(get_handle());

      m_puserinteraction->set_need_redraw();

   }

   bool interaction_impl::has_pending_graphical_update()
   {

      if (::user::interaction_impl::has_pending_graphical_update())
      {

         return true;

      }

      synchronous_lock synchronouslock(m_puserinteraction->synchronization());

      for (auto p : m_puserinteraction->m_uiptraChild)
      {

         if (p->has_pending_graphical_update())
         {

            return true;

         }

      }

      return false;

   }


} // namespace ios



