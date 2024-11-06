#pragma once


#include "color32.h"
#include "opacity.h"
#include "acme/graphics/image/color_indexes.h"


struct rgba_t
{

   unsigned int m_u32;


   constexpr unsigned char byte_red()const { return lower_u8(m_u32); }
   constexpr unsigned char byte_green()const { return lower_u8(m_u32 >> 8); }
   constexpr unsigned char byte_blue()const { return lower_u8(m_u32 >> 16); }
   constexpr unsigned char byte_opacity()const { return lower_u8(m_u32 >> 24); }


   constexpr bool operator == (const rgba_t & rgba) const { return m_u32 == rgba.m_u32; }


};


struct bgra_t
{

   unsigned int m_u32;


   constexpr unsigned char byte_blue() const { return lower_u8(m_u32); }
   constexpr unsigned char byte_green()const { return lower_u8(m_u32 >> 8); }
   constexpr unsigned char byte_red() const { return lower_u8(m_u32 >> 16); }
   constexpr unsigned char byte_opacity()const { return lower_u8(m_u32 >> 24); }


   constexpr bool operator == (const bgra_t & rgba) const { return m_u32 == rgba.m_u32; }


};



constexpr ::color32_t argb32_color32(
   ::iptr u8Opacity,
   ::iptr u8Red,
   ::iptr u8Green,
   ::iptr u8Blue)
{

   return { make_u32(u8Red, u8Green, u8Blue, u8Opacity) };

}


//constexpr unsigned char color32_byte_red(::color32_t color32) { return lower_u8(color32.m_u32); }
//constexpr unsigned char color32_byte_green(::color32_t color32) { return lower_u8(color32.m_u32 >> 8); }
//constexpr unsigned char color32_byte_blue(::color32_t color32) { return lower_u8(color32.m_u32 >> 16); }
//constexpr unsigned char color32_byte_opacity(::color32_t color32) { return lower_u8(color32.m_u32 >> 24); }



//#define  HLSMAX   100.0 /* H,L, and S vary over 0-HLSMAX */
//#define  RGBMAX   100.0   /* R,G, and B vary over 0-RGBMAX */
/* HLSMAX BEST IF DIVISIBLE BY 6 */
/* RGBMAX, HLSMAX must each fit in a unsigned char. */
/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED_HUE (HLSMAX*2.0/3.0)




//auto inline red(::color32_t rgba) { return ((unsigned char)(rgba & 0xff)); }
//auto inline green(::color32_t rgba) { return ((unsigned char)((rgba >> 8) & 0xff)); }
//auto inline blue(::color32_t rgba) { return ((unsigned char)((rgba >> 16) & 0xff)); }
//auto inline opacity(::color32_t rgba) { return ((unsigned char)((rgba >> 24) & 0xff)); }


namespace color
{


   class color;

   
   struct HLS
   {
     
      double m_dH;
      double m_dL;
      double m_dS;

   };


   class CLASS_DECL_ACME hls :
      public HLS
   {
   public:


 

      hls() {}
      hls(enum_zero_init) : HLS{ 0.0,0.0, 0.0 } {}
      hls(double dH, double dL = 0.5, double dS = 1.0) :HLS{ dH, dL, dS } {}
      hls(const ::color::color & color);
      hls & operator =(const ::payload & payload);


   };

   enum enum_channel
   {

      e_channel_red = 0,
      e_channel_green = 1,
      e_channel_blue = 2,
      e_channel_opacity = 3

   };


