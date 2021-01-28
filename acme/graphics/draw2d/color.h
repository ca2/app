#pragma once


#include "color32.h"


//#define  HLSMAX   100.0 /* H,L, and S vary over 0-HLSMAX */
//#define  RGBMAX   100.0   /* R,G, and B vary over 0-RGBMAX */
/* HLSMAX BEST IF DIVISIBLE BY 6 */
/* RGBMAX, HLSMAX must each fit in a byte. */
/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED_HUE (HLSMAX*2.0/3.0)


inline string hex_color(const COLOR32 & c)
{

   string str;

   str.Format("%02x%02x%02x", c.red, c.green, c.blue);

   return str;

}


inline string _hex_color(const COLOR32 & c)
{

   return "#" + hex_color(c);

}


auto inline red(color32_t rgba) { return ((byte)(rgba & 0xff)); }
auto inline green(color32_t rgba) { return ((byte)((rgba >> 8) & 0xff)); }
auto inline blue(color32_t rgba) { return ((byte)((rgba >> 16) & 0xff)); }
auto inline alpha(color32_t rgba) { return ((byte)((rgba >> 24) & 0xff)); }


class rgba :
   public COLOR32
{
public:


   rgba() {}
   rgba(e_zero_init) {red =green=blue=alpha=0;}
   rgba(byte r, byte g, byte b, byte a) {red=r;green=g;blue=b;alpha=a;}
   rgba(color32_t cr) {color32 = cr;}
   rgba(const ::rgba & rgba) { color32 = rgba.color32;}


   float fr() const {return red / 255.f;}
   float fg() const {return green / 255.f;}
   float fb() const {return blue / 255.f;}
   float fa() const {return alpha / 255.f;}
   double dr() const {return red / 255.;}
   double dg() const {return green / 255.;}
   double db() const {return blue / 255.;}
   double da() const {return alpha / 255.;}



   rgba & operator =(const ::payload & payload);


};


inline auto red(const rgba & rgba) { return rgba.red; }
inline auto green(const rgba & rgba) { return rgba.green; }
inline auto blue(const rgba & rgba) { return rgba.blue; }
inline auto alpha(const rgba & rgba) { return rgba.alpha; }

#define A_RGB(a, rgb) ARGB(a, ::red(rgb), ::green(rgb), ::blue(rgb))


class hls
{
public:


   double m_dH;
   double m_dL;
   double m_dS;

   hls() {}
   hls(e_zero_init): m_dH(0.0), m_dL(0.0), m_dS(0.0) {}
   hls(double dH, double dL = 0.5, double dS = 1.0) : m_dH(dH), m_dL(dL), m_dS(dS) {}

   hls & operator =(const ::payload & payload);


};


inline ::payload & assign(::payload & payload, const ::hls & hls);


