#pragma once




struct CLASS_DECL_CORE oswindow_data
{
public:


   ::mq *                        m_pmq;

   ::user::interaction_impl *    m_pimpl;

   iptr_to_iptr *          m_plongptrmap;


   ::user::interaction_impl* window();

   oswindow_data(::user::interaction_impl* pimpl = nullptr);
   ~oswindow_data();

   bool is_child(::oswindow oswindow);
   ::oswindow get_parent();
   ::oswindow set_parent(::oswindow oswindow);
   bool show_window(int nCmdShow);
   LONG_PTR get_window_long_ptr(int nIndex);
   LONG_PTR set_window_long_ptr(int nIndex, LONG_PTR l);


   bool _001ClientToScreen(POINT32 * lppoint);
   bool _001ScreenToClient(POINT32 * lppoint);
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
CLASS_DECL_CORE index oswindow_find(::user::interaction_impl* pinteraction);
CLASS_DECL_CORE oswindow oswindow_get(::user::interaction_impl* pinteraction);
CLASS_DECL_CORE oswindow oswindow_remove(::user::interaction_impl* pinteraction);
CLASS_DECL_CORE::user::interaction_impl* oswindow_interaction_impl(oswindow oswindow);
CLASS_DECL_CORE::user::interaction* oswindow_interaction(oswindow oswindow);
#if defined(__cplusplus_winrt)
CLASS_DECL_CORE Agile < Windows::UI::Core::CoreWindow > oswindow_core_window(oswindow window);
#endif

