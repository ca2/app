//
// Created by camilo on 10/6/23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display_base.h"
#include "window_base.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/operating_system/wayland/xfree86_key.h"
#include "acme/platform/system.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/constant/_user_key_text.h"
#include <xkbcommon/xkbcommon.h>

bool is_control_character(ansi_character ansich)
{

   return ansich >= 0 && ansich <= 31;

}


bool is_control_character(const ::scoped_string & scopedstr)
{

   return scopedstr.length_in_bytes() == 1 && ::is_control_character(scopedstr.begin()[0]);

}

namespace wayland
{

namespace nano
{
   namespace user
   {
      //struct  {
      /**
       * the exported activation token
       *
       * The 'done' event contains the unique token of this activation
       * request and notifies that the provider is done.
       * @param token the exported activation token
       */
      void xdg_activation_token_v1_done(void * data,
                                        ::xdg_activation_token_v1 * pxdgactivationtokenv1,
                                        const char * token)
      {

         auto pwaylandwindow = (window_base *) data;

         if (pxdgactivationtokenv1 == pwaylandwindow->m_pxdgactivationtokenv1)
         {

            pwaylandwindow->m_strActivationToken = token;

            pwaylandwindow->information() << "Got Activation Token : " << token;
            //            xdg_activation_v1_activate(pwaylandwindow->wayland_display()->m_pxdgactivationv1,
            //                                       token,
            //                                       pwaylandwindow->m_pwlsurface);
            //            xdg_activation_token_v1_destroy(pwaylandwindow->m_pxdgactivationtokenv1);
            //            pwaylandwindow->m_pxdgactivationtokenv1 = NULL;

            //            wl_display_dispatch(pwaylandwindow->wayland_display()->m_pwldisplay);
            //
            //            wl_display_roundtrip(pwaylandwindow->wayland_display()->m_pwldisplay);

         }
      }

      //};
      const static struct xdg_activation_token_v1_listener g_xdg_activation_token_v1_listener =
         {
         xdg_activation_token_v1_done
      };

      //   const static struct wl_surface_listener g_wl_surface_listener =
      //      {
      //
      //
      //      };

      void xdg_surface_configure(void * data, struct xdg_surface * xdg_surface, uint32_t serial)
      {

         auto pwaylandwindow = (window_base *) data;

         pwaylandwindow->__handle_xdg_surface_configure(serial);

      }


      /**
       * close - surface wants to be closed
       *
       * The close event is sent by the compositor when the user wants
       * the surface to be closed. This should be equivalent to the user
       * clicking the close button in client-side decorations, if your
       * application has any...
       *
       * This is only a request that the user intends to close your
       * window. The client may choose to ignore this request, or show a
       * dialog to ask the user to save their data...
       */
      void xdg_surface_close(void * data, struct xdg_surface * xdg_surface)
      {

      }


      static const struct xdg_surface_listener xdg_surface_listener =
         {

         xdg_surface_configure,

      };


      /**
       * suggest a surface change
       *
       * This configure event asks the client to resize its toplevel
       * surface or to change its state. The configured state should not
       * be applied immediately. See xdg_surface.configure for details.
       *
       * The width and height arguments specify a hint to the window
       * about how its surface should be resized in window geometry
       * coordinates. See set_window_geometry.
       *
       * If the width or height arguments are zero, it means the client
       * should decide its own window dimension. This may happen when the
       * compositor needs to configure the state of the surface but
       * doesn't have any information about any previous or expected
       * dimension.
       *
       * The states listed in the event specify how the width/height
       * arguments should be interpreted, and possibly how it should be
       * drawn.
       *
       * Clients must send an ack_configure in response to this event.
       * See xdg_surface.configure and xdg_surface.ack_configure for
       * details.
       */
      void xdg_toplevel_configure(void * data,
                                  struct xdg_toplevel * pxdgtoplevel,
                                  int32_t width,
                                  int32_t height,
                                  ::wl_array * pwlarrayState)
      {

         auto pwaylandwindow = (window_base *) data;

         if (pwaylandwindow->m_resizeedge != 0)
         {

            if (pwlarrayState->size == 0)
            {

               pwaylandwindow->m_resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;

            }
            else
            {

               if (pwaylandwindow->m_resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM
                   || pwaylandwindow->m_resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_TOP)
               {

                  width = 0;

               }
               else if (pwaylandwindow->m_resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_LEFT
                        || pwaylandwindow->m_resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_RIGHT)
               {

                  height = 0;

               }

            }

         }

         pwaylandwindow->__handle_xdg_toplevel_configure(width, height, pwlarrayState);

      }


      /**
       * surface wants to be closed
       *
       * The close event is sent by the compositor when the user wants
       * the surface to be closed. This should be equivalent to the user
       * clicking the close button in client-side decorations, if your
       * application has any.
       *
       * This is only a request that the user intends to close the
       * window. The client may choose to ignore this request, or show a
       * dialog to ask the user to save their data, etc.
       */
      void xdg_toplevel_close(void * data,
                              struct xdg_toplevel * xdg_toplevel)
      {


      }

