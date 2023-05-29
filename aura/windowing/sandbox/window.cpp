// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// Adapted by Camilo for android 2022-01-05 04:37 <3TBS (Thomas likes number 5), Mummi and bilbo!!
#include "framework.h"
#include "_sandbox.h"
#include "acme/constant/message.h"
#include "apex/platform/system.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/interaction_prodevian.h"
#include "aura/platform/application.h"
#include "aura/platform/message_queue.h"


namespace sandbox_windowing
{


   window::window()
   {

      m_psandboxwindowingwindow = this;

   }


   window::~window()
   {


   }


   void window::create_window(::user::interaction_impl* pimpl)
   {

      bool bOk = true;

      auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;

      pimpl->m_puserinteraction->m_bMessageWindow = false;

      auto pwindowing = windowing();

      auto pwindowingdisplay = pwindowing->display();

      int x = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().x();

      int y = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().origin().y();

      int cx = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().width();

      int cy = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().height();

      bool bVisible = m_puserinteractionimpl->m_puserinteraction->const_layout().sketch().is_screen_visible();

      if (cx <= 0)
      {

         cx = 1;

      }

      if (cy <= 0)
      {

         cy = 1;

      }

      m_puserinteractionimpl = pimpl;

      pimpl->m_pwindow = this;

      set_oswindow(this);

      pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;

      pimpl->m_puserinteraction->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "native_create_window"));

      auto papp = get_app();

      if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
      {

         auto psystem = acmesystem()->m_papexsystem;

         string strApplicationServerName = psystem->get_application_server_name();

         //set_wm_class(strApplicationServerName);

         //         XClassHint * pupdate = XAllocClassHint();
         //
         //         auto psystem = acmesystem()->m_papexsystem;
         //
         //         string strApplicationServerName = psystem->get_application_server_name();
         //
         //         pupdate->res_class = (char *) (const char *) strApplicationServerName;
         //
         //         pupdate->res_name = (char *) (const char *) strApplicationServerName;
         //
         //         XSetClassHint(display, window, pupdate);
         //
         //         XFree(pupdate);

      }



      //#ifndef RASPBERRYPIOS
      //
      //      if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
      //      {
      //
      //         papp->os_on_start_application();
      //
      //         on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);
      //
      //         papp->m_bSnLauncheeSetup = true;
      //
      //      }
      //
      //#endif

            //if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_dock_window)
            //{

            //   wm_dockwindow(true);

            //}
            //else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_desktop_window)
            //{

            //   wm_desktopwindow(true);

            //}
            //else if (pimpl->m_puserinteraction->layout().sketch().activation() & e_activation_on_center_of_screen)
            //{

            //   wm_centerwindow(true);

            //}
            //else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window
            //   || pimpl->m_puserinteraction->m_bToolWindow)
            //{

            //   wm_toolwindow(true);

            //}
            //else
            //{

            //   wm_normalwindow();

            //}

            ////m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);

            //::Window root = 0;

            //::Window * pchildren = nullptr;

            //u32 ncount = 0;

            //XQueryTree(display, window, &root, &m_parent, &pchildren, &ncount);

            //if (pchildren != nullptr)
            //{

            //   XFree(pchildren);

            //}

            //htask_t htask = ::get_current_htask();

            //m_htask = htask;

            //if (!XGetWindowAttributes(Display(), Window(), &m_px11data->m_attr))
            //{

            //   INFORMATION("freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.");

            //}

            //int event_base, error_base, major_version, minor_version;

            //pimpl->m_bComposite = XGetSelectionOwner(Display(), x11_display()->intern_atom("_NET_WM_CM_S0", True));

            //string strName;

            ////      if (pusersystem && pusersystem->m_createstruct.lpszName != nullptr && strlen(pusersystem->m_createstruct.lpszName) > 0)
            ////      {
            ////
            ////         strName = pusersystem->m_createstruct.lpszName;
            ////
            ////      }

            ////if(strName.is_empty())
            ////{

      string strWindowText = pimpl->m_puserinteraction->get_window_text();

      //if (strWindowText.has_char())
      //{

      //   strName = strWindowText;

      //}

      //}

      //if (strName.has_char())
      //{

      //   XStoreName(Display(), Window(), strName);

      //}

      //bamf_set_icon();

      //_wm_nodecorations(0);

      //if (pusersystem->m_createstruct.style & WS_VISIBLE)
      //if (bVisible)
      //{

      //   map_window();

      //}
      //else
      //{

      //   pimpl->m_puserinteraction->layout().window().display() = e_display_none;

      //}

      ////if(m_px11data->m_attr.map_state != IsUnmapped)
      //{

      //   if (!attr.override_redirect)
      //   {

      //      if (is_docking_appearance(pimpl->m_puserinteraction->layout().sketch().display()))
      //      {

      //         // window managers generally "don't like" windows that starts "docked/snapped".
      //         // initial (XCreateWindow) size_i32 and position maybe not be honored.
      //         // so requesting the same change again in a effort to set the "docked/snapped" size_i32 and position.

      //         //set_window_position(e_zorder_top, pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y(),
      //         //                  pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(), SWP_SHOWWINDOW);

      //         set_window_position(e_zorder_top, x, y, cx, cy, SWP_SHOWWINDOW);

      //      }

      //   }

      //}

      //displaylock.unlock();

      //if(pshowwindow->m_bShow)
      {

         //::rectangle_i32 rect32;

         //(::window_rectangle((oswindow) get_handle(), rect32))
         {


            if (get_session() != nullptr)
            {

               // Initial position of window below the cursor position
               // with invalid (empty) size.
               // (Hinting for monitor placement, if no stored information
               // available).

               if (pimpl->m_puserinteraction->const_layout().sketch().display() == e_display_undefined)
               {

                  auto pointCursor = get_cursor_position();

                  pimpl->m_puserinteraction->set_position(pointCursor);

                  pimpl->m_puserinteraction->set_size({0, 0});

               }

            }

         }

         //   }

         //});
         //}

      }

      if (bOk)
      {

         //auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);

         auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, 0);

         if (lresult == -1)
         {

            throw ::exception(error_failed);

         }

         pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         pimpl->m_puserinteraction->set_flag(e_flag_task_started);

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   void windowing::initialize_windowing()
   {

   }

   void windowing::terminate_windowing()
   {

   }



   //void window::set_wm_class(const ::scoped_string & scopedstr)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   m_strWMClass = psz;

   //   display_lock displaylock(x11_display()->Display());

   //   XClassHint classHint;

   //   classHint.res_name = m_strWMClass;

   //   classHint.res_class = m_strWMClass;

   //   XSetClassHint(Display(), Window(), &classHint);

   //}


   //i32 window::map_window()
   //{

   //   int i = 0;

   //   synchronous_lock synchronouslock(user_synchronization());

   //   {

   //      windowing_output_debug_string("\nwindow::map_window");

   //      display_lock displaylock(x11_display()->Display());

   //      i = XMapWindow(Display(), Window());

   //   }

   //   //#ifdef WITH_SN

   //   auto pwindowing = x11_windowing();

   //   //  if (pwindowing->m_pSnLauncheeContext != nullptr)
   //   if (!pwindowing->m_bFirstWindowMap)
   //   {

   //      pwindowing->m_bFirstWindowMap = true;

   //      auto psystem = acmesystem()->m_papexsystem;

   //      auto pnode = psystem->node();

   //      pnode->defer_notify_startup_complete();

   //      on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);

   //      pwindowing->m_pSnLauncheeContext = nullptr;

   //   }

   //   //#endif // RASPBERRYPIOS

   //   windowing_output_debug_string("\nwindow::map_window END");

   //   return i;

   //}


   //i32 window::unmap_window(bool bWithdraw)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   windowing_output_debug_string("\nwindow::unmap_window");

   //   display_lock displaylock(x11_display()->Display());

   //   int i;

   //   if (bWithdraw)
   //   {

   //      i = XWithdrawWindow(Display(), Window(), x11_display()->m_iScreen);

   //   }
   //   else
   //   {

   //      i = XUnmapWindow(Display(), Window());

   //   }

   //   windowing_output_debug_string("\nwindow::unmap_window END");

   //   return i;

   //}


   //   oswindow_dataptra *window::s_pdataptra = nullptr;
   //
   //
   //   ::pointer< ::mutex >window::s_pmutex = nullptr;


   //   i32 oswindow_find_message_only_window(::user::interaction_impl *pimpl)
   //   {
   //
   //      if (pimpl == nullptr)
   //      {
   //
   //         return -1;
   //
   //      }
   //
   //      single_lock slOsWindow(window::s_pmutex, true);
   //
   //      for (i32 i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //
   //         if (::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_puserinteractionimpl == pimpl)
   //         {
   //
   //            return i;
   //
   //         }
   //
   //      }
   //
   //      return -1;
   //
   //   }

   //   i32 oswindow_find(Display *Display(), Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      for (i32 i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_osdisplay->display() == Display()
   //             && ::window::s_pdataptra->element_at(i)->m_window == window)
   //         {
   //            return i;
   //         }
   //      }
   //
   //      return -1;
   //
   //   }

   //   i32 oswindow_find(Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      for (i32 i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_window == window)
   //         {
   //            return i;
   //         }
   //      }
   //
   //      return -1;
   //
   //   }

   //
   //   window *oswindow_get_message_only_window(::user::interaction_impl *pinteraction)
   //   {
   //
   //      if (pinteraction == nullptr)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find_message_only_window(pinteraction);
   //
   //      if (::is_set(pFind))
   //      {
   //
   //         return ::window::s_pdataptra->element_at(iFind);
   //
   //      }
   //
   //      ::window *pdata = memory_new window;
   //
   //      pdata->m_bMessageOnlyWindow = true;
   //      pdata->m_window = None;
   //      pdata->m_puserinteractionimpl = pinteraction;
   //      pdata->m_osdisplay = nullptr;
   //      pdata->m_parent = 0;
   //      pdata->m_pmq = pinteraction->m_puserinteraction->m_pthreadUserInteraction->get_mq();
   //
   //      ::window::s_pdataptra->add(pdata);
   //
   //      return pdata;
   //
   //   }

   //
   //   window *oswindow_defer_get(Display *Display(), Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find(Display(), window);
   //
   //      if (::is_null(pFind))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return ::window::s_pdataptra->element_at(iFind);
   //
   //   }


   //::e_status
   //   window::initialize_x11_window(::windowing_android::display * pdisplay, ::Window window, ::Visual * pvisual, int iDepth,
   //      int iScreen, Colormap colormap)
   //{

   //   //single_lock slOsWindow(::window::s_pmutex, true);

   //   //      auto pFind = oswindow_find(Display(), window);
   //   //
   //   //      if (::is_set(pFind))
   //   //      {
   //   //
   //   //         return ::window::s_pdataptra->element_at(iFind);
   //   //
   //   //      }
   //   //
   //   //      ::window *pdata = memory_new ::window;

   //   m_bMessageOnlyWindow = false;
   //   //m_osdisplay = osdisplay_get(Display());
   //   m_pdisplay = pdisplay;
   //   m_window = window;

   //   if (pvisual != nullptr)
   //   {

   //      m_visual = *pvisual;

   //   }

   //   m_iDepth = iDepth;
   //   //m_iScreen = iScreen;
   //   //m_colormap = colormap;
   //   //m_parent = 0;

   //   //::window::s_pdataptra->add(pdata);

   //   x11_display()->m_windowmap[m_window] = this;

   //   return ::success;

   //}


   //void x11_on_start_session()
   //{

   //   Display * dpy = x11_get_display();
   //
   //   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));
   //
   //   g_oswindowDesktop->m_puserinteractionimpl = nullptr;
   //
   //   XSelectInput(g_oswindowDesktop->Display(), g_oswindowDesktop->Window(), StructureNotifyMask);
   //
   //}

   //Display * window::Display()
   //{

   //   return x11_display()->Display();

   //}

   //Display * window::Display() const
   //{

   //   return x11_display()->Display();

   //}


   //int window::Screen()
   //{

   //   return x11_display()->Screen();

   //}


   //int window::Screen() const
   //{

   //   return x11_display()->Screen();

   //}


   //Window window::Window()
   //{

   //   return m_window;

   //}


   //Window window::Window() const
   //{

   //   return m_window;

   //}


   //Visual * window::Visual()
   //{

   //   return &m_visual;

   //}


   //const Visual * window::Visual() const
   //{

   //   return &m_visual;

   //}

   //   window *oswindow_get(Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find(window);
   //
   //      if (::is_null(pFind))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return ::window::s_pdataptra->element_at(iFind);
   //
   //   }


   //bool window::bamf_set_icon()
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   auto psystem = acmesystem()->m_papexsystem;

   //   auto pnode = psystem->node();

   //   auto papp = get_app();

   //   ::file::path path = pnode->get_desktop_file_path(papp);

   //   output_debug_string("\nfreebsd::interaction_impl::set_window_text");

   //   fflush(stdout);

   //   display_lock displaylock(x11_display()->Display());

   //   Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);

   //   Atom cardinal = x11_display()->intern_atom("STRING", False);

   //   int ixa = XA_STRING;

   //   int status = XChangeProperty(
   //      Display(),
   //      Window(),
   //      net_wm_icon,
   //      ixa,
   //      8,
   //      PropModeReplace,
   //      (const unsigned char *)(const char *)path,
   //      path.get_length());

   //   output_debug_string("\nfreebsd::interaction_impl::bamf_set_icon END");

   //   fflush(stdout);

   //   if (status != 0)
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //int
   //   window::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements)
   //{

   //   return XChangeProperty(Display(), Window(), property, type, format, mode, data, nelements);

   //}


   //   Atom window::x11_display()->intern_atom(const char *pszAtomName, bool bCreate)
   //   {
   //
   //      return m_osdisplay->x11_display()->intern_atom(pszAtomName, bCreate);
   //
   //   }


   //   Atom window::x11_display()->intern_atom(e_net_wm_state estate, bool bCreate)
   //   {
   //
   //      return m_osdisplay->x11_display()->intern_atom(estate, bCreate);
   //
   //   }


