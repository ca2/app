// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSørensen
#pragma once


namespace windows
{


   class nano_window :
      virtual public ::nano_window_implementation
   {
   public:


      //CreatableFromBase(nano_window, ::nano_window_implementation);


      HWND m_hwnd;
      bool m_bDestroy;
//      HFONT m_hfont;
//      COLORREF m_crText;
//      COLORREF m_crFocus;
//      COLORREF m_crWindow;
//      string m_strTitle;
//      bool m_bNcActive;

//      rectangle_i32 m_rectangle;
//      rectangle_i32 m_rectangleClient;
//
//      __pointer_array(nano_child) m_childa;
//      ::atom m_atomLeftButtonDown;
//      ::atom m_atomLeftButtonUp;
//      //::atom                             m_atomResult;
//      __pointer(nano_child) m_pchildFocus;


      nano_window();

      ~nano_window() override;

      void create() override;

      void display_synchronously() override;

      void message_loop() override;

      virtual void _draw(HDC hdc);

      //void on_draw(nano_device * pnanodevice) override;

      void on_char(int iChar) override;

      //bool is_active() override;

      //virtual void draw_children(nano_device * pnanodevice);

      void delete_drawing_objects() override;

      bool get_dark_mode() override;

      void create_drawing_objects() override;

      void update_drawing_objects() override;

      nano_child * hit_test(int x, int y) override;

      void add_child(nano_child * pchild) override;

      ::atom get_result() override;

      void on_mouse_move(int x, int y) override;

      void on_left_button_down(int x, int y) override;

      void on_left_button_up(int x, int y) override;

      void on_click(const ::atom & atom, int x, int y) override;

      void on_right_button_down(int x, int y) override;

      void on_right_button_up(int x, int y) override;

      void on_right_click(const ::atom & atom, int x, int y) override;

      virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

      void move_to(int x, int y) override;

      void destroy() override;

      void redraw() override;


      void get_client_rectangle(::rectangle_i32 & rectangle) override;

      void get_window_rectangle(::rectangle_i32 & rectangle) override;

      void set_capture() override;

      bool has_capture() const override;

      void release_capture() override;

      void set_cursor(enum_cursor ecursor) override;
      
      static bool _is_light_theme();


   };


} // namespace windows



