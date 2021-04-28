#ifndef BASE_SOLARIS_USER_IMPL_H
#define BASE_SOLARIS_USER_IMPL_H


#pragma once



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


class ::mutex;


class CLASS_DECL_CORE oswindow_data
{
public:


   osdisplay m_osdisplay;
   Window m_window;
   Visual m_visual;
   int m_iDepth;
   int m_iScreen;
   bool m_bMessageOnlyWindow;
   ::user::interaction * m_puserinteraction;
   htask_t m_htask;
   int_to_int * m_plongmap;
   bool m_bDestroying;
   Colormap m_colormap;


   static oswindow_dataptra * s_pdataptra;
   static ::mutex * s_pmutex;

   static Atom s_atomLongType;
   static Atom s_atomLongStyle;
   static Atom s_atomLongStyleEx;

   static Atom get_window_long_atom(i32 nIndex);




   oswindow_data();
   oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
   oswindow_data(const void * p);
   oswindow_data(const LPARAM & lparam);
   oswindow_data(const WPARAM & wparam);


   ~oswindow_data();

   operator void * ()
   {
      return this;
   }

   operator void * () const
   {
      return (void *) this;
   }

   oswindow_data & operator =(const oswindow_data & window);

   bool operator ==(const void * p) const
   {
      return this == p;
   }

   bool operator !=(const void * p) const
   {
      return this != p;
   }

   Display * display()
   {
      return this == nullptr ? nullptr : m_osdisplay->display();
   }

   Display * display() const
   {
      return this == nullptr ? nullptr : m_osdisplay->display();
   }

   Window window()
   {
      return this == nullptr ? None : m_window;
   }

   Window window() const
   {
      return this == nullptr ? None : m_window;
   }

   Visual * draw2d()
   {
      return this == nullptr ? nullptr : &m_visual;
   }

   Visual * draw2d() const
   {
      return this == nullptr ? nullptr : (Visual *) & m_visual;
   }


   i32 store_name(const char * psz);
   i32 select_input(i32 iInput);
   i32 select_all_input();
   i32 map_window();

   void set_user_interaction(::user::interaction * pinteraction);
   ::user::interaction * get_user_interaction_base();
   ::user::interaction * get_user_interaction_base() const;
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowcandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(i32 nCmdShow);
   ::i32 get_window_long(i32 nIndex);
   ::i32 set_window_long(i32 nIndex, ::i32 l);
   bool _001ClientToScreen(POINT_I32 * lppoint);
   bool _001ScreenToClient(POINT_I32 * lppoint);

   bool is_null() const
   {
      return this == nullptr;
   }


   bool is_destroying();


};


CLASS_DECL_CORE i32 oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_CORE i32 oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_CORE i32 oswindow_find(Window window);
CLASS_DECL_CORE oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_CORE oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = nullptr);
CLASS_DECL_CORE oswindow_data * oswindow_get(Window window);
CLASS_DECL_CORE oswindow oswindow_defer_get(Window w);
CLASS_DECL_CORE bool oswindow_erase(Display * pdisplay, Window window);
CLASS_DECL_CORE bool oswindow_erase_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);




#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)

inline bool IsChild(oswindow oswindowParent, ::oswindow oswindowcandidateChildOrDescendant)
{
   return oswindowParent->is_child(oswindowcandidateChildOrDescendant);
}

inline oswindow get_parent(::oswindow oswindow)
{
   return oswindow->get_parent();
}

inline oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent)
{
   return oswindow->set_parent(oswindowNewParent);
}

inline bool ShowWindow(::oswindow oswindow, i32 nCmdShow)
{
   return oswindow->show_window(nCmdShow);
}

inline ::i32 GetWindowLongA(::oswindow oswindow, i32 nIndex)
{
   return oswindow->get_window_long(nIndex);
}

inline ::i32 SetWindowLongA(::oswindow oswindow, i32 nIndex, ::i32 l)
{
   return oswindow->set_window_long(nIndex, l);
}

inline bool _001ClientToScreen(::oswindow oswindow, POINT_I32 * lppoint)
{
   return oswindow->_001ClientToScreen(lppoint);
}

inline bool _001ScreenToClient(::oswindow oswindow, POINT_I32 * lppoint)
{
   return oswindow->_001ScreenToClient(lppoint);
}

inline i32 IsIconic(::oswindow oswindow)
{
   return oswindow->is_iconic();
}

inline i32 IsWindowVisible(::oswindow oswindow)
{
   return oswindow->is_window_visible();
}


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_CORE int IsWindow(oswindow oswindow);

class oswindow_dataptra :
   public array < oswindow_data * >
{
public:


};

extern oswindow g_oswindowDesktop;

oswindow GetCapture();
oswindow SetCapture(oswindow window);
int_bool ReleaseCapture();
oswindow SetFocus(oswindow window);
oswindow GetFocus();
oswindow GetWindow(oswindow window, int iParentHood);
oswindow GetActiveWindow();
oswindow SetActiveWindow(oswindow window);
int_bool DestroyWindow(oswindow window);
oswindow get_desktop_window();

class osdisplay_dataptra :
   public ::raw_array < osdisplay_data * >
{
public:


};


#endif // BASE_SOLARIS_USER_IMPL_H










