// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace windowing
{


   class CLASS_DECL_ACME window :
      virtual public ::matter
   {
   public:


      bool                                         m_bMessageOnlyWindow : 1;

#ifdef WINDOWS
      void *                                       m_posdata;
#endif

      __pointer(display)                           m_pdisplay;
      __pointer(::user::interaction_impl)    m_pimpl;
      __pointer(mq)                                m_pmq;
      millis                                       m_millisLastMouseMove;
      __pointer(window)                            m_pwindowParent;
      ::rectangle_i32                                       m_rectangle;

      window();
      virtual ~window();



      virtual iptr get_os_data() const;


      bool operator== (const window & window) const
      {
         return m_pdisplay == window.m_pdisplay
         && get_os_data() == window.get_os_data();
      }

      bool operator!= (const window & window) const
      {
         return !operator==(window);
      }

      virtual display * display();




      //void send_client_event(Atom atom, unsigned int numArgs, ...);
      virtual i32 store_name(const char * psz);
      virtual i32 select_input(i32 iInput);
      virtual i32 select_all_input();
      virtual i32 map_window();
      virtual i32 unmap_window(bool bWithdraw);
      virtual void set_wm_class(const char * psz);

      virtual void exit_iconify();

      virtual void full_screen(const::rectangle_i32 & rectangle = nullptr);

      virtual void exit_full_screen();

      virtual void exit_zoomed();

      virtual ::e_status set_focus();

      virtual __pointer(window) get_active_window();

      virtual ::e_status set_active_window();

      virtual ::e_status set_capture();

      virtual ::e_status destroy_window();

      virtual ::e_status show_window(const ::e_display & edisplay, const ::e_activation & eactivation);

      virtual void set_user_interaction(::layered * pinteraction);

      virtual void post_nc_destroy();

      virtual bool is_child(window * pwindow); // or descendant
      virtual oswindow get_parent();
      virtual iptr get_parent_os_data();

      virtual oswindow set_parent(oswindow oswindowNewParent);
      virtual long get_state();
      virtual bool is_iconic();
      virtual bool is_window_visible();
      //virtual ::e_status show_window(const::e_display & edisplay, const::e_activation & eactivation);
      virtual iptr get_window_long_ptr(i32 nIndex);
      virtual iptr set_window_long_ptr(i32 nIndex, iptr l);
      virtual bool _001ClientToScreen(POINT_I32 * ppoint);

      virtual bool _001ScreenToClient(POINT_I32 * ppoint);




      virtual bool set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      virtual bool _set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);

      virtual bool is_destroying();

      virtual bool bamf_set_icon();

      virtual bool set_icon(::image * pimage);

      //int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

   };


   using window_map = iptr_map < __pointer(window) >;


} // namespace windowing


