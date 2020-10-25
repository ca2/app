#include "framework.h"
#include "_.h"
#include "_uwp.h"
#include "aura/platform/mq.h"


using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Microsoft::WRL;
using namespace Windows::Graphics::Display;
using namespace D2D1;

static void __pre_init_dialog(::user::interaction * pWnd,LPRECT lpRectOld,u32* pdwStyleOld);
static void __post_init_dialog(::user::interaction * pWnd,const RECT& rectOld,u32 dwStyleOld);
LRESULT CALLBACK __activation_window_procedure(oswindow hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam);


namespace uwp
{


   interaction_impl::interaction_impl()
   {

      m_bScreenRelativeMouseMessagePosition  = false;
      m_plistener                            = nullptr;
      m_nModalResult                         = 0;
      m_pfont                                = nullptr;
      m_pguieCapture                         = nullptr;
      //m_pwindow                              = new ::user::native_window;

   }


   void interaction_impl::construct(oswindow hWnd)
   {

      m_bScreenRelativeMouseMessagePosition  = false;
      m_plistener = nullptr;
      m_nModalResult = 0;
      // m_bMouseHover = false;
      m_pfont = nullptr;
      m_pguieCapture = nullptr;
      //m_pwindow = nullptr;

   }


   interaction_impl::interaction_impl(::layered * pobjectContext):
      ::object(pobjectContext)
   {

      m_bScreenRelativeMouseMessagePosition  = false;
      m_plistener = nullptr;
      m_nModalResult = 0;
      // m_bMouseHover = false;
      m_pfont = nullptr;
      m_pguieCapture = nullptr;
      //m_pwindow = new ::user::native_window;

   }


      //::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
      //{
      //return dynamic_cast <::user::interaction_impl *>(from_handle((oswindow) pdata));
      //}

      //void * interaction_impl::get_os_data() const
      //{
      ////      return hwnd_handle::get_handle();
      //return oswindow(m_puserinteraction);
      //}

   // Change a interaction_impl's style

   static bool __modify_style(oswindow hWnd,int nStyleOffset,u32 dwRemove,u32 dwAdd,UINT nFlags)
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(hWnd != nullptr);
      u32 uStyle = ::GetWindowLong(hWnd, nStyleOffset);
      u32 dwNewStyle = (uStyle & ~dwRemove) | dwAdd;
      if (uStyle == dwNewStyle)
         return FALSE;

      ::SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
      if (nFlags != 0)
      {
         ::set_window_pos(hWnd, nullptr, 0, 0, 0, 0,
                        SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
      }

#else

      __throw(todo());

#endif

      return TRUE;

   }

   bool interaction_impl::ModifyStyle(oswindow hWnd,u32 dwRemove,u32 dwAdd,UINT nFlags)
   {
      return __modify_style(hWnd,GWL_STYLE,dwRemove,dwAdd,nFlags);
   }

   bool interaction_impl::ModifyStyleEx(oswindow hWnd,u32 dwRemove,u32 dwAdd,UINT nFlags)
   {
      return __modify_style(hWnd,GWL_EXSTYLE,dwRemove,dwAdd,nFlags);
   }


   const MSG* interaction_impl::GetCurrentMessage()
   {

      return nullptr;

   }


   LRESULT interaction_impl::Default()
   {

      return 0;

   }


   void interaction_impl::pre_subclass_window()
   {

   }


   //bool interaction_impl::CreateEx(u32 dwExStyle,const char * lpszClassName,
   //                                const char * lpszWindowName,u32 uStyle,
   //                                const RECT& rect,::user::interaction* puiParent,id id,
   //                                LPVOID lpParam /* = nullptr */)
   //{
   //   return CreateEx(dwExStyle,lpszClassName,lpszWindowName,uStyle,
   //                   rect.left,rect.top,rect.right - rect.left,rect.bottom - rect.top,
   //                   puiParent->get_safe_handle(),id,lpParam);
   //}

   //bool interaction_impl::CreateEx(u32 dwExStyle,const char * lpszClassName,
   //                                const char * lpszWindowName,u32 uStyle,
   //                                int x,int y,int nWidth,int nHeight,
   //                                oswindow hWndParent,id id,LPVOID lpParam)
   //{


   bool interaction_impl::_native_create_window_ex(::user::create_struct& cs)
   {

      __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_task());

      m_puserinteraction->m_pthreadUserInteraction->uiptra().add(m_puserinteraction);

      __refer(m_pthreadUserImpl, m_puserinteraction->m_pthreadUserInteraction);

      //m_strDebug += ::str::demangle(m_puserinteraction->type_name()) + ";";

      if(!m_puserinteraction->pre_create_window(cs))
      {
      
         return false;
         
      }

      m_oswindow = oswindow_get(this);

      set_window_long(GWL_STYLE, cs.style);

      set_window_long(GWL_EXSTYLE, cs.dwExStyle);

      install_message_routing(m_puserinteraction);

      send_message(e_message_create,0,(LPARAM)&cs);

      m_puserinteraction->set_dim(cs.x,cs.cy,cs.cx,cs.cy);

      send_message(e_message_size);

      m_puserinteraction->add_ref(OBJ_REF_DBG_ARGS);

      m_puserinteraction->m_ewindowflag |= ::window_flag_is_window;

      m_puserinteraction->m_ewindowflag |= ::window_flag_window_created;

      return true;

   }


   // for child windows
   bool interaction_impl::pre_create_window(::user::create_struct& cs)
   {

#ifdef WINDOWS_DESKTOP
      if (cs.lpszClass == nullptr)
      {
         // make sure the default interaction_impl class is registered
         VERIFY(__end_defer_register_class(__WND_REG, &cs.lpszClass));

         // no WNDCLASS provided - use child interaction_impl default
         ASSERT(cs.style & WS_CHILD);
      }
#else
      __throw(todo());
#endif
      return TRUE;

   }


   //bool interaction_impl::create_native_window(::user::native_window_initialize * pinitialize)
   //{

   //   throw "trying to remove this create native window, it does anything or do less?";

   //   //m_window = pinitialize->m_window;

   //   //m_pwindow->m_pwindow  = pinitialize->m_pwindow;

   //   //m_oswindow = oswindow_get(this);

   //   //ModifyStyle(0, WS_VISIBLE);

   //   //install_message_routing(this);

   //   //fork([&]()
   //   //{

   //   //   while (::thread_get_run())
   //   //   {

   //   //      {

   //   //         sync_lock sl(&m_mutexQueue);

   //   //         if (m_messageaQueue.has_elements())
   //   //         {

   //   //            __pointer(::message::base) pmessage = m_messageaQueue[0];

   //   //            m_messageaQueue.remove_at(0);

   //   //            if (m_messageaQueue.is_empty())
   //   //            {

   //   //               m_evQueue.ResetEvent();

   //   //            }

   //   //            sl.unlock();

   //   //            m_puserinteraction->message_handler(pmessage);

   //   //         }
   //   //         else
   //   //         {

   //   //            do
   //   //            {

   //   //               sl.unlock();

   //   //               m_evQueue.wait(millis(300));

   //   //               sl.lock();

   //   //            }
   //   //            while (m_messageaQueue.is_empty() && ::thread_get_run());

   //   //         }

   //   //      }

   //   //   }

   //   //});

   //   return true;

   //}


   // bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const char * pszName)
   // {


   //    // uwp todo
   //    return true;

   // }


   interaction_impl::~interaction_impl()
   {

      if(get_context_application() != nullptr)
      {

         Sys(get_context_application()).window_map().m_map.remove_key((oswindow)(iptr)(void *)get_handle());

      }

   }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {
      last_install_message_routing(pchannel);
      //m_pbuffer->InstallMessageHandling(pinterface);
      MESSAGE_LINK(e_message_destroy, pchannel, this,&interaction_impl::_001OnDestroy);
      MESSAGE_LINK(WM_PAINT, pchannel, this,&interaction_impl::_001OnPaint);
      MESSAGE_LINK(WM_PRINT, pchannel, this,&interaction_impl::_001OnPrint);
      if(m_puserinteraction != nullptr)
      {
         m_puserinteraction->install_message_routing(pchannel);
      }
      MESSAGE_LINK(e_message_create, pchannel, this,&interaction_impl::_001OnCreate);
      MESSAGE_LINK(WM_SETCURSOR, pchannel, this,&interaction_impl::_001OnSetCursor);
      MESSAGE_LINK(WM_ERASEBKGND, pchannel, this,&interaction_impl::_001OnEraseBkgnd);
      MESSAGE_LINK(e_message_move, pchannel, this,&interaction_impl::_001OnMove);
      MESSAGE_LINK(e_message_size, pchannel, this,&interaction_impl::_001OnSize);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::_001OnKillFocus);
      //MESSAGE_LINK(WM_SHOWWINDOW, pchannel, this,&interaction_impl::_001OnShowWindow);
//      MESSAGE_LINK(ca2m_PRODEVIAN_SYNCH, pchannel, this,&interaction_impl::_001OnProdevianSynch);
      prio_install_message_routing(pchannel);
   }

   void interaction_impl::_001OnMove(::message::message * pmessage)
   {
   }

   void interaction_impl::_001OnSize(::message::message * pmessage)
   {


   }


   void interaction_impl::_001OnSetFocus(::message::message* pmessage)
   {

      SCAST_PTR(::message::set_focus, psetfocus, pmessage);

      //if (Session.get_focus_ui())
      //{

         m_directxapplication->SetInternalFocus();

      //}

   }


   void interaction_impl::_001OnKillFocus(::message::message* pmessage)
   {

      SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

      m_directxapplication->RemoveInternalFocus();

   }


   void interaction_impl::_001OnDestroy(::message::message * pmessage)
   {
      
      UNREFERENCED_PARAMETER(pmessage);
      
      Default();

   }


   void interaction_impl::PostNcDestroy()
   {

      ::user::interaction_impl::PostNcDestroy();

#ifdef WINDOWS_DESKTOP
      
      WNDPROC pfnWndProc = WNDPROC(GetWindowLongPtr(get_handle(), GWLP_WNDPROC));
      
      Default();

      if (WNDPROC(GetWindowLongPtr(get_handle(), GWLP_WNDPROC)) == pfnWndProc)
      {
         
         WNDPROC pfnSuper = *GetSuperWndProcAddr();
         
         if (pfnSuper != nullptr)
         {

            SetWindowLongPtr(get_handle(), GWLP_WNDPROC, reinterpret_cast<iptr>(pfnSuper));

         }

      }

#else

      __throw(todo());

#endif
      
      ASSERT(get_handle() == nullptr);

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
      if(get_handle() == nullptr)
         return;     // nullptr (unattached) windows are valid

      // check for special wnd??? values
      ASSERT(HWND_TOP == nullptr);       // same as desktop
#ifdef WINDOWS_DESKTOP
      if (get_handle() == HWND_BOTTOM)
      {
      }
      else if (get_handle() == HWND_TOPMOST)
      {
      }
      else if (get_handle() == HWND_NOTOPMOST)
      {
      }
      else
#endif
      {
         // should be a normal interaction_impl
#ifdef WINDOWS_DESKTOP
         ASSERT(::is_window(get_handle()));
#else
         __throw(todo());
#endif

         // should also be in the permanent or temporary handle ::map
         //single_lock sl(afxMutexHwnd(),TRUE);
         //hwnd_map * pMap = afxMapHWND();
         //if(pMap == nullptr) // inside thread not having windows
         //   return; // let go
         //ASSERT(pMap != nullptr);

         //         ::object* p=nullptr;
         /*if(pMap)
         {
         ASSERT( (p = pMap->lookup_permanent(get_handle())) != nullptr ||
         (p = pMap->lookup_temporary(get_handle())) != nullptr);
         }*/

         //ASSERT(dynamic_cast < ::user::interaction_impl * > (p) == this);   // must be us

         // Note: if either of the above asserts fire and you are
         // writing a multithreaded application, it is likely that
         // you have passed a C++ object from one thread to another
         // and have used that object in a way that was not intended.
         // (only simple inline wrapper functions should be used)
         //
         // In general, interaction_impl objects should be passed by oswindow from
         // one thread to another.  The receiving thread can wrap
         // the oswindow with a interaction_impl object by using ::uwp::interaction_impl::from_handle.
         //
         // It is dangerous to pass C++ objects from one thread to
         // another, unless the objects are designed to be used in
         // such a manner.
      }
   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

      dumpcontext << "\nm_hWnd = " << (void *)get_handle();

#ifdef WINDOWS_DESKTOP

      if(get_handle() == nullptr || get_handle() == HWND_BOTTOM || get_handle() == HWND_TOPMOST || get_handle() == HWND_NOTOPMOST)
      {
         // not a normal interaction_impl - nothing more to dump
         return;
      }


      if (!::is_window(get_handle()))
      {
         // not a valid interaction_impl
         dumpcontext << " (illegal oswindow)";
         return; // don't do anything more
      }
#endif

      ::rect rect;
      ((::user::interaction_impl *) this)->m_puserinteraction->get_window_rect(&rect);
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent ::user::interaction_impl * = " << (void *)((::user::interaction_impl *) this)->GetParent();

#ifdef WINDOWS_DESKTOP
      dumpcontext << "\nstyle = " << (void *)(dword_ptr)::GetWindowLong(get_handle(), GWL_STYLE);
      if (::GetWindowLong(get_handle(), GWL_STYLE) & WS_CHILD)
         dumpcontext << "\nid = " << __get_dialog_control_id(get_handle());
#endif
      dumpcontext << "\n";
   }

   bool interaction_impl::DestroyWindow()
   {
      //single_lock sl(m_pthread == nullptr ? nullptr : &m_pthread->m_mutex,TRUE);
      //::user::interaction_impl * pWnd;
      //hwnd_map * pMap;
      //oswindow hWndOrig;
      bool bResult = false;

      if((get_handle() == nullptr))
         return FALSE;

      ShowWindow(SW_HIDE);

      return bResult;

   }


   LRESULT interaction_impl::DefWindowProc(UINT nMsg,WPARAM wParam,lparam lParam)
   {
      return 0;

#ifdef WINDOWS_DESKTOP
      if (m_pfnSuper != nullptr)
         return ::CallWindowProc(m_pfnSuper, get_handle(), nMsg, wParam, lParam);

      WNDPROC pfnWndProc;
      if ((pfnWndProc = *GetSuperWndProcAddr()) == nullptr)
         return ::DefWindowProc(get_handle(), nMsg, wParam, lParam);
      else
         return ::CallWindowProc(pfnWndProc, get_handle(), nMsg, wParam, lParam);
#else
      __throw(todo());
#endif
   }

#ifdef WINDOWS_DESKTOP
   WNDPROC* interaction_impl::GetSuperWndProcAddr()
   {
      // Note: it is no longer necessary to override GetSuperWndProcAddr
      //  for each control class with a different WNDCLASS.
      //  This implementation now uses instance data, such that the previous
      //  WNDPROC can be anything.

      return &m_pfnSuper;
   }
#endif


   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // no default processing
   }


   void interaction_impl::get_window_text(string & rString)
   {


      ::wait(m_window->Dispatcher->RunAsync(
             CoreDispatcherPriority::Normal,
             ref new Windows::UI::Core::DispatchedHandler([this]()
      {

         Windows::UI::ViewManagement::ApplicationView ^ applicationview = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();

         m_strWindowText = applicationview->Title->Begin();

      })));


      rString = m_strWindowText;

   }


#ifdef WINDOWS_DESKTOP

   int interaction_impl::GetDlgItemText(int nID, string & rString) const
   {
      ASSERT(::is_window(get_handle()));
      rString = "";    // is_empty without deallocating

      oswindow hWnd = ::GetDlgItem(get_handle(), nID);
      if (hWnd != nullptr)
      {
         int nLen = ::GetWindowTextLength(hWnd);
         ::GetWindowText(hWnd, rString.get_string_buffer(nLen), nLen+1);
         rString.ReleaseBuffer();
      }

      return (int)rString.get_length();

   }

#endif

