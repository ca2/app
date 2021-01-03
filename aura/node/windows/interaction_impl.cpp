#include "framework.h"
#include "acme/os/windows/windowing.h"
#include "aura/node/windows/_windows.h"
#include "system_interaction_impl.h"
#include "aura/message.h"
#include "aura/user/interaction_thread.h"
#include "aura/os/windows/windowing.h"
#include "aura/os/windows/imm_context.h"
#include "aura/node/windows/buffer.h"
#include "acme/const/timer.h"
#include "apex/platform/app_core.h"


#ifdef WINDOWS_DESKTOP
#include <dwmapi.h>
#include <VersionHelpers.h>
#include <VersionHelpers.h>
#include <shellapi.h>
#ifndef WM_NCUAHDRAWCAPTION
#define WM_NCUAHDRAWCAPTION (0x00AE)
#endif
#ifndef WM_NCUAHDRAWFRAME
#define WM_NCUAHDRAWFRAME (0x00AF)
#endif


CLASS_DECL_AURA WNDPROC windows_user_interaction_impl_get_window_procedure();


CLASS_DECL_AURA wstring windows_register_window_class(::layered * pobjectContext, ::u32 nClassStyle, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon);


static bool has_autohide_appbar(::u32 edge, const rect& mon) // Interface Update - Infinisys Ltd.
{
   if (IsWindows8Point1OrGreater())
   {
      APPBARDATA data = {};
      data.cbSize = sizeof(APPBARDATA);
      data.uEdge = edge;
      data.rc = mon;
      return SHAppBarMessage(0x0000000b, &data);
   }

   /* Before Windows 8.1, it was not possible to specify a monitor when
    checking for hidden appbars, so check only on the primary monitor */
   if (mon.left != 0 || mon.top != 0)
      return false;
   APPBARDATA data = {};
   data.cbSize = sizeof(APPBARDATA);
   data.uEdge = edge;
   return SHAppBarMessage(ABM_GETAUTOHIDEBAR, &data);
}
#endif



//const GUID CLSID_TaskbarList = { 0x56FDF344, 0xFD6D, 0x11D0,{ 0x95, 0x8A, 0x00, 0x60, 0x97, 0xC9, 0xA0, 0x90 } };
//const GUID IID_ITaskbarList = { 0x56FDF342, 0xFD6D, 0x11D0,{ 0x95, 0x8A, 0x00, 0x60, 0x97, 0xC9, 0xA0, 0x90 } };
//const GUID IID_ITaskbarList2 = { 0x602D4995, 0xB13A, 0x429b,{ 0xA6, 0x6E, 0x19, 0x35, 0xE4, 0x4F, 0x43, 0x17 } };
//const GUID IID_ITaskList3 = { 0xEA1AFB91, 0x9E28, 0x4B86,{ 0x90, 0xE9, 0x9E, 0x9F, 0x8A, 0x5E, 0xEF, 0xAF } };

CLASS_DECL_AURA int g_iMouseDown = 0;

//CLASS_DECL_AURA thread_iptr < DWORD_PTR > t_time1;
//CLASS_DECL_AURA thread_iptr < DWORD_PTR > t_time2;


//extern CLASS_DECL_AURA thread_int_ptr < DWORD_PTR > t_time1;

//thread_int_ptr < HHOOK > t_hHookOldCbtFilter;
//thread_pointer < ::windows::interaction_impl  > thread_set("wnd_init");

//LRESULT CALLBACK __activation_window_procedure(oswindow oswindow,::u32 nMsg,WPARAM wParam,LPARAM lParam);

const char * gen_OldWndProc = "::aura::OldWndProc423";

//CLASS_DECL_AURA bool hook_window_create(::windows::interaction_impl * pwindow);


//#define __WNDCLASS(s)    L"ca2" L##s
//#define __WND             __WNDCLASS("Wnd")
//#define __WNDCONTROLBAR   __WNDCLASS("ControlBar")
//#define __WNDMDIFRAME     __WNDCLASS("MDIFrame")
//#define __WNDFRAMEORVIEW  __WNDCLASS("FrameOrView")
//#define __WNDOLECONTROL   __WNDCLASS("OleControl")


const unichar gen_WndControlBar[] = L"window_control_impl";
const unichar gen_WndMDIFrame[] = L"window_mdi_frame_impl";
const unichar gen_WndFrameOrView[] = L"window_interaction_impl";
const unichar gen_WndOleControl[] = L"window_ole_control_impl";

struct __CTLCOLOR
{
   oswindow oswindow;
   HDC hDC;
   ::u32 nCtlType;
};


const unichar gen_Wnd[] = L"windows_interaction_impl";


namespace windows
{


   interaction_impl::interaction_impl()
   {

      user_common_construct();

   }


