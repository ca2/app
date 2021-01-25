#include "framework.h"


image_array::image_array()
{

}


image_array::~image_array()
{


}


bool image_array::explode(::object * pobject, ::payload varFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
{

   return explode(pobject, ::size(-1, -1), varFile, cols, rows, bCache, bCreateHelperMaps);

}


bool image_array::explode(::object * pobject, const ::size & sizeParam, ::payload varFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
{

   ::size size(sizeParam);

   auto pimageSource = App(pobject).image().get_image(varFile);

   //if (!imageSource.load_image(varFile, bCreateHelperMaps))
   //{

   //   return false;

   //}

   if (pimageSource.nok())
   {

      return false;

   }

   ::size sizeSource(pimageSource->width() / cols, pimageSource->height() / rows);

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

         auto rectDst = pimage->rect();

         auto rectSrc = ::rect_dim(sizeSource.cx * col, sizeSource.cy * row, sizeSource.cx, sizeSource.cy);

         pimage->g()->stretch(rectDst, pimageSource, rectSrc);

         add(pimage);

      }

   }

   return true;

}

