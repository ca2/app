//
// Created to host save_image by camilo on 30/12/2021 15:40 <3ThomasBorregaardSorensen!!
// Renamed image::save_options by camilo on 2024-09-06 19:46 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace image
{


   class CLASS_DECL_AURA save_options
   {
   public:


      ::image::enum_format       m_eformat = ::image::e_format_none;
      int                        m_iQuality = -1;
      int                        m_iDpi = -1;

      save_options(){}
      save_options(const ::payload & payloadFile);


   };


} // namespace image



