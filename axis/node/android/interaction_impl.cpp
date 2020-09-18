#include "framework.h"
#include "_android.h"
#include "aura/os/android/windowing.h"


extern __pointer(os_local) g_poslocal;


void android_edit_on_set_focus(int l, int t, int r, int b, const char* pszText, int iBeg, int iEnd);
void android_edit_on_kill_focus();


CLASS_DECL_AXIS int g_iMouseDown = 0;
//
//CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;
//CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time2;
//
//
//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;
//
//
//




namespace android
{


   interaction_impl::interaction_impl() 
   {

      m_bScreenRelativeMouseMessagePosition = true;
      m_oswindow           = nullptr;
      //m_bMouseHover        = false;
      m_bUpdateGraphics    = false;
      //m_bEnabled           = true;
      m_pthreadDraw = nullptr;

      //xxf_zero(m_rectParentClient);
      xxf_zero(m_size);
      xxf_zero(m_point);



   }




   //void interaction_impl::construct(oswindow oswindow)
   //{

   //   m_bScreenRelativeMouseMessagePosition = true;
   //   m_oswindow           = nullptr;
   //   //m_bMouseHover        = false;
   //   m_bUpdateGraphics    = false;
   //   m_bEnabled           = true;
   //   m_pthreadDraw = nullptr;
   //   //xxf_zero(m_rectParentClient);
   //   xxf_zero(m_size);
   //   xxf_zero(m_point);

   //   set_handle(oswindow);

   //}


   //interaction_impl::interaction_impl(::layered * pobjectContext):
   //   ::object(pobject)
   //{
   //   m_bScreenRelativeMouseMessagePosition = true;
   //   //  m_bScreenRelativeMouseMessagePosition = false;
   //   m_oswindow           = nullptr;
   //   m_bUpdateGraphics    = false;
   //   m_bIgnoreSizeEvent   = false;
   //   m_bIgnoreMoveEvent   = false;
   //   m_bEnabled           = true;
   //   m_pthreadDraw = nullptr;
   //   xxf_zero(m_rectParentClient);
   //   xxf_zero(m_size);
   //   xxf_zero(m_point);

   //}