      /**
       * recommended window geometry bounds
       *
       * The configure_bounds event may be sent prior to a
       * xdg_toplevel.configure event to communicate the bounds a window
       * geometry size is recommended to constrain to.
       *
       * The passed width and height are in surface coordinate space. If
       * width and height are 0, it means bounds is unknown and
       * equivalent to as if no configure_bounds event was ever sent for
       * this surface.
       *
       * The bounds can for example correspond to the size of a monitor
       * excluding any panels or other shell components, so that a
       * surface isn't created in a way that it cannot fit.
       *
       * The bounds may change at any point, and in such a case, a new
       * xdg_toplevel.configure_bounds will be sent, followed by
       * xdg_toplevel.configure and xdg_surface.configure.
       * @since 4
       */
      void xdg_toplevel_configure_bounds(void * data,
                                         struct xdg_toplevel * xdg_toplevel,
                                         int32_t width,
                                         int32_t height)
      {


      }

      /**
       * compositor capabilities
       *
       * This event advertises the capabilities supported by the
       * compositor. If a capability isn't supported, clients should hide
       * or disable the UI elements that expose this functionality. For
       * instance, if the compositor doesn't advertise support for
       * minimized toplevels, a button triggering the set_minimized
       * request should not be displayed.
       *
       * The compositor will ignore requests it doesn't support. For
       * instance, a compositor which doesn't advertise support for
       * minimized will ignore set_minimized requests.
       *
       * Compositors must send this event once before the first
       * xdg_surface.configure event. When the capabilities change,
       * compositors must send this event again and then send an
       * xdg_surface.configure event.
       *
       * The configured state should not be applied immediately. See
       * xdg_surface.configure for details.
       *
       * The capabilities are sent as an array of 32-bit unsigned
       * integers in native endianness.
       * @param capabilities array of 32-bit capabilities
       * @since 5
       */
      void xdg_toplevel_capabilities(void * data,
                                     struct xdg_toplevel * xdg_toplevel,
                                     struct wl_array * capabilities)
      {

      }


      static const struct xdg_toplevel_listener g_xdg_toplevel_listener =
         {

         xdg_toplevel_configure,
         xdg_toplevel_close,
         xdg_toplevel_configure_bounds,
         xdg_toplevel_capabilities

      };


      static void
      redraw(void * data, struct wl_callback * callback, uint32_t time)
      {
         printf("Redrawing\n");
      }

      static void
      configure_callback(void * data, struct wl_callback * callback, uint32_t time)
      {
         if (callback == NULL)
            redraw(data, NULL, time);
      }

      static struct wl_callback_listener configure_callback_listener = {
         configure_callback,
      };
      //   static void
      //   handle_ping(void *data, struct wl_shell_surface *shell_surface,
      //               uint32_t serial)
      //   {
      //      wl_shell_surface_pong(shell_surface, serial);
      //      fprintf(stderr, "Pinged and ponged\n");
      //   }
      //
      //   static void
      //   handle_configure(void *data, struct wl_shell_surface *shell_surface,
      //                    uint32_t edges, int32_t width, int32_t height)
      //   {
      //   }
      //
      //   static void
      //   handle_popup_done(void *data, struct wl_shell_surface *shell_surface)
      //   {
      //   }
      //
      //
      //   static const struct wl_shell_surface_listener shell_surface_listener = {
      //      handle_ping,
      //      handle_configure,
      //      handle_popup_done
      //   };

      static void handle_configure_xdg_popup(void * data,
                                             struct xdg_popup * xdg_popup,
                                             int32_t x,
                                             int32_t y,
                                             int32_t width,
                                             int32_t height)
      {
         /* No-op, we don't use x/y and width/height are fixed-size */
      }

      static void handle_done_xdg_popup(void * data, struct xdg_popup * xdg_popup)
      {
         auto pwindow = (window_base *) data;
         //pwindow->m_puserinteractionimpl->m_puserinteraction->post_message(e_message_close);
         pwindow->_on_windowing_close_window();
         //SDL_SendWindowEvent(window->sdlwindow, SDL_WINDOWEVENT_CLOSE, 0, 0);
      }

      static void handle_repositioned_xdg_popup(void * data,
                                                struct xdg_popup * xdg_popup,
                                                uint32_t token)
      {
         /* No-op, configure does all the work we care about */
      }

      static const struct xdg_popup_listener popup_listener_xdg = {
         handle_configure_xdg_popup,
         handle_done_xdg_popup,
         handle_repositioned_xdg_popup
      };



      window_base::window_base()
      {

         m_bDoneFirstMapping = false;
         m_uLastConfigureSerial = 0;
         m_uLastRequestSerial = 0;
         m_uLastAckSerial = 0;
         //m_iXic = 0;


         m_bHasKeyboardFocus = false;

         //m_xic = nullptr;
         m_pxdgsurface = nullptr;
         m_pwlsurface = nullptr;
         m_pwlsubsurface = nullptr;
         m_pxdgtoplevel = nullptr;
         m_pxdgpopup = nullptr;
         m_pxdgpositioner = nullptr;

         m_pxdgactivationtokenv1 = nullptr;

      }


      window_base::~window_base()
      {

      }


      void window_base::destroy()
      {

         __unmap();

      }


