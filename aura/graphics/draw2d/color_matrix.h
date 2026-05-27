#pragma once


//namespace draw2d
//{


   class CLASS_DECL_AURA color_matrix
   {
   public:


      union
      {
         struct
         {

            ::f64 a1;
            ::f64 a2;
            ::f64 a3;
            ::f64 a4;
            ::f64 a5;
            ::f64 b1;
            ::f64 b2;
            ::f64 b3;
            ::f64 b4;
            ::f64 b5;
            ::f64 c1;
            ::f64 c2;
            ::f64 c3;
            ::f64 c4;
            ::f64 c5;
            ::f64 d1;
            ::f64 d2;
            ::f64 d3;
            ::f64 d4;
            ::f64 d5;
            ::f64 e1;
            ::f64 e2;
            ::f64 e3;
            ::f64 e4;
            ::f64 e5;

         };

         ::f64 da[25];

         ::f64 a[5][5];

      };


      color_matrix();
      color_matrix(const color_matrix &) = default;


      color_matrix & operator = (const color_matrix &) = default;

      color_matrix & brightness(::f64 r, ::f64 g, ::f64 b);
      color_matrix & saturation(::f64 r, ::f64 g, ::f64 b, ::f64 s);
      color_matrix & opacity(class ::opacity opacity);
      color_matrix & invert();
      color_matrix & grayscale();

      void clear();

      bool is_identity() const;


   };

//
//} // namespace draw2d
//



template < typename A, typename B >
inline void copy_color_matrix(A & a, const B & b)
{

   for (::collection::index i = 0; i < 5; i++)
   {

      for (::collection::index j = 0; j < 5; j++)
      {

         a[i][j] = (non_reference<decltype(a[0][0])>) b[i][j];

      }

   }

}



