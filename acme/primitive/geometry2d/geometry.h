#pragma once


namespace geometry
{


   class CLASS_DECL_ACME rotation
   {
   public:
      double   m_dCosPhi;
      double   m_dSinPhi;
      i32      m_iXCenter;
      i32      m_iYCenter;

      void rotate(POINT_I32 * ppoint, i32 iCount);

   };

   class CLASS_DECL_ACME geometry :
      virtual public ::matter
   {
   public:


      geometry();
      virtual ~geometry();


      //virtual ::e_status initialize(::object * pobject) override;
      ::e_status destroy() override;


      double rotate_y(double x, double y, double phi);
      double rotate_x(double x, double y, double phi);
      void rotate(i32 x, i32 y, POINT_I32 * ppoint, i32 iCount, double phi);

      void rotate(i32 x, i32 y, POINT_I32 * ppoint, i32 iCount, double cosphi, double sinphi);

      void rotate(i32 x, i32 y, POINT_F64 * ppoint, i32 iCount, double phi);

      void rotate(i32 x, i32 y, POINT_F64 * ppoint, i32 iCount, double cosphi, double sinphi);



      //void RandomPoint(POINT_I32 * ppoint, const ::rectangle_i32 & rectangle);
      void deflate(RECTANGLE_I32 * prectangle, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);



   };


} // namespace geometry



