#include "framework.h"
#include "acme/id.h"


namespace user
{


   bool g_bSystemDarkMode;


   bool g_bAppDarkMode;


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

      return g_bSystemDarkMode;

   }


   CLASS_DECL_ACME bool is_app_dark_mode()
   {

      return g_bAppDarkMode;

   }


   ::color g_colorSystemAppBackground;


   CLASS_DECL_ACME ::color get_system_app_background_color()
   {

      return g_colorSystemAppBackground;

   }


   CLASS_DECL_ACME void set_system_app_background_color(::color color)
   {

      g_colorSystemAppBackground = color;

   }


   double g_dSystemLuminance;


   CLASS_DECL_ACME double get_system_app_luminance()
   {


      return g_dSystemLuminance;

   }


   CLASS_DECL_ACME void set_system_app_luminance(double dLuminance)
   {

      g_dSystemLuminance = dLuminance;

   }


} // namespace user


static int g_iWeatherDarkness = 0;


CLASS_DECL_ACME int get_simple_ui_darkness()
{

   return g_iWeatherDarkness;

}


CLASS_DECL_ACME void set_simple_ui_darkness(int iWeatherDarkness)
{

   g_iWeatherDarkness = iWeatherDarkness;

}


color32_t argb_swap_rb(color32_t cr)
{

   return ARGB(
      colorref_get_a_value(cr),
      colorref_get_b_value(cr),
      colorref_get_g_value(cr),
      colorref_get_r_value(cr));

}


