// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace windowing
{


   class CLASS_DECL_ACME monitor :
      virtual public ::matter
   {
   public:


      ::index                                               m_iIndex;
      ::rectangle_i32                                       m_rectangle;
      ::rectangle_i32                                       m_rectangleWorkspace;


      monitor();
      virtual ~monitor();


      virtual ::e_status update_cache();


   };


   using monitor_map = iptr_map < __pointer(monitor) >;


} // namespace windowing



