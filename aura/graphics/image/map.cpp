#include "framework.h"
#include "map.h"
#include "image.h"
#include "acme/platform/system.h"


namespace image
{


   ::image::image * image_descriptor_map::operator[](const image_header & key)
   {

      while (get_count() > m_iLimitCount)
      {

         erase_bigger();

      }

      auto & pimage = image_descriptor_map_base::operator [](key);

      if (pimage->is_null())
      {

         system()->__øconstruct(pimage);

         pimage->create(key.m_size);

      }

      return pimage;

   }



   void image_descriptor_map::erase_bigger()
   {

      image_header itemFind;

      huge_natural uAreaMax = 0;

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

         erase_item(itemFind);

      }
      else
      {

         erase_item(this->begin()->item());

      }

   }


   ::image::image_pointer & size_image::operator[](const ::int_size & size)
   {

      bool bExists;

      return get(size, bExists);

   }


   ::image::image_pointer & size_image::get(const ::int_size & size, bool & bExists)
   {

      auto & pimage = ::map < ::int_size, ::image::image_pointer >::operator [](size);

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