#ifdef WINDOWS_DESKTOP
   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      ASSERT(::is_window(get_handle()));
      lpwndpl->length = sizeof(WINDOWPLACEMENT);
      return ::GetWindowPlacement(get_handle(), lpwndpl) != FALSE;
   }

   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      ASSERT(::is_window(get_handle()));
      ((WINDOWPLACEMENT*)lpwndpl)->length = sizeof(WINDOWPLACEMENT);
      return ::SetWindowPlacement(get_handle(), lpwndpl) != FALSE;
   }
   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
   void interaction_impl::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
   {

      // reflect notification to child interaction_impl control
      if (ReflectLastMsg(lpDrawItemStruct->hwndItem))
         return;     // eat it

      // not handled - do default
      Default();
   }

   // Drawing: for all 4 control types
   int interaction_impl::OnCompareItem(int /*nIDCtl*/, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   {
      // reflect notification to child interaction_impl control
      LRESULT lResult;
      if (ReflectLastMsg(lpCompareItemStruct->hwndItem, &lResult))
         return (int)lResult;        // eat it

      // not handled - do default
      return (int)Default();
   }

   void interaction_impl::OnDeleteItem(int /*nIDCtl*/, LPDELETEITEMSTRUCT lpDeleteItemStruct)
   {
      // reflect notification to child interaction_impl control
      if (ReflectLastMsg(lpDeleteItemStruct->hwndItem))
         return;     // eat it
      // not handled - do default
      Default();
   }

#endif


   bool interaction_impl::_EnableToolTips(bool bEnable,UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      return FALSE;
   }




   ::user::interaction_impl * interaction_impl::GetAncestor(UINT gaFlags) const
   {

#ifdef WINDOWS_DESKTOP
      ASSERT(::is_window((oswindow)get_os_data()));
      return  ::uwp::interaction_impl::from_handle(::GetAncestor((oswindow)get_os_data(), gaFlags));
#else
      __throw(todo());
#endif


   }



#ifdef WINDOWS_DESKTOP
   bool interaction_impl::GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const
   {
      ASSERT(::is_window((oswindow)get_os_data()));
      ASSERT(psbi != nullptr);
      return ::GetScrollBarInfo((oswindow)get_os_data(), idObject, psbi) != FALSE;
   }

   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   {
      ASSERT(::is_window((oswindow)get_os_data()));
      ASSERT(pti != nullptr);
      return ::GetTitleBarInfo((oswindow)get_os_data(), pti) != FALSE;
   }
#endif

   bool interaction_impl::AnimateWindow(tick tick,u32 dwFlags)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(::is_window((oswindow)get_os_data()));
      return ::AnimateWindow((oswindow)get_os_data(), tick, dwFlags) != FALSE;
#else
      __throw(todo());
#endif
   }

   bool interaction_impl::FlashWindowEx(u32 dwFlags,UINT  uCount,tick tickTimeout)
   {
      __throw(todo());

      //   ASSERT(::is_window((oswindow)get_os_data()));
      //   FLASHWINFO fwi;
      //   fwi.cbSize = sizeof(fwi);
      //   fwi.hwnd = (oswindow)get_os_data();
      //   fwi.dwFlags = dwFlags;
      //   fwi.uCount = uCount;
      //   fwi.tickTimeout = tickTimeout;

      //   return ::FlashWindowEx(&fwi) != FALSE;
   }



   //bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,u32 dwFlags)
   //{
   //   __throw(todo());
   //   //ASSERT(::is_window((oswindow)get_os_data()));
   //   //return ::SetLayeredWindowAttributes((oswindow)get_os_data(), crKey, bAlpha, dwFlags) != FALSE;
   //}

   //bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT *pptDst,SIZE *psize,
   //      ::draw2d::graphics * pDCSrc,POINT *pptSrc,COLORREF crKey,BLENDFUNCTION *pblend,u32 dwFlags)
   //{
   //   __throw(todo());
   //   //ASSERT(::is_window((oswindow)get_os_data()));
   //   //return ::UpdateLayeredWindow((oswindow)get_os_data(), WIN_HDC(pDCDst), pptDst, psize,
   //   //   WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != FALSE;
   //}


   //bool interaction_impl::GetLayeredWindowAttributes(COLORREF *pcrKey,BYTE *pbAlpha,u32 *pdwFlags) const
   //{
   //   __throw(todo());
   //   //ASSERT(::is_window((oswindow)get_os_data()));
   //   //return ::GetLayeredWindowAttributes((oswindow)get_os_data(), pcrKey, pbAlpha, pdwFlags) != FALSE;
   //}

   bool interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics,UINT nFlags) const
   {
      __throw(todo());
      //ASSERT(::is_window((oswindow)get_os_data()));
      //return ::PrintWindow((oswindow)get_os_data(), (HDC)(dynamic_cast<::uwp::graphics * >(pgraphics))->get_os_data(), nFlags) != FALSE;
   }


   LRESULT interaction_impl::OnNTCtlColor(WPARAM wParam,LPARAM lParam)
   {

      __throw(todo());

   }


   void interaction_impl::PrepareForHelp()
   {
      if(is_frame_window())
      {
         // frame_window windows should be allowed to exit help mode first
         __pointer(::user::frame) pFrameWnd = m_puserinteraction;
         pFrameWnd->ExitHelpMode();
      }

      // cancel any tracking modes
      send_message(WM_CANCELMODE);
      send_message_to_descendants(WM_CANCELMODE,0,0,TRUE,TRUE);

      // need to use top level parent (for the case where get_handle() is in DLL)
      ::user::interaction * pWnd = EnsureTopLevel();
      pWnd->send_message(WM_CANCELMODE);
      pWnd->send_message_to_descendants(WM_CANCELMODE,0,0,TRUE,TRUE);

      __throw(todo());
      // attempt to cancel capture
      //oswindow hWndCapture = ::GetCapture();
      //if (hWndCapture != nullptr)
      //   ::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);
   }

#ifdef WINDOWS_DESKTOP
   void interaction_impl::WinHelpInternal(dword_ptr dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      __throw(not_implemented());
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

#endif

   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      channel::route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }


   void interaction_impl::on_control_event(::user::control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

//      return false;

   }


   void interaction_impl::_002OnDraw(::image * pimage)
   {
      __throw(todo());
      //::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::uwp::graphics * >(pgraphics))->get_os_data()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));

   }


   void interaction_impl::message_handler(::message::base * pbase)
   {

      if (pbase == nullptr)
      {

         return;

      }

      //if(m_puserinteraction != nullptr)
      //{

      //   m_puserinteraction->pre_translate_message(pbase);

      //   if(pbase->m_bRet)
      //   {

      //      return;

      //   }

      //}

      if(m_plistener != nullptr)
      {

         m_plistener->message_queue_message_handler(pbase);

         if(pbase->m_bRet)
         {

            return;

         }

      }


      if(pbase->m_id == WM_KEYDOWN ||
            pbase->m_id == WM_KEYUP ||
            pbase->m_id == WM_CHAR ||
            pbase->m_id == WM_SYSKEYDOWN ||
            pbase->m_id == WM_SYSKEYUP ||
            pbase->m_id == WM_SYSCHAR)
      {

         SCAST_PTR(::message::key, pkey, pbase);

         //Session.keyboard().translate_os_key_message(pkey);

         if(pbase->m_id == WM_KEYDOWN || pbase->m_id == WM_SYSKEYDOWN)
         {
            try
            {
               Session.set_key_pressed(pkey->m_ekey,true);
            }
            catch(...)
            {
            }
         }
         else if(pbase->m_id == WM_KEYUP || pbase->m_id == WM_SYSKEYUP)
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

      if(pbase->m_id == WM_TIMER)
      {
//         m_puserinteraction->get_context_application()->step_timer();
      }
      else if(pbase->m_id == WM_LBUTTONDOWN)
      {
         //g_pwndLastLButtonDown = m_puserinteraction;
      }
      /*      else if(pbase->m_id == CA2M_BERGEDGE)
      {
      if(pbase->m_wparam == BERGEDGE_GETAPP)
      {
      ::aura::application ** ppapp= (::aura::application **) pbase->m_lparam;
      *ppapp = get_context_application();
      pbase->m_bRet = true;
      return;
      }
      }*/
      pbase->set_lresult(0);

      //_000OnMouseLeave(pbase);

      if(pbase->m_id == WM_LBUTTONDOWN ||
            pbase->m_id == WM_LBUTTONUP ||
            pbase->m_id == WM_MBUTTONDOWN ||
            pbase->m_id == WM_MBUTTONUP ||
            pbase->m_id == WM_RBUTTONDOWN ||
            pbase->m_id == WM_RBUTTONUP ||
            pbase->m_id == e_message_mouse_move ||
            pbase->m_id == WM_MOUSEWHEEL)
      {

         message::mouse * pmouse = (::message::mouse *) pbase;

         if (pbase)
         {

            if (pbase->m_id == WM_LBUTTONUP)
            {

               output_debug_string("WM_LBUTTONUP");

            }

         }

         Session.on_ui_mouse_message(pmouse);


         //Application.m_pointCursor = pmouse->m_point;
         //if(get_context_application()->m_pcoreapp->m_psession != nullptr)
         //{
         //   Session.m_pointCursor = pmouse->m_point;
         //}
         //if(m_puserinteraction != nullptr && m_puserinteraction->get_context_application()->m_pcoreapp->m_psession != nullptr && m_puserinteraction->get_context_application()->m_pcoreapp->m_psession != get_context_application()->m_pcoreapp->m_psession)
         //{
         //   Sess(m_puserinteraction->get_context_application()->m_pcoreapp->m_psession).m_pointCursor = pmouse->m_point;
         //}

         //__pointer(base_session) psession;
         //if(get_context_application()->m_pcoreapp->is_system())
         //{
         //   psession = System.query_session(0);
         //   if(psession != nullptr && psession->m_bSessionSynchronizedCursor)
         //   {
         //      psession->m_pointCursor = pmouse->m_point;
         //   }
         //}

         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {
            pmouse->m_bTranslated = true;
            rect rectWindow;
            if(m_bScreenRelativeMouseMessagePosition)
            {
               /*               ::rect rectWindow32;
                              ::get_window_rect(get_handle(), &rectWindow32);
                              ::copy(rectWindow, rectWindow32);*/
            }
            else
            {

               m_puserinteraction->get_window_rect(rectWindow);

            }

            if(get_context_session()->get_monitor_count() > 0)
            {
               
               ::rect rcMonitor;

               get_context_session()->get_monitor_rect(0,&rcMonitor);
               if(rectWindow.left >= rcMonitor.left)
                  pmouse->m_point.x += (LONG)rectWindow.left;
               if(rectWindow.top >= rcMonitor.top)
                  pmouse->m_point.y += (LONG)rectWindow.top;
            }
            else
            {
               if(rectWindow.left >= 0)
                  pmouse->m_point.x += (LONG)rectWindow.left;
               if(rectWindow.top >= 0)
                  pmouse->m_point.y += (LONG)rectWindow.top;
            }
         }

         if(pbase->m_id == e_message_mouse_move)
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
      else if(pbase->m_id == WM_KEYDOWN ||
              pbase->m_id == WM_KEYUP ||
              pbase->m_id == WM_CHAR)
      {

         ::message::key * pkey = (::message::key *) pbase;


         ::user::interaction * puiFocus = dynamic_cast <::user::interaction *> (Session.get_keyboard_focus());
         if(puiFocus != nullptr
               && puiFocus->is_window()
               && puiFocus->GetTopLevel() != nullptr)
         {
            puiFocus->send(pkey);
            if(pbase->m_bRet)
               return;
         }
         else if(!pkey->m_bRet)
         {
            if(m_puserinteraction != nullptr)
            {
               m_puserinteraction->_000OnKey(pkey);
               if(pbase->m_bRet)
                  return;
            }
         }
         pbase->set_lresult(DefWindowProc((UINT) pbase->m_id.i64(),pbase->m_wparam,pbase->m_lparam));
         return;
      }
      if(pbase->m_id == e_message_event)
      {
         if(m_puserinteraction != nullptr)
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

      /*
      if(m_puserinteraction != nullptr)
      {
      m_puserinteraction->_user_message_handler(pmessage);
      if(pmessage->m_bRet)
      return;
      }
      */
      pbase->set_lresult(DefWindowProc((UINT) pbase->m_id.i64(),pbase->m_wparam,pbase->m_lparam));
   }

   /*
   bool interaction_impl::OnWndMsg(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
   {
   LRESULT lResult = 0;
   union MessageMapFunctions mmf;
   mmf.pfn = 0;
   CInternalGlobalLock winMsgLock;
   // special case for commands
   if (message == WM_COMMAND)
   {
   if (OnCommand(wParam, lParam))
   {
   lResult = 1;
   goto LReturnTrue;
   }
   return FALSE;
   }

   // special case for notifies
   if (message == WM_NOTIFY)
   {
   NMHDR* pNMHDR = (NMHDR*)lParam;
   if (pNMHDR->hwndFrom != nullptr && OnNotify(wParam, lParam, &lResult))
   goto LReturnTrue;
   return FALSE;
   }

   // special case for activation
   if (message == e_message_activate)
   __handle_activate(this, wParam, ::uwp::interaction_impl::from_handle((oswindow)lParam));

   // special case for set cursor HTERROR
   if (message == WM_SETCURSOR &&
   __handle_set_cursor(this, (short)LOWORD(lParam), HIWORD(lParam)))
   {
   lResult = 1;
   goto LReturnTrue;
   }

   // special case for windows that contain windowless ActiveX controls
   bool bHandled;

   bHandled = FALSE;

   const __MSGMAP* pMessageMap; pMessageMap = GetMessageMap();
   UINT iHash; iHash = (LOWORD((dword_ptr)pMessageMap) ^ message) & (iHashMax-1);
   winMsgLock.lock(CRIT_WINMSGCACHE);
   __MSG_CACHE* pMsgCache; pMsgCache = &gen_MsgCache[iHash];
   const __MSGMAP_ENTRY* lpEntry;
   if (message == pMsgCache->nMsg && pMessageMap == pMsgCache->pMessageMap)
   {
   // cache hit
   lpEntry = pMsgCache->lpEntry;
   winMsgLock.unlock();
   if (lpEntry == nullptr)
   return FALSE;

   // cache hit, and it needs to be handled
   if (message < 0xC000)
   goto LDispatch;
   else
   goto LDispatchRegistered;
   }
   else
   {
   // not in cache, look for it
   pMsgCache->nMsg = message;
   pMsgCache->pMessageMap = pMessageMap;

   for (/* pMessageMap already init'ed */ /*; pMessageMap->pfnGetBaseMap != nullptr;
pMessageMap = (*pMessageMap->pfnGetBaseMap)())
{
// Note: catch not so common but fatal mistake!!
//       // BEGIN_MESSAGE_MAP(CMyWnd, CMyWnd)
ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
if (message < 0xC000)
{
// constant interaction_impl message
if ((lpEntry = ::ca2::FindMessageEntry(pMessageMap->lpEntries,
message, 0, 0)) != nullptr)
{
pMsgCache->lpEntry = lpEntry;
winMsgLock.unlock();
goto LDispatch;
}
}
else
{
// registered windows message
lpEntry = pMessageMap->lpEntries;
while ((lpEntry = ::ca2::FindMessageEntry(lpEntry, 0xC000, 0, 0)) != nullptr)
{
UINT* pnID = (UINT*)(lpEntry->nSig);
ASSERT(*pnID >= 0xC000 || *pnID == 0);
// must be successfully registered
if (*pnID == message)
{
pMsgCache->lpEntry = lpEntry;
winMsgLock.unlock();
goto LDispatchRegistered;
}
lpEntry++;      // keep looking past this one
}
}
}

pMsgCache->lpEntry = nullptr;
winMsgLock.unlock();
return FALSE;
}

LDispatch:
ASSERT(message < 0xC000);

mmf.pfn = lpEntry->pfn;

switch (lpEntry->nSig)
{
default:
ASSERT(FALSE);
break;
case ::ca2::Sig_l_p:
{
::point point(lParam);
lResult = (this->*mmf.pfn_l_p)(point);
break;
}
case ::ca2::Sig_b_D_v:
lResult = (this->*mmf.pfn_b_D)(::uwp::graphics::from_handle(reinterpret_cast<HDC>(wParam)));
break;

case ::ca2::Sig_b_b_v:
lResult = (this->*mmf.pfn_b_b)(static_cast<bool>(wParam));
break;

case ::ca2::Sig_b_u_v:
lResult = (this->*mmf.pfn_b_u)(static_cast<UINT>(wParam));
break;

case ::ca2::Sig_b_h_v:
lResult = (this->*mmf.pfn_b_h)(reinterpret_cast<HANDLE>(wParam));
break;

case ::ca2::Sig_i_u_v:
lResult = (this->*mmf.pfn_i_u)(static_cast<UINT>(wParam));
break;

case ::ca2::Sig_C_v_v:
lResult = reinterpret_cast<LRESULT>((this->*mmf.pfn_C_v)());
break;

case ::ca2::Sig_v_u_W:
(this->*mmf.pfn_v_u_W)(static_cast<UINT>(wParam),
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(lParam)));
break;

case ::ca2::Sig_u_u_v:
lResult = (this->*mmf.pfn_u_u)(static_cast<UINT>(wParam));
break;

case ::ca2::Sig_b_v_v:
lResult = (this->*mmf.pfn_b_v)();
break;

case ::ca2::Sig_b_W_uu:
lResult = (this->*mmf.pfn_b_W_u_u)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)),
LOWORD(lParam), HIWORD(lParam));
break;

case ::ca2::Sig_b_W_COPYDATASTRUCT:
lResult = (this->*mmf.pfn_b_W_COPYDATASTRUCT)(
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)),
reinterpret_cast<COPYDATASTRUCT*>(lParam));
break;

case ::ca2::Sig_b_v_HELPINFO:
lResult = (this->*mmf.pfn_b_HELPINFO)(reinterpret_cast<LPHELPINFO>(lParam));
break;

case ::ca2::Sig_CTLCOLOR:
{
// special case for OnCtlColor to avoid too many temporary objects
ASSERT(message == WM_CTLCOLOR);
__CTLCOLOR* pCtl = reinterpret_cast<__CTLCOLOR*>(lParam);
::draw2d::graphics_pointer dcTemp;
dcTemp.set_handle1(pCtl->hDC);
interaction_impl wndTemp;
wndTemp.set_handle(pCtl->hWnd);
UINT nCtlType = pCtl->nCtlType;
// if not coming from a permanent interaction_impl, use stack temporary
::user::interaction_impl * pWnd = ::uwp::interaction_impl::FromHandlePermanent(wndTemp.get_handle());
if (pWnd == nullptr)
{
pWnd = &wndTemp;
}
HBRUSH hbr = (this->*mmf.pfn_B_D_W_u)(&dcTemp, pWnd, nCtlType);
// fast detach of temporary objects
dcTemp.set_handle1(nullptr);
wndTemp.set_handle(nullptr);
lResult = reinterpret_cast<LRESULT>(hbr);
}
break;

case ::ca2::Sig_CTLCOLOR_REFLECT:
{
// special case for CtlColor to avoid too many temporary objects
ASSERT(message == WM_REFLECT_BASE+WM_CTLCOLOR);
__CTLCOLOR* pCtl = reinterpret_cast<__CTLCOLOR*>(lParam);
::draw2d::graphics_pointer dcTemp;
dcTemp.set_handle1(pCtl->hDC);
UINT nCtlType = pCtl->nCtlType;
HBRUSH hbr = (this->*mmf.pfn_B_D_u)(&dcTemp, nCtlType);
// fast detach of temporary objects
dcTemp.set_handle1(nullptr);
lResult = reinterpret_cast<LRESULT>(hbr);
}
break;

case ::ca2::Sig_i_u_W_u:
lResult = (this->*mmf.pfn_i_u_W_u)(LOWORD(wParam),
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(lParam)), HIWORD(wParam));
break;

case ::ca2::Sig_i_uu_v:
lResult = (this->*mmf.pfn_i_u_u)(LOWORD(wParam), HIWORD(wParam));
break;

case ::ca2::Sig_i_W_uu:
lResult = (this->*mmf.pfn_i_W_u_u)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)),
LOWORD(lParam), HIWORD(lParam));
break;

case ::ca2::Sig_i_v_s:
lResult = (this->*mmf.pfn_i_s)(reinterpret_cast<LPTSTR>(lParam));
break;

case ::ca2::Sig_l_w_l:
lResult = (this->*mmf.pfn_l_w_l)(wParam, lParam);
break;



case ::ca2::Sig_v_b_h:
(this->*mmf.pfn_v_b_h)(static_cast<bool>(wParam),
reinterpret_cast<HANDLE>(lParam));
break;

case ::ca2::Sig_v_h_v:
(this->*mmf.pfn_v_h)(reinterpret_cast<HANDLE>(wParam));
break;

case ::ca2::Sig_v_h_h:
(this->*mmf.pfn_v_h_h)(reinterpret_cast<HANDLE>(wParam),
reinterpret_cast<HANDLE>(lParam));
break;

case ::ca2::Sig_v_v_v:
(this->*mmf.pfn_v_v)();
break;

case ::ca2::Sig_v_u_v:
(this->*mmf.pfn_v_u)(static_cast<UINT>(wParam));
break;

case ::ca2::Sig_v_u_u:
(this->*mmf.pfn_v_u_u)(static_cast<UINT>(wParam), static_cast<UINT>(lParam));
break;

case ::ca2::Sig_v_uu_v:
(this->*mmf.pfn_v_u_u)(LOWORD(wParam), HIWORD(wParam));
break;

case ::ca2::Sig_v_v_ii:
(this->*mmf.pfn_v_i_i)(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
break;

case ::ca2::Sig_v_u_uu:
(this->*mmf.pfn_v_u_u_u)(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
break;

case ::ca2::Sig_v_u_ii:
(this->*mmf.pfn_v_u_i_i)(static_cast<UINT>(wParam), LOWORD(lParam), HIWORD(lParam));
break;

case ::ca2::Sig_v_w_l:
(this->*mmf.pfn_v_w_l)(wParam, lParam);
break;

case ::ca2::Sig_MDIACTIVATE:
(this->*mmf.pfn_v_b_W_W)(get_handle() == reinterpret_cast<oswindow>(lParam),
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(lParam)),
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)));
break;

case ::ca2::Sig_v_D_v:
(this->*mmf.pfn_v_D)(::uwp::graphics::from_handle(reinterpret_cast<HDC>(wParam)));
break;


case ::ca2::Sig_v_W_v:
(this->*mmf.pfn_v_W)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)));
break;

case ::ca2::Sig_v_v_W:
(this->*mmf.pfn_v_W)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(lParam)));
break;

case ::ca2::Sig_v_W_uu:
(this->*mmf.pfn_v_W_u_u)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)), LOWORD(lParam),
HIWORD(lParam));
break;

case ::ca2::Sig_v_W_p:
{
::point point(lParam);
(this->*mmf.pfn_v_W_p)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)), point);
}
break;

case ::ca2::Sig_v_W_h:
(this->*mmf.pfn_v_W_h)(::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(wParam)),
reinterpret_cast<HANDLE>(lParam));
break;

case ::ca2::Sig_ACTIVATE:
(this->*mmf.pfn_v_u_W_b)(LOWORD(wParam),
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(lParam)), HIWORD(wParam));
break;

case ::ca2::Sig_SCROLL:
case ::ca2::Sig_SCROLL_REFLECT:
{
// special case for WM_VSCROLL and WM_HSCROLL
ASSERT(message == WM_VSCROLL || message == WM_HSCROLL ||
message == WM_VSCROLL+WM_REFLECT_BASE || message == WM_HSCROLL+WM_REFLECT_BASE);
int nScrollCode = (short)LOWORD(wParam);
int nPos = (short)HIWORD(wParam);
if (lpEntry->nSig == ::ca2::Sig_SCROLL)
(this->*mmf.pfn_v_u_u_W)(nScrollCode, nPos,
::uwp::interaction_impl::from_handle(reinterpret_cast<oswindow>(lParam)));
else
(this->*mmf.pfn_v_u_u)(nScrollCode, nPos);
}
break;

case ::ca2::Sig_v_v_s:
(this->*mmf.pfn_v_s)(reinterpret_cast<LPTSTR>(lParam));
break;

case ::ca2::Sig_v_u_cs:
(this->*mmf.pfn_v_u_cs)(static_cast<UINT>(wParam), reinterpret_cast<const char *>(lParam));
break;

case ::ca2::Sig_OWNERDRAW:
(this->*mmf.pfn_v_i_s)(static_cast<int>(wParam), reinterpret_cast<LPTSTR>(lParam));
lResult = TRUE;
break;

case ::ca2::Sig_i_i_s:
lResult = (this->*mmf.pfn_i_i_s)(static_cast<int>(wParam), reinterpret_cast<LPTSTR>(lParam));
break;

case ::ca2::Sig_u_v_p:
{
::point point(lParam);
lResult = (this->*mmf.pfn_u_p)(point);
}
break;

case ::ca2::Sig_u_v_v:
lResult = (this->*mmf.pfn_u_v)();
break;

case ::ca2::Sig_v_b_NCCALCSIZEPARAMS:
(this->*mmf.pfn_v_b_NCCALCSIZEPARAMS)(static_cast<bool>(wParam),
reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam));
break;

case ::ca2::Sig_v_v_WINDOWPOS:
(this->*mmf.pfn_v_v_WINDOWPOS)(reinterpret_cast<WINDOWPOS*>(lParam));
break;

case ::ca2::Sig_v_uu_M:
(this->*mmf.pfn_v_u_u_M)(LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HMENU>(lParam));
break;

case ::ca2::Sig_v_u_p:
{
::point point(lParam);
(this->*mmf.pfn_v_u_p)(static_cast<UINT>(wParam), point);
}
break;

case ::ca2::Sig_SIZING:
(this->*mmf.pfn_v_u_pr)(static_cast<UINT>(wParam), reinterpret_cast<LPRECT>(lParam));
lResult = TRUE;
break;

case ::ca2::Sig_MOUSEWHEEL:
lResult = (this->*mmf.pfn_b_u_s_p)(LOWORD(wParam), (short)HIWORD(wParam),
point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
if (!lResult)
return FALSE;
break;
case ::ca2::Sig_l:
lResult = (this->*mmf.pfn_l_v)();
if (lResult != 0)
return FALSE;
break;
}
goto LReturnTrue;

LDispatchRegistered:    // for registered windows messages
ASSERT(message >= 0xC000);
ASSERT(sizeof(mmf) == sizeof(mmf.pfn));
mmf.pfn = lpEntry->pfn;
lResult = (this->*mmf.pfn_l_w_l)(wParam, lParam);

LReturnTrue:
if (pResult != nullptr)
*pResult = lResult;
return TRUE;
}
*/


   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl command handling


   bool interaction_impl::OnCommand(WPARAM wParam,LPARAM lParam)
   {
      
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);

      return false;

   }


   bool interaction_impl::OnNotify(WPARAM,LPARAM lParam,LRESULT* pResult)
   {
      ASSERT(pResult != nullptr);
      NMHDR* pNMHDR = (NMHDR*)lParam;
      oswindow hWndCtrl = (oswindow)pNMHDR->hwndFrom;

      // get the child ID from the interaction_impl itself
      //      uptr nID = __get_dialog_control_id(hWndCtrl);
      //      int nCode = pNMHDR->code;

      ASSERT(hWndCtrl != nullptr);
      ASSERT(::is_window(hWndCtrl));

      //if(gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
      //   return true;        // locked out - ignore control notification

      // reflect notification to child interaction_impl control
      if(ReflectLastMsg(hWndCtrl,pResult))
         return true;        // eaten by child

      //      __NOTIFY notify;
      //    notify.pResult = pResult;
      //  notify.pNMHDR = pNMHDR;
      //xxx   return _001OnCommand((UINT)nID, MAKELONG(nCode, WM_NOTIFY), &notify, nullptr);
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl extensions

   //::user::frame_window *  interaction_impl::GetParentFrame()
   //{
   //   if(get_handle() == nullptr) // no Window attached
   //   {
   //      return nullptr;
   //   }

   //   ASSERT_VALID(this);

   //   ::user::interaction * puiParent = GetParent();  // start with one parent up
   //   while(puiParent != nullptr)
   //   {
   //      if(puiParent->is_frame_window())
   //      {
   //         return dynamic_cast <::user::frame_window *> (puiParent);
   //      }
   //      puiParent = puiParent->GetParent();
   //   }
   //   return nullptr;
   //}

   ///* trans oswindow CLASS_DECL_AURA __get_parent_owner(::user::interaction * hWnd)
   //{
   //// check for permanent-owned interaction_impl first
   //::user::interaction_impl * pWnd = ::uwp::interaction_impl::FromHandlePermanent(hWnd);
   //if (pWnd != nullptr)
   //return WIN_WINDOW(pWnd)->GetOwner();

   //// otherwise, return parent in the Windows sense
   //return (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) ?
   //::GetParent(hWnd) : ::GetWindow(hWnd, GW_OWNER);
   //}*/


   //::user::interaction *  interaction_impl::GetTopLevel()
   //{
   //   if(get_handle() == nullptr) // no Window attached
   //      return nullptr;

   //   ASSERT_VALID(this);

   //   ::user::interaction * hWndParent = this;
   //   ::user::interaction * hWndT;
   //   while((hWndT = ::user::get_parent_owner(hWndParent)) != nullptr)
   //      hWndParent = hWndT;

   //   return hWndParent;
   //}

   //::user::interaction *  interaction_impl::GetTopLevelOwner()
   //{

   //   __throw(todo());


   //   //if (get_handle() == nullptr) // no Window attached
   //   //   return nullptr;

   //   //ASSERT_VALID(this);

   //   //oswindow hWndOwner = get_handle();
   //   //oswindow hWndT;
   //   //while ((hWndT = ::GetWindow(hWndOwner, GW_OWNER)) != nullptr)
   //   //   hWndOwner = hWndT;

   //   //return ::uwp::interaction_impl::from_handle(hWndOwner);
   //}

   //::user::interaction *  interaction_impl::GetParentOwner()
   //{

   //   __throw(todo());

   //   //if (get_handle() == nullptr) // no Window attached
   //   //   return nullptr;

   //   //ASSERT_VALID(this);

   //   //oswindow hWndParent = get_handle();
   //   //oswindow hWndT;
   //   //while ((::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) &&
   //   //   (hWndT = ::GetParent(hWndParent)) != nullptr)
   //   //{
   //   //   hWndParent = hWndT;
   //   //}

   //   //return ::uwp::interaction_impl::from_handle(hWndParent);
   //}

   //bool interaction_impl::IsTopParentActive()
   //{
   //   ASSERT(get_handle() != nullptr);
   //   ASSERT_VALID(this);

   //   ::user::interaction *pWndTopLevel=EnsureTopLevelParent();

   //   return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
   //}

   void interaction_impl::ActivateTopParent()
   {

      __throw(todo());

      //// special activate logic for floating toolbars and palettes
      //::user::interaction_impl * pActiveWnd = GetForegroundWindow();
      //if (pActiveWnd == nullptr || !(WIN_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(WIN_WINDOW(pActiveWnd)->get_handle(), get_handle())))
      //{
      //   // clicking on floating frame when it does not have
      //   // focus itself -- activate the toplevel frame instead.
      //   EnsureTopLevelParent()->SetForegroundWindow();
      //}
   }

   //::user::frame_window *  interaction_impl::GetTopLevelFrame()
   //{
   //   if(get_handle() == nullptr) // no Window attached
   //      return nullptr;

   //   ASSERT_VALID(this);

   //   ::user::frame_window* pFrameWnd = nullptr;
   //   if(m_puserinteraction != this)
   //      pFrameWnd = dynamic_cast <::user::frame_window *> (m_puserinteraction.m_p);
   //   else
   //      pFrameWnd = dynamic_cast <::user::frame_window *> (this);
   //   if(pFrameWnd == nullptr || !pFrameWnd->is_frame_window())
   //      pFrameWnd = GetParentFrame();

   //   if(pFrameWnd != nullptr)
   //   {
   //      ::user:: frame_window* pTemp;
   //      while((pTemp = pFrameWnd->GetParentFrame()) != nullptr)
   //         pFrameWnd = pTemp;
   //   }
   //   return pFrameWnd;
   //}

   /*   ::user::interaction_impl * interaction_impl::GetSafeOwner(::user::interaction_impl * pParent, oswindow* pWndTop)
      {
      oswindow hWnd = GetSafeOwner_((oswindow) pParent->get_os_data(), pWndTop);
      return ::uwp::interaction_impl::from_handle(hWnd);
      }
      */
   //int interaction_impl::message_box(const char * lpszText,const char * lpszCaption,UINT nType)
   //{
   //   if(lpszCaption == nullptr)
   //      lpszCaption = Application.m_strAppName;
   //   int nResult = ::message_box(get_handle(),lpszText,lpszCaption,nType,callback);
   //   return nResult;
   //}

   int interaction_impl::SetScrollPos(int nBar,int nPos,bool bRedraw)
   {

      __throw(todo());

      //return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
   }

   int interaction_impl::GetScrollPos(int nBar) const
   {

      __throw(todo());

      //return ::GetScrollPos(get_handle(), nBar);
   }

   void interaction_impl::SetScrollRange(int nBar,int nMinPos,int nMaxPos,bool bRedraw)
   {

      __throw(todo());

      //::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
   }

   void interaction_impl::GetScrollRange(int nBar,LPINT lpMinPos,LPINT lpMaxPos) const
   {

      __throw(todo());

      //::GetScrollRange(get_handle(), nBar, lpMinPos, lpMaxPos);
   }

   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(int nBar,bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar,bEnable);
   }

#ifdef WINDOWS_DESKTOP

   bool interaction_impl::SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, bool bRedraw)
   {
      ASSERT(lpScrollInfo != nullptr);

      oswindow hWnd = get_handle();
      lpScrollInfo->cbSize = sizeof(*lpScrollInfo);
      ::SetScrollInfo(hWnd, nBar, lpScrollInfo, bRedraw);
      return true;
   }

   bool interaction_impl::GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, UINT nMask)
   {
      UNREFERENCED_PARAMETER(nMask);
      ASSERT(lpScrollInfo != nullptr);

      oswindow hWnd = get_handle();
      return ::GetScrollInfo(hWnd, nBar, lpScrollInfo) != FALSE;
   }

