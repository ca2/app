// Created by camilo on 2022-11-01 23:14 <3ThomasBorregaardSorensen!!
#pragma once


//CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails = nullptr);
//
//
//CLASS_DECL_ACME void set_last_status(const ::e_status& estatus);

//CLASS_DECL_ACME char * strdup2(const_char_pointer psz1, const_char_pointer psz2);


CLASS_DECL_ACME long long ansi_to_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);

CLASS_DECL_ACME long long ansi_to_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);


CLASS_DECL_ACME unsigned long long ansi_to_unsigned_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);


CLASS_DECL_ACME int ansi_to_int(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);


CLASS_DECL_ACME unsigned int ansi_to_unsigned_int(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);


CLASS_DECL_ACME void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);


CLASS_DECL_ACME void throw_encoding_exception(const ::scoped_string & scopedstrMessage);


//CLASS_DECL_ACME::platform::system* system();


//inline bool __enum_is_failed(const ::e_status& e);


CLASS_DECL_ACME void set_platform_level(enum_platform_level eplatformlevel);


CLASS_DECL_ACME enum_platform_level get_platform_level();


CLASS_DECL_ACME int ansi_open(const ::scoped_string & scopedstr, int i);

//CLASS_DECL_ACME FILE* ansi_fopen(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrMode);

CLASS_DECL_ACME int ansi_file_flag(int iFlag);

CLASS_DECL_ACME void ansi_get_errno(int* perrno);

CLASS_DECL_ACME void ansi_unlink(const ::scoped_string & scopedstr);


//CLASS_DECL_ACME::e_status get_last_status();


#if !defined(__APPLE__) \
&& !defined(LINUX) \
&& !defined(__ANDROID__) \
&& !defined(__BSD__)

int ftruncate(int file, filesize len);

#endif


CLASS_DECL_ACME int get_os_thread_priority(::enum_priority epriority);

CLASS_DECL_ACME int get_os_priority_class(::enum_priority epriority);

CLASS_DECL_ACME::enum_priority get_os_thread_scheduling_priority(int iCa2Priority);

CLASS_DECL_ACME::enum_priority get_os_class_scheduling_priority(int iCa2Priority);


CLASS_DECL_ACME const ::particle * general_trace_object();

CLASS_DECL_ACME int_bool c_enable_trace_category(enum_trace_category ecategory, int_bool iEnable);

inline const ::particle * context_trace_object();


//CLASS_DECL_ACME extern unsigned int g_tickStartTime;




CLASS_DECL_ACME const_char_pointer trace_category_name(enum_trace_category ecategory);

CLASS_DECL_ACME const ::particle * trace_object(enum_trace_category ecategory);

CLASS_DECL_ACME const_char_pointer topic_text(::particle* pparticle);

CLASS_DECL_ACME enum_trace_category object_trace_category(::particle* pparticle);



//
//template<typename LEFT, typename RIGHT>
//inline void assign(LEFT& l, const RIGHT& r) { l = r; }
//

inline void assign(::block& block, const ::payload& r);

inline void assign(long& l, const ::payload& r);
inline void assign(unsigned long& l, const ::payload& r);


inline void assign(bool& b, const ::payload& r);
inline void assign(char& ch, const ::payload& r);
inline void assign(unsigned char & uch, const ::payload& r);
inline void assign(short & sh, const ::payload& r);
inline void assign(unsigned short & ush, const ::payload& r);
inline void assign(int& i, const ::payload& r);
inline void assign(unsigned int& ui, const ::payload& r);
inline void assign(long long & hi, const ::payload& r);
inline void assign(unsigned long long & hn, const ::payload& r);


//CLASS_DECL_ACME void add_release_on_end(::matter* pmatter);
//
//
//CLASS_DECL_ACME void add_release_on_end(::matter* pmatter);



CLASS_DECL_ACME void __node_acme_pre_init();

CLASS_DECL_ACME void __node_acme_pos_init();

CLASS_DECL_ACME void __node_acme_pre_term();

CLASS_DECL_ACME void __node_acme_pos_term();



typedef void THREAD_ROUTINE(thread_parameter parameter);


class e_status;