   interaction_impl::~interaction_impl()
   {

      if(get_context_session() != nullptr)
      {

         if(System.m_pwindowmap != nullptr)
         {

            System.m_pwindowmap->m_map.remove_key(get_handle());

         }

      }

   }


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      return from_handle((oswindow)pdata);

   }


   void * interaction_impl::get_os_data() const
   {

      return (void *)get_handle();

   }



   // Change a interaction_impl's style

   __STATIC bool CLASS_DECL_AXIS __modify_style(oswindow oswindow,i32 nStyleOffset,
         u32 dwRemove,u32 dwAdd,UINT nFlags)
   {
      ASSERT(oswindow != nullptr);
      u32 dwStyle = ::GetWindowLong(oswindow,nStyleOffset);
      u32 dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
      if(dwStyle == dwNewStyle)
         return FALSE;

      ::SetWindowLong(oswindow,nStyleOffset,dwNewStyle);
      if(nFlags != 0)
      {
         ::SetWindowPos(oswindow,nullptr,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
      }
      return TRUE;
   }


   bool interaction_impl::ModifyStyle(oswindow oswindow,u32 dwRemove,u32 dwAdd,UINT nFlags)
   {

      return __modify_style(oswindow,GWL_STYLE,dwRemove,dwAdd,nFlags);

   }


   bool interaction_impl::ModifyStyleEx(oswindow oswindow,u32 dwRemove,u32 dwAdd,UINT nFlags)
   {

      return __modify_style(oswindow,GWL_EXSTYLE,dwRemove,dwAdd,nFlags);

   }


   LRESULT interaction_impl::Default()
   {

      return 0;

   }


   ::user::interaction * interaction_impl::FromHandlePermanent(oswindow oswindow)
   {

      if (oswindow->get_impl() == nullptr)
      {

         return nullptr;

      }

      return oswindow->get_impl()->m_puserinteraction;

   }


   bool interaction_impl::Attach(oswindow hWndNew)
   {

      ASSERT(get_handle() == nullptr);

      if (hWndNew == nullptr)
         return false;

      m_oswindow = hWndNew;

      return true;

   }

   oswindow interaction_impl::Detach()
   {

      oswindow hwnd = (oswindow)get_handle();

      if (hwnd != nullptr)
      {

         m_oswindow = nullptr;

      }

      return hwnd;

   }


   void interaction_impl::pre_subclass_window()
   {


   }


   bool interaction_impl::create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction * puiParent, id id)
   {

      auto oswindow = puiParent ? puiParent->get_safe_handle() : nullptr;

      if(puiParent == nullptr)
      {

         if(!native_create_window_ex(pinteraction, cs, oswindow, id))
         {

            return false;

         }

      }
      else
      {

         if(!native_create_window_ex(pinteraction, cs, oswindow, id))
         {

            return false;

         }

      }

      return true;

   }


   bool interaction_impl::_native_create_window_ex(::user::create_struct& cs)
   {

//      __throw(not_implemented("no multiple native windows per application"));

//      return false;

      ENSURE_ARG(cs.lpszClass == nullptr || __is_valid_string(cs.lpszClass));

      if (cs.hwndParent == HWND_MESSAGE)
      {

         m_puserinteraction->m_bMessageWindow = true;

         m_puserinteraction->m_pimpl = this;


         return true;

      }
      else
      {

         m_puserinteraction->m_bMessageWindow = false;

         m_oswindow = oswindow_get(this);

         m_puserinteraction->ModifyStyle(0, WS_VISIBLE);

         ::rect rectCreate;

         cs.get_rect(rectCreate);

         m_puserinteraction->place(rectCreate);

         m_puserinteraction->display(display_full_screen);

         //::estatus estatus = __compose(m_pgraphics);

         //if (!estatus)
         //{

         //   return false;

         //}

         //m_pgraphics->initialize_graphics_graphics(this);
         
         m_oswindow->m_pimpl = this;

      }

      set_handle(m_oswindow);

      if(m_oswindow == nullptr)
      {

         if (get_context_application() == nullptr)
         {

            PostNcDestroy();

            m_puserinteraction = nullptr;

            return false;

         }

         u32 dwLastError = get_last_error();

         string strLastError = FormatMessageFromSystem(dwLastError);

         string strMessage;

         strMessage.Format("%s\n\nSystem Error Code: %d",strLastError.c_str(),dwLastError);

         TRACE("Warning: Window creation failed: get_last_error returned:\n");

         TRACE("%s\n", strMessage.c_str());

         try
         {

            if(dwLastError == 0x0000057e)
            {

               TRACE("Cannot create a top-level child interaction_impl.");

            }
            else
            {

               TRACE("%s", strMessage.c_str());

            }

         }
         catch(...)
         {

         }

      }

      if(m_oswindow == nullptr)
      {

         PostNcDestroy();

         m_puserinteraction = nullptr;

         return false;

      }

      install_message_routing(m_puserinteraction);

      m_puserinteraction->__refer(m_puserinteraction->m_pthreadUserInteraction, ::get_thread());

      if (m_puserinteraction->m_pthreadUserInteraction != nullptr)
      {

         if (m_puserinteraction->m_pthreadUserInteraction->m_puiptraThread == nullptr)
         {

            m_puserinteraction->m_pthreadUserInteraction->m_puiptraThread = new user_interaction_ptr_array();

         }

         m_puserinteraction->m_pthreadUserInteraction->m_puiptraThread->add(m_puserinteraction);

      }

      output_debug_string("android_interaction_impl send WM_CREATE");

      m_puserinteraction->send_message(WM_CREATE, 0, (LPARAM)&cs);

      m_puserinteraction->send_message(WM_SIZE);

      if(m_oswindow != get_handle())
      {

         ASSERT(FALSE); // should have been set in send msg hook

      }

      m_puserinteraction->m_pimpl = this;

      m_puserinteraction->m_ewindowflag |= window_flag_window_created;

      return true;

   }


   //bool interaction_impl::create_native_window(::user::native_window_initialize * pinitialize)
   //{

   //   m_oswindow = oswindow_get(this);

   //   m_oswindow->set_impl(this);

   //   install_message_routing(this);

   //   m_puserinteraction->set_window_pos(zorder_top, pinitialize->m_rect, SWP_SHOWWINDOW);

   //   m_puserinteraction->ModifyStyle(0, WS_VISIBLE);

   //   output_debug_string("android_interaction_impl m_spgraphics alloc");

   //   //m_spgraphics.create(this);

   //   //m_spgraphics->on_create_window(this);

   //   m_puserinteraction->ModifyStyle(0, WS_VISIBLE);

   //   m_puserinteraction->send_message(WM_CREATE);

   //   m_puserinteraction->send_message(WM_SIZE);

   //   m_puserinteraction->send_message(WM_MOVE);

   //   m_puserinteraction->send_message(WM_SHOWWINDOW, 1);

   //   output_debug_string("android_interaction_impl on _create_window");

   //   output_debug_string("android_interaction_impl initialize (width=" + __str(width(pinitialize->m_rect)) + ",height=" + __str(height(pinitialize->m_rect)) + ")");

   //   return true;

   //}


   // for child android
   bool interaction_impl::pre_create_window(::user::create_struct& cs)
   {

      return true;

   }


   bool interaction_impl::create_window(::user::interaction * pinteraction, const char * lpszClassName, const char * lpszWindowName, u32 dwStyle, const ::rect & rect, ::user::interaction * pParentWnd, id id, ::create * pcreate)
   {

      // can't use for desktop or pop-up android (use create_window_ex instead)
      // can't use for desktop or pop-up windows (use create_window_ex instead)
      ASSERT(pParentWnd != nullptr);
      ASSERT((dwStyle & WS_POPUP) == 0);

      ::user::create_struct createstruct;

      createstruct.dwExStyle = 0;
      createstruct.lpszClass = lpszClassName;
      createstruct.lpszName = lpszWindowName;
      createstruct.style = dwStyle | WS_CHILD;
      createstruct.x = rect.left;
      createstruct.y = rect.top;
      createstruct.cx = width(rect);
      createstruct.cy = height(rect);
      createstruct.hwndParent = pParentWnd->get_safe_handle();
      createstruct.lpCreateParams = (LPVOID)pcreate;

      return create_window_ex(pinteraction, createstruct, pParentWnd, id);
   }


   // bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const char * pszName)
   // {

   //    if(m_puserinteraction->is_window())
   //    {

   //       DestroyWindow();

   //    }

   //    ::user::create_struct createstruct(0, nullptr, pszName, WS_CHILD, ::rect());

   //    createstruct.hwndParent = HWND_MESSAGE;

   //    if(!native_create_window_ex(pinteraction, createstruct))
   //    {

   //       return false;

   //    }

   //    return true;

   // }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);
      ::user::interaction_impl::install_message_routing(pchannel);

      if(!m_puserinteraction->m_bMessageWindow)
      {
         IGUI_MSG_LINK(WM_PAINT, pchannel, this,&interaction_impl::_001OnPaint);
         IGUI_MSG_LINK(WM_PRINT, pchannel, this,&interaction_impl::_001OnPrint);
      }
      m_puserinteraction->install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this,&interaction_impl::_001OnCreate);
      if(!m_puserinteraction->m_bMessageWindow)
      {

         IGUI_MSG_LINK(WM_SETCURSOR, pchannel, this,&interaction_impl::_001OnSetCursor);

         //IGUI_MSG_LINK(WM_ERASEBKGND, pchannel, this,&interaction_impl::_001OnEraseBkgnd);

         IGUI_MSG_LINK(WM_SIZE, pchannel, this,&interaction_impl::_001OnSize);

         //IGUI_MSG_LINK(WM_WINDOWPOSCHANGING, pchannel, this,&interaction_impl::_001OnWindowPosChanging);
         //IGUI_MSG_LINK(WM_WINDOWPOSCHANGED, pchannel, this,&interaction_impl::_001OnWindowPosChanged);
         //IGUI_MSG_LINK(WM_GETMINMAXINFO, pchannel, this,&interaction_impl::_001OnGetMinMaxInfo);

//         IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this,&interaction_impl::_001OnShowWindow);

         //IGUI_MSG_LINK(ca2m_PRODEVIAN_SYNCH, pchannel, this,&interaction_impl::_001OnProdevianSynch);

         prio_install_message_routing(pchannel);

      }

      IGUI_MSG_LINK(WM_DESTROY, pchannel, this,&interaction_impl::_001OnDestroy);

      IGUI_MSG_LINK(WM_NCCALCSIZE, pchannel, this,&interaction_impl::_001OnNcCalcSize);

   }

   void interaction_impl::win_update_graphics()
   {

      single_lock sl(m_puserinteraction->mutex(),false);

      if(!sl.lock())
      {
         m_bUpdateGraphics = true;
         return;
      }

      m_bUpdateGraphics = false;

      ::rect rectWindow;

      m_puserinteraction->get_window_rect(rectWindow);

      m_point = rectWindow.top_left();

      if (rectWindow.area() <= 0)
      {

         return;

      }

      if(m_size != rectWindow.size())
      {

         m_size = rectWindow.size();

      }

   }




   void interaction_impl::_001OnDestroy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      //::multithreading::post_quit_and_wait(m_pprodevian, seconds(10));

      //if (m_puserinteraction->m_pthreadUserInteraction != nullptr)
      //{

         //m_puserinteraction->m_pthreadUserInteraction->m_puiptraThread->remove(m_puserinteraction);

      //}

      Default();

   }


   void interaction_impl::_001OnNcCalcSize(::message::message * pmessage)
   {

      SCAST_PTR(::message::base,pbase,pmessage);

      pbase->set_lresult(0);

      pmessage->m_bRet = true;

   }


   void interaction_impl::PostNcDestroy()
   {

      single_lock sl(m_puserinteraction->get_context_application()->mutex(), TRUE);

      ::user::interaction_impl * pwindow;

      ::thread* pThread = ::get_thread();

      if (pThread != nullptr)
      {

         if (pThread->get_active_ui() == m_puserinteraction)
         {

            pThread->set_active_ui(nullptr);

         }

      }

      detach();

      ASSERT(get_handle() == nullptr);

      set_handle(nullptr);

      ::user::interaction_impl::PostNcDestroy();

   }


   void interaction_impl::on_final_release()
   {
      if(get_handle() != nullptr)
         DestroyWindow();    // will call PostNcDestroy
      else
         PostNcDestroy();
   }

   void interaction_impl::assert_valid() const
   {
      if(((::android::interaction_impl *)this)->get_handle() == nullptr)
         return;     // null (unattached) android are valid

      // check for special wnd??? values
///      ASSERT(HWND_TOP == nullptr);       // same as desktop
      //if(((::android::interaction_impl *)this)->get_handle() == HWND_BOTTOM)
      //{
      //}
      //else if(((::android::interaction_impl *)this)->get_handle() == HWND_TOPMOST)
      //{
      //}
      //else if(((::android::interaction_impl *)this)->get_handle() == HWND_NOTOPMOST)
      //{
      //}
      //else
      //{
      //   // should be a normal interaction_impl
      //   ASSERT(::is_window(((::android::interaction_impl *)this)->get_handle()));

      //}
   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      dumpcontext << "\nm_oswindow_ = " << ((::android::interaction_impl *)this)->get_handle();

   }

   void interaction_impl::on_set_parent(::user::interaction * pinteraction)
   {

      if(pinteraction != nullptr)
      {

         detach();

      }

   }


   bool interaction_impl::DestroyWindow()
   {

      bool bResult = false;

      if (get_handle() != nullptr)
      {

         bResult = ::destroy_window(get_handle()) != FALSE;

      }

      return bResult;

   }


   LRESULT interaction_impl::DefWindowProc(UINT nMsg,WPARAM wParam,lparam lParam)
   {

      return 0;

   }


   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // no default processing
   }



   //i32 interaction_impl::GetChildByIdText(i32 nID,string & rString) const
   //{
   //   ASSERT(::is_window(((::android::interaction_impl *)this)->get_handle()));
   //   rString = "";    // is_empty without deallocating

   //   //oswindow oswindow = ::GetDlgItem(((::android::interaction_impl *)this)->get_handle(),nID);
   //   //if(oswindow != nullptr)
   //   //{
   //   //   i32 nLen = ::GetWindowTextLength(oswindow);
   //   //   ::GetWindowText(oswindow,rString.get_string_buffer(nLen),nLen + 1);
   //   //   rString.ReleaseBuffer();
   //   //}

   //   return (i32)rString.get_length();
   //}


   //bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   //{

   //   //ASSERT(::is_window(get_handle()));

   //   //lpwndpl->length = sizeof(WINDOWPLACEMENT);

   //   //return ::GetWindowPlacement(get_handle(),lpwndpl) != FALSE;

   //   return false;

   //}


   //bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   //{

   //   //sync_lock sl(&user_mutex());

   //   //ASSERT(::is_window(get_handle()));

   //   //((WINDOWPLACEMENT*)lpwndpl)->length = sizeof(WINDOWPLACEMENT);

   //   //return ::SetWindowPlacement(get_handle(),lpwndpl) != FALSE;

   //   return false;

   //}


   ///////////////////////////////////////////////////////////////////////////////
   //// interaction_impl will delegate owner draw messages to self drawing controls

   //// Drawing: for all 4 control types
   //void interaction_impl::OnDrawItem(i32 /*nIDCtl*/,LPDRAWITEMSTRUCT lpDrawItemStruct)
   //{

   //   // reflect notification to child interaction_impl control
   //   //      if (ReflectMessage(lpDrawItemStruct->hwndItem))
   //   //       return;     // eat it

   //   // not handled - do default
   //   Default();
   //}

   //// Drawing: for all 4 control types
   //i32 interaction_impl::OnCompareItem(i32 /*nIDCtl*/,LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   //{
   //   // reflect notification to child interaction_impl control
   //   //      LRESULT lResult;
   //   //      if (ReflectLastMsg(lpCompareItemStruct->hwndItem, &lResult))
   //   //       return (i32)lResult;        // eat it

   //   // not handled - do default
   //   return (i32)Default();
   //}

   //void interaction_impl::OnDeleteItem(i32 /*nIDCtl*/,LPDELETEITEMSTRUCT lpDeleteItemStruct)
   //{
   //   // reflect notification to child interaction_impl control
   //   //if (ReflectLastMsg(lpDeleteItemStruct->hwndItem))
   //   // return;     // eat it
   //   // not handled - do default
   //   Default();
   //}

   bool interaction_impl::_EnableToolTips(bool bEnable,UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      return FALSE;
   }


   //bool interaction_impl::GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const
   //{
   //   ASSERT(::is_window(((interaction_impl *) this)->get_handle()));
   //   ASSERT(psbi != nullptr);
   //   return ::GetScrollBarInfo(((interaction_impl *) this)->get_handle(),idObject,psbi) != FALSE;
   //}

   //bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   //{
   //   ASSERT(::is_window(((interaction_impl *) this)->get_handle()));
   //   ASSERT(pti != nullptr);
   //   return ::GetTitleBarInfo(((interaction_impl *) this)->get_handle(),pti) != FALSE;
   //}

   //bool interaction_impl::AnimateWindow(tick tick,u32 dwFlags)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   return ::AnimateWindow(get_handle(),tick,dwFlags) != FALSE;
   //}

   //bool interaction_impl::FlashWindowEx(u32 dwFlags,UINT  uCount,tick tickTimeout)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   FLASHWINFO fwi;
   //   fwi.cbSize = sizeof(fwi);
   //   fwi.hwnd = get_handle();
   //   fwi.dwFlags = dwFlags;
   //   fwi.uCount = uCount;
   //   fwi.tickTimeout = tickTimeout;

   //   return ::FlashWindowEx(&fwi) != FALSE;
   //}



   //bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,u32 dwFlags)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   return ::SetLayeredWindowAttributes(get_handle(),crKey,bAlpha,dwFlags) != FALSE;
   //}

   //bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT *pptDst,SIZE *psize,
   //   ::draw2d::graphics * pDCSrc,POINT *pptSrc,COLORREF crKey,BLENDFUNCTION *pblend,u32 dwFlags)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   ::exception::throw_not_implemented();
   //   return false;
   //   /*      return ::UpdateLayeredWindow(get_handle(), WIN_HDC(pDCDst), pptDst, psize,
   //   WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != FALSE;*/
   //}


   //bool interaction_impl::GetLayeredWindowAttributes(COLORREF *pcrKey,BYTE *pbAlpha,u32 *pdwFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *) this)->get_handle()));
   //   return ::GetLayeredWindowAttributes(((interaction_impl *) this)->get_handle(),pcrKey,pbAlpha,(LPDWORD)pdwFlags) != FALSE;
   //}

   //bool interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics,UINT nFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *) this)->get_handle()));
   //   ::exception::throw_not_implemented();
   //   //      return ::PrintWindow(get_handle(), (HDC)(dynamic_cast<::android::graphics * >(pgraphics))->get_handle(), nFlags) != FALSE;
   //   return false;
   //}


   LRESULT interaction_impl::OnNTCtlColor(WPARAM wParam,LPARAM lParam)
   {
      // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
      //__CTLCOLOR ctl;
      //ctl.hDC = (HDC)wParam;
      //ctl.oswindow = (oswindow)lParam;
      return 0;
   }

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl extensions for help support

   void interaction_impl::WinHelp(uptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      ::exception::throw_not_implemented();

      /*      application* pApp = &System;
      ASSERT_VALID(pApp);
      ASSERT(pApp->m_pszHelpFilePath != nullptr);
      ASSERT(pApp->m_eHelpType == afxWinHelp);

      wait_cursor wait(get_object());

      PrepareForHelp();

      // need to use top level parent (for the case where get_handle() is in DLL)
      __pointer(::user::interaction) pwindow = EnsureTopLevelParent();

      TRACE(trace_category_appmsg, 0, "WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

      // finally, run the Windows Help engine
      /* trans   if (!::WinHelp(NODE_WINDOW(pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
      {
      // android System.message_box(__IDP_FAILED_TO_LAUNCH_HELP);
      System.message_box("Failed to launch help");
      }*/
   }

   //void interaction_impl::HtmlHelp(uptr dwData, UINT nCmd)
   //{
   // ::exception::throw_not_implemented();
   /*
   application* pApp = &System;
   ASSERT_VALID(pApp);
   ASSERT(pApp->m_pszHelpFilePath != nullptr);
   // to call HtmlHelp the m_fUseHtmlHelp must be set in
   // the application's constructor
   ASSERT(pApp->m_eHelpType == afxHTMLHelp);

   wait_cursor wait(get_object());

   PrepareForHelp();

   // need to use top level parent (for the case where get_handle() is in DLL)
   __pointer(::user::interaction) pwindow = EnsureTopLevelParent();

   TRACE(trace_category_appmsg, 0, "HtmlHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

   // run the HTML Help engine
   /* trans   if (!::aura::HtmlHelp(NODE_WINDOW(pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
   {
   // android System.message_box(__IDP_FAILED_TO_LAUNCH_HELP);
   System.message_box("Failed to launch help");
   }*/
   //}

   void interaction_impl::PrepareForHelp()
   {

      __pointer(::user::frame) pFrameWnd = m_puserinteraction;

      if(pFrameWnd.is_set())
      {

         // frame_window android should be allowed to exit help mode first

         pFrameWnd->ExitHelpMode();

      }

      // Cancel any tracking modes
      send_message(WM_CANCELMODE);
      send_message_to_descendants(WM_CANCELMODE,0,0,TRUE,TRUE);

      // need to use top level parent (for the case where get_handle() is in DLL)
      __pointer(::user::interaction) pwindow = EnsureTopLevel();
      pwindow->send_message(WM_CANCELMODE);
      pwindow->send_message_to_descendants(WM_CANCELMODE,0,0,TRUE,TRUE);

      // attempt to cancel capture
      oswindow oswindow_Capture = ::get_capture();

      if (oswindow_Capture != nullptr)
      {

         oswindow_Capture->m_pimpl->m_puserinteraction->send_message(WM_CANCELMODE);

      }

   }


   void interaction_impl::WinHelpInternal(uptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      ::exception::throw_not_implemented();
      /*
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
   }



   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      channel::route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      //      bool b;

      //if(_iguimessageDispatchCommandMessage(pcommand, b))
      // return b;

      channel * pcmdtarget = dynamic_cast <channel *> (this);

      pcmdtarget->channel::route_command_message(pcommand);

   }


   void interaction_impl::_002OnDraw(::image * pimage)
   {

      ::exception::throw_not_implemented();
      //::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::android::graphics * >(pgraphics))->get_handle()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));

   }


   void interaction_impl::message_handler(::message::base * pmessage)
   {


      if(pmessage->m_id == WM_SIZE || pmessage->m_id == WM_MOVE)
      {

         //win_update_graphics();

      }

      if(pmessage->m_id == WM_KEYDOWN ||
            pmessage->m_id == WM_KEYUP ||
            pmessage->m_id == WM_CHAR ||
            pmessage->m_id == WM_SYSKEYDOWN ||
            pmessage->m_id == WM_SYSKEYUP ||
            pmessage->m_id == WM_SYSCHAR)
      {

         SCAST_PTR(::message::key, pkey, pmessage);

         if(pmessage->m_id == WM_KEYDOWN || pmessage->m_id == WM_SYSKEYDOWN)
         {
            try
            {
               Session.set_key_pressed(pkey->m_ekey,true);
            }
            catch(...)
            {
            }
         }
         else if(pmessage->m_id == WM_KEYUP || pmessage->m_id == WM_SYSKEYUP)
         {
            try
            {
               Session.set_key_pressed(pkey->m_ekey,false);
            }
            catch(...)
            {
            }
         }
      }



      if(m_puserinteraction != nullptr)
      {
         if(m_puserinteraction->layout().is_moving())
         {
            //TRACE("moving: skip pre translate message");
         }
         else if(m_puserinteraction->layout().is_sizing())
         {
            //TRACE("sizing: skip pre translate message");
         }
         else
         {
            m_puserinteraction->pre_translate_message(pmessage);
            if(pmessage->m_bRet)
               return;

         }
      }

      if(pmessage->m_id == WM_TIMER)
      {
//         m_puserinteraction->get_context_application()->step_timer();
      }
      else if(pmessage->m_id == WM_LBUTTONDOWN)
      {
         //::rect rectClient;
         //::get_client_rect(get_handle(),rectClient);
         //::rect rectWindow;
         //::get_window_rect(get_handle(),rectWindow);
         //::rect rectRegion;
         //HRGN hrgn = CreateRectRgn(0,0,0,0);
         //int regionType = ::GetWindowRgn(get_handle(),hrgn);
         //if(regionType != ERROR)
         //{
         //   ::GetRgnBox(hrgn,rectRegion);
         //}
         //::DeleteObject(hrgn); /* finished with region */
         //WINDOWPLACEMENT wp;
         //xxf_zero(wp);
         //wp.length = sizeof(WINDOWPLACEMENT);
         //::GetWindowPlacement(get_handle(),&wp);
         //bool bZoomed = ::IsZoomed(get_handle()) != FALSE;
         //bool bIconic = ::IsIconic(get_handle()) != FALSE;
         Session.m_puiLastLButtonDown = m_puserinteraction;
      }
      /*      else if(pbase->m_id == CA2M_BERGEDGE)
      {
      if(pbase->m_wparam == BERGEDGE_GETAPP)
      {
      __pointer(::aura::application)* ppapp= (__pointer(::aura::application)*) pbase->m_lparam;
      *ppapp = get_context_application();
      pbase->m_bRet = true;
      return;
      }
      }*/
      pmessage->set_lresult(0);

      if(pmessage->m_id == WM_MOUSELEAVE)
      {

         _000OnMouseLeave(pmessage);

         return;

      }

      if(pmessage->m_id == WM_LBUTTONDOWN ||
            pmessage->m_id == WM_LBUTTONUP ||
            pmessage->m_id == WM_MBUTTONDOWN ||
            pmessage->m_id == WM_MBUTTONUP ||
            pmessage->m_id == WM_RBUTTONDOWN ||
            pmessage->m_id == WM_RBUTTONUP ||
            pmessage->m_id == WM_LBUTTONDBLCLK ||
            pmessage->m_id == WM_MOUSEMOVE ||
            pmessage->m_id == WM_NCMOUSEMOVE ||
            pmessage->m_id == WM_MOUSEWHEEL)
      {

         message::mouse * pmouse = (::message::mouse *) pmessage;

         Session.on_ui_mouse_message(pmouse);

         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {
            pmouse->m_bTranslated = true;
            rect rectWindow;
            if(m_bScreenRelativeMouseMessagePosition)
            {
               rectWindow.Null();
               //::rect rectWindow32;
               //::get_window_rect(get_handle(), rectWindow32);
               //::copy(rectWindow,rectWindow32);
            }
            else
            {
               m_puserinteraction->get_window_rect(rectWindow);
            }
            /*if(System.get_monitor_count() > 0)
            {
            ::rect rcMonitor;
            System.get_monitor_rect(0,&rcMonitor);
            if(rectWindow.left >= rcMonitor.left)
            pmouse->m_point.x += (LONG)rectWindow.left;
            if(rectWindow.top >= rcMonitor.top)
            pmouse->m_point.y += (LONG)rectWindow.top;
            }
            else*/
            //if(rectWindow.left >= 0)
            pmouse->m_point.x += (LONG)rectWindow.left;
            //if(rectWindow.top >= 0)
            pmouse->m_point.y += (LONG)rectWindow.top;
         }

         if(pmessage->m_id == WM_MOUSEMOVE)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;
         }
         else if(pmessage->m_id == WM_NCMOUSEMOVE)
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

      //if(pbase->m_id == MESSAGE_OLE_DRAGENTER ||
      //   pbase->m_id == MESSAGE_OLE_DRAGOVER ||
      //   pbase->m_id == MESSAGE_OLE_DRAGLEAVE ||
      //   pbase->m_id == MESSAGE_OLE_DRAGDROP)
      //{

      //   message::drag_and_drop * pdrag = (::message::drag_and_drop *) pbase;


      //   user::oswindow_array oswindowa;
      //   user::interaction_ptra wnda;
      //   wnda = System.m_uiptraFrame;
      //   oswindowa = wnda.get_hwnda();
      //   user::window_util::SortByZOrder(oswindowa);
      //   for(i32 i = 0; i < oswindowa.get_size(); i++)
      //   {
      //      __pointer(::user::interaction) pinteraction = wnda.find_first(oswindowa[i]);
      //      if(pinteraction != nullptr)
      //      {
      //         pinteraction->_000OnDrag(pdrag);
      //         if(pdrag->m_bRet)
      //            return;
      //      }
      //   }
      //   return;
      //}
      if(pmessage->m_id == WM_KEYDOWN ||
            pmessage->m_id == WM_KEYUP ||
            pmessage->m_id == WM_CHAR ||
            pmessage->m_id == WM_SYSKEYDOWN ||
            pmessage->m_id == WM_SYSKEYUP ||
            pmessage->m_id == WM_SYSCHAR)
      {

         message::key * pkey = (::message::key *) pmessage;

         __pointer(::user::interaction) puiFocus = Session.get_keyboard_focus();

         if(puiFocus != nullptr && puiFocus->is_window() && puiFocus != m_puserinteraction)
         {

            puiFocus->send(pkey);

            if(pmessage->m_bRet)
               return;

         }
         else if(!pkey->m_bRet)
         {

            if(m_puserinteraction != nullptr)
            {

               m_puserinteraction->_000OnKey(pkey);

               if(pmessage->m_bRet)
                  pmessage;

            }

         }

         pmessage->set_lresult(DefWindowProc(pmessage->m_id, pmessage->m_wparam, pmessage->m_lparam));

         return;

      }
      if(pmessage->m_id == EVENT_MESSAGE)
      {
         if(m_puserinteraction != nullptr)
         {

            m_puserinteraction->on_control_event((::user::control_event *) pmessage->m_lparam.m_lparam);

         }
         return;
      }

      ::user::interaction_impl::message_handler(pmessage);

      //if(pmessage->m_bRet && !pmessage->m_bDoSystemDefault)
      if(pmessage->m_bRet)
         return;
      if(m_puserinteraction != nullptr)
      {
         m_puserinteraction->default_message_handler(pmessage);
      }
      else
      {
         pmessage->set_lresult(DefWindowProc(pmessage->m_id, pmessage->m_wparam, pmessage->m_lparam));
      }
   }


   bool interaction_impl::OnCommand(::message::base * pbase)
   {
      UNREFERENCED_PARAMETER(pbase);
      return FALSE;
   }


   bool interaction_impl::OnNotify(::message::base * pbase)
   {

      ASSERT(pbase != nullptr);
      NMHDR* pNMHDR = (NMHDR*)pbase->m_lparam.m_lparam;
      oswindow oswindow_Ctrl = pNMHDR->hwndFrom;

      // get the child ID from the interaction_impl itself
      //      uptr nID = __get_dialog_control_id(oswindow_Ctrl);
      //      i32 nCode = pNMHDR->code;

      ASSERT(oswindow_Ctrl != nullptr);
      ASSERT(::is_window(oswindow_Ctrl));

      //      if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
      //       return true;        // locked out - ignore control notification

      // reflect notification to child interaction_impl control
      //if(ReflectMessage(oswindow_Ctrl,pbase))
      // return true;        // eaten by child

      //      __NOTIFY notify;
      //    notify.pResult = pResult;
      //  notify.pNMHDR = pNMHDR;
      //xxx   return _001OnCommand(pbase);

      return false;

   }


   bool interaction_impl::IsTopParentActive()
   {
      ASSERT(get_handle() != nullptr);
      ASSERT_VALID(this);

      __pointer(::user::interaction)pWndTopLevel=EnsureTopLevel();

      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
   }

   void interaction_impl::ActivateTopParent()
   {
      // special activate logic for floating toolbars and palettes
      //::user::interaction_impl * pActiveWnd = GetForegroundWindow();
      //if(pActiveWnd == nullptr || !(NODE_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(NODE_WINDOW(pActiveWnd)->get_handle(),get_handle())))
      {
         // clicking on floating frame when it does not have
         // focus itself -- activate the toplevel frame instead.
         EnsureTopLevel()->SetForegroundWindow();
      }
   }



   //::user::interaction * interaction_impl::get_safe_owner(::user::interaction * pParent,oswindow* pWndTop)
   //{
   //   oswindow oswindow = get_safe_owner(pParent->get_handle(),pWndTop);
   //   return ::android::interaction_impl::from_handle(oswindow);
   //}

   //i32 interaction_impl::message_box(const char * lpszText,const char * lpszCaption,UINT nType)
   //{
   //   if(lpszCaption == nullptr)
   //      lpszCaption = Application.m_strAppName;
   //   i32 nResult = ::message_box(get_handle(),lpszText,lpszCaption,nType);
   //   return nResult;
   //}


   i32 interaction_impl::SetScrollPos(i32 nBar,i32 nPos,bool bRedraw)
   {
      //return ::SetScrollPos(get_handle(),nBar,nPos,bRedraw);
      return -1;
   }

   i32 interaction_impl::GetScrollPos(i32 nBar) const
   {
      //return ::GetScrollPos(((::android::interaction_impl *)this)->get_handle(),nBar);
      return -1;
   }

   void interaction_impl::SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos,bool bRedraw)
   {
      //::SetScrollRange(get_handle(),nBar,nMinPos,nMaxPos,bRedraw);

   }

   void interaction_impl::GetScrollRange(i32 nBar,LPINT lpMinPos,LPINT lpMaxPos) const
   {
      //::GetScrollRange(((::android::interaction_impl *)this)->get_handle(),nBar,lpMinPos,lpMaxPos);
   }

   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(i32 nBar,bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar,bEnable);
   }

   //bool interaction_impl::SetScrollInfo(i32 nBar,LPSCROLLINFO lpScrollInfo,bool bRedraw)
   //{
   //   ASSERT(lpScrollInfo != nullptr);

   //   oswindow oswindow = get_handle();
   //   lpScrollInfo->cbSize = sizeof(*lpScrollInfo);
   //   ::SetScrollInfo(oswindow,nBar,lpScrollInfo,bRedraw);
   //   return true;
   //}

   //bool interaction_impl::GetScrollInfo(i32 nBar,LPSCROLLINFO lpScrollInfo,UINT nMask)
   //{
   //   UNREFERENCED_PARAMETER(nMask);
   //   ASSERT(lpScrollInfo != nullptr);

   //   oswindow oswindow = get_handle();
   //   return ::GetScrollInfo(oswindow,nBar,lpScrollInfo) != FALSE;
   //}

   i32 interaction_impl::GetScrollLimit(i32 nBar)
   {
      //i32 nMin,nMax;
      //GetScrollRange(nBar,&nMin,&nMax);
      //SCROLLINFO info;
      //if(GetScrollInfo(nBar,&info,SIF_PAGE))
      //{
      //   nMax -= __max(info.nPage - 1,0);
      //}
      //return nMax;
      return -1;
   }

   void interaction_impl::ScrollWindow(i32 xAmount,i32 yAmount,
                                       LPCRECT lpRect,LPCRECT lpClipRect)
   {
      //ASSERT(::is_window(get_handle()));

      //if(is_window_visible() || lpRect != nullptr || lpClipRect != nullptr)
      //{
      //   // When visible, let Windows do the scrolling
      //   ::ScrollWindow(get_handle(),xAmount,yAmount,lpRect,lpClipRect);
      //}
      //else
      //{
      //   // Windows does not perform any scrolling if the interaction_impl is
      //   // not visible.  This leaves child android unscrolled.
      //   // To ac::count for this oversight, the child android are moved
      //   // directly instead.
      //   oswindow oswindow_Child = ::GetWindow(get_handle(),GW_CHILD);
      //   if(oswindow_Child != nullptr)
      //   {
      //      for(; oswindow_Child != nullptr;
      //         oswindow_Child = ::GetNextWindow(oswindow_Child,GW_HWNDNEXT))
      //      {
      //         ::rect rect;
      //         ::get_window_rect(oswindow_Child,&rect);
      //         _001ScreenToClient(&rect);
      //         ::set_window_pos(oswindow_Child,nullptr,rect.left + xAmount,rect.top + yAmount,0,0,SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
      //      }
      //   }
      //}

   }




   void interaction_impl::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
   {
      /*DWORD dwExStyle = GetExStyle();
      if (nAdjustType == 0)
      dwExStyle &= ~WS_EX_CLIENTEDGE;
      ::AdjustWindowRectEx(lpClientRect, GetStyle(), FALSE, dwExStyle);*/
   }

