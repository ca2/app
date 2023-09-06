// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/rectangle.h"


namespace windowing
{


   class CLASS_DECL_AURA monitor :
      virtual public ::matter
   {
   public:


      ::index                                               m_iIndex;
      ::rectangle_i32                                       m_rectangle;
      ::rectangle_i32                                       m_rectangleWorkspace;
      ::rectangle_i32                                       m_rectangleFixedWorkspace;
      ::pointer<::windowing::display>                       m_pdisplay;


      monitor();
      ~monitor() override;


      virtual void update_cache();


      virtual ::u32 monitor_color_temperature();
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma);


      virtual ::rectangle_i32 monitor_rectangle();
      virtual ::rectangle_i32 workspace_rectangle();

      virtual ::rectangle_i32 _workspace_rectangle();


      virtual void set_workspace_rectangle(const ::rectangle_i32 & rectangle);

      virtual void set_workspace_rectangle_left(::i32 left);
      virtual void set_workspace_rectangle_top(::i32 top);
      virtual void set_workspace_rectangle_right(::i32 right);
      virtual void set_workspace_rectangle_bottom(::i32 bottom);


   };


} // namespace windowing