      void window_base::__activate_window(bool bNormalPriority)
      {

         auto pdisplaybase = m_pdisplaybase;

         information() << "::windowing_wayland::window::__activate_window bNormalPriority : " << bNormalPriority;

         if (pdisplaybase->m_pxdgactivationv1)
         {

            /* If the focus request does not have a startup ID associated, get a
   * new token to activate the window.
   */
            if (m_strActivationToken.is_empty())
            {

               //         if (m_pxdgactivationtokenv1 != NULL) {
               //            /* We're about to overwrite this with a new request */
               //            xdg_activation_token_v1_destroy(m_pxdgactivationtokenv1);
               //         }
               information() << "__activate_window getting activation token";

               //struct xdg_activation_token_v1 *token;
               //struct wl_event_queue *event_queue;
               //struct wl_surface *wl_surface = NULL;
               //GdkSurface *focus_surface;

               auto pwleventqueue = wl_display_create_queue(pdisplaybase->m_pwldisplay);

               information() << "wl_display_create_queue : " << (::iptr) pwleventqueue;

               m_pxdgactivationtokenv1 = xdg_activation_v1_get_activation_token(pdisplaybase->m_pxdgactivationv1);

               information() << "xdg_activation_v1_get_activation_token : " << (::iptr) m_pxdgactivationtokenv1;

               wl_proxy_set_queue((struct wl_proxy *) m_pxdgactivationtokenv1, pwleventqueue);

               xdg_activation_token_v1_add_listener(m_pxdgactivationtokenv1,
                                                    &g_xdg_activation_token_v1_listener,
                                                    this);


               xdg_activation_token_v1_set_serial(m_pxdgactivationtokenv1,
                                                  pdisplaybase->m_uLastPointerSerial,
                                                  pdisplaybase->m_pwlseat);

               //focus_surface = gdk_wayland_device_get_focus (gdk_seat_get_keyboard (GDK_SEAT (seat)));
               //if (focus_surface)
               // wl_surface = gdk_wayland_surface_get_wl_surface (focus_surface);

               auto pwlsurfaceFocus = pdisplaybase->_wl_surface_focus();

               if (pwlsurfaceFocus)
                  xdg_activation_token_v1_set_surface(m_pxdgactivationtokenv1, pwlsurfaceFocus);

               xdg_activation_token_v1_commit(m_pxdgactivationtokenv1);

               while (m_strActivationToken.is_empty())
               {
                  wl_display_dispatch_queue(pdisplaybase->m_pwldisplay,
                                            pwleventqueue);
               }

               xdg_activation_token_v1_destroy(m_pxdgactivationtokenv1);
               wl_event_queue_destroy(pwleventqueue);
            }

            xdg_activation_v1_activate(pdisplaybase->m_pxdgactivationv1,
                                       m_strActivationToken,
                                       m_pwlsurface);

            information() << "xdg_activation_v1_activate activating with token : " << m_strActivationToken;

            //            m_pxdgactivationtokenv1 = xdg_activation_v1_get_activation_token(pwaylanddisplay->m_pxdgactivationv1);
            //
            //         information() << "m_pxdgactivationtokenv1 : " << (::iptr) m_pxdgactivationtokenv1;
            //         xdg_activation_token_v1_add_listener(m_pxdgactivationtokenv1,
            //                                              &g_xdg_activation_token_v1_listener,
            //                                              this);
            //
            //         auto psystem = system()->m_papexsystem;
            //
            //         string strApplicationServerName = psystem->get_application_server_name();
            //
            //         xdg_activation_token_v1_set_app_id(m_pxdgactivationtokenv1, strApplicationServerName);
            //
            //         information() << "xdg_activation_token_v1_set_app_id : " << strApplicationServerName;
            //
            //         /* Note that we are not setting the app_id here.
            //          *
            //          * Hypothetically we could set the app_id from data->classname, but
            //          * that part of the API is for _external_ programs, not ourselves.
            //          *
            //          * -flibit
            //          */
            //         if (m_pwlsurface != NULL) {
            //            /* This specifies the surface from which the activation request is originating, not the activation target surface. */
            //            xdg_activation_token_v1_set_surface(m_pxdgactivationtokenv1, m_pwlsurface);
            //            information() << "xdg_activation_token_v1_set_surface : " << (::iptr) m_pwlsurface;
            //         }
            //         if (bNormalPriority && pwaylanddisplay->m_pwlseat) {
            //            /* Not setting the serial will specify 'urgency' without switching focus as per
            // * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
            // */
            //            xdg_activation_token_v1_set_serial(m_pxdgactivationtokenv1,
            //                                               pwaylanddisplay->m_uLastPointerSerial,
            //                                               pwaylanddisplay->m_pwlseat);
            //            information() << "xdg_activation_token_v1_set_serial : " << (::iptr) pwaylanddisplay->m_uLastPointerSerial << ", pwlseat : " << (::iptr) pwaylanddisplay->m_pwlseat;
            //         }
            //         xdg_activation_token_v1_commit(m_pxdgactivationtokenv1);
         }

      }


