#pragma once


//namespace boot
//{
//
//
//   class thread_base;
//   class interaction_impl;
//
//
//} // namespace boot
//

//namespace user
//{
//
//
//   class primitive;
//   class interaction;
//
//
//} // namespace user
//

typedef ref_array < oswindow_data > oswindow_dataptra;


struct CLASS_DECL_CORE oswindow_data
{

   bool                          m_bMessageOnlyWindow;
   ::user::primitive *         m_puserinteraction;
   HTHREAD                       m_hthread;
   COLORREF *                    m_pcolorref;
   RECT                          m_rect;
   int_map < LONG > *            m_plongmap;
   bool                          m_bDestroying;


   static oswindow_dataptra * s_pdataptra;
   static ::mutex * s_pmutex;


   oswindow_data();
   oswindow_data(::user::primitive * puibaseMessageOnlyWindow);
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

   oswindow_data & operator = (const oswindow_data & interaction_impl);

   bool operator == (const void * p) const
   {
      return this == p;
   }

   bool operator != (const void * p) const
   {
      return this != p;
   }


   i32 store_name(const char * psz);
   i32 select_input(i32 iInput);
   i32 select_all_input();
   i32 map_window();

   void set_user_interaction(::user::primitive * pinteraction);
   ::user::primitive * get_user_interaction();
   ::user::primitive * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow GetParent();
   oswindow SetParent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool ShowWindow(int nCmdShow);
   LONG get_window_long(i32 nIndex);
   LONG set_window_long(i32 nIndex, LONG l);
   bool ClientToScreen(LPPOINT lppoint);
   bool ScreenToClient(LPPOINT lppoint);



   bool is_null() const
   {
      return this == nullptr;
   }


   bool is_destroying();


};





