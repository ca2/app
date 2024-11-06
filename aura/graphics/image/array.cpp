#include "framework.h"
#include "array.h"
#include "drawing.h"
#include "image.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "aura/graphics/image/context.h"
#include "aura/platform/context.h"


namespace image
{


   image_array::image_array()
   {

   }


   image_array::~image_array()
   {


   }


   bool image_array::explode(::particle * pparticle, ::payload payloadFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
   {

      return explode(pparticle, ::size_i32(-1, -1), payloadFile, cols, rows, bCache, bCreateHelperMaps);

   }


   bool image_array::explode(::particle * pparticle, const ::size_i32 & sizeParam, ::payload payloadFile, int cols, int rows, bool bCache, bool bCreateHelperMaps)
   {

      ::size_i32 size(sizeParam);

      auto pimageSource = image()->get_image(payloadFile);

      //if (!imageSource.load_image(payloadFile, bCreateHelperMaps))
      //{

      //   return false;

      //}

      if (pimageSource.nok())
      {

         return false;

      }

      ::size_i32 sizeSource(pimageSource->width() / cols, pimageSource->height() / rows);

      if (size.cx() < 0)
      {

         size.cx() = sizeSource.cx();

      }

      if (size.cy() < 0)
      {

         size.cy() = sizeSource.cy();

      }

      for (int row = 0; row < rows; row++)
      {

         for (int col = 0; col < cols; col++)
         {

            auto pimage = pparticle->image()->create_image(size);

            auto rectangleTarget = pimage->rectangle();

            auto rectangleSource = ::rectangle_int_dimension(sizeSource.cx() * col, sizeSource.cy() * row, sizeSource.cx(), sizeSource.cy());

            ::image::image_source imagesource(pimageSource, rectangleSource);

            ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            /*

            ::image::image_source imagesource();

            ::image::image_drawing_options imagedrawingoptions();

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            */

            pimage->draw(imagedrawing);

            add_image(pimage);

         }

      }

      return true;

   }


} // namespace image