#endif

   int interaction_impl::GetScrollLimit(int nBar)
   {

#ifdef WINDOWS_DESKTOP

      int nMin, nMax;
      GetScrollRange(nBar, &nMin, &nMax);
      SCROLLINFO info;
      if (GetScrollInfo(nBar, &info, SIF_PAGE))
      {
         nMax -= __max(info.nPage-1,0);
      }
      return nMax;

#endif

      return 0;

   }

   //void interaction_impl::ScrollWindow(int xAmount,int yAmount,const ::rect & rect,LPCRECT lpClipRect)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));

   //   //if (is_window_visible() || lpRect != nullptr || lpClipRect != nullptr)
   //   //{
   //   //   // When visible, let Windows do the scrolling
   //   //   ::ScrollWindow(get_handle(), xAmount, yAmount, lpRect, lpClipRect);
   //   //}
   //   //else
   //   //{
   //   //   // Windows does not perform any scrolling if the interaction_impl is
   //   //   // not visible.  This leaves child windows unscrolled.
   //   //   // To account for this oversight, the child windows are moved
   //   //   // directly instead.
   //   //   oswindow hWndChild = ::GetWindow(get_handle(), GW_CHILD);
   //   //   if (hWndChild != nullptr)
   //   //   {
   //   //      for (; hWndChild != nullptr;
   //   //         hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
   //   //      {
   //   //         ::rect rect;
   //   //         ::get_window_rect(hWndChild, &rect);
   //   //         _001ScreenToClient(&rect);
   //   //         ::set_window_pos(hWndChild, nullptr,
   //   //            rect.left+xAmount, rect.top+yAmount, 0, 0,
   //   //            SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
   //   //      }
   //   //   }
   //   //}

   //}


   void interaction_impl::CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType)
   {

      __throw(todo());

      //u32 dwExStyle = GetExStyle();
      //if (nAdjustType == 0)
      //   dwExStyle &= ~WS_EX_CLIENTEDGE;
      //::AdjustWindowRectEx(lpClientRect, GetStyle(), FALSE, dwExStyle);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(UINT nID,LPARAM lParam)
   {


      __throw(todo());


      //::user::interaction* pParent = GetTopLevel();
      //switch (nID & 0xfff0)
      //{
      //case SC_PREVWINDOW:
      //case SC_NEXTWINDOW:
      //   if (LOWORD(lParam) == VK_F6 && pParent != nullptr)
      //   {
      //      pParent->SetFocus();
      //      return true;
      //   }
      //   break;

      //case SC_CLOSE:
      //case SC_KEYMENU:
      //   // Check lParam.  If it is 0L, then the ::account::user may have done
      //   // an Alt+Tab, so just ignore it.  This breaks the ability to
      //   // just press the Alt-key and have the first menu selected,
      //   // but this is minor compared to what happens in the Alt+Tab
      //   // case.
      //   if ((nID & 0xfff0) == SC_CLOSE || lParam != 0L)
      //   {
      //      if (pParent != nullptr)
      //      {
      //         // Sending the above WM_SYSCOMMAND may destroy the cast,
      //         // so we have to be careful about restoring activation
      //         // and focus after sending it.
      //         oswindow hWndSave = get_handle();
      //         oswindow hWndFocus = ::GetFocus();
      //         pParent->SetActiveWindow();
      //         pParent->send_message(WM_SYSCOMMAND, nID, lParam);

      //         // be very careful here...
      //         if (::is_window(hWndSave))
      //            ::SetActiveWindow(hWndSave);
      //         if (::is_window(hWndFocus))
      //            ::SetFocus(hWndFocus);
      //      }
      //   }
      //   return true;
      //}
      //return false;
   }

   void interaction_impl::WalkPreTranslateTree(::user::interaction * puiStop,::message::message * pmessage)
   {
      ASSERT(puiStop == nullptr || puiStop->is_window());
      ASSERT(pmessage != nullptr);

      SCAST_PTR(::message::base,pbase,pmessage);
      // walk from the target interaction_impl up to the hWndStop interaction_impl checking
      //  if any interaction_impl wants to translate this message

      for(::user::interaction * pinteraction = pbase->userinteraction(); pinteraction != nullptr; pinteraction->GetParent())
      {

         pinteraction->pre_translate_message(pmessage);

         if(pmessage->m_bRet)
            return; // trapped by target interaction_impl (eg: accelerators)

         // got to hWndStop interaction_impl without interest
         if(pinteraction == puiStop)
            break;

      }
      // no special processing
   }


   bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
   {

      return false;

   }


   bool interaction_impl::ReflectLastMsg(oswindow hWndChild,LRESULT* pResult)
   {
      return false;
      //// get the ::map, and if no ::map, then this message does not need reflection
      //single_lock sl(afxMutexHwnd(),TRUE);
      //hwnd_map * pMap = afxMapHWND();
      //if(pMap == nullptr)
      //   return FALSE;

      //// check if in permanent ::map, if it is reflect it (could be OLE control)
      //::user::interaction * pWnd = hWndChild->interaction_impl();
      //if(pWnd == nullptr)
      //{
      //   return false;
      //}

      //// only OLE controls and permanent windows will get reflected msgs
      //ASSERT(pWnd != nullptr);
      //return WIN_WINDOW(pWnd)->SendChildNotifyLastMsg(pResult);
   }

   bool interaction_impl::OnChildNotify(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT* pResult)
   {

      return ReflectChildNotify(uMsg,wParam,lParam,pResult);
   }

   bool interaction_impl::ReflectChildNotify(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(wParam);
      // Note: reflected messages are send directly to interaction_impl::OnWndMsg
      //  and interaction_impl::_001OnCommand for speed and because these messages are not
      //  routed by normal _001OnCommand routing (they are only dispatched)

      switch(uMsg)
      {
      // normal messages (just wParam, lParam through OnWndMsg)
      case WM_HSCROLL:
      case WM_VSCROLL:
      case WM_PARENTNOTIFY:
      case WM_DRAWITEM:
      case WM_MEASUREITEM:
      case WM_DELETEITEM:
      case WM_VKEYTOITEM:
      case WM_CHARTOITEM:
      case WM_COMPAREITEM:
         // reflect the message through the message ::map as WM_REFLECT_BASE+uMsg
         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wParam, lParam, pResult);
         return FALSE;

      // special case for WM_COMMAND
      case WM_COMMAND:
      {
         // reflect the message through the message ::map as OCM_COMMAND
         /* xxx         int nCode = HIWORD(wParam);
         if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_COMMAND), nullptr, nullptr))
         {
         if (pResult != nullptr)
         *pResult = 1;
         return TRUE;
         } */
      }
      break;

      // special case for WM_NOTIFY
      case WM_NOTIFY:
      {
         // reflect the message through the message ::map as OCM_NOTIFY
         NMHDR* pNMHDR = (NMHDR*)lParam;
         //            int nCode = pNMHDR->code;
         //            __NOTIFY notify;
         //          notify.pResult = pResult;
         //        notify.pNMHDR = pNMHDR;
         // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
      }

      // other special cases (WM_CTLCOLOR family)
      default:
         if(uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
         {
            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
            /*__CTLCOLOR ctl;
            ctl.hDC = (HDC)wParam;
            ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
            //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
            ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);

            // reflect the message through the message ::map as OCM_CTLCOLOR
            bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
            if ((HBRUSH)*pResult == nullptr)
            bResult = FALSE;
            return bResult;*/
            return false;
         }
         break;
      }

      return false;   // let the parent handle it
   }

   void interaction_impl::OnParentNotify(const ::id & id,LPARAM lParam)
   {
      if((LOWORD(message) == e_message_create || LOWORD(message) == e_message_destroy))
      {
         if(ReflectLastMsg((oswindow)lParam))
            return;     // eat it
      }
      // not handled - do default
      Default();
   }

   void interaction_impl::OnSetFocus(::user::interaction_impl *)
   {
      bool bHandled;

      bHandled = FALSE;
      if(!bHandled)
      {
         Default();
      }
   }

   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wParam,LPARAM)
   {
      if(LOWORD(wParam) == WA_INACTIVE)
      {
         //         __MODULE_THREAD_STATE* pModuleThreadState = __get_module_thread_state();
      }

      return 0;
   }

   void interaction_impl::OnSysColorChange()
   {
      __throw(not_implemented());

      /*      application* pApp = &System;
      if (pApp != nullptr && pApp->GetMainWnd() == this)
      {
      // recolor global brushes used by control bars
      afxData.UpdateSysColors();
      }

      // forward this message to all other child windows
      if (!(GetStyle() & WS_CHILD))
      send_message_to_descendants(WM_SYSCOLORCHANGE, 0, 0L, TRUE, TRUE);

      Default();*/
   }

   bool gen_GotScrollLines;

   void interaction_impl::OnSettingChange(UINT uFlags,const char * lpszSection)
   {
      UNUSED_ALWAYS(uFlags);
      UNUSED_ALWAYS(lpszSection);

      // force refresh of settings that we cache
      gen_GotScrollLines = FALSE;


      interaction_impl::OnDisplayChange(0,0);    // to update system metrics, etc.
   }

   void interaction_impl::OnDevModeChange(char * lpDeviceName)
   {
      UNREFERENCED_PARAMETER(lpDeviceName);
      __throw(not_implemented());
      /*application* pApp = &System;
      if (pApp != nullptr && pApp->GetMainWnd() == this)
      pApp->DevModeChange(lpDeviceName);

      // forward this message to all other child windows
      if (!(GetStyle() & WS_CHILD))
      {
      const MSG* pMsg = GetCurrentMessage();
      send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam,
      TRUE, TRUE);
      }*/
   }


