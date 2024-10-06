//
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
#pragma once


//#include "acme/platform/conversation_message.h"
//#include "acme/user/user/drag_client.h"
//#include "acme/user/user/interaction_base.h"
//#include "acme/prototype/geometry2d/rectangle.h"
//#include "acme/user/user/item.h"

#include "acme/user/user/element.h"

namespace nano
{


   namespace windowing
   {


      class CLASS_DECL_ACME window :
         virtual public ::user::element
         //virtual public ::conversation_message
      {
      public:


         ::function < void(::nano::user::interaction *) >        m_functionClose;

         ::pointer < ::nano::windowing::window >                m_pwindowOwner;

         //::pointer<::nano::user::window_implementation>     m_pnanouserwindowimplementation;
         bool                                      m_bNcActive;

         rectangle_i32                             m_rectangle;

         bool                                      m_bMinimizeBox;
         bool                                      m_bMaximizeBox;
         bool                                      m_bResizeable;
         //bool                                      m_bTopMost;
         // bool                                      m_bStartCentered;
         //bool                                      m_bArbitraryPositioning;


         bool                                      m_bCapture;
         bool                                      m_bStartCentered;
         bool                                      m_bArbitraryPositioning;

         bool                                      m_bTopMost;


         //pointer_array < ::nano::user::button >             m_nanobuttona;
         ::collection::index                                   m_iDefaultButton = -1;

         //map < const ::item *, ::user::item >      m_useritemmap;

         bool                                               m_bRepositioningWindowFromCenter;
         bool                                               m_bResizingWindowFromBottomRight;
         ::point_i32                                        m_pointWindow;
         ::size_i32                                         m_sizeWindow;
         ::point_i32                                        m_pointCursor2;

         ::pointer < ::operating_system::a_system_menu >    m_psystemmenu;

         ::pointer < ::nano::user::interaction >            m_pnanouserinteraction;
         ::pointer<::nano::user::interaction>               m_pnanouserinteractionFocus;
         ::pointer<::nano::user::interaction>               m_pnanouserinteractionHover;
         ::pointer<::nano::user::interaction>               m_pnanouserinteractionCapture;

         ::pointer < ::nano::windowing::display >           m_pdisplay;

         ::pointer < ::nano::windowing::window >            m_pnanowindowingwindowOwner;



         window();
         ~window() override;


         //virtual void do_interchange();




         //virtual ::pointer < item_container > item_form();

         void on_initialize_particle() override;




         //bool defer_perform_entire_reposition_process() override;

         bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

         bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;




         virtual ::point_i32 origin();

         void set_position(const ::point_i32 & point) override;

         ::rectangle_i32 get_window_rectangle() override;

         void on_create_window() override;

         void destroy() override;

         void redraw() override;


         void set_interaction_rectangle(const ::rectangle_i32 & rectangle) override;

         ::rectangle_i32 get_interaction_rectangle() override;


         //void get_window_rectangle() override;

         void set_capture() override;

         bool has_capture() override;

         void release_capture() override;

         void set_cursor(enum_cursor ecursor) override;




         ::pointer<::nano::graphics::device>create_device();


         void _run_modal_loop() override;


         //::atom do_synchronously() override;


         void handle(::topic * ptopic, ::context * pcontext) override;


         //::user::item & user_item(const ::item * pitem) override;


         /// Merged from window_base by camilo on
         ///    2024-10-05 11:09 <3ThomasBorregaardSorensen!!
         /// 
         /// 


         //interchange();
         //~interchange() override;


         ::nano::user::interaction * nano_user_interaction() override;
         ::nano::windowing::window * nano_windowing_window() override;


         //void on_initialize_particle() override;


         //void destroy() override;

         virtual ::payload do_synchronously(const class time & timeWait);
         virtual void do_asynchronously();


         virtual bool is_windowing_popup();
         virtual ::point_i32 windowing_popup_origin();
         virtual ::size_i32 windowing_popup_size();
         virtual void _on_windowing_close_window();
         virtual bool is_satellite_window();
         virtual ::nano::windowing::window * owner_window();
         ::string get_window_text() override;


         //virtual ::rectangle_i32 get_window_rectangle();

         ///::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true) override;

         //bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

         //bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;


         //virtual void on_char(int iChar);
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


         virtual ::nano::windowing::display * get_display();


         //void draw(::nano::graphics::device * pnanodevice) override;

         //static ::pointer_array < ::nano::user::window_implementation > & nanowindowimplementationa();



         //bool get_dark_mode() override;
         //bool is_active() override;

         //virtual void nano_window_on_create();

         virtual void create_window();
         virtual void _create_window();

         //void on_create_window() override;

         virtual void nano_window_on_destroy();

         //virtual void _console_create();

         //virtual void _display_console();

         virtual void on_position_window();
         virtual void on_size_window();

         virtual void show_window();
         virtual void hide_window();

         virtual bool is_window_zoomed();
         virtual void window_minimize();
         virtual void window_maximize(); // m_puserinteractionimpl->m_puserinteraction->display(::e_display_zoomed);
         virtual void window_full_screen(); // m_puserinteractionimpl->m_puserinteraction->display(::e_display_full_screen);
         virtual void window_restore(); // m_puserinteractionimpl->m_puserinteraction->display(::e_display_normal);
         virtual void window_close();
         //virtual void show_window();
         //virtual void hide_window();

         //virtual void message_loop();

         virtual void set_active_window();

         virtual bool is_active_window();

         //virtual ::point_i32 try_absolute_mouse_position(const ::point_i32 & point);


         //void handle(::topic * ptopic, ::context * pcontext) override;


         virtual ::size_i32 get_main_screen_size();


         void _on_window_simple_action(const char * pszActionName) override;


         //virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
         //virtual void do_asynchronously() override;


         virtual void defer_show_system_menu(::user::mouse * pmouse);

         virtual void window_message_loop_step();

         virtual void window_message_loop();



         virtual void set_interface_client_size(const ::size_i32 & sizeWindow);


         void set_rectangle(const rectangle_i32 & rectangle) override;
         //void set_position(const point_i32 & point) override;
         void set_size(const size_i32 & size) override;


         //::rectangle_i32 get_window_rectangle() override;
         virtual ::rectangle_i32 get_window_rectangle_unlocked();


         virtual void set_rectangle_unlocked(const rectangle_i32 & rectangle);
         virtual void set_position_unlocked(const point_i32 & point);
         virtual void set_size_unlocked(const size_i32 & size);


         virtual void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem);



      };


   } // namespace user


} // namespace nano



