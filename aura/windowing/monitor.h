// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


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
      virtual ~monitor();


      virtual void update_cache();

      virtual ::u32 get_monitor_color_temperature();
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma);


      virtual void get_monitor_rectangle(::RECTANGLE_I32 * prectangle);
      virtual void get_workspace_rectangle(::RECTANGLE_I32 * prectangle);


   };


   //using monitor_map = iptr_map < ::pointer<monitor >>


} // namespace windowing



