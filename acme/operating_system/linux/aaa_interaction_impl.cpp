#include "framework.h"
#include "_linux.h"
#include "acme/platform/app_core.h"
#include "acme/operating_system/linux/_linux.h"
//!!!#include <X11/Xatom.h>
////#include "sn/sn.h"
#include <gdk/gdkx.h>

#define TEST 0


void x11_store_name(oswindow oswindow, const ::scoped_string & scopedstrName);
void x11_defer_check_configuration(oswindow oswindow);
void upper_window_rects(oswindow oswindow, int_rectangle_array & ra);
#undef ALOG_CONTEXT
#define ALOG_CONTEXT (::trace_object(::trace_category_windowing))


void wm_add_erase_state(oswindow w, e_net_wm_state estate, bool bSet);

void wm_iconify_window(oswindow w);

void wm_state_above_raw(oswindow w, bool bSet);

void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);

Display * x11_get_display();

void wm_state_above_raw(oswindow w, bool bSet);

void wm_toolwindow(oswindow w, bool bSet);

void wm_centerwindow(oswindow w, bool bSet);

void wm_desktopwindow(oswindow w, bool bSet);

void wm_dockwindow(oswindow w, bool bSet);

void wm_state_hidden(oswindow w, bool bSet);

//#include <X11/extensions/Xcomposite.h>

//CLASS_DECL_ACME thread_int_ptr < DWORD_PTR > t_time1;

//#define COMPILE_MULTIMON_STUBS
//#include <multimon.h>

//#include "sal.h"

extern SnLauncheeContext* g_psncontext;

CLASS_DECL_ACME void hook_window_create(::user::interaction * pWnd);
CLASS_DECL_ACME bool unhook_window_create();
void CLASS_DECL_ACME __pre_init_dialog(
::user::interaction * pWnd, RECT32 * pRectOld, unsigned int* pdwStyleOld);

void CLASS_DECL_ACME __post_init_dialog(
::user::interaction * pWnd, const rectangle & rectangleOld, unsigned int dwStyleOld);
LRESULT CALLBACK
__activation_window_procedure(oswindow hWnd, unsigned int nMsg, WPARAM wparam, LPARAM lparam);


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
   unsigned int nCtlType;
};

//extern cairo_surface_t *  g_cairosurface;
//extern cairo_t *  g_cairo;

// int_bool PeekMessage(LPMESSAGE pMsg, oswindow hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg);



// int_bool GetMessage(LPMESSAGE pMsg, oswindow hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);


/*
const char gen_Wnd[] = __WND;
*/

namespace linux
{


   huge_integer g_iMouseMove = 0;


   interaction_impl::interaction_impl()
   {

      linux_interaction_impl_common_construct();

   }


   interaction_impl::interaction_impl(::particle * pparticle) :
      ::matter(pparticle)
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


   ::windowing::window * interaction_impl::from_os_data(void * pdata)
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


   ::windowing::window * interaction_impl::from_handle(oswindow oswindow)
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


   ::windowing::window * interaction_impl::FromHandlePermanent(oswindow oswindow)
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


   bool interaction_impl::_native_create_window_ex(::pointer<::user::system>pusersystem)
   {

      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || is_string_ok(pusersystem->m_createstruct.lpszName));

      if (!m_puserinteraction->pre_create_window(pusersystem))
      {

         return false;

      }

      __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_task());

      m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

      install_message_routing(m_puserinteraction);

      bool bOk = true;

      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
      {

         m_oswindow = oswindow_get_message_only_window(this);

         m_puserinteraction->m_bMessageWindow = true;

         //send_message(e_message_create, 0, (LPARAM) &cs);

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

            if(pusersystem->m_createstruct.cx() <= 0)
            {

               pusersystem->m_createstruct.cx() = 1;

            }

            if(pusersystem->m_createstruct.cy() <= 0)
            {

               pusersystem->m_createstruct.cy() = 1;

            }

            m_iScreen            =  DefaultScreen(display);

            Window rootwin       =  RootWindow(display, m_iScreen);

            XEvent e;

            // query Visual for "TrueColor" and 32 bits depth (RGBA)

            Visual * vis = DefaultVisual(display, DefaultScreen(display));

            m_iDepth = 0;

            if(m_px11data.is_null())
            {

               m_px11data = __allocate x11data();

            }

            if(XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_px11data->m_visualinfo))
            {

               vis = m_px11data->m_visualinfo.visual;

            }
            else
            {

               zero(m_px11data->m_visualinfo);

            }

            m_iDepth = m_px11data->m_visualinfo.depth;

            XSetWindowAttributes attr;

            zero(attr);

            attr.colormap = XCreateColormap( display, rootwin, vis, AllocNone);

            attr.event_mask = PropertyChangeMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask | FocusChangeMask;

            attr.background_pixmap = None;

            attr.border_pixmap = None;

            attr.border_pixel = 0;

            attr.override_redirect = m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning ? True : False;

            //attr.override_redirect = True;

            informationf("XCreateWindow (l=%d, t=%d) (w=%d, h=%d)", pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y(), pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy());

            Window window = XCreateWindow(display, DefaultRootWindow(display), pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y(), pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(),
            0,
            m_iDepth,
            InputOutput,
            vis,
            CWColormap|CWEventMask|CWBackPixmap|CWBorderPixel
                          | CWOverrideRedirect
                                          , &attr);

            m_puserinteraction->layout().window() = ::int_point(INT_MIN, INT_MIN);

            m_puserinteraction->layout().window() = ::size(INT_MIN, INT_MIN);

            m_puserinteraction->screen_origin() = ::int_point(INT_MIN, INT_MIN);

   //         {
   //
   //            auto & uistate = m_puserinteraction->ui_state();
   //
   //            uistate.m_point.set(pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y());
   //
   //            uistate.m_size.set(pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy());
   //
   //            uistate.m_pointScreen = uistate.m_point;
   //
   //         }
   //
            {

               m_puserinteraction->layout().sketch() = ::int_point(pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y());

               m_puserinteraction->layout().sketch() = ::size(pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy());

               m_puserinteraction->screen_origin() = ::int_point(pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y());

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

               unsigned int dwLastError = get_last_error();

               string strLastError = FormatMessageFromSystem(dwLastError);

               string strMessage;

               strMessage.formatf("%s\n\nSystem Error Code: %d", strLastError.c_str(), dwLastError);

               information(trace_category_appmsg, e_trace_level_warning, "Warning: oswindow creation failed: get_last_error returned:\n");

               information(trace_category_appmsg, e_trace_level_warning, "%s\n", strMessage.c_str());

               try
               {

                  if(dwLastError == 0x0000057e)
                  {

                     ::acmeacmesystem()->output_error_message("cannot create a top-level child interaction_impl.");

                  }
                  else
                  {

                     ::acmeacmesystem()->message_box(strMessage);

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

            m_puserinteraction->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(this, "native_create_window"));

            auto papp = get_app();

            if(!(m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
            {

               XClassHint * pupdate = XAllocClassHint();

               string strPrgName = papp->m_strAppId;

               strPrgName.replace("/", ".");

               strPrgName.replace("_", "-");

               strPrgName = "com." + strPrgName;

               pupdate->res_class = (char *) (const char *) strPrgName;

               pupdate->res_name = (char *) (const char *) strPrgName;

               XSetClassHint(display, window, pupdate);

               XFree(pupdate);

            }

   #ifndef RASPBERRYPIOS

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
            else if(m_puserinteraction->layout().sketch().activation() & ::user::e_activation_on_center_of_screen)
            {

               wm_centerwindow(m_oswindow, true);

            }

            if(m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window)
            {

               wm_toolwindow(m_oswindow, true);

            }

            //m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);

            Window root = 0;

            Window * pchildren = nullptr;

            unsigned int ncount = 0;

            XQueryTree(display, window, &root, &m_oswindow->m_parent, &pchildren, &ncount);

            if(pchildren != nullptr)
            {

               XFree(pchildren);

            }

            htask htask = ::current_htask();

            m_oswindow->m_htask = htask;


            if(!XGetWindowAttributes(m_oswindow->display(), m_oswindow->window(), &m_px11data->m_attr))
            {

               information() << "linux::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.";

            }

            int event_base, error_base, major_version, minor_version;

            m_bComposite = XGetSelectionOwner(m_oswindow->display(), XInternAtom(m_oswindow->display(), "_NET_WM_CM_S0", True));

            if(pusersystem->m_createstruct.lpszName != nullptr && strlen(pusersystem->m_createstruct.lpszName) > 0)
            {

               XStoreName(m_oswindow->display(), m_oswindow->window(), pusersystem->m_createstruct.lpszName);

            }

            if(pusersystem->m_createstruct.dwExStyle & WS_EX_TOOLWINDOW)
            {

               m_oswindow->set_window_long_ptr(GWL_EXSTYLE, m_oswindow->get_window_long_ptr(GWL_EXSTYLE) |  WS_EX_TOOLWINDOW);

            }

            _wm_nodecorations(m_oswindow, 0);

            if(pusersystem->m_createstruct.style & WS_VISIBLE)
            {

               m_oswindow->map_window();

            }
            else
            {

               m_puserinteraction->layout().window().display() = e_display_none;

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

                     m_oswindow->set_window_position(e_zorder_top, pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y(), pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(), SWP_SHOWWINDOW);

                  }

               }

            }

            d.unlock();

            //if(pshowwindow->m_bShow)
            {

               //::double_rectangle rect32;

               //(::window_rectangle((oswindow) get_handle(), rect32))
               {


                  if(get_session() != nullptr)
                  {

                     // Initial position of window below the cursor position
                     // with invalid (empty) size.
                     // (Hinting for monitor placement, if no stored information
                     // available).

                     if(m_puserinteraction->layout().sketch().display() == e_display_undefined)
                     {

                        m_puserinteraction->move_to(get_session()->get_cursor_position());

                        m_puserinteraction->set_size(0, 0);

                     }

                  }

               }

            }

         });

      }

      if(bOk)
      {

         m_puserinteraction->send_message(e_message_create, 0, (LPARAM) &cs);

         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

      }

      return bOk;

   }


   bool interaction_impl::pre_create_window(::user::system * pusersystem)
   {

      return true;

   }





   void interaction_impl::install_message_routing(::channel * pchannel)
   {
      //m_pbuffer->InstallMessageHandling(pinterface);

      ::windowing::window::last_install_message_routing(pchannel);
      ::windowing::window::install_message_routing(pchannel);

      if(!m_puserinteraction->m_bMessageWindow)
      {
         MESSAGE_LINK(e_message_paint, pchannel, this,&interaction_impl::_001OnPaint);
         MESSAGE_LINK(WM_PRINT, pchannel, this,&interaction_impl::_001OnPrint);
      }

      m_puserinteraction->install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this,&interaction_impl::on_message_create);



      if(!m_puserinteraction->m_bMessageWindow)
      {
         //MESSAGE_LINK(e_message_set_cursor, pchannel, this,&interaction_impl::on_message_set_cursor);
         //MESSAGE_LINK(e_message_erase_background, pchannel, this,&interaction_impl::_001OnEraseBkgnd);
         //MESSAGE_LINK(e_message_size, pchannel, this,&interaction_impl::on_message_size);
         //MESSAGE_LINK(e_message_non_client_calcsize, pchannel, this,&interaction_impl::on_message_non_client_calculate_size);

         // linux
         MESSAGE_LINK(e_message_reposition, pchannel, this, &interaction_impl::on_message_move);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::on_message_size);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_impl::on_message_show_window);

         //MESSAGE_LINK(e_message_window_position_changing, pchannel, this,&interaction_impl::_001OnWindowPosChanging);
         //MESSAGE_LINK(e_message_window_position_changed, pchannel, this,&interaction_impl::_001OnWindowPosChanged);
         //MESSAGE_LINK(WM_GETMINMAXINFO, pchannel, this,&interaction_impl::_001OnGetMinMaxInfo);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this,&interaction_impl::on_message_set_focus);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this,&interaction_impl::on_message_kill_focus);
