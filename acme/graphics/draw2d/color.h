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


inline bool operator == (const COLOR32 & color1, const COLOR32 & color2) { return color1.u32 == color2.u32; }


auto inline red(::color32_t rgba) { return ((byte)(rgba & 0xff)); }
auto inline green(::color32_t rgba) { return ((byte)((rgba >> 8) & 0xff)); }
auto inline blue(::color32_t rgba) { return ((byte)((rgba >> 16) & 0xff)); }
auto inline alpha(::color32_t rgba) { return ((byte)((rgba >> 24) & 0xff)); }


namespace color
{


   class CLASS_DECL_ACME hls
   {
   public:


      double m_dH;
      double m_dL;
      double m_dS;

      hls() {}
      hls(e_zero_init) : m_dH(0.0), m_dL(0.0), m_dS(0.0) {}
      hls(double dH, double dL = 0.5, double dS = 1.0) : m_dH(dH), m_dL(dL), m_dS(dS) {}

      hls & operator =(const ::payload & payload);


   };

   enum enum_channel
   {

      e_channel_red = 0,
      e_channel_green = 1,
      e_channel_blue = 2,
      e_channel_alpha = 3

   };


   class CLASS_DECL_ACME color :
      public COLOR32
   {
   public:


      color() {}
      color(e_zero_init) { red = green = blue = alpha = 0; }
      color(byte r, byte g, byte b, byte a = 255) { red = r; green = g; blue = b; alpha = a; }
      color(::color32_t color32) { u32 = color32; }
      color(const ::color::color & color) { u32 = color.u32; }
      color(const ::color::color& color, const opacity& opacity) { u32 = color.u32; alpha = opacity.get_alpha(); }


      float fr() const { return red / 255.f; }
      float fg() const { return green / 255.f; }
      float fb() const { return blue / 255.f; }
      float fa() const { return alpha / 255.f; }
      double dr() const { return red / 255.; }
      double dg() const { return green / 255.; }
      double db() const { return blue / 255.; }
      double da() const { return alpha / 255.; }



      color & operator =(const ::payload & payload);


   //};



   //   int  m_flags;


      //color() { m_flags = -1; }
      //color(const ::color::color & color) { this->u32 = color.u32;  m_flags = color.m_flags; }
      color(enum_color ecolor, byte A = 255);
      color(const hls & hls, byte A = 255);
      //color(const COLOR32 & color32, int flags = 0) { this->u32 = color32.u32;  m_flags = flags; }
      //color(::color32_t color32, int flags = 0) { this->u32 = color32;  m_flags = flags; }
      //color(byte R, byte G, byte B, byte A = 255);


      ///bool is_set() const { return m_flags >= 0; }


      bool is_opaque() const { return alpha == 255; }
      bool is_translucent() const { return  alpha > 0 && alpha < 255; }
      bool is_transparent() const { return  alpha == 0; }
      bool non_transparent() const { return  alpha > 0; }
      bool has_opacity() const { return non_transparent(); }


      void hls_mult(double dRateH, double dRateL, double dRateS);
      void hls_rate(double dRateH, double dRateL, double dRateS);
      void hue_rate(double dRateL);
      void lightness_rate(double dRateL);
      void saturation_rate(double dRateL);
      void set_rgb(::color32_t color32);
      void set_argb(::color32_t color32);
      void set_bgr(::u32 dw);
      void get_hls(double & dHue, double & dLightness, double & dSaturation) const;

      void set_hls(double dHue, double dLightness, double dSaturation);
      void hls_mult(hls & hls);
      void hls_rate(hls & hls);
      void get_hls(hls & hls) const;
      void set_hls(const hls & hls);



      ::color::hls get_hls() const { hls hls; get_hls(hls); return hls; }

      ::u32 get_rgb() const;
      ::u32 get_bgr() const;
      ::u32 get_rgba() const;
      ::u32 get_bgra() const;

      //   operator rgb & () {return m_rgb;}
      //   operator const rgb & () const {return m_rgb;}
      //   operator rgba & () {return m_rgba;}
      //   operator const rgba & () const {return m_rgba;}

      template < primitive_integral R, primitive_integral G, primitive_integral B, primitive_integral A >
      void set(R r, G g, B b) { set_byte((byte)r, (byte)g, (byte)b); }

      template < primitive_integral R, primitive_integral G, primitive_integral B, primitive_integral A >
      void set(R r, G g, B b, A a) { set_byte((byte)r, (byte)g, (byte)b, (byte)a); }

      template < primitive_floating R, primitive_floating G, primitive_floating B >
      void set(R r, G g, B b) { set_double((double)r, (double)g, (double)b); }

      template < primitive_floating R, primitive_floating G, primitive_floating B, primitive_floating A >
      void set(R r, G g, B b, A a) { set_double((double)r, (double)g, (double)b, (double)a); }

      void set_byte(byte R, byte G, byte B) { red = R; green = G; blue = B; alpha = 255; }
      void set_byte(byte R, byte G, byte B, byte A) { red = R; green = G; blue = B; alpha = A; }
      void set_double(double R, double G, double B) { red = (byte) (R * 255.); green = (byte) (G * 255.); blue = (byte) (B * 255.); alpha = 255; }
      void set_double(double R, double G, double B, double A) { red = (byte)(R * 255.); green = (byte) (G * 255.); blue = (byte) (B * 255.); alpha = (byte) (A * 255.); }

      void make_black_and_white();

      operator ::color32_t() const { return u32; }
      operator ::color32_t& () { return u32; }

      color & operator = (const ::color::color & color);
      color & operator = (::color32_t color32);
      color & operator = (enum_color ecolor);
      color & operator = (const hls & hls);

      bool parse_color(const char * psz);

      void set_COLORREF(::color32_t color32);

      void hue_offset(double dRadians);


      inline static bool similar_color_component(double d1, double d2) { return fabs(d2 - d1) < (1.0 / 255.0); }

      bool operator == (const ::color::color& color) const { return u32 == color.u32; }
      bool operator == (::color32_t color32) const { return u32 == color32; }
      bool operator == (enum_color ecolor) const { return u32 == ::color::color(ecolor).u32; }
      bool operator == (const hls & hls) const
      {

         auto hlsThis = get_hls();

         return similar_color_component(hlsThis.m_dH, hls.m_dH)
            && similar_color_component(hlsThis.m_dL, hls.m_dL)
            && similar_color_component(hlsThis.m_dS, hls.m_dS);
      }
      bool operator != (const ::color::color & color) const { return !operator == (color); }
      bool operator != (::color32_t color32) const { return !operator == (color32); }
      bool operator != (enum_color ecolor) const { return !operator == (ecolor); }
      bool operator != (const hls & hls) const { return !operator == (hls); }


      string _hex_color()
      {

         return ::_hex_color(*this);

      }


      string hex_color()
      {

         return ::hex_color(*this);

      }


      void blend(const ::color::color & color, double dRate)
      {

         double dComplement = 1.0 - dRate;

         red = (byte)(red * dComplement + color.red * dRate);
         green = (byte)(green * dComplement + color.green * dRate);
         blue = (byte)(blue * dComplement + color.blue * dRate);
         alpha = (byte)(alpha * dComplement + color.alpha * dRate);

      }

      ::color::color get_blend(const ::color::color& color, double dRate) const
      {

         ::color::color colorResult(*this);

         colorResult.blend(color, dRate);

         return colorResult;
         
      }

      double get_a_rate() const { return da(); }
      double get_r_rate() const { return dr(); }
      double get_g_rate() const { return dg(); }
      double get_b_rate() const { return db(); }

      double get_luminance() const { return (red + green + blue) / (255.0 * 3.0); }
      double get_saturation() const { return get_hls().m_dS; }
      double get_hue() const { return get_hls().m_dH; }

      
      color & operator &=(const ::opacity & opacity)
      {

         alpha = opacity.get_alpha();

         return *this;

      }


      color& operator &=(color32_t color32)
      {

         u32 &= color32;

         return *this;

      }

      color operator &(const ::opacity & opacity) const
      {

         color color(*this);

         color &= opacity;

         return color;

      }


      color operator &(color32_t color32) const
      {

         color color(*this);

         color.u32 &= color32;

         return color;

      }

   };


