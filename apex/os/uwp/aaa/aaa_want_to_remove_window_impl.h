#pragma once



namespace user
{


   class interaction;
   class interaction;


} // namespace user


struct CLASS_DECL_APEX oswindow_data
{
public:

   
   ::user::interaction * m_puserinteraction;

   ::user::interaction * window();

};


class oswindow_dataptra;



///static oswindow_dataptra * s_pdataptra;
CLASS_DECL_APEX int oswindow_find(::user::interaction * pinteraction);
CLASS_DECL_APEX oswindow oswindow_get(::user::interaction * pinteraction);
CLASS_DECL_APEX int oswindow_remove(::user::interaction * pinteraction);
#if defined(__cplusplus_winrt)
CLASS_DECL_APEX Windows::UI::Core::CoreWindow ^ get_os_window(oswindow window);
#endif
