#include "framework.h"
#include <stdio.h>


double primitive_color_round(double d);

::color::color color::transparent(0, 0, 0, 0);
::color::color color::black(0, 0, 0, 255);
::color::color color::red(255, 0, 0, 255);
::color::color color::green(0, 255, 0, 255);
::color::color color::blue(0, 0, 255, 255);
::color::color color::yellow(255, 255, 0, 255);
::color::color color::cyan(0, 255, 255, 255);
::color::color color::magenta(255, 0, 255, 255);
::color::color color::white(255, 255, 255, 255);


color::color::color()
{

   m_iA = -1;

}


color::color::color(const ::color::color & color)
{

   operator = (color);

}


color::color::color(color32_t color32)
{

   operator = (color32);

}


color::color::color(enum_plain_color ecolor, int A)
{

   set_rgb(pure_color(ecolor));

   m_iA = A;

}


color::color::color(int R, int G, int B, int A)
{

   set(R, G, B, A);

}

color::color::color(const hls & hls, int A)
{

   operator = (hls);

   m_iA = A;

}


color::~color()
{

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
    set rectangle [expr {$rectangle < 0.0 ? 0.0 : $rectangle > 1.0 ? 1.0 : double($rectangle)}]
    set g [expr {$g < 0.0 ? 0.0 : $g > 1.0 ? 1.0 : double($g)}]
    set b [expr {$b < 0.0 ? 0.0 : $b > 1.0 ? 1.0 : double($b)}]

    set rectangle [expr {(($rectangle-1)*$s+1)*$l}]
    set g [expr {(($g-1)*$s+1)*$l}]
    set b [expr {(($b-1)*$s+1)*$l}]
    return [list $rectangle $g $b]
}

  */

void color::get_hls(double & h, double & l, double & s) const
{

   double rectangle = m_iR / 255.0;
   double g = m_iG / 255.0;
   double b = m_iB / 255.0;

   //double rectangle = rgb.R / 255.0;

   //double g = rgb.G / 255.0;

   //double b = rgb.B / 255.0;

   double v;

   double m;

   double vm;

   double r2, g2, b2;



   h = 0; // default to black

   s = 0;

   l = 0;

   v = maximum(rectangle, g);

   v = maximum(v, b);

   m = minimum(rectangle, g);

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

   r2 = (v - rectangle) / vm;

   g2 = (v - g) / vm;

   b2 = (v - b) / vm;

   if (rectangle == v)

   {

      h = (g == m ? 5.0 + b2 : 1.0 - g2);

   }

   else if (g == v)

   {

      h = (b == m ? 1.0 + r2 : 3.0 - b2);

   }

   else

   {

      h = (rectangle == m ? 3.0 + g2 : 5.0 - r2);

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
      ::information("dHParam > 1.0");
   }
   if(dLParam > 1.0)
   {
      ::information("dLParam > 1.0");
   }
   if(dSParam > 1.0)
   {
      ::information("dSParam > 1.0");
   }
   */
}


double primitive_color_round(double d)
{
   double n;
   double f;
   f = modf(d, &n);
   if (f > 0.5)
      return n + 1.0;
   else if (f < -0.5)
      return n - 1.0;
   else
      return n;
}

#define dsin(x) (sin(((x) *2.0 * 3.1415) / 360.0))

void color::set_hls(
double dH,
double dL,
double dS)
{
   //ASSERT(dH >= 0.0);
   //ASSERT(dH <= 1.0);
   //ASSERT(dL >= 0.0);
   //ASSERT(dL <= 1.0);
   //ASSERT(dS >= 0.0);
   //ASSERT(dS <= 1.0);


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

   m_iR = (::u8)primitive_color_round(dFinalR * 255.0);
   m_iG = (::u8)primitive_color_round(dFinalG * 255.0);
   m_iB = (::u8)primitive_color_round(dFinalB * 255.0);

   /*   double H = dH * 360.0;


      double d360 = dsin(360.0);

      double R1 = dsin(H) * dL;
      double G1 = dsin(H + 120.0) * dL;
      double B1 = dsin(H + 240.0) * dL;

      double AVERAGE = (R1 + G1 + B1) / 3;

      m_dR = ((R1 - AVERAGE) * dS) + AVERAGE;
      m_dG = ((G1 - AVERAGE) * dS) + AVERAGE;
      m_dB = ((B1 - AVERAGE) * dS) + AVERAGE;

      m_iR      = (::u8)primitive_color_round(m_dR * 255.0);
      m_iG      = (::u8)primitive_color_round(m_dG * 255.0);
      m_iB      = (::u8)primitive_color_round(m_dB * 255.0);*/

}

