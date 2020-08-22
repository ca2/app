#pragma once




struct CLASS_DECL_AXIS oswindow_data
{
public:


   ::mq *                        m_pmq;

   ::user::interaction_impl *    m_pimpl;

   int_ptr_to_int_ptr *          m_plongptrmap;


   ::user::interaction_impl* window();

   oswindow_data(::user::interaction_impl* pimpl = nullptr);
   ~oswindow_data();

   bool is_child(::oswindow oswindow);
   ::oswindow get_parent();
   ::oswindow set_parent(::oswindow oswindow);
   bool show_window(int nCmdShow);
   LONG_PTR get_window_long_ptr(int nIndex);
   LONG_PTR set_window_long_ptr(int nIndex, LONG_PTR l);


   bool _001ClientToScreen(LPPOINT lppoint);
   bool _001ScreenToClient(LPPOINT lppoint);
   bool is_iconic();
   bool is_window_visible();


};
//
//
//class oswindow_dataptra;
//
//
//
/////static oswindow_dataptra * s_pdataptra;
CLASS_DECL_AXIS index oswindow_find(::user::interaction_impl* pinteraction);
CLASS_DECL_AXIS oswindow oswindow_get(::user::interaction_impl* pinteraction);
CLASS_DECL_AXIS oswindow oswindow_remove(::user::interaction_impl* pinteraction);
CLASS_DECL_AXIS::user::interaction_impl* oswindow_interaction_impl(oswindow oswindow);
CLASS_DECL_AXIS::user::interaction* oswindow_interaction(oswindow oswindow);
#if defined(__cplusplus_winrt)
CLASS_DECL_AXIS Agile < Windows::UI::Core::CoreWindow > oswindow_core_window(oswindow window);
#endif

