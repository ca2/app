// Created by camilo 2022-04-26 18:37 <3ThomasBorregaardS�rensen!!
#pragma once


namespace draw3d
{


   class CLASS_DECL_AURA matrix
   {
   public:


      //enum e_mode
      //{

      //   mode_append,
      //   mode_prepend,

      //};

      union
      {
         struct
         {

            float a1;
            float a2;
            float a3;
            float a4;
            float b1;
            float b2;
            float b3;
            float b4;
            float c1;
            float c2;
            float c3;
            float c4;
            float d1;
            float d2;
            float d3;
            float d4;

         };

         float fa[16];

         float a[4][4];

      };


      //matrix();
      //matrix(const matrix &) = default;


      //matrix & operator = (const matrix &) = default;

      //static matrix translation(point_f64 point) { return translation(point.x(), point.y()); }
      //static matrix translation(double x, double y);
      //static matrix rotation(double dAngleRadians);
      //static matrix scaling(double dRateX, double dRateY);
      //static matrix scaling(point_f64 point) { return scaling(point.x(), point.y()); }


      //matrix & translate(point_f64 point, e_mode emode = mode_append) { return translate(point.x(), point.y(), emode); }
      //matrix & translate(double x, double y, e_mode emode = mode_append);
      //matrix & rotate(double dAngleRadians, e_mode emode = mode_append);
      //matrix & scale(double dRateX, double dRateY, e_mode emode = mode_append);
      //matrix & scale(const ::point_i32 & point, e_mode emode = mode_append) { return scale(point.x(), point.y(), emode); }


      //matrix & prepend(const matrix & m);
      //matrix & append(const matrix & m);


      //double determinant() const;

      //static bool invert(matrix & aDst, const matrix & aSrc);

      //bool invert()
      //{

      //   matrix m(*this);

      //   if (!invert(*this, m))
      //   {

      //      return false;

      //   }

      //   return true;

      //}

      //matrix & operator * (const matrix & m);

      //// 6 (six) elements
      //virtual void SetElements(float * fa);


      //void transform(point_i32 & point);

      //void transform(point_f64 & point);

   };


   //   class CLASS_DECL_AURA matrix
   //{
   //public:


   //   //enum e_mode
   //   //{

   //   //   mode_append,
   //   //   mode_prepend,

   //   //};

   //   union
   //   {
   //      struct
   //      {

   //         float a1;
   //         float a2;
   //         float a3;
   //         float a4;
   //         float b1;
   //         float b2;
   //         float b3;
   //         float b4;
   //         float c1;
   //         float c2;
   //         float c3;
   //         float c4;
   //         float d1;
   //         float d2;
   //         float d3;
   //         float d4;

   //      };

   //      float fa[16];

   //      float a[4][4];

   //   };


   //   //matrix();
   //   //matrix(const matrix &) = default;


   //   //matrix & operator = (const matrix &) = default;

   //   //static matrix translation(point_f64 point) { return translation(point.x(), point.y()); }
   //   //static matrix translation(double x, double y);
   //   //static matrix rotation(double dAngleRadians);
   //   //static matrix scaling(double dRateX, double dRateY);
   //   //static matrix scaling(point_f64 point) { return scaling(point.x(), point.y()); }


   //   //matrix & translate(point_f64 point, e_mode emode = mode_append) { return translate(point.x(), point.y(), emode); }
   //   //matrix & translate(double x, double y, e_mode emode = mode_append);
   //   //matrix & rotate(double dAngleRadians, e_mode emode = mode_append);
   //   //matrix & scale(double dRateX, double dRateY, e_mode emode = mode_append);
   //   //matrix & scale(const ::point_i32 & point, e_mode emode = mode_append) { return scale(point.x(), point.y(), emode); }


   //   //matrix & prepend(const matrix & m);
   //   //matrix & append(const matrix & m);


   //   //double determinant() const;

   //   //static bool invert(matrix & aDst, const matrix & aSrc);

   //   //bool invert()
   //   //{

   //   //   matrix m(*this);

   //   //   if (!invert(*this, m))
   //   //   {

   //   //      return false;

   //   //   }

   //   //   return true;

   //   //}

   //   //matrix & operator * (const matrix & m);

   //   //// 6 (six) elements
   //   //virtual void SetElements(float * fa);


   //   //void transform(point_i32 & point);

   //   //void transform(point_f64 & point);

   //};


   //inline matrix multiplication(const matrix & m1, const matrix & m2)
   //{

   //   matrix m;

   //   m.a1 = m1.a1 * m2.a1 + m1.a2 * m2.b1 + m1.a3 * m2.c1;
   //   m.a2 = m1.a1 * m2.a2 + m1.a2 * m2.b2 + m1.a3 * m2.c2;
   //   m.a3 = m1.a1 * m2.a3 + m1.a2 * m2.b3 + m1.a3 * m2.c3;
   //   m.b1 = m1.b1 * m2.a1 + m1.b2 * m2.b1 + m1.b3 * m2.c1;
   //   m.b2 = m1.b1 * m2.a2 + m1.b2 * m2.b2 + m1.b3 * m2.c2;
   //   m.b3 = m1.b1 * m2.a3 + m1.b2 * m2.b3 + m1.b3 * m2.c3;
   //   m.c1 = m1.c1 * m2.a1 + m1.c2 * m2.b1 + m1.c3 * m2.c1;
   //   m.c2 = m1.c1 * m2.a2 + m1.c2 * m2.b2 + m1.c3 * m2.c2;
   //   m.c3 = m1.c1 * m2.a3 + m1.c2 * m2.b3 + m1.c3 * m2.c3;

   //   return m;

   //}

   //inline matrix operator*(const matrix & m1, const matrix & m2)
   //{
   //   return multiplication(m1, m2);
   //}


} // namespace draw3d



