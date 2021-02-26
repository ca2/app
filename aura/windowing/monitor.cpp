// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"


namespace windowing
{


   monitor::monitor()
   {


   }


   monitor::~monitor()
   {


   }


   ::e_status monitor::update_cache()
   {

      return ::success_none;

   }

   
   ::u32 monitor::get_monitor_color_temperature()
   {

      return 0;

   }


   bool monitor::adjust_monitor(::u32 dwTemperature, double dBrightness, double dwGamma)
   {

      return false;

   }


   bool monitor::get_monitor_rectangle(::RECTANGLE_I32 * prectangle)
   {

      __copy(prectangle, m_rectangle);

      return true;

   }


   bool monitor::get_workspace_rectangle(::RECTANGLE_I32 * prectangle)
   {

      __copy(prectangle, m_rectangleWorkspace);

      return true;

   }


} // namespace windowing



