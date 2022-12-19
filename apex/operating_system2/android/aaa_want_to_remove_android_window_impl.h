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


struct CLASS_DECL_APEX oswindow_data
{

   bool                          m_bMessageOnlyWindow;
   ::user::primitive *         m_puserinteraction;
   htask_t                       m_htask;
   color32_t *                    m_pcolorref;
   RECT32                          m_rect;
   i32_map < ::i32 > *            m_plongmap;
   bool                          m_bDestroying;


   static oswindow_dataptra * s_pdataptra;
   static ::pointer< ::mutex > s_pmutex;


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


   i32 store_name(const scoped_string & str);
   i32 select_input(i32 iInput);
   i32 select_all_input();
   i32 map_window();

   void set_user_interaction(::user::primitive * pinteraction);
   ::user::primitive * get_user_interaction();
   ::user::primitive * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow SetParent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool ShowWindow(int nCmdShow);
   ::i32 get_window_long(i32 nIndex);
   ::i32 set_window_long(i32 nIndex, ::i32 l);
   bool client_to_screen(POINT32 * lppoint);
   bool screen_to_client(POINT32 * lppoint);



   bool is_null() const
   {
      return this == nullptr;
   }


   bool is_destroying();


};





