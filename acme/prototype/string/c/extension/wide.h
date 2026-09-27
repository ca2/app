#pragma once





CLASS_DECL_ACME ::wide_character               wide_char_tolower(::i32 ch);
CLASS_DECL_ACME ::wide_character               wide_char_toupper(::i32 ch);


CLASS_DECL_ACME ::i32                    wide_char_isdigit(::i32 ch);
CLASS_DECL_ACME ::i32                    wide_char_isalpha(::i32 ch);
CLASS_DECL_ACME ::i32                    wide_char_isalnum(::i32 ch);
CLASS_DECL_ACME ::i32                    wide_char_isspace(::i32 ch);


CLASS_DECL_ACME ::i32                    wide_char_isxdigit(::i32 ch);


CLASS_DECL_ACME ::wide_character *             wide_last_char(::wide_character * psz);
CLASS_DECL_ACME const ::wide_character *       wide_const_last_char(const ::wide_character * psz);
CLASS_DECL_ACME ::wide_character *             wide_concatenate(::wide_character * dest, const ::wide_character * cat);
CLASS_DECL_ACME ::wide_character *             wide_copy(::wide_character * dest, const ::wide_character * cat);
CLASS_DECL_ACME ::wide_character *             wide_count_copy(::wide_character * dest, const ::wide_character * cat, character_count iLen);
CLASS_DECL_ACME character_count                wide_length(const ::wide_character * cat);
CLASS_DECL_ACME ::wide_character *             wide_duplicate(const ::wide_character * src); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME ::wide_character *             wide_count_duplicate(const ::wide_character * src, character_count srclen); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME const ::wide_character *       wide_find_string(const ::wide_character * src, const ::wide_character * find);
CLASS_DECL_ACME const ::wide_character *       wide_find_string_case_insensitive(const ::wide_character * src, const ::wide_character * find);
CLASS_DECL_ACME const ::wide_character *       wide_count_find_string(const ::wide_character * src, const ::wide_character * find, character_count iLen);
CLASS_DECL_ACME const ::wide_character *       wide_count_find_string_case_insensitive(const ::wide_character * src, const ::wide_character * find, character_count iLen);

CLASS_DECL_ACME const ::wide_character *       wide_next_separator_token(const ::wide_character * src, ::wide_character chFind);


CLASS_DECL_ACME ::i32                    wide_compare(const ::wide_character * sz1, const ::wide_character * sz2);
CLASS_DECL_ACME ::i32                    wide_compare_case_insensitive(const ::wide_character * sz1, const ::wide_character * sz2);
CLASS_DECL_ACME ::i32                    wide_count_compare(const ::wide_character * sz1, const ::wide_character * sz2, character_count iLen);
CLASS_DECL_ACME ::i32                    wide_count_compare_case_insensitive(const ::wide_character * sz1, const ::wide_character * sz2, character_count iLen);
CLASS_DECL_ACME ::i32                    wide_collate(const ::wide_character * sz1, const ::wide_character * sz2);
CLASS_DECL_ACME ::i32                    wide_collate_case_insensitive(const ::wide_character * sz1, const ::wide_character * sz2);
CLASS_DECL_ACME ::i32                    wide_count_collate(const ::wide_character * sz1, const ::wide_character * sz2, character_count iLen);
CLASS_DECL_ACME ::i32                    wide_count_collate_case_insensitive(const ::wide_character * sz1, const ::wide_character * sz2, character_count iLen);
CLASS_DECL_ACME ::i32                    wide_begins(const ::wide_character * sz1, const ::wide_character * prefix);
CLASS_DECL_ACME ::i32                    wide_begins_case_insensitive(const ::wide_character * sz1, const ::wide_character * prefix);
CLASS_DECL_ACME const ::wide_character *       wide_begins_eat(const ::wide_character * sz1, const ::wide_character * prefix);
CLASS_DECL_ACME ::i32                    wide_ends(const ::wide_character * sz1, const ::wide_character * suffix);
CLASS_DECL_ACME ::i32                    wide_ends_case_insensitive(const ::wide_character * sz1, const ::wide_character * suffix);
CLASS_DECL_ACME const ::wide_character *       wide_find_char(const ::wide_character * sz, ::wide_character ch);
CLASS_DECL_ACME const ::wide_character *       wide_find_char_reverse(const ::wide_character * sz, ::wide_character ch);
CLASS_DECL_ACME const ::wide_character *       wide_concatenate_and_duplicate(const ::wide_character * psz1, const ::wide_character * psz2, ::i32 iFree1, ::i32 iFree2);


CLASS_DECL_ACME void                   wide_from_u64(::wide_character * psz, ::u64 u, ::i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wide_from_i64(::wide_character * psz, ::i64 i, ::i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   wide_from_ui(::wide_character * psz, ::u32 u, ::i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wide_from_i(::wide_character * psz, ::i32 i, ::i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME ::i64                    wide_to_i64(const ::wide_character * psz, const ::wide_character ** ppszEnd = nullptr, ::i32 iBase = 10);
CLASS_DECL_ACME ::u64                    wide_to_u64(const ::wide_character * psz, const ::wide_character ** ppszEnd = nullptr, ::i32 iBase = 10);
CLASS_DECL_ACME ::i64                    wide_count_to_i64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase, character_count srclen);

CLASS_DECL_ACME ::i32                    wide_to_int(const ::wide_character * psz, const ::wide_character ** ppszEnd = nullptr, ::i32 iBase = 10);
CLASS_DECL_ACME ::u32                    wide_to_u32(const ::wide_character * psz, const ::wide_character ** ppszEnd = nullptr, ::i32 iBase = 10);
CLASS_DECL_ACME ::i32                    wide_count_to_int(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase, character_count srclen);


CLASS_DECL_ACME void                   wide_reverse(::wide_character * sz);
CLASS_DECL_ACME void                   wide_zero_pad(::wide_character * sz, character_count iPad);
CLASS_DECL_ACME const ::wide_character *       _wide_scan(const ::wide_character * psz, const ::wide_character * find);
CLASS_DECL_ACME const ::wide_character *       wide_scan(const ::wide_character * psz, const ::wide_character * find);
CLASS_DECL_ACME ::wide_character *             wide_first_token(::wide_character * psz, const ::wide_character * delimiters, ::wide_character ** action_context);
CLASS_DECL_ACME ::wide_character *             wide_next_token(const ::wide_character * delimiters, ::wide_character ** action_context);




CLASS_DECL_ACME ::wide_character *             wide_lower(::wide_character * pch);
CLASS_DECL_ACME ::wide_character *             wide_upper(::wide_character * pch);

CLASS_DECL_ACME void          wide_parse_command_line(::wide_character * cmdstart, ::wide_character ** argv, ::wide_character * args, ::i32 * numargs, ::i32 * numchars);




CLASS_DECL_ACME ::i64 wide_to_i64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase);
CLASS_DECL_ACME ::u64 wide_to_u64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase);
CLASS_DECL_ACME ::i32 wide_to_int(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase);
CLASS_DECL_ACME ::u32 wide_to_u32(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase);








