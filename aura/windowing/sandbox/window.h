// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// Adapted by Camilo for android 2022-01-05 04:35 <3TBS (Thomas likes number 5), Mummi and bilbo!!
// Adapted by Camilo for cached/simulation of mouse-capture/keyboard-focus state information and
// a few other things present in sandboxed applications (mobile/tablet/small devices)
//     - 2022-06-02 12:44 PM <3TBS (Thomas likes number 5), Mummi and bilbo!!
#pragma once


#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"


namespace sandbox_windowing
{


   class CLASS_DECL_AURA window :
      virtual public ::windowing::window
   {
   public:


      class ::time                                m_timeLastMouseMove;
      ::rectangle_i32                           m_rect;
      ::point_i32                               m_pointCursor;


      htask_t                                   m_htask;


      window();
      ~window() override;


      void create_window(::user::interaction_impl* pimpl) override;



      //::sandbox_windowing::windowing* windowing();

      inline ::sandbox_windowing::windowing * windowing()
      { return m_pwindowing->m_psandboxwindowing; }


      void exit_iconify() override;

      void full_screen(const ::rectangle_i32& rect = nullptr) override;

      void exit_full_screen() override;

      void exit_zoomed() override;

      virtual void set_user_interaction(::user::interaction_impl* pinteraction);

      virtual void post_nc_destroy();

      virtual ::e_status set_window_icon(const ::file::path& path);

      virtual bool is_child(::windowing::window* candidateChildOrDescendant); // or descendant

      ::windowing::window* get_parent() const override;
      //virtual ::Window get_parent_handle();
      ::oswindow get_parent_oswindow() const override;

      ::point_i32 get_mouse_cursor_position() override;

      //virtual ::Window get_parent_handle() const;

      //::windowing::windowing* android_windowing() const { return (::windowing_android::windowing*)m_pwindowing->m_pWindowing; }
      //::windowing_android::display * x11_display() const { return (::windowing_android::display *)m_pdisplay->m_pDisplay; }

      void set_parent(::windowing::window* pwindowNewParent) override;
      //virtual ::e_status set_parent(::windowing::window * pwindowNewParent) override;
      //virtual long get_state();
      virtual bool is_iconic() override;
      virtual bool is_window_visible() override;
      void show_window(const ::e_display& edisplay, const ::e_activation& eactivation) override;
      //virtual iptr get_window_long_ptr(i32 nIndex);
      //virtual iptr set_window_long_ptr(i32 nIndex, iptr l);
      virtual bool client_to_screen(::point_i32* ppoint) override;

      virtual bool screen_to_client(::point_i32* ppoint) override;


      //virtual bool set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      //virtual bool _set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);


      virtual bool is_destroying() override;


      //virtual bool bamf_set_icon();


      //virtual bool set_icon(::image* pimage);

      //virtual int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

      void set_mouse_cursor(::windowing::cursor* pcursor) override;

      virtual void set_mouse_cursor2(::windowing::cursor* pcursor);

      void set_keyboard_focus() override;
      void set_mouse_capture() override;
      void set_active_window() override;


      virtual void SetInternalFocus();


      void set_foreground_window() override;


      bool has_mouse_capture() const override;

      bool has_keyboard_focus() const override;




      //virtual Atom get_window_long_atom(i32 nIndex);
      //virtual void mapped_net_state_raw(bool add, windowing_android_WINDOW_MEMBER int iScreen, Atom state1, Atom state2);
      //virtual void unmapped_net_state_raw( windowing_android_WINDOW_MEMBER ...);
      //virtual bool x11_get_window_rect(windowing_android_WINDOW_MEMBER  ::rectangle_i32 * prectangle);
      //virtual bool x11_get_client_rect(windowing_android_WINDOW_MEMBER  ::rectangle_i32 * prectangle);
      //virtual oswindow set_capture( windowing_android_WINDOW_MEMBER );
      //virtual int_bool release_capture();
      //virtual oswindow set_focus( windowing_android_WINDOW_MEMBER );
      //virtual void x11_check_status(int status, unsigned long window);
      //virtual unsigned long x11_get_long_property( windowing_android_WINDOW_MEMBER char* property_name);
      //virtual string x11_get_name(windowing_android_WINDOW_MEMBER);
      //virtual ::e_status set_active_window();
      //virtual void upper_window_rects(windowing_android_WINDOW_MEMBER  rectangle_i32_array & ra);
      //virtual oswindow set_active_window( windowing_android_WINDOW_MEMBER );
//      virtual  windowing_android_WINDOW_MEMBER _get_if_found(Window w);
      //virtual oswindow get_parent( windowing_android_WINDOW_MEMBER );
      //virtual ::Window _get_window_relative(windowing_android_WINDOW_MEMBER enum_relative erelative, ::Window * windowa, int numItems);
      //virtual ::windowing::window * get_window(windowing_android_WINDOW_MEMBER enum_relative erelative);

      void destroy_window() override;
      //virtual int_bool destroy_window( windowing_android_WINDOW_MEMBER );
      bool is_window() override;
      //virtual int_bool is_window( windowing_android_WINDOW_MEMBER );


      void set_window_text(const ::scoped_string & scopedstrString) override;


      void set_tool_window(bool bSet) override;


      bool set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide) override;


