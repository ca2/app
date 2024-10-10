#pragma once


namespace user
{

   extern CLASS_DECL_AURA critical_section * g_pcsImpl;

   extern CLASS_DECL_AURA map < oswindow, ::windowing::window * > * g_pmapImpl;

   CLASS_DECL_AURA void init_windowing();

   CLASS_DECL_AURA void term_windowing();


} // namespace user





//CLASS_DECL_AURA bool oswindow_assign(::windowing::window * pwindow, ::windowing::window * pimpl);
//CLASS_DECL_AURA ::windowing::window * pwindow_erase_impl(::windowing::window * pimpl);
//CLASS_DECL_AURA void oswindow_erase(::windowing::window * pwindow);
//CLASS_DECL_AURA ::windowing::window * pwindow_get(::windowing::window * pimpl);
//CLASS_DECL_AURA ::windowing::window * oswindow_interaction_impl(::windowing::window * pwindow);
//CLASS_DECL_AURA ::user::interaction * oswindow_interaction(::windowing::window * pwindow);


//#if defined(WINDOWS) || defined(LINUX)
//
//inline ::user::interaction * window_from_handle(::windowing::window * pwindow);
//
//inline ::user::interaction * window_from_handle(::windowing::window * pwindow)
//{
//
//   if(oswindow == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   critical_section_lock slOsWindow(::user::g_pcsUi);
//
//   return ::user::g_pmapUi->operator[](oswindow);
//
//}
//
//#else
//
//CLASS_DECL_AURA ::user::interaction * window_from_handle(::windowing::window * pwindow);
//
//#endif
