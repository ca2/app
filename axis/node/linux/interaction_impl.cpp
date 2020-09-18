#include "framework.h"
#include "_linux.h"
#include "aura/platform/app_core.h"
#include "aura/os/linux/_linux.h"
#include <X11/Xatom.h>
#include "third/sn/sn.h"
#include <gdk/gdkx.h>

#define TEST 0


void x11_store_name(oswindow oswindow, const char * pszName);
void x11_defer_check_configuration(oswindow oswindow);
void upper_window_rects(oswindow oswindow, rect_array & ra);
#undef ALOG_CONTEXT
#define ALOG_CONTEXT (::trace_object(::trace_category_windowing))


void wm_add_remove_state(oswindow w, e_net_wm_state estate, bool bSet);

void wm_iconify_window(oswindow w);

void wm_state_above_raw(oswindow w, bool bSet);

void windowing_output_debug_string(const char * pszDebugString);

Display * x11_get_display();

void wm_state_above_raw(oswindow w, bool bSet);

void wm_toolwindow(oswindow w, bool bSet);

void wm_centerwindow(oswindow w, bool bSet);

void wm_desktopwindow(oswindow w, bool bSet);

void wm_dockwindow(oswindow w, bool bSet);

void wm_state_hidden(oswindow w, bool bSet);

//#include <X11/extensions/Xcomposite.h>

//CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;

//#define COMPILE_MULTIMON_STUBS
//#include <multimon.h>

//#include "sal.h"

extern SnLauncheeContext* g_psncontext;

CLASS_DECL_AXIS void hook_window_create(::user::interaction * pWnd);
CLASS_DECL_AXIS bool unhook_window_create();
void CLASS_DECL_AXIS __pre_init_dialog(
::user::interaction * pWnd, RECT * pRectOld, DWORD* pdwStyleOld);

void CLASS_DECL_AXIS __post_init_dialog(
::user::interaction * pWnd, const rect & rectOld, DWORD dwStyleOld);
LRESULT CALLBACK
__activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam);


const char gen_OldWndProc[] = "::ca2::OldWndProc423";

/*const char gen_WndControlBar[] = __WNDCONTROLBAR;
const char gen_WndMDIFrame[] = __WNDMDIFRAME;
const char gen_WndFrameOrView[] = __WNDFRAMEORVIEW;
const char gen_WndOleControl[] = __WNDOLECONTROL;
*/
struct __CTLCOLOR
{
   oswindow hWnd;
   HDC hDC;
   UINT nCtlType;
};

//extern cairo_surface_t *  g_cairosurface;
//extern cairo_t *  g_cairo;

// WINBOOL PeekMessage(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);



// WINBOOL GetMessage(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);


/*
const char gen_Wnd[] = __WND;
*/

namespace linux
{


   i64 g_iMouseMove = 0;

   class x11data :
      virtual public object
   {
   public:

      XWindowAttributes             m_attr;
      XVisualInfo                   m_visualinfo;
      GdkWindow *                   m_pgdkwindow;

   };


   interaction_impl::interaction_impl()
   {

      linux_interaction_impl_common_construct();

   }


   interaction_impl::interaction_impl(::layered * pobjectContext) :
      ::object(pobject)
   {

      linux_interaction_impl_common_construct();

   }


   void interaction_impl::linux_interaction_impl_common_construct()
   {

      set_handle(nullptr);
      m_bExposing    = false;
      m_bEnabled     = true;
      m_bMoveEvent   = false;
      m_bSizeEvent   = false;


   }


   interaction_impl::~interaction_impl()
   {

   }


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      return from_handle((oswindow) pdata);

   }

   void * interaction_impl::get_os_data() const
   {

      return m_oswindow;

   }


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

      if(is_null(oswindow))
      {

         return nullptr;

      }

      if(is_null(oswindow->m_pimpl))
      {

         return nullptr;

      }

      return oswindow->m_pimpl;

   }


   ::user::interaction_impl * interaction_impl::FromHandlePermanent(oswindow oswindow)
   {

      if(oswindow->m_pimpl == nullptr)
         return nullptr;

      return oswindow->m_pimpl;

   }

   bool interaction_impl::Attach(oswindow hWndNew)
   {

      ASSERT(get_handle() == nullptr);

      if (hWndNew == nullptr)
         return false;

      m_oswindow = hWndNew;

      return true;

   }


   bool interaction_impl::setWMClass(const char * psz)
   {

    string str(psz);

        m_oswindow->set_wm_class(str);


    return true;

   }

   oswindow interaction_impl::Detach()
   {

      oswindow hwnd = (oswindow) get_handle();

      if (hwnd != nullptr)
      {

         m_oswindow = nullptr;

      }

      return hwnd;

   }


   void interaction_impl::pre_subclass_window()
   {


   }


   bool interaction_impl::_native_create_window_ex(::user::create_struct & cs)
   {

      ENSURE_ARG(cs.lpszName == nullptr || __is_valid_string(cs.lpszName));

      if (!m_puserinteraction->pre_create_window(cs))
      {

         return false;

      }

      __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_thread());

      m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

      install_message_routing(m_puserinteraction);

      bool bOk = true;

      if(cs.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
      {

         m_oswindow = oswindow_get_message_only_window(this);

         m_puserinteraction->m_bMessageWindow = true;

         //send_message(WM_CREATE, 0, (LPARAM) &cs);

      }
      else
      {

         m_puserinteraction->m_bMessageWindow = false;

         x11_sync([&]()
         {

            Display * display    = x11_get_display();

            if(display == nullptr)
            {

               fprintf(stderr, "ERROR: Could not open display\n");

               bOk = false;

               return;

            }

            xdisplay d(display);

            if(cs.cx <= 0)
            {

               cs.cx = 1;

            }

            if(cs.cy <= 0)
            {

               cs.cy = 1;

            }

            m_iScreen            =  DefaultScreen(display);

            Window rootwin       =  RootWindow(display, m_iScreen);

            XEvent e;

            // query Visual for "TrueColor" and 32 bits depth (RGBA)

            Visual * vis = DefaultVisual(display, DefaultScreen(display));

            m_iDepth = 0;

            if(m_px11data.is_null())
            {

               m_px11data = __new(x11data);

            }

            if(XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_px11data->m_visualinfo))
            {

               vis = m_px11data->m_visualinfo.visual;

            }
            else
            {

               xxf_zero(m_px11data->m_visualinfo);

            }

            m_iDepth = m_px11data->m_visualinfo.depth;

            XSetWindowAttributes attr;

            xxf_zero(attr);

            attr.colormap = XCreateColormap( display, rootwin, vis, AllocNone);

            attr.event_mask = PropertyChangeMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask | FocusChangeMask;

            attr.background_pixmap = None;

            attr.border_pixmap = None;

            attr.border_pixel = 0;

            attr.override_redirect = m_puserinteraction->m_ewindowflag & window_flag_arbitrary_positioning ? True : False;

            //attr.override_redirect = True;

            INFO("XCreateWindow (l=%d, t=%d) (w=%d, h=%d)", cs.x, cs.y, cs.cx, cs.cy);

            Window window = XCreateWindow(display, DefaultRootWindow(display), cs.x, cs.y, cs.cx, cs.cy,
            0,
            m_iDepth,
            InputOutput,
            vis,
            CWColormap|CWEventMask|CWBackPixmap|CWBorderPixel
                          | CWOverrideRedirect
                                          , &attr);

            auto & windowstate3 = m_puserinteraction->window_state3();

            windowstate3.m_point.set(INT_MIN, INT_MIN);

            windowstate3.m_size.set(INT_MIN, INT_MIN);

            windowstate3.m_pointScreen.set(INT_MIN, INT_MIN);

   //         {
   //
   //            auto & uistate = m_puserinteraction->ui_state();
   //
   //            uistate.m_point.set(cs.x, cs.y);
   //
   //            uistate.m_size.set(cs.cx, cs.cy);
   //
   //            uistate.m_pointScreen = uistate.m_point;
   //
   //         }
   //
            {

               auto & state = m_puserinteraction->request_state();

               state.m_point.set(cs.x, cs.y);

               state.m_size.set(cs.cx, cs.cy);

               //state.m_pointScreen = windowstate.m_pointScreen;

            }

   //         {
   //
   //            auto & state = m_puserinteraction->process_state();
   //
   //            state.m_point = windowstate.m_point;
   //
   //            state.m_size = windowstate.m_size;
   //
   //            state.m_pointScreen = windowstate.m_pointScreen;
   //
   //         }

            if (window == 0)
            {

               DWORD dwLastError = get_last_error();

               string strLastError = FormatMessageFromSystem(dwLastError);

               string strMessage;

               strMessage.Format("%s\n\nSystem Error Code: %d", strLastError.c_str(), dwLastError);

               TRACE(trace_category_appmsg, trace_level_warning, "Warning: oswindow creation failed: get_last_error returned:\n");

               TRACE(trace_category_appmsg, trace_level_warning, "%s\n", strMessage.c_str());

               try
               {

                  if(dwLastError == 0x0000057e)
                  {

                     System.message_box("cannot create a top-level child interaction_impl.");

                  }
                  else
                  {

                     System.message_box(strMessage);

                  }

               }
               catch(...)
               {

               }

               bOk = false;

               return;

            }

            m_oswindow = oswindow_get(display, window, vis, m_iDepth, m_iScreen, attr.colormap);

            m_oswindow->set_user_interaction(this);

            m_puserinteraction->m_pimpl = this;

            m_puserinteraction->add_ref(OBJ_REF_DBG_P_NOTE(this, "native_create_window"));

            auto papp = get_context_application();

            if(!(m_puserinteraction->m_ewindowflag & window_flag_satellite_window))
            {

               XClassHint * pupdate = XAllocClassHint();

               string strPrgName = papp->m_strAppId;

               strPrgName.replace("/", ".");

               strPrgName.replace("_", "-");

               strPrgName = "cc.ca2." + strPrgName;

               pupdate->res_class = (char *) (const char *) strPrgName;

               pupdate->res_name = (char *) (const char *) strPrgName;

               XSetClassHint(display, window, pupdate);

               XFree(pupdate);

            }

   #ifndef RASPBIAN

            if(g_psncontext != nullptr && !papp->m_bSnLauncheeSetup)
            {

               sn_launchee_context_setup_window(g_psncontext, window);

               papp->m_bSnLauncheeSetup = true;

            }

   #endif

            if(m_puserinteraction->m_ewindowflag & window_flag_dock_window)
            {

               wm_dockwindow(m_oswindow, true);

            }
            else if(m_puserinteraction->m_ewindowflag & window_flag_desktop_window)
            {

               wm_desktopwindow(m_oswindow, true);

            }
            else if(m_puserinteraction->layout().sketch().m_eactivation & activation_on_center_of_screen)
            {

               wm_centerwindow(m_oswindow, true);

            }

            if(m_puserinteraction->m_ewindowflag & window_flag_satellite_window)
            {

               wm_toolwindow(m_oswindow, true);

            }

            //m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);

            Window root = 0;

            Window * pchildren = nullptr;

            u32 ncount = 0;

            XQueryTree(display, window, &root, &m_oswindow->m_parent, &pchildren, &ncount);

            if(pchildren != nullptr)
            {

               XFree(pchildren);

            }

            HTHREAD hthread = ::get_current_hthread();

            m_oswindow->m_hthread = hthread;


            if(!XGetWindowAttributes(m_oswindow->display(), m_oswindow->window(), &m_px11data->m_attr))
            {

               INFO("linux::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.");

            }

            int event_base, error_base, major_version, minor_version;

            m_bComposite = XGetSelectionOwner(m_oswindow->display(), XInternAtom(m_oswindow->display(), "_NET_WM_CM_S0", True));

            if(cs.lpszName != nullptr && strlen(cs.lpszName) > 0)
            {

               XStoreName(m_oswindow->display(), m_oswindow->window(), cs.lpszName);

            }

            if(cs.dwExStyle & WS_EX_TOOLWINDOW)
            {

               m_oswindow->set_window_long_ptr(GWL_EXSTYLE, m_oswindow->get_window_long_ptr(GWL_EXSTYLE) |  WS_EX_TOOLWINDOW);

            }

            _wm_nodecorations(m_oswindow, 0);

            if(cs.style & WS_VISIBLE)
            {

               m_oswindow->map_window();

            }
            else
            {

               m_puserinteraction->window_state3().m_edisplay3 = display_none;

            }

            //if(m_px11data->m_attr.map_state != IsUnmapped)
            {

               if(!attr.override_redirect)
               {

                  if(is_docking_appearance(m_puserinteraction->layout().sketch().display()))
                  {

                     // window managers generally "don't like" windows that starts "docked/snapped".
                     // initial (XCreateWindow) size and position maybe not be honored.
                     // so requesting the same change again in a effort to set the "docked/snapped" size and position.

                     m_oswindow->set_window_pos(zorder_top, cs.x, cs.y, cs.cx, cs.cy, SWP_SHOWWINDOW);

                  }

               }

            }

            d.unlock();

            //if(pshowwindow->m_bShow)
            {

               //::rect rect32;

               //(::get_window_rect((oswindow) get_handle(), rect32))
               {


                  if(get_context_session() != nullptr)
                  {

                     // Initial position of window below the cursor position
                     // with invalid (empty) size.
                     // (Hinting for monitor placement, if no stored information
                     // available).

                     if(m_puserinteraction->layout().sketch().m_edisplay3 == display_undefined)
                     {

                        m_puserinteraction->move_to(get_context_session()->get_cursor_pos());

                        m_puserinteraction->set_size(0, 0);

                     }

                  }

               }

            }

         });

      }

      if(bOk)
      {

         m_puserinteraction->send_message(WM_CREATE, 0, (LPARAM) &cs);

         m_puserinteraction->m_ewindowflag |= window_flag_window_created;

      }

      return bOk;

   }


   bool interaction_impl::pre_create_window(::user::create_struct & cs)
   {

      return true;

   }





   void interaction_impl::install_message_routing(::channel * pchannel)
   {
      //m_pbuffer->InstallMessageHandling(pinterface);

      ::user::interaction_impl::last_install_message_routing(pchannel);
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
         //IGUI_MSG_LINK(WM_SIZE, pchannel, this,&interaction_impl::_001OnSize);
         //IGUI_MSG_LINK(WM_NCCALCSIZE, pchannel, this,&interaction_impl::_001OnNcCalcSize);

         // linux
         IGUI_MSG_LINK(WM_MOVE, pchannel, this, &interaction_impl::_001OnMove);
         IGUI_MSG_LINK(WM_SIZE, pchannel, this, &interaction_impl::_001OnSize);
         IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &interaction_impl::_001OnShowWindow);

         //IGUI_MSG_LINK(WM_WINDOWPOSCHANGING, pchannel, this,&interaction_impl::_001OnWindowPosChanging);
         //IGUI_MSG_LINK(WM_WINDOWPOSCHANGED, pchannel, this,&interaction_impl::_001OnWindowPosChanged);
         //IGUI_MSG_LINK(WM_GETMINMAXINFO, pchannel, this,&interaction_impl::_001OnGetMinMaxInfo);
         //IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this,&interaction_impl::_001OnSetFocus);
         //IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this,&interaction_impl::_001OnKillFocus);
