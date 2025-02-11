#pragma once





CLASS_DECL_ACME ::wd16_character               wd16_char_tolower(int ch);
CLASS_DECL_ACME ::wd16_character               wd16_char_toupper(int ch);

CLASS_DECL_ACME int                    wd16_char_isdigit(int ch);
CLASS_DECL_ACME int                    wd16_char_isalpha(int ch);
CLASS_DECL_ACME int                    wd16_char_isalnum(int ch);
CLASS_DECL_ACME int                    wd16_char_isspace(int ch);


CLASS_DECL_ACME int                    wd16_char_isxdigit(int ch);

CLASS_DECL_ACME ::wd16_character *             wd16_last_char(::wd16_character * psz);
CLASS_DECL_ACME const ::wd16_character *       wd16_const_last_char(const ::wd16_character * psz);
CLASS_DECL_ACME ::wd16_character *             wd16_concatenate(::wd16_character * dest, const ::wd16_character * cat);
CLASS_DECL_ACME ::wd16_character *             wd16_copy(::wd16_character * dest, const ::wd16_character * cat);
CLASS_DECL_ACME ::wd16_character *             wd16_count_copy(::wd16_character * dest, const ::wd16_character * cat, character_count iLen);
CLASS_DECL_ACME character_count                wd16_length(const ::wd16_character * cat);
CLASS_DECL_ACME ::wd16_character *             wd16_duplicate(const ::wd16_character * src); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME ::wd16_character *             wd16_count_duplicate(const ::wd16_character * src, character_count srclen); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME const ::wd16_character *       wd16_find_string(const ::wd16_character * src, const ::wd16_character * find);
CLASS_DECL_ACME const ::wd16_character *       wd16_find_string_case_insensitive(const ::wd16_character * src, const ::wd16_character * find);
CLASS_DECL_ACME const ::wd16_character *       wd16_count_find_string(const ::wd16_character * src, const ::wd16_character * find, character_count iLen);
CLASS_DECL_ACME const ::wd16_character *       wd16_count_find_string_case_insensitive(const ::wd16_character * src, const ::wd16_character * find, character_count iLen);

CLASS_DECL_ACME const ::wd16_character *       wd16_next_separator_token(const ::wd16_character * src, ::wd16_character chFind);


CLASS_DECL_ACME int                    wd16_compare(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME int                    wd16_compare_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME int                    wd16_count_compare(const ::wd16_character * sz1, const ::wd16_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd16_count_compare_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd16_collate(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME int                    wd16_collate_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2);
CLASS_DECL_ACME int                    wd16_count_collate(const ::wd16_character * sz1, const ::wd16_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd16_count_collate_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * sz2, character_count iLen);
CLASS_DECL_ACME int                    wd16_begins(const ::wd16_character * sz1, const ::wd16_character * prefix);
CLASS_DECL_ACME int                    wd16_begins_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * prefix);
CLASS_DECL_ACME const ::wd16_character *       wd16_begins_eat(const ::wd16_character * sz1, const ::wd16_character * prefix);
CLASS_DECL_ACME int                    wd16_ends(const ::wd16_character * sz1, const ::wd16_character * suffix);
CLASS_DECL_ACME int                    wd16_ends_case_insensitive(const ::wd16_character * sz1, const ::wd16_character * suffix);
CLASS_DECL_ACME const ::wd16_character *       wd16_find_char(const ::wd16_character * sz, ::wd16_character ch);
CLASS_DECL_ACME const ::wd16_character *       wd16_find_char_reverse(const ::wd16_character * sz, ::wd16_character ch);
CLASS_DECL_ACME const ::wd16_character *       wd16_concatenate_and_duplicate(const ::wd16_character * psz1, const ::wd16_character * psz2, int iFree1, int iFree2);


CLASS_DECL_ACME void                   wd16_from_unsigned_long_long(::wd16_character * psz, unsigned long long u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd16_from_long_long(::wd16_character * psz, long long i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   wd16_from_ui(::wd16_character * psz, unsigned int u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   wd16_from_i(::wd16_character * psz, int i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME long long                    wd16_to_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned long long                    wd16_to_unsigned_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME long long                    wd16_count_to_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase, character_count srclen);

CLASS_DECL_ACME int                    wd16_to_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned int                    wd16_to_unsigned_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME int                    wd16_count_to_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase, character_count srclen);


CLASS_DECL_ACME void                   wd16_reverse(::wd16_character * sz);
CLASS_DECL_ACME void                   wd16_zero_pad(::wd16_character * sz, character_count iPad);
CLASS_DECL_ACME const ::wd16_character *       _wd16_scan(const ::wd16_character * psz, const ::wd16_character * find);
CLASS_DECL_ACME const ::wd16_character *       wd16_scan(const ::wd16_character * psz, const ::wd16_character * find);
CLASS_DECL_ACME ::wd16_character *             wd16_first_token(::wd16_character * psz, const ::wd16_character * delimiters, ::wd16_character ** action_context);
CLASS_DECL_ACME ::wd16_character *             wd16_next_token(const ::wd16_character * delimiters, ::wd16_character ** action_context);




CLASS_DECL_ACME ::wd16_character *             wd16_lower(::wd16_character * pch);
CLASS_DECL_ACME ::wd16_character *             wd16_upper(::wd16_character * pch);

CLASS_DECL_ACME void          wd16_parse_command_line(::wd16_character * cmdstart, ::wd16_character ** argv, ::wd16_character * args, int * numargs, int * numchars);




CLASS_DECL_ACME long long wd16_to_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned long long wd16_to_unsigned_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase);
CLASS_DECL_ACME int wd16_to_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase);
CLASS_DECL_ACME unsigned int wd16_to_unsigned_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase);








CLASS_DECL_ACME character_count wd16_to_ansi_char_len(::wd16_character wch);
CLASS_DECL_ACME void wd16_to_ansi_char(char * psz, ::wd16_character wch);



