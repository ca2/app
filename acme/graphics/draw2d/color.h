#pragma once


#include "acme/graphics/draw2d/color32.h"
#include "acme/graphics/draw2d/opacity.h"
#include "acme/graphics/image/color_indexes.h"


struct rgba_t
{

   ::u32 m_u32;


   constexpr ::u8 u8_red()const { return lower_byte(m_u32); }
   constexpr ::u8 u8_green()const { return lower_byte(m_u32 >> 8); }
   constexpr ::u8 u8_blue()const { return lower_byte(m_u32 >> 16); }
   constexpr ::u8 u8_opacity()const { return lower_byte(m_u32 >> 24); }


   constexpr bool operator == (const rgba_t & rgba) const { return m_u32 == rgba.m_u32; }


};


struct bgra_t
{

   ::u32 m_u32;


   constexpr ::u8 u8_blue() const { return lower_byte(m_u32); }
   constexpr ::u8 u8_green()const { return lower_byte(m_u32 >> 8); }
   constexpr ::u8 u8_red() const { return lower_byte(m_u32 >> 16); }
   constexpr ::u8 u8_opacity()const { return lower_byte(m_u32 >> 24); }


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


//constexpr ::u8 color32_u8_red(::color32_t color32) { return lower_byte(color32.m_u32); }
//constexpr ::u8 color32_u8_green(::color32_t color32) { return lower_byte(color32.m_u32 >> 8); }
//constexpr ::u8 color32_u8_blue(::color32_t color32) { return lower_byte(color32.m_u32 >> 16); }
//constexpr ::u8 color32_u8_opacity(::color32_t color32) { return lower_byte(color32.m_u32 >> 24); }



//#define  HLSMAX   100.0 /* H,L, and S vary over 0-HLSMAX */
//#define  RGBMAX   100.0   /* R,G, and B vary over 0-RGBMAX */
/* HLSMAX BEST IF DIVISIBLE BY 6 */
/* RGBMAX, HLSMAX must each fit in a ::u8. */
/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED_HUE (HLSMAX*2.0/3.0)




//auto inline red(::color32_t rgba) { return ((::u8)(rgba & 0xff)); }
//auto inline green(::color32_t rgba) { return ((::u8)((rgba >> 8) & 0xff)); }
//auto inline blue(::color32_t rgba) { return ((::u8)((rgba >> 16) & 0xff)); }
//auto inline opacity(::color32_t rgba) { return ((::u8)((rgba >> 24) & 0xff)); }


namespace color
{


   class color;

   class hsv;

   
   struct HLS
   {
     
      ::f64 m_dH;
      ::f64 m_dL;
      ::f64 m_dS;

   };


   class CLASS_DECL_ACME hls :
      public HLS
   {
   public:


 

      hls(): HLS{ 0.0,0.0, 0.0 } {}
      hls(enum_zero_init) : HLS{ 0.0,0.0, 0.0 } {}
      hls(::f64 dH, ::f64 dL = 0.5, ::f64 dS = 1.0) :HLS{ dH, dL, dS } {}
      hls(const ::color::color & color);
      hls(const ::color::hsv & hsv);
      hls & operator =(const ::payload & payload);


   };

   struct HSV
   {

      ::f64 m_dH;
      ::f64 m_dS;
      ::f64 m_dV;

   };