   class CLASS_DECL_ACME color :
      public COLOR32
   {
   public:


      constexpr color() { m_u8Red = m_u8Green = m_u8Blue = m_u8Opacity = 0; }
      constexpr color(no_initialize_t) { }
      template < primitive_number GRAY, primitive_number ALPHA >
      constexpr color(GRAY gray, ALPHA u8Opacity) { set_red(gray); set_green(gray); set_blue(gray); set_opacity(u8Opacity); }
      //template < primitive_number R, primitive_number G, primitive_number B >
      //constexpr color(R r, G g, B b) { set_red(r); set_green(g); set_blue(b); }
      //template < primitive_number R, primitive_number G, primitive_number B, primitive_number A >
      //constexpr color(R r, G g, B b, A a) { set_red(r); set_green(g); set_blue(b); set_opacity(a); }
      constexpr color(const ::color32_t & color32) { set(color32); }
      constexpr color(const ::rgba_t & rgba) { set(rgba); }
      constexpr color(const ::bgra_t & bgra) { set(bgra); }
      constexpr color(const ::color::color & color) { m_u32 = color.m_u32; }
      constexpr color(const ::color::color & color, const class ::opacity& opacity) { m_u32 = color.m_u32; m_u8Opacity = opacity.byte_opacity(); }
      //color() { m_flags = -1; }
//color(const ::color::color & color) { this->m_u32 =h color.m_u32;  m_flags = color.m_flags; }
      constexpr color(enum_plain_color eplaincolor);
      constexpr color(enum_plain_color eplaincolor, unsigned char u8Opacity) : color(eplaincolor) { m_u8Opacity = u8Opacity; }
      color(const hls & hls, unsigned char A = 255);
      //color(const COLOR32 & color32, int flags = 0) { this->m_u32 = color32.m_u32;  m_flags = flags; }
      //color(::color32_t color32, int flags = 0) { this->m_u32 = color32;  m_flags = flags; }
      //color(unsigned char R, unsigned char G, unsigned char B, unsigned char A = 255);

      constexpr unsigned char byte_red() const { return m_u8Red; }
      constexpr unsigned char byte_green() const { return m_u8Green; }
      constexpr unsigned char byte_blue() const { return m_u8Blue; }
      constexpr unsigned char byte_opacity() const { return m_u8Opacity; }
      constexpr float f32_red() const { return m_u8Red / 255.f; }
      constexpr float f32_green() const { return m_u8Green / 255.f; }
      constexpr float f32_blue() const { return m_u8Blue / 255.f; }
      constexpr float f32_opacity() const { return m_u8Opacity / 255.f; }
      constexpr double f64_red() const { return m_u8Red / 255.; }
      constexpr double f64_green() const { return m_u8Green / 255.; }
      constexpr double f64_blue() const { return m_u8Blue / 255.; }
      constexpr double f64_opacity() const { return m_u8Opacity / 255.; }

      constexpr color contrasting_color() const {
         float luminance = 0.299f * f32_red() + 0.587f * f32_green() + 0.144f * f32_blue();
         return color(luminance < 0.5f ? 255 : 0, 255);
      }

      color & operator =(const ::payload & payload);


   //};



   //   int  m_flags;




      ///bool is_set() const { return m_flags >= 0; }


      constexpr bool is_opaque() const { return m_u8Opacity == 255; }
      constexpr bool is_translucent() const { return  m_u8Opacity > 0 && m_u8Opacity < 255; }
      constexpr bool is_transparent() const { return  m_u8Opacity == 0; }
      constexpr bool non_transparent() const { return  m_u8Opacity > 0; }
      constexpr bool has_opacity() const { return non_transparent(); }


      void hls_mult(double dRateH, double dRateL, double dRateS);
      void hls_rate(double dRateH, double dRateL, double dRateS);
      void hue_rate(double dRateL);
      void lightness_rate(double dRateL);
      void saturation_rate(double dRateL);
      constexpr void set(::rgba_t rgba);
      //constexpr void set(::rgba_t rgba);
      //constexpr void set_bgr(::bgra_t bgra);
      constexpr void set(::bgra_t bgra);
      void get_hls(double & dHue, double & dLightness, double & dSaturation) const;

      void set_hls(double dHue, double dLightness, double dSaturation);
      void hls_mult(hls & hls);
      void hls_rate(hls & hls);
      void get_hls(hls & hls) const;
      void set_hls(const hls & hls);



      ::color::hls get_hls() const { hls hls; get_hls(hls); return hls; }

      constexpr ::rgba_t rgba() const;
      constexpr ::bgra_t bgra() const;
      constexpr ::rgba_t rgb() const;
      constexpr ::bgra_t bgr() const;
      constexpr ::color32_t color32() const
      {

         return argb32_color32(
         m_u8Opacity,
         m_u8Red,
         m_u8Green,
         m_u8Blue);

      }

      //    rgb & () {return m_rgb;}
      //   operator const rgb & () const {return m_rgb;}
      //   operator rgba & () {return m_rgba;}
      //   operator const rgba & () const {return m_rgba;}

      template < typename R, typename G, typename B >
      constexpr void set(R r, G g, B b) { set_red(r); set_green(g); set_blue(b); }

      template < typename R, typename G, typename B, typename A >
      constexpr void set(R r, G g, B b, A a) { set_red(r); set_green(g); set_blue(b); set_opacity(a); }

      constexpr unsigned char set_red(unsigned char r) { return this->m_u8Red = r; }

      constexpr unsigned char set_green(unsigned char g) { return this->m_u8Green = g; }

      constexpr unsigned char set_blue(unsigned char b) { return this->m_u8Blue = b; }

      constexpr unsigned char set_opacity(unsigned char a) { return this->m_u8Opacity = a; }

      constexpr unsigned short set_red(unsigned short r) { this->m_u8Red = r >> 8; return r; }

      constexpr unsigned short set_green(unsigned short g) { this->m_u8Green = g >> 8; return g;}

      constexpr unsigned short set_blue(unsigned short b) { this->m_u8Blue = b >> 8; return b;}

      constexpr unsigned short set_opacity(unsigned short a) { this->m_u8Opacity = a >> 8; return a;}

      constexpr int set_red(int r) { this->m_u8Red = r; return r; }

      constexpr int set_green(int g) { this->m_u8Green = g; return g; }

      constexpr int set_blue(int b) { this->m_u8Blue = b; return b;}

      constexpr int set_opacity(int a) { this->m_u8Opacity = a; return a;}

      constexpr float set_red(float f) { this->m_u8Red = (unsigned char)(f * 255.0f); return f; }

      constexpr float set_green(float f) { this->m_u8Green = (unsigned char)(f * 255.0f); return f;  }

      constexpr float set_blue(float f) { this->m_u8Blue = (unsigned char)(f * 255.0f); return f;  }

      constexpr float set_opacity(float f) { this->m_u8Opacity = (unsigned char)(f * 255.0f); return f;  }

      constexpr double set_red(double f) { this->m_u8Red = (unsigned char)(f * 255.0); return f; }

      constexpr double set_green(double f) { this->m_u8Green = (unsigned char)(f * 255.0); return f; }

      constexpr double set_blue(double f) { this->m_u8Blue = (unsigned char)(f * 255.0); return f; }

      constexpr double set_opacity(double f) { this->m_u8Opacity = (unsigned char)(f * 255.0); return f; }

      constexpr void set_opacity(class ::opacity opacity) { this->m_u8Opacity = (unsigned char)(opacity.byte_opacity() * 255.0); }

      constexpr void set_opaque() { this->m_u8Opacity = 255; }

      constexpr void set_u8(unsigned char R, unsigned char G, unsigned char B) { m_u8Red = R; m_u8Green = G; m_u8Blue = B; m_u8Opacity = 255; }
      constexpr void set_u8(unsigned char R, unsigned char G, unsigned char B, unsigned char A) { m_u8Red = R; m_u8Green = G; m_u8Blue = B; m_u8Opacity = A; }
      constexpr void set_f64(double R, double G, double B) { m_u8Red = (unsigned char) (R * 255.); m_u8Green = (unsigned char) (G * 255.); m_u8Blue = (unsigned char) (B * 255.); m_u8Opacity = 255; }
      constexpr void set_f64(double R, double G, double B, double A) { m_u8Red = (unsigned char)(R * 255.); m_u8Green = (unsigned char) (G * 255.); m_u8Blue = (unsigned char) (B * 255.); m_u8Opacity = (unsigned char) (A * 255.); }

      void make_black_and_white();

      constexpr operator ::color32_t() const 
      {

         return this->color32();

      }


      constexpr void set(::color32_t color32)
      {

         m_u8Red = color32.byte_red();
         m_u8Green = color32.byte_green();
         m_u8Blue = color32.byte_blue();
         m_u8Opacity = color32.byte_opacity();

      }

      
      constexpr void set(const ::color::color & color)
      {

         m_u32 = color.m_u32;

      }


      constexpr color & operator = (const ::color::color & color);
      constexpr color & operator = (::color32_t color32);
      constexpr color & operator = (enum_plain_color ecolor);
      color & operator = (const hls & hls);

      bool parse_color(const ::scoped_string & scopedstr);

      //void set_color32(::color32_t color32);

      void hue_offset(double dRadians);


      constexpr auto byte_minimum_rgb() const { return minimum({ byte_red(), byte_green(), byte_blue() }); }
      constexpr auto byte_maximum_rgb() const { return maximum({ byte_red(), byte_green(), byte_blue() }); }
      constexpr auto f32_minimum_rgb() const { return byte_minimum_rgb() / 255.f; }
      constexpr auto f32_maximum_rgb() const { return byte_maximum_rgb() / 255.f; }
      constexpr auto f64_minimum_rgb() const { return byte_minimum_rgb() / 255.; }
      constexpr auto f64_maximum_rgb() const { return byte_maximum_rgb() / 255.; }


      constexpr ::color::color & rate_rgb_set_opacity(class ::opacity opacity, double dRate)
      {

         rate_red(dRate);
         rate_green(dRate);
         rate_blue(dRate);

         set_opacity(opacity);

         return *this;

      }


      constexpr void rate_red(double dRate) { m_u8Red = (unsigned char)(m_u8Red * dRate); }
      constexpr void rate_green(double dRate) { m_u8Green = (unsigned char)(m_u8Green * dRate); }
      constexpr void rate_blue(double dRate) { m_u8Blue = (unsigned char)(m_u8Blue * dRate); }
      constexpr void rate_opacity(double dRate) { m_u8Opacity = (unsigned char)(m_u8Opacity * dRate); }


      inline static bool similar_color_component(double d1, double d2) { return fabs(d2 - d1) < (1.0 / 255.0); }

      constexpr bool operator == (const ::color::color& color) const { return m_u32 == color.m_u32; }
      constexpr bool operator == (::color32_t color32) const { return this->operator color32_t().m_u32 == color32.m_u32; }
      constexpr bool operator == (enum_plain_color ecolor) const { return m_u32 == ::color::color(ecolor).m_u32; }
      bool operator == (const hls & hls) const
      {

         auto hlsThis = get_hls();

         return similar_color_component(hlsThis.m_dH, hls.m_dH)
            && similar_color_component(hlsThis.m_dL, hls.m_dL)
            && similar_color_component(hlsThis.m_dS, hls.m_dS);
      }
      //bool operator != (const ::color::color & color) const { return !operator == (color); }
      //bool operator != (::color32_t color32) const { return !operator == (color32); }
      //bool operator != (enum_plain_color ecolor) const { return !operator == (ecolor); }
      //bool operator != (const hls & hls) const { return !operator == (hls); }




      void blend(const ::color::color & color, double dRate)
      {

         double dComplement = 1.0 - dRate;

         m_u8Red = (unsigned char)(m_u8Red * dComplement + color.m_u8Red * dRate);
         m_u8Green = (unsigned char)(m_u8Green * dComplement + color.m_u8Green * dRate);
         m_u8Blue = (unsigned char)(m_u8Blue * dComplement + color.m_u8Blue * dRate);
         m_u8Opacity = (unsigned char)(m_u8Opacity * dComplement + color.m_u8Opacity * dRate);

      }

      ::color::color get_blend(const ::color::color& color, double dRate) const
      {

         ::color::color colorResult(*this);

         colorResult.blend(color, dRate);

         return colorResult;
         
      }

      //double get_opacity_rate() const { return f64_opacity(); }
      //double get_red_rate() const { return f64_red(); }
      //double get_green_rate() const { return f64_green(); }
      //double get_blue_rate() const { return f64_blue(); }

      constexpr double get_luminance() const { return (m_u8Red + m_u8Green + m_u8Blue) / (255.0 * 3.0); }
      double get_saturation() const { return get_hls().m_dS; }
      double get_hue() const { return get_hls().m_dH; }

      constexpr auto opaque() const { return *this & ::opacity(255); }

      
      constexpr color & operator &=(const class ::opacity & opacity)
      {

         this->m_u8Opacity = opacity.byte_opacity();

         return *this;

      }


      //constexpr color& operator &=(color32_t color32)
      //{

      //   m_u32 &= color32;

      //   return *this;

      //}

      constexpr color operator &(const class ::opacity & opacity) const
      {

         color color(*this);

         color &= opacity;

         return color;

      }


      //constexpr color operator &(color32_t color32) const
      //{

      //   color color(*this);

      //   color.m_u32 &= color32;

      //   return color;

      //}

      //constexpr ::color::color plain_color(enum_plain_color ecolor);


   };


