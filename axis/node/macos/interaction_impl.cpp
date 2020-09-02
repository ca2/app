#include "framework.h"
#include "aura/os/macos/oswindow_data.h"
#include "aura/platform/mq.h"
#include "aura/message.h"


void deactivate_window(oswindow window);


struct __CTLCOLOR
{

   oswindow hWnd;
   HDC hDC;
   UINT nCtlType;

};


// WINBOOL PeekMessage(LPMESSAGE lpMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

// WINBOOL GetMessage(LPMESSAGE lpMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);


namespace macos
{

   ::aura::application * g_pappPreTranslateMouseMessage = nullptr;


   class round_window_draw_life_time
   {
   public:


      interaction_impl * m_pimpl;

      round_window_draw_life_time(interaction_impl * pimpl) :
         m_pimpl(pimpl)
      {

         m_pimpl->m_uiLastUpdateBeg = get_nanos();

      }

      ~round_window_draw_life_time()
      {

         m_pimpl->m_uiLastUpdateEnd = get_nanos();

      }

   };


   interaction_impl::interaction_impl()
   {

      m_bEnabled = true;
      set_handle(nullptr);

   }


   void interaction_impl::construct(oswindow hWnd)
   {

      set_handle(hWnd);

   }


   interaction_impl::interaction_impl(::object * pobject) :
      ::object(pobject)
   {

      m_bEnabled = true;
      set_handle(nullptr);

   }


   interaction_impl::~interaction_impl()
   {

   }


   void interaction_impl::round_window_add_ref()
   {

      add_ref(OBJ_REF_DBG_P_NOTE(this, "round_window_add_ref"));

      m_puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "round_window_add_ref"));

   }


   void interaction_impl::round_window_dec_ref()
   {

      m_puserinteraction->dec_ref(OBJ_REF_DBG_P_NOTE(this, "round_window_dec_ref"));

      dec_ref(OBJ_REF_DBG_P_NOTE(this, "round_window_dec_ref"));

   }


   CLASS_DECL_AXIS void hook_window_create(::user::interaction * pWnd);

   CLASS_DECL_AXIS bool unhook_window_create();

   void CLASS_DECL_AXIS __pre_init_dialog(::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld);

   void CLASS_DECL_AXIS __post_init_dialog(::user::interaction * pWnd, const RECT& rectOld, DWORD dwStyleOld);

   LRESULT CALLBACK __activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam);


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      return from_handle((oswindow)pdata);

   }


   void * interaction_impl::get_os_data() const
   {

      return ((oswindow &)m_oswindow);

   }


   bool interaction_impl::ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      if (!::is_window(hWnd))
         return false;

      DWORD_PTR dw = hWnd->get_window_long_ptr(GWL_STYLE);

      dw &= ~dwRemove;

      dw |= dwAdd;

      hWnd->set_window_long_ptr(GWL_STYLE, dw);

      return true;

   }


   bool interaction_impl::ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      if (!::is_window(hWnd))
      {

         return false;

      }

      DWORD_PTR dw = hWnd->get_window_long_ptr(GWL_EXSTYLE);

      dw &= ~dwRemove;

      dw |= dwAdd;

      hWnd->set_window_long_ptr(GWL_EXSTYLE, dw);

      return true;

   }


   const MESSAGE * PASCAL interaction_impl::GetCurrentMessage()
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

      if (oswindow == nullptr)
      {

         return nullptr;

      }

      return oswindow->m_pimpl;

   }


   ::user::interaction_impl * interaction_impl::FromHandlePermanent(oswindow oswindow)
   {

      if (oswindow == nullptr)
      {

         return nullptr;

      }

      return oswindow->m_pimpl;

   }


   bool interaction_impl::Attach(oswindow hWndNew)
   {

      ASSERT(get_handle() == nullptr);     // only attach once, detach on destroy
      //  ASSERT(FromHandlePermanent(hWndNew) == nullptr);
      // must not already be in permanent ::collection::map

      if (hWndNew == nullptr)
      {

         return FALSE;

      }

      //single_lock sl(afxMutexHwnd(), TRUE);
      //hwnd_map * pMap = afxMapHWND(TRUE); // create ::collection::map if not exist
      //ASSERT(pMap != nullptr);

      //pMap->set_permanent(set_handle(hWndNew), this);
      //if(m_puserinteraction == nullptr)
      {
         //m_puserinteraction = this;
      }

      m_oswindow = hWndNew;

      return TRUE;

   }

   oswindow interaction_impl::Detach()
   {
      oswindow hWnd = (oswindow)get_handle();
      if (hWnd != nullptr)
      {
         //         single_lock sl(afxMutexHwnd(), TRUE);
         //  ;;       hwnd_map * pMap = afxMapHWND(); // don't create if not exist
         //     if (pMap != nullptr)
         //      pMap->remove_handle(get_handle());
         //         set_handle(nullptr);
         m_oswindow = nullptr;
      }

      return hWnd;
   }

   void interaction_impl::pre_subclass_window()
   {
      // no default processing
   }


   bool interaction_impl::create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction *  puiParent, id id)
   {

      if (!native_create_window_ex(pinteraction, cs,
                                   puiParent == nullptr ? nullptr : puiParent->get_safe_handle(), id))
      {

         return false;

      }

      return true;

   }


   ::estatus interaction_impl::update_graphics_resources()
   {
      
      if(m_pgraphics.is_null())
      {
   
         auto estatus = __compose(m_pgraphics, __new(::graphics::multiple_buffer));
      
         if(!estatus)
         {
         
            return estatus;
         
         }

         estatus = m_pgraphics->initialize_graphics_graphics(this);
      
         if(!estatus)
         {
      
            return estatus;
         
         }
         
         return ::success;
   
      }
      
      return ::success_none;
      
   }


   bool interaction_impl::_native_create_window_ex(::user::create_struct & cs)
   {

      //if (::is_window(get_handle()))
      //{

      //   DestroyWindow();

      //}

      //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
      //       __is_valid_atom(lpszClassName));
      ENSURE_ARG(cs.lpszName == nullptr || __is_valid_string(cs.lpszName));

      // allow modification of several common create parameters
      //::user::create_struct createstruct;
      //      cs.hwndParent = hWndParent;
      //   cs.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
      cs.hMenu = nullptr;
      //      cs.hInstance = System.m_hInstance;
      //cs.lpCreateParams = lpParam;

      if (!m_puserinteraction->pre_create_window(cs))
      {

         return false;

      }

      install_message_routing(m_puserinteraction);

      hook_window_create(m_puserinteraction);

      CGRect rect;

      RECT rectParam;

      rectParam.left = cs.x;
      rectParam.top = cs.y;
      rectParam.right = cs.x + cs.cx;
      rectParam.bottom = cs.y + cs.cy;

      __copy(rect, rectParam);

      if (cs.hwndParent == MESSAGE_WINDOW_PARENT)
      {

         return true;

      }
      else
      {

         unsigned uStyle = 0;

         if(m_puserinteraction->m_ewindowflag & window_flag_miniaturizable)
         {

#define NSWindowStyleMaskMiniaturizable (1 << 2)

            uStyle |= NSWindowStyleMaskMiniaturizable;

         }

         m_oswindow = oswindow_get(new_round_window(this, rect, uStyle));

         m_puserinteraction->m_stateWindow3.m_point = ::top_left(rectParam);

         m_puserinteraction->m_stateWindow3.m_size = ::size(rectParam);

         __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_thread());

         //m_puserinteraction->place(rectParam);



         m_oswindow->set_user_interaction_impl(this);

         oswindow_assign(m_oswindow, this);

      }

      LRESULT lresult = m_puserinteraction->send_message(WM_CREATE, 0, (LPARAM)&cs);

      bool bOk = true;

      if (!unhook_window_create() || lresult == -1)
      {

         bOk = false;
         
         finalize();

         //children_post_quit();

         //children_wait_quit(one_minute());

         PostNcDestroy();        // cleanup if CreateWindowEx fails too soon
         
         return false;

      }

      if(cs.style & WS_VISIBLE)
      {

         m_puserinteraction->display();

         m_puserinteraction->set_need_redraw();

         //m_puserinteraction->post_redraw();

         //;//round_window_show();

      }

      m_puserinteraction->set_need_layout();

      m_puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "native_create_window"));

      m_puserinteraction->m_ewindowflag |= window_flag_window_created;
      
      return bOk;

   }


   // for child windows
   bool interaction_impl::pre_create_window(::user::create_struct& cs)
   {
      /*      if (cs.lpszClass == nullptr)
       {
/xcore/app/aura/node/macos/macos_interaction_impl.cpp:712:44: No member named 'get_window_rect' in 'user::interaction_impl'       // make sure the default user::interaction class is registered
       VERIFY(__end_defer_register_class(__WND_REG, &cs.lpszClass));

       // no WNDCLASS provided - use child user::interaction default
       ASSERT(cs.style & WS_CHILD);
       }*/
      return true;
   }


   bool interaction_impl::create_window(::user::interaction * pinteraction, const char * lpszClassName,const char * lpszWindowName,u32 uStyle, const ::rect & rect,::user::interaction * puiParent,id id, ::create * pcreate)
   {

      // can't use for desktop or pop-up windows (use CreateEx instead)

      ASSERT(puiParent != nullptr);
      
      ::user::create_struct createstruct(0, lpszClassName, lpszWindowName, uStyle, rect, pcreate);

      createstruct.hwndParent = puiParent->get_safe_handle();

      ASSERT((createstruct.style & WS_POPUP) == 0);

      return create_window_ex(pinteraction, createstruct, puiParent, id);

   }


   // bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const char * pszName)
   // {

   //    if (is_window(get_handle()))
   //    {

   //       set_window_text(pszName);

   //    }
   //    else
   //    {

   //       ::user::create_struct createstruct(0, nullptr, pszName, WS_CHILD, nullptr);

   //       if (!native_create_window_ex(pinteraction, createstruct, MESSAGE_WINDOW_PARENT, "message_queue"))
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

         IGUI_MSG_LINK(WM_PAINT, pchannel, this, &interaction_impl::_001OnPaint);
         IGUI_MSG_LINK(WM_PRINT, pchannel, this, &interaction_impl::_001OnPrint);

      }

      m_puserinteraction->install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &interaction_impl::_001OnCreate);

      if (!m_puserinteraction->m_bMessageWindow)
      {

//         IGUI_MSG_LINK(WM_SETCURSOR, pchannel, this, &interaction_impl::_001OnSetCursor);
//         IGUI_MSG_LINK(WM_ERASEBKGND, pchannel, this,&interaction_impl::_001OnEraseBkgnd);
         //         IGUI_MSG_LINK(WM_NCCALCSIZE, pchannel, this,&interaction_impl::_001OnNcCalcSize);
//         IGUI_MSG_LINK(WM_SIZE, pchannel, this, &interaction_impl::_001OnSize);
         //         IGUI_MSG_LINK(WM_WINDOWPOSCHANGING, pchannel, this,&interaction_impl::_001OnWindowPosChanging);
         //         IGUI_MSG_LINK(WM_WINDOWPOSCHANGED, pchannel, this,&interaction_impl::_001OnWindowPosChanged);
         //         IGUI_MSG_LINK(WM_GETMINMAXINFO, pchannel, this,&interaction_impl::_001OnGetMinMaxInfo);
         //         IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this,&interaction_impl::_001OnSetFocus);
         //         IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this,&interaction_impl::_001OnKillFocus);
         //IGUI_MSG_LINK(ca2m_PRODEVIAN_SYNCH, pchannel, this,&interaction_impl::_001OnProdevianSynch);
      }
      prio_install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &interaction_impl::_001OnDestroy);

      //      ::user::interaction_impl::install_message_routing(pchannel);
      //      //m_pbuffer->InstallMessageHandling(pinterface);
      //      IGUI_MSG_LINK(WM_DESTROY           , pchannel, this, &interaction_impl::_001OnDestroy);
      //      IGUI_MSG_LINK(WM_PAINT             , pchannel, this, &interaction_impl::_001OnPaint);
      //      IGUI_MSG_LINK(WM_PRINT             , pchannel, this, &interaction_impl::_001OnPrint);
      //      if(m_puserinteraction != nullptr)
      //      {
      //         m_puserinteraction->install_message_routing(pchannel);
      //      }
      //      IGUI_MSG_LINK(WM_CREATE            , pchannel, this, &interaction_impl::_001OnCreate);
      //      IGUI_MSG_LINK(WM_SETCURSOR         , pchannel, this, &interaction_impl::_001OnSetCursor);
      //      IGUI_MSG_LINK(WM_ERASEBKGND        , pchannel, this, &interaction_impl::_001OnEraseBkgnd);
      //      IGUI_MSG_LINK(WM_MOVE              , pchannel, this, &interaction_impl::_001OnMove);
      //      IGUI_MSG_LINK(WM_SIZE              , pchannel, this, &interaction_impl::_001OnSize);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &interaction_impl::_001OnShowWindow);
      //      IGUI_MSG_LINK(ca2m_PRODEVIAN_SYNCH , pchannel, this, &interaction_impl::_001OnProdevianSynch);
      ////      //IGUI_MSG_LINK(WM_TIMER             , pchannel, this, &interaction_impl::_001OnTimer);
   }


   void interaction_impl::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