      void window_base::__map()
      {

         if (m_pxdgtoplevel != nullptr || m_pxdgpopup != nullptr)
         {

            return;

         }

         information() << "windowing_wayland::window::__map sizeWindow : " << m_sizeWindow;

         ::minimum(m_sizeConfigure.cx());

         ::minimum(m_sizeConfigure.cy());

         m_bDoneFirstMapping = false;

         m_bXdgInitialConfigure = false;

         m_uLastRequestSerial = 0;

         m_uLastConfigureSerial = 0;

         m_uLastAckSerial = 0;

         auto pdisplaybase = m_pdisplaybase;

         information() << "pdisplaybase : " << (::iptr) pdisplaybase.m_p;

         auto pwlcompositor = pdisplaybase->m_pwlcompositor;

         information() << "pwlcompositor : " << (::iptr) pwlcompositor;

         m_pwlsurface = wl_compositor_create_surface(pwlcompositor);

         if (m_pwlsurface == NULL)
         {

            error() << "Can't create wayland surface";

            throw ::exception(::error_failed);

         }
         else
         {

            information() << "Created wayland surface";

         }


         //auto puserinteractionOwner = m_puserinteractionimpl->m_puserinteraction->m_puserinteractionOwner;

         //      if(puserinteractionOwner)
         //      {
         //
         //         ::pointer < window > pwindowOwner = puserinteractionOwner->window();
         //
         //         if(pwindowOwner->m_pwlsurface)
         //         {
         //
         //            m_pwlsubsurface = wl_subcompositor_get_subsurface(
         //               pdisplaybase->m_pwlsubcompositor,
         //               m_pwlsurface,
         //               pwindowOwner->m_pwlsurface);
         //
         //            if(m_pwlsubsurface)
         //            {
         //
         //               information() << "Created wayland subsurface";
         //
         //            }
         //            else
         //            {
         //
         //               information() << "Failed to create wayland subsurface";
         //
         //               wl_subsurface_set_desync(m_pwlsubsurface);
         //
         //            }
         //
         //         }
         //
         //      }

         //wl_surface_add_listener(m_pwlsurface, &g_wl_surface_listener, this);

         pdisplaybase->m_windowmap[m_pwlsurface] = this;

         auto pxdgwmbase = pdisplaybase->m_pxdgwmbase;

         information() << "pxdgwmbase : " << (::iptr) pxdgwmbase;

         if (!m_pxdgsurface)
         {

            m_pxdgsurface = xdg_wm_base_get_xdg_surface(pxdgwmbase, m_pwlsurface);

            if (m_pxdgsurface == NULL)
            {

               pdisplaybase->m_windowmap.erase_item(m_pwlsurface);

               error() << "Can't create shell surface";

               throw ::exception(::error_failed);

            }
            else
            {

               information() << "Created shell surface";

            }

            xdg_surface_add_listener(m_pxdgsurface, &xdg_surface_listener, this);

         }


         ::i32 x = m_pointWindow.x();

         ::i32 y = m_pointWindow.y();

         ::i32 cx = m_sizeWindow.cx();

         ::i32 cy = m_sizeWindow.cy();

         if (is_windowing_popup())
         {

            m_pxdgpositioner = xdg_wm_base_create_positioner(pxdgwmbase);

            m_pointWindow = windowing_popup_origin();

            m_sizeWindow = windowing_popup_size();

            //x = m_pointWindow.x();

            //y = m_pointWindow.y();

            x = 0;

            y = 0;

            cx = m_sizeWindow.cx();

            cy = m_sizeWindow.cy();

            auto sizeScreen = m_pdisplaybase->get_main_screen_size();

            auto pwindowbaseParent = owner_window();

            ::rectangle_i32 rectangleAnchor;

            rectangleAnchor.set_dimension(
               -sizeScreen.cx(),
               -sizeScreen.cy(),
               sizeScreen.cx() * 3,
               sizeScreen.cy() * 3);

            information() << "xdg_positioner_set_anchor_rect : " << rectangleAnchor;

            xdg_positioner_set_anchor_rect(m_pxdgpositioner,
                                    rectangleAnchor.left(),
                                    rectangleAnchor.top(),
                                    rectangleAnchor.width(),
                                    rectangleAnchor.height());

            information() << "xdg_positioner_set_offset : " << m_pointWindow;

            xdg_positioner_set_offset(m_pxdgpositioner,
                                      sizeScreen.cx() + m_pointWindow.x(),
                                      sizeScreen.cy() + m_pointWindow.y());

            information() << "xdg_positioner_set_size : " << m_sizeWindow;

            xdg_positioner_set_size(m_pxdgpositioner,
                                    m_sizeWindow.cx(),
                                    m_sizeWindow.cy());

            information() << "xdg_positioner_set_anchor XDG_POSITIONER_ANCHOR_TOP_LEFT";

            xdg_positioner_set_anchor(m_pxdgpositioner, XDG_POSITIONER_ANCHOR_TOP_LEFT);

            ::pointer<window_base> pwindowOwner = owner_window();

            //         if(pwindowOwner->m_pwlsurface)
            //       {

            /* Assign the popup role */
            //data->shell_surface.xdg.roleobj.popup.popup = xdg_surface_get_popup(data->shell_surface.xdg.surface,
            //                                                                  focuseddata->shell_surface.xdg.surface,
            //                                                                data->shell_surface.xdg.roleobj.popup.positioner);

            m_pxdgpopup = xdg_surface_get_popup(m_pxdgsurface, pwindowOwner->m_pxdgsurface, m_pxdgpositioner);

            xdg_popup_add_listener(m_pxdgpopup, &popup_listener_xdg, this);

         }
         else
         {


            m_pxdgtoplevel = xdg_surface_get_toplevel(m_pxdgsurface);

            if (m_pxdgtoplevel == NULL)
            {

               pdisplaybase->m_windowmap.erase_item(m_pwlsurface);

               error() << "Can't create toplevel";

               throw ::exception(::error_failed);

            }
            else
            {

               information() << "Created toplevel";

            }

            xdg_toplevel_add_listener(m_pxdgtoplevel, &g_xdg_toplevel_listener, this);

         }


         //      information() << "m_pointWindow : " << m_pointWindow;
         //
         //      information() << "m_sizeWindow : " << m_sizeWindow;
         //
         //      information() << "x, y : " << x << ", " << y;
         //
         //      information() << "cx, cy : " << cx << ", " << cy;

         //m_pointWindow.x() = x;

         //m_pointWindow.y() = y;

         //auto x = m_pointWindowBestEffort.x();

         //auto y = m_pointWindowBestEffort.y();

         if (m_pxdgsurface)
         {

            informationf("xdg_surface_set_window_geometry x, y, cx, cy : %d, %d, %d, %d", x, y, cx, cy);

            xdg_surface_set_window_geometry(m_pxdgsurface, x, y, cx, cy);

         }

         //auto pimpl = m_puserinteractionimpl;


         if (m_pxdgtoplevel)
         {

            if (!is_satellite_window())
            {

               information() << "xdg_toplevel_set_app_id (1)";

               auto psystem = system();

               string strApplicationServerName = psystem->get_application_server_name();

               xdg_toplevel_set_app_id(m_pxdgtoplevel, strApplicationServerName);

            }

         }

         string strWindowText = get_window_text();

         //         if (strWindowText.has_char())
         //         {
         //
         //            strName = strWindowText;
         //
         //         }

         //}

         if (strWindowText.has_char())
         {

            information() << "xdg_toplevel_set_title (1)";

            xdg_toplevel_set_title(m_pxdgtoplevel, strWindowText);

         }

         m_timeLastConfigureRequest.Now();

         m_uLastRequestSerial = m_uLastConfigureSerial;

         information() << "wl_surface_commit (1)";

         wl_surface_commit(m_pwlsurface);

         //m_timeLastConfigureRequest += 1_s;

         while (!m_bXdgInitialConfigure)
         {

            //wl_display_flush(pdisplaybase->m_pwldisplay);

            information() << "wl_display_dispatch (!m_bXdgInitialConfigure)";

            wl_display_dispatch(pdisplaybase->m_pwldisplay);

            //wl_display_dispatch(pdisplaybase->m_pwldisplay);

            //wl_display_roundtrip(pdisplaybase->m_pwldisplay);

         }

      }


