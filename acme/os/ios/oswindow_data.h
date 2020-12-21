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
   class interaction;


} // namespace user



class CLASS_DECL_ACME oswindow_data
{
public:


   nswindow                      m_nswindow;
   ::user::interaction_impl *    m_pimpl;
   __pointer(::mq)               m_pmq;



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
      return is_null() ? nullptr : m_nswindow;
   }


   void set_user_interaction_impl(::user::interaction_impl * pimpl);
   ::user::interaction_impl * get_user_interaction_impl();
   ::user::interaction_impl * get_user_interaction_impl() const;
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(enum_display edisplay);
   iptr get_window_long_ptr(iptr nIndex);
   iptr set_window_long_ptr(iptr nIndex, iptr l);
   bool _001ClientToScreen(POINT32 * lppoint);
   bool _001ScreenToClient(POINT32 * lppoint);

   bool is_null() const
   {

      return ::is_null(this);

   }

};


int oswindow_find(UIWindow * window);
oswindow_data * oswindow_get(UIWindow * window);
bool oswindow_remove(UIWindow * window);


