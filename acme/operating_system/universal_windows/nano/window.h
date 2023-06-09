//
// From acme/user/nano/window by camilo on 2022-03-11 14:42 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/nano/window_implementation.h"
#include <winrt/Windows.UI.Popups.h>


namespace universal_windows
{


   class CLASS_DECL_ACME nano_window :
      virtual public ::nano_window_implementation
   {
   public:


      ::winrt::Windows::UI::Popups::MessageDialog     m_messagedialog = nullptr;
   

      nano_window();
      ~nano_window() override;


      //void on_initialize_particle() override;

      void create() override;

      void display() override;

      //void message_loop() override;

      //void draw(nano_device * pnanodevice) override;

      //void on_draw(nano_device * pnanodevice) override;

      //void on_char(int iChar) override;

      //bool is_active() override;
      //void set_active() override;

      //void draw_children(nano_device * pnanodevice) override;

      //void delete_drawing_objects() override;
      //bool get_dark_mode() override;

      //void create_drawing_objects() override;
      //void update_drawing_objects() override;

      //::nano_child * hit_test(int x, int y) override;
      //void add_child(nano_child * pchild) override;
      //nano_child * get_child_by_id(const ::atom & atom);

      //::atom get_result() override;

      //void on_mouse_move(int x, int y) override;
      //void on_left_button_down(int x, int y) override;
      //void on_left_button_up(int x, int y) override;
      //void on_click(const ::atom & atom, int x, int y) override;
      //void on_right_button_down(int x, int y) override;
      //void on_right_button_up(int x, int y) override;
      //void on_right_click(const ::atom & atom, int x, int y) override;

      //void move_to(int x, int y) override;

      //virtual void on_create();

      //void destroy() override;

      //void redraw() override;

      //void get_client_rectangle(::rectangle_i32 & rectangle) override;

      //void get_window_rectangle(::rectangle_i32 & rectangle) override;

      //void set_capture() override;

      //bool has_capture() const override;

      //void release_capture() override;

      //void set_cursor(enum_cursor ecursor) override;


      //void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult);


      //void display_temporary_file_with_text(const ::string & str);


      //::pointer<nano_device>create_device();


   };


} // namespace universal_windows



