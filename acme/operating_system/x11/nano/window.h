//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/user/nano/_nano.h"


#include <X11/Xutil.h>


namespace x11
{


   class CLASS_DECL_ACME nano_window :
      virtual public ::nano_window_implementation,
      virtual public event_listener
   {
   public:


      __pointer(class display)         m_pdisplay;
      Window                           m_window;
      Window                           m_windowRoot;
      cairo_surface_t *                m_psurface;
      __pointer(nano_device)           m_pnanodevice;
      int                              m_iDepth;
      XVisualInfo                      m_visualinfo;
      Visual *                         m_pvisual;
      Colormap                         m_colormap;
      //__pointer(nano_font)          m_pfont;
      //color32_t                     m_colorText;
      //color32_t                     m_colorFocus;
      //color32_t                     m_colorWindow;
      //string                        m_strTitle;
      //bool                          m_bNcActive;

      manual_reset_event              m_eventEnd;
      //rectangle_i32                 m_rectangle;
      //rectangle_i32                 m_rectangleClient;

      //__pointer_array(nano_child)   m_childa;
      //::atom                          m_atomLeftButtonDown;
      //::atom                          m_atomLeftButtonUp;
      //::atom                             m_atomResult;
      //__pointer(nano_child)         m_pchildFocus;


      nano_window();
      ~nano_window() override;


      ::nano::display * get_display() override;


      void on_initialize_object() override;

      void create() override;

      void destroy() override;

      void display() override;

      bool _on_event(XEvent *pevent) override;

      virtual void _update_window();

      //void message_loop() override;

      //virtual bool message_loop_step();

      virtual void _draw(nano_device * pnanodevice);

      //virtual void on_draw(nano_device * pnanodevice);

      void on_char(int iChar) override;

      bool is_active() override;

      void set_active() override;

      ///virtual void draw_children(nano_device * pnanodevice);

      void delete_drawing_objects() override;

      bool get_dark_mode() override;

      void create_drawing_objects() override;

      void update_drawing_objects() override;

      nano_child * hit_test(::user::mouse * pmouse) override;

      //virtual void add_child(nano_child * pchild);

      ::atom get_result() override;

      void on_mouse_move(::user::mouse * pmouse) override;

      void on_left_button_down(::user::mouse * pmouse) override;

      void on_left_button_up(::user::mouse * pmouse) override;

      void on_right_button_down(::user::mouse * pmouse) override;

      void on_right_button_up(::user::mouse * pmouse) override;

      void on_click(const ::atom & atom, ::user::mouse * pmouse) override;

      void on_right_click(const ::atom & atom, ::user::mouse * pmouse) override;

      //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

      void move_to(const ::point_i32 & point) override;

      void redraw() override;

      void get_client_rectangle(::rectangle_i32 & rectangle) override;

      void get_window_rectangle(::rectangle_i32 & rectangle) override;

      void set_capture() override;

      void release_capture() override;

      virtual void _wm_nodecorations(int iMap);


      //::size_i32 get_main_screen_size() override;


   };


} // namespace x11