u32 color::get_rgb() const
{
   return m_iR | (m_iG << 8) | (m_iB << 16);
}

u32 color::get_bgr() const
{
   return m_iB | (m_iG << 8) | (m_iR << 16);
}

u32 color::get_rgba() const
{
   return m_iR | (m_iG << 8) | (m_iB << 16) | (m_iA << 24);
}

u32 color::get_bgra() const
{
   return m_iB | (m_iG << 8) | (m_iR << 16) | (m_iA << 24);
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

color::operator color32_t() const
{
   return get_rgba();
}


void color::set_rgb(color32_t color32)
{

   m_iR = color32_u8_red(color32);
   m_iG = color32_u8_green(color32);
   m_iB = color32_u8_blue(color32);

}


void color::set_argb(color32_t color32)
{

   m_iR = color32_u8_red(color32);
   m_iG = color32_u8_green(color32);
   m_iB = color32_u8_blue(color32);
   m_iA = color32_u8_opacity(color32);

}


void color::set_COLORREF(color32_t color32)
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

   double oldr = m_iR;
   double oldg = m_iG;
   double oldb = m_iB;
   m_iR = clampAndConvert((.299 + .701*U + .168*W)*oldr
                          + (.587 - .587*U + .330*W)*oldg
                          + (.114 - .114*U - .497*W)*oldb);
   m_iG = clampAndConvert((.299 - .299*U - .328*W)*oldr
                          + (.587 + .413*U + .035*W)*oldg
                          + (.114 - .114*U + .292*W)*oldb);
   m_iB = clampAndConvert((.299 - .3*U + 1.25*W)*oldr
                          + (.587 - .588*U - 1.05*W)*oldg
                          + (.114 + .886*U - .203*W)*oldb);

}


void color::set_bgr(u32 bgr)
{
   m_iR = bgr_u8_red(bgr);
   m_iG = bgr_u8_green(bgr);
   m_iB = bgr_u8_blue(bgr);
   m_iA = bgr_u8_opacity(bgr);
}


//void color::set_rgbquad(RGBQUAD quad)
//{
//   m_iR   = quad.rgbRed;
//   m_iG   = quad.rgbGreen;
//   m_iB   = quad.rgbBlue;
//   m_iA   = quad.rgbReserved;
//   m_dR     = m_iR / 255.0;
//   m_dG     = m_iG / 255.0;
//   m_dB     = m_iB / 255.0;
//   m_dA     = m_iA / 255.0;
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
void color::get_hls(
hls & hls) const
{
   get_hls(hls.m_dH, hls.m_dL, hls.m_dS);
}
void color::set_hls(
const hls & hls)
{
   set_hls(hls.m_dH, hls.m_dL, hls.m_dS);
}














/*
void CColor::get_hls(::u8 * H, ::u8 * L, ::u8 * S)
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
   dLightness = (::u8) (((dMax + dMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);
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
   *H = (::u8) dHue;
   *L = (::u8) dLightness;
   *S = (::u8) dSaturation;
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

      // get rgb, change units from HLSMAX to RGBMAX
      dRed   = (HueToRGB(dMagic1, dMagic2, dHue+(HLSMAX/3.0))*RGBMAX +
         (HLSMAX/2.0))/HLSMAX;
      dGreen   = (HueToRGB(dMagic1, dMagic2, dHue)*RGBMAX + (HLSMAX/2.0)) / HLSMAX;
      dBlue   = (HueToRGB(dMagic1, dMagic2, dHue-(HLSMAX/3.0))*RGBMAX +
         (HLSMAX/2))/HLSMAX;
   }
   m_bBlue      = (::u8) dBlue;
   m_bGreen   = (::u8) dGreen;
   m_bRed      = (::u8) dRed;


}

u32 CColor::get_rgb()
{
   return rgb(m_bRed, m_bGreen, m_bBlue);
}*/


::color::color & color::operator = (const ::color::color & color)
{
   if (&color != this)
   {
      m_iR = color.m_iR;
      m_iG = color.m_iG;
      m_iB = color.m_iB;
      m_iA = color.m_iA;
   }
   return *this;
}