//   bool window::set_icon(::image* pimage)
//   {
//
//      // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
//      // http://stackoverflow.com/users/432509/ideasman42
//
//#if 0
//
//      unsigned int buffer[] =
//      {
//      16, 16,
//      4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
//      32, 32,
//      4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
//      };
//
//      display_lock displaylock(x11_display()->Display());
//
//      int iScreen = DefaultScreen(d);
//
//      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);
//
//      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);
//
//      int length = 2 + 16 * 16 + 2 + 32 * 32;
//
//      int status = XChangeProperty(Display(), w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*)buffer, length);
//
//      if (status != 0)
//      {
//
//         return false;
//
//      }
//
//#elif 1
//
//      auto d1 = m_pcontext->m_pauracontext->create_image({ 32, 32 });
//
//      if (!::is_ok(d1))
//      {
//
//         return false;
//
//      }
//
//      d1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
//
//      {
//
//         image_source imagesource(pimage->g(), pimage->rectangle());
//
//         rectangle_f64 rectangle(d1->rectangle());
//
//         image_drawing_options imagedrawingoptions(rectangle);
//
//         image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//         //getfileimage.m_iImage = m_pimagelist[16]->set(getfileimage.m_iImage, imagedrawing);
//
//         d1->g()->draw(imagedrawing);
//
//      }
//
//      memory m(m_puserinteractionimpl->m_puserinteraction->get_app());
//
//      int length = 2 + d1->area();
//
//      m.set_size(length * 4);
//
//      unsigned int* pcr = (unsigned int*)m.get_data();
//
//      pcr[0] = d1->width();
//
//      pcr[1] = d1->height();
//
//      int c = d1->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + 2] = d1->colorref()[i];
//
//      }
//
//      windowing_output_debug_string("\nwindow::set_icon");
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      //Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);
//
//      //Atom cardinal = x11_display()->intern_atom("CARDINAL", False);
//
//      //int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *)pcr, length);
//
//      //if (status == BadAlloc)
//      //{
//
//
//      //}
//      //else if (status != 0)
//      //{
//
//      //   return false;
//
//      //}
//
//      windowing_output_debug_string("\nwindow::set_icon END");
//
//      fflush(stdout);
//
//#else
//
//      image d1(w->m_puserinteractionimpl->m_puserinteraction->create_new, this);
//
//      if (!d1->create(24, 24))
//      {
//
//         return false;
//
//      }
//
//      d1->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      d1->get_graphics()->StretchBlt(0, 0, d1.width(), d1.height(), point->get_graphics(), 0, 0, point.width(), point.height());
//
//      image d2(w->m_puserinteractionimpl->m_puserinteraction->create_new, this);
//
//      if (!d2->create(54, 54))
//      {
//
//         return false;
//
//      }
//
//      d2->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      d2->get_graphics()->StretchBlt(0, 0, d2.width(), d2.height(), point->get_graphics(), 0, 0, point.width(), point.height());
//
//      memory m(w->m_puserinteractionimpl->m_puserinteraction->get_context_application());
//
//      int length = 2 + d1->area() + 2 + d2->area();
//
//      m.set_size(length * 4);
//
//      unsigned int* pcr = (unsigned int*)m.get_data();
//
//      pcr[0] = d1.width();
//
//      pcr[1] = d1.height();
//
//      int c = d1->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + 2] = d1->m_pcolorref[i];
//
//      }
//
//      memsize o;
//
//      o = 2 + d1->area();
//
//      pcr[o] = d2.width();
//
//      pcr[o + 1] = d2.height();
//
//      c = d2->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + o + 2] = d2->m_pcolorref[i];
//
//      }
//
//      Display* display = w->display();
//
//      Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
//
//      Atom cardinal = XInternAtom(display, "CARDINAL", False);
//
//      int status = XChangeProperty(display, w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*)pcr, length);
//
//      if (status != 0)
//      {
//
//         //file_put_contents("/home/camilo/window.txt", as_string((int)w->Window()));
//         return false;
//
//      }
//#endif
//      return true;
//
//   }


   //i32 window::store_name(const ::scoped_string & scopedstr)
   //{

   //   windowing_output_debug_string("\nwindow::store_name");

   //   synchronous_lock synchronouslock(user_synchronization());

   //   display_lock displaylock(x11_display()->Display());

   //   int i = XStoreName(Display(), Window(), psz);

   //   windowing_output_debug_string("\nwindow::store_name END");

   //   return i;

   //}


   //i32 window::select_input(i32 iInput)
   //{

   //   windowing_output_debug_string("\nwindow::select_input");

   //   synchronous_lock synchronouslock(user_synchronization());

   //   display_lock displaylock(x11_display()->Display());

   //   int i = XSelectInput(Display(), Window(), iInput);

   //   windowing_output_debug_string("\nwindow::select_input END");

   //   return i;

   //}


   //i32 window::select_all_input()
   //{

   //   windowing_output_debug_string("\nwindow::select_all_input");

   //   synchronous_lock synchronouslock(user_synchronization());

   //   display_lock displaylock(x11_display()->Display());

   //   int i = select_input(ExposureMask | ButtonPressMask);

   //   windowing_output_debug_string("\nwindow::select_all_input");

   //   return i;

   //}


   void window::post_nc_destroy()
   {

      if (!::is_null(this))
      {

         m_pwindowing->erase_window(this);

      }

   }


   void window::set_user_interaction(::user::interaction_impl* pimpl)
   {

      //      single_lock sl(ms_pmutex, true);
      //
      //      if (::is_null(this))
      //      {
      //
      //         throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));
      //
      //      }

      m_puserinteractionimpl = pimpl;

      m_htask = pimpl->get_app()->get_os_handle();

      m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

      //oswindow_assign(this, pimpl);

   }


   bool window::is_child(::oswindow oswindow)
   {

      if (oswindow == nullptr || oswindow->m_puserinteractionimpl == nullptr || oswindow->m_puserinteractionimpl->m_puserinteraction == nullptr)
      {

         return false;

      }

      if (m_puserinteractionimpl == nullptr || m_puserinteractionimpl->m_puserinteraction == nullptr)
      {

         return false;

      }

      return m_puserinteractionimpl->m_puserinteraction->is_child(oswindow->m_puserinteractionimpl->m_puserinteraction);

   }


   ::windowing::window* window::get_parent() const
   {

      return nullptr;

   }


   //virtual ::Window get_parent_handle();
   oswindow window::get_parent_oswindow() const
   {

      return nullptr;

   }


   ::point_i32 window::get_mouse_cursor_position()
   {

      return m_pointCursor;

   }


   //   ::Window window::get_parent_handle()
   //   {
   //
   //      //single_lock slOsWindow(s_pmutex, true);
   //
   //      //if (::is_null(this))
   //        // return 0;
   //
   //      return m_parent;
   //
   //   }


   //   oswindow window::get_parent()
   //   {
   //
   //      if (::is_null(this))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return nullptr;
   //
   //   }


   void window::set_parent(::windowing::window* pwindowNewParent)
   {

      if (::is_null(this))
      {

         throw ::exception(error_failed);

      }

      if (::is_null(pwindowNewParent))
      {

         throw ::exception(error_failed);

      }

      auto pwindowx11NewParent = dynamic_cast <::sandbox_windowing::window*> (pwindowNewParent);

      if (::is_null(pwindowx11NewParent))
      {

         throw ::exception(error_null_pointer);

      }

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //XReparentWindow(Display(), Window(), pwindowx11NewParent->Window(), 0, 0);

      //return ::success;

   }


   ///// Post an event from the client to the X server
   //void window::send_client_event(Atom atom, unsigned int numArgs, ...)
   //{

   //   XEvent xevent;

   //   unsigned int i;

   //   va_list argp;

   //   va_start(argp, numArgs);

   //   zero(xevent);

   //   xevent.xclient.type = ClientMessage;
   //   xevent.xclient.serial = 0;
   //   xevent.xclient.send_event = False;
   //   xevent.xclient.display = Display();
   //   xevent.xclient.window = Window();
   //   xevent.xclient.message_type = atom;
   //   xevent.xclient.format = 32;

   //   for (i = 0; i < numArgs; i++)
   //   {

   //      xevent.xclient.data.l[i] = va_arg(argp, int);

   //   }

   //   XSendEvent(Display(), RootWindow(Display(), x11_display()->m_iScreen), False,
   //      SubstructureRedirectMask | SubstructureNotifyMask, &xevent);

   //   va_end(argp);

   //}


