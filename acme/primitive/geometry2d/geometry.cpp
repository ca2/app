#include "framework.h"


namespace geometry
{


   geometry::geometry()
   {

   }


   geometry::~geometry()
   {

   }


   ::estatus geometry::initialize(::layered * pobjectContext)
   {

      auto estatus = ::matter::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void geometry::finalize()
   {

      ::matter::finalize();

   }


   double geometry::rotate_x(double x, double y, double phi)
   {
      return x * cos(phi) - y * sin(phi);
   }

   double geometry::rotate_y(double x, double y, double phi)
   {
      return x * sin(phi) + y * cos(phi);
   }

   void geometry::rotate(i32 xParam, i32 yParam, POINT32 * ppoint, i32 iCount, double phi)

   {
      double phicos = cos(phi);
      double phisin = sin(phi);
      rotate(xParam, yParam, ppoint, iCount, phicos, phisin);

   }

   void geometry::rotate(
      i32 xParam,
      i32 yParam,
      POINT32 * ppoint,

      i32 iCount,
      double phicos,
      double phisin)
   {
      for (i32 i = 0; i < iCount; i++)
      {
         double x = ppoint[i].x - xParam;

         double y = ppoint[i].y - yParam;

         ppoint[i].x = (::i32)(((x * phicos - y * phisin)) + xParam);

         ppoint[i].y = (::i32)(((x * phisin + y * phicos)) + yParam);

      }
   }

   void geometry::rotate(i32 xParam, i32 yParam, POINTD * ppoint, i32 iCount, double phi)

   {
      double phicos = cos(phi);
      double phisin = sin(phi);
      rotate(xParam, yParam, ppoint, iCount, phicos, phisin);

   }

   void geometry::rotate(
      i32 xParam,
      i32 yParam,
      POINTD * ppoint,

      i32 iCount,
      double phicos,
      double phisin)
   {
      for (i32 i = 0; i < iCount; i++)
      {
         double x = ppoint[i].x - xParam;

         double y = ppoint[i].y - yParam;

         ppoint[i].x = (::i32)(((x * phicos - y * phisin)) + xParam);

         ppoint[i].y = (::i32)(((x * phisin + y * phicos)) + yParam);

      }
   }


   //void geometry::RandomPoint(POINT32 * ppoint, const ::rect & rect)
   //{

   //   ppoint->x = (::i32)Sy(rect.left,rect.right);

   //   ppoint->y = (::i32)__random(rect.top,rect.bottom);

   //}


   //////////////////////////////////////////////////////////////////////
   //
   // Function Name: deflate
   //
   // Purpose:
   // Change rectangle dimension using its dimensions and the specified
   // rates. For example, the dLeftRate machine the left position of the
   // rectangle. If 0.0, it remains the same as the original left.
   // If 1.0, it turns as the original right. If 0.4, it will be 40%
   // of the width from left to right.
   //
   // Output:
   // -1 if the creation of the ::user::impact failed.
   // 0 if the creation of the ::user::impact succeeded.
   //
   // Author:
   // Vanessa Testoni
   //
   //////////////////////////////////////////////////////////////////////
   void geometry::deflate(RECT32 * prect, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)

   {
      ::rect rect(prect);

      prect->left = range_rate(rect.left, rect.right, dLeftRate);

      prect->right = range_rate(rect.right, rect.left, dRightRate);

      prect->top = range_rate(rect.top, rect.bottom, dTopRate);

      prect->bottom = range_rate(rect.bottom, rect.top, dBottomRate);


   }


   void rotation::rotate(POINT32 * ppoint, i32 iCount)

   {
      for (i32 i = 0; i < iCount; i++)
      {
         long x = ppoint[i].x - m_iXCenter;

         long y = ppoint[i].y - m_iYCenter;

         ppoint[i].x = ((::i32)(x * m_dCosPhi - y * m_dSinPhi)) + m_iXCenter;

         ppoint[i].y = ((::i32)(x * m_dSinPhi + y * m_dCosPhi)) + m_iYCenter;

      }
   }


} // namespace geometry


