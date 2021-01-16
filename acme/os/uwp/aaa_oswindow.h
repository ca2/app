#pragma once




struct CLASS_DECL_ACME oswindow_data
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
