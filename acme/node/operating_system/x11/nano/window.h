//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/nano/_nano.h"


namespace x11
{


   class CLASS_DECL_ACME nano_window :
      virtual public ::nano_window
   {
   public:


      //HWND m_hwnd;
      __pointer(nano_font)          m_pfont;
      color32_t                     m_colorText;
      color32_t                     m_colorFocus;
      color32_t                     m_colorWindow;
      string                        m_strTitle;
      bool                          m_bNcActive;

      rectangle_i32                 m_rectangle;
      rectangle_i32                 m_rectangleClient;

      __pointer_array(nano_child)   m_childa;
      ::id                          m_idLeftButtonDown;
      ::id                          m_idLeftButtonUp;
      //::id                             m_idResult;
      __pointer(nano_child)         m_pchildFocus;


      nano_window();

      ~nano_window();

      virtual void create();

      virtual void display_synchronously();

      virtual void message_loop();

      virtual void _draw(nano_device * pnanodevice);

      //virtual void on_draw(nano_device * pnanodevice);

      virtual void on_char(int iChar);

      virtual bool is_active();

      ///virtual void draw_children(nano_device * pnanodevice);

      virtual void delete_drawing_objects();

      virtual bool get_dark_mode();

      virtual void create_drawing_objects();

      virtual void update_drawing_objects();

      virtual ::id hit_test(int x, int y);

      virtual void add_child(nano_child * pchild);

      virtual ::id get_result();

      virtual void on_mouse_move(int x, int y);

      virtual void on_left_button_down(int x, int y);

      virtual void on_left_button_up(int x, int y);

      virtual void on_click(const ::id & id);

      //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

      virtual void move_to(int x, int y);

      virtual void destroy();

      virtual void redraw();

      void get_client_rectangle(::rectangle_i32 & rectangle) override;

      void set_capture() override;

      void release_capture() override;


   };


} // namespace x11



