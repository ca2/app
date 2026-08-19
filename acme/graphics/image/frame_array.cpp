#include "platform.h"
#include "frame_array.h"
//#include "aura/graphics/image/drawing.h"

namespace image
{


   image_frame_array::image_frame_array()
   {

      m_iLoop = 0;
      m_countLoop = 0;

   }


   image_frame_array::~image_frame_array()
   {

   }


   void image_frame_array::create_from_pixmap(::pixmap * ppixmap)
   {

      m_ppixmap = ppixmap;

   }


   ::pixmap * image_frame_array::get_pixmap()
   {

      if (this->count() <= 1)
      {

         return m_ppixmap;

      }

      return nullptr;

   }


   ::particle * image_frame_array::get_image()
   {

      if (this->count() <= 1)
      {

         return m_pparticleImage;

      }

      return nullptr;

   }





} // namespace image


