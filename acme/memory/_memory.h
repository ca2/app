// Created by camilo on 2022-02-14 10:51 PM <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME const void * memory_find(const void* l, memsize l_len, const void* s, memsize s_len);


#if defined(_WIN32) || defined(__BSD__) || defined(__APPLE__)


const void * _memory_find(const void * l, memsize l_len, const void * s, memsize s_len);

#else


inline const void * _memory_find(const void* l, memsize l_len, const void* s, memsize s_len)
{

   return memmem(l, l_len, s, s_len);

}


#endif


inline const void * _memory_find_u8(const void* l, int i, memsize len)
{

    auto u = (unsigned char) (*((::u32*)(&i)) & 0xff);

    auto p = (const unsigned char*)l;

    while(len > 0)
    {

        if(*p == u)
        {

            return p;

        }

        p++;

        len--;

    }

    return nullptr;

}



inline const void * memory_find_u8(const void* l, int i, memsize len)
{

    if(::is_null(l))
    {

        return nullptr;

    }

    return _memory_find_u8(l, i, len);

}




#pragma once



CLASS_DECL_ACME void * memory_set(void * p, i32 i, memsize iSize);
CLASS_DECL_ACME void * memory_and(void * p, const void * point1, const void * point2, memsize iSize);
CLASS_DECL_ACME void * memory_copy(void * dst, const void * src, memsize iSize);
CLASS_DECL_ACME void * memory_transfer(void * dst, const void * src, memsize iSize);
CLASS_DECL_ACME::wide_character * wide_memory_copy(::wide_character * dst, const ::wide_character * src, memsize iSize);

CLASS_DECL_ACME void * reverse_memory(void * p, memsize iSize);
CLASS_DECL_ACME void * reverse_memory_copy(void * p, const void * point1, memsize iSize);


CLASS_DECL_ACME::std::strong_ordering memory_order(const void * sz1, const void * sz2, memsize iSize);

CLASS_DECL_ACME::std::strong_ordering _memory_order(const void * p1, const void * p2, memsize size);


#ifdef __cplusplus


inline void * zero(void * p, memsize size) { memory_set(p, 0, size); return p; }


inline bool is_zero(const void * p, memsize iSize)
{

   unsigned char * pb = (unsigned char *)p;

   while (*pb == '\0' && iSize > 0)
   {

      pb++;

      iSize--;

   }

   return iSize == 0;

}




//#define zero(array) (::zero(array, sizeof(array)))



#endif









