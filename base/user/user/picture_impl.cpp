// From picture.cpp by camilo on 2022-09-04 01:19 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "picture_impl.h"
//#include <math.h>
//#include "aura/graphics/draw2d/matrix.h"
//#include "aura/graphics/image/image.h"
//#include "aura/graphics/image/drawing.h"
//#include "picture.h"


//property & operator << (property & property, const RECTANGLE_F64 & rectangle)
//{
//
//   property["left"] = rectangle.left;
//   property["top"] = rectangle.top;
//   property["right"] = rectangle.right;
//   property["bottom"] = rectangle.bottom;
//
//   return property;
//
//}
//
//property & operator >> (property & property, RECTANGLE_F64 & rectangle)
//{
//
//   property["left"].as(rectangle.left);
//   rectangle.top = property["top"].f64();
//   rectangle.right = property["right"].f64();
//   rectangle.bottom = property["bottom"].f64();
//
//   return property;
//
//}



namespace user
{


   picture_impl::picture_impl()
   {

      set_flag(e_flag_default_io_exchange);

      m_dZoom = 1.0;
      m_pointDrag2.x = 0.0;
      m_pointDrag2.y = 0.0;


      m_bOutline = false;
      m_iOutlineWidth = 7;
      m_hlsOutline.m_dH = 0.0;
      m_hlsOutline.m_dL = 0.0;
      m_hlsOutline.m_dS = 0.0;

      m_bGlowDropShadow = false;
      m_iGlowDropShadowOffset = 12;
      m_iGlowDropShadowBlur = 4;
      m_hlsGlowDropShadow.m_dH = 0.0;
      m_hlsGlowDropShadow.m_dL = 0.0;
      m_hlsGlowDropShadow.m_dS = 0.0;

      m_iBlur = 0;
      m_bGrayscale = false;
      m_bInvert = false;
      m_iOpacity = 100;
      m_iSaturation = 100;

   }


   picture_impl::~picture_impl()
   {


   }

   //void picture_impl::exchange(::stream & stream)
   //{

   //   __EXCHANGE(rectangle);
   //   __EXCHANGE(rectangleDrawing);
   //   __EXCHANGE(rectangleCursor);
   //   __EXCHANGE(bDrag);
   //   __EXCHANGE(dRotate);
   //   __EXCHANGE(rectangleBounding);
   //   __EXCHANGE(polygon);
   //   __EXCHANGE(polygonDrawing);
   //   __EXCHANGE(pointaCursor);
   //   __EXCHANGE(dZoom);
   //   __EXCHANGE(pointDrag2);


   //   __EXCHANGE(bOutline);
   //   __EXCHANGE(iOutlineWidth);
   //   __EXCHANGE(hlsOutline);

   //   __EXCHANGE(bGlowDropShadow);
   //   __EXCHANGE(iGlowDropShadowOffset);
   //   __EXCHANGE(iGlowDropShadowBlur);
   //   __EXCHANGE(hlsGlowDropShadow);

   //   __EXCHANGE(iBlur);
   //   __EXCHANGE(bGrayscale);
   //   __EXCHANGE(bInvert);
   //   __EXCHANGE(iOpacity);
   //   __EXCHANGE(iSaturation);


   //}





} // namespace user