   CLASS_DECL_ACME extern color transparent;
   CLASS_DECL_ACME extern color black;
   CLASS_DECL_ACME extern color red;
   CLASS_DECL_ACME extern color green;
   CLASS_DECL_ACME extern color blue;
   CLASS_DECL_ACME extern color yellow;
   CLASS_DECL_ACME extern color cyan;
   CLASS_DECL_ACME extern color magenta;
   CLASS_DECL_ACME extern color gray;
   CLASS_DECL_ACME extern color white;


   using array = ::array < color >;



//
// Color utils
//
// Colors in NanoVG are stored as unsigned ints in ABGR format.

// Returns a color value from red, green, blue values. Alpha will be set to 255 (1.0f).
//CLASS_DECL_ACME   ::color::color RGB_color(unsigned char r, unsigned char g, unsigned char b);

// Returns a color value from red, green, blue values. Alpha will be set to 1.0f.
//CLASS_DECL_ACME ::color::color RGBf_color(float r, float g, float b);

// Returns a color value from red, green, blue and m_u8Opacity values.
//CLASS_DECL_ACME ::color::color RGBA_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

// Returns a color value from red, green, blue and m_u8Opacity values.
//CLASS_DECL_ACME::color::color RGBAf_color(float r, float g, float b, float a);

// Linearly interpolates from color c0 to c1, and returns resulting color value.
CLASS_DECL_ACME::color::color LerpRGBA_color(color c0, color c1, float u);

// Sets transparency of a color value.
CLASS_DECL_ACME::color::color TransRGBA_color(color c0, unsigned char a);

// Sets transparency of a color value.
CLASS_DECL_ACME::color::color TransRGBAf(color c0, float a);

// Returns color value specified by hue, saturation and lightness.
// HSL values are all in range [0..1], m_u8Opacity will be set to 255.
CLASS_DECL_ACME::color::color HSL_color(float h, float s, float l);

// Returns color value specified by hue, saturation and lightness and m_u8Opacity.
// HSL values are all in range [0..1], m_u8Opacity in range [0..255]
CLASS_DECL_ACME ::color::color HSLA_color(float h, float s, float l, unsigned char a);


} // namespace color


