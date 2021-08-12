// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 02:54
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#include "framework.h"


bool image_drawer::draw(const image_drawing & imagedrawing)
{

   if (::is_null(imagedrawing.m_pimage))
   {

      return false;

   }

   if (_draw_blend(imagedrawing))
   {

      return true;

   }

   if (_draw_raw(imagedrawing))
   {

      return true;

   }

   return false;

}


//bool image_drawer::_draw_raw(const ::rectangle_f64 & rectDst, const ::image_drawing & imagedrawing, const ::rectangle_f64 & rectSrc)
//{
//
//   if (rectDst.size() == rectSrc.size())
//   {
//
//      _draw_raw(rectDst, imagedrawing, rectSrc.top_left());
//
//   }
//   else
//   {
//
//      _stretch_raw(rectDst, imagedrawing, rectSrc);
//
//   }
//
//   return false;
//
//}
//
//
//bool image_drawer::_draw_raw(const ::rectangle_f64 & rectDst, const ::image_drawing & imagedrawing, const ::point_f64 & pointSrc)
//{
//
//   return false;
//
//}
//
//
//bool image_drawer::_stretch_raw(const ::rectangle_f64 & rectDst, const ::image_drawing & imagedrawing, const ::rectangle_f64 & rectSrc)
//{
//
//   return false;
//
//}
//
//
//bool image_drawer::_draw_blend(const ::rectangle_f64 & rectDst, const ::image_drawing & imagedrawing, const ::rectangle_f64 & pointSrc)
//{
//
//   return false;
//
//}
//
//


bool image_drawer::_draw_raw(const image_drawing & imagedrawing)
{

   if (imagedrawing.m_rectangleSource.size() == imagedrawing.m_rectangleTarget.size())
   {

      return _draw_raw(imagedrawing.m_rectangleTarget, imagedrawing.m_pimage, imagedrawing, imagedrawing.m_rectangleSource.top_left());

   }
   else
   {

      return _stretch_raw(imagedrawing.m_rectangleTarget, imagedrawing.m_pimage, imagedrawing, imagedrawing.m_rectangleSource);

   }

   return false;

}


bool image_drawer::_draw_raw(const ::rectangle_f64 & rectDst, image * pimage, const image_drawing_options & imagedrawingoptions, const ::point_f64 & pointSrc)
{

   return false;

}


bool image_drawer::_stretch_raw(const ::rectangle_f64 & rectDst, image * pimage, const image_drawing_options & imagedrawingoptions, const ::rectangle_f64 & rectSrc)
{

   return false;

}