#ifdef WINDOWS_DESKTOP

   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   {
      if (!(GetStyle() & WS_CHILD))
      {
         ::user::interaction* pMainWnd = System.GetMainWnd();
         if (pMainWnd != nullptr &&
               GetKeyState(VK_SHIFT) >= 0 &&
               GetKeyState(VK_CONTROL) >= 0 &&
               GetKeyState(VK_MENU) >= 0)
         {
            //            pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
            return TRUE;
         }
      }
      return Default() != 0;
   }

#endif

   LRESULT interaction_impl::OnDisplayChange(WPARAM,LPARAM)
   {
      // update metrics if this interaction_impl is the main interaction_impl
      //if(System.GetMainWnd() == this)
      //{
      //   // update any system metrics cache
      //   //         afxData.UpdateSysMetrics();
      //}

      // forward this message to all other child windows
      if(!(GetStyle() & WS_CHILD))
      {
         const MSG* pMsg = GetCurrentMessage();
         send_message_to_descendants(pMsg->message,pMsg->wParam,pMsg->lParam,
                                     TRUE,TRUE);
      }

      return Default();
   }

   LRESULT interaction_impl::OnDragList(WPARAM,LPARAM lParam)
   {

      __throw(todo());

      //LPDRAGLISTINFO lpInfo = (LPDRAGLISTINFO)lParam;
      //ASSERT(lpInfo != nullptr);

      //LRESULT lResult;
      //if (ReflectLastMsg(lpInfo->hWnd, &lResult))
      //   return (int)lResult;    // eat it

      //// not handled - do default
      //return (int)Default();
   }

   void interaction_impl::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      Default();



   }

   //void interaction_impl::OnHScroll(UINT,UINT,CScrollBar* pScrollBar)
   //{
   //   UNREFERENCED_PARAMETER(pScrollBar);
   //   Default();
   //}

   //void interaction_impl::OnVScroll(UINT,UINT,CScrollBar* pScrollBar)
   //{
   //   UNREFERENCED_PARAMETER(pScrollBar);
   //   Default();
   //}

   BOOL CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow hwnd,LPARAM lParam)
   {
      user::oswindow_array * phwnda = (user::oswindow_array *) lParam;
      phwnda->add(hwnd);
      return TRUE;
   }

   //void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   //{

   //   __throw(todo(::get_context_application()));

   //   //      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
   //}

  /*   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
   {
   _001DeferPaintLayeredWindowBackground(pgraphics);
   }*/


   //class print_window:
   //   virtual ::object
   //{
   //public:



   //   manual_reset_event m_event;
   //   oswindow m_hwnd;
   //   HDC m_hdc;

   //   print_window(oswindow hwnd,HDC hdc,tick tickTimeout)
   //   {
   //      m_event.ResetEvent();
   //      m_hwnd = hwnd;
   //      m_hdc = hdc;
   //      begin_thread(&print_window::s_print_window,(LPVOID) this,::priority_above_normal);
   //      if(m_event.wait(millis(tickTimeout)).timeout())
   //      {
   //         TRACE("print_window::time_out");
   //      }
   //   }


   //    ::estatus     c_cdecl print_window(LPVOID pvoid)
   //   {
   //      __throw(todo(::get_context_application()));

   //      //print_window * pprintwindow = (print_window *) pvoid;
   //      //try
   //      //{
   //      //   HANDLE hevent = (HANDLE) pprintwindow->m_event.get_os_data();
   //      //   ::PrintWindow(pprintwindow->m_hwnd, pprintwindow->m_hdc, 0);
   //      //   ::SetEvent(hevent);
   //      //}
   //      //catch(...)
   //      //{
   //      //}
   //      //return 0;
   //   }
   //};

   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

   }

   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //      System.get_event(m_pthread)->SetEvent();
      //    System.get_event(System.get_twf())->wait(millis(8400));
   }

   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {

      //lock lock(m_puserinteraction, 2000);
      __throw(todo());

   }


   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {
      __throw(todo());

      //SCAST_PTR(::message::base, pbase, pmessage);

      //if(pbase->m_wparam == nullptr)
      //   return;

      //::draw2d::graphics_pointer graphics(get_object());
      //METROWIN_DC(graphics.m_p)->Attach((HDC) pbase->m_wparam);
      //::rect rectx;
      //::draw2d::bitmap * pbitmap = &pgraphics->GetCurrentBitmap();
      //::GetCurrentObject((HDC) pbase->m_wparam, OBJ_BITMAP);
      ////      u32 dw = ::get_last_error();
      //::size size = pbitmap->get_size();
      //rectx.left = 0;
      //rectx.top = 0;
      //rectx.right = size.cx;
      //rectx.bottom = size.cy;
      //try
      //{
      //   ::rect rectWindow;
      //   get_window_rect(rectWindow);

      //   ::image_pointer pimage(get_object());
      //   if(!pimage = create_image(rectWindow.bottom_right()))
      //      return;

      //   ::draw2d::graphics_pointer & pgraphics = pimage->get_graphics();

      //   if(pgraphics->get_os_data() == nullptr)
      //      return;

      //   ::rect rectPaint;
      //   ::rect rectUpdate;
      //   rectUpdate = rectWindow;
      //   rectPaint = rectWindow;
      //   rectPaint.offset(-rectPaint.top_left());
      //   (dynamic_cast<::uwp::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //   if(m_puserinteraction != nullptr)
      //   {
      //      m_puserinteraction->_001OnDeferPaintLayeredWindowBackground(pgraphics);
      //   }
      //   else
      //   {
      //      _001OnDeferPaintLayeredWindowBackground(pgraphics);
      //   }
      //   (dynamic_cast<::uwp::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //   (dynamic_cast<::uwp::graphics * >(pgraphics))->SetViewportOrg(::point());
      //   _000OnDraw(pgraphics);
      //   (dynamic_cast<::uwp::graphics * >(pgraphics))->SetViewportOrg(::point());
      //   //(dynamic_cast<::uwp::graphics * >(pgraphics))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //   (dynamic_cast<::uwp::graphics * >(pgraphics))->SelectClipRgn(nullptr);
      //   (dynamic_cast<::uwp::graphics * >(pgraphics))->SetViewportOrg(::point());

      //   pgraphics->SelectClipRgn( nullptr);
      //   pgraphics->BitBlt(rectPaint.left, rectPaint.top,
      //      rectPaint.width(), rectPaint.height(),
      //      pgraphics, rectUpdate.left, rectUpdate.top,
      //      SRCCOPY);

      //   pgraphics->text_out(0, 0, "Te Amo Carlinhos!!", 11);
      //}
      //catch(...)
      //{
      //}
      //pgraphics->FillSolidRect(rectx, RGB(255, 255, 255));
      //METROWIN_DC(graphics.m_p)->Detach();
      //pmessage->m_bRet = true;
      //pbase->set_lresult(0);
   }


   void interaction_impl::OnEnterIdle(UINT /*nWhy*/,::user::interaction_impl * /*pWho*/)
   {

      __throw(todo());


      //// In some OLE inplace active scenarios, OLE will post a
      //// message instead of sending it.  This causes so many WM_ENTERIDLE
      //// messages to be sent that tasks running in the background stop
      //// running.  By dispatching the pending WM_ENTERIDLE messages
      //// when the first one is received, we trick Windows into thinking
      //// that only one was really sent and dispatched.
      //{
      //   MSG msg;
      //   while (PeekMessage(&msg, nullptr, WM_ENTERIDLE, WM_ENTERIDLE, PM_REMOVE))
      //      DispatchMessage(&msg);
      //}

      //Default();
   }

   //HBRUSH interaction_impl::OnCtlColor(::draw2d::graphics *,::user::interaction_impl * pWnd,UINT)
   //{
   //   //ASSERT(pWnd != nullptr && pWnd->get_handle() != nullptr);
   //   //LRESULT lResult;
   //   //if(pWnd->SendChildNotifyLastMsg(&lResult))
   //   //   return (HBRUSH)lResult;     // eat it
   //   //return (HBRUSH)Default();

   //   return nullptr;

   //}

   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any interaction_impl containing controls)
   //  return value of FALSE means caller must call DefWindowProc's default
   //  TRUE means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
   bool interaction_impl::GrayCtlColor(HDC hDC,oswindow hWnd,UINT nCtlColor,HBRUSH hbrGray,COLORREF clrText)
   {

      //if (hDC == nullptr)
      //{
      //   // sometimes Win32 passes a nullptr hDC in the WM_CTLCOLOR message.
      //   //         TRACE(::aura::trace::category_AppMsg, 0, "Warning: hDC is nullptr in interaction_impl::GrayCtlColor; WM_CTLCOLOR not processed.\n");
      //   return FALSE;
      //}

      //if (hbrGray == nullptr ||
      //   nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX ||
      //   nCtlColor == CTLCOLOR_SCROLLBAR)
      //{
      //   return FALSE;
      //}

      //if (nCtlColor == CTLCOLOR_LISTBOX)
      //{
      //   // only handle requests to draw the space between edit and drop button
      //   //  in a drop-down combo (not a drop-down list)
      //   if (!__is_combo_box_control(hWnd, (UINT)CBS_DROPDOWN))
      //      return FALSE;
      //}

      //// set background color and return handle to brush
      //LOGBRUSH logbrush;
      //VERIFY(::GetObject(hbrGray, sizeof(LOGBRUSH), (LPVOID)&logbrush));
      //::SetBkColor(hDC, logbrush.lbColor);
      //if (clrText == (COLORREF)-1)
      //   clrText = ::GetSysColor(COLOR_WINDOWTEXT);  // normal text
      //::SetTextColor(hDC, clrText);
      //return TRUE;


      __throw(todo());


   }


   void interaction_impl::CenterWindow(::user::interaction * pAlternateOwner)
   {

      __throw(todo());

      ////ASSERT(::is_window(get_handle()));

      ////// determine owner interaction_impl to center against
      ////u32 uStyle = GetStyle();
      ////::user::interaction * hWndCenter = pAlternateOwner;
      ////if (pAlternateOwner == nullptr)
      ////{
      ////   if (uStyle & WS_CHILD)
      ////      hWndCenter = GetParent();
      ////   else
      ////      hWndCenter = GetWindow(GW_OWNER);
      ////   if (hWndCenter != nullptr)
      ////   {
      ////      // let parent determine alternate center interaction_impl
      ////      ::user::interaction * hWndTemp =
      ////         (::user::interaction * )hWndCenter->send_message(WM_QUERYCENTERWND, 0, 0);
      ////      if (hWndTemp != nullptr)
      ////         hWndCenter = hWndTemp;
      ////   }
      ////}

      ////// get coordinates of the interaction_impl relative to its parent
      ////rect rcDlg;
      ////get_window_rect(&rcDlg);
      ////rect rcArea;
      ////rect rcCenter;
      ////::user::interaction * hWndParent;
      ////if (!(uStyle & WS_CHILD))
      ////{
      ////   // don't center against invisible or minimized windows
      ////   if (hWndCenter != nullptr)
      ////   {
      ////      u32 dwAlternateStyle = hWndCenter->GetWindowLong(GWL_STYLE);
      ////      if (!(dwAlternateStyle & WS_VISIBLE) || (dwAlternateStyle & WS_MINIMIZE))
      ////         hWndCenter = nullptr;
      ////   }

      ////   MONITORINFO mi;
      ////   mi.cbSize = sizeof(mi);

      ////   // center within appropriate monitor coordinates
      ////   if (hWndCenter == nullptr)
      ////   {
      ////      oswindow hwDefault = System.GetMainWnd()->_get_handle();

      ////      GetMonitorInfo(
      ////         MonitorFromWindow(hwDefault, MONITOR_DEFAULTTOPRIMARY), &mi);
      ////      rcCenter = mi.rcWork;
      ////      rcArea = mi.rcWork;
      ////   }
      ////   else
      ////   {
      ////      hWndCenter->get_window_rect(&rcCenter);
      ////      GetMonitorInfo(
      ////         MonitorFromWindow(hWndCenter->_get_handle(), MONITOR_DEFAULTTONEAREST), &mi);
      ////      rcArea = mi.rcWork;
      ////   }
      ////}
      ////else
      ////{
      ////   // center within parent client coordinates
      ////   hWndParent = GetParent();
      ////   ASSERT(hWndParent->is_window());

      ////   hWndParent->get_client_rect(&rcArea);
      ////   ASSERT(hWndCenter->is_window());
      ////   hWndCenter->get_client_rect(&rcCenter);
      ////   ::MapWindowPoints(hWndCenter->_get_handle(), hWndParent->_get_handle(), (POINT*)&rcCenter, 2);
      ////}

      ////// find dialog's upper left based on rcCenter
      ////int xLeft = (rcCenter.left + rcCenter.right) / 2 - rcDlg.width() / 2;
      ////int yTop = (rcCenter.top + rcCenter.bottom) / 2 - rcDlg.height() / 2;

      ////// if the dialog is outside the screen, move it inside
      ////if (xLeft < rcArea.left)
      ////   xLeft = rcArea.left;
      ////else if (xLeft + rcDlg.width() > rcArea.right)
      ////   xLeft = rcArea.right - rcDlg.width();

      ////if (yTop < rcArea.top)
      ////   yTop = rcArea.top;
      ////else if (yTop + rcDlg.height() > rcArea.bottom)
      ////   yTop = rcArea.bottom - rcDlg.height();

      ////// ::map screen coordinates to child coordinates
      ////set_window_pos(nullptr, xLeft, yTop, -1, -1,
      ////   SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   bool interaction_impl::CheckAutoCenter()
   {
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
   {
      // find resource handle
      LPVOID lpResource = nullptr;
      HGLOBAL hResource = nullptr;
      if(lpszResourceName != nullptr)
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


      __throw(todo());


   }

   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {


      __throw(todo());

   }


   void interaction_impl::UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      //::user::command state(get_object());
      //interaction_impl wndTemp;       // very temporary interaction_impl just for CmdUI update

      // walk all the kids - assume the IDs are for buttons
      /* xxx   for (oswindow hWndChild = ::GetTopWindow(get_handle()); hWndChild != nullptr;
      hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
      {
      // send to buttons
      wndTemp.set_handle(hWndChild); // quick and dirty attach
      state.m_nID = __get_dialog_control_id(hWndChild);
      state.m_pOther = &wndTemp;

      // check for reflect handlers in the child interaction_impl
      ::user::interaction_impl * pWnd = ::uwp::interaction_impl::FromHandlePermanent(hWndChild);
      if (pWnd != nullptr)
      {
      // call it directly to disable any routing
      if (WIN_WINDOW(pWnd)->interaction_impl::_001OnCommand(0, MAKELONG(0xffff,
      WM_COMMAND+WM_REFLECT_BASE), &state, nullptr))
      continue;
      }

      // check for handlers in the parent interaction_impl
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
      // only certain button controls get automagically disabledi
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


//   id interaction_impl::RunModalLoop(u32 dwFlags)
//   {
//
//      // for tracking the idle time state
//      bool bIdle = TRUE;
//      LONG lIdleCount = 0;
////      bool bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
//      bool bShowIdle = !(GetStyle() & WS_VISIBLE);
//      oswindow hWndParent = oswindow_get(GetParent()->m_pimpl.cast < ::user::interaction_impl >());
////      m_puserinteraction->m_iModal = m_puserinteraction->m_iModalCount;
//      //    int iLevel = m_puserinteraction->m_iModal;
//      //prop(string("RunModalLoop.thread(") + __str(iLevel) + ")") = ::get_task();
//      //  m_puserinteraction->m_iModalCount++;
//
//      //m_puserinteraction->m_threadptraModal.add(::get_task());
//      ::aura::application * pappThis1 = dynamic_cast <::aura::application *> (get_context_application());
//      ::aura::application * pappThis2 = dynamic_cast <::aura::application *> (get_context_application());
//      // acquire and dispatch messages until the modal state is done
//      MESSAGE msg;
//      for(;;)
//      {
//
//         if (!ContinueModal())
//         {
//
//            break;
//
//         }
//
//         while(bIdle && ! mq_peek_message(&msg, nullptr, 0, 0, PM_NOREMOVE))
//         {
//
//            if (!ContinueModal())
//            {
//
//               break;
//
//            }
//
//            // show the dialog when the message queue goes idle
//            if(bShowIdle)
//            {
//               ShowWindow(SW_SHOWNORMAL);
//               UpdateWindow();
//               bShowIdle = FALSE;
//            }
//
//            // call on_idle while in bIdle state
//            //if(!(dwFlags & MLF_NOIDLEMSG) && hWndParent != nullptr && lIdleCount == 0)
//            //{
//            //   // send WM_ENTERIDLE to the parent
//            //   // uwp todo               ::SendMessage(hWndParent, WM_ENTERIDLE, MSGF_DIALOGBOX, (LPARAM)get_handle());
//            //}
//            //if((dwFlags & MLF_NOKICKIDLE))
//
//            //   // uwp todo    ||           !__call_window_procedure(this, get_handle(), WM_KICKIDLE, MSGF_DIALOGBOX, lIdleCount++))
//            //{
//            //   // stop idle processing next time
//            //   bIdle = FALSE;
//            //}
//
//            //get_task()->m_dwAlive = get_task()->m_dwAlive = ::get_tick();
//
//            //if(pappThis1 != nullptr)
//            //{
//
//            //   pappThis1->m_dwAlive = get_task()->m_dwAlive;
//
//            //}
//
//            //if(pappThis2 != nullptr)
//            //{
//
//            //   pappThis1->m_dwAlive = get_task()->m_dwAlive;
//
//            //}
//
//         }
//
//
//         // phase2: pump messages while available
//         do
//         {
//
//            if (!ContinueModal())
//            {
//
//               goto ExitModal;
//
//            }
//
//            if(!get_task()->pump_message())
//            {
//
//               __post_quit_message(0);
//
//               return -1;
//
//            }
//
//            // show the interaction_impl when certain special messages rec'd
//            if(bShowIdle &&
//                  (msg.message == 0x118 || msg.message == WM_SYSKEYDOWN))
//            {
//               ShowWindow(SW_SHOWNORMAL);
//               UpdateWindow();
//               bShowIdle = FALSE;
//            }
//
//            if(!ContinueModal())
//               goto ExitModal;
//
//            //// reset "no idle" state after pumping "normal" message
//            //if(__is_idle_message(&msg))
//            //{
//            //   bIdle = TRUE;
//            //   lIdleCount = 0;
//            //}
//
//            //get_task()->m_dwAlive = ::get_tick();
//            //if(pappThis1 != nullptr)
//            //{
//            //   pappThis1->m_dwAlive = get_task()->m_dwAlive;
//            //}
//            //if(pappThis2 != nullptr)
//            //{
//            //   pappThis2->m_dwAlive = get_task()->m_dwAlive;
//            //}
//
//         }
//         while(::mq_peek_message(&msg,nullptr,0,0,PM_NOREMOVE) != FALSE);
//
//         if (!ContinueModal())
//         {
//
//            goto ExitModal;
//
//         }
//
//      }
//
//ExitModal:
//
//      return m_nModalResult;
//
//   }


   bool interaction_impl::ContinueModal()
   {

      return m_puserinteraction->ContinueModal();

   }


   void interaction_impl::EndModalLoop(id nResult)
   {

      __throw(todo());

   }

   //void interaction_impl::EndAllModalLoops(id nResult)
   //{

   //   __throw(todo());

   //   ASSERT(::is_window(get_handle()));

   //    this result will be returned from interaction_impl::RunModalLoop
   //   m_puserinteraction->m_idModalResult = nResult;

   //    make sure a message goes through to exit the modal loop
   //   if(m_puserinteraction->m_iModalCount > 0)
   //   {
   //      int iLevel = m_puserinteraction->m_iModalCount - 1;
   //      m_puserinteraction->m_iModalCount = 0;
   //      m_puserinteraction->kick_queue();
   //      ::get_task()->kick_thread();
   //      for(int i = iLevel; i >= 0; i--)
   //      {
   //         ::thread * pthread = prop(string("RunModalLoop.thread(") + __str(i) + ")").cast < ::thread >();
   //         try
   //         {
   //            pthread->kick_thread();
   //         }
   //         catch(...)
   //         {
   //         }
   //      }
   //   }
   //}


   /////////////////////////////////////////////////////////////////////////////
   // frame_window (here for library granularity)

   bool interaction_impl::is_frame_window()
   {
      return FALSE;
   }
   /////////////////////////////////////////////////////////////////////////////
   // Extra interaction_impl support for dynamic subclassing of controls

   bool interaction_impl::SubclassWindow(oswindow hWnd)
   {

      __throw(todo());

   }
   

   bool interaction_impl::SubclassDlgItem(UINT nID,::user::interaction_impl * pParent)
   {

      __throw(todo());


      //ASSERT(pParent != nullptr);
      //ASSERT(::is_window(WIN_WINDOW(pParent)->get_handle()));

      //// check for normal dialog control first
      //oswindow hWndControl = ::GetDlgItem(WIN_WINDOW(pParent)->get_handle(), nID);
      //if (hWndControl != nullptr)
      //   return SubclassWindow(hWndControl);


      //return FALSE;   // control not found
   }

   oswindow interaction_impl::UnsubclassWindow()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //// set WNDPROC back to original value
      //WNDPROC* lplpfn = GetSuperWndProcAddr();
      //SetWindowLongPtr(get_handle(), GWLP_WNDPROC, (iptr)*lplpfn);
      //*lplpfn = nullptr;

      //// and Detach the oswindow from the interaction_impl object
      //return Detach();
   }


   bool interaction_impl::IsChild(::user::interaction *  pWnd)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //if(WIN_WINDOW(pWnd)->_get_handle() == nullptr)
      //{
      //   return ::user::interaction::IsChild(pWnd);
      //}
      //else
      //{
      //   return ::IsChild(get_handle(), WIN_WINDOW(pWnd)->_get_handle()) != FALSE;
      //}
   }


   oswindow interaction_impl::_get_handle()
   {

      return get_handle();

   }


   //bool interaction_impl::set_window_pos(iptr z,int x,int y,int cx,int cy,UINT nFlags)
   //{
   //   /*bool b;
   //   bool * pb = &b;
   //   if(get_context_application()->m_pcoreapp->s_ptwf != nullptr)
   //   pb = &get_context_application()->m_pcoreapp->s_ptwf->m_bProDevianMode;
   //   keeper < bool > keepOnDemandDraw(pb, false, *pb, true);
   //   */
   //   //ASSERT(::is_window(get_handle()));
   //   ///*   return ::set_window_pos(get_handle(), pWndInsertAfter->get_handle(),
   //   //x, y, cx, cy, nFlags) != FALSE; */
   //   //rect64 rectWindowOld = m_rectParentClient;
   //   if(nFlags & SWP_NOMOVE)
   //   {
   //      if(nFlags & SWP_NOSIZE)
   //      {
   //      }
   //      else
   //      {
   //         m_rectParentClient.right   = m_rectParentClient.left + cx;
   //         m_rectParentClient.bottom  = m_rectParentClient.top + cy;
   //      }
   //   }
   //   else
   //   {
   //      if(nFlags & SWP_NOSIZE)
   //      {
   //         m_rectParentClient.offset(x - m_rectParentClient.left,y - m_rectParentClient.top);
   //      }
   //      else
   //      {
   //         m_rectParentClient.left    = x;
   //         m_rectParentClient.top     = y;
   //         m_rectParentClient.right   = m_rectParentClient.left + cx;
   //         m_rectParentClient.bottom  = m_rectParentClient.top + cy;
   //      }
   //   }
   //   return true;

   //}

   //void interaction_impl::MoveWindow(int x,int y,int nWidth,int nHeight,bool bRepaint)
   //{

   //   ASSERT(::is_window(get_handle()));

   //   set_window_pos(nullptr,x,y,nWidth,nHeight,bRepaint ? SWP_SHOWWINDOW : 0);

   //}


   //bool interaction_impl::_001ClientToScreen(LPRECT lprect)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left   += (LONG)rectWindow.left;
   //   lprect->right  += (LONG)rectWindow.left;
   //   lprect->top    += (LONG)rectWindow.top;
   //   lprect->bottom += (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ClientToScreen(LPPOINT lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x     += (LONG)rectWindow.left;
   //   lppoint->y     += (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ClientToScreen(RECT64 * lprect)
   //{

   //   ::rect rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left   += rectWindow.left;
   //   lprect->right  += rectWindow.left;
   //   lprect->top    += rectWindow.top;
   //   lprect->bottom += rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ClientToScreen(POINT64 * lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x     += rectWindow.left;
   //   lppoint->y     += rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(LPRECT lprect)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left   -= (LONG)rectWindow.left;
   //   lprect->right  -= (LONG)rectWindow.left;
   //   lprect->top    -= (LONG)rectWindow.top;
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

   //   lppoint->x     -= (LONG)rectWindow.left;
   //   lppoint->y     -= (LONG)rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(RECT64 * lprect)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lprect->left   -= rectWindow.left;
   //   lprect->right  -= rectWindow.left;
   //   lprect->top    -= rectWindow.top;
   //   lprect->bottom -= rectWindow.top;

   //   return true;

   //}


   //bool interaction_impl::_001ScreenToClient(POINT64 * lppoint)
   //{

   //   ::rect64 rectWindow;

   //   if(!m_puserinteraction->get_window_rect(rectWindow))
   //   {

   //      return false;

   //   }

   //   lppoint->x     -= rectWindow.left;
   //   lppoint->y     -= rectWindow.top;

   //   return true;

   //}



   //bool interaction_impl::get_window_rect(RECT64 * lprect)
   //{

   //   if(m_pwindow == nullptr)
   //   {

   //      return false;

   //   }

   //   if(m_pwindow->m_pwindow == nullptr)
   //   {

   //      return false;

   //   }

   //   if(!::is_window(get_handle()))
   //   {

   //      return false;

   //   }

   //   Windows::Foundation::Rect rect = m_pwindow->m_pwindow->get_window_rect();


   //   lprect->left   = (i64)rect.X;

   //   lprect->top    = (i64)rect.Y;

   //   lprect->right  = (i64)(lprect->left + rect.Width);

   //   lprect->bottom = (i64)(lprect->top + rect.Height);

   //   /*if(!::is_window(get_handle()))
   //      __throw(::exception::exception("no more a window"));
   //      // if it is temporary interaction_impl - probably not ca2 wrapped interaction_impl
   //      if(m_puserinteraction == nullptr || m_puserinteraction == this)
   //      {
   //      __throw(todo());
   //      //::rect rect32;
   //      //::get_window_rect(get_handle(), rect32);
   //      //::copy(lprect, rect32);

   //      //#endif
   //      }
   //      else
   //      {
   //      interaction::get_window_rect(lprect);
   //      }*/

   //   return true;

   //}


   //bool interaction_impl::get_client_rect(RECT64 * lprect)
   //{

   //   if(!::is_window(get_handle()))
   //   {

   //      return false;

   //   }

   //   get_window_rect(lprect);

   //   lprect->right -= lprect->left;
   //   lprect->left = 0;
   //   lprect->bottom -= lprect->top;
   //   lprect->top = 0;
   //   // if it is temporary interaction_impl - probably not ca2 wrapped interaction_impl
   //   //if(m_puserinteraction == nullptr || m_puserinteraction == this)
   //   {
   //      // __throw(todo());
   //      //::rect rect32;
   //      //::get_client_rect(get_handle(), rect32);
   //      //::copy(lprect, rect32);
   //   }
   //   //else
   //   {
   //      // interaction::get_client_rect(lprect);
   //   }

   //   return true;

   //}


   id interaction_impl::SetDlgCtrlId(id id)
   {
//      m_id = id;
      //    return m_id;
      m_puserinteraction->m_id = id;
      return m_puserinteraction->m_id;
   }

   id interaction_impl::GetDlgCtrlId()
   {
      return m_puserinteraction->m_id;
   }


   void interaction_impl::_001WindowMaximize()
   {

      //::user::interaction::_001WindowMaximize();

   }


   void interaction_impl::_001WindowRestore()
   {

      __throw(todo());

      /*      m_edisplay = display_normal;
            if(m_puserinteraction != nullptr)
            m_puserinteraction->m_edisplay = display_normal;
            ::ShowWindow(get_handle(), SW_RESTORE);*/
   }


   bool interaction_impl::ShowWindow(int nCmdShow)
   {

      return m_puserinteraction->is_window_visible();

   }




   ::user::interaction *  interaction_impl::GetParent()
   {

      __throw(todo());

      //if(!::is_window(get_handle()))
      //   return nullptr;
      //if(get_handle() == nullptr)
      //   return nullptr;
      //return ::uwp::interaction_impl::from_handle(::GetParent(get_handle()));
   }

   LONG interaction_impl::GetWindowLong(int nIndex)
   {

      __throw(todo());

      //return ::GetWindowLong(get_handle(), nIndex);
   }

   LONG interaction_impl::SetWindowLong(int nIndex,LONG lValue)
   {

      __throw(todo());

      //return ::SetWindowLong(get_handle(), nIndex, lValue);
   }


   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const ::user::interaction_impl& wnd) const
   {

      return wnd.get_handle() == get_handle();

   }


   bool interaction_impl::operator!=(const ::user::interaction_impl& wnd) const
   {

      return wnd.get_handle() != get_handle();

   }


   LONG_PTR interaction_impl::get_window_long_ptr(i32 nIndex) const
   {

      return m_mapLong[nIndex];

   }


   LONG_PTR interaction_impl::set_window_long_ptr(i32 nIndex, LONG_PTR lValue)
   {

      return m_mapLong[nIndex] = lValue;

   }


   u32 interaction_impl::GetStyle() const
   {

      return get_window_long_ptr(GWL_STYLE);

   }

   u32 interaction_impl::GetExStyle() const
   {

      return get_window_long_ptr(GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(u32 dwRemove,u32 dwAdd,UINT nFlags)
   {

      set_window_long_ptr(GWL_STYLE, (get_window_long_ptr(GWL_STYLE) | dwAdd) & ~(dwRemove));

      if (nFlags != 0)
      {

         set_need_redraw();

      }

      return true;
   }


   bool interaction_impl::ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags)
   {

      set_window_long_ptr(GWL_EXSTYLE, (get_window_long_ptr(GWL_EXSTYLE) | dwAdd) & ~(dwRemove));

      if (nFlags != 0)
      {

         set_need_redraw();

      }

      return true;
   }

   //void interaction_impl::SetOwner(::user::interaction * pOwnerWnd)
   //{
   //   m_pguieOwner = pOwnerWnd;
   //}

   LRESULT interaction_impl::send_message(const ::id & id,WPARAM wparam,lparam lparam)
   {

      ___pointer < ::message::base > spbase;

      spbase = m_puserinteraction->get_message_base(emessage,wparam,lparam);

      /*      try
            {
            ::user::interaction * pinteraction = m_puserinteraction;
            while(pinteraction != nullptr)
            {
            try
            {
            pinteraction->pre_translate_message(spbase);
            }
            catch(...)
            {
            break;
            }
            if(spbase->m_bRet)
            return spbase->get_lresult();
            try
            {
            pinteraction = pinteraction->GetParent();
            }
            catch(...)
            {
            break;
            }
            }
            }
            catch(...)
            {
            }*/
      message_handler(spbase);
      return spbase->m_lresult;

      //__throw(todo());

      ////ASSERT(::is_window(get_handle()));
      //return ::SendMessage(get_handle(), message, wParam, lParam);
   }


   bool interaction_impl::post_message(const ::id & id,WPARAM wParam,lparam lParam)
   {

//      return ::PostMessageW(get_handle(),message,wParam,lParam) != FALSE;
      //return m_puserinteraction->post_message(message, wParam, lParam);
      return mq_post_message(get_handle(), message, wParam, lParam) != FALSE;

   }


   bool interaction_impl::DragDetect(POINT point) const
   {


      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::DragDetect(get_handle(), point) != FALSE;

   }


   void interaction_impl::set_window_text(const char * lpszString)
   {

      {

         sync_lock sl(m_puserinteraction->mutex());

         m_strWindowText = lpszString;

      }

      m_window->Dispatcher->RunAsync(
      CoreDispatcherPriority::Normal,
      ref new Windows::UI::Core::DispatchedHandler([this]()
      {

         Windows::UI::ViewManagement::ApplicationView ^ applicationview = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();

         {

            sync_lock sl(m_puserinteraction->mutex());

            applicationview->Title = m_strWindowText;

         }

      }));

   }

   //strsize interaction_impl::GetWindowText(LPSTR lpszString,strsize nMaxCount)
   //{
   //   strncpy(lpszString,m_strWindowText,nMaxCount);
   //   return min(nMaxCount,m_strWindowText.get_length());
   //}

   //strsize interaction_impl::get_window_text_length()
   //{

   //   string str;

   //   get_window_text(str);

   //   return str.get_length();

   //   //__throw(todo());

   //   ////ASSERT(::is_window(get_handle()));

   //   ////return ::GetWindowTextLength(get_handle());

   //}

   void interaction_impl::SetFont(::draw2d::font* pfont,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(bRedraw);
      ASSERT(::is_window(get_handle()));
      m_pfont = new ::draw2d::font(*pfont);
   }

   ::draw2d::font* interaction_impl::GetFont()
   {
      ASSERT(::is_window(get_handle()));
      return m_pfont;
   }

   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //::DragAcceptFiles(get_handle(), bAccept);
   }

   //::user::frame_window *  interaction_impl::EnsureParentFrame()
   //{
   //   ::user::frame_window * pFrameWnd=GetParentFrame();
   //   ENSURE_VALID(pFrameWnd);
   //   return pFrameWnd;
   //}

   //::user::interaction *  interaction_impl::EnsureTopLevelParent()
   //{
   //   ::user::interaction *pWnd=GetTopLevel();
   //   ENSURE_VALID(pWnd);
   //   return pWnd;
   //}

   //void interaction_impl::MoveWindow(const ::rect & rect,bool bRepaint)
   //{
   //   MoveWindow(lpRect->left,lpRect->top,lpRect->right - lpRect->left,lpRect->bottom - lpRect->top,bRepaint);
   //}

   UINT interaction_impl::ArrangeIconicWindows()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle())); return ::ArrangeIconicWindows(get_handle());
   }

   //int interaction_impl::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle())); return ::SetWindowRgn(get_handle(), hRgn, bRedraw);
   //}

   //int interaction_impl::GetWindowRgn(HRGN hRgn)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()) && hRgn != nullptr); return ::GetWindowRgn(get_handle(), hRgn);
   //}

   bool interaction_impl::BringWindowToTop()
   {

      __throw(todo());

      //return ::BringWindowToTop(get_handle()) != FALSE;

   }

   void interaction_impl::MapWindowPoints(::user::interaction_impl * pwndTo,LPPOINT lpPoint,UINT nCount)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_os_data(), lpPoint, nCount);
   }

   void interaction_impl::MapWindowPoints(::user::interaction_impl * pwndTo,LPRECT lpRect)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_os_data(), (LPPOINT)lpRect, 2);
   }

   ::draw2d::graphics * interaction_impl::GetDC()
   {

      __throw(todo());

      //::draw2d::graphics_pointer g(get_object());
      //if(get_handle() == nullptr)
      //{
      //   (dynamic_cast < ::uwp::graphics * >(g.m_p))->Attach(::GetDC(nullptr));
      //}
      //else
      //{
      //   (dynamic_cast < ::uwp::graphics * >(g.m_p))->Attach(::GetDC(get_handle()));
      //}
      //return g.detach();
   }

   ::draw2d::graphics * interaction_impl::GetWindowDC()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //::draw2d::graphics_pointer g(get_object());
      //g->attach(::GetWindowDC(get_handle()));
      //return g.detach();
   }

  bool interaction_impl::ReleaseDC(::image * pimage)
   {

      __throw(todo());

      //if(pgraphics == nullptr)
      //   return false;

      //if(((Gdiplus::Graphics *)(dynamic_cast<::uwp::graphics * >(pgraphics))->get_os_data()) == nullptr)
      //   return false;

      //::ReleaseDC(get_handle(), (dynamic_cast<::uwp::graphics * >(pgraphics))->m_hdc);

      //(dynamic_cast<::uwp::graphics * >(pgraphics))->m_hdc = nullptr;

      //pgraphics->release();

      //return true;

   }

   void interaction_impl::UpdateWindow()
   {

      __throw(todo());

      //::UpdateWindow(get_handle());
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
   }

   //bool interaction_impl::GetUpdateRect(LPRECT lpRect,bool bErase)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //return ::GetUpdateRect(get_handle(), lpRect, bErase) != FALSE;
   //}

   //int interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_os_data(), bErase);
   //}

   //void interaction_impl::Invalidate(bool bErase)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //::InvalidateRect(get_handle(), nullptr, bErase);
   //}

   //void interaction_impl::InvalidateRect(const ::rect & rect,bool bErase)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //::InvalidateRect(get_handle(), lpRect, bErase);
   //}

   //void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_os_data(), bErase);
   //}

   //void interaction_impl::ValidateRect(const ::rect & rect)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //
   //   //::ValidateRect(get_handle(), lpRect);

   //}

   //void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //
   //   //::ValidateRgn(get_handle(), (HRGN)pRgn->get_os_data());

   //}

   bool interaction_impl::is_window_visible()
   {

      return true;

      if(!::is_window(get_handle()))
         return false;

      if(m_puserinteraction != nullptr)
      {

         if(!m_puserinteraction->is_this_visible())
            return false;

         if(m_puserinteraction->GetParent() != nullptr && !m_puserinteraction->GetParent()->is_window_visible())
            return false;

      }


      __throw(todo());


      //if(!::IsWindowVisible(get_handle()))
      //   return false;

      return true;

   }


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //::ShowOwnedPopups(get_handle(), bShow);

   }

   //void interaction_impl::send_message_to_descendants(const ::id & id,WPARAM wParam,lparam lParam,bool bDeep,bool bOnlyPerm)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   //interaction_impl::send_message_to_descendants(get_handle(), message, wParam, lParam, bDeep, bOnlyPerm);

   //   // walk through HWNDs to avoid creating temporary interaction_impl objects
   //   // unless we need to call this function recursively
   //   user::interaction * pinteraction = m_puserinteraction->top_child();
   //   while(pinteraction != nullptr)
   //   {
   //      try
   //      {
   //         pinteraction->send_message(message,wParam,lParam);
   //      }
   //      catch(...)
   //      {
   //      }
   //      if(bDeep)
   //      {
   //         // send to child windows after parent
   //         try
   //         {
   //            pinteraction->send_message_to_descendants(message,wParam,lParam,bDeep,bOnlyPerm);
   //         }
   //         catch(...)
   //         {
   //         }
   //      }
   //      try
   //      {
   //         pinteraction = pinteraction->under_sibling();
   //      }
   //      catch(...)
   //      {
   //         break;
   //      }
   //   }
   //}



   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region* prgnClip,u32 flags)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //::draw2d::graphics_pointer g(get_object());
      //g->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_os_data(), flags));
      //return g.detach();

   }

   bool interaction_impl::LockWindowUpdate()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::LockWindowUpdate(get_handle()) != FALSE;

   }

   void interaction_impl::UnlockWindowUpdate()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //::LockWindowUpdate(nullptr);

   }


   bool interaction_impl::RedrawWindow(const ::rect& rectUpdate, ::draw2d::region* prgnUpdate, UINT flags)
   {

      m_puserinteraction->m_bNeedRedraw = true;

      //__throw(todo());

      //if(System.get_twf() == nullptr)
      //   return false;

      //if(System.get_twf()->m_bProDevianMode)
      //   return true;

      //ASSERT(::is_window(get_handle()));

      //return ::set_need_redraw(get_handle(), lpRectUpdate, prgnUpdate == nullptr ? nullptr : (HRGN)prgnUpdate->get_os_data(), flags) != FALSE;

      return true;

   }

