//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/window_implementation.h"
#include "event_listener.h"
#include "acme/parallelization/manual_reset_happening.h"
#include <cairo/cairo.h>


namespace xcb
{


   namespace nano
   {
      namespace user
      {
         class CLASS_DECL_ACME window :
            virtual public ::micro::window_implementation,
            virtual public event_listener
         {
         public:


            ::pointer<class display>        m_pdisplay;
            xcb_window_t                    m_window;
            cairo_surface_t *               m_psurface;
            ::pointer<::nano::graphics::device>         m_pnanodevice;
            //::pointer<::nano::graphics::font>         m_pfont;
            //color32_t                     m_colorText;
            //color32_t                     m_colorFocus;
            //color32_t                     m_colorWindow;
            //string                        m_strTitle;
            //bool                          m_bNcActive;

            manual_reset_happening              m_eventEnd;
            //int_rectangle                 m_rectangle;
            //int_rectangle                 m_rectangleX;

            //pointer_array < ::micro::child >   m_childa;
            //::atom                          m_atomLeftButtonDown;
            //::atom                          m_atomLeftButtonUp;
            //::atom                             m_atomResult;
            //::pointer<::micro::child>        m_pchildFocus;


            window();
            ~window() override;


            ::acme::windowing::display * get_display() override;


            void on_initialize_particle() override;

            void create() override;

            void destroy() override;

            void display() override;

            bool _on_event(xcb_generic_event_t *pevent) override;

            virtual void _update_window();

            ::e_status _map_window();
            ::e_status _unmap_window();

            ::e_status _raise_window();

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual void _draw(::nano::graphics::device * pnanodevice);

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            void on_char(int iChar) override;

            bool is_active() override;

            void set_active() override;

            ///virtual void draw_children(::nano::graphics::device * pnanodevice);

            void delete_drawing_objects() override;

            bool get_dark_mode() override;

            void create_drawing_objects() override;

            void update_drawing_objects() override;

            ::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::micro::child * pchild);

            ::atom get_result() override;

            void on_mouse_move(::user::mouse * pmouse) override;

            void on_left_button_down(::user::mouse * pmouse) override;

            void on_left_button_up(::user::mouse * pmouse) override;

            void on_right_button_down(::user::mouse * pmouse) override;

            void on_right_button_up(::user::mouse * pmouse) override;

            void on_click(const ::atom & atom, ::user::mouse * pmouse) override;

            void on_right_click(const ::atom & atom, ::user::mouse * pmouse) override;

            //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

            void move_to(const ::int_point & point) override;

            void redraw() override;

            void get_client_rectangle(::int_rectangle & rectangle) override;

            void get_window_rectangle(::int_rectangle & rectangle) override;

            void set_capture() override;

            void release_capture() override;

            virtual void _wm_nodecorations(int iMap);

            virtual void _get_geometry(xcb_get_geometry_reply_t * pgeometry);


            //::int_size get_main_screen_size() override;


         };
      }//namespace user
   }//namespace nano


} // namespace xcb



