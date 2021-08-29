#include "framework.h"


image_array::image_array()
{

}


image_array::~image_array()
{


}


bool image_array::explode(::object * pobject, ::payload varFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
{

   return explode(pobject, ::size_i32(-1, -1), varFile, cols, rows, bCache, bCreateHelperMaps);

}


bool image_array::explode(::object * pobject, const ::size_i32 & sizeParam, ::payload varFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
{

   ::size_i32 size(sizeParam);

   auto pcontext = pobject->get_context()->m_pauracontext;

   auto pcontextimage = pcontext->context_image();

   auto pimageSource = pcontextimage->get_image(varFile);

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

         auto rectangleTarget = pimage->rectangle();

         auto rectangleSource = ::rectangle_i32_dimension(sizeSource.cx * col, sizeSource.cy * row, sizeSource.cx, sizeSource.cy);

         image_source imagesource(pimageSource, rectangleSource);

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         /*

         image_source imagesource();

         image_drawing_options imagedrawingoptions();

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         */

         pimage->draw(imagedrawing);

         add(pimage);

      }

   }

   return true;

}

