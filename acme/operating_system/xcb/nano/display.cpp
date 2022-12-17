
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "acme/user/nano/window.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/platform/acme.h"


struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};


#define MWM_HINTS_DECORATIONS   (1L << 1)


#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


void * x11_get_display(::particle * pparticle);

void set_main_user_thread();

xcb_connection_t * x11_display_xcb_connection(void * pX11Display);


namespace xcb
{


   display * display::g_p = nullptr;


   display::display()
   {

      m_pconnection = nullptr;

      m_bUnhook = false;

      if (!g_p)
      {

         g_p = this;

      }

      defer_create_synchronization();


   }


   display::~display()
   {


   }


   display * display::get()
   {

      return g_p;

   }


   xcb_atom_t display::intern_atom(const char * pszAtomName, bool bCreate)
   {

      if (m_pconnection == nullptr)
      {

         return 0;

      }

      auto cookie = xcb_intern_atom(m_pconnection, !bCreate, strlen(pszAtomName), pszAtomName);

      ::acme::malloc preply(xcb_intern_atom_reply(m_pconnection, cookie, nullptr));

      if (!preply)
      {

         return 0;

      }

      auto atom = preply->atom;

      return atom;

   }


   xcb_atom_t display::intern_atom(::x11::enum_atom eatom, bool bCreate)
   {

      if (eatom < 0 || eatom >= ::x11::e_atom_count)
      {

         return XCB_ATOM_NONE;

      }

      xcb_atom_t atom = m_atoma[eatom];

      if (atom == XCB_ATOM_NONE)
      {

         auto pszName = atom_name(eatom);

         if(eatom == ::x11::e_atom_net_active_window)
         {

            ::output_debug_string("e_atom_net_active_window");

         }

         atom = intern_atom(pszName, bCreate);

         m_atoma[eatom] = atom;

      }

      return atom;

   }


