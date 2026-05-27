#pragma once


#include "acme/prototype/mathematics/mathematics.h"


namespace geometry
{


   class CLASS_DECL_ACME rotation
   {
   public:
      ::f64   m_dCosPhi;
      ::f64   m_dSinPhi;
      ::i32      m_iXCenter;
      ::i32      m_iYCenter;

      void rotate(::i32_point * ppoint, ::i32 iCount);

   };

   class CLASS_DECL_ACME geometry :
      virtual public ::particle
   {
   public:


      geometry();
      ~geometry() override;


      //virtual void initialize(::particle * pparticle) override;
      void destroy() override;


      ::f64 rotate_y(::f64 x, ::f64 y, ::f64 phi);
      ::f64 rotate_x(::f64 x, ::f64 y, ::f64 phi);
      void rotate(::i32 x, ::i32 y, ::i32_point * ppoint, ::i32 iCount, ::f64 phi);

      void rotate(::i32 x, ::i32 y, ::i32_point * ppoint, ::i32 iCount, ::f64 cosphi, ::f64 sinphi);

      void rotate(::i32 x, ::i32 y, ::f64_point * ppoint, ::i32 iCount, ::f64 phi);

      void rotate(::i32 x, ::i32 y, ::f64_point * ppoint, ::i32 iCount, ::f64 cosphi, ::f64 sinphi);



      //void RandomPoint(::i32_point * ppoint, const ::i32_rectangle & rectangle);
      void deflate(::i32_rectangle * prectangle, ::f64 dLeftRate, ::f64 dRightRate, ::f64 dTopRate, ::f64 dBottomRate);


      template < prototype_rectangle RECTANGLE >
      inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r)
      {

         return { mathematics()->random(r.left, r.right), mathematics()->random(r.top, r.bottom) };

      }


      template < prototype_rectangle RECTANGLE >
      inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r, ::f64 dRate)
      {

         auto rectangle = r;

         rectangle.rate(dRate);

         return random_point(rectangle);

      }





   };


} // namespace geometry



