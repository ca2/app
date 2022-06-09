#pragma once





inline ansichar               ansi_char_lowered(i32 i);
inline ansichar               ansi_char_uppered(i32 i);
inline i32                    ansi_char_is_digit(i32 i);
inline i32                    ansi_char_is_hexadecimal(i32 i);
inline i32                    ansi_char_is_alphabetic(i32 i);
inline i32                    ansi_char_is_alphanumeric(i32 i);
inline i32                    ansi_char_is_space(i32 i);


inline ansichar *             ansi_last_char(ansichar * psz);
inline const ansichar *       ansi_const_last_char(const ansichar * psz);
inline ansichar *             ansi_concatenate(ansichar * psz, const ansichar * cat);
inline ansichar *             ansi_copy(ansichar * psz, const ansichar * cpy);
inline ansichar *             ansi_count_copy(ansichar * psz, const ansichar * cpy, strsize len);
inline strsize                ansi_length(const ansichar * psz);
inline ansichar *             ansi_duplicate(const ansichar * psz); // ATTENTION - memory_allocate
inline ansichar *             ansi_count_duplicate(const ansichar * psz, strsize len); // ATTENTION - memory_allocate 
inline const ansichar *       ansi_find_string(const ansichar * psz, const ansichar * find);
inline const ansichar *       ansi_find_string_ci(const ansichar * psz, const ansichar * find);
inline const ansichar *       ansi_count_find_string(const ansichar * psz, const ansichar * find, strsize len);
inline const ansichar *       ansi_count_find_string_ci(const ansichar * psz, const ansichar * find, strsize len);

//inline ansichar *             ansi_next_token(ansichar * psz, ansichar ch);


inline i32                    ansi_compare(const ansichar * sz1, const ansichar * sz2);
inline i32                    ansi_compare_ci(const ansichar * sz1, const ansichar * sz2);
inline i32                    ansi_count_compare(const ansichar * sz1, const ansichar * sz2, strsize iLen);
inline i32                    ansi_count_compare_ci(const ansichar * sz1, const ansichar * sz2, strsize iLen);
inline i32                    ansi_collate(const ansichar * sz1, const ansichar * sz2);
inline i32                    ansi_collate_ci(const ansichar * sz1, const ansichar * sz2);
inline i32                    ansi_count_collate(const ansichar * sz1, const ansichar * sz2, strsize iLen);
inline i32                    ansi_count_collate_ci(const ansichar * sz1, const ansichar * sz2, strsize iLen);
inline i32                    ansi_begins(const ansichar * sz1, const ansichar * prefix);
inline i32                    ansi_begins_ci(const ansichar * sz1, const ansichar * prefix);
inline const ansichar *       ansi_begins_eat(const ansichar * sz1, const ansichar * prefix);
inline const ansichar *       ansi_begins_eat_ci(const ansichar * sz1, const ansichar * prefix);
inline i32                    ansi_ends(const ansichar * sz1, const ansichar * suffix);
inline i32                    ansi_ends_ci(const ansichar * sz1, const ansichar * suffix);
inline const ansichar *       ansi_find_char(const ansichar * sz, ansichar ch);
inline const ansichar *       ansi_find_char_reverse(const ansichar * sz, ansichar ch);
inline const ansichar *       ansi_concatenate_and_duplicate(const ansichar * psz1, const ansichar * psz2, int_bool iFree1 = false, int_bool iFree2 = false);


inline void                   ansi_from_u64(ansichar * psz, u64 u, i32 iBase = 10);
inline void                   ansi_from_i64(ansichar * psz, i64 i, i32 iBase = 10);

inline void                   ansi_from_u32(ansichar * psz, u32 u, i32 iBase = 10);
inline void                   ansi_from_i32(ansichar * psz, i32 i, i32 iBase = 10);

inline i64                    ansi_to_i64(const ansichar * psz, const ansichar ** ppszEnd = nullptr, i32 iBase = 10);
inline u64                    ansi_to_u64(const ansichar * psz, const ansichar ** ppszEnd = nullptr, i32 iBase = 10);
inline i64                    ansi_count_to_i64(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase, strsize srclen);

inline i32                    ansi_to_i32(const ansichar * psz, const ansichar ** ppszEnd = nullptr, i32 iBase = 10);
inline u32                    ansi_to_u32(const ansichar * psz, const ansichar ** ppszEnd = nullptr, i32 iBase = 10);
inline i32                    ansi_count_to_i32(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase, strsize srclen);


inline void                   ansi_reverse(ansichar * sz);
inline void                   ansi_zero_pad(ansichar * sz, strsize lenPad);
inline const ansichar *       ansi_scan(const ansichar * psz, const ansichar * find);
inline ansichar *             ansi_first_token(ansichar * psz, const ansichar * delimiters, ansichar ** action_context);
inline ansichar *             ansi_next_token(const ansichar * delimiters, ansichar ** action_context);


inline ansichar *             ansi_lower(ansichar * pch);
inline ansichar *             ansi_upper(ansichar * pch);


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const ansichar * pszCriteria, const char * pszValue);
CLASS_DECL_ACME int_bool matches_wildcard_criteria_ci(const ansichar * pszCriteria, const char * pszValue);


CLASS_DECL_ACME void ansi_parse_command_line(ansichar * cmdstart, ansichar ** argv, ansichar * args, i32 * numargs, i32 * numchars);


inline i64 ansi_to_i64(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase);
inline u64 ansi_to_u64(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase);
inline i32 ansi_to_i32(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase);
inline u32 ansi_to_u32(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase);


inline const void *           memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen);


CLASS_DECL_ACME const ansichar *       wildcard_next_stop(const ansichar * pszCriteria);


CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const ansichar * pszCriteria, const ansichar * pszValue);
CLASS_DECL_ACME int_bool               wildcard_matches_criteria_ci(const ansichar * pszCriteria, const ansichar * pszValue);


inline const ansichar * eol();


#ifdef __cplusplus


#define EOL (::eol())

#else

#define EOL (eol())

#endif





















