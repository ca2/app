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

      __pointer(display)                           m_pdisplay;
      __pointer(::user::interaction_impl)    m_pimpl;
      __pointer(mq)                                m_pmq;
      millis                                       m_millisLastMouseMove;
      __pointer(window)                            m_pwindowParent;
      ::rect                                       m_rect;

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
      i32 store_name(const char * psz);
      i32 select_input(i32 iInput);
      i32 select_all_input();
      i32 map_window();
      i32 unmap_window(bool bWithdraw);
      void set_wm_class(const char * psz);

      void exit_iconify();

      void full_screen(const::rect & rect = nullptr);

      void exit_full_screen();

      void exit_zoomed();

      void set_user_interaction(::layered * pinteraction);

      void post_nc_destroy();

      bool is_child(window * pwindow); // or descendant
      oswindow get_parent();
      iptr get_parent_os_data();

      oswindow set_parent(oswindow oswindowNewParent);
      long get_state();
      bool is_iconic();
      bool is_window_visible();
      bool show_window(const::e_display & edisplay, const::e_activation & eactivation);
      iptr get_window_long_ptr(i32 nIndex);
      iptr set_window_long_ptr(i32 nIndex, iptr l);
      bool _001ClientToScreen(POINT32 * ppoint);

      bool _001ScreenToClient(POINT32 * ppoint);




      bool set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      bool _set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);

      bool is_destroying();

      bool bamf_set_icon();

      bool set_icon(::image * pimage);

      //int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

   };


   using window_map = iptr_map < __pointer(window) >;


} // namespace windowing