class CLASS_DECL_ACME color :
   public rgba
{
public:


   static ::color transparent;
   static ::color black;
   static ::color red;
   static ::color green;
   static ::color blue;
   static ::color yellow;
   static ::color cyan;
   static ::color magenta;
   static ::color white;


   enum e_channel
   {

      channel_red = 0,
      channel_green = 1,
      channel_blue = 2,
      channel_alpha = 3

   };

   int  m_flags;


   color();
   color(const color & color);
   color(enum_color ecolor, byte A = 255);
   color(const hls & hls, byte A = 255);
   color(const COLOR32 & color32, int flags = 0);
   color(color32_t cr);
   color(byte R, byte G, byte B, byte A = 255);


   bool is_set() const { return m_flags >= 0; }


   bool is_opaque() const { return m_flags >= 0 && alpha == 255; }
   bool is_translucent() const { return m_flags < 0 || alpha < 255; }
   bool is_transparent() const { return m_flags < 0 || alpha == 0; }
   bool non_transparent() const { return m_flags >= 0 && alpha > 0; }


   void hls_mult(double dRateH, double dRateL, double dRateS);
   void hls_rate(double dRateH, double dRateL, double dRateS);
   void hue_rate(double dRateL);
   void lightness_rate(double dRateL);
   void saturation_rate(double dRateL);
   void set_rgb(color32_t cr);
   void set_argb(color32_t cr);
   void set_bgr(u32 dw);
   void get_hls(double & dHue, double & dLightness, double & dSaturation) const;

   void set_hls(double dHue, double dLightness, double dSaturation);
   void hls_mult(hls & hls);
   void hls_rate(hls & hls);
   void get_hls(hls & hls) const;
   void set_hls(const hls & hls);



   ::hls get_hls() const { hls hls; get_hls(hls); return hls; }

   u32 get_rgb() const;
   u32 get_bgr() const;
   u32 get_rgba() const;
   u32 get_bgra() const;

//   operator rgb & () {return m_rgb;}
//   operator const rgb & () const {return m_rgb;}
//   operator rgba & () {return m_rgba;}
//   operator const rgba & () const {return m_rgba;}

   void set(byte R, byte G, byte B);
   void set(byte R, byte G, byte B, byte A);
   void set(double R, double G, double B, double A);

   void make_black_and_white();

   operator color32_t() const;

   color & operator = (const color & color);
   color & operator = (color32_t cr);
   color & operator = (enum_color ecolor);
   color & operator = (const hls & hls);

   bool parse_color(const char * psz);

   void set_COLORREF(color32_t cr);

   void hue_offset(double dRadians);


   inline static bool similar_color_component(double d1, double d2) { return fabs(d2 - d1) < (1.0 / 255.0); }

   bool operator == (const color & color) const { return memcmp(this, &color, sizeof(color)) == 0; }
   bool operator == (color32_t cr) const { return this->operator color32_t() == cr; }
   bool operator == (enum_color ecolor) const { return this->operator color32_t() == ::color(ecolor).operator color32_t(); }
   bool operator == (const hls & hls) const
   {

      auto hlsThis = get_hls();

      return similar_color_component(hlsThis.m_dH, hls.m_dH)
         && similar_color_component(hlsThis.m_dL, hls.m_dL)
         && similar_color_component(hlsThis.m_dS, hls.m_dS);
   }
   bool operator != (const color& color) const { return !operator == (color); }
   bool operator != (color32_t cr) const { return !operator == (cr); }
   bool operator != (enum_color ecolor) const { return !operator == (ecolor); }
   bool operator != (const hls& hls) const { return !operator == (hls); }


   string _hex_color()
   {

      ::_hex_color(*this);

   }


   string hex_color()
   {

      ::hex_color(*this);

   }

   void blend(const ::color & color, double dRate)
   {

      double dComplement = 1.0 - dRate;

      red   = (byte) (red     * dComplement + color.red  * dRate);
      green = (byte) (green   * dComplement + color.green   * dRate);
      blue  = (byte) (blue    * dComplement + color.blue    * dRate);
      alpha = (byte) (alpha   * dComplement + color.alpha   * dRate);

   }

   double get_a_rate() const { return da(); }
   double get_r_rate() const { return dr(); }
   double get_g_rate() const { return dg(); }
   double get_b_rate() const { return db(); }

   double get_luminance() const { return get_hls().m_dL;}
   double get_saturation() const { return get_hls().m_dS;}
   double get_hue() const { return get_hls().m_dH;}

};


CLASS_DECL_ACME color32_t alpha_color(byte bAlpha, color32_t cr);
CLASS_DECL_ACME color32_t alpha_color(byte bAlpha, enum_color ecolor);
CLASS_DECL_ACME color32_t opaque_color(color32_t cr);
CLASS_DECL_ACME color32_t pure_color(enum_color ecolor);
CLASS_DECL_ACME color32_t opaque_color(enum_color ecolor);


#define rgb_get_r_value(rgb)      (LOBYTE(rgb))
#define rgb_get_g_value(rgb)      (LOBYTE((rgb)>>8))
#define rgb_get_b_value(rgb)      (LOBYTE((rgb)>>16))
#define rgb_get_a_value(rgb)      (LOBYTE((rgb)>>24))

#define bgr_get_b_value(bgr)      (LOBYTE(bgr))
#define bgr_get_g_value(bgr)      (LOBYTE((bgr)>>8))
#define bgr_get_r_value(bgr)      (LOBYTE((bgr)>>16))
#define bgr_get_a_value(bgr)      (LOBYTE((bgr)>>24))



inline void __exchange(::stream & s, ::rgba & rgba);



inline void __exchange(::stream & s, ::hls & hls);





