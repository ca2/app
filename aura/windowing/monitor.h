// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace windowing
{


   class CLASS_DECL_AURA monitor :
      virtual public ::matter
   {
   public:


      ::collection::index                                               m_iIndex;
      ::i32_rectangle                                       m_rectangle;
      ::i32_rectangle                                       m_rectangleWorkspace;
      ::i32_rectangle                                       m_rectangleFixedWorkspace;
      ::pointer<::windowing::display>                       m_pdisplay;


      monitor();
      ~monitor() override;


      virtual void update_cache();


      virtual ::u32 monitor_color_temperature();
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma);


      virtual ::i32_rectangle monitor_rectangle();
      virtual ::i32_rectangle workspace_rectangle();

      virtual ::i32_rectangle _workspace_rectangle();


      virtual void set_workspace_rectangle(const ::i32_rectangle & rectangle);

      virtual void set_workspace_rectangle_left(int left);
      virtual void set_workspace_rectangle_top(int top);
      virtual void set_workspace_rectangle_right(int right);
      virtual void set_workspace_rectangle_bottom(int bottom);


   };


} // namespace windowing



