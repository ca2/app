#include "framework.h"
#include "acme/graphics/image/image32.h"
#include <stdio.h>


double primitive_color_round(double d);


namespace color
{


   color transparent = rgba(0, 0, 0, 0);
   color black = rgba(0, 0, 0, 255);
   color red = rgba(255, 0, 0, 255);
   color green = rgba(0, 255, 0, 255);
   color blue = rgba(0, 0, 255, 255);
   color yellow = rgba(255, 255, 0, 255);
   color cyan = rgba(0, 255, 255, 255);
   color magenta = rgba(255, 0, 255, 255);
   color gray = rgba(255, 127, 127, 127);
   color white = rgba(255, 255, 255, 255);


   //color::color::color()
   //{
   //
   //   
   //
   //}


   //color::color::color(const ::color::color & color)
   //{
   //
   //   operator = (color);
   //
   //}


   //color::color::color(::color32_t color32)
   //{
   //
   //   operator = (color32);
   //
   //}





   //color::color::color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
   //{

   //   set(r, g, b, a);

   //}


   color::color::color(const hls & hls, unsigned char a)
   {

      operator = (hls);

      m_uchOpacity = a;

   }


   color::color::color(const hsv & hsv, unsigned char a)
   {

      operator = (hsv);

      m_uchOpacity = a;

   }



   /*

   proc hls2rgb {h l s} {
       # Posted by frederic.bonnet@ciril.fr
       # h, l and s are floats between 0.0 and 1.0, ditto for rectangle, g and b
       # h = 0   => m_uchRed
       # h = 1/3 => m_uchGreen
       # h = 2/3 => m_uchBlue

       set h6 [expr {($h-floor($h))*6}]
       set rectangle [expr {  $h6 <= 3 ? 2-$h6
                               : $h6-4}]
       set g [expr {  $h6 <= 2 ? $h6
                               : $h6 <= 5 ? 4-$h6
                               : $h6-6}]
   1    set b [expr {  $h6 <= 1 ? -$h6
                               : $h6 <= 4 ? $h6-2
                               : 6-$h6}]
       set rectangle [expr {$int_rectangle < 0.0 ? 0.0 : $int_rectangle > 1.0 ? 1.0 : double($int_rectangle)}]
       set g [expr {$g < 0.0 ? 0.0 : $g > 1.0 ? 1.0 : double($g)}]
       set b [expr {$b < 0.0 ? 0.0 : $b > 1.0 ? 1.0 : double($b)}]

       set rectangle [expr {(($int_rectangle-1)*$s+1)*$l}]
       set g [expr {(($g-1)*$s+1)*$l}]
       set b [expr {(($b-1)*$s+1)*$l}]
       return [list $int_rectangle $g $b]
   }


   */

   hls::hls(const ::color::hsv & hsv)
   {

      m_dH = hsv.m_dH;
      
      m_dL = hsv.m_dV * (1.0 - hsv.m_dS / 2.0);

      if (m_dL <= 0.0 || m_dL >= 1.0)
      {

         m_dS = 0.0;

      }
      else
      {

         double dDiff = (hsv.m_dV - m_dL);

         double dMin = minimum(m_dL, 1.0 - m_dL);;

         m_dS = dDiff / dMin;

      }

   }


   hsv::hsv(const ::color::hls & hls)
   {

      m_dH = hls.m_dH;
      m_dV = hls.m_dL + hls.m_dS * minimum(hls.m_dL, 1.0 - hls.m_dL);
      
      if (m_dV <= 0.0)
      {

         if (hls.m_dL > 0.5)
         {

            m_dS = 0.0;

         }
         else
         {

            m_dS = 1.0;

         }

      }
      else
      {

         m_dS = 2.0 - (2.0 * hls.m_dL / m_dV);

      }

   }

