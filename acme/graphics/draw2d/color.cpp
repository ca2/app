#include "framework.h"
//#include "acme/primitive/primitive/payload.h"
//#include "acme/primitive/string/hex.h"
// #include "acme/primitive/string/string.h"
#include <stdio.h>


double primitive_color_round(double d);


namespace color
{


   color transparent(0, 0, 0, 0);
   color black(0, 0, 0, 255);
   color red(255, 0, 0, 255);
   color green(0, 255, 0, 255);
   color blue(0, 0, 255, 255);
   color yellow(255, 255, 0, 255);
   color cyan(0, 255, 255, 255);
   color magenta(255, 0, 255, 255);
   color white(255, 255, 255, 255);


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


   color::color::color(enum_color ecolor, byte a)
   {

      set_rgb(pure_color(ecolor));

      alpha = a;

   }


   //color::color::color(byte r, byte g, byte b, byte a)
   //{

   //   set(r, g, b, a);

   //}


   color::color::color(const hls & hls, byte a)
   {

      operator = (hls);

      alpha = a;

   }




   /*

   proc hls2rgb {h l s} {
       # Posted by frederic.bonnet@ciril.fr
       # h, l and s are floats between 0.0 and 1.0, ditto for rectangle, g and b
       # h = 0   => red
       # h = 1/3 => green
       # h = 2/3 => blue

       set h6 [expr {($h-floor($h))*6}]
       set rectangle [expr {  $h6 <= 3 ? 2-$h6
                               : $h6-4}]
       set g [expr {  $h6 <= 2 ? $h6
                               : $h6 <= 5 ? 4-$h6
                               : $h6-6}]
   1    set b [expr {  $h6 <= 1 ? -$h6
                               : $h6 <= 4 ? $h6-2
                               : 6-$h6}]
       set rectangle [expr {$rectangle_i32 < 0.0 ? 0.0 : $rectangle_i32 > 1.0 ? 1.0 : double($rectangle_i32)}]
       set g [expr {$g < 0.0 ? 0.0 : $g > 1.0 ? 1.0 : double($g)}]
       set b [expr {$b < 0.0 ? 0.0 : $b > 1.0 ? 1.0 : double($b)}]

       set rectangle [expr {(($rectangle_i32-1)*$s+1)*$l}]
       set g [expr {(($g-1)*$s+1)*$l}]
       set b [expr {(($b-1)*$s+1)*$l}]
       return [list $rectangle_i32 $g $b]
   }


   */