constexpr ::color::color color_with_byte_opacity(unsigned char bAlpha, ::color32_t color);
constexpr ::color::color color_with_byte_opacity(unsigned char bAlpha, enum_plain_color ecolor);
constexpr ::color::color opaque_color(::color32_t color32);
//constexpr ::color::color _color(enum_plain_color ecolor);
constexpr ::color::color opaque_color(enum_plain_color ecolor);



constexpr rgba_t argb_rgba(unsigned char u8Opacity, unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue)
{
   return { make_u32(u8Red, u8Green, u8Blue, u8Opacity) };
}

//constexpr unsigned char rgba_byte_red(::rgba_t rgba) { return lower_u8(rgba.m_u32); }
//constexpr unsigned char rgba_byte_green(::rgba_t rgba) { return lower_u8(rgba.m_u32 >> 8); }
//constexpr unsigned char rgba_byte_blue(::rgba_t rgba) { return lower_u8(rgba.m_u32 >> 16); }
//constexpr unsigned char rgba_byte_opacity(::rgba_t rgba) { return lower_u8(rgba.m_u32 >> 24); }


//constexpr unsigned char bgr_byte_blue(unsigned int bgr) { return lower_u8(bgr); }
//constexpr unsigned char bgr_byte_green(unsigned int bgr) { return lower_u8((bgr) >> 8); }
//constexpr unsigned char bgr_byte_red(unsigned int bgr) { return lower_u8((bgr) >> 16); }
//constexpr unsigned char bgr_byte_opacity(unsigned int bgr) { return lower_u8((bgr) >> 24); }