   void color::get_hls(double & h, double & l, double & s) const
   {

         double rf = f64_red();
         double gf = f64_green();
         double bf = f64_blue();

         double max_val = f64_maximum_rgb();
         double min_val = f64_minimum_rgb();
         l = (max_val + min_val) / 2.0;
         s = 0.0;
         h = 0.0;

         if (max_val != min_val) {
            double d = max_val - min_val;
            s = (l > 0.5) ? (d / (2.0 - max_val - min_val)) : (d / (max_val + min_val));

            if (max_val == rf) {
               h = (gf - bf) / d + (gf < bf ? 6.0 : 0.0);
            }
            else if (max_val == gf) {
               h = (bf - rf) / d + 2.0;
            }
            else {
               h = (rf - gf) / d + 4.0;
            }
            h /= 6.0;
         }

         //return { h, l, s };
      //}

      //double r = m_uchRed / 255.0;
      //double g = m_uchGreen / 255.0;
      //double b = m_uchBlue / 255.0;

      //double v;
      //double m;
      //double vm;

      //double r2, g2, b2;

      //h = 0; // default to black
      //s = 0;
      //l = 0;

      //v = maximum(r, g);

      //v = maximum(v, b);

      //m = minimum(r, g);

      //m = minimum(m, b);

      //l = (m + v) / 2.0;

      //if (l <= 0.0)
      //{

      //   return;

      //}

      //vm = v - m;

      //s = vm;

      //if (s > 0.0)
      //{

      //   s /= (l <= 0.5) ? (v + m) : (2.0 - v - m);

      //}
      //else
      //{

      //   return;

      //}

      //r2 = (v - r) / vm;

      //g2 = (v - g) / vm;

      //b2 = (v - b) / vm;

      //if (r == v)
      //{

      //   h = (g == m ? 5.0 + b2 : 1.0 - g2);

      //}
      //else if (g == v)
      //{

      //   h = (b == m ? 1.0 + r2 : 3.0 - b2);

      //}
      //else
      //{

      //   h = (r == m ? 3.0 + g2 : 5.0 - r2);

      //}

      //h /= 6.0;

      ///*double dCMin = minimum(dR, minimum(dG, dB));;
      //double dCMax = maximum(dR, maximum(dG, dB));
      //double dA;

      //if(dR > dB)
      //{
      //   // Red component intensity is
      //   // greater than m_uchBlue component intensity.
      //   if(dG > dB)
      //   {
      //      // Blue component intensity is minimum.
      //      // The hue must be between (0 / 6) and (2 / 6)
      //      if(dR > dG)
      //      {
      //         // Red component intensity is maximum.
      //         // The hue goes from m_uchRed to yellow.
      //         // The hue must be between (0 / 6) and (1 / 6)
      //         dA = (dG - dB) / (dR - dB);
      //         dHParam = dA / 6.0;
      //      }
      //      else if(dG > dR)
      //      {
      //         // Green component intensity is maximum.
      //         // The hue goes from yellow to m_uchGreen.
      //         // The hue must be between (1 / 6) and (2 / 6)
      //         dA = (dR - dB) / (dG - dB);
      //         dHParam = (dA + 1.0) / 6.0;
      //      }
      //      else // if(dG == dR)
      //      {
      //         // Green component intensity is equal
      //         // m_uchRed component intensity.
      //         // The m_uchBlue component is minimum.
      //         // The color is yellow-ish
      //         dHParam = 1.0 / 6.0;
      //      }
      //   }
      //   else if(dG == dB)
      //   {
      //      // Green component intensity is equal
      //      // m_uchBlue component intensity.
      //      // The color is m_uchRed-ish
      //      dHParam = 0.0 / 6.0;
      //   }
      //   else // if(dB > dG)
      //   {
      //      // Green component intensity is minimum.
      //      // Red component intensity is maximum.
      //      // The color go from magenta to m_uchRed.
      //      // The hue must be between (5 / 6) and (6 / 6)
      //      dA = (dB - dG) / (dR - dG);
      //      dHParam = (dA + 5.0) / 6.0;
      //   }
      //}
      //else if(dB > dR)
      //{
      //   // Blue component intensity is
      //   // greater than m_uchRed component intensity.
      //   if(dG > dB)
      //   {
      //      // Red component intensity is minimum.
      //      // Green component intensity is maximum.
      //      // The color go from m_uchGreen to cyan.
      //      // The hue must be between (2 / 6) and (3 / 6)
      //      dA = (dB - dR) / (dG - dR);
      //      dHParam = (dA + 2.0) / 6.0;
      //   }
      //   else if(dB > dG)
      //   {
      //      // Blue component intensity is maximum.
      //      if(dG > dR)
      //      {
      //         // Red component intensity is mimimum.
      //         // The hue goes from cyan to m_uchBlue.
      //         // The hue must be between (3 / 6) and (4 / 6)
      //         dA = (dG - dR) / (dB - dR);
      //         dHParam = (dA + 3.0) / 6.0;
      //      }
      //      else if(dR > dG)
      //      {
      //         // Green component intensity is minimum.
      //         // The hue goes from m_uchBlue to magenta.
      //         // The hue must be between (4 / 6) and (5 / 6)
      //         dA = (dR - dG) / (dB - dG);
      //         dHParam = (dA + 4.0) / 6.0;
      //      }
      //      else // if(dG == dR)
      //      {
      //         // Green component intensity is equal
      //         // m_uchRed component intensity.
      //         // The color is m_uchBlue-ish
      //         dHParam = 4.0 / 6.0;
      //         return;
      //      }
      //   }
      //   else // if(dG == dB)
      //   {
      //      // Green component intensity is equal
      //      // m_uchBlue component intensity.
      //      // The m_uchRed component intensity is minimum.
      //      // The color is cyan-ish
      //      dHParam = 3.0 / 6.0;
      //      return;
      //   }
      //}
      //else // if(dR == dB)
      //{
      //   // Red and m_uchBlue components have equal intensity
      //   if(dG > dR)
      //   {
      //      // The color is m_uchGreen-ish
      //      dHParam = 2.0 / 6.0;
      //   }
      //   else if(dG < dR)
      //   {
      //      // The color is magenta-ish
      //      dHParam = 5.0 / 6.0;
      //   }
      //   else // if(dG == dR)
      //   {
      //      // All colors have the same intensity
      //      dHParam = 0.0;
      //      dLParam = 0.0;
      //      dSParam = 0.0;
      //      return;
      //   }
      //}

      //double dCDiff = dCMax - dCMin;
      //double dCSum = dCMax + dCMin;
      //dLParam = dCSum / 2.0;
      //dSParam = dLParam < 0.5 ?
      //           dCDiff / dCSum :
      //        dCDiff / (2.0 - dCSum);


      //if(dHParam > 1.0)
      //{
      //   informationf("dHParam > 1.0");
      //}
      //if(dLParam > 1.0)
      //{
      //   informationf("dLParam > 1.0");
      //}
      //if(dSParam > 1.0)
      //{
      //   informationf("dSParam > 1.0");
      //}
      //*/

   }


