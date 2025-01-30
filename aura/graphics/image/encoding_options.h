//
// Created to host save_image by camilo on 30/12/2021 15:40 <3ThomasBorregaardSorensen!!
// Renamed image::save_options by camilo on 2024-09-06 19:46 <3ThomasBorregaardSorensen!!
// Renamed to image::encoding_options by camilo on 2025-01-29 12:59 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace image
{


   class CLASS_DECL_AURA encoding_options
   {
   public:


      ::image::enum_format       m_eformat = ::image::e_format_none;
      int                        m_iQuality = -1;
      int                        m_iDpi = -1;

      encoding_options(){}
      encoding_options(const ::payload & payloadFile);


   };


} // namespace image