//      do_show_flags();
//
//      clear_show_flags();

   }


   void interaction_impl::_001OnMove(::message::message * pmessage)
   {

//      if (m_bDestroyImplOnly)
//      {
//
//         return;
//
//      }
//
//      if (m_puserinteraction->m_eflagLayouting)
//      {
//
//         return;
//
//      }
//
//      SCAST_PTR(::message::move, pmove, pmessage);
//
//      m_puserinteraction->window_state().m_point = pmove->m_point;
//
//      if (m_puserinteraction->layout().sketch().m_point != pmove->m_point)
//      {
//
//         if (m_puserinteraction->layout().is_moving())
//         {
//
//            output_debug_string("\nWindow is Moving :: _001OnMove");
//
//         }
//
//         m_puserinteraction->move_to(pmove->m_point);
//
//         if (m_puserinteraction->layout().design().display() != display_normal)
//         {
//
//            m_puserinteraction->display();
//
//         }
//
//         m_puserinteraction->set_reposition();
//
//         m_puserinteraction->set_need_redraw();
//
//      }

   }


   void interaction_impl::_001OnSize(::message::message * pmessage)
   {
//
//      if (m_bDestroyImplOnly)
//      {
//
//         return;
//
//      }
//
//      if (m_puserinteraction->m_eflagLayouting)
//      {
//
//         return;
//
//      }
//
//      SCAST_PTR(::message::size, psize, pmessage);
//
//      m_puserinteraction->window_state().m_size = psize->m_size;
//
//      if (m_puserinteraction->layout().sketch().m_size != psize->m_size)
//      {
//
//         m_puserinteraction->set_size(psize->m_size);
//
//         if (m_puserinteraction->layout().design().display() != display_normal)
//         {
//
//            m_puserinteraction->display();
//
//         }
//
//         m_puserinteraction->set_need_layout();
//
//         m_puserinteraction->set_need_redraw();
//
//      }
//
   }


   void interaction_impl::_001OnDestroy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if(GetActiveWindow() == m_puserinteraction)
      {

         ::set_active_window(nullptr);

      }

      default_message_handler(pmessage);

      round_window_hide();

      m_ptimerarray.release();
      
   }


   void interaction_impl::PostNcDestroy()
   {

      Detach();

      ASSERT(get_handle() == nullptr);

      ::user::interaction_impl::PostNcDestroy();

      ns_main_async(^()
      {
      
         round_window_destroy();
                      
      });

   }


   void interaction_impl::assert_valid() const
   {
      
      if (get_handle() == nullptr)
      {
         
         return; // null (unattached) windows are valid
         
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
       single_lock sl(afxMutexHwnd(), TRUE);
       hwnd_map * pMap = afxMapHWND();
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
      // writing a multithreaded application, it is likely that
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
      char szBuf[64];
      dumpcontext << "\ncaption = \"" << szBuf << "\"";

      //      ::GetClassName(get_handle(), szBuf, _countof(szBuf));
      //    dumpcontext << "\nclass name = \"" << szBuf << "\"";

      ::rect rect;
      
      ((::user::interaction_impl *) this)->m_puserinteraction->get_window_rect(rect);
      
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent ::user::interaction * = " << (void *)((::user::interaction_impl *) this)->GetParent();

      //      dumpcontext << "\nstyle = " << (void *)(dword_ptr)::GetWindowLong(get_handle(), GWL_STYLE);
      //    if (::GetWindowLong(get_handle(), GWL_STYLE) & WS_CHILD)
      //     dumpcontext << "\nid = " << __get_dialog_control_id(get_handle());

      dumpcontext << "\n";
   }


   bool interaction_impl::DestroyWindow()
   {

      return ::user::interaction_impl::DestroyWindow();

   }


//   LRESULT interaction_impl::DefWindowProc(UINT nMsg, WPARAM wparam, LPARAM lparam)
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
      UNREFERENCED_PARAMETER(pmessage);
      // no default processing
   }


   void interaction_impl::get_window_text(string & str)
   {

      char sz[2048];

      xxf_zero(sz);

      round_window_get_title(sz, sizeof(sz));

      str = m_strWindowText;

   }


   /*
    i32 interaction_impl::GetDlgItemText(i32 nID, string & rString) const
    {
    ASSERT(::is_window(get_handle()));
    rString = "";    // is_empty without deallocating

    oswindow hWnd = ::GetDlgItem(get_handle(), nID);
    if (hWnd != nullptr)
    {
    i32 nLen = ::GetWindowTextLength(hWnd);
    ::GetWindowText(hWnd, rString.get_string_buffer(nLen), nLen+1);
    rString.ReleaseBuffer();
    }

    return (i32)rString.get_length();
    }
    */

//   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
//   {
//      /*    ASSERT(::is_window(get_handle()));
//       lpwndpl->length = sizeof(WINDOWPLACEMENT);
//       return ::GetWindowPlacement(get_handle(), lpwndpl) != FALSE;*/
//      return false;
//   }
//
//   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
//   {
//      /*      ASSERT(::is_window(get_handle()));
//       ((WINDOWPLACEMENT*)lpwndpl)->length = sizeof(WINDOWPLACEMENT);
//       return ::SetWindowPlacement(get_handle(), lpwndpl) != FALSE;*/
//      return false;
//   }

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

//   bool interaction_impl::_EnableToolTips(bool bEnable, UINT nFlag)
//   {
//      UNREFERENCED_PARAMETER(bEnable);
//      UNREFERENCED_PARAMETER(nFlag);
//      return FALSE;
//   }
//
//
//   LRESULT interaction_impl::OnNTCtlColor(WPARAM wparam, LPARAM lparam)
//   {
//      return 0;
//   }
//
//
//   void interaction_impl::PrepareForHelp()
//   {
//      /*if (IsFrameWnd())
//       {
//       // frame_window windows should be allowed to exit help mode first
//       frame_window* pFrameWnd = dynamic_cast < frame_window * >(this);
//       pFrameWnd->ExitHelpMode();
//       }
//
//       // cancel any tracking modes
//       send_message(WM_CANCELMODE);
//       send_message_to_descendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);
//
//       // need to use top level parent (for the case where get_handle() is in DLL)
//       ::user::interaction * pWnd = EnsureTopLevelParent();
//       MAC_WINDOW(pWnd)->send_message(WM_CANCELMODE);
//       MAC_WINDOW(pWnd)->send_message_to_descendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);
//
//       // attempt to cancel capture
//       oswindow hWndCapture = ::GetCapture();
//       if (hWndCapture != nullptr)
//       ::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);*/
//   }


   /*void interaction_impl::WinHelpInternal(dword_ptr dwData, UINT nCmd)
    {
    UNREFERENCED_PARAMETER(dwData);
    UNREFERENCED_PARAMETER(nCmd);
    __throw(not_implemented());

    application* pApp = &System;
    ASSERT_VALID(pApp);
    if (pApp->m_eHelpType == afxHTMLHelp)
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



   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      channel::route_command_message(pcommand);

      if(pcommand->m_bRet)
      {

         return;

      }

      //      bool b;

      //if(_iguimessageDispatchCommandMessage(pcommand, b))
      // return b;

      channel * pcmdtarget = dynamic_cast <channel *> (this);
      return pcmdtarget->channel::route_command_message(pcommand);
   }


   void interaction_impl::on_control_event(::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

   void interaction_impl::_002OnDraw(::image * pimage)
   {

      //      ::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));

   }

   
   void interaction_impl::default_message_handler(::message::message * pmessage)
   {
      
//      if (get_handle() == nullptr)
//      {
//
//         return;
//
//      }
//
//      WNDPROC pfnWndProc = *GetSuperWndProcAddr();
//
//      LRESULT lresult = 0;
//
//      if (pfnWndProc == nullptr)
//      {
//
//         lresult = ::DefWindowProcW(m_oswindow, pmessage->m_id.i64(), pmessage->m_wparam, pmessage->m_lparam);
//
//      }
//      else
//      {
//
//         lresult = ::CallWindowProc(pfnWndProc, m_oswindow, pmessage->m_id.i64(), pmessage->m_wparam, pmessage->m_lparam);
//
//      }
      
      pmessage->m_lresult = 0;
      
   }


   void interaction_impl::message_handler(::message::base * pbase)
   {

      if (pbase->m_id == WM_SIZE || pbase->m_id == WM_MOVE)
      {

         //         win_update_graqhics();

      }

      if (pbase->m_id == WM_KEYDOWN ||
            pbase->m_id == WM_KEYUP ||
            pbase->m_id == WM_CHAR)
      {

         SCAST_PTR(::message::key, pkey, pbase);

         Session.translate_os_key_message(pkey);

         if(pkey->m_ekey != ::user::key_refer_to_text_member)
         {
            
            if (pbase->m_id == WM_KEYDOWN)
            {
               
               try
               {
                  
                  if(Session.is_key_pressed(pkey->m_ekey))
                  {

                     return;

                  }
                  
                  Session.set_key_pressed(pkey->m_ekey, true);
                  
               }
               catch (...)
               {
                  
               }
               
            }
            else if (pbase->m_id == WM_KEYUP)
            {
               
               try
               {
                  
                  Session.set_key_pressed(pkey->m_ekey, false);
                  
               }
               catch (...)
               {
                  
               }
               
            }
            
         }
         
      }

      if (m_puserinteraction != nullptr)
      {

         if (m_puserinteraction->layout().is_moving())
         {
            //TRACE("moving: skip pre translate message");
         }
         else if (m_puserinteraction->layout().is_sizing())
         {
            //TRACE("sizing: skip pre translate message");
         }
         else
         {

            m_puserinteraction->pre_translate_message(pbase);

            if (pbase->m_bRet)
               return;

            pbase->m_uiMessageFlags |= 1;

         }

      }

      if (pbase->m_id == WM_TIMER)
      {
         //         get_context_application()->get_context_application()->step_timer();
      }
      else if (pbase->m_id == WM_LBUTTONDOWN)
      {
         //  g_pwndLastLButtonDown = this;
      }
      else if (pbase->m_id == WM_SIZE)
      {
         m_bUpdateGraphics = true;
      }
         /*   else if(pbase->m_id == CA2M_BERGEDGE)
       {
       if(pbase->m_wparam == BERGEDGE_GETAPP)
       {
       ::application ** ppapp= (::application **) pbase->m_lparam;
       *ppapp = get_context_application();
       pbase->m_bRet = true;
       return;
       }
       }*/
      pbase->m_lresult = 0;


      if (pbase->m_id == WM_LBUTTONDOWN ||
            pbase->m_id == WM_LBUTTONUP ||
            pbase->m_id == WM_MBUTTONDOWN ||
            pbase->m_id == WM_MBUTTONUP ||
            pbase->m_id == WM_RBUTTONDOWN ||
            pbase->m_id == WM_RBUTTONUP ||
            pbase->m_id == WM_RBUTTONDBLCLK ||
            pbase->m_id == WM_LBUTTONDBLCLK ||
            pbase->m_id == WM_MOUSEMOVE ||
            pbase->m_id == WM_MOUSEMOVE ||
            pbase->m_id == WM_MOUSEWHEEL)
      {

         if (pbase->m_id == WM_LBUTTONDOWN)
         {

            output_debug_string("\nWM_LBUTTONDOWN");

         }
         else if(pbase->m_id == WM_MOUSEMOVE)
         {
            
            //output_debug_string("\nWM_MOUSEMOVE");
            
         }

         ::message::mouse * pmouse = (::message::mouse *) pbase;


         // user presence status activity reporting

         Session.on_ui_mouse_message(pmouse);


         if (get_context_session() != nullptr)
         {

            Session.m_pointCursor = pmouse->m_point;

         }

         if (m_bTranslateMouseMessageCursor)
         {

            ::rect rect;

            if(!pmouse->m_bTranslated)
            {

               pmouse->m_bTranslated = true;

               if (System.get_monitor_count() > 0)
               {

                  System.get_monitor_rect(0, &rect);

               }
               else
               {

                  if (m_bScreenRelativeMouseMessagePosition)
                  {

                     ::get_window_rect(get_handle(), &rect);

                  }
                  else
                  {

                     m_puserinteraction->get_window_rect(rect);

                  }

               }

               if (rect.left >= 0)
               {

                  pmouse->m_point.x += (LONG)rect.left;

               }

               if (rect.top >= 0)
               {

                  pmouse->m_point.y += (LONG)rect.top;

               }

            }

         }

         if (pbase->m_id == WM_MOUSEMOVE)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;

         }

         _008OnMouse(pmouse);

         return;

      }
      else if (pbase->m_id == WM_KEYDOWN ||
               pbase->m_id == WM_KEYUP ||
               pbase->m_id == WM_CHAR)
      {

         ::message::key * pkey = (::message::key *) pbase;

         ::user::interaction * puiFocus = dynamic_cast <::user::interaction *> (Session.get_keyboard_focus());

         if (puiFocus != nullptr
               && puiFocus->is_window()
               && puiFocus->GetTopLevel() != nullptr
               && puiFocus != m_puserinteraction)
         {

            puiFocus->send(pkey);

            if (pbase->m_bRet)
            {

               return;

            }

         }
         else if (!pkey->m_bRet)
         {

            if (m_puserinteraction != nullptr)
            {

               m_puserinteraction->_000OnKey(pkey);

               if (pbase->m_bRet)
               {

                  return;

               }

            }

         }

         default_message_handler(pbase);

         return;

      }

      if (pbase->m_id == EVENT_MESSAGE)
      {

         if (m_puserinteraction != nullptr)
         {

            m_puserinteraction->on_control_event((::user::control_event *) pbase->m_lparam.m_lparam);

         }
         else
         {

            on_control_event((::user::control_event *) pbase->m_lparam.m_lparam);

         }

         return;

      }

      //(this->*m_pfnDispatchWindowProc)(pmessage);

      m_puserinteraction->route_message(pbase);

      if (pbase->m_bRet)
      {

         return;

      }

      default_message_handler(pbase);

   }


