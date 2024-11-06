#pragma once

//CLASS_DECL_ACME int ansi_to_i32(const char * sz, const char ** pszEnd, int iBase);
//CLASS_DECL_ACME int ansi_to_i32(const char * sz, const char ** pszEnd);
//CLASS_DECL_ACME int ansi_to_i32(const char * sz, int iOnNull = 0);

//CLASS_DECL_ACME unsigned int ansi_to_u32(const char * sz, const char ** pszEnd, int iBase);
//CLASS_DECL_ACME unsigned int ansi_to_u32(const char * sz, const char ** pszEnd);
//CLASS_DECL_ACME unsigned int ansi_to_u32(const char * sz);

//CLASS_DECL_ACME int ansi_count_to_i64(const char * sz, const char ** pszEnd, int iBase, size_t iLen);
//CLASS_DECL_ACME int ansi_count_to_i64(const char * sz, const char ** pszEnd, size_t iLen);
//CLASS_DECL_ACME int ansi_count_to_i64(const char * sz, size_t iLen);


//#define atoint_dup(...) ansi_to_i32(__VA_ARGS__)
//#define atouint_dup(...) ansi_to_u32(__VA_ARGS__)
//#define ntouint_dup(...) ntoui_dup(__VA_ARGS__)



//CLASS_DECL_ACME int wtoi_dup(const unichar * sz);
//CLASS_DECL_ACME int nwtoi_dup(const unichar * sz, int iCount);



//CLASS_DECL_ACME i64 ansi_to_i64(const char * sz, char ** pszEnd);
//CLASS_DECL_ACME i64 ansi_to_i64(const char * sz);


//CLASS_DECL_ACME u64 ansi_to_u64(const char * sz, char ** pszEnd);
//CLASS_DECL_ACME u64 ansi_to_u64(const char * sz);


//CLASS_DECL_ACME i64 ansi_count_to_i64(const char * sz, char ** pszEnd, size_t iLen);
//CLASS_DECL_ACME i64 ansi_count_to_i64(const char * sz, size_t iLen);


#define ansi_to_iptr __END_OSBIT(ansi_to_i)
#define ansi_to_uptr __END_OSBIT(ansi_to_u)
#define ansi_count_to_iptr(...) __END_OSBIT(ansi_count_to_i)


#define wide_to_iptr __END_OSBIT(wide_to_i)
#define wide_to_uptr __END_OSBIT(wide_to_u)
#define wide_count_to_iptr(...) __END_OSBIT(wide_count_to_i)


//#if defined(LINUX)
//
//#define _strtoi64 ansi_to_i64
//
//#endif


//CLASS_DECL_ACME i64 wide_to_i64(const unichar * sz, const unichar ** pszEnd, int iBase);
//CLASS_DECL_ACME i64 wide_to_i64(const unichar * sz, const unichar ** pszEnd);
//CLASS_DECL_ACME i64 wide_to_i64(const unichar * sz);


#ifdef __cplusplus

inline void ansi_to(unsigned int & u, const ::ansi_character * psz) { u = ansi_to_u32(psz); }
inline void ansi_to(u64 & u, const ::ansi_character * psz) { u = ansi_to_u64(psz); }
//inline void ansi_to(uptr & u, const ::ansi_character * psz) { u = ansi_to_uptr(psz); }

inline void wide_to(unsigned int & u, const ::wide_character * psz) { u = wide_to_u32(psz); }
inline void wide_to(u64 & u, const ::wide_character * psz) { u = wide_to_u64(psz); }
//inline void wide_to(uptr & u, const ::wide_character * psz) { u = wide_to_uptr(psz); }

#endif
