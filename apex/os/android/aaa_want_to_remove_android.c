#include "framework.h"


void swab(const void *from, void*to, ssize_t n)
{
   ssize_t i;

   if (n < 0)
      return;

   for (i = 0; i < (n/2)*2; i += 2)
      *((u16*)to+i) = __arch__swab16(*((u16*)from+i));
}

// used deep inside FreeImage
void* lfind( const void * key, const void * apex, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) )
{

   char * Ptr = (char *) apex;

   size_t i;

   for(i = 0; i != *num; i++, Ptr += width)
   {
      if(fncomparison(key, Ptr) == 0)
         return Ptr;
   }

   return NULL;

}


void* lsearch( const void * key, const void * apex, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) )
{

   char * Ptr = (char *) apex;

   size_t i;

   for(i = 0; i != *num; i++, Ptr += width)
   {
      if(fncomparison(key, Ptr) == 0)
         return Ptr;
   }

   *num = i;

   return Ptr;

}






