#pragma once


namespace image
{
   class CLASS_DECL_AURA image_dynamic
   {
   public:


      bool                 m_bStart;
      class ::time           m_timeStart;
      ::collection::index                m_iFrame;


      image_dynamic();
      image_dynamic(image_dynamic&& imagedynamic);
      ~image_dynamic();

   };
} // namespace image