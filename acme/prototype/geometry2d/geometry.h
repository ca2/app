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

      void rotate(::int_point * ppoint, int iCount);

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
      void rotate(int x, int y, ::int_point * ppoint, int iCount, double phi);

      void rotate(int x, int y, ::int_point * ppoint, int iCount, double cosphi, double sinphi);

      void rotate(int x, int y, ::double_point * ppoint, int iCount, double phi);

      void rotate(int x, int y, ::double_point * ppoint, int iCount, double cosphi, double sinphi);



      //void RandomPoint(::int_point * ppoint, const ::int_rectangle & rectangle);
      void deflate(::int_rectangle * prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);


      template < prototype_rectangle RECTANGLE >
      inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r)
      {

         return { mathematics()->random(r.left, r.right), mathematics()->random(r.top, r.bottom) };

      }


      template < prototype_rectangle RECTANGLE >
      inline typename RECTANGLE::POINT_TYPE random_point(const RECTANGLE & r, double dRate)
      {

         auto rectangle = r;

         rectangle.rate(dRate);

         return random_point(rectangle);

      }





   };


} // namespace geometry