//         MESSAGE_LINK(ca2m_PRODEVIAN_SYNCH, pchannel, this,&interaction_impl::_001OnProdevianSynch);
         ::windowing::window::prio_install_message_routing(pchannel);
      }

      MESSAGE_LINK(e_message_destroy, pchannel, this,&interaction_impl::on_message_destroy);

   }


   void interaction_impl::defer_delayed_placement()
   {

      if(!m_puserinteraction->layout().is_changing())
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

      while(m_durationLastPlacementEvent.elapsed() < 40 || m_puserinteraction->layout().is_changing())
      {

         if(!task_sleep(10_ms))
         {

            return;

         }

      }

      if(!task_get_run())
      {

         return;

      }

      bool bMove = m_bMoveEvent && m_puserinteraction->layout().sketch().origin() != m_pointLastMove;

      m_bMoveEvent = false;

      if (bMove)
      {

         informationf("linux::interaction_impl Window Manager Move (%d, %d)", m_pointLastMove.x(), m_pointLastMove.y());

         m_puserinteraction->move_to(m_pointLastMove);

         m_puserinteraction->set_reposition();

      }

      bool bSize = m_bSizeEvent && m_puserinteraction->layout().sketch().size() != m_sizeLastSize;

      m_bSizeEvent = false;

      if (bSize)
      {

         informationf("linux::interaction_impl Window Manager Size (%d, %d)", m_sizeLastSize.cx(), m_sizeLastSize.cy());

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


   void interaction_impl::on_message_move(::message::message * pmessage)
   {

      ::pointer<::message::size>psize(pmessage);

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         pmessage->m_bRet = true;

         return;

      }

      ::pointer<::message::transfer>pmove(pmessage);

      m_puserinteraction->layout().window() = pmove->m_point;

      if(m_puserinteraction->layout().window().origin() != m_puserinteraction->layout().sketch().origin())
      {

         m_puserinteraction->move_to(pmove->m_point);

         m_puserinteraction->set_reposition();

         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::on_message_size(::message::message * pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         pmessage->m_bRet = true;

         return;

      }

      ::pointer<::message::size>psize(pmessage);

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


   void interaction_impl::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if(!m_puserinteraction)
      {

         return;

      }

      if(pshowwindow->m_bShow)
      {

         informationf("linux::interaction_impl::on_message_show_window VISIBLE edisplay=%s", __c_str(m_puserinteraction->layout().design().display().m_eenum));

         m_puserinteraction->ModifyStyle(0, WS_VISIBLE);

         if(m_puserinteraction->layout().design().display() == ::e_display_iconic && !m_oswindow->is_iconic())
         {

            m_puserinteraction->hide();

            if(m_puserinteraction->window_previous_display() == ::e_display_iconic)
            {

               m_puserinteraction->_001OnDeiconify(::e_display_normal);

            }
            else
            {

               m_puserinteraction->_001OnDeiconify(m_puserinteraction->window_previous_display());

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


   void interaction_impl::on_start_layout_experience(enum_layout_experience elayout)
   {

      child_post_quit("delayed_placement");

   }


   void interaction_impl::on_end_layout_experience(enum_layout_experience elayout)
   {

      defer_delayed_placement();

   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::windowing::window::on_layout(pgraphics);

   }


   void interaction_impl::on_message_destroy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      {

         single_lock synchronouslock(get_app() == nullptr ? nullptr : get_app()->synchronization(), true);

         ::thread* pThread = ::get_task();

         if (pThread != nullptr)
         {

            if (pThread->get_active_ui() == m_puserinteraction)
            {

               pThread->set_active_ui(nullptr);

            }

         }

      }

//      ::parallelization::post_quit_and_wait(m_pthreadProDevian, seconds(10));

//      if (m_puserinteraction->m_pthread != nullptr)
//      {
//
//         synchronous_lock synchronouslock(m_puserinteraction->m_pthread->mutex());
//
//         if(m_puserinteraction->m_pthread->m_puiptra != nullptr)
//         {
//
//            m_puserinteraction->m_pthread->m_puiptra->erase(m_puserinteraction);
//
//         }
//
//      }

      //Default();

   }


   void interaction_impl::post_non_client_destroy()
   {

      Detach();

      if (!::is_null(m_oswindow))
      {

         m_oswindow->post_nc_destroy();

      }

      ::windowing::window::post_non_client_destroy();

   }


   void interaction_impl::on_final_release()
   {

      if (get_handle() != nullptr)
      {

         DestroyWindow();

      }
      else
      {

         post_non_client_destroy();

      }

   }


   void interaction_impl::assert_ok() const
   {

      if (((interaction_impl *) this)->get_handle() == nullptr)
      {

         return;

      }

   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {

      ::matter::dump(dumpcontext);

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

      ::pointer<::windowing::window>pWnd = (::windowing::window *) this;
      if (pWnd.m_p != this)
         dumpcontext << " (Detached or temporary interaction_impl)";
      else
         dumpcontext << " (permanent interaction_impl)";

      char szBuf [64];

      ::double_rectangle rectangle;
      ((::windowing::window *) this)->m_puserinteraction->window_rectangle(&rectangle);
      dumpcontext << "\nrect = " << rectangle;
      dumpcontext << "\nparent ::pointer<::interaction_impl>= " << (void *)((::windowing::window *) this)->get_parent();

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

         send_message(e_message_destroy, 0, 0);

         send_message(e_message_non_client_destroy, 0, 0);

         ::oswindow_erase_message_only_window(this);

         return true;

      }

      bool bResult = false;

      oswindow window = get_handle();

      if (window != nullptr)
      {

         bResult = ::destroy_window(window) != false;

         //Detach();

      }

      return bResult;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Default interaction_impl implementation


   void interaction_impl::default_window_procedure(::user::message * pusermessage)

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
      __UNREFERENCED_PARAMETER(pmessage);
      // no default processing
   }


   void interaction_impl::get_window_text(string & rectangleString)
   {

      rectangleString = m_strWindowText;

   }

   /*
      int interaction_impl::GetDlgItemText(int nID, string & rectangleString) const
      {
         ASSERT(::is_window((oswindow) get_handle()));
         rectangleString = "";    // is_empty without deallocating

         oswindow hWnd = ::GetDlgItem(get_handle(), nID);
         if (hWnd != nullptr)
         {
            int nLen = ::GetWindowTextLength(hWnd);
            ::GetWindowText(hWnd, rectangleString.get_buffer(nLen), nLen+1);
            rectangleString.ReleaseBuffer();
         }

         return (int)rectangleString.get_length();
      }
   */

   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)

   {
      /*    ASSERT(::is_window((oswindow) get_handle()));
          puserinteractionpl->length = sizeof(WINDOWPLACEMENT);

          return ::GetWindowPlacement(get_handle(), puserinteractionpl) != false;*/

      return false;
   }

   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)

   {
      /*      ASSERT(::is_window((oswindow) get_handle()));
            ((WINDOWPLACEMENT*)puserinteractionpl)->length = sizeof(WINDOWPLACEMENT);

            return ::SetWindowPlacement(get_handle(), puserinteractionpl) != false;*/

      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
// /*   void interaction_impl::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT pDrawItemStruct)

   // {

   // reflect notification to child interaction_impl control
   //  if (ReflectLastMsg(pDrawItemStruct->hwndItem))

   //   return;     // eat it

   // not handled - do default
//      Default();
   // }

   // Drawing: for all 4 control types
//   int interaction_impl::OnCompareItem(int /*nIDCtl*/, LPCOMPAREITEMSTRUCT pCompareItemStruct)

   // {
   //  // reflect notification to child interaction_impl control
   //LRESULT lResult;
//      if (ReflectLastMsg(pCompareItemStruct->hwndItem, &lResult))

   //       return (int)lResult;        // eat it

   // not handled - do default
   //  return (int)Default();
//   }

   // void interaction_impl::OnDeleteItem(int /*nIDCtl*/, LPDELETEITEMSTRUCT pDeleteItemStruct)

   //{
   // reflect notification to child interaction_impl control
   // if (ReflectLastMsg(pDeleteItemStruct->hwndItem))

   //  return;     // eat it
   // not handled - do default
//      Default();
   // }

//   bool interaction_impl::_EnableToolTips(bool bEnable, unsigned int nFlag)
//   {
//      __UNREFERENCED_PARAMETER(bEnable);
//      __UNREFERENCED_PARAMETER(nFlag);
//      return false;
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




   void interaction_impl::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      channel::route_command(pcommand);

   }


   void interaction_impl::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(pevent);

   }


//   void interaction_impl::_002OnDraw(::image::image *pimage)
//   {
//
//   }
//

   ::duration     tickDebugmessage_handlerTime;
   int      iDebugmessage_handlerTime;
   ::duration     tickLastMouseMove;
   ::duration     tickLastPaint;


   void interaction_impl::aaa_message_handler(::user::message * pusermessage)
   {

      if(pusermessage->m_emessage == e_message_timer)
      {

         //m_pthread->step_timer();

      }
      else if(pusermessage->m_emessage == e_message_left_button_down)
      {

         informationf("e_message_left_button_down (0)");

      }
      else if(pusermessage->m_emessage == e_message_left_button_up)
      {

         informationf("e_message_left_button_up (0)");

      }
      else if(pusermessage->m_emessage == e_message_mouse_move)
      {

         g_iMouseMove++;

         //informationf("linux::aaa_interaction_impl::message_handler e_message_mouse_move");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if(pusermessage->m_emessage == e_message_paint)
      {

      }

      if(::is_set(m_puserinteraction))
      {

         m_puserinteraction->pre_translate_message(pusermessage);

      }

      if(tickDebugmessage_handlerTime.timeout(1))
      {

         iDebugmessage_handlerTime = 0;

      }
      else
      {

         if(iDebugmessage_handlerTime > 20)
         {

            informationf("interaction_impl::message handler flooded?\n");

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
            //informationf("moving: skip pre translate message");
         }
         else if (m_puserinteraction->layout().is_sizing())
         {
            //informationf("sizing: skip pre translate message");
         }
         else
         {

            //m_puserinteraction->pre_translate_message(pusermessage);

            //if (pusermessage->m_bRet)
            //{

              // return;

            //}

            //pusermessage->m_uiMessageFlags |= 1;

         }

      }

      if(pusermessage->m_emessage == e_message_key_down || pusermessage->m_emessage == e_message_key_up || pusermessage->m_emessage == e_message_char)
      {

         ::message::key * pkey = (::message::key *) pusermessage;

         psession->translate_os_key_message(pkey);

         if(pusermessage->m_emessage == e_message_key_down)
         {

            try
            {

               psession->set_key_pressed(pkey->m_ekey, true);

            }
            catch(...)
            {

            }

         }
         else if(pusermessage->m_emessage == e_message_key_up)
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

      pusermessage->m_lresult = 0;

      if(pusermessage->m_emessage == e_message_mouse_leave)
      {

         _000OnMouseLeave(pusermessage);

         return;

      }

      if(pusermessage->m_emessage == e_message_left_button_down ||
            pusermessage->m_emessage == e_message_left_button_up ||
            pusermessage->m_emessage == e_message_middle_button_down ||
            pusermessage->m_emessage == e_message_middle_button_up ||
            pusermessage->m_emessage == e_message_right_button_down ||
            pusermessage->m_emessage == e_message_right_button_up ||
            pusermessage->m_emessage == e_message_mouse_move ||
            pusermessage->m_emessage == e_message_mouse_move)
//         pusermessage->m_emessage == e_message_mouse_wheel)
      {

         if(::is_set(m_puserinteraction) && !m_puserinteraction->m_bUserElementOk)
         {

            return;

         }

         ::message::mouse * pmouse = (::message::mouse *) pusermessage;

         if(get_session() != nullptr)
         {

            psession->on_ui_mouse_message(pmouse);

            psession->m_pointCursor = pmouse->m_point;

         }

         if(m_puserinteraction != nullptr && m_puserinteraction->get_session()  != nullptr && m_puserinteraction->get_session() != get_session())
         {

            Sess(m_puserinteraction->get_session()).m_pointCursor = pmouse->m_point;

         }

         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {
            pmouse->m_bTranslated = true;
            ::double_rectangle rectangleWindow;
            if(m_bScreenRelativeMouseMessagePosition)
            {

               information() << "Screen Relative Mouse Message Position";
               ::double_rectangle rectangleWindow32;
               ::window_rectangle((oswindow) get_handle(), &rectangleWindow32);
               ::copy(rectangleWindow, rectangleWindow32);
            }
            else
            {
               m_puserinteraction->window_rectangle(rectangleWindow);
            }
            if(::acmeacmesystem()->get_monitor_count() > 0)
            {
               ::double_rectangle rcMonitor;
               ::acmeacmesystem()->get_monitor_rectangle(0, &rcMonitor);
               if(rectangleWindow.left() >= rcMonitor.left())
                  pmouse->m_point.x() += (int) rectangleWindow.left();
               if(rectangleWindow.top() >= rcMonitor.top())
                  pmouse->m_point.y() += (int) rectangleWindow.top();
            }
            else
            {
               if(rectangleWindow.left() >= 0)
                  pmouse->m_point.x() += (int) rectangleWindow.left();
               if(rectangleWindow.top() >= 0)
                  pmouse->m_point.y() += (int) rectangleWindow.top();
            }
         }

         if(pusermessage->m_emessage == e_message_mouse_move)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse transfer happenings should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = cursor_default;
         }

         _008OnMouse(pmouse);

         return;

      }
      else if(pusermessage->m_emessage == e_message_key_down ||
              pusermessage->m_emessage == e_message_key_up ||
              pusermessage->m_emessage == e_message_char)
      {

         ::message::key * pkey = (::message::key *) pusermessage;

         ::pointer<::user::interaction>puiFocus =  get_keyboard_focus();

         if(puiFocus != nullptr
               && puiFocus->is_window()
               && puiFocus->get_top_level() != nullptr
               && puiFocus != m_puserinteraction)
         {

            puiFocus->send(pkey);

            if(pusermessage->m_bRet)
            {

               return;

            }

         }
         else if(!pkey->m_bRet)
         {

            if(m_puserinteraction != nullptr)
            {

               m_puserinteraction->_000OnKey(pkey);

               if(pusermessage->m_bRet)
               {

                  return;

               }

            }

         }

         default_window_procedure(pusermessage);

         return;

      }

      if(pusermessage->m_emessage == e_message_event)
      {

         if(m_puserinteraction != nullptr)
         {

            m_puserinteraction->handle_event((::user::control_event *) pusermessage->m_lparam.m_lparam);

         }
         else
         {

            handle_event((::user::control_event *) pusermessage->m_lparam.m_lparam);

         }

         return;

      }

      if(::is_set(m_puserinteraction))
      {

         m_puserinteraction->route_message(pusermessage);

      }
      else
      {

         route_message(pusermessage);

      }

      if(pusermessage->m_bRet)
      {

         return;

      }

      default_window_procedure(pusermessage);

   }


//   bool interaction_impl::OnCommand(WPARAM wparam, LPARAM lparam)
//   {
//
//      __UNREFERENCED_PARAMETER(wparam);
//      __UNREFERENCED_PARAMETER(lparam);
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


//   ::user::interaction * interaction_impl::get_parent()
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
//      //return ::linux::interaction_impl::from_handle(::get_parent(get_handle()));
//
//      return nullptr;
//
//   }


//   ::user::interaction * interaction_impl::get_top_level()
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
   //            (hWndT = ::get_parent(hWndParent)) != nullptr)
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
//      ::pointer<::user::interaction>WndTopLevel=EnsureTopLevel();
//
//      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
//   }

//   void interaction_impl::ActivateTopParent()
//   {
//      // special activate logic for floating toolbars and palettes
//      ::pointer<::user::interaction>pActiveWnd = GetForegroundWindow();
////      if (pActiveWnd == nullptr || !(LNX_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(LNX_WINDOW(pActiveWnd)->get_handle(), get_handle())))
//      {
//         // clicking on floating frame when it does not have
//         // focus itself -- activate the toplevel frame instead.
//         EnsureTopLevel()->set_foreground_window();
//      }
//   }

   /*
      ::pointer<::user::frame_window>interaction_impl::top_level_frame()
      {
         if (get_handle() == nullptr) // no oswindow attached
            return nullptr;

         ASSERT_VALID(this);

         ::pointer<::user::frame_window>pFrameWnd = nullptr;
         if(m_puserinteraction != this)
            pFrameWnd =  (m_puserinteraction);
         else
            pFrameWnd =  (this);
         if (pFrameWnd == nullptr || !pFrameWnd->is_frame_window())
            pFrameWnd = get_parent_frame();

         if (pFrameWnd != nullptr)
         {
            ::pointer<::user::frame_window>pTemp;
            while ((pTemp = pFrameWnd->get_parent_frame()) != nullptr)
               pFrameWnd = pTemp;
         }
         return pFrameWnd;
      }*/

   /*   ::pointer<::interaction_impl>interaction_impl::GetSafeOwner(::interaction_impl * pParent, oswindow* pWndTop)
      {
         oswindow hWnd = GetSafeOwner_((oswindow) pParent->get_handle(), pWndTop);
         return ::linux::interaction_impl::from_handle(hWnd);
      }
   */
//   int interaction_impl::message_box(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrcaption, unsigned int nType)
//   {
//
//      string strCaption;
//
//      if (pszcaption == nullptr)
//      {
//
//         strCaption = get_app()->m_strAppName;
//
//      }
//      else
//      {
//
//         strCaption = pszcaption;
//
//      }
//
//      int nResult = ::auto pmessagebox = __initialize_new ::message_box((oswindow)get_handle(), pszText, strCaption, nType);

pmessagebox->sync();
//
//      return nResult;
//
//   }


   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::impact) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID


//   int interaction_impl::SetScrollPos(int nBar, int nPos, bool bRedraw)
//   {
////      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
//      return 0;
//   }
//
//   int interaction_impl::GetScrollPos(int nBar) const
//   {
//      //return ::GetScrollPos(get_handle(), nBar);
//      return 0;
//   }
//
//   void interaction_impl::SetScrollRange(int nBar, int nMinPos, int nMaxPos, bool bRedraw)
//   {
//      //::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
//   }

//   void interaction_impl::GetScrollRange(int nBar, LPINT pMinPos, LPINT lpMaxPos) const
//
//   {
//      //::GetScrollRange(get_handle(), nBar, pMinPos, lpMaxPos);
//
//   }
//
//   // Turn on/off non-control scrollbars
//   //   for WS_?SCROLL scrollbars - show/hide them
//   //   for control scrollbar - enable/disable them
//   void interaction_impl::EnableScrollBarCtrl(int nBar, bool bEnable)
//   {
//      // WS_?SCROLL scrollbar - show or hide
//      ShowScrollBar(nBar, bEnable);
//   }

   /*
      bool interaction_impl::SetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, bool bRedraw)

      {
         ASSERT(pScrollInfo != nullptr);


         oswindow hWnd = get_handle();
         pScrollInfo->cbSize = sizeof(*lpScrollInfo);

         ::SetScrollInfo(hWnd, nBar, pScrollInfo, bRedraw);

         return true;
      }

      bool interaction_impl::GetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, unsigned int nMask)

      {
         __UNREFERENCED_PARAMETER(nMask);
         ASSERT(pScrollInfo != nullptr);


         oswindow hWnd = get_handle();
         return ::GetScrollInfo(hWnd, nBar, pScrollInfo) != false;

      }
   */
//   int interaction_impl::GetScrollLimit(int nBar)
//   {
//      int nMin, nMax;
//      GetScrollRange(nBar, &nMin, &nMax);
//      /*      SCROLLINFO info;
//            if (GetScrollInfo(nBar, &info, SIF_PAGE))
//            {
//               nMax -= maximum(info.nPage-1,0);
//            }*/
//      return nMax;
//   }
//
//   void interaction_impl::ScrollWindow(int xAmount, int yAmount,
//                                       const ::double_rectangle & rectangle, const ::double_rectangle & lpClipRect)
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
//                     ::double_rectangle rectangle;
//                     ::window_rectangle(hWndChild, &rectangle);
//                     screen_to_client(&rectangle);
//                     ::set_window_position(hWndChild, nullptr,
//                        rectangle.left()+xAmount, rectangle.top()+yAmount, 0, 0,
//                        SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
//                  }
//               }
//            }
//      */
//   }
//
//
//   void interaction_impl::CalcWindowRect(RECT32 * pClientRect, unsigned int nAdjustType)
//   {
//
//      /*unsigned int dwExStyle = GetExStyle();
//      if (nAdjustType == 0)
//         dwExStyle &= ~WS_EX_CLIENTEDGE;
//      ::AdjustWindowRectEx(pClientRect, GetStyle(), false, dwExStyle);*/
//
//   }
//
//   /////////////////////////////////////////////////////////////////////////////
//   // Special keyboard/system command processing
//
//   bool interaction_impl::HandleFloatingSysCommand(unsigned int nID, LPARAM lparam)
//
//   {
//      /*      ::pointer<::user::interaction>pParent = GetTopLevelParent();
//            switch (nID & 0xfff0)
//            {
//            case SC_PREVWINDOW:
//            case SC_NEXTWINDOW:
//               if (LOWORD(lparam) == VK_F6 && pParent != nullptr)
//
//               {
//                  pParent->XXXSetFocus();
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
//                     pParent->set_active_window();
//                     pParent->send_message(WM_SYSCOMMAND, nID, lparam);
//
//
//                     // be very careful here...
//                     if (::is_window(hWndSave))
//                        ::XXXSetActiveWindow(hWndSave);
//                     if (::is_window(hWndFocus))
//                        ::XXXSetFocus(hWndFocus);
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
//      ::pointer<::user::message>pusermessage(pmessage);
//      // walk from the target interaction_impl up to the hWndStop interaction_impl checking
//      //  if any interaction_impl wants to translate this message
//
//      for (::pointer<::user::interaction>pinteraction = pusermessage->m_puserinteraction; pinteraction != nullptr; pinteraction->get_parent())
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
//      /*      single_lock synchronouslock(::windows_definition::MutexHwnd(), true);
//            hwnd_map * pMap = ::windows_definition::MapHWND();
//            if (pMap == nullptr)
//               return false;
//
//            // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
//            ::pointer<::interaction_impl>pWnd =  (pMap->lookup_permanent(hWndChild)); */
//
//      __s_throw(todo());
////      ::pointer<::user::interaction>pWnd =  (FromHandlePermanent(hWndChild));
////      ASSERT(pWnd == nullptr || pWnd->get_handle() == hWndChild);
////      if (pWnd == nullptr)
////      {
////         return false;
////      }
////
////      // only OLE controls and permanent windows will get reflected msgs
////      ASSERT(pWnd != nullptr);
////      return pWnd->SendChildNotifyLastMsg(pResult);
//   }
//
//   bool interaction_impl::OnChildNotify(unsigned int uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//
//   {
//
//      return ReflectChildNotify(uMsg, wparam, lparam, pResult);
//
//   }
//
//   bool interaction_impl::ReflectChildNotify(unsigned int uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
//
//   {
//      __UNREFERENCED_PARAMETER(wparam);
//      // Note: reflected messages are send directly to interaction_impl::OnWndMsg
//      //  and interaction_impl::_001OnCommand for speed and because these messages are not
//      //  routed by normal _001OnCommand routing (they are only dispatched)
//
//      switch (uMsg)
//      {
//      // normal messages (just wparam, lparam through OnWndMsg)
//
//      case e_message_scroll_x:
//      case e_message_scroll_y:
//      case WM_PARENTNOTIFY:
//      case WM_DRAWITEM:
//      case e_message_measure_item:
//      case WM_DELETEITEM:
//      case WM_VKEYTOITEM:
//      case WM_CHARTOITEM:
//      case WM_COMPAREITEM:
//         // reflect the message through the message ::collection::map as WM_REFLECT_BASE+uMsg
//         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wparam, lparam, pResult);
//
//         return false;
//
//      // special case for e_message_command
//      case e_message_command:
//      {
//         // reflect the message through the message ::collection::map as OCM_COMMAND
//         /* xxx         int nCode = HIWORD(wparam);
//         if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+e_message_command), nullptr, nullptr))
//         {
//         if (pResult != nullptr)
//         *pResult = 1;
//         return true;
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
//                  //            int nCode = pNMHDR->code;
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
//            bResult = false;
//            return bResult;*/
//            return false;
//         }
//         break;
//      }
//
//      return false;   // let the parent handle it
//   }
//
//   void interaction_impl::OnParentNotify(const ::atom & atom, LPARAM lparam)
//
//   {
//      if ((LOWORD(message) == e_message_create || LOWORD(message) == e_message_destroy))
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
//      bHandled = false;
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
//   void interaction_impl::OnSettingChange(unsigned int uFlags, const ::scoped_string & scopedstrSection)
//
//   {
//
//      gen_GotScrollLines = false;
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
//         send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam, true, true);
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
//      throw ::not_implemented();
////
////      LPDRAGLISTINFO pInfo = (LPDRAGLISTINFO)lparam;
//
////      ASSERT(pInfo != nullptr);
//
////
////      LRESULT lResult;
////      if (ReflectLastMsg(pInfo->hWnd, &lResult))
//
////         return (int)lResult;    // eat it
////
////      // not handled - do default
////      return (int)Default();
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
////            unsigned int tickStart;
////
////            while (::task_get_run())
////            {
////
//// auto tickStart = ::duration::now();
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
////                  informationf("window is locked for drawing update");
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
////               unsigned int dwDiff = tickStart.elapsed();
////
////               if (dwDiff < 20)
////               {
////
////                  sleep(20 - dwDiff);
////
////               }
////
////               //sleep(500_ms);
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
////      ::windowing::window::set_need_redraw();
////
////   }
//

   void interaction_impl::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

//      Default();

//      if(m_puserinteraction->is_message_only_window())
//      {
//
//         informationf("good : opt out!");
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
//      return true;
//   }
//
//   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
//   {
//      __s_throw(not_implemented());
////      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
//   }

//   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image::image *pimage)
//   {
//
//      _001DeferPaintLayeredWindowBackground(pgraphics);
//
//   }



//   class print_window :
//      virtual ::matter
//   {
//   public:
//
//
//
//      manual_reset_happening m_happening;
//      oswindow m_hwnd;
//      HDC m_hdc;
//
//      print_window(::particle * pparticle, oswindow hwnd, HDC hdc, unsigned int tickTimeout) :
//         ::matter(pparticle)
//      {
//         m_happening.reset_happening();
//         m_hwnd = hwnd;
//         m_hdc = hdc;
//
//         fork();
//#undef timeout
//
//         if(m_happening.wait(::duration(tickTimeout)).timeout())
//         {
//            informationf("print_window::time_out");
//         }
//      }
//
//
//      virtual void     run() override
//      {
//
//         try
//         {
////            HANDLE hevent = (HANDLE) pprintwindow->m_happening.get_os_data();
//            //          throw ::not_implemented();
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
//      ::double_rectangle rectangleX;
//
//      m_puserinteraction->rectangle(rectangleX);
//
//
//      //pgraphics->FillSolidRect(rectangleX, 0x00000000);
//
//      //return;
//      ::double_rectangle rectangleUpdate;
//      m_puserinteraction->window_rectangle(rectangleUpdate);
////      SetContextOrgEx(hdc, 0, 0, nullptr);
//      ::double_rectangle rectanglePaint;
//      rectanglePaint = rectangleUpdate;
//      m_puserinteraction->screen_to_client(rectanglePaint);
//      user::oswindow_array wndaApp;
//
//
//      HRGN rgnWindow;
//      HRGN rgnIntersect;
//      HRGN rgnUpdate = nullptr;
//
//      throw ::not_implemented();
//      /*
//            rgnWindow = CreateRectRgn(0, 0, 0, 0);
//            rgnIntersect = CreateRectRgn(0, 0, 0, 0);
//      */
//      //      int iCount = wndaApp.get_count();
//
//      throw ::not_implemented();
//   }
//
//   void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
//   {
//      __UNREFERENCED_PARAMETER(pmessage);
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

      return ::is_window(m_oswindow) != false;

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

//      if(::is_null(m_oswindow))
//      {
//
//         return;
//
//      }
//
//      x11_sync([this]()
//      {
//
//         m_oswindow->exit_zoomed();
//
//      });

   }



//   bool interaction_impl::set_window_position(iptr z, int x, int y, int cx, int cy, unsigned int nFlags)
//   {
//
//      if(!(nFlags & SWP_NOMOVE))
//      {
//
//         m_puserinteraction->m_pointRequest = ::int_point(x, y);
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
//      if(!::set_window_position(get_handle(), (oswindow)z, x, y, cx, cy, nFlags))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }





//   void interaction_impl::MoveWindow(int x, int y, int nWidth, int nHeight, bool bRepaint)
//   {
//
//      set_window_position(0, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);
//
//   }


//   ::int_point interaction_impl::client_screen_top_left()
//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return double_point(0.0,0.0);
//
//      }
//
//      return rectangleWindow.top_left();
//
//   }
//
//
//   bool interaction_impl::client_to_screen(RECT32 * prect)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left()   += (int) rectangleWindow.left();

//      prect->right()  += (int) rectangleWindow.left();

//      prect->top()    += (int) rectangleWindow.top();

//      prect->bottom() += (int) rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::client_to_screen(POINT32 * ppoint)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     += (int) rectangleWindow.left();

//      ppoint->y     += (int) rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::client_to_screen(RECT64 * prect)

//   {
//
//      ::double_rectangle rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left()   += rectangleWindow.left();

//      prect->right()  += rectangleWindow.left();

//      prect->top()    += rectangleWindow.top();

//      prect->bottom() += rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::client_to_screen(POINT64 * ppoint)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     += rectangleWindow.left();

//      ppoint->y     += rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::screen_to_client(RECT32 * prect)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left()   -= (int) rectangleWindow.left();

//      prect->right()  -= (int) rectangleWindow.left();

//      prect->top()    -= (int) rectangleWindow.top();

//      prect->bottom() -= (int) rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::screen_to_client(POINT32 * ppoint)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     -= (int) rectangleWindow.left();

//      ppoint->y     -= (int) rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::screen_to_client(RECT64 * prect)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      prect->left()   -= rectangleWindow.left();

//      prect->right()  -= rectangleWindow.left();

//      prect->top()    -= rectangleWindow.top();

//      prect->bottom() -= rectangleWindow.top();

//
//      return true;
//
//   }
//
//
//   bool interaction_impl::screen_to_client(POINT64 * ppoint)

//   {
//
//      ::rect64 rectangleWindow;
//
//      if(!window_rectangle(rectangleWindow))
//      {
//
//         return false;
//
//      }
//
//      ppoint->x     -= rectangleWindow.left();

//      ppoint->y     -= rectangleWindow.top();

//
//      return true;
//
//   }


//   bool interaction_impl::_001GetWindowRect(RECT64 * prect)
//   {
//
//      return ::windowing::window::window_rectangle(prect);
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
//         ::double_rectangle rect32;
//
//         if(!::window_rectangle((oswindow) get_handle(), rect32))
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
//         //      primitive_impl::window_rectangle(prect);
//
//      }
//
//      return true;
//
//   }
//
//
//   bool interaction_impl::window_rectangle(RECT64 * prect)
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
//   bool interaction_impl::this->rectangle(RECT64 * prect)
//
//   {
//
//
//      return ::windowing::window::this->rectangle(prect);
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
//         ::double_rectangle rect32;
//
//         //if(!::this->rectangle((oswindow) get_handle(), rect32))
//         //{
//
//         // return false;
//
//         //}
//
//         rect64 r = m_puserinteraction->m_rectangleParentClient;
//
//         rectangle.offset(rectangle.top_left());
//
//         *prect = r;
//
//
//      }
//      //else
//      {
//         // interaction::this->rectangle(prect);
//
//      }
//
//      return true;
//
//   }


//   atom interaction_impl::SetDlgCtrlId(atom atom)
//   {
//
//      return m_puserinteraction->SetDlgCtrlId(atom);
//
//   }
//
//
//   atom interaction_impl::GetDlgCtrlId()
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
//         m_puserinteraction->dis = ::e_display_normal;
//
//      }
//
//      ::show_window(m_oswindow, e_display_normal);
//
//   }


//   void interaction_impl::WfiOnMinimize(bool bNoActivate)
//   {
//
//      m_puserinteraction->display(e_display_iconic);
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


   bool interaction_impl::node_is_iconic()
   {

      if(!::is_window(m_oswindow))
      {

         return false;

      }

#ifdef LINUX

      return m_puserinteraction->layout().design().display() == ::e_display_iconic;

#else

      if(GetExStyle() & WS_EX_LAYERED)
      {

         return m_puserinteraction->m_edisplay == ::e_display_iconic;

      }
      else
      {

         return ::is_iconic((oswindow) get_handle()) != false;

      }

#endif

   }


   LONG_PTR interaction_impl::get_window_long_ptr(int nIndex) const
   {

      return ::GetWindowLongPtr((oswindow) get_handle(), nIndex);

   }


   LONG_PTR interaction_impl::set_window_long_ptr(int nIndex, LONG_PTR lValue)
   {

      return ::SetWindowLongPtr((oswindow) get_handle(), nIndex, lValue);

   }





   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const ::windowing::window& wnd) const
   {
      return wnd.get_handle() ==((interaction_impl *)this)->get_handle();
   }

   bool interaction_impl::operator!=(const ::windowing::window& wnd) const
   {
      return wnd.get_handle() != ((interaction_impl *)this)->get_handle();
   }


   unsigned int interaction_impl::GetStyle() const
   {

      return (unsigned int)::GetWindowLong((oswindow) get_handle(), GWL_STYLE);

   }


   unsigned int interaction_impl::GetExStyle() const
   {

      return (unsigned int)::GetWindowLong((oswindow) get_handle(), GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   {

      set_window_long(GWL_STYLE, (GetStyle() | dwAdd) & ~(dwRemove));

      if(nFlags != 0)
      {

         //set_window_position(0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | nFlags);
         set_need_redraw();

      }

      return true;

   }


   bool interaction_impl::ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   {

      set_window_long(GWL_EXSTYLE, (GetExStyle() | dwAdd) & ~(dwRemove));

      if(nFlags != 0)
      {

         //set_window_position(0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | nFlags);
         set_need_redraw();

      }

      return true;

   }


   void interaction_impl::set_owner(::user::interaction * pOwnerWnd)
   {
//      m_puiOwner = pOwnerWnd;
      m_puserinteraction->SetOwner((pOwnerWnd));
   }


   LRESULT interaction_impl::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)

   {

      return ::windowing::window::send_message(message, wparam, lparam);


   }


   bool interaction_impl::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

//      if(::is_set(m_pwindowthread))
//      {
//
//         return ::windowing::window::post_message(message, wparam, lparam);
//
//      }
//
      return ::post_message((oswindow) get_handle(), message, wparam, lparam) != false;

   }