//   Atom get_window_long_atom(i32 nIndex);
//
//   // Change _NET_WM_STATE if Window is Mapped
//   void window::mapped_net_state_raw(bool add, int iScreen, Atom state1, Atom state2)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      XClientMessageEvent xclient;
//
//#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
//#define _NET_WM_STATE_ADD           1    /* add/set property */
//#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */
//
//      zero(xclient);
//      xclient.type = ClientMessage;
//      xclient.window = Window();
//      xclient.message_type = x11_display()->intern_atom("_NET_WM_STATE", False);
//      xclient.format = 32;
//      xclient.data.l[0] = add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
//      xclient.data.l[1] = state1;
//      xclient.data.l[2] = state2;
//      xclient.data.l[3] = 1; /* source indication */
//      xclient.data.l[4] = 0;
//
//      XSendEvent(Display(), RootWindow(Display(), iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask,
//         (XEvent *)&xclient);
//
//   }
//
//
//   void window::unmapped_net_state_raw(Atom atom1, ...)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      XEvent xevent;
//
//      unsigned int i;
//
//      va_list argp;
//
//      va_start(argp, atom1);
//
//      zero(xevent);
//
//      array<Atom> atoms;
//
//      atoms.add(atom1);
//
//      while (true)
//      {
//
//         Atom atom = va_arg(argp, int);
//
//         if (atom == 0)
//         {
//
//            break;
//
//         }
//
//         atoms.add(atom);
//
//      }
//
//      if (atoms.has_elements())
//      {
//
//         XChangeProperty(Display(), Window(), x11_display()->intern_atom("_NET_WM_STATE", False),
//            XA_ATOM, 32, PropModeReplace,
//            (const unsigned char *)atoms.get_data(), atoms.get_size());
//      }
//      else
//      {
//
//         XDeleteProperty(Display(), Window(), x11_display()->intern_atom("_NET_WM_STATE", False));
//
//      }
//
//      va_end(argp);
//
//   }
//
//
   void window::show_window(const ::e_display& edisplay, const ::e_activation& eactivation)
   {

   }

   //
   //      x11_windowing()->windowing_post([this, edisplay, eactivation]()
   //         {
   //
   //            windowing_output_debug_string("\n::window::show_window 1");
   //
   //            synchronous_lock synchronouslock(user_synchronization());
   //
   //            display_lock displaylock(x11_display()->Display());
   //
   //            XWindowAttributes attr;
   //
   //            if (!XGetWindowAttributes(Display(), Window(), &attr))
   //            {
   //
   //               windowing_output_debug_string("\n::window::show_window 1.2");
   //
   //               return false;
   //
   //            }
   //
   //            if (edisplay == e_display_zoomed)
   //            {
   //
   //               if (attr.map_state == IsUnmapped)
   //               {
   //
   //                  XMapWindow(Display(), Window());
   //
   //               }
   //
   //               mapped_net_state_raw(true, x11_display()->m_iScreen,
   //                  x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
   //                  x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_vert, false));
   //
   //            }
   //            else if (edisplay == e_display_iconic)
   //            {
   //
   //               wm_iconify_window();
   //
   //            }
   //            else if (::is_visible(edisplay))
   //            {
   //
   //               if (attr.map_state == IsUnmapped)
   //               {
   //
   //                  XMapWindow(Display(), Window());
   //
   //               }
   //
   //            }
   //            else
   //            {
   //
   //               if (attr.map_state != IsUnmapped)
   //               {
   //
   //                  XWithdrawWindow(Display(), Window(), Screen());
   //
   //               }
   //
   //            }
   //
   //            windowing_output_debug_string("\n::window::show_window 2");
   //
   //            return true;
   //
   //         });
   //
   //      //return ::success;
   //
   //   }
   //
   //
   void window::full_screen(const ::rectangle_i32& rectangle)
   {


   }

   //
   //      ::rectangle_i32 rBest;
   //
   //      int iMonitor = m_pdisplay->get_best_monitor(&rBest, rectangle);
   //
   //      windowing_output_debug_string("\n::window::full_screen 1");
   //
   //      synchronous_lock synchronouslock(user_synchronization());
   //
   //      display_lock displaylock(x11_display()->Display());
   //
   //      //      if (x11_display()->is_null())
   //      //      {
   //      //
   //      //         windowing_output_debug_string("\n::window::full_screen 1.1");
   //      //
   //      //         return;
   //      //
   //      //      }
   //
   //      XWindowAttributes attr;
   //
   //      if (!XGetWindowAttributes(Display(), Window(), &attr))
   //      {
   //
   //         windowing_output_debug_string("\n::window::full_screen 1.2");
   //
   //         fflush(stdout);
   //
   //         throw ::exception(error_failed);
   //
   //      }
   //
   //      ::rectangle_i32 rWindow;
   //
   //      rWindow.left = attr.x();
   //      rWindow.top = attr.y();
   //      rWindow.right = attr.x() + attr.width;
   //      rWindow.bottom = attr.y() + attr.height;
   //
   //      if (rBest != rWindow)
   //      {
   //
   //         m_puserinteractionimpl->m_puserinteraction->place(rBest);
   //
   //         XMoveResizeWindow(Display(), Window(), rBest.left, rBest.top, rBest.width(), rBest.height());
   //
   //      }
   //
   //      if (attr.map_state == IsViewable)
   //      {
   //
   //         mapped_net_state_raw(true, Screen(), x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);
   //
   //      }
   //      else
   //      {
   //
   //         unmapped_net_state_raw(x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);
   //
   //         XMapWindow(Display(), Window());
   //
   //      }
   //
   //      windowing_output_debug_string("\n::window::full_screen 2");
   //
   //      ::fflush(stdout);
   //
   //      //return ::success;
   //
   //   }


   void window::exit_iconify()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(Display(), Window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::exit_full_screen 1.2");

      //   fflush(stdout);

      //   throw ::exception(error_failed);

      //}

      //if (attr.map_state == IsViewable)
      //{

      //   mapped_net_state_raw(false, Screen(), x11_display()->intern_atom(::x11::e_atom_net_wm_state_hidden, false), 0);

      //}

      ////return ::success;

   }


   void window::exit_full_screen()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(Display(), Window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::exit_full_screen 1.2");

      //   fflush(stdout);

      //   throw ::exception(error_failed);

      //}

      //if (attr.map_state == IsViewable)
      //{

      //   mapped_net_state_raw(false, Screen(), x11_display()->intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

      //}

      ////return ::success;

   }


   void window::exit_zoomed()
   {

      //synchronous_lock sl(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(Display(), Window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::exit_zoomed 1.2");

      //   fflush(stdout);

      //   throw ::exception(error_failed);

      //}

      //if (attr.map_state == IsViewable)
      //{

      //   mapped_net_state_raw(false, Screen(),
      //      x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
      //      x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_vert, false));

      //}

      ////return success;

   }


   //   iptr window::get_window_long_ptr(i32 nIndex)
   //   {
   //
   //      return m_puserinteractionimpl->get_window_long_ptr(nIndex);
   //
   //   }


   //   iptr window::set_window_long_ptr(i32 nIndex, iptr i)
   //   {
   //
   //      return m_puserinteractionimpl->set_window_long_ptr(nIndex, i);
   //
   //      //iptr iOld = m_plongmap->operator[](nIndex);
   //
   //      //   if(nIndex == GWL_EXSTYLE)
   //      //   {
   //      //
   //      //      if(is_different((l & WS_EX_TOOLWINDOW), (m_plongmap->operator[](nIndex) & WS_EX_TOOLWINDOW)))
   //      //      {
   //      //
   //      //         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);
   //      //
   //      //      }
   //      //
   //      //   }
   //
   //      //m_plongmap->operator[](nIndex) = i;
   //
   //      //return iOld;
   //
   //   }


   bool window::client_to_screen(::point_i32* ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::point_i32* ppoint)
   {

      return true;

   }


   //long window::get_state()
   //{

   //   windowing_output_debug_string("\n::window::get_state 1");

   //   synchronous_lock synchronouslock(user_synchronization());

   //   display_lock displaylock(x11_display()->Display());

   //   static const long WM_STATE_ELEMENTS = 2L;

   //   unsigned long nitems = 0;

   //   unsigned long leftover = 0;

   //   Atom atomWmState = 0;

   //   Atom actual_type = 0;

   //   i32 actual_format = 0;

   //   i32 status = 0;

   //   unsigned char * point = nullptr;

   //   if (x11_display()->m_atomWmState == None)
   //   {

   //      x11_display()->m_atomWmState = x11_display()->intern_atom("WM_STATE", false);

   //   }

   //   atomWmState = x11_display()->m_atomWmState;

   //   status = XGetWindowProperty(Display(), Window(), atomWmState, 0L, WM_STATE_ELEMENTS, False, AnyPropertyType,
   //      &actual_type,
   //      &actual_format, &nitems, &leftover, &point);

   //   if (status == 0)
   //   {

   //      long lStatus = -1;

   //      if (point != nullptr)
   //      {

   //         lStatus = (long)*point;

   //      }

   //      XFree(point);

   //      windowing_output_debug_string("\n::window::get_state 1.1");

   //      return lStatus;

   //   }

   //   windowing_output_debug_string("\n::window::get_state 2");

   //   return -1;

   //}


   bool window::is_iconic()
   {

      //#ifdef XDISPLAY_LOCK_LOG
      //
      //      b_prevent_xdisplay_lock_log = true;
      //
      //#endif
      //
      //      bool b = get_state() == IconicState;
      //
      //#ifdef XDISPLAY_LOCK_LOG
      //
      //      b_prevent_xdisplay_lock_log = false;
      //
      //#endif
      //
      //      return b;
      return false;

   }


   bool window::is_window_visible()
   {

      //windowing_output_debug_string("\n::window::is_window_visible 1");

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //if (x11_display()->is_null())
      //{

      //   windowing_output_debug_string("\n::window::is_window_visible 1.1");

      //   return false;

      //}

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(Display(), Window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::is_window_visible 1.2");

      //   return false;

      //}

      //windowing_output_debug_string("\n::window::is_window_visible 2");

      //return attr.map_state == IsViewable;

      return false;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      if (m_puserinteractionimpl == nullptr)
      {

         return true;

      }

      if (!m_puserinteractionimpl->m_puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


#undef SET_WINDOW_POS_LOG


   //   bool window::set_window_pos(class ::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   //   {
   //
   //      bool bOk = false;
   //
   //
   //                  bOk = _set_window_pos(zorder, x, y, cx, cy, nFlags);
   //
   //               });
   //
   //      return bOk;
   //
   //   }


   ::e_status window::set_window_icon(const ::file::path& path)
   {


      //Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);

      //Atom cardinal = x11_display()->intern_atom("STRING", False);

      //int ixa = XA_STRING;

      //int status = XChangeProperty(
      //   Display(),
      //   Window(),
      //   net_wm_icon,
      //   ixa,
      //   8,
      //   PropModeReplace,
      //   (const unsigned char *)(const char *)path,
      //   path.get_length());

      //output_debug_string("\nfreebsd::interaction_impl::bamf_set_icon END");

      //fflush(stdout);

      //if (status != 0)
      //{

      //   return false;

      //}

      return ::success;

   }


   //   void oswindow_data::wm_full_screen(const ::rectangle_i32 & rectangle)
   //   {
   //
   //      ::rectangle_i32 rBest;
   //
   //      int iMonitor = best_xinerama_monitor(m_puserinteractionimpl->m_puserinteraction, rectangle, rBest);
   //
   //      windowing_output_debug_string("\n::oswindow_data::full_screen 1");
   //
   //      xdisplay d(display());
   //
   //      if(d.is_null())
   //      {
   //
   //         windowing_output_debug_string("\n::oswindow_data::full_screen 1.1");
   //
   //         return;
   //
   //      }
   //
   //      XWindowAttributes attr;
   //
   //      if(!XGetWindowAttributes(display(), window(), &attr))
   //      {
   //
   //         windowing_output_debug_string("\n::oswindow_data::full_screen 1.2");
   //
   //         fflush(stdout);
   //
   //         return;
   //
   //      }
   //
   //      ::rectangle_i32 rWindow;
   //
   //      rWindow.left      = attr.x();
   //      rWindow.top       = attr.y();
   //      rWindow.right     = attr.x()    + attr.width;
   //      rWindow.bottom    = attr.y()    + attr.height;
   //
   //      if(rBest != rWindow)
   //      {
   //
   //         m_puserinteractionimpl->m_puserinteraction->place(rBest);
   //
   //         XMoveResizeWindow(d, m_window, rBest.left, rBest.top, rBest.width(), rBest.height());
   //
   //      }
   //
   //      if(attr.map_state == IsViewable)
   //      {
   //
   //         mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom(net_wm_state_fullscreen, false), 0);
   //
   //      }
   //      else
   //      {
   //
   //         unmapped_net_state_raw(d, window(), intern_atom(net_wm_state_fullscreen, false), 0);
   //
   //         XMapWindow(display(), window());
   //
   //      }
   //
   //      windowing_output_debug_string("\n::oswindow_data::full_screen 2");
   //
   //      ::fflush(stdout);
   //
   //   }
   //


   //::e_status window::x11_post_message(MESSAGE & msg)
   //{

   //   try
   //   {

   //      if (msg.oswindow == nullptr)
   //      {

   //         auto pcontext = m_pcontext->m_papexcontext;

   //         pcontext->post_message(msg.m_atom, msg.wParam, msg.lParam);

   //      }
   //      else
   //      {

   //         if (msg.oswindow != nullptr && msg.oswindow->m_puserinteractionimpl != nullptr &&
   //            msg.oswindow->m_puserinteractionimpl->m_puserinteraction != nullptr)
   //         {

   //            ::user::interaction * pinteraction = msg.oswindow->m_puserinteractionimpl->m_puserinteraction;

   //            pinteraction->post_message(msg.m_atom, msg.wParam, msg.lParam);

   //         }

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return ::success;

   //}


   //::e_status window::post_ui_message(const MESSAGE & message)
   //{

   //   oswindow oswindow = message.oswindow;

   //   ASSERT(oswindow != nullptr);

   //   ::user::interaction * pinteraction = oswindow->m_puserinteractionimpl->m_puserinteraction;

   //   ::thread * pthread = nullptr;

   //   if (::is_set(pinteraction))
   //   {

   //      pthread = pinteraction->m_pthreadUserInteraction;

   //   }

   //   if (::is_null(pthread))
   //   {

   //      return false;

   //   }

   //   auto pmessagequeue = pthread->m_pmessagequeue.get();

   //   if (pmessagequeue == nullptr)
   //   {

   //      if (message.m_atom == e_message_quit)
   //      {

   //         return false;

   //      }

   //      pmessagequeue = pthread->get_message_queue();

   //   }

   //   if (pmessagequeue == nullptr)
   //   {

   //      return false;

   //   }

   //   synchronous_lock ml(pmessagequeue->synchronization());

   //   if (message.m_atom == e_message_quit)
   //   {

   //      output_debug_string("e_message_quit thread");

   //   }

   //   if (message.m_atom == e_message_left_button_down)
   //   {

   //      output_debug_string("post_ui_message::e_message_left_button_down\n");

   //   }
   //   else if (message.m_atom == e_message_left_button_up)
   //   {

   //      output_debug_string("post_ui_message::e_message_left_button_up\n");

   //   }

   //   pmessagequeue->m_messagea.add(message);

   //   pmessagequeue->m_eventNewMessage.set_event();

   //   return true;

   //}


   //::e_status window::mq_remove_window_from_all_queues()
   //{

   //   ::user::interaction * pinteraction = m_puserinteractionimpl->m_puserinteraction;

   //   if (pinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   if (pinteraction->get_app() == nullptr)
   //   {

   //      return false;

   //   }

   //   itask_t idthread = pinteraction->get_app()->get_itask();

   //   message_queue * pmq = get_message_queue(idthread, false);

   //   if (pmq == nullptr)
   //   {

   //      return false;

   //   }

   //   synchronous_lock ml(pmq->synchronization());

   //   pmq->m_messagea.predicate_erase([this](MESSAGE & item)
   //      {

   //         return item.oswindow == this;

   //      });

   //   return true;

   //}


   bool window::set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   {

      //synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("\n::window::set_window_pos 1");

      //      display_lock displaylock(x11_display()->Display());
      //
      //      XWindowAttributes attrs = {};
      //
      //      if (!XGetWindowAttributes(Display(), Window(), &attrs))
      //      {
      //
      //         windowing_output_debug_string("\n::window::set_window_pos 1.1 xgetwindowattr failed");
      //
      //         return false;
      //
      //      }
      //
      //      if (nFlags & SWP_SHOWWINDOW)
      //      {
      //
      //         if (attrs.map_state == IsUnmapped)
      //         {
      //
      //            windowing_output_debug_string("\n::window::set_window_pos Mapping Window 1.2");
      //
      //            XMapWindow(Display(), Window());
      //
      //         }
      //
      //         if (!XGetWindowAttributes(Display(), Window(), &attrs))
      //         {
      //
      //            windowing_output_debug_string("\n::window::set_window_pos 1.3 xgetwindowattr failed");
      //
      //            return false;
      //
      //         }
      //
      //      }
      //
      //      bool bMove = !(nFlags & SWP_NOMOVE);
      //
      //      bool bSize = !(nFlags & SWP_NOSIZE);
      //
      //      if (bMove)
      //      {
      //
      //         if (bSize)
      //         {
      //
      //            windowing_output_debug_string("\n::window::set_window_pos Move Resize Window 1.4");
      //
      //#ifdef SET_WINDOW_POS_LOG
      //
      //            FORMATTED_INFORMATION("XMoveResizeWindow (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);
      //
      //#endif
      //
      //            if (cx <= 0 || cy <= 0)
      //            {
      //
      //               cx = 1;
      //
      //               cy = 1;
      //
      //#ifdef SET_WINDOW_POS_LOG
      //
      //               FORMATTED_INFORMATION("Changing parameters... (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);
      //
      //#endif
      //
      //            }
      //
      //            XMoveResizeWindow(Display(), Window(), x, y, cx, cy);
      //
      //         }
      //         else
      //         {
      //
      //            windowing_output_debug_string("\n::window::set_window_pos Move Window 1.4.1");
      //
      //            XMoveWindow(Display(), Window(), x, y);
      //
      //         }
      //
      //      }
      //      else if (bSize)
      //      {
      //
      //         windowing_output_debug_string("\n::window::set_window_pos Resize Window 1.4.2");
      //
      //         XResizeWindow(Display(), Window(), cx, cy);
      //
      //      }
      //
      //      //   if(bMove || bSize)
      //      //   {
      //      //
      //      //      if(attrs.override_redirect)
      //      //      {
      //      //
      //      //         if(!(m_puserinteractionimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
      //      //         {
      //      //
      //      //            XSetWindowAttributes set;
      //      //
      //      //            set.override_redirect = False;
      //      //
      //      //            if(!XChangeWindowAttributes(Display(), Window(), CWOverrideRedirect, &set))
      //      //            {
      //      //
      //      //               INFORMATION("freebsd::interaction_impl::_native_create_window_ex failed to clear override_redirect");
      //      //
      //      //            }
      //      //
      //      //         }
      //      //
      //      //      }
      //      //
      //      //   }
      //
      //
      //      if ((nFlags & SWP_HIDEWINDOW) != 0U)
      //      {
      //
      //         if (attrs.map_state == IsViewable)
      //         {
      //
      //            windowing_output_debug_string("\n::window::set_window_pos Withdraw Window 1.4.3");
      //
      //            XWithdrawWindow(Display(), Window(), Screen());
      //
      //         }
      //
      //      }
      //
      //      if (XGetWindowAttributes(Display(), Window(), &attrs) == 0)
      //      {
      //
      //         windowing_output_debug_string("\n::window::set_window_pos xgetwndattr 1.4.4");
      //
      //         return false;
      //
      //      }
      //
      //      if (attrs.map_state == IsViewable || ((nFlags & SWP_SHOWWINDOW) != 0U))
      //      {
      //
      //         if ((nFlags & SWP_NOZORDER) == 0U)
      //         {
      //
      //            if (zorder.m_ezorder == e_zorder_top_most)
      //            {
      //
      //               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
      //               {
      //
      //                  wm_state_above_raw(true);
      //
      //               }
      //
      //               XRaiseWindow(Display(), Window());
      //
      //            }
      //            else if (zorder.m_ezorder == e_zorder_top)
      //            {
      //
      //               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
      //                  || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
      //                  || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
      //                  || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
      //                  || net_wm_state(::x11::e_atom_net_wm_state_maximized_vert) != 0
      //                  || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
      //               {
      //
      //                  wm_state_clear_raw(false);
      //
      //               }
      //
      //               XRaiseWindow(Display(), Window());
      //
      //            }
      //            else if (zorder.m_ezorder == e_zorder_bottom)
      //            {
      //
      //               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
      //               {
      //
      //                  wm_state_below_raw(true);
      //
      //               }
      //
      //               XLowerWindow(Display(), Window());
      //
      //            }
      //
      //         }
      //
      //         //m_puserinteractionimpl->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);
      //
      //      }
      //      //      else
      //      //      {
      //      //
      //      //         //m_puserinteractionimpl->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
      //      //
      //      //      }
      //
      //            //m_puserinteractionimpl->on_change_visibility();
      //
      //      windowing_output_debug_string("\n::window::set_window_pos 2");

      return true;

   }


   //void window::set_need_redraw()
   //{


   //}


   //   int_bool window::show_window(
   //                        const ::e_display &edisplay,
   //                        const ::e_activation &eactivation
   //   )
   //   {
   //
   //      x11_sync([oswindow, edisplay, eactivation]()
   //               {
   //
   //                  return oswindow->
   //                     show_window(edisplay, eactivation
   //                  );
   //
   //               });
   //
   //      return true;
   //
   //   }


   //   iptr get_window_long_ptr(window *pdata, int
   //   nIndex)
   //   {
   //
   //      return pdata->
   //         get_window_long_ptr(nIndex);
   //
   //   }


   //   iptr set_window_long_ptr(window *pdata, int
   //   nIndex,
   //                            iptr i
   //   )
   //   {
   //
   //      return pdata->
   //         set_window_long_ptr(nIndex, i
   //      );
   //
   //   }


   void window::set_window_text(const ::scoped_string & scopedstrString)
   {

      //      m_strWindowText = pszString;

            //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text");

            //fflush(stdout);

            //x11_store_name(m_oswindow, m_strWindowText);

      //x11_store_name(pszString);

      //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text END");

      //fflush(stdout);

   }


   void window::set_tool_window(bool bSet)
   {

      //wm_toolwindow(bSet);

      //return ::success;

   }


   void window::set_mouse_cursor2(::windowing::cursor* pcursor)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);

      //Atom cardinal = x11_display()->intern_atom("STRING", False);

      //int ixa = XA_STRING;

      //::file::path path = pcursor->get_file_path();

      //int status = XChangeProperty(
      //   Display(),
      //   Window(),
      //   net_wm_icon,
      //   ixa,
      //   8,
      //   PropModeReplace,
      //   (const unsigned char *)(const char *)path,
      //   path.get_length());

      //output_debug_string("\nfreebsd::interaction_impl::bamf_set_icon END");

      //fflush(stdout);

      //if (status != 0)
      //{

      //   throw ::exception(error_failed);

      //}

      ////return true;

   }


   void window::set_mouse_cursor(::windowing::cursor* pcursor)
   {

      if (::is_null(pcursor))
      {

         throw ::exception(error_null_pointer);

      }

      //auto pcursorx11 = dynamic_cast <::windowing_android::cursor *>(pcursor);

      //if (::is_null(pcursorx11))
      //{

      //   throw ::exception(error_null_pointer);

      //}

      //if (!pcursorx11->m_cursor)
      //{

      //   //auto estatus =
      //   //
      //   pcursorx11->_create_os_cursor();

      //   //         if(!estatus)
      //   //         {
      //   //
      //   //            return estatus;
      //   //
      //   //         }

      //}

      //if (m_cursorLast == pcursorx11->m_cursor)
      //{

      //   //return true;

      //   return;

      //}

      //m_pwindowing->windowing_post([this, pcursorx11]()
      //   {

      //      synchronous_lock sl(user_synchronization());

      //      windowing_output_debug_string("\n::SetCursor 1");

      //      display_lock displaylock(x11_display()->Display());;

      //      XDefineCursor(Display(), Window(), pcursorx11->m_cursor);

      //      m_cursorLast = pcursorx11->m_cursor;

      //   });

      ////return true;

   }


   //string window::x11_get_name()
   //{

   //   return ::x11_get_name(Display(), Window());

   //}


   //bool window::x11_get_window_rect(::rectangle_i32 * prectangle)
   //{

   //   return ::x11_get_window_rect(Display(), Window(), prectangle);

   //}


   //::e_status window::window_rectangle(::rectangle_i32 * prectangle)
   //{

   //   return x11_get_window_rect(prectangle);

   //}


   //bool window::x11_get_client_rect(::rectangle_i32 * prectangle)
   //{

   //   return ::x11_get_client_rect(Display(), Window(), prectangle);

   //}


   //::e_status window::client_rectangle(::rectangle_i32 * prectangle)
   //{

   //   return x11_get_client_rect(prectangle);

   //}


//   void window::upper_window_rects(rectangle_i32_array & ra)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      ra.erase_all();
//
//      windowing_output_debug_string("\n::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//      b_prevent_display_lock_lock_log = false;
//
//#endif
//
//      display_lock displaylock(x11_display()->Display());
//
//      windowing_output_debug_string("\n::GetFocus 1.01");
//
//      auto windowa = x11_display()->x11_window_list();
//
//      if (windowa.last() == Window())
//      {
//
//         return;
//
//      }
//
//      auto pFind = windowa.find_last(Window());
//
//      if (::is_null(pFind))
//      {
//
//         return;
//
//      }
//
//      ::rectangle_i32 rectangle;
//
//      x11_get_window_rect(rectangle);
//
//      //r = oswindow->m_puserinteractionimpl->m_puserinteraction->window_rectangle();
//
//      //string strTopic = x11_get_name(x11_display(), Window());
//
//      ::rectangle_i32 rectangleTest;
//
//      for (iFind++; iFind < windowa.get_size(); iFind++)
//      {
//
//         //string strItem = x11_get_name(x11_display(), windowa[iFind]);
//
//         ::rectangle_i32 rectangleHigher;
//
//         if (::x11_get_window_rect(Display(), windowa[iFind], rectangleHigher))
//         {
//
//            ra.add(rectangleHigher);
//
//         }
//
//      }
//
//   }
//
//
   void window::set_active_window()
   {

   }

   //   synchronous_lock synchronouslock(user_synchronization());

   //   {

   //      windowing_output_debug_string("\n::set_active_window 1");

   //      display_lock displaylock(x11_display()->Display());

   //      XEvent xev;

   //      zero(xev);

   //      auto windowRoot = DefaultRootWindow(Display());

   //      Atom atomActiveWindow = x11_display()->intern_atom("_NET_ACTIVE_WINDOW", False);

   //      xev.xclient.type = ClientMessage;
   //      xev.xclient.send_event = True;
   //      xev.xclient.display = Display();
   //      xev.xclient.window = Window();
   //      xev.xclient.message_type = atomActiveWindow;
   //      xev.xclient.format = 32;
   //      xev.xclient.data.l[0] = 1;
   //      xev.xclient.data.l[1] = 0;
   //      xev.xclient.data.l[2] = 0;
   //      xev.xclient.data.l[3] = 0;
   //      xev.xclient.data.l[4] = 0;

   //      XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

   //      windowing_output_debug_string("\n::set_active_window 2");

   //   }

   //   //auto estatus =
   //   //
   //   set_keyboard_focus();

   //   //      if (!estatus)
   //   //      {
   //   //
   //   //         return estatus;
   //   //
   //   //      }
   //   //
   //   //      return estatus;

   //}


   //Window window::_get_window_relative(enum_relative erelative, ::Window * windowa, int numItems)
   //{

   //   if (::is_null(windowa))
   //   {

   //      windowing_output_debug_string("\n::_get_window_relative");

   //      return 0;

   //   }

   //   ::Window window = 0;

   //   switch (erelative)
   //   {

   //   case e_relative_first_sibling:
   //   {

   //      window = windowa[0];

   //   }
   //   break;

   //   case e_relative_last_sibling:
   //   {

   //      window = windowa[numItems - 1];

   //   }
   //   break;

   //   case e_relative_next_sibling:
   //   case e_relative_previous_sibling:
   //   {

   //      int iFound = -1;

   //      for (int i = 0; i < numItems; i++)
   //      {

   //         if (windowa[i] == Window())
   //         {

   //            iFound = i;

   //            break;

   //         }

   //      }

   //      if (iFound < 0)
   //      {

   //         return 0;

   //      }

   //      if (erelative == e_relative_next_sibling)
   //      {

   //         if (iFound + 1 >= numItems)
   //         {

   //            return 0;

   //         }

   //         window = windowa[iFound + 1];

   //      }
   //      else if (erelative == e_relative_previous_sibling)
   //      {

   //         if (iFound - 1 < 0)
   //         {

   //            return 0;

   //         }

   //         window = windowa[iFound - 1];

   //      }
   //      else
   //      {

   //         return 0;

   //      }

   //   }
   //   default:
   //   {

   //      return 0;

   //   }

   //   }

   //   return window;

   //}


   //::windowing::window * window::get_window(enum_relative erelative)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   ::Window window = 0;

   //   windowing_output_debug_string("\n::get_window 1");

   //   display_lock displaylock(x11_display()->Display());

   //   if (erelative == e_relative_first_sibling ||
   //      erelative == e_relative_last_sibling ||
   //      erelative == e_relative_next_sibling ||
   //      erelative == e_relative_previous_sibling)
   //   {

   //      ::oswindow oswindowParent = get_parent();

   //      if (oswindowParent == nullptr)
   //      {

   //         Atom atomNetClientListStacking = x11_display()->intern_atom("_NET_CLIENT_LIST_STACKING", False);

   //         Atom atomActualType;

   //         int format;

   //         unsigned long numItems, bytesAfter;

   //         ::Window * windowa = nullptr;

   //         int status = XGetWindowProperty(
   //            Display(),
   //            RootWindow(Display(), Screen()),
   //            atomNetClientListStacking,
   //            0L,
   //            1024,
   //            false,
   //            AnyPropertyType,
   //            &atomActualType,
   //            &format,
   //            &numItems,
   //            &bytesAfter,
   //            (unsigned char **)&windowa);

   //         if (status >= Success && numItems)
   //         {

   //            window = _get_window_relative(erelative, windowa, numItems);

   //         }

   //         if (windowa != NULL)
   //         {

   //            XFree(windowa);

   //         }

   //      }
   //      else
   //      {

   //         ::Window root = 0;
   //         ::Window parent = 0;
   //         ::Window * pchildren = nullptr;
   //         u32 numItems = 0;

   //         int status = XQueryTree(Display(), Window(),
   //            &root, &parent, &pchildren, &numItems);

   //         if (status >= Success && numItems)
   //         {

   //            window = _get_window_relative(erelative, pchildren, numItems);

   //         }

   //         if (pchildren != nullptr)
   //         {

   //            XFree(pchildren);

   //         }

   //      }

   //   }
   //   else
   //   {

   //      ::Window root = 0;
   //      ::Window parent = 0;
   //      ::Window * pchildren = nullptr;
   //      u32 numItems = 0;

   //      int status = XQueryTree(Display(), Window(),
   //         &root, &parent, &pchildren, &numItems);

   //      if (status >= Success && numItems)
   //      {

   //         if (erelative == e_relative_first_child)
   //         {

   //            window = pchildren[0];

   //         }
   //         else if (erelative == e_relative_last_child)
   //         {

   //            window = pchildren[numItems - 1];

   //         }

   //      }

   //      if (pchildren != nullptr)
   //      {

   //         XFree(pchildren);

   //      }

   //   }

   //   auto pwindowx11 = x11_display()->_window(window);

   //   if (::is_null(pwindowx11))
   //   {

   //      return nullptr;

   //   }

   //   return pwindowx11;

   //}


   void window::destroy_window()
   {

      bool bOk = false;

      if (::is_set(m_puserinteractionimpl))
      {

         ::pointer<::user::interaction>pinteraction = m_puserinteractionimpl->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_destroy, 0, 0);

            //mq_remove_window_from_all_queues();

            pinteraction->send_message(e_message_non_client_destroy, 0, 0);

         }
         else
         {

            try
            {

               //window->m_puserinteractionimpl->release();

            }
            catch (...)
            {

            }

         }

         //oswindow_remove_impl(window->m_puserinteractionimpl);

         m_pwindowing->erase_window(this);

      }

      //      x11_fork([window]()
      //               {

      //synchronous_lock synchronouslock(user_synchronization());

      //Display *Display() = Display();

      //Window win = window->window();

      //oswindow_data * pdata = (oswindow_data * )(void * )
      //window;

      bool bIs = is_window();

      m_pwindowing->erase_window(this);

      windowing_output_debug_string("\n::DestroyWindow 1");

      //display_lock displaylock(x11_display()->Display());

      //XUnmapWindow(Display(), Window());

      //XDestroyWindow(Display(), Window());

      //windowing_output_debug_string("\n::DestroyWindow 2");
      ////
      ////               });

      //      //return ::success;

   }


   bool window::is_window()
   {

      //      if (::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
      //      {
      //
      //         return false;
      //
      //      }

            //return true;

      return true;

   }


   //comparable_array < Atom > window::wm_get_list_raw(Atom atomList)
   //{

   //   comparable_array < Atom >atoma;

   //   synchronous_lock synchronouslock(user_synchronization());

   //   if (atomList == None)
   //   {

   //      return atoma;

   //   }

   //   Atom actual_type;

   //   int actual_format;

   //   unsigned long int bytes_after;

   //   Atom * patoms = nullptr;

   //   long unsigned int num_items = 0;

   //   XGetWindowProperty(Display(), Window(), atomList, 0, 1024,
   //      False, XA_ATOM, &actual_type, &actual_format,
   //      &num_items,
   //      &bytes_after, (unsigned char **)&patoms);

   //   atoma.set_size(num_items);

   //   memcpy(atoma.get_data(), patoms, atoma.get_size_in_bytes());
   //   XFree(patoms);

   //   return atoma;

   //}


   //int window::wm_test_list_raw(Atom atomList, Atom atomFlag)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   Atom actual_type;

   //   int actual_format;

   //   unsigned long i;

   //   auto atoma = wm_get_list_raw(atomList);

   //   if (atoma.is_empty())
   //   {

   //      return 0;

   //   }

   //   bool bFind = atoma.contains(atomFlag);

   //   return bFind ? 1 : 0;

   //}


   //int window::wm_test_state_raw(const ::scoped_string & scopedstrNetStateFlag)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   Atom atomFlag = x11_display()->intern_atom(pszNetStateFlag, 1);

   //   if (atomFlag == None)
   //   {

   //      windowing_output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");

   //      return 0;

   //   }

   //   Atom atomNetState = x11_display()->intern_atom("_NET_WM_STATE", 1);

   //   if (atomNetState == None)
   //   {

   //      windowing_output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

   //      return 0;

   //   }

   //   return wm_test_list_raw(atomNetState, atomFlag);

   //}


   //int window::wm_test_state(const ::scoped_string & scopedstrNetStateFlag)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   windowing_output_debug_string("\n::wm_test_state 1");

   //   display_lock displaylock(x11_display()->Display());

   //   if (x11_display()->is_null())
   //   {

   //      windowing_output_debug_string("\n::wm_test_state 1.1");

   //      return 0;

   //   }

   //   int i = wm_test_state_raw(pszNetStateFlag);

   //   windowing_output_debug_string("\n::wm_test_state 2");

   //   return i;

   //}


   //bool window::wm_add_remove_list_raw(Atom atomList, Atom atomFlag, bool bSet)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   if (atomFlag == None)
   //   {

   //      return false;

   //   }

   //   if (atomList == None)
   //   {

   //      return false;

   //   }

   //   int scr = DefaultScreen(Display());

   //   auto defaultRootWindow = RootWindow(Display(), DefaultScreen(Display()));

   //   if (bSet)
   //   {

   //      if (!wm_test_list_raw(atomList, atomFlag))
   //      {

   //         XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeAppend, (unsigned char *)&atomFlag, 1);

   //      }

   //   }
   //   else
   //   {

   //      unsigned long num_items;

   //      auto atoma = wm_get_list_raw(atomList);

   //      if (atoma.is_empty())
   //      {

   //         return false;

   //      }

   //      auto pFind = -1;

   //      int i;

   //      for (i = 0; i < num_items; i++)
   //      {

   //         if (atoma[i] == atomFlag)
   //         {

   //            iFind = i;

   //            break;

   //         }

   //      }

   //      if (::is_set(pFind))
   //      {

   //         atoma.erase_at(iFind);

   //         XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeReplace, (unsigned char *)atoma.get_data(),
   //            atoma.get_size());

   //      }

   //   }

   //   return true;

   //}


   /// should be run at user_thread
   void window::set_foreground_window()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_display()->Display());

      //XRaiseWindow(Display(), Window());

      //XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);

      ////return true;

   }


   bool window::has_mouse_capture() const
   {

      auto pwindowing = ((window*)this)->windowing();

      if (!pwindowing)
      {

         return false;

      }

      auto pwindowKeyboardFocus = pwindowing->m_pwindowKeyboardFocus;

      if (::is_null(pwindowKeyboardFocus))
      {

         return false;

      }


      bool bHasKeyboardFocus = pwindowKeyboardFocus == this;

      if (!bHasKeyboardFocus)
      {

         return false;

      }

      return true;

   }


   bool window::has_keyboard_focus() const
   {

      auto pwindowing = ((window*)this)->windowing();

      if (!pwindowing)
      {

         return false;

      }

      auto pwindowKeyboardFocus = pwindowing->m_pwindowKeyboardFocus;

      if (::is_null(pwindowKeyboardFocus))
      {

         return false;

      }

      //auto pimplFocus = pwindowFocus->m_puserinteractionimpl;

      //if (::is_null(pimplFocus))
      //{

      //   return false;

      //}

      //auto pinteractionFocus = pimplFocus->m_puserinteraction;

      //if (::is_null(pinteractionFocus))
      //{

      //   return false;

      //}

      //if (!(pinteractionFocus->m_ewindowflag & ::e_window_flag_focus))
      //{

      //   return false;

      //}

      bool bHasKeyboardFocus = pwindowKeyboardFocus == this;

      if (!bHasKeyboardFocus)
      {

         return false;

      }

      return true;

   }


   ///// should be run in user thread
   //::e_status window::x11_store_name(const ::scoped_string & scopedstrName)
   //{

   //   synchronous_lock synchronouslock(user_synchronization());

   //   display_lock displaylock(x11_display()->Display());

   //   XStoreName(Display(), Window(), pszName);

   //   return ::success;

   //}


   //   string window::x11_get_name()
   //   {
   //
   //      string str;
   //
   //      char *name = NULL;
   //      int status = XFetchName(Display(), Window(), &name);
   //      if (status >= Success)
   //      {
   //         str = name;
   //      }
   //      XFree(name);
   //      return str;
   //
   //   }

   //// should be called in user_thread
   //   int_bool window::x11_get_window_rect(::rectangle_i32 *prectangle)
   //   {
   //
   //      XWindowAttributes attrs;
   //
   //      if (!XGetWindowAttributes(Display(), window, &attrs))
   //      {
   //
   //         windowing_output_debug_string("\n::x11_get_window_rect 1.1 (xgetwindowattributes failed)");
   //
   //         return false;
   //
   //      }
   //
   //      int x = 0;
   //
   //      int y = 0;
   //
   //      int screen = XDefaultScreen((Display *) d);
   //
   //      Window windowRoot = RootWindow((Display *) Display(), screen);
   //
   //      Window child;
   //
   //      XTranslateCoordinates(Display(), window, windowRoot, 0, 0, &x, &y, &child);
   //
   //      prectangle->left = x + attrs.x();
   //
   //      prectangle->top = y + attrs.y();
   //
   //      prectangle->right = x + attrs.x() + attrs.width;
   //
   //      prectangle->bottom = y + attrs.y() + attrs.height;
   //
   //
   //      windowing_output_debug_string("\n::x11_get_window_rect 2");
   //
   //      return true;
   //
   //   }

   //   int_bool window::client_rectangle(::rectangle_i32 *prectangle)
   //   {
   //
   //      synchronous_lock synchronouslock(user_synchronization());
   //
   //      display_lock displaylock(x11_display()->Display());
   //
   //      if (x11_display()->is_null())
   //      {
   //
   //         windowing_output_debug_string("\n::client_rectangle 1.1 (display is null)");
   //
   //         return false;
   //
   //      }
   //
   //      XWindowAttributes attr;
   //
   //      if (XGetWindowAttributes(Display(), Window(), &attr) == 0)
   //      {
   //
   //         windowing_output_debug_string("\n::client_rectangle 1.2 (xgetwindowattributes failed");
   //
   //         return false;
   //
   //      }
   //
   //      prectangle->left = 0;
   //
   //      prectangle->top = 0;
   //
   //      prectangle->right = prectangle->left + attr.width;
   //
   //      prectangle->bottom = prectangle->top + attr.height;
   //
   //      windowing_output_debug_string("\n::client_rectangle 2");
   //
   //      return true;
   //
   //   }


   void window::update_screen()
   {

      window_post([this]()
         {

            auto pimpl = m_puserinteractionimpl;

            if (::is_set(pimpl))
            {

               auto puserinteraction = pimpl->m_puserinteraction;

               if (::is_set(puserinteraction))
               {

                  string strType = __type_name(puserinteraction);

                  if (strType.contains("menu"))
                  {

                     output_debug_string("menu");

                  }

                  auto pimpl2 = puserinteraction->m_pinteractionimpl;

                  if (::is_set(pimpl2))
                  {

                     auto pprodevian = pimpl2->m_pprodevian;

                     if (::is_set(pprodevian))
                     {

                        pprodevian->update_screen();

                     }

                  }

               }

            }

         });

   }


   void window::window_show()
   {

      m_pwindowing->windowing_post([this]()
         {

            auto pimpl = m_puserinteractionimpl;

            if (::is_set(pimpl))
            {

               auto puserinteraction = pimpl->m_puserinteraction;

               if (::is_set(puserinteraction))
               {

                  auto pimpl2 = puserinteraction->m_pinteractionimpl;

                  if (::is_set(pimpl2))
                  {

                     pimpl2->window_show();

                  }

               }

            }

         });


   }


   void window::set_mouse_capture()
   {

      auto pwindowing = windowing();

      if (!pwindowing)
      {

         throw ::exception(error_wrong_state);

      }

      if (pwindowing->m_pwindowMouseCapture)
      {

         if (pwindowing->m_pwindowMouseCapture != this)
         {

            if (pwindowing->m_pwindowMouseCapture->m_puserinteractionimpl)
            {

               pwindowing->m_pwindowMouseCapture->m_puserinteractionimpl->m_puserinteractionMouseCapture.release();

            }

         }

      }

      pwindowing->m_pwindowMouseCapture = this;

      //if (Display() == nullptr)
      //{

      //   throw ::exception(error_failed);

      //}

      //if (Window() == None)
      //{

      //   throw ::exception(error_failed);

      //}

      //windowing_output_debug_string("\noswindow_data::SetCapture 1");

      //m_pwindowing->windowing_post([this]()
      //   {

      //      display_lock displaylock(x11_display()->Display());

      //      auto grabStatus = XGrabPointer(Display(), Window(), False,
      //         ButtonPressMask | ButtonReleaseMask |
      //         PointerMotionMask,
      //         GrabModeAsync, GrabModeAsync, None, None,
      //         CurrentTime);

      //      if (grabStatus != GrabSuccess)
      //      {

      //         windowing_output_debug_string("\noswindow_data::SetCapture 2.1");

      //         return;

      //      }

      //      auto pdisplay = x11_display();

      //      if (pdisplay)
      //      {

      //         pdisplay->_on_capture_changed_to(this);

      //      }

      //      windowing_output_debug_string("\noswindow_data::SetCapture 2");

      //   });

      //return ::success;

   }


   void window::set_keyboard_focus()
{
   
   auto pwindowing = windowing();

   if (!pwindowing)
   {

      throw ::exception(error_wrong_state);

   }

      auto puserinteractionimpl = m_puserinteractionimpl;

   if (pwindowing->m_pwindowKeyboardFocus && pwindowing->m_pwindowKeyboardFocus != this)
   {

      pwindowing->clear_keyboard_focus(puserinteractionimpl ? puserinteractionimpl->m_puserinteractionKeyboardFocusRequest : nullptr);

   }

   pwindowing->m_pwindowKeyboardFocus = this;

   SetInternalFocus();
     
      if (puserinteractionimpl)
   {

      puserinteractionimpl->on_final_set_keyboard_focus();
         //auto puserinteraction = puserinteractionimpl->m_puserinteraction;

         //if (puserinteraction)
         //{

         //   puserinteraction->post_message(e_message_set_focus);

         //}

   }

   //if (Window() == 0)
   //{

   //   throw ::exception(error_failed);

   //}

   //windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1");

   //display_lock displaylock(x11_display()->Display());

   //if (!is_window())
   //{

   //   windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1.1");

   //   throw ::exception(error_failed);

   //}

   //if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
   //{

   //   windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1.3");

   //   throw ::exception(error_failed);

   //}

   //windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 2");

   ////return ::success;





}

