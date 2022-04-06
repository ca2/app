#include "framework.h"
#include "map.h"
#include "image.h"


::image * image_descriptor_map::operator[](const image_header & key)
{

   while (get_count() > m_iLimitCount)
   {

      erase_bigger();

   }

   auto & pimage = image_descriptor_map_base::operator [](key);

   if (pimage->is_null())
   {

      m_psystem->__construct(pimage);

      pimage->create(key.m_size);

   }

   return pimage;

}



void image_descriptor_map::erase_bigger()
{

   image_header keyFind;

   u64 uAreaMax = 0;

   auto passociation = get_start();

   while (passociation != nullptr)
   {

      if (passociation->element2()->reference_count() <= 1 && passociation->element2()->area() > uAreaMax)
      {

         uAreaMax = passociation->element2()->area();

         keyFind = passociation->element1();

      }

      passociation = passociation->m_pnext;

   }

   if (uAreaMax > 0)
   {

      erase_key(keyFind);

   }
   else
   {

      erase_key(get_start()->element1());

   }

}


image_pointer & size_image::operator[](const concrete < ::size_i32 > & size)
{

   bool bExists;

   return get(size, bExists);

}


image_pointer & size_image::get(const concrete < ::size_i32 > & size, bool & bExists)
{

   auto & pimage = ::map < concrete < ::size_i32 >, ::image_pointer >::operator [](size);

   if (pimage->is_null())
   {

      m_psystem->__construct(pimage);
      
      pimage->create(size);

      bExists = false;

   }
   else
   {

      bExists = true;

   }

   return pimage;

}