   class CLASS_DECL_ACME hsv :
      public HSV
   {
   public:




      hsv() {}
      hsv(enum_zero_init) : HSV{ 0.0,0.0, 0.0 } {}
      hsv(::f64 dH, ::f64 dS = 1.0, ::f64 dV = .5) :HSV{ dH, dS, dV } {}
      hsv(const ::color::color & color);
      hsv(const ::color::hls & hls);
      hsv & operator =(const ::payload & payload);


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
      template < prototype_number GRAY, prototype_number ALPHA >
      constexpr color(GRAY gray, ALPHA u8Opacity) { set_red(gray); set_green(gray); set_blue(gray); set_opacity(u8Opacity); }
      //template < prototype_number R, prototype_number G, prototype_number B >
      //constexpr color(R r, G g, B b) { set_red(r); set_green(g); set_blue(b); }
      //template < prototype_number R, prototype_number G, prototype_number B, prototype_number A >
      //constexpr color(R r, G g, B b, A a) { set_red(r); set_green(g); set_blue(b); set_opacity(a); }
      constexpr color(const ::color32_t & color32) { set(color32); }
      constexpr color(const ::rgba_t & rgba) { set(rgba); }
      constexpr color(const ::bgra_t & bgra) { set(bgra); }
      constexpr color(const ::color::color & color) { m_u32 = color.m_u32; }
      constexpr color(const ::color::color & color, const class ::opacity& opacity) { m_u32 = color.m_u32; m_u8Opacity = opacity.u8_opacity(); }
      //color() { m_flags = -1; }
//color(const ::color::color & color) { this->m_u32 =h color.m_u32;  m_flags = color.m_flags; }
      constexpr color(enum_plain_color eplaincolor);
      constexpr color(enum_plain_color eplaincolor, ::u8 u8Opacity) : color(eplaincolor) { m_u8Opacity = u8Opacity; }
      color(const hls & hls, ::u8 A = 255);
      color(const hsv & hsv, ::u8 A = 255);
      //color(const COLOR32 & color32, ::i32 flags = 0) { this->m_u32 = color32.m_u32;  m_flags = flags; }
      //color(::color32_t color32, ::i32 flags = 0) { this->m_u32 = color32;  m_flags = flags; }
      //color(::u8 R, ::u8 G, ::u8 B, ::u8 A = 255);

      constexpr ::u8 u8_red() const { return m_u8Red; }
      constexpr ::u8 u8_green() const { return m_u8Green; }
      constexpr ::u8 u8_blue() const { return m_u8Blue; }
      constexpr ::u8 u8_opacity() const { return m_u8Opacity; }
      constexpr ::f32 f32_red() const { return m_u8Red / 255.f; }
      constexpr ::f32 f32_green() const { return m_u8Green / 255.f; }
      constexpr ::f32 f32_blue() const { return m_u8Blue / 255.f; }
      constexpr ::f32 f32_opacity() const { return m_u8Opacity / 255.f; }
      constexpr ::f64 f64_red() const { return m_u8Red / 255.; }
      constexpr ::f64 f64_green() const { return m_u8Green / 255.; }
      constexpr ::f64 f64_blue() const { return m_u8Blue / 255.; }
      constexpr ::f64 f64_opacity() const { return m_u8Opacity / 255.; }

      constexpr color contrasting_color() const {
         ::f32 luminance = 0.299f * f32_red() + 0.587f * f32_green() + 0.144f * f32_blue();
         return color(luminance < 0.5f ? 255 : 0, 255);
      }

      color & operator =(const ::payload & payload);


   //};



   //   ::i32  m_flags;




      ///bool is_set() const { return m_flags >= 0; }


      constexpr bool is_opaque() const { return m_u8Opacity == 255; }
      constexpr bool is_translucent() const { return  m_u8Opacity > 0 && m_u8Opacity < 255; }
      constexpr bool is_transparent() const { return  m_u8Opacity == 0; }
      constexpr bool non_transparent() const { return  m_u8Opacity > 0; }
      constexpr bool has_opacity() const { return non_transparent(); }


      void hls_mult(::f64 dRateH, ::f64 dRateL, ::f64 dRateS);
      void hls_rate(::f64 dRateH, ::f64 dRateL, ::f64 dRateS);
      void hue_rate(::f64 dRateL);
      void lightness_rate(::f64 dRateL);
      void saturation_rate(::f64 dRateL);
      constexpr void set(::rgba_t rgba);
      //constexpr void set(::rgba_t rgba);
      //constexpr void set_bgr(::bgra_t bgra);
      constexpr void set(::bgra_t bgra);
      void get_hls(::f64 & dHue, ::f64 & dLightness, ::f64 & dSaturation) const;
      void get_hsv(::f64 & dHue, ::f64 & dBlack, ::f64 & dWhite) const;

      static ::color::color from_hue(::f64 dHue);

      void set_hls(::f64 dHue, ::f64 dLightness, ::f64 dSaturation);
      void set_hsv(::f64 dHue, ::f64 dBlack, ::f64 dWhite);
      void hls_mult(hls & hls);
      void hls_rate(hls & hls);
      void get_hls(hls & hls) const;
      void get_hsv(hsv & hsv) const;
      void set_hls(const hls & hls);
      void set_hsv(const hsv & hsv);



      ::color::hls get_hls() const { hls hls; get_hls(hls); return hls; }

      ::color::hsv get_hsv() const { hsv hsv; get_hsv(hsv); return hsv; }

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

      constexpr ::u8 set_red(::u8 r) { return this->m_u8Red = r; }

      constexpr ::u8 set_green(::u8 g) { return this->m_u8Green = g; }

      constexpr ::u8 set_blue(::u8 b) { return this->m_u8Blue = b; }

      constexpr ::u8 set_opacity(::u8 a) { return this->m_u8Opacity = a; }

      constexpr ::u16 set_red(::u16 r) { this->m_u8Red = r >> 8; return r; }

      constexpr ::u16 set_green(::u16 g) { this->m_u8Green = g >> 8; return g;}

      constexpr ::u16 set_blue(::u16 b) { this->m_u8Blue = b >> 8; return b;}

      constexpr ::u16 set_opacity(::u16 a) { this->m_u8Opacity = a >> 8; return a;}

      constexpr ::i32 set_red(::i32 r) { this->m_u8Red = r; return r; }

      constexpr ::i32 set_green(::i32 g) { this->m_u8Green = g; return g; }

      constexpr ::i32 set_blue(::i32 b) { this->m_u8Blue = b; return b;}

      constexpr ::i32 set_opacity(::i32 a) { this->m_u8Opacity = a; return a;}

      constexpr ::f32 set_red(::f32 f) { this->m_u8Red = (::u8)(f * 255.0f); return f; }

      constexpr ::f32 set_green(::f32 f) { this->m_u8Green = (::u8)(f * 255.0f); return f;  }

      constexpr ::f32 set_blue(::f32 f) { this->m_u8Blue = (::u8)(f * 255.0f); return f;  }

      constexpr ::f32 set_opacity(::f32 f) { this->m_u8Opacity = (::u8)(f * 255.0f); return f;  }

      constexpr ::f64 set_red(::f64 f) { this->m_u8Red = (::u8)(f * 255.0); return f; }

      constexpr ::f64 set_green(::f64 f) { this->m_u8Green = (::u8)(f * 255.0); return f; }

      constexpr ::f64 set_blue(::f64 f) { this->m_u8Blue = (::u8)(f * 255.0); return f; }

      constexpr ::f64 set_opacity(::f64 f) { this->m_u8Opacity = (::u8)(f * 255.0); return f; }

      constexpr void set_opacity(class ::opacity opacity) { this->m_u8Opacity = (::u8)(opacity.u8_opacity() * 255.0); }

      constexpr void set_opaque() { this->m_u8Opacity = 255; }

      constexpr void set_unsigned_char(::u8 R, ::u8 G, ::u8 B) { m_u8Red = R; m_u8Green = G; m_u8Blue = B; m_u8Opacity = 255; }
      constexpr void set_unsigned_char(::u8 R, ::u8 G, ::u8 B, ::u8 A) { m_u8Red = R; m_u8Green = G; m_u8Blue = B; m_u8Opacity = A; }
      constexpr void set_f64(::f64 R, ::f64 G, ::f64 B) { m_u8Red = (::u8) (R * 255.); m_u8Green = (::u8) (G * 255.); m_u8Blue = (::u8) (B * 255.); m_u8Opacity = 255; }
      constexpr void set_f64(::f64 R, ::f64 G, ::f64 B, ::f64 A) { m_u8Red = (::u8)(R * 255.); m_u8Green = (::u8) (G * 255.); m_u8Blue = (::u8) (B * 255.); m_u8Opacity = (::u8) (A * 255.); }

      void make_black_and_white();

      constexpr operator ::color32_t() const 
      {

         return this->color32();

      }


      constexpr void set(::color32_t color32)
      {

         m_u8Red = color32.u8_red();
         m_u8Green = color32.u8_green();
         m_u8Blue = color32.u8_blue();
         m_u8Opacity = color32.u8_opacity();

      }

      
      constexpr void set(const ::color::color & color)
      {

         m_u32 = color.m_u32;

      }


      constexpr color & operator = (const ::color::color & color);
      constexpr color & operator = (::color32_t color32);
      constexpr color & operator = (enum_plain_color ecolor);
      color & operator = (const hls & hls);
      color & operator = (const hsv & hsv);

      bool parse_color(const ::scoped_string & scopedstr);

      //void set_color32(::color32_t color32);

      void hue_offset(::f64 dRadians);


      constexpr auto byte_minimum_rgb() const { return minimum({ u8_red(), u8_green(), u8_blue() }); }
      constexpr auto byte_maximum_rgb() const { return maximum({ u8_red(), u8_green(), u8_blue() }); }
      constexpr auto f32_minimum_rgb() const { return byte_minimum_rgb() / 255.f; }
      constexpr auto f32_maximum_rgb() const { return byte_maximum_rgb() / 255.f; }
      constexpr auto f64_minimum_rgb() const { return byte_minimum_rgb() / 255.; }
      constexpr auto f64_maximum_rgb() const { return byte_maximum_rgb() / 255.; }


      constexpr ::color::color & rate_rgb_set_opacity(class ::opacity opacity, ::f64 dRate)
      {

         rate_red(dRate);
         rate_green(dRate);
         rate_blue(dRate);

         set_opacity(opacity);

         return *this;

      }


      constexpr void rate_red(::f64 dRate) { m_u8Red = (::u8)(m_u8Red * dRate); }
      constexpr void rate_green(::f64 dRate) { m_u8Green = (::u8)(m_u8Green * dRate); }
      constexpr void rate_blue(::f64 dRate) { m_u8Blue = (::u8)(m_u8Blue * dRate); }
      constexpr void rate_opacity(::f64 dRate) { m_u8Opacity = (::u8)(m_u8Opacity * dRate); }


      inline static bool similar_color_component(::f64 d1, ::f64 d2) { return fabs(d2 - d1) < (1.0 / 255.0); }

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




      void blend(const ::color::color & color, ::f64 dRate)
      {

         ::f64 dComplement = 1.0 - dRate;

         m_u8Red = (::u8)(m_u8Red * dComplement + color.m_u8Red * dRate);
         m_u8Green = (::u8)(m_u8Green * dComplement + color.m_u8Green * dRate);
         m_u8Blue = (::u8)(m_u8Blue * dComplement + color.m_u8Blue * dRate);
         m_u8Opacity = (::u8)(m_u8Opacity * dComplement + color.m_u8Opacity * dRate);

      }

      ::color::color get_blend(const ::color::color& color, ::f64 dRate) const
      {

         ::color::color colorResult(*this);

         colorResult.blend(color, dRate);

         return colorResult;
         
      }

      //::f64 get_opacity_rate() const { return f64_opacity(); }
      //::f64 get_red_rate() const { return f64_red(); }
      //::f64 get_green_rate() const { return f64_green(); }
      //::f64 get_blue_rate() const { return f64_blue(); }

      constexpr ::f64 get_luminance() const { return (m_u8Red + m_u8Green + m_u8Blue) / (255.0 * 3.0); }
      ::f64 get_saturation() const { return get_hls().m_dS; }
      ::f64 get_hue() const { return get_hls().m_dH; }

      constexpr auto opaque() const { return *this & ::opacity(255); }

      
      constexpr color & operator &=(const class ::opacity & opacity)
      {

         this->m_u8Opacity = opacity.u8_opacity();

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
// Colors in NanoVG are stored as ::u32 ints in ABGR format.

// Returns a color value from red, green, blue values. Alpha will be set to 255 (1.0f).
//CLASS_DECL_ACME   ::color::color RGB_color(::u8 r, ::u8 g, ::u8 b);

// Returns a color value from red, green, blue values. Alpha will be set to 1.0f.
//CLASS_DECL_ACME ::color::color RGBf_color(::f32 r, ::f32 g, ::f32 b);

// Returns a color value from red, green, blue and m_u8Opacity values.
//CLASS_DECL_ACME ::color::color RGBA_color(::u8 r, ::u8 g, ::u8 b, ::u8 a);

// Returns a color value from red, green, blue and m_u8Opacity values.
//CLASS_DECL_ACME::color::color RGBAf_color(::f32 r, ::f32 g, ::f32 b, ::f32 a);

// Linearly interpolates from color c0 to c1, and returns resulting color value.
CLASS_DECL_ACME::color::color LerpRGBA_color(color c0, color c1, ::f64 u);

// Sets transparency of a color value.
CLASS_DECL_ACME::color::color TransRGBA_color(color c0, ::u8 a);

// Sets transparency of a color value.
CLASS_DECL_ACME::color::color TransRGBAf(color c0, ::f64 a);

// Returns color value specified by hue, saturation and lightness.
// HSL values are all in range [0..1], m_u8Opacity will be set to 255.
CLASS_DECL_ACME::color::color HSL_color(::f64 h, ::f64 s, ::f64 l);

// Returns color value specified by hue, saturation and lightness and m_u8Opacity.
// HSL values are all in range [0..1], m_u8Opacity in range [0..255]
CLASS_DECL_ACME ::color::color HSLA_color(::f64 h, ::f64 s, ::f64 l, ::u8 a);


} // namespace color


constexpr ::color::color color_with_u8_opacity(::u8 bAlpha, ::color32_t color);
constexpr ::color::color color_with_u8_opacity(::u8 bAlpha, enum_plain_color ecolor);
constexpr ::color::color opaque_color(::color32_t color32);
//constexpr ::color::color _color(enum_plain_color ecolor);
constexpr ::color::color opaque_color(enum_plain_color ecolor);



constexpr rgba_t argb_rgba(::u8 u8Opacity, ::u8 u8Red, ::u8 u8Green, ::u8 u8Blue)
{
   return { make_u32(u8Red, u8Green, u8Blue, u8Opacity) };
}

//constexpr ::u8 rgba_u8_red(::rgba_t rgba) { return lower_byte(rgba.m_u32); }
//constexpr ::u8 rgba_u8_green(::rgba_t rgba) { return lower_byte(rgba.m_u32 >> 8); }
//constexpr ::u8 rgba_u8_blue(::rgba_t rgba) { return lower_byte(rgba.m_u32 >> 16); }
//constexpr ::u8 rgba_u8_opacity(::rgba_t rgba) { return lower_byte(rgba.m_u32 >> 24); }


//constexpr ::u8 bgr_u8_blue(::u32 bgr) { return lower_byte(bgr); }
//constexpr ::u8 bgr_u8_green(::u32 bgr) { return lower_byte((bgr) >> 8); }
//constexpr ::u8 bgr_u8_red(::u32 bgr) { return lower_byte((bgr) >> 16); }
//constexpr ::u8 bgr_u8_opacity(::u32 bgr) { return lower_byte((bgr) >> 24); }


constexpr bgra_t argb_bgra(::u8 u8Opacity, ::u8 u8Red, ::u8 u8Green, ::u8 u8Blue)
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


//constexpr ::color::color argb(::i32 a, ::i32 r, ::i32 g, ::i32 b)
//{
//
//   return ::color::color(r, g, b, a);
//
//}


//constexpr ::color::color argb(::f64 a, ::f64 r, ::f64 g, ::f64 b)
//{
//
//   return ::color::color(r, g, b, a);
//
//}


namespace color
{


   constexpr color::color(enum_plain_color eplaincolor)
   {

      ::u32 ui;

      switch (eplaincolor)
      {
      case e_plain_color_black:
         ui = ::rgb(0, 0, 0).m_u32;
         break;
      case e_plain_color_red:
         ui = ::rgb(255, 0, 0).m_u32;
         break;
      case e_plain_color_green:
         ui = ::rgb(0, 255, 0).m_u32;
         break;
      case e_plain_color_blue:
         ui = ::rgb(0, 0, 255).m_u32;
         break;
      case e_plain_color_white:
         ui = ::rgb(255, 255, 255).m_u32;
         break;
      case e_plain_color_yellow:
         ui = ::rgb(255, 255, 0).m_u32;
         break;
      case e_plain_color_magenta:
         ui = ::rgb(255, 0, 255).m_u32;
         break;
      case e_plain_color_cyan:
         ui = ::rgb(0, 255, 255).m_u32;
         break;
      case e_plain_color_gray:
         ui = ::rgb(127, 127, 127).m_u32;
         break;
      default:
         ui = 0;
         break;
      };

      m_u32 = ui;

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

      m_u8Red = rgba.u8_red();
      m_u8Green = rgba.u8_green();
      m_u8Blue = rgba.u8_blue();
      m_u8Opacity = rgba.u8_opacity();

   }


   constexpr void color::set(bgra_t bgra)
   {

      m_u8Red = bgra.u8_red();
      m_u8Green = bgra.u8_green();
      m_u8Blue = bgra.u8_blue();
      m_u8Opacity = bgra.u8_opacity();

   }


   CLASS_DECL_ACME ::color::color hex_to_color(const_char_pointer psz);

   //constexpr void color::set_bgr(::u32 ui)
   //{

   //   m_u8Red = bgr_u8_red(ui);
   //   m_u8Green = bgr_u8_green(ui);
   //   m_u8Blue = bgr_u8_blue(ui);
   //   m_u8Opacity = bgr_u8_opacity(ui);

   //}


   //constexpr void color::set_bgra(::u32 ui)
   //{

   //   m_u8Red = bgra_u8_red(ui);
   //   m_u8Green = bgra_u8_green(ui);
   //   m_u8Blue = bgra_u8_blue(ui);
   //   m_u8Opacity = bgra_u8_opacity(ui);

   //}

} // namespace color


constexpr ::color::color color_with_u8_opacity(::u8 bAlpha, ::color32_t color32)
{

   ::color::color color;

   color.m_u32  = (color32.m_u32 & 0xffffff) | ((bAlpha & 0xff) << 24);

   return color;

}


constexpr::color::color color_with_u8_opacity(::u8 bAlpha, enum_plain_color ecolor)
{

   return color_with_u8_opacity(bAlpha, ::color::color(ecolor));

}


constexpr ::color::color opaque_color(::color32_t color32)
{

   return color_with_u8_opacity(255, color32);

}


constexpr ::color::color opaque_color(enum_plain_color ecolor)
{

   return opaque_color(::color::color(ecolor));

}





constexpr ::color::color color32_color_with_u8_opacity(::u8 u8Opacity, ::color32_t color32)
{

   return argb(u8Opacity, color32.u8_red(), color32.u8_green(), color32.u8_blue());

}


//constexpr ::color::color color32_color(color32_t color32)
//{
//
//   ::color::color color;
//
//   color.m_u8Red = color32_u8_red(color32);
//   color.m_u8Green = color32_u8_green(color32);
//   color.m_u8Blue = color32_u8_blue(color32);
//   color.m_u8Opacity = color32_u8_opacity(color32);
//
//   return color;
//
//}


#define __expand_f32_rgba(color) color.f32_red(), color.f32_green(), color.f32_blue(), color.f32_opacity()
#define __expand_f64_rgba(color) color.f64_red(), color.f64_green(), color.f64_blue(), color.f64_opacity()
#define __expand_f32_rgb(color) color.f32_red(), color.f32_green(), color.f32_blue()
#define __expand_f64_rgb(color) color.f64_red(), color.f64_green(), color.f64_blue()



namespace color
{


   inline hls::hls(const ::color::color & color)
   {

      operator=(color.get_hls());

   }




   inline hsv::hsv(const ::color::color & color)
   {

      operator=(color.get_hsv());

   }


} // namespace color