   HRESULT STDMETHODCALLTYPE interaction_impl::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL point, DWORD *pdwEffect)
   {

      ::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGENTER);

      m.pDataObj = pDataObj;
      m.grfKeyState = grfKeyState;
      m.point = point;
      m.dwEffect = DROPEFFECT_NONE;

      try
      {

         message_handler(&m);

      }
      catch (...)
      {

      }

      // Call the drag and drop helper.
      if (m_bUseDnDHelper)
      {
         // The DnD helper needs an IDataObject interface, so get one from
         // the COleDataObject.  Note that the FALSE lparam means that
         // GetIDataObject will not AddRef() the returned interface, so
         // we do not Release() it.
         ::point point(m.point.x, m.point.y);

         m_piDropHelper->DragEnter(get_handle(), m.pDataObj, &point, m.dwEffect);
      }

      *pdwEffect = m.dwEffect;

      return S_OK;

   }


   HRESULT STDMETHODCALLTYPE interaction_impl::DragOver(DWORD grfKeyState, POINTL point,  DWORD *pdwEffect)
   {

      ::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGOVER);

      m.pDataObj = nullptr;
      m.grfKeyState = grfKeyState;
      m.point = point;
      m.dwEffect = DROPEFFECT_NONE;

      try
      {

         message_handler(&m);

      }
      catch (...)
      {

      }

      // Call the drag and drop helper.
      if (m_bUseDnDHelper)
      {
         // The DnD helper needs an IDataObject interface, so get one from
         // the COleDataObject.  Note that the FALSE lparam means that
         // GetIDataObject will not AddRef() the returned interface, so
         // we do not Release() it.
         ::point point(m.point.x, m.point.y);
         m_piDropHelper->DragOver(&point, m.dwEffect);
      }


      *pdwEffect = m.dwEffect;

      return S_OK;
   }


   HRESULT STDMETHODCALLTYPE interaction_impl::DragLeave(void)
   {

      ::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGLEAVE);

      m.pDataObj = nullptr;
      m.grfKeyState = 0;
      m.point = { 0,0 };
      m.dwEffect = DROPEFFECT_NONE;

      try
      {

         message_handler(&m);

      }
      catch (...)
      {

      }

      // Call the drag and drop helper.
      if (m_bUseDnDHelper)
      {
         m_piDropHelper->DragLeave();
      }


      return S_OK;

   }


   HRESULT STDMETHODCALLTYPE interaction_impl::Drop(IDataObject * pDataObj, DWORD grfKeyState, POINTL point, DWORD * pdwEffect)
   {

      ::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGDROP);

      m.pDataObj = pDataObj;
      m.grfKeyState = grfKeyState;
      m.point = point;
      m.dwEffect = DROPEFFECT_NONE;

      try
      {

         message_handler(&m);

      }
      catch (...)
      {

      }

      // Call the drag and drop helper.
      if (m_bUseDnDHelper)
      {
         // The DnD helper needs an IDataObject interface, so get one from
         // the COleDataObject.  Note that the FALSE lparam means that
         // GetIDataObject will not AddRef() the returned interface, so
         // we do not Release() it.
         ::point point(m.point.x, m.point.y);
         m_piDropHelper->Drop(m.pDataObj, &point, m.dwEffect);
      }

      *pdwEffect = m.dwEffect;

      return S_OK;

   }


   HRESULT STDMETHODCALLTYPE interaction_impl::QueryInterface(REFIID riid, void **ppvObject)
   {

      if (__uuidof(IDropTarget) == riid)
      {
         *ppvObject = this;
      }
      else if (__uuidof(IUnknown) == riid)
      {
         *ppvObject = this;
      }
      else
      {
         *ppvObject = nullptr;
         return E_FAIL;
      }

      this->AddRef();

      return S_OK;

   }


   ULONG STDMETHODCALLTYPE interaction_impl::AddRef(void)
   {

      return (ULONG)add_ref(OBJ_REF_DBG_THIS);

   }


   ULONG STDMETHODCALLTYPE interaction_impl::Release(void)
   {

      return (ULONG)release();

   }


   void interaction_impl::construct(oswindow oswindow)
   {

      set_handle(oswindow);

   }


   void interaction_impl::user_common_construct()
   {

      m_bFocusImpl = false;

      m_bSystemCaret = false;

      m_uCodePage = CP_UTF8;

      m_iLangId = LANG_USER_DEFAULT;

      m_pfnSuper = nullptr;
      m_bUseDnDHelper = false;
      m_bUpdateGraphics = false;
      m_bIgnoreSizeEvent = false;
      m_bIgnoreMoveEvent = false;

      set_handle(nullptr);

      xxf_zero(m_size);
      xxf_zero(m_point);

   }


   interaction_impl::~interaction_impl()
   {

      if (m_strDebug.contains_ci("main_frame"))
      {

         output_debug_string("main_frame");

      }

   }


   void * interaction_impl::get_os_data() const
   {

      return (void *)((::windows::interaction_impl *) this)->get_handle();

   }


   //::e_status interaction_impl::finish(::context_object * pcontextobjectFinish)
   //{

   //   auto estatus = ::user::interaction_impl::finish(pcontextobjectFinish);

   //   return estatus;

   //}


   __STATIC bool CLASS_DECL_AURA __modify_style(oswindow oswindow, i32 nStyleOffset,
         u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   {
      ASSERT(oswindow != nullptr);
      u32 uStyle = ::GetWindowLong(oswindow, nStyleOffset);
      u32 dwNewStyle = (uStyle & ~dwRemove) | dwAdd;
      if (uStyle == dwNewStyle)
         return FALSE;

      ::SetWindowLong(oswindow, nStyleOffset, dwNewStyle);
      if (nFlags != 0)
      {
         ::SetWindowPos(oswindow, nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
      }
      return TRUE;
   }

   bool interaction_impl::ModifyStyle(oswindow oswindow, u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   {

      bool bOk = __modify_style(oswindow, GWL_STYLE, dwRemove, dwAdd, 0);

      if (nFlags != 0)
      {

         //m_iShowFlags = nFlags;



      }

      return bOk;

   }


   bool interaction_impl::ModifyStyleEx(oswindow oswindow, u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   {

      return __modify_style(oswindow, GWL_EXSTYLE, dwRemove, dwAdd, nFlags);

   }


   //LRESULT interaction_impl::Default()
   //{

   //   return default_window_procedure(m_uiMessage, m_wparam, m_lparam);

   //}


   void interaction_impl::pre_subclass_window()
   {

   }


   bool interaction_impl::_native_create_window_ex(__pointer(::user::create_struct) pcreatestruct)
   {

      //__refer(m_puserinteraction->m_pthreadUserInteraction, ::get_task() OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      //m_puserinteraction->m_pthreadUserInteraction->uiptra().add(m_puserinteraction);

      //__refer(m_pthreadUserImpl, m_puserinteraction->m_pthreadUserInteraction OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      m_strDebug += ::str::demangle(m_puserinteraction->type_name()) +  ";";

      ASSERT(pcreatestruct->m_createstruct.lpszClass == nullptr || __is_valid_string(pcreatestruct->m_createstruct.lpszClass) || __is_valid_atom(pcreatestruct->m_createstruct.lpszClass));

      ENSURE_ARG(pcreatestruct->m_createstruct.lpszName == nullptr || __is_valid_string(pcreatestruct->m_createstruct.lpszName));

      wstring wstrClassName(pcreatestruct->m_createstruct.lpszClass);

      if (wstrClassName.is_empty())
      {

         wstrClassName = m_puserinteraction->calc_window_class();

      }

      pcreatestruct->m_createstruct.lpszClass = wstrClassName;

      if (!m_puserinteraction->pre_create_window(pcreatestruct))
      {

         return false;

      }

      install_message_routing(m_puserinteraction);

      //if (!hook_window_create(this))
      //{

      //   PostNcDestroy();

      //   return false;

      //}

      // if window is not created, it may destroy this object, so keep the app as local payload

      thread_value("wnd_init") = this;

      //::aura::application * papp = &Application;

      wstring wstrWindowName(pcreatestruct->m_createstruct.lpszName);

      //string char

      //wstring wchar_t

      //if (wstrWindowName.is_empty())
      //{

      //   wstrWindowName = L"window";

      //}

#if 0

      WCHAR szTitle[256];
      WCHAR szWindowClass[256];

      wcscpy(szTitle, L"123");
      wcscpy(szWindowClass, L"WindowsDestkop1");

      //oswindow oswindow = CreateWindowExW(pcreatestruct->m_createstruct.dwExStyle, szWindowClass, wstrWindowName, pcreatestruct->m_createstruct.style,
        // pcreatestruct->m_createstruct.x, pcreatestruct->m_createstruct.y, pcreatestruct->m_createstruct.cx, pcreatestruct->m_createstruct.cy, pcreatestruct->m_createstruct.hwndParent, pcreatestruct->m_createstruct.hMenu, pcreatestruct->m_createstruct.hInstance, pcreatestruct->m_createstruct.lpCreateParams);
      oswindow oswindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED,
         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, pcreatestruct->m_createstruct.hInstance, nullptr);
      //if (!oswindow)
      //{
         //return false;
      //}

      ::ShowWindow(oswindow, SW_SHOWNORMAL);
      ::UpdateWindow(oswindow);

#if 0

      MSG msg;

      // Main message loop:
      while (mq_get_message(&msg, nullptr, 0, 0))
      {
         //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }

#else

      m_puserthread->run();

#endif

      //return true;

#else

      oswindow oswindow = ::CreateWindowExW(
         pcreatestruct->m_createstruct.dwExStyle,
         wstrClassName,
         wstrWindowName,
         pcreatestruct->m_createstruct.style,
         pcreatestruct->m_createstruct.x, 
         pcreatestruct->m_createstruct.y, 
         pcreatestruct->m_createstruct.cx,
         pcreatestruct->m_createstruct.cy,
         pcreatestruct->m_createstruct.hwndParent, 
         pcreatestruct->m_createstruct.hMenu, 
         pcreatestruct->m_createstruct.hInstance,
         pcreatestruct->m_createstruct.lpCreateParams);

#endif

      //HWND oswindow = CreateWindowW(wstrClassName, wstrWindowName, WS_OVERLAPPED,
      //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, pcreatestruct->m_createstruct.hInstance, nullptr);

      //::ShowWindow(oswindow,SW_SHOWNORMAL);
      //::UpdateWindow(oswindow);

      //bool bUnicode = IsWindowUnicode(oswindow);

      u32 dwLastError = ::GetLastError();

      //if (!unhook_window_create())
      //{

      //   PostNcDestroy();        // cleanup if CreateWindowEx fails too soon

      //}

      if (pcreatestruct->m_createstruct.hwndParent == HWND_MESSAGE)
      {

         m_puserinteraction->m_ewindowflag -= e_window_flag_graphical;

      }

      if (oswindow == nullptr)
      {

         //if (papp == nullptr)
         //{

         //   return false;

         //}

         string strLastError = FormatMessageFromSystem(dwLastError);

         string strMessage;

         strMessage.Format("%s\n\nSystem Error Code: %d", strLastError, dwLastError);

         TRACE(trace_category_appmsg, trace_level_warning, "Warning: Window creation failed: get_last_error returned:\n");

         TRACE(trace_category_appmsg, trace_level_warning, "%s\n", strMessage);

         try
         {

            if (dwLastError == 0x0000057e)
            {

               TRACE("Cannot create a top-level child interaction_impl.");

            }
            else
            {

               TRACE("%s", strMessage);

            }

         }
         catch (...)
         {

         }

      }

      if (oswindow == nullptr)
      {

         return false;

      }

      m_puserinteraction->layout().sketch() = ::point(pcreatestruct->m_createstruct.x, pcreatestruct->m_createstruct.y);
      m_puserinteraction->layout().sketch() = ::size(pcreatestruct->m_createstruct.cx, pcreatestruct->m_createstruct.cy);

      m_puserinteraction->layout().window() = ::point(pcreatestruct->m_createstruct.x, pcreatestruct->m_createstruct.y);
      m_puserinteraction->layout().window() = ::size(pcreatestruct->m_createstruct.cx, pcreatestruct->m_createstruct.cy);

      bool bUnicode = ::IsWindowUnicode(oswindow) != FALSE;

      if (bUnicode)
      {

         output_debug_string("window is unicode");

      }
      else
      {

         output_debug_string("window is ANSI");

      }

      //WNDCLASSEXW wndcls;

      //if (wstrClassName.get_length() > 0 && GetClassInfoExW(System.m_hinstance, wstrClassName, &wndcls) && wndcls.hIcon != nullptr)
      {

         //Application.set_icon(m_puserinteraction, __new(::draw2d::icon(get_context_application(), wndcls.hIcon)), false);

         //Application.set_icon(m_puserinteraction, __new(::draw2d::icon(get_context_application(), wndcls.hIcon)), true);

      }

      if (oswindow != get_handle())
      {

         set_handle(oswindow);
         //ASSERT(FALSE); // should have been set in send msg hook

      }

      /// this Windows native window "holds" context_object to the
      /// wrapping object.
      m_puserinteraction->add_ref(OBJ_REF_DBG_THIS);

      m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

      return true;

   }


   bool interaction_impl::pre_create_window(::user::create_struct * pcreatestruct)
   {

      return true;

   }


   // bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const char * lpszName)
   // {

   //    if (_is_window())
   //    {

   //       DestroyWindow();

   //    }

   //    ::user::create_struct createstruct(0, nullptr, lpszName, WS_CHILD, nullptr);

   //    pcreatestruct->m_createstruct.hwndParent = HWND_MESSAGE;

   //    if (!native_create_window_ex(pinteraction, createstruct, HWND_MESSAGE))
   //    {

   //       return false;

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
      MESSAGE_LINK(e_message_create, pchannel, this, &interaction_impl::_001OnCreate);
      if (!m_puserinteraction->m_bMessageWindow)
      {
         MESSAGE_LINK(e_message_set_cursor, pchannel, this, &interaction_impl::_001OnSetCursor);
         MESSAGE_LINK(e_message_erase_background, pchannel, this, &interaction_impl::_001OnEraseBkgnd);
         MESSAGE_LINK(e_message_nccalcsize, pchannel, this, &interaction_impl::_001OnNcCalcSize);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_impl::_001OnShowWindow);
         MESSAGE_LINK(e_message_activate, pchannel, this, &interaction_impl::_001OnActivate);
         MESSAGE_LINK(WM_DWMNCRENDERINGCHANGED, pchannel, this, &interaction_impl::_001OnDwmNcRenderingChanged);
         MESSAGE_LINK(e_message_move, pchannel, this, &interaction_impl::_001OnMove);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::_001OnSize);
         MESSAGE_LINK(e_message_window_position_changing,pchannel,this,&interaction_impl::_001OnWindowPosChanging);
         MESSAGE_LINK(e_message_window_position_changed,pchannel,this,&interaction_impl::_001OnWindowPosChanged);
         MESSAGE_LINK(WM_GETMINMAXINFO,pchannel,this,&interaction_impl::_001OnGetMinMaxInfo);


      }

      prio_install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction_impl::_001OnDestroy);
      MESSAGE_LINK(e_message_enable, pchannel, this, &interaction_impl::_001OnEnable);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::_001OnKillFocus);



   }


   void interaction_impl::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if (pshowwindow->m_bShow)
      {

         output_debug_string("windows::interaction_impl::_001OnShowWindow bShow = true");

      }
      else
      {

         output_debug_string("windows::interaction_impl::_001OnShowWindow bShow = false");

      }


   }


   void interaction_impl::win_update_graphics()
   {

      single_lock sl(m_puserinteraction->mutex(), false);

      if (!sl.lock())
      {
         
         m_bUpdateGraphics = true;

         return;

      }

      m_bUpdateGraphics = false;

      ::rect rectWindow;

      m_puserinteraction->layout().design().screen_rect(rectWindow);

      m_point = rectWindow.top_left();

      if (m_size != rectWindow.size())
      {

         //if(m_pimage->is_null())
         //   m_pimage->create(this);

         //m_pimage = create_image(rectWindow->size());

         m_size = rectWindow.size();

      }

   }


   void interaction_impl::_001OnMove(::message::message* pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         return;

      }

      SCAST_PTR(::message::move, pmove, pmessage);

      if (m_puserinteraction->layout().sketch().origin() != pmove->m_point)
      {

         if (m_puserinteraction->layout().is_moving())
         {

            INFO("Window is Moving :: _001OnMove");

         }

         m_puserinteraction->layout().sketch().origin()= pmove->m_point;

         if (m_puserinteraction->layout().sketch().display() != e_display_normal)
         {

            m_puserinteraction->display(e_display_normal);

         }

         m_puserinteraction->set_reposition();

         m_puserinteraction->set_need_redraw();

      }

   }


   void interaction_impl::_001OnSize(::message::message * pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         return;

      }

      SCAST_PTR(::message::size, psize, pmessage);

      if (m_puserinteraction->layout().sketch().size() != psize->m_size)
      {

         m_puserinteraction->layout().sketch().size() = psize->m_size;

         if (m_puserinteraction->layout().sketch().display() != e_display_normal)
         {

            m_puserinteraction->display(e_display_normal);

         }

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

      }

   }


   void interaction_impl::_001OnEnable(::message::message * pmessage)
   {

      SCAST_PTR(::message::enable, penable, pmessage);

      if (penable != nullptr)
      {

         if (penable->get_enable())
         {

            output_debug_string("::window::interaction_impl _001OnEnable = TRUE");

         }
         else
         {

            output_debug_string("::window::interaction_impl _001OnEnable = FALSE");

         }

      }

   }


   void interaction_impl::_001OnDestroy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      //__release(m_pthreadUserImpl OBJ_REF_DBG_COMMA_THIS);

   }


   void interaction_impl::PostNcDestroy()
   {

      WNDPROC pfnWndProc = WNDPROC(::GetWindowLongPtr(get_handle(), GWLP_WNDPROC));

      if (WNDPROC(::GetWindowLongPtr(get_handle(), GWLP_WNDPROC)) == pfnWndProc)
      {

         WNDPROC pfnSuper = *GetSuperWndProcAddr();

         if (pfnSuper != nullptr)
         {

            ::SetWindowLongPtr(get_handle(), GWLP_WNDPROC, reinterpret_cast<iptr>(pfnSuper));

         }

      }

      ::user::interaction_impl::PostNcDestroy();

   }


   void interaction_impl::on_final_release()
   {

      if (get_handle() != nullptr)
      {

         DestroyWindow();    // will call PostNcDestroy

      }
      else
      {

         PostNcDestroy();

      }

   }


   void interaction_impl::assert_valid() const
   {
      if (((::windows::interaction_impl *)this)->get_handle() == nullptr)
         return;     // null (unattached) windows are valid

      // check for special wnd??? values
      ASSERT(HWND_TOP == nullptr);       // same as desktop
      if (((::windows::interaction_impl *)this)->get_handle() == HWND_BOTTOM)
      {
      }
      else if (((::windows::interaction_impl *)this)->get_handle() == HWND_TOPMOST)
      {
      }
      else if (((::windows::interaction_impl *)this)->get_handle() == HWND_NOTOPMOST)
      {
      }
      else
      {
         // should be a normal interaction_impl
         ASSERT(::is_window(((::windows::interaction_impl *)this)->get_handle()));

      }
   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      dumpcontext << "\nm_oswindow_ = " << ((::windows::interaction_impl *)this)->get_handle();

      if (((::windows::interaction_impl *)this)->get_handle() == nullptr || ((::windows::interaction_impl *)this)->get_handle() == HWND_BOTTOM ||
            ((::windows::interaction_impl *)this)->get_handle() == HWND_TOPMOST || ((::windows::interaction_impl *)this)->get_handle() == HWND_NOTOPMOST)
      {
         // not a normal interaction_impl - nothing more to dump
         return;
      }

      if (!::is_window(((::windows::interaction_impl *)this)->get_handle()))
      {
         // not a valid interaction_impl
         dumpcontext << " (illegal oswindow)";
         return; // don't do anything more
      }

      auto puserinteraction = System.ui_from_handle(((::windows::interaction_impl *)this)->get_handle());
      if (puserinteraction->m_pimpl != (::user::interaction_impl *) this)
         dumpcontext << " (Detached or temporary interaction_impl)";
      else
         dumpcontext << " (permanent interaction_impl)";

      wchar_t szBuf[64];
      ::GetClassNameW(((::windows::interaction_impl *)this)->get_handle(), szBuf, _countof(szBuf));
      dumpcontext << "\nclass name = \"" << szBuf << "\"";

      ::rect rect;
      ((::windows::interaction_impl *) this)->m_puserinteraction->layout().window().screen_rect(&rect);
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent ::user::interaction_impl * = " << ::hex::lower_from((::iptr)((::windows::interaction_impl *)this)->GetParent());

      dumpcontext << "\nstyle = " << (uptr)::GetWindowLong(((::windows::interaction_impl *)this)->get_handle(), GWL_STYLE);
      if (::GetWindowLong(((::windows::interaction_impl *)this)->get_handle(), GWL_STYLE) & WS_CHILD)
         dumpcontext << "\nid = " << __get_dialog_control_id(((::windows::interaction_impl *)this)->get_handle());

      dumpcontext << "\n";
   }


   void interaction_impl::on_set_parent(::user::interaction * pinteraction)
   {

   }


   bool interaction_impl::destroy_impl_only()
   {


      return ::user::interaction_impl::destroy_impl_only();

   }


   bool interaction_impl::DestroyWindow()
   {

      return ::user::interaction_impl::DestroyWindow();

   }


   void interaction_impl::destroy_window()
   {

      return ::user::interaction_impl::destroy_window();

   }




   WNDPROC* interaction_impl::GetSuperWndProcAddr()
   {

      // Note: it is no longer necessary to override GetSuperWndProcAddr
      //  for each control class with a different WNDCLASS.
      //  This implementation now uses instance data, such that the previous
      //  WNDPROC can be anything.

      return &m_pfnSuper;

   }


   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

   }


   i32 interaction_impl::GetChildByIdText(i32 nID, string & rString) const
   {

      ASSERT(::is_window(((::windows::interaction_impl *)this)->get_handle()));

      rString = "";    // is_empty without deallocating

      oswindow oswindow = ::GetDlgItem(((::windows::interaction_impl *)this)->get_handle(), nID);

      if (oswindow != nullptr)
      {

         i32 nLen = ::GetWindowTextLength(oswindow);
         wstring wstr;

         ::GetWindowTextW(oswindow, wstr.get_string_buffer(nLen), nLen + 1);

         wstr.release_string_buffer();

         rString = wstr;

      }

      return (i32)rString.get_length();

   }


   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* pwndpl)

   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      pwndpl->length = sizeof(WINDOWPLACEMENT);


      return ::GetWindowPlacement(get_handle(), pwndpl) != FALSE;


   }


   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* pwndpl)

   {

      sync_lock sl(m_puserinteraction->mutex());

      ASSERT(::is_window(get_handle()));

      ((WINDOWPLACEMENT*)pwndpl)->length = sizeof(WINDOWPLACEMENT);


      return ::SetWindowPlacement(get_handle(), pwndpl) != FALSE;


   }


   ///////////////////////////////////////////////////////////////////////////////
   //// interaction_impl will delegate owner draw messages to self drawing controls

   //// Drawing: for all 4 control types
   //void interaction_impl::OnDrawItem(i32 nIDCtl, LPDRAWITEMSTRUCT pDrawItemStruct)

   //{

   //   // reflect notification to child interaction_impl control
   //   //      if (ReflectMessage(pDrawItemStruct->hwndItem))

   //   //       return;     // eat it

   //   // not handled - do default
   //   // Default();
   //}

   //// Drawing: for all 4 control types
   //i32 interaction_impl::OnCompareItem(i32 nIDCtl, LPCOMPAREITEMSTRUCT pCompareItemStruct)

   //{
   //   // reflect notification to child interaction_impl control
   //   //      LRESULT lResult;
   //   //      if (ReflectLastMsg(pCompareItemStruct->hwndItem, &lResult))

   //   //       return (i32)lResult;        // eat it

   //   // not handled - do default
   //   return (i32)Default();
   //}

   //void interaction_impl::OnDeleteItem(i32 nIDCtl, LPDELETEITEMSTRUCT pDeleteItemStruct)

   //{
   //   // reflect notification to child interaction_impl control
   //   //if (ReflectLastMsg(pDeleteItemStruct->hwndItem))

   //   // return;     // eat it
   //   // not handled - do default
   //   //Default();
   //}

   //bool interaction_impl::_EnableToolTips(bool bEnable, ::u32 nFlag)
   //{
   //   UNREFERENCED_PARAMETER(bEnable);
   //   UNREFERENCED_PARAMETER(nFlag);
   //   return FALSE;
   //}



   //bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return ::GetWindowInfo(((interaction_impl *)this)->get_handle(), pwi) != FALSE;
   //}

   //::user::interaction_impl * interaction_impl::GetAncestor(::u32 gaFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return  System.ui_from_handle(::GetAncestor(((interaction_impl *)this)->get_handle(), gaFlags));
   //}



   //bool interaction_impl::GetScrollBarInfo(::i32 idObject, PSCROLLBARINFO psbi) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   ASSERT(psbi != nullptr);
   //   return ::GetScrollBarInfo(((interaction_impl *)this)->get_handle(), idObject, psbi) != FALSE;
   //}

   //bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   ASSERT(pti != nullptr);
   //   return ::GetTitleBarInfo(((interaction_impl *)this)->get_handle(), pti) != FALSE;
   //}

   //bool interaction_impl::AnimateWindow(millis millis, u32 dwFlags)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   return ::AnimateWindow(get_handle(), __os(millis), dwFlags) != FALSE;
   //}

   //bool interaction_impl::FlashWindowEx(u32 dwFlags, ::u32  uCount, millis tickTimeout)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   FLASHWINFO fwi;
   //   fwi.cbSize = sizeof(fwi);
   //   fwi.hwnd = get_handle();
   //   fwi.dwFlags = dwFlags;
   //   fwi.uCount = uCount;
   //   fwi.dwTimeout = __os(tickTimeout);

   //   return ::FlashWindowEx(&fwi) != FALSE;
   //}



   //bool interaction_impl::SetLayeredWindowAttributes(color32_t crKey, byte bAlpha, u32 dwFlags)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   return ::SetLayeredWindowAttributes(get_handle(), crKey, bAlpha, dwFlags) != FALSE;
   //}

   //bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT32 *pptDst, SIZE32 *psize,
   //      ::draw2d::graphics * pDCSrc, POINT32 *pptSrc, color32_t crKey, BLENDFUNCTION *pblend, u32 dwFlags)
   //{
   //   ASSERT(::is_window(get_handle()));
   //   ::exception::throw_not_implemented();
   //   return false;
   //   /*      return ::UpdateLayeredWindow(get_handle(), WIN_HDC(pDCDst), pptDst, psize,
   //   WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != FALSE;*/
   //}


   //bool interaction_impl::GetLayeredWindowAttributes(color32_t *pcrKey, byte *pbAlpha, u32 *pdwFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return ::GetLayeredWindowAttributes(((interaction_impl *)this)->get_handle(), pcrKey, pbAlpha, (LPDWORD)pdwFlags) != FALSE;
   //}

   //bool interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics, ::u32 nFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   ::exception::throw_not_implemented();
   //   //      return ::PrintWindow(get_handle(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), nFlags) != FALSE;
   //   return false;
   //}


   //LRESULT interaction_impl::OnNTCtlColor(WPARAM wParam, LPARAM lParam)
   //{
   //   // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
   //   __CTLCOLOR ctl;
   //   ctl.hDC = (HDC)wParam;
   //   ctl.oswindow = (oswindow)lParam;
   //   return 0;
   //}

   ///////////////////////////////////////////////////////////////////////////////
   //// interaction_impl extensions for help support

   //void interaction_impl::WinHelp(uptr dwData, ::u32 nCmd)
   //{
   //   UNREFERENCED_PARAMETER(dwData);
   //   UNREFERENCED_PARAMETER(nCmd);
   //   ::exception::throw_not_implemented();

   //   /*      application* pApp = &System;
   //   ASSERT_VALID(pApp);
   //   ASSERT(pApp->m_pszHelpFilePath != nullptr);
   //   ASSERT(pApp->m_eHelpType == afxWinHelp);

   //   wait_cursor wait(get_object());

   //   PrepareForHelp();

   //   // need to use top level parent (for the case where get_handle() is in DLL)
   //   __pointer(::user::interaction) pwindow = EnsureTopLevelParent();

   //   TRACE(trace_category_appmsg, trace_level_warning, "WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

   //   // finally, run the Windows Help engine
   //   /* trans   if (!::WinHelp((pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
   //   {
   //   // linux System.message_box(__IDP_FAILED_TO_LAUNCH_HELP);
   //   System.message_box("Failed to launch help");
   //   }*/
   //}

   ////void interaction_impl::HtmlHelp(uptr dwData, ::u32 nCmd)
   ////{
   //// ::exception::throw_not_implemented();
   ///*
   //application* pApp = &System;
   //ASSERT_VALID(pApp);
   //ASSERT(pApp->m_pszHelpFilePath != nullptr);
   //// to call HtmlHelp the m_fUseHtmlHelp must be set in
   //// the application's constructor
   //ASSERT(pApp->m_eHelpType == afxHTMLHelp);

   //wait_cursor wait(get_object());

   //PrepareForHelp();

   //// need to use top level parent (for the case where get_handle() is in DLL)
   //__pointer(::user::interaction) pwindow = EnsureTopLevelParent();

   //TRACE(trace_category_appmsg, trace_level_warning, "HtmlHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

   //// run the HTML Help engine
   ///* trans   if (!::aura::HtmlHelp((pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
   //{
   //// linux System.message_box(__IDP_FAILED_TO_LAUNCH_HELP);
   //System.message_box("Failed to launch help");
   //}*/
   ////}

   //void interaction_impl::PrepareForHelp()
   //{

   //   __pointer(::user::interaction) pFrameWnd = m_puserinteraction;

   //   if (pFrameWnd.is_set())
   //   {

   //      // frame_window windows should be allowed to exit help mode first

   //      pFrameWnd->ExitHelpMode();

   //   }

   //   // cancel any tracking modes
   //   send_message(WM_CANCELMODE);
   //   send_message_to_descendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

   //   // need to use top level parent (for the case where get_handle() is in DLL)
   //   __pointer(::user::interaction) pwindow = EnsureTopLevel();
   //   (pwindow.m_p)->send_message(WM_CANCELMODE);
   //   (pwindow.m_p)->send_message_to_descendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

   //   // attempt to cancel capture
   //   oswindow oswindow_Capture = ::GetCapture();
   //   if (oswindow_Capture != nullptr)
   //      ::SendMessage(oswindow_Capture, WM_CANCELMODE, 0, 0);
   //}


   //void interaction_impl::WinHelpInternal(uptr dwData, ::u32 nCmd)
   //{
   //   UNREFERENCED_PARAMETER(dwData);
   //   UNREFERENCED_PARAMETER(nCmd);
   //   ::exception::throw_not_implemented();
   //   /*
   //   application* pApp = &System;
   //   ASSERT_VALID(pApp);
   //   if (pApp->m_eHelpType == afxHTMLHelp)
   //   {
   //   // translate from WinHelp commands and data to to HtmlHelp
   //   ASSERT((nCmd == HELP_CONTEXT) || (nCmd == HELP_CONTENTS) || (nCmd == HELP_FINDER));
   //   if (nCmd == HELP_CONTEXT)
   //   nCmd = HH_HELP_CONTEXT;
   //   else if (nCmd == HELP_CONTENTS)
   //   nCmd = HH_DISPLAY_TOC;
   //   else if (nCmd == HELP_FINDER)
   //   nCmd = HH_HELP_FINDER;
   //   HtmlHelp(dwData, nCmd);
   //   }
   //   else
   //   WinHelp(dwData, nCmd);*/
   //}



   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      channel::route_command_message(pcommand);

      if (pcommand->m_bRet)
         return;

      channel * pcmdtarget = dynamic_cast <channel *> (this);

      pcmdtarget->channel::route_command_message(pcommand);

   }




   bool interaction_impl::OnCommand(::message::base * pbase)
   {
      UNREFERENCED_PARAMETER(pbase);
      return FALSE;
   }


   bool interaction_impl::OnNotify(::message::base * pbase)
   {

      ASSERT(pbase != nullptr);
      NMHDR* pNMHDR = pbase->m_lparam.cast < NMHDR>();
      oswindow oswindow_Ctrl = pNMHDR->hwndFrom;

      // get the child ID from the interaction_impl itself
      //      uptr nID = __get_dialog_control_id(oswindow_Ctrl);
      //      i32 nCode = pNMHDR->code;

      ASSERT(oswindow_Ctrl != nullptr);
      ASSERT(::is_window(oswindow_Ctrl));

      //      if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
      //       return true;        // locked out - ignore control notification

      // reflect notification to child interaction_impl control
      if (ReflectMessage(oswindow_Ctrl, pbase))
         return true;        // eaten by child

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

      __pointer(::user::interaction)pWndTopLevel = EnsureTopLevel();

      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
   }

   void interaction_impl::ActivateTopParent()
   {
      // special activate logic for floating toolbars and palettes
      auto pActiveWnd = GetForegroundWindow();
      if (!pActiveWnd || !((pActiveWnd)->get_handle() == get_handle() || ::IsChild((pActiveWnd)->get_handle(), get_handle())))
      {
         // clicking on floating frame when it does not have
         // focus itself -- activate the toplevel frame instead.
         EnsureTopLevel()->SetForegroundWindow();
      }

   }


   //void interaction_impl::message_box(const char * pszText, const char * pszCaption, const ::e_message_box & emessagebox, ::callback const function_arg & function)
   //{
   //   
   //   if (pszCaption == nullptr)
   //   {

   //      pszCaption = Application.m_strAppName;

   //   }

   //   ::os_message_box(get_handle(), pszText, pszCaption, uFlags, function);

   //}


   i32 interaction_impl::SetScrollPos(i32 nBar, i32 nPos, bool bRedraw)
   {

      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);

   }


   i32 interaction_impl::GetScrollPos(i32 nBar) const
   {
      return ::GetScrollPos(((::windows::interaction_impl *)this)->get_handle(), nBar);
   }

   void interaction_impl::SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos, bool bRedraw)
   {
      ::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
   }

   void interaction_impl::GetScrollRange(i32 nBar, LPINT pMinPos, LPINT lpMaxPos) const

   {
      ::GetScrollRange(((::windows::interaction_impl *)this)->get_handle(), nBar, pMinPos, lpMaxPos);

   }

