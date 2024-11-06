/*
 *   Source file:      muldiv64.cpp
 *   Author:            Richard van der Wal
 *   Contact:         R.vdWal@xs4all.nl
 *
 *   Description:
 *      Implementation for muldiv64 and mulshr64
 *
 *   $Log: $
 */


/*
 * muldiv64
 * Multiplies an operant by a multiplier and divides the result by a divider
 * Used for scaling 64 bit integer values
 *     Xscaled = Xstart * Multiplier / Divider
 * Uses 128 bit intermediate result
 */

#include "framework.h"

#define ABS64(num) (num >=0 ? num : -num)


// http://www.pusersystem->m_createstruct.uaf.edu/~cs301/notes/Chapter5/node5.html
/*
 Multiply two 32-bit numbers, V1 and V2, to produce
 a 64 bit result in the HI/LO registers.
 The algorithm is high-school math:

         A B
       x C D
       ------
       AD || BD
 AC || CB || 0

 where A and B are the high and low short words of V1,
 C and D are the short words of V2, AD is the product of
 A and D, and X || Y is (X << 16) + Y.
 Since the algorithm is programmed in C, we need to be
 careful not to overflow.
*/


void mul64(huge_natural v1, huge_natural v2, huge_natural & hi, huge_natural & lo)
{
  huge_natural a, ca;
   huge_natural b, d;
   huge_natural x, y;

  a = (v1 >> 32) & 0xffffffff;
  b = v1 & 0xffffffff;
  ca = (v2 >> 32) & 0xffffffff;
  d = v2 & 0xffffffff;

  lo = b * d;                   /* BD */
  x = a * d + ca * b;            /* AD + CB */
  y = ((lo >> 32) & 0xffffffff) + x;

  lo = (lo & 0xffffffff) | ((y & 0xffffffff) << 32);
  hi = (y >> 32) & 0xffffffff;

  hi += a * ca;                  /* AC */
}

void mul64(huge_integer v1, huge_integer v2, huge_integer & hi, huge_natural & lo)
{
   if(v1 > 0)
   {
      if(v2 > 0)
      {
         mul64((huge_natural) v1, (huge_natural) v2, (huge_natural &) hi, lo);
      }
      else
      {
         mul64((huge_natural) v1, (huge_natural) -(huge_integer)v2, (huge_natural &) hi, lo);
         hi = -hi;
         lo = (huge_natural)-(huge_integer)lo;
      }
   }
   else
   {
      if(v2 > 0)
      {
         mul64((huge_natural) -v1, (huge_natural) v2, (huge_natural &) hi, lo);
         hi = -hi;
         lo = (huge_natural)-(huge_integer)lo;
      }
      else
      {
         mul64((huge_natural) -(huge_integer)v1, (huge_natural) -(huge_integer)v2, (huge_natural &) hi, lo);
      }
   }
}


// http://stackoverflow.com/questions/1870158/unsigned int-128-bit-division-on-64-bit-machine
   //64t hi, lo;
   //32t div;

   //64t rhi = hi/div;
   //64t rlo = hi % div + lo /div;
huge_natural div128_64(huge_natural hi, huge_natural lo, huge_natural div, huge_natural & remainder)
{
   for(size_t i = 1; i <= 64; ++i)
   {
      huge_natural t = huge_integer(hi) >> 63;
      // t is all ones if x(63) = 1
      // Shift the hi|lo left one bit
      hi = (hi << 1) | (lo >> 63);
      lo = lo << 1;

      if((hi | t) >= div)
      {
         hi -= div;
         lo += 1;
      }
   }
   remainder = hi;
   return lo;
}

huge_integer div128_64(huge_integer hi, huge_natural lo, huge_integer div, huge_natural & remainder)
{
   if(hi > 0)
   {
      if(div > 0)
      {
         return div128_64((huge_natural) hi, lo, (huge_natural) div, remainder);
      }
      else
      {
         return -(huge_integer)div128_64((huge_natural) hi, lo, (huge_natural) -(huge_integer)div, remainder);
      }
   }
   else
   {
      if(div > 0)
      {
         return -(huge_integer)div128_64((huge_natural) -(huge_integer)hi, (huge_natural)-(huge_integer)lo, (huge_natural) div, remainder);
      }
      else
      {
         return div128_64((huge_natural) -(huge_integer)hi, (huge_natural)-(huge_integer)lo, (huge_natural) -(huge_integer)div, remainder);
      }
   }
}



/** the two 32 bit parts of an 64 bit integer */
struct  u64_unsigned_int{
    unsigned int l : 32;
    unsigned int h : 32;
};

/**
 * determine the msb of a value in O(log log n)
 * @author Sean Eron Anderson
 */
