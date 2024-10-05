//
// // Created from nano::user::interchange by
// // camilo on 2024-10-05 16:52 <3ThomasBorregaardSorensen!!
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
// 
// // // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:07 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->nano::user::user
// //   (acme)windowing::window_base
// //       ---->nano::user::interchange
//
// Child merged into interaction on 2024-10-05 05:15 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
// 

#pragma once


#include "acme/user/user/interaction_base.h"


namespace nano
{


   namespace user
   {


      class CLASS_DECL_ACME interaction :
         virtual public ::user::interaction_base
      {
      public:


         string                                    m_strText;
         ::atom                                    m_atom;
         rectangle_i32                             m_rectangle;
         enum_font                                 m_efont;


         interaction();
         ~interaction();

         ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
         void do_asynchronously() override;


         virtual ::nano::user::theme * nano_user_theme();

         virtual enum_font nano_user_font();

         void create() override;

         void show_window() override;

         void hide_window() override;

         void message_loop() override;

         void draw(::nano::graphics::device * pnanodevice) override;

         void on_draw(::nano::graphics::device * pnanodevice) override;

         void on_char(int iChar) override;

         bool is_active() override;
         void set_active() override;

         void draw_children(::nano::graphics::device * pnanodevice) override;

         void delete_drawing_objects() override;
         bool get_dark_mode() override;

         void create_drawing_objects() override;
         void update_drawing_objects() override;

         ::point_i32 try_absolute_mouse_position(const ::point_i32 & point) override;


         ::point_i32 origin() override;

         ::payload get_result() override;

         void on_mouse_move(::user::mouse * pmouse) override;
         void on_left_button_down(::user::mouse * pmouse) override;
         void on_left_button_up(::user::mouse * pmouse) override;
         void on_click(const ::payload & payload, ::user::mouse * pmouse) override;
         void on_right_button_down(::user::mouse * pmouse) override;
         void on_right_button_up(::user::mouse * pmouse) override;
         void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;


         void get_client_rectangle(::rectangle_i32 & rectangle) override;


         /// @brief  Child
         /// @param pnanodevice 
         //virtual void on_draw(::nano::graphics::device * pnanodevice);
         //virtual void on_char(int iChar);
         virtual void set_focus();
         virtual bool is_focusable();
         //virtual void on_mouse_move(::user::mouse * pmouse);
         virtual void set_capture();
         virtual bool has_capture();
         virtual void release_capture();


         virtual void resize_to_fit();


         //virtual void display_temporary_file_with_text(const ::string & str);


      };


   } // namespace user


} // namespace nano