/////////////////////////////////////////////////////////////////////////////
// Special keyboard/system command processing

   //bool interaction_impl::HandleFloatingSysCommand(UINT nID, LPARAM lparam)
   //{

   //   return false;
   //   /*      __pointer(::user::interaction) pParent = GetTopLevelParent();
   //   switch (nID & 0xfff0)
   //   {
   //   case SC_PREVWINDOW:
   //   case SC_NEXTWINDOW:
   //   if (LOWORD(lparam) == VK_F6 && pParent != nullptr)
   //   {
   //   pParent->SetFocus();
   //   return true;
   //   }
   //   break;

   //   case SC_CLOSE:
   //   case SC_KEYMENU:
   //   // Check lparam.  If it is 0L, then the ::account::user may have done
   //   // an Alt+Tab, so just ignore it.  This breaks the ability to
   //   // just press the Alt-key and have the first menu selected,
   //   // but this is minor compared to what happens in the Alt+Tab
   //   // case.
   //   if ((nID & 0xfff0) == SC_CLOSE || lparam != 0L)
   //   {
   //   if (pParent != nullptr)
   //   {
   //   // Sending the above WM_SYSCOMMAND may destroy the cast,
   //   // so we have to be careful about restoring activation
   //   // and focus after sending it.
   //   oswindow hWndSave = get_handle();
   //   oswindow hWndFocus = ::GetFocus();
   //   pParent->SetActiveWindow();
   //   pParent->send_message(WM_SYSCOMMAND, nID, lparam);

   //   // be very careful here...
   //   if (::is_window(hWndSave))
   //   ::SetActiveWindow(hWndSave);
   //   if (::is_window(hWndFocus))
   //   ::SetFocus(hWndFocus);
   //   }
   //   }
   //   return true;
   //   }
   //   return false;*/
   //}

   //void interaction_impl::WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage)
   //{
   //   ASSERT(puiStop == nullptr || puiStop->is_window());
   //   ASSERT(pmessage != nullptr);

   //   SCAST_PTR(::message::base, pbase, pmessage);
   //   // walk from the target interaction_impl up to the hWndStop interaction_impl checking
   //   //  if any interaction_impl wants to translate this message

   //   for (__pointer(::user::interaction) pinteraction = pbase->m_puserinteraction; pinteraction != nullptr; pinteraction->GetParent())
   //   {

   //      pinteraction->pre_translate_message(pmessage);

   //      if (pmessage->m_bRet)
   //         return; // trapped by target interaction_impl (eg: accelerators)

   //      // got to hWndStop interaction_impl without interest
   //      if (pinteraction == puiStop)
   //         break;

   //   }
   //   // no special processing
   //}


   bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
   {

      return false;

   }