//   {
//
//      auto pwindowing = windowing();
//
//      if (!pwindowing)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      if (pwindowing->m_pwindowKeyboardFocus && pwindowing->m_pwindowKeyboardFocus != this)
//      {
//
//         pwindowing->clear_keyboard_focus(this);
//
//      }
//
//      pwindowing->m_pwindowKeyboardFocus = this;
//
//      SetInternalFocus();
//
//      //auto puserinteractionimpl = m_puserinteractionimpl;
//
//      //if (puserinteractionimpl)
//      //{
//
//      //   auto puserinteraction = puserinteractionimpl->m_puserinteraction;
//
//      //   if (puserinteraction)
//      //   {
//
//      //      if (puserinteraction->keyboard_focus_is_focusable())
//      //      {
//
//      //         //puserinteraction->post_message(e_message_set_focus);
//
//      //
//
//      //      }
//
//      //   }
//
//      //}
//
//      //if (Window() == 0)
//      //{
//
//      //   throw ::exception(error_failed);
//
//      //}
//
//      //windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      //if (!is_window())
//      //{
//
//      //   windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1.1");
//
//      //   throw ::exception(error_failed);
//
//      //}
//
//      //if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
//      //{
//
//      //   windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1.3");
//
//      //   throw ::exception(error_failed);
//
//      //}
//
//      //windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 2");
//
//      ////return ::success;
//
//   }


   void window::SetInternalFocus()
   {

      //if (m_puserinteractionimpl->m_puserinteractionKeyboardFocusRequest != nullptr)
      //{

      //   m_puserinteractionimpl->on_final_set_keyboard_focus(m_puserinteractionimpl->m_puserinteractionKeyboardFocusRequest);

      //}

   }


   bool window::is_active_window() const
   {

      return ::windowing::window::is_active_window();

   }


   void window::bring_to_front()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      //if (Window() == 0)
      //{

      //   throw ::exception(error_failed);

      //}

      //windowing_output_debug_string("\nwindow(sandbox)::set_keyboard_focus 1");

      //display_lock displaylock(x11_display()->Display());

      //XRaiseWindow(displaylock.m_pdisplay, Window());

      //return ::success;

   }


   //void window::on_touch_drag(int x, int y)
   //{


   //}


   /*float window::get_dpi_for_window()
   {

      return ::operating_system_driver::get()->m_fDpiX;

   }


   float window::get_density_for_window()
   {

      return ::operating_system_driver::get()->m_fDensity;

   }*/


} // namespace sandbox_windowing



