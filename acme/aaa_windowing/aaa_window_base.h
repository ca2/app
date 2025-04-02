//
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
// ::micro::window_implementation Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged from former ::micro::window_implementation by
//    camilo on 2024-0926 14:45 <3ThomasBorregaardSorensen!!
//
//
//
#pragma once


#include "acme/prototype/geometry2d/size.h"
#include "acme/user/user/element.h"


namespace windowing
{


   class CLASS_DECL_ACME window_base :
      virtual public ::user::element
   {
   public:



      bool                                               m_bRepositioningWindowFromCenter;
      bool                                               m_bResizingWindowFromBottomRight;
      ::int_point                                        m_pointWindow;
      ::int_size                                         m_sizeWindow;
      ::int_point                                        m_pointCursor2;

      ::pointer < ::operating_system::a_system_menu >    m_psystemmenu;

      ::pointer < ::acme::user::interaction >             m_puserinteractionbase;

      ::pointer < ::acme::windowing::display >                m_pdisplaybase;


      window_base();
      ~window_base() override;


      ::acme::user::interaction * user_interaction_base() override;
      ::acme::windowing::window * windowing_window_base() override;


      void on_initialize_particle() override;


      void destroy() override;


      virtual bool is_windowing_popup();
      virtual ::int_point windowing_popup_origin();
      virtual ::int_size windowing_popup_size();
      virtual void _on_windowing_close_window();
      virtual bool is_satellite_window();
      virtual window_base * owner_window();
      ::string get_window_text() override;


      ///::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true) override;

      bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

      bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;


      virtual void on_char(int iChar);
//       //
//       // Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
//       //
// #pragma once
//
//
// #include "window_interface.h"
// #include "acme/user/user/element.h"
//
//
//       namespace nano
//       {
//
//
//          namespace user
//          {
//
//
//             class CLASS_DECL_ACME window_implementation :
//                virtual public ::user::element
//             {
//             public:
//

               //
               // window_implementation();
               // ~window_implementation() override;


               virtual ::acme::windowing::display * get_display();


               //void draw(::nano::graphics::device * pnanodevice) override;

               //static ::pointer_array < ::micro::window_implementation > & nanowindowimplementationa();



               //bool get_dark_mode() override;
               //bool is_active() override;

               //virtual void nano_window_on_create();

      virtual void create_window();
      virtual void _create_window();

               void on_create_window() override;

               virtual void nano_window_on_destroy();

               //virtual void _console_create();

               //virtual void _display_console();


      virtual void show_window();
      virtual void hide_window();

      virtual void message_loop();

      virtual void set_active_window();

      virtual bool is_active_window();

               virtual ::int_point try_absolute_mouse_position(const ::int_point & point);


               void handle(::topic * ptopic, ::handler_context * pcontext) override;


               virtual ::int_size get_main_screen_size();


      void _on_window_simple_action(const char * pszActionName) override;


               //virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
               //virtual void do_asynchronously() override;


               virtual void defer_show_system_menu(::user::mouse * pmouse);

               virtual void implementation_message_loop_step();



      virtual void set_interface_client_size(const ::int_size & sizeWindow);


      void set_rectangle(const int_rectangle &rectangle) override;
      void set_position(const int_point &point) override;
      void set_size(const int_size &size) override;


      ::int_rectangle get_window_rectangle() override;
      virtual ::int_rectangle get_window_rectangle_unlocked();


      virtual void set_rectangle_unlocked(const int_rectangle &rectangle);
      virtual void set_position_unlocked(const int_point &point);
      virtual void set_size_unlocked(const int_size &size);


      virtual void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem);


   };


} // namespace windowing