//   bool interaction_impl::IsTopParentActive()
//   {
//
//      ASSERT(get_handle() != nullptr);
//
//      ASSERT_VALID(this);
//
//      ::user::interaction *pWndTopLevel = EnsureTopLevel();
//
//      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
//
//   }
//
//
//   void interaction_impl::ActivateTopParent()
//   {
//      // special activate logic for floating toolbars and palettes
////      ::user::interaction * pActiveWnd = GetForegroundWindow();
//      //      if (pActiveWnd == nullptr || !(MAC_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(MAC_WINDOW(pActiveWnd)->get_handle(), get_handle())))
//      {
//         // clicking on floating frame when it does not have
//         // focus itself -- activate the toplevel frame instead.
//         EnsureTopLevel()->SetForegroundWindow();
//      }
//   }


   /*

   __pointer(::user::frame_window) interaction_impl::GetTopLevelFrame()
   {
      if (get_handle() == nullptr) // no oswindow attached
         return nullptr;

      ASSERT_VALID(this);

      ::user::frame_window* pFrameWnd = nullptr;
      if(m_puserinteraction != nullptr)
         pFrameWnd = dynamic_cast < ::user::frame_window * > (m_puserinteraction);
      if (pFrameWnd == nullptr || !pFrameWnd->is_frame_window())
         pFrameWnd = GetParentFrame();

      if (pFrameWnd != nullptr)
      {
         ::user::frame_window* pTemp;
         while ((pTemp = pFrameWnd->GetParentFrame()) != nullptr)
            pFrameWnd = pTemp;
      }
      return pFrameWnd;
   }


    */




//   i32 interaction_impl::message_box(const char * lpszText, const char * lpszCaption, UINT nType)
//   {
//
//      string strCaption;
//
//      if (lpszCaption == nullptr)
//         lpszCaption = Application.m_strAppName;
//      else
//         lpszCaption = strCaption;
//
//      i32 nResult = ::os_message_box((oswindow)get_handle(), lpszText, lpszCaption, nType);
//
//      return nResult;
//
//   }


//   ::user::interaction *  PASCAL interaction_impl::

   int interaction_impl::SetScrollPos(int nBar, int nPos, bool bRedraw)
   {
      //      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
      return 0;
   }

   int interaction_impl::GetScrollPos(int nBar) const
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

    bool interaction_impl::GetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo, UINT nMask)
    {
    UNREFERENCED_PARAMETER(nMask);
    ASSERT(lpScrollInfo != nullptr);

    oswindow hWnd = get_handle();
    return ::GetScrollInfo(hWnd, nBar, lpScrollInfo) != FALSE;
    }
    */


   i32 interaction_impl::GetScrollLimit(i32 nBar)
   {

      i32 nMin = 0, nMax = 0;

      GetScrollRange(nBar, &nMin, &nMax);

      return nMax;

   }


   void interaction_impl::ScrollWindow(i32 xAmount, i32 yAmount,
                                       LPCRECT lpRect, LPCRECT lpClipRect)
   {

   }


   void interaction_impl::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
   {

   }


//   bool interaction_impl::HandleFloatingSysCommand(UINT nID, LPARAM lparam)
//   {
//      /*      ::user::interaction* pParent = GetTopLevelParent();
//       switch (nID & 0xfff0)
//       {
//       case SC_PREVWINDOW:
//       case SC_NEXTWINDOW:
//       if (LOWORD(lparam) == VK_F6 && pParent != nullptr)
//       {
//       pParent->SetFocus();
//       return true;
//       }
//       break;
//
//       case SC_CLOSE:
//       case SC_KEYMENU:
//       // Check lparam.  If it is 0L, then the ::account::user may have done
//       // an Alt+Tab, so just ignore it.  This breaks the ability to
//       // just press the Alt-key and have the first menu selected,
//       // but this is minor compared to what happens in the Alt+Tab
//       // case.
//       if ((nID & 0xfff0) == SC_CLOSE || lparam != 0L)
//       {
//       if (pParent != nullptr)
//       {
//       // Sending the above WM_SYSCOMMAND may destroy the cast,
//       // so we have to be careful about restoring activation
//       // and focus after sending it.
//       oswindow hWndSave = get_handle();
//       oswindow hWndFocus = ::GetFocus();
//       pParent->SetActiveWindow();
//       pParent->send_message(WM_SYSCOMMAND, nID, lparam);
//
//       // be very careful here...
//       if (::is_window(hWndSave))
//       ::set_active_window(hWndSave);
//       if (::is_window(hWndFocus))
//       ::SetFocus(hWndFocus);
//       }
//       }
//       return true;
//       }
//       return false;*/
//      return false;
//   }

//   void interaction_impl::WalkPreTranslateTree(::user::interaction *  puiStop, ::message::message * pmessage)
//   {
//      ASSERT(puiStop == nullptr || puiStop->is_window());
//      ASSERT(pmessage != nullptr);
//
//      SCAST_PTR(::message::base, pbase, pmessage);
//      // walk from the target user::interaction up to the hWndStop user::interaction checking
//      //  if any user::interaction wants to translate this message
//
//      for (__pointer(::user::interaction) pinteraction = pbase->m_puserinteraction; pinteraction != nullptr; pinteraction->GetParent())
//      {
//
//         pinteraction->pre_translate_message(pmessage);
//
//         if (pmessage->m_bRet)
//            return; // trapped by target user::interaction (eg: accelerators)
//
//         // got to hWndStop user::interaction without interest
//         if (pinteraction == puiStop)
//            break;
//
//      }
//      // no special processing
//   }


//   bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
//   {
//
//      return false;
//
//   }
//
//   bool PASCAL interaction_impl::ReflectLastMsg(oswindow hWndChild, LRESULT* pResult)
//   {
//      // get the ::collection::map, and if no ::collection::map, then this message does not need reflection
//      /*      single_lock sl(afxMutexHwnd(), TRUE);
//       hwnd_map * pMap = afxMapHWND();
//       if (pMap == nullptr)
//       return FALSE;
//
//       // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
//       ::user::interaction * pWnd = dynamic_cast < ::user::interaction * > (pMap->lookup_permanent(hWndChild)); */
//      ::user::interaction * pWnd = dynamic_cast <::user::interaction *> (FromHandlePermanent(hWndChild));
//      ASSERT(pWnd == nullptr || pWnd->get_handle() == hWndChild);
//      if (pWnd == nullptr)
//      {
//         return FALSE;
//      }
//
//      // only OLE controls and permanent windows will get reflected msgs
//      ASSERT(pWnd != nullptr);
//      __throw(todo());
//      //return pWnd->SendChildNotifyLastMsg(pResult);
//
//      return FALSE;
//   }

//   bool interaction_impl::OnChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//   {
//
//      return ReflectChildNotify(uMsg, wparam, lparam, pResult);
//   }

//   bool interaction_impl::ReflectChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//   {
//      UNREFERENCED_PARAMETER(wparam);
//      // Note: reflected messages are m_puserinteraction->send directly to interaction_impl::OnWndMsg
//      //  and interaction_impl::_001OnCommand for speed and because these messages are not
//      //  routed by normal _001OnCommand routing (they are only dispatched)
//
//      switch (uMsg)
//      {
//      // normal messages (just wparam, lparam through OnWndMsg)
//      case WM_HSCROLL:
//      case WM_VSCROLL:
//      case WM_PARENTNOTIFY:
//      case WM_DRAWITEM:
//      case WM_MEASUREITEM:
//      case WM_DELETEITEM:
//      case WM_VKEYTOITEM:
//      case WM_CHARTOITEM:
//      case WM_COMPAREITEM:
//         // reflect the message through the message ::collection::map as WM_REFLECT_BASE+uMsg
//         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wparam, lparam, pResult);
//         return FALSE;
//
//      // special case for WM_COMMAND
//      case WM_COMMAND:
//      {
//         // reflect the message through the message ::collection::map as OCM_COMMAND
//         /* xxx         i32 nCode = HIWORD(wparam);
//          if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_COMMAND), nullptr, nullptr))
//          {
//          if (pResult != nullptr)
//          *pResult = 1;
//          return TRUE;
//          } */
//      }
//      break;
//
//      // special case for WM_NOTIFY
//      /*      case WM_NOTIFY:
//       {
//       // reflect the message through the message ::collection::map as OCM_NOTIFY
//       NMHDR* pNMHDR = (NMHDR*)lparam;
//       //            i32 nCode = pNMHDR->code;
//       //            __NOTIFY notify;
//       //          notify.pResult = pResult;
//       //        notify.pNMHDR = pNMHDR;
//       // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
//       }
//
//       // other special cases (WM_CTLCOLOR family)*/
//      default:
//         if (uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
//         {
//            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
//            /*__CTLCOLOR ctl;
//             ctl.hDC = (HDC)wparam;
//             ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
//             //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
//             ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);
//
//             // reflect the message through the message ::collection::map as OCM_CTLCOLOR
//             bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
//             if ((HBRUSH)*pResult == nullptr)
//             bResult = FALSE;
//             return bResult;*/
//            return false;
//         }
//         break;
//      }
//
//      return false;   // let the parent handle it
//   }

//   void interaction_impl::OnParentNotify(UINT message, LPARAM lparam)
//   {
//      if ((LOWORD(message) == WM_CREATE || LOWORD(message) == WM_DESTROY))
//      {
//         if (ReflectLastMsg((oswindow)lparam))
//            return;     // eat it
//      }
//      // not handled - do default
//      Default();
//   }

//   void interaction_impl::OnSetFocus(::user::interaction *)
//   {
//      bool bHandled;
//
//      bHandled = FALSE;
//      if (!bHandled)
//      {
//         Default();
//      }
//   }
//
//
//   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wparam, LPARAM)
//   {
//
//      return 0;
//
//   }
//
//   void interaction_impl::OnSysColorChange()
//   {
//      __throw(not_implemented());
//
//      /*      application* pApp = &System;
//       if (pApp != nullptr && pApp->GetMainWnd() == this)
//       {
//       // recolor global brushes used by control bars
//       afxData.UpdateSysColors();
//       }
//
//       // forward this message to all other child windows
//       if (!(GetStyle() & WS_CHILD))
//       send_message_to_descendants(WM_SYSCOLORCHANGE, 0, 0L, TRUE, TRUE);
//
//       Default();*/
//   }
//
//   bool gen_GotScrollLines;
//
//   void interaction_impl::OnSettingChange(UINT uFlags, const char * lpszSection)
//   {
//      //      UNUSED_ALWAYS(uFlags);
//      //    UNUSED_ALWAYS(lpszSection);
//
//      // force refresh of settings that we cache
//      gen_GotScrollLines = FALSE;
//
//
//      interaction_impl::OnDisplayChange(0, 0);    // to update system metrics, etc.
//   }

   /*   void interaction_impl::OnDevModeChange(__in LPTSTR lpDeviceName)
    {
    UNREFERENCED_PARAMETER(lpDeviceName);
    __throw(not_implemented());
    application* pApp = &System;
    if (pApp != nullptr && pApp->GetMainWnd() == this)
    pApp->DevModeChange(lpDeviceName);

    // forward this message to all other child windows
    if (!(GetStyle() & WS_CHILD))
    {
    const MESSAGE* pMsg = GetCurrentMessage();
    send_message_to_descendants(pMsg->message, pMsg->wparam, pMsg->lparam,
    TRUE, TRUE);
    }*/
   //}


   //
   //   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   //   {
   //      if (!(GetStyle() & WS_CHILD))
   //      {
   //         ::user::interaction* pMainWnd = System.GetMainWnd();
   //         if (pMainWnd != nullptr &&
   //            GetKeyState(VK_SHIFT) >= 0 &&
   //            GetKeyState(VK_CONTROL) >= 0 &&
   //            GetKeyState(VK_MENU) >= 0)
   //         {
   //            //            pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
   //            return TRUE;
   //         }
   //      }
   //      return Default() != 0;
   //   }
   //
//   LRESULT interaction_impl::OnDisplayChange(WPARAM, LPARAM)
//   {
//      if (!(GetStyle() & WS_CHILD))
//      {
//         const MESSAGE* pMsg = GetCurrentMessage();
//         send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam, TRUE, TRUE);
//      }
//
//      return Default();
//   }

