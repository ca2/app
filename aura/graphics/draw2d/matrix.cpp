#include "framework.h"


namespace draw2d
{

   matrix::matrix()
   {

      a1 = 1.0;
      a2 = 0.0;
      a3 = 0.0;
      b1 = 0.0;
      b2 = 1.0;
      b3 = 0.0;
      c1 = 0.0;
      c2 = 0.0;
      c3 = 1.0;

   }




   matrix matrix::translation(double x, double y)
   {

      matrix m;

      m.c1 = x;

      m.c2 = y;

      return m;

   }

   matrix matrix::rotation(double dAngleDegrees)
   {

      matrix m;

      m.a1 = ::cos(dAngleDegrees);

      m.a2 = ::sin(dAngleDegrees);


      m.b1 = - ::sin(dAngleDegrees);

      m.b2 = ::cos(dAngleDegrees);

      return m;

   }


   matrix matrix::scaling(double dRateX, double dRateY)
   {


      matrix m;

      m.a1 = dRateX;

      m.b2 = dRateY;

      return m;

   }


   matrix & matrix::prepend(const matrix & m)
   {

      operator = (m * *this);

      return *this;
   }


   matrix & matrix::append(const matrix & m)
   {

      operator = (*this * m);

      return *this;

   }

   matrix & matrix::operator * (const matrix & m)
   {

      operator=(multiplication(*this, m));

      return *this;

   }

   void matrix::transform(point & point)
   {

      ::point p;

      p.x = (::i32) (point.x * a1 + point.y * b1 + c1);
      p.y = (::i32) (point.x * a2 + point.y * b2 + c2);

      point = p;

   }

   void matrix::transform(pointd & point)
   {

      pointd p;

      p.x = point.x * a1 + point.y * b1 + c1;
      p.y = point.x * a2 + point.y * b2 + c2;

      point = p;

   }


   // 6 (six) elements
   void matrix::SetElements(float * fa)
   {

      a1 = fa[0];
      a2 = fa[1];
      b1 = fa[2];
      b2 = fa[3];
      c1 = fa[4];
      c2 = fa[5];


   }

   matrix & matrix::translate(double x, double y, e_mode emode)
   {

      if (emode == mode_prepend)
      {

         return prepend(translation(x, y));

      }
      else
      {
         return append(translation(x, y));

      }

   }


   matrix & matrix::rotate(double dAngleRadians, e_mode emode)
   {

      if (emode == mode_prepend)
      {

         return prepend(rotation(dAngleRadians));

      }
      else
      {

         return append(rotation(dAngleRadians));

      }

   }


   matrix & matrix::scale(double dRateX, double dRateY, e_mode emode)
   {

      if (emode == mode_prepend)
      {

         return prepend(scaling(dRateX, dRateY));

      }
      else
      {

         return append(scaling(dRateX, dRateY));

      }

   }


   double matrix::determinant() const
   {

      return
      a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2]) -
      a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0]) +
      a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);

   }


   bool matrix::invert(matrix & aDst, const matrix & aSrc)
   {

      double det = aSrc.determinant();

      if (det == 0.0)
      {

         //cout << "Singular matrix, can't find its inverse";

         return false;

      }

      double invdet = 1 / det;

      aDst.a[0][0] = (aSrc.a[1][1] * aSrc.a[2][2] - aSrc.a[2][1] * aSrc.a[1][2]) * invdet;
      aDst.a[0][1] = (aSrc.a[0][2] * aSrc.a[2][1] - aSrc.a[0][1] * aSrc.a[2][2]) * invdet;
      aDst.a[0][2] = (aSrc.a[0][1] * aSrc.a[1][2] - aSrc.a[0][2] * aSrc.a[1][1]) * invdet;
      aDst.a[1][0] = (aSrc.a[1][2] * aSrc.a[2][0] - aSrc.a[1][0] * aSrc.a[2][2]) * invdet;
      aDst.a[1][1] = (aSrc.a[0][0] * aSrc.a[2][2] - aSrc.a[0][2] * aSrc.a[2][0]) * invdet;
      aDst.a[1][2] = (aSrc.a[1][0] * aSrc.a[0][2] - aSrc.a[0][0] * aSrc.a[1][2]) * invdet;
      aDst.a[2][0] = (aSrc.a[1][0] * aSrc.a[2][1] - aSrc.a[2][0] * aSrc.a[1][1]) * invdet;
      aDst.a[2][1] = (aSrc.a[2][0] * aSrc.a[0][1] - aSrc.a[0][0] * aSrc.a[2][1]) * invdet;
      aDst.a[2][2] = (aSrc.a[0][0] * aSrc.a[1][1] - aSrc.a[1][0] * aSrc.a[0][1]) * invdet;

      return true;

   }


} // namespace draw2d