//         IGUI_MSG_LINK(ca2m_PRODEVIAN_SYNCH, pchannel, this,&interaction_impl::_001OnProdevianSynch);
         ::user::interaction_impl::prio_install_message_routing(pchannel);
      }

      IGUI_MSG_LINK(WM_DESTROY, pchannel, this,&interaction_impl::_001OnDestroy);

   }


   void interaction_impl::defer_delayed_placement()
   {

      if(!m_puserinteraction->is_layout_experience_active())
      {

         if(m_bMoveEvent || m_bSizeEvent)
         {

            defer_fork("delayed_placement", [this]()
            {

               _thread_delayed_placement();

            });

         }

      }

   }


   void interaction_impl::_thread_delayed_placement()
   {

      while(m_tickLastPlacementEvent.elapsed() < 40 || m_puserinteraction->is_layout_experience_active())
      {

         if(!thread_sleep(10))
         {

            return;

         }

      }

      if(!thread_get_run())
      {

         return;

      }

      bool bMove = m_bMoveEvent && m_puserinteraction->layout().sketch().m_point != m_pointLastMove;

      m_bMoveEvent = false;

      if (bMove)
      {

         INFO("linux::interaction_impl Window Manager Move (%d, %d)", m_pointLastMove.x, m_pointLastMove.y);

         m_puserinteraction->move_to(m_pointLastMove);

         m_puserinteraction->set_reposition();

      }

      bool bSize = m_bSizeEvent && m_puserinteraction->layout().sketch().m_size != m_sizeLastSize;

      m_bSizeEvent = false;

      if (bSize)
      {

         INFO("linux::interaction_impl Window Manager Size (%d, %d)", m_sizeLastSize.cx, m_sizeLastSize.cy);

         m_puserinteraction->set_size(m_sizeLastSize);

         m_puserinteraction->set_need_layout();

      }

      if(bMove || bSize)
      {

         m_puserinteraction->display();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::_001OnMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::size, psize, pmessage);

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->m_eflagLayouting)
      {

         pmessage->m_bRet = true;

         return;

      }

      SCAST_PTR(::message::move, pmove, pmessage);

//      m_puserinteraction->window_state3().m_point = pmove->m_point;
//
//      if(m_puserinteraction->window_state3().m_point != m_puserinteraction->layout().sketch().m_point)
//      {
//
//         m_puserinteraction->move_to(pmove->m_point);
//
//         m_puserinteraction->set_reposition();
//
//         m_puserinteraction->post_redraw();
//
//      }
//
   }


   void interaction_impl::_001OnSize(::message::message * pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->m_eflagLayouting)
      {

         pmessage->m_bRet = true;

         return;

      }

      SCAST_PTR(::message::size, psize, pmessage);

//      m_puserinteraction->window_state3().m_size = psize->m_size;
//
//      if(m_puserinteraction->window_state3().m_size != m_puserinteraction->layout().sketch().m_size)
//      {
//
//         m_puserinteraction->set_size(psize->m_size);
//
//         m_puserinteraction->set_need_layout();
//
//         m_puserinteraction->post_redraw();
//
//      }

   }


   void interaction_impl::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if(!m_puserinteraction)
      {

         return;

      }

      if(pshowwindow->m_bShow)
      {

         INFO("linux::interaction_impl::_001OnShowWindow VISIBLE edisplay=%s", __cstr(m_puserinteraction->ui_state().m_edisplay3.m_eenum));

         m_puserinteraction->ModifyStyle(0, WS_VISIBLE);

         if(m_puserinteraction->layout().design().display() == ::display_iconic && !m_oswindow->is_iconic())
         {

            m_puserinteraction->hide();

            if(m_puserinteraction->m_windowrect.m_edisplayPrevious == ::display_iconic)
            {

               m_puserinteraction->_001OnDeiconify(::display_normal);

            }
            else
            {

               m_puserinteraction->_001OnDeiconify(m_puserinteraction->m_windowrect.m_edisplayPrevious);

            }

         }

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

         //x11_defer_check_configuration(m_oswindow);

      }
      else
      {

         m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);

      }

   }


   void interaction_impl::on_start_layout_experience(e_layout_experience elayout)
   {

      child_post_quit("delayed_placement");

   }


   void interaction_impl::on_end_layout_experience(e_layout_experience elayout)
   {

      defer_delayed_placement();

   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction_impl::on_layout(pgraphics);

   }


   void interaction_impl::_001OnDestroy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      {

         single_lock sl(get_context_application() == nullptr ? nullptr : get_context_application()->mutex(), TRUE);

         ::thread* pThread = ::get_thread();

         if (pThread != nullptr)
         {

            if (pThread->get_active_ui() == m_puserinteraction)
            {

               pThread->set_active_ui(nullptr);

            }

         }

      }

//      ::multithreading::post_quit_and_wait(m_pthreadProDevian, seconds(10));

