//
//  oswindow_data.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 18/05/20.
//
#pragma once


struct NSWindow;


typedef NSWindow * nswindow;


class message_queue;


class CLASS_DECL_CORE oswindow_data
{
public:


   nswindow                      m_nswindow;
   ::user::interaction_impl *    m_pimpl;
   ::pointer<::message_queue>              m_pmq;

   iptr_to_iptr *          m_plongmap;

   bool                          m_bNsWindowRect;
   RECT32                          m_rectangleNsWindow;


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

//#ifdef __MM

  // operator ::nswindow ()
   //{
     // return window();
   //}

//#endif

   oswindow_data & operator = (const oswindow_data & window);

   bool operator == (const void * p) const
   {
      return this == p;
   }
   bool operator != (const void * p) const
   {
      return this != p;
   }

   //bool is_null();

   nswindow window() const
   {
      return is_null() ? nullptr : m_nswindow;
   }


   void set_user_interaction_impl(::user::interaction_impl * pimpl);
   ::user::interaction * get_user_interaction_base();
   ::user::interaction * get_user_interaction_base() const;
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool iconify();
   bool is_window_visible();
   bool show_window(int iShow);
   iptr get_window_long_ptr(iptr nIndex);
   iptr set_window_long_ptr(iptr nIndex, iptr l);
   bool client_to_screen(POINT32 * ppoint);

   bool screen_to_client(POINT32 * ppoint);




   bool is_null() const;

};





int oswindow_find(nswindow window);
oswindow_data * oswindow_get(nswindow window);
bool oswindow_erase(nswindow window);




//inline int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant)
//{
//   return oswindowParent->is_child(oswindowCandidateChildOrDescendant);
//}

//inline oswindow get_parent(::oswindow window)
//{
//   return window->get_parent();
//}

//oswindow get_window(oswindow window, int iParentHood);

//inline oswindow SetParent(::oswindow window, ::oswindow oswindowNewParent)
//{
//   return window->set_parent(oswindowNewParent);
//}

//inline int display(::oswindow window, ::display edisplay)
//{
//   return window->show_window(nCmdShow);
//}

//inline i32 GetWindowLongA(::oswindow window, i32 nIndex)
//{
//   return (i32) window->get_window_long(nIndex);
//}
//
//inline i32 SetWindowLongA(::oswindow window, i32 nIndex, i32 l)
//{
//   return (i32) window->set_window_long(nIndex, l);
//}
//
//inline int client_to_screen(::oswindow window, POINT32 * ppoint)

//{
//   return window->client_to_screen(ppoint);

//}
//
//inline int screen_to_client(::oswindow window, POINT32 * ppoint)

//{
//   return window->screen_to_client(ppoint);

//}
//
//inline i32 is_iconic(::oswindow window)
//{
//   return window->is_iconic();
//}
//
//inline i32 IsWindowVisible(::oswindow window)
//{
//   return window->is_window_visible();
//}


