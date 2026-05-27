#pragma once

//CLASS_DECL_ACME ::i32 ansi_to_int(const_char_pointer sz, const_char_pointer *pszEnd, ::i32 iBase);
//CLASS_DECL_ACME ::i32 ansi_to_int(const_char_pointer sz, const_char_pointer *pszEnd);
//CLASS_DECL_ACME ::i32 ansi_to_int(const_char_pointer sz, ::i32 iOnNull = 0);

//CLASS_DECL_ACME ::u32 ansi_to_unsigned_int(const_char_pointer sz, const_char_pointer *pszEnd, ::i32 iBase);
//CLASS_DECL_ACME ::u32 ansi_to_unsigned_int(const_char_pointer sz, const_char_pointer *pszEnd);
//CLASS_DECL_ACME ::u32 ansi_to_unsigned_int(const_char_pointer sz);

//CLASS_DECL_ACME ::i32 ansi_count_to_long_long(const_char_pointer sz, const_char_pointer *pszEnd, ::i32 iBase, size_t iLen);
//CLASS_DECL_ACME ::i32 ansi_count_to_long_long(const_char_pointer sz, const_char_pointer *pszEnd, size_t iLen);
//CLASS_DECL_ACME ::i32 ansi_count_to_long_long(const_char_pointer sz, size_t iLen);


//#define atoint_dup(...) ansi_to_int(__VA_ARGS__)
//#define atouint_dup(...) ansi_to_unsigned_int(__VA_ARGS__)
//#define ntouint_dup(...) ntoui_dup(__VA_ARGS__)



//CLASS_DECL_ACME ::i32 wtoi_dup(const wide_character * sz);
//CLASS_DECL_ACME ::i32 nwtoi_dup(const wide_character * sz, ::i32 iCount);



//CLASS_DECL_ACME ::i64 ansi_to_long_long(const_char_pointer sz, char_pointer * pszEnd);
//CLASS_DECL_ACME ::i64 ansi_to_long_long(const_char_pointer sz);


//CLASS_DECL_ACME ::u64 ansi_to_unsigned_long_long(const_char_pointer sz, char_pointer * pszEnd);
//CLASS_DECL_ACME ::u64 ansi_to_unsigned_long_long(const_char_pointer sz);


//CLASS_DECL_ACME ::i64 ansi_count_to_long_long(const_char_pointer sz, char_pointer * pszEnd, size_t iLen);
//CLASS_DECL_ACME ::i64 ansi_count_to_long_long(const_char_pointer sz, size_t iLen);


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


//CLASS_DECL_ACME ::i64 wide_to_long_long(const wide_character * sz, const wide_character * * pszEnd, ::i32 iBase);
//CLASS_DECL_ACME ::i64 wide_to_long_long(const wide_character * sz, const wide_character * * pszEnd);
//CLASS_DECL_ACME ::i64 wide_to_long_long(const wide_character * sz);


#ifdef __cplusplus

inline void ansi_to(::u32 & u, const_char_pointer psz) { u = ansi_to_unsigned_int(scopedstr); }
inline void ansi_to(::u64 & u, const_char_pointer psz) { u = ansi_to_unsigned_long_long(scopedstr); }
//inline void ansi_to(uptr & u, const_char_pointer psz) { u = ansi_to_uptr(scopedstr); }

inline void wide_to(::u32 & u, const ::wide_character * psz) { u = wide_to_unsigned_int(scopedstr); }
inline void wide_to(::u64 & u, const ::wide_character * psz) { u = wide_to_unsigned_long_long(scopedstr); }
//inline void wide_to(uptr & u, const ::wide_character * psz) { u = wide_to_uptr(scopedstr); }

#endif
