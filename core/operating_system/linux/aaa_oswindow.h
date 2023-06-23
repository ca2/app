#pragma once


// define portable types for 32-bit / 64-bit OS
//typedef i32 int_bool;
typedef u8 ::u8;
//typedef u16 ::u16;
typedef u32 ::u32;
//typedef i32 ::i32;


#undef
#undef


#ifndef const
#define const               const
#endif


struct htask;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user
{


   class interaction;
   class interaction;


} // namespace user


class oswindow_dataptra;


class event;


class mutex;


class oswindow_data;


CLASS_DECL_CORE i32 oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_CORE i32 oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_CORE i32 oswindow_find(Window window);
CLASS_DECL_CORE oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_CORE oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = nullptr, int iDepth = -1, int iScreen = -1, Colormap colormap = None);
CLASS_DECL_CORE oswindow_data * oswindow_get(Window window);
CLASS_DECL_CORE oswindow_data * oswindow_defer_get(Display * pdisplay, Window window);
CLASS_DECL_CORE oswindow oswindow_defer_get(Window w);
CLASS_DECL_CORE bool oswindow_erase(Display * pdisplay, Window window);
CLASS_DECL_CORE bool oswindow_erase_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);


struct htask;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user
{


   class interaction;
   class interaction;


} // namespace user


class oswindow_dataptra;


class simple_event;


class mutex;


class CLASS_DECL_CORE oswindow_data
{
public:


   HCURSOR                                m_hcursorLast;

   int                                    m_iXic;
   XIC                                    m_xic;
   osdisplay                              m_osdisplay;
   Window                                 m_window;
   Visual                                 m_visual;
   int                                    m_iDepth;
   int                                    m_iScreen;
   bool                                   m_bMessageOnlyWindow;
   ::pointer<::user::interaction_impl>   m_pimpl;
   ::pointer<message_queue>                         m_pmq;
   htask_t                                m_htask;
   Colormap                               m_colormap;
   ::duration                                   m_durationLastMouseMove;
   Window                                 m_parent;
   ::rectangle_f64                                 m_rect;
   string                                 m_strWMClass;
   int                                    m_iaNetWmState[net_wm_state_count];


   static oswindow_dataptra * s_pdataptra;
   static ::pointer< ::mutex > s_pmutex;

   static Atom s_atomLongType;
   static Atom s_atomLongStyle;
   static Atom s_atomLongStyleEx;

   static Atom get_window_long_atom(i32 nIndex);




   oswindow_data();
   //oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
   //oswindow_data(const void * p);
   //oswindow_data(const LPARAM & lparam);

   //oswindow_data(const WPARAM & wparam);


   ~oswindow_data();



   operator void * ()
   {
      return this;
   }

   operator void * () const
   {
      return (void *) this;
   }

   oswindow_data & operator = (const oswindow_data & window);

   bool operator == (const void * p) const
   {
      return this == p;
   }

   bool operator != (const void * p) const
   {
      return this != p;
   }

   Display * display()
   {
      return ::is_null(this) ? nullptr : m_osdisplay->display();
   }

   Display * display() const
   {
      return ::is_null(this) ? nullptr : m_osdisplay->display();
   }

   Window window()
   {
      return ::is_null(this) ? None : m_window;
   }

   Window window() const
   {
      return ::is_null(this) ? None : m_window;
   }

   Visual * visual()
   {
      return ::is_null(this) ? nullptr : &m_visual;
   }

   Visual * visual() const
   {
      return ::is_null(this) ? nullptr : (Visual *) &m_visual;
   }

   Window root_window_raw() const
   {
      return ::is_null(this) || ::is_null(m_osdisplay) ? None : RootWindow(display(), m_iScreen);
   }

   void send_client_event(Atom atom, unsigned int numArgs, ...);
   i32 store_name(const ::string & psz);
   i32 select_input(i32 iInput);
   i32 select_all_input();
   i32 map_window();
   i32 unmap_window(bool bWithdraw);
    void set_wm_class(const ::string & psz);

   void exit_iconify();

   void full_screen(const ::rectangle_f64 & rectangle = nullptr);

   void exit_full_screen();

   void exit_zoomed();

   void set_user_interaction(::user::interaction_impl * pinteraction);


   void post_nc_destroy();


   bool is_child(oswindow oswindowcandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   Window get_parent_handle();

   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(int iShow);
   LONG_PTR get_window_long_ptr(i32 nIndex);
   LONG_PTR set_window_long_ptr(i32 nIndex, LONG_PTR l);
   bool client_to_screen(POINT32 * ppoint);

   bool screen_to_client(POINT32 * ppoint);


   Atom intern_atom(const ::string & pszAtomName, bool bCreate);
   Atom intern_atom(e_net_wm_state state, bool bCreate);

   bool is_null() const
   {
      return ::is_null(this);
   }

   bool set_window_position(class ::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags);
   bool _set_window_pos(class ::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags);

   bool is_destroying();

   bool bamf_set_icon();

   bool set_icon(::image * pimage);

   int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

};

class oswindow_dataptra :
   public address_array < oswindow_data * >
{
public:

   virtual ~oswindow_dataptra()
   {

      erase_all();

   }

   void erase_all()
   {

      for(auto point : *this)
      {

         delete point;

      }

      address_array < oswindow_data * >::erase_all();
   }

};

extern oswindow g_oswindowDesktop;




