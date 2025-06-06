#include "framework.h"
#include "acme/prototype/collection/map.h"


#define DEBUG_LEVEL 0

//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_ACME void os_set_window_procedure(WNDPROC puserinteractionproc);
//
//
//CLASS_DECL_AURA WNDPROC windows_user_interaction_impl_get_window_procedure();
//
//#endif

//namespace user
//{
//
//
//   critical_section * g_pcsImpl = nullptr;
//   map < oswindow, ::windowing::window * > * g_pmapImpl = nullptr;
//   map < ::windowing::window *, oswindow > * g_pmapHandle = nullptr;
//
//
//   CLASS_DECL_AURA void init_windowing()
//   {
//
//      g_pcsImpl = ___new critical_section();
//
//      g_pmapImpl = memory_new map < oswindow, ::windowing::window * >;
//
//      g_pmapHandle = memory_new  map < ::windowing::window *, oswindow >;
//      
////      
////#ifdef WINDOWS_DESKTOP
////
////      os_set_window_procedure(windows_user_interaction_impl_get_window_procedure());
////      
////#endif
//
//   }
//
//
//   CLASS_DECL_AURA void term_windowing()
//   {
//
//      ::acme::del(g_pmapImpl);
//
//      ::acme::del(g_pmapHandle);
//
//      ::acme::del(g_pcsImpl);
//
//   }
//
//
//} // namespace user


//CLASS_DECL_AURA bool oswindow_assign(oswindow, ::windowing::window * pimpl)
//{
//
//   if (oswindow == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (pimpl == nullptr)
//   {
//
//      return false;
//
//   }
//
//   critical_section_lock slOsWindow(::user::g_pcsImpl);
//
//   ::user::g_pmapImpl->set_at(oswindow, pimpl);
//
//   ::user::g_pmapHandle->set_at(pimpl, oswindow);
//
//   return true;
//
//}
//

//CLASS_DECL_AURA ::windowing::window * pwindow_erase_impl(::windowing::window * pimpl)
//{
//
//   ASSERT(pimpl != nullptr);
//
//   if (pimpl == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   critical_section_lock slOsWindow(::user::g_pcsImpl);
//
//   ::windowing::window * pwindow = ::user::g_pmapHandle->operator[](pimpl);
//
//   if (::user::g_pmapImpl->erase_key(oswindow))
//   {
//
//#if DEBUG_LEVEL > 0
//
//      informationf("::user::g_pmapImpl erased oswindow");
//
//#endif
//
//   }
//
//   if(::user::g_pmapImpl->erase_key((::oswindow) pimpl->m_pwindow->get_os_data()))
//   {
//
//#if DEBUG_LEVEL > 0
//
//      informationf("::user::g_pmapImpl erased pimpl->m_oswindow");
//
//#endif
//
//   }
//
//   if (::user::g_pmapHandle->erase_key(pimpl))
//   {
//
//#if DEBUG_LEVEL > 0
//
//      informationf("::user::g_pmapHandle erased pimpl");
//
//#endif
//
//   }
//
//
//   return oswindow;
//
//}


//CLASS_DECL_AURA void oswindow_erase(::windowing::window * pwindow)
//{
//
//   ASSERT(oswindow != nullptr);
//
//   if (oswindow == nullptr)
//   {
//
//      return;
//
//   }
//
//   {
//
//      critical_section_lock slOsWindow(::user::g_pcsImpl);
//
//      if (::user::g_pmapImpl->erase_key(oswindow))
//      {
//
//#if DEBUG_LEVEL > 0
//
//         informationf("::user::g_pmapImpl erased oswindow");
//
//#endif
//
//      }
//
//   }
//
//   {
//
//      synchronous_lock slSystem(psystem->synchronization());
//
//      if (psystem->m_pwindowmap->m_map.erase_key(oswindow))
//      {
//
//#if DEBUG_LEVEL > 0
//
//         informationf("psystem->m_pwindowmap erased oswindow");
//
//#endif
//
//      }
//
//   }
//
//}



