#pragma once





inline wd32char               wd32_char_lowered(i32 ch);
inline wd32char               wd32_char_uppered(i32 ch);
inline i32                    wd32_char_is_digit(i32 ch);
inline i32                    wd32_char_is_hexadecimal(i32 ch);
inline i32                    wd32_char_is_alphabetic(i32 ch);
inline i32                    wd32_char_is_alphanumeric(i32 ch);
inline i32                    wd32_char_is_space(i32 ch);



inline wd32char *             wd32_last_char(wd32char * psz);
inline const wd32char *       wd32_const_last_char(const wd32char * psz);
inline wd32char *             wd32_concatenate(wd32char * dest, const wd32char * cat);
inline wd32char *             wd32_copy(wd32char * dest, const wd32char * cat);
inline wd32char *             wd32_count_copy(wd32char * dest, const wd32char * cat, strsize iLen);
inline strsize                wd32_length(const wd32char * cat);
inline wd32char *             wd32_duplicate(const wd32char * src); // ATTENTION - memory_alloc
inline wd32char *             wd32_count_duplicate(const wd32char * src, strsize srclen); // ATTENTION - memory_alloc 
inline const wd32char *       wd32_find_string(const wd32char * src, const wd32char * find);
inline const wd32char *       wd32_find_string_case_insensitive(const wd32char * src, const wd32char * find);
inline const wd32char *       wd32_count_find_string(const wd32char * src, const wd32char * find, strsize iLen);
inline const wd32char *       wd32_count_find_string_case_insensitive(const wd32char * src, const wd32char * find, strsize iLen);

inline const wd32char *       wd32_next_separator_token(const wd32char * src, wd32char chFind);


inline i32                    wd32_compare(const wd32char * sz1, const wd32char * sz2);
inline i32                    wd32_compare_case_insensitive(const wd32char * sz1, const wd32char * sz2);
inline i32                    wd32_count_compare(const wd32char * sz1, const wd32char * sz2, strsize iLen);
inline i32                    wd32_count_compare_case_insensitive(const wd32char * sz1, const wd32char * sz2, strsize iLen);
inline i32                    wd32_collate(const wd32char * sz1, const wd32char * sz2);
inline i32                    wd32_collate_case_insensitive(const wd32char * sz1, const wd32char * sz2);
inline i32                    wd32_count_collate(const wd32char * sz1, const wd32char * sz2, strsize iLen);
inline i32                    wd32_count_collate_case_insensitive(const wd32char * sz1, const wd32char * sz2, strsize iLen);
inline i32                    wd32_begins(const wd32char * sz1, const wd32char * prefix);
inline i32                    wd32_begins_case_insensitive(const wd32char * sz1, const wd32char * prefix);
inline const wd32char *       wd32_begins_eat(const wd32char * sz1, const wd32char * prefix);
inline i32                    wd32_ends(const wd32char * sz1, const wd32char * suffix);
inline i32                    wd32_ends_case_insensitive(const wd32char * sz1, const wd32char * suffix);
inline const wd32char *       wd32_find_char(const wd32char * sz, wd32char ch);
inline const wd32char *       wd32_find_char_reverse(const wd32char * sz, wd32char ch);
inline const wd32char *       wd32_concatenate_and_duplicate(const wd32char * psz1, const wd32char * psz2, int iFree1, int iFree2);


inline void                   wd32_from_u64(wd32char * psz, u64 u, i32 iBase = 10);
inline void                   wd32_from_i64(wd32char * psz, i64 i, i32 iBase = 10);

inline void                   wd32_from_u32(wd32char * psz, u32 u, i32 iBase = 10);
inline void                   wd32_from_i32(wd32char * psz, i32 i, i32 iBase = 10);

inline i64                    wd32_to_i64(const wd32char * psz, const wd32char ** ppszEnd = nullptr, i32 iBase = 10);
inline u64                    wd32_to_u64(const wd32char * psz, const wd32char ** ppszEnd = nullptr, i32 iBase = 10);
inline i64                    wd32_count_to_i64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase, strsize srclen);

inline i32                    wd32_to_i32(const wd32char * psz, const wd32char ** ppszEnd = nullptr, i32 iBase = 10);
inline u32                    wd32_to_u32(const wd32char * psz, const wd32char ** ppszEnd = nullptr, i32 iBase = 10);
inline i32                    wd32_count_to_i32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase, strsize srclen);


inline void                   wd32_reverse(wd32char * sz);
inline void                   wd32_zero_pad(wd32char * sz, strsize iPad);
inline const wd32char *       wd32_scan(const wd32char * psz, const wd32char * find);
inline wd32char *             wd32_first_token(wd32char * psz, const wd32char * delimiters, wd32char ** action_context);
inline wd32char *             wd32_next_token(const wd32char * delimiters, wd32char ** action_context);




inline wd32char *             wd32_lower(wd32char * pch);
inline wd32char *             wd32_upper(wd32char * pch);

CLASS_DECL_AURA void          wd32_parse_command_line(wd32char * cmdstart, wd32char ** argv, wd32char * args, i32 * numargs, i32 * numchars);




inline i64 wd32_to_i64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase);
inline u64 wd32_to_u64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase);
inline i32 wd32_to_i32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase);
inline u32 wd32_to_u32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase);







