// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-26 00:17
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#pragma once


class CLASS_DECL_ACME opacity
{
protected:


   byte        m_bAlpha;


public:


   opacity() { m_bAlpha = 255; }
   opacity(const class ::opacity & opacity) : m_bAlpha(opacity.m_bAlpha) { }
   template < primitive_floating FLOATING >
   opacity(FLOATING f) { m_bAlpha = byte_clip(f * 255.); }
   template < primitive_integral INTEGRAL >
   opacity(INTEGRAL i) { m_bAlpha = byte_clip(i); }


   double get_opacity_rate() const { return m_bAlpha / 255.; }
   byte get_alpha() const { return m_bAlpha; }


   bool is_opaque() const { return m_bAlpha == 255; }
   bool is_translucent() const { return m_bAlpha < 255; }
   bool is_transparent() const { return m_bAlpha == 0; }
   bool non_transparent() const { return m_bAlpha > 0; }
   byte complement() const { return 255 - m_bAlpha; }

   template < primitive_floating FLOATING >
   opacity & operator = (FLOATING f) { m_bAlpha = byte_clip(f * 255.); return *this; }
   template < primitive_integral INTEGRAL >
   opacity & operator = (INTEGRAL i) { m_bAlpha = byte_clip(i); return *this; }


   template < primitive_integral INTEGRAL >
   opacity operator + (INTEGRAL i) { return byte_clip(m_bAlpha + i); }
   template < primitive_integral INTEGRAL >
   opacity operator - (INTEGRAL i) { return byte_clip(m_bAlpha - i); }

};


inline class ::opacity operator "" _opacity(long double d) { return d; }