inline unsigned int msb(huge_natural value)
{
    const int MAX_LOGLOG = 6;
    const huge_natural BIT_LL[MAX_LOGLOG] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000, 0xFFFFFFFF00000000uLL};
    const unsigned int EXP_LL[MAX_LOGLOG] = {1, 2, 4, 8, 16, 32};
    unsigned int r = 0;
    for (int i = MAX_LOGLOG-1; i >= 0; i--)  {
        if (value & BIT_LL[i])  {
            value >>= EXP_LL[i];
            r |= EXP_LL[i];
        }
    }
    return r;
}



static huge_natural const g_base = 1ULL<<32;
static huge_natural const g_maxdiv = (g_base-1)*g_base + (g_base-1);

huge_natural my_multdiv_64(huge_natural a, huge_natural b, huge_natural c)
{
    // First get the easy thing
    if(c == 0)
      return 0;

    huge_natural res = (a/c) * b + (a%c) * (b/c);
    a %= c;
    b %= c;
    // Are we done?
    if (a == 0 || b == 0)
        return res;
    // Is it easy to compute what remain to be added?
    if (c < g_base)
        return res + (a*b/c);
    // Now 0 < a < c, 0 < b < c, c >= 1ULL
    // Normalize
    huge_natural norm = g_maxdiv/c;
    c *= norm;
    a *= norm;
    // split into 2 digits
    huge_natural ah = a / g_base, al = a % g_base;
    huge_natural bh = b / g_base, bl = b % g_base;
    huge_natural ch = c / g_base, cl = c % g_base;
    // compute the product
    huge_natural p0 = al*bl;
    huge_natural u1 = p0 / g_base + al*bh;
    p0 %= g_base;
    huge_natural u2 = u1 / g_base + ah*bh;
    u1 = (u1 % g_base) + ah * bl;
    u2 += u1 / g_base;
    u1 %= g_base;
    // u2 holds 2 digits, u1 and p0 one

    // first digit is easy, not null only in case of overflow
//    huge_natural q2 = u2 / c;
    u2 = u2 % c;

    // second digit, estimate
    huge_natural q1 = u2 / ch;
    // and now adjust
    huge_natural rhat = u2 % ch;
    // the loop can be unrolled, it will be executed at most twice for
    // even g_bases -- three times for odd one -- due to the normalisation above
    while (q1 >= g_base || (rhat < g_base && q1*cl > rhat*g_base+u1)) {
        q1--;
        rhat += ch;
    }
    // subtract
    u1 = ((u2 % g_base) * g_base + u1) - q1 * cl;
    u2 = (u2 / g_base * g_base + u1 / g_base) - q1 * ch;
    u1 = u1 % g_base + (u2 % g_base) * g_base;

    // now u1 hold 2 digits, p0 one and u2 is to be ignored
    huge_natural q0 = u1 / ch;
    rhat = u1 % ch;
    while (q0 >= g_base || (rhat < g_base && q0*cl > rhat*g_base+p0)) {
        q0--;
        rhat += ch;
    }
    // we don't need to do the subtraction (needed only to get the remainder,
    // in which case we have to divide it by norm)
    return res + q0 + q1 * g_base; // + q2 *g_base*g_base
}


//
huge_integer _stdcall muldiv64(huge_integer number, huge_integer numerator, huge_integer denominator)
{
   return my_multdiv_64(number, numerator, denominator);

//   huge_integer hi;
//   huge_natural lo;
//   mul64(number, numerator, hi, lo);
//   huge_natural remainder;
//   return div128_64(hi, lo, denominator, remainder);
}

// /*
//  * mulshr64
//  * Multiplies an operant by a multiplier and right shifts the result rshift times
//  * Used for scaling 64 bit integer values
//  *     Xscaled = (Xstart * Multiplier) SHR rshift
//  * Uses 128 bit intermediate result
//  */
// huge_integer _stdcall mulshr64(huge_integer operant, huge_integer multiplier, uchar rshift)
// {
//    return (operant * multiplier) >> rshift;
// /*   // Declare 128bit storage
//    struct{
//       unsigned long DW[4];
//    }var128;

//    // Save combined sign on stack
//    _asmxxx{
//       mov      eax, dword ptr[operant+4]
//       xor      eax, dword ptr[multiplier+4]
//       pushfd
//    }

//    // Take absolute values because algorithm is for unsigned int only
//    operant      = ABS64(operant);
//    multiplier   = ABS64(multiplier);