   void color::get_hsv(double & dHue, double & dBlack, double & dWhite) const
   {

      auto r = this->f64_red();
      auto g = this->f64_green();
      auto b = this->f64_blue();

      double M = this->f64_maximum_rgb();

      double m = this->f64_minimum_rgb();

      if (M == m)
      {

         double l = 0.5 * (M + m);
         dHue = 0.;
         dBlack = 1. - l;
         dWhite = l;

      }
      else
      {

         double d = M - m, h;

         if (fabs(M- r) < 0.001)
         {

            h = (g - b) / d + (g < b ? 6 : 0);

         }
         else if (fabs(M - g) < 0.001)
         {

            h = (b - r) / d + 2;

         }
         else
         {

            h = (r - g) / d + 4;

         }

         h /= 6;

         ::color::color ch = from_hue(h);

         auto M2 = ch.f64_maximum_rgb();

         auto m2 = ch.f64_minimum_rgb();

         dWhite = (M * m2 - m * M2) / (m2 - M2);

         dBlack = (M + m2 + m * M2 - m - M * m2 - M2) / (m2 - M2);

         dHue = h;

      }


   }


   double primitive_color_round(double d)
   {

      double n;

      double f;

      f = modf(d, &n);

      if (f > 0.5)
      {

         return n + 1.0;

      }
      else if (f < -0.5)
      {

         return n - 1.0;

      }
      else
      {

         return n;

      }

   }


#define dsin(x) (sin(((x) *2.0 * 3.1415) / 360.0))

   ::color::color color::from_hue(double h)
   {

      double s = 1.f;
      double v = 1.f;

      if (h < 0) h += 1;

      int i = int(h * 6);
      double f = h * 6 - i;
      double p = v * (1 - s);
      double q = v * (1 - f * s);
      double t = v * (1 - (1 - f) * s);

      double r = 0, g = 0, b = 0;
      switch (i % 6) {
      case 0:
      {
         r = v;
         g = t;
         b = p;
      }
      break;
      case 1:
      {
         r = q;
         g = v;
         b = p;
      }
      break;
      case 2:
      {
         r = p;
         g = v;
         b = t;

      }
      break;
      case 3:
      {
         r = p;
         g = q;
         b = v;

      }
      break;
      case 4:
      {
         r = t;
         g = p;
         b = v;
      }
      break;
      case 5:
      {
         r = v;
         g = p;
         b = q;

      }
      break;
      }

      return ::rgba(r, g, b, 1.f);

   }


   void color::set_hls(double dH, double dL, double dS)
   {

      //ASSERT(dH >= 0.0);
      //ASSERT(dH <= 1.0);
      //ASSERT(dL >= 0.0);
      //ASSERT(dL <= 1.0);
      //ASSERT(dS >= 0.0);
      //ASSERT(dS <= 1.0);

      dH = fmod(dH, 1.0);

      if (dH < 0.0)
      {

         dH += 1.0;

      }

      double dR, dG, dB;

      if (dH >= 1.0)
         dH = 0.0;
      else if (dH < 0.0)
         dH = 0.0;

      if (dL > 1.0)
         dL = 1.0;
      else if (dL < 0.0)
         dL = 0.0;

      if (dS > 1.0)
         dS = 1.0;
      else if (dS < 0.0)
         dS = 0.0;

      dH *= 6.0;

      double dA = dH - (double)((int)dH);

      if (dH >= 3.0)
      {
         if (dH >= 4.0)
         {
            if (dH >= 5.0)
            {
               // 5.0
               // magenta to m_uchRed
               dR = 1.0;
               dG = 0.0;
               dB = 1.0 - dA;
            }
            else
            {
               // 4.0
               // m_uchBlue to magenta
               dR = dA;
               dG = 0.0;
               dB = 1.0;
            }
         }
         else
         {
            // 3.0
            // cyan to m_uchBlue
            dR = 0.0;
            dG = 1.0 - dA;
            dB = 1.0;
         }
      }
      else /// if(dH >= 0.0)
      {
         if (dH >= 2.0)
         {
            // 2
            // m_uchGreen to cyan
            dR = 0.0;
            dG = 1.0;
            dB = dA;
         }
         else // (dH >= 0.0 && dH < 2.0)
         {
            if (dH >= 1.0)
            {
               // 1
               // yellow to m_uchGreen
               dR = 1.0 - dA;
               dG = 1.0;
               dB = 0.0;
            }
            else // if(dh >= 0 && dH < 1.0);
            {
               // 0
               // m_uchRed to yellow
               dR = 1.0;
               dG = dA;
               dB = 0.0;
            }
         }
      }

      double dCMin;
      double dCAdd;
      double dSL = dS * dL;
      if (dL >= 0.5)
      {
         dCMin = dL - dS + dSL;
         dCAdd = 2.0 * dS - 2.0 * dSL;
      }
      else
      {
         dCMin = dL - dSL;
         dCAdd = 2.0 * dSL;
      }


      double dFinalR = (dCMin + dR * dCAdd);
      double dFinalG = (dCMin + dG * dCAdd);
      double dFinalB = (dCMin + dB * dCAdd);

      m_uchRed = (unsigned char)primitive_color_round(dFinalR * 255.0);
      m_uchGreen = (unsigned char)primitive_color_round(dFinalG * 255.0);
      m_uchBlue = (unsigned char)primitive_color_round(dFinalB * 255.0);

      /*   double H = dH * 360.0;


         double d360 = dsin(360.0);

         double R1 = dsin(H) * dL;
         double G1 = dsin(H + 120.0) * dL;
         double B1 = dsin(H + 240.0) * dL;

         double AVERAGE = (R1 + G1 + B1) / 3;

         m_dR = ((R1 - AVERAGE) * dS) + AVERAGE;
         m_dG = ((G1 - AVERAGE) * dS) + AVERAGE;
         m_dB = ((B1 - AVERAGE) * dS) + AVERAGE;

         m_iR      = (unsigned char)primitive_color_round(m_dR * 255.0);
         m_iG      = (unsigned char)primitive_color_round(m_dG * 255.0);
         m_iB      = (unsigned char)primitive_color_round(m_dB * 255.0);*/

   }


