#include "framework.h"
#include "aura/user/_user.h"


#define DEBUG_LEVEL 0

//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_ACME void os_set_window_procedure(WNDPROC puserinteractionproc);
//
//
//CLASS_DECL_AURA WNDPROC windows_user_interaction_impl_get_window_procedure();
//
//#endif

namespace user
{


   critical_section * g_pcsImpl = nullptr;
   map < oswindow, ::user::interaction_impl * > * g_pmapImpl = nullptr;
   map < ::user::interaction_impl *, oswindow > * g_pmapHandle = nullptr;


   CLASS_DECL_AURA void init_windowing()
   {

      g_pcsImpl = new critical_section();

      g_pmapImpl = new map < oswindow, ::user::interaction_impl * >;

      g_pmapHandle = new  map < ::user::interaction_impl *, oswindow >;
      
//      
//#ifdef WINDOWS_DESKTOP
//
//      os_set_window_procedure(windows_user_interaction_impl_get_window_procedure());
//      
//#endif

   }


   CLASS_DECL_AURA void term_windowing()
   {

      ::acme::del(g_pmapImpl);

      ::acme::del(g_pmapHandle);

      ::acme::del(g_pcsImpl);

   }


} // namespace user


//CLASS_DECL_AURA bool oswindow_assign(oswindow, ::user::interaction_impl * pimpl)
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

//CLASS_DECL_AURA ::windowing::window * pwindow_remove_impl(::user::interaction_impl * pimpl)
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
//   if (::user::g_pmapImpl->remove_key(oswindow))
//   {
//
//#if DEBUG_LEVEL > 0
//
//      ::output_debug_string("::user::g_pmapImpl removed oswindow");
//
//#endif
//
//   }
//
//   if(::user::g_pmapImpl->remove_key((::oswindow) pimpl->m_pwindow->get_os_data()))
//   {
//
//#if DEBUG_LEVEL > 0
//
//      ::output_debug_string("::user::g_pmapImpl removed pimpl->m_oswindow");
//
//#endif
//
//   }
//
//   if (::user::g_pmapHandle->remove_key(pimpl))
//   {
//
//#if DEBUG_LEVEL > 0
//
//      ::output_debug_string("::user::g_pmapHandle removed pimpl");
//
//#endif
//
//   }
//
//
//   return oswindow;
//
//}


//CLASS_DECL_AURA void oswindow_remove(::windowing::window * pwindow)
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
//      if (::user::g_pmapImpl->remove_key(oswindow))
//      {
//
//#if DEBUG_LEVEL > 0
//
//         ::output_debug_string("::user::g_pmapImpl removed oswindow");
//
//#endif
//
//      }
//
//   }
//
//   {
//
//      synchronization_lock slSystem(psystem->mutex());
//
//      if (psystem->m_pwindowmap->m_map.remove_key(oswindow))
//      {
//
//#if DEBUG_LEVEL > 0
//
//         ::output_debug_string("psystem->m_pwindowmap removed oswindow");
//
//#endif
//
//      }
//
//   }
//
//}



