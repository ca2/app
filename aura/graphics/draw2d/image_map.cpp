#include "framework.h"


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



