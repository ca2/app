#include "framework.h"

CLASS_DECL_AQUA void pre_multiply_alpha(unsigned int * pinteraction,int cx,int cy,int stride)
{

   int s =  stride / 4 * cy;

   for(int i = 0; i < s; i++)
   {
      pinteraction[i] = ((pinteraction[i] & 0xff000000) >> 24) << 24
         | (((((pinteraction[i] & 0xff0000) >> 16) * ((pinteraction[i] & 0xff000000) >> 24)) << 8) & 0xff0000)
         | ((((pinteraction[i] & 0xff00) >> 8) * ((pinteraction[i] & 0xff000000) >> 24)) & 0xff00)
         | (((pinteraction[i] & 0xff) * ((pinteraction[i] & 0xff000000) >> 24)) >> 8);
      //pinteraction++;
   }

}