//   bool interaction_impl::DragDetect(const ::int_point & point) const
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//
//      //return ::DragDetect(get_handle(), point) != false;
//
//   }
//

   void interaction_impl::set_window_text(const ::scoped_string & scopedstrString)

   {

      m_strWindowText = pszString;


      //windowing_output_debug_string("\nlinux::interaction_impl::set_window_text");

      //fflush(stdout);

      x11_store_name(m_oswindow, m_strWindowText);

      //windowing_output_debug_string("\nlinux::interaction_impl::set_window_text END");

      //fflush(stdout);

   }


//   character_count interaction_impl::GetWindowText(char * pszString, character_count nMaxCount)

//   {
//
//      ansi_count_copy(pszString, m_strWindowText, nMaxCount);

//
//      return minimum(nMaxCount, m_strWindowText.length());
//
//   }

//
//   character_count interaction_impl::GetWindowTextLength()
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//
//      //return ::GetWindowTextLength(get_handle());
//
//   }


   void interaction_impl::SetFont(::write_text::font* pfont, bool bRedraw)
   {

      __UNREFERENCED_PARAMETER(bRedraw);

      //ASSERT(::is_window((oswindow) get_handle())); m_pfont = aaa_primitive_new ::write_text::font(*pfont);

   }


   ::write_text::font* interaction_impl::GetFont()
   {

      //ASSERT(::is_window((oswindow) get_handle()));

      //return m_pfont;
      return nullptr;

   }