      void window_base::__unmap()
      {

         information() << "windowing_wayland::window_base::__unmap";

         if (m_pwlsurface != nullptr)
         {

            /* Detach any previous buffers before resetting everything, otherwise when
            * calling this a second time you'll get an annoying protocol error
            */
            wl_surface_attach(m_pwlsurface, NULL, 0, 0);
            wl_surface_commit(m_pwlsurface);

         }

         if (m_pxdgtoplevel != nullptr)
         {

            xdg_toplevel_destroy(m_pxdgtoplevel);

            m_pxdgtoplevel = nullptr;

         }

         if (m_pxdgpopup != nullptr)
         {

            xdg_popup_destroy(m_pxdgpopup);

            m_pxdgpopup = nullptr;

         }

         if (m_pxdgpositioner != nullptr)
         {

            xdg_positioner_destroy(m_pxdgpositioner);

            m_pxdgpositioner = nullptr;

         }

         if (m_pxdgsurface != nullptr)
         {

            xdg_surface_destroy(m_pxdgsurface);

            m_pxdgsurface = nullptr;

         }

         if (m_pwlsubsurface != nullptr)
         {

            wl_subsurface_destroy(m_pwlsubsurface);

            m_pwlsubsurface = nullptr;

         }

         if (m_pwlsurface != nullptr)
         {

            wl_surface_destroy(m_pwlsurface);

            m_pwlsurface = nullptr;

         }

         information() << "windowing_wayland::window_base::__unmap end";

      }


      void window_base::__handle_pointer_enter(::wl_pointer * pwlpointer)
      {

         m_pwlpointer = pwlpointer;

         //m_pointCursor2 = m_pointPointer;

      }


      void window_base::__handle_pointer_motion(::wl_pointer * pwlpointer, ::u32 millis)
      {

         m_pwlpointer = pwlpointer;

         //m_pointCursor2 = m_pointPointer;

         //      auto pmouse = __create_new<::message::mouse>();
         //
         //      pmouse->m_oswindow = this;
         //
         //      pmouse->m_pwindow = this;
         //
         //      pmouse->m_atom = e_message_mouse_move;
         //
         //      pmouse->m_pointHost = m_pointCursor2;
         //
         //      pmouse->m_pointAbsolute = m_pointCursor2;
         //
         //      pmouse->m_time.m_iSecond = millis / 1_k;
         //
         //      pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
         //
         //      //pwindow->message_handler(pmouse);
         //
         //      //wayland_windowing()->post_ui_message(pmouse);
         //
         //      m_puserinteractionimpl->message_handler(pmouse);

      }