//      if (m_puserinteraction->m_pthread != nullptr)
//      {
//
//         sync_lock sl(m_puserinteraction->m_pthread->mutex());
//
//         if(m_puserinteraction->m_pthread->m_puiptra != nullptr)
//         {
//
//            m_puserinteraction->m_pthread->m_puiptra->remove(m_puserinteraction);
//
//         }
//
//      }

      //Default();

   }


   void interaction_impl::PostNcDestroy()
   {

      Detach();

      if (!::is_null(m_oswindow))
      {

         m_oswindow->post_nc_destroy();

      }

      ::user::interaction_impl::PostNcDestroy();

   }


   void interaction_impl::on_final_release()
   {

      if (get_handle() != nullptr)
      {

         DestroyWindow();

      }
      else
      {

         PostNcDestroy();

      }

   }


   void interaction_impl::assert_valid() const
   {

      if (((interaction_impl *) this)->get_handle() == nullptr)
      {

         return;

      }

   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {

      ::object::dump(dumpcontext);

      dumpcontext << "\nm_hWnd = " << (void *)((interaction_impl *) this)->get_handle();

      /*

      if (get_handle() == nullptr || get_handle() == oswindow_BOTTOM ||
               get_handle() == oswindow_TOPMOST || get_handle() == oswindow_NOTOPMOST)
      {

         // not a normal interaction_impl - nothing more to dump
            return;

      }

      */

      /*

      if (!::is_window((oswindow) get_handle()))
      {

         // not a valid interaction_impl
         dumpcontext << " (illegal oswindow)";
         return; // don't do anything more

      }

      */

      __pointer(::user::interaction_impl) pWnd = (::user::interaction_impl *) this;
      if (pWnd.m_p != this)
         dumpcontext << " (Detached or temporary interaction_impl)";
      else
         dumpcontext << " (permanent interaction_impl)";

      char szBuf [64];

      ::rect rect;
      ((::user::interaction_impl *) this)->m_puserinteraction->get_window_rect(&rect);
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent __pointer(::interaction_impl) = " << (void *)((::user::interaction_impl *) this)->GetParent();

//      dumpcontext << "\nstyle = " << (void *)(dword_ptr)::GetWindowLong(get_handle(), GWL_STYLE);
      //    if (::GetWindowLong(get_handle(), GWL_STYLE) & WS_CHILD)
      //     dumpcontext << "\nid = " << __get_dialog_control_id(get_handle());

      dumpcontext << "\n";
   }

   bool interaction_impl::DestroyWindow()
   {

      if((get_handle() == nullptr))
      {

         return true;

      }

      if(m_oswindow->m_bMessageOnlyWindow)
      {

         ::user::interaction * pinteraction = m_puserinteraction;

         send_message(WM_DESTROY, 0, 0);

         send_message(WM_NCDESTROY, 0, 0);

         ::oswindow_remove_message_only_window(this);

         return true;

      }

      bool bResult = false;

      oswindow window = get_handle();

      if (window != nullptr)
      {

         bResult = ::destroy_window(window) != FALSE;

         //Detach();

      }

      return bResult;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Default interaction_impl implementation


   void interaction_impl::default_window_procedure(::message::base * pbase)

   {
      /*  if (m_pfnSuper != nullptr)
           return ::callWindowProc(m_pfnSuper, get_handle(), nMsg, wparam, lparam);


        WNDPROC pfnWndProc;
        if ((pfnWndProc = *GetSuperWndProcaddr()) == nullptr)
           return ::default_window_procedure(get_handle(), nMsg, wparam, lparam);

        else
           return ::callWindowProc(pfnWndProc, get_handle(), nMsg, wparam, lparam);*/


//      return 0;
   }

   /*
      WNDPROC* interaction_impl::GetSuperWndProcaddr()
      {
         // Note: it is no longer necessary to override GetSuperWndProcaddr
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


   void interaction_impl::get_window_text(string & rectString)
   {

      rectString = m_strWindowText;

   }

   /*
      i32 interaction_impl::GetDlgItemText(i32 nID, string & rectString) const
      {
         ASSERT(::is_window((oswindow) get_handle()));
         rectString = "";    // is_empty without deallocating

         oswindow hWnd = ::GetDlgItem(get_handle(), nID);
         if (hWnd != nullptr)
         {
            i32 nLen = ::GetWindowTextLength(hWnd);
            ::GetWindowText(hWnd, rectString.get_string_buffer(nLen), nLen+1);
            rectString.ReleaseBuffer();
         }

         return (i32)rectString.get_length();
      }
   */

   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* pwndpl)

   {
      /*    ASSERT(::is_window((oswindow) get_handle()));
          pwndpl->length = sizeof(WINDOWPLACEMENT);

          return ::GetWindowPlacement(get_handle(), pwndpl) != FALSE;*/

      return false;
   }

   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* pwndpl)

   {
      /*      ASSERT(::is_window((oswindow) get_handle()));
            ((WINDOWPLACEMENT*)pwndpl)->length = sizeof(WINDOWPLACEMENT);

            return ::SetWindowPlacement(get_handle(), pwndpl) != FALSE;*/

      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
// /*   void interaction_impl::OnDrawItem(i32 /*nIDCtl*/, LPDRAWITEMSTRUCT pDrawItemStruct)

   // {

   // reflect notification to child interaction_impl control
   //  if (ReflectLastMsg(pDrawItemStruct->hwndItem))

   //   return;     // eat it

   // not handled - do default
//      Default();
   // }

   // Drawing: for all 4 control types
//   i32 interaction_impl::OnCompareItem(i32 /*nIDCtl*/, LPCOMPAREITEMSTRUCT pCompareItemStruct)

   // {
   //  // reflect notification to child interaction_impl control
   //LRESULT lResult;
//      if (ReflectLastMsg(pCompareItemStruct->hwndItem, &lResult))

   //       return (i32)lResult;        // eat it

   // not handled - do default
   //  return (i32)Default();
//   }

   // void interaction_impl::OnDeleteItem(i32 /*nIDCtl*/, LPDELETEITEMSTRUCT pDeleteItemStruct)

   //{
   // reflect notification to child interaction_impl control
   // if (ReflectLastMsg(pDeleteItemStruct->hwndItem))

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

//   LRESULT interaction_impl::OnNTCtlColor(WPARAM wparam, LPARAM lparam)
//
//   {
//      return 0;
//   }
//
//
//   void interaction_impl::PrepareForHelp()
//   {
//   }




   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      channel::route_command_message(pcommand);

   }


   void interaction_impl::on_control_event(::user::control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


//   void interaction_impl::_002OnDraw(::image * pimage)
//   {
//
//   }
//

   tick     tickDebugmessage_handlerTime;
   int      iDebugmessage_handlerTime;
   tick     tickLastMouseMove;
   tick     tickLastPaint;


   void interaction_impl::message_handler(::message::base * pbase)
   {

      if(pbase->m_id == WM_TIMER)
      {

         //m_pthread->step_timer();

      }
      else if(pbase->m_id == WM_LBUTTONDOWN)
      {

         TRACE("WM_LBUTTONDOWN (0)");

      }
      else if(pbase->m_id == WM_MOUSEMOVE)
      {

         g_iMouseMove++;

         //TRACE("linux::interaction_impl::message_handler WM_MOUSEMOVE");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if(pbase->m_id == WM_PAINT)
      {

      }
      else if(pbase->m_id == WM_LBUTTONUP)
      {

         TRACE("WM_LBUTTONUP (0)");

      }

      if(::is_set(m_puserinteraction))
      {

         m_puserinteraction->pre_translate_message(pbase);

      }

      if(tickDebugmessage_handlerTime.timeout(1))
      {

         iDebugmessage_handlerTime = 0;

      }
      else
      {

         if(iDebugmessage_handlerTime > 20)
         {

            writeln("interaction_impl::message handler flooded?");

         }
         else
         {

            iDebugmessage_handlerTime++;

         }

      }

      if(m_puserinteraction != nullptr)
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

            //m_puserinteraction->pre_translate_message(pbase);

            //if (pbase->m_bRet)
            //{

              // return;

            //}

            //pbase->m_uiMessageFlags |= 1;

         }

      }

      if(pbase->m_id == WM_KEYDOWN || pbase->m_id == WM_KEYUP || pbase->m_id == WM_CHAR)
      {

         ::message::key * pkey = (::message::key *) pbase;

         Session.translate_os_key_message(pkey);

         if(pbase->m_id == WM_KEYDOWN)
         {

            try
            {

               Session.set_key_pressed(pkey->m_ekey, true);

            }
            catch(...)
            {

            }

         }
         else if(pbase->m_id == WM_KEYUP)
         {

            try
            {

               Session.set_key_pressed(pkey->m_ekey, false);

            }
            catch(...)
            {

            }

         }

      }

      pbase->m_lresult = 0;

      if(pbase->m_id == WM_MOUSELEAVE)
      {

         _000OnMouseLeave(pbase);

         return;

      }

      if(pbase->m_id == WM_LBUTTONDOWN ||
            pbase->m_id == WM_LBUTTONUP ||
            pbase->m_id == WM_MBUTTONDOWN ||
            pbase->m_id == WM_MBUTTONUP ||
            pbase->m_id == WM_RBUTTONDOWN ||
            pbase->m_id == WM_RBUTTONUP ||
            pbase->m_id == WM_MOUSEMOVE ||
            pbase->m_id == WM_MOUSEMOVE)
//         pbase->m_id == WM_MOUSEWHEEL)
      {

         if(::is_set(m_puserinteraction) && !m_puserinteraction->m_bUserPrimitiveOk)
         {

            return;

         }

         if(pbase->m_id == WM_LBUTTONDOWN)
         {

            TRACE("WM_LBUTTONDOWN");

         }

         ::message::mouse * pmouse = (::message::mouse *) pbase;

         Session.on_ui_mouse_message(pmouse);

         if(get_context_session() != nullptr)
         {

            Session.m_pointCursor = pmouse->m_point;

         }

         if(m_puserinteraction != nullptr && m_puserinteraction->get_context_session()  != nullptr && m_puserinteraction->get_context_session() != get_context_session())
         {

            Sess(m_puserinteraction->get_context_session()).m_pointCursor = pmouse->m_point;

         }

         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {
            pmouse->m_bTranslated = true;
            ::rect rectWindow;
            if(m_bScreenRelativeMouseMessagePosition)
            {

               INFO("Screen Relative Mouse Message Position");
               ::rect rectWindow32;
               ::get_window_rect((oswindow) get_handle(), &rectWindow32);
               ::copy(rectWindow, rectWindow32);
            }
            else
            {
               m_puserinteraction->get_window_rect(rectWindow);
            }
            if(System.get_monitor_count() > 0)
            {
               ::rect rcMonitor;
               System.get_monitor_rect(0, &rcMonitor);
               if(rectWindow.left >= rcMonitor.left)
                  pmouse->m_point.x += (LONG) rectWindow.left;
               if(rectWindow.top >= rcMonitor.top)
                  pmouse->m_point.y += (LONG) rectWindow.top;
            }
            else
            {
               if(rectWindow.left >= 0)
                  pmouse->m_point.x += (LONG) rectWindow.left;
               if(rectWindow.top >= 0)
                  pmouse->m_point.y += (LONG) rectWindow.top;
            }
         }

         if(pbase->m_id == WM_MOUSEMOVE)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;
         }

         if(pbase->m_id == WM_LBUTTONDOWN)
         {


            //message_box(NULL, "WM_LBUTTONDOWN", MB_OK);


            TRACE("WM_LBUTTONDOWN");

         }

         _008OnMouse(pmouse);

         return;

      }
      else if(pbase->m_id == WM_KEYDOWN ||
              pbase->m_id == WM_KEYUP ||
              pbase->m_id == WM_CHAR)
      {

         ::message::key * pkey = (::message::key *) pbase;

         __pointer(::user::interaction) puiFocus =  get_focus_primitive();

         if(puiFocus != nullptr
               && puiFocus->is_window()
               && puiFocus->GetTopLevel() != nullptr
               && puiFocus != m_puserinteraction)
         {

            puiFocus->send(pkey);

            if(pbase->m_bRet)
            {

               return;

            }

         }
         else if(!pkey->m_bRet)
         {

            if(m_puserinteraction != nullptr)
            {

               m_puserinteraction->_000OnKey(pkey);

               if(pbase->m_bRet)
               {

                  return;

               }

            }

         }

         default_window_procedure(pbase);

         return;

      }

      if(pbase->m_id == EVENT_MESSAGE)
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

      if(::is_set(m_puserinteraction))
      {

         m_puserinteraction->route_message(pbase);

      }
      else
      {

         route_message(pbase);

      }

      if(pbase->m_bRet)
      {

         return;

      }

      default_window_procedure(pbase);

   }


//   bool interaction_impl::OnCommand(WPARAM wparam, LPARAM lparam)
//   {
//
//      UNREFERENCED_PARAMETER(wparam);
//      UNREFERENCED_PARAMETER(lparam);
//
//      return false;
//
//   }
//
//
//   bool interaction_impl::OnNotify(WPARAM, LPARAM lparam, LRESULT* pResult)
//   {
//
//      return false;
//
//   }


//   ::user::interaction * interaction_impl::GetParent()
//   {
//
//      if(!::is_window((oswindow) get_handle()))
//      {
//
//         return nullptr;
//
//      }
//
//      if(get_handle() == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      //return ::linux::interaction_impl::from_handle(::GetParent(get_handle()));
//
//      return nullptr;
//
//   }


//   ::user::interaction * interaction_impl::GetTopLevel()
//   {
//
//      if(!::is_window((oswindow) get_handle()))
//         return nullptr;
//
//      if(get_handle() == nullptr)
//         return nullptr;
//
//      return m_puserinteraction;
//
//   }


   /*
      ::user::interaction * interaction_impl::GetTopLevelOwner()
      {
         if (get_handle() == nullptr) // no oswindow attached
            return nullptr;

         ASSERT_VALID(this);

   //      oswindow hWndOwner = get_handle();
     //    oswindow hWndT;
       //  while ((hWndT = ::GetWindow(hWndOwner, GW_OWNER)) != nullptr)
         //   hWndOwner = hWndT;

   //      return ::linux::interaction_impl::from_handle(hWndOwner);
           return nullptr;
      }

      ::user::interaction * interaction_impl::GetParentOwner()
      {
         if (get_handle() == nullptr) // no oswindow attached
            return nullptr;

         ASSERT_VALID(this);

   //         oswindow hWndParent = get_handle();
   //         oswindow hWndT;
   //         while ((::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) &&
   //            (hWndT = ::GetParent(hWndParent)) != nullptr)
   //         {
   //            hWndParent = hWndT;
   //         }
   //
   //         return ::linux::interaction_impl::from_handle(hWndParent);

   //return nullptr;
   //}

   */

//   bool interaction_impl::IsTopParentActive()
//   {
//      ASSERT(get_handle() != nullptr);
//      ASSERT_VALID(this);
//
//      __pointer(::user::interaction)pWndTopLevel=EnsureTopLevel();
//
//      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
//   }

//   void interaction_impl::ActivateTopParent()
//   {
//      // special activate logic for floating toolbars and palettes
//      __pointer(::user::interaction) pActiveWnd = GetForegroundWindow();
////      if (pActiveWnd == nullptr || !(LNX_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(LNX_WINDOW(pActiveWnd)->get_handle(), get_handle())))
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

         __pointer(::user::frame_window) pFrameWnd = nullptr;
         if(m_puserinteraction != this)
            pFrameWnd =  (m_puserinteraction);
         else
            pFrameWnd =  (this);
         if (pFrameWnd == nullptr || !pFrameWnd->is_frame_window())
            pFrameWnd = GetParentFrame();

         if (pFrameWnd != nullptr)
         {
            __pointer(::user::frame_window) pTemp;
            while ((pTemp = pFrameWnd->GetParentFrame()) != nullptr)
               pFrameWnd = pTemp;
         }
         return pFrameWnd;
      }*/

   /*   __pointer(::interaction_impl) interaction_impl::GetSafeOwner(::interaction_impl * pParent, oswindow* pWndTop)
      {
         oswindow hWnd = GetSafeOwner_((oswindow) pParent->get_handle(), pWndTop);
         return ::linux::interaction_impl::from_handle(hWnd);
      }
   */