   long display::_window_get_long_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type)
   {

      int iDelete = 0;

      auto cookie = xcb_get_property(m_pconnection, iDelete, window, property, type, 0, 1);

      ::acme::malloc preply(xcb_get_property_reply(m_pconnection, cookie, nullptr));

      if (!preply)
      {

         return 0;

      }

      auto len = xcb_get_property_value_length(preply);

      if (len != 4)
      {

         //ASSERT(FALSE);

         return 0;

      }

      auto pint = (int *) xcb_get_property_value(preply);

      if (!pint)
      {

         return 0;

      }

      return *pint;

   }


   ::e_status display::_change_window_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type, int mode, int format, int nelements, const void * data)
   {

      auto cookie = xcb_change_property(
         m_pconnection,
         mode,
         window,
         property,
         type,
         format,
         nelements,
         data
      );

      auto estatus = _request_check(cookie);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_select_input(xcb_window_t window, i32 iInput)
   {

      windowing_output_debug_string("\nwindow::select_input");

      synchronous_lock synchronouslock(this->synchronization());

      //display_lock displaylock(xcb_display());

      uint32_t value[1];

      value[0] = iInput;

      auto cookie = xcb_change_window_attributes(
         m_pconnection,
         window,
         XCB_CW_EVENT_MASK,
         value);

      auto estatus = _request_check(cookie);

      windowing_output_debug_string("\nwindow::select_input END");

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


//   void display::display_post(const ::procedure & procedure)
//   {
//
//      defer_create_synchronization();
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_routineaPost.add(routine);
//
//      kick_idle();
//
//   }


//   bool display::display_posted_routine_step()
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_routineaPost.has_element())
//      {
//
//         auto proutine = m_routineaPost.pick_first();
//
//         if (proutine)
//         {
//
//            synchronouslock.unlock();
//
//            proutine->run();
//
//            return true;
//
//         }
//
//      }
//
//      return false;
//
//   }
//
//
//   void display::display_send(const ::procedure & procedure)
//   {
//
//      if (m_bUnhook)
//      {
//
//
//      }
//
//      /*auto estatus = */ __send_procedure(this, &display::display_post, routine);
//
//      //if(!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //return estatus;
//
//   }

//int g_fdX11[2] = {};
//
//bool g_bX11Idle = false;
//
//
//
//void display::wait_timer_or_event()
//{
//
//   struct timeval tv;
//
//   // This returns the FD of the X11 display (or something like that)
//   int x11_fd = ConnectionNumber(m_pconnection);
//
//   fd_set in_fds;
//
//   // Create a File Description Set containing x11_fd
//   FD_ZERO(&in_fds);
//   FD_SET(x11_fd, &in_fds);
//   FD_SET(g_fdX11[0], &in_fds);
//
//   // Set our timer.  One second sounds good.
//   tv.tv_usec = 0;
//   tv.tv_sec = 1;
//
//   // Wait for X Event or a Timer
//   int num_ready_fds = select(maximum(x11_fd, g_fdX11[0]) + 1, &in_fds, NULL, NULL, &tv);
//
//   if (num_ready_fds > 0)
//   {
//
//      //printf("Event Received!\n");
//
//      g_bX11Idle = false;
//
//      char buf[32];
//
//      int iRead;
//
//      while((iRead = read(g_fdX11[0], buf, sizeof(buf)))>0)
//      {
//
//         //printf("X11 fork count = %d\n", iRead);
//
//      }
//
//   }
//   else if (num_ready_fds == 0)
//   {
//
//      // Handle timer here
//      //printf("Timer Fired!\n");
//
//   }
//   else
//   {
//
//      //printf("An error occured!\n");
//
//   }
//
//}
//

   display * display::get(::particle * pparticle, bool bBranch, void * pX11Display)
   {

      critical_section_lock lock(::acme::g_p->globals_critical_section());

      if (g_p == nullptr)
      {

         auto p = memory_new display;

         p->initialize(pparticle);

         p->add_listener(p);

         p->m_pX11Display = pX11Display;

         if (bBranch)
         {

            lock.unlock();

            p->branch_synchronously();

         }
         else
         {

            p->init_task();

         }

      }

      return g_p;

   }


   void display::add_listener(event_listener * plistener)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_eventlistenera.add(plistener);

   }


   void display::add_window(nano_window * pwindow)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_windowa.add(pwindow);

   }


   void display::erase_listener(event_listener * plistener)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_eventlistenera.erase(plistener);

   }


   void display::erase_window(nano_window * pwindow)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_windowa.erase(pwindow);

   }


   bool display::message_loop_step()
   {

      ::acme::malloc pevent(xcb_poll_for_event(m_pconnection));

      if (!pevent)
      {

         return false;

      }

      xcb_event(pevent);

      return true;

   }


   bool display::xcb_posted()
   {

      return display_posted_routine_step();

   }


   bool display::xcb_event(xcb_generic_event_t * pevent)
   {

      bool bHandled = false;

      ::index i = 0;

      // if (pevent->response_type == XCB_CONFIGURE_NOTIFY)
      // {

      //    output_debug_string("ConfigureNotify");

      // }
      // else if (pevent->response_type == XCB_BUTTON_PRESS)
      // {

      //    output_debug_string("ButtonPress");

      // }

      for (; i < m_eventlistenera.get_count(); i++)
      {

         auto plistener = m_eventlistenera[i];

         if (plistener->_on_event(pevent))
         {

            bHandled = true;

            break;

         }

      }

      return bHandled;

   }


   void display::message_loop()
   {

      bool bHandled1;

      bool bHandled2;

      while (::task_get_run())
      {

         if (m_bUnhook)
         {

            break;

         }

         bHandled1 = false;

         bHandled2 = false;

         while (message_loop_step())
         {

            bHandled1 = true;

         }

         if (!bHandled1)
         {

            bHandled2 = xcb_posted();

         }

         xcb_flush(m_pconnection);

         if (!bHandled1 && !bHandled2)
         {

            preempt(5_ms);

         }

      }

      INFORMATION("Finished display::message_loop for nano::display");

   }


   void display::init_task()
   {

      if(acmesystem()->m_ewindowing == e_windowing_none)
      {

         set_main_user_thread();

         acmesystem()->m_ewindowing = e_windowing_xcb;

      }

      if(!m_pX11Display)
      {

         m_pX11Display = x11_get_display(this);

      }

#if defined(WITH_XCB)

      m_pconnection = (xcb_connection_t *) acmesystem()->m_pnode->get_os_xcb_connection();

#endif

      if(!m_pconnection)
      {

         m_pconnection = x11_display_xcb_connection(m_pX11Display);

      }

      if (xcb_connection_has_error(m_pconnection))
      {

         fprintf(stderr, "ERROR: failed to connection to X server\n");

         throw ::exception(error_failed);

      }

      auto cookie = xcb_render_query_pict_formats_unchecked(m_pconnection);

      ::acme::malloc preply(xcb_render_query_pict_formats_reply(m_pconnection, cookie, nullptr));

      m_prender_query_pict_formats_reply2 = preply;

      // Init the visual ID -> format ID hash table
      for (auto screens = xcb_render_query_pict_formats_screens_iterator(
         preply); screens.rem; xcb_render_pictscreen_next(&screens))
      {

         for (auto depths = xcb_render_pictscreen_depths_iterator(screens.data); depths.rem; xcb_render_pictdepth_next(
            &depths))
         {

            const xcb_render_pictvisual_t * visuals = xcb_render_pictdepth_visuals(depths.data);

            const int len = xcb_render_pictdepth_visuals_length(depths.data);

            for (int i = 0; i < len; i++)
            {

               m_mapVisualPictFormat.set_at(visuals[i].visual, visuals[i].format);

            }

         }

      }

      // Init the format ID -> xcb_render_directformat_t* hash table
      const xcb_render_pictforminfo_t * formats = xcb_render_query_pict_formats_formats(preply);

      const int len = xcb_render_query_pict_formats_formats_length(preply);

      for (int i = 0; i < len; i++)
      {

         if (formats[i].type == XCB_RENDER_PICT_TYPE_DIRECT)
         {

            m_mapFormatInfo.set_at(formats[i].id, &formats[i]);

         }

         // Init the visual ID -> depth hash table
         const xcb_setup_t * psetup = xcb_get_setup(m_pconnection);

         for (auto screen = xcb_setup_roots_iterator(psetup); screen.rem; xcb_screen_next(&screen))
         {

            for (auto depth = xcb_screen_allowed_depths_iterator(screen.data); depth.rem; xcb_depth_next(&depth))
            {

               const int len = xcb_depth_visuals_length(depth.data);

               const xcb_visualtype_t * visualtypea = xcb_depth_visuals(depth.data);

               for (int i = 0; i < len; i++)
               {

                  m_mapVisualDepth.set_at(visualtypea[i].visual_id, depth.data->depth);

               }

            }

         }

      }

      const xcb_setup_t * psetup = xcb_get_setup(m_pconnection);

      m_pscreen = xcb_setup_roots_iterator(psetup).data;

      m_windowRoot = m_pscreen->root;

      xcb_depth_iterator_t depthiterator = xcb_screen_allowed_depths_iterator(m_pscreen);

      m_pdepth = nullptr;

      while (depthiterator.rem)
      {

         if (depthiterator.data->depth == 32 && depthiterator.data->visuals_len)
         {

            m_pdepth = depthiterator.data;

            break;

         }

         xcb_depth_next(&depthiterator);

      }

      if (!m_pdepth)
      {

         fprintf(stderr, "ERROR: screen does not support 32 bit color depth\n");

         xcb_disconnect(m_pconnection);

         //return error_failed;

         throw ::exception(error_failed);

      }

      xcb_visualtype_iterator_t visualtypeiterator = xcb_depth_visuals_iterator(m_pdepth);

      while (visualtypeiterator.rem)
      {

         if (visualtypeiterator.data->_class == XCB_VISUAL_CLASS_TRUE_COLOR)
         {

            m_pvisualtype = visualtypeiterator.data;

            break;

         }

         xcb_visualtype_next(&visualtypeiterator);

      }

      if (!m_pvisualtype)
      {

         fprintf(stderr, "ERROR: screen does not support true Color\n");

         xcb_disconnect(m_pconnection);

         throw ::exception(error_failed);

      }

      m_colormap = xcb_generate_id(m_pconnection);

      {

         auto cookie = xcb_create_colormap_checked(
            m_pconnection,
            XCB_COLORMAP_ALLOC_NONE,
            m_colormap,
            m_pscreen->root,
            m_pvisualtype->visual_id);

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            fprintf(stderr, "ERROR: failed to create colormap\n");

            xcb_disconnect(m_pconnection);

            throw ::exception(estatus);

         }

      }

      _select_input(m_windowRoot, XCB_EVENT_MASK_PROPERTY_CHANGE);

      {

         xcb_window_t window = xcb_generate_id(m_pconnection);

         u32 uEventMask = XCB_EVENT_MASK_NO_EVENT;

         auto cookie = xcb_create_window(
            m_pconnection,
            m_pdepth->depth,
            window,
            m_windowRoot,
            0, 0,
            1, 1,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            m_pvisualtype->visual_id,
            XCB_CW_EVENT_MASK,
            &uEventMask);

         auto estatus = _request_check(cookie);

         if (!estatus)
         {

            throw exception(error_failed);

         }

         m_windowHelper = window;

      }

   }


   bool display::is_branch_current() const
   {

      if (!m_bUnhook && ::object::is_branch_current())
      {

         return true;

      }

      if (m_bUnhook && ::is_main_thread())
      {

         return true;

      }

      return false;

   }


   void display::run()
   {

      ::task_set_name("xcb:display:run");

      set_main_user_thread();

      message_loop();

      if (m_pconnection != nullptr)
      {

         xcb_disconnect(m_pconnection);

         m_pconnection = nullptr;

      }

   }


   void display::kick_idle()
   {

      xcb_client_message_event_t event;

      memset(&event, 0, sizeof(event));

      event.response_type = XCB_CLIENT_MESSAGE;
      event.format = 32;
      event.sequence = 0;
      event.window = m_windowHelper;
      event.type = intern_atom("kick_idle", true);
      event.data.data32[0] = 0;

      xcb_send_event(m_pconnection,
                     false,
                     m_windowHelper,
                     XCB_EVENT_MASK_NO_EVENT,
                     reinterpret_cast<const char *>(&event));

      xcb_flush(m_pconnection);

   }


   bool display::_on_event(xcb_generic_event_t * pevent)
   {

      if (pevent->response_type == XCB_CLIENT_MESSAGE)
      {

         auto pmessage = (xcb_client_message_event_t *) pevent;

         if (pmessage->window == m_windowHelper)
         {

            if(pmessage->type == intern_atom("kick_idle", true))
            {


               output_debug_string("kick_idle\n");

            }


            return true;

         }

      }
      else if (pevent->response_type == XCB_PROPERTY_NOTIFY)
      {

         auto pproperty = (xcb_property_notify_event_t *) pevent;

         if (pproperty->window == m_windowRoot)
         {

            auto atom = intern_atom(::x11::e_atom_net_active_window, false);

            if (atom == pproperty->atom)
            {

               auto windowActive = m_windowActive;

               for (auto & pwindow: m_windowa)
               {

                  bool bNcActive = windowActive == pwindow->m_window;

                  if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
                  {

                     pwindow->m_pinterface->m_bNcActive = bNcActive;

                     pwindow->redraw();

                  }

               }

               m_windowActive = windowActive;

            }

         }

      }

      return false;

   }


   ::e_status display::_request_check(xcb_void_cookie_t cookie)
   {

      ::acme::malloc perror(xcb_request_check(m_pconnection, cookie));

      if (perror)
      {

         int iErrorCode = perror->error_code;

         return error_failed;

      }

      return success;

   }


   ::e_status
   display::_send_client_event(xcb_window_t window1, xcb_window_t window2, xcb_atom_t atom, unsigned int numArgs, ...)
   {

      va_list argList;

      va_start(argList, numArgs);

      auto estatus = _send_client_event_v(window1, window2, atom, numArgs, argList);

      va_end(argList);

      return estatus;

   }


   ::e_status
   display::_send_client_event_v(xcb_window_t window1, xcb_window_t window2, xcb_atom_t atom, unsigned int numArgs,
                                 va_list argList)
   {

      xcb_client_message_event_t event;

      zero(event);

      event.response_type = XCB_CLIENT_MESSAGE;
      event.sequence = 0;
      event.window = window2;
      event.type = atom;
      event.format = 32;

      for (int i = 0; i < 5; i++)
      {

         if (i < numArgs)
         {

            event.data.data32[i] = va_arg(argList, int);

         }
         else
         {

            event.data.data32[i] = 0;

         }

      }

      auto cookie = xcb_send_event(
         m_pconnection,
         window1,
         false,
         XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_STRUCTURE_NOTIFY,
         (const char *) &event);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   xcb_window_t display::_get_active_window()
   {

      auto window = (xcb_window_t) _window_get_long_property(m_windowRoot, intern_atom(::x11::e_atom_net_active_window, false), XCB_ATOM_WINDOW);

      windowing_output_debug_string("\n::_get_active_window 2");

      return window;

   }


   ::e_status display::_set_active_window(xcb_window_t window)
   {

      windowing_output_debug_string("\n::set_active_window 1");

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomActiveWindow = intern_atom(::x11::e_atom_net_active_window, false);

      auto estatus = _send_client_event(
         m_windowRoot,
         window,
         atomActiveWindow,
         1,
         1);

      if (!estatus)
      {

         throw ::exception(estatus);

      }

      windowing_output_debug_string("\n::set_active_window 2");

      return estatus;

   }


   ::e_status display::_map_window(xcb_window_t window)
   {

      int i = 0;

      windowing_output_debug_string("\nwindow::map_window");

      //display_lock displaylock(xcb_display());

      auto cookie = xcb_map_window(m_pconnection, window);

      auto estatus = _request_check(cookie);

      //auto pwindowing = xcb_windowing();

//      if(!pwindowing->m_bFirstWindowMap)
//      {
//
//         pwindowing->m_bFirstWindowMap = true;
//
//         auto psystem = acmesystem()->m_paurasystem;
//
//         auto pnode = psystem->node();
//
//         pnode->defer_notify_startup_complete();
//
//      }

      windowing_output_debug_string("\nwindow::map_window END");

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_unmap_window(xcb_window_t window)
   {

//      auto estatus = xcb_display()->m_pxcbdisplay->_unmap_window(xcb_window());
//
//      windowing_output_debug_string("\nwindow::unmap_window");
//
//      //display_lock displaylock(xcb_display());
//
      ::e_status estatus;

      auto cookie = xcb_unmap_window(m_pconnection, window);

      estatus = _request_check(cookie);

      windowing_output_debug_string("\nwindow::unmap_window END");

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_raise_window(xcb_window_t window)
   {

      auto estatus = _clear_net_wm_state(window);

      auto cookie = xcb_circulate_window(m_pconnection, XCB_CIRCULATE_RAISE_LOWEST, window);

      estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_lower_window(xcb_window_t window)
   {

      auto estatus = _clear_net_wm_state(window);

      auto cookie = xcb_circulate_window(m_pconnection, XCB_CIRCULATE_LOWER_HIGHEST, window);

      estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   bool display::_has_net_wm_state(xcb_window_t window, xcb_atom_t propertyItem)
   {

      auto atomWmState = intern_atom(::x11::e_atom_net_wm_state, false);

      return _list_has_atom(window, atomWmState, propertyItem);

   }


   bool display::_list_has_atom(xcb_window_t window, xcb_atom_t propertyList, xcb_atom_t propertyItem)
   {

      array < xcb_atom_t > atoma;

      auto cookie = xcb_get_property(
         m_pconnection,
         0,
         window,
         propertyList,
         XCB_ATOM_ATOM,
         0,
         0);

      ::acme::malloc preply(xcb_get_property_reply(
         m_pconnection,
         cookie,
         nullptr
      ));

      if(!preply)
      {

         return false;

      }

      auto len = xcb_get_property_value_length(preply);

      auto patom = (xcb_atom_t *) xcb_get_property_value(preply);

      auto count = len / sizeof(xcb_atom_t);

      for(int i = 0; i < count; i++)
      {

         if(patom[i] == propertyItem)
         {

            return true;

         }

      }

      return false;

   }


   comparable_array < xcb_atom_t > display::_list_atom(xcb_window_t window, xcb_atom_t property)
   {

      comparable_array < xcb_atom_t > atoma;

      auto cookie = xcb_get_property(
         m_pconnection,
         0,
         window,
         property,
         XCB_ATOM_ATOM,
         0,
         0);

      ::acme::malloc preply(xcb_get_property_reply(
         m_pconnection,
         cookie,
         nullptr
      ));

      if(!preply)
      {

         return atoma;

      }

      auto size = xcb_get_property_value_length(preply);

      auto patom = xcb_get_property_value(preply);

      atoma.set_size(size / sizeof(xcb_atom_t));

      memcpy(atoma.data(), patom, atoma.get_size_in_bytes());

      return atoma;

   }


   ::e_status display::_list_add_atom(xcb_window_t window, xcb_atom_t atomList, xcb_atom_t atomFlag)
   {

      if (atomFlag == 0)
      {

         return false;

      }

      if (atomList == 0)
      {

         return false;

      }

      if (!_list_has_atom(window, atomList, atomFlag))
      {

         _change_window_property(window, atomList, XCB_ATOM_ATOM, XCB_PROP_MODE_APPEND, 32, 1, &atomFlag);

      }

      return true;

   }


   ::e_status display::_list_erase_atom(xcb_window_t window, xcb_atom_t atomList, xcb_atom_t atomFlag)
   {

      if (atomFlag == 0)
      {

         return false;

      }

      if (atomList == 0)
      {

         return false;

      }

      auto atoma = _list_atom(window, atomList);

      if (atoma.is_empty())
      {

         return true;

      }

      ::count cRemove = atoma.erase(atomFlag);

      if (cRemove > 0)
      {

         _change_window_property(window, atomList, XCB_ATOM_ATOM, XCB_PROP_MODE_REPLACE, 32, atoma.get_count(), atoma.data());

      }

      return true;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_clear_net_wm_state(xcb_window_t window)
   {

      auto estatus1 = _erase_net_wm_state(window, ::x11::e_atom_net_wm_state_above);

      auto estatus2 = _erase_net_wm_state(window, ::x11::e_atom_net_wm_state_below);

      auto estatus3 = _erase_net_wm_state(window, ::x11::e_atom_net_wm_state_hidden);

      if (!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_add_net_wm_state_below(xcb_window_t window)
   {

      auto estatus1 = _erase_net_wm_state_hidden(window);

      auto estatus2 = _erase_net_wm_state_above(window);

      auto estatus3 = _add_net_wm_state(window, ::x11::e_atom_net_wm_state_below);

      if (!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_add_net_wm_state_above(xcb_window_t window)
   {

      auto estatus1 = _erase_net_wm_state_hidden(window);
      auto estatus2 = _add_net_wm_state(window,::x11::e_atom_net_wm_state_above);
      auto estatus3 = _erase_net_wm_state_hidden(window);

      if (!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_add_net_wm_state_hidden(xcb_window_t window)
   {

      auto estatus1 = _add_net_wm_state(window, ::x11::e_atom_net_wm_state_hidden);
      auto estatus2 = _erase_net_wm_state_above(window);
      auto estatus3 = _erase_net_wm_state_below(window);

      if (!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_add_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState)
   {

      //display_lock displaylock(xcb_display());

      xcb_get_window_attributes_reply_t attributes;

      auto estatus = _get_window_attributes(&attributes, window);

      if(!estatus)
      {

         return estatus;

      }

      if(attributes.map_state != XCB_MAP_STATE_UNMAPPED)
      {

         estatus = _mapped_add_net_wm_state(window, eatomNetWmState);

      }
      else
      {

         estatus = _unmapped_add_net_wm_state(window, eatomNetWmState);

      }

      return estatus;

   }

   /// must be run in x11 thread (user thread)
   ::e_status display::_mapped_add_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState)
   {

      auto atomFlag = intern_atom(eatomNetWmState, false);

      auto atomWmNetState = intern_atom(::x11::e_atom_net_wm_state, false);

      if (_list_has_atom(window, atomWmNetState, atomFlag))
      {

         return success_none;

      }

      auto estatus = _send_client_event(m_windowRoot, window, atomWmNetState, _NET_WM_STATE_ADD, atomFlag);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_mapped_erase_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState)
   {

      auto atomFlag = intern_atom(eatomNetWmState, false);

      auto atomWmNetState = intern_atom(::x11::e_atom_net_wm_state, false);

      if (!_list_has_atom(window, atomWmNetState, atomFlag))
      {

         return success_none;

      }

      auto estatus = _send_client_event(m_windowRoot, window, atomWmNetState, _NET_WM_STATE_REMOVE, atomFlag);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_unmapped_add_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState)
   {

      auto atomNetWmState = intern_atom(::x11::e_atom_net_wm_state, false);

      auto atomWmNetState = intern_atom(eatomNetWmState, false);

      auto estatus = _list_add_atom(window, atomWmNetState, atomWmNetState);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_unmapped_erase_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState)
   {

      auto atomNetWmState = intern_atom(::x11::e_atom_net_wm_state, false);

      auto atomWmNetState = intern_atom(eatomNetWmState, false);

      auto estatus = _list_erase_atom(window, atomWmNetState, atomWmNetState);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_erase_net_wm_state_below(xcb_window_t window)
   {

      auto estatus = _erase_net_wm_state(window, ::x11::e_atom_net_wm_state_below);

      if (!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_erase_net_wm_state_above(xcb_window_t window)
   {

      auto estatus = _erase_net_wm_state(window, ::x11::e_atom_net_wm_state_above);

      if (!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status display::_erase_net_wm_state_hidden(xcb_window_t window)
   {

      auto estatus = _erase_net_wm_state(window, ::x11::e_atom_net_wm_state_hidden);

      if (!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   ::e_status display::_erase_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState)
   {

      xcb_get_window_attributes_reply_t attributes;

      auto estatus = _get_window_attributes(&attributes, window);

      if(!estatus)
      {

         return estatus;

      }

      if(attributes.map_state != XCB_MAP_STATE_UNMAPPED)
      {

         estatus = _mapped_erase_net_wm_state(window, eatomNetWmState);

      }
      else
      {

         estatus = _unmapped_erase_net_wm_state(window, eatomNetWmState);

      }

      return
         estatus;


   }

   ::e_status display::_destroy_window(xcb_window_t window)
   {

      auto cookie = xcb_destroy_window(m_pconnection, window);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status display::_move_window(xcb_window_t window, int x, int y)
   {

      uint16_t mask = 0;

      mask |=
         XCB_CONFIG_WINDOW_X;
      mask |=
         XCB_CONFIG_WINDOW_Y;

      ::u32 ua[] = {(::u32) x, (::u32) y};

      auto cookie = xcb_configure_window(m_pconnection, window, mask, ua);

      auto estatus = _request_check(cookie);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;


   }


   ::e_status display::_set_mouse_capture(xcb_window_t window)
   {

      if (m_pconnection == nullptr)
      {

         return error_failed;

      }

      if (window == 0)
      {

         return error_failed;

      }

      windowing_output_debug_string("\noswindow_data::SetCapture 1");

      //display_lock displaylock(xcb_display());

      int owner_events = 0;

      xcb_window_t confine_to = XCB_WINDOW_NONE;

      xcb_cursor_t cursor = XCB_CURSOR_NONE;

      auto cookie = xcb_grab_pointer(
         m_pconnection,
         owner_events,
         window,
         XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION,
         XCB_GRAB_MODE_ASYNC,
         XCB_GRAB_MODE_ASYNC,
         confine_to,
         cursor,
         XCB_CURRENT_TIME);

      ::acme::malloc preply(xcb_grab_pointer_reply(m_pconnection, cookie, nullptr));

      if (!preply)
      {

         return error_failed;

      }

      windowing_output_debug_string("\noswindow_data::SetCapture 2");

      return ::success;

   }


   ::e_status display::_release_mouse_capture()
   {

      //_on_capture_changed_to(nullptr);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

      //display_lock displaylock(this);

      xcb_ungrab_pointer(m_pconnection, XCB_CURRENT_TIME);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

      return ::success;

   }


   ::e_status display::_get_window_attributes(xcb_get_window_attributes_reply_t * pattributes, xcb_window_t window)
   {

      auto cookie = xcb_get_window_attributes(m_pconnection, window);

      ::acme::malloc preply(xcb_get_window_attributes_reply(m_pconnection, cookie, nullptr));

      if(!preply)
      {

         INFORMATION("freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.");

         return error_failed;

      }

      *pattributes = *preply;

      return success;

   }


   ::e_status display::_get_window_geometry(xcb_get_geometry_reply_t * pgeometry, xcb_window_t window)
   {

      auto cookie = xcb_get_geometry(m_pconnection, window);

      ::acme::malloc preply(xcb_get_geometry_reply(m_pconnection, cookie, nullptr));

      if (!preply)
      {

         INFORMATION("freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.");

         return
            error_failed;

      }

      *pgeometry = *preply;

      return success;

   }


/// must be run in x11 thread (user thread)
   ::e_status display::_set_nodecorations(xcb_window_t window, int bMap)
   {

      ::e_status estatus = ::error_failed;

      xcb_atom_t atomMotifHints = intern_atom("_MOTIF_WM_HINTS", true);

      if (atomMotifHints != XCB_ATOM_NONE)
      {

         MWMHints hints = {};

         hints.flags = MWM_HINTS_DECORATIONS;
         hints.decorations = MWM_DECOR_NONE;

         //XChangeProperty(xcb_connection(), xcb_window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
         //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
         estatus = _change_window_property(window, atomMotifHints, atomMotifHints, XCB_PROP_MODE_REPLACE, 32, 5, &hints);

      }

      if (bMap)
      {

         _unmap_window(window);

         _map_window(window);

      }

      windowing_output_debug_string("\n::wm_nodecorations 2");

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::size_i32 display::get_main_screen_size()
   {

      auto snum = DefaultScreen((Display *) m_pX11Display);

      auto width = DisplayWidth((Display *) m_pX11Display, snum);

      auto height = DisplayHeight((Display *) m_pX11Display, snum);

      return { width, height };

   }



} // namespace xcb