#ifdef WINDOWS_DESKTOP

   bool interaction_impl::EnableScrollBar(int nSBFlags, UINT nArrowFlags)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != FALSE;

   }

#endif

   bool interaction_impl::DrawAnimatedRects(int idAni,CONST RECT *lprcFrom,CONST RECT *lprcTo)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::DrawAnimatedRects(get_handle(), idAni, lprcFrom, lprcTo) != FALSE;

   }

   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics,LPCRECT lprc,UINT uFlags)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::uwp::graphics * >(pgraphics))->get_os_data(), lprc, uFlags) != FALSE;

   }

   bool interaction_impl::SetTimer(uptr uEvent,UINT nElapse,PFN_TIMER pfnTimer)
   {


      return ::user::interaction_impl::SetTimer(uEvent,nElapse,pfnTimer);


   }

   bool interaction_impl::KillTimer(uptr uEvent)
   {

      return ::user::interaction_impl::KillTimer(uEvent);

   }

   bool interaction_impl::IsWindowEnabled()
   {

      return true;

      return interaction_impl::IsWindowEnabled();

   }


   bool interaction_impl::EnableWindow(bool bEnable)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::EnableWindow(get_handle(), bEnable) != FALSE;

   }


   ::user::interaction *  interaction_impl::GetActiveWindow()
   {

      oswindow window = ::get_active_window();

      return window == nullptr ? nullptr : oswindow_interaction(window);

   }


   ::user::interaction *  interaction_impl::SetActiveWindow()
   {

      oswindow window = ::set_active_window(get_handle());

      return window == nullptr ? nullptr : oswindow_interaction(window);

   }


   ::user::interaction *  interaction_impl::GetFocus()
   {

      return oswindow_interaction(::get_focus());

   }


   bool interaction_impl::SetFocus()
   {

      ::set_focus(m_puserinteraction->get_handle());

      return true;

   }


   ::user::interaction *  interaction_impl::get_desktop_window()
   {

      return nullptr;

   }


   // Helper for radio buttons
   int interaction_impl::GetCheckedRadioButton(int nIDFirstButton,int nIDLastButton)
   {
      for(int nID = nIDFirstButton; nID <= nIDLastButton; nID++)
      {
         if(IsDlgButtonChecked(nID))
            return nID; // id that matched
      }
      return 0; // invalid ID
   }

   void interaction_impl::CheckDlgButton(int nIDButton,UINT nCheck)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //::CheckDlgButton(get_handle(), nIDButton, nCheck);

   }

   void interaction_impl::CheckRadioButton(int nIDFirstButton,int nIDLastButton,int nIDCheckButton)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);

   }