//   i32 interaction_impl::message_box(const char * pszText, const char * pszcaption, UINT nType)
//   {
//
//      string strCaption;
//
//      if (pszcaption == nullptr)
//      {
//
//         strCaption = get_context_application()->m_strAppName;
//
//      }
//      else
//      {
//
//         strCaption = pszcaption;
//
//      }
//
//      i32 nResult = ::os_message_box((oswindow)get_handle(), pszText, strCaption, nType);
//
//      return nResult;
//
//   }


   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::view) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID


//   i32 interaction_impl::SetScrollPos(i32 nBar, i32 nPos, bool bRedraw)
//   {
////      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
//      return 0;
//   }
//
//   i32 interaction_impl::GetScrollPos(i32 nBar) const
//   {
//      //return ::GetScrollPos(get_handle(), nBar);
//      return 0;
//   }
//
//   void interaction_impl::SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos, bool bRedraw)
//   {
//      //::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
//   }

//   void interaction_impl::GetScrollRange(i32 nBar, LPINT pMinPos, LPINT lpMaxPos) const
//
//   {
//      //::GetScrollRange(get_handle(), nBar, pMinPos, lpMaxPos);
//
//   }
//
//   // Turn on/off non-control scrollbars
//   //   for WS_?SCROLL scrollbars - show/hide them
//   //   for control scrollbar - enable/disable them
//   void interaction_impl::EnableScrollBarCtrl(i32 nBar, bool bEnable)
//   {
//      // WS_?SCROLL scrollbar - show or hide
//      ShowScrollBar(nBar, bEnable);
//   }

   /*
      bool interaction_impl::SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, bool bRedraw)

      {
         ASSERT(pScrollInfo != nullptr);


         oswindow hWnd = get_handle();
         pScrollInfo->cbSize = sizeof(*lpScrollInfo);

         ::SetScrollInfo(hWnd, nBar, pScrollInfo, bRedraw);

         return true;
      }

      bool interaction_impl::GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, UINT nMask)

      {
         UNREFERENCED_PARAMETER(nMask);
         ASSERT(pScrollInfo != nullptr);


         oswindow hWnd = get_handle();
         return ::GetScrollInfo(hWnd, nBar, pScrollInfo) != FALSE;

      }
   */
//   i32 interaction_impl::GetScrollLimit(i32 nBar)
//   {
//      i32 nMin, nMax;
//      GetScrollRange(nBar, &nMin, &nMax);
//      /*      SCROLLINFO info;
//            if (GetScrollInfo(nBar, &info, SIF_PAGE))
//            {
//               nMax -= __max(info.nPage-1,0);
//            }*/
//      return nMax;
//   }
//
//   void interaction_impl::ScrollWindow(i32 xAmount, i32 yAmount,
//                                       const ::rect & rect, const ::rect & lpClipRect)
//
//   {
//      /*      ASSERT(::is_window((oswindow) get_handle()));
//
//            if (is_window_visible() || prect != nullptr || lpClipRect != nullptr)
//
//            {
//               // When visible, let oswindows do the scrolling
//               ::ScrollWindow(get_handle(), xAmount, yAmount, prect, lpClipRect);
//
//            }
//            else
//            {
//               // oswindows does not perform any scrolling if the interaction_impl is
//               // not visible.  This leaves child windows unscrolled.
//               // To account for this oversight, the child windows are moved
//               // directly instead.
//               oswindow hWndChild = ::GetWindow(get_handle(), GW_CHILD);
//               if (hWndChild != nullptr)
//               {
//                  for (; hWndChild != nullptr;
//                     hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
//                  {
//                     ::rect rect;
//                     ::get_window_rect(hWndChild, &rect);
//                     _001ScreenToClient(&rect);
//                     ::set_window_pos(hWndChild, nullptr,
//                        rect.left+xAmount, rect.top+yAmount, 0, 0,
//                        SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
//                  }
//               }
//            }
//      */
//   }
//
//
//   void interaction_impl::CalcWindowRect(RECT * pClientRect, UINT nAdjustType)
//   {
//
//      /*DWORD dwExStyle = GetExStyle();
//      if (nAdjustType == 0)
//         dwExStyle &= ~WS_EX_CLIENTEDGE;
//      ::AdjustWindowRectEx(pClientRect, GetStyle(), FALSE, dwExStyle);*/
//
//   }
//
//   /////////////////////////////////////////////////////////////////////////////
//   // Special keyboard/system command processing
//
//   bool interaction_impl::HandleFloatingSysCommand(UINT nID, LPARAM lparam)
//
//   {
//      /*      __pointer(::user::interaction) pParent = GetTopLevelParent();
//            switch (nID & 0xfff0)
//            {
//            case SC_PREVWINDOW:
//            case SC_NEXTWINDOW:
//               if (LOWORD(lparam) == VK_F6 && pParent != nullptr)
//
//               {
//                  pParent->SetFocus();
//                  return true;
//               }
//               break;
//
//            case SC_CLOSE:
//            case SC_KEYMENU:
//               // Check lparam.  If it is 0L, then the ::account::user may have done
//
//               // an Alt+Tab, so just ignore it.  This breaks the ability to
//               // just press the Alt-key and have the first menu selected,
//               // but this is minor compared to what happens in the Alt+Tab
//               // case.
//               if ((nID & 0xfff0) == SC_CLOSE || lparam != 0L)
//
//               {
//                  if (pParent != nullptr)
//                  {
//                     // Sending the above WM_SYSCOMMAND may destroy the cast,
//                     // so we have to be careful about restoring activation
//                     // and focus after sending it.
//                     oswindow hWndSave = get_handle();
//                     oswindow hWndFocus = ::GetFocus();
//                     pParent->SetActiveWindow();
//                     pParent->send_message(WM_SYSCOMMAND, nID, lparam);
//
//
//                     // be very careful here...
//                     if (::is_window(hWndSave))
//                        ::SetActiveWindow(hWndSave);
//                     if (::is_window(hWndFocus))
//                        ::SetFocus(hWndFocus);
//                  }
//               }
//               return true;
//            }
//            return false;*/
//
//      return false;
//   }

//   void interaction_impl::WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage)
//   {
//      ASSERT(puiStop == nullptr || puiStop->is_window());
//      ASSERT(pmessage != nullptr);
//
//      SCAST_PTR(::message::base, pbase, pmessage);
//      // walk from the target interaction_impl up to the hWndStop interaction_impl checking
//      //  if any interaction_impl wants to translate this message
//
//      for (__pointer(::user::interaction) pinteraction = pbase->m_puserinteraction; pinteraction != nullptr; pinteraction->GetParent())
//      {
//
//         pinteraction->pre_translate_message(pmessage);
//
//         if(pmessage->m_bRet)
//            return; // trapped by target interaction_impl (eg: accelerators)
//
//         // got to hWndStop interaction_impl without interest
//         if(pinteraction == puiStop)
//            break;
//
//      }
//      // no special processing
//   }
//
//
//   bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
//   {
//
//      return false;
//
//   }
//
//
//   bool PASCAL interaction_impl::ReflectLastMsg(oswindow hWndChild, LRESULT* pResult)
//   {
//      // get the ::collection::map, and if no ::collection::map, then this message does not need reflection
//      /*      single_lock sl(afxMutexHwnd(), TRUE);
//            hwnd_map * pMap = afxMapHWND();
//            if (pMap == nullptr)
//               return FALSE;
//
//            // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
//            __pointer(::interaction_impl) pWnd =  (pMap->lookup_permanent(hWndChild)); */
//
//      __s_throw(todo());
////      __pointer(::user::interaction) pWnd =  (FromHandlePermanent(hWndChild));
////      ASSERT(pWnd == nullptr || pWnd->get_handle() == hWndChild);
////      if (pWnd == nullptr)
////      {
////         return FALSE;
////      }
////
////      // only OLE controls and permanent windows will get reflected msgs
////      ASSERT(pWnd != nullptr);
////      return pWnd->SendChildNotifyLastMsg(pResult);
//   }
//
//   bool interaction_impl::OnChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//
//   {
//
//      return ReflectChildNotify(uMsg, wparam, lparam, pResult);
//
//   }
//
//   bool interaction_impl::ReflectChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//
//   {
//      UNREFERENCED_PARAMETER(wparam);
//      // Note: reflected messages are send directly to interaction_impl::OnWndMsg
//      //  and interaction_impl::_001OnCommand for speed and because these messages are not
//      //  routed by normal _001OnCommand routing (they are only dispatched)
//
//      switch (uMsg)
//      {
//      // normal messages (just wparam, lparam through OnWndMsg)
//
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
//
//         return FALSE;
//
//      // special case for WM_COMMAND
//      case WM_COMMAND:
//      {
//         // reflect the message through the message ::collection::map as OCM_COMMAND
//         /* xxx         i32 nCode = HIWORD(wparam);
//         if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_COMMAND), nullptr, nullptr))
//         {
//         if (pResult != nullptr)
//         *pResult = 1;
//         return TRUE;
//         } */
//      }
//      break;
//
//      // special case for WM_NOTIFY
//      /*      case WM_NOTIFY:
//               {
//                  // reflect the message through the message ::collection::map as OCM_NOTIFY
//                  NMHDR* pNMHDR = (NMHDR*)lparam;
//
//                  //            i32 nCode = pNMHDR->code;
//                  //            __NOTIFY notify;
//                  //          notify.pResult = pResult;
//                  //        notify.pNMHDR = pNMHDR;
//                  // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
//               }
//
//               // other special cases (WM_CTLCOLOR family)*/
//      default:
//         if (uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
//         {
//            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
//            /*__CTLCOLOR ctl;
//            ctl.hDC = (HDC)wparam;
//            ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
//            //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
//            ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);
//
//            // reflect the message through the message ::collection::map as OCM_CTLCOLOR
//            bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
//            if ((HBRUSH)*pResult == nullptr)
//            bResult = FALSE;
//            return bResult;*/
//            return false;
//         }
//         break;
//      }
//
//      return false;   // let the parent handle it
//   }
//
//   void interaction_impl::OnParentNotify(UINT message, LPARAM lparam)
//
//   {
//      if ((LOWORD(message) == WM_CREATE || LOWORD(message) == WM_DESTROY))
//      {
//         if (ReflectLastMsg((oswindow)lparam))
//
//            return;     // eat it
//      }
//      // not handled - do default
////      Default();
//   }
//
//   void interaction_impl::OnSetFocus(::user::interaction *)
//   {
//      bool bHandled;
//
//      bHandled = FALSE;
//      if( !bHandled )
//      {
////         Default();
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
//
//   void interaction_impl::OnSysColorChange()
//   {
//
//   }
//
//
//   bool gen_GotScrollLines;
//
//
//   void interaction_impl::OnSettingChange(UINT uFlags, const char * pszSection)
//
//   {
//
//      gen_GotScrollLines = FALSE;
//
//      interaction_impl::OnDisplayChange(0, 0);
//
//   }
//
//
//   LRESULT interaction_impl::OnDisplayChange(WPARAM, LPARAM)
//   {
//
//      if (!(GetStyle() & WS_CHILD))
//      {
//
//         const MESSAGE* pMsg = GetCurrentMessage();
//
//         send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam, TRUE, TRUE);
//
//      }
//
////      return Default();
//
//      return 0;
//
//   }
//
//
//   LRESULT interaction_impl::OnDragList(WPARAM, LPARAM lparam)
//
//   {
//
//      __throw(not_implemented());
////
////      LPDRAGLISTINFO pInfo = (LPDRAGLISTINFO)lparam;
//
////      ASSERT(pInfo != nullptr);
//
////
////      LRESULT lResult;
////      if (ReflectLastMsg(pInfo->hWnd, &lResult))
//
////         return (i32)lResult;    // eat it
////
////      // not handled - do default
////      return (i32)Default();
//   }
//
////
////   void interaction_impl::present()
////   {
////
////      _001UpdateWindow();
////
////   }
////
//
////   void interaction_impl::prodevian_task()
////   {
////
////
////      if (m_pthreadProDevian.is_null())
////      {
////
////         m_pthreadProDevian = fork([&]()
////         {
////
////            DWORD tickStart;
////
////            while (::thread_get_run())
////            {
////
//// auto tickStart = ::tick::now();
////
////               bool bUpdateScreen = false;
////
////               if (!m_puserinteraction->m_bLockWindowUpdate)
////               {
////
////                  if (m_puserinteraction->m_bProDevian ||
////                        m_puserinteraction->has_pending_graphical_update() ||
////                        m_puserinteraction->check_need_layout())
////                  {
////
////                     _001UpdateBuffer();
////
////                     m_puserinteraction->on_after_graphical_update();
////
////                     bUpdateScreen = true;
////
////                  }
////
////               }
////               else
////               {
////
////                  output_debug_string("window is locked for drawing update");
////
////                  fflush(stdout);
////
////               }
////
////               if(bUpdateScreen)
////               {
////
////                  windowing_output_debug_string("\nGoing to _001UpdateScreen");
////
////                  fflush(stdout);
////
////                  _001UpdateScreen();
////
////               }
////
////               DWORD dwDiff = tickStart.elapsed();
////
////               if (dwDiff < 20)
////               {
////
////                  Sleep(20 - dwDiff);
////
////               }
////
////               //Sleep(500);
////
////            }
////
////            m_pthreadProDevian.release();
////
////         });
////
////      }
////
////
////   }
//
//
////   void interaction_impl::set_need_redraw()
////   {
////
////      ::user::interaction_impl::set_need_redraw();
////
////   }
//

   void interaction_impl::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

