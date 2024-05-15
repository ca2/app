//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/display.h"
#include "event_listener.h"
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include "acme/operating_system/xcb/_.h"
// dnf install xcb-util-image-devel
#include <xcb/xcb_image.h>
#include <xcb/render.h>
// apt install libx11-xcb-dev
#include <X11/Xlib-xcb.h>


#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property



namespace xcb
{

namespace nano
{
   namespace user
   {
      template < typename TYPE >
      using visual_id_map = map < xcb_visualid_t, TYPE >;

      using visual_pictformat_map = visual_id_map < xcb_render_pictformat_t >;

      using visual_depth_map = visual_id_map < uint32_t >;

      template < typename TYPE >
      using pictformat_map = map < xcb_render_pictformat_t, TYPE >;

      using pictformat_info_map = pictformat_map < const xcb_render_pictforminfo_t * >;



      class window;


      class display :
         virtual public ::nano::user::display,
         virtual public event_listener
      {
      public:


         bool                                   m_bUnhook;
         void *                                 m_pX11Display;
         xcb_connection_t   *                   m_pconnection;
         pointer_array < event_listener >        m_eventlistenera;
         pointer_array < nano::user::window >           m_windowa;
         xcb_window_t                           m_windowActive;
         //::procedure_array                        m_routineaPost;
         xcb_depth_t *                          m_pdepth;
         xcb_visualtype_t *                     m_pvisualtype;
         xcb_screen_t *                         m_pscreen;
         xcb_colormap_t                         m_colormap;
         xcb_window_t                           m_windowRoot;
         xcb_window_t                           m_windowHelper;
         xcb_atom_t                             m_atoma[::x11::e_atom_count];

         acme::malloc < xcb_render_query_pict_formats_reply_t * > m_prender_query_pict_formats_reply2;
         visual_pictformat_map                                    m_mapVisualPictFormat;
         visual_depth_map                                         m_mapVisualDepth;
         //map < xcb_visualid_t, FbConfigInfo * >                 m_mapVisualFbConfig;
         pictformat_info_map                                      m_mapFormatInfo;

         static display *                       g_p;


         display();
         ~display() override;


         static display * get();


         virtual xcb_atom_t intern_atom(const ::scoped_string & scopedstrAtomName, bool bCreate = true);
         virtual xcb_atom_t intern_atom(::x11::enum_atom eatom, bool bCreate = true);


         virtual long _window_get_long_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type);
         virtual ::e_status _change_window_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type, int mode, int format, int nelements, const void * data);



         virtual xcb_window_t _get_active_window();



         ::e_status _select_input(xcb_window_t window, i32 iInput);


         //void wait_timer_or_event();

         static display * get(::particle * pparticle, bool bBranch = true, void * pX11Display = nullptr, void * pXcbConnection = nullptr);

         bool message_loop_step();
         void message_loop();

         void init_task() override;

         void run() override;


         bool is_branch_current() const override;


         void add_listener(event_listener * plistener);
         void add_window(nano::user::window * pwindow);

         void erase_listener(event_listener * plistener);
         void erase_window(nano::user::window * pwindow);

         bool _on_event(xcb_generic_event_t * pevent) override;

         virtual bool xcb_event(xcb_generic_event_t * pevent);

         virtual bool xcb_posted();

         //void aaa_display_post(const ::procedure & procedure) override;
         //void aaa_display_send(const ::procedure & procedure);
         //bool aaa_display_posted_routine_step();


         virtual ::e_status _request_check(xcb_void_cookie_t cookie);


         ::e_status _send_client_event(xcb_window_t window1, xcb_window_t window2, xcb_atom_t atom, unsigned int numArgs, ...);

         ::e_status _send_client_event_v(xcb_window_t window1, xcb_window_t window2, xcb_atom_t atom, unsigned int numArgs, va_list argList);


         virtual ::e_status _set_active_window(xcb_window_t window);


         virtual ::e_status _map_window(xcb_window_t window);
         virtual ::e_status _unmap_window(xcb_window_t window);
         virtual ::e_status _raise_window(xcb_window_t window);
         virtual ::e_status _lower_window(xcb_window_t window);


         virtual comparable_array < xcb_atom_t > _list_atom(xcb_window_t window, xcb_atom_t atomList);
         virtual bool _has_net_wm_state(xcb_window_t window, xcb_atom_t propertyItem);
         virtual bool _list_has_atom(xcb_window_t window, xcb_atom_t propertyList, xcb_atom_t propertyItem);
         virtual ::e_status _list_add_atom(xcb_window_t window, xcb_atom_t atomList, xcb_atom_t atomFlag);
         virtual ::e_status _list_erase_atom(xcb_window_t window, xcb_atom_t atomList, xcb_atom_t atomFlag);

         virtual ::e_status _clear_net_wm_state(xcb_window_t window);

         virtual ::e_status _add_net_wm_state_below(xcb_window_t window);
         virtual ::e_status _add_net_wm_state_above(xcb_window_t window);
         virtual ::e_status _add_net_wm_state_hidden(xcb_window_t window);
         virtual ::e_status _add_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState);
         virtual ::e_status _mapped_add_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState);
         virtual ::e_status _unmapped_add_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState);

         virtual ::e_status _erase_net_wm_state_below(xcb_window_t window);
         virtual ::e_status _erase_net_wm_state_above(xcb_window_t window);
         virtual ::e_status _erase_net_wm_state_hidden(xcb_window_t window);
         virtual ::e_status _erase_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState);
         virtual ::e_status _mapped_erase_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState);
         virtual ::e_status _unmapped_erase_net_wm_state(xcb_window_t window, ::x11::enum_atom eatomNetWmState);



         virtual ::e_status _destroy_window(xcb_window_t window);


         virtual ::e_status _move_window(xcb_window_t window, int x, int y);


         virtual ::e_status _set_mouse_capture(xcb_window_t window);
         virtual ::e_status _release_mouse_capture();


         virtual ::e_status _get_window_attributes(xcb_get_window_attributes_reply_t * pattributes, xcb_window_t window);
         virtual ::e_status _get_window_geometry(xcb_get_geometry_reply_t * pgeometry, xcb_window_t window);


         virtual ::e_status _set_nodecorations(xcb_window_t window, int bMap);


         void kick_idle() override;


         ::size_i32 get_main_screen_size() override;


      };
   } // namespace user
} // namespace nano

} // namespace xcb