   void color::set_hsv(double h, double s, double v)
   {

      double r, g, b;
      int i = static_cast<int>(h * 6);
      double f = (h * 6) - i;
      double p = v * (1 - s);
      double q = v * (1 - f * s);
      double t = v * (1 - (1 - f) * s);

      switch (i % 6) {
         case 0: r = v; g = t; b = p; break;
         case 1: r = q; g = v; b = p; break;
         case 2: r = p; g = v; b = t; break;
         case 3: r = p; g = q; b = v; break;
         case 4: r = t; g = p; b = v; break;
         case 5: r = v; g = p; b = q; break;
      }

      m_uchRed = static_cast<int>(r * 255);
      m_uchGreen = static_cast<int>(g * 255);
      m_uchBlue = static_cast<int>(b * 255);
   
      //auto rgb = from_hue(dHue);
      //::color::color black = ::color::black;
      //::color::color white = ::color::white;

      //double luminanceComplement = 1.0 - dWhite - dBlack;

      //double dFinalR = rgb.f64_red() * luminanceComplement + dBlack * black.f64_red() + dWhite * white.f64_red();
      //double dFinalG = rgb.f64_green() * luminanceComplement + dBlack * black.f64_green() + dWhite * white.f64_green();
      //double dFinalB = rgb.f64_blue() * luminanceComplement + dBlack * black.f64_blue() + dWhite * white.f64_blue();

      //m_uchRed = (unsigned char)primitive_color_round(dFinalR * 255.0);
      //m_uchGreen = (unsigned char)primitive_color_round(dFinalG * 255.0);
      //m_uchBlue = (unsigned char)primitive_color_round(dFinalB * 255.0);

   }


   //RGBQUAD color::get_rgbquad() const
   //{
   //   RGBQUAD quad;
   //   quad.rgbBlue      = m_iB;
   //   quad.rgbGreen     = m_iG;
   //   quad.rgbRed       = m_iR;
   //   quad.rgbReserved  = m_iA;
   //   return quad;
   //}


   //void color::set_COLORREF(::color32_t color32)
   //{

   //   set_argb(color32);

   //}


   void color::hue_offset(double dRadians)
   {

      if (dRadians >= 0.0)
      {

         dRadians = fmod(dRadians, 3.1415 * 2.0);

      }
      else
      {

         dRadians = (3.1415 * 2.0) - fmod(-dRadians, 3.1415 * 2.0);

      }

      //http://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color
      //http://stackoverflow.com/users/630989/jacob-eggers
      double U = ::cos(dRadians);
      double W = ::sin(dRadians);

      double oldr = m_uchRed;
      double oldg = m_uchGreen;
      double oldb = m_uchBlue;
      m_uchRed = clampAndConvert((.299 + .701 * U + .168 * W) * oldr
                             + (.587 - .587 * U + .330 * W) * oldg
                             + (.114 - .114 * U - .497 * W) * oldb);
      m_uchGreen = clampAndConvert((.299 - .299 * U - .328 * W) * oldr
                             + (.587 + .413 * U + .035 * W) * oldg
                             + (.114 - .114 * U + .292 * W) * oldb);
      m_uchBlue = clampAndConvert((.299 - .3 * U + 1.25 * W) * oldr
                             + (.587 - .588 * U - 1.05 * W) * oldg
                             + (.114 + .886 * U - .203 * W) * oldb);

   }


   //void color::set_bgr(unsigned int bgr)
   //{

   //   m_uchRed   = bgr_byte_red(bgr);
   //   m_uchGreen = bgr_byte_green(bgr);
   //   m_uchBlue  = bgr_byte_blue(bgr);
   //   m_uchOpacity = bgr_byte_opacity(bgr);

   //}


   void color::hls_rate(double dRateH, double dRateL, double dRateS)
   {
      double dH, dL, dS;

      get_hls(dH, dL, dS);

      dH = dRateH >= 0 ?
         (1.0 - dH) * dRateH + dH :
         (1.0 + dRateH) * dH;
      dL = dRateL >= 0 ?
         (1.0 - dL) * dRateL + dL :
         (1.0 + dRateL) * dL;
      dS = dRateS >= 0 ?
         (1.0 - dS) * dRateS + dS :
         (1.0 + dRateS) * dS;

      if (dH > 1.0)
         dH = 1.0;
      else if (dH < 0.0)
         dH = 0.0;

      if (dL > 1.0)
         dL = 1.0;
      else if (dL < 0.0)
         dL = 0.0;

      if (dS > 1.0)
         dS = 1.0;
      else if (dS < 0.0)
         dS = 0.0;

      set_hls(dH, dL, dS);

   }


