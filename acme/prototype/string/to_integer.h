#pragma once

//CLASS_DECL_ACME int ansi_to_int(const_char_pointer  sz, const_char_pointer * pszEnd, int iBase);
//CLASS_DECL_ACME int ansi_to_int(const_char_pointer  sz, const_char_pointer * pszEnd);
//CLASS_DECL_ACME int ansi_to_int(const_char_pointer  sz, int iOnNull = 0);

//CLASS_DECL_ACME unsigned int ansi_to_unsigned_int(const_char_pointer  sz, const_char_pointer * pszEnd, int iBase);
//CLASS_DECL_ACME unsigned int ansi_to_unsigned_int(const_char_pointer  sz, const_char_pointer * pszEnd);
//CLASS_DECL_ACME unsigned int ansi_to_unsigned_int(const_char_pointer  sz);

//CLASS_DECL_ACME int ansi_count_to_long_long(const_char_pointer  sz, const_char_pointer * pszEnd, int iBase, size_t iLen);
//CLASS_DECL_ACME int ansi_count_to_long_long(const_char_pointer  sz, const_char_pointer * pszEnd, size_t iLen);
//CLASS_DECL_ACME int ansi_count_to_long_long(const_char_pointer  sz, size_t iLen);


//#define atoint_dup(...) ansi_to_int(__VA_ARGS__)
//#define atouint_dup(...) ansi_to_unsigned_int(__VA_ARGS__)
//#define ntouint_dup(...) ntoui_dup(__VA_ARGS__)



//CLASS_DECL_ACME int wtoi_dup(const unichar * sz);
//CLASS_DECL_ACME int nwtoi_dup(const unichar * sz, int iCount);



//CLASS_DECL_ACME long long ansi_to_long_long(const_char_pointer  sz, char ** pszEnd);
//CLASS_DECL_ACME long long ansi_to_long_long(const_char_pointer  sz);


//CLASS_DECL_ACME unsigned long long ansi_to_unsigned_long_long(const_char_pointer  sz, char ** pszEnd);
//CLASS_DECL_ACME unsigned long long ansi_to_unsigned_long_long(const_char_pointer  sz);


//CLASS_DECL_ACME long long ansi_count_to_long_long(const_char_pointer  sz, char ** pszEnd, size_t iLen);
//CLASS_DECL_ACME long long ansi_count_to_long_long(const_char_pointer  sz, size_t iLen);


#define ansi_to_iptr __END_OSBIT(ansi_to_i)
#define ansi_to_uptr __END_OSBIT(ansi_to_u)
#define ansi_count_to_iptr(...) __END_OSBIT(ansi_count_to_i)


#define wide_to_iptr __END_OSBIT(wide_to_i)
#define wide_to_uptr __END_OSBIT(wide_to_u)
#define wide_count_to_iptr(...) __END_OSBIT(wide_count_to_i)


//#if defined(LINUX)
//
//#define _strtoi64 ansi_to_long_long
//
//#endif


//CLASS_DECL_ACME long long wide_to_long_long(const unichar * sz, const unichar ** pszEnd, int iBase);
//CLASS_DECL_ACME long long wide_to_long_long(const unichar * sz, const unichar ** pszEnd);
//CLASS_DECL_ACME long long wide_to_long_long(const unichar * sz);


#ifdef __cplusplus

inline void ansi_to(unsigned int & u, const ::ansi_character * psz) { u = ansi_to_unsigned_int(scopedstr); }
inline void ansi_to(unsigned long long & u, const ::ansi_character * psz) { u = ansi_to_unsigned_long_long(scopedstr); }
//inline void ansi_to(uptr & u, const ::ansi_character * psz) { u = ansi_to_uptr(scopedstr); }

inline void wide_to(unsigned int & u, const ::wide_character * psz) { u = wide_to_unsigned_int(scopedstr); }
inline void wide_to(unsigned long long & u, const ::wide_character * psz) { u = wide_to_unsigned_long_long(scopedstr); }
//inline void wide_to(uptr & u, const ::wide_character * psz) { u = wide_to_uptr(scopedstr); }

#endif
