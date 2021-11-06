/*
Copyright (ca) 2003-2004, Mark Borgerding



Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the author nor the names of any contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* kiss_fft.h
   defines kiss_fft_scalar as either i16 or a double type
   and defines
   typedef struct { kiss_fft_scalar r; kiss_fft_scalar i; }COMPLEXD; */
#include "fft.h"


#define MAXFACTORS 32
/* e.g. an fft of length 128 has 4 factors
 as far as kissfft is concerned
 4*4*4*2
 */

struct kiss_fft_state{
    i32 nfft;
    i32 inverse;
    i32 factors[2*MAXFACTORS];
    COMPLEXD twiddles[1];
};

/*
  Explanation of macros dealing with complex math:

   C_MUL(m,a,b)         : m = a*b
   C_FIXDIV( ca , div )  : if a fixed point_i32 impl., ca /= div. noop otherwise
   C_SUB( res, a,b)     : res = a - b
   C_SUBFROM( res , a)  : res -= a
   C_ADDTO( res , a)    : res += a
 * */
#ifdef FIXED_POINT

#   define smul(a,b) ( (long)(a)*(b) )
#   define sround( x )  (i16)( ( (x) + (1<<14) ) >>15 )

#   define S_MUL(a,b) sround( smul(a,b) )

#   define C_MUL(m,a,b) \
      do{ (m).r = sround( smul((a).r,(b).r) - smul((a).i,(b).i) ); \
          (m).i = sround( smul((a).r,(b).i) + smul((a).i,(b).r) ); }while(0)

#   define C_FIXDIV(ca,div) \
    do{ (ca).r /= div; (ca).i /=div; }while(0)

#   define C_MULBYSCALAR( ca, s ) \
    do{ (ca).r =  sround( smul( (ca).r , s ) ) ;\
        (ca).i =  sround( smul( (ca).i , s ) ) ; }while(0)

#else  /* not FIXED_POINT*/

#   define S_MUL(a,b) ( (a)*(b) )
#define C_MUL(m,a,b) \
    do{ (m).r = (a).r*(b).r - (a).i*(b).i;\
        (m).i = (a).r*(b).i + (a).i*(b).r; }while(0)
#   define C_FIXDIV(ca,div) /* NOOP */
#   define C_MULBYSCALAR( ca, s ) \
    do{ (ca).r *= (s);\
        (ca).i *= (s); }while(0)
#endif

#define  C_ADD( res, a,b)\
    do {    (res).r=(a).r+(b).r;  (res).i=(a).i+(b).i;  }while(0)
#define  C_SUB( res, a,b)\
    do {    (res).r=(a).r-(b).r;  (res).i=(a).i-(b).i;  }while(0)
#define C_ADDTO( res , a)\
    do {    (res).r += (a).r;  (res).i += (a).i;  }while(0)
#define C_SUBFROM( res , a)\
    do {    (res).r -= (a).r;  (res).i -= (a).i;  }while(0)

void kf_cexp(COMPLEXD * x,double phase); /* returns e ** (j*phase)   */

/* a debugging function */
#define pcpx(ca)\
    fprintf(stderr,"%g + %gi\n",(double)((ca)->r),(double)((ca)->i) )