#ifdef WINDOWS_DESKTOP

   int interaction_impl::DlgDirList(__inout_z LPTSTR lpPathSpec, __in int nIDListBox, __in int nIDStaticPath, __in UINT nFileType)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::DlgDirList(get_handle(), lpPathSpec, nIDListBox, nIDStaticPath, nFileType);

   }

   int interaction_impl::DlgDirListComboBox(__inout_z LPTSTR lpPathSpec, __in int nIDComboBox,  __in int nIDStaticPath, __in UINT nFileType)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::DlgDirListComboBox(get_handle(), lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);

   }

   bool interaction_impl::DlgDirSelect(LPTSTR lpString, int nSize, int nIDListBox)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::DlgDirSelectEx(get_handle(), lpString, nSize, nIDListBox) != FALSE;

   }

   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString, int nSize, int nIDComboBox)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::DlgDirSelectComboBoxEx(get_handle(), lpString, nSize, nIDComboBox) != FALSE;

   }

#endif

   void interaction_impl::GetDlgItem(id id,oswindow* phWnd) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //ASSERT(phWnd != nullptr);
      //*phWnd = ::GetDlgItem(get_handle(), (int) id);

   }

   UINT interaction_impl::GetDlgItemInt(int nID,BOOL * lpTrans,bool bSigned) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::GetDlgItemInt(get_handle(), nID, lpTrans, bSigned);

   }

#ifdef WINDOWS_DESKTOP

   int interaction_impl::GetDlgItemText(__in int nID, __out_ecount_part_z(nMaxCount, return + 1) LPTSTR lpStr, __in int nMaxCount) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::GetDlgItemText(get_handle(), nID, lpStr, nMaxCount);

   }

#endif

   ::user::interaction_impl * interaction_impl::GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //return ::uwp::interaction_impl::from_handle(::GetNextDlgGroupItem(get_handle(), (oswindow) pWndCtl->get_os_data(), bPrevious));
   }

   ::user::interaction_impl * interaction_impl::GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //return ::uwp::interaction_impl::from_handle(::GetNextDlgTabItem(get_handle(), (oswindow) pWndCtl->get_os_data(), bPrevious));
   }

   UINT interaction_impl::IsDlgButtonChecked(int nIDButton) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::IsDlgButtonChecked(get_handle(), nIDButton);

   }
   LPARAM interaction_impl::SendDlgItemMessage(int nID,const ::id & id,WPARAM wParam,LPARAM lParam)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::SendDlgItemMessage(get_handle(), nID, message, wParam, lParam);

   }
   void interaction_impl::SetDlgItemInt(int nID,UINT nValue,bool bSigned)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //::SetDlgItemInt(get_handle(), nID, nValue, bSigned);

   }
   void interaction_impl::SetDlgItemText(int nID,const char * lpszString)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //::SetDlgItemText(get_handle(), nID, lpszString);

   }


   //int interaction_impl::ScrollWindowEx(int dx,int dy,const ::rect & rectScroll,const ::rect & rectClip,::draw2d::region* prgnUpdate,LPRECT lpRectUpdate,UINT flags)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //
   //   //return ::ScrollWindowEx(get_handle(), dx, dy, lpRectScroll, lpRectClip, (HRGN)prgnUpdate->get_os_data(), lpRectUpdate, flags);

   //}


   void interaction_impl::ShowScrollBar(UINT nBar,bool bShow)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //::ShowScrollBar(get_handle(), nBar, bShow);

   }

   ::user::interaction *  interaction_impl::ChildWindowFromPoint(POINT point)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::uwp::interaction_impl::from_handle(::ChildWindowFromPoint(get_handle(), point));

   }

   ::user::interaction *  interaction_impl::ChildWindowFromPoint(POINT point,UINT nFlags)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::uwp::interaction_impl::from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));

   }




   ::user::interaction *  interaction_impl::GetTopWindow()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::uwp::interaction_impl::from_handle(::GetTopWindow(get_handle()));

   }


   ::user::interaction *  interaction_impl::GetWindow(UINT nCmd)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::uwp::interaction_impl::from_handle(::GetWindow(get_handle(), nCmd));

   }

   ::user::interaction *  interaction_impl::GetLastActivePopup()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::uwp::interaction_impl::from_handle(::GetLastActivePopup(get_handle()));

   }

   //::user::interaction *  interaction_impl::set_parent(::user::interaction *  pWndNewParent)
   //{

   //   __throw(todo());

   //   //ASSERT(::is_window(get_handle()));
   //   //return ::uwp::interaction_impl::from_handle(::SetParent(get_handle(), (oswindow) pWndNewParent->get_os_data()));
   //}

   
   __pointer(::user::interaction_impl) interaction_impl::WindowFromPoint(POINT point)
   {

      __throw(todo());

      //return ::uwp::interaction_impl::from_handle(::WindowFromPoint(point));

   }


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::FlashWindow(get_handle(), bInvert) != FALSE;

   }

   bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::ChangeClipboardChain(get_handle(), hWndNext) != FALSE;

   }

   oswindow interaction_impl::SetClipboardViewer()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::SetClipboardViewer(get_handle());

   }

   bool interaction_impl::OpenClipboard()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::OpenClipboard(get_handle()) != FALSE;

   }


   ::user::interaction_impl * interaction_impl::GetOpenClipboardWindow()
   {

      __throw(todo());

      //return ::uwp::interaction_impl::from_handle(::GetOpenClipboardWindow());

   }


   ::user::interaction_impl * interaction_impl::GetClipboardOwner()
   {

      __throw(todo());

      //return ::uwp::interaction_impl::from_handle(::GetClipboardOwner());

   }


   ::user::interaction_impl * interaction_impl::GetClipboardViewer()
   {

      __throw(todo());

   }


   point interaction_impl::GetCaretPos()
   {

      __throw(todo());

   }


   void interaction_impl::SetCaretPos(POINT point)
   {

      __throw(todo());

   }


   void interaction_impl::HideCaret()
   {

      __throw(todo());

      //::HideCaret(get_handle());

   }


   void interaction_impl::ShowCaret()
   {

      __throw(todo());

      //::ShowCaret(get_handle());

   }


   bool interaction_impl::SetForegroundWindow()
   {

      __throw(todo());

      //return ::SetForegroundWindow(get_handle()) != FALSE;

   }


   __pointer(::user::interaction_impl) interaction_impl::GetForegroundWindow()
   {

      __throw(todo());

      //return ::uwp::interaction_impl::from_handle(::GetForegroundWindow());

   }


   bool interaction_impl::SendNotifyMessage(const ::id & id,WPARAM wParam,LPARAM lParam)
   {

      __throw(todo());

      //return ::SendNotifyMessage(get_handle(), message, wParam, lParam) != FALSE;

   }

   // Win4
   HICON interaction_impl::SetIcon(HICON hIcon,bool bBigIcon)
   {

      __throw(todo());

      //return (HICON)send_message(WM_SETICON, bBigIcon, (LPARAM)hIcon);

   }


   HICON interaction_impl::GetIcon(bool bBigIcon) const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return (HICON)const_cast < interaction_impl * > (this)->send_message(WM_GETICON, bBigIcon, 0);

   }


   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const
   {

      ASSERT(::is_window(get_handle()));

      __throw(not_implemented());
      //      const_cast < interaction_impl * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::uwp::graphics * >(pgraphics))->get_os_data(), (LPARAM) dwFlags);

   }


   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const
   {

      ASSERT(::is_window(get_handle()));

      __throw(not_implemented());
      //const_cast < interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::uwp::graphics * >(pgraphics))->get_os_data(), (LPARAM) dwFlags);

   }


   bool interaction_impl::SetWindowContextHelpId(u32 dwContextHelpId)
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != FALSE;

   }


   u32 interaction_impl::GetWindowContextHelpId() const
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));

      //return ::GetWindowContextHelpId(get_handle());

   }


   // Default message ::map implementations
   void interaction_impl::OnActivateApp(bool,u32)
   {
      Default();
   }
   void interaction_impl::OnActivate(UINT,::user::interaction_impl *,bool)
   {
      Default();
   }
   void interaction_impl::OnCancelMode()
   {
      Default();
   }
   void interaction_impl::OnChildActivate()
   {
      Default();
   }
   void interaction_impl::OnClose()
   {
      Default();
   }
   void interaction_impl::OnContextMenu(::user::interaction_impl *,point)
   {
      Default();
   }

#ifdef WINDOWS_DESKTOP

   bool interaction_impl::OnCopyData(::user::interaction_impl *, COPYDATASTRUCT*)
   {

      return Default() != FALSE;

   }

#endif

   void interaction_impl::OnEnable(bool)
   {
      Default();
   }
   void interaction_impl::OnEndSession(bool)
   {
      Default();
   }

   
   //bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   //{

   //   return Default() != FALSE;

   //}


