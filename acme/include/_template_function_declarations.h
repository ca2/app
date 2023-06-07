// Created by camilo on 2022-11-01 23:14 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/exception/debug.h"
#include "acme/primitive/primitive/e_status.h"

template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox);
CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails);




CLASS_DECL_ACME void set_last_status(const ::e_status& estatus);


CLASS_DECL_ACME void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);


CLASS_DECL_ACME void throw_encoding_exception(const ::scoped_string & scopedstrMessage);


//CLASS_DECL_ACME::acme::system* acmesystem();


inline bool __enum_is_failed(const ::e_status& e);


CLASS_DECL_ACME void set_platform_level(enum_platform_level eplatformlevel);


CLASS_DECL_ACME enum_platform_level get_platform_level();


CLASS_DECL_ACME i32 ansi_open(const ::scoped_string & scopedstr, i32 i);

CLASS_DECL_ACME FILE* ansi_fopen(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrMode);

CLASS_DECL_ACME int ansi_file_flag(int iFlag);

CLASS_DECL_ACME void ansi_get_errno(i32* perrno);

CLASS_DECL_ACME void ansi_unlink(const ::scoped_string & scopedstr);


CLASS_DECL_ACME::e_status get_last_status();


#if !defined(__APPLE__) && !defined(LINUX) && !defined(ANDROID)

int ftruncate(int file, filesize len);

#endif


CLASS_DECL_ACME i32 get_os_thread_priority(::enum_priority epriority);

CLASS_DECL_ACME i32 get_os_priority_class(::enum_priority epriority);

CLASS_DECL_ACME::enum_priority get_os_thread_scheduling_priority(i32 iCa2Priority);

CLASS_DECL_ACME::enum_priority get_os_class_scheduling_priority(i32 iCa2Priority);


CLASS_DECL_ACME const ::particle * general_trace_object();

CLASS_DECL_ACME int_bool c_enable_trace_category(enum_trace_category ecategory, int_bool iEnable);

inline const ::particle * context_trace_object();


//CLASS_DECL_ACME extern u32 g_tickStartTime;




CLASS_DECL_ACME const char* trace_category_name(enum_trace_category ecategory);

CLASS_DECL_ACME const ::particle * trace_object(enum_trace_category ecategory);

CLASS_DECL_ACME const char* topic_text(::particle* pparticle);

CLASS_DECL_ACME enum_trace_category object_trace_category(::particle* pparticle);




template<typename LEFT, typename RIGHT>
inline void assign(LEFT& l, const RIGHT& r) { l = r; }


inline void assign(::block& block, const ::payload& r);

inline void assign(long& l, const ::payload& r);
inline void assign(unsigned long& l, const ::payload& r);


inline void assign(bool& l, const ::payload& r);
inline void assign(::i8& i8, const ::payload& r);
inline void assign(::u8& u8, const ::payload& r);
inline void assign(::i16& i16, const ::payload& r);
inline void assign(::u16& u16, const ::payload& r);
inline void assign(::i32& i32, const ::payload& r);
inline void assign(::u32& u32, const ::payload& r);
inline void assign(::i64& i64, const ::payload& r);
inline void assign(::u64& u64, const ::payload& r);


//CLASS_DECL_ACME void add_release_on_end(::matter* pmatter);
//
//
//CLASS_DECL_ACME void add_release_on_end(::matter* pmatter);



CLASS_DECL_ACME void __node_acme_pre_init();

CLASS_DECL_ACME void __node_acme_pos_init();

CLASS_DECL_ACME void __node_acme_pre_term();

CLASS_DECL_ACME void __node_acme_pos_term();



typedef void THREAD_ROUTINE(thread_parameter parameter);


CLASS_DECL_ACME bool succeeded(const ::payload& payload);






CLASS_DECL_ACME bool is_filemanager(const ::atom& atom);


CLASS_DECL_ACME bool is_filemanager_group(const ::atom& atom, const ::scoped_string & scopedstrGroup);

CLASS_DECL_ACME bool is_filemanager_group(const ::atom& atom, int iGroup);


CLASS_DECL_ACME bool is_color_sel(const ::atom& atom);


CLASS_DECL_ACME bool is_font_sel(const ::atom& atom);




//template<class TYPE>
//inline void dump_elements(dump_context& dumpcontext, const TYPE* pElements, ::count nCount);


i32 CLASS_DECL_ACME MultiByteToWideChar2(::u32 CodePage, ::u32 dwFlags, const ::ansi_character* pMultByteStr, i32 cbMultiByte,
   ::wide_character* pWideCharStr, i32 cchWideChar);

i32 CLASS_DECL_ACME WideCharToMultiByte2(::u32 CodePage, ::u32 dwFlags, const ::wide_character* pWideCharStr, i32 cchWideChar,
   ::ansi_character* pMultByteStr, i32 cbMultiByte, const char* pDefaultChar,
   int_bool* pUsedDefaultChar);









namespace acme
{



   mutex* get_global_mutex();




} // namespace acme



inline ::u64 make64_from32(::u32 l, ::u32 h);

//inline bool is_memory_segment_ok(const void* p, memsize size, bool bReadWrite = true);
//
//
//inline bool is_string_ok(const ::wide_character* pwsz, memsize nMaxLength = INT_MAX);
//
//
//inline bool is_string_ok(const ::scoped_string & scopedstr, memsize nMaxLength = UINT_MAX);


inline int_bool address_overlaps(const void* pszDst, const void* pszSrc, strsize srclen);


CLASS_DECL_ACME::u32 __u32_hash(const ::scoped_string & scopedstr);


template < typename TYPE > inline TYPE*& __defer_new(TYPE*& p);


inline const ::particle * context_trace_object();


inline const ::particle * trace_object(const ::particle* pparticle);


inline bool failed(const ::payload& payload);



inline int read_char(u8*& pdata, memsize& s, char* pch);



template < typename TYPE >
inline bool is_reference_null(const TYPE& t);



template < typename TYPE >
inline bool is_reference_set(const TYPE& t);



inline bool is_impact_group(::u64 u, ::u64 uGroup);


inline bool is_impact_subgroup(::u64 u, ::u64 uGroup);


inline bool is_file_or_folder(const ::file::enum_type& etype);
inline bool exists(const ::file::enum_type& etype);


//CLASS_DECL_ACME void set_verbose_log(bool bVerbose);


//CLASS_DECL_ACME bool is_verbose_log();


inline i64 ansi_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase);
inline u64 ansi_to_u64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase);
inline i32 ansi_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase);
inline u32 ansi_to_u32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase);


CLASS_DECL_ACME ::ansi_character * __u64toansi(::u64 u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase, ::ansi_character * & len);

CLASS_DECL_ACME ::ansi_character * __i64toansi(::i64 u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase, ::ansi_character * & len);


template<typename T1, typename T2>
inline void sort_non_negative(T1& t1, T2& t2);