   void color::hue_rate(double dRateH)
   {

      double dH, dL, dS;

      get_hls(dH, dL, dS);

      dH = dRateH >= 0 ?
         (1.0 - dH) * dRateH + dH :
         (1.0 + dRateH) * dH;

      if (dH > 1.0)
         dH = 1.0;
      else if (dH < 0.0)
         dH = 0.0;

      set_hls(dH, dL, dS);

   }


   void color::lightness_rate(double dRateL)
   {

      double dH, dL, dS;

      get_hls(dH, dL, dS);

      dL = dRateL >= 0 ?
         (1.0 - dL) * dRateL + dL :
         (1.0 + dRateL) * dL;

      if (dL > 1.0)
         dL = 1.0;
      else if (dL < 0.0)
         dL = 0.0;

      set_hls(dH, dL, dS);

   }


   void color::saturation_rate(double dRateS)
   {

      double dH, dL, dS;

      get_hls(dH, dL, dS);

      dS = dRateS >= 0 ?
         (1.0 - dS) * dRateS + dS :
         (1.0 + dRateS) * dS;

      if (dH > 1.0)
         dH = 1.0;
      else if (dH < 0.0)
         dH = 0.0;

      if (dL > 1.0)
         dL = 1.0;
      else if (dL < 0.0)
         dL = 0.0;

      if (dS > 1.0)
         dS = 1.0;
      else if (dS < 0.0)
         dS = 0.0;

      set_hls(dH, dL, dS);

   }


   void color::hls_mult(double dMultH, double dMultL, double dMultS)
   {

      double dH, dL, dS;

      get_hls(dH, dL, dS);

      dH = dMultH * dH;
      dL = dMultL * dL;
      dS = dMultS * dS;

      if (dH > 1.0)
         dH = 1.0;
      else if (dH < 0.0)
         dH = 0.0;

      if (dL > 1.0)
         dL = 1.0;
      else if (dL < 0.0)
         dL = 0.0;

      if (dS > 1.0)
         dS = 1.0;
      else if (dS < 0.0)
         dS = 0.0;

      set_hls(dH, dL, dS);

   }


   void color::hls_mult(hls & hls)
   {

      hls_mult(hls.m_dH, hls.m_dL, hls.m_dS);

   }


   void color::hls_rate(hls & hls)
   {

      hls_rate(hls.m_dH, hls.m_dL, hls.m_dS);

   }


   void color::get_hls(hls & hls) const
   {

      get_hls(hls.m_dH, hls.m_dL, hls.m_dS);

   }


   void color::get_hsv(hsv & hsv) const
   {

      get_hsv(hsv.m_dH, hsv.m_dS, hsv.m_dV);

   }


   void color::set_hls(const hls & hls)
   {

      set_hls(hls.m_dH, hls.m_dL, hls.m_dS);

   }


   void color::set_hsv(const hsv & hsv)
   {

      set_hsv(hsv.m_dH, hsv.m_dS, hsv.m_dV);

   }

   /*
   void CColor::get_hls(unsigned char * H, unsigned char * L, unsigned char * S)
   {
      double dHue, dLightness, dSaturation;
      // input rgb values
      double dRed = m_bRed;
      double dGreen = m_bGreen;
      double dBlue = m_bBlue;
      // maximum and minimum rgb values
      double dMax, dMin;
      // intermediate value: % of spread from maximum
      double dRedDelta, dGreenDelta, dBlueDelta;
      // calculate lightness
      dMax = maximum(maximum(dRed, dGreen), dBlue);
      dMin = minimum(minimum(dRed, dGreen), dBlue);
      dLightness = (unsigned char) (((dMax + dMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);
      if(dMax == dMin)
      {
         // rectangle=g=b --> achromatic case
         dSaturation = 0;                     // saturation
         dHue = UNDEFINED_HUE;             // hue
      }
      else
      {
         // chromatic case
         // saturation
         if (dLightness <= (HLSMAX / 2.0))
            dSaturation = (((dMax - dMin) * HLSMAX) + ((dMax + dMin) / 2.0) )
            / (dMax + dMin);
         else
            dSaturation = (((dMax - dMin) * HLSMAX) + ((2.0 * RGBMAX - dMax - dMin) / 2.0))
               / (2.0 * RGBMAX - dMax - dMin);

         // hue
         dRedDelta   = ( ((dMax-dRed  )*(HLSMAX/6.0)) + ((dMax-dMin)/2.0) ) / (dMax-dMin);
         dGreenDelta = ( ((dMax-dGreen)*(HLSMAX/6.0)) + ((dMax-dMin)/2.0) ) / (dMax-dMin);
         dBlueDelta   = ( ((dMax-dBlue )*(HLSMAX/6.0)) + ((dMax-dMin)/2.0) ) / (dMax-dMin);

         if (dRed == dMax)
            dHue = dBlueDelta - dGreenDelta;
         else if (dGreen == dMax)
            dHue= (HLSMAX/3.0) + dRedDelta - dBlueDelta;
         else // B == cMax
            dHue = ((2.0*HLSMAX)/3.0) + dGreenDelta - dRedDelta;
         if (dHue < 0)
            dHue += HLSMAX;
         if (dHue > HLSMAX)
            dHue -= HLSMAX;
      }
      *H = (unsigned char) dHue;
      *L = (unsigned char) dLightness;
      *S = (unsigned char) dSaturation;
   }*/

