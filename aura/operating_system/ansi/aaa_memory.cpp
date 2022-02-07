#include "framework.h"

/*
* Find the first occurrence of the byte string s in byte string l.
*/

void * memmem(const void * l, size_t l_len, const void * s, size_t s_len)
{
   char * cur, * last;
   const char * cl = (const ::string &)l;
   const char * cs = (const ::string &)s;

   /* we need something to compare */
   if (l_len == 0 || s_len == 0)
      return nullptr;

   /* "s" must be smaller or equal to "l" */
   if (l_len < s_len)
      return nullptr;

   /* special case where s_len == 1 */
   if (s_len == 1)
      return memchr((void *)l, (int)*cs, l_len);

   /* the last position where its possible to find "s" in "l" */
   last = (char *)cl + l_len - s_len;

   for (cur = (char *)cl; cur <= last; cur++)
   {

      if (cur[0] == cs[0] && __memcmp(cur, cs, s_len) == 0)
      {

         return cur;

      }

   }

   return nullptr;

}


