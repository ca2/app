#pragma once




struct CLASS_DECL_APEX oswindow_data
{
public:


   ::message_queue *                        m_pmq;

   ::windowing::window *    m_pimpl;

   iptr_to_iptr *          m_plongptrmap;


   ::windowing::window* window();

   oswindow_data(::windowing::window* pimpl = nullptr);
   ~oswindow_data();

   bool is_child(::oswindow oswindow);
   ::oswindow get_parent();
   ::oswindow set_parent(::oswindow oswindow);
   bool show_window(int nCmdShow);
   LONG_PTR get_window_long_ptr(int nIndex);
   LONG_PTR set_window_long_ptr(int nIndex, LONG_PTR l);


   bool client_to_screen(POINT32 * lppoint);
   bool screen_to_client(POINT32 * lppoint);
   bool is_iconic();
   bool is_window_visible();


};