//    _asmxxxx{
//       // Test rshift for >128
//       mov      al, unsigned char ptr[rshift]
//       cmp      al, 80
//       jl      shiftOK
//       popfd                           // cleanup stack
//       xor      edx, edx
//       xor      eax, eax
//       jmp      done
// shiftOK:
//       lea      edi,[var128]               // edi = &var128
//       // Check multiplier for 1 or 0
//       xor      eax, eax
//       cmp      eax, dword ptr[multiplier+4]
//       jnz      startMUL
//       cmp      eax, dword ptr[multiplier]
//       jnz      multiNotNUL
//       xor      edx, edx
//       popfd                           // cleanup stack
//       jmp      done
// multiNotNUL:
//       // set result HI part to 0
//       xor      eax,eax
//       mov      dword ptr[edi+12], eax
//       mov      dword ptr[edi+8], eax
//       mov      eax, 1
//       cmp      eax, dword ptr[multiplier]
//       jnz      smallMUL
//       // Multiplier is 1 so just copy operant to result
//       mov      eax, dword ptr[operant+4]
//       mov      dword ptr[edi+4], eax
//       mov      eax, dword ptr[operant]
//       mov      dword ptr[edi], eax
//       jmp      startDIV
// smallMUL:
//       // Test for 32/32 bit multiplication
//         xor      eax, eax
//         mov      ecx, dword ptr[operant+4]
//         or      ecx, eax         ;test for both hiwords zero.
//       jnz      startMUL
//       // Do 32/32 bit multiplication
//         mov      ecx, dword ptr[multiplier]
//       mov      eax, dword ptr[operant]
//       mul      ecx
//       mov      dword ptr[edi+4], edx
//       mov      dword ptr[edi], eax
//       jmp      startDIV
// startMUL:
//       // Check signs
//       // Multiply: var128 = operant * multiplier
//       mov      eax, dword ptr[multiplier]      // eax = LO(multiplier)
//       mul      dword ptr[operant]            // edx:eax = eax * LO(operant)
//       mov      dword ptr[edi], eax            // var128.DW0 = eax
//       mov      ecx, edx                  // ecx = edx

//       mov      eax, dword ptr[multiplier]      // eax = LO(multiplier)
//       mul      dword ptr[operant+4]         // edx:eax = eax * HI(operant)
//       add      eax, ecx                  // eax = eax + ecx
//       adc      edx, 0                     // edx = edx + 0 + carry
//       mov      ebx, eax
//       mov      ecx, edx

//       mov      eax, dword ptr[multiplier+4]
//       mul      dword ptr[operant]
//       add      eax, ebx
//       mov      dword ptr[edi+4], eax
//       adc      ecx, edx
//       pushfd

//       mov      eax, dword ptr[multiplier+4]
//       mul      dword ptr[operant+4]
//       popfd
//       adc      eax, ecx
//       adc      edx, 0
//       mov      dword ptr[edi+8], eax
//       mov      dword ptr[edi+12], edx
// startDIV:
//       // Divide: var128 = var128 / (2^rshift)
//       //
//       xor      eax, eax
//       mov      al, unsigned char ptr[rshift]
//       cmp      al, 0
//       jz      applySign

//       // Start 128bit right shift
//       //
//       // Test shift for multiples of 32
//       mov      cl, 0x20
//       div      cl
//       mov      cl, al                  // Store number of 32 blocks in counter
//       mov      char ptr[rshift], ah      // Store remaining number of shifts
//       // Test shift not equal or larger than 4*32 already done at the begining
//       // Do dword shift cl times (maximum = 3)
//       xor      ch, ch
//       xor      edx, edx
//       jcxz   bitShift
//       mov      eax, dword ptr[edi+4]
//       mov      dword ptr[edi], eax
//       mov      eax, dword ptr[edi+8]
//       mov      dword ptr[edi+4], eax
//       mov      eax, dword ptr[edi+12]
//       mov      dword ptr[edi+8], eax
//       mov      dword ptr[edi+12], edx
//       dec      cx
//       jcxz   bitShift
//       mov      eax, dword ptr[edi+4]
//       mov      dword ptr[edi], eax
//       mov      eax, dword ptr[edi+8]
//       mov      dword ptr[edi+4], eax
//       mov      dword ptr[edi+8], edx
//       dec      cx
//       jcxz   bitShift
//       mov      eax, dword ptr[edi+4]
//       mov      dword ptr[edi], eax
//       mov      dword ptr[edi+4], edx

// bitShift:
//       // Do multiple precision bitshift
//       mov      cl, unsigned char ptr[rshift]
//       mov      eax, dword ptr[edi+4]
//       shrd   dword ptr[edi], eax, cl
//       mov      eax, dword ptr[edi+8]
//       shrd   dword ptr[edi+4], eax, cl
//       mov      eax, dword ptr[edi+12]
//       shrd   dword ptr[edi+8], eax, cl
//       // To sign correction and return

// applySign:
//       // Correct the sign of the result based on the stored combined sign
//       popfd
//       jns      storeRes
//       not      dword ptr[edi+12]
//       not      dword ptr[edi+ 8]
//       not      dword ptr[edi+ 4]
//       not      dword ptr[edi]
//       add      dword ptr[edi], 1
//       adc      dword ptr[edi+ 4], 0
//       adc      dword ptr[edi+ 8], 0
//       adc      dword ptr[edi+12], 0

// storeRES:
//       // get low order qword from var128
//       mov      edx, dword ptr[edi+4]
//       mov      eax, dword ptr[edi]
// done:
//    }
//    // result is returned in edx:eax*/
// }


