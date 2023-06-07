// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"


namespace windowing
{


   class CLASS_DECL_AURA monitor :
      virtual public ::matter
   {
   public:


      ::index                                               m_iIndex;
      ::rectangle_i32                                       m_rectangle;
      ::rectangle_i32                                       m_rectangleWorkspace;
      ::pointer<::windowing::display>                      m_pdisplay;


      monitor();
      ~monitor() override;


      virtual void update_cache();


      virtual ::u32 monitor_color_temperature();
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma);


      virtual ::rectangle_i32 monitor_rectangle();
      virtual ::rectangle_i32 workspace_rectangle();


   };


} // namespace windowing



