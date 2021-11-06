#pragma once





inline wd16char               wd16_char_lowered(i32 ch);
inline wd16char               wd16_char_uppered(i32 ch);
inline i32                    wd16_char_is_digit(i32 ch);
inline i32                    wd16_char_is_hexadecimal(i32 ch);
inline i32                    wd16_char_is_alphabetic(i32 ch);
inline i32                    wd16_char_is_alphanumeric(i32 ch);
inline i32                    wd16_char_is_space(i32 ch);



inline wd16char *             wd16_last_char(wd16char * psz);
inline const wd16char *       wd16_const_last_char(const wd16char * psz);
inline wd16char *             wd16_concatenate(wd16char * dest, const wd16char * cat);
inline wd16char *             wd16_copy(wd16char * dest, const wd16char * cat);
inline wd16char *             wd16_count_copy(wd16char * dest, const wd16char * cat, strsize iLen);
inline strsize                wd16_length(const wd16char * cat);
inline wd16char *             wd16_duplicate(const wd16char * src); // ATTENTION - memory_allocate
inline wd16char *             wd16_count_duplicate(const wd16char * src, strsize srclen); // ATTENTION - memory_allocate 
inline const wd16char *       wd16_find_string(const wd16char * src, const wd16char * find);
inline const wd16char *       wd16_find_string_case_insensitive(const wd16char * src, const wd16char * find);
inline const wd16char *       wd16_count_find_string(const wd16char * src, const wd16char * find, strsize iLen);
inline const wd16char *       wd16_count_find_string_case_insensitive(const wd16char * src, const wd16char * find, strsize iLen);

inline const wd16char *       wd16_next_separator_token(const wd16char * src, wd16char chFind);


inline i32                    wd16_compare(const wd16char * sz1, const wd16char * sz2);
inline i32                    wd16_compare_case_insensitive(const wd16char * sz1, const wd16char * sz2);
inline i32                    wd16_count_compare(const wd16char * sz1, const wd16char * sz2, strsize iLen);
inline i32                    wd16_count_compare_case_insensitive(const wd16char * sz1, const wd16char * sz2, strsize iLen);
inline i32                    wd16_collate(const wd16char * sz1, const wd16char * sz2);
inline i32                    wd16_collate_case_insensitive(const wd16char * sz1, const wd16char * sz2);
inline i32                    wd16_count_collate(const wd16char * sz1, const wd16char * sz2, strsize iLen);
inline i32                    wd16_count_collate_case_insensitive(const wd16char * sz1, const wd16char * sz2, strsize iLen);
inline i32                    wd16_begins(const wd16char * sz1, const wd16char * prefix);
inline i32                    wd16_begins_case_insensitive(const wd16char * sz1, const wd16char * prefix);
inline const wd16char *       wd16_begins_eat(const wd16char * sz1, const wd16char * prefix);
inline i32                    wd16_ends(const wd16char * sz1, const wd16char * suffix);
inline i32                    wd16_ends_case_insensitive(const wd16char * sz1, const wd16char * suffix);
inline const wd16char *       wd16_find_char(const wd16char * sz, wd16char ch);
inline const wd16char *       wd16_find_char_reverse(const wd16char * sz, wd16char ch);
inline const wd16char *       wd16_concatenate_and_duplicate(const wd16char * psz1, const wd16char * psz2, int iFree1, int iFree2);


inline void                   wd16_from_u64(wd16char * psz, u64 u, i32 iBase = 10);
inline void                   wd16_from_i64(wd16char * psz, i64 i, i32 iBase = 10);

inline void                   wd16_from_u32(wd16char * psz, u32 u, i32 iBase = 10);
inline void                   wd16_from_i32(wd16char * psz, i32 i, i32 iBase = 10);

inline i64                    wd16_to_i64(const wd16char * psz, const wd16char ** ppszEnd = nullptr, i32 iBase = 10);
inline u64                    wd16_to_u64(const wd16char * psz, const wd16char ** ppszEnd = nullptr, i32 iBase = 10);
inline i64                    wd16_count_to_i64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase, strsize srclen);

inline i32                    wd16_to_i32(const wd16char * psz, const wd16char ** ppszEnd = nullptr, i32 iBase = 10);
inline u32                    wd16_to_u32(const wd16char * psz, const wd16char ** ppszEnd = nullptr, i32 iBase = 10);
inline i32                    wd16_count_to_i32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase, strsize srclen);


inline void                   wd16_reverse(wd16char * sz);
inline void                   wd16_zero_pad(wd16char * sz, strsize iPad);
inline const wd16char *       wd16_scan(const wd16char * psz, const wd16char * find);
inline wd16char *             wd16_first_token(wd16char * psz, const wd16char * delimiters, wd16char ** action_context);
inline wd16char *             wd16_next_token(const wd16char * delimiters, wd16char ** action_context);




inline wd16char *             wd16_lower(wd16char * pch);
inline wd16char *             wd16_upper(wd16char * pch);

CLASS_DECL_ACME void          wd16_parse_command_line(wd16char * cmdstart, wd16char ** argv, wd16char * args, i32 * numargs, i32 * numchars);




inline i64 wd16_to_i64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase);
inline u64 wd16_to_u64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase);
inline i32 wd16_to_i32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase);
inline u32 wd16_to_u32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase);