//   void interaction_impl::DragAcceptFiles(bool bAccept)
//   {
//
//      throw ::not_implemented();
//
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::DragAcceptFiles(get_handle(), bAccept);
//
//   }
//
//   /*
//      ::pointer<::user::frame_window>interaction_impl::EnsureParentFrame()
//      {
//
//         ::pointer<::user::frame_window>pFrameWnd=get_parent_frame();
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
//         ::pointer<::user::interaction>Wnd=GetTopLevelParent();
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
////   void interaction_impl::MoveWindow(const ::double_rectangle & rectangle, bool bRepaint)
////   {
////
////      MoveWindow(rectangle.left(), rectangle.top(), rectangle.right() - rectangle.left(), rectangle.bottom() - rectangle.top(), bRepaint);
////
////   }
//
//
//   unsigned int interaction_impl::ArrangeIconicWindows()
//   {
//
//      throw ::not_implemented();
//
////      ASSERT(::is_window((oswindow) get_handle())); return ::ArrangeIconicWindows(get_handle());
//
//   }
//
//
//   int interaction_impl::SetWindowRgn(HRGN hRgn, bool bRedraw)
//   {
//
//      __UNREFERENCED_PARAMETER(hRgn);
//      __UNREFERENCED_PARAMETER(bRedraw);
//
//      //throw ::not_implemented();
//
////      ASSERT(::is_window((oswindow) get_handle())); return ::SetWindowRgn(get_handle(), hRgn, bRedraw);
//      return 0;
//   }
//
//
//   int interaction_impl::GetWindowRgn(HRGN hRgn)
//   {
//
//      throw ::not_implemented();
//
////      ASSERT(::is_window((oswindow) get_handle()) && hRgn != nullptr); return ::GetWindowRgn(get_handle(), hRgn);
//
//   }
//
//
//   bool interaction_impl::BringWindowToTop()
//   {
//
////      throw ::not_implemented();
////      return ::BringWindowToTop(get_handle()) != false;
//      return true;
//   }
//
//
//   void interaction_impl::MapWindowPoints(::user::interaction * puserinteractionTo, POINT32 * pPoint, unsigned int nCount)
//
//   {
//
//      throw ::not_implemented();
//
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::MapWindowPoints(get_handle(), (oswindow) puserinteractionTo->get_handle(), pPoint, nCount);
//
//
//   }
//
//
//   void interaction_impl::MapWindowPoints(::user::interaction * puserinteractionTo, RECT32 * prect)
//
//   {
//
//      throw ::not_implemented();
//
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::MapWindowPoints(get_handle(), (oswindow) puserinteractionTo->get_handle(), (POINT32 *)prect, 2);
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
//      ::double_rectangle rectangleX;
//
//      //oswindow->rectangle(rectangleX);
//
//      rectangleX.left() = 0;
//      rectangleX.top() = 0;
//      rectangleX.right() = 500;
//      rectangleX.bottom() = 500;
////      (dynamic_cast < ::linux::graphics * >(g.m_p))->attach(cairo_create(cairo_xlib_surface_create(oswindow->display(), oswindow->interaction_impl(), oswindow->draw2d(),rectangleX.width(), rectangleX.height())));
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
//   bool interaction_impl::ReleaseDC(::image::image *pimage)
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
//      //throw ::not_implemented();
//      //::UpdateWindow(get_handle());
//   }
//
//   void interaction_impl::SetRedraw(bool bRedraw)
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
//   }
//
//   bool interaction_impl::GetUpdateRect(RECT32 * prect, bool bErase)
//
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::GetUpdateRect(get_handle(), prect, bErase) != false;
//
//   }
//
//   int interaction_impl::GetUpdateRgn(draw2d::region * pRgn, bool bErase)
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
//   }
//
//   void interaction_impl::Invalidate(bool bErase)
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::InvalidateRect(get_handle(), nullptr, bErase);
//   }
//
//   void interaction_impl::InvalidateRect(const ::double_rectangle & rectangle, bool bErase)
//
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::InvalidateRect(get_handle(), prect, bErase);
//
//   }
//
//   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
//   }
//
//   void interaction_impl::ValidateRect(const ::double_rectangle & rectangle)
//
//   {
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::ValidateRect(get_handle(), prect);
//
//   }
//
//   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
//   {
//      throw ::not_implemented();
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
//      if(m_puserinteraction->m_puserinteractionParent != nullptr)
//      {
//
//         if(!m_puserinteraction->m_puserinteractionParent->is_window_visible())
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
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::ShowOwnedPopups(get_handle(), bShow);
//
//   }
//
////   void interaction_impl::send_message_to_descendants(::enum_message emessage, ::wparam wparam, ::lparam lparam, bool bDeep, bool bOnlyPerm)
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
//   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip, unsigned int flags)
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::draw2d::graphics_pointer g(this);
//      //g->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_handle(), flags));
//      //return g.detach();
//
//   }
//
//   bool interaction_impl::LockWindowUpdate()
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::LockWindowUpdate(get_handle()) != false;
//
//   }
//
//   void interaction_impl::UnlockWindowUpdate()
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //::LockWindowUpdate(nullptr);
//
//   }
//

