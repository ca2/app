#include "framework.h"


image_array::image_array()
{

}


image_array::~image_array()
{


}


bool image_array::explode(::context_object * pcontextobject, ::payload varFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
{

   return explode(pcontextobject, ::size_i32(-1, -1), varFile, cols, rows, bCache, bCreateHelperMaps);

}


bool image_array::explode(::context_object * pcontextobject, const ::size_i32 & sizeParam, ::payload varFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
{

   ::size_i32 size(sizeParam);

   __pointer(::aura::application) papplication = pcontextobject->get_application();

   auto pimageSource = papplication->image().get_image(varFile);

   //if (!imageSource.load_image(varFile, bCreateHelperMaps))
   //{

   //   return false;

   //}

   if (pimageSource.nok())
   {

      return false;

   }

   ::size_i32 sizeSource(pimageSource->width() / cols, pimageSource->height() / rows);

   if (size.cx < 0)
   {

      size.cx = sizeSource.cx;

   }

   if (size.cy < 0)
   {

      size.cy = sizeSource.cy;

   }

   for (int row = 0; row < rows; row++)
   {

      for (int col = 0; col < cols; col++)
      {

         auto pimage = create_image(size);

         auto rectDst = pimage->rectangle();

         auto rectSrc = ::rect_dim(sizeSource.cx * col, sizeSource.cy * row, sizeSource.cx, sizeSource.cy);

         pimage->stretch(rectDst, pimageSource, rectSrc);

         add(pimage);

      }

   }

   return true;

}