   /*
   // utility routine for HLStoRGB

   double HueToRGB(
      double d1,
      double d2,
      double dHue)
   {
      // range check: note values passed add/subtract thirds of range
      if (dHue < 0.0)
         dHue += HLSMAX;
      if (dHue > HLSMAX)
         dHue -= HLSMAX;
      // return rectangle,g, or b value from this tridrant
      if (dHue < (HLSMAX/6))
         return ( d1 + (((d2-d1)*dHue+(HLSMAX/12))/(HLSMAX/6)) );
      if (dHue < (HLSMAX/2))
         return ( d2 );
      if (dHue < ((HLSMAX*2)/3))
         return ( d1 + (((d2-d1)*(((HLSMAX*2)/3)-dHue)+(HLSMAX/12))/(HLSMAX/6)));
      else
         return ( d1 );
   }

   void CColor::set_hls(
      double dHue,
      double dLightness,
      double dSaturation)
   {
      double dRed, dGreen, dBlue;        // rgb component values
      double dMagic1, dMagic2;       // calculated magic numbers (really!)

      if (dSaturation == 0.0)
      {
         //achromatic case
         dRed = dGreen = dBlue = (dLightness * RGBMAX) / HLSMAX;
         if (dHue != UNDEFINED_HUE)
         {
            // ERROR
         }
      }
      else
      {
         // chromatic case
         // set up magic numbers
         if (dLightness <= (HLSMAX / 2.0))
            dMagic2 = (dLightness * (HLSMAX + dSaturation) + (HLSMAX/2.0))/HLSMAX;
         else
            dMagic2 = dLightness + dSaturation - ((dLightness * dSaturation) + (HLSMAX/2.0))/HLSMAX;
         dMagic1 = 2.0 * dLightness- dMagic2;

         // get rgb, machine units from HLSMAX to RGBMAX
         dRed   = (HueToRGB(dMagic1, dMagic2, dHue+(HLSMAX/3.0))*RGBMAX +
            (HLSMAX/2.0))/HLSMAX;
         dGreen   = (HueToRGB(dMagic1, dMagic2, dHue)*RGBMAX + (HLSMAX/2.0)) / HLSMAX;
         dBlue   = (HueToRGB(dMagic1, dMagic2, dHue-(HLSMAX/3.0))*RGBMAX +
            (HLSMAX/2))/HLSMAX;
      }
      m_bBlue      = (unsigned char) dBlue;
      m_bGreen   = (unsigned char) dGreen;
      m_bRed      = (unsigned char) dRed;


   }

   unsigned int CColor::get_rgb()
   {
      return rgb(m_bRed, m_bGreen, m_bBlue);
   }*/




   ::color::color & color::operator = (const hls & hls)
   {

      set_hls(hls);

      return *this;

   }


   ::color::color & color::operator = (const hsv & hsv)
   {

      set_hsv(hsv);

      return *this;

   }


   //::color::color & color::operator = (RGBQUAD rgbquad)
   //{
   //   set_rgbquad(rgbquad);
   //   return *this;
   //}


#define duplicate_color_nible(nible) ((nible << 4) | (nible))


   bool color::parse_color(const ::scoped_string & scopedstr)
   {

      string str(scopedstr);
      str.trim();
      str += " ";
      if (str.left(1) == "#" && str.length() >= 7 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]) && ishexdigit(str[4])
            && ishexdigit(str[5]) && ishexdigit(str[6]))
      {
         if (str.length() >= 9 && ishexdigit(str[7]) && ishexdigit(str[8]) && !ishexdigit(str[9]))
         {
            int iA, iR, iG, iB;
            sscanf(str.c_str(), "#%02x%02x%02x%02x", &iA, &iR, &iG, &iB);
            set(argb(iA, iR, iG, iB));
            return true;
         }
         else if (!ishexdigit(str[7]))
         {
            int iR, iG, iB;
            sscanf(str.c_str(), "#%02x%02x%02x", &iR, &iG, &iB);
            set(argb(255, iR, iG, iB));
            return true;
         }
      }
      else if (str.left(1) == "#" && str.length() >= 4 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]))
      {
         if (str.length() >= 5 && ishexdigit(str[4]) && !ishexdigit(str[5]))
         {
            int iA, iR, iG, iB;
            sscanf(str.c_str(), "#%1x%1x%1x%1x", &iA, &iR, &iG, &iB);
            set(argb(
               duplicate_color_nible(iA),
               duplicate_color_nible(iR),
               duplicate_color_nible(iG),
               duplicate_color_nible(iB)));
            return true;
         }
         else if (!ishexdigit(str[4]))
         {
            int iR, iG, iB;
            sscanf(str.c_str(), "#%1x%1x%1x", &iR, &iG, &iB);
            set(argb(255,
               duplicate_color_nible(iR),
               duplicate_color_nible(iG),
               duplicate_color_nible(iB)));
            return true;
         }
      }
      else if (str.case_insensitive_begins_eat("rgb") || str.case_insensitive_begins_eat("argb"))
      {
         str.trim();
         if (str.case_insensitive_begins_eat("("))
         {
            str.trim();
            if (str.case_insensitive_ends_eat(")"))
            {
               str.trim();
               ::payload a;
               a.as_string_array().explode(",", str);
               auto & ia = a.int_array_reference();
               if (ia.get_count() == 3)
               {
                  set(argb(255, ia[0], ia[1], ia[2]));
                  return true;
               }
               else if (ia.get_count() == 4)
               {
                  set(argb(ia[0], ia[1], ia[2], ia[3]));
                  return true;
               }
            }
         }
      }
      return false;


   }


   //void color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
   //{

   //   m_uchRed      = r;
   //   m_uchGreen    = g;
   //   m_uchBlue     = b;
   //   m_uchOpacity    = a;

   //}


   void color::make_black_and_white()
   {

      //hls_rate(0.0, 0.0, -1.0);
      //saturation_rate(-1.0);

      m_uchRed = m_uchGreen = m_uchBlue = (m_uchRed + m_uchGreen + m_uchBlue) / 3;

   }


   //void color::set(double r, double g, double b, double a)
   //{

   //   m_uchRed      = (int)(r * 255.);
   //   m_uchGreen    = (int)(g * 255.);
   //   m_uchBlue     = (int)(b * 255.);
   //   m_uchOpacity    = (int)(a * 255.);

   //}


} // namespace color