      void window_base::__handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::nano::user::window_base * pwaylandwindowLeave)
      {

         auto pinterfaceclientparticle = get_interface_client_particle();

         if(pinterfaceclientparticle)
         {

            ::string strType = ::type(pinterfaceclientparticle).name();

            information() << "__handle_pointer_leave : " << strType;

         }

         m_pwlpointer = pwlpointer;

         //            if (msg.oswindow)
         //            {
         //
         //               ::minimum(m_pointCursor.x());
         //
         //               ::minimum(m_pointCursor.y());
         //
         //
         //               if(e.xcrossing.mode == NotifyUngrab)
         //               {
         //
         //                  information() << "X11 LeaveNotify NotifyUngrab";
         //
         //               }
         //
         ////            if(e.xcrossing.mode == NotifyUngrab)
         ////            {
         ////
         ////  //             MESSAGE msgCaptureChanged;
         ////
         //////               msgCaptureChanged.oswindow = m_pwindowCapture;
         ////               msg.m_atom = e_message_capture_changed;
         ////               msg.wParam = 0;
         ////               msg.lParam = (lparam) (oswindow) (msg.oswindow == m_pwindowCapture ? nullptr : m_pwindowCapture.m_p);
         ////               msg.time = e.xcrossing.time;
         ////
         ////               post_ui_message(msg);
         ////
         ////            }


         //
         //
         //      ::minimum(m_pointCursor2.x());
         //
         //      ::minimum(m_pointCursor2.y());
         //
         ////      MESSAGE msg;
         ////      msg.oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
         ////      msg.m_atom = e_message_mouse_leave;
         ////      msg.wParam = 0;
         ////      msg.lParam = 0;
         ////      //   msg.time = e.xcrossing.time;
         ////      msg.time = 0;
         ////
         ////      wayland_windowing()->post_ui_message(msg);
         //
         //      auto pmouse = __create_new<::message::mouse>();
         //
         //      pmouse->m_oswindow = ::is_set(pwaylandwindowLeave) ? pwaylandwindowLeave : this;
         //
         //      pmouse->m_pwindow = pmouse->m_oswindow;
         //
         //      pmouse->m_atom = e_message_mouse_leave;
         //
         //      pmouse->m_pointHost = m_pointCursor2;
         //
         //      pmouse->m_pointAbsolute = m_pointCursor2;
         //
         //      //pmouse->m_time.m_iSecond = millis / 1_k;
         //
         //      //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
         //
         //      //msg.wParam = 0;
         //
         //      //msg.lParam = make_i32(e.xbutton.x_root, e.xbutton.y_root);
         //
         //      //post_ui_message(msg);
         //      //wayland_windowing()->post_ui_message(pmouse);
         //
         //      m_puserinteractionimpl->message_handler(pmouse);
         //
         ////            }

      }


      void window_base::__handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 millis)
      {

         ::string strType = ::type(get_interface_client_particle()).name();



         m_pwlpointer = pwlpointer;

         //      enum_message emessage = e_message_undefined;
         //      //msg.m_atom = e_message_mouse_wheel;
         //
         //      //post_ui_message(pmouse);
         //
         //      bool bRet = true;
         //
         //      //msg.time = e.xbutton.time;
         //
         //      int Δ = 0;
         //
         //      if (pressed == WL_POINTER_BUTTON_STATE_PRESSED)
         //      {
         //
         //
         //         ::point_i32                                  m_pointWindowDragStart;
         //
         //
         //         if (linux_button == BTN_LEFT)
         //         {
         //
         //            information()
         //               << "LeftButtonDown";
         //
         //            emessage = e_message_left_button_down;
         //
         //         }
         //         else if (linux_button == BTN_MIDDLE)
         //         {
         //
         //            emessage = e_message_middle_button_down;
         //
         //         }
         //         else if (linux_button == BTN_RIGHT)
         //         {
         //
         //            emessage = e_message_right_button_down;
         //
         //         }
         //         else if (linux_button == BTN_GEAR_DOWN)
         //         {
         //
         //            Δ = 120;
         //
         //         }
         //         else if (linux_button == BTN_GEAR_UP)
         //         {
         //
         //            Δ = -120;
         //
         //         }
         //         else
         //         {
         //
         //            bRet = false;
         //
         //         }
         //
         //      }
         //      else if (pressed == WL_POINTER_BUTTON_STATE_RELEASED)
         //      {
         //
         //         if (linux_button == BTN_LEFT)
         //         {
         //
         //            information()
         //               << "LeftButtonUp";
         //
         //            emessage = e_message_left_button_up;
         //
         //         }
         //         else if (linux_button == BTN_MIDDLE)
         //         {
         //
         //            emessage = e_message_middle_button_up;
         //
         //         }
         //         else if (linux_button == BTN_RIGHT)
         //         {
         //
         //            emessage = e_message_right_button_up;
         //
         //         }
         //         else
         //         {
         //
         //            bRet = false;
         //
         //         }
         //
         //      }
         //      else
         //      {
         //
         //         bRet = false;
         //
         //      }
         //
         //      //m_pointCursor2 = m_pointPointer;
         //
         ////      MESSAGE msg;
         ////
         ////      msg.oswindow = this;
         ////
         ////      msg.oswindow->set_cursor_position(m_pointCursor);
         //
         //
         //
         ////      int l = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.x;
         ////      int t = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.y;
         ////      int w = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cx();
         ////      int h = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cy();
         ////
         ////      ::rectangle_i32 r;
         ////
         ////      window_rectangle(msg.oswindow, &r);
         ////
         ////      int l1 = r.left();
         ////      int t1 = r.top();
         ////      int w1 = r.width();
         ////      int h1 = r.height();
         //
         //      if (Δ != 0)
         //      {
         //
         //         auto pmousewheel = __create_new<::message::mouse_wheel>();
         //
         //         pmousewheel->m_oswindow = this;
         //
         //         pmousewheel->m_pwindow = this;
         //
         //         pmousewheel->m_atom = e_message_mouse_wheel;
         //
         //         //msg.wParam = make_i32(0, iDelta);
         //
         //         //msg.lParam = make_i32(e.xbutton.x_root, e.xbutton.y_root);
         //
         //         pmousewheel->m_Δ = Δ;
         //
         //         pmousewheel->m_pointHost = m_pointCursor2;
         //
         //         pmousewheel->m_pointAbsolute = m_pointCursor2;
         //
         //         pmousewheel->m_time.m_iSecond =millis / 1_k;
         //
         //         pmousewheel->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
         //
         //         //wayland_windowing()->post_ui_message(pmousewheel);
         //
         //         m_puserinteractionimpl->message_handler(pmousewheel);
         //
         //      }
         //      else if (bRet)
         //      {
         //
         //         auto pmouse = __create_new<::message::mouse>();
         //
         //         pmouse->m_oswindow = this;
         //
         //         pmouse->m_pwindow = this;
         //
         //         pmouse->m_atom = emessage;
         //
         //         pmouse->m_pointHost = m_pointCursor2;
         //
         //         pmouse->m_pointAbsolute = m_pointCursor2;
         //
         //         pmouse->m_time.m_iSecond = millis / 1_k;
         //
         //         pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
         //
         //         //msg.wParam = 0;
         //
         //         //msg.lParam = make_i32(e.xbutton.x_root, e.xbutton.y_root);
         //
         //         //post_ui_message(msg);
         //         //wayland_windowing()->post_ui_message(pmouse);
         //
         //         m_puserinteractionimpl->message_handler(pmouse);
         //
         //      }

      }