// Turn on/off non-control scrollbars
//   for WS_?SCROLL scrollbars - show/hide them
//   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(i32 nBar, bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar, bEnable);
   }

   bool interaction_impl::SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, bool bRedraw)

   {
      ASSERT(pScrollInfo != nullptr);


      oswindow oswindow = get_handle();
      pScrollInfo->cbSize = sizeof(*pScrollInfo);

      ::SetScrollInfo(oswindow, nBar, pScrollInfo, bRedraw);

      return true;
   }

   bool interaction_impl::GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, ::u32 nMask)

   {
      UNREFERENCED_PARAMETER(nMask);
      ASSERT(pScrollInfo != nullptr);


      oswindow oswindow = get_handle();
      return ::GetScrollInfo(oswindow, nBar, pScrollInfo) != FALSE;

   }

   i32 interaction_impl::GetScrollLimit(i32 nBar)
   {
      i32 nMin, nMax;
      GetScrollRange(nBar, &nMin, &nMax);
      SCROLLINFO info;
      if (GetScrollInfo(nBar, &info, SIF_PAGE))
      {
         nMax -= __max(info.nPage - 1, 0);
      }
      return nMax;
   }

   void interaction_impl::ScrollWindow(i32 xAmount, i32 yAmount,
      LPCRECT32 rect, LPCRECT32 lpClipRect)

   {
      //ASSERT(::is_window(get_handle()));

      //if(is_window_visible() || prect != nullptr || lpClipRect != nullptr)

      //{
      //   // When visible, let Windows do the scrolling
      //   ::ScrollWindow(get_handle(),xAmount,yAmount,prect,lpClipRect);

      //}
      //else
      //{
      //   // Windows does not perform any scrolling if the interaction_impl is
      //   // not visible.  This leaves child windows unscrolled.
      //   // To ac::count for this oversight, the child windows are moved
      //   // directly instead.
      //   oswindow oswindow_Child = ::GetWindow(get_handle(),GW_CHILD);
      //   if(oswindow_Child != nullptr)
      //   {
      //      for(; oswindow_Child != nullptr;
      //            oswindow_Child = ::GetNextWindow(oswindow_Child,GW_HWNDNEXT))
      //      {
      //         ::rect rect;
      //         ::get_window_rect(oswindow_Child,&rect);
      //         _001ScreenToClient(&rect);
      //         ::set_window_pos(oswindow_Child,nullptr,rect.left + xAmount,rect.top + yAmount,0,0,SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
      //      }
      //   }
      //}

   }


   void interaction_impl::CalcWindowRect(RECT32 * pClientRect, ::u32 nAdjustType)
   {

      u32 dwExStyle = GetExStyle();
      if (nAdjustType == 0)
         dwExStyle &= ~WS_EX_CLIENTEDGE;
      ::AdjustWindowRectEx(pClientRect, GetStyle(), FALSE, dwExStyle);

   }


   bool interaction_impl::HandleFloatingSysCommand(::u32 nID, LPARAM lParam)
   {

      __pointer(::user::interaction) pParent = GetTopLevel();

      switch (nID & 0xfff0)
      {
      case SC_PREVWINDOW:
      case SC_NEXTWINDOW:
         if (LOWORD(lParam) == VK_F6 && pParent)
         {
            pParent->SetFocus();
            return true;
         }
         break;

      case SC_CLOSE:
      case SC_KEYMENU:
         // Check lParam.  If it is 0L, then the ::account::user may have done
         // an Alt+Tab, so just ignore it.  This breaks the ability to
         // just press the Alt-key and have the first menu selected,
         // but this is minor compared to what happens in the Alt+Tab
         // case.
         if ((nID & 0xfff0) == SC_CLOSE || lParam != 0L)
         {
            if (pParent)
            {
               // Sending the above WM_SYSCOMMAND may destroy the cast,
               // so we have to be careful about restoring activation
               // and focus after sending it.
               oswindow oswindow_Save = get_handle();
               oswindow oswindow_Focus = ::GetFocus();
               pParent->SetActiveWindow();
               pParent->send_message(WM_SYSCOMMAND, nID, lParam);

               // be very careful here...
               if (::is_window(oswindow_Save))
                  ::set_active_window(oswindow_Save);
               if (::is_window(oswindow_Focus))
                  ::set_focus(oswindow_Focus);
            }
         }
         return true;
      }
      return false;
   }

   bool interaction_impl::ReflectMessage(oswindow oswindow_Child, ::message::base * pbase)
   {

      // check if in permanent map, if it is reflect it (could be OLE control)
      auto pwindow = System.ui_from_handle(oswindow_Child);
      ASSERT(!pwindow || (pwindow)->get_handle() == oswindow_Child);
      if (!pwindow)
      {
         return FALSE;
      }

      // only OLE controls and permanent windows will get reflected msgs
      ASSERT(pwindow);
      return (pwindow)->OnChildNotify(pbase);
   }

   bool interaction_impl::OnChildNotify(::message::base * pbase)
   {

      return ReflectChildNotify(pbase);
   }

   bool interaction_impl::ReflectChildNotify(::message::base * pbase)
   {

      // Note: reflected messages are send directly to interaction_impl::OnWndMsg
      //  and interaction_impl::_001OnCommand for speed and because these messages are not
      //  routed by normal _001OnCommand routing (they are only dispatched)

      ::u32 message;

      message = ::message::translate_to_os_message(pbase->m_id);

      switch (message)
      {
      // normal messages (just wParam, lParam through OnWndMsg)
      case e_message_hscroll:
      case e_message_vscroll:
      case WM_PARENTNOTIFY:
      case WM_DRAWITEM:
      case e_message_measure_item:
      case WM_DELETEITEM:
      case WM_VKEYTOITEM:
      case WM_CHARTOITEM:
      case WM_COMPAREITEM:
         // reflect the message through the message map as WM_REFLECT_BASE+uMsg
         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wParam, lParam, pResult);
         return FALSE;

      // special case for e_message_command
      case e_message_command:
      {
         // reflect the message through the message map as OCM_COMMAND
         __keep(pbase->m_bReflect, true);

         if (interaction_impl::OnCommand(pbase))
         {
            pbase->m_bRet = true;
            return true;
         }
      }
      break;

      // special case for WM_NOTIFY
      case WM_NOTIFY:
      {
         // reflect the message through the message map as OCM_NOTIFY
         NMHDR* pNMHDR = pbase->m_lparam.cast < NMHDR >();
         //            i32 nCode = pNMHDR->code;
         //            __NOTIFY notify;
         //          notify.pResult = pResult;
         //        notify.pNMHDR = pNMHDR;
         // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
      }

      // other special cases (WM_CTLCOLOR family)
      default:
         if (message >= WM_CTLCOLORMSGBOX && message <= WM_CTLCOLORSTATIC)
         {
            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
            /*__CTLCOLOR ctl;
            ctl.hDC = (HDC)wParam;
            ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
            //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
            ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);

            // reflect the message through the message map as OCM_CTLCOLOR
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

//   void interaction_impl::OnParentNotify(const ::id & id, LPARAM lParam)
//   {
//      if ((LOWORD(message) == e_message_create || LOWORD(message) == e_message_destroy))
//      {
//         //if (ReflectMessage((oswindow) lParam))
//         // return;     // eat it
//      }
//      // not handled - do default
//      //Default();
//   }
//
////void interaction_impl::_001OnSetFocus(::message::message * pdetails)
////{
////
////   //bool bHandled;
//
////   //bHandled = FALSE;
////   //if(!bHandled)
////   //{
////   //   Default();
////   //}
//
//
//
////}
//
//
//   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wParam, LPARAM)
//   {
//
//      return 0;
//
//   }
//
//
//   void interaction_impl::OnSysColorChange()
//   {
//      ::exception::throw_not_implemented();
//
//      /*      application* pApp = &System;
//      if (pApp != nullptr && pApp->m_puiMain == this)
//      {
//      // recolor global brushes used by control bars
//      afxData.UpdateSysColors();
//      }
//
//      // forward this message to all other child windows
//      if (!(GetStyle() & WS_CHILD))
//      send_message_to_descendants(WM_SYSCOLORCHANGE, 0, 0L, TRUE, TRUE);
//
//      Default();*/
//   }
//
//   bool gen_GotScrollLines;
//
//   void interaction_impl::OnSettingChange(::u32 uFlags, const char * pszSection)
//
//   {
//      UNUSED_ALWAYS(uFlags);
//      UNUSED_ALWAYS(pszSection);
//
//
//      // force refresh of settings that we cache
//      gen_GotScrollLines = FALSE;
//
//
//      interaction_impl::OnDisplayChange(0, 0);    // to update system metrics, etc.
//   }
//
//   void interaction_impl::OnDevModeChange(__in char * pDeviceName)
//
//   {
//      UNREFERENCED_PARAMETER(pDeviceName);
//
//      ::exception::throw_not_implemented();
//      /*application* pApp = &System;
//      if (pApp != nullptr && pApp->m_puiMain == this)
//      pApp->DevModeChange(pDeviceName);
//
//
//      // forward this message to all other child windows
//      if (!(GetStyle() & WS_CHILD))
//      {
//      const MSG* pMsg = GetCurrentMessage();
//      send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam,
//      TRUE, TRUE);
//      }*/
//   }
//
//   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
//   {
//      //return //Default() != 0;
//      return false;
//   }
//
//   LRESULT interaction_impl::OnDisplayChange(WPARAM wparam, LPARAM lparam)
//
//   {
//
//      // forward this message to all other child windows
//      if (!(GetStyle() & WS_CHILD))
//      {
//         //         const MSG* pMsg = GetCurrentMessage();
//         send_message_to_descendants(e_message_display_change, wparam, lparam, TRUE, TRUE);
//
//      }
//
//      return Default();
//   }
//
//   LRESULT interaction_impl::OnDragList(WPARAM, LPARAM lParam)
//   {
//      LPDRAGLISTINFO pInfo = (LPDRAGLISTINFO)lParam;
//
//      ASSERT(pInfo != nullptr);
//
//
//      //      LRESULT lResult;
//      //if (ReflectLastMsg(pInfo->hWnd, &lResult))
//
//      //   return (i32)lResult;    // eat it
//
//      // not handled - do default
//      //return (i32)Default();
//      return 0;
//   }
//
//
   //void interaction_impl::_002OnDraw(::image * pimage)
   //{

   //   ::exception::throw_not_implemented();

   //}


   void interaction_impl::present()
   {

      _001UpdateWindow();

   }


   //void interaction_impl::defer_start_prodevian()
   //{


   //   ::user::interaction_impl::defer_start_prodevian();


   //}


   void interaction_impl::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);


      {

         DEVMODE dm;

         if (EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm))
         {

            set_config_fps(dm.dmDisplayFrequency);

         }

      }

      default_message_handler(pmessage);

      if (m_puserinteraction)
      {

         if (m_puserinteraction->is_message_only_window() || m_puserinteraction.cast <::user::system_interaction_impl >())
         {

            TRACE("good : opt out!");

         }

         if (m_puserinteraction->m_bUserPrimitiveOk)
         {

            pcreate->m_lresult = 0;

         }

      }

   }


   BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam);


   BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam)
   {

      user::oswindow_array * poswindowa = (user::oswindow_array *) lParam;

      poswindowa->add(oswindow);

      return TRUE;

   }

   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   {
      EnumWindows(GetAppsEnumWindowsProc, (LPARAM)&wnda);
   }


   class print_window :
      virtual public ::object
   {
   public:


      manual_reset_event m_event;
      oswindow m_oswindow;
      HDC m_hdc;


      print_window(::object * pobject, oswindow oswindow, HDC hdc, millis tickTimeout) :
         ::object(pobject)
      {

         m_oswindow = oswindow;

         m_hdc = hdc;

         start();

         if (m_event.wait(tickTimeout).timeout())
         {

            TRACE("print_window::time_out");

         }

      }


      virtual ::e_status     run() override
      {

         try
         {

            ::PrintWindow(m_oswindow, m_hdc, 0);

         }
         catch (...)
         {

         }

         m_event.set_event();

         return ::success;

      }

   };

   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

   }


   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {

      //HideCaret();

      //PAINTSTRUCT ps;
      //HDC hdc1 = BeginPaint(m_oswindow, &ps);
      //// TODO: Add any drawing code that uses hdc here...
      //EndPaint(m_oswindow, &ps);

      //return
      //   ;
      if (GetExStyle() & WS_EX_LAYERED)
      {


         return;

      }

      SCAST_PTR(::message::base, pbase, pmessage);

      ::rect rectWindow;

      m_puserinteraction->layout().design().screen_rect(rectWindow);

      PAINTSTRUCT paint;

      __memset(&paint, 0, sizeof(paint));

      HDC hdc = ::BeginPaint(get_handle(), &paint);

      ::SelectClipRgn(hdc, nullptr);

      ::rect rectPaint;

      ::rect rectUpdate;

      rectPaint = paint.rcPaint;

      if (rectPaint.is_null() || (GetExStyle() & WS_EX_LAYERED))
      {

         rectUpdate = rectWindow;

         rectPaint = rectWindow;

         m_puserinteraction->_001ScreenToClient(rectPaint, ::user::e_layout_design);

      }
      else
      {

         rectUpdate = rectPaint;

      }

      if (m_pgraphics.is_null())
      {

         update_graphics_resources();

      }

      __pointer(::windows::buffer) pbuffer = m_pgraphics;

      ASSERT(pbuffer.is_set());

      single_lock sl(pbuffer->mutex());

      auto & buffer = pbuffer->m_osbuffera[!pbuffer->m_iCurrentBuffer];

      ::BitBlt(hdc, rectUpdate.left, rectUpdate.top, rectUpdate.width(), rectUpdate.height(), buffer.m_hdc, 0, 0, SRCCOPY);

      //if (m_spgraphics.is_set())
      //{

      //   ::draw2d::graphics_pointer & pgraphics = m_spgraphics->on_begin_draw();

      //   if (pgraphics != nullptr)
      //   {

      //      try
      //      {

      //         _001Print(pgraphics);

      //      }
      //      catch (...)
      //      {


      //      }

      //      ::draw2d::graphics_pointer g(e_create);

      //      try
      //      {

      //         if (pgraphics != nullptr && g->attach_hdc(hdc))
      //         {

      //            pgraphics->SetViewportOrg(0, 0);

      //            g->BitBlt(rectPaint.left, rectPaint.top, rectPaint.width(), rectPaint.height(), pgraphics, rectUpdate.left, rectUpdate.top);

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}

      ::EndPaint(get_handle(), &paint);

      pmessage->m_bRet = true;

      pbase->m_lresult = 0;

      //ShowCaret();

   }


   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {

      //      if(m_pimage->is_null())
      //       m_pimage->create(this);

      //m_pimage->print_window(this,pmessage);

      //m_spimageBuffer.print_window(this, pmessage);

   }



   bool interaction_impl::subclass_window(oswindow oswindow)
   {

      if (!attach(oswindow))
         return FALSE;

      // allow any other subclassing to occur
      pre_subclass_window();

      m_pfnSuper = (WNDPROC)::GetWindowLongPtr(oswindow, GWLP_WNDPROC);

      WNDPROC * plpfn = GetSuperWndProcAddr();

      WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(oswindow, GWLP_WNDPROC, (iptr)windows_user_interaction_impl_get_window_procedure());

      ASSERT(oldWndProc != windows_user_interaction_impl_get_window_procedure());

      if (*plpfn == nullptr)
      {

         *plpfn = oldWndProc;   // the first control of that type created

      }


#ifdef __DEBUG

      else if (*plpfn != oldWndProc)
      {

         TRACE(trace_category_appmsg, trace_level_warning, "point: Trying to use subclass_window with incorrect interaction_impl\n");
         TRACE(trace_category_appmsg, trace_level_warning, "\tderived class.\n");
         TRACE(trace_category_appmsg, trace_level_warning, "\toswindow_ = $%08X (nIDC=$%08X) is not a %hs.\n", (::u32)(uptr)oswindow, __get_dialog_control_id(oswindow), typeid(*this).name());

         ASSERT(FALSE);

         // undo the subclassing if continuing after assert

         ::SetWindowLongPtr(oswindow, GWLP_WNDPROC, (iptr)oldWndProc);

      }

#endif //__DEBUG

      message::size size;

      _001OnSize(&size);

      return true;

   }


   bool interaction_impl::SubclassDlgItem(::u32 nID, ::user::interaction_impl * pParent)
   {

      ASSERT(pParent);

      ASSERT(::is_window((pParent)->get_handle()));

      // check for normal dialog control first
      oswindow oswindow_Control = ::GetDlgItem((pParent)->get_handle(), nID);
      if (oswindow_Control != nullptr)
         return subclass_window(oswindow_Control);


      return false;   // control not found
   }


   oswindow interaction_impl::unsubclass_window()
   {
      //ASSERT(::is_window(get_handle()));

      if (!_is_window())
         return nullptr;

      // set WNDPROC back to original value
      WNDPROC* plpfn = GetSuperWndProcAddr();

      ::SetWindowLongPtr(get_handle(), GWLP_WNDPROC, (iptr)*plpfn);

      *plpfn = nullptr;


      // and detach the oswindow from the interaction_impl object
      return detach();
   }


   /*

   bool interaction_impl::IsChild(const ::user::interaction * pwindow) const
   {

   ASSERT(::is_window(get_handle()));

   if(pwindow->get_handle() == nullptr)
   {
   return ::user::primitive::IsChild(pwindow);
   }
   else
   {
   return ::IsChild(get_handle(),pwindow->get_handle()) != FALSE;
   }

   }

   */


   bool interaction_impl::_is_window() const
   {

      if (!m_bUserPrimitiveOk)
      {

         return false;

      }

      if (m_puserinteraction == nullptr)
      {

         return false;

      }

      if (!::is_window(get_handle()))
      {

         return false;

      }

      return true;

   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void interaction_impl::rects_from_os()
   {

      //::rect rectClient;

      //::GetClientRect(m_oswindow, rectClient);

      //::rect rectScreen;

      //::GetWindowRect(m_oswindow, rectScreen);

      //if (::IsIconic(m_oswindow))
      //{

      //   INFO("interaction_impl::rects_from_os window is iconic");

      //}
      //else
      //{

      //   m_puserinteraction->m_pointScreen = rectScreen.origin();

      //   m_puserinteraction->m_size = rectScreen.size();

      //}

      //if (rectClient.size() != m_puserinteraction->m_size)
      //{

      //   TRACE("ATTENTION!! Client Size <> Window Size");

      //}


      ////m_puserinteraction->m_sizeScreen = rectScreen.size();

      ////m_puserinteraction->m_pointScreenClient.x = 0;

      ////m_puserinteraction->m_pointScreenClient.y = 0;

      ////::ScreenToClient(m_oswindow, m_puserinteraction->m_pointScreenClient);

      ////HWND hwndParent = ::GetParent(m_oswindow);

      ////if (hwndParent != NULL)
      ////{

      ////   m_puserinteraction->m_pointParentClient.x = 0;

      ////   m_puserinteraction->m_pointParentClient.y = 0;

      ////   ::ClientToScreen(m_oswindow, m_puserinteraction->m_pointParentClient);

      ////   ::ScreenToClient(hwndParent, m_puserinteraction->m_pointParentClient);

      ////}
      ////else
      ////{

      ////   m_puserinteraction->m_pointParentClient = m_puserinteraction.m_pointScreenWindow;

      ////}

      ////m_puserinteraction->m_pointClient = m_puserinteraction.m_pointScreenWindow;

      ////m_puserinteraction->m_pointClient -= m_puserinteraction.m_pointScreenClient;

   }


   //pointd interaction_impl::client_screen_top_left()
   //{

   //   ::point point;

   //   ::ClientToScreen(m_oswindow, &point);

   //   return pointd(point.x, point.y);

   //}


   bool interaction_impl::window_rect_from_os(RECT32 * prect)
   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      ::rect rectWindow;

      //if (!(GetExStyle() & WS_EX_LAYERED))
      //{

      //   ::GetWindowRect(m_oswindow, rectWindow);

      //   m_puserinteraction->m_pointParentClientRequest = rectWindow.origin();

      //   m_puserinteraction->m_sizeClientRequest = rectWindow.size();

      //}
      //else
      //{

      //   ::set_rect_point_size(&rectWindow, m_puserinteraction->m_pointParentClientRequest, m_puserinteraction.m_sizeClientRequest);

      //}

      //*prect = rectWindow;

      //if (GetParent() != nullptr)
      //{

      //   GetParent()->_001ClientToScreen(prect);

      //}

      return true;

   }


   bool interaction_impl::client_rect_from_os(RECT32 * prect)
   {

      //oswindow handle = get_handle();

      //if (!::is_window(get_handle()))
      //{

      //   return false;

      //}

      //::rect rect32;

      //if (!(GetExStyle() & WS_EX_LAYERED))
      //{

      //   if (!::GetWindowRect(get_handle(), rect32))
      //   {

      //      return false;

      //   }

      //   if (GetParent() != nullptr)
      //   {

      //      GetParent()->_001ScreenToClient(rect32);

      //   }

      //   //::copy(m_puserinteraction->m_rectParentClient, rect32);

      //}

      //rect32 = m_puserinteraction->m_rectParentClient;

      //rect32.offset(-rect32.top_left());

      //::copy(prect, rect32);

      return true;

   }


   void interaction_impl::sketch_prepare_window_minimize(::e_activation eactivation)
   {

      primitive_impl::sketch_prepare_window_minimize(eactivation);

   }


   void interaction_impl::sketch_prepare_window_maximize()
   {

      primitive_impl::sketch_prepare_window_maximize();

   }


   void interaction_impl::sketch_prepare_window_full_screen(const ::rect & rectHint)
   {

      primitive_impl::sketch_prepare_window_full_screen(rectHint);

   }


   void interaction_impl::sketch_prepare_window_restore(edisplay edisplay)
   {

      primitive_impl::sketch_prepare_window_restore(edisplay);

   }


   bool interaction_impl::display(::e_display edisplay)
   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl::node_is_iconic()
   {

      if (GetExStyle() & WS_EX_LAYERED)
      {

         return ::user::interaction_impl::node_is_iconic();

      }
      else
      {

         if (!::is_window(get_handle()))
         {

            return false;

         }

         return ::IsIconic(get_handle()) != FALSE;

      }

   }


   bool interaction_impl::node_is_zoomed()
   {

      return ::user::interaction_impl::node_is_zoomed();

   }


   ::user::interaction * interaction_impl::GetParent() const
   {

      if (!::is_window(get_handle()))
         return nullptr;

      if (get_handle() == nullptr)
         return nullptr;

      HWND hwndParent = ::GetParent(get_handle());

      if (hwndParent == nullptr)
         return nullptr;

      return System.ui_from_handle(hwndParent);

   }


   ::user::interaction * interaction_impl::SetParent(::user::interaction * pWndNewParent)
   {

      ASSERT(::is_window(get_handle()));

      return System.ui_from_handle(::SetParent(get_handle(), pWndNewParent->get_handle()));

   }

   ::user::interaction * interaction_impl::GetOwner() const
   {

      if (!::is_window(get_handle()))
         return nullptr;

      if (get_handle() == nullptr)
         return nullptr;

      HWND hwndParent = ::GetWindow(get_handle(), GW_OWNER);

      if (hwndParent == nullptr)
         return GetParent();

      return System.ui_from_handle(hwndParent);
   }

   ::user::interaction * interaction_impl::SetOwner(::user::interaction * pWndNewParent)
   {

      return nullptr;

   }



   ::i32 interaction_impl::get_window_long(i32 nIndex) const
   {
      return ::GetWindowLong(get_handle(), nIndex);
   }

   ::i32 interaction_impl::set_window_long(i32 nIndex, ::i32 lValue)
   {
      return ::SetWindowLong(get_handle(), nIndex, lValue);
   }


   iptr interaction_impl::get_window_long_ptr(i32 nIndex) const
   {

      return ::GetWindowLongPtr(get_handle(), nIndex);

   }


   iptr interaction_impl::set_window_long_ptr(i32 nIndex, iptr lValue)
   {

      return ::SetWindowLongPtr(get_handle(), nIndex, lValue);

   }


// interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const interaction_impl& wnd) const
   {

      return (((interaction_impl *)&wnd)->get_handle()) == ((interaction_impl *)this)->get_handle();

   }


   bool interaction_impl::operator!=(const interaction_impl& wnd) const
   {

      return (((interaction_impl *)&wnd)->get_handle()) != ((interaction_impl *)this)->get_handle();

   }


   u32 interaction_impl::GetStyle() const
   {

      if (!::is_window(get_handle()))
         return 0;

      return (u32)::GetWindowLong(get_handle(), GWL_STYLE);

   }


   u32 interaction_impl::GetExStyle() const
   {

      if (!::is_window(get_handle()))
         return 0;

      return (u32)::GetWindowLong(get_handle(), GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   {

      if (!::is_window(get_handle()))
         return false;

      return ModifyStyle(get_handle(), dwRemove, dwAdd, nFlags);

   }


   bool interaction_impl::ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   {

      if (!::is_window(get_handle()))
         return false;

      return ModifyStyleEx(get_handle(), dwRemove, dwAdd, nFlags);

   }


   LRESULT interaction_impl::send_message(const ::id & id, WPARAM wParam, lparam lParam)
   {

      return ::SendMessage(get_handle(), id.umessage(), wParam, lParam);

   }


   bool interaction_impl::post_message(const ::id & id, WPARAM wParam, lparam lParam)
   {

      oswindow oswindow = get_handle();

      ::u32 message = id.umessage();

      WPARAM wparam = wParam;

      LPARAM lparam = lParam;

      return ::PostMessage(oswindow, message, wparam, lparam) != FALSE;

   }


   bool interaction_impl::DragDetect(const ::point & point) const
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return ::DragDetect(((interaction_impl *)this)->get_handle(), point) != FALSE;

   }


   void interaction_impl::set_window_text(const char * pszString)
   {

      DWORD_PTR lresult = 0;

      m_puserinteraction->m_strWindowText = pszString;

      wstring wstrText(m_puserinteraction->m_strWindowText);

      const unichar * pwszText = wstrText;

      if (!::SendMessageTimeoutW(get_handle(), WM_SETTEXT, 0, (LPARAM)pwszText, SMTO_ABORTIFHUNG, 500, &lresult))
      {

         return;

      }

      string str;

      get_window_text(str);

   }



   strsize interaction_impl::get_window_text(char * pszString, strsize nMaxCount)

   {

      string str;

      get_window_text(str);

      ansi_count_copy(pszString, str, (size_t) min(nMaxCount, str.get_length()));


      return str.get_length();

   }

   void interaction_impl::get_window_text(string & str)
   {

      DWORD_PTR lresult = 0;

      if (!::SendMessageTimeoutW(get_handle(), WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG, 90, &lresult))
         return;

      wstring wstr;

      if (!::SendMessageTimeoutW(get_handle(), WM_GETTEXT, (LPARAM)wstr.get_string_buffer(lresult + 1), lresult + 1, SMTO_ABORTIFHUNG, 90, &lresult))
         return;

      str = wstr;

   }

   strsize interaction_impl::get_window_text_length()
   {

      ASSERT(::is_window(get_handle()));

      return ::GetWindowTextLength(get_handle());

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {
      ASSERT(::is_window(get_handle()));
      ::DragAcceptFiles(get_handle(), bAccept);
   }


   ::u32 interaction_impl::ArrangeIconicWindows()
   {

      ASSERT(::is_window(get_handle()));
      return ::ArrangeIconicWindows(get_handle());

   }


//i32 interaction_impl::SetWindowRgn(HRGN hRgn,bool bRedraw)
//{

//   //ASSERT(::is_window(get_handle())); return ::SetWindowRgn(get_handle(),hRgn,bRedraw);

//}


//i32 interaction_impl::GetWindowRgn(HRGN hRgn)
//{

//   //ASSERT(::is_window(get_handle()) && hRgn != nullptr); return ::GetWindowRgn(get_handle(),hRgn);

//}


   //void interaction_impl::bring_to_top(::e_display edisplay)
   //{

   //   if (GetParent() == nullptr)
   //   {

   //      // place the interaction_impl on top except for certain nCmdShow

   //      if (is_visible(edisplay)
   //         && edisplay_command(edisplay) != e_display_iconic &&
   //         !no_activate(edisplay))
   //      {

   //         oswindow oswindow = get_handle();

   //         oswindow = ::GetLastActivePopup(oswindow);

   //         ::user::interaction * pinteraction = System.ui_from_handle(oswindow);

   //         if (pinteraction == nullptr)
   //            BringWindowToTop();
   //         else
   //            pinteraction->BringWindowToTop();

   //      }

   //   }

   //}

   // MSDN
   // Brings the specified window to the top of the Z order.
   // If the window is a top-level window, it is activated.
   // If the window is a child window, the top-level parent
   // window associated with the child window is activated.
   //
   // Use the BringWindowToTop function to uncover any window
   // that is partially or completely obscured by other windows.
   // Calling this function is similar to calling the set_window_pos
   // function to change a window's position in the Z order.
   // BringWindowToTop does not make a window a top-level window.

   //bool interaction_impl::BringWindowToTop()
   //{

   //   bool bOk = ::BringWindowToTop(get_handle()) != FALSE;


   //   if (GetExStyle() & WS_EX_LAYERED)
   //   {

   //      if (!(GetExStyle() & WS_EX_TOPMOST))
   //      {

   //         ::set_window_pos(get_handle(), (HWND)zorder_top, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

   //         //::set_window_pos(get_handle(),(HWND)zorder_top,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

   //         //::set_window_pos(get_handle(),(HWND)zorder_top_most,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

   //         //::set_window_pos(get_handle(),(HWND)zorder_top,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

   //      }

   //   }

   //   return bOk;

   //}

   void interaction_impl::MapWindowPoints(::user::interaction_impl * pwndTo, POINT32 * pPoint, ::u32 nCount)

   {
      ASSERT(::is_window(get_handle()));
      ::MapWindowPoints(get_handle(), pwndTo->get_handle(), pPoint, nCount);

   }

   void interaction_impl::MapWindowPoints(::user::interaction_impl * pwndTo, RECT32 * prect)

   {
      ASSERT(::is_window(get_handle()));
      ::MapWindowPoints(get_handle(), pwndTo->get_handle(), (POINT32 *)prect, 2);

   }



   void interaction_impl::UpdateWindow()
   {
      ::UpdateWindow(get_handle());
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      ASSERT(::is_window(get_handle()));
      ::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
   }

   bool interaction_impl::GetUpdateRect(RECT32 * prect, bool bErase)

   {
      ASSERT(::is_window(get_handle()));
      return ::GetUpdateRect(get_handle(), prect, bErase) != FALSE;

   }

   
   i32 interaction_impl::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {
   
      //ASSERT(::is_window(get_handle()));
      //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_os_data(), bErase);

      return 0;

   }


   void interaction_impl::Invalidate(bool bErase)
   {
      ASSERT(::is_window(get_handle()));
      ::InvalidateRect(get_handle(), nullptr, bErase);
   }

   void interaction_impl::InvalidateRect(LPCRECT32 rect, bool bErase)

   {
      ASSERT(::is_window(get_handle()));
      ::InvalidateRect(get_handle(), rect, bErase);

   }

   
   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {
      
      //ASSERT(::is_window(get_handle()));
      //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_os_data(), bErase);

   }


   void interaction_impl::ValidateRect(LPCRECT32 rect)

   {

      ASSERT(::is_window(get_handle()));

      ::ValidateRect(get_handle(), rect);


   }


   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {

      ASSERT(::is_window(get_handle()));

      //::ValidateRgn(get_handle(), (HRGN)pRgn->get_os_data());

   }


   void interaction_impl::on_visual_applied()
   {

      //rects_from_os();

      ::user::interaction_impl::on_visual_applied();

   }


   // void interaction_impl::window_apply_visual(const ::user::window_state & windowstate)
   // {

   //    return ::user::interaction_impl::window_apply_visual(windowstate);

   // }


   //bool interaction_impl::_is_window_visible()
   //{

   //   try
   //   {

   //      if (!::IsWindowVisible(get_handle()))
   //      {

   //         return false;

   //      }

   //      return true;

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //}


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      ASSERT(::is_window(get_handle()));

      ::ShowOwnedPopups(get_handle(), bShow);

   }




   __pointer(::draw2d::graphics) interaction_impl::GetDCEx(::draw2d::region* prgnClip, u32 flags)
   {

      ASSERT(::is_window(get_handle()));

      auto pgraphics = __create < ::draw2d::graphics > ();

      __throw(todo());

      //pgraphics->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_os_data(), flags));

      return pgraphics;


   }


   bool interaction_impl::LockWindowUpdate()
   {

      ASSERT(::is_window(get_handle()));

      return ::LockWindowUpdate(get_handle()) != FALSE;

   }

   void interaction_impl::UnlockWindowUpdate()
   {

      ASSERT(::is_window(get_handle()));

      ::LockWindowUpdate(nullptr);

   }


   bool interaction_impl::RedrawWindow(const ::rect& rectUpdate, ::draw2d::region* prgnUpdate, ::u32 flags)
   {

      if (m_bDestroyImplOnly)
      {

         return false;

      }

      if (!m_puserinteraction->is_window_visible(::user::e_layout_sketch))
      {

         return true;

      }

      if (!(GetExStyle() & WS_EX_LAYERED))
      {

         ::RedrawWindow(get_handle(), nullptr, nullptr, flags);

      }

      if (flags & RDW_UPDATENOW)
      {





         //if (GetExStyle() & WS_EX_LAYERED)
         {

            _001UpdateWindow();

            return true;

         }
         //else
         //{

         //   if (!is_window_visible() && !m_bShowFlags)
         //      return false;

         //   if (!is_window_visible())
         //   {

         //      if (m_iShowFlags & SWP_SHOWWINDOW)
         //      {

         //         display(e_display_normal);

         //      }

         //   }

         //   return ::set_need_redraw(get_handle(), pRectUpdate, prgnUpdate == nullptr ? nullptr : (HRGN)prgnUpdate->get_os_data(),

         //      flags | RDW_NOERASE | RDW_NOFRAME | RDW_INVALIDATE) != FALSE;

         //}

      }
      else
      {

         m_puserinteraction->set_need_redraw();

      }

      return true;

   }





   bool interaction_impl::EnableScrollBar(i32 nSBFlags, ::u32 nArrowFlags)
   {

      ASSERT(::is_window(get_handle()));

      return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != FALSE;

   }

   //bool interaction_impl::DrawAnimatedRects(i32 idAni, const LPRECTprcFrom, const LPRECTlprcTo)

   //{

   //   ASSERT(::is_window(get_handle()));

   //   return ::DrawAnimatedRects(get_handle(), idAni, prcFrom, lprcTo) != FALSE;


   //}

   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, const rect & prc, ::u32 uFlags)

   {

      ASSERT(::is_window(get_handle()));

      ::exception::throw_not_implemented();
      return false;
      //      return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), prc, uFlags) != FALSE;


   }


   bool interaction_impl::is_this_enabled()
   {

      return ::IsWindowEnabled(get_handle()) != FALSE;

   }


   bool interaction_impl::enable_window(bool bEnable)
   {

      return ::EnableWindow(get_handle(), bEnable) != FALSE;

   }


   ::user::interaction * interaction_impl::GetActiveWindow()
   {

      return System.ui_from_handle(::GetActiveWindow());

   }


   ::user::interaction * interaction_impl::SetActiveWindow()
   {

      if (!::is_window(get_handle()))
      {

         return nullptr;

      }

      if (!::IsWindowVisible(get_handle()))
      {

         return nullptr;

      }

      oswindow window = ::SetActiveWindow(get_handle());

      ::user::interaction * pinteraction = System.ui_from_handle(window);

      return pinteraction;

   }



   ::user::interaction * interaction_impl::GetFocus()
   {

      return System.ui_from_handle(::GetFocus());

   }


   bool interaction_impl::has_focus()
   {

      //HWND hwndFocus = ::get_focus();

      //HWND hwndThis = get_handle();

      //return hwndFocus ==  hwndThis;

      return m_bFocusImpl;

   }


   bool interaction_impl::is_active()
   {

      ithread_t ithread = 0;
      
      if (m_puserinteraction && m_puserinteraction->m_pthreadUserInteraction)
      {

         ithread = m_puserinteraction->m_pthreadUserInteraction->get_ithread();

      }

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      oswindow oswindowActive;

      if (GetGUIThreadInfo(ithread, &info))
      {

         oswindowActive = info.hwndActive;

      }
      else
      {

         oswindowActive = ::get_active_window();

      }

      if (oswindowActive == m_oswindow)
      {

         return true;

      }

      auto pinteraction = System.ui_from_handle(oswindowActive);

      if (::is_set(pinteraction))
      {

         if (pinteraction->m_pthreadUserInteraction == m_puserinteraction->m_pthreadUserInteraction)
         {

            if (pinteraction->m_ewindowflag & e_window_flag_satellite_window)
            {

               return true;

            }

         }

      }

      return false;

   }


   bool interaction_impl::SetFocus()
   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      if (!::IsWindowVisible(get_handle()))
      {

         return false;

      }

      m_puserinteraction->post_routine(__routine([this]()
      {

         HWND hwnd = ::SetFocus(get_handle());

         ::output_debug_string("::windows::interaction_impl::SetFocus ::SetFocus(" + ::hex::lower_from((iptr) hwnd) + ")");

         return ::success;

      }));

      return true;

   }


   ::user::interaction *  interaction_impl::get_desktop_window()
   {

      return System.ui_from_handle(::get_desktop_window());

   }