constexpr bgra_t argb_bgra(unsigned char u8Opacity, unsigned char u8Red, unsigned char u8Green, unsigned char u8Blue)
{
   return { make_u32(u8Blue, u8Green, u8Red, u8Opacity) };
}



//CLASS_DECL_ACME void __exchange(::stream & s, ::color::color & color);
//
//
//
//CLASS_DECL_ACME void __exchange(::stream & s, ::color::hls & hls);


CLASS_DECL_ACME ::payload & assign(::payload & payload, const ::color::hls & hls);

//struct image_argb_type {};

//constexpr auto red(const ::color::color & color) { return color.m_u8Red; }
//constexpr auto green(const ::color::color & color) { return color.m_u8Green; }
//constexpr auto blue(const ::color::color & color) { return color.m_u8Blue; }
//constexpr auto opacity(const ::color::color & color) { return color.m_u8Opacity; }

template < typename RED, typename GREEN, typename BLUE, typename OPACITY >
constexpr auto rgba(RED red, GREEN green, BLUE blue, OPACITY opacity)
{

   ::color::color color(no_initialize_t{});

   color.set_red(red);
   color.set_green(green);
   color.set_blue(blue);
   color.set_opacity(opacity);

   return color;

}


template < typename RED, typename GREEN, typename BLUE >
constexpr auto rgb(RED red, GREEN green, BLUE blue)
{
   
   return rgba(red, green, blue, 255);

}




