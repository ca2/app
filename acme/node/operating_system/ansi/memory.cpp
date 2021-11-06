#include "framework.h"


#ifdef WINDOWS
/*
* Find the first occurrence of the byte string s in byte string l.
*/

void * memmem(const void * l, size_t l_len, const void * s, size_t s_len)
{
   char * cur, * last;
   const char * cl = (const char *)l;
   const char * cs = (const char *)s;

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

#endif // #ifdef WINDOWS

void* reverse_memchr(const void* l, int ch, size_t l_len)
{

   char* end;

   if (l_len <= 0)
   {

      return nullptr;

   }

   end = (char *) l + l_len - 1;

   while (end >= l)
   {

      if (*end == ch)
      {

         return end;

      }

   }

   return nullptr;

}

/*
* Find the last occurrence of the byte string s in byte string l.
*/

void* reverse_memmem(const void* l, size_t l_len, const void* s, size_t s_len)
{
   char* cur, * last;
   const char* cl = (const char*)l;
   const char* cs = (const char*)s;

   /* we need something to compare */
   if (l_len == 0 || s_len == 0)
      return nullptr;

   /* "s" must be smaller or equal to "l" */
   if (l_len < s_len)
      return nullptr;

   /* special case where s_len == 1 */
   if (s_len == 1)
      return memchr((void*)l, (int)*cs, l_len);

   /* the last position where its possible to find "s" in "l" */
   last = (char*)cl + l_len - s_len;

   for (cur = (char*)last; cur >= cl; cur--)
   {

      if (cur[0] == cs[0] && __memcmp(cur, cs, s_len) == 0)
      {

         return cur;

      }

   }

   return nullptr;

}


void* reverse_byte_not_in_block(const void* l, size_t l_len, const void* s, size_t s_len)
{

   char* cur, * last, *curByte;
   char* prev = nullptr;
   const char* cl = (const char*)l;
   const char* cs = (const char*)s;
   const char* ends = (const char*)s + s_len;

   /* we need something to compare */
   if (l_len <= 0)
      return nullptr;

   /* the last position where its possible to find "s" in "l" */
   last = (char*)cl + l_len - 1;

   for (cur = (char*)last; cur >= cl; cur--)
   {

      for (curByte = (char*)cs; curByte < ends; curByte++)
      {

         if (cur[0] == curByte[0])
         {

            return prev;

         }

      }

      prev = cur;

   }

   return prev;

}





CLASS_DECL_ACME::u32 __u32_hash(const char* psz)
{

   ::u32 u = 0;

   //DUMMY // dummy implementation

   while (*psz)
   {

      u += *psz;

      psz++;

   }

   return u;

}