// helper for radio buttons
   i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton)
   {
      for (i32 nID = nIDFirstButton; nID <= nIDLastButton; nID++)
      {
         if (IsDlgButtonChecked(nID))
            return nID; // id that matched
      }
      return 0; // invalid ID
   }


   void interaction_impl::CheckDlgButton(i32 nIDButton, ::u32 nCheck)
   {

      ASSERT(::is_window(get_handle()));

      ::CheckDlgButton(get_handle(), nIDButton, nCheck);

   }


   void interaction_impl::CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton)
   {

      ASSERT(::is_window(get_handle()));

      ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);

   }


   i32 interaction_impl::DlgDirList(TCHAR * pPathSpec, i32 nIDListBox, i32 nIDStaticPath, ::u32 nFileType)

   {

      ASSERT(::is_window(get_handle()));

      return ::DlgDirList(get_handle(), pPathSpec, nIDListBox, nIDStaticPath, nFileType);


   }


   i32 interaction_impl::DlgDirListComboBox(TCHAR * pPathSpec, i32 nIDComboBox, i32 nIDStaticPath, ::u32 nFileType)

   {

      ASSERT(::is_window(get_handle()));

      return ::DlgDirListComboBox(get_handle(), pPathSpec, nIDComboBox, nIDStaticPath, nFileType);


   }


   bool interaction_impl::DlgDirSelect(TCHAR * pString, i32 nSize, i32 nIDListBox)

   {

      ASSERT(::is_window(get_handle()));

      return ::DlgDirSelectEx(get_handle(), pString, nSize, nIDListBox) != FALSE;


   }


   bool interaction_impl::DlgDirSelectComboBox(TCHAR * pString, i32 nSize, i32 nIDComboBox)

   {

      ASSERT(::is_window(get_handle()));

      return ::DlgDirSelectComboBoxEx(get_handle(), pString, nSize, nIDComboBox) != FALSE;


   }


   void interaction_impl::get_child_by_id(id id, oswindow* poswindow_) const
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      ASSERT(poswindow_ != nullptr);

      *poswindow_ = ::GetDlgItem(((interaction_impl *)this)->get_handle(), (i32)id);

   }


   ::u32 interaction_impl::GetChildByIdInt(i32 nID, BOOL * pTrans, bool bSigned) const

   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return ::GetDlgItemInt(((interaction_impl *)this)->get_handle(), nID, pTrans, bSigned);


   }


   i32 interaction_impl::GetChildByIdText(i32 nID, TCHAR * pStr, i32 nMaxCount) const

   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return ::GetDlgItemText(((interaction_impl *)this)->get_handle(), nID, pStr, nMaxCount);


   }


   //::user::interaction_impl * interaction_impl::GetNextDlgGroupItem(::user::interaction_impl * pWndCtl, bool bPrevious) const
   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return System.ui_from_handle(::GetNextDlgGroupItem(((interaction_impl *)this)->get_handle(), pWndCtl->get_handle(), bPrevious));

   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgTabItem(::user::interaction_impl * pWndCtl, bool bPrevious) const
   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return System.ui_from_handle(::GetNextDlgTabItem(((interaction_impl *)this)->get_handle(), pWndCtl->get_handle(), bPrevious));

   //}


   ::u32 interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   {
      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
      return ::IsDlgButtonChecked(((interaction_impl *)this)->get_handle(), nIDButton);
   }


   LPARAM interaction_impl::SendDlgItemMessage(i32 nID, ::u32 message, WPARAM wParam, LPARAM lParam)
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return ::SendDlgItemMessage(((interaction_impl *)this)->get_handle(), message, message, wParam, lParam);

   }


   void interaction_impl::SetDlgItemInt(i32 nID, ::u32 nValue, bool bSigned)
   {
      ASSERT(::is_window(get_handle()));
      ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);
   }
   void interaction_impl::SetDlgItemText(i32 nID, const char * pszString)

   {
      ASSERT(::is_window(get_handle()));
      ::SetDlgItemTextW(get_handle(), nID, wstring(pszString));

   }
   i32 interaction_impl::ScrollWindowEx(i32 dx, i32 dy,
      LPCRECT32 pRectScroll, LPCRECT32 lpRectClip,

                                        ::draw2d::region* prgnUpdate, RECT32 * pRectUpdate, ::u32 flags)

   {

      //ASSERT(::is_window(get_handle()));
      //return ::ScrollWindowEx(get_handle(), dx, dy, pRectScroll, lpRectClip,

      //                        (HRGN)prgnUpdate->get_os_data(), pRectUpdate, flags);

      return 0;


   }

   void interaction_impl::ShowScrollBar(::u32 nBar, bool bShow)
   {
      ASSERT(::is_window(get_handle()));
      ::ShowScrollBar(get_handle(), nBar, bShow);
   }
   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point & point)
   {
      ASSERT(::is_window(get_handle()));

      return  System.ui_from_handle(::ChildWindowFromPoint(get_handle(), point));


   }

   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point & point, ::u32 nFlags)
   {
      ASSERT(::is_window(get_handle()));

      return  System.ui_from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));


   }



   ::user::interaction * interaction_impl::get_next_window(::u32 nFlag)
   {

      if (!::is_window(get_handle()))
         return nullptr;

      return  System.ui_from_handle(::GetNextWindow(get_handle(), nFlag));

   }


   ::user::interaction * interaction_impl::GetTopWindow() const
   {

      ASSERT(::is_window(get_handle()));

      return System.ui_from_handle(::GetTopWindow(get_handle()));

   }


   ::user::interaction * interaction_impl::GetWindow(::u32 nCmd) const
   {

      ASSERT(::is_window(get_handle()));

      return System.ui_from_handle(::GetWindow(get_handle(), nCmd));

   }


   ::user::interaction * interaction_impl::GetLastActivePopup() const
   {

      ASSERT(::is_window(get_handle()));

      return System.ui_from_handle(::GetLastActivePopup(get_handle()));

   }



   //bool interaction_impl::FlashWindow(bool bInvert)
   //{

   //   ASSERT(::is_window(get_handle()));

   //   return ::FlashWindow(get_handle(), bInvert) != FALSE;

   //}

   bool interaction_impl::ChangeClipboardChain(oswindow oswindow_Next)
   {

      ASSERT(::is_window(get_handle()));

      return ::ChangeClipboardChain(get_handle(), oswindow_Next) != FALSE;

   }

   oswindow interaction_impl::SetClipboardViewer()
   {

      ASSERT(::is_window(get_handle()));

      return ::SetClipboardViewer(get_handle());

   }

   bool interaction_impl::OpenClipboard()
   {

      ASSERT(::is_window(get_handle()));

      return ::OpenClipboard(get_handle()) != FALSE;

   }

   ::user::interaction * interaction_impl::GetOpenClipboardWindow()
   {

      return System.ui_from_handle(::GetOpenClipboardWindow());

   }

   ::user::interaction * interaction_impl::GetClipboardOwner()
   {

      return System.ui_from_handle(::GetClipboardOwner());

   }

   ::user::interaction * interaction_impl::GetClipboardViewer()
   {

      return System.ui_from_handle(::GetClipboardViewer());

   }



   point interaction_impl::GetCaretPos()
   {

      ::point point;

      ::GetCaretPos((POINT32 *)&point);

      return point;

   }


   void interaction_impl::SetCaretPos(const ::point & point)
   {

      ::SetCaretPos(point.x, point.y);

   }

   void interaction_impl::HideCaret()
   {

      ::HideCaret(get_handle());

   }

   void interaction_impl::ShowCaret()
   {

      ::ShowCaret(get_handle());

   }

   bool interaction_impl::SetForegroundWindow()
   {

      return ::SetForegroundWindow(get_handle()) != FALSE;

   }

   ::user::interaction * interaction_impl::GetForegroundWindow()
   {

      return System.ui_from_handle(::GetForegroundWindow());

   }


   bool interaction_impl::SendNotifyMessage(::u32 message, WPARAM wParam, lparam lParam)
   {

      return ::SendNotifyMessage(get_handle(), message, wParam, lParam) != FALSE;

   }

