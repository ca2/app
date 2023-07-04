// From acme/_c.h by camilo on 2022-11-09 02:40 <3ThomasBorregaardSorensen!!
#pragma once


inline bool is_null(const void* p, std::size_t s)
{

   return ((std::size_t)p <= s);

}


inline int is_null(const void* p) { return ((uptr)p) < 65536; }
inline int is_set(const void* p) { return !is_null(p); }


CLASS_DECL_ACME strsize safe_strlen(void* p, strsize n);


inline int_bool address_overlaps(const void* pszDst, const void* pszSrc, strsize srclen);






CLASS_DECL_ACME void* reverse_memchr(const void* l, int ch, std::size_t l_len);
CLASS_DECL_ACME void* reverse_memmem(const void* l, std::size_t l_len, const void* s, std::size_t s_len);
CLASS_DECL_ACME void* reverse_byte_not_in_block(const void* l, std::size_t l_len, const void* s, std::size_t s_len);
