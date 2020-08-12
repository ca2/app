#pragma once



namespace user
{


   class interaction;
//   class interaction;
//
//
} // namespace user


struct CLASS_DECL_BASE oswindow_data
{
public:

   
   ::user::interaction_impl * m_pimpl;

   ::user::interaction_impl * window();

};
//
//
//class oswindow_dataptra;
//
//
//
/////static oswindow_dataptra * s_pdataptra;
CLASS_DECL_BASE index oswindow_find(::user::interaction_impl * pinteraction);
CLASS_DECL_BASE oswindow oswindow_get(::user::interaction_impl * pinteraction);
CLASS_DECL_BASE oswindow oswindow_remove(::user::interaction_impl * pinteraction);
#if defined(__cplusplus_winrt)
//CLASS_DECL_BASE Agile<Windows::UI::Core::CoreWindow> get_os_window(oswindow window);
CLASS_DECL_BASE Agile < Windows::UI::Core::CoreWindow > get_os_window(oswindow window);

#endif