//CLASS_DECL_ACME bool succeeded(const ::payload & payload);
//constexpr bool succeeded(const ::e_status & e_status);


//inline bool failed(const ::payload & payload);
//constexpr bool failed(const ::e_status & e_status);




//
//CLASS_DECL_ACME::atom auto pmessagebox = __initialize_new ::message_box(::particle* ppartcicle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const e_message_box& emessagebox = e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

//pmessagebox->sync();
//
//CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom& atom) > function, ::particle* pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const e_message_box& emessagebox = e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);
//




CLASS_DECL_ACME bool is_filemanager(const ::atom& atom);


CLASS_DECL_ACME bool is_filemanager_group(const ::atom& atom, const ::scoped_string & scopedstrGroup);

CLASS_DECL_ACME bool is_filemanager_group(const ::atom& atom, int iGroup);


CLASS_DECL_ACME bool is_color_sel(const ::atom& atom);


CLASS_DECL_ACME bool is_font_sel(const ::atom& atom);




//template<class TYPE>
//inline void dump_elements(dump_context& dumpcontext, const TYPE* pElements, ::collection::count nCount);


int CLASS_DECL_ACME MultiByteToWideChar2(unsigned int CodePage, unsigned int dwFlags, const ::ansi_character* pMultByteStr, int cbMultiByte,
   ::wide_character* pWideCharStr, int cchWideChar);

int CLASS_DECL_ACME WideCharToMultiByte2(unsigned int CodePage, unsigned int dwFlags, const ::wide_character* pWideCharStr, int cchWideChar,
   ::ansi_character* pMultByteStr, int cbMultiByte, const_char_pointer pDefaultChar,
   int_bool* pUsedDefaultChar);









namespace acme
{



   mutex* get_global_mutex();




} // namespace acme



inline unsigned long long make64_from32(unsigned int l, unsigned int h);


inline bool is_memory_segment_ok(void * p, memsize s);


inline bool is_memory_segment_read_ok(const void* p, memsize s);


inline bool is_string_ok(::wide_character * p, ::character_count s);


inline bool is_string_ok(::ansi_character * p, ::character_count s);


inline int_bool address_overlaps(const void* pszDst, const void* pszSrc, character_count srclen);


CLASS_DECL_ACME unsigned int __unsigned_int_hash(const ::scoped_string & scopedstr);


template < typename TYPE > inline TYPE*& __defer_new(TYPE*& p);


inline const ::particle * context_trace_object();


inline const ::particle * trace_object(const ::particle* pparticle);



inline int read_char(unsigned char*& pdata, memsize& s, char* pch);



template < typename TYPE >
inline bool is_reference_null(const TYPE& t);



template < typename TYPE >
inline bool is_reference_set(const TYPE& t);



inline bool is_impact_group(unsigned long long u, unsigned long long uGroup);


inline bool is_impact_subgroup(unsigned long long u, unsigned long long uGroup);


inline bool is_file_or_folder2(const ::file::enum_type& etype);
inline bool is_existing_file_or_folder(const ::file::enum_type& etype);
inline bool exists(const ::file::enum_type& etype);


// CLASS_DECL_ACME void set_verbose_log(bool bVerbose);


// CLASS_DECL_ACME bool is_verbose_log();


CLASS_DECL_ACME long long ansi_to_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);
CLASS_DECL_ACME unsigned long long ansi_to_unsigned_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);
CLASS_DECL_ACME int ansi_to_int(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int ansi_to_unsigned_int(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase);


CLASS_DECL_ACME ::ansi_character * __u64toansi(unsigned long long u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase, ::ansi_character * & end);

CLASS_DECL_ACME ::ansi_character * __long_longtoansi(long long u, ::ansi_character * buf, int iBase, enum_digit_case edigitcase, ::ansi_character * & end);


template<typename T1, typename T2>
inline void sort_non_negative(T1& t1, T2& t2);



CLASS_DECL_ACME void application_send_status(::enum_status estatus, ::particle * pparticle = nullptr, long long hi = 0, void * p = nullptr);


CLASS_DECL_ACME void node_application_send_status(const_char_pointer pszStatus, void * p = nullptr, long long hi = 0);

namespace platform
{

   class system;

} // namespace platform


inline ::platform::system * system();




