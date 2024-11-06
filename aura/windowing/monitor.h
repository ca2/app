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
      ::int_rectangle                                       m_rectangle;
      ::int_rectangle                                       m_rectangleWorkspace;
      ::int_rectangle                                       m_rectangleFixedWorkspace;
      ::pointer<::windowing::display>                       m_pdisplay;


      monitor();
      ~monitor() override;


      virtual void update_cache();


      virtual unsigned int monitor_color_temperature();
      virtual bool adjust_monitor( unsigned int dwTemperature, double dBrightness, double dwGamma);


      virtual ::int_rectangle monitor_rectangle();
      virtual ::int_rectangle workspace_rectangle();

      virtual ::int_rectangle _workspace_rectangle();


      virtual void set_workspace_rectangle(const ::int_rectangle & rectangle);

      virtual void set_workspace_rectangle_left(int left);
      virtual void set_workspace_rectangle_top(int top);
      virtual void set_workspace_rectangle_right(int right);
      virtual void set_workspace_rectangle_bottom(int bottom);


   };


} // namespace windowing