//      Default();

//      if(m_puserinteraction->is_message_only_window())
//      {
//
//         TRACE("good : opt out!");
//
//      }
//      else
//      {
//
//         m_pthreadDraw = fork([&]()
//         {
//
//
//         });
//
//      }
//
   }



//   bool CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lparam)
//
//   {
//      user::oswindow_array * phwnda = (user::oswindow_array *) lparam;
//
//      phwnda->add(hwnd);
//      return TRUE;
//   }
//
//   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
//   {
//      __s_throw(not_implemented());
////      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
//   }

//   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
//   {
//
//      _001DeferPaintLayeredWindowBackground(pgraphics);
//
//   }



//   class print_window :
//      virtual ::object
//   {
//   public:
//
//
//
//      manual_reset_event m_event;
//      oswindow m_hwnd;
//      HDC m_hdc;
//
//      print_window(::object * pobject, oswindow hwnd, HDC hdc, DWORD tickTimeout) :
//         ::object(pobject)
//      {
//         m_event.ResetEvent();
//         m_hwnd = hwnd;
//         m_hdc = hdc;
//
//         fork();
//#undef timeout
//
//         if(m_event.wait(millis(tickTimeout)).timeout())
//         {
//            TRACE("print_window::time_out");
//         }
//      }
//
//
//      virtual ::estatus     run() override
//      {
//
//         try
//         {
////            HANDLE hevent = (HANDLE) pprintwindow->m_event.get_os_data();
//            //          __throw(not_implemented());
//            /*            ::PrintWindow(pprintwindow->m_hwnd, pprintwindow->m_hdc, 0);
//                        ::SetEvent(hevent);*/
//         }
//         catch(...)
//         {
//         }
//         return ::success;
//      }
//   };
//
//   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
//   {
//
//      ::rect rectClient;
//
//      m_puserinteraction->get_client_rect(rectClient);
//
//
//      //pgraphics->FillSolidRect(rectClient, 0x00000000);
//
//      //return;
//      ::rect rectUpdate;
//      m_puserinteraction->get_window_rect(rectUpdate);
////      SetViewportOrgEx(hdc, 0, 0, nullptr);
//      ::rect rectPaint;
//      rectPaint = rectUpdate;
//      m_puserinteraction->_001ScreenToClient(rectPaint);
//      user::oswindow_array wndaApp;
//
//
//      HRGN rgnWindow;
//      HRGN rgnIntersect;
//      HRGN rgnUpdate = nullptr;
//
//      __throw(not_implemented());
//      /*
//            rgnWindow = CreateRectRgn(0, 0, 0, 0);
//            rgnIntersect = CreateRectRgn(0, 0, 0, 0);
//      */
//      //      i32 iCount = wndaApp.get_count();
//
//      __throw(not_implemented());
//   }
//
//   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
//   {
//      UNREFERENCED_PARAMETER(pmessage);
//   }


   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {

      set_need_redraw();

      //m_puserinteraction->defer_start_prodevian();

   }


   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {

      set_need_redraw();

   }


   bool interaction_impl::_is_window() const
   {

      return ::is_window(m_oswindow) != FALSE;

   }


   oswindow interaction_impl::get_handle() const
   {

      return m_oswindow;

   }


   void interaction_impl::_001OnExitIconic()
   {

      if(::is_null(m_oswindow))
      {

         return;

      }

      m_oswindow->exit_iconify();

   }


   void interaction_impl::_001OnExitFullScreen()
   {

      if(::is_null(m_oswindow))
      {

         return;

      }

      m_oswindow->exit_full_screen();

   }


   void interaction_impl::_001OnExitZoomed()
   {

      if(::is_null(m_oswindow))
      {

         return;

      }

      x11_sync([this]()
      {

         m_oswindow->exit_zoomed();

      });

   }



//   bool interaction_impl::set_window_pos(iptr z, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags)
//   {
//
//      if(!(nFlags & SWP_NOMOVE))
//      {
//
//         m_puserinteraction->m_pointRequest = ::point(x, y);
//
//      }
//
//      if(!(nFlags & SWP_NOSIZE))
//      {
//
//         m_puserinteraction->m_sizeRequest = ::size(cx, cy);
//
//      }
//
//      if(!::set_window_pos(get_handle(), (oswindow)z, x, y, cx, cy, nFlags))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }





//   void interaction_impl::MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight, bool bRepaint)
//   {
//
//      set_window_pos(0, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);
//
//   }


//   ::point interaction_impl::client_screen_top_left()
//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return pointd(0.0,0.0);
//
//      }
//
//      return rectWindow.top_left();
//
//   }
//
//
//   bool interaction_impl::_001ClientToScreen(RECT * prect)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left   += (LONG) rectWindow.left;

//      prect->right  += (LONG) rectWindow.left;

//      prect->top    += (LONG) rectWindow.top;

//      prect->bottom += (LONG) rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ClientToScreen(LPPOINT ppoint)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     += (LONG) rectWindow.left;

//      ppoint->y     += (LONG) rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ClientToScreen(RECT64 * prect)

//   {
//
//      ::rect rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left   += rectWindow.left;

//      prect->right  += rectWindow.left;

//      prect->top    += rectWindow.top;

//      prect->bottom += rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ClientToScreen(POINT64 * ppoint)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     += rectWindow.left;

//      ppoint->y     += rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ScreenToClient(RECT * prect)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left   -= (LONG) rectWindow.left;

//      prect->right  -= (LONG) rectWindow.left;

//      prect->top    -= (LONG) rectWindow.top;

//      prect->bottom -= (LONG) rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ScreenToClient(LPPOINT ppoint)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     -= (LONG) rectWindow.left;

//      ppoint->y     -= (LONG) rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ScreenToClient(RECT64 * prect)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left   -= rectWindow.left;

//      prect->right  -= rectWindow.left;

//      prect->top    -= rectWindow.top;

//      prect->bottom -= rectWindow.top;

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::_001ScreenToClient(POINT64 * ppoint)

//   {
//
//      ::rect64 rectWindow;
//
//      if(!get_window_rect(rectWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     -= rectWindow.left;

//      ppoint->y     -= rectWindow.top;

//
//      return true;
//
//   }


//   bool interaction_impl::_001GetWindowRect(RECT64 * prect)
//   {
//
//      return ::user::interaction_impl::get_window_rect(prect);
//
//
//
//
//      if(!::is_window((oswindow) get_handle()))
//      {
//
//         return false;
//
//      }
//
//      // if it is temporary interaction_impl - probably not ca2 wrapped interaction_impl
//      //if(m_puserinteraction == nullptr || m_puserinteraction == this)
//      {
//         ::rect rect32;
//
//         if(!::get_window_rect((oswindow) get_handle(), rect32))
//         {
//
//            return false;
//
//         }
//
//         ::copy(prect, rect32);
//
//
//      }
////      else
//      {
//         //      primitive_impl::get_window_rect(prect);
//
//      }
//
//      return true;
//
//   }
//
//
//   bool interaction_impl::get_window_rect(RECT64 * prect)
//
//   {
//
//      if(!_001GetWindowRect(prect))
//
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }
//
//   bool interaction_impl::get_client_rect(RECT64 * prect)
//
//   {
//
//
//      return ::user::interaction_impl::get_client_rect(prect);
//
//
//      if(!::is_window((oswindow) get_handle()))
//      {
//
//         return false;
//
//      }
//      // if it is temporary interaction_impl - probably not ca2 wrapped interaction_impl
//      //if(m_puserinteraction == nullptr || m_puserinteraction == this)
//      {
//
//         ::rect rect32;
//
//         //if(!::get_client_rect((oswindow) get_handle(), rect32))
//         //{
//
//         // return false;
//
//         //}
//
//         rect64 r = m_puserinteraction->m_rectParentClient;
//
//         rect.offset(rect.top_left());
//
//         *prect = r;
//
//
//      }
//      //else
//      {
//         // interaction::get_client_rect(prect);
//
//      }
//
//      return true;
//
//   }


//   id interaction_impl::SetDlgCtrlId(id id)
//   {
//
//      return m_puserinteraction->SetDlgCtrlId(id);
//
//   }
//
//
//   id interaction_impl::GetDlgCtrlId()
//   {
//
//      return m_puserinteraction->GetDlgCtrlId();
//
//   }
//
//
//   bool interaction_impl::WfiOnStartDock()
//   {
//
//      return true;
//
//   }


//   void interaction_impl::WfiOnDock(edisplay edisplay)
//   {
//
//   }


//   void interaction_impl::prodevian_prepare_down()
//   {
//
//   }


//   void interaction_impl::prodevian_prepare_up()
//   {
//
//   }


//   void interaction_impl::WfiOnRestore()
//   {
//
//      if(m_puserinteraction != nullptr)
//      {
//
//         m_puserinteraction->dis = ::display_normal;
//
//      }
//
//      ::show_window(m_oswindow, display_normal);
//
//   }


//   void interaction_impl::WfiOnMinimize(bool bNoActivate)
//   {
//
//      m_puserinteraction->display(display_iconic);
//
//   }


//   void interaction_impl::WfiOnMaximize()
//   {
//
//   }


//   void interaction_impl::WfiOnFullScreen()
//   {
//
//      get_handle()->full_screen(nullptr);
//
//   }


//   void interaction_impl::WfiOnExitFullScreen()
//   {
//
//   }


//   void interaction_impl::WfiOnClose()
//   {
//
//   }