   CLASS_DECL_ACME extern color transparent;
   CLASS_DECL_ACME extern color black;
   CLASS_DECL_ACME extern color red;
   CLASS_DECL_ACME extern color green;
   CLASS_DECL_ACME extern color blue;
   CLASS_DECL_ACME extern color yellow;
   CLASS_DECL_ACME extern color cyan;
   CLASS_DECL_ACME extern color magenta;
   CLASS_DECL_ACME extern color white;


   using array = ::array < color >;


} // namespace color


CLASS_DECL_ACME ::color::color alpha_color(byte bAlpha, ::color32_t color);
CLASS_DECL_ACME ::color::color alpha_color(byte bAlpha, enum_color ecolor);
CLASS_DECL_ACME ::color::color opaque_color(::color32_t color32);
CLASS_DECL_ACME ::color::color pure_color(enum_color ecolor);
CLASS_DECL_ACME ::color::color opaque_color(enum_color ecolor);


#define rgb_get_r_value(rgb)      (__LOBYTE(rgb))
#define rgb_get_g_value(rgb)      (__LOBYTE((rgb)>>8))
#define rgb_get_b_value(rgb)      (__LOBYTE((rgb)>>16))
#define rgb_get_a_value(rgb)      (__LOBYTE((rgb)>>24))

#define bgr_get_b_value(bgr)      (__LOBYTE(bgr))
#define bgr_get_g_value(bgr)      (__LOBYTE((bgr)>>8))
#define bgr_get_r_value(bgr)      (__LOBYTE((bgr)>>16))
#define bgr_get_a_value(bgr)      (__LOBYTE((bgr)>>24))



CLASS_DECL_ACME void __exchange(::stream & s, ::color::color & color);



CLASS_DECL_ACME void __exchange(::stream & s, ::color::hls & hls);


CLASS_DECL_ACME ::payload & assign(::payload & payload, const ::color::hls & hls);


inline auto red(const ::color::color & color) { return color.red; }
inline auto green(const ::color::color & color) { return color.green; }
inline auto blue(const ::color::color & color) { return color.blue; }
inline auto alpha(const ::color::color & color) { return color.alpha; }
auto inline rgb(byte r, byte g, byte b) { return ::color::color(r, g, b); }
auto inline rgba(byte r, byte g, byte b, byte a) { return ::color::color(r, g, b, a); }
auto inline argb(byte a, byte r, byte g, byte b) { return ::color::color(r, g, b, a); }


inline auto alpha(const ::opacity & opacity, const ::color::color& rgb) { return ::color::color(rgb, opacity); }
auto inline opaque(const ::color::color& color) { return alpha(255, color); }



