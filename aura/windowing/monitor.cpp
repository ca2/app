// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "desktop_environment.h"
#include "display.h"
#include "monitor.h"
#include "acme/platform/system.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/user.h"
#include "aura/platform/session.h"


namespace windowing
{


   monitor::monitor()
   {

      m_rectangleFixedWorkspace.left() = I32_MINIMUM;
      m_rectangleFixedWorkspace.top() = I32_MINIMUM;
      m_rectangleFixedWorkspace.right() = I32_MINIMUM;
      m_rectangleFixedWorkspace.bottom() = I32_MINIMUM;

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

      auto psession = session()->m_paurasession;

      auto pdesktopenvironment = psession->user()->m_pdesktopenvironment;

      pdesktopenvironment->get_monitor_rectangle(m_iIndex, &m_rectangle);

      return m_rectangle;

   }


   ::rectangle_i32 monitor::workspace_rectangle()
   {

      if(m_rectangleFixedWorkspace.left() != I32_MINIMUM
      && m_rectangleFixedWorkspace.top() != I32_MINIMUM
      && m_rectangleFixedWorkspace.right() != I32_MINIMUM
      && m_rectangleFixedWorkspace.bottom() != I32_MINIMUM)
      {

         information() << "monitor returning fixed workspace rectangle : " << m_rectangleFixedWorkspace;

         return m_rectangleFixedWorkspace;

      }

      ::rectangle_i32 rectangleWorkspace = _workspace_rectangle();

      for(auto i = 0; i < 4; i++)
      {

         if (m_rectangleFixedWorkspace.coordinate(i) != I32_MINIMUM)
         {

            rectangleWorkspace.coordinate(i) = m_rectangleFixedWorkspace.coordinate(i);

         }

      }

      return rectangleWorkspace;

   }


   ::rectangle_i32 monitor::_workspace_rectangle()
   {

      information() << "monitor::_workspace_rectangle";

      auto rectangleMonitor = monitor_rectangle();

      information() << "monitor::_workspace_rectangle monitor_rectangle : " << rectangleMonitor;

      for(auto & r : m_pdisplay->m_rectangleaWorkAreas)
      {

         if(rectangleMonitor.contains(r))
         {

            return r;

         }

      }

      auto psession = session()->m_paurasession;

      auto pdesktopenvironment = psession->user()->m_pdesktopenvironment;

      pdesktopenvironment->get_workspace_rectangle(m_iIndex, &m_rectangleWorkspace);

      return m_rectangleWorkspace;

   }


   void monitor::set_workspace_rectangle(const ::rectangle_i32 & rectangle)
   {

      m_rectangleFixedWorkspace = rectangle;

   }


   void monitor::set_workspace_rectangle_left(::i32 left)
   {

      m_rectangleFixedWorkspace.left() = left;

      information() << "monitor::fixed_workspace left : " << left;

   }


   void monitor::set_workspace_rectangle_top(::i32 top)
   {

      m_rectangleFixedWorkspace.top() = top;

      information() << "monitor::fixed_workspace top : " << top;

   }


   void monitor::set_workspace_rectangle_right(::i32 right)
   {

      m_rectangleFixedWorkspace.right() = right;

      information() << "monitor::fixed_workspace right : " << right;

   }


   void monitor::set_workspace_rectangle_bottom(::i32 bottom)
   {

      m_rectangleFixedWorkspace.bottom() = bottom;

      information() << "monitor::fixed_workspace bottom : " << bottom;

   }


} // namespace windowing