//   void interaction_impl::WfiOnNotifyIcon()
//   {
//
//   }


   bool interaction_impl::layout().is_iconic()
   {

      if(!::is_window(m_oswindow))
      {

         return false;

      }

#ifdef LINUX

      return m_puserinteraction->layout().design().display() == ::display_iconic;

#else

      if(GetExStyle() & WS_EX_LAYERED)
      {

         return m_puserinteraction->m_edisplay == ::display_iconic;

      }
      else
      {

         return ::is_iconic((oswindow) get_handle()) != FALSE;

      }

#endif

   }


   LONG_PTR interaction_impl::get_window_long_ptr(i32 nIndex) const
   {

      return ::GetWindowLongPtr((oswindow) get_handle(), nIndex);

   }


   LONG_PTR interaction_impl::set_window_long_ptr(i32 nIndex, LONG_PTR lValue)
   {

      return ::SetWindowLongPtr((oswindow) get_handle(), nIndex, lValue);

   }





   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const ::user::interaction_impl& wnd) const
   {
      return wnd.get_handle() ==((interaction_impl *)this)->get_handle();
   }

   bool interaction_impl::operator!=(const ::user::interaction_impl& wnd) const
   {
      return wnd.get_handle() != ((interaction_impl *)this)->get_handle();
   }


   DWORD interaction_impl::GetStyle() const
   {

      return (DWORD)::GetWindowLong((oswindow) get_handle(), GWL_STYLE);

   }


   DWORD interaction_impl::GetExStyle() const
   {

      return (DWORD)::GetWindowLong((oswindow) get_handle(), GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      set_window_long(GWL_STYLE, (GetStyle() | dwAdd) & ~(dwRemove));

      if(nFlags != 0)
      {

         //set_window_pos(0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | nFlags);
         set_need_redraw();

      }

      return true;

   }


   bool interaction_impl::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      set_window_long(GWL_EXSTYLE, (GetExStyle() | dwAdd) & ~(dwRemove));

      if(nFlags != 0)
      {

         //set_window_pos(0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | nFlags);
         set_need_redraw();

      }

      return true;

   }


   void interaction_impl::set_owner(::user::interaction * pOwnerWnd)
   {
//      m_puiOwner = pOwnerWnd;
      m_puserinteraction->SetOwner((pOwnerWnd));
   }


   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)

   {

      return ::user::interaction_impl::send_message(message, wparam, lparam);


   }


   bool interaction_impl::post_message(UINT message, WPARAM wparam, lparam lparam)
   {

//      if(::is_set(m_pwindowthread))
//      {
//
//         return ::user::interaction_impl::post_message(message, wparam, lparam);
//
//      }
//
      return ::post_message((oswindow) get_handle(), message, wparam, lparam) != FALSE;

   }


//   bool interaction_impl::DragDetect(const ::point & point) const
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//
//      //return ::DragDetect(get_handle(), point) != FALSE;
//
//   }
//

   void interaction_impl::set_window_text(const char * pszString)

   {

      m_strWindowText = pszString;


      //windowing_output_debug_string("\nlinux::interaction_impl::set_window_text");

      //fflush(stdout);

      x11_store_name(m_oswindow, m_strWindowText);

      //windowing_output_debug_string("\nlinux::interaction_impl::set_window_text END");

      //fflush(stdout);

   }


//   strsize interaction_impl::GetWindowText(LPTSTR pszString, strsize nMaxCount)

//   {
//
//      ansi_count_copy(pszString, m_strWindowText, nMaxCount);

//
//      return min(nMaxCount, m_strWindowText.get_length());
//
//   }

//
//   strsize interaction_impl::GetWindowTextLength()
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//
//      //return ::GetWindowTextLength(get_handle());
//
//   }


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


//   void interaction_impl::DragAcceptFiles(bool bAccept)
//   {
//
//      __throw(not_implemented());
//
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::DragAcceptFiles(get_handle(), bAccept);
//
//   }
//
//   /*
//      __pointer(::user::frame_window) interaction_impl::EnsureParentFrame()
//      {
//
//         __pointer(::user::frame_window) pFrameWnd=GetParentFrame();
//
//         ENSURE_VALID(pFrameWnd);
//
//         return pFrameWnd;
//
//      }
//
//
//      ::user::interaction * interaction_impl::EnsureTopLevelParent()
//      {
//
//         __pointer(::user::interaction)pWnd=GetTopLevelParent();
//
//         ENSURE_VALID(pWnd);
//
//         return pWnd;
//
//      }
//
//   */
//
//
////   void interaction_impl::MoveWindow(const ::rect & rect, bool bRepaint)
////   {
////
////      MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, bRepaint);
////
////   }
//
//
//   UINT interaction_impl::ArrangeIconicWindows()
//   {
//
//      __throw(not_implemented());
//
////      ASSERT(::is_window((oswindow) get_handle())); return ::ArrangeIconicWindows(get_handle());
//
//   }
//
//
//   i32 interaction_impl::SetWindowRgn(HRGN hRgn, bool bRedraw)
//   {
//
//      UNREFERENCED_PARAMETER(hRgn);
//      UNREFERENCED_PARAMETER(bRedraw);
//
//      //__throw(not_implemented());
//
////      ASSERT(::is_window((oswindow) get_handle())); return ::SetWindowRgn(get_handle(), hRgn, bRedraw);
//      return 0;
//   }
//
//
//   i32 interaction_impl::GetWindowRgn(HRGN hRgn)
//   {
//
//      __throw(not_implemented());
//
////      ASSERT(::is_window((oswindow) get_handle()) && hRgn != nullptr); return ::GetWindowRgn(get_handle(), hRgn);
//
//   }
//
//
//   bool interaction_impl::BringWindowToTop()
//   {
//
////      __throw(not_implemented());
////      return ::BringWindowToTop(get_handle()) != FALSE;
//      return true;
//   }
//
//
//   void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPPOINT pPoint, UINT nCount)
//
//   {
//
//      __throw(not_implemented());
//
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_handle(), pPoint, nCount);
//
//
//   }
//
//
//   void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, RECT * prect)
//
//   {
//
//      __throw(not_implemented());
//
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_handle(), (LPPOINT)prect, 2);
//
//
//   }


//   ::draw2d::graphics * interaction_impl::GetDC()
//   {
//
//      ::draw2d::graphics_pointer g(e_create);
//
//      windowing_output_debug_string("\nlinux::interaction_impl::GetDC");
//
//      fflush(stdout);
//
//      xdisplay d(m_oswindow->display());
//
//      oswindow oswindow;
//
//      if(get_handle() == nullptr)
//      {
//
////         oswindow = ::get_desktop_window();
//
//      }
//      else
//      {
//
//         oswindow = (::oswindow) get_handle();
//
//      }
//
//      ::rect rectClient;
//
//      //oswindow->get_client_rect(rectClient);
//
//      rectClient.left = 0;
//      rectClient.top = 0;
//      rectClient.right = 500;
//      rectClient.bottom = 500;
////      (dynamic_cast < ::linux::graphics * >(g.m_p))->attach(cairo_create(cairo_xlib_surface_create(oswindow->display(), oswindow->interaction_impl(), oswindow->draw2d(),rectClient.width(), rectClient.height())));
//
//      windowing_output_debug_string("\nlinux::interaction_impl::GetDC END");
//
//      fflush(stdout);
//
//      return g.detach();
//
//   }
//
//
//   ::draw2d::graphics * interaction_impl::GetWindowDC()
//   {
//      ASSERT(::is_window((oswindow) get_handle()));
//      //::draw2d::graphics_pointer g(e_create);
//      //g->attach(::GetWindowDC(get_handle()));
//      //return g.detach();
//      return nullptr;
//   }
//
//   bool interaction_impl::ReleaseDC(::image * pimage)
//   {
//
//      if(pimage->is_null())
//         return false;
//
//      /*      cairo_t * pcairo = (cairo_t *) pgraphics->get_os_data();
//
//            cairo_surface_t * psurface = cairo_get_target(pcairo);
//      	if(pcairo ==  g_cairo)
//      	{
//               printf("123");
//
//      	}
//
//            cairo_destroy(pcairo);
//
//      if(psurface == g_cairosurface)
//      {
//         printf("123");
//      }      cairo_surface_destroy(psurface);*/
//
////      if(((Gdiplus::Graphics *)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle()) == nullptr)
//      //       return false;
//
//      //::ReleaseDC(get_handle(), (dynamic_cast < ::linux::graphics * > (pgraphics))->detach());
//
////      (dynamic_cast<::linux::graphics * >(pgraphics))->m_hdc = nullptr;
//
////      pgraphics->release();
//
//      return true;
//
//   }
//
//   void interaction_impl::UpdateWindow()
//   {
//      //__throw(not_implemented());
//      //::UpdateWindow(get_handle());
//   }
//
//   void interaction_impl::SetRedraw(bool bRedraw)
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
//   }
//
//   bool interaction_impl::GetUpdateRect(RECT * prect, bool bErase)
//
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::GetUpdateRect(get_handle(), prect, bErase) != FALSE;
//
//   }
//
//   i32 interaction_impl::GetUpdateRgn(draw2d::region * pRgn, bool bErase)
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
//   }
//
//   void interaction_impl::Invalidate(bool bErase)
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::InvalidateRect(get_handle(), nullptr, bErase);
//   }
//
//   void interaction_impl::InvalidateRect(const ::rect & rect, bool bErase)
//
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::InvalidateRect(get_handle(), prect, bErase);
//
//   }
//
//   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
//   }
//
//   void interaction_impl::ValidateRect(const ::rect & rect)
//
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::ValidateRect(get_handle(), prect);
//
//   }
//
//   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
//   {
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::ValidateRgn(get_handle(), (HRGN)pRgn->get_handle());
//   }


//   bool interaction_impl::_is_window_visible()
//   {
//
//      if(!m_puserinteraction->is_this_visible())
//      {
//
//         return false;
//
//      }
//
//      if(m_puserinteraction->m_pdescriptor->m_puserinteractionParent != nullptr)
//      {
//
//         if(!m_puserinteraction->m_pdescriptor->m_puserinteractionParent->is_window_visible())
//         {
//
//            return false;
//
//         }
//
//      }
//
//      return true;
//
//   }


//   void interaction_impl::ShowOwnedPopups(bool bShow)
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::ShowOwnedPopups(get_handle(), bShow);
//
//   }
//
////   void interaction_impl::send_message_to_descendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
//
////   {
////      ASSERT(::is_window((oswindow) get_handle()));
////      //interaction_impl::send_message_to_descendants(get_handle(), message, wparam, lparam, bDeep, bOnlyPerm);
//
////
////      // walk through oswindows to avoid creating temporary interaction_impl objects
////      // unless we need to call this function recursively
////      user::interaction * pinteraction = m_puserinteraction->first_child();
////      while(pinteraction != nullptr)
////      {
////         try
////         {
////            pinteraction->send_message(message, wparam, lparam);
//
////         }
////         catch(...)
////         {
////         }
////         if (bDeep)
////         {
////            // send to child windows after parent
////            try
////            {
////               pinteraction->send_message_to_descendants(message, wparam, lparam, bDeep, bOnlyPerm);
//
////            }
////            catch(...)
////            {
////            }
////         }
////         try
////         {
////            pinteraction = pinteraction->next_sibling();
////         }
////         catch(...)
////         {
////            break;
////         }
////      }
////   }
////
//
//   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip, DWORD flags)
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::draw2d::graphics_pointer g(get_object());
//      //g->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_handle(), flags));
//      //return g.detach();
//
//   }
//
//   bool interaction_impl::LockWindowUpdate()
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::LockWindowUpdate(get_handle()) != FALSE;
//
//   }
//
//   void interaction_impl::UnlockWindowUpdate()
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::LockWindowUpdate(nullptr);
//
//   }
//

//   bool interaction_impl::RedrawWindow(const ::rect& rectUpdate, ::draw2d::region * prgnUpdate, UINT flags)
//   {
//
////      ASSERT(::is_window((oswindow) get_handle()));
//
//      if(flags & RDW_UPDATENOW)
//      {
//
//         _001UpdateWindow();
//
//      }
//      else
//      {
//
//         m_puserinteraction->m_bRedraw = true;
//
//      }
//
//      return true;
//
//   }

   /*
      bool interaction_impl::EnableScrollBar(i32 nSBFlags, UINT nArrowFlags)
      {

         ASSERT(::is_window((oswindow) get_handle()));

         return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != FALSE;

      }
   */

//   bool interaction_impl::DrawAnimatedRects(i32 idAni, CONST LPRECTprcFrom, CONST LPRECTlprcTo)
//
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::DrawAnimatedRects(get_handle(), idAni, prcFrom, lprcTo) != FALSE;
//
//
//   }


