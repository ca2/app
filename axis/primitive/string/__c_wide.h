#pragma once


//using widechar             = unichar;
//using wd16char             = wd16char;
//using wd32char             = wd32char;

// widechar widech;
// widech16 wchr16;
// widech36 wchr32;
// widestring widestr;
// wd16string wd16str;
// wd32string wd32str;





inline widechar               wide_char_lowered(i32 ch);
inline widechar               wide_char_lowered(i32 ch);
inline i32                    wide_char_is_digit(i32 ch);
inline i32                    wide_char_is_hexadecimal(i32 ch);
inline i32                    wide_char_is_alphabetic(i32 ch);
inline i32                    wide_char_is_alphanumeric(i32 ch);
inline i32                    wide_char_is_space(i32 ch);



inline widechar *             wide_last_char(widechar * psz);
inline const widechar *       wide_const_last_char(const widechar * psz);
inline widechar *             wide_concatenate(widechar * dest, const widechar * cat);
inline widechar *             wide_copy(widechar * dest, const widechar * cat);
inline widechar *             wide_count_copy(widechar * dest, const widechar * cat, strsize iLen);
inline strsize                wide_length(const widechar * cat);
inline widechar *             wide_duplicate(const widechar * src); // ATTENTION - memory_alloc
inline widechar *             wide_count_duplicate(const widechar * src, strsize srclen); // ATTENTION - memory_alloc 
inline const widechar *       wide_find_string(const widechar * src, const widechar * find);
inline const widechar *       wide_find_string_case_insensitive(const widechar * src, const widechar * find);
inline const widechar *       wide_count_find_string(const widechar * src, const widechar * find, strsize iLen);
inline const widechar *       wide_count_find_string_case_insensitive(const widechar * src, const widechar * find, strsize iLen);

inline const widechar *       wide_next_separator_token(const widechar * src, widechar chFind);


inline i32                    wide_compare(const widechar * sz1, const widechar * sz2);
inline i32                    wide_compare_case_insensitive(const widechar * sz1, const widechar * sz2);
inline i32                    wide_count_compare(const widechar * sz1, const widechar * sz2, strsize iLen);
inline i32                    wide_count_compare_case_insensitive(const widechar * sz1, const widechar * sz2, strsize iLen);
inline i32                    wide_collate(const widechar * sz1, const widechar * sz2);
inline i32                    wide_collate_case_insensitive(const widechar * sz1, const widechar * sz2);
inline i32                    wide_count_collate(const widechar * sz1, const widechar * sz2, strsize iLen);
inline i32                    wide_count_collate_case_insensitive(const widechar * sz1, const widechar * sz2, strsize iLen);
inline i32                    wide_begins(const widechar * sz1, const widechar * prefix);
inline i32                    wide_begins_case_insensitive(const widechar * sz1, const widechar * prefix);
inline const widechar *       wide_begins_eat(const widechar * sz1, const widechar * prefix);
inline i32                    wide_ends(const widechar * sz1, const widechar * suffix);
inline i32                    wide_ends_case_insensitive(const widechar * sz1, const widechar * suffix);
inline const widechar *       wide_find_char(const widechar * sz, widechar ch);
inline const widechar *       wide_find_char_reverse(const widechar * sz, widechar ch);
inline const widechar *       wide_concatenate_and_duplicate(const widechar * psz1, const widechar * psz2, int iFree1, int iFree2);


inline void                   wide_from_u64(widechar * psz, u64 u, i32 iBase = 10);
inline void                   wide_from_i64(widechar * psz, i64 i, i32 iBase = 10);

inline void                   wide_from_u32(widechar * psz, u32 u, i32 iBase = 10);
inline void                   wide_from_i32(widechar * psz, i32 i, i32 iBase = 10);

inline i64                    wide_to_i64(const widechar * psz, const widechar ** ppszEnd = nullptr, i32 iBase = 10);
inline u64                    wide_to_u64(const widechar * psz, const widechar ** ppszEnd = nullptr, i32 iBase = 10);
inline i64                    wide_count_to_i64(const widechar * psz, const widechar ** ppszEnd, i32 iBase, strsize srclen);

inline i32                    wide_to_i32(const widechar * psz, const widechar ** ppszEnd = nullptr, i32 iBase = 10);
inline u32                    wide_to_u32(const widechar * psz, const widechar ** ppszEnd = nullptr, i32 iBase = 10);
inline i32                    wide_count_to_i32(const widechar * psz, const widechar ** ppszEnd, i32 iBase, strsize srclen);


inline void                   wide_reverse(widechar * sz);
inline void                   wide_zero_pad(widechar * sz, strsize iPad);
inline const widechar *       wide_scan(const widechar * psz, const widechar * find);
inline widechar *             wide_first_token(widechar * psz, const widechar * delimiters, widechar ** action_context);
inline widechar *             wide_next_token(const widechar * delimiters, widechar ** action_context);




inline widechar *             wide_lower(widechar * pch);
inline widechar *             wide_upper(widechar * pch);

CLASS_DECL_AURA void          wide_parse_command_line(widechar * cmdstart, widechar ** argv, widechar * args, i32 * numargs, i32 * numchars);


inline i64 wide_to_i64(const widechar * psz, const widechar ** ppszEnd, i32 iBase);
inline u64 wide_to_u64(const widechar * psz, const widechar ** ppszEnd, i32 iBase);
inline i32 wide_to_i32(const widechar * psz, const widechar ** ppszEnd, i32 iBase);
inline u32 wide_to_u32(const widechar * psz, const widechar ** ppszEnd, i32 iBase);