//bool PASCAL interaction_impl::ReflectLastMsg(oswindow hWndChild, LRESULT* pResult)
//{
//   // get the ::collection::map, and if no ::collection::map, then this message does not need reflection
//   /*      single_lock sl(afxMutexHwnd(), TRUE);
//   hwnd_map * pMap = afxMapHWND();
//   if (pMap == nullptr)
//   return FALSE;
//
//   // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
//   __pointer(::interaction_impl) pWnd =  (pMap->lookup_permanent(hWndChild)); */
//   __pointer(::user::interaction) pWnd = (FromHandlePermanent(hWndChild));
//   ASSERT(pWnd == nullptr || LNX_WINDOW(pWnd)->get_handle() == hWndChild);
//   if (pWnd == nullptr)
//   {
//      return FALSE;
//   }
//
//   // only OLE controls and permanent windows will get reflected msgs
//   ASSERT(pWnd != nullptr);
//   return LNX_WINDOW(pWnd)->SendChildNotifyLastMsg(pResult);
//}

//bool interaction_impl::OnChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//{
//
//   return ReflectChildNotify(uMsg, wparam, lparam, pResult);
//}
//
//bool interaction_impl::ReflectChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//{
//   UNREFERENCED_PARAMETER(wparam);
//   // Note: reflected messages are send directly to interaction_impl::OnWndMsg
//   //  and interaction_impl::_001OnCommand for speed and because these messages are not
//   //  routed by normal _001OnCommand routing (they are only dispatched)
//
//   switch (uMsg)
//   {
//      // normal messages (just wparam, lparam through OnWndMsg)
//   case WM_HSCROLL:
//   case WM_VSCROLL:
//   case WM_PARENTNOTIFY:
//   case WM_DRAWITEM:
//   case WM_MEASUREITEM:
//   case WM_DELETEITEM:
//   case WM_VKEYTOITEM:
//   case WM_CHARTOITEM:
//   case WM_COMPAREITEM:
//      // reflect the message through the message ::collection::map as WM_REFLECT_BASE+uMsg
//      //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wparam, lparam, pResult);
//      return FALSE;
//
//      // special case for WM_COMMAND
//   case WM_COMMAND:
//   {
//      // reflect the message through the message ::collection::map as OCM_COMMAND
//      /* xxx         i32 nCode = HIWORD(wparam);
//      if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_COMMAND), nullptr, nullptr))
//      {
//      if (pResult != nullptr)
//      *pResult = 1;
//      return TRUE;
//      } */
//   }
//   break;
//
//   // special case for WM_NOTIFY
//   /*      case WM_NOTIFY:
//   {
//   // reflect the message through the message ::collection::map as OCM_NOTIFY
//   NMHDR* pNMHDR = (NMHDR*)lparam;
//   //            i32 nCode = pNMHDR->code;
//   //            __NOTIFY notify;
//   //          notify.pResult = pResult;
//   //        notify.pNMHDR = pNMHDR;
//   // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
//   }
//
//   // other special cases (WM_CTLCOLOR family)*/
//   default:
//      if (uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
//      {
//         // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
//         /*__CTLCOLOR ctl;
//         ctl.hDC = (HDC)wparam;
//         ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
//         //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
//         ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);
//
//         // reflect the message through the message ::collection::map as OCM_CTLCOLOR
//         bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
//         if ((HBRUSH)*pResult == nullptr)
//         bResult = FALSE;
//         return bResult;*/
//         return false;
//      }
//      break;
//   }
//
//   return false;   // let the parent handle it
//}

   void interaction_impl::OnParentNotify(UINT message, LPARAM lparam)
   {
      //if ((LOWORD(message) == WM_CREATE || LOWORD(message) == WM_DESTROY))
      //{
      //   if (ReflectLastMsg((oswindow)lparam))
      //      return;     // eat it
      //}
      //// not handled - do default
      //Default();
   }

   void interaction_impl::OnSetFocus(::user::interaction *)
   {
      bool bHandled;

      bHandled = FALSE;
      if (!bHandled)
      {
         Default();
      }
   }


   //LRESULT interaction_impl::OnActivateTopLevel(WPARAM wparam, LPARAM)
   //{

   //   return 0;

   //}


   void interaction_impl::OnSysColorChange()
   {

   }


   bool gen_GotScrollLines;


   void interaction_impl::OnSettingChange(UINT uFlags, const char * lpszSection)
   {

      gen_GotScrollLines = FALSE;

      interaction_impl::OnDisplayChange(0, 0);

   }


   LRESULT interaction_impl::OnDisplayChange(WPARAM, LPARAM)
   {

      if (!(GetStyle() & WS_CHILD))
      {

         //const MESSAGE* pMsg = GetCurrentMessage();

         //send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam, TRUE, TRUE);

      }

      return Default();

   }


   LRESULT interaction_impl::OnDragList(WPARAM, LPARAM lparam)
   {

      __throw(not_implemented());
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


   //void interaction_impl::set_need_redraw()
   //{

   //   if (!m_puserinteraction->m_bProDevian)
   //   {

   //      if (m_puserinteraction->m_pthread != nullptr)
   //      {

   //         if (!m_bRedraw)
   //         {

   //            m_bRedraw = true;

   //            m_puserinteraction->m_pthread->post_message(WM_KICKIDLE);

   //         }

   //      }

   //   }

   //}


   void interaction_impl::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      Default();

      if (m_puserinteraction->is_message_only_window())
      {

         TRACE("good : opt out!");

      }
      else
      {

         //m_pthreadDraw = ::fork(get_context_application(), [&]()
         //{

         //   DWORD tickStart;

         //   while (::thread_get_run())
         //   {

         // auto tickStart = ::tick::now();

         //      if (!m_puserinteraction->m_bLockWindowUpdate)
         //      {

         //         if (m_puserinteraction->has_pending_graphical_update())
         //         {

         //            set_need_redraw(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);

         //            m_puserinteraction->on_after_graphical_update();

         //         }

         //      }

         //      _001UpdateBuffer();

         //      if (m_spgraphics.is_set())
         //      {

         //         m_spgraphics->update_window();

         //      }

         //      if (tickStart.elapsed() < 5)
         //      {

         //         Sleep(5);

         //      }

         //   }

         //});

      }

   }


   bool CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lparam)
   {
      user::oswindow_array * phwnda = (user::oswindow_array *) lparam;
      phwnda->add(hwnd);
      return TRUE;
   }


   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   {

      // __throw(not_implemented());
      // EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);

   }


   /*   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
   {
   _001DeferPaintLayeredWindowBackground(pgraphics);
   }*/


   //class print_window :
   //   virtual ::object
   //{
   //public:



   //   manual_reset_event m_event;
   //   oswindow m_hwnd;
   //   HDC m_hdc;

   //   print_window(oswindow hwnd, HDC hdc, DWORD tickTimeout)
   //   {

   //      m_event.ResetEvent();
   //      m_hwnd = hwnd;
   //      m_hdc = hdc;
   //      begin_thread( &print_window::s_print_window, (LPVOID) this, ::priority_normal);
   //      if (m_event.wait(millis(tickTimeout)).timeout())
   //      {
   //         TRACE("print_window::time_out");
   //      }
   //   }


   //   static ::estatus     c_cdecl s_print_window(LPVOID pvoid)
   //   {
   //      print_window * pprintwindow = (print_window *)pvoid;
   //      try
   //      {
   //         HANDLE hevent = (HANDLE)pprintwindow->m_event.get_os_data();
   //         __throw(not_implemented(pprintwindow->get_context_application()));
   //         /*            ::PrintWindow(pprintwindow->m_hwnd, pprintwindow->m_hdc, 0);
   //         ::SetEvent(hevent);*/
   //      }
   //      catch (...)
   //      {
   //      }
   //      return 0;
   //   }
   //};

   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

      ::rect rectClient;

      m_puserinteraction->get_client_rect(rectClient);


      //pgraphics->FillSolidRect(rectClient, 0x00000000);

      //return;
      ::rect rectUpdate;
      m_puserinteraction->get_window_rect(rectUpdate);
      //      SetViewportOrgEx(hdc, 0, 0, nullptr);
      ::rect rectPaint;
      rectPaint = rectUpdate;
      m_puserinteraction->_001ScreenToClient(rectPaint);
      user::oswindow_array wndaApp;


      HRGN rgnWindow;
      HRGN rgnIntersect;
      HRGN rgnUpdate = nullptr;

      __throw(not_implemented());

   }

   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }

   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {

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
      //         (dynamic_cast<::android::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         if(m_puserinteraction != nullptr && m_puserinteraction != this)
      //         {
      //            m_puserinteraction->_001OnDeferPaintLayeredWindowBackground(pgraphics);
      //         }
      //         else
      //         {
      //            _001OnDeferPaintLayeredWindowBackground(pgraphics);
      //         }
      //         (dynamic_cast<::android::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         (dynamic_cast<::android::graphics * >(pgraphics))->SetViewportOrg(::point());
      //         _000OnDraw(pgraphics);
      //         (dynamic_cast<::android::graphics * >(pgraphics))->SetViewportOrg(::point());
      //         //(dynamic_cast<::android::graphics * >(pgraphics))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //         (dynamic_cast<::android::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //         (dynamic_cast<::android::graphics * >(pgraphics))->SetViewportOrg(::point());
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


   //void interaction_impl::OnEnterIdle(UINT /*nWhy*/ , ::user::interaction  /*pWho*/)
   //{
   //   // In some OLE inplace active scenarios, OLE will post a
   //   // message instead of sending it.  This causes so many WM_ENTERIDLE
   //   // messages to be sent that tasks running in the background stop
   //   // running.  By dispatching the pending WM_ENTERIDLE messages
   //   // when the first one is received, we trick oswindows into thinking
   //   // that only one was really sent and dispatched.
   //   {
   //      MESSAGE msg;
   //      __throw(not_implemented());
   //      //while (PeekMessage(&msg, nullptr, WM_ENTERIDLE, WM_ENTERIDLE, PM_REMOVE))
   //      //while (PeekMessage(&msg, nullptr, WM_ENTERIDLE, WM_ENTERIDLE, TRUE))
   //      // DispatchMessage(&msg);
   //   }

   //   Default();
   //}

   HBRUSH interaction_impl::OnCtlColor(::draw2d::graphics *, ::user::interaction * pWnd, UINT)
   {
      ASSERT(pWnd != nullptr && pWnd->get_handle() != nullptr);
      LRESULT lResult;
      if (pWnd->m_pimpl.cast < interaction_impl >()->SendChildNotifyLastMsg(&lResult))
         return (HBRUSH)lResult;     // eat it
      return (HBRUSH)Default();
   }

//// implementation of OnCtlColor for default gray backgrounds
////   (works for any interaction_impl containing controls)
////  return value of FALSE means caller must call DefWindowProc's default
////  TRUE means that 'hbrGray' will be used and the appropriate text
////    ('clrText') and background colors are set.
//   bool PASCAL interaction_impl::GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
//         HBRUSH hbrGray, COLORREF clrText)
//   {
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


   void interaction_impl::CenterWindow(::user::interaction * pAlternateOwner)
   {
      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //
      //      // determine owner interaction_impl to center against
      //      DWORD dwStyle = GetStyle();
      //      __pointer(::user::interaction) hWndCenter = pAlternateOwner;
      //      if (pAlternateOwner == nullptr)
      //      {
      //         if (dwStyle & WS_CHILD)
      //            hWndCenter = GetParent();
      //         else
      //            hWndCenter = GetWindow(GW_OWNER);
      //         if (hWndCenter != nullptr)
      //         {
      //            // let parent determine alternate center interaction_impl
      //            __pointer(::user::interaction) hWndTemp =
      //               (__pointer(::user::interaction) )hWndCenter->send_message(WM_QUERYCENTERWND, 0, 0);
      //            if (hWndTemp != nullptr)
      //               hWndCenter = hWndTemp;
      //         }
      //      }
      //
      //      // get coordinates of the interaction_impl relative to its parent
      //      rect rcDlg;
      //      get_window_rect(&rcDlg);
      //      rect rcarea;
      //      rect rcCenter;
      //      __pointer(::user::interaction) hWndParent;
      //      if (!(dwStyle & WS_CHILD))
      //      {
      //         // don't center against invisible or minimized windows
      //         if (hWndCenter != nullptr)
      //         {
      //            DWORD dwAlternateStyle = hWndCenter->GetWindowLong(GWL_STYLE);
      //            if (!(dwAlternateStyle & WS_VISIBLE) || (dwAlternateStyle & WS_MINIMIZE))
      //               hWndCenter = nullptr;
      //         }
      //
      //         MONITORINFO mi;
      //         mi.cbSize = sizeof(mi);
      //
      //         // center within appropriate monitor coordinates
      //         if (hWndCenter == nullptr)
      //         {
      //            oswindow hwDefault = System.GetMainWnd()->get_handle();
      //
      //            GetMonitorInfo(
      //               MonitorFromWindow(hwDefault, MONITOR_DEFAULTTOPRIMARY), &mi);
      //            rcCenter = mi.rcWork;
      //            rcarea = mi.rcWork;
      //         }
      //         else
      //         {
      //            hWndCenter->get_window_rect(&rcCenter);
      //            GetMonitorInfo(
      //               MonitorFromWindow(hWndCenter->get_handle(), MONITOR_DEFAULTTONEAREST), &mi);
      //            rcarea = mi.rcWork;
      //         }
      //      }
      //      else
      //      {
      //         // center within parent client coordinates
      //         hWndParent = GetParent();
      //         ASSERT(hWndParent->is_window());
      //
      //         hWndParent->get_client_rect(&rcarea);
      //         ASSERT(hWndCenter->is_window());
      //         hWndCenter->get_client_rect(&rcCenter);
      //         ::MapWindowPoints(hWndCenter->get_handle(), hWndParent->get_handle(), (POINT*)&rcCenter, 2);
      //      }
      //
      //      // find dialog's upper left based on rcCenter
      //      i32 xLeft = (rcCenter.left + rcCenter.right) / 2 - rcDlg.width() / 2;
      //      i32 yTop = (rcCenter.top + rcCenter.bottom) / 2 - rcDlg.height() / 2;
      //
      //      // if the dialog is outside the screen, move it inside
      //      if (xLeft < rcarea.left)
      //         xLeft = rcarea.left;
      //      else if (xLeft + rcDlg.width() > rcarea.right)
      //         xLeft = rcarea.right - rcDlg.width();
      //
      //      if (yTop < rcarea.top)
      //         yTop = rcarea.top;
      //      else if (yTop + rcDlg.height() > rcarea.bottom)
      //         yTop = rcarea.bottom - rcDlg.height();
      //
      //      // ::collection::map screen coordinates to child coordinates
      //      set_window_pos(nullptr, xLeft, yTop, -1, -1,
      //         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   bool interaction_impl::CheckAutoCenter()
   {
      return TRUE;
   }


   ///////////////////////////////////////////////////////////////////////////////
   //// Dialog initialization support


   //bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
   //{

   //   // find resource handle
   //   LPVOID lpResource = nullptr;

   //   HGLOBAL hResource = nullptr;

   //   if (lpszResourceName != nullptr)
   //   {
   //      //         HINSTANCE hInst = ::ca2::FindResourceHandle(lpszResourceName, RT_DLGINIT);
   //      //       HRSRC hDlgInit = ::FindResource(hInst, lpszResourceName, RT_DLGINIT);
   //      /*     if (hDlgInit != nullptr)
   //      {
   //      // load it
   //      hResource = LoadResource(hInst, hDlgInit);
   //      if (hResource == nullptr)
   //      return FALSE;
   //      // lock it
   //      lpResource = LockResource(hResource);
   //      ASSERT(lpResource != nullptr);
   //      }*/
   //   }

   //   // execute it
   //   bool bResult = ExecuteDlgInit(lpResource);

   //   // cleanup
   //   if (lpResource != nullptr && hResource != nullptr)
   //   {

   //      __throw(not_implemented());

   // 

   //   }

   //   return bResult;

   //}


   //bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   //{

   //   __throw(not_implemented());

   //}


   void interaction_impl::UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler)
   {

      //UNREFERENCED_PARAMETER(pTarget);

      //UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      //::user::command state(get_object());

   }


   bool interaction_impl::is_frame_window()
   {

      return false;

   }


   bool interaction_impl::SubclassWindow(oswindow hWnd)
   {

      if (!Attach(hWnd))
      {

         return false;

      }

      // allow any other subclassing to occur
      pre_subclass_window();

      __throw(not_implemented());


   }


   oswindow interaction_impl::UnsubclassWindow()
   {

      ASSERT(::is_window((oswindow)get_handle()));

      __throw(not_implemented());

   }


   //bool interaction_impl::IsChild(::user::interaction * pWnd)
   //{

   //   ASSERT(::is_window((oswindow)get_handle()));

   //   if (pWnd->get_handle() == nullptr)
   //   {

   //      return ::user::interaction_impl::is_child(pWnd);

   //   }
   //   else
   //   {

   //      return ::IsChild((oswindow)get_handle(), pWnd->get_handle()) != FALSE;

   //   }

   //}


   bool interaction_impl::_is_window() const
   {

      return ::is_window((oswindow)get_safe_handle()) != FALSE;

   }


   oswindow interaction_impl::get_handle() const
   {

      return m_oswindow;

   }


//#define SWP_IGNOREPALACEGUARD 0x80000000
//
//   bool interaction_impl::set_window_pos(iptr z, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags)
//   {
//
//      return ::user::interaction_impl::set_window_pos(z, x, y, cx, cy, nFlags);
//
//      //      single_lock sl(&user_mutex(), true);
//
//      //xdisplay d(m_oswindow->display());
//
//      ::rect rectScreen;
//
//      m_puserinteraction->best_monitor(rectScreen);
//
//      int iPalaceGuard = 256;
//
//      if (nFlags & SWP_IGNOREPALACEGUARD)
//         iPalaceGuard = 1;
//
//      if (x > rectScreen.right - iPalaceGuard)
//         x = rectScreen.right - iPalaceGuard;
//
//      if (x < 0)
//         x = 0;
//
//      if (y > rectScreen.bottom - iPalaceGuard)
//         y = rectScreen.bottom - iPalaceGuard;
//
//      if (y < 0)
//         y = 0;
//
//      if (cx > rectScreen.width())
//         cx = rectScreen.width();
//
//      if (cx < iPalaceGuard)
//         cx = iPalaceGuard;
//
//      if (cy > rectScreen.height())
//         cy = rectScreen.height();
//
//      if (cy < iPalaceGuard)
//         cy = iPalaceGuard;
//
//
//      ASSERT(::is_window((oswindow)get_handle()));
//      /*   return ::set_window_pos(get_handle(), pWndInsertAfter->get_handle(),
//      x, y, cx, cy, nFlags) != FALSE; */
//
//      //__throw(not_implemented());
//
//      //XSizeHints hints;
//
//      ::set_window_pos((oswindow) get_handle(), 0, x, y, cx, cy, nFlags);
//      if (nFlags & SWP_NOMOVE)
//      {
//         if (nFlags & SWP_NOSIZE)
//         {
//            //hints.flags = 0;
//         }
//         else
//         {
//            //hints.flags = PSize;
//            //hints.width = cx;
//            //hints.height = cy;
//            //XResizeWindow(m_oswindow->display(), m_oswindow->window(), cx, cy);
//            //            XClearWindow(m_oswindow->display(), m_oswindow->interaction_impl());
//         }
//      }
//      else
//      {
//      }
//
//      if (!is_window_visible())
//      {
//
//         /*XSetNormalHints(m_oswindow->display(), m_oswindow->window(), &hints);*/
//
//      }
//
//      ::rect rect;
//
//      ::get_window_rect(get_handle(), rect);
//
//      ::copy(m_rectParentClient, rect);
//
//      if ((nFlags & SWP_SHOWWINDOW))
//      {
//
//         if (!is_window_visible())
//         {
//
//            /*XMapWindow(m_oswindow->display(), m_oswindow->window());*/
//
//            ::show_window(get_handle(), display_normal);
//
//         }
//
//      }
//
//
//      return true;
//
//   }


   //void interaction_impl::MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight, bool bRepaint)
   //{
   //   ASSERT(::is_window((oswindow)get_handle()));
   //   SetWindowPos(0, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);
   //}


   //bool interaction_impl::_001ClientToScreen(LPRECT lprect)
   //{

   //   ::rect64 rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left += (LONG)rectWindow.left;
   //   lprect->right += (LONG)rectWindow.left;
   //   lprect->top += (LONG)rectWindow.top;
   //   lprect->bottom += (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ClientToScreen(LPPOINT lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x += (LONG)rectWindow.left;
   //   lppoint->y += (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ClientToScreen(RECT64 * lprect)
   //{

   //   ::rect rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left += rectWindow.left;
   //   lprect->right += rectWindow.left;
   //   lprect->top += rectWindow.top;
   //   lprect->bottom += rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ClientToScreen(POINT64 * lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x += rectWindow.left;
   //   lppoint->y += rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(LPRECT lprect)
   //{

   //   ::rect64 rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left -= (LONG)rectWindow.left;
   //   lprect->right -= (LONG)rectWindow.left;
   //   lprect->top -= (LONG)rectWindow.top;
   //   lprect->bottom -= (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(LPPOINT lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x -= (LONG)rectWindow.left;
   //   lppoint->y -= (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(RECT64 * lprect)
   //{

   //   ::rect64 rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left -= rectWindow.left;
   //   lprect->right -= rectWindow.left;
   //   lprect->top -= rectWindow.top;
   //   lprect->bottom -= rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(POINT64 * lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x -= rectWindow.left;
   //   lppoint->y -= rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::get_window_rect(RECT64 * lprect)
   //{

   //   if (!::is_window((oswindow)get_handle()))
   //   {

   //      return false;

   //   }

   //   // if it is temporary interaction_impl - probably not ca2 wrapped interaction_impl
   //   //if(m_puserinteraction == nullptr || m_puserinteraction == this)
   //   {
   //      ::rect rect32;

   //      if(!::get_window_rect((oswindow)get_handle(),rect32))
   //      {

   //         return false;

   //      }

   //      ::copy(lprect, rect32);
   //   }
   //   //else
   //   {
   //      //  interaction::get_window_rect(lprect);
   //   }

   //   return true;

   //}


   //bool interaction_impl::get_client_rect(RECT64 * lprect)
   //{

   //   if(!::is_window((oswindow)get_handle()))
   //   {

   //      return false;

   //   }
   //   // if it is temporary interaction_impl - probably not ca2 wrapped interaction_impl
   //   //if(m_puserinteraction == nullptr || m_puserinteraction == this)
   //   {
   //      ::rect rect32;
   //      if(!::get_client_rect((oswindow)get_handle(),rect32))
   //      {

   //         return false;

   //      }
   //      ::copy(lprect, rect32);
   //   }
   //   //else
   //   {
   //      // interaction::get_client_rect(lprect);
   //   }

   //   return true;

   //}


   id interaction_impl::SetDlgCtrlId(id id)
   {

      return m_puserinteraction->SetDlgCtrlId(id);
   }

   id interaction_impl::GetDlgCtrlId()
   {
      return m_puserinteraction->GetDlgCtrlId();
   }



   //void interaction_impl::_001WindowMaximize()
   //{
   //   ::user::interaction_impl::_001WindowMaximize();
   //}


   //void interaction_impl::_001WindowRestore()
   //{

   //   if (m_puserinteraction != nullptr)
   //   {

   //      m_puserinteraction->m_edisplay = ::display_normal;

   //   }

   //   ::show_window((oswindow)get_handle(), SW_RESTORE);

   //}


   bool interaction_impl::ShowWindow(i32 nCmdShow)
   {

      if (!::is_window((oswindow)get_handle()))
      {

         return false;

      }

      ::show_window((oswindow)get_handle(), nCmdShow);

      return m_puserinteraction->is_window_visible();

   }


   //bool interaction_impl::layout().is_iconic()
   //{

   //   if (GetExStyle() & WS_EX_LAYERED)
   //   {

   //      return m_puserinteraction->m_edisplay == ::display_iconic;

   //   }
   //   else
   //   {

   //      return ::IsIconic((oswindow)get_handle()) != FALSE;

   //   }

   //}

   
   LONG interaction_impl::GetWindowLong(i32 nIndex)
   {

      return ::GetWindowLong((oswindow)get_handle(), nIndex);

   }


   LONG interaction_impl::SetWindowLong(i32 nIndex, LONG lValue)
   {
      return ::SetWindowLong((oswindow)get_handle(), nIndex, lValue);
   }




// interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const ::user::interaction_impl& wnd) const
   {
      return const_cast < ::user::interaction_impl * >  (&wnd)->get_handle() == ((interaction_impl *)this)->get_handle();
   }

   bool interaction_impl::operator!=(const ::user::interaction_impl& wnd) const
   {
      return const_cast < ::user::interaction_impl * >  (&wnd)->get_handle() != ((interaction_impl *)this)->get_handle();
   }

//DWORD interaction_impl::GetStyle() const
//{
//   ASSERT(::is_window((oswindow)get_handle()));
//   return (DWORD)::GetWindowLong((oswindow)get_handle(), GWL_STYLE);
//}
//
//DWORD interaction_impl::GetExStyle() const
//{
//   ASSERT(::is_window((oswindow)get_handle()));
//   return (DWORD)::GetWindowLong((oswindow)get_handle(), GWL_EXSTYLE);
//}


   bool interaction_impl::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
   
      ASSERT(::is_window((oswindow)get_handle()));
   
      return ModifyStyle((oswindow)get_handle(), dwRemove, dwAdd, nFlags);

   }


   bool interaction_impl::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      ASSERT(::is_window((oswindow)get_handle()));

      return ModifyStyleEx((oswindow)get_handle(), dwRemove, dwAdd, nFlags);

   }

   
   void interaction_impl::set_owner(::user::interaction * pOwnerWnd)
   {
      //      m_puiOwner = pOwnerWnd;
      m_puserinteraction->SetOwner((pOwnerWnd));
   }

   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)
   {

      if (::get_thread() == nullptr)
      {

         ::set_thread(m_puserinteraction->get_context_application());

      }

      return ::user::interaction_impl::send_message(message, wparam, lparam);

   }


   bool interaction_impl::post_message(UINT message, WPARAM wparam, lparam lparam)
   {

      return ::user::interaction_impl::post_message(message, wparam, lparam);
      //return ::post_me((oswindow)get_handle(), message, wparam, lparam) != FALSE;

   }


   //bool interaction_impl::DragDetect(POINT pt) const
   //{

   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));

   //   //return ::DragDetect(get_handle(), point) != FALSE;

   //}


