#include "framework.h"
#include "acme/id.h"


#if !defined(WINDOWS_DESKTOP) && !defined(MACOS)

namespace user
{


   bool g_bSystemDarkMode;


   bool g_bAppDarkMode;

   void defer_calc_os_dark_mode()
   {

      system_call_update(id_calc_os_dark_mode);

   }


   CLASS_DECL_ACME void set_system_dark_mode(bool bDark)
   {

      g_bSystemDarkMode = bDark;

   }


   CLASS_DECL_ACME void set_app_dark_mode(bool bDark)
   {

      g_bAppDarkMode = bDark;

   }


   CLASS_DECL_ACME bool is_system_dark_mode()
   {

      defer_calc_os_dark_mode();

      return g_bSystemDarkMode;

   }


   CLASS_DECL_ACME bool is_app_dark_mode()
   {

      //defer_calc_os_dark_mode();

      return g_bAppDarkMode;

   }


} // namespace user


#endif




static int g_iWeatherDarkness = 0;


CLASS_DECL_ACME int get_simple_ui_darkness()
{

   return g_iWeatherDarkness;

}


CLASS_DECL_ACME void set_simple_ui_darkness(int iWeatherDarkness)
{

   g_iWeatherDarkness = iWeatherDarkness;

}



COLORREF argb_swap_rb(COLORREF cr)
{
   return ARGB(
      colorref_get_a_value(cr),
      colorref_get_b_value(cr),
      colorref_get_g_value(cr),
      colorref_get_r_value(cr));
}



