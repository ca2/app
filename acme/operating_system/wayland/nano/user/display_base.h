//
// Created by camilo on 10/6/23 <3ThomasBorregaardSorensen!!
// From windowing_wayland on 2023-10-06
//
#pragma once


#include "_.h"
#include "acme/operating_system/wayland/xkb_input.h"
#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/primitive/geometry2d/size_array.h"
#include "acme/nano/user/display.h"


namespace wayland
{


    namespace nano
    {
        namespace user
        {
            class display_base :
               virtual public ::nano::user::display,
               virtual public ::xkb_input::xkb_input
            {
            public:



                critical_section                             m_criticalsectionWindowMap;

                window_map                                   m_windowmap;

                bool                                         m_bOpened;

                ::wl_display *                               m_pwldisplay;

                bool                                         m_bOwnDisplay;

                //::wl_display * m_pwldisplay;
                ::wl_shm *m_pwlshm;
                ::xdg_wm_base *m_pxdgwmbase;
                ::wl_compositor * m_pwlcompositor;
                ::wl_surface *       m_pwlsurfaceCursor;
                ::wl_seat *             m_pwlseat;
                ::wl_keyboard * m_pwlkeyboard;
                ::wl_pointer * m_pwlpointer;
                ::wl_subcompositor * m_pwlsubcompositor;
                //::wl_shm_pool * m_pwlshmpool;
                ::wl_surface * m_pwlsurfacePointerEnter;
                ::wl_surface * m_pwlsurfaceLastLButtonDown;
                ::wl_surface * m_pwlsurfaceMouseCapture;
                ::xdg_surface * m_pxdgsurfaceMouseCapture;
                ::xdg_toplevel * m_pxdgtoplevelMouseCapture;
                buffer m_bufferMouseCapture;
                bool m_bMouseCaptured ;
                ::rectangle_i32 m_rectangleMouseCapture;
                ::u32 m_uLastButtonSerial;
                ::u32 m_uLastPointerSerial;
                ::u32 m_uLastSeatSerial;
                ::u32 m_uLastKeyboardSerial;
                ::u32 m_uLastKeyboardEnterSerial;
                ::u32 m_uLastKeyboardLeaveSerial;
                ::gtk_shell1 * m_pgtkshell1;
                ::xdg_activation_v1 *m_pxdgactivationv1;
                //::wl_keyboard * m_pwlkeyboard;
                ::wl_surface * m_pwlsurfaceKeyboardEnter;
                ::comparable_array < ::wl_output * > m_wloutputa;
                ::size_i32_array                       m_sizeaMonitor;
                //::comparable_array < ::xdg_output * > m_xdgoutputa;

                //::point_f64 m_pointPointer;

                //::u32 m_uLastPointerButton;
                //::u32 m_uLastPointerState;

                ::pointer < ::wayland::nano::user::window_base > m_pwindowPointerEnter;
                ::pointer < ::wayland::nano::user::window_base > m_pwindowPointerCapture;
                ::pointer < ::wayland::nano::user::window_base > m_pwindowKeyboardFocus;


                static display_base * s_pdisplaybase;


                display_base();
                ~display_base() override;


                static display_base * get(::particle * pparticle, bool bBranch = true, ::wl_display * pwldisplay = nullptr);


                void initialize(::particle * pparticle) override;


                virtual ::wl_display * __get_wayland_display();


                virtual void open();
                virtual void close();


                void init_task() override;


                virtual ::wl_display * _wl_display();

                virtual ::wl_display * _wl_display() const;

                virtual ::wl_surface * _wl_surface_focus();


                virtual ::wayland::nano::user::window_base * get_keyboard_focus();

                virtual ::wayland::nano::user::window_base * _get_keyboard_focus();

                virtual ::wayland::nano::user::window_base * _get_active_window(::thread * pthread);


                virtual ::wayland::nano::user::window_base * _window(::wl_surface * pwlsurface);


                virtual bool message_loop_step();

                //      //void add_listener(event_listener * plistener);
                //      void add_window(nano_window_base * pwindow);
                //
                //      //void erase_listener(event_listener * plistener);
                //      void erase_window(nano_window_base * pwindow);

                void destroy_wayland_buffer(buffer & waylandbuffer);
                void update_wayland_buffer(buffer & waylandbuffer, const ::size_i32 & size);
                void update_wayland_buffer(buffer & waylandbuffer, ::pixmap * ppixmap);


                //virtual void __handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::wayland::nano::user::window_base * pwindowPointerEnter);
                virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, ::u32 time);
                virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::nano::user::window_base * pwindowPointerLeave);

                virtual void __handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 time);


                //virtual void __capture_mouse(::windowing_wayland::window * pwindowMouseCapture, ::u32 serial);


                virtual void __handle_keyboard_keymap(struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);
                virtual void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface, ::wl_array *pwlarrayKeys);
                virtual void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface);
                virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
                virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);

                virtual void __handle_wl_output_geometry(::wl_output *pwloutput,
                                        int32_t x,
                                        int32_t y,
                                        int32_t physical_width,
                                        int32_t physical_height,
                                        int32_t subpixel,
                                        const char *make,
                                        const char *model,
                                        int32_t transform);


                virtual void __handle_wl_output_mode(
                                    ::wl_output *pwloutput,
                                    uint32_t flags,
                                    int32_t width,
                                    int32_t height,
                                    int32_t refresh);

                virtual void message_loop();

                void run() override;


                void __handle_pointer_enter(struct wl_pointer * pwlpointer,
                                     uint32_t serial, struct wl_surface * pwlsurface,
                                     double x, double y);



            };
        } // namespace user
    } // namespace nano


} //  namespace wayland




