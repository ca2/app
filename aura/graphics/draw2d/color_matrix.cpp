#include "framework.h"


color_matrix::color_matrix()
{

   clear();

}


void color_matrix::clear()
{

   a1 = 1.0;
   a2 = 0.0;
   a3 = 0.0;
   a4 = 0.0;
   a5 = 0.0;
   b1 = 0.0;
   b2 = 1.0;
   b3 = 0.0;
   b4 = 0.0;
   b5 = 0.0;
   c1 = 0.0;
   c2 = 0.0;
   c3 = 1.0;
   c4 = 0.0;
   c5 = 0.0;
   d1 = 0.0;
   d2 = 0.0;
   d3 = 0.0;
   d4 = 1.0;
   d5 = 0.0;
   e1 = 0.0;
   e2 = 0.0;
   e3 = 0.0;
   e4 = 0.0;
   e5 = 1.0;

}


bool color_matrix::is_identity() const
{

   return a1 == 1.0 &&
            a2 == 0.0 &&
            a3 == 0.0 &&
            a4 == 0.0 &&
            a5 == 0.0 &&
            b1 == 0.0 &&
            b2 == 1.0 &&
            b3 == 0.0 &&
            b4 == 0.0 &&
            b5 == 0.0 &&
            c1 == 0.0 &&
            c2 == 0.0 &&
            c3 == 1.0 &&
            c4 == 0.0 &&
            c5 == 0.0 &&
            d1 == 0.0 &&
            d2 == 0.0 &&
            d3 == 0.0 &&
            d4 == 1.0 &&
            d5 == 0.0 &&
            e1 == 0.0 &&
            e2 == 0.0 &&
            e3 == 0.0 &&
            e4 == 0.0 &&
            e5 == 1.0;

}


color_matrix & color_matrix::brightness(double r, double g, double b)
{

   e1 = r;
   e2 = g;
   e3 = b;

   return *this;

}


color_matrix & color_matrix::saturation(double r, double g, double b, double s)
{

   a1 = (1.0 - s) * r + s;
   a2 = (1.0 - s) * r;
   a3 = (1.0 - s) * r;
   b1 = (1.0 - s) * g;
   b2 = (1.0 - s) * g + s;
   b3 = (1.0 - s) * g;
   c1 = (1.0 - s) * b;
   c2 = (1.0 - s) * b;
   c3 = (1.0 - s) * b + s;

   return *this;

}


color_matrix & color_matrix::opacity(class ::opacity opacity)
{

   d4 = opacity.get_opacity_rate();

   return *this;

}


color_matrix & color_matrix::invert()
{

   a1 = -a1;
   a2 = -a2;
   a3 = -a3;
   b1 = -b1;
   b2 = -b2;
   b3 = -b3;
   c1 = -c1;
   c2 = -c2;
   c3 = -c3;
   e1 = 1.0;
   e2 = 1.0;
   e3 = 1.0;

   return *this;

}


color_matrix & color_matrix::grayscale()
{

   return saturation(0.3333, 0.3333, 0.3333, 0.0);

}