//void interaction_impl::RedrawWindo
   void interaction_impl::SetFont(::draw2d::font* pfont, bool bRedraw)
   {

      UNREFERENCED_PARAMETER(bRedraw);

      //ASSERT(::is_window((oswindow) get_handle())); m_pfont = new ::draw2d::font(*pfont);

   }


   ::draw2d::font* interaction_impl::GetFont()
   {

      //ASSERT(::is_window((oswindow) get_handle()));

      //return m_pfont;
      return nullptr;

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      __throw(not_implemented());

      //ASSERT(::is_window((oswindow) get_handle()));
      //::DragAcceptFiles(get_handle(), bAccept);

   }

   /*
   __pointer(::user::frame_window) interaction_impl::EnsureParentFrame()
   {

   __pointer(::user::frame_window) pFrameWnd=GetParentFrame();

   ENSURE_VALID(pFrameWnd);

   return pFrameWnd;

   }


   ::user::interaction * interaction_impl::EnsureTopLevelParent()
   {

   __pointer(::user::interaction)pWnd=GetTopLevelParent();

   ENSURE_VALID(pWnd);

   return pWnd;

   }

   */


   void interaction_impl::set_window_text(const char * lpszString)
   {

      m_strWindowText = lpszString;

   }


   strsize interaction_impl::get_window_text(char * lpszStringBuf, strsize nMaxCount)
   {

      strncpy(lpszStringBuf, m_strWindowText, nMaxCount);

      return min(nMaxCount, m_strWindowText.get_length());

   }


   void interaction_impl::get_window_text(string & rString)
   {

      m_strWindowText = rString;

   }


   strsize interaction_impl::get_window_text_length()
   {

      return m_strWindowText.get_length();

   }


   //::user::interaction * interaction_impl::GetParent()
   //{

   //   if (!::is_window((oswindow)get_handle()))
   //      return nullptr;

   //   if (get_handle() == nullptr)
   //      return nullptr;

   //   //return ::linux::interaction_impl::from_handle(::GetParent(get_handle()));

   //   return nullptr;

   //}

   //void interaction_impl::MoveWindow(LPCRECT lpRect, bool bRepaint)
   //{

   //   MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);

   //}


   //UINT interaction_impl::ArrangeIconicWindows()
   //{

   //   __throw(not_implemented());

   //   //      ASSERT(::is_window((oswindow) get_handle())); return ::ArrangeIconicWindows(get_handle());

   //}


   //i32 interaction_impl::SetWindowRgn(HRGN hRgn, bool bRedraw)
   //{

   //   UNREFERENCED_PARAMETER(hRgn);
   //   UNREFERENCED_PARAMETER(bRedraw);

   //   //__throw(not_implemented());

   //   //      ASSERT(::is_window((oswindow) get_handle())); return ::SetWindowRgn(get_handle(), hRgn, bRedraw);

   //   return 0;

   //}


   //i32 interaction_impl::GetWindowRgn(HRGN hRgn)
   //{

   //   __throw(not_implemented());

   //   //      ASSERT(::is_window((oswindow) get_handle()) && hRgn != nullptr); return ::GetWindowRgn(get_handle(), hRgn);
   //   return 0;

   //}


   //bool interaction_impl::BringWindowToTop()
   //{

   //   //      __throw(not_implemented());
   //   //      return ::BringWindowToTop(get_handle()) != FALSE;

   //   return true;

   //}


   //void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPPOINT lpPoint, UINT nCount)
   //{

   //   __throw(not_implemented());

   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      ::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_handle(), lpPoint, nCount);

   //}


   //void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPRECT lpRect)
   //{

   //   __throw(not_implemented());

   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      ::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_handle(), (LPPOINT)lpRect, 2);

   //}


   ::draw2d::graphics * interaction_impl::GetDC()
   {

      ::draw2d::graphics_pointer g(e_create);

      //xdisplay d(m_oswindow->display());

      oswindow oswindow;

      if (get_handle() == nullptr)
      {

         //         oswindow = ::get_desktop_window();

      }
      else
      {

         oswindow = (::oswindow) get_handle();

      }

      ::rect rectClient;

      //oswindow->get_client_rect(rectClient);

      rectClient.left = 0;
      rectClient.top = 0;
      rectClient.right = 500;
      rectClient.bottom = 500;
      //      (dynamic_cast < ::android::graphics * >(g.m_p))->attach(cairo_create(cairo_xlib_surface_create(oswindow->display(), oswindow->interaction_impl(), oswindow->draw2d(),rectClient.width(), rectClient.height())));
      return g.detach();
   }

   ::draw2d::graphics * interaction_impl::GetWindowDC()
   {
      /*ASSERT(::is_window((oswindow)get_handle()));
      ::draw2d::graphics_pointer g(e_create);
      g->attach(::GetWindowDC(get_handle()));
      return g.detach();*/
      return GetDC();
   }

   //bool interaction_impl::ReleaseDC(::image * pimage)
   //{

   //   //if (pgraphics == nullptr)
   //   // return false;

   //   /*      cairo_t * pcairo = (cairo_t *) pgraphics->get_os_data();

   //   cairo_surface_t * psurface = cairo_get_target(pcairo);
   //   if(pcairo ==  g_cairo)
   //   {
   //   printf("123");

   //   }

   //   cairo_destroy(pcairo);

   //   if(psurface == g_cairosurface)
   //   {
   //   printf("123");
   //   }      cairo_surface_destroy(psurface);*/

   //   //      if(((Gdiplus::Graphics *)(dynamic_cast<::android::graphics * >(pgraphics))->get_handle()) == nullptr)
   //   //       return false;

   //   //::ReleaseDC(get_handle(), (dynamic_cast < ::android::graphics * > (pgraphics))->detach());

   //   //      (dynamic_cast<::android::graphics * >(pgraphics))->m_hdc = nullptr;

   //   //      pgraphics->release();

   //   return true;

   //}

   //void interaction_impl::UpdateWindow()
   //{
   //   __throw(not_implemented());
   //   //::UpdateWindow(get_handle());
   //}

   //void interaction_impl::SetRedraw(bool bRedraw)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
   //}

   //bool interaction_impl::GetUpdateRect(LPRECT lpRect, bool bErase)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //return ::GetUpdateRect(get_handle(), lpRect, bErase) != FALSE;
   //}

   //i32 interaction_impl::GetUpdateRgn(draw2d::region * pRgn, bool bErase)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
   //}

   //void interaction_impl::Invalidate(bool bErase)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::InvalidateRect(get_handle(), nullptr, bErase);
   //}

   //void interaction_impl::InvalidateRect(LPCRECT lpRect, bool bErase)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::InvalidateRect(get_handle(), lpRect, bErase);
   //}

   //void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
   //}

   //void interaction_impl::ValidateRect(LPCRECT lpRect)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::ValidateRect(get_handle(), lpRect);
   //}

   //void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   //{
   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::ValidateRgn(get_handle(), (HRGN)pRgn->get_handle());
   //}

   bool interaction_impl::is_window_visible()
   {

      if (!::is_window((oswindow)get_handle()))
      {

         return false;

      }

      if (m_puserinteraction != nullptr)
      {

         if (!m_puserinteraction->is_this_visible())
         {

            return false;

         }

         if (m_puserinteraction->GetParent() != nullptr && !m_puserinteraction->GetParent()->is_window_visible())
            return false;

      }

      if (!::IsWindowVisible(get_handle()))
         return false;

      return true;

   }


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      __throw(not_implemented());
      //ASSERT(::is_window((oswindow) get_handle()));
      //::ShowOwnedPopups(get_handle(), bShow);

   }

   //void interaction_impl::send_message_to_descendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   //{
   //   ASSERT(::is_window((oswindow)get_handle()));
   //   //interaction_impl::send_message_to_descendants(get_handle(), message, wparam, lparam, bDeep, bOnlyPerm);

   //   // walk through oswindows to avoid creating temporary interaction_impl objects
   //   // unless we need to call this function recursively
   //   user::interaction * pinteraction = m_puserinteraction->first_child();
   //   while (pinteraction != nullptr)
   //   {
   //      try
   //      {
   //         pinteraction->send_message(message, wparam, lparam);
   //      }
   //      catch (...)
   //      {
   //      }
   //      if (bDeep)
   //      {
   //         // send to child windows after parent
   //         try
   //         {
   //            pinteraction->send_message_to_descendants(message, wparam, lparam, bDeep, bOnlyPerm);
   //         }
   //         catch (...)
   //         {
   //         }
   //      }
   //      try
   //      {
   //         pinteraction = pinteraction->next_sibling();
   //      }
   //      catch (...)
   //      {
   //         break;
   //      }
   //   }
   //}

   //::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip, DWORD flags)
   //{

   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //::draw2d::graphics_pointer g(get_object());
   //   //g->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_handle(), flags));
   //   //return g.detach();

   //}

   bool interaction_impl::LockWindowUpdate()
   {

      __throw(not_implemented());
      //ASSERT(::is_window((oswindow) get_handle()));
      //return ::LockWindowUpdate(get_handle()) != FALSE;

   }

   void interaction_impl::UnlockWindowUpdate()
   {

      __throw(not_implemented());
      //ASSERT(::is_window((oswindow) get_handle()));
      //::LockWindowUpdate(nullptr);

   }


   //bool interaction_impl::RedrawWindow(const ::rect & rectUpdate, ::draw2d::region * prgnUpdate, UINT flags)
   //{

   //   if (!is_window_visible())
   //   {

   //      return true;

   //   }

   //   if (flags & RDW_UPDATENOW)
   //   {

   //      _001UpdateWindow();

   //   }
   //   else
   //   {

   //      m_puserinteraction->m_bRedraw = true;

   //   }

   //   return true;

   //}

   /*
   bool interaction_impl::EnableScrollBar(i32 nSBFlags, UINT nArrowFlags)
   {

   ASSERT(::is_window((oswindow) get_handle()));

   return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != FALSE;

   }
   */

   //bool interaction_impl::DrawAnimatedRects(i32 idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo)
   //{

   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //return ::DrawAnimatedRects(get_handle(), idAni, lprcFrom, lprcTo) != FALSE;

   //}

   //bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, LPCRECT lprc, UINT uFlags)
   //{

   //   __throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::android::graphics * >(pgraphics))->get_handle(), lprc, uFlags) != FALSE;

   //}

   //bool interaction_impl::SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer)
   //{

   //   return ::user::interaction_impl::SetTimer(nIDEvent, nElapse, pfnTimer);

   //   //return ::user::interaction_impl::SetTimer(nIDEvent, nElapse, lpfnTimer);


   //   //UNREFERENCED_PARAMETER(lpfnTimer);

   //   //m_puserinteraction->get_context_application()->set_timer(m_puserinteraction, nIDEvent, nElapse);

   //   //return nIDEvent;

   //   //__throw(not_implemented());
   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //return ::SetTimer(get_handle(), nIDEvent, nElapse, lpfnTimer);

   //}


   //bool interaction_impl::KillTimer(uptr nIDEvent)
   //{

   //   return ::user::interaction_impl::KillTimer(nIDEvent);

   //   //m_puserinteraction->get_context_application()->unset_timer(m_puserinteraction, nIDEvent);

   //   //return TRUE;

   //   //ASSERT(::is_window((oswindow) get_handle()));
   //   //return ::KillTimer(get_handle(), nIDEvent)  != FALSE;

   //}

   //bool interaction_impl::IsWindowEnabled()
   //{

   //   return m_bEnabled;

   //}


   //bool interaction_impl::EnableWindow(bool bEnable)
   //{

   //   return m_bEnabled = bEnable;

   //}

   ::user::interaction * interaction_impl::GetActiveWindow()
   {

      return ::android::interaction_impl::ui_from_handle(::get_active_window());

   }

   ::user::interaction * interaction_impl::SetActiveWindow()
   {

      return ::android::interaction_impl::ui_from_handle(::set_active_window(get_handle()));

   }


