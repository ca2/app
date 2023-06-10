// Created by camilo on 2022-02-14 10:51 PM <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME const void * memory_find(const void* l, memsize l_len, const void* s, memsize s_len);


#ifdef _WIN32


inline const void * _memory_find(const void* l, memsize l_len, const void* s, memsize s_len)
{

   const ::u8* cur;

   const ::u8* last;

   const ::u8* cl = (const ::u8*)l;
   const ::u8* cs = (const ::u8*)s;

   /* the last position where its possible to find "s" in "l" */
   last = cl + l_len - s_len;

   for (cur = cl; cur <= last; cur++)
   {

      if (cur[0] == cs[0] && _memory_order(cur, cs, s_len) == 0)
      {

         return (const void *) cur;

      }

   }

   return nullptr;

}

#else


inline const void * _memory_find(const void* l, memsize l_len, const void* s, memsize s_len)
{

   return memmem(l, l_len, s, s_len);

}


#endif



