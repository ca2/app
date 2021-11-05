// http://www.beedub.com/Sprite093/src/lib/c/etc/gcvt.c
//#if defined(LIBC_SCCS) && !defined(lint)
//static char sccsid[] = "@(#)gcvt.c	5.2 (Berkeley) 3/9/86";
//#endif LIBC_SCCS and not lint

/*
* gcvt  - Floating output conversion to minimal length string
*/

#include "framework.h"


#define GCVTBUFSIZE 2 * DBL_MAX_10_EXP + 33

char * gcvt_internal(double number,int ndigit, char * buf)
{
   int sign,decpt;
   char sz[GCVTBUFSIZE];
   char *point1;
   char *point2;
    int i;

   ecvt_dup(sz,GCVTBUFSIZE,  number,ndigit,&decpt,&sign);
   point1 = sz;
   point2 = buf;
   if(sign)
      *point2++ = '-';
   for(i=ndigit - 1; i>0 && point1[i] == '0'; i--)
      ndigit--;
   if((decpt >= 0 && decpt - ndigit > 4) || (decpt < 0 && decpt < -3))  /* use E-style */
   {
      decpt--;
      *point2++ = *point1++;
      *point2++ = '.';
      for(i=1; i<ndigit; i++)
         *point2++ = *point1++;
      *point2++ = 'e';
      if(decpt<0) {
         decpt = -decpt;
         *point2++ = '-';
      }
      else
         *point2++ = '+';
      *point2++ = decpt / 10 + '0';
      *point2++ = decpt % 10 + '0';
   }
   else {
      if(decpt <= 0) {
         if(*point1 != '0')
            *point2++ = '.';
         while(decpt<0) {
            decpt++;
            *point2++ = '0';
         }
      }
      for(i=1; i <= ndigit; i++) {
         *point2++ = *point1++;
         if(i == decpt)
            *point2++ = '.';
      }
      if(ndigit<decpt) {
         while(ndigit++<decpt)
            *point2++ = '0';
         *point2++ = '.';
      }
   }
   if(point2[-1] == '.')
      point2--;
   *point2 = '\0';
   return(buf);
}




int gcvt_dup(char *buf,int nchar,double arg,int ndigits)
{

   char sz[GCVTBUFSIZE + 9];

   gcvt_internal(arg,ndigits,sz);

   if(strlen(sz) > natural(nchar))
      return EINVAL;

   strcpy(buf,sz);

   return 0;

}



