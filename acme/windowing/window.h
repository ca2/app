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
//#include "acme/operating_system/window.h"

#include "acme/user/user/element.h"
#ifdef WINDOWS_DESKTOP
#include "acme/operating_system/windows/_window_class.h"
#endif

namespace acme
{


   namespace windowing
   {

   
   class gpu_context_render_frame :
   virtual public particle
   {
   public:
      
      virtual void on_gpu_context_render_frame(::i32 w, ::i32 h) = 0;
      
   };

      class CLASS_DECL_ACME window :
         virtual public ::user::element
         //virtual public ::conversation_message
      {
      public:


         //::operating_system::window          m_operatingsystemwindow;
         ::pointer_array < ::exception >     m_exceptiona;
         ::pointer < ::acme::windowing::gpu_context_render_frame >         m_pgpucontextrenderframe;
         //::pointer < ::acme::windowing::window >                m_pwindowOwner;

         //::pointer<::micro::window_implementation>     m_pnanouserwindowimplementation;

         class ::time                              m_timeHoverNoiseSuppression;




         i32_rectangle                             m_rectangle;
         ::i32_rectangle                           m_rectanglePointingTo;

         //bool                                      m_bTopMost;
         // bool                                      m_bStartCentered;
         //bool                                      m_bArbitraryPositioning;




         //pointer_array < ::micro::button >             m_nanobuttona;

         //map_base < const ::item *, ::user::item >      m_useritemmap;

         bool                                               m_bPerformingEntireRepositionProcess;
         bool                                               m_bPerformingEntireResizingProcess;
         bool                                               m_bRepositioningWindowFromCenter;
         bool                                               m_bResizingWindowFromBottomRight;
         //::i32_point                                        m_pointDesignRequest;
         //::i32_size                                         m_sizeDesignRequest;
         ::i32_point                                        m_pointWindow;
         ::i32_size                                         m_sizeWindow;
         ::i32_point                                        m_pointCursor2;

         ::pointer < ::operating_system::a_system_menu >    m_psystemmenu;

         ::pointer<::acme::user::interaction>               m_pacmeuserinteraction;
         ::pointer<::acme::user::interaction>               m_pacmeuserinteractionKeyboardFocus;
         ::pointer<::acme::user::interaction>               m_pacmeuserinteractionHover;
         ::pointer<::acme::user::interaction>               m_pacmeuserinteractionMouseCapture;
         //::pointer<::acme::user::interaction>               m_pacmeuserinteractionOwner;


         ::pointer < ::acme::windowing::display >           m_pacmewindowingdisplayWindow;
         class ::time m_timeLastPresent;
//         long                                               m_lX11NativeVisualId;
//         ::i32                                                m_lX11MapNotify = -1;



//enum_bias m_ebias;


         window();
         ~window() override;


         //virtual void do_interchange();
         ::windowing::enum_bias windowing_bias() const;

         //virtual ::pointer < item_container > item_form();

         void on_initialize_particle() override;

         virtual void initialize_window(::acme::user::interaction* pacmeuserinteraction);

         //virtual void * __win32_HWND();

         //virtual long __x11_Window();
         //virtual void * __x11_Display();
         //virtual void * __win32_HWND();
         //virtual ::i64 __CGWindowID() const;
         
         virtual bool should_avoid_default_swap_chain_present();
         
         virtual ::operating_system::window operating_system_window() const;
         virtual void set_user_interaction(::acme::user::interaction * pacmeuserinteraction);
         virtual void set_user_thread(::user::thread * puserthread);
         virtual void set_user_graphics_thread(::user::graphics_thread * pusergraphicsthread);

         
         virtual void set_last_present_time();

         //bool defer_perform_entire_reposition_process() override;

         bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

         bool defer_perform_entire_resizing_process(const ::experience::e_frame & eframeSizing, ::user::mouse * pmouse) override;




         virtual ::i32_point origin();

         void set_position(const ::i32_point & point) override;

         ::i32_rectangle get_window_rectangle() override;

         void on_create_window() override;

         void destroy() override;

         void redraw() override;


         void set_interaction_rectangle(const ::i32_rectangle & rectangle) override;

         ::i32_rectangle get_rectangle() override;


         //void get_window_rectangle() override;

         void set_mouse_capture() override;

         bool has_mouse_capture() override;

         void release_mouse_capture() override;

         void set_cursor(enum_cursor ecursor) override;

         virtual bool _is_window();

         
         void set_foreground_window(::user::activation_token * puseractivationtoken) override;
         
         
         virtual bool has_keyboard_focus();
         virtual void set_keyboard_focus(::acme::user::interaction * pacmeuserinteractionFocus);
         void set_keyboard_focus() override;
         //virtual void erase_keyboard_focus(::acme::user::interaction * pacmeuserinteractionFocus);

         virtual bool is_window();
         //virtual ::i32_bool is_window( windowing_android_WINDOW_MEMBER );
         
         
         void set_window_text(const ::scoped_string & scopedstrString) override;

         ::pointer<::nano::graphics::context>create_device();


         virtual bool on_window_mouse_move(const ::i32_point & point, const ::i32_point & pointAbsolute);

         virtual void on_mouse_enter();
         virtual void fore_on_mouse_move(::user::mouse * pmouse);
         virtual void back_on_mouse_move(::user::mouse * pmouse);
         virtual void on_mouse_leave();

#ifdef WINDOWS_DESKTOP
         virtual ::windows::window_class _get_window_class();
#endif

         virtual void on_window_paint(::nano::graphics::context * pgraphicscontext);
         void on_window_size() override;
         void on_window_set_focus() override;
         bool on_window_activate(::i32 iActivate, bool bMinimized, const ::operating_system::window & operatingsystemwindow) override;
         bool on_window_mouse_activate(::i32 & iResult, const ::operating_system::window & operatingsystemwindowTop ,
            ::i32 iHitTest, ::i32 iMessage)override;


         bool is_window_iconic() override;
         ::f32 get_window_scale() override;


         void show_window(::i32 iShowFlags) override;
         void set_window_style(::i32 iStyle) override;
         ::i64 get_window_style() override;
         void set_window_position(const ::operating_system::window & operatingsystemwindow, const ::i32_point & point, const ::i32_size & size, ::i32 iSetWindowPosFlags) override;
         void window_invalidate_rect(const ::i32_rectangle * prectangle, bool bErase) override;
         void update_window() override;
         void redraw_window(const ::i32_rectangle * prectangle, void * pHRGN, ::i32 iRedrawFlags) override;
         void window_set_focus() override;
         ::i32_rectangle window_get_client_rect() override;
         ::i32_rectangle get_window_rect() override;
         void dump_operating_system_child_window_hierarchy() override;

         virtual ::pointer < ::user::activation_token > get_initial_frame_display_activation_token();
         //void run_modal_loop() override;


         //::atom do_synchronously() override;


         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


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
         virtual ::i32_point windowing_popup_origin();
         virtual ::i32_size windowing_popup_size();
         virtual void _on_windowing_close_window();
         virtual ::i32_boolean is_satellite_window();
         ::acme::user::interaction * owner_interaction();
         ::acme::windowing::window * owner_window();
         ::string get_window_text() override;


         virtual itask get_itask() const;

         //virtual ::i32_rectangle get_window_rectangle();

         ///::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true) override;

         //bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

         //bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;


         //virtual void on_char(::i32 iChar);
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

         virtual ::particle * get_acme_window_bridge();

         //void draw(::nano::graphics::context * pnanodevice) override;

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

         virtual void _on_reposition(::i32 x, ::i32 y);
         virtual void _on_size(::i32 cx, ::i32 cy);

         //virtual void show_window();
         //virtual void hide_window();

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


         void set_active_window() override;

         virtual bool is_active_window();

         //virtual ::i32_point try_absolute_mouse_position(const ::i32_point & point);

         
         virtual void exit_iconify();
         
         virtual void full_screen(const ::i32_rectangle & rect = {});
         
         virtual void exit_full_screen();
         
         virtual void exit_zoomed();

         
         virtual void set_parent(::acme::windowing::window* pwindowNewParent);
         //virtual ::e_status set_parent(::windowing::window * pwindowNewParent) override;
         //virtual long get_state();
         virtual bool is_iconic();
         //virtual bool is_window_visible() override;
//         virtual bool _configure_window_unlocked(const class ::zorder & zorder, const ::user::e_activation & useractivation, bool bNoZorder, ::e_display edisplay);
         //virtual iptr get_window_long_ptr(::i32 nIndex);
         //virtual iptr set_window_long_ptr(::i32 nIndex, iptr l);
         virtual bool client_to_screen(::i32_point* ppoint);
         
         virtual bool screen_to_client(::i32_point* ppoint);
         
         
         //virtual bool set_window_pos(class::zorder zorder, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy,::u32 nFlags);
         //virtual bool _set_window_pos(class::zorder zorder, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy,::u32 nFlags);
         
         
         virtual bool is_destroying();
         
         
         //virtual bool bamf_set_icon();
         
         
         //virtual bool set_icon(::image::image* pimage);
         
         //virtual ::i32 x_change_property(Atom property, Atom type, ::i32 format, ::i32 mode, const ::u8 * data, ::i32 nelements);
         
         virtual void set_mouse_cursor(::windowing::cursor* pcursor);


         //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


         //virtual ::i32_size get_main_screen_size();


         void _on_window_simple_action(const_char_pointer pszActionName, ::user::activation_token * puseractivationtoken) override;


         //virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
         //virtual void do_asynchronously() override;


         virtual void defer_show_system_menu(::user::mouse * pmouse);

         virtual void window_message_loop_step();

         virtual void window_message_loop();



         virtual void set_interface_client_size(const ::i32_size & sizeWindow);


         void set_rectangle(const i32_rectangle & rectangle) override;
         //void set_position(const i32_point & point) override;
         void set_size(const i32_size & size) override;


         //::i32_rectangle get_window_rectangle() override;
         virtual ::i32_rectangle get_window_rectangle_unlocked();


         virtual void set_rectangle_unlocked(const i32_rectangle & rectangle);
         virtual void set_position_unlocked(const i32_point & point);
         virtual void set_size_unlocked(const i32_size & size);


         virtual void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem, ::user::activation_token * puseractivationtoken);

         virtual ::i32 control_box_right_when_at_left() const;

         virtual bool should_use_desktop_ambient_like_control_box() const;
         
         virtual void on_control_box_close();
         virtual void on_control_box_minimize();
         virtual void on_control_box_zoom();


         virtual void get_os_window_handle(void *p, ::i32 iSize);

         virtual void on_gpu_context_render_frame(::i32 w, ::i32 h);
         
         virtual void _lock_window_gpu_context();
         virtual void _unlock_window_gpu_context();

      };


   } // namespace windowing


} // namespace acme



