// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "acme/platform/system.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/monitor.h"
#include "aura/windowing/desktop_environment.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/user.h"
#include "aura/platform/session.h"


namespace windowing
{


   monitor::monitor()
   {


   }


   monitor::~monitor()
   {


   }


   void monitor::update_cache()
   {

      //return ::success_none;

   }

   
   ::u32 monitor::monitor_color_temperature()
   {

      return 0;

   }


   bool monitor::adjust_monitor(::u32 dwTemperature, double dBrightness, double dwGamma)
   {

      return false;

   }


   ::rectangle_i32 monitor::monitor_rectangle()
   {

      auto psession = acmesession()->m_paurasession;

      auto pdesktopenvironment = psession->user()->m_pdesktopenvironment;

      pdesktopenvironment->get_monitor_rectangle(m_iIndex, m_rectangle);

      return m_rectangle;

   }


   ::rectangle_i32 monitor::workspace_rectangle()
   {

      auto psession = acmesession()->m_paurasession;

      auto pdesktopenvironment = psession->user()->m_pdesktopenvironment;

      pdesktopenvironment->get_workspace_rectangle(m_iIndex, m_rectangleWorkspace);

      return m_rectangleWorkspace;

   }


} // namespace windowing