::payload & assign(::payload & payload, const ::color::color & color32)
{

   payload["rec"] = color32.m_uchRed;
   payload["m_uchGreen"] = color32.m_uchGreen;
   payload["m_uchBlue"] = color32.m_uchBlue;
   payload["m_uchOpacity"] = color32.m_uchOpacity;

   return payload;

}



//void __exchange(::stream & s, ::color::color & color32)
//{
//
//   s.exchange("m_uchRed", color32.m_uchRed);
//   s.exchange("m_uchGreen", color32.m_uchGreen);
//   s.exchange("m_uchBlue", color32.m_uchBlue);
//   s.exchange("m_uchOpacity", color32.m_uchOpacity);
//
//}


namespace color
{


   ::color::color & color::operator =(const ::payload & payload)
   {

      m_uchRed = payload["m_uchRed"].as_unsigned_char();
      m_uchGreen = payload["m_uchGreen"].as_unsigned_char();
      m_uchBlue = payload["m_uchBlue"].as_unsigned_char();
      m_uchOpacity = payload["m_uchOpacity"].as_unsigned_char();

      return *this;

   }


   ::color::hls & hls::operator =(const ::payload & payload)
   {

      if (payload.m_etype == e_type_hls)
      {

         return operator=(payload.m_hls);

      }
      else if (payload.m_etype == e_type_property_set)
      {

         m_dH = payload["hue"].as_double();
         m_dL = payload["lightness"].as_double();
         m_dS = payload["saturation"].as_double();

      }

      return *this;

   }

   //namespace nano2d
   //{


      ////::color::color context::RGB(unsigned char r, unsigned char g, unsigned char b)
      //::color::color RGB_color(unsigned char r, unsigned char g, unsigned char b)
      //{
      //   ///return context::RGBA)(r, g, b, 255);
      //   return { r / 255.f, g / 255.f, b / 255.f, 1.0f };
      //}

      ////::color::color context::RGBf)(float r, float g, float b)
      //::color::color RGBf_color(float r, float g, float b)
      //{
      //   //return context::RGBAf)(r, g, b, 1.0f);
      //   return { r , g, b, 1.0f };
      //}

      ////::color::color context::RGBA)(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
      //::color::color RGBA_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
      //{
      //   ::color::color color;
      //   // Use longer initialization to suppress warning.
      //   color.set_red(r);
      //   color.set_green(g);
      //   color.set_blue(b);
      //   color.set_opacity(a);
      //   return color;
      //}

      ////::color::color context::RGBAf)(float r, float g, float b, float a)
      //::color::color RGBAf_color(float r, float g, float b, float a)
      //{
      //   ::color::color color;
      //   // Use longer initialization to suppress warning.
      //   color.set_red(r);
      //   color.set_green(g);
      //   color.set_blue(b);
      //   color.set_opacity(a);
      //   return color;
      //}

      //::color::color context::TransRGBA)(::color::color c, unsigned char a)
   ::color::color TransRGBA_color(::color::color c, unsigned char a)
   {
      c.set_opacity(a);
      return c;
   }

   //::color::color context::TransRGBAf)(::color::color c, float a)
   ::color::color TransRGBAf_color(::color::color c, double a)
   {
      c.set_opacity(a);
      return c;
   }

   //::color::color context::LerpRGBA)(::color::color c0, ::color::color c1, float u)
   //{
   //   int i;
   //   float oneminu;
   //   ::color::color cint = { {{0}} };
   //
   //   u = context::__clampf)(u, 0.0f, 1.0f);
   //   oneminu = 1.0f - u;
   //   for (i = 0; i < 4; i++)
   //   {
   //      cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
   //   }
   //
   //   return cint;
   //}

   //::color::color context::HSL)(float h, float s, float l)
   ::color::color HSL_color(double h, double s, double l)
   {
      //return context::HSLA)(h, s, l, 255);
      ::color::color color;

      color.set_hls(h, l, s);

      return color;

   }

   //static float context::__hue)(float h, float m1, float m2)
   //{
   //   if (h < 0) h += 1;
   //   if (h > 1) h -= 1;
   //   if (h < 1.0f / 6.0f)
   //      return m1 + (m2 - m1) * h * 6.0f;
   //   else if (h < 3.0f / 6.0f)
   //      return m2;
   //   else if (h < 4.0f / 6.0f)
   //      return m1 + (m2 - m1) * (2.0f / 3.0f - h) * 6.0f;
   //   return m1;
   //}

