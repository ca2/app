//
// Created by camilo on 10/5/23 <3ThomasBorregaardSorensen!!
// Wayland implementation incoming from windowing_wayland on 2023-10-06
//
#pragma once


#include "_.h"
#include "acme/operating_system/wayland/_.h"
#include "acme/windowing/window_base.h"

#include <cairo/cairo.h>
namespace wayland
{

   namespace nano
   {
      namespace user
      {
         class window_base :
            virtual public ::windowing::window_base
         {
         public:


            ::pointer<class display_base>         m_pdisplaybase;


            cairo_surface_t *m_pcairosurface;

            xdg_toplevel_resize_edge m_resizeedge;
            buffer m_buffer;
            ::wl_surface * m_pwlsurface;
            ::wl_subsurface * m_pwlsubsurface;
            ::xdg_surface * m_pxdgsurface;
            ::xdg_toplevel * m_pxdgtoplevel;
            ::xdg_popup * m_pxdgpopup;
            ::xdg_positioner * m_pxdgpositioner;
            ::wl_pointer * m_pwlpointer;
            ::wl_shm_pool * m_pwlshmpool;
            ::point_i32 m_pointWindowBestEffort;
            ::xdg_activation_token_v1 * m_pxdgactivationtokenv1;
            ::wl_callback * m_pwlcallbackFrame;
            ::size_i32 m_sizeDrag;

            ::u32 m_uLastConfigureSerial;
            ::u32 m_uLastRequestSerial;
            ::u32 m_uLastAckSerial;
            ::string m_strActivationToken;
            ::size_i32                                      m_sizeConfigure;
            class ::time                                 m_timeLastConfigureRequest;
            bool                                         m_bXdgInitialConfigure;
            bool                                            m_bDoneFirstMapping;

            bool                                         m_bMessageOnlyWindow;
            bool                                         m_bHasKeyboardFocus;


            window_base();
            ~window_base() override;



            void destroy() override;


            virtual ::particle * get_interface_client_particle() = 0; // m_puserinteractionimpl->m_puserinteraction
            //virtual void set_window_width(::i32 iWidth) = 0; // m_sizeWindow.cx()
            //virtual void set_window_height(::i32 iHeight) = 0; // m_sizeWindow.cy()
            //virtual ::size_i32 get_window_size() = 0; // m_sizeWindow
            virtual void set_interface_client_size(const ::size_i32 & sizeWindow) = 0; // m_sizeWindow

            virtual bool is_window_stored_iconic() = 0; // m_puserinteractionimpl->m_puserinteraction->const_layout().window().display() == e_display_iconic
            virtual void window_maximize() = 0; // m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);
            virtual void window_full_screen() = 0; // m_puserinteractionimpl->m_puserinteraction->display(::e_display_full_screen);
            virtual void window_restore() = 0; // m_puserinteractionimpl->m_puserinteraction->display(::e_display_normal);


            virtual void __activate_window(bool bNormalPriority);


            virtual void __map();

            virtual void __unmap();


            virtual void __handle_pointer_enter(::wl_pointer * pwlpointer);
            virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, ::u32 millis);
            virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::nano::user::window_base * pwaylandwindowLeave);
            virtual void __handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 millis);


            virtual void __defer_update_wayland_buffer();

            virtual void __handle_xdg_surface_configure(::u32 serial);

            virtual void __handle_xdg_toplevel_configure(::i32 width, ::i32 height, ::wl_array * pwlarrayState);

            virtual void __defer_xdg_surface_ack_configure();


            virtual bool _perform_entire_reposition_process();

            virtual bool _perform_entire_resizing_process(::experience::enum_frame eframeSizing);

            //void on_destruct_mouse_message(::message::mouse * pmouse) override;


            virtual void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys);
            virtual void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial);
            virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
            virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);


            virtual void _on_simple_key_message(::user::e_key ekey, ::enum_message emesssage);
            virtual void _on_text_composition(const ::scoped_string & scopedstrText);
            virtual void _on_windowing_close_window();


            virtual void _update_window();


         };
      } // namespace user
   }// namespace nano

} // namespace wayland



