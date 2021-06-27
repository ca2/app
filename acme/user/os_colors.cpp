#include "framework.h"
#include "acme/id.h"


namespace user
{


   //bool g_bSystemDarkMode;


   //bool g_bAppDarkMode;


   //CLASS_DECL_ACME void set_system_dark_mode(bool bDark)
   //{

   //   g_bSystemDarkMode = bDark;

   //}


   //CLASS_DECL_ACME void set_app_dark_mode(bool bDark)
   //{

   //   g_bAppDarkMode = bDark;

   //}


   //CLASS_DECL_ACME bool is_system_dark_mode()
   //{

   //   return g_bSystemDarkMode;

   //}


   //CLASS_DECL_ACME bool is_app_dark_mode()
   //{

   //   return g_bAppDarkMode;

   //}


   //::color::color g_colorSystemAppBackground;


   //CLASS_DECL_ACME ::color::color get_system_app_background_color()
   //{

   //   return g_colorSystemAppBackground;

   //}


   //CLASS_DECL_ACME void set_system_app_background_color(::color::color color)
   //{

   //   g_colorSystemAppBackground = color;

   //}


   //double g_dSystemLuminance;


   //CLASS_DECL_ACME double get_system_app_luminance()
   //{


   //   return g_dSystemLuminance;

   //}


   //CLASS_DECL_ACME void set_system_app_luminance(double dLuminance)
   //{

   //   g_dSystemLuminance = dLuminance;

   //}


} // namespace user



::color32_t argb_swap_rb(::color32_t color32)
{

   return argb(
      colorref_get_a_value(color32),
      colorref_get_b_value(color32),
      colorref_get_g_value(color32),
      colorref_get_r_value(color32));

}


