#pragma once



CLASS_DECL_AURA void * __memset(void * p, i32 i, memsize iSize);
CLASS_DECL_AURA void * __memand(void * p, const void * point1, const void * point2, memsize iSize);
CLASS_DECL_AURA void * memcpy_dup(void * dst, const void * src, memsize iSize);
CLASS_DECL_AURA void * __memmov(void * dst, const void * src, memsize iSize);
CLASS_DECL_AURA i32    __memcmp(const void * sz1, const void * sz2, memsize iSize);
CLASS_DECL_AURA widechar * __wmemcpy(widechar * dst, const widechar * src, memsize iSize);

CLASS_DECL_AURA void * reverse_memory(void * p, memsize iSize);
CLASS_DECL_AURA void * reverse_memcpy(void * p, const void * point1, memsize iSize);




#ifdef __cplusplus


inline void * zero(void * p, memsize size) { __memset(p, 0, size); return p; }


inline bool is_zero(void * p, memsize iSize)
{

   u8 * pb = (u8 *) p;

   while(*pb == '\0' && iSize > 0)
   {

      pb++;

      iSize--;

   }

   return iSize == 0;

}



#define xxf_zeroa(array) (::zero(array, sizeof(array)))




inline void copy(void *, const void *);



#endif









