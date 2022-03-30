// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 02:54
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#include "framework.h"
#include "drawer.h"
#include "drawing.h"


void image_drawer::draw(const image_drawing & imagedrawing)
{

   if (::is_null(imagedrawing.m_pimagesource))
   {

      return;

   }

   if (has_blender())
   {

      if (_draw_blend(imagedrawing))
      {

         return;

      }

   }

   _draw_raw(imagedrawing);

}


//void image_drawer::_draw_raw(const ::rectangle_f64 & rectangleTarget, const ::image_drawing & imagedrawing, const ::rectangle_f64 & rectangleSource)
//{
//
//   if (rectangleTarget.size() == rectangleSource.size())
//   {
//
//      _draw_raw(rectangleTarget, imagedrawing, rectangleSource.top_left());
//
//   }
//   else
//   {
//
//      _stretch_raw(rectangleTarget, imagedrawing, rectangleSource);
//
//   }
//
//   return false;
//
//}
//
//
//void image_drawer::_draw_raw(const ::rectangle_f64 & rectangleTarget, const ::image_drawing & imagedrawing, const ::point_f64 & pointSrc)
//{
//
//   return false;
//
//}
//
//
//void image_drawer::_stretch_raw(const ::rectangle_f64 & rectangleTarget, const ::image_drawing & imagedrawing, const ::rectangle_f64 & rectangleSource)
//{
//
//   return false;
//
//}
//
//
//void image_drawer::_draw_blend(const ::rectangle_f64 & rectangleTarget, const ::image_drawing & imagedrawing, const ::rectangle_f64 & pointSrc)
//{
//
//   return false;
//
//}
//
//


bool image_drawer::has_blender() const
{

   return false;

}


void image_drawer::_draw_raw(const image_drawing & imagedrawing)
{

   auto rectangleSource = imagedrawing.source_rectangle();

   auto rectangleTarget = imagedrawing.target_rectangle();

   auto pimage = imagedrawing.image();

   if (rectangleSource.size() == rectangleTarget.size())
   {

      _draw_raw(rectangleTarget, pimage, imagedrawing, rectangleSource.top_left());

      return;

   }

   _stretch_raw(rectangleTarget, pimage, imagedrawing, rectangleSource);

}


void image_drawer::_draw_raw(const ::rectangle_f64 & rectangleTarget, image * pimage, const image_drawing_options & imagedrawingoptionsParam, const ::point_f64 & pointSrc)
{

   image_source imagesource(pimage, { pointSrc, rectangleTarget.size()});

   image_drawing_options imagedrawingoptions(imagedrawingoptionsParam);

   imagedrawingoptions.m_rectangleTarget = rectangleTarget;

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   _draw_raw(imagedrawing);

}


void image_drawer::_stretch_raw(const ::rectangle_f64 & rectangleTarget, image * pimage, const image_drawing_options & imagedrawingoptions, const ::rectangle_f64 & rectangleSource)
{

}



