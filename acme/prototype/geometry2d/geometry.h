#pragma once


#include "acme/prototype/mathematics/mathematics.h"


namespace geometry
{


   class CLASS_DECL_ACME rotation
   {
   public:
      double   m_dCosPhi;
      double   m_dSinPhi;
      int      m_iXCenter;
      int      m_iYCenter;

      void rotate(::point_i32 * ppoint, int iCount);

   };

   class CLASS_DECL_ACME geometry :
      virtual public ::particle
   {
   public:


      geometry();
      ~geometry() override;


      //virtual void initialize(::particle * pparticle) override;
      void destroy() override;


      double rotate_y(double x, double y, double phi);
      double rotate_x(double x, double y, double phi);
      void rotate(int x, int y, ::point_i32 * ppoint, int iCount, double phi);

      void rotate(int x, int y, ::point_i32 * ppoint, int iCount, double cosphi, double sinphi);

      void rotate(int x, int y, ::point_f64 * ppoint, int iCount, double phi);

      void rotate(int x, int y, ::point_f64 * ppoint, int iCount, double cosphi, double sinphi);



      //void RandomPoint(::point_i32 * ppoint, const ::rectangle_i32 & rectangle);
      void deflate(::rectangle_i32 * prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);


      template < primitive_rectangle RECTANGLE >
      inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r)
      {

         return { mathematics()->random(r.left(), r.right()), mathematics()->random(r.top(), r.bottom()) };

      }


      template < primitive_rectangle RECTANGLE >
      inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r, double dRate)
      {

         auto rectangle = r;

         rectangle.rate(dRate);

         return random_point(rectangle);

      }





   };


} // namespace geometry



