#include "platform.h"
#include "map.h"
#include "image.h"
#include "acme/platform/system.h"
#include "aura/graphics/draw2d/draw2d.h"


namespace image
{


   ::image::image_pointer & image_descriptor_map::operator[](const image_header & key)
   {

      while (get_count() > m_iLimitCount)
      {

         erase_bigger();

      }

      auto & pimage = BASE_PAIR_MAP::operator [](key);

      if (pimage->is_null())
      {

         system()->constructø(pimage);

         pimage->create_as_descriptor(key.m_size, m_pdraw2ddomain);

      }

      return pimage;

   }



   void image_descriptor_map::erase_bigger()
   {

      image_header itemFind;

      ::u64 uAreaMax = 0;

      auto iterator = this->begin();

      while (iterator.is_ok())
      {

         if (iterator->element2()->reference_count() <= 1 && iterator->element2()->area() > uAreaMax)
         {

            uAreaMax = iterator->element2()->area();

            itemFind = iterator->element1();

         }

         iterator++;

      }

      if (uAreaMax > 0)
      {

         erase(itemFind);

      }
      else
      {

         erase(this->begin()->key());

      }

   }


   ::image::image_pointer & size_image::operator[](const ::i32_size & size)
   {

      bool bExists;

      return get(size, bExists);

   }


   ::image::image_pointer & size_image::get(const ::i32_size & size, bool & bExists)
   {

      auto & pimage = ::map_base < ::i32_size, ::image::image_pointer >::operator [](size);

      if (pimage->is_null())
      {

         system()->constructø(pimage);

         pimage->create_as_descriptor(size, m_pdraw2ddomain);

         bExists = false;

      }
      else
      {

         bExists = true;

      }

      return pimage;

   }


} // namespace image



