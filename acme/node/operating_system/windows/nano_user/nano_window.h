// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "nano_child.h"


class nano_window :
   virtual public ::conversation,
   virtual public ::user::drag_move_client
{
public:


   HWND                             m_hwnd;
   HBRUSH                           m_hbrushWindow;
   HPEN                             m_hpenBorder;
   HPEN                             m_hpenBorderFocus;
   HPEN                             m_hpenNull;
   HFONT                            m_hfont;
   COLORREF                         m_crText;
   COLORREF                         m_crFocus;
   COLORREF                         m_crWindow;
   string                           m_strTitle;
   bool                             m_bNcActive;

   rectangle_i32                    m_rectangle;
   rectangle_i32                    m_rectangleClient;

   __pointer_array(nano_child)      m_childa;
   ::id                             m_idLeftButtonDown;
   ::id                             m_idLeftButtonUp;
   //::id                             m_idResult;
   __pointer(nano_child)            m_pchildFocus;


   nano_window();
   ~nano_window();

   virtual void create();

   virtual void display_synchronously();

   virtual void message_loop();

   virtual void draw(HDC hdc);

   virtual void on_draw(HDC hdc);

   virtual void on_char(int iChar);

   virtual bool is_active();

   virtual void draw_children(HDC hdc);

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

   virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

   virtual void move_to(int x, int y);

   virtual void destroy();

   virtual void redraw();


};
