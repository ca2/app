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
CLASS_DECL_ACME ::wd32_character *             wd32_count_copy(::wd32_character * dest, const ::wd32_character * cat, character_count iLen);
CLASS_DECL_ACME character_count                wd32_length(const ::wd32_character * cat);
CLASS_DECL_ACME ::wd32_character *             wd32_duplicate(const ::wd32_character * src); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME ::wd32_character *             wd32_count_duplicate(const ::wd32_character * src, character_count srclen); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME const ::wd32_character *       wd32_find_string(const ::wd32_character * src, const ::wd32_character * find);
CLASS_DECL_ACME const ::wd32_character *       wd32_find_string_case_insensitive(const ::wd32_character * src, const ::wd32_character * find);
CLASS_DECL_ACME const ::wd32_character *       wd32_count_find_string(const ::wd32_character * src, const ::wd32_character * find, character_count iLen);
CLASS_DECL_ACME const ::wd32_character *       wd32_count_find_string_case_insensitive(const ::wd32_character * src, const ::wd32_character * find, character_count iLen);

CLASS_DECL_ACME const ::wd32_character *       wd32_next_separator_token(const ::wd32_character * src, ::wd32_character chFind);


CLASS_DECL_ACME int                    wd32_compare(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_compare_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_count_compare(const ::wd32_character * sz1, const ::wd32_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd32_count_compare_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd32_collate(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_collate_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2);
CLASS_DECL_ACME int                    wd32_count_collate(const ::wd32_character * sz1, const ::wd32_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd32_count_collate_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd32_begins(const ::wd32_character * sz1, const ::wd32_character * prefix);
CLASS_DECL_ACME int                    wd32_begins_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * prefix);
CLASS_DECL_ACME const ::wd32_character *       wd32_begins_eat(const ::wd32_character * sz1, const ::wd32_character * prefix);
CLASS_DECL_ACME int                    wd32_ends(const ::wd32_character * sz1, const ::wd32_character * suffix);
CLASS_DECL_ACME int                    wd32_ends_case_insensitive(const ::wd32_character * sz1, const ::wd32_character * suffix);
CLASS_DECL_ACME const ::wd32_character *       wd32_find_char(const ::wd32_character * sz, ::wd32_character ch);
CLASS_DECL_ACME const ::wd32_character *       wd32_find_char_reverse(const ::wd32_character * sz, ::wd32_character ch);
CLASS_DECL_ACME const ::wd32_character *       wd32_concatenate_and_duplicate(const ::wd32_character * psz1, const ::wd32_character * psz2, int iFree1, int iFree2);


CLASS_DECL_ACME void                   wd32_from_unsigned_long_long(::wd32_character * psz, unsigned long long u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd32_from_long_long(::wd32_character * psz, long long i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   wd32_from_ui(::wd32_character * psz, unsigned int u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd32_from_i(::wd32_character * psz, int i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME long long                    wd32_to_long_long(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned long long                    wd32_to_unsigned_long_long(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME long long                    wd32_count_to_long_long(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase, character_count srclen);

CLASS_DECL_ACME int                    wd32_to_int(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned int                    wd32_to_unsigned_int(const ::wd32_character * psz, const ::wd32_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME int                    wd32_count_to_int(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase, character_count srclen);


CLASS_DECL_ACME void                   wd32_reverse(::wd32_character * sz);
CLASS_DECL_ACME void                   wd32_zero_pad(::wd32_character * sz, character_count iPad);
CLASS_DECL_ACME const ::wd32_character *       _wd32_scan(const ::wd32_character * psz, const ::wd32_character * find);
CLASS_DECL_ACME const ::wd32_character *       wd32_scan(const ::wd32_character * psz, const ::wd32_character * find);
CLASS_DECL_ACME ::wd32_character *             wd32_first_token(::wd32_character * psz, const ::wd32_character * delimiters, ::wd32_character ** action_context);
CLASS_DECL_ACME ::wd32_character *             wd32_next_token(const ::wd32_character * delimiters, ::wd32_character ** action_context);




CLASS_DECL_ACME ::wd32_character *             wd32_lower(::wd32_character * pch);
CLASS_DECL_ACME ::wd32_character *             wd32_upper(::wd32_character * pch);

CLASS_DECL_ACME void          wd32_parse_command_line(::wd32_character * cmdstart, ::wd32_character ** argv, ::wd32_character * args, int * numargs, int * numchars);




CLASS_DECL_ACME long long wd32_to_long_long(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned long long wd32_to_unsigned_long_long(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME int wd32_to_int(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int wd32_to_unsigned_int(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, int iBase);