   //::color::color context::HSLA)(float h, float s, float l, unsigned char a)
   ::color::color HSLA_color(double h, double s, double l, unsigned char a)
   {
      //float m1, m2;
      //::color::color col;
      //h = context::__modf)(h, 1.0f);
      //if (h < 0.0f) h += 1.0f;
      //s = context::__clampf)(s, 0.0f, 1.0f);
      //l = context::__clampf)(l, 0.0f, 1.0f);
      //m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
      //m1 = 2 * l - m2;
      //col.r = context::__clampf)(context::__hue)(h + 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
      //col.g = context::__clampf)(context::__hue)(h, m1, m2), 0.0f, 1.0f);
      //col.b = context::__clampf)(context::__hue)(h - 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
      ::color::color color;

      color.set_hls(h, l, s);

      color.m_uchOpacity = a;

      return color;

   }

   //
   //} // namespace nano2d
   //
   //
   //


} // namespace color


::payload & assign(::payload & payload, const ::color::hls & hls)
{

   payload["hue"] = hls.m_dH;
   payload["lightness"] = hls.m_dL;
   payload["saturation"] = hls.m_dS;

   return payload;

}

//
//void __exchange(::stream & s, ::color::hls & hls)
//{
//
//   s.exchange("hue", hls.m_dH);
//   s.exchange("lightness", hls.m_dL);
//   s.exchange("saturation", hls.m_dS);
//
//}

::color::color g_color20[] = {
::argb(0xff, 0x80, 0x80, 0x80),
::argb(0xff, 0x00, 0x00, 0x75),
::argb(0xff, 0x00, 0x80, 0x80),
::argb(0xff, 0x80, 0x80, 0x00),
::argb(0xff, 0x80, 0x00, 0x00),
::argb(0xff, 0xe6, 0x19, 0x4b),
::argb(0xff, 0x3c, 0xb4, 0x4b),
::argb(0xff, 0xff, 0xe1, 0x19),
::argb(0xff, 0x43, 0x63, 0xd8),
::argb(0xff, 0xf5, 0x82, 0x31),
::argb(0xff, 0x91, 0x1e, 0xb4),
::argb(0xff, 0x46, 0xf0, 0xf0),
::argb(0xff, 0xf0, 0x32, 0xe6),
::argb(0xff, 0xbc, 0xf6, 0x0c),
::argb(0xff, 0xfa, 0xbe, 0xbe),
::argb(0xff, 0xe6, 0xbe, 0xff),
::argb(0xff, 0x9a, 0x63, 0x24),
::argb(0xff, 0xff, 0xfa, 0xc8),
::argb(0xff, 0xaa, 0xff, 0xc3),
::argb(0xff, 0xff, 0xd8, 0xb1)
};


CLASS_DECL_ACME::color::color _020GetColor(::collection::index i)
{

   return g_color20[i % 20];

}


CLASS_DECL_ACME::color::color as_color(const ::scoped_string & scopedstr)
{

   if (scopedstr.size() == 6)
   {

      int r = 255;
      int g = 255;
      int b = 255;

      sscanf(scopedstr, "%02x%02x%02x", &r, &g, &b);

      return rgba((unsigned char)r, (unsigned char)g, (unsigned char)b, 255);

   }
   else if (scopedstr.size() == 8)
   {

      int r = 255;
      int g = 255;
      int b = 255;
      int a = 255;

      sscanf(scopedstr, "%02x%02x%02x%02x", &r, &g, &b, &a);

      return rgba((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a);

   }
   else
   {

      float r = 1.0, g = 1.0, b = 1.0, a = 1.0;

      sscanf(scopedstr, "%f %f %f %f", &r, &g, &b, &a);

      return rgba(r, g, b, a);

   }

}



namespace color
{

   CLASS_DECL_ACME::color::color hex_to_color(const char* psz)
   {

      ::string str(scopedstr);

      if (str.size() < 6)
      {

         throw ::exception(error_parsing);

      }

      str.make_upper();

      ::string_array straPermitted;

      straPermitted.add("0");
      straPermitted.add("1");
      straPermitted.add("2");
      straPermitted.add("3"); 
      straPermitted.add("4");
      straPermitted.add("5");
      straPermitted.add("6");
      straPermitted.add("7");
      straPermitted.add("8");
      straPermitted.add("9");
      straPermitted.add("A");
      straPermitted.add("B");
      straPermitted.add("C");
      straPermitted.add("D");
      straPermitted.add("E");
      straPermitted.add("F");


      ::string strResult;

      for (::character_count i = 0; i < str.size(); i++)
      {

         ::string strDigit;

         strDigit = str[i];

         if (straPermitted.contains(strDigit))
         {

            strResult += strDigit;

         }

      }

      if (strResult.size() < 6)
      {

         throw ::exception(error_parsing);

      }

      unsigned int r = 0;
      unsigned int g = 0;
      unsigned int b = 0;

      ::hex::to(r, strResult.substr(0, 2));
      ::hex::to(g, strResult.substr(2, 2));
      ::hex::to(b, strResult.substr(4, 2));

      return ::rgba((int)r, (int)g, (int) b, 255);

   }



} // namespace color