template < typename OPACITY, typename RED, typename GREEN, typename BLUE >
constexpr auto argb(OPACITY opacity, RED red, GREEN green, BLUE blue)
{

   ::color::color color(no_initialize_t{});

   color.set_opacity(opacity);
   color.set_red(red);
   color.set_green(green);
   color.set_blue(blue);

   return color;

}


//constexpr auto opacity(const class ::opacity & opacity, const ::color::color& rgb) { return ::color::color(rgb, opacity); }
//constexpr auto opaque(const ::color::color& color) { return opacity(255, color); }


CLASS_DECL_ACME::color::color _020GetColor(::collection::index i);


//constexpr ::color::color argb(int a, int r, int g, int b)
//{
//
//   return ::color::color(r, g, b, a);
//
//}


//constexpr ::color::color argb(double a, double r, double g, double b)
//{
//
//   return ::color::color(r, g, b, a);
//
//}


namespace color
{


   constexpr color::color(enum_plain_color eplaincolor)
   {

      unsigned int unsigned int;

      switch (eplaincolor)
      {
      case e_plain_color_black:
         unsigned int = ::rgb(0, 0, 0).m_u32;
         break;
      case e_plain_color_red:
         unsigned int = ::rgb(255, 0, 0).m_u32;
         break;
      case e_plain_color_green:
         unsigned int = ::rgb(0, 255, 0).m_u32;
         break;
      case e_plain_color_blue:
         unsigned int = ::rgb(0, 0, 255).m_u32;
         break;
      case e_plain_color_white:
         unsigned int = ::rgb(255, 255, 255).m_u32;
         break;
      case e_plain_color_yellow:
         unsigned int = ::rgb(255, 255, 0).m_u32;
         break;
      case e_plain_color_magenta:
         unsigned int = ::rgb(255, 0, 255).m_u32;
         break;
      case e_plain_color_cyan:
         unsigned int = ::rgb(0, 255, 255).m_u32;
         break;
      case e_plain_color_gray:
         unsigned int = ::rgb(127, 127, 127).m_u32;
      default:
         unsigned int = 0;
         break;
      };

      m_u32 = unsigned int;

   }