   void color::get_hls(double & h, double & l, double & s) const
   {

      double r = red / 255.0;
      double g = green / 255.0;
      double b = blue / 255.0;

      double v;
      double m;
      double vm;

      double r2, g2, b2;

      h = 0; // default to black
      s = 0;
      l = 0;

      v = maximum(r, g);

      v = maximum(v, b);

      m = minimum(r, g);

      m = minimum(m, b);

      l = (m + v) / 2.0;

      if (l <= 0.0)
      {

         return;

      }

      vm = v - m;

      s = vm;

      if (s > 0.0)
      {

         s /= (l <= 0.5) ? (v + m) : (2.0 - v - m);

      }
      else
      {

         return;

      }

      r2 = (v - r) / vm;

      g2 = (v - g) / vm;

      b2 = (v - b) / vm;

      if (r == v)
      {

         h = (g == m ? 5.0 + b2 : 1.0 - g2);

      }
      else if (g == v)
      {

         h = (b == m ? 1.0 + r2 : 3.0 - b2);

      }
      else
      {

         h = (r == m ? 3.0 + g2 : 5.0 - r2);

      }

      h /= 6.0;

      /*double dCMin = minimum(dR, minimum(dG, dB));;
      double dCMax = maximum(dR, maximum(dG, dB));
      double dA;

      if(dR > dB)
      {
         // Red component intensity is
         // greater than blue component intensity.
         if(dG > dB)
         {
            // Blue component intensity is minimum.
            // The hue must be between (0 / 6) and (2 / 6)
            if(dR > dG)
            {
               // Red component intensity is maximum.
               // The hue goes from red to yellow.
               // The hue must be between (0 / 6) and (1 / 6)
               dA = (dG - dB) / (dR - dB);
               dHParam = dA / 6.0;
            }
            else if(dG > dR)
            {
               // Green component intensity is maximum.
               // The hue goes from yellow to green.
               // The hue must be between (1 / 6) and (2 / 6)
               dA = (dR - dB) / (dG - dB);
               dHParam = (dA + 1.0) / 6.0;
            }
            else // if(dG == dR)
            {
               // Green component intensity is equal
               // red component intensity.
               // The blue component is minimum.
               // The color is yellow-ish
               dHParam = 1.0 / 6.0;
            }
         }
         else if(dG == dB)
         {
            // Green component intensity is equal
            // blue component intensity.
            // The color is red-ish
            dHParam = 0.0 / 6.0;
         }
         else // if(dB > dG)
         {
            // Green component intensity is minimum.
            // Red component intensity is maximum.
            // The color go from magenta to red.
            // The hue must be between (5 / 6) and (6 / 6)
            dA = (dB - dG) / (dR - dG);
            dHParam = (dA + 5.0) / 6.0;
         }
      }
      else if(dB > dR)
      {
         // Blue component intensity is
         // greater than red component intensity.
         if(dG > dB)
         {
            // Red component intensity is minimum.
            // Green component intensity is maximum.
            // The color go from green to cyan.
            // The hue must be between (2 / 6) and (3 / 6)
            dA = (dB - dR) / (dG - dR);
            dHParam = (dA + 2.0) / 6.0;
         }
         else if(dB > dG)
         {
            // Blue component intensity is maximum.
            if(dG > dR)
            {
               // Red component intensity is mimimum.
               // The hue goes from cyan to blue.
               // The hue must be between (3 / 6) and (4 / 6)
               dA = (dG - dR) / (dB - dR);
               dHParam = (dA + 3.0) / 6.0;
            }
            else if(dR > dG)
            {
               // Green component intensity is minimum.
               // The hue goes from blue to magenta.
               // The hue must be between (4 / 6) and (5 / 6)
               dA = (dR - dG) / (dB - dG);
               dHParam = (dA + 4.0) / 6.0;
            }
            else // if(dG == dR)
            {
               // Green component intensity is equal
               // red component intensity.
               // The color is blue-ish
               dHParam = 4.0 / 6.0;
               return;
            }
         }
         else // if(dG == dB)
         {
            // Green component intensity is equal
            // blue component intensity.
            // The red component intensity is minimum.
            // The color is cyan-ish
            dHParam = 3.0 / 6.0;
            return;
         }
      }
      else // if(dR == dB)
      {
         // Red and blue components have equal intensity
         if(dG > dR)
         {
            // The color is green-ish
            dHParam = 2.0 / 6.0;
         }
         else if(dG < dR)
         {
            // The color is magenta-ish
            dHParam = 5.0 / 6.0;
         }
         else // if(dG == dR)
         {
            // All colors have the same intensity
            dHParam = 0.0;
            dLParam = 0.0;
            dSParam = 0.0;
            return;
         }
      }

      double dCDiff = dCMax - dCMin;
      double dCSum = dCMax + dCMin;
      dLParam = dCSum / 2.0;
      dSParam = dLParam < 0.5 ?
                 dCDiff / dCSum :
              dCDiff / (2.0 - dCSum);


      if(dHParam > 1.0)
      {
         ::output_debug_string("dHParam > 1.0");
      }
      if(dLParam > 1.0)
      {
         ::output_debug_string("dLParam > 1.0");
      }
      if(dSParam > 1.0)
      {
         ::output_debug_string("dSParam > 1.0");
      }
      */

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

      double dA = dH - (double)((i32)dH);

      if (dH >= 3.0)
      {
         if (dH >= 4.0)
         {
            if (dH >= 5.0)
            {
               // 5.0
               // magenta to red
               dR = 1.0;
               dG = 0.0;
               dB = 1.0 - dA;
            }
            else
            {
               // 4.0
               // blue to magenta
               dR = dA;
               dG = 0.0;
               dB = 1.0;
            }
         }
         else
         {
            // 3.0
            // cyan to blue
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
            // green to cyan
            dR = 0.0;
            dG = 1.0;
            dB = dA;
         }
         else // (dH >= 0.0 && dH < 2.0)
         {
            if (dH >= 1.0)
            {
               // 1
               // yellow to green
               dR = 1.0 - dA;
               dG = 1.0;
               dB = 0.0;
            }
            else // if(dh >= 0 && dH < 1.0);
            {
               // 0
               // red to yellow
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

      red   = (byte)primitive_color_round(dFinalR * 255.0);
      green = (byte)primitive_color_round(dFinalG * 255.0);
      blue  = (byte)primitive_color_round(dFinalB * 255.0);

      /*   double H = dH * 360.0;


         double d360 = dsin(360.0);

         double R1 = dsin(H) * dL;
         double G1 = dsin(H + 120.0) * dL;
         double B1 = dsin(H + 240.0) * dL;

         double AVERAGE = (R1 + G1 + B1) / 3;

         m_dR = ((R1 - AVERAGE) * dS) + AVERAGE;
         m_dG = ((G1 - AVERAGE) * dS) + AVERAGE;
         m_dB = ((B1 - AVERAGE) * dS) + AVERAGE;

         m_iR      = (byte)primitive_color_round(m_dR * 255.0);
         m_iG      = (byte)primitive_color_round(m_dG * 255.0);
         m_iB      = (byte)primitive_color_round(m_dB * 255.0);*/

   }


   u32 color::get_rgb() const
   {

      return red | (green << 8) | (blue << 16);

   }


   u32 color::get_bgr() const
   {

      return blue | (green << 8) | (red << 16);

   }


   u32 color::get_rgba() const
   {

      return u32;

   }


   u32 color::get_bgra() const
   {

      return blue | (green << 8) | (red << 16) | (alpha << 24);

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



   void color::set_rgb(::color32_t color32)
   {

      red      = colorref_get_r_value(color32);
      green    = colorref_get_g_value(color32);
      blue     = colorref_get_b_value(color32);

   }


   void color::set_argb(::color32_t color32)
   {

      red      = colorref_get_r_value(color32);
      green    = colorref_get_g_value(color32);
      blue     = colorref_get_b_value(color32);
      alpha    = colorref_get_a_value(color32);

   }


   void color::set_COLORREF(::color32_t color32)
   {

      set_argb(color32);

   }


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

      double oldr = red;
      double oldg = green;
      double oldb = blue;
      red   = clampAndConvert((.299 + .701*U + .168*W)*oldr
                             + (.587 - .587*U + .330*W)*oldg
                             + (.114 - .114*U - .497*W)*oldb);
      green = clampAndConvert((.299 - .299*U - .328*W)*oldr
                             + (.587 + .413*U + .035*W)*oldg
                             + (.114 - .114*U + .292*W)*oldb);
      blue  = clampAndConvert((.299 - .3*U + 1.25*W)*oldr
                             + (.587 - .588*U - 1.05*W)*oldg
                             + (.114 + .886*U - .203*W)*oldb);

   }


   void color::set_bgr(::u32 bgr)
   {

      red   = bgr_get_r_value(bgr);
      green = bgr_get_g_value(bgr);
      blue  = bgr_get_b_value(bgr);
      alpha = bgr_get_a_value(bgr);

   }


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


   void color::set_hls(const hls & hls)
   {

      set_hls(hls.m_dH, hls.m_dL, hls.m_dS);

   }


   /*
   void CColor::get_hls(byte * H, byte * L, byte * S)
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
      dLightness = (byte) (((dMax + dMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);
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
      *H = (byte) dHue;
      *L = (byte) dLightness;
      *S = (byte) dSaturation;
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
      m_bBlue      = (byte) dBlue;
      m_bGreen   = (byte) dGreen;
      m_bRed      = (byte) dRed;


   }

   u32 CColor::get_rgb()
   {
      return rgb(m_bRed, m_bGreen, m_bBlue);
   }*/


   ::color::color & color::operator = (const ::color::color & color)
   {

      if (&color != this)
      {

         red      = color.red;
         green    = color.green;
         blue     = color.blue;
         alpha    = color.alpha;

      }

      return *this;

   }


   ::color::color & color::operator = (::color32_t color32)
   {

      u32 = color32;

      return *this;

   }


   ::color::color & color::operator = (enum_color ecolor)
   {

      return operator=(pure_color(ecolor));

   }


   ::color::color & color::operator = (const hls & hls)
   {

      set_hls(hls);

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
            i32 iA, iR, iG, iB;
            sscanf(str.c_str(), "#%02x%02x%02x%02x", &iA, &iR, &iG, &iB);
            set_COLORREF(argb(iA, iR, iG, iB));
            return true;
         }
         else if (!ishexdigit(str[7]))
         {
            i32 iR, iG, iB;
            sscanf(str.c_str(), "#%02x%02x%02x", &iR, &iG, &iB);
            set_COLORREF(argb(255, iR, iG, iB));
            return true;
         }
      }
      else if (str.left(1) == "#" && str.length() >= 4 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]))
      {
         if (str.length() >= 5 && ishexdigit(str[4]) && !ishexdigit(str[5]))
         {
            i32 iA, iR, iG, iB;
            sscanf(str.c_str(), "#%1x%1x%1x%1x", &iA, &iR, &iG, &iB);
            set_COLORREF(argb(
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
            set_COLORREF(argb(255,
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
               a.stra().explode(",", str);
               auto & ia = a.i32_array_reference();
               if (ia.get_count() == 3)
               {
                  set_COLORREF(argb(255, ia[0], ia[1], ia[2]));
                  return true;
               }
               else if (ia.get_count() == 4)
               {
                  set_COLORREF(argb(ia[0], ia[1], ia[2], ia[3]));
                  return true;
               }
            }
         }
      }
      return false;


   }


   //void color::set(byte r, byte g, byte b, byte a)
   //{

   //   red      = r;
   //   green    = g;
   //   blue     = b;
   //   alpha    = a;

   //}


   void color::make_black_and_white()
   {

      //hls_rate(0.0, 0.0, -1.0);
      //saturation_rate(-1.0);

      red = green = blue = (red + green + blue) / 3;

   }


   //void color::set(double r, double g, double b, double a)
   //{

   //   red      = (int)(r * 255.);
   //   green    = (int)(g * 255.);
   //   blue     = (int)(b * 255.);
   //   alpha    = (int)(a * 255.);

   //}


} // namespace color






CLASS_DECL_ACME ::color::color alpha_color(byte bAlpha, ::color32_t color32)
{

   return (color32 & 0xffffff) | ((bAlpha & 0xff) << 24);

}

CLASS_DECL_ACME ::color::color alpha_color(byte bAlpha, enum_color ecolor)
{

   return alpha_color(bAlpha, pure_color(ecolor));

}


CLASS_DECL_ACME ::color::color pure_color(enum_color ecolor)
{

   ::color32_t color32;

   switch (ecolor)
   {
   case e_color_black:
      color32 = argb(255, 0, 0, 0);
      break;
   case e_color_red:
      color32 = argb(255, 255, 0, 0);
      break;
   case e_color_green:
      color32 = argb(255, 0, 255, 0);
      break;
   case e_color_blue:
      color32 = argb(255, 0, 0, 255);
      break;
   case e_color_white:
      color32 = argb(255, 255, 255, 255);
      break;
   case e_color_yellow:
      color32 = argb(255, 255, 255, 0);
      break;
   case e_color_magenta:
      color32 = argb(255, 255, 0, 255);
      break;
   case e_color_cyan:
      color32 = argb(255, 0, 255, 255);
      break;
   case e_color_gray:
      color32 = argb(255, 127, 127, 127);
   default:
      color32 = 0;
      break;
   };

   return color32;

}


CLASS_DECL_ACME ::color::color opaque_color(::color32_t color32)
{

   return alpha_color(255, color32);

}


CLASS_DECL_ACME ::color::color opaque_color(enum_color ecolor)
{

   return opaque_color(pure_color(ecolor));

}


::payload & assign(::payload & payload, const ::color::color & color32)
{

   payload["rec"] = color32.red;
   payload["green"] = color32.green;
   payload["blue"] = color32.blue;
   payload["alpha"] = color32.alpha;

   return payload;

}



//void __exchange(::stream & s, ::color::color & color32)
//{
//
//   s.exchange("red", color32.red);
//   s.exchange("green", color32.green);
//   s.exchange("blue", color32.blue);
//   s.exchange("alpha", color32.alpha);
//
//}


namespace color
{


   ::color::color & color::operator =(const ::payload & payload)
   {

      red = payload["red"].as_u8();
      green = payload["green"].as_u8();
      blue = payload["blue"].as_u8();
      alpha = payload["alpha"].as_u8();

      return *this;

   }


   ::color::hls & hls::operator =(const ::payload & payload)
   {

      if(payload.m_etype == e_type_hls)
      {

         return operator=(payload.m_hls);

      }
      else if(payload.m_etype == e_type_property_set)
      {

         m_dH = payload["hue"].as_f64();
         m_dL = payload["lightness"].as_f64();
         m_dS = payload["saturation"].as_f64();

      }

      return *this;

   }

//namespace nano2d
//{


   //::color::color context::RGB(unsigned char r, unsigned char g, unsigned char b)
   ::color::color RGB_color(unsigned char r, unsigned char g, unsigned char b)
   {
      ///return context::RGBA)(r, g, b, 255);
      return { r / 255.f, g / 255.f, b / 255.f, 1.0f };
   }

   //::color::color context::RGBf)(float r, float g, float b)
   ::color::color RGBf_color(float r, float g, float b)
   {
      //return context::RGBAf)(r, g, b, 1.0f);
      return { r , g, b, 1.0f };
   }

   //::color::color context::RGBA)(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
   ::color::color RGBA_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
   {
      ::color::color color;
      // Use longer initialization to suppress warning.
      color.set_red(r);
      color.set_green(g);
      color.set_blue(b);
      color.set_alpha(a);
      return color;
   }

   //::color::color context::RGBAf)(float r, float g, float b, float a)
   ::color::color RGBAf_color(float r, float g, float b, float a)
   {
      ::color::color color;
      // Use longer initialization to suppress warning.
      color.set_red(r);
      color.set_green(g);
      color.set_blue(b);
      color.set_alpha(a);
      return color;
   }

   //::color::color context::TransRGBA)(::color::color c, unsigned char a)
   ::color::color TransRGBA_color(::color::color c, unsigned char a)
   {
      c.set_alpha(a);
      return c;
   }

   //::color::color context::TransRGBAf)(::color::color c, float a)
   ::color::color TransRGBAf_color(::color::color c, float a)
   {
      c.set_alpha(a);
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
   ::color::color HSL_color(float h, float s, float l)
   {
      //return context::HSLA)(h, s, l, 255);
      ::color::color color;

      color.set_hls(h, l, s);
      return { color.fr(), color.fg(), color.fb(), color.fa() };

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
   ::color::color HSLA_color(float h, float s, float l, unsigned char a)
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
      color.alpha = a;
      return { color.fr(), color.fg(), color.fb(), color.fa() };
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
::color::color(0xff808080),
::color::color(0xff000075),
::color::color(0xff008080),
::color::color(0xff808000),
::color::color(0xff800000),
::color::color(0xffe6194b),
::color::color(0xff3cb44b),
::color::color(0xffffe119),
::color::color(0xff4363d8),
::color::color(0xfff58231),
::color::color(0xff911eb4),
::color::color(0xff46f0f0),
::color::color(0xfff032e6),
::color::color(0xffbcf60c),
::color::color(0xfffabebe),
::color::color(0xffe6beff),
::color::color(0xff9a6324),
::color::color(0xfffffac8),
::color::color(0xffaaffc3),
::color::color(0xffffd8b1)
};


CLASS_DECL_ACME::color::color _020GetColor(::index i)
{
   
   return g_color20[i %20];

}


CLASS_DECL_ACME::color::color as_color(const ::scoped_string& scopedstr)
{

   if (scopedstr.size() == 6)
   {

      int r = 255;
      int g = 255;
      int b = 255;

      sscanf(scopedstr, "%02x%02x%02x", &r, &g, &b);

      return { (::byte)r, (::byte)g, (::byte)b, 255 };

   }
   else if (scopedstr.size() == 8)
   {

      int r = 255;
      int g = 255;
      int b = 255;
      int a = 255;

      sscanf(scopedstr, "%02x%02x%02x%02x", &r, &g, &b, &a);

      return { (::byte)r, (::byte)g, (::byte)b, (::byte)a};

   }
   else
   {

      float r = 1.0, g = 1.0, b = 1.0, a = 1.0;

      sscanf(scopedstr, "%f %f %f %f", &r, &g, &b, &a);

      return ::color::color(r, g, b, a);

   }

}