//::user::interaction * interaction_impl::SetCapture(::user::interaction * pinterface)
//{
//
//
//}


   ::user::interaction * PASCAL interaction_impl::GetFocus()
   {

      oswindow w = ::get_focus();

      if (!::is_window(w))
      {

         return nullptr;

      }

      return w->get_user_interaction();

   }


   bool interaction_impl::SetFocus()
   {

      ASSERT(::is_window((oswindow)get_handle()));

      oswindow w = ::set_focus(get_handle());

      if (!::is_window(w))
         return false;

      return w->get_user_interaction();

   }


   bool interaction_impl::has_focus()
   {

      return get_handle() == ::get_focus();

   }


   bool interaction_impl::is_active()
   {

      return get_handle() == ::get_active_window();

   }


   ::user::interaction * PASCAL interaction_impl::get_desktop_window()
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
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      ::CheckDlgButton(get_handle(), nIDButton, nCheck);

   }

   void interaction_impl::CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);

   }

   i32 interaction_impl::DlgDirList(LPTSTR lpPathSpec, i32 nIDListBox, i32 nIDStaticPath, UINT nFileType)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::DlgDirList(get_handle(), lpPathSpec, nIDListBox, nIDStaticPath, nFileType);

   }

   i32 interaction_impl::DlgDirListComboBox(LPTSTR lpPathSpec, i32 nIDComboBox, i32 nIDStaticPath, UINT nFileType)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::DlgDirListComboBox(get_handle(), lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);

   }

   bool interaction_impl::DlgDirSelect(LPTSTR lpString, i32 nSize, i32 nIDListBox)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::DlgDirSelectEx(get_handle(), lpString, nSize, nIDListBox) != FALSE;

   }

   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString, i32 nSize, i32 nIDComboBox)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::DlgDirSelectComboBoxEx(get_handle(), lpString, nSize, nIDComboBox) != FALSE;

   }

   /*
   void interaction_impl::GetDlgItem(id id, oswindow* phWnd) const
   {

   ASSERT(::is_window((oswindow) get_handle()));
   ASSERT(phWnd != nullptr);
   *phWnd = ::GetDlgItem(get_handle(), (i32) id);

   }
   */

   /*
   UINT interaction_impl::GetDlgItemInt(i32 nID, WINBOOL * lpTrans, bool bSigned) const
   {

   ASSERT(::is_window((oswindow) get_handle()));

   return ::GetDlgItemInt(get_handle(), nID, lpTrans, bSigned);

   }
   */