   constexpr ::color::color & color::operator = (const ::color::color & color)
   {

      if (&color != this)
      {

         m_u8Red = color.m_u8Red;
         m_u8Green = color.m_u8Green;
         m_u8Blue = color.m_u8Blue;
         m_u8Opacity = color.m_u8Opacity;

      }

      return *this;

   }


   constexpr ::color::color & color::operator = (::color32_t color32)
   {

      set(color32);

      return *this;

   }


   constexpr ::color::color & color::operator = (enum_plain_color eplaincolor)
   {

      return operator=(color(eplaincolor));

   }


   constexpr rgba_t color::rgba() const
   {

      return argb_rgba(m_u8Opacity, m_u8Red, m_u8Green, m_u8Blue);

   }


   constexpr bgra_t color::bgra() const
   {

      return argb_bgra(m_u8Opacity, m_u8Red, m_u8Green, m_u8Blue);

   }


   constexpr rgba_t color::rgb() const
   {

      return this->rgba();

   }


   constexpr bgra_t color::bgr() const
   {

      return this->bgra();

   }


   constexpr void color::set(::rgba_t rgba)
   {

      m_u8Red = rgba.byte_red();
      m_u8Green = rgba.byte_green();
      m_u8Blue = rgba.byte_blue();
      m_u8Opacity = rgba.byte_opacity();

   }


   constexpr void color::set(bgra_t bgra)
   {

      m_u8Red = bgra.byte_red();
      m_u8Green = bgra.byte_green();
      m_u8Blue = bgra.byte_blue();
      m_u8Opacity = bgra.byte_opacity();

   }


   //constexpr void color::set_bgr(unsigned int unsigned int)
   //{

   //   m_u8Red = bgr_byte_red(unsigned int);
   //   m_u8Green = bgr_byte_green(unsigned int);
   //   m_u8Blue = bgr_byte_blue(unsigned int);
   //   m_u8Opacity = bgr_byte_opacity(unsigned int);

   //}


   //constexpr void color::set_bgra(unsigned int unsigned int)
   //{

   //   m_u8Red = bgra_byte_red(unsigned int);
   //   m_u8Green = bgra_byte_green(unsigned int);
   //   m_u8Blue = bgra_byte_blue(unsigned int);
   //   m_u8Opacity = bgra_byte_opacity(unsigned int);

   //}

} // namespace color


constexpr ::color::color color_with_byte_opacity(unsigned char bAlpha, ::color32_t color32)
{

   ::color::color color;

   color.m_u32  = (color32.m_u32 & 0xffffff) | ((bAlpha & 0xff) << 24);

   return color;

}


constexpr::color::color color_with_byte_opacity(unsigned char bAlpha, enum_plain_color ecolor)
{

   return color_with_byte_opacity(bAlpha, ::color::color(ecolor));

}


constexpr ::color::color opaque_color(::color32_t color32)
{

   return color_with_byte_opacity(255, color32);

}


constexpr ::color::color opaque_color(enum_plain_color ecolor)
{

   return opaque_color(::color::color(ecolor));

}





constexpr ::color::color color32_color_with_byte_opacity(unsigned char u8Opacity, ::color32_t color32)
{

   return argb(u8Opacity, color32.byte_red(), color32.byte_green(), color32.byte_blue());

}


//constexpr ::color::color color32_color(color32_t color32)
//{
//
//   ::color::color color;
//
//   color.m_u8Red = color32_byte_red(color32);
//   color.m_u8Green = color32_byte_green(color32);
//   color.m_u8Blue = color32_byte_blue(color32);
//   color.m_u8Opacity = color32_byte_opacity(color32);
//
//   return color;
//
//}


#define __expand_float_rgba(color) color.f32_red(), color.f32_green(), color.f32_blue(), color.f32_opacity()
#define __expand_double_rgba(color) color.f64_red(), color.f64_green(), color.f64_blue(), color.f64_opacity()



namespace color
{


   inline hls::hls(const ::color::color & color)
   {

      operator=(color.get_hls());

   }


} // namespace color