//   LRESULT interaction_impl::OnDragList(WPARAM, LPARAM lparam)
//   {
//
//      __throw(not_implemented());
//      //
//      //      LPDRAGLISTINFO lpInfo = (LPDRAGLISTINFO)lparam;
//      //      ASSERT(lpInfo != nullptr);
//      //
//      //      LRESULT lResult;
//      //      if (ReflectLastMsg(lpInfo->hWnd, &lResult))
//      //         return (i32)lResult;    // eat it
//      //
//      //      // not handled - do default
//      //      return (i32)Default();
//   }


   void interaction_impl::_thread_prodevian()
   {

//      DWORD tickStart;
//
//      bool bUpdateScreen = false;
//
//      while (::thread_get_run())
//      {
//
//         try
//         {
//auto tickStart = ::tick::now();
//
//            if(m_puserinteraction == nullptr)
//            {
//
//               break;
//
//            }
//
//            if(m_oswindow != nullptr)
//            {
//
//               m_oswindow->m_bNsWindowRect = false;
//
//            }
//
//            if (!m_puserinteraction->m_bLockWindowUpdate)
//            {
//
//               bool bUpdateBuffer = m_puserinteraction->m_bProDevian || m_puserinteraction->_001UpdateVisual();
//
//               if(bUpdateBuffer)
//               {
//
//               }
//               else if(m_puserinteraction->is_window_visible())
//               {
//
//                  bUpdateBuffer = m_puserinteraction->has_pending_graphical_update();
//
//               }
//
//               if(bUpdateBuffer)
//               {
//
//                  _001UpdateBuffer();
//
//                  if(m_puserinteraction == nullptr)
//                  {
//
//                     break;
//
//                  }
//
//                  m_puserinteraction->on_after_graphical_update();
//
//                  bUpdateScreen = true;
//
//               }
//
//            }
//
//            if(bUpdateScreen)
//            {
//
//               u64 now = get_nanos();
//
//               u64 delta1 = now - m_uiLastUpdateBeg;
//
//               i64 delta2 = (i64) m_uiLastUpdateBeg - (i64) m_uiLastUpdateEnd;
//
//               u64 frameNanos = 1000000000LL / get_config_fps();
//
//               if(delta1 < frameNanos || (delta2 > 0 && delta2 < 10000000000LL))
//               {
//
//                  output_debug_string("opt_out set need redraw");
//
//               }
//               else
//               {
//
//                  bUpdateScreen = false;
//
//                  _001UpdateScreen();
//
//               }
//
//            }
//
//            DWORD dwSpan = tickStart.elapsed();
//
//            if (dwSpan < 50)
//            {
//
//               Sleep(50 - dwSpan);
//
//            }
//
//         }
//         catch(...)
//         {
//
//            break;
//
//         }
//
//      }
//
//      output_debug_string("m_pthreadDraw has finished!");
//
   }


   void interaction_impl::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      default_message_handler(pmessage);

      if (m_puserinteraction->is_message_only_window())
      {

         TRACE("good : opt out!");

      }
      else
      {

      }

      if(::is_null(g_pappPreTranslateMouseMessage))
      {

         g_pappPreTranslateMouseMessage = System.value("pre_translate_mouse_message").cast < ::aura::application >();

      }

   }


   void interaction_impl::release_graphics_resources()
   {

      __release(m_pgraphics);


   }


   void interaction_impl::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction_impl::_001OnTimer(ptimer);;

//      if (ptimer->m_nIDEvent == 2049)
      //    {
//
      //       set_need_redraw();
//
      //    }

   }


   /*


      void interaction_impl::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
      {
         UNREFERENCED_PARAMETER(pScrollBar);
         Default();
      }

      void interaction_impl::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
      {
         UNREFERENCED_PARAMETER(pScrollBar);
         Default();
      }
      */
   bool CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lparam)
   {
      user::oswindow_array * phwnda = (user::oswindow_array *) lparam;
      phwnda->add(hwnd);
      return TRUE;
   }

   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   {

      __throw(not_implemented());
      //      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
   }

   /*   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
    {
    _001DeferPaintLayeredWindowBackground(pgraphics);
    }*/


   class print_window :
      virtual ::object
   {
   public:



      manual_reset_event m_event;
      oswindow m_hwnd;
      HDC m_hdc;

      print_window(::object * pobject, oswindow hwnd, HDC hdc, DWORD tickTimeout) :
         ::object(pobject)

      {
         m_event.ResetEvent();
         m_hwnd = hwnd;
         m_hdc = hdc;
         //begin_thread(pobject, &print_window::s_print_window, (LPVOID) this, ::priority_normal);
         //if (m_event.wait(millis(tickTimeout)).timeout())
         //{
         // TRACE("print_window::time_out");
         // }
      }
   };


//   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
//   {
//
//      //::rect rectClient;
//
//      //get_client_rect(rectClient);
//
//
//      //pgraphics->FillSolidRect(rectClient, 0x00000000);
//
//      //return;
//
//      //auto rectUpdate = get_window_rect();
//
//      //      SetViewportOrgEx(hdc, 0, 0, nullptr);
//
//      //::rect rectPaint;
//
//      //rectPaint = rectUpdate;
//
//      //_001ScreenToClient(rectPaint);
//
//      //user::oswindow_array wndaApp;
//
//
//
//   }


   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //      System.get_event(get_context_application()->get_context_application())->SetEvent();
      //    System.get_event(System.get_twf())->wait(millis(8400));
   }

   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {

      //lock lock(m_puserinteraction, 2000);

      __throw(not_implemented());

   }


   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {
      __throw(not_implemented());
      //      SCAST_PTR(::message::base, pbase, pmessage);
      //
      //      if(pbase->m_wparam == nullptr)
      //         return;
      //
      //      ::draw2d::graphics_pointer graphics(get_object());
      //      WIN_DC(graphics.m_p)->Attach((HDC) pbase->m_wparam);
      //      ::rect rectx;
      //      ::draw2d::bitmap * pbitmap = &pgraphics->GetCurrentBitmap();
      //      ::GetCurrentObject((HDC) pbase->m_wparam, OBJ_BITMAP);
      //      //      DWORD dw = ::get_last_error();
      //      ::size size = pbitmap->get_size();
      //      rectx.left = 0;
      //      rectx.top = 0;
      //      rectx.right = size.cx;
      //      rectx.bottom = size.cy;
      //      try
      //      {
      //         ::rect rectWindow;
      //         get_window_rect(rectWindow);
      //
      //         ::image_pointer pimage(get_object());
      //         if(!pimage = create_image(rectWindow.bottom_right()))
      //            return;
      //
      //         ::draw2d::graphics_pointer & pgraphics = pimage->get_graphics();
      //
      //         if(pgraphics->get_handle() == nullptr)
      //            return;
      //
      //         ::rect rectPaint;
      //         ::rect rectUpdate;
      //         rectUpdate = rectWindow;
      //         rectPaint = rectWindow;
      //         rectPaint.offset(-rectPaint.top_left());
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
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SetViewportOrg(::point());
      //         _000OnDraw(pgraphics);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SetViewportOrg(::point());
      //         //(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SetViewportOrg(::point());
      //
      //         pgraphics->SelectClipRgn( nullptr);
      //         pgraphics->BitBlt(rectPaint.left, rectPaint.top,
      //            rectPaint.width(), rectPaint.height(),
      //            pgraphics, rectUpdate.left, rectUpdate.top,
      //            SRCCOPY);
      //
      //         pgraphics->text_out(0, 0, "Te Amo Carlinhos!!", 11);
      //      }
      //      catch(...)
      //      {
      //      }
      //      pgraphics->FillSolidRect(rectx, RGB(255, 255, 255));
      //      WIN_DC(graphics.m_p)->Detach();
      //      pmessage->m_bRet = true;
      //      pbase->set_lresult(0);
   }


//   void interaction_impl::OnEnterIdle(UINT /*nWhy*/, ::user::interaction * /*pWho*/)
//   {
//      // In some OLE inplace active scenarios, OLE will m_puserinteraction->send a
//      // message instead of sending it.  This causes so many WM_ENTERIDLE
//      // messages to be sent that tasks running in the background stop
//      // running.  By dispatching the pending WM_ENTERIDLE messages
//      // when the first one is received, we trick oswindows into thinking
//      // that only one was really sent and dispatched.
//      {
//         //         MESSAGE msg;
//         __throw(not_implemented());
//         //while (PeekMessage(&msg, nullptr, WM_ENTERIDLE, WM_ENTERIDLE, PM_REMOVE))
//         //while (PeekMessage(&msg, ::caNULL, WM_ENTERIDLE, WM_ENTERIDLE, TRUE))
//         // DispatchMessage(&msg);
//      }
//
//      //Default();
//   }

   HBRUSH interaction_impl::OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction * pWnd, UINT)
   {
//      ASSERT(pWnd != nullptr && pWnd->get_handle() != nullptr);
//      LRESULT lResult;
//      if (pWnd->SendChildNotifyLastMsg(&lResult))
//         return (HBRUSH)lResult;     // eat it
//      return (HBRUSH)Default();
      __throw(todo());
      return nullptr;
   }

   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any user::interaction containing controls)
   //  return value of FALSE means caller must call DefWindowProc's default
   //  TRUE means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
//   bool PASCAL interaction_impl::GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
//         HBRUSH hbrGray, COLORREF clrText)
//   {
//
//      __throw(not_implemented());
//      //      if (hDC == nullptr)
//      //      {
//      //         // sometimes Win32 passes a nullptr hDC in the WM_CTLCOLOR message.
//      //         //         TRACE(::ca2::trace::category_AppMsg, 0, "Warning: hDC is nullptr in interaction_impl::GrayCtlColor; WM_CTLCOLOR not processed.\n");
//      //         return FALSE;
//      //      }
//      //
//      //      if (hbrGray == nullptr ||
//      //         nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX ||
//      //         nCtlColor == CTLCOLOR_SCROLLBAR)
//      //      {
//      //         return FALSE;
//      //      }
//      //
//      //      if (nCtlColor == CTLCOLOR_LISTBOX)
//      //      {
//      //         // only handle requests to draw the space between edit and drop button
//      //         //  in a drop-down combo (not a drop-down list)
//      //         if (!__is_combo_box_control(hWnd, (UINT)CBS_DROPDOWN))
//      //            return FALSE;
//      //      }
//      //
//      //      // set background color and return handle to brush
//      //      LOGBRUSH logbrush;
//      //      VERIFY(::GetObject(hbrGray, sizeof(LOGBRUSH), (LPVOID)&logbrush));
//      //      ::SetBkColor(hDC, logbrush.lbColor);
//      //      if (clrText == (COLORREF)-1)
//      //         clrText = ::GetSysColor(COLOR_WINDOWTEXT);  // normal text
//      //      ::SetTextColor(hDC, clrText);
//      //      return TRUE;
//   }



   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child user::interaction)

   void interaction_impl::CenterWindow(::user::interaction *  pAlternateOwner)
   {
      __throw(not_implemented());
   }

//   bool interaction_impl::CheckAutoCenter()
//   {
//      return TRUE;
//   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
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
          return FALSE;
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
         __throw(not_implemented());
         //         UnlockResource(hResource);
      }
      return bResult;
   }

   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {
      __throw(not_implemented());
   }

   void interaction_impl::UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      ::user::command state(get_context_object());
      user::interaction wndTemp;       // very temporary user::interaction just for CmdUI update

      // walk all the kids - assume the IDs are for buttons
      /* xxx   for (oswindow hWndChild = ::GetTopWindow(get_handle()); hWndChild != nullptr;
       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
       {
       // m_puserinteraction->send to buttons
       wndTemp.set_handle(hWndChild); // quick and dirty attach
       state.m_nID = __get_dialog_control_id(hWndChild);
       state.m_pOther = &wndTemp;

       // check for reflect handlers in the child user::interaction
       ::user::interaction * pWnd = ::macos::interaction_impl::FromHandlePermanent(hWndChild);
       if (pWnd != nullptr)
       {
       // call it directly to disable any routing
       if (MAC_WINDOW(pWnd)->interaction_impl::_001OnCommand(0, MAKELONG(0xffff,
       WM_COMMAND+WM_REFLECT_BASE), &state, nullptr))
       continue;
       }

       // check for handlers in the parent user::interaction
       if (interaction_impl::_001OnCommand((UINT)state.m_nID, CN_UPDATE_::user::command, &state, nullptr))
       continue;

       // determine whether to disable when no handler exists
       bool bDisableTemp = bDisableIfNoHndler;
       if (bDisableTemp)
       {
       if ((wndTemp.SendMessage(WM_GETDLGCODE) & DLGC_BUTTON) == 0)
       {
       // non-button controls don't get automagically disabled
       bDisableTemp = FALSE;
       }
       else
       {
       // only certain button controls get automagically disabled
       UINT nStyle = (UINT)(wndTemp.GetStyle() & 0x0F);
       if (nStyle == (UINT)BS_AUTOCHECKBOX ||
       nStyle == (UINT)BS_AUTO3STATE ||
       nStyle == (UINT)BS_GROUPBOX ||
       nStyle == (UINT)BS_AUTORADIOBUTTON)
       {
       bDisableTemp = FALSE;
       }
       }
       }
       // check for handlers in the target (owner)
       state.DoUpdate(pTarget, bDisableTemp);
       }
       wndTemp.set_handle(nullptr);      // quick and dirty detach */
   }


//   bool interaction_impl::IsFrameWnd()
//   {
//      return FALSE;
//   }

   bool interaction_impl::SubclassWindow(oswindow hWnd)
   {
      if (!Attach(hWnd))
         return FALSE;

      // allow any other subclassing to occur
      pre_subclass_window();

      __throw(not_implemented());
   }

   oswindow interaction_impl::UnsubclassWindow()
   {
      ASSERT(::is_window(get_handle()));

      __throw(not_implemented());
      //      // set WNDPROC back to original value
      //      WNDPROC* lplpfn = GetSuperWndProcAddr();
      //      SetWindowLongPtr(get_handle(), GWLP_WNDPROC, (iptr)*lplpfn);
      //      *lplpfn = nullptr;
      //
      //      // and Detach the oswindow from the user::interaction object
      //      return Detach();
   }


   bool interaction_impl::IsChild(::user::interaction *  pWnd)
   {
      ASSERT(::is_window(get_handle()));
      if (pWnd->get_handle() == nullptr)
      {
         return ::user::interaction_impl::is_child(pWnd);
      }
      else
      {
         //         return ::IsChild(get_handle(), MAC_WINDOW(pWnd)->get_handle()) != FALSE;
         return FALSE;
      }
   }


   bool interaction_impl::_is_window() const
   {

      return ::is_window(m_oswindow) != FALSE;

   }


   ::user::interaction * interaction_impl::get_wnd() const
   {

      return m_puserinteraction;

   }


//   void interaction_impl::MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight, bool bRepaint)
//   {
//
//      ASSERT(::is_window(get_handle()));
//
//      set_window_pos(zorder_none, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);
//
//   }


//   pointd interaction_impl::client_screen_top_left()
//   {
//
//      ::rect64 rectWindow;
//
//      if (!m_puserinteraction->get_window_rect(rectWindow))
//      {
//
//         return point(0.0, 0.0);
//
//      }
//
//      return rectWindow.top_left();
//
//   }