//   bool interaction_impl::RedrawWindow(const ::double_rectangle& rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
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
      bool interaction_impl::EnableScrollBar(int nSBFlags, unsigned int nArrowFlags)
      {

         ASSERT(::is_window((oswindow) get_handle()));

         return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != false;

      }
   */

//   bool interaction_impl::DrawAnimatedRects(int idAni, const LPRECTprcFrom, const LPRECTlprcTo)
//
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::DrawAnimatedRects(get_handle(), idAni, prcFrom, lprcTo) != false;
//
//
//   }


//   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, const rectangle & prc, unsigned int uFlags)
//
//   {
//
//      throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle(), prc, uFlags) != false;
//
//
//   }
//
//
//   bool interaction_impl::SetTimer(uptr uEvent, unsigned int nElapse, PFN_TIMER pfnTimer)
//   {
//
//      return ::windowing::window::SetTimer(uEvent, nElapse, pfnTimer);
//
//
////        __UNREFERENCED_PARAMETER(pfnTimer);
//
////
////        m_puserinteraction->get_app()->set_timer(m_puserinteraction, uEvent, nElapse);
////
////        return uEvent;
//
//      //throw ::not_implemented();
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::SetTimer(get_handle(), uEvent, nElapse, pfnTimer);
//
//
//   }
//
//
//   bool interaction_impl::KillTimer(uptr uEvent)
//   {
//
//      return ::windowing::window::KillTimer(uEvent);
//
////       m_puserinteraction->get_app()->unset_timer(m_puserinteraction, uEvent);
//
//      //     return true;
//
//      //return ::user::int
//
//      //ASSERT(::is_window((oswindow) get_handle()));
//      //return ::KillTimer(get_handle(), uEvent)  != false;
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

      ::windowing::window * pimpl = ::linux::interaction_impl::from_handle(oswindow);

      if(pimpl == nullptr)
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::user::interaction * interaction_impl::set_active_window()
   {

      return nullptr;


//      ::windowing::window * pimpl = ::linux::interaction_impl::from_handle(::set_active_window(get_handle()));

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


   bool interaction_impl::set_keyboard_focus()
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
//   int interaction_impl::GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)
//   {
//      for (int nID = nIDFirstButton; nID <= nIDLastButton; nID++)
//      {
//         if (IsDlgButtonChecked(nID))
//            return nID; // atom that matched
//      }
//      return 0; // invalid ID
//   }
//
//   void interaction_impl::CheckDlgButton(int nIDButton, unsigned int nCheck)
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::CheckDlgButton(get_handle(), nIDButton, nCheck);
//
//   }
//
//   void interaction_impl::CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);
//
//   }
//
//   int interaction_impl::DlgDirList(char * pPathSpec, int nIDListBox, int nIDStaticPath, unsigned int nFileType)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirList(get_handle(), pPathSpec, nIDListBox, nIDStaticPath, nFileType);
//
//
//   }
//
//   int interaction_impl::DlgDirListComboBox(char * pPathSpec, int nIDComboBox, int nIDStaticPath, unsigned int nFileType)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirListComboBox(get_handle(), pPathSpec, nIDComboBox, nIDStaticPath, nFileType);
//
//
//   }
//
//   bool interaction_impl::DlgDirSelect(char * pString, int nSize, int nIDListBox)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirSelectEx(get_handle(), pString, nSize, nIDListBox) != false;
//
//
//   }
//
//   bool interaction_impl::DlgDirSelectComboBox(char * pString, int nSize, int nIDComboBox)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::DlgDirSelectComboBoxEx(get_handle(), pString, nSize, nIDComboBox) != false;
//
//
//   }
//
//   /*
//      void interaction_impl::GetDlgItem(atom atom, oswindow* phWnd) const
//      {
//
//         ASSERT(::is_window((oswindow) get_handle()));
//         ASSERT(phWnd != nullptr);
//         *phWnd = ::GetDlgItem(get_handle(), (int) atom);
//
//      }
//   */
//
//   /*
//      unsigned int interaction_impl::GetDlgItemInt(int nID, int_bool * pTrans, bool bSigned) const
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
////   int interaction_impl::GetDlgItemText(int nID, char * pStr, int nMaxCount) const
//
////   {
////
////      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle())); return ::GetDlgItemText(get_handle(), nID, pStr, nMaxCount);}
//
//
//   ::user::interaction * interaction_impl::GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious) const
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetNextDlgGroupItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));
//
//   }
//
//   ::user::interaction * interaction_impl::GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious) const
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetNextDlgTabItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));
//
//   }
//
//   unsigned int interaction_impl::IsDlgButtonChecked(int nIDButton) const
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::IsDlgButtonChecked(get_handle(), nIDButton);
//
//   }
//
//   LPARAM interaction_impl::SendDlgItemMessage(int nID, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::SendDlgItemMessage(get_handle(), nID, message, wparam, lparam);
//
//
//   }
//
//   void interaction_impl::SetDlgItemInt(int nID, unsigned int nValue, bool bSigned)
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);
//
//   }
//
//   void interaction_impl::SetDlgItemText(int nID, const ::scoped_string & scopedstrString)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::SetDlgItemText(get_handle(), nID, pszString);
//
//
//   }
//
//   int interaction_impl::ScrollWindowEx(int Δx, int Δy, const rectangle & pRectScroll, const rectangle & lpRectClip, ::draw2d::region * prgnUpdate, RECT32 * lpRectUpdate, unsigned int flags)
//
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::ScrollWindowEx(get_handle(), Δx, Δy, pRectScroll, lpRectClip, (HRGN)prgnUpdate->get_handle(), lpRectUpdate, flags);
//
//
//   }
//
//   void interaction_impl::ShowScrollBar(unsigned int nBar, bool bShow)
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::ShowScrollBar(get_handle(), nBar, bShow);
//
//   }
//
//   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::int_point & point)
//   {
//
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::ChildWindowFromPoint(get_handle(), point));
//
//   }
//
//   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags)
//   {
//
//      throw ::not_implemented();
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
//      //  throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::linux::interaction_impl::from_handle(::GetTopWindow(get_handle()));
//
//   }
//
//   ::user::interaction * interaction_impl::GetWindow(unsigned int nCmd)
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
//      throw ::exception(todo);
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
//   ::user::interaction * PASCAL interaction_impl::oswindowFromPoint(const ::int_point & point)
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
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::FlashWindow(get_handle(), bInvert) != false;
//
//   }
//
//   bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::ChangeClipboardChain(get_handle(), hWndNext) != false;
//
//   }
//
//   oswindow interaction_impl::SetClipboardViewer()
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::SetClipboardViewer(get_handle());
//
//   }
//
//   bool interaction_impl::OpenClipboard()
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::OpenClipboard(get_handle()) != false;
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
////      const ::int_point & point;
////      ::GetcaretPos((POINT32 *)&point); return point;
//
//   }
//
//
//   void PASCAL interaction_impl::SetCaretPos(const ::int_point & point)
//   {
//
//      __s_throw(not_implemented());
////      ::SetcaretPos(point.x(), point.y());
//
//   }
//
//
//   void interaction_impl::HideCaret()
//   {
//
//      throw ::not_implemented();
////      ::Hidecaret(get_handle());
//
//   }
//
//   void interaction_impl::ShowCaret()
//   {
//
//      throw ::not_implemented();
////    ::Showcaret(get_handle());
//   }
//


   bool interaction_impl::set_foreground_window()
   {

      return ::set_foreground_window(get_handle()) != false;

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
//   bool interaction_impl::SendNotifyMessage(::enum_message emessage, ::wparam wparam, ::lparam lparam)
//
//   {
//
//      throw ::not_implemented();
////      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != false;
//
//
//   }
//
//   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      const_cast < interaction_impl * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle(), dwFlags);
//
//   }
//
//   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      const_cast < interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::linux::graphics * >(pgraphics))->get_handle(), dwFlags);
//
//   }
//
//   bool interaction_impl::SetWindowContextHelpId(unsigned int dwContextHelpId)
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != false;
//
//   }
//
//   unsigned int interaction_impl::GetWindowContextHelpId() const
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::GetWindowContextHelpId(get_handle());
//
//   }
//
//
//   // Default message ::collection::map implementations
//   void interaction_impl::OnActivateApp(bool, unsigned int)
//   {
//   //Default();
//   }
//   void interaction_impl::OnActivate(unsigned int, ::user::interaction *, bool)
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
//   LRESULT interaction_impl::OnMenuChar(unsigned int, unsigned int, ::user::menu*)
//   {
//   //Default();
//   }
//   void interaction_impl::OnMenuSelect(unsigned int, unsigned int, HMENU)
//   {
//   //Default();
//   }
//   void interaction_impl::OnMove(int, int)
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
//      //return Default() != false;
//      return true;
//
//   }
//
//   bool interaction_impl::OnQueryOpen()
//   {
//
//      //return Default() != false;
//      return true;
//
//   }
//
//    void interaction_impl::on_message_set_cursor(::message::message * pmessage)
//    {
//       ::pointer<::user::message>pusermessage(pmessage);
//       if(psession->get_cursor() != nullptr
//             && psession->get_cursor()->m_ecursor != cursor_system)
//       {

//          throw ::not_implemented();
// //         ::SetCursor(nullptr);
//       }
//       pusermessage->m_lresult  = 1;
//       pusermessage->m_bRet = true;
//       //(bool)Default();
//    }


//   void interaction_impl::OnShowWindow(bool, unsigned int)
//   {
//   //Default();
//   }
//   void interaction_impl::OnSize(unsigned int, int, int)
//   {
//   //Default();
//   }
//   void interaction_impl::OnTcard(unsigned int, unsigned int)
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
//      //return Default() != false;
//      return true;
//
//   }
//
//   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
//   {
//   //Default();
//   }
//
//   bool interaction_impl::OnNcCreate(::user::system *)
//   {
//
////      return Default() != false;
//return true;
//
//   }

//   LRESULT interaction_impl::OnNcHitTest(point)
//   { return Default(); }
//   void interaction_impl::OnNcLButtonDblClk(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcLButtonDown(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcLButtonUp(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcMButtonDblClk(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcMButtonDown(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcMButtonUp(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcMouseMove(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcPaint()
//   { Default(); }
//   void interaction_impl::OnNcRButtonDblClk(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcRButtonDown(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnNcRButtonUp(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnSysChar(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnSysCommand(unsigned int, LPARAM)
//   { Default(); }
//   void interaction_impl::OnSysDeadChar(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnSysKeyDown(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnSysKeyUp(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnCompacting(unsigned int)
//   { Default(); }
//   void interaction_impl::OnFontChange()
//   { Default(); }
//   void interaction_impl::OnPaletteChanged(::user::interaction *)
//   { Default(); }
//   void interaction_impl::OnSpoolerStatus(unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnTimeChange()
//   { Default(); }
//   void interaction_impl::OnChar(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnDeadChar(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnKeyDown(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnKeyUp(unsigned int, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnLButtonDblClk(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnLButtonDown(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnLButtonUp(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnMButtonDblClk(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnMButtonDown(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnMButtonUp(unsigned int, point)
//   { Default(); }
//   int interaction_impl::OnMouseActivate(::user::interaction *, unsigned int, unsigned int)
//   { return (int)Default(); }
//   void interaction_impl::OnMouseMove(unsigned int, point)
//   { Default(); }

//   bool interaction_impl::OnMouseWheel(unsigned int, short, point)
//   {
//
//      return Default() != false;
//
//   }
//
//   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
//   { return Default(); }
//   void interaction_impl::OnRButtonDblClk(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnRButtonDown(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnRButtonUp(unsigned int, point)
//   { Default(); }
//   void interaction_impl::OnTimer(uptr)
//   { Default(); }
//   void interaction_impl::OnInitMenu(::user::menu*)
//   { Default(); }
//   void interaction_impl::OnInitMenuPopup(::user::menu*, unsigned int, bool)
//   { Default(); }
//   void interaction_impl::OnAskCbFormatName(unsigned int nMaxCount, char * lpszName)
//   {
//      (nMaxCount);
//      if(nMaxCount>0)
//      {
//         /* defwindow proc should do this for us, but to be safe, we'hi do it here too */
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
//   void interaction_impl::OnHScrollClipboard(::user::interaction *, unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnPaintClipboard(::user::interaction *, HGLOBAL)
//   { Default(); }
//   void interaction_impl::OnRenderAllFormats()
//   { Default(); }
//   void interaction_impl::OnRenderFormat(unsigned int)
//   { Default(); }
//   void interaction_impl::OnSizeClipboard(::user::interaction *, HGLOBAL)
//   { Default(); }
//   void interaction_impl::OnVScrollClipboard(::user::interaction *, unsigned int, unsigned int)
//   { Default(); }
//   unsigned int interaction_impl::OnGetDlgCode()
//   { return (unsigned int)Default(); }
//   void interaction_impl::OnMDIActivate(bool, ::user::interaction *, ::user::interaction *)
//   { Default(); }
//   void interaction_impl::OnEnterMenuLoop(bool)
//   { Default(); }
//   void interaction_impl::OnExitMenuLoop(bool)
//   { Default(); }
//   // Win4 support
////   void interaction_impl::OnStyleChanged(int, LPSTYLESTRUCT)
////   { Default(); }
////   void interaction_impl::OnStyleChanging(int, LPSTYLESTRUCT)
////   { Default(); }
//   void interaction_impl::OnSizing(unsigned int, RECT32 *)
//   { Default(); }
//   void interaction_impl::OnMoving(unsigned int, RECT32 *)
//   { Default(); }
//   void interaction_impl::OncaptureChanged(::user::interaction *)
//   { Default(); }
//
//   bool interaction_impl::OnDeviceChange(unsigned int, dword_ptr)
//   {
//
//      return Default() != false;
//
//   }
//
//   void interaction_impl::OnWinIniChange(const char *)
//   { Default(); }
//   void interaction_impl::OnChangeUIState(unsigned int, unsigned int)
//   { Default(); }
//   void interaction_impl::OnUpdateUIState(unsigned int, unsigned int)
//   { Default(); }
//
//   unsigned int interaction_impl::OnQueryUIState()
//   {
//
//      return (unsigned int)Default();
//
//   }

   // interaction_impl dialog data support
   //    void interaction_impl::DoDataExchange(CDataExchange*)
   //   { } // default does nothing

   // interaction_impl modality support

//   void interaction_impl::BeginModalState()
//   {
//
//      throw ::exception(todo);
//
//      //::EnableWindow(get_handle(), false);
//
//   }
//
//   void interaction_impl::EndModalState()
//   {
//
//      throw ::exception(todo);
//
//      //::EnableWindow(get_handle(), true);
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
//   void frame_window::set_title(const ::scoped_string & scopedstrTitle)
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
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      ::CloseWindow(get_handle());
//
//   }
//
//   bool interaction_impl::OpenIcon()
//   {
//
//      throw ::not_implemented();
////      ASSERT(::is_window((oswindow) get_handle()));
////      return ::OpenIcon(get_handle()) != false;
//
//   }
//
//   ////////////////////////////////////////////////////////////////////////////
//   // UI related ::windowing::window functions
//
//   oswindow PASCAL interaction_impl::GetSafeOwner_(oswindow hParent, oswindow* pWndTop)
//   {
//      // get ::windowing::window to start with
//      oswindow hWnd = hParent;
//      if (hWnd == nullptr)
//      {
//         /* trans      ::pointer<frame_window>pFrame = channel::GetRoutingFrame_();
//         if (pFrame != nullptr)
//         hWnd = pFrame->get_handle();
//         else
//         hWnd = ::acmeacmesystem()->GetMainWnd()->get_handle();*/
//      }
//
//      // a popup ::windowing::window cannot be owned by a child ::windowing::window
//      while (hWnd != nullptr && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
//         hWnd = ::get_parent(hWnd);
//
//      // determine toplevel ::windowing::window to disable as well
//      oswindow hWndTop = hWnd, hWndTemp = hWnd;
//      for (;;)
//      {
//         if (hWndTemp == nullptr)
//            break;
//         else
//            hWndTop = hWndTemp;
//         hWndTemp = ::get_parent(hWndTop);
//      }
//
//      __s_throw(todo());
//      // get last active popup of first non-child that was found
//      //    if (hParent == nullptr && hWnd != nullptr)
//      //       hWnd = ::GetLastActivePopup(hWnd);
//
//      // disable and store top level parent ::windowing::window if specified
//      if (pWndTop != nullptr)
//      {
//         /*         if (hWndTop != nullptr && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
//                  {
//                     *pWndTop = hWndTop;
//                     ::EnableWindow(hWndTop, false);
//                  }
//                  else
//                     *pWndTop = nullptr;*/
//      }
//
//      return hWnd;    // return the owner as oswindow
//   }
//
//   void interaction_impl::on_delete(::matter * pinteraction)
//   {
//      __UNREFERENCED_PARAMETER(pinteraction);
//   }
//
//
//
//
////   void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
////   {
////      ::pointer<::message::erase_bkgnd>perasebkgnd(pmessage);
////      perasebkgnd->m_bRet = true;
////      perasebkgnd->set_result(true);
////   }
//
//
//   void interaction_impl::_001BaseWndInterfaceMap()
//   {
//
//      ::windowing::window::_001BaseWndInterfaceMap();
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


   void interaction_impl::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_origin(::int_point());

   }


   void interaction_impl::window_show_change_visibility(::e_display edisplay, const ::user::activation & useractivation)
   {

      __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_show_window);

      //auto edisplay = m_puserinteraction->layout().design().display();

      //auto useractivation = m_puserinteraction->layout().design().activation();

      //if(useractivation &)
//      {
//
//         wm_add_erase_state(m_oswindow, net_wm_state_hidden, false);
//
//      }
//
      if (edisplay == e_display_full_screen)
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

         ::windowing::window::window_show_change_visibility(edisplay, useractivation);

      }

   }


//   ::user::interaction * interaction_impl::GetNextWindow(unsigned int nFlag)
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
//         throw ::interface_only();
//
//      }
//
//   }
//
//
//   ::user::interaction * interaction_impl::get_next(bool bIgnoreChildren,int * piLevel)
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

      if(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian)
      {

         _001UpdateScreen();

      }
      else
      {

         //x11_sync([&]()
         //{

         synchronous_lock synchronouslock(x11_mutex());

            _001UpdateScreen();

         //});

      }

      return true;

   }


   void interaction_impl::non_top_most_upper_window_rects(::int_rectangle_array& recta)
   {

      upper_window_rects(get_safe_handle(), recta);

   }


} // namespace linux



