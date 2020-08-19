#include "framework.h"


image_pointer & size_image::operator[](const ::size & size)
{

   bool bExists;

   return get(size, bExists);

}


image_pointer & size_image::get(const ::size & size, bool & bExists)
{

   auto & pimage = ::keymap < ::size, ::image_pointer >::operator [](size);

   if (pimage->is_null())
   {

      __construct(pimage);
      
      pimage->create(size);

      bExists = false;

   }
   else
   {

      bExists = true;

   }

   return pimage;

}



