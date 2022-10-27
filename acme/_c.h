#pragma once



inline bool is_null(const void * p, size_t s)
{

   return ((size_t)p <= s);

}


inline int c_is_null(const void * p) { return ((uptr)p) < 65536; }
inline int c_is_set(const void * p) { return !c_is_null(p); }


CLASS_DECL_ACME strsize safe_strlen(void * p, strsize n);
