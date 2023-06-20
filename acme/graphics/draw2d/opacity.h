// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-26 00:17
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


class CLASS_DECL_ACME opacity
{
protected:


   ::u8        m_u8Opacity;


public:


   constexpr opacity() { m_u8Opacity = 255; }
   constexpr opacity(const class ::opacity & opacity) : m_u8Opacity(opacity.m_u8Opacity) { }

   template < primitive_floating FLOATING >
   constexpr opacity(FLOATING f) { m_u8Opacity = u8_clip(f * 255.); }
   template < primitive_integral INTEGRAL >
   constexpr opacity(INTEGRAL i) { m_u8Opacity = u8_clip(i); }


   constexpr ::f64 f64_opacity() const { return m_u8Opacity / 255.; }
   constexpr ::f32 f32_opacity() const { return m_u8Opacity / 255.f; }
   constexpr ::u8 u8_opacity() const { return m_u8Opacity; }


   constexpr bool is_opaque() const { return m_u8Opacity == 255; }
   constexpr bool is_translucent() const { return m_u8Opacity < 255; }
   constexpr bool is_transparent() const { return m_u8Opacity == 0; }
   constexpr bool non_transparent() const { return m_u8Opacity > 0; }
   constexpr ::u8 complement() const { return 255 - m_u8Opacity; }

   template < primitive_floating FLOATING >
   constexpr opacity & operator = (FLOATING f) { m_u8Opacity = u8_clip(f * 255.); return *this; }
   template < primitive_integral INTEGRAL >
   constexpr opacity & operator = (INTEGRAL i) { m_u8Opacity = u8_clip(i); return *this; }

   template < primitive_integral INTEGRAL >
   constexpr opacity operator + (INTEGRAL i) { return u8_clip(m_u8Opacity + i); }
   template < primitive_integral INTEGRAL >
   constexpr opacity operator - (INTEGRAL i) { return u8_clip(m_u8Opacity - i); }

};


inline class ::opacity operator "" _opacity(long double d) { return d; }
inline class ::opacity operator "" _opacity(unsigned long long ul) { return (::u8) ul; }