//   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, const rect & prc, UINT uFlags)
//
//   {
//
//      __throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle(), prc, uFlags) != FALSE;
//
//
//   }
//
//
//   bool interaction_impl::SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer)
//   {
//
//      return ::user::interaction_impl::SetTimer(nIDEvent, nElapse, pfnTimer);
//
//
////        UNREFERENCED_PARAMETER(pfnTimer);
//
////
////        m_puserinteraction->get_context_application()->set_timer(m_puserinteraction, nIDEvent, nElapse);
////
////        return nIDEvent;
//
//      //__throw(not_implemented());
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::SetTimer(get_handle(), nIDEvent, nElapse, pfnTimer);
//
//
//   }
//
//
//   bool interaction_impl::KillTimer(uptr nIDEvent)
//   {
//
//      return ::user::interaction_impl::KillTimer(nIDEvent);
//
////       m_puserinteraction->get_context_application()->unset_timer(m_puserinteraction, nIDEvent);
//
//      //     return TRUE;
//
//      //return ::user::int
//
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::KillTimer(get_handle(), nIDEvent)  != FALSE;
//
//   }


   bool interaction_impl::IsWindowEnabled()
   {

      return m_bEnabled;

   }


   bool interaction_impl::EnableWindow(bool bEnable)
   {

      return m_bEnabled = bEnable;

   }


   ::user::interaction * interaction_impl::GetActiveWindow()
   {

      oswindow oswindow = nullptr;

      x11_sync([&]()
      {

         oswindow = ::get_active_window();

      });

      if(oswindow == nullptr)
      {

         return nullptr;

      }

      ::user::interaction_impl * pimpl = ::linux::interaction_impl::from_handle(oswindow);

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::user::interaction * interaction_impl::SetActiveWindow()
   {

      return nullptr;


//      ::user::interaction_impl * pimpl = ::linux::interaction_impl::from_handle(::set_active_window(get_handle()));

  //    if(pimpl == nullptr)
    //  {

      //   return nullptr;

      //}

      //return pimpl->m_puserinteraction;

   }


   ::user::interaction * PASCAL interaction_impl::GetFocus()
   {

      oswindow w = ::get_focus();

      if(w == nullptr)
         return nullptr;

      return w->m_pimpl->m_puserinteraction;

   }


   bool interaction_impl::SetFocus()
   {

      oswindow w = ::set_focus(get_handle());

      if(w  == nullptr)
      {

         return false;

      }

      return true;

   }


   ::user::interaction * PASCAL interaction_impl::get_desktop_window()
   {
      /*
            return ::linux::interaction_impl::from_handle(::get_desktop_window());
      */
      return nullptr;
   }


//   // Helper for radio buttons
//   i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton)
//   {
//      for (i32 nID = nIDFirstButton; nID <= nIDLastButton; nID++)
//      {
//         if (IsDlgButtonChecked(nID))
//            return nID; // id that matched
//      }
//      return 0; // invalid ID
//   }
//
//   void interaction_impl::CheckDlgButton(i32 nIDButton, UINT nCheck)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::CheckDlgButton(get_handle(), nIDButton, nCheck);
//
//   }
//
//   void interaction_impl::CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);
//
//   }
//
//   i32 interaction_impl::DlgDirList(LPTSTR pPathSpec, i32 nIDListBox, i32 nIDStaticPath, UINT nFileType)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirList(get_handle(), pPathSpec, nIDListBox, nIDStaticPath, nFileType);
//
//
//   }
//
//   i32 interaction_impl::DlgDirListComboBox(LPTSTR pPathSpec, i32 nIDComboBox, i32 nIDStaticPath, UINT nFileType)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirListComboBox(get_handle(), pPathSpec, nIDComboBox, nIDStaticPath, nFileType);
//
//
//   }
//
//   bool interaction_impl::DlgDirSelect(LPTSTR pString, i32 nSize, i32 nIDListBox)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirSelectEx(get_handle(), pString, nSize, nIDListBox) != FALSE;
//
//
//   }
//
//   bool interaction_impl::DlgDirSelectComboBox(LPTSTR pString, i32 nSize, i32 nIDComboBox)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirSelectComboBoxEx(get_handle(), pString, nSize, nIDComboBox) != FALSE;
//
//
//   }
//
//   /*
//      void interaction_impl::GetDlgItem(id id, oswindow* phWnd) const
//      {
//
//         ASSERT(::is_window((oswindow) get_handle()));
//         ASSERT(phWnd != nullptr);
//         *phWnd = ::GetDlgItem(get_handle(), (i32) id);
//
//      }
//   */
//
//   /*
//      UINT interaction_impl::GetDlgItemInt(i32 nID, WINBOOL * pTrans, bool bSigned) const
//
//      {
//
//         ASSERT(::is_window((oswindow) get_handle()));
//
//         return ::GetDlgItemInt(get_handle(), nID, pTrans, bSigned);
//
//
//      }
//   */
//
////   i32 interaction_impl::GetDlgItemText(i32 nID, LPTSTR pStr, i32 nMaxCount) const
//
////   {
////
////      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle())); return ::GetDlgItemText(get_handle(), nID, pStr, nMaxCount);}
//
//
//   ::user::interaction * interaction_impl::GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious) const
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetNextDlgGroupItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));
//
//   }
//
//   ::user::interaction * interaction_impl::GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious) const
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetNextDlgTabItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));
//
//   }
//
//   UINT interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::IsDlgButtonChecked(get_handle(), nIDButton);
//
//   }
//
//   LPARAM interaction_impl::SendDlgItemMessage(i32 nID, UINT message, WPARAM wparam, LPARAM lparam)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::SendDlgItemMessage(get_handle(), nID, message, wparam, lparam);
//
//
//   }
//
//   void interaction_impl::SetDlgItemInt(i32 nID, UINT nValue, bool bSigned)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);
//
//   }
//
//   void interaction_impl::SetDlgItemText(i32 nID, const char * pszString)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::SetDlgItemText(get_handle(), nID, pszString);
//
//
//   }
//
//   i32 interaction_impl::ScrollWindowEx(i32 dx, i32 dy, const rect & pRectScroll, const rect & lpRectClip, ::draw2d::region * prgnUpdate, RECT * lpRectUpdate, UINT flags)
//
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::ScrollWindowEx(get_handle(), dx, dy, pRectScroll, lpRectClip, (HRGN)prgnUpdate->get_handle(), lpRectUpdate, flags);
//
//
//   }
//
//   void interaction_impl::ShowScrollBar(UINT nBar, bool bShow)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::ShowScrollBar(get_handle(), nBar, bShow);
//
//   }
//
//   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point & point)
//   {
//
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::ChildWindowFromPoint(get_handle(), point));
//
//   }
//
//   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point & point, UINT nFlags)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));
//
//   }
//
//
//
//
//
//
//   ::user::interaction * interaction_impl::GetTopWindow() const
//   {
//
//      if(m_puserinteraction->m_uiptraChild.get_size() <= 0)
//         return nullptr;
//
//      return m_puserinteraction->m_uiptraChild[0];
//      //  __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetTopWindow(get_handle()));
//
//   }
//
//   ::user::interaction * interaction_impl::GetWindow(UINT nCmd)
//   {
//
//      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetWindow(get_handle(), nCmd));
//      return nullptr;
//
//   }
//
//   ::user::interaction * interaction_impl::GetLastActivePopup()
//   {
//
//
//      __throw(todo());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetLastActivePopup(get_handle()));
//
//   }
//

//   ::user::interaction * interaction_impl::SetParent(::user::interaction * pWndNewParent)
//   {
//
//      ASSERT(::is_window((oswindow) get_handle()));
//
//      return ::linux::interaction_impl::from_handle(::SetParent(get_handle(), (oswindow) pWndNewParent->get_handle()))->m_puserinteraction;
//
//   }
//
//
//   ::user::interaction * PASCAL interaction_impl::oswindowFromPoint(const ::point & point)
//   {
//
//      __s_throw(not_implemented());
////      return ::linux::interaction_impl::from_handle(::oswindowFromPoint(point));
//
//   }
//
//
//   bool interaction_impl::FlashWindow(bool bInvert)
//   {
//
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::FlashWindow(get_handle(), bInvert) != FALSE;
//
//   }
//
//   bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::ChangeClipboardChain(get_handle(), hWndNext) != FALSE;
//
//   }
//
//   oswindow interaction_impl::SetClipboardViewer()
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::SetClipboardViewer(get_handle());
//
//   }
//
//   bool interaction_impl::OpenClipboard()
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::OpenClipboard(get_handle()) != FALSE;
//
//   }
//
//
//   ::user::interaction * PASCAL interaction_impl::GetOpenClipboardWindow()
//   {
//
//      __s_throw(not_implemented());
////      return ::linux::interaction_impl::from_handle(::GetOpenClipboardWindow());
//
//   }
//
//
//   ::user::interaction * PASCAL interaction_impl::GetClipboardOwner()
//   {
//
//      __s_throw(not_implemented());
////      return ::linux::interaction_impl::from_handle(::GetClipboardOwner());
//
//   }
//
//
//   ::user::interaction * PASCAL interaction_impl::GetClipboardViewer()
//   {
//
//      __s_throw(not_implemented());
////      return ::linux::interaction_impl::from_handle(::GetClipboardViewer());
//
//   }
//
//
//
//
//
//   point PASCAL interaction_impl::GetCaretPos()
//   {
//
//      __s_throw(not_implemented());
////      const ::point & point;
////      ::GetcaretPos((LPPOINT)&point); return point;
//
//   }
//
//
//   void PASCAL interaction_impl::SetCaretPos(const ::point & point)
//   {
//
//      __s_throw(not_implemented());
////      ::SetcaretPos(point.x, point.y);
//
//   }
//
//
//   void interaction_impl::HideCaret()
//   {
//
//      __throw(not_implemented());
////      ::Hidecaret(get_handle());
//
//   }
//
//   void interaction_impl::ShowCaret()
//   {
//
//      __throw(not_implemented());
////    ::Showcaret(get_handle());
//   }
//


   bool interaction_impl::SetForegroundWindow()
   {

      return ::set_foreground_window(get_handle()) != FALSE;

   }

//
//
//   ::user::interaction * PASCAL interaction_impl::GetForegroundWindow()
//   {
//
//      return nullptr;
//
//      __s_throw(not_implemented());
////      return ::linux::interaction_impl::from_handle(::GetForegroundWindow());
//
//   }
//
//
//   bool interaction_impl::SendNotifyMessage(UINT message, WPARAM wparam, lparam lparam)
//
//   {
//
//      __throw(not_implemented());
////      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != FALSE;
//
//
//   }
//
//   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      const_cast < interaction_impl * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle(), dwFlags);
//
//   }
//
//   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      const_cast < interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle(), dwFlags);
//
//   }
//
//   bool interaction_impl::SetWindowContextHelpId(DWORD dwContextHelpId)
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != FALSE;
//
//   }
//
//   DWORD interaction_impl::GetWindowContextHelpId() const
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::GetWindowContextHelpId(get_handle());
//
//   }
//
//
//   // Default message ::collection::map implementations
//   void interaction_impl::OnActivateApp(bool, DWORD)
//   {
//   //Default();
//   }
//   void interaction_impl::OnActivate(UINT, ::user::interaction *, bool)
//   {
//   //Default();
//   }
//   void interaction_impl::OncancelMode()
//   {
//   //Default();
//   }
//   void interaction_impl::OnChildActivate()
//   {
//   //Default();
//   }
//   void interaction_impl::OnClose()
//   {
//   //Default();
//   }
//   void interaction_impl::OnContextMenu(::user::interaction *, point)
//   {
//   //Default();
//   }
//
//   bool interaction_impl::OnCopyData(::user::interaction *, COPYDATASTRUCT*)
//   {
//   //Default();
//   return false;
//   }
//
//   void interaction_impl::OnEnable(bool)
//   {
//   //Default();
//   }
//   void interaction_impl::OnEndSession(bool)
//   {
//   //Default();
//   }
//
//   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
//   {
//   //Default();
//   }
//
//   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
//   {
//   //Default();
//   }
//   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
//   {
//   //Default();
//   }
//   void interaction_impl::OnKillFocus(::user::interaction *)
//   {
//   //Default();
//   }
//   LRESULT interaction_impl::OnMenuChar(UINT, UINT, ::user::menu*)
//   {
//   //Default();
//   }
//   void interaction_impl::OnMenuSelect(UINT, UINT, HMENU)
//   {
//   //Default();
//   }
//   void interaction_impl::OnMove(i32, i32)
//   {
//   //Default();
//   }
//
//   bool interaction_impl::OnQueryEndSession()
//   {
//   //return Default();
//   return true;
//   }
//
//   bool interaction_impl::OnQueryNewPalette()
//   {
//
//      //return Default() != FALSE;
//      return true;
//
//   }
//
//   bool interaction_impl::OnQueryOpen()
//   {
//
//      //return Default() != FALSE;
//      return true;
//
//   }
//
   void interaction_impl::_001OnSetCursor(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if(Session.get_cursor() != nullptr
            && Session.get_cursor()->m_ecursor != cursor_system)
      {

         __throw(not_implemented());
//         ::SetCursor(nullptr);
      }
      pbase->m_lresult  = 1;
      pbase->m_bRet = true;
      //(bool)Default();
   }


