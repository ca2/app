#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/primitive/particle.h"


namespace geometry
{


   class CLASS_DECL_ACME rotation
   {
   public:
      double   m_dCosPhi;
      double   m_dSinPhi;
      i32      m_iXCenter;
      i32      m_iYCenter;

      void rotate(::point_i32 * ppoint, i32 iCount);

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
      void rotate(i32 x, i32 y, ::point_i32 * ppoint, i32 iCount, double phi);

      void rotate(i32 x, i32 y, ::point_i32 * ppoint, i32 iCount, double cosphi, double sinphi);

      void rotate(i32 x, i32 y, ::point_f64 * ppoint, i32 iCount, double phi);

      void rotate(i32 x, i32 y, ::point_f64 * ppoint, i32 iCount, double cosphi, double sinphi);



      //void RandomPoint(::point_i32 * ppoint, const ::rectangle_i32 & rectangle);
      void deflate(::rectangle_i32 * prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);



   };


} // namespace geometry