#ifdef WINDOWS_DESKTOP

   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   {
      Default();
   }

#endif

   //void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   //{
   //   Default();
   //}
   void interaction_impl::OnKillFocus(::user::interaction_impl *)
   {
      Default();
   }
   //LRESULT interaction_impl::OnMenuChar(UINT,UINT,::user::menu*)
   //{
   //   return Default();
   //}
   void interaction_impl::OnMenuSelect(UINT,UINT,HMENU)
   {
      Default();
   }
   void interaction_impl::OnMove(int,int)
   {
      Default();
   }
   HCURSOR interaction_impl::OnQueryDragIcon()
   {
      return (HCURSOR)Default();
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

      __throw(todo());

      //SCAST_PTR(::message::base, pbase, pmessage);
      //if(System.get_cursor() != nullptr
      //   && System.get_cursor()->m_ecursor != cursor_system)
      //{
      //   ::SetCursor(nullptr);
      //}
      //pbase->set_lresult(1);
      //pbase->m_bRet = true;
      ////(bool)Default();

   }

   void interaction_impl::OnShowWindow(bool,UINT)
   {
      Default();
   }
   void interaction_impl::OnSize(UINT,int,int)
   {
      Default();
   }
   void interaction_impl::OnTCard(UINT,u32)
   {
      Default();
   }

#ifdef WINDOWS_DESKTOP

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

#endif

   void interaction_impl::OnPaletteIsChanging(::user::interaction_impl *)
   {
      Default();
   }

   bool interaction_impl::OnNcActivate(bool)
   {

      return Default() != FALSE;

   }


#ifdef WINDOWS_DESKTOP

   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
   {
      Default();
   }

#endif

   bool interaction_impl::OnNcCreate(LPCREATESTRUCT)
   {

      return Default() != FALSE;

   }


   LRESULT interaction_impl::OnNcHitTest(point)
   {

      return Default();

   }


   //void interaction_impl::OnNcLButtonDblClk(UINT,point)
   //{

   //   Default();

   //}


   //void interaction_impl::OnNcLButtonDown(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcLButtonUp(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMButtonDblClk(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMButtonDown(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMButtonUp(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcMouseMove(UINT,point)
   //{
   //   Default();
   //}
   void interaction_impl::OnNcPaint()
   {
      Default();
   }
   //void interaction_impl::OnNcRButtonDblClk(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcRButtonDown(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnNcRButtonUp(UINT,point)
   //{
   //   Default();
   //}
   void interaction_impl::OnSysChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnSysCommand(UINT,LPARAM)
   {
      Default();
   }
   void interaction_impl::OnSysDeadChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyDown(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyUp(UINT,UINT,UINT)
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
   void interaction_impl::OnPaletteChanged(::user::interaction_impl *)
   {
      Default();
   }
   void interaction_impl::OnSpoolerStatus(UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnTimeChange()
   {
      Default();
   }
   void interaction_impl::OnChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnDeadChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyDown(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyUp(UINT,UINT,UINT)
   {
      Default();
   }
   //void interaction_impl::OnLButtonDblClk(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnLButtonDown(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnLButtonUp(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnMButtonDblClk(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnMButtonDown(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnMButtonUp(UINT,point)
   //{
   //   Default();
   //}
   int interaction_impl::OnMouseActivate(::user::interaction_impl *,UINT,UINT)
   {
      return (int)Default();
   }
   //void interaction_impl::OnMouseMove(UINT,point)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnMouseWheel(UINT,short,point)
   //{

   //   return Default() != FALSE;

   //}

   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM,LPARAM)
   {
      return Default();
   }
   //void interaction_impl::OnRButtonDblClk(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnRButtonDown(UINT,point)
   //{
   //   Default();
   //}
   //void interaction_impl::OnRButtonUp(UINT,point)
   //{
   //   Default();
   //}
   void interaction_impl::OnTimer(uptr)
   {
      Default();
   }
   //void interaction_impl::OnInitMenu(::user::menu*)
   //{
   //   Default();
   //}
   //void interaction_impl::OnInitMenuPopup(::user::menu*,UINT,bool)
   //{
   //   Default();
   //}

#ifdef WINDOWS_DESKTOP

   void interaction_impl::OnAskCbFormatName(__in UINT nMaxCount, __out_ecount_z(nMaxCount) LPTSTR pszName)
   {
      (nMaxCount);
      if(nMaxCount>0)
      {
         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
         pszName[0]='\0';
      }
      Default();
   }

#endif

   void interaction_impl::OnChangeCbChain(oswindow,oswindow)
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
   void interaction_impl::OnHScrollClipboard(::user::interaction_impl *,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnPaintClipboard(::user::interaction_impl *,HGLOBAL)
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
   void interaction_impl::OnSizeClipboard(::user::interaction_impl *,HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnVScrollClipboard(::user::interaction_impl *,UINT,UINT)
   {
      Default();
   }
   UINT interaction_impl::OnGetDlgCode()
   {
      return (UINT)Default();
   }
   void interaction_impl::OnMDIActivate(bool,::user::interaction_impl *,::user::interaction_impl *)
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

#ifdef WINDOWS_DESKTOP

   void interaction_impl::OnStyleChanged(int, LPSTYLESTRUCT)
   {
      Default();
   }
   void interaction_impl::OnStyleChanging(int, LPSTYLESTRUCT)
   {
      Default();
   }

#endif

   void interaction_impl::OnSizing(UINT,LPRECT)
   {
      Default();
   }
   void interaction_impl::OnMoving(UINT,LPRECT)
   {
      Default();
   }
   void interaction_impl::OnCaptureChanged(::user::interaction_impl *)
   {
      Default();
   }

   bool interaction_impl::OnDeviceChange(UINT,dword_ptr)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnWinIniChange(const char *)
   {
      Default();
   }
   void interaction_impl::OnChangeUIState(UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnUpdateUIState(UINT,UINT)
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

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //::CloseWindow(get_handle());

   }

   bool interaction_impl::OpenIcon()
   {

      __throw(todo());

      //ASSERT(::is_window(get_handle()));
      //
      //return ::OpenIcon(get_handle()) != FALSE;

   }

   ////////////////////////////////////////////////////////////////////////////
   // UI related ::user::interaction_impl functions

   oswindow interaction_impl::GetSafeOwner_(oswindow hParent,oswindow* pWndTop)
   {

      __throw(todo());

      //// get ::user::interaction_impl to start with
      //oswindow hWnd = hParent;
      //if (hWnd == nullptr)
      //{
      //   /* trans      frame_window* pFrame = channel::GetRoutingFrame_();
      //   if (pFrame != nullptr)
      //   hWnd = pFrame->get_handle();
      //   else
      //   hWnd = System.GetMainWnd()->get_handle();*/
      //}

      //// a popup ::user::interaction_impl cannot be owned by a child ::user::interaction_impl
      //while (hWnd != nullptr && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
      //   hWnd = ::GetParent(hWnd);

      //// determine toplevel ::user::interaction_impl to disable as well
      //oswindow hWndTop = hWnd, hWndTemp = hWnd;
      //for (;;)
      //{
      //   if (hWndTemp == nullptr)
      //      break;
      //   else
      //      hWndTop = hWndTemp;
      //   hWndTemp = ::GetParent(hWndTop);
      //}

      //// get last active popup of first non-child that was found
      //if (hParent == nullptr && hWnd != nullptr)
      //   hWnd = ::GetLastActivePopup(hWnd);

      //// disable and store top level parent ::user::interaction_impl if specified
      //if (pWndTop != nullptr)
      //{
      //   if (hWndTop != nullptr && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
      //   {
      //      *pWndTop = hWndTop;
      //      ::EnableWindow(hWndTop, FALSE);
      //   }
      //   else
      //      *pWndTop = nullptr;
      //}

      //return hWnd;    // return the owner as oswindow
   }


   /////////////////////////////////////////////////////////////////////////////
   // Official way to send message to a interaction_impl

#ifdef WINDOWS_DESKTOP

   CLASS_DECL_AURA LRESULT __call_window_procedure(::user::interaction * pinteraction, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
   {


      // Catch exceptions thrown outside the scope of a callback
      // in debug builds and warn the ::account::user.
      pointer < ::message::base > spbase;

      spbase(pinteraction->get_base(pinteraction, nMsg, wParam, lParam));

      __trace_message("WndProc", spbase);

      try
      {

         // special case for WM_INITDIALOG
         ::rect rectOld;
         u32 uStyle = 0;
         if (nMsg == WM_INITDIALOG)
            __pre_init_dialog(pinteraction, &rectOld, &uStyle);

         if(pinteraction->m_puserinteraction != nullptr && pinteraction->m_puserinteraction != pinteraction)
         {
            pinteraction->m_puserinteraction->message_handler(spbase);
         }
         else
         {
            pinteraction->message_handler(spbase);
         }
         // more special case for WM_INITDIALOG
         if (nMsg == WM_INITDIALOG)
            __post_init_dialog(pinteraction, rectOld, uStyle);
      }
      catch(const ::exception_pointer pe)
      {
         try
         {
            if(App(pinteraction->get_context_application()).on_run_exception((::exception::exception &) e))
               goto run;
         }
         catch(...)
         {
         }
         return -1;
      }
      catch(::exception::aura * pe)
      {
         __process_window_procedure_exception(pe, spbase);
         //         TRACE(::aura::trace::category_AppMsg, 0, "Warning: Uncaught exception in message_handler (returning %ld).\n", spbase->get_lresult());
         ::exception_pointer esp(pe);
      }
      catch(...)
      {
      }
run:
      try
      {
         pThreadState->m_lastSentMsg = oldState;
         LRESULT lresult = spbase->get_lresult();
         return lresult;
      }
      catch(...)
      {
         return 0;
      }
   }

#endif


   /*CDataExchange::CDataExchange(::user::interaction_impl * pDlgWnd, bool bSaveAndValidate)
   {
   ASSERT_VALID(pDlgWnd);
   m_bSaveAndValidate = bSaveAndValidate;
   m_pDlgWnd = pDlgWnd;
   m_idLastControl = 0;
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // Window creation hooks


#ifdef WINDOWS_DESKTOP

   LRESULT CALLBACK __cbt_filter_hook(int code, WPARAM wParam, LPARAM lParam)
   {
      if (code != HCBT_CREATEWND)
      {
         // wait for HCBT_CREATEWND just pass others on...
         return CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code,
                               wParam, lParam);
      }

      ASSERT(lParam != nullptr);
      LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
      ASSERT(lpcs != nullptr);

      ::user::interaction * pWndInit = pThreadState->m_pWndInit;
      bool bContextIsDLL = afxContextIsDLL;
      if (pWndInit != nullptr || (!(lpcs->style & WS_CHILD) && !bContextIsDLL))
      {
         // Note: special check to avoid subclassing the IME interaction_impl
         //if (gen_DBCS)
         {
            // check for cheap CS_IME style first...
            if (GetClassLong((oswindow)wParam, GCL_STYLE) & CS_IME)
               goto lCallNextHook;

            // get class name of the interaction_impl that is being created
            const char * pszClassName;
            char szClassName[_countof("ime")+1];
            if (dword_ptr(lpcs->lpszClass) > 0xffff)
            {
               pszClassName = lpcs->lpszClass;
            }
            else
            {
               szClassName[0] = '\0';
               GlobalGetAtomName((ATOM)lpcs->lpszClass, szClassName, _countof(szClassName));
               pszClassName = szClassName;
            }

            // a little more expensive to test this way, but necessary...
            if (::__invariant_stricmp(pszClassName, "ime") == 0)
               goto lCallNextHook;
         }

         ASSERT(wParam != nullptr); // should be non-nullptr oswindow
         oswindow hWnd = (oswindow)wParam;
         WNDPROC oldWndProc;
         if (pWndInit != nullptr)
         {
            // the interaction_impl should not be in the permanent ::map at this time
            ASSERT(::uwp::interaction_impl::FromHandlePermanent(hWnd) == nullptr);

            pWndInit->m_pthread = dynamic_cast < ::thread * > (::uwp::get_task());
            pWndInit->m_pthread->add(pWndInit);
            pWndInit->m_puserinteraction->m_pthread = pWndInit->m_pthread;
            pWndInit->m_puserinteraction->m_pthread->add(pWndInit->m_puserinteraction);
            pWndInit->m_puserinteraction->m_pimpl = pWndInit;

            // connect the oswindow to pWndInit...
            pWndInit->Attach(hWnd);
            // allow other subclassing to occur first
            pWndInit->pre_subclass_window();

            WNDPROC *pOldWndProc = pWndInit->GetSuperWndProcAddr();
            ASSERT(pOldWndProc != nullptr);

            // subclass the interaction_impl with standard __window_procedure
            WNDPROC afxWndProc = __get_window_procedure();
            oldWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC,
                                                   (dword_ptr)afxWndProc);
            ASSERT(oldWndProc != nullptr);
            if (oldWndProc != afxWndProc)
               *pOldWndProc = oldWndProc;

            pThreadState->m_pWndInit = nullptr;
         }
         else
         {
            ASSERT(!bContextIsDLL);   // should never get here

            static ATOM s_atomMenu = 0;
            bool bSubclass = true;

            if (s_atomMenu == 0)
            {
               WNDCLASSEX wc;
               __memset(&wc, 0, sizeof(WNDCLASSEX));
               wc.cbSize = sizeof(WNDCLASSEX);
               s_atomMenu = (ATOM)::GetClassInfoEx(nullptr, "#32768", &wc);
            }

            // Do not subclass menus.
            if (s_atomMenu != 0)
            {
               ATOM atomWnd = (ATOM)::GetClassLongPtr(hWnd, GCW_ATOM);
               if (atomWnd == s_atomMenu)
                  bSubclass = false;
            }
            else
            {
               char szClassName[256];
               if (::GetClassName(hWnd, szClassName, 256))
               {
                  szClassName[255] = nullptr;
                  if (_tcscmp(szClassName, "#32768") == 0)
                     bSubclass = false;
               }
            }
            if (bSubclass)
            {
               // subclass the interaction_impl with the proc which does gray backgrounds
               oldWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
               if (oldWndProc != nullptr && GetProp(hWnd, gen_OldWndProc) == nullptr)
               {
                  SetProp(hWnd, gen_OldWndProc, oldWndProc);
                  if ((WNDPROC)GetProp(hWnd, gen_OldWndProc) == oldWndProc)
                  {
                     GlobalAddAtom(gen_OldWndProc);
                     SetWindowLongPtr(hWnd, GWLP_WNDPROC, (dword_ptr)__activation_window_procedure);
                     ASSERT(oldWndProc != nullptr);
                  }
               }
            }
         }
      }

lCallNextHook:
      LRESULT lResult = CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code,
                                       wParam, lParam);

      return lResult;
   }

#endif


   void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
   {
      SCAST_PTR(::message::erase_bkgnd,perasebkgnd,pmessage);
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }


   void interaction_impl::_001BaseWndInterfaceMap()
   {

      Sys(get_context_application()).window_map().set((oswindow)(iptr)(void *)get_handle(),this);

   }


   void interaction_impl::_001OnTriggerMouseInside()
   {

      //__throw(todo());


//      m_bMouseHover = true;
      //TRACKMOUSEEVENT tme = { sizeof(tme) };
      //tme.dwFlags = TME_LEAVE;
      //tme.hwndTrack = get_handle();
      //TrackMouseEvent(&tme);

   }


} // namespace uwp




/////////////////////////////////////////////////////////////////////////////
// Map from oswindow to ::user::interaction_impl *

//hwnd_map* afxMapHWND(bool bCreate)
//{
//   UNREFERENCED_PARAMETER(bCreate);
//   try
//   {
//      __MODULE_STATE* pState = __get_module_state();
//      if(pState == nullptr)
//         return nullptr;
//      return pState->m_pmapHWND;
//   }
//   catch(...)
//   {
//      return nullptr;
//   }
//}


//::mutex * afxMutexHwnd()
//{
//   try
//   {
//      __MODULE_STATE* pState = __get_module_state();
//      if(pState == nullptr)
//         return nullptr;
//      return pState->m_pmutexHwnd;
//   }
//   catch(...)
//   {
//      return nullptr;
//   }
//}

/////////////////////////////////////////////////////////////////////////////
// The WndProc for all interaction_impl's and derived classes

#ifdef WINDOWS_DESKTOP

#undef __window_procedure

LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   // special message which identifies the interaction_impl as using __window_procedure
   if (nMsg == WM_QUERYAFXWNDPROC)
      return 1;

   // all other messages route through message ::map
   ::user::interaction_impl * pWnd = ::uwp::interaction_impl::FromHandlePermanent(hWnd);
   //ASSERT(pWnd != nullptr);
   //ASSERT(pWnd==nullptr || WIN_WINDOW(pWnd)->get_handle() == hWnd);
   if (pWnd == nullptr || WIN_WINDOW(pWnd)->get_handle() != hWnd)
      return ::DefWindowProc(hWnd, nMsg, wParam, lParam);
   return uwp::__call_window_procedure(pWnd, hWnd, nMsg, wParam, lParam);
}

// always indirectly accessed via __get_window_procedure
WNDPROC CLASS_DECL_AURA __get_window_procedure()
{
   return __get_module_state()->m_pfn_window_procedure;
}
/////////////////////////////////////////////////////////////////////////////
// Special helpers for certain windows messages

__STATIC void CLASS_DECL_AURA __pre_init_dialog(
::user::interaction * pWnd, LPRECT lpRectOld, u32* pdwStyleOld)
{
   ASSERT(lpRectOld != nullptr);
   ASSERT(pdwStyleOld != nullptr);

   WIN_WINDOW(pWnd)->get_window_rect(lpRectOld);
   *pdwStyleOld = WIN_WINDOW(pWnd)->GetStyle();
}

__STATIC void CLASS_DECL_AURA __post_init_dialog(
::user::interaction * pWnd, const RECT& rectOld, u32 dwStyleOld)
{
   // must be hidden to start with
   if (dwStyleOld & WS_VISIBLE)
      return;

   // must not be visible after WM_INITDIALOG
   if (WIN_WINDOW(pWnd)->GetStyle() & (WS_VISIBLE|WS_CHILD))
      return;

   // must not move during WM_INITDIALOG
   ::rect rect;
   WIN_WINDOW(pWnd)->get_window_rect(rect);
   if (rectOld.left != rect.left || rectOld.top != rect.top)
      return;

   // must be unowned or owner disabled
   ::user::interaction * pParent = WIN_WINDOW(pWnd)->GetWindow(GW_OWNER);
   if (pParent != nullptr && pParent->IsWindowEnabled())
      return;

   if (!WIN_WINDOW(pWnd)->CheckAutoCenter())
      return;

   // center modal dialog boxes/message boxes
   //WIN_WINDOW(pWnd)->CenterWindow();
}



CLASS_DECL_AURA void hook_window_create(::user::interaction * pWnd)
{

}

CLASS_DECL_AURA bool unhook_window_create()
{
   return TRUE;
}



CLASS_DECL_AURA const char * __register_window_class(UINT nClassStyle,
      HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
{
   // Returns a temporary string name for the class
   //  Save in a string if you want to use it for a long time
   LPTSTR lpszName = __get_thread_state()->m_szTempClassName;

   // generate a synthetic name for this class
   HINSTANCE hInst = Sys(::uwp::get_task()->get_context_application()).m_hInstance;

   if (hCursor == nullptr && hbrBackground == nullptr && hIcon == nullptr)
   {
      C_RUNTIME_ERRORCHECK_SPRINTF(_sntprintf_s(lpszName, ___TEMP_CLASS_NAME_SIZE, ___TEMP_CLASS_NAME_SIZE - 1, "::ca2:::%p:%x", hInst, nClassStyle));
   }
   else
   {
      C_RUNTIME_ERRORCHECK_SPRINTF(_sntprintf_s(lpszName, ___TEMP_CLASS_NAME_SIZE, ___TEMP_CLASS_NAME_SIZE - 1, "::ca2:::%p:%x:%p:%p:%p", hInst, nClassStyle,
                                   hCursor, hbrBackground, hIcon));
   }

   // see if the class already exists
   WNDCLASS wndcls;
   if (::GetClassInfo(hInst, lpszName, &wndcls))
   {
      // already registered, assert everything is good
      ASSERT(wndcls.style == nClassStyle);

      // NOTE: We have to trust that the hIcon, hbrBackground, and the
      //  hCursor are semantically the same, because sometimes Windows does
      //  some internal translation or copying of those handles before
      //  storing them in the internal WNDCLASS retrieved by GetClassInfo.
      return lpszName;
   }

   // otherwise we need to register a new class
   wndcls.style = nClassStyle;
   wndcls.lpfnWndProc = DefWindowProc;
   wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
   wndcls.hInstance = hInst;
   wndcls.hIcon = hIcon;
   //wndcls.hCursor = hCursor;
   wndcls.hCursor = nullptr;
   wndcls.hbrBackground = hbrBackground;
   wndcls.lpszMenuName = nullptr;
   wndcls.lpszClassName = lpszName;
   if (!__register_class(&wndcls))
      __throw(resource_exception());

   // return thread-local pointer
   return lpszName;
}



__STATIC void CLASS_DECL_AURA
__handle_activate(::user::interaction_impl * pWnd, WPARAM nState, ::user::interaction_impl * pWndOther)
{
   ASSERT(pWnd != nullptr);

   // send WM_ACTIVATETOPLEVEL when top-level parents change
   if (!(WIN_WINDOW(pWnd)->GetStyle() & WS_CHILD))
   {
      ::user::interaction * pTopLevel= WIN_WINDOW(pWnd)->GetTopLevel();
      if (pTopLevel && (pWndOther == nullptr || !::is_window(WIN_WINDOW(pWndOther)->get_handle()) || pTopLevel != WIN_WINDOW(pWndOther)->GetTopLevel()))
      {
         // lParam points to interaction_impl getting the e_message_activate message and
         //  hWndOther from the e_message_activate.
         oswindow hWnd2[2];
         hWnd2[0] = WIN_WINDOW(pWnd)->get_handle();
         if(pWndOther == nullptr || WIN_WINDOW(pWndOther) == nullptr)
         {
            hWnd2[1] = nullptr;
         }
         else
         {
            hWnd2[1] = WIN_WINDOW(pWndOther)->get_handle();
         }
         // send it...
         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (LPARAM)&hWnd2[0]);
      }
   }
}

__STATIC bool CLASS_DECL_AURA
__handle_set_cursor(::user::interaction_impl * pWnd, UINT nHitTest, UINT nMsg)
{
   if (nHitTest == HTERROR &&
         (nMsg == WM_LBUTTONDOWN || nMsg == WM_MBUTTONDOWN ||
          nMsg == WM_RBUTTONDOWN))
   {
      // activate the last active interaction_impl if not active
      ::user::interaction * pLastActive = WIN_WINDOW(pWnd)->GetTopLevel();
      if (pLastActive != nullptr)
         pLastActive = pLastActive->GetLastActivePopup();
      if (pLastActive != nullptr &&
            pLastActive != ::uwp::interaction_impl::GetForegroundWindow() &&
            pLastActive->IsWindowEnabled())
      {
         pLastActive->SetForegroundWindow();
         return TRUE;
      }
   }
   return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// Standard init called by WinMain

__STATIC bool CLASS_DECL_AURA __register_with_icon(WNDCLASS* pWndCls,
      const char * lpszClassName, UINT nIDIcon)
{
   pWndCls->lpszClassName = lpszClassName;
   pWndCls->hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
   return __register_class(pWndCls);
}


bool CLASS_DECL_AURA __end_defer_register_class(LONG fToRegisterParam, const char ** ppszClass)
{
   // mask off all classes that are already registered
   __MODULE_STATE* pModuleState = __get_module_state();
   LONG fToRegister = fToRegisterParam & ~pModuleState->m_fRegisteredClasses;
   if (fToRegister == 0)
   {
      fToRegister = fToRegisterParam;
      if(ppszClass != nullptr)
      {
         if(fToRegister & __WND_REG)
         {
            *ppszClass = gen_Wnd;
         }
         else if (fToRegister & __WNDOLECONTROL_REG)
         {
            *ppszClass = gen_WndOleControl;
         }
         else if (fToRegister & __WNDCONTROLBAR_REG)
         {
            *ppszClass = gen_WndControlBar;
         }
         else if(fToRegister & __WNDMDIFRAME_REG)
         {
            *ppszClass = gen_WndMDIFrame;
         }
         else if(fToRegister & __WNDFRAMEORVIEW_REG)
         {
            *ppszClass = gen_WndFrameOrView;
         }
      }
      return TRUE;
   }

   LONG fRegisteredClasses = 0;

   // common initialization
   WNDCLASS wndcls;
   __memset(&wndcls, 0, sizeof(WNDCLASS));   // start with nullptr defaults
   wndcls.lpfnWndProc = DefWindowProc;
   wndcls.hInstance = Sys(::uwp::get_task()->get_context_application()).m_hInstance;
   //wndcls.hCursor = afxData.hcurArrow;

   INITCOMMONCONTROLSEX init;
   init.dwSize = sizeof(init);

   // work to register classes as specified by fToRegister, populate fRegisteredClasses as we go
   if (fToRegister & __WND_REG)
   {
      // Child windows - no brush, no icon, safest default class styles
      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
      wndcls.lpszClassName = gen_Wnd;
      if (__register_class(&wndcls))
      {
         if(ppszClass != nullptr)
         {
            *ppszClass = wndcls.lpszClassName;
         }
         fRegisteredClasses |= __WND_REG;
      }
   }
   if (fToRegister & __WNDOLECONTROL_REG)
   {
      // OLE control windows - use parent DC for speed
      wndcls.style |= CS_PARENTDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
      wndcls.lpszClassName = gen_WndOleControl;
      if (__register_class(&wndcls))
      {
         if(ppszClass != nullptr)
         {
            *ppszClass = wndcls.lpszClassName;
         }
         fRegisteredClasses |= __WNDOLECONTROL_REG;
      }
   }
   if (fToRegister & __WNDCONTROLBAR_REG)
   {
      // control bar windows
      wndcls.style = 0;   // control bars don't handle double click
      wndcls.lpszClassName = gen_WndControlBar;
      wndcls.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
      if (__register_class(&wndcls))
      {
         if(ppszClass != nullptr)
         {
            *ppszClass = wndcls.lpszClassName;
         }
         fRegisteredClasses |= __WNDCONTROLBAR_REG;
      }
   }
   if (fToRegister & __WNDMDIFRAME_REG)
   {
      // MDI Frame interaction_impl (also used for splitter interaction_impl)
      wndcls.style = CS_DBLCLKS;
      wndcls.hbrBackground = nullptr;
      /*      if (__register_with_icon(&wndcls, gen_WndMDIFrame, __IDI_STD_MDIFRAME))
      {
      if(ppszClass != nullptr)
      {
      *ppszClass = gen_WndMDIFrame;
      }
      fRegisteredClasses |= __WNDMDIFRAME_REG;
      }*/
   }
   if (fToRegister & __WNDFRAMEORVIEW_REG)
   {
      // SDI Frame or MDI Child windows or views - normal colors
      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
      wndcls.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
      if (__register_with_icon(&wndcls, gen_WndFrameOrView, 123))
      {
         if(ppszClass != nullptr)
         {
            *ppszClass = gen_WndFrameOrView;
         }
         fRegisteredClasses |= __WNDFRAMEORVIEW_REG;
      }
   }


   // save new state of registered controls
   pModuleState->m_fRegisteredClasses |= fRegisteredClasses;

   // special case for all common controls registered, turn on __WNDCOMMCTLS_REG
   if ((pModuleState->m_fRegisteredClasses & __WIN95CTLS_MASK) == __WIN95CTLS_MASK)
   {
      pModuleState->m_fRegisteredClasses |= __WNDCOMMCTLS_REG;
      fRegisteredClasses |= __WNDCOMMCTLS_REG;
   }

   // must have registered at least as mamy classes as requested
   return (fToRegister & fRegisteredClasses) == fToRegister;
}


/////////////////////////////////////////////////////////////////////////////
// Special WndProcs (activation handling & gray dialogs)


LRESULT CALLBACK
__activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, gen_OldWndProc);
   ASSERT(oldWndProc != nullptr);

   LRESULT lResult = 0;
   try
   {
      bool bCallDefault = TRUE;
      switch (nMsg)
      {
      case WM_INITDIALOG:
      {
         u32 uStyle;
         ::rect rectOld;
         ::user::interaction_impl * pWnd = ::uwp::interaction_impl::from_handle(hWnd);
         __pre_init_dialog(pWnd, &rectOld, &uStyle);
         bCallDefault = FALSE;
         lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wParam, lParam);
         __post_init_dialog(pWnd, rectOld, uStyle);
      }
      break;

      case e_message_activate:
         __handle_activate(::uwp::interaction_impl::from_handle(hWnd), wParam,
                           ::uwp::interaction_impl::from_handle((oswindow)lParam));
         break;

      case WM_SETCURSOR:
         bCallDefault = !__handle_set_cursor(::uwp::interaction_impl::from_handle(hWnd),
                                             (short)LOWORD(lParam), HIWORD(lParam));
         break;

      case WM_NCDESTROY:
         SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<iptr>(oldWndProc));
         RemoveProp(hWnd, gen_OldWndProc);
         GlobalDeleteAtom(GlobalFindAtom(gen_OldWndProc));
         break;
      }

      // call original wndproc for default handling
      if (bCallDefault)
         lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wParam, lParam);
   }
   catch(::exception::aura * pe)
   {
      // handle exception
      MSG msg;
      msg.hwnd = hWnd;
      msg.message = nMsg;
      msg.wParam = wParam;
      msg.lParam = lParam;

      //lResult = __process_window_procedure_exception(pe, &msg);
      //      TRACE(::aura::trace::category_AppMsg, 0, "Warning: Uncaught exception in __activation_window_procedure (returning %ld).\n",
      //       lResult);
      ::exception_pointer esp(pe);
   }


   return lResult;
}




