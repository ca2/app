//
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
// 
// // // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:07 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->micro::user
// //   (acme)windowing::window_base
// //       ---->micro::interchange

//
#pragma once


//#include "acme/platform/conversation_message.h"
//#include "acme/user/user/drag_client.h"
//#include "acme/user/user/interaction_base.h"
//#include "acme/prototype/geometry2d/rectangle.h"
//#include "acme/user/user/item.h"


#include "acme/user/user/element.h"


namespace acme
{


   namespace windowing
   {


      class CLASS_DECL_ACME window :
         virtual public ::user::element
         //virtual public ::conversation_message
      {
      public:



         //::pointer < ::acme::windowing::window >                m_pwindowOwner;

         //::pointer<::micro::window_implementation>     m_pnanouserwindowimplementation;


         class ::time                              m_timeHoverNoiseSuppression;



         int_rectangle                             m_rectangle;
         ::int_rectangle                           m_rectanglePointingTo;

         //bool                                      m_bTopMost;
         // bool                                      m_bStartCentered;
         //bool                                      m_bArbitraryPositioning;




         //pointer_array < ::micro::button >             m_nanobuttona;

         //map < const ::item *, ::user::item >      m_useritemmap;

         bool                                               m_bRepositioningWindowFromCenter;
         bool                                               m_bResizingWindowFromBottomRight;
         ::int_point                                        m_pointDesignRequest;
         ::int_size                                         m_sizeDesignRequest;
         ::int_point                                        m_pointWindow;
         ::int_size                                         m_sizeWindow;
         ::int_point                                        m_pointCursor2;

         ::pointer < ::operating_system::a_system_menu >    m_psystemmenu;

         ::pointer<::acme::user::interaction>               m_pacmeuserinteraction;
         ::pointer<::acme::user::interaction>               m_pacmeuserinteractionKeyboardFocus;
         ::pointer<::acme::user::interaction>               m_pacmeuserinteractionHover;
         ::pointer<::acme::user::interaction>               m_pacmeuserinteractionCapture;
         //::pointer<::acme::user::interaction>               m_pacmeuserinteractionOwner;


         ::pointer < ::acme::windowing::display >           m_pdisplay;



//enum_bias m_ebias;


         window();
         ~window() override;


         //virtual void do_interchange();
         ::windowing::enum_bias windowing_bias() const;


         //virtual ::pointer < item_container > item_form();

         void on_initialize_particle() override;

         virtual ::oswindow oswindow();

         virtual void set_user_interaction(::acme::user::interaction * pacmeuserinteraction);
         virtual void set_user_thread(::user::thread * puserthread);
         virtual void set_user_graphics_thread(::user::graphics_thread * pusergraphicsthread);


         //bool defer_perform_entire_reposition_process() override;

         bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

         bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;




         virtual ::int_point origin();

         void set_position(const ::int_point & point) override;

         ::int_rectangle get_window_rectangle() override;

         void on_create_window() override;

         void destroy() override;

         void redraw() override;


         void set_interaction_rectangle(const ::int_rectangle & rectangle) override;

         ::int_rectangle get_rectangle() override;


         //void get_window_rectangle() override;

         void set_mouse_capture() override;

         bool has_mouse_capture() override;

         void release_mouse_capture() override;

         void set_cursor(enum_cursor ecursor) override;

         virtual bool _is_window();

         
         virtual void set_foreground_window(::user::activation_token * puseractivationtoken);
         
         
         virtual bool has_keyboard_focus();
         virtual void set_keyboard_focus(::acme::user::interaction * pacmeuserinteractionFocus);
         virtual void set_keyboard_focus();
         //virtual void erase_keyboard_focus(::acme::user::interaction * pacmeuserinteractionFocus);

         virtual bool is_window();
         //virtual int_bool is_window( windowing_android_WINDOW_MEMBER );
         
         
         virtual void set_window_text(const ::scoped_string & scopedstrString);

         ::pointer<::nano::graphics::device>create_device();


         virtual ::pointer < ::user::activation_token > get_initial_frame_display_activation_token();
         //void run_modal_loop() override;


         //::atom do_synchronously() override;


         void handle(::topic * ptopic, ::context * pcontext) override;


         //::user::item & user_item(const ::item * pitem) override;


         /// Merged from window_base by camilo on
         ///    2024-10-05 11:09 <3ThomasBorregaardSorensen!!
         /// 
         /// 


         //interchange();
         //~interchange() override;


         ::acme::user::interaction * acme_user_interaction() override;
         ::acme::windowing::window * acme_windowing_window() override;



         ::windowing::window * windowing_window() override;

         //void on_initialize_particle() override;


         //void destroy() override;

         //virtual ::payload do_synchronously(const class time & timeWait);
         //virtual void do_asynchronously();


         virtual bool is_windowing_popup();
         virtual ::int_point windowing_popup_origin();
         virtual ::int_size windowing_popup_size();
         virtual void _on_windowing_close_window();
         virtual bool is_satellite_window();
         ::acme::user::interaction * owner_interaction();
         ::acme::windowing::window * owner_window();
         ::string get_window_text() override;


         virtual itask get_itask() const;

         //virtual ::int_rectangle get_window_rectangle();

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


         virtual ::acme::windowing::display * get_display();


         //void draw(::nano::graphics::device * pnanodevice) override;

         //static ::pointer_array < ::micro::window_implementation > & nanowindowimplementationa();



         //bool get_dark_mode() override;
         //bool is_active() override;

         //virtual void nano_window_on_create();

         void create_window() override;
         void _create_window() override;

         //void on_create_window() override;

         virtual void nano_window_on_destroy();


         void on_window_close() override;

         //virtual void _console_create();

         //virtual void _display_console();

         virtual void on_position_window();
         virtual void on_size_window();

         virtual void show_window();
         virtual void hide_window();

         bool is_window_zoomed() override;
         void window_minimize() override;
         void window_maximize() override; // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
         void window_full_screen() override; // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
         void window_restore() override; // m_pwindow->m_puserinteraction->display(::e_display_normal);
         void window_close() override;
         //virtual void show_window();
         //virtual void hide_window();

         //virtual void message_loop();


         void on_window_deiconified() override;
         void on_window_activated() override;
         void on_window_iconified() override;
         void on_window_deactivated() override;
         void on_window_shown() override;
         void on_window_hidden() override;


         virtual void set_active_window();

         virtual bool is_active_window();

         //virtual ::int_point try_absolute_mouse_position(const ::int_point & point);

         
         virtual void exit_iconify();
         
         virtual void full_screen(const ::int_rectangle & rect = {});
         
         virtual void exit_full_screen();
         
         virtual void exit_zoomed();

         
         virtual void set_parent(::acme::windowing::window* pwindowNewParent);
         //virtual ::e_status set_parent(::windowing::window * pwindowNewParent) override;
         //virtual long get_state();
         virtual bool is_iconic();
         //virtual bool is_window_visible() override;
//         virtual bool _configure_window_unlocked(const class ::zorder & zorder, const ::user::e_activation & useractivation, bool bNoZorder, ::e_display edisplay);
         //virtual iptr get_window_long_ptr(int nIndex);
         //virtual iptr set_window_long_ptr(int nIndex, iptr l);
         virtual bool client_to_screen(::int_point* ppoint);
         
         virtual bool screen_to_client(::int_point* ppoint);
         
         
         //virtual bool set_window_pos(class::zorder zorder, int x, int y, int cx, int cy,unsigned int nFlags);
         //virtual bool _set_window_pos(class::zorder zorder, int x, int y, int cx, int cy,unsigned int nFlags);
         
         
         virtual bool is_destroying();
         
         
         //virtual bool bamf_set_icon();
         
         
         //virtual bool set_icon(::image::image* pimage);
         
         //virtual int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);
         
         virtual void set_mouse_cursor(::windowing::cursor* pcursor);


         //void handle(::topic * ptopic, ::context * pcontext) override;


         //virtual ::int_size get_main_screen_size();


         void _on_window_simple_action(const char * pszActionName) override;


         //virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
         //virtual void do_asynchronously() override;


         virtual void defer_show_system_menu(::user::mouse * pmouse);

         virtual void window_message_loop_step();

         virtual void window_message_loop();



         virtual void set_interface_client_size(const ::int_size & sizeWindow);


         void set_rectangle(const int_rectangle & rectangle) override;
         //void set_position(const int_point & point) override;
         void set_size(const int_size & size) override;


         //::int_rectangle get_window_rectangle() override;
         virtual ::int_rectangle get_window_rectangle_unlocked();


         virtual void set_rectangle_unlocked(const int_rectangle & rectangle);
         virtual void set_position_unlocked(const int_point & point);
         virtual void set_size_unlocked(const int_size & size);


         virtual void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem);
         

      };


   } // namespace windowing


} // namespace acme



