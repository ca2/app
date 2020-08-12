//
//  ios_window.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#ifdef __MM

typedef void * int_to_int;

#else

struct UIWindow;

#endif

typedef UIWindow * nswindow;


namespace user
{
   
   
   class interaction;
   class interaction_impl;
   
   
} // namespace user


class CLASS_DECL_AURA oswindow_data
{
public:
   
   
   nswindow                      m_nswindow;
   ::user::interaction_impl *    m_pimpl;
   
   int m_x;
   int m_y;
   int m_cx;
   int m_cy;
   
   
   int_to_int *                  m_plongmap;
   
   
   oswindow_data();
   oswindow_data(nswindow window);
   oswindow_data(const oswindow_data & oswindow);
   ~oswindow_data();
   
   
   operator void * ()
   {
      
      return this;
      
   }
   
   operator void * () const
   {
      
      return (void *) this;
      
   }
   
#ifdef __MM
   
   operator ::nswindow ()
   {
      return window();
   }
   
#endif
   
   oswindow_data & operator = (const oswindow_data & window);
   
   bool operator == (const void * p) const
   {
      return this == p;
   }
   bool operator != (const void * p) const
   {
      return this != p;
   }
   
   nswindow window()
   {
      return ::is_null(this) ? nullptr : m_nswindow;
   }
   
   
   void set_user_interaction(::user::interaction_impl * pinteraction);
   ::user::interaction_impl * get_user_interaction_base();
   ::user::interaction_impl * get_user_interaction_base() const;
   ::user::interaction_impl * get_user_interaction();
   ::user::interaction_impl * get_user_interaction() const;
   
   
   void post_nc_destroy();
   
   
   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(i32 nCmdShow);
   i32 get_window_long(i32 nIndex);
   i32 set_window_long(i32 nIndex, i32 l);
   bool _001ClientToScreen(POINT * lppoint);
   bool _001ScreenToClient(POINT * lppoint);
   
   
   
   bool is_null() const
   {
      return ::is_null(this);
   }
   
};





int oswindow_find(nswindow window);
oswindow_data * oswindow_get(nswindow window);
bool oswindow_remove(nswindow window);


inline int IsWindow(oswindow oswindow)
{
   return oswindow->get_user_interaction() != nullptr;
}

inline int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant)
{
   return oswindowParent->is_child(oswindowCandidateChildOrDescendant);
}

inline oswindow GetParent(::oswindow oswindow)
{
   return oswindow->get_parent();
}

inline oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent)
{
   return oswindow->set_parent(oswindowNewParent);
}

inline int ShowWindow(::oswindow oswindow, i32 nCmdShow)
{
   return oswindow->show_window(nCmdShow);
}

inline i32 GetWindowLongA(::oswindow oswindow, i32 nIndex)
{
   return oswindow->get_window_long(nIndex);
}

inline i32 SetWindowLongA(::oswindow oswindow, i32 nIndex, i32 l)
{
   return oswindow->set_window_long(nIndex, l);
}

inline int _001ClientToScreen(::oswindow oswindow, POINT * lppoint)
{
   return oswindow->_001ClientToScreen(lppoint);
}

inline int _001ScreenToClient(::oswindow oswindow, POINT * lppoint)
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


oswindow GetWindow(oswindow window, int iParentHood);


void DeactivateWindow(oswindow window);