//   void interaction_impl::OnShowWindow(bool, UINT)
//   {
//   //Default();
//   }
//   void interaction_impl::OnSize(UINT, i32, i32)
//   {
//   //Default();
//   }
//   void interaction_impl::OnTcard(UINT, DWORD)
//   {
//   //Default();
//   }
//   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
//   {
//   //Default();
//   }
//   void interaction_impl::OnWindowPosChanged(WINDOWPOS*)
//   {
//   //Default();
//   }
//   void interaction_impl::OnDropFiles(HDROP)
//   {
//   //Default();
//   }
//   void interaction_impl::OnPaletteIsChanging(::user::interaction *)
//   {
//   //Default();
//   }
//
//   bool interaction_impl::OnNcActivate(bool)
//   {
//
//      //return Default() != FALSE;
//      return true;
//
//   }
//
//   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
//   {
//   //Default();
//   }
//
//   bool interaction_impl::OnNcCreate(::user::create_struct *)
//   {
//
////      return Default() != FALSE;
//return true;
//
//   }

//   LRESULT interaction_impl::OnNcHitTest(point)
//   { return Default(); }
//   void interaction_impl::OnNcLButtonDblClk(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcLButtonDown(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcLButtonUp(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcMButtonDblClk(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcMButtonDown(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcMButtonUp(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcMouseMove(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcPaint()
//   { Default(); }
//   void interaction_impl::OnNcRButtonDblClk(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcRButtonDown(UINT, point)
//   { Default(); }
//   void interaction_impl::OnNcRButtonUp(UINT, point)
//   { Default(); }
//   void interaction_impl::OnSysChar(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnSysCommand(UINT, LPARAM)
//   { Default(); }
//   void interaction_impl::OnSysDeadChar(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnSysKeyDown(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnSysKeyUp(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnCompacting(UINT)
//   { Default(); }
//   void interaction_impl::OnFontChange()
//   { Default(); }
//   void interaction_impl::OnPaletteChanged(::user::interaction *)
//   { Default(); }
//   void interaction_impl::OnSpoolerStatus(UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnTimeChange()
//   { Default(); }
//   void interaction_impl::OnChar(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnDeadChar(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnKeyDown(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnKeyUp(UINT, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnLButtonDblClk(UINT, point)
//   { Default(); }
//   void interaction_impl::OnLButtonDown(UINT, point)
//   { Default(); }
//   void interaction_impl::OnLButtonUp(UINT, point)
//   { Default(); }
//   void interaction_impl::OnMButtonDblClk(UINT, point)
//   { Default(); }
//   void interaction_impl::OnMButtonDown(UINT, point)
//   { Default(); }
//   void interaction_impl::OnMButtonUp(UINT, point)
//   { Default(); }
//   i32 interaction_impl::OnMouseActivate(::user::interaction *, UINT, UINT)
//   { return (i32)Default(); }
//   void interaction_impl::OnMouseMove(UINT, point)
//   { Default(); }

//   bool interaction_impl::OnMouseWheel(UINT, short, point)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
//   { return Default(); }
//   void interaction_impl::OnRButtonDblClk(UINT, point)
//   { Default(); }
//   void interaction_impl::OnRButtonDown(UINT, point)
//   { Default(); }
//   void interaction_impl::OnRButtonUp(UINT, point)
//   { Default(); }
//   void interaction_impl::OnTimer(uptr)
//   { Default(); }
//   void interaction_impl::OnInitMenu(::user::menu*)
//   { Default(); }
//   void interaction_impl::OnInitMenuPopup(::user::menu*, UINT, bool)
//   { Default(); }
//   void interaction_impl::OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszName)
//   {
//      (nMaxCount);
//      if(nMaxCount>0)
//      {
//         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
//         lpszName[0]='\0';
//      }
//      Default();
//   }
//   void interaction_impl::OnChangeCbChain(oswindow, oswindow)
//   { Default(); }
//   void interaction_impl::OnDestroyClipboard()
//   { Default(); }
//   void interaction_impl::OnDrawClipboard()
//   { Default(); }
//   void interaction_impl::OnHScrollClipboard(::user::interaction *, UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnPaintClipboard(::user::interaction *, HGLOBAL)
//   { Default(); }
//   void interaction_impl::OnRenderAllFormats()
//   { Default(); }
//   void interaction_impl::OnRenderFormat(UINT)
//   { Default(); }
//   void interaction_impl::OnSizeClipboard(::user::interaction *, HGLOBAL)
//   { Default(); }
//   void interaction_impl::OnVScrollClipboard(::user::interaction *, UINT, UINT)
//   { Default(); }
//   UINT interaction_impl::OnGetDlgCode()
//   { return (UINT)Default(); }
//   void interaction_impl::OnMDIActivate(bool, ::user::interaction *, ::user::interaction *)
//   { Default(); }
//   void interaction_impl::OnEnterMenuLoop(bool)
//   { Default(); }
//   void interaction_impl::OnExitMenuLoop(bool)
//   { Default(); }
//   // Win4 support
////   void interaction_impl::OnStyleChanged(i32, LPSTYLESTRUCT)
////   { Default(); }
////   void interaction_impl::OnStyleChanging(i32, LPSTYLESTRUCT)
////   { Default(); }
//   void interaction_impl::OnSizing(UINT, RECT *)
//   { Default(); }
//   void interaction_impl::OnMoving(UINT, RECT *)
//   { Default(); }
//   void interaction_impl::OncaptureChanged(::user::interaction *)
//   { Default(); }
//
//   bool interaction_impl::OnDeviceChange(UINT, dword_ptr)
//   {
//
//      return Default() != FALSE;
//
//   }
//
//   void interaction_impl::OnWinIniChange(const char *)
//   { Default(); }
//   void interaction_impl::OnChangeUIState(UINT, UINT)
//   { Default(); }
//   void interaction_impl::OnUpdateUIState(UINT, UINT)
//   { Default(); }
//
//   UINT interaction_impl::OnQueryUIState()
//   {
//
//      return (UINT)Default();
//
//   }

   // interaction_impl dialog data support
   //    void interaction_impl::DoDataExchange(CDataExchange*)
   //   { } // default does nothing

   // interaction_impl modality support

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
//   // frame_window
//   /*    void frame_window::DelayUpdateFrameTitle()
//   { m_nIdleFlags |= idleTitle; }
//   void frame_window::DelayRecalcLayout(bool bNotify)
//   { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
//   bool frame_window::InModalState() const
//   { return m_cModalStack != 0; }
//   void frame_window::set_title(const char * pszTitle)
//
//   { m_strTitle = pszTitle; }
//
//   string frame_window::get_title() const
//   { return m_strTitle; }
//   */
//
//
//
//   void interaction_impl::CloseWindow()
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::CloseWindow(get_handle());
//
//   }
//
//   bool interaction_impl::OpenIcon()
//   {
//
//      __throw(not_implemented());
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::OpenIcon(get_handle()) != FALSE;
//
//   }
//
//   ////////////////////////////////////////////////////////////////////////////
//   // UI related ::user::interaction_impl functions
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
//      __s_throw(todo());
//      // get last active popup of first non-child that was found
//      //    if (hParent == nullptr && hWnd != nullptr)
//      //       hWnd = ::GetLastActivePopup(hWnd);
//
//      // disable and store top level parent ::user::interaction_impl if specified
//      if (pWndTop != nullptr)
//      {
//         /*         if (hWndTop != nullptr && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
//                  {
//                     *pWndTop = hWndTop;
//                     ::EnableWindow(hWndTop, FALSE);
//                  }
//                  else
//                     *pWndTop = nullptr;*/
//      }
//
//      return hWnd;    // return the owner as oswindow
//   }
//
//   void interaction_impl::on_delete(::object * pinteraction)
//   {
//      UNREFERENCED_PARAMETER(pinteraction);
//   }
//
//
//
//
////   void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
////   {
////      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pmessage);
////      perasebkgnd->m_bRet = true;
////      perasebkgnd->set_result(TRUE);
////   }
//
//
//   void interaction_impl::_001BaseWndInterfaceMap()
//   {
//
//      ::user::interaction_impl::_001BaseWndInterfaceMap();
//
//   }
//
//
//   void interaction_impl::_001OnTriggerMouseInside()
//   {
//

////      m_bMouseHover = true;
//
//   }


   void interaction_impl::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->SetViewportOrg(::point());

   }


   void interaction_impl::window_show_change_visibility()
   {

      __keep_flag_on(m_puserinteraction->m_eflagLayouting, ::user::layout::layout_show_window);

      auto edisplay = m_puserinteraction->process_display();

      auto eactivation = m_puserinteraction->process_state().m_eactivation;

      //if(eactivation &)
//      {
//
//         wm_add_remove_state(m_oswindow, net_wm_state_hidden, false);
//
//      }
//
      if (edisplay == display_full_screen)
      {

         if(m_puserinteraction->m_bWorkspaceFullScreen)
         {

            ::show_window(m_oswindow, SW_MAXIMIZE);

         }
         else
         {

            m_oswindow->full_screen();

         }

      }
      else
      {

         ::user::interaction_impl::window_show_change_visibility();

      }

   }


//   ::user::interaction * interaction_impl::GetNextWindow(UINT nFlag)
//   {
//
//      if(nFlag == GW_HWNDNEXT)
//      {
//
//         return get_next(true, nullptr);
//
//      }
//      else
//      {
//
//         __throw(interface_only_exception());
//
//      }
//
//   }
//
//
//   ::user::interaction * interaction_impl::get_next(bool bIgnoreChildren,i32 * piLevel)
//   {
//
//      return  m_puserinteraction->get_next(bIgnoreChildren, piLevel);
//
//   }
//

   void interaction_impl::show_task(bool bShow)
   {

      wm_toolwindow(get_handle(), bShow ? 0: 1);

   }


   bool interaction_impl::has_focus()
   {

      if(!::is_window(m_oswindow))
      {

         return false;

      }

      return m_puserinteraction->m_ewindowflag & ::window_flag_focus;

   }


   bool interaction_impl::is_active()
   {

      if(!::is_window(m_oswindow))
      {

         return false;

      }

//      x11_sync([this]()
//      {
//
//         m_puserinteraction->m_ewindowflag.set(::window_flag_active, m_oswindow == ::get_active_window());
//
//      });
//
      return m_puserinteraction->m_ewindowflag & ::window_flag_active;

   }


   bool interaction_impl::prodevian_update_screen()
   {

      if(!m_puserinteraction)
      {

         return false;

      }

      if(m_puserinteraction->m_ewindowflag & window_flag_embedded_prodevian)
      {

         _001UpdateScreen();

      }
      else
      {

         //x11_sync([&]()
         //{

         sync_lock sl(x11_mutex());

            _001UpdateScreen();

         //});

      }

      return true;

   }


   void interaction_impl::non_top_most_upper_window_rects(::rect_array& recta)
   {

      upper_window_rects(get_safe_handle(), recta);

   }


} // namespace linux



