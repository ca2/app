// http://www.jbox.dk/sanos/source/lib/fcvt.c.html
//
// fcvt.c
//
// Floating p to string conversion routines
//
// Copyright (C) 2002 Michael Ringgaard. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include "framework.h"
//#include <math.h>

//
// cvt.c - IEEE floating p formatting routines for FreeBSD
// from GNU libc-4.6.27
//

#define CVTBUFSIZE  2 * DBL_MAX_10_EXP + 10

#define MAX_PRECISION 2048

char *ccvt_internal(double arg,int ndigits,int *decpt,int *sign,char *buf,int eflag, int * pi  = nullptr)
{
   int r2;
   double fi,fj;
   char *p,*point1;

   if(ndigits < 0) ndigits = 0;
   if(ndigits >= CVTBUFSIZE - 1) ndigits = CVTBUFSIZE - 2;
   r2 = 0;
   *sign = 0;
   p = &buf[0];
   if(arg < 0) {
      *sign = 1;
      arg = -arg;
   }
   arg = modf(arg,&fi);
   point1 = &buf[CVTBUFSIZE];

   if(fi != 0) {
      point1 = &buf[CVTBUFSIZE];
      while(fi != 0) {
         fj = modf(fi / 10,&fi);
         *--point1 = (int)((fj + .03) * 10) + '0';
         r2++;
      }
      while(point1 < &buf[CVTBUFSIZE]) *p++ = *point1++;
   }
   else if(arg > 0) {
      while((fj = arg * 10) < 1) {
         arg = fj;
         r2--;
      }
   }
   point1 = &buf[ndigits];
   if((eflag & 1) == 0) point1 += r2;
   *decpt = r2;
   if(point1 < &buf[0]) {
      buf[0] = '\0';
      return buf;
   }
   int i = 0;
   while(p <= point1 && p < &buf[CVTBUFSIZE] && (!(eflag & MAX_PRECISION) || (arg != 0.0 || i >= ndigits))) {
      arg *= 10;
      arg = modf(arg,&fj);
      *p++ = (int)fj + '0';
      i++;
   }
   if(pi != nullptr)
   {
      *pi =i;
   }
   if(point1 >= &buf[CVTBUFSIZE]) {
      buf[CVTBUFSIZE - 1] = '\0';
      return buf;
   }
   p = point1;
   *point1 += 5;
   while(*point1 > '9') {
      *point1 = '0';
      if(point1 > buf) {
         ++*--point1;
      }
      else {
         *point1 = '1';
         (*decpt)++;
         if((eflag & 1) == 0) {
            if(p > buf) *p = '0';
            p++;
         }
      }
   }
   *p = '\0';
   return buf;
}

int ccvt_dup(char *buf, int nchar, double arg,int ndigits,int *decpt,int *sign,int eflag)
{

   char sz[CVTBUFSIZE + 9];

   ccvt_internal(arg,ndigits,decpt,sign,sz,eflag);

   if(strlen(sz) > natural(nchar))
      return EINVAL;

   strcpy(buf,sz);

   return 0;

}


int ecvt_dup(char *buf,int nchar,double arg,int ndigits,int *decpt,int *sign)
{

   return ccvt_dup(buf,nchar, arg,ndigits,decpt,sign,1);

}


int fcvt_dup(char *buf, int nchar,double arg,int ndigits,int *decpt,int *sign)
{

   return ccvt_dup(buf,nchar,arg,ndigits,decpt,sign,0);

}


int max_cvt_dup(char *buf,int nchar,double arg,int ndigits,int *decpt,int *sign, int *pi)
{

   char sz[CVTBUFSIZE + 9];

   ccvt_internal(arg,ndigits,decpt,sign,sz,MAX_PRECISION, pi);

   if(strlen(sz) > natural(nchar))
      return EINVAL;

   strcpy(buf,sz);

   return 0;

}