//   bool interaction_impl::get_window_rect(RECT64 * lprect)
//   {
//
//      return ::user::interaction_impl::get_window_rect(lprect);
//
//   }
//
//
//   bool interaction_impl::get_client_rect(RECT64 * lprect)
//   {
//
//      if (!::is_window(get_handle()))
//      {
//
//         return false;
//
//      }
//
//      ::rect rect32;
//
//      if (!::get_client_rect(get_handle(), rect32))
//      {
//
//         return false;
//
//      }
//
//      ::copy(lprect, rect32);
//
//      return true;
//
//   }
//
//
   id interaction_impl::SetDlgCtrlId(id id)
   {

      return m_puserinteraction->SetDlgCtrlId((id));

   }


   id interaction_impl::GetDlgCtrlId()
   {

      return m_puserinteraction->GetDlgCtrlId();

   }


//   void interaction_impl::window_impl_maximize()()
//   {
//
//      ::user::interaction_impl::_001WindowMaximize();
//
//   }
//
//
//   void interaction_impl::_001WindowRestore()
//   {
//
//      m_puserinteraction->m_edisplay = user::display_normal;
//
//      if (m_puserinteraction != nullptr)
//      {
//
//         m_puserinteraction->m_edisplay = user::display_normal;
//
//      }
//
//   }


   void interaction_impl::show_task(bool bShow)
   {

      if(bShow)
      {

         defer_dock_application(true);

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

      }
      else
      {

         defer_dock_application(false);

      }

   }


//   bool interaction_impl::ShowWindow(i32 nCmdShow)
//   {
//
//      return ::user::interaction_impl::ShowWindow(nCmdShow);
//
////      if (!::is_window(get_handle()))
////      {
////
////         return false;
////
////      }
////
////      if(nCmdShow <= SW_HIDE)
////      {
////
////         round_window_hide();
////
////
////      }
////      else
////      {
////
////         ::show_window(get_handle(), nCmdShow);
////
////         //m_puserinteraction->send_message(WM_SHOWWINDOW, ::IsWindowVisible(get_handle()));
////
////      }
////
////      //deferred_on_change_visibility();
////
////      return m_puserinteraction->is_window_visible();
//
//   }


   bool interaction_impl::window_impl_is_iconic()
   {

      if(!::is_window(get_handle()))
      {
         return false;
      }

      return m_puserinteraction->layout().is_iconic();

   }


   ::user::interaction * interaction_impl::GetParent() const
   {

      return nullptr;

   }


   LONG interaction_impl::GetWindowLong(i32 nIndex)
   {

      return ::GetWindowLong(get_handle(), nIndex);

   }


   LONG interaction_impl::SetWindowLong(i32 nIndex, LONG lValue)
   {

      return ::SetWindowLong(get_handle(), nIndex, lValue);

   }


   DWORD interaction_impl::GetStyle() const
   {

      ASSERT(::is_window(get_handle()));

      return (DWORD)::GetWindowLong(get_handle(), GWL_STYLE);

   }


   DWORD interaction_impl::GetExStyle() const
   {

      ASSERT(::is_window(get_handle()));

      return (DWORD)::GetWindowLong(get_handle(), GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      ASSERT(::is_window(get_handle()));

      return ModifyStyle(get_handle(), dwRemove, dwAdd, nFlags);

   }


   bool interaction_impl::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      ASSERT(::is_window(get_handle()));

      return ModifyStyleEx(get_handle(), dwRemove, dwAdd, nFlags);

   }


   ::user::interaction *  interaction_impl::SetOwner(::user::interaction *  pOwnerWnd)
   {

      return nullptr;

   }


   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)
   {

      return ::user::interaction_impl::send_message(message, wparam, lparam);

   }


   bool interaction_impl::post_message(UINT message, WPARAM wparam, lparam lparam)
   {

      if (m_puserinteraction->m_pthreadUserInteraction == nullptr)
      {

         return false;

      }
      
      auto pmq = m_puserinteraction->m_pthreadUserInteraction->get_mq();

      return pmq->post_message(m_oswindow, message, wparam, lparam);

      //return ::post_message((oswindow) m_oswindow, message, wparam, lparam);

   }


//   bool interaction_impl::DragDetect(const ::point & point) const
//   {
//
//      __throw(not_implemented());
//
//      return true;
//
//   }


   void interaction_impl::set_window_text(const char * lpszString)
   {

      m_strWindowText = lpszString;

      round_window_set_title(m_strWindowText);

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      __throw(not_implemented());

   }


//   void interaction_impl::MoveWindow(LPCRECT lpRect, bool bRepaint)
//   {
//
//      MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
//
//   }


   UINT interaction_impl::ArrangeIconicWindows()
   {

      __throw(not_implemented());

   }


   i32 interaction_impl::SetWindowRgn(HRGN hRgn, bool bRedraw)
   {

      __throw(not_implemented());

   }


   i32 interaction_impl::GetWindowRgn(HRGN hRgn)
   {

      __throw(not_implemented());

   }


//   void interaction_impl::bring_to_top(::edisplay edisplay)
//   {
//
//      ::user::interaction_impl::bring_to_top(edisplay);
//
////      return;
////
////      if (nCmdShow > SW_HIDE && nCmdShow != SW_MINIMIZE)
////      {
////
////         BringWindowToTop();
////
////         //round_window_show();
////
////      }
//
//   }


//   bool interaction_impl::BringWindowToTop()
//   {
//
//      bool b = ::BringWindowToTop(get_handle()) != FALSE;
//
//      return b;
//
//   }


//   void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPPOINT lpPoint, UINT nCount)
//   {
//
//      __throw(not_implemented());
//
//   }
//
//
//   void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPRECT lpRect)
//   {
//
//      __throw(not_implemented());
//
//   }
//
//
//   ::draw2d::graphics * interaction_impl::GetDC()
//   {
//
//      return nullptr;
//
//   }
//
//
//   ::draw2d::graphics * interaction_impl::GetWindowDC()
//   {
//
//      return nullptr;
//
//   }
//
//
//   bool interaction_impl::ReleaseDC(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      if (pgraphics == nullptr)
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


   void interaction_impl::UpdateWindow()
   {

      __throw(not_implemented());

   }


   void interaction_impl::SetRedraw(bool bRedraw)
   {

      __throw(not_implemented());

   }


   bool interaction_impl::GetUpdateRect(LPRECT lpRect, bool bErase)
   {

      __throw(not_implemented());

   }


   i32 interaction_impl::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {

      __throw(not_implemented());

   }


   void interaction_impl::Invalidate(bool bErase)
   {

      m_bNeedsUpdate = true;

   }


   void interaction_impl::InvalidateRect(const ::rect & rect, bool bErase)
   {

      __throw(not_implemented());

   }


   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {

      __throw(not_implemented());

   }


   void interaction_impl::ValidateRect(const ::rect & rect)
   {

      __throw(not_implemented());

   }


   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {

      __throw(not_implemented());

   }


//   bool interaction_impl::window_impl_is_visible()
//   {
//
//      if (!::is_window(get_handle()))
//      {
//
//         return false;
//
//      }
//
////      if (m_puserinteraction != nullptr)
////      {
////
////         if (!m_puserinteraction->is_this_visible())
////         {
////
////            return false;
////
////         }
////
////         if (m_puserinteraction->GetParent() != nullptr && !m_puserinteraction->GetParent()->is_window_visible())
////         {
////
////            return false;
////
////         }
////
////      }
//
//      if (!::IsWindowVisible(get_handle()))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      __throw(not_implemented());

   }


//   void interaction_impl::send_message_to_descendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
//   {
//
//      ASSERT(::is_window(get_handle()));
//
//      // walk through oswindows to avoid creating temporary user::interaction objects
//      // unless we need to call this function recursively
//      user::interaction * pinteraction = m_puserinteraction->top_child();
//
//      while (pinteraction != nullptr)
//      {
//
//         try
//         {
//
//            pinteraction->send_message(message, wparam, lparam);
//
//         }
//         catch (...)
//         {
//
//         }
//
//         if (bDeep)
//         {
//
//            // m_puserinteraction->send to child windows after parent
//
//            try
//            {
//
//               pinteraction->send_message_to_descendants(message, wparam, lparam, bDeep, bOnlyPerm);
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//
//         try
//         {
//
//            pinteraction = pinteraction->under_sibling();
//
//         }
//         catch (...)
//         {
//
//            break;
//
//         }
//
//      }
//
//   }



//   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region* prgnClip, DWORD flags)
//   {
//
//      __throw(not_implemented());
//
//   }


   bool interaction_impl::LockWindowUpdate()
   {

      __throw(not_implemented());

   }


   void interaction_impl::UnlockWindowUpdate()
   {

      __throw(not_implemented());

   }


   void interaction_impl::on_show_window()
   {

      ::user::interaction_impl::on_show_window();

//      if(show_window_is_visible(m_puserinteraction->m_iShowWindowRequest))
//      {
//
//         round_window_show();
//
//      }
//      else if(show_window_is_visible(m_puserinteraction->m_iShowWindowRequest))
//      {
//
//         round_window_hide();
//
//      }

   }


   void interaction_impl::on_zorder()
   {

//      if (m_bZ)
//      {
//
//         ::set_window_pos(m_oswindow, (oswindow) m_iZ,
//                        0,
//                        0,
//                        0,
//                        0,
//                        SWP_NOSIZE
//                        | SWP_NOMOVE
//                        | (m_bZ ? 0 : SWP_NOZORDER)
//                        | SWP_NOREDRAW
//                        | SWP_NOCOPYBITS
//                        | SWP_NOACTIVATE
//                        | SWP_NOOWNERZORDER
//                        | SWP_NOSENDCHANGING
//                        | SWP_DEFERERASE);
//
//         m_bZ = false;
//
//      }

      //::user::interaction_impl::on_reposition();

   }


   void interaction_impl::on_reposition()
   {

//      if (m_rectLastOsPlacement.top_left() != m_puserinteraction.m_rectParentClientRequest.top_left())
//      {
//
//         ::set_window_pos(m_oswindow, (oswindow) m_iZ,
//                        (int) m_puserinteraction->m_rectParentClientRequest.left,
//                        (int) m_puserinteraction->m_rectParentClientRequest.top,
//                        0,
//                        0,
//                        SWP_NOSIZE
//                        | (m_bZ ? 0 : SWP_NOZORDER)
//                        | SWP_NOREDRAW
//                        | SWP_NOCOPYBITS
//                        | SWP_NOACTIVATE
//                        | SWP_NOOWNERZORDER
//                        | SWP_NOSENDCHANGING
//                        | SWP_DEFERERASE);
//
//         m_rectLastOsPlacement.move_to(m_puserinteraction.m_rectParentClientRequest.top_left());
//
//      }

      //::user::interaction_impl::on_reposition();

   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

//      if (m_rectLastOsPlacement != m_puserinteraction.m_rectParentClientRequest)
//      {
//
//         ::set_window_pos(m_oswindow, (oswindow) m_iZ,
//                        (int) m_puserinteraction->m_rectParentClientRequest.left,
//                        (int) m_puserinteraction->m_rectParentClientRequest.top,
//                        (int) m_puserinteraction->m_rectParentClientRequest.width(),
//                        (int) m_puserinteraction->m_rectParentClientRequest.height(),
//                        (m_bZ ? 0 : SWP_NOZORDER)
//                        | SWP_NOREDRAW
//                        | SWP_NOCOPYBITS
//                        | SWP_NOACTIVATE
//                        | SWP_NOOWNERZORDER
//                        | SWP_NOSENDCHANGING
//                        | SWP_DEFERERASE);
//
//         m_puserinteraction->m_rectParentClient = m_puserinteraction.m_rectParentClientRequest;
//
//         m_rectLastOsPlacement = m_puserinteraction.m_rectParentClientRequest;
//
//      }

      //::user::interaction_impl::on_layout(pgraphics);

   }


   void interaction_impl::_001UpdateScreen()
   {



      if (m_puserinteraction->is_window_visible())
      {

         round_window_redraw();

      }

   }