// Win4
   HICON interaction_impl::SetIcon(HICON hIcon, bool bBigIcon)
   {

      return (HICON)send_message(WM_SETICON, bBigIcon, (LPARAM)hIcon);

   }

   HICON interaction_impl::GetIcon(bool bBigIcon) const
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return (HICON)const_cast <::windows::interaction_impl *> (this)->send_message(WM_GETICON, bBigIcon);

   }

   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      ::exception::throw_not_implemented();
      //      const_cast < ::windows::interaction_impl * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), (LPARAM) dwFlags);

   }

   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      ::exception::throw_not_implemented();
      //const_cast < ::windows::interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), (LPARAM) dwFlags);

   }

   bool interaction_impl::SetWindowContextHelpId(u32 dwContextHelpId)
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return ::SetWindowContextHelpId(((interaction_impl *)this)->get_handle(), dwContextHelpId) != FALSE;

   }

   u32 interaction_impl::GetWindowContextHelpId() const
   {

      ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

      return ::GetWindowContextHelpId(((interaction_impl *)this)->get_handle());

   }


// Default message map implementations
   //void interaction_impl::OnActivateApp(bool, u32)
   //{
   //   Default();
   //}
   //void interaction_impl::OnActivate(::u32, ::user::interaction_impl *, bool)
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
   //void interaction_impl::OnContextMenu(::user::interaction_impl *, point)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnCopyData(::user::interaction_impl *, COPYDATASTRUCT*)
   //{

   //   return Default() != FALSE;

   //}

   //void interaction_impl::OnEnable(bool)
   //{
   //   Default();
   //}
   //void interaction_impl::OnEndSession(bool)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   //{

   //   return Default() != FALSE;

   //}

   //void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   //{
   //   Default();
   //}
   //void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   //{
   //   Default();
   //}


   void interaction_impl::_001OnSetFocus(::message::message * pbase)
   {

      m_bFocusImpl = true;

      if (!m_bSystemCaret)
      {

         m_bSystemCaret = true;

         //::CreateCaret(m_oswindow, nullptr, 1, 1);

      }

   }


   void interaction_impl::_001OnKillFocus(::message::message * pmessage)
   {

      m_bFocusImpl = false;

      if (m_bSystemCaret)
      {

         m_bSystemCaret = false;

         ::DestroyCaret();

      }

   }


   //LRESULT interaction_impl::OnMenuChar(::u32, ::u32, ::user::menu*)
   //{

   //   return Default();

   //}


   //void interaction_impl::OnMenuSelect(::u32, ::u32, HMENU)
   //{

   //   Default();

   //}


   //void interaction_impl::OnMove(i32, i32)
   //{

   //   Default();

   //}


   //HCURSOR interaction_impl::OnQueryDragIcon()
   //{

   //   return (HCURSOR)Default();

   //}

   //bool interaction_impl::OnQueryEndSession()
   //{

   //   return Default() != FALSE;

   //}

   //bool interaction_impl::OnQueryNewPalette()
   //{

   //   return Default() != FALSE;

   //}

   //bool interaction_impl::OnQueryOpen()
   //{

   //   return Default() != FALSE;

   //}

   void interaction_impl::_001OnSetCursor(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      auto psession = Session;

      auto pcursor = psession->get_cursor();

      if (pcursor != nullptr && pcursor->m_ecursor != cursor_system)
      {

         pcursor->set_current(m_puserinteraction, psession);

      }

      pbase->m_lresult = 1;

      pbase->m_bRet = true;

   }


   //void interaction_impl::OnShowWindow(bool, ::u32)
   //{

   //   Default();

   //}


   //void interaction_impl::OnSize(::u32, i32, i32)
   //{

   //   Default();

   //}


   //void interaction_impl::OnTCard(::u32, u32)
   //{

   //   Default();

   //}


   void interaction_impl::_001OnWindowPosChanging(::message::message * pmessage)
   {

      return;


   }


   void interaction_impl::_001OnWindowPosChanged(::message::message * pmessage)
   {

      WINDOWPOS * pwindowpos = (WINDOWPOS *) pmessage->m_lparam.m_lparam;

      output_debug_string("\ninteraction_impl::_001OnWindowPosChanged");

      if (::IsIconic(get_handle()))
      {

         if (m_puserinteraction->layout().sketch().display() != ::e_display_iconic)
         {

            output_debug_string(" IsIconic or not IsIconic, thats the question interaction_impl::_001OnWindowPosChanged");

         }

      }
      else if (::IsZoomed(get_handle()))
      {

         if (m_puserinteraction->layout().window().display() != ::e_display_zoomed)
         {

            output_debug_string(" IsZoomed or not IsZoomed, thats the question interaction_impl::_001OnWindowPosChanged");

         }

      }

      
      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         return;

      }

      ::point point(pwindowpos->x, pwindowpos->y);

      bool bMove = false;

      if (m_puserinteraction->layout().sketch().origin() != point)
      {

         if (m_puserinteraction->layout().is_moving())
         {

            INFO("Window is Moving :: _001OnMove");

         }

         m_puserinteraction->layout().sketch().origin() = point;

         bMove = true;

      }

      ::size size(pwindowpos->cx, pwindowpos->cy);

      bool bSize = false;

      if (m_puserinteraction->layout().sketch().size() != size)
      {

         m_puserinteraction->layout().sketch().size() = size;

         bSize = true;

      }

      if (bMove)
      {

         m_puserinteraction->set_reposition();

         m_puserinteraction->set_need_redraw();

      }

      if (bSize)
      {

         m_puserinteraction->set_need_layout();

      }

      if (bMove || bSize)
      {

         m_puserinteraction->set_need_redraw();

      }


      pmessage->m_bRet = true;

   }


   void interaction_impl::_001OnGetMinMaxInfo(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

   }

