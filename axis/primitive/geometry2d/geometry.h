#pragma once


namespace geometry
{


   class CLASS_DECL_AURA rotation
   {
   public:
      double   m_dCosPhi;
      double   m_dSinPhi;
      i32      m_iXCenter;
      i32      m_iYCenter;

      void rotate(LPPOINT ppoint, i32 iCount);

   };

   class CLASS_DECL_AURA geometry :
      virtual public ::object
   {
   public:


      geometry();
      virtual ~geometry();


      virtual ::estatus initialize(::object * pobjectContext) override;
      virtual void finalize() override;


      double rotate_y(double x, double y, double phi);
      double rotate_x(double x, double y, double phi);
      void rotate(i32 x, i32 y, LPPOINT ppoint, i32 iCount, double phi);

      void rotate(i32 x, i32 y, LPPOINT ppoint, i32 iCount, double cosphi, double sinphi);

      void rotate(i32 x, i32 y, POINTD * ppoint, i32 iCount, double phi);

      void rotate(i32 x, i32 y, POINTD * ppoint, i32 iCount, double cosphi, double sinphi);



      //void RandomPoint(POINT * ppoint, const ::rect & rect);
      void deflate(RECT * prect, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);



   };


} // namespace geometry

