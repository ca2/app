#pragma once





CLASS_DECL_ACME ::wd16_character               wd16_char_tolower(i32 ch);
CLASS_DECL_ACME ::wd16_character               wd16_char_toupper(i32 ch);

CLASS_DECL_ACME i32                    wd16_char_isdigit(i32 ch);
CLASS_DECL_ACME i32                    wd16_char_isalpha(i32 ch);
CLASS_DECL_ACME i32                    wd16_char_isalnum(i32 ch);
CLASS_DECL_ACME i32                    wd16_char_isspace(i32 ch);


CLASS_DECL_ACME i32                    wd16_char_is_hexadecimal(i32 ch);

CLASS_DECL_ACME ::wd16_character *             wd16_last_char(::wd16_character * psz);
CLASS_DECL_ACME const ::wd16_character *       wd16_const_last_char(const ::wd16_character * psz);
CLASS_DECL_ACME ::wd16_character *             wd16_concatenate(::wd16_character * dest, const ::wd16_character * cat);
CLASS_DECL_ACME ::wd16_character *             wd16_copy(::wd16_character * dest, const ::wd16_character * cat);
CLASS_DECL_ACME ::wd16_character *             wd16_count_copy(::wd16_character * dest, const ::wd16_character * cat, strsize iLen);
CLASS_DECL_ACME strsize                wd16_length(const ::wd16_character * cat);
CLASS_DECL_ACME ::wd16_character *             wd16_duplicate(const ::wd16_character * src); // ATTENTION - memory_allocate
CLASS_DECL_ACME ::wd16_character *             wd16_count_duplicate(const ::wd16_character * src, strsize srclen); // ATTENTION - memory_allocate
CLASS_DECL_ACME const ::wd16_character *       wd16_find_string(const ::wd16_character * src, const ::wd16_character * find);
CLASS_DECL_ACME const ::wd16_character *       wd16_find_string_case_insensitive(const ::wd16_character * src, const ::wd16_character * find);
CLASS_DECL_ACME const ::wd16_character *       wd16_count_find_string(const ::wd16_character * src, const ::wd16_character * find, strsize iLen);
CLASS_DECL_ACME const ::wd16_character *       wd16_count_find_string_case_insensitive(const ::wd16_character * src, const ::wd16_character * find, strsize iLen);

CLASS_DECL_ACME const ::wd16_character *       wd16_next_separator_token(const ::wd16_character * src, ::wd16_character chFind);


CLASS_DECL_ACME i32                    wd16_compare(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME i32                    wd16_compare_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME i32                    wd16_count_compare(const ::wd16_character * sz1, const ::wd16_character * sz2, strsize iLen);
CLASS_DECL_ACME i32                    wd16_count_compare_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2, strsize iLen);
CLASS_DECL_ACME i32                    wd16_collate(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME i32                    wd16_collate_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME i32                    wd16_count_collate(const ::wd16_character * sz1, const ::wd16_character * sz2, strsize iLen);
CLASS_DECL_ACME i32                    wd16_count_collate_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2, strsize iLen);
CLASS_DECL_ACME i32                    wd16_begins(const ::wd16_character * sz1, const ::wd16_character * prefix);
CLASS_DECL_ACME i32                    wd16_begins_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * prefix);
CLASS_DECL_ACME const ::wd16_character *       wd16_begins_eat(const ::wd16_character * sz1, const ::wd16_character * prefix);
CLASS_DECL_ACME i32                    wd16_ends(const ::wd16_character * sz1, const ::wd16_character * suffix);
CLASS_DECL_ACME i32                    wd16_ends_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * suffix);
CLASS_DECL_ACME const ::wd16_character *       wd16_find_char(const ::wd16_character * sz, ::wd16_character ch);
CLASS_DECL_ACME const ::wd16_character *       wd16_find_char_reverse(const ::wd16_character * sz, ::wd16_character ch);
CLASS_DECL_ACME const ::wd16_character *       wd16_concatenate_and_duplicate(const ::wd16_character * psz1, const ::wd16_character * psz2, int iFree1, int iFree2);


CLASS_DECL_ACME void                   wd16_from_u64(::wd16_character * psz, u64 u, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd16_from_i64(::wd16_character * psz, i64 i, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   wd16_from_u32(::wd16_character * psz, u32 u, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd16_from_i32(::wd16_character * psz, i32 i, i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME i64                    wd16_to_i64(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, i32 iBase = 10);
CLASS_DECL_ACME u64                    wd16_to_u64(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, i32 iBase = 10);
CLASS_DECL_ACME i64                    wd16_count_to_i64(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, i32 iBase, strsize srclen);

CLASS_DECL_ACME i32                    wd16_to_i32(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, i32 iBase = 10);
CLASS_DECL_ACME u32                    wd16_to_u32(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, i32 iBase = 10);
CLASS_DECL_ACME i32                    wd16_count_to_i32(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, i32 iBase, strsize srclen);


CLASS_DECL_ACME void                   wd16_reverse(::wd16_character * sz);
CLASS_DECL_ACME void                   wd16_zero_pad(::wd16_character * sz, strsize iPad);
CLASS_DECL_ACME const ::wd16_character *       _wd16_scan(const ::wd16_character * psz, const ::wd16_character * find);
CLASS_DECL_ACME const ::wd16_character *       wd16_scan(const ::wd16_character * psz, const ::wd16_character * find);
CLASS_DECL_ACME ::wd16_character *             wd16_first_token(::wd16_character * psz, const ::wd16_character * delimiters, ::wd16_character ** action_context);
CLASS_DECL_ACME ::wd16_character *             wd16_next_token(const ::wd16_character * delimiters, ::wd16_character ** action_context);




CLASS_DECL_ACME ::wd16_character *             wd16_lower(::wd16_character * pch);
CLASS_DECL_ACME ::wd16_character *             wd16_upper(::wd16_character * pch);

CLASS_DECL_ACME void          wd16_parse_command_line(::wd16_character * cmdstart, ::wd16_character ** argv, ::wd16_character * args, i32 * numargs, i32 * numchars);




CLASS_DECL_ACME i64 wd16_to_i64(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u64 wd16_to_u64(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME i32 wd16_to_i32(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, i32 iBase);
CLASS_DECL_ACME u32 wd16_to_u32(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, i32 iBase);








CLASS_DECL_ACME strsize wd16_to_ansi_char_len(::wd16_character wch);
CLASS_DECL_ACME void wd16_to_ansi_char(char * psz, ::wd16_character wch);



