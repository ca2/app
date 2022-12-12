#pragma once


inline ::ansi_character               ansi_char_tolower(i32 i);
inline ::ansi_character               ansi_char_toupper(i32 i);

inline i32                    ansi_char_isdigit(i32 i);
inline i32                    ansi_char_isalpha(i32 i);
inline i32                    ansi_char_isalnum(i32 i);
inline i32                    ansi_char_isspace(i32 i);


inline i32                    ansi_char_is_hexadecimal(i32 i);


inline ::ansi_character * ansi_last_char(::ansi_character * psz);
inline const ::ansi_character * ansi_const_last_char(const ::ansi_character * psz);
inline ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat);
inline ::ansi_character * ansi_copy(::ansi_character * psz, const ::ansi_character * cpy);
inline ::ansi_character * ansi_count_copy(::ansi_character * psz, const ::ansi_character * cpy, strsize len);
inline strsize                ansi_length(const ::ansi_character * psz);
inline ::ansi_character * ansi_duplicate(const ::ansi_character * psz); // ATTENTION - memory_allocate
inline ::ansi_character * ansi_count_duplicate(const ::ansi_character * psz, strsize len); // ATTENTION - memory_allocate 
inline const ::ansi_character * ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find);
inline const ::ansi_character * ansi_find_string_ci(const ::ansi_character * psz, const ::ansi_character * find);
inline const ::ansi_character * ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len);
inline const ::ansi_character * ansi_count_find_string_ci(const ::ansi_character * psz, const ::ansi_character * find, strsize len);

//inline ::ansi_character *             ansi_next_token(::ansi_character * psz, ::ansi_character ch);


inline i32                    ansi_compare(const ::ansi_character * sz1, const ::ansi_character * sz2);
inline i32                    ansi_compare_ci(const ::ansi_character * sz1, const ::ansi_character * sz2);
inline i32                    ansi_count_compare(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
inline i32                    ansi_count_compare_ci(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
inline i32                    ansi_collate(const ::ansi_character * sz1, const ::ansi_character * sz2);
inline i32                    ansi_collate_ci(const ::ansi_character * sz1, const ::ansi_character * sz2);
inline i32                    ansi_count_collate(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
inline i32                    ansi_count_collate_ci(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
inline i32                    ansi_begins(const ::ansi_character * sz1, const ::ansi_character * prefix);
inline i32                    ansi_begins_ci(const ::ansi_character * sz1, const ::ansi_character * prefix);
inline const ::ansi_character * ansi_begins_eat(const ::ansi_character * sz1, const ::ansi_character * prefix);
inline const ::ansi_character * ansi_begins_eat_ci(const ::ansi_character * sz1, const ::ansi_character * prefix);
inline i32                    ansi_ends(const ::ansi_character * sz1, const ::ansi_character * suffix);
inline i32                    ansi_ends_ci(const ::ansi_character * sz1, const ::ansi_character * suffix);
inline const ::ansi_character * ansi_find_char(const ::ansi_character * sz, ::ansi_character ch);
inline const ::ansi_character * ansi_find_char_reverse(const ::ansi_character * sz, ::ansi_character ch);
inline const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2, int_bool iFree1 = false, int_bool iFree2 = false);

//inline void ansi_from_i64(char* sz, i64 i, i32 iBase, enum_digit_case edigitcase = e_digit_case_lower);
//inline void ansi_from_u64(char* sz, u64 u, i32 iBase, enum_digit_case edigitcase = e_digit_case_lower);

inline void                   ansi_from_u64(::ansi_character * psz, u64 u, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
inline void                   ansi_from_i64(::ansi_character * psz, i64 i, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

inline void                   ansi_from_u32(::ansi_character * psz, u32 u, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
inline void                   ansi_from_i32(::ansi_character * psz, i32 i, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

inline i64                    ansi_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, i32 iBase = 10);
inline u64                    ansi_to_u64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, i32 iBase = 10);
inline i64                    ansi_count_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase, strsize srclen);

inline i32                    ansi_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, i32 iBase = 10);
inline u32                    ansi_to_u32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, i32 iBase = 10);
inline i32                    ansi_count_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase, strsize srclen);


inline void                   ansi_reverse(::ansi_character * sz);
inline void                   ansi_reverse(::ansi_character * sz, strsize size);
inline void                   ansi_zero_pad(::ansi_character * sz, strsize lenPad);
inline const ::ansi_character *       _ansi_scan(const ::ansi_character * psz, const ::ansi_character * pszCharacters);
inline const ::ansi_character *       ansi_scan(const ::ansi_character * psz, const ::ansi_character * pszCharacters);
//inline const ::ansi_character *       ansi_token(const ::ansi_character * psz, const ::ansi_character * pszSeparators);
inline ::ansi_character *             ansi_first_token(::ansi_character * psz, const ::ansi_character * delimiters, ::ansi_character ** action_context);
inline ::ansi_character *             ansi_next_token(const ::ansi_character * delimiters, ::ansi_character ** action_context);


inline ::ansi_character * ansi_lower(::ansi_character * pch);
inline ::ansi_character * ansi_upper(::ansi_character * pch);


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const ::ansi_character * pszCriteria, const char * pszValue);
CLASS_DECL_ACME int_bool matches_wildcard_criteria_ci(const ::ansi_character * pszCriteria, const char * pszValue);


CLASS_DECL_ACME void ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, i32 * numargs, i32 * numchars);




inline const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen);


CLASS_DECL_ACME const ::ansi_character * wildcard_next_stop(const ::ansi_character * pszCriteria);


CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
CLASS_DECL_ACME int_bool               wildcard_matches_criteria_ci(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);


//inline const ::ansi_character * eol();


//#ifdef __cplusplus
//
//
//#define EOL (::eol())
//
//#else
//
//#define EOL (eol())
//
//#endif