//   i32 interaction_impl::GetDlgItemText(i32 nID, LPTSTR lpStr, i32 nMaxCount) const
//   {
//
//      __throw(not_implemented());
//      ASSERT(::is_window((oswindow) get_handle())); return ::GetDlgItemText(get_handle(), nID, lpStr, nMaxCount);}

   //::user::interaction * interaction_impl::GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious) const
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      return ::android::interaction_impl::from_handle(::GetNextDlgGroupItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));

   //}

   //::user::interaction * interaction_impl::GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious) const
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      return ::android::interaction_impl::from_handle(::GetNextDlgTabItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));

   //}

   UINT interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::IsDlgButtonChecked(get_handle(), nIDButton);

   }

   LPARAM interaction_impl::SendDlgItemMessage(i32 nID, UINT message, WPARAM wparam, LPARAM lparam)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::SendDlgItemMessage(get_handle(), nID, message, wparam, lparam);

   }

   void interaction_impl::SetDlgItemInt(i32 nID, UINT nValue, bool bSigned)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);

   }

   void interaction_impl::SetDlgItemText(i32 nID, const char * lpszString)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      ::SetDlgItemText(get_handle(), nID, lpszString);

   }

   i32 interaction_impl::ScrollWindowEx(i32 dx, i32 dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::draw2d::region * prgnUpdate, LPRECT lpRectUpdate, UINT flags)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::ScrollWindowEx(get_handle(), dx, dy, lpRectScroll, lpRectClip, (HRGN)prgnUpdate->get_handle(), lpRectUpdate, flags);

   }

   void interaction_impl::ShowScrollBar(UINT nBar, bool bShow)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      ::ShowScrollBar(get_handle(), nBar, bShow);

   }

   ::user::interaction * interaction_impl::ChildWindowFromPoint(POINT point)
   {


      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::android::interaction_impl::from_handle(::ChildWindowFromPoint(get_handle(), point));

   }

   ::user::interaction * interaction_impl::ChildWindowFromPoint(POINT point, UINT nFlags)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::android::interaction_impl::from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));

   }






   ::user::interaction * interaction_impl::GetTopWindow() const
   {

      if (m_puserinteraction->m_uiptraChild.get_size() <= 0)
         return nullptr;

      return m_puserinteraction->m_uiptraChild[0];
      //  __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::android::interaction_impl::from_handle(::GetTopWindow(get_handle()));

   }

   //::user::interaction * interaction_impl::GetWindow(UINT nCmd)
   //{

   //   ASSERT(::is_window((oswindow)get_handle()));
   //   //      return ::android::interaction_impl::from_handle(::GetWindow(get_handle(), nCmd));
   //   return nullptr;

   //}

   ::user::interaction * interaction_impl::GetLastActivePopup()
   {


      __throw(todo());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::android::interaction_impl::from_handle(::GetLastActivePopup(get_handle()));

   }


   //::user::interaction * interaction_impl::SetParent(::user::interaction * pWndNewParent)
   //{

   //   ASSERT(::is_window((oswindow)get_handle()));

   //   return ::android::interaction_impl::ui_from_handle(::SetParent(get_handle(), (oswindow)pWndNewParent->get_handle()));

   //}


   //::user::interaction * PASCAL interaction_impl::oswindowFromPoint(POINT point)
   //{


   //   __throw(not_implemented());
   //   //      return ::android::interaction_impl::from_handle(::oswindowFromPoint(point));

   //}

   //bool interaction_impl::FlashWindow(bool bInvert)
   //{


   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      return ::FlashWindow(get_handle(), bInvert) != FALSE;

   //}

   //bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      return ::ChangeClipboardChain(get_handle(), hWndNext) != FALSE;

   //}

   //oswindow interaction_impl::SetClipboardViewer()
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      return ::SetClipboardViewer(get_handle());

   //}

   //bool interaction_impl::OpenClipboard()
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      return ::OpenClipboard(get_handle()) != FALSE;

   //}

   //::user::interaction * PASCAL interaction_impl::GetOpenClipboardWindow()
   //{

   //   __throw(not_implemented());
   //   //      return ::android::interaction_impl::from_handle(::GetOpenClipboardWindow());

   //}

   //::user::interaction * PASCAL interaction_impl::GetClipboardOwner()
   //{

   //   __throw(not_implemented());
   //   //      return ::android::interaction_impl::from_handle(::GetClipboardOwner());

   //}

   //::user::interaction * PASCAL interaction_impl::GetClipboardViewer()
   //{

   //   __throw(not_implemented());
   //   //      return ::android::interaction_impl::from_handle(::GetClipboardViewer());

   //}



   //point PASCAL interaction_impl::GetCaretPos()
   //{

   //   __throw(not_implemented());
   //   //      ::point point;
   //   //      ::GetCaretPos((LPPOINT)&point); return point;

   //}

   //void PASCAL interaction_impl::SetCaretPos(POINT point)
   //{

   //   __throw(not_implemented());
   //   //      ::SetCaretPos(point.x, point.y);

   //}

   //void interaction_impl::HideCaret()
   //{

   //   __throw(not_implemented());
   //   //      ::HideCaret(get_handle());

   //}

   //void interaction_impl::ShowCaret()
   //{

   //   __throw(not_implemented());
   //   //    ::ShowCaret(get_handle());

   //}

   bool interaction_impl::SetForegroundWindow()
   {

      //    __throw(not_implemented());
      //      return ::SetForegroundWindow(get_handle()) != FALSE;

      return false;

   }

   ::user::interaction * PASCAL interaction_impl::GetForegroundWindow()
   {

      return nullptr;

      __throw(not_implemented());
      //      return ::android::interaction_impl::from_handle(::GetForegroundWindow());

   }

   bool interaction_impl::SendNotifyMessage(UINT message, WPARAM wparam, lparam lparam)
   {

      __throw(not_implemented());
      //      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != FALSE;

   }

   //void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      const_cast < interaction_impl * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::android::graphics * >(pgraphics))->get_handle(), dwFlags);

   //}

   //void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const
   //{

   //   __throw(not_implemented());
   //   //      ASSERT(::is_window((oswindow) get_handle()));
   //   //      const_cast < interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::android::graphics * >(pgraphics))->get_handle(), dwFlags);

   //}

   bool interaction_impl::SetWindowContextHelpId(DWORD dwContextHelpId)
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != FALSE;

   }

   DWORD interaction_impl::GetWindowContextHelpId() const
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::GetWindowContextHelpId(get_handle());

   }


