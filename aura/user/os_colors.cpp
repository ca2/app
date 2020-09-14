#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


#if !defined(WINDOWS_DESKTOP) && !defined(MACOS)

namespace user
{


   bool g_bSystemDarkMode;


   bool g_bAppDarkMode;

   void defer_calc_os_dark_mode()
   {

      ::get_context_system()->defer_calc_os_dark_mode();

   }


   CLASS_DECL_AURA void set_system_dark_mode(bool bDark)
   {

      g_bSystemDarkMode = bDark;

   }


   CLASS_DECL_AURA void set_app_dark_mode(bool bDark)
   {

      g_bAppDarkMode = bDark;

   }


   CLASS_DECL_AURA bool is_system_dark_mode()
   {

      defer_calc_os_dark_mode();

      return g_bSystemDarkMode;

   }


   CLASS_DECL_AURA bool is_app_dark_mode()
   {

      defer_calc_os_dark_mode();

      return g_bAppDarkMode;

   }


} // namespace user


#endif