      void window_base::__defer_update_wayland_buffer()
      {

         if(m_uLastConfigureSerial && m_buffer.m_size != m_sizeWindow)
         {

            auto pdisplaybase = m_pdisplaybase;

            pdisplaybase->destroy_wayland_buffer(m_buffer);

            pdisplaybase->update_wayland_buffer(m_buffer, m_sizeWindow);

            //wl_surface_attach(m_pwlsurface, m_buffer.m_pwlbuffer, 0, 0);

            //m_puserinteractionimpl->m_puserinteraction->set_need_redraw();

            //m_puserinteractionimpl->m_puserinteraction->post_redraw();

         }
         //wl_surface_damage(surface, 0, 0, WIDTH, HEIGHT);
         //wl_surface_commit(m_pwlsurface);

      }


      void window_base::__defer_xdg_surface_ack_configure()
      {

         if(m_uLastAckSerial < m_uLastConfigureSerial)
         {

            m_uLastAckSerial = m_uLastConfigureSerial;

            xdg_surface_ack_configure(m_pxdgsurface, m_uLastAckSerial);

            ::string strType = ::type(get_interface_client_particle()).name();

            information()

               << "xdg_surface_ack_configure : " << m_uLastAckSerial;

         }

      }


      void window_base::__handle_xdg_surface_configure(::u32 serial)
      {

         ::string strType = ::type(get_interface_client_particle()).name();

         information()

            << "__handle_xdg_surface_configure : " << serial;

         if(!m_bXdgInitialConfigure)
         {

            m_bXdgInitialConfigure = true;

         }

         m_uLastConfigureSerial = serial;

         //      interface_client_set_need
         //
         //      auto puserinteractionimpl = m_puserinteractionimpl;
         //
         //      if(puserinteractionimpl)
         //      {
         //
         //         auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;
         //
         //         if(puserinteraction)
         //         {
         //
         //            puserinteraction->set_need_redraw();
         //
         //            puserinteraction->post_redraw();
         //
         //         }
         //
         //      }

         //
         //
         //      if(m_bFirstConfigure)
         //      {
         //
         //         m_bFirstConfigure = false;
         //
         //         __continue_initialization_after_configure();
         //
         //      }

      }


