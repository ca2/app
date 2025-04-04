#pragma once




template < primitive_natural NATURAL >
class bits
{
public:


   NATURAL     m_natural;


   bits() { m_natural = 0; }
   bits(no_initialize_t) {}
   bits(NATURAL n) : m_natural(n) { }
   bits(nullptr_t) { m_natural = 0; }

   
   template < primitive_integral INTEGRAL >
   inline bool is_set(INTEGRAL bit) const { return (m_natural >> (unsigned char) bit) & 1; }
   template < primitive_integral INTEGRAL >
   inline void set(INTEGRAL bit) { m_natural = m_natural | (NATURAL)(1ull << (unsigned char)bit); }
   template < primitive_integral INTEGRAL >
   inline void unset(INTEGRAL bit) { m_natural = m_natural & (NATURAL)(~(1ull << (unsigned char)bit)); }
   template < primitive_integral INTEGRAL >
   inline void set(INTEGRAL bit, bool bSet) { if (bSet) set(bit); else unset(bit); }


   template < primitive_integral INTEGRAL >
   bool operator [] (INTEGRAL bit) const { return is_set(bit); }


};


