// From acme/_c.h by camilo on 2022-11-09 02:40 <3ThomasBorregaardSorensen!!
#pragma once


inline bool is_set(const void* p, memsize s)
{

   return ((::iptr)p >= s);

}


inline int is_set(const void* p) { return ::is_set(p, 65536); }


inline bool is_null(const void* p) { return !::is_set(p); }


CLASS_DECL_ACME character_count safe_strlen(void* p, character_count n);


inline int_bool address_overlaps(const void* pszDst, const void* pszSrc, character_count srclen);






CLASS_DECL_ACME void* reverse_memchr(const void* l, int ch, std::size_t l_len);
CLASS_DECL_ACME void* reverse_memmem(const void* l, std::size_t l_len, const void* s, std::size_t s_len);
CLASS_DECL_ACME void* reverse_byte_not_in_block(const void* l, std::size_t l_len, const void* s, std::size_t s_len);

//#ifdef	_STDIO_H_
//#define _STDIO_H_
//#error "already included?!?! WHAT?!?! (Before including acme/exception/_c.h)"
//#endif

#include "acme/exception/_c.h"
//#ifdef	_STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/exception/_c.h)"
//#endif

#include "acme/prototype/comparison/_c.h"
//#ifdef	_STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/comparison/_c.h)"
//#endif



