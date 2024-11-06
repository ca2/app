#pragma once


CLASS_DECL_ACME ::ansi_character               ansi_char_tolower(int i);
CLASS_DECL_ACME ::ansi_character               ansi_char_toupper(int i);

CLASS_DECL_ACME int                    ansi_char_isdigit(int i);
CLASS_DECL_ACME int                    ansi_char_isalpha(int i);
CLASS_DECL_ACME int                    ansi_char_isalnum(int i);
CLASS_DECL_ACME int                    ansi_char_isspace(int i);

CLASS_DECL_ACME int                    ansi_char_isxdigit(int i);


CLASS_DECL_ACME int                    ansi_char_is_hexadecimal(int i);


CLASS_DECL_ACME ::ansi_character * ansi_last_char(::ansi_character * psz);
CLASS_DECL_ACME const ::ansi_character * ansi_const_last_char(const ::ansi_character * psz);
CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat);
CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat, strsize n);
CLASS_DECL_ACME ::ansi_character * ansi_copy(::ansi_character * psz, const ::ansi_character * cpy);
CLASS_DECL_ACME ::ansi_character * ansi_count_copy(::ansi_character * psz, const ::ansi_character * cpy, strsize len);
CLASS_DECL_ACME strsize                ansi_length(const ::ansi_character * psz);
CLASS_DECL_ACME ::ansi_character * ansi_duplicate(const ::ansi_character * psz); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME ::ansi_character * ansi_count_duplicate(const ::ansi_character * psz, strsize len); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME const ::ansi_character * ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find);
CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find);
CLASS_DECL_ACME const ::ansi_character * ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len);
CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len);

//CLASS_DECL_ACME ::ansi_character *             ansi_next_token(::ansi_character * psz, ::ansi_character ch);


CLASS_DECL_ACME int                    ansi_compare(const ::ansi_character * sz1, const ::ansi_character * sz2);
CLASS_DECL_ACME int                    case_insensitive_ansi_compare(const ::ansi_character * sz1, const ::ansi_character * sz2);
CLASS_DECL_ACME int                    ansi_count_compare(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    case_insensitive_ansi_count_compare(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    ansi_collate(const ::ansi_character * sz1, const ::ansi_character * sz2);
CLASS_DECL_ACME int                    case_insensitive_ansi_collate(const ::ansi_character * sz1, const ::ansi_character * sz2);
CLASS_DECL_ACME int                    ansi_count_collate(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    case_insensitive_ansi_count_collate(const ::ansi_character * sz1, const ::ansi_character * sz2, strsize iLen);
CLASS_DECL_ACME int                    ansi_begins(const ::ansi_character * sz1, const ::ansi_character * prefix);
CLASS_DECL_ACME int                    case_insensitive_ansi_begins(const ::ansi_character * sz1, const ::ansi_character * prefix);
CLASS_DECL_ACME const ::ansi_character * ansi_begins_eat(const ::ansi_character * sz1, const ::ansi_character * prefix);
CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_begins_eat(const ::ansi_character * sz1, const ::ansi_character * prefix);
CLASS_DECL_ACME int                    ansi_ends(const ::ansi_character * sz1, const ::ansi_character * suffix);
CLASS_DECL_ACME int                    case_insensitive_ansi_ends(const ::ansi_character * sz1, const ::ansi_character * suffix);
CLASS_DECL_ACME const ::ansi_character * ansi_find_char(const ::ansi_character * sz, ::ansi_character ch);
CLASS_DECL_ACME const ::ansi_character * ansi_find_char_reverse(const ::ansi_character * sz, ::ansi_character ch);
CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2, int_bool iFree1 = false, int_bool iFree2 = false);

//CLASS_DECL_ACME void ansi_from_i64(char* sz, i64 i, int iBase, enum_digit_case edigitcase = e_digit_case_lower);
//CLASS_DECL_ACME void ansi_from_u64(char* sz, u64 u, int iBase, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   ansi_from_u64(::ansi_character * psz, u64 u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   ansi_from_i64(::ansi_character * psz, i64 i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   ansi_from_u32(::ansi_character * psz, unsigned int u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   ansi_from_i32(::ansi_character * psz, int i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME i64                    ansi_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME u64                    ansi_to_u64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME i64                    ansi_count_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase, strsize srclen);

CLASS_DECL_ACME int                    ansi_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned int                    ansi_to_u32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME int                    ansi_count_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase, strsize srclen);


CLASS_DECL_ACME void                   ansi_reverse(::ansi_character * sz);
CLASS_DECL_ACME void                   ansi_reverse(::ansi_character * sz, strsize size);
CLASS_DECL_ACME void                   ansi_zero_pad(::ansi_character * sz, strsize lenPad);
CLASS_DECL_ACME const ::ansi_character *       _ansi_scan(const ::ansi_character * psz, const ::ansi_character * pszCharacters);
CLASS_DECL_ACME const ::ansi_character *       ansi_scan(const ::ansi_character * psz, const ::ansi_character * pszCharacters);
//CLASS_DECL_ACME const ::ansi_character *       ansi_token(const ::ansi_character * psz, const ::ansi_character * pszSeparators);
CLASS_DECL_ACME ::ansi_character *             ansi_first_token(::ansi_character * psz, const ::ansi_character * delimiters, ::ansi_character ** action_context);
CLASS_DECL_ACME ::ansi_character *             ansi_next_token(const ::ansi_character * delimiters, ::ansi_character ** action_context);


CLASS_DECL_ACME ::ansi_character * ansi_lower(::ansi_character * pch);
CLASS_DECL_ACME ::ansi_character * ansi_upper(::ansi_character * pch);


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
CLASS_DECL_ACME int_bool case_insensitive_matches_wildcard_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);


CLASS_DECL_ACME void ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, int * numargs, int * numchars);




CLASS_DECL_ACME const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen);


CLASS_DECL_ACME const ::ansi_character * wildcard_next_stop(const ::ansi_character * pszCriteria);


CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
CLASS_DECL_ACME int_bool               case_insensitive_wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);


//CLASS_DECL_ACME const ::ansi_character * eol();


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



