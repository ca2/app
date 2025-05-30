#pragma once



CLASS_DECL_ACME void * memory_set(void * p, int i, memsize iSize);
CLASS_DECL_ACME void * memory_and(void * p, const void * point1, const void * point2, memsize iSize);
CLASS_DECL_ACME void * memory_copy(void * dst, const void * src, memsize iSize);
CLASS_DECL_ACME void * memory_transfer(void * dst, const void * src, memsize iSize);
CLASS_DECL_ACME ::wide_character * wide_memory_copy(::wide_character * dst, const ::wide_character * src, memsize iSize);

CLASS_DECL_ACME void * reverse_memory(void * p, memsize iSize);
CLASS_DECL_ACME void * reverse_memory_copy(void * p, const void * point1, memsize iSize);


CLASS_DECL_ACME ::std::strong_ordering memory_order(const void* sz1, const void* sz2, memsize iSize);

CLASS_DECL_ACME ::std::strong_ordering _memory_order(const void* p1, const void* p2, memsize size);


#ifdef __cplusplus


inline void * zero(void * p, memsize size) { memory_set(p, 0, size); return p; }


inline bool is_zero(const void * p, memsize iSize)
{

   unsigned char * pb = (unsigned char *) p;

   while(*pb == '\0' && iSize > 0)
   {

      pb++;

      iSize--;

   }

   return iSize == 0;

}




//#define zero(array) (::zero(array, sizeof(array)))



#endif