      //virtual comparable_array < Atom > wm_get_list_raw(windowing_android_WINDOW_MEMBER Atom atomList);
      //virtual int wm_test_state(windowing_android_WINDOW_MEMBER const ::scoped_string & scopedstrNetStateFlag);
      //virtual int wm_test_state_raw(windowing_android_WINDOW_MEMBER const ::scoped_string & scopedstrNetStateFlag);
      //virtual int wm_test_list_raw(windowing_android_WINDOW_MEMBER Atom atomList, Atom atomFlag);
      //virtual bool wm_add_remove_list_raw(windowing_android_WINDOW_MEMBER Atom atomList, Atom atomFlag, bool bSet);
      //virtual void wm_add_remove_state_mapped_raw(windowing_android_WINDOW_MEMBER::x11::enum_atom eatomNetWmState, bool bSet);
      //virtual void wm_add_remove_state_mapped(windowing_android_WINDOW_MEMBER::x11::enum_atom eatomNetWmState, bool bSet);
      //virtual void wm_add_remove_state_unmapped_raw(windowing_android_WINDOW_MEMBER::x11::enum_atom eatomNetWmState, bool bSet);
      //virtual void wm_add_remove_state_unmapped(windowing_android_WINDOW_MEMBER::x11::enum_atom eatomNetWmState, bool bSet);
      //virtual void wm_add_remove_state_raw(windowing_android_WINDOW_MEMBER::x11::enum_atom eatomNetWmState, bool bSet);
      //virtual void wm_add_remove_state(windowing_android_WINDOW_MEMBER::x11::enum_atom eatomNetWmState, bool bSet);
      //virtual void wm_state_clear_raw(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_below_raw(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_above_raw(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_hidden_raw(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_above(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_below(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_hidden(windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_toolwindow(windowing_android_WINDOW_MEMBER bool bToolWindow);
      //virtual void wm_normalwindow();
      //virtual void wm_hidden_state(windowing_android_WINDOW_MEMBER bool bHidden);
      //virtual void wm_desktopwindow(windowing_android_WINDOW_MEMBER bool bDesktopWindow);
      //virtual void wm_centerwindow(windowing_android_WINDOW_MEMBER bool bCenterWindow);
      //virtual void wm_splashwindow(windowing_android_WINDOW_MEMBER bool bCenterWindow);
      //virtual void wm_dockwindow(windowing_android_WINDOW_MEMBER bool bDockWindow);
      //virtual void wm_nodecorations(windowing_android_WINDOW_MEMBER int bMap);
      //virtual void _wm_nodecorations(windowing_android_WINDOW_MEMBER int bMap);
      //virtual int_bool IsWindowVisibleRaw(windowing_android_WINDOW_MEMBER);
      //virtual void wm_iconify_window(windowing_android_WINDOW_MEMBER);
      //virtual int_bool IsWindowVisibleRaw( windowing_android_WINDOW_MEMBER);
      //virtual int_bool IsWindowVisibleRaw(oswindow w);
//      virtual Atom * wm_get_list_raw( windowing_android_WINDOW_MEMBER Atom atomList, unsigned long int * pnum_items);
//      virtual int wm_test_list_raw( windowing_android_WINDOW_MEMBER Atom atomList, Atom atomFlag);
//      virtual int wm_test_state_raw( windowing_android_WINDOW_MEMBER const ::scoped_string & scopedstrNetStateFlag);
//      virtual int wm_test_state( windowing_android_WINDOW_MEMBER const ::scoped_string & scopedstrNetStateFlag);
//      virtual bool wm_add_remove_list_raw( windowing_android_WINDOW_MEMBER Atom atomList, Atom atomFlag, bool bSet);


      //virtual ::e_status x11_post_message(MESSAGE & msg);
      //virtual ::e_status post_ui_message(const MESSAGE & message);
      ////virtual bool x11_process_event(osdisplay_data * pdisplaydata, XEvent * pevent, XGenericEventCookie *cookie);
      ////virtual ::e_status set_window_position( windowing_android_WINDOW_MEMBER const ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags);
      //virtual ::e_status window_rectangle(windowing_android_WINDOW_MEMBER ::rectangle_i32 * prectangle);
      //virtual ::e_status client_rectangle(windowing_android_WINDOW_MEMBER  ::rectangle_i32 * prectangle);
      ////virtual ::e_status wm_full_screen( windowing_android_WINDOW_MEMBER const ::rectangle_i32 & rectangle);

      //virtual ::e_status x11_store_name(const ::scoped_string & scopedstrName);
      //virtual ::e_status set_foreground_window();
      //virtual ::e_status set_active_window();
      //virtual void wm_toolwindow( windowing_android_WINDOW_MEMBER bool bToolWindow);
      //virtual void wm_state_hidden( windowing_android_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_hidden_raw( windowing_android_WINDOW_MEMBER bool bSet);
      //virtual ::e_status mq_remove_window_from_all_queues(windowing_android_WINDOW_MEMBER);

      void update_screen() override;
      void window_show() override;

      bool is_active_window() const override;


      void bring_to_front() override;


      //float get_dpi_for_window() override;

      //float get_density_for_window() override;

      //virtual void on_touch_down(int x, int y);
      //virtual void on_touch_drag(int x, int y);
      //virtual void on_touch_up(int x, int y);


   };


} // namespace sandbox_windowing



