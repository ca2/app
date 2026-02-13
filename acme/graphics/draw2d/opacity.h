// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-26 00:17
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


class CLASS_DECL_ACME opacity
{
protected:


   unsigned char        m_uchOpacity;


public:


   constexpr opacity() { m_uchOpacity = 255; }
   constexpr opacity(const class ::opacity & opacity) : m_uchOpacity(opacity.m_uchOpacity) { }

   template < prototype_floating FLOATING >
   constexpr opacity(FLOATING f) { m_uchOpacity = byte_clip(f * 255.); }
   template < prototype_integral INTEGRAL >
   constexpr opacity(INTEGRAL i) { m_uchOpacity = byte_clip(i); }


   constexpr double f64_opacity() const { return m_uchOpacity / 255.; }
   constexpr float f32_opacity() const { return m_uchOpacity / 255.f; }
   constexpr unsigned char byte_opacity() const { return m_uchOpacity; }


   constexpr bool is_opaque() const { return m_uchOpacity == 255; }
   constexpr bool is_translucent() const { return m_uchOpacity < 255; }
   constexpr bool is_transparent() const { return m_uchOpacity == 0; }
   constexpr bool non_transparent() const { return m_uchOpacity > 0; }
   constexpr unsigned char complement() const { return 255 - m_uchOpacity; }

   template < prototype_floating FLOATING >
   constexpr opacity & operator = (FLOATING f) { m_uchOpacity = byte_clip(f * 255.); return *this; }
   template < prototype_integral INTEGRAL >
   constexpr opacity & operator = (INTEGRAL i) { m_uchOpacity = byte_clip(i); return *this; }

   template < prototype_integral INTEGRAL >
   constexpr opacity operator + (INTEGRAL i) { return byte_clip(m_uchOpacity + i); }
   template < prototype_integral INTEGRAL >
   constexpr opacity operator - (INTEGRAL i) { return byte_clip(m_uchOpacity - i); }

};


inline class ::opacity operator""_opacity(long double d) { return d; }
inline class ::opacity operator""_opacity(unsigned long long ul) { return (unsigned char) ul; }