// Default message ::collection::map implementations
   //void interaction_impl::OnActivateApp(bool, DWORD)
   //{
   //   Default();
   //}
   //void interaction_impl::OnActivate(UINT, ::user::interaction *, bool)
   //{
   //   Default();
   //}
   //void interaction_impl::OnCancelMode()
   //{
   //   Default();
   //}
   //void interaction_impl::OnChildActivate()
   //{
   //   Default();
   //}
   //void interaction_impl::OnClose()
   //{
   //   Default();
   //}
   //void interaction_impl::OnContextMenu(::user::interaction *, point)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnCopyData(::user::interaction *, COPYDATASTRUCT*)
   //{

   //   return Default() != FALSE;

   //}

   void interaction_impl::OnEnable(bool)
   {
      Default();
   }
   void interaction_impl::OnEndSession(bool)
   {
      Default();
   }

   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   {
      Default();
   }
   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   {
      Default();
   }
   void interaction_impl::OnKillFocus(::user::interaction *)
   {
      Default();
   }
   LRESULT interaction_impl::OnMenuChar(UINT, UINT, ::user::menu*)
   {
      return Default();
   }
   void interaction_impl::OnMenuSelect(UINT, UINT, HMENU)
   {
      Default();
   }
   void interaction_impl::OnMove(i32, i32)
   {
      Default();
   }

   bool interaction_impl::OnQueryEndSession()
   {

      return Default() != FALSE;

   }

   bool interaction_impl::OnQueryNewPalette()
   {

      return Default() != FALSE;

   }

   bool interaction_impl::OnQueryOpen()
   {

      return Default() != FALSE;

   }

   void interaction_impl::_001OnSetCursor(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if (Session.get_cursor() != nullptr
            && Session.get_cursor()->m_ecursor != ::cursor_system)
      {

         __throw(not_implemented());
         //         ::SetCursor(nullptr);
      }
      pbase->set_lresult(1);
      pbase->m_bRet = true;
      //(bool)Default();
   }



   void interaction_impl::_001OnSize(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);

      //size sizeRequest = m_puserinteraction->m_rectParentClientRequest.size();

      //for (auto & pinteraction : m_puserinteraction->m_uiptraChild)
      //{

      //   pinteraction->ResizeWindow(sizeRequest);

      //}



   }



   void interaction_impl::OnShowWindow(bool, UINT)
   {
      Default();
   }
   void interaction_impl::OnSize(UINT, i32, i32)
   {
      Default();
   }
   void interaction_impl::OnTCard(UINT, DWORD)
   {
      Default();
   }
   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
   {
      Default();
   }
   void interaction_impl::OnWindowPosChanged(WINDOWPOS*)
   {
      Default();
   }
   void interaction_impl::OnDropFiles(HDROP)
   {
      Default();
   }
   void interaction_impl::OnPaletteIsChanging(::user::interaction *)
   {
      Default();
   }

   bool interaction_impl::OnNcActivate(bool)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
   {
      Default();
   }

   bool interaction_impl::OnNcCreate(::user::create_struct *)
   {

      return Default() != FALSE;

   }

   LRESULT interaction_impl::OnNcHitTest(point)
   {
      return Default();
   }
   //void interaction_impl::OnNcLButtonDblClk(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcLButtonDown(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcLButtonUp(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMButtonDblClk(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMButtonDown(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMButtonUp(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMouseMove(UINT, point)
   //{
   //   Default();
   //}
   void interaction_impl::OnNcPaint()
   {
      Default();
   }
   //void interaction_impl::OnNcRButtonDblClk(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcRButtonDown(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcRButtonUp(UINT, point)
   //{
   //   Default();
   //}
   void interaction_impl::OnSysChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnSysCommand(UINT, LPARAM)
   {
      Default();
   }
   void interaction_impl::OnSysDeadChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyDown(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyUp(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnCompacting(UINT)
   {
      Default();
   }
   void interaction_impl::OnFontChange()
   {
      Default();
   }
   void interaction_impl::OnPaletteChanged(::user::interaction *)
   {
      Default();
   }
   void interaction_impl::OnSpoolerStatus(UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnTimeChange()
   {
      Default();
   }
   void interaction_impl::OnChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnDeadChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyDown(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyUp(UINT, UINT, UINT)
   {
      Default();
   }
   //void interaction_impl::OnLButtonDblClk(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnLButtonDown(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnLButtonUp(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnMButtonDblClk(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnMButtonDown(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnMButtonUp(UINT, point)
   //{
   //   Default();
   //}
   i32 interaction_impl::OnMouseActivate(::user::interaction *, UINT, UINT)
   {
      return (i32)Default();
   }
   //void interaction_impl::OnMouseMove(UINT, point)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnMouseWheel(UINT, short, point)
   //{

   //   return Default() != FALSE;

   //}

   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
   {
      return Default();
   }
   //void interaction_impl::OnRButtonDblClk(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnRButtonDown(UINT, point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnRButtonUp(UINT, point)
   //{
   //   Default();
   //}
   void interaction_impl::OnTimer(uptr)
   {
      Default();
   }
   void interaction_impl::OnInitMenu(::user::menu*)
   {
      Default();
   }
   void interaction_impl::OnInitMenuPopup(::user::menu*, UINT, bool)
   {
      Default();
   }
   void interaction_impl::OnAskCbFormatName(UINT nMaxCount, LPTSTR pszName)
   {
      (nMaxCount);
      if (nMaxCount>0)
      {
         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
         pszName[0] = '\0';
      }
      Default();
   }
   void interaction_impl::OnChangeCbChain(oswindow, oswindow)
   {
      Default();
   }
   void interaction_impl::OnDestroyClipboard()
   {
      Default();
   }
   void interaction_impl::OnDrawClipboard()
   {
      Default();
   }
   void interaction_impl::OnHScrollClipboard(::user::interaction *, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnPaintClipboard(::user::interaction *, HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnRenderAllFormats()
   {
      Default();
   }
   void interaction_impl::OnRenderFormat(UINT)
   {
      Default();
   }
   void interaction_impl::OnSizeClipboard(::user::interaction *, HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnVScrollClipboard(::user::interaction *, UINT, UINT)
   {
      Default();
   }
   UINT interaction_impl::OnGetDlgCode()
   {
      return (UINT)Default();
   }
   void interaction_impl::OnMDIActivate(bool, ::user::interaction *, ::user::interaction *)
   {
      Default();
   }
   void interaction_impl::OnEnterMenuLoop(bool)
   {
      Default();
   }
   void interaction_impl::OnExitMenuLoop(bool)
   {
      Default();
   }
// Win4 support
//   void interaction_impl::OnStyleChanged(i32, LPSTYLESTRUCT)
//   { Default(); }
//   void interaction_impl::OnStyleChanging(i32, LPSTYLESTRUCT)
//   { Default(); }
   void interaction_impl::OnSizing(UINT, LPRECT)
   {
      Default();
   }
   void interaction_impl::OnMoving(UINT, LPRECT)
   {
      Default();
   }
   void interaction_impl::OnCaptureChanged(::user::interaction *)
   {
      Default();
   }

   bool interaction_impl::OnDeviceChange(UINT, dword_ptr)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnWinIniChange(const char *)
   {
      Default();
   }
   void interaction_impl::OnChangeUIState(UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnUpdateUIState(UINT, UINT)
   {
      Default();
   }

   UINT interaction_impl::OnQueryUIState()
   {

      return (UINT)Default();

   }

// interaction_impl dialog data support
//    void interaction_impl::DoDataExchange(CDataExchange*)
//   { } // default does nothing

// interaction_impl modality support

   void interaction_impl::BeginModalState()
   {

      __throw(todo());

      //::EnableWindow(get_handle(), FALSE);

   }

   void interaction_impl::EndModalState()
   {

      __throw(todo());

      //::EnableWindow(get_handle(), TRUE);

   }

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
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      ::CloseWindow(get_handle());

   }

   bool interaction_impl::OpenIcon()
   {

      __throw(not_implemented());
      //      ASSERT(::is_window((oswindow) get_handle()));
      //      return ::OpenIcon(get_handle()) != FALSE;

   }

//////////////////////////////////////////////////////////////////////////////
//// UI related ::user::interaction_impl functions
//
//   oswindow PASCAL interaction_impl::GetSafeOwner_(oswindow hParent, oswindow* pWndTop)
//   {
//      // get ::user::interaction_impl to start with
//      oswindow hWnd = hParent;
//      if (hWnd == nullptr)
//      {
//         /* trans      __pointer(frame_window) pFrame = channel::GetRoutingFrame_();
//         if (pFrame != nullptr)
//         hWnd = pFrame->get_handle();
//         else
//         hWnd = System.GetMainWnd()->get_handle();*/
//      }
//
//      // a popup ::user::interaction_impl cannot be owned by a child ::user::interaction_impl
//      while (hWnd != nullptr && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
//         hWnd = ::GetParent(hWnd);
//
//      // determine toplevel ::user::interaction_impl to disable as well
//      oswindow hWndTop = hWnd, hWndTemp = hWnd;
//      for (;;)
//      {
//         if (hWndTemp == nullptr)
//            break;
//         else
//            hWndTop = hWndTemp;
//         hWndTemp = ::GetParent(hWndTop);
//      }
//
//      __throw(todo());
//      // get last active popup of first non-child that was found
//      //    if (hParent == nullptr && hWnd != nullptr)
//      //       hWnd = ::GetLastActivePopup(hWnd);
//
//      // disable and store top level parent ::user::interaction_impl if specified
//      if (pWndTop != nullptr)
//      {
//         /*         if (hWndTop != nullptr && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
//         {
//         *pWndTop = hWndTop;
//         ::EnableWindow(hWndTop, FALSE);
//         }
//         else
//         *pWndTop = nullptr;*/
//      }
//
//      return hWnd;    // return the owner as oswindow
//   }

//void interaction_impl::on_delete(::object * pinteraction)
//{
//   UNREFERENCED_PARAMETER(pinteraction);
//}


//
//
//void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
//{
//   SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pmessage);
//   perasebkgnd->m_bRet = true;
//   perasebkgnd->set_result(TRUE);
//}

   void interaction_impl::_001BaseWndInterfaceMap()
   {

      System.window_map().set(get_handle(), this);

   }


   void interaction_impl::_001OnTriggerMouseInside()
   {


      ::user::interaction_impl::_001OnTriggerMouseInside();

   }


} // namespace android



/////////////////////////////////////////////////////////////////////////////
// The WndProc for all interaction_impl's and derived classes











namespace android
{




   void interaction_impl::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {
      // graphics will be already set its view port to the interaction_impl for android - cairo with xlib

      pgraphics->SetViewportOrg(::point());

      /*      rect64 rectWindow;
      get_window_rect(rectWindow);
      get_wnd()->_001ScreenToClient(rectWindow);
      pgraphics->SetViewportOrg(point(rectWindow.top_left()));
      pgraphics->SelectClipRgn(nullptr);
      */

   }


   ::user::interaction * interaction_impl::GetNextWindow(UINT nFlag)
   {

      if (nFlag == GW_HWNDNEXT)
      {

         return get_next(true, nullptr);

      }
      else
      {

         __throw(interface_only_exception());

      }

   }


   ::user::interaction * interaction_impl::get_next(bool bIgnoreChildren, i32 * piLevel)
   {

      return  m_puserinteraction->get_next(bIgnoreChildren, piLevel);

   }


   bool interaction_impl::on_keyboard_focus(::user::primitive * pfocus)
   {

      UNREFERENCED_PARAMETER(pfocus);

      System.oslocal().m_bShowKeyboard = true;

      return true;

   }


   bool interaction_impl::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      output_debug_string("::android::interaction_impl::keyboard_focus_OnKillFocus() (1) \n");

      System.oslocal().m_bHideKeyboard = true;

      return true;

   }

   bool interaction_impl::keyboard_focus_OnChildKillFocus()
   {

      output_debug_string("::android::interaction_impl::keyboard_focus_OnChildKillFocus() (2) \n");

      System.oslocal().m_bHideKeyboard = true;

      return true;

   }


   ::user::interaction_impl * interaction_impl::from_handle(oswindow oswindow)
   {

      return oswindow_interaction_impl(oswindow);

   }


   ::user::interaction * interaction_impl::ui_from_handle(oswindow oswindow)
   {

      return oswindow_interaction(oswindow);

   }

   bool interaction_impl::has_pending_graphical_update()
   {

      sync_lock sl(m_puserinteraction->mutex());

      for (auto p : m_puserinteraction->m_uiptraChild)
      {

         if (p->has_pending_graphical_update())
         {

            return true;

         }

      }


      return false;

   }


   void interaction_impl::edit_on_set_focus(::user::interaction* pinteraction)
   {

      auto puserinteraction = pinteraction->GetParentFrame();

      ::rect rWindowFrame;

      puserinteraction->get_window_rect(rWindowFrame);

      ::rect r1;

      pinteraction->get_window_rect(r1);

      ::size size = m_puserinteraction->get_client_size();

      int iSoftwareKeyboardTop = size.cy / 2;

      if (r1.top > iSoftwareKeyboardTop)
      {

         m_iSoftwareKeyboardScroll = r1.bottom - iSoftwareKeyboardTop;

         puserinteraction->m_pointScroll.y = m_iSoftwareKeyboardScroll;

      }

      puserinteraction->set_need_redraw();

      puserinteraction->post_redraw();

      ::rect r2;

      pinteraction->get_window_rect(r2);

      string strText;

      pinteraction->_001GetText(strText);

      strsize iBeg = 0;

      strsize iEnd = 0;

      pinteraction->_001GetSel(iBeg, iEnd);

      android_edit_on_set_focus(r2.left, r2.top, r2.right, r2.bottom, strText, iBeg, iEnd);

   }


   void interaction_impl::edit_on_kill_focus(::user::interaction* pinteraction)
   {

      auto puserinteraction = pinteraction->GetParentFrame();

      ::rect rWindowFrame;

      puserinteraction->get_window_rect(rWindowFrame);

      if (m_iSoftwareKeyboardScroll > 0)
      {

         puserinteraction->m_pointScroll.y -= m_iSoftwareKeyboardScroll;

         m_iSoftwareKeyboardScroll = 0;

      }

      android_edit_on_kill_focus();

   }
   

   void interaction_impl::show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd)
   {

      if (bShow)
      {

         auto plocal = g_poslocal;

         plocal->m_bShowKeyboard = true;

      }
      else
      {

         auto plocal = g_poslocal;

         plocal->m_bHideKeyboard = true;


      }

   }

} // namespace android