//   bool interaction_impl::DrawAnimatedRects(i32 idAni, CONST RECT *lprcFrom, CONST RECT * lprcTo)
//   {
//
//      __throw(not_implemented());
//
//   }


   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, UINT uFlags)
   {

      __throw(not_implemented());

      return false;

   }


   bool interaction_impl::SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer)
   {

      return ::user::interaction_impl::SetTimer(nIDEvent, nElapse, pfnTimer);

   }


   bool interaction_impl::KillTimer(uptr nIDEvent)
   {

      return ::user::interaction_impl::KillTimer(nIDEvent);

   }


   bool interaction_impl::IsWindowEnabled()
   {

      return true;

   }


   bool interaction_impl::enable_window(bool bEnable)
   {

      m_bEnabled = bEnable;

      return true;

   }


   ::user::interaction *  interaction_impl::GetActiveWindow()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::get_active_window());

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      try
      {

         return pimpl->m_puserinteraction;

      }
      catch(...)
      {

      }

      return nullptr;

   }


   ::user::interaction *  interaction_impl::SetActiveWindow()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::set_active_window(get_handle()));

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::user::interaction *  interaction_impl::GetFocus()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::get_focus());

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   bool  interaction_impl::SetFocus()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::set_focus(get_handle()));

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
         {

            return nID; // id that matched

         }

      }

      return 0; // invalid ID

   }


   void interaction_impl::CheckDlgButton(i32 nIDButton, UINT nCheck)
   {

      __throw(not_implemented());

   }


   void interaction_impl::CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton)
   {

      __throw(not_implemented());

   }


   i32 interaction_impl::DlgDirList(LPTSTR lpPathSpec, i32 nIDListBox, i32 nIDStaticPath, UINT nFileType)
   {

      __throw(not_implemented());

   }


   i32 interaction_impl::DlgDirListComboBox(LPTSTR lpPathSpec, i32 nIDComboBox, i32 nIDStaticPath, UINT nFileType)
   {

      __throw(not_implemented());

   }


   bool interaction_impl::DlgDirSelect(LPTSTR lpString, i32 nSize, i32 nIDListBox)
   {

      __throw(not_implemented());

   }


   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString, i32 nSize, i32 nIDComboBox)
   {

      __throw(not_implemented());

   }


   ::user::interaction * interaction_impl::GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious) const
   {

      __throw(not_implemented());

   }


   ::user::interaction * interaction_impl::GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious) const
   {

      __throw(not_implemented());

   }


   UINT interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   {

      __throw(not_implemented());

   }


   LPARAM interaction_impl::SendDlgItemMessage(i32 nID, UINT message, WPARAM wparam, LPARAM lparam)
   {

      __throw(not_implemented());

   }


   void interaction_impl::SetDlgItemInt(i32 nID, UINT nValue, bool bSigned)
   {

      __throw(not_implemented());

   }


   void interaction_impl::SetDlgItemText(i32 nID, const char * lpszString)
   {

      __throw(not_implemented());

   }


   i32 interaction_impl::ScrollWindowEx(i32 dx, i32 dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
   {

      __throw(not_implemented());

   }


   void interaction_impl::ShowScrollBar(UINT nBar, bool bShow)
   {

      __throw(not_implemented());

   }


   ::user::interaction *  interaction_impl::ChildWindowFromPoint(const ::point & point)
   {

      __throw(not_implemented());

   }


   ::user::interaction *  interaction_impl::ChildWindowFromPoint(const ::point & point, UINT nFlags)
   {

      __throw(not_implemented());

   }





   ::user::interaction *  interaction_impl::GetNextWindow(UINT nFlag)
   {

      return nullptr;

   }


   ::user::interaction *  interaction_impl::GetTopWindow()
   {

      if (m_puserinteraction->m_uiptraChild.get_size() <= 0)
         return nullptr;

      return m_puserinteraction->m_uiptraChild[0];

   }


   ::user::interaction *  interaction_impl::GetWindow(UINT nCmd)
   {

      ASSERT(::is_window(get_handle()));

      return nullptr;

   }


   ::user::interaction *  interaction_impl::GetLastActivePopup()
   {

      __throw(todo());

   }


   ::user::interaction * interaction_impl::SetParent(::user::interaction * pWndNewParent)
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::SetParent(get_handle(), (oswindow)pWndNewParent->get_handle()));

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::user::interaction * PASCAL interaction_impl::oswindowFromPoint(POINT point)
   {

      __throw(not_implemented());

   }


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::FlashWindow(get_handle(), bInvert) != FALSE;

   }

   bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::ChangeClipboardChain(get_handle(), hWndNext) != FALSE;

   }

   oswindow interaction_impl::SetClipboardViewer()
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::SetClipboardViewer(get_handle());

   }

   bool interaction_impl::OpenClipboard()
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::OpenClipboard(get_handle()) != FALSE;

   }

   ::user::interaction * PASCAL interaction_impl::GetOpenClipboardWindow()
   {

      __throw(not_implemented());
      //      return ::macos::interaction_impl::from_handle(::GetOpenClipboardWindow());

   }

   ::user::interaction * PASCAL interaction_impl::GetClipboardOwner()
   {

      __throw(not_implemented());
      //      return ::macos::interaction_impl::from_handle(::GetClipboardOwner());

   }

   ::user::interaction * PASCAL interaction_impl::GetClipboardViewer()
   {

      __throw(not_implemented());
      //      return ::macos::interaction_impl::from_handle(::GetClipboardViewer());

   }



   point PASCAL interaction_impl::GetCaretPos()
   {

      __throw(not_implemented());
      //      ::point point;
      //      ::GetCaretPos((LPPOINT)&point); return point;

   }

   void PASCAL interaction_impl::SetCaretPos(POINT point)
   {

      __throw(not_implemented());
      //      ::SetCaretPos(point.x, point.y);

   }

   void interaction_impl::HideCaret()
   {

      __throw(not_implemented());
      //      ::HideCaret(get_handle());

   }

   void interaction_impl::ShowCaret()
   {

      __throw(not_implemented());
      //    ::ShowCaret(get_handle());

   }

   bool interaction_impl::SetForegroundWindow()
   {

      bool b = ::SetForegroundWindow(get_handle()) != FALSE;

      //      round_window_show();

      return b;

   }

   ::user::interaction * PASCAL interaction_impl::GetForegroundWindow()
   {

      return nullptr;
      // return ::macos::interaction_impl::from_handle(::GetForegroundWindow());

   }

//   bool interaction_impl::SendNotifyMessage(UINT message, WPARAM wparam, LPARAM lparam)
//   {
//
//      __throw(not_implemented());
//      //      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != FALSE;
//
//   }


//   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const
//   {
//
//      __throw(not_implemented());
//      //      ASSERT(::is_window(get_handle()));
//      //      const_cast < user::interaction * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);
//
//   }
//
//   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const
//   {
//
//      __throw(not_implemented());
//      //      ASSERT(::is_window(get_handle()));
//      //      const_cast < user::interaction * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);
//
//   }

   bool interaction_impl::SetWindowContextHelpId(DWORD dwContextHelpId)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != FALSE;

   }

   DWORD interaction_impl::GetWindowContextHelpId() const
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::GetWindowContextHelpId(get_handle());

   }


   // Default message ::collection::map implementations
//   void interaction_impl::OnActivateApp(bool, DWORD)
//   {
//      Default();
//   }
//   void interaction_impl::OnActivate(UINT, ::user::interaction *, bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnCancelMode()
//   {
//      Default();
//   }
//   void interaction_impl::OnChildActivate()
//   {
//      Default();
//   }
//   void interaction_impl::OnClose()
//   {
//      Default();
//   }
//   void interaction_impl::OnContextMenu(::user::interaction *, point)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnCopyData(::user::interaction *, COPYDATASTRUCT*)
//   {
//
//      return Default() != FALSE;
//
//   }

