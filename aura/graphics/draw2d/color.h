#pragma once


//
//
////#define  HLSMAX   100.0 /* H,L, and S vary over 0-HLSMAX */
////#define  RGBMAX   100.0   /* R,G, and B vary over 0-RGBMAX */
///* HLSMAX BEST IF DIVISIBLE BY 6 */
///* RGBMAX, HLSMAX must each fit in a byte. */
///* Hue is undefined if Saturation is 0 (grey-scale) */
///* This value determines where the Hue scrollbar is */
///* initially set for achromatic colors */
//#define UNDEFINED_HUE (HLSMAX*2.0/3.0)
//
//class rgb
//{
//public:
//
//
//   int         m_iR;
//   int         m_iG;
//   int         m_iB;
//
//
//   rgb() {}
//
//   rgb(e_zero_init) : m_iR(0), m_iG(0), m_iB(0) {}
//
//   rgb(COLORREF cr) : m_iR(colorref_get_r_value(cr)), m_iG(colorref_get_r_value(cr)), m_iB(colorref_get_r_value(cr)) {}
//
//   rgb(int iR, int iG, int iB) : m_iR(iR), m_iG(iG), m_iB(iB) {}
//
//   rgb(const rgb & rgb) : m_iR(rgb.m_iR), m_iG(rgb.m_iG), m_iB(rgb.m_iB) { }
//
//   rgb & operator =(const ::var & var);
//
//   float fr() const {return m_iR / 255.f;}
//   float fg() const {return m_iG / 255.f;}
//   float fb() const {return m_iB / 255.f;}
//   double dr() const {return m_iR / 255.;}
//   double dg() const {return m_iG / 255.;}
//   double db() const {return m_iB / 255.;}
//
//};
//
//
//auto inline red(COLORREF rgba) { return ((byte)(rgba & 0xff)); }
//auto inline green(COLORREF rgba) { return ((byte)((rgba >> 8) & 0xff)); }
//auto inline blue(COLORREF rgba) { return ((byte)((rgba >> 16) & 0xff)); }
//auto inline opacity(COLORREF rgba) { return ((byte)((rgba >> 24) & 0xff)); }
//
//class rgba :
//   public rgb
//{
//public:
//
//   int      m_iA;
//
//   rgba() {}
//   rgba(e_zero_init) : rgb(zero_init), m_iA(0) {}
//   rgba(int iR, int iG, int iB, int iA) : rgb(iR, iG, iB), m_iA(iA) {}
//   rgba(COLORREF cr) : rgb(cr), m_iA(colorref_get_a_value(cr)) {}
//   rgba(const ::rgb & rgb) : ::rgb(rgb), m_iA(255) { }
//   rgba(const ::rgba & rgba) : ::rgb(rgba), m_iA(rgba.m_iA) { }
//
//   rgba & operator =(const ::var & var);
//
//   float fa() const {return m_iA / 255.f;}
//   double da() const {return m_iA / 255.;}
//
//};
//
//
//inline auto red(const rgb & rgb) { return rgb.m_iR; }
//inline auto green(const rgb & rgb) { return rgb.m_iG; }
//inline auto blue(const rgb & rgb) { return rgb.m_iB; }
//inline auto opacity(const rgb & rgba) { return 255; }
//inline auto opacity(const rgba & rgba) { return rgba.m_iA; }
//
//#define A_RGB(a, rgb) ARGB(a, ::red(rgb), ::green(rgb), ::blue(rgb))
//
//
//class hls
//{
//public:
//
//
//   double m_dH;
//   double m_dL;
//   double m_dS;
//
//   hls() {}
//   hls(e_zero_init): m_dH(0.0), m_dL(0.0), m_dS(0.0) {}
//   hls(double dH, double dL = 0.5, double dS = 1.0) : m_dH(dH), m_dL(dL), m_dS(dS) {}
//
//   hls & operator =(const ::var & var);
//
//
//};
//
//inline var & assign(var & var, const ::hls & hls);
//
//class CLASS_DECL_AURA color :
//   public rgba
//{
//public:
//
//   static ::color transparent;
//   static ::color black;
//   static ::color red;
//   static ::color green;
//   static ::color blue;
//   static ::color yellow;
//   static ::color cyan;
//   static ::color magenta;
//   static ::color white;
//
//   enum e_channel
//   {
//
//      channel_red = 0,
//      channel_green = 1,
//      channel_blue = 2,
//      channel_alpha = 3
//
//   };
//
//
//   color();
//   color(const color & color);
//   color(enum_color ecolor, int A = 255);
//   color(const hls & hls, int A = 255);
//   color(COLORREF cr);
//   color(int R, int G, int B, int A = 255);
//   ~color();
//
//
//   bool is_set() const { return m_iA >= 0; }
//
//
//   void hls_mult(double dRateH, double dRateL, double dRateS);
//   void hls_rate(double dRateH, double dRateL, double dRateS);
//   void set_rgb(COLORREF cr);
//   void set_argb(COLORREF cr);
//   void set_bgr(u32 dw);
//   void get_hls(double & dHue, double & dLightness, double & dSaturation) const;
//
//   void set_hls(double dHue, double dLightness, double dSaturation);
//   void hls_mult(hls & hls);
//   void hls_rate(hls & hls);
//   void get_hls(hls & hls) const;
//   void set_hls(const hls & hls);
//
//   auto get_hls() const { hls hls; get_hls(hls); return hls; }
//
//   u32 get_rgb() const;
//   u32 get_bgr() const;
//   u32 get_rgba() const;
//   u32 get_bgra() const;
//
////   operator rgb & () {return m_rgb;}
////   operator const rgb & () const {return m_rgb;}
////   operator rgba & () {return m_rgba;}
////   operator const rgba & () const {return m_rgba;}
//
//   void set(int R, int G, int B);
//   void set(int R, int G, int B, int A);
//
//   operator COLORREF() const;
//
//   color & operator = (const color & color);
//   color & operator = (COLORREF cr);
//   color & operator = (enum_color ecolor);
//   color & operator = (const hls & hls);
//
//   bool parse_color(const char * psz);
//
//   void set_COLORREF(COLORREF cr);
//
//   void hue_offset(double dRadians);
//
//
//   inline static bool similar_color_component(double d1, double d2) { return fabs(d2 - d1) < (1.0 / 255.0); }
//
//   bool operator == (const color & color) const { return memcmp(this, &color, sizeof(color)) == 0; }
//   bool operator == (COLORREF cr) const { return this->operator COLORREF() == cr; }
//   bool operator == (enum_color ecolor) const { return this->operator COLORREF() == ::color(ecolor).operator COLORREF(); }
//   bool operator == (const hls & hls) const
//   {
//
//      auto hlsThis = get_hls();
//
//      return similar_color_component(hlsThis.m_dH, hls.m_dH)
//         && similar_color_component(hlsThis.m_dL, hls.m_dL)
//         && similar_color_component(hlsThis.m_dS, hls.m_dS);
//   }
//   bool operator != (const color& color) const { return !operator == (color); }
//   bool operator != (COLORREF cr) const { return !operator == (cr); }
//   bool operator != (enum_color ecolor) const { return !operator == (ecolor); }
//   bool operator != (const hls& hls) const { return !operator == (hls); }
//
//
//
//};
//
//
//CLASS_DECL_AURA COLORREF alpha_color(BYTE bAlpha, COLORREF cr);
//CLASS_DECL_AURA COLORREF alpha_color(BYTE bAlpha, enum_color ecolor);
//CLASS_DECL_AURA COLORREF opaque_color(COLORREF cr);
//CLASS_DECL_AURA COLORREF pure_color(enum_color ecolor);
//CLASS_DECL_AURA COLORREF opaque_color(enum_color ecolor);
//
//
//#define rgb_get_r_value(rgb)      (LOBYTE(rgb))
//#define rgb_get_g_value(rgb)      (LOBYTE((rgb)>>8))
//#define rgb_get_b_value(rgb)      (LOBYTE((rgb)>>16))
//#define rgb_get_a_value(rgb)      (LOBYTE((rgb)>>24))
//
//#define bgr_get_b_value(bgr)      (LOBYTE(bgr))
//#define bgr_get_g_value(bgr)      (LOBYTE((bgr)>>8))
//#define bgr_get_r_value(bgr)      (LOBYTE((bgr)>>16))
//#define bgr_get_a_value(bgr)      (LOBYTE((bgr)>>24))
//
//
//
//inline void __exchange(::stream & s, ::rgb & rgb);
//
//
//
//inline void __exchange(::stream & s, ::rgba & rgba);
//
//
//
//inline void __exchange(::stream & s, ::hls & hls);
//
//
//