      void window_base::__handle_xdg_toplevel_configure(::i32 width, ::i32 height, ::wl_array * pwlarrayState)
      {

         ::string strType = ::type(get_interface_client_particle()).name();

         ::size_i32 size(width, height);

         information()

            << "__handle_xdg_toplevel_configure input size : " << size;

         if(size.cx() > 0)
         {

            m_sizeWindow.cx() = size.cx();

         }

         if(size.cy() > 0)
         {

            m_sizeWindow.cy() = size.cy();

         }

         m_sizeConfigure = m_sizeWindow;

         information()

            << "__handle_xdg_toplevel_configure effective size : " << m_sizeConfigure;

         if(pwlarrayState->size == 0)
         {

            information()

               << "pwlarrayState is EMPTY";

         }
         else
         {

            if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
            {

               information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_MAXIMIZED";

            }

            if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
            {

               information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_FULLSCREEN";

            }

            if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_ACTIVATED))
            {

               information() << "pwlarrayState contains XDG_TOPLEVEL_STATE_ACTIVATED";

               if(is_window_stored_iconic())
               {

                  ::string strType = ::type(get_interface_client_particle());

                  information() << "Window was iconic type : " << strType;

                  if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_MAXIMIZED))
                  {

                     //m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);

                     window_maximize();

                  }
                  else if (xdg_toplevel_state_array_contains(pwlarrayState, XDG_TOPLEVEL_STATE_FULLSCREEN))
                  {

                     //m_puserinteractionimpl->m_puserinteraction->display(::e_display_full_screen);

                     window_full_screen();

                  }
                  else
                  {

                     //m_puserinteractionimpl->m_puserinteraction->display(::e_display_normal);

                     window_restore();

                  }

               }

            }

         }

         set_interface_client_size(m_sizeConfigure);

      }


      void window_base::_update_window()
      {

         auto height = cairo_image_surface_get_height(m_pcairosurface);
         auto width = cairo_image_surface_get_width(m_pcairosurface);
         auto stride = cairo_image_surface_get_stride(m_pcairosurface);
         auto data = cairo_image_surface_get_data(m_pcairosurface);

         __defer_update_wayland_buffer();



         //         m_pwlcallbackFrame = wl_surface_frame(pwaylandwindow->m_pwlsurface);
         //         wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, this);

         //auto & pimage = pitem->m_pimage2;

         //pimage->map();

         ::copy_image32((::image32_t *) m_buffer.m_pdata,
                        m_buffer.m_size,
                        m_buffer.m_stride,
                        (const ::image32_t *) data, stride);

         information()

            << "_update_screen_unlocked data : "
            << (::iptr) m_buffer.m_pdata;
         //::memory_set(pwindow->m_buffer.m_pdata, 127,pitem->m_size.cx() * 4 * pitem->m_size.cy());
         //      m_pwlcallbackFrame = wl_surface_frame(pwindow->m_pwlsurface);
         wl_surface_attach(m_pwlsurface,
                           m_buffer.m_pwlbuffer, 0, 0);
         //       wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, NULL);
         wl_surface_damage(m_pwlsurface, 0, 0, width, height);


         __defer_xdg_surface_ack_configure();
         wl_surface_commit(m_pwlsurface);

      }




      bool window_base::_perform_entire_reposition_process()
      {

         //windowing()->windowing_post([this]()
         //                          {

         auto pxdgtoplevel = m_pxdgtoplevel;

         if(::is_set(pxdgtoplevel))
         {

            auto pwlseat = m_pdisplaybase->m_pwlseat;

            auto uSerial = m_pdisplaybase->m_uLastButtonSerial;

            xdg_toplevel_move(pxdgtoplevel, pwlseat, uSerial);

         }

         //                        });
         //      while (wl_display_dispatch(wayland_display()->m_pwldisplay) != -1)
         //      {
         //
         //
         //      }

         return true;

      }






      bool window_base::_perform_entire_resizing_process(::experience::enum_frame eframeSizing)
      {

         xdg_toplevel_resize_edge resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;

         copy(&resizeedge, &eframeSizing);

         if(resizeedge == XDG_TOPLEVEL_RESIZE_EDGE_NONE)
         {

            return true;

         }

         information() << "defer_perform_entire_resizing_process resizeedge : " << (::iptr) resizeedge;

         //windowing()->windowing_post([this, resizeedge]()
         //                          {

         if(::is_set(m_pxdgtoplevel))
         {

            m_resizeedge = resizeedge;

            xdg_toplevel_resize(
               m_pxdgtoplevel,
               m_pdisplaybase->m_pwlseat,
               m_pdisplaybase->m_uLastButtonSerial,
               resizeedge);

            //});
         }

         return true;

      }


      void window_base::__handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys)
      {

         m_bHasKeyboardFocus = true;

      }


      void window_base::__handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial)
      {

         m_bHasKeyboardFocus = false;

      }


      void window_base::__handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t pressed)
      {

         if (key < ARRAY_SIZE(xfree86_key_table2))
         {

            auto ekey = xfree86_key_table2[key];

            if(pressed == WL_KEYBOARD_KEY_STATE_PRESSED)
            {

               information() << "_on_simple_key_message e_message_key_down : " << ::as_string(ekey);

               _on_simple_key_message(ekey, e_message_key_down);

            }
            else
            {

               information() << "_on_simple_key_message e_message_key_up : " << ::as_string(ekey);

               _on_simple_key_message(ekey, e_message_key_up);

            }


         }

         auto pdisplaybase = m_pdisplaybase;

         if (!pdisplaybase->m_pxkbstate)
         {

            return;

         }

         const xkb_keysym_t *syms = nullptr;

         // TODO can this happen?
         if (::xkb_state_key_get_syms(pdisplaybase->m_pxkbstate, key + 8, &syms) != 1)
         {

            information() << "xkb_state_key_get_syms has failed";

            return;

         }

         if (pressed)
         {

            char text[8];

            auto size = ::xkb_keysym_to_utf8(syms[0], text, sizeof text);

            if (size > 0)
            {

               text[size] = 0;

               ::string strText(text);

               information() << "xkb_keysym_to_utf8 size : " << size << " and text : \"" << strText << "\"";

               for(::collection::index i = 0; i < size; i++)
               {

                  information() << "xkb_keysym_to_utf8 size ("  << i <<  ") : 0x" << ::hex::lower_case_from(text[i]);

               }

               if(!::is_control_character(strText))
               {

                  _on_text_composition(strText);

               }

               //            //Wayland_data_device_set_serial(input->data_device, serial);
               //
               //            auto pkey = __create_new<::message::key>();
               //
               //            pkey->m_oswindow = this;
               //
               //            pkey->m_pwindow = this;
               //
               //            pkey->m_atom = e_message_text_composition;
               //
               //            pkey->m_strText = text;
               //
               //            information() << "e_message_text_composition";
               //
               //            m_puserinteractionimpl->message_handler(pkey);

            }

         }

      }


      void window_base::_on_simple_key_message(::user::e_key ekey, ::enum_message emesssage)
      {

      }


      void window_base::_on_text_composition(const ::scoped_string & scopedstrText)
      {


      }


      void window_base::__handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
      {

         //::pointer < ::windowing_wayland::keyboard > pkeyboard = windowing()->keyboard();

         auto pdisplaybase = m_pdisplaybase;

         if (!pdisplaybase->m_pxkbstate)
         {

            return;

         }

         ::xkb_state_update_mask(pdisplaybase->m_pxkbstate, mods_depressed, mods_latched, mods_locked, 0, 0, group);

      }


      void window_base::_on_windowing_close_window()
      {



      }
   } // namespace user
} // namespace nano


} // namespace wayland



