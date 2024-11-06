#pragma once





CLASS_DECL_ACME ::wd32_character               wd32_char_tolower(int ch);
CLASS_DECL_ACME ::wd32_character               wd32_char_toupper(int ch);


CLASS_DECL_ACME int                    wd32_char_isdigit(int ch);
CLASS_DECL_ACME int                    wd32_char_isalpha(int ch);
CLASS_DECL_ACME int                    wd32_char_isalnum(int ch);
CLASS_DECL_ACME int                    wd32_char_isspace(int ch);


CLASS_DECL_ACME int                    wd32_char_isxdigit(int ch);


CLASS_DECL_ACME ::wd32_character *             wd32_last_char(::wd32_character * psz);
CLASS_DECL_ACME const ::wd32_character *       wd32_const_last_char(const ::wd32_character * psz);
CLASS_DECL_ACME ::wd32_character *             wd32_concatenate(::wd32_character * dest, const ::wd32_character * cat);
CLASS_DECL_ACME ::wd32_character *             wd32_copy(::wd32_character * dest, const ::wd32_character * cat);
CLASS_DECL_ACME ::wd32_character *             wd32_count_copy(::wd32_character * dest, const ::wd32_character * cat, strsize iLen);
CLASS_DECL_ACME strsize                wd32_length(const ::wd32_character * cat);
CLASS_DECL_ACME ::wd32_character *             wd32_duplicate(const ::wd32_character * src); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME ::wd32_character *             wd32_count_duplicate(const ::wd32_character * src, strsize srclen); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME const ::wd32_character *       wd32_find_string(const ::wd32_character * src, const ::wd32_character * find);
CLASS_DECL_ACME const ::wd32_character *       wd32_find_string_case_insensitive(const ::wd32_character * src, const ::wd32_character * find);
CLASS_DECL_ACME const ::wd32_character *       wd32_count_find_string(const ::wd32_character * src, const ::wd32_character * find, strsize iLen);
CLASS_DECL_ACME const ::wd32_character *       wd32_count_find_string_case_insensitive(const ::wd32_character * src, const ::wd32_character * find, strsize iLen);

CLASS_DECL_ACME const ::wd32_character *       wd32_next_separator_token(const ::wd32_character * src, ::wd32_character chFind);


CLASS_DECL_ACME int                    wd32_compare(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_compare_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_count_compare(const ::wd32_character * sz1, const ::wd32_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    wd32_count_compare_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    wd32_collate(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_collate_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_count_collate(const ::wd32_character * sz1, const ::wd32_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    wd32_count_collate_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    wd32_begins(const ::wd32_character * sz1, const ::wd32_character * prefix);
CLASS_DECL_ACME int                    wd32_begins_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * prefix);
CLASS_DECL_ACME const ::wd32_character *       wd32_begins_eat(const ::wd32_character * sz1, const ::wd32_character * prefix);
CLASS_DECL_ACME int                    wd32_ends(const ::wd32_character * sz1, const ::wd32_character * suffix);
CLASS_DECL_ACME int                    wd32_ends_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * suffix);
CLASS_DECL_ACME const ::wd32_character *       wd32_find_char(const ::wd32_character * sz, ::wd32_character ch);
CLASS_DECL_ACME const ::wd32_character *       wd32_find_char_reverse(const ::wd32_character * sz, ::wd32_character ch);
CLASS_DECL_ACME const ::wd32_character *       wd32_concatenate_and_duplicate(const ::wd32_character * psz1, const ::wd32_character * psz2, int iFree1, int iFree2);


CLASS_DECL_ACME void                   wd32_from_u64(::wd32_character * psz, u64 u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd32_from_i64(::wd32_character * psz, i64 i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   wd32_from_u32(::wd32_character * psz, unsigned int u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd32_from_i32(::wd32_character * psz, int i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME i64                    wd32_to_i64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME u64                    wd32_to_u64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME i64                    wd32_count_to_i64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase, strsize srclen);

CLASS_DECL_ACME int                    wd32_to_i32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned int                    wd32_to_u32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME int                    wd32_count_to_i32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase, strsize srclen);


CLASS_DECL_ACME void                   wd32_reverse(::wd32_character * sz);
CLASS_DECL_ACME void                   wd32_zero_pad(::wd32_character * sz, strsize iPad);
CLASS_DECL_ACME const ::wd32_character *       _wd32_scan(const ::wd32_character * psz, const ::wd32_character * find);
CLASS_DECL_ACME const ::wd32_character *       wd32_scan(const ::wd32_character * psz, const ::wd32_character * find);
CLASS_DECL_ACME ::wd32_character *             wd32_first_token(::wd32_character * psz, const ::wd32_character * delimiters, ::wd32_character ** action_context);
CLASS_DECL_ACME ::wd32_character *             wd32_next_token(const ::wd32_character * delimiters, ::wd32_character ** action_context);




CLASS_DECL_ACME ::wd32_character *             wd32_lower(::wd32_character * pch);
CLASS_DECL_ACME ::wd32_character *             wd32_upper(::wd32_character * pch);

CLASS_DECL_ACME void          wd32_parse_command_line(::wd32_character * cmdstart, ::wd32_character ** argv, ::wd32_character * args, int * numargs, int * numchars);




CLASS_DECL_ACME i64 wd32_to_i64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME u64 wd32_to_u64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME int wd32_to_i32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int wd32_to_u32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);







