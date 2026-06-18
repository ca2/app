#include "framework.h"
#include "geometry.h"


namespace geometry
{


   geometry::geometry()
   {

   }


   geometry::~geometry()
   {

   }


   void geometry::destroy()
   {

      ::particle::destroy();

   }


   ::f64 geometry::rotate_x(::f64 x, ::f64 y, ::f64 phi)
   {
      return x * cos(phi) - y * sin(phi);
   }

   ::f64 geometry::rotate_y(::f64 x, ::f64 y, ::f64 phi)
   {
      return x * sin(phi) + y * cos(phi);
   }

   void geometry::rotate(::i32 xParam, ::i32 yParam, ::i32_point * ppoint, ::i32 iCount, ::f64 phi)

   {
      ::f64 phicos = cos(phi);
      ::f64 phisin = sin(phi);
      rotate(xParam, yParam, ppoint, iCount, phicos, phisin);

   }

   void geometry::rotate(
      ::i32 xParam,
      ::i32 yParam,
      ::i32_point * ppoint,

      ::i32 iCount,
      ::f64 phicos,
      ::f64 phisin)
   {
      for (::i32 i = 0; i < iCount; i++)
      {
         ::f64 x = ppoint[i].x - xParam;

         ::f64 y = ppoint[i].y - yParam;

         ppoint[i].x = (::i32)(((x * phicos - y * phisin)) + xParam);

         ppoint[i].y = (::i32)(((x * phisin + y * phicos)) + yParam);

      }
   }

   void geometry::rotate(::i32 xParam, ::i32 yParam, ::f64_point * ppoint, ::i32 iCount, ::f64 phi)

   {
      ::f64 phicos = cos(phi);
      ::f64 phisin = sin(phi);
      rotate(xParam, yParam, ppoint, iCount, phicos, phisin);

   }

   void geometry::rotate(
      ::i32 xParam,
      ::i32 yParam,
      ::f64_point * ppoint,

      ::i32 iCount,
      ::f64 phicos,
      ::f64 phisin)
   {
      for (::i32 i = 0; i < iCount; i++)
      {
         ::f64 x = ppoint[i].x - xParam;

         ::f64 y = ppoint[i].y - yParam;

         ppoint[i].x = (::i32)(((x * phicos - y * phisin)) + xParam);

         ppoint[i].y = (::i32)(((x * phisin + y * phicos)) + yParam);

      }
   }


   //void geometry::RandomPoint(::i32_point * ppoint, const ::i32_rectangle & rectangle)
   //{

   //   ppoint->x = (::i32)Sy(rectangle.left,rectangle.right);

   //   ppoint->y = (::i32)random(rectangle.top,rectangle.bottom);

   //}


   ////////////////////////////////////////////////////////////////////////
   ////
   //// Function Name: deflate
   ////
   //// Purpose:
   //// Change rectangle dimension using its dimensions and the specified
   //// rates. For example, the dLeftRate machine the left position of the
   //// rectangle. If 0.0, it remains the same as the original left.
   //// If 1.0, it turns as the original right. If 0.4, it will be 40%
   //// of the width from left to right.
   ////
   //// Output:
   //// -1 if the creation of the ::user::impact failed.
   //// 0 if the creation of the ::user::impact succeeded.
   ////
   //// Author:
   //// Vanessa Testoni
   ////
   ////////////////////////////////////////////////////////////////////////
   //void geometry::deflate(::i32_rectangle * prectangle, ::f64 dLeftRate, ::f64 dRightRate, ::f64 dTopRate, ::f64 dBottomRate)

   //{
   //   ::i32_rectangle rectangle(prectangle);

   //   prectangle->left = range_rate(rectangle.left, rectangle.right, dLeftRate);

   //   prectangle->right = range_rate(rectangle.right, rectangle.left, dRightRate);

   //   prectangle->top = range_rate(rectangle.top, rectangle.bottom, dTopRate);

   //   prectangle->bottom = range_rate(rectangle.bottom, rectangle.top, dBottomRate);


   //}


   void rotation::rotate(::i32_point * ppoint, ::i32 iCount)

   {
      for (::i32 i = 0; i < iCount; i++)
      {
         long x = ppoint[i].x - m_iXCenter;

         long y = ppoint[i].y - m_iYCenter;

         ppoint[i].x = ((::i32)(x * m_dCosPhi - y * m_dSinPhi)) + m_iXCenter;

         ppoint[i].y = ((::i32)(x * m_dSinPhi + y * m_dCosPhi)) + m_iYCenter;

      }
   }


} // namespace geometry