//   void interaction_impl::OnDropFiles(HDROP)
//   {
//      Default();
//   }
//   void interaction_impl::OnPaletteIsChanging(::user::interaction_impl *)
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
//   LRESULT interaction_impl::OnNcHitTest(const point & )
//   {
//      return Default();
//   }
//   void interaction_impl::OnNcLButtonDblClk(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcLButtonDown(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcLButtonUp(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonDblClk(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonDown(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonUp(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMouseMove(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcPaint()
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonDblClk(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonDown(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonUp(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysChar(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysCommand(::u32, LPARAM)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysDeadChar(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysKeyDown(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysKeyUp(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnCompacting(::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnFontChange()
//   {
//      Default();
//   }
//   void interaction_impl::OnPaletteChanged(::user::interaction_impl *)
//   {
//      Default();
//   }
//   void interaction_impl::OnSpoolerStatus(::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnTimeChange()
//   {
//      Default();
//   }
//   void interaction_impl::OnChar(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnDeadChar(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnKeyDown(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnKeyUp(::u32, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonDblClk(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonDown(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonUp(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonDblClk(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonDown(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonUp(::u32, const point&)
//   {
//      Default();
//   }
//   i32 interaction_impl::OnMouseActivate(::user::interaction_impl *, ::u32, ::u32)
//   {
//      return (i32)Default();
//   }
//   void interaction_impl::OnMouseMove(::u32, const point&)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnMouseWheel(::u32, i16, const point&)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
//   {
//      return Default();
//   }
//   void interaction_impl::OnRButtonDblClk(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnRButtonDown(::u32, const point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnRButtonUp(::u32, const point&)
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
//   void interaction_impl::OnInitMenuPopup(::user::menu*, ::u32, bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnAskCbFormatName(__in ::u32 nMaxCount, __out_ecount_z(nMaxCount) char * lpszName)
//   {
//      (nMaxCount);
//      if (nMaxCount > 0)
//      {
//         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
//         lpszName[0] = '\0';
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
//   void interaction_impl::OnHScrollClipboard(::user::interaction_impl *, ::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnPaintClipboard(::user::interaction_impl *, HGLOBAL)
//   {
//      Default();
//   }
//   void interaction_impl::OnRenderAllFormats()
//   {
//      Default();
//   }
//   void interaction_impl::OnRenderFormat(::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnSizeClipboard(::user::interaction_impl *, HGLOBAL)
//   {
//      Default();
//   }
//   void interaction_impl::OnVScrollClipboard(::user::interaction_impl *, ::u32, ::u32)
//   {
//      Default();
//   }
//   ::u32 interaction_impl::OnGetDlgCode()
//   {
//      return (::u32)Default();
//   }
//   void interaction_impl::OnMDIActivate(bool, ::user::interaction_impl *, ::user::interaction_impl *)
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
//// Win4 support
//   void interaction_impl::OnStyleChanged(i32, LPSTYLESTRUCT)
//   {
//      Default();
//   }
//   void interaction_impl::OnStyleChanging(i32, LPSTYLESTRUCT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSizing(::u32, RECT32 *)
//   {
//      Default();
//   }
//   void interaction_impl::OnMoving(::u32, RECT32 *)
//   {
//      Default();
//   }
//   void interaction_impl::OnCaptureChanged(::user::interaction_impl *)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnDeviceChange(::u32, uptr)
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
//   void interaction_impl::OnChangeUIState(::u32, ::u32)
//   {
//      Default();
//   }
//   void interaction_impl::OnUpdateUIState(::u32, ::u32)
//   {
//      Default();
//   }
//   ::u32 interaction_impl::OnQueryUIState()
//   {
//      return (::u32)Default();
//   }

// interaction_impl dialog data support
//    void interaction_impl::do_data_exchange(CDataExchange*)
//   { } // default does nothing

// interaction_impl modality support

   void interaction_impl::BeginModalState()
   {

      ::EnableWindow(get_handle(), FALSE);

   }

   void interaction_impl::EndModalState()
   {

      ::EnableWindow(get_handle(), TRUE);

   }

// frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
   { m_nIdleFlags |= idleTitle; }
   void frame_window::DelayRecalcLayout(bool bNotify)
   { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
   bool frame_window::InModalState() const
   { return m_cModalStack != 0; }
   void frame_window::set_title(const char * pszTitle)

   { m_strTitle = pszTitle; }

   string frame_window::get_title() const
   { return m_strTitle; }
   */



   void interaction_impl::CloseWindow()
   {
      ASSERT(::is_window(get_handle()));
      ::CloseWindow(get_handle());
   }

   bool interaction_impl::OpenIcon()
   {

      ASSERT(::is_window(get_handle()));

      return ::OpenIcon(get_handle()) != FALSE;

   }

////////////////////////////////////////////////////////////////////////////
// UI related interaction_impl functions

   oswindow interaction_impl::get_safe_owner(oswindow hParent, oswindow* pWndTop)
   {
      // get interaction_impl to start with
      oswindow oswindow = hParent;
      if (oswindow == nullptr)
      {
         /* trans      __pointer(::user::frame_window) pFrame = channel::GetRoutingFrame_();
         if (pFrame != nullptr)
         oswindow = pFrame->get_handle();
         else
         oswindow = System.m_puiMain->get_handle();*/
      }

      // a popup interaction_impl cannot be owned by a child interaction_impl
      while (oswindow != nullptr && (::GetWindowLong(oswindow, GWL_STYLE) & WS_CHILD))
         oswindow = ::GetParent(oswindow);

      // determine toplevel interaction_impl to disable as well
      ::oswindow oswindow_Top = oswindow;
      ::oswindow oswindow_Temp = oswindow;
      for (;;)
      {
         if (oswindow_Temp == nullptr)
            break;
         else
            oswindow_Top = oswindow_Temp;
         oswindow_Temp = ::GetParent(oswindow_Top);
      }

      // get last active popup of first non-child that was found
      if (hParent == nullptr && oswindow != nullptr)
         oswindow = ::GetLastActivePopup(oswindow);

      // disable and store top level parent interaction_impl if specified
      if (pWndTop != nullptr)
      {
         if (oswindow_Top != nullptr && ::IsWindowEnabled(oswindow_Top) && oswindow_Top != oswindow)
         {
            *pWndTop = oswindow_Top;
            ::EnableWindow(oswindow_Top, FALSE);
         }
         else
            *pWndTop = nullptr;
      }

      return oswindow;    // return the owner as oswindow
   }


   //LRESULT CALLBACK __cbt_filter_hook(i32 code, WPARAM wParam, LPARAM lParam)
   //{

   //   if (code != HCBT_CREATEWND)
   //   {

   //      goto call_next_hook;

   //   }

   //   ASSERT(lParam != 0);

   //   ::user::create_struct * pcs = (::user::create_struct *) ((LPCBT_CREATEWND)lParam)->lpcs;

   //   ASSERT(pcs != nullptr);

   //   ::windows::interaction_impl * pwnd = thread_set("wnd_init");

   //   if (pwnd != nullptr || (!(pcs->style & WS_CHILD)))
   //   {

   //      thread_set("wnd_init") = nullptr;

   //      // Note: special check to avoid subclassing the IME interaction_impl
   //      //if (gen_DBCS)
   //      {
   //         // check for cheap CS_IME style first...
   //         if (GetClassLongW((oswindow)wParam, GCL_STYLE) & CS_IME)
   //         {

   //            goto call_next_hook;

   //         }

   //         const wchar_t * pszClassName;

   //         wchar_t szClassName[128] = {};

   //         if(uptr(pcs->lpszClass) > 0xffff)
   //         {

   //            pszClassName = pcs->lpszClass;

   //         }
   //         else
   //         {

   //            ::GlobalGetAtomNameW((ATOM)(uptr)pcs->lpszClass, szClassName, _countof(szClassName));

   //            pszClassName = szClassName;

   //         }

   //         // a little more expensive to test this way, but necessary...
   //         if (wide_find_string_case_insensitive(pszClassName, L"ime") != 0)
   //         {
   //          
   //            goto call_next_hook;

   //         }

   //      }

   //      ASSERT(wParam != 0);

   //      ::oswindow oswindow = (::oswindow) wParam;

   //      if (pwnd != nullptr)
   //      {

   //         ASSERT(oswindow_get(oswindow) == nullptr);

   //         pwnd->m_puserinteraction->m_pimpl = pwnd;

   //         pwnd->attach(oswindow);

   //         pwnd->pre_subclass_window();

   //         WNDPROC * ppwndprocSuper = pwnd->GetSuperWndProcAddr();

   //         ASSERT(ppwndprocSuper != nullptr);

   //         WNDPROC pwndprocOld = (WNDPROC)SetWindowLongPtrW(oswindow, GWLP_WNDPROC, (uptr)get_window_procedure();

   //         ASSERT(pwndprocOld != nullptr);

   //         if (pwndprocOld != get_window_procedure())
   //         {

   //            *ppwndprocSuper = pwndprocOld;

   //         }

   //      }

   //   }

   //call_next_hook:

   //   LRESULT lResult = CallNextHookEx(t_hHookOldCbtFilter, code, wParam, lParam);

   //   return lResult;

   //}


   void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
   {
      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pmessage);
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }



   void interaction_impl::_001OnTriggerMouseInside()
   {

      ::user::interaction_impl::_001OnTriggerMouseInside();

      TRACKMOUSEEVENT tme = { sizeof(tme) };
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = get_handle();
      TrackMouseEvent(&tme);

   }



   void interaction_impl::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      // graphics will be already set its view port to the interaction_impl for linux - cairo with xlib

      pgraphics->SetViewportOrg(::point());

   }


   /*

/*   void interaction_impl::_001DeferPaintLayeredWindowBackground(::image * pimage)
   {


   }

   */



   bool interaction_impl::get_rect_normal(RECT32 * prect)

   {

      WINDOWPLACEMENT wp;

      xxf_zero(wp);

      if (!GetWindowPlacement(&wp))
         return false;

      *prect = wp.rcNormalPosition;


      return true;

   }


   DWORD WINAPI drop_target(LPVOID point)

   {

      interaction_impl* pimpl = (interaction_impl *)point;


      HRESULT hr = OleInitialize(nullptr);

      hr = ::RegisterDragDrop(pimpl->get_handle(), pimpl);

      if (SUCCEEDED(CoCreateInstance(CLSID_DragDropHelper, nullptr,
                                     CLSCTX_INPROC_SERVER,
                                     IID_IDropTargetHelper,
                                     (void**)& pimpl->m_piDropHelper)))
      {
         pimpl->m_bUseDnDHelper = true;
      }

      MSG msg;

      while (::GetMessage(&msg, nullptr, 0, 0xffffffffu))
      {

         TranslateMessage(&msg);

         DispatchMessage(&msg);

      }

      return 0;

   }


   void interaction_impl::register_drop_target()
   {
      m_bUseDnDHelper = false;

      ::CreateThread(nullptr, 0, drop_target, this, 0, nullptr);


   }


   void interaction_impl::show_task(bool bShow)
   {

      sync_lock sl(mutex());

      // https://www.daniweb.com/programming/software-development/threads/457564/mfc-application-disablehide-taskbar-icon

      if (bShow)
      {

         ModifyStyleEx(WS_EX_TOOLWINDOW, 0, SWP_FRAMECHANGED);

      }
      else
      {

         ModifyStyleEx(0, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);

      }

      defer_co_initialize_ex(false);

      comptr < ITaskbarList>                     tasklist;

      HRESULT hr = tasklist.CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER);

      if(SUCCEEDED(hr) && SUCCEEDED(hr = tasklist->HrInit()))
      {

         if (bShow)
         {

            hr = tasklist->AddTab(get_handle());

            TRACE("result = %d", hr);

         }
         else
         {

            tasklist->DeleteTab(get_handle());

         }

      }

   }


   /*bool interaction_impl::set_window_pos(class ::user::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   {

      if (!::user::interaction_impl::set_window_pos(zorder, x, y, cx, cy, nFlags))
      {

         return false;

      }

      if (!(GetExStyle() & WS_EX_LAYERED))
      {


         if (!::set_window_pos(get_handle(), zorder, x, y, cx, cy, nFlags))
         {

            return false;

         }

      }

      return true;

   }
*/


   void interaction_impl::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

      ::user::interaction_impl::window_show_change_visibility(edisplay, eactivation);

   }


   void interaction_impl::_001OnActivate(::message::message* pmessage)
   {

      BOOL enabled = FALSE;

      DwmIsCompositionEnabled(&enabled);

      //data->composition_enabled = enabled;

      if (enabled)
      {

         /* The u needs a frame to show a shadow, so give it the smallest amount of frame possible */

         MARGINS m = { 0,0,0,0 };

         ::u32  dw = DWMNCRP_ENABLED;

         DwmExtendFrameIntoClientArea(get_safe_handle(), &m);

         DwmSetWindowAttribute(get_safe_handle(), DWMWA_NCRENDERING_POLICY, &dw, sizeof(::u32));

      }
      else
      {

      }

   }


   void interaction_impl::_001OnDwmNcRenderingChanged(::message::message* pmessage)
   {

//#ifdef WINDOWS_DESKTOP

      SCAST_PTR(::message::base, pbase, pmessage);

      WPARAM wparam;

      LPARAM lparam;

      wparam = pbase->m_wparam;

      lparam = pbase->m_lparam;

      //return Default();

      BOOL enabled = FALSE;

      DwmIsCompositionEnabled(&enabled);

      //data->composition_enabled = enabled;

      if (enabled)
      {

         /* The u needs a frame to show a shadow, so give it the smallest amount of frame possible */

         MARGINS m = { 0,0,0,0 };

         ::u32  dw = DWMNCRP_ENABLED;

         DwmExtendFrameIntoClientArea(get_safe_handle(), &m);

         DwmSetWindowAttribute(get_safe_handle(), DWMWA_NCRENDERING_POLICY, &dw, sizeof(::u32));

      }
      else
      {

      }

      //update_region(data);
      //      long dwEx = ::GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE);
      //      dwEx &= ~(WS_EX_LAYERED);
      //      ::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,dwEx);
      //      ::InvalidateRect(GetSafeHwnd(),nullptr,true);
      //      ::UpdateWindow(GetSafeHwnd());
      //      //MoveAnchorsImmediatelly(hwndDlg);
      pbase->m_bRet = true;

      pbase->m_lresult = 0;

//#endif

   }


   void interaction_impl::_001OnNcCalcSize(::message::message* pmessage)
   {

//#ifdef WINDOWS_DESKTOP

      SCAST_PTR(::message::nc_calc_size, pcalcsize, pmessage);

      BOOL bCalcValidRects = pcalcsize->GetCalcValidRects();
      NCCALCSIZE_PARAMS* pncsp = pcalcsize->m_pparams;


      // TODO: Add your message handler code here and/or call default
      //if(bCalcValidRects)
      //{
      //   TRACE("1");
      //   pncsp->rgrc[0].left = lpncsp->lppos->x + 1;

      //   pncsp->rgrc[0].right = lpncsp->lppos->x + lpncsp->lppos->cx - 1;

      //   pncsp->rgrc[0].top = lpncsp->lppos->y + 32;

      //   pncsp->rgrc[0].bottom = lpncsp->lppos->y + lpncsp->lppos->cy - 1;

      //}
      //else
      //{
      //   CRect * prect = (CRect *) pncsp;

      //   prect->top += 32;
      //   prect->left++;
      //   prect->bottom--;
      //   prect->right--;

      //   TRACE("2");
      //}
      const rect& nonclient = pncsp->rgrc[0];

      //CMiniFrameWnd::OnNcCalcSize(bCalcValidRects, pncsp);

      const rect& client = pncsp->rgrc[0];

      if (node_is_zoomed())
      {
         WINDOWINFO wi = {};
         wi.cbSize = sizeof(wi);
         ::GetWindowInfo(get_safe_handle(), &wi);

         /* Maximized windows always have a non-client border that hangs over
         the edge of the screen, so the size proposed by e_message_nccalcsize is
         fine. Just adjust the top border to remove the u title. */
         pncsp->rgrc[0].left = client.left;

         pncsp->rgrc[0].top = nonclient.top + wi.cyWindowBorders;

         pncsp->rgrc[0].right = client.right;

         pncsp->rgrc[0].bottom = client.bottom;


         HMONITOR mon = MonitorFromWindow(get_safe_handle(), MONITOR_DEFAULTTOPRIMARY);
         MONITORINFO mi = {};
         mi.cbSize = sizeof(mi);
         GetMonitorInfoW(mon, &mi);

         /* If the client rectangle is the same as the monitor's rectangle,
         the shell assumes that the u has gone fullscreen, so it removes
         the topmost attribute from any auto-hide appbars, making them
         inaccessible. To avoid this, reduce the size of the client area by
         one pixel on a certain edge. The edge is chosen based on which side
         of the monitor is likely to contain an auto-hide appbar, so the
         missing client area is covered by it. */
         if (EqualRect(&pncsp->rgrc[0], &mi.rcMonitor))

         {
            if (has_autohide_appbar(ABE_BOTTOM, mi.rcMonitor))
               pncsp->rgrc[0].bottom--;

            else if (has_autohide_appbar(ABE_LEFT, mi.rcMonitor))
               pncsp->rgrc[0].left++;

            else if (has_autohide_appbar(ABE_TOP, mi.rcMonitor))
               pncsp->rgrc[0].top++;

            else if (has_autohide_appbar(ABE_RIGHT, mi.rcMonitor))
               pncsp->rgrc[0].right--;

         }
      }
      else
      {
         /* For the non-maximized case, set the output const rect & to what it was
         before e_message_nccalcsize modified it. This will make the client size the
         same as the non-client size. */
         pncsp->rgrc[0] = nonclient;


      }


      //SCAST_PTR(::message::base, pbase, pmessage);

      pcalcsize->m_lresult = 0;

      pcalcsize->m_bRet = true;

//#endif

   }


} // namespace windows


bool is_registered_windows_message(::u32 message)
{

   return message >= 0xc000 && message <= 0xffff;

}


LRESULT CALLBACK WndProc(HWND oswindow, ::u32 message, WPARAM wparam, LPARAM lparam);

int g_iCol = 0;

LRESULT CALLBACK __window_procedure(HWND oswindow, ::u32 message, WPARAM wparam, LPARAM lparam)
{

   ::user::interaction_impl * pimpl = oswindow_interaction_impl(oswindow);

   LRESULT lresult = 0;

   if (is_registered_windows_message(message))
   {

      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      return lresult;

   }

   if (pimpl)
   {

      if (pimpl->__windows_message_bypass(oswindow, message, wparam, lparam, lresult))
      {

         return lresult;

      }

   }

   //return ::DefWindowProcW(oswindow, message, wparam, lparam);

   if (::get_context_system() == nullptr)
   {

      return 0;

   }

   if (&System == nullptr)
   {

      return 0;

   }

   pimpl->m_uiMessage = message;

   pimpl->m_wparam = wparam;

   pimpl->m_lparam = lparam;

   ::user::interaction * pinteraction = pimpl->m_puserinteraction;

   if (message == e_message_activate)
   {

      output_debug_string("test");

   }

   if (message == e_message_left_button_up)
   {

      ::output_debug_string("e_message_left_button_up");

   }

   if (message == e_message_mouse_move)
   {

      if (lparam == pimpl->m_lparamLastMouseMove)
      {

         return 0;

      }

      pimpl->m_lparamLastMouseMove = lparam;

      ::point pointCursor;

      ::GetCursorPos(pointCursor);

      if (pimpl->m_pointCursor == pointCursor)
      {

         return 0;

      }

      pimpl->m_pointCursor = pointCursor;

   }
   else if (message == e_message_timer)
   {

      if (wparam == e_timer_transparent_mouse_event)
      {

         ::point pointCursor;

         ::GetCursorPos(pointCursor);

         if (pimpl->m_pointCursor == pointCursor)
         {

            return 0;

         }

         pimpl->m_pointCursor = pointCursor;

         LPARAM lparam;

         ::ScreenToClient(oswindow, pointCursor);

         lparam = MAKELPARAM(pointCursor.x, pointCursor.y);

         pimpl->call_message_handler(e_message_mouse_move, 0, lparam);

      }
      else
      {

         // ignoring Timer Event

         output_debug_string("iTE\n");

      }

      return 0;

   }

   if (pimpl->m_bDestroyImplOnly || ::is_null(pinteraction))
   {

      auto pbase = pimpl->get_message_base(oswindow, (enum_message) message, wparam, lparam);

      try
      {

         pimpl->message_handler(pbase);

      }
      catch (...)
      {

      }
      
      if (!pbase->m_bRet)
      {

         pimpl->default_message_handler(pbase);

      }

      lresult = pbase->m_lresult;

   }
   else if (::is_set(pinteraction))
   {

      if (message == WM_GETTEXT)
      {

         return ::DefWindowProcW(oswindow, message, wparam, lparam);
         
      }
      else if (message == WM_GETTEXTLENGTH)
      {

         return ::DefWindowProcW(oswindow, message, wparam, lparam);

      }
      else if (message == WM_SETTEXT)
      {

         return ::DefWindowProcW(oswindow, message, wparam, lparam);

      }

      auto pbase = pinteraction->get_message_base(oswindow,(enum_message) message, wparam, lparam);

      try
      {

         pinteraction->message_handler(pbase);

      }
      catch (...)
      {

      }

      if (!pbase->m_bRet)
      {

         pinteraction->default_message_handler(pbase);

      }

      lresult = pbase->m_lresult;

   }
   else
   {

      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

   }

   return lresult;

}






//CLASS_DECL_AURA bool hook_window_create(::windows::interaction_impl * pwindow)
//{
//
//   if (pwindow == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (pwindow->get_handle() != nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (t_hHookOldCbtFilter == nullptr)
//   {
//
//      t_hHookOldCbtFilter = ::SetWindowsHookExW(WH_CBT, windows::__cbt_filter_hook, nullptr, ::GetCurrentThreadId());
//
//      if (t_hHookOldCbtFilter == nullptr)
//      {
//
//         return false;
//
//      }
//
//   }
//
//   if (t_hHookOldCbtFilter == nullptr)
//   {
//
//      return false;
//
//   }
//
//   thread_set("wnd_init") = pwindow;
//
//   if (thread_set("wnd_init") == nullptr)   // hook not already in progress
//   {
//
//      return false;
//
//   }
//
//   if (thread_set("wnd_init") != pwindow)
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//CLASS_DECL_AURA bool unhook_window_create()
//{
//
//   if (thread_set("wnd_init") != nullptr)
//   {
//
//      thread_set("wnd_init") = nullptr;
//
//      return false;   // was not successfully hooked
//
//   }
//
//   return true;
//
//}
//

void CLASS_DECL_AURA _handle_activate(::user::interaction_impl * pwindow, WPARAM nState, ::user::interaction_impl * pWndOther)
{

   ASSERT(pwindow);

   // send WM_ACTIVATETOPLEVEL when top-level parents change
   if (!((pwindow)->GetStyle() & WS_CHILD))
   {
      __pointer(::user::interaction) pTopLevel = (pwindow)->GetTopLevel();
      if (pTopLevel && (!pWndOther || !::is_window((pWndOther)->get_handle()) || pTopLevel != (pWndOther)->GetTopLevel()))
      {
         // lParam points to interaction_impl getting the e_message_activate message and
         //  oswindow_Other from the e_message_activate.
         oswindow oswindow_2[2];
         oswindow_2[0] = (pwindow)->get_handle();
         if (!pWndOther)
         {
            oswindow_2[1] = nullptr;
         }
         else
         {

            oswindow_2[1] = (pWndOther)->get_handle();

         }

         // send it...
         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (LPARAM)&oswindow_2[0]);

      }

   }

}


void __term_windowing()
{

   //if (t_hHookOldCbtFilter != nullptr)
   //{

   //   ::UnhookWindowsHookEx(t_hHookOldCbtFilter);

   //   t_hHookOldCbtFilter = nullptr;

   //}

}







namespace windows
{


   void interaction_impl::default_message_handler(::message::message * pmessage)
   {

      if (get_handle() == nullptr)
      {

         return;

      }

      WNDPROC pfnWndProc = *GetSuperWndProcAddr();

      LRESULT lresult = 0;

      if (pfnWndProc == nullptr)
      {

         lresult = ::DefWindowProcW(m_oswindow, (::u32) pmessage->m_id.i64(), pmessage->m_wparam, pmessage->m_lparam);

      }
      else
      {

         lresult = ::CallWindowProc(pfnWndProc, m_oswindow, (::u32) pmessage->m_id.i64(), pmessage->m_wparam, pmessage->m_lparam);

      }

      pmessage->m_lresult = lresult;

   }


   bool interaction_impl::set_icon(::draw2d::icon * picon, bool bSmall)
   {

      if (::is_null(picon))
      {

         return false;

      }

      HICON hicon = picon->get_os_data();

      if(::is_null(hicon))
      {	

         return false;

      }

      if(bSmall)
      {
 
         SendMessage(get_handle(), (::u32)WM_SETICON, ICON_SMALL, (LPARAM)hicon);

      }
      else
      {

         SendMessage(get_handle(), (::u32)WM_SETICON, ICON_BIG, (LPARAM)hicon);

      }

      return true;

   }


   void interaction_impl::message_handler(::message::base * pbase)
   {

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->pre_translate_message(pbase);

      }

      if (pbase->m_bRet)
      {

         return;

      }

      ::u32 message;

      message = pbase->m_id.umessage();

      m_uiMessage = message;

      m_wparam = pbase->m_wparam;

      m_lparam = pbase->m_lparam;

      if (message == WM_IME_SETCONTEXT)
      {

         if (m_wparam == 1)
         {

            m_lparam &= ~ISC_SHOWUICOMPOSITIONWINDOW;

         }

         pbase->m_lresult = ::DefWindowProcW(m_oswindow, m_uiMessage, m_wparam, m_lparam);

         pbase->m_bRet = true;

         return;

      }

      bool bUserElementalOk = !m_bDestroyImplOnly && m_puserinteraction && m_puserinteraction->m_bUserPrimitiveOk;

      if (message == e_message_key_down ||
         message == e_message_key_up ||
         message == e_message_char ||
         message == e_message_sys_key_down ||
         message == e_message_sys_key_up ||
         message == e_message_sys_char ||
         message == WM_IME_KEYDOWN ||
         message == WM_IME_SETCONTEXT ||
         message == WM_IME_SELECT ||
         message == WM_IME_KEYUP ||
         message == WM_IME_CHAR ||
         message == WM_IME_STARTCOMPOSITION ||
         message == WM_IME_COMPOSITION ||
         message == WM_IME_COMPOSITIONFULL ||
         message == WM_IME_NOTIFY ||
         message == WM_IME_ENDCOMPOSITION)
      {

         SCAST_PTR(::message::key, pkey, pbase);

         if (message == e_message_key_down)
         {

            output_debug_string("\n Key Down Event ");

         }

         auto psession = Session;

         if (message == e_message_key_down || message == e_message_sys_key_down)
         {
            try
            {
               psession->set_key_pressed(pkey->m_ekey, true);
            }
            catch (...)
            {
            }
         }
         else if (message == e_message_key_up || message == e_message_sys_key_up)
         {

            try
            {

               psession->set_key_pressed(pkey->m_ekey, false);

            }
            catch (...)
            {

            }

         }

      }

      if (message == e_message_timer)
      {
         //         m_puserinteraction->get_context_application()->step_timer();
      }
      else if (message == e_message_left_button_down)
      {
         ::rect rectClient;
         ::GetClientRect(get_handle(), rectClient);
         ::rect rectWindow;
         ::GetWindowRect(get_handle(), rectWindow);
         ::rect rectRegion;
         HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
         int regionType = ::GetWindowRgn(get_handle(), hrgn);
         if (regionType != ERROR)
         {
            ::GetRgnBox(hrgn, rectRegion);
         }
         ::DeleteObject(hrgn); /* finished with region */
         WINDOWPLACEMENT wp;
         xxf_zero(wp);
         wp.length = sizeof(WINDOWPLACEMENT);
         ::GetWindowPlacement(get_handle(), &wp);
         bool bZoomed = ::IsZoomed(get_handle()) != FALSE;
         bool bIconic = ::IsIconic(get_handle()) != FALSE;
      }
      else if (message == e_message_set_cursor
         || message == e_message_non_client_mouse_move)
      {
         //output_debug_string(".");
      }
      else
      {

#ifdef __DEBUG

         if (0)
         {
            switch (message)
            {
            case e_message_create:
               TRACE("e_message_create wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_window_position_changing:
               TRACE("e_message_window_position_changing wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_window_position_changed:
               TRACE("e_message_window_position_changed wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_activate:
               TRACE("e_message_activate wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case WM_ACTIVATEAPP:
               TRACE("WM_ACTIVATEAPP wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_mouse_activate:
               TRACE("e_message_mouse_activate wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_ncactivate:
               TRACE("e_message_ncactivate wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_set_focus:
               TRACE("e_message_set_focus wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_kill_focus:
               TRACE("e_message_kill_focus wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_move:
               TRACE("e_message_move wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            case e_message_size:
               TRACE("e_message_size wparam=%08x lparam=%08x", pbase->m_wparam, pbase->m_lparam);

               break;
            default:
               TRACE("MESSAGE %08x wparam=%08x lparam=%08x", message, pbase->m_wparam, pbase->m_lparam);

               break;
            }

         }

#endif //__DEBUG

      }
      
      //auto psession = Session;



      /*      else if(message == CA2M_BERGEDGE)
      {
      if(pbase->m_wparam == BERGEDGE_GETAPP)
      {
      __pointer(::aura::application)* ppapp= (__pointer(::aura::application)*) pbase->m_lparam;
      *ppapp = get_context_application();
      pbase->m_bRet = true;
      return;
      }
      }*/
      //pbase->set_lresult(0);

      if (message == e_message_mouse_leave)
      {

         auto papexsession = get_context_session();

         ::aura::session * psession = nullptr;

         if (papexsession)
         {

            psession = papexsession->m_paurasession;

         }

         if (psession && psession->m_puiCapture)
         {

            psession->m_puiCapture->_000OnMouseLeave(pbase);

         }
         else if (m_puserinteraction)
         {

            m_puserinteraction->_000OnMouseLeave(pbase);

         }

         return;

      }

      if (message == e_message_left_button_down ||
         message == e_message_left_button_up ||
         message == e_message_middle_button_down ||
         message == e_message_middle_button_up ||
         message == e_message_right_button_down ||
         message == e_message_right_button_up ||
         message == e_message_left_button_double_click ||
         message == e_message_mouse_move ||
         message == e_message_non_client_mouse_move ||
         message == e_message_mouse_wheel)
      {

         message::mouse * pmouse = dynamic_cast <::message::mouse *> (pbase);

         if (message >= WM_MOUSEFIRST
            && message <= WM_MOUSELAST
            && m_bTranslateMouseMessageCursor
            && !pmouse->m_bTranslated)
         {

            pmouse->m_bTranslated = true;

            ::ClientToScreen(get_handle(), &pmouse->m_point);

         }

         if (message == e_message_left_button_down)
         {

            TRACE("e_message_left_button_down");

            string strType = ::str::demangle(m_puserinteraction->type_name());

            if (strType.contains_ci("combo_list"))
            {

               ::output_debug_string("combo_list e_message_left_button_down");

            }

         }
         else if (message == e_message_left_button_up)
         {

            TRACE("e_message_left_button_up");

         }
         else if (message == e_message_non_client_left_button_up)
         {

            TRACE("e_message_non_client_left_button_up");

         }
         else if (message == e_message_non_client_left_button_down)
         {

            TRACE("e_message_non_client_left_button_down");

            string strType;

            if (strType.contains_ci("combo_list"))
            {

               ::output_debug_string("combo_list e_message_non_client_left_button_down");

            }

         }

         auto papexsession = get_context_session();

         ::aura::session * psession = nullptr;

         if (papexsession)
         {

            psession = papexsession->m_paurasession;

         }

         if (psession)
         {

            psession->on_ui_mouse_message(pmouse);

         }

         if (message == e_message_mouse_move)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;

            //INFO("windows::e_message_mouse_move(%d,%d)", pmouse->m_point.x, pmouse->m_point.y);

            string strType;

            if (m_puserinteraction)
            {

               strType = ::str::demangle(m_puserinteraction->type_name());

               if (strType.contains_ci("combo_list"))
               {

                  //::output_debug_string("combo_list e_message_mouse_move");

               }

            }

         }
         else if (message == e_message_non_client_mouse_move)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;
         }

         if (psession)
         {

            auto puiCapture = psession->m_puiCapture;

            if (::is_set(puiCapture))
            {

               puiCapture->_000OnMouse(pmouse);

               return;

            }

         }

         _008OnMouse(pmouse);

         return;

      }

      if (message == MESSAGE_OLE_DRAGENTER ||
         message == MESSAGE_OLE_DRAGOVER ||
         message == MESSAGE_OLE_DRAGLEAVE ||
         message == MESSAGE_OLE_DRAGDROP)
      {

         message::drag_and_drop * pdrag = (::message::drag_and_drop *) pbase;

         auto pinteraction = pdrag->userinteraction();

         //user::oswindow_array oswindowa;
         //user::interaction_pointer_array wnda;
         //wnda = *System.m_puiptraFrame;
         //oswindowa = wnda.get_hwnda();
         //user::window_util::SortByZOrder(oswindowa);
         //for (i32 i = 0; i < oswindowa.get_size(); i++)
         //{
         //   __pointer(::user::interaction) pinteraction = wnda.find_first(oswindowa[i]);
         //   if (pinteraction != nullptr)
         //   {

         if (pinteraction)
         {
            pinteraction->_000OnDrag(pdrag);
            if (pdrag->m_bRet)
               return;

         }
    /*        }
         }*/
         return;
      }
      if (message == e_message_key_down ||
         message == e_message_key_up ||
         message == e_message_char ||
         message == e_message_sys_key_down ||
         message == e_message_sys_key_up ||
         message == e_message_sys_char ||
         message == WM_IME_KEYDOWN ||
         message == WM_IME_KEYUP ||
         message == WM_IME_CHAR ||
         message == WM_IME_SELECT ||
         message == WM_IME_SETCONTEXT ||
         message == WM_IME_STARTCOMPOSITION ||
         message == WM_IME_COMPOSITION ||
         message == WM_IME_COMPOSITIONFULL ||
         message == WM_IME_NOTIFY ||
         message == WM_IME_ENDCOMPOSITION ||
         message == WM_INPUTLANGCHANGE)
      {

     
         message::key * pkey = (::message::key *) pbase;

         __pointer(::user::interaction) puiFocus;
         
         auto papexsession = get_context_session();

         ::aura::session * psession = nullptr;

         if (papexsession)
         {

            psession = papexsession->m_paurasession;

         }

         if (psession)
         {

            puiFocus = m_puserinteraction->get_keyboard_focus();

         }

         if (puiFocus && puiFocus->is_window() && puiFocus != m_puserinteraction)
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

         //m_wparam-

         //m_lparam = pbase->m_lparam;

         //pbase->set_lresult(::default_window_procedure(message, pbase->m_wparam, pbase->m_lparam));

         //return;

      }

      if (message == e_message_event)
      {

         m_puserinteraction->on_control_event(pbase);

         return;

      }

      ::user::interaction_impl::message_handler(pbase);

      //if(pmessage->m_bRet && !pbase->m_bDoSystemDefault)

      if (pbase->m_bRet)
      {

         return;

      }

      if(message == WM_IME_STARTCOMPOSITION ||
         message == WM_IME_COMPOSITION ||
         message == WM_IME_COMPOSITIONFULL ||
         message == WM_IME_NOTIFY ||
         message == WM_IME_ENDCOMPOSITION ||
         message == WM_IME_SELECT ||
         message == WM_IME_SETCONTEXT)
      {

         //return;

      }

      //if (bUserElementalOk && pbase->m_bWindowProc)
      //{
      //   
      //   if (m_puserinteraction != nullptr)
      //   {
      //      
      //      m_puserinteraction->default_window_procedure(pbase);

      //   }
      //   else
      //   {
      //      
      //      pbase->set_lresult(::DefWindowProcW(m_oswindow, pbase->m_id, pbase->m_wparam, pbase->m_lparam));

      //   }

      //}

   }


   void interaction_impl::non_top_most_upper_window_rects(::rect_array& recta)
   {

      /// from top to bottom
      top_level_enum toplevelenum;

      auto poswindowa = toplevelenum.m_poswindowa;

      oswindow oswindow = get_safe_handle();
      
      index iFind = poswindowa->find_first(oswindow);

      if (iFind < 0)
      {

         return;

      }

      ::rect rHigher;

      for (iFind--; iFind >= 0; iFind--)
      {

         oswindow = poswindowa->element_at(iFind);

         int iExStyle = GetWindowLong(oswindow, GWL_EXSTYLE);

         if ((iExStyle & WS_EX_TOPMOST) == WS_EX_TOPMOST)
         {

            continue;

         }

         if (::GetWindowRect(oswindow, rHigher))
         {

            recta.add(rHigher);

         }

      }

   }


   ::e_status interaction_impl::finish(::context_object * pcontextobjectFinish)
   {

      auto estatus = set_finish(pcontextobjectFinish);

      if (estatus == success)
      {

         on_finish();

      }

      return estatus;

   }




   ::e_status interaction_impl::set_tool_window(bool bSet)
   {

      if(bSet)
      {

         ModifyStyleEx(0, WS_EX_TOOLWINDOW);

      }
      else
      {

         ModifyStyleEx(WS_EX_TOOLWINDOW, 0);

      }

      return ::success;

   }


} // namespace windows


wstring windows_calc_icon_window_class(::user::interaction * pinteraction, u32 dwDefaultStyle, const char * pszMatter)
{

   string strPath = Ctx(pinteraction).dir().matter(pszMatter, "icon.ico");

   HICON hIcon = (HICON) ::LoadImageW(nullptr, wstring(Ctx(pinteraction).get_matter_path(strPath)), IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

   wstring strClass = windows_get_user_interaction_window_class(pinteraction);

   if (hIcon != nullptr)
   {

      // will fill pszClassName with default WNDCLASS name

      // ignore instance handle from pre_create_window.

      WNDCLASSEXW wndcls;

      if (strClass.get_length() > 0 && GetClassInfoExW(System.m_hinstance, strClass, &wndcls) && wndcls.hIcon != hIcon)
      {
         // register a very similar WNDCLASS

         return windows_register_window_class(get_context_application(), wndcls.style, wndcls.hCursor, wndcls.hbrBackground, hIcon);

      }

   }

   return strClass;

}




wstring CLASS_DECL_AURA windows_get_user_interaction_window_class(::user::interaction * pinteraction)
{

   ::user::interaction::enum_type etype = pinteraction->get_window_type();

   WNDCLASSEXW wndcls;
   
   __memset(&wndcls, 0, sizeof(WNDCLASSEXW));   // start with nullptr defaults
   
   wndcls.lpfnWndProc = windows_user_interaction_impl_get_window_procedure();

   wndcls.hInstance = GetModuleHandleW(L"aura.dll");

   //INITCOMMONCONTROLSEX init;
   //init.dwSize = sizeof(init);
   if (etype == ::user::interaction::type_frame || etype == ::user::interaction::type_view)
   {
      // SDI Frame or MDI Child windows or views - normal colors
      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
      //wndcls.style = CS_HREDRAW | CS_VREDRAW;
      wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      if (windows_register_with_icon(&wndcls, gen_WndFrameOrView, 0))
      {
         return wndcls.lpszClassName;

      }
   }

   return windows_register_window_class(pinteraction->get_context_application(), 0);

}



bool CLASS_DECL_AURA windows_register_with_icon(WNDCLASSEXW * pwndclass, const unichar * pszClassName, ::u32 nIDIcon)
{

   pwndclass->lpszClassName = pszClassName;
   
   pwndclass->hIcon = ::LoadIconW(nullptr, MAKEINTRESOURCEW(32512));

   return windows_register_class(pwndclass);

}


CLASS_DECL_ACME WNDPROC get_window_procedure();


CLASS_DECL_AURA wstring windows_register_window_class(::layered * pobjectContext, ::u32 nClassStyle, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
{

  ::apex::application * papp = ::get_context_application(pobjectContext);

  const int iLen = 4096;

  wstring wstrClassName;

  {

     LPWSTR lpwsz = wstrClassName.get_string_buffer(iLen);

     if (hCursor == nullptr && hbrBackground == nullptr && hIcon == nullptr)
     {

        C_RUNTIME_ERRORCHECK_SPRINTF(_snwprintf_s(lpwsz, iLen, iLen - 1, L"windows_interaction_impl:%p,%x", System.m_hinstance, nClassStyle));

     }
     else
     {

        C_RUNTIME_ERRORCHECK_SPRINTF(_snwprintf_s(lpwsz, iLen, iLen - 1, L"windows_interaction_impl:%p,%x,%p,%p,%p", System.m_hinstance, nClassStyle, hCursor, hbrBackground, hIcon));

     }

     wstrClassName.release_string_buffer();

  }

  // see if the class already exists
  WNDCLASSEXW wndcls = {};

  if (::GetClassInfoExW(System.m_hinstance, wstrClassName, &wndcls))
  {
     // already registered, assert everything is good
     ASSERT(wndcls.style == nClassStyle);

     // NOTE: We have to trust that the hIcon, hbrBackground, and the
     //  hCursor are semantically the same, because sometimes Windows does
     //  some internal translation or copying of those handles before
     //  storing them in the internal WNDCLASS retrieved by GetClassInfo.
     return wstrClassName;

  }
  wndcls.cbSize = sizeof(wndcls);
  // otherwise we need to register a new class
  wndcls.style = nClassStyle;
  wndcls.lpfnWndProc = get_window_procedure();

  wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
  wndcls.hInstance = ::GetModuleHandleW(L"aura.dll");
  //wndcls.hIcon = hIcon;
  //wndcls.hCursor = hCursor;
  wndcls.hCursor = nullptr;
  wndcls.hbrBackground = hbrBackground;
  wndcls.lpszMenuName = nullptr;

  wndcls.lpszClassName = wstrClassName;

  if (!windows_register_class(&wndcls))
  {

     __throw(resource_exception());

  }

  // return thread-local pointer
  return wstrClassName;

}




LRESULT CALLBACK WndProc(HWND hWnd, const ::id & id, WPARAM wParam, LPARAM lParam);

//bool windows_register_class(HINSTANCE hinstance)
//{
//   
//   WNDCLASSEXW wcex = {};
//
//   wcex.cbSize = sizeof(WNDCLASSEXW);
//   wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//   wcex.lpfnWndProc = get_window_procedure();
//   wcex.cbClsExtra = 0;
//   wcex.cbWndExtra = 0;
//   wcex.hInstance = hinstance;
//   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
//   wcex.lpszClassName = L"windows_interaction_impl";
//
//   if (!RegisterClassExW(&wcex))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


CLASS_DECL_AURA WNDPROC windows_user_interaction_impl_get_window_procedure()
{

   return &__window_procedure;

}


