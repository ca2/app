#include "framework.h"
#include "map.h"
#include "image.h"
#include "acme/platform/system.h"


namespace image
{


   ::image::image_pointer & image_descriptor_map_base::operator[](const image_header & key)
   {

      while (get_count() > m_iLimitCount)
      {

         erase_bigger();

      }

      auto & pimage = BASE_PAIR_MAP::operator [](key);

      if (pimage->is_null())
      {

         system()->__øconstruct(pimage);

         pimage->create(key.m_size);

      }

      return pimage;

   }



   void image_descriptor_map_base::erase_bigger()
   {

      image_header itemFind;

      unsigned long long uAreaMax = 0;

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


   ::image::image_pointer & size_image_base::operator[](const ::int_size & size)
   {

      bool bExists;

      return get(size, bExists);

   }


   ::image::image_pointer & size_image_base::get(const ::int_size & size, bool & bExists)
   {

      auto & pimage = ::map_base < ::int_size, ::image::image_pointer >::operator [](size);

      if (pimage->is_null())
      {

         system()->__øconstruct(pimage);

         pimage->create(size);

         bExists = false;

      }
      else
      {

         bExists = true;

      }

      return pimage;

   }


} // namespace image



