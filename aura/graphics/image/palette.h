#pragma once

#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

typedef void * HPALETTE;

#endif

namespace image
{
   class image_palette
   {
   public:


      image_palette();


      void create(::image::image *pimage);


      //HPALETTE m_hpalette;

   public:


      virtual ~image_palette();


   };
} //namespace image