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

            double a1;
            double a2;
            double a3;
            double a4;
            double a5;
            double b1;
            double b2;
            double b3;
            double b4;
            double b5;
            double c1;
            double c2;
            double c3;
            double c4;
            double c5;
            double d1;
            double d2;
            double d3;
            double d4;
            double d5;
            double e1;
            double e2;
            double e3;
            double e4;
            double e5;

         };

         double da[25];

         double a[5][5];

      };


      color_matrix();
      color_matrix(const color_matrix &) = default;


      color_matrix & operator = (const color_matrix &) = default;

      color_matrix & brightness(double r, double g, double b);
      color_matrix & saturation(double r, double g, double b, double s);
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

   for (index i = 0; i < 5; i++)
   {

      for (index j = 0; j < 5; j++)
      {

         a[i][j] = (typename remove_reference<decltype(a[0][0])>::TYPE) b[i][j];

      }

   }

}