//   void interaction_impl::OnEnable(bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnEndSession(bool)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
//   {
//      Default();
//   }
//   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
//   {
//      Default();
//   }
//   void interaction_impl::OnKillFocus(::user::interaction *)
//   {
//      Default();
//   }
//   LRESULT interaction_impl::OnMenuChar(UINT, UINT, ::user::menu*)
//   {
//      return Default();
//   }
//   void interaction_impl::OnMenuSelect(UINT, UINT, HMENU)
//   {
//      Default();
//   }
//   void interaction_impl::OnMove(i32, i32)
//   {
//      Default();
//   }
//   HCURSOR interaction_impl::OnQueryDragIcon()
//   {
//      return (HCURSOR)Default();
//   }
//
//   bool interaction_impl::OnQueryEndSession()
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   bool interaction_impl::OnQueryNewPalette()
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   bool interaction_impl::OnQueryOpen()
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   void interaction_impl::_001OnSetCursor(::message::message * pmessage)
//   {
//      SCAST_PTR(::message::base, pbase, pmessage);
//      if (Session.get_cursor() != nullptr
//            && Session.get_cursor()->m_ecursor != cursor_system)
//      {
//
//         __throw(not_implemented());
//         //         ::SetCursor(nullptr);
//      }
//      pbase->set_lresult(1);
//      pbase->m_bRet = true;
//      //(bool)Default();
//   }
//   void interaction_impl::OnShowWindow(bool, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSize(UINT, i32, i32)
//   {
//      Default();
//   }
//   void interaction_impl::OnTCard(UINT, DWORD)
//   {
//      Default();
//   }
//   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
//   {
//      Default();
//   }
//   void interaction_impl::OnWindowPosChanged(WINDOWPOS*)
//   {
//      Default();
//   }
//   void interaction_impl::OnDropFiles(HDROP)
//   {
//      Default();
//   }
//   void interaction_impl::OnPaletteIsChanging(::user::interaction *)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnNcActivate(bool)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnNcCreate(::user::create_struct *)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   LRESULT interaction_impl::OnNcHitTest(point)
//   {
//      return Default();
//   }
//   void interaction_impl::OnNcLButtonDblClk(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcLButtonDown(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcLButtonUp(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonDblClk(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonDown(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonUp(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMouseMove(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcPaint()
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonDblClk(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonDown(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonUp(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysChar(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysCommand(UINT, LPARAM)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysDeadChar(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysKeyDown(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysKeyUp(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnCompacting(UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnFontChange()
//   {
//      Default();
//   }
//   void interaction_impl::OnPaletteChanged(::user::interaction *)
//   {
//      Default();
//   }
//   void interaction_impl::OnSpoolerStatus(UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnTimeChange()
//   {
//      Default();
//   }
//   void interaction_impl::OnChar(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnDeadChar(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnKeyDown(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnKeyUp(UINT, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonDblClk(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonDown(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonUp(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonDblClk(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonDown(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonUp(UINT, point)
//   {
//      Default();
//   }
//   i32 interaction_impl::OnMouseActivate(::user::interaction *, UINT, UINT)
//   {
//      return (i32)Default();
//   }
//   void interaction_impl::OnMouseMove(UINT, point)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnMouseWheel(UINT, short, point)
//   {
//
//      return Default() != FALSE;
//
//   }

//   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
//   {
//      return Default();
//   }
//   void interaction_impl::OnRButtonDblClk(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnRButtonDown(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnRButtonUp(UINT, point)
//   {
//      Default();
//   }
//   void interaction_impl::OnTimer(uptr)
//   {
//      Default();
//   }
//   void interaction_impl::OnInitMenu(::user::menu*)
//   {
//      Default();
//   }
//   void interaction_impl::OnInitMenuPopup(::user::menu*, UINT, bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnAskCbFormatName(UINT nMaxCount, LPTSTR pszName)
//   {
//      //      (nMaxCount);
//      if (nMaxCount > 0)
//      {
//         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
//         pszName[0] = '\0';
//      }
//      Default();
//   }
//   void interaction_impl::OnChangeCbChain(oswindow, oswindow)
//   {
//      Default();
//   }
//   void interaction_impl::OnDestroyClipboard()
//   {
//      Default();
//   }
//   void interaction_impl::OnDrawClipboard()
//   {
//      Default();
//   }
//   void interaction_impl::OnHScrollClipboard(::user::interaction *, UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnPaintClipboard(::user::interaction *, HGLOBAL)
//   {
//      Default();
//   }
//   void interaction_impl::OnRenderAllFormats()
//   {
//      Default();
//   }
//   void interaction_impl::OnRenderFormat(UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSizeClipboard(::user::interaction *, HGLOBAL)
//   {
//      Default();
//   }
//   void interaction_impl::OnVScrollClipboard(::user::interaction *, UINT, UINT)
//   {
//      Default();
//   }
//   UINT interaction_impl::OnGetDlgCode()
//   {
//      return (UINT)Default();
//   }
//   void interaction_impl::OnMDIActivate(bool, ::user::interaction *, ::user::interaction *)
//   {
//      Default();
//   }
//   void interaction_impl::OnEnterMenuLoop(bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnExitMenuLoop(bool)
//   {
//      Default();
//   }
   // Win4 support
   //   void interaction_impl::OnStyleChanged(i32, LPSTYLESTRUCT)
   //   { Default(); }
   //   void interaction_impl::OnStyleChanging(i32, LPSTYLESTRUCT)
   //   { Default(); }
//   void interaction_impl::OnSizing(UINT, LPRECT)
//   {
//      Default();
//   }
//   void interaction_impl::OnMoving(UINT, LPRECT)
//   {
//      Default();
//   }
//   void interaction_impl::OnCaptureChanged(::user::interaction *)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnDeviceChange(UINT, uptr)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   void interaction_impl::OnWinIniChange(const char *)
//   {
//      Default();
//   }
//   void interaction_impl::OnChangeUIState(UINT, UINT)
//   {
//      Default();
//   }
//   void interaction_impl::OnUpdateUIState(UINT, UINT)
//   {
//      Default();
//   }
//
//   UINT interaction_impl::OnQueryUIState()
//   {
//
//      return (UINT)Default();
//
//   }

   // user::interaction dialog data support
   //    void interaction_impl::DoDataExchange(CDataExchange*)
   //   { } // default does nothing

   // user::interaction modality support

//   void interaction_impl::BeginModalState()
//   {
//
//      __throw(todo());
//
//      //::EnableWindow(get_handle(), FALSE);
//
//   }
//
//   void interaction_impl::EndModalState()
//   {
//
//      __throw(todo());
//
//      //::EnableWindow(get_handle(), TRUE);
//
//   }
//
   // frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
    { m_nIdleFlags |= idleTitle; }
    void frame_window::DelayRecalcLayout(bool bNotify)
    { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
    bool frame_window::InModalState() const
    { return m_cModalStack != 0; }
    void frame_window::set_title(const char * lpszTitle)
    { m_strTitle = lpszTitle; }
    string frame_window::get_title() const
    { return m_strTitle; }
    */



   void interaction_impl::CloseWindow()
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      ::CloseWindow(get_handle());

   }

   bool interaction_impl::OpenIcon()
   {

      __throw(not_implemented());
      //      ASSERT(::is_window(get_handle()));
      //      return ::OpenIcon(get_handle()) != FALSE;

   }


//   oswindow PASCAL interaction_impl::GetSafeOwner_(oswindow hParent, oswindow* pWndTop)
//   {
//
//      return nullptr;
//
//   }
//
//
//   LRESULT CALLBACK __cbt_filter_hook(i32 code, WPARAM wparam, LPARAM lparam)
//   {
//
//      __throw(not_implemented());
//
//   }
//
//
//   void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pmessage);
//
//      perasebkgnd->m_bRet = true;
//
//      perasebkgnd->set_result(TRUE);
//
//   }
//
//
//   void interaction_impl::_001BaseWndInterfaceMap()
//   {
//
//      System.window_map().set(get_handle(), this);
//
//   }


   void interaction_impl::_001OnTriggerMouseInside()
   {

      //__throw(not_implemented());
      //      m_bMouseHover = true;
      //      TRACKMOUSEEVENT tme = { sizeof(tme) };
      //      tme.dwFlags = TME_LEAVE;
      //      tme.hwndTrack = get_handle();
      //      TrackMouseEvent(&tme);

   }

#ifdef EXTRALOG

   ::rect rectLast;

   ::size sizeLast;

#endif

   void interaction_impl::round_window_draw(CGContextRef cgc, CGSize sizeWindowParam)
   {

      ::size sizeWindow(sizeWindowParam.width, sizeWindowParam.height);

      #ifdef EXTRALOG

      static int s_iLastExact = -1;

      string str;

      string strFormat;

      strFormat.Format("|-> window size %d, %d", sizeWindow.cx, sizeWindow.cy);

      string strSize;

      if(sizeLast != sizeWindow)
      {

         sizeLast = sizeWindow;

         strSize = strFormat;

      }

      str += strFormat;

      rect rect1 = m_puserinteraction->get_window_rect();

      if(rect1.size() != rectLast.size())
      {

         rectLast = rect1;

         // xxxlog output_debug_string("different window rect size (1)");

      }

#endif

      tick tickNow = tick::now();

      tick tickEllapsed = tickNow - m_tickLastRoundWindowDraw;

      if(tickEllapsed < 12)
      {

         // xxxlog
         //output_debug_string("\n\nwarning: round_window_draw more than 80FPS!!! Ellapsed: " + str::from(tickEllapsed) + "ms.\n\n");

      }

      m_tickLastRoundWindowDraw = tickNow;

      round_window_draw_life_time roundwindowdrawlifetime(this);

      cslock slDisplay(cs_display());

      __pointer(::graphics::multiple_buffer) pmultiplebuffer = m_pgraphics;

      if(!pmultiplebuffer)
      {

         return;

      }
      
      if(!m_puserinteraction)
      {
      
         return;

      }
         
      ::draw2d::graphics_pointer g(e_create);

      g->attach(cgc);

      auto rectClient = m_puserinteraction->get_client_rect();

      g->set_alpha_mode(::draw2d::alpha_mode_set);

      sync_lock slGraphics(pmultiplebuffer->mutex());
      
      sync_lock sl1(pmultiplebuffer->get_screen_sync());

      ::image_pointer & imageBuffer2 = pmultiplebuffer->get_screen_image();

      if (!imageBuffer2)
      {

         output_debug_string("NOT DRAWING? <<---- search and bp here !imageBuffer2 ");

         return;

      }
      
      slGraphics.unlock();

#ifdef EXTRALOG

      if(strSize.has_char())
      {

         s_iLastExact = -1;

      }

      if(s_iLastExact > 0)
      {


         if(s_iLastExact % 10 == 0)
         {

            str = "\n.";

         }
         else
         {

            str = ".";

         }
         
         strFormat.Format("%d", iAge);

         str += strFormat;
         
         output_debug_string(str);
         
      }
      else
      {
         
         INFO(str);
         
      }
      
#endif

      ::size sizeMin = imageBuffer2->size().min(sizeWindow);

      g->draw(::rect(sizeMin), imageBuffer2->g(), sizeMin);
      
      m_bPendingRedraw = false;
      
      m_tickLastRedraw.Now();

   }


   bool interaction_impl::round_window_key_down(unsigned int uiKeyCode)
   {

      __pointer(::message::base) spbase;

      auto pkey  = __new(::message::key);

      pkey->m_id = WM_KEYDOWN;

      pkey->m_nChar = uiKeyCode;

      spbase = pkey;

      if(m_puserinteraction == nullptr)
      {

         return false;

      }

      m_puserinteraction->send(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_up(unsigned int uiKeyCode)
   {

      __pointer(::message::base) spbase;

      auto pkey  = __new(::message::key);

      pkey->m_id = WM_KEYUP;

      pkey->m_nChar = uiKeyCode;

      spbase = pkey;

      if(m_puserinteraction == nullptr)
      {

         return false;

      }

      m_puserinteraction->send(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8)
   {

      __pointer(::message::base) spbase;

      auto pkey  = __new(::message::key);

      pkey->set(m_puserinteraction, WM_KEYDOWN, vk, (LPARAM)(scan << 16));

      if(::is_set(pszUtf8))
      {
      
         

         string * pstringText = new string(pszUtf8);

         auto lparam = (LPARAM) (iptr) (string *) (pstringText);

         printf("x11_process_message message_text_composition\n");

         m_puserinteraction->post_message(message_text_composition, 0, lparam);
         
         
//         pkey->m_strText = pszUtf8;
//
//         if(pkey->m_strText.has_char())
//         {
//
//            pkey->m_ekey = ::user::key_refer_to_text_member;
//
//         }
         
      }
      
      spbase = pkey;

      if(m_puserinteraction == nullptr)
      {

         return false;

      }

      m_puserinteraction->send(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_up(unsigned int vk, unsigned int scan)
   {

      __pointer(::message::base) spbase;

      auto pkey  = __new(::message::key);

      pkey->set(m_puserinteraction, WM_KEYUP, vk, (LPARAM)(scan << 16));

      spbase = pkey;

      if(m_puserinteraction == nullptr)
      {

         return false;

      }

      m_puserinteraction->send(spbase);

      return spbase->m_bRet;

   }


   void interaction_impl::round_window_mouse_down(int iButton, double x, double y)
   {

      __pointer(::message::base) spbase;

      if (!is_active())
      {

         try
         {

            auto pmouseactivate = __new(::message::mouse_activate);

            pmouseactivate->m_id = WM_MOUSEACTIVATE;

            spbase = pmouseactivate;

            m_puserinteraction->send(spbase);

            if (spbase->m_lresult == MA_ACTIVATE || spbase->m_lresult == MA_ACTIVATEANDEAT)
            {


               m_puserinteraction->post_message(WM_ACTIVATE, MAKELONG(WA_CLICKACTIVE, 0), 0);

            }

         }
         catch (...)
         {

         }

      }

      {

         int message;

         if (iButton == 1)
         {

            message = WM_RBUTTONDOWN;

         }
         else
         {

            message = WM_LBUTTONDOWN;

         }

         LPARAM lparam = MAKELPARAM(x, y);
         
         if(m_puserinteraction)
         {

            m_puserinteraction->post_message(message, 0, lparam);
            
         }

      }

   }


   void interaction_impl::round_window_mouse_up(int iButton, double x, double y)
   {

      int message;

      if (iButton == 1)
      {

         message = WM_RBUTTONUP;

      }
      else
      {

         message = WM_LBUTTONUP;

      }

      LPARAM lparam = MAKELPARAM(x, y);
      
      if(!m_puserinteraction)
      {
         
         return;
         
      }

      m_puserinteraction->post_message(message, 0, lparam);


   }


   void interaction_impl::round_window_double_click(int iButton, double x, double y)
   {

      int message;

      if (iButton == 1)
      {

         message = WM_RBUTTONDBLCLK;

      }
      else
      {

         message = WM_LBUTTONDBLCLK;

      }

      LPARAM lparam = MAKELPARAM(x, y);
      
      if(!m_puserinteraction)
      {
         
         return;
         
      }

      m_puserinteraction->post_message(message, 0, lparam);

   }


   void interaction_impl::round_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton)
   {
      
      if(is_destroying())
      {
         
         return;
         
      }
      
      bool bOk = true;
      
      if(!m_puserinteraction)
      {
         
         return;
         
      }
      
      __pointer(::user::interaction) pinteraction = m_puserinteraction;

      if(pinteraction.is_set())
      {

         if(pinteraction->m_tickMouseMove.elapsed() < pinteraction->m_tickMouseMoveIgnore)
         {
            
            //printf("mouse_move_ignored %f, %f\n", x, y);

            bOk = false;

         }

         if(bOk)
         {

//            printf("mouse_move_\"accepted\" %f, %f\n", x, y);

            pinteraction->m_tickMouseMove.Now();

            pinteraction->m_pointMouseMove.x = x;

            pinteraction->m_pointMouseMove.y = y;

//            if(false)
//            {
//
//               if(pinteraction->m_tickMouseMovePeriod > 0)
//               {
//
//                  ::size sizeDistance((pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
//                     (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));
//
//                  if(!pinteraction->m_tickMouseMoveSkip.timeout(pinteraction->m_tickMouseMovePeriod)
//                     && sizeDistance.cx * sizeDistance.cx + sizeDistance.cy * sizeDistance.cy < pinteraction->m_iMouseMoveSkipSquareDistance)
//                  {
//
//                     pinteraction->m_iMouseMoveSkipCount++;
//
//                     pinteraction->m_bMouseMovePending = true;
//
//                     if(pinteraction->m_iMouseMoveSkipCount == 2)
//                     {
//
//                        //output_debug_string("\nmmv>skip 2!");
//
//                     }
//                     else if(pinteraction->m_iMouseMoveSkipCount == 5)
//                     {
//
//                        //output_debug_string("\nmmv>Skip 5!!!");
//
//                     }
//                     else if(pinteraction->m_iMouseMoveSkipCount == 10)
//                     {
//
//                        //output_debug_string("\nmmv>SKIP 10 !!!!!!!!!");
//
//                     }
//
//                     return true;
//
//                  }
//
//                  pinteraction->m_iMouseMoveSkipCount = 0;
//
//                  pinteraction->m_pointMouseMoveSkip = pinteraction->m_pointMouseMove;
//
//               }
//
//            }

         }

      }

      if(!bOk)
      {

         return true;

      }

      if(m_puserinteraction == nullptr)
      {

         return;

      }

      LPARAM lparam = MAKELPARAM(x, y);

      WPARAM wparam = 0;

      if(ulAppleMouseButton & 1)
      {

         wparam |= MK_LBUTTON;

      }

      if(ulAppleMouseButton & 2)
      {

         wparam |= MK_RBUTTON;

      }
      
      //printf("mouse_move_\"posted\" %f, %f\n", x, y);
      
      m_puserinteraction->post_message(WM_MOUSEMOVE, wparam, lparam);
      
   }


   void interaction_impl::round_window_mouse_dragged(double x, double y, unsigned long ulAppleMouseButton)
   {

      if(is_destroying())
      {
         
         return;
         
      }

      if(m_puserinteraction == nullptr)
      {

         return;

      }

      LPARAM lparam = MAKELPARAM(x, y);

      WPARAM wparam = 0;

      if(ulAppleMouseButton & 1)
      {

         wparam |= MK_LBUTTON;

      }

      if(ulAppleMouseButton & 2)
      {

         wparam |= MK_RBUTTON;

      }

      m_puserinteraction->post_message(WM_MOUSEMOVE, wparam, lparam);

   }


   void interaction_impl::round_window_mouse_wheel(double deltaY, double x, double y)
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      __pointer(::message::base) spbase;
      
      if(!m_puserinteraction)
      {
         
         return;
         
      }

      {

         auto pwheel  = __new(::message::mouse_wheel);

         pwheel->m_id = WM_MOUSEWHEEL;

         pwheel->m_point.x = (LONG)x;
         pwheel->m_point.y = (LONG)y;
         pwheel->m_bTranslated = true;

         short delta = deltaY * WHEEL_DELTA / 3.0;

         pwheel->m_wparam = delta << 16;

         spbase = pwheel;

         if(m_puserinteraction == nullptr)
         {

            return;

         }

         m_puserinteraction->send(spbase);

      }

   }


   void interaction_impl::round_window_resized(CGRect rect)
   {
      
      if(is_destroying())
      {
         
         return;
         
      }
      
      if(!m_puserinteraction)
      {
         
         return;
         
      }

      m_puserinteraction->post_message(WM_MOVE,0, MAKELPARAM(rect.origin.x, rect.origin.y));

      m_puserinteraction->post_message(WM_SIZE,0, MAKELPARAM(rect.size.width, rect.size.height));

      return;

//      if(m_puserinteraction == nullptr)
//      {
//
//         return;
//
//      }
//
//      //
//      if(m_puserinteraction->window_state().m_point != rect.origin)
//      {
//
//         m_puserinteraction->window_state().m_point = rect.origin;
//
//         TRACE("interaction_impl::round_window_resized effective position is different from requested position");
//
//         m_puserinteraction->post_message(WM_MOVE, 0, m_puserinteraction->window_state().m_point.lparam());
//
//      }
//
//      if(m_puserinteraction->m_sizeRequest != rect.size)
//      {
//
//         m_puserinteraction->m_sizeRequest = rect.size;
//
//         TRACE("interaction_impl::round_window_resized effective position is different from requested position");
//
//         m_puserinteraction->post_message(WM_SIZE, 0, m_puserinteraction->m_sizeRequest.lparam());
//
//      }
//
//      m_puserinteraction->m_point = rect.origin;
//
//      m_puserinteraction->m_size = rect.size;
//
////      ::size sz;
////
////      point64 pt(rect.origin.x, rect.origin.y);
////
////      bool bMove = false;
////
////      {
////
////         sync_lock sl(m_puserinteraction->mutex());
////
////         if (pt != m_puserinteraction->m_rectParentClient.top_left())
////         {
////
////            bMove = true;
////
////         }
////
////         m_puserinteraction->m_rectParentClient.move_to(point);
////
////         m_puserinteraction->set_size(rect.size);
////
////         sz = m_puserinteraction->m_rectParentClient.size();
////
////      }
////
////      if(m_puserinteraction == nullptr)
////      {
////
////         return;
////
////      }
////
////      m_puserinteraction->post_message(WM_SIZE, 0, sz.lparam());
////
////      if (bMove)
////      {
////
////         m_puserinteraction->post_message(WM_MOVE, 0, pt.lparam());
////
////      }

//      if (m_puserinteraction->m_eflagLayouting)
//      {
//
//         //pmessage->m_bRet = true;
//
//         return;
//
//      }
//
//      ::rect rectSize;
//
//      __copy(rectSize, rect);
//
//      if(m_puserinteraction->window_state().rect() != rectSize)
//      {
//
//         m_puserinteraction->window_state().m_point = rectSize.origin();
//
//         m_puserinteraction->window_state().m_size = rectSize.size();
//
//      }
//
//
//      if (m_puserinteraction->layout().sketch().rect() != rectSize)
//      {
//
//         m_puserinteraction->place(rectSize);
//
//         if (m_puserinteraction->layout().design().display() != display_normal)
//         {
//
//            m_puserinteraction->display();
//
//         }
//
//         m_puserinteraction->set_need_layout();
//
//         m_puserinteraction->set_need_redraw();
//
//      }

   }


   void interaction_impl::round_window_moved(CGPoint point)
   {
      
      if(is_destroying())
      {
         
         return;
         
      }
      
      if(m_bEatMoveEvent)
      {
         
         m_bEatMoveEvent = false;
         
         return;
         
      }

      m_puserinteraction->post_message(WM_MOVE,0, MAKELPARAM(point.x, point.y));

      return;

//      if(m_puserinteraction == nullptr)
//      {
//
//         return;
//
//      }
//
//
//      ::point pointMove;
//
//      __copy(pointMove, point);
//
//      if (m_puserinteraction->m_eflagLayouting)
//      {
//
//         //pmessage->m_bRet = true;
//
//         return;
//
//      }
//
//      ///SCAST_PTR(::message::move, pmove, pmessage);
//
//      if (m_puserinteraction->layout().sketch().m_point != pointMove)
//      {
//
//         m_puserinteraction->move_to(pointMove);
//
//         if (m_puserinteraction->layout().design().display() != display_normal)
//         {
//
//            m_puserinteraction->display();
//
//         }
//
//         m_puserinteraction->set_reposition();
//
//         m_puserinteraction->set_need_redraw();
//
//      }
//
//
////      if(m_puserinteraction->m_pointRequest != point)
////      {
////
////         m_puserinteraction->m_pointRequest = point;
////
////         TRACE("interaction_impl::round_window_resized effective position is different from requested position");
////
////      }
////
////      m_puserinteraction->m_point = point;

   }


   void interaction_impl::round_window_did_become_key()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      m_tickLastExposureAddUp.Now();

   }


   void interaction_impl::round_window_activate()
   {
      
      if(is_destroying())
      {
         
         return;
         
      }
      
      ::set_active_window(get_handle());

      if(m_puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteraction->set_need_redraw();

   }


   void interaction_impl::round_window_deactivate()
   {

      if(is_destroying())
      {
         
         //return;
         
         output_debug_string("destroying");
         
      }
      
      ::deactivate_window(get_handle());

      if(m_puserinteraction == nullptr)
      {

         return;

      }
 
      if(!is_destroying())
      {
      
         m_puserinteraction->set_need_redraw();
         
      }

   }


   void interaction_impl::round_window_iconified()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      if(m_puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteraction->m_windowrect.m_edisplayPrevious = m_puserinteraction->m_windowrect.m_edisplay;

      m_puserinteraction->window_state3().m_edisplay3 = ::display_iconic;

   }


   void interaction_impl::round_window_deiconified()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      if(m_puserinteraction == nullptr)
      {

         return;

      }

      if(m_puserinteraction->m_windowrect.m_edisplayPrevious == ::display_iconic)
      {

         m_puserinteraction->m_windowrect.m_edisplayPrevious = ::display_normal;

      }

      m_puserinteraction->_001OnDeiconify(m_puserinteraction->m_windowrect.m_edisplayPrevious);

   }


   void interaction_impl::round_window_on_show()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      if(m_puserinteraction == nullptr)
      {

         return;

      }

      m_tickLastExposureAddUp.Now();

      m_puserinteraction->message_call(WM_SHOWWINDOW, 1);

      //m_puserinteraction->user_interaction_update_visibility_cache(true);

//      if(!(m_puserinteraction->m_ewindowflag & window_flag_miniaturizable))
//      {
//
//         if(m_puserinteraction->layout().sketch().display() == display_iconic)
//         {
//
//            m_puserinteraction->m_windowState3
//
//         }
//
//      }

      m_puserinteraction->set_need_layout();

      m_puserinteraction->set_need_redraw();

      m_puserinteraction->post_redraw();

   }


   void interaction_impl::round_window_on_hide()
   {

//      if(is_destroying())
//      {
//         
//         return;
//         
//      }
      
      INFO("macos::interaction_impl::round_window_on_hide");

      if(m_puserinteraction == nullptr)
      {

         WARN("macos::interaction_impl::round_window_on_hide (2) m_puserinteraction == nullptr");

         return;

      }

      if(::is_screen_visible(m_puserinteraction->m_stateWindow3.m_edisplay3))
      {

         m_puserinteraction->m_stateWindow3.m_edisplay3 = display_none;

      }

      m_puserinteraction->message_call(WM_SHOWWINDOW, 0);

   }


   void interaction_impl::round_window_on_miniaturize()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      if(m_puserinteraction == nullptr)
      {

         return;

      }

      //m_puserinteraction->message_call(WM_SHOWWINDOW, 0);

      //m_puserinteraction->user_interaction_update_visibility_cache(false);

   }


   void CLASS_DECL_AXIS __pre_init_dialog(
   ::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld)
   {
      ASSERT(lpRectOld != nullptr);
      ASSERT(pdwStyleOld != nullptr);

      pWnd->get_window_rect(lpRectOld);
      *pdwStyleOld = pWnd->GetStyle();
   }

//   __STATIC void CLASS_DECL_AXIS __post_init_dialog(
//      ::user::interaction * p, const RECT& rectOld, DWORD dwStyleOld)
//   {
//      // must be hidden to start with
//      if (dwStyleOld & WS_VISIBLE)
//         return;
//
//      // must not be visible after WM_INITDIALOG
//      if (pWnd->GetStyle() & (WS_VISIBLE | WS_CHILD))
//         return;
//
//      // must not move during WM_INITDIALOG
//      ::rect rect;
//      pWnd->get_window_rect(rect);
//      if (rectOld.left != rect.left || rectOld.top != rect.top)
//         return;
//
//      // must be unowned or owner disabled
//      ::user::interaction * pParent = pWnd->GetWindow(GW_OWNER);
//      if (pParent != nullptr && pParent->is_window_enabled())
//         return;
//
//      if (!pWnd->CheckAutoCenter())
//         return;
//
//      // center modal dialog boxes/message boxes
//      //MAC_WINDOW(pWnd)->CenterWindow();
//   }



   CLASS_DECL_AXIS void hook_window_create(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

   }


   CLASS_DECL_AXIS bool unhook_window_create()
   {

      return true;

   }


   void CLASS_DECL_AXIS
   __handle_activate(::user::interaction * pWnd, WPARAM nState, ::user::interaction * pWndOther)
   {

      __throw(not_implemented());
      //   ASSERT(pWnd != nullptr);
      //
      //   // m_puserinteraction->send WM_ACTIVATETOPLEVEL when top-level parents change
      //   if (!(MAC_WINDOW(pWnd)->GetStyle() & WS_CHILD))
      //   {
      //      ::user::interaction * pTopLevel= MAC_WINDOW(pWnd)->GetTopLevelParent();
      //      if (pTopLevel && (pWndOther == nullptr || !::is_window(MAC_WINDOW(pWndOther)->get_handle()) || pTopLevel != MAC_WINDOW(pWndOther)->GetTopLevelParent()))
      //      {
      //         // lparam points to user::interaction getting the WM_ACTIVATE message and
      //         //  hWndOther from the WM_ACTIVATE.
      //         oswindow hWnd2[2];
      //         hWnd2[0] = MAC_WINDOW(pWnd)->get_handle();
      //         if(pWndOther == nullptr || MAC_WINDOW(pWndOther) == nullptr)
      //         {
      //            hWnd2[1] = nullptr;
      //         }
      //         else
      //         {
      //            hWnd2[1] = MAC_WINDOW(pWndOther)->get_handle();
      //         }
      //         // m_puserinteraction->send it...
      //         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (LPARAM)&hWnd2[0]);
      //      }
      //   }
   }

   bool CLASS_DECL_AXIS
   __handle_set_cursor(::user::interaction * pWnd, UINT nHitTest, UINT nMsg)
   {

      __throw(not_implemented());
      //   if (nHitTest == HTERROR &&
      //      (nMsg == WM_LBUTTONDOWN || nMsg == WM_MBUTTONDOWN ||
      //      nMsg == WM_RBUTTONDOWN))
      //   {
      //      // activate the last active user::interaction if not active
      //      ::user::interaction * pLastActive = MAC_WINDOW(pWnd)->GetTopLevelParent();
      //      if (pLastActive != nullptr)
      //         pLastActive = pLastActive->GetLastActivePopup();
      //      if (pLastActive != nullptr &&
      //         pLastActive != ::macos::interaction_impl::GetForegroundWindow() &&
      //         pLastActive->IsWindowEnabled())
      //      {
      //         pLastActive->SetForegroundWindow();
      //         return TRUE;
      //      }
      //   }
      //   return FALSE;
   }





   LRESULT CALLBACK
   __activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam)
   {

      __throw(not_implemented());
      //   WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, gen_OldWndProc);
      //   ASSERT(oldWndProc != nullptr);
      //
      //   LRESULT lResult = 0;
      //   try
      //   {
      //      bool bCallDefault = TRUE;
      //      switch (nMsg)
      //      {
      //      case WM_INITDIALOG:
      //         {
      //            DWORD uStyle;
      //            ::rect rectOld;
      //            ::user::interaction * pWnd = ::macos::interaction_impl::from_handle(hWnd);
      //            __pre_init_dialog(pWnd, &rectOld, &uStyle);
      //            bCallDefault = FALSE;
      //            lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wparam, lparam);
      //            __post_init_dialog(pWnd, rectOld, uStyle);
      //         }
      //         break;
      //
      //      case WM_ACTIVATE:
      //         __handle_activate(::macos::interaction_impl::from_handle(hWnd), wparam,
      //            ::macos::interaction_impl::from_handle((oswindow)lparam));
      //         break;
      //
      //      case WM_SETCURSOR:
      //         bCallDefault = !__handle_set_cursor(::macos::interaction_impl::from_handle(hWnd),
      //            (short)LOWORD(lparam), HIWORD(lparam));
      //         break;
      //
      //      case WM_NCDESTROY:
      //         SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<iptr>(oldWndProc));
      //         RemoveProp(hWnd, gen_OldWndProc);
      //         GlobalDeleteAtom(GlobalFindAtom(gen_OldWndProc));
      //         break;
      //      }
      //
      //      // call original wndproc for default handling
      //      if (bCallDefault)
      //         lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wparam, lparam);
      //   }
      //   catch(::exception::aura * pe)
      //   {
      //      // handle exception
      //      MESSAGE msg;
      //      msg.hwnd = hWnd;
      //      msg.message = nMsg;
      //      msg.wparam = wparam;
      //      msg.lparam = lparam;
      //
      //      //lResult = __process_window_procedure_exception(pe, &msg);
      //      //      TRACE(::ca2::trace::category_AppMsg, 0, "Warning: Uncaught exception in __activation_window_procedure (returning %ld).\n",
      //      //       lResult);
      //      ::exception_pointer esp(pe);
      //   }
      //
      //
      //   return lResult;
   }


   void interaction_impl::offset_viewport_org(LPRECT lprectScreen)
   {

   }


   void interaction_impl::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      // graphics will be already set its view port to the user::interaction for linux - cairo with xlib

      pgraphics->SetViewportOrg(::point());

   }


   void interaction_impl::_001WindowMinimize()
   {

      if(get_handle() == nullptr)
      {

         return;

      }

      round_window_iconified();

      get_handle()->iconify();

   }


   bool interaction_impl::has_focus()
   {

      return ::get_focus() == get_handle();

   }


   bool interaction_impl::is_active()
   {

      return ::get_active_window() == get_handle();

   }


//   void interaction_impl::ns_main_async(dispatch_block_t block)
//   {
//
//      ::ns_main_async(block);
//
//   }


   void interaction_impl::window_show_change_visibility()
   {

      auto edisplay = m_puserinteraction->process_display();

      if(!::is_visible(edisplay))
      {

         round_window_hide();

      }
      else if(edisplay == display_iconic)
      {

         round_window_miniaturize();

      }
      else if(m_puserinteraction->process_state().m_eactivation & activation_no_activate)
      {

         round_window_order_front();

      }
      else
      {

         defer_dock_application(true);

         nsapp_activate_ignoring_other_apps(1);

         round_window_show();

      }

      return 1;

   }

   
   void interaction_impl::set_destroying()
   {
      
      ::user::interaction_impl::set_destroying();

      ::round_window::m_bDestroying = true;

   }


} // namespace macos



