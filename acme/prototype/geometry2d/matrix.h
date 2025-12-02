// From draw2d_matrix by camilo on
// 2023-09-12 11:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "size.h"


namespace geometry2d
{


   class CLASS_DECL_ACME matrix
   {
   public:


      enum e_mode
      {

         mode_append,
         mode_prepend,

      };


      union
      {
         struct
         {

            double a1;
            double a2;
            double a3;
            double b1;
            double b2;
            double b3;
            double c1;
            double c2;
            double c3;

         };

         double da[9];

         double a[3][3];

      };


      matrix();
      matrix(const matrix&) = default;


      matrix& operator = (const matrix&) = default;

      static matrix translation(double_point point) { return translation(point.x, point.y); }
      static matrix translation(double x, double y);
      static matrix rotation(double dAngleRadians);
      static matrix scaling(double dRateX, double dRateY);
      static matrix scaling(double_point point) { return scaling(point.x, point.y); }
      static matrix scaling(double_size size) { return scaling(size.cx, size.cy); }


      matrix& translate(double_point point, e_mode emode = mode_append) { return translate(point.x, point.y, emode); }
      matrix& translate(double x, double y, e_mode emode = mode_append);
      matrix& rotate(double dAngleRadians, e_mode emode = mode_append);
      matrix& scale(double dRateX, double dRateY, e_mode emode = mode_append);
      matrix& scale(const ::int_point& point, e_mode emode = mode_append) { return scale(point.x, point.y, emode); }


      matrix& prepend(const matrix& m);
      matrix& append(const matrix& m);


      double determinant() const;

      static bool invert(matrix& aDst, const matrix& aSrc);

      bool invert()
      {

         matrix m(*this);

         if (!invert(*this, m))
         {

            return false;

         }

         return true;

      }

      matrix& operator * (const matrix& m);

      // 6 (six) elements
      virtual void SetElements(float* fa);


      void transform(int_sequence2& point);

      void transform(double_sequence2& point);
      void transform(double_sequence2 * ppoint, ::collection::count c);

      template < prototype_container CONTAINER >
      void transform(CONTAINER& container) 
      { for (auto& item : container) transform(item); }

   };


   inline matrix multiplication(const matrix& m1, const matrix& m2)
   {

      matrix m;

      m.a1 = m1.a1 * m2.a1 + m1.a2 * m2.b1 + m1.a3 * m2.c1;
      m.a2 = m1.a1 * m2.a2 + m1.a2 * m2.b2 + m1.a3 * m2.c2;
      m.a3 = m1.a1 * m2.a3 + m1.a2 * m2.b3 + m1.a3 * m2.c3;
      m.b1 = m1.b1 * m2.a1 + m1.b2 * m2.b1 + m1.b3 * m2.c1;
      m.b2 = m1.b1 * m2.a2 + m1.b2 * m2.b2 + m1.b3 * m2.c2;
      m.b3 = m1.b1 * m2.a3 + m1.b2 * m2.b3 + m1.b3 * m2.c3;
      m.c1 = m1.c1 * m2.a1 + m1.c2 * m2.b1 + m1.c3 * m2.c1;
      m.c2 = m1.c1 * m2.a2 + m1.c2 * m2.b2 + m1.c3 * m2.c2;
      m.c3 = m1.c1 * m2.a3 + m1.c2 * m2.b3 + m1.c3 * m2.c3;

      return m;

   }

   inline matrix operator*(const matrix& m1, const matrix& m2)
   {
      return multiplication(m1, m2);
   }


} // namespace draw2d