::color::color & color::operator = (color32_t color32)
{

   set_argb(color32);

   return *this;

}


::color::color & color::operator = (enum_plain_color ecolor)
{

   set_rgb(pure_color(ecolor));

   if(m_iA < 0)
   {

      m_iA = 255;

   }

   return *this;

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

bool color::parse_color(const ::string & psz)
{

   string str(psz);
   str.trim();
   str += " ";
   if (str.left(1) == "#" && str.length() >= 7 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]) && ishexdigit(str[4])
         && ishexdigit(str[5]) && ishexdigit(str[6]))
   {
      if (str.length() >= 9 && ishexdigit(str[7]) && ishexdigit(str[8]) && !ishexdigit(str[9]))
      {
         i32 iA, iR, iG, iB;
         sscanf(str, "#%02x%02x%02x%02x", &iA, &iR, &iG, &iB);
         set_COLORREF(argb(iA, iR, iG, iB));
         return true;
      }
      else if (!ishexdigit(str[7]))
      {
         i32 iR, iG, iB;
         sscanf(str, "#%02x%02x%02x", &iR, &iG, &iB);
         set_COLORREF(argb(255, iR, iG, iB));
         return true;
      }
   }
   else if (str.left(1) == "#" && str.length() >= 4 && ishexdigit(str[1]) && ishexdigit(str[2]) && ishexdigit(str[3]))
   {
      if (str.length() >= 5 && ishexdigit(str[4]) && !ishexdigit(str[5]))
      {
         i32 iA, iR, iG, iB;
         sscanf(str, "#%1x%1x%1x%1x", &iA, &iR, &iG, &iB);
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
         sscanf(str, "#%1x%1x%1x", &iR, &iG, &iB);
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
            int_array & ia = a.inta();
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


CLASS_DECL_AURA color32_t color_with_u8_opacity(::u8 bAlpha, color32_t color32)
{

   return (color32 & 0xffffff) | ((bAlpha & 0xff) << 24);

}

CLASS_DECL_AURA color32_t color_with_u8_opacity(::u8 bAlpha, enum_plain_color ecolor)
{

   return color_with_u8_opacity(bAlpha, pure_color(ecolor));

}

CLASS_DECL_AURA color32_t pure_color(enum_plain_color ecolor)
{

   color32_t color32;

   switch (ecolor)
   {
   case e_plain_color_black:
      color32 = rgb(0, 0, 0);
      break;
   case e_plain_color_red:
      color32 = rgb(255, 0, 0);
      break;
   case e_plain_color_green:
      color32 = rgb(0, 255, 0);
      break;
   case e_plain_color_blue:
      color32 = rgb(0, 0, 255);
      break;
   case e_plain_color_white:
      color32 = rgb(255, 255, 255);
      break;
   case e_plain_color_yellow:
      color32 = rgb(255, 255, 0);
      break;
   case e_plain_color_magenta:
      color32 = rgb(255, 0, 255);
      break;
   case e_plain_color_cyan:
      color32 = rgb(0, 255, 255);
      break;
   case e_plain_color_gray:
      color32 = rgb(127, 127, 127);
   default:
      color32 = 0;
      break;
   };

   return color32;


}

CLASS_DECL_AURA color32_t opaque_color(color32_t color32)
{

   return color_with_u8_opacity(255, color32);

}

CLASS_DECL_AURA color32_t opaque_color(enum_plain_color ecolor)
{

   return opaque_color(pure_color(ecolor));

}


void color::set(int R, int G, int B, int A)
{

   m_iR = R;
   m_iG = G;
   m_iB = B;
   m_iA = A;

}


void color::set(int R, int G, int B)
{

   m_iR = R;
   m_iG = G;
   m_iB = B;

}




CLASS_DECL_AURA void cra_from_quada(colorref_array & colorrefa, RGBQUAD * prgbquad, int iCount)
{

   colorrefa.set_size(iCount);

   for (index i = 0; i < iCount; i++)
   {

#if defined(ANDROID) && defined(__arm__)
      colorrefa[i] = argb(255, prgbquad[i].rgbRed, prgbquad[i].rgbGreen, prgbquad[i].rgbBlue);
#else
      colorrefa[i] = argb(255, prgbquad[i].rgbBlue, prgbquad[i].rgbGreen, prgbquad[i].rgbRed);
#endif

      if (colorrefa[i] == argb(255, 255, 255, 255))
      {

         information("completely white");

      }

   }

}

