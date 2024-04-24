// Through https://github.com/nordlow/justcxx/blob/master/muldiv64.h
/*!
 * \file muldiv64.h
 * \brief Multiply and Divide for 64-bit Integers.
 * \see http://blogs.plinge.de/dev/2009/10/08/muldiv64
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

   /*! Determine the \em MSB of a value in O(log log n).
    * \return \em MSB.
    * \author Sean Eron Anderson
    */
   static inline unsigned int uint64_msb(uint64_t value)
   {
      const int MAX_LOGLOG = 6;
      const uint64_t BIT_LL[MAX_LOGLOG] = { 0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000, 0xFFFFFFFF00000000LL };
      const unsigned int EXP_LL[MAX_LOGLOG] = { 1, 2, 4, 8, 16, 32 };
      unsigned int r = 0;
      for (int i = MAX_LOGLOG - 1; i >= 0; i--) {
         if (value & BIT_LL[i]) {
            value >>= EXP_LL[i];
            r |= EXP_LL[i];
         }
      }
      return r;
   }

   /*!
    * \em Multiply a 64 and a 32-bit value and divide them by a \em 64-bit value.
    * Result bits above 64 are ignored, so overflow flags are not set.
    *
    * \param a 64-bit multiplicant
    * \param b 32-bit multiplicant
    * \param c  64-bit divisor
    *
    * \return  (a*b)/c (+/-) 1
    *
    * \author Axel Plinge
    */
   static inline uint64_t uint64_muldiv(uint64_t a, uint32_t b, uint64_t c)
   {
      const uint32_t aH = ((uint32_t*)&a)[1];
      const uint32_t aL = ((uint32_t*)&a)[0];

      // lower 32-bit portions yield 64-bit product that can be divided
      // directly giving 64-bits of result,
      uint64_t res = (aL * b) / c;

      // upper 32-bit have to be shifted, so calculate modulus 2^32
      const uint64_t prod_h = aH * b;
      const uint64_t div_h = prod_h / c; // division main
      const uint64_t mod_h = prod_h - c * div_h; // modulus

      // upper bits
      res += div_h << 32;
      if (mod_h == 0) {
         return res;
      }

      // remainder of division. if msb modulus < 32 we can be quick about
      // it
      if ((mod_h >> 32) == 0) {
         res += (mod_h << 32) / c;
         return res;
      }

      // if we reach this point we have full 64-bit values, i.e. a 96-bit
      // dividend. calculate an approximate result by shifting according
      // to msb set
      int msb_nominator = uint64_msb(mod_h) + 32;
      int msb_c = uint64_msb(c);
      int msb = maximum(msb_nominator, msb_c);
      int shift = msb - 63;
      res += (mod_h << (32 - shift)) / (c >> shift);

      return res;
   }

#ifdef __cplusplus
}
#endif