/////////////////////////////////////////////////////////////////////////////
// Additional helpers for WNDCLASS init

// like RegisterClass, except will automatically call UnregisterClass
bool CLASS_DECL_AURA __register_class(WNDCLASS* lpWndClass)
{
   WNDCLASS wndcls;
   if (GetClassInfo(lpWndClass->hInstance, lpWndClass->lpszClassName,
                    &wndcls))
   {
      // class already registered
      return TRUE;
   }

   if (!::RegisterClass(lpWndClass))
   {
      //      TRACE(::aura::trace::category_AppMsg, 0, "Can't register interaction_impl class named %s\n",
      //       lpWndClass->lpszClassName);
      return FALSE;
   }

   bool bRet = TRUE;

   if (afxContextIsDLL)
   {

      try
      {
         // class registered successfully, add to registered list
         __MODULE_STATE* pModuleState = __get_module_state();
         single_lock sl(&pModuleState->m_mutexRegClassList, TRUE);
         if(pModuleState->m_pstrUnregisterList == nullptr)
            pModuleState->m_pstrUnregisterList = new string;
         *pModuleState->m_pstrUnregisterList += lpWndClass->lpszClassName;
         *pModuleState->m_pstrUnregisterList +='\n';
      }
      catch(::exception::aura * pe)
      {
         ::ca2::rethrow(pe);
         // Note: DELETE_EXCEPTION not required.
      }

   }

   return bRet;
}

#endif


namespace uwp
{



   ::user::interaction *  interaction_impl::get_wnd() const
   {

      return  m_puserinteraction;

   }


   Agile<Windows::UI::Core::CoreWindow> interaction_impl::get_os_window()
   {
      
      return m_window;

   }


   void interaction_impl::set_view_port_org(::image * pimage)
   {
      // graphics will be already set its view port to the interaction_impl for linux - cairo with xlib


      rect rectWindow;
      m_puserinteraction->get_window_rect(rectWindow);
      //      get_wnd()->_001ScreenToClient(rectWindow);
      pimage->SetViewportOrg(point(rectWindow.top_left()));
      //pimage->SelectClipRgn(nullptr);

   }


   void interaction_impl::offset_view_port_org(LPRECT lprectScreen)
   {
   }


   bool interaction_impl::has_pending_graphical_update()
   {

      if (::user::interaction_impl::has_pending_graphical_update())
      {

         return true;

      }

      sync_lock sl(m_puserinteraction->mutex());

      for (auto p : m_puserinteraction->m_uiptraChild.m_interactiona)
      {

         if (p != nullptr)
         {

            if (p->has_pending_graphical_update())
            {

               return true;

            }

         }

      }

      return false;

   }


   void interaction_impl::on_after_graphical_update()
   {

      //m_puserinteraction->on_after_graphical_update();

      sync_lock sl(m_puserinteraction->mutex());

      for (auto p : m_puserinteraction->m_uiptraChild.m_interactiona)
      {

         p->on_after_graphical_update();

      }

      main_async([this]()
         {

            auto presizemanager = ::Windows::UI::Core::CoreWindowResizeManager::GetForCurrentView();

            presizemanager->NotifyLayoutCompleted();

         });

   }


   ::estatus interaction_impl::update_graphics_resources()
   {

      return ::user::interaction_impl::update_graphics_resources();

   }


   void interaction_impl::queue_message_handler(::message::base * pbaseParam)
   {

      defer_create_thread(this);

      //if (bFreeHandDrawingMode)
      //{

      //   return m_puserinteraction->message_handler(pbaseParam);

      //}
      //else
      //{

         //__pointer(::message::mouse) pmouse = pbaseParam;

         //if (pmouse)
         //{

         //   if (pmouse->m_id == e_message_mouse_move)
         //   {

         //      pointd pointNow(pmouse->m_point);

         //      double dx = pointNow.x - m_pointLastMouseMove.x;

         //      double dy = pointNow.y - m_pointLastMouseMove.y;

         //      m_pointLastMouseMove = pointNow;

         //      double dDistanceFromLast = sqrt(dx * dx + dy * dy);

         //      m_dAccumulatedMouseMoveDistance += dDistanceFromLast;

         //      double dTimeFromLast = (double) m_tickLastMouseMove.elapsed().m_i / 1000.0;

         //      if (dTimeFromLast == 0.) dTimeFromLast = 0.001;

         //      double dDistanceMomentum = m_dAccumulatedMouseMoveDistance * dTimeFromLast;

         //      bool bIgnoreMessage = dDistanceMomentum < 2.0;

         //      if (bIgnoreMessage)
         //      {

         //         return;

         //      }

         //      m_dAccumulatedMouseMoveDistance = 0.0;

         //      m_tickLastMouseMove.Now();

         //   }

         //}

         //sync_lock sl(&m_mutexQueue);

         //m_messageaQueue.add(pbase);

         //m_evQueue.set_event();
      
         //void primitive_impl::queue_message_handler(::message::base * pbaseParam)
         //{

         __pointer(::message::base) pbase = pbaseParam;

         post(pbase);

      //}

      //m_puserinteraction->message_handler(pbase);

   }


   bool interaction_impl::has_focus()
   {

      return get_handle() == ::get_focus();

   }


   bool interaction_impl::is_active()
   {

      return get_handle() == ::get_active_window();

   }

   //int alskdjfh = 0;

   void interaction_impl::_001UpdateScreen()
   {

      ::user::interaction_impl::_001UpdateScreen();

      //alskdjfh++;
      //::output_debug_string("::uwp::interaction_impl::_001UpdateScreen " + __str(alskdjfh) + "\n");

      //if (m_directxapplication)
      //{

      //   if (m_directxapplication->m_window.Get())
      //   {

      //      main_async([this]()
      //         {

      //            m_directxapplication->m_window->Activate();

      //         });

      //   }

      //}

   }


   bool interaction_impl::_is_window() const
   {

      return m_directxapplication != nullptr && m_directxapplication->m_window != nullptr;

   }


   void interaction_impl::show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd)
   {

      Session.m_directxapplication->SetText(str, iBeg, iEnd);

   }

   
   void interaction_impl::edit_on_set_focus(::user::interaction* pinteraction)
   {

      string strText;

      pinteraction->_001GetText(strText);

      strsize sizeLen = strText.get_length();

      Session.m_directxapplication->SetText(strText, 0, sizeLen);

   }


   bool interaction_impl::is_text_composition_active()
   {

      return m_directxapplication->m_bTextCompositionActive;


   }


   void interaction_impl::set_input_content_rect(const rect& rect)
   {

      __copy(m_directxapplication->m_rectInputContentRect, rect);

   }


   void interaction_impl::set_input_selection_rect(const rect& rect)
   {

      __copy(m_directxapplication->m_rectInputSelectionRect, rect);

   }


   rect interaction_impl::get_input_content_rect()
   {

      ::rect rect;

      __copy(rect, m_directxapplication->m_rectInputContentRect);

      return rect;

   }


   rect interaction_impl::get_input_selection_rect()
   {

      ::rect rect;

      __copy(rect, m_directxapplication->m_rectInputSelectionRect);

      return rect;


   }



} // namespace uwp





