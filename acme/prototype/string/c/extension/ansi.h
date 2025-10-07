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
CLASS_DECL_ACME const_char_pointer ansi_const_last_char(const_char_pointer psz);
CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const_char_pointer cat);
CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const_char_pointer cat, character_count n);
CLASS_DECL_ACME ::ansi_character * ansi_copy(::ansi_character * psz, const_char_pointer cpy);
CLASS_DECL_ACME ::ansi_character * ansi_count_copy(::ansi_character * psz, const_char_pointer cpy, character_count len);
CLASS_DECL_ACME character_count                ansi_length(const_char_pointer psz);
CLASS_DECL_ACME ::ansi_character * ansi_duplicate(const_char_pointer psz); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME ::ansi_character * ansi_count_duplicate(const_char_pointer psz, character_count len); // ATTENTION - ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate
CLASS_DECL_ACME const_char_pointer ansi_find_string(const_char_pointer psz, const_char_pointer find);
CLASS_DECL_ACME const_char_pointer case_insensitive_ansi_find_string(const_char_pointer psz, const_char_pointer find);
CLASS_DECL_ACME const_char_pointer ansi_count_find_string(const_char_pointer psz, const_char_pointer find, character_count len);
CLASS_DECL_ACME const_char_pointer case_insensitive_ansi_count_find_string(const_char_pointer psz, const_char_pointer find, character_count len);

//CLASS_DECL_ACME ::ansi_character *             ansi_next_token(::ansi_character * psz, ::ansi_character ch);


CLASS_DECL_ACME int                    ansi_compare(const_char_pointer sz1, const_char_pointer sz2);
CLASS_DECL_ACME int                    case_insensitive_ansi_compare(const_char_pointer sz1, const_char_pointer sz2);
CLASS_DECL_ACME int                    ansi_count_compare(const_char_pointer sz1, const_char_pointer sz2, character_count iLen);
CLASS_DECL_ACME int                    case_insensitive_ansi_count_compare(const_char_pointer sz1, const_char_pointer sz2, character_count iLen);
CLASS_DECL_ACME int                    ansi_collate(const_char_pointer sz1, const_char_pointer sz2);
CLASS_DECL_ACME int                    case_insensitive_ansi_collate(const_char_pointer sz1, const_char_pointer sz2);
CLASS_DECL_ACME int                    ansi_count_collate(const_char_pointer sz1, const_char_pointer sz2, character_count iLen);
CLASS_DECL_ACME int                    case_insensitive_ansi_count_collate(const_char_pointer sz1, const_char_pointer sz2, character_count iLen);
CLASS_DECL_ACME int                    ansi_begins(const_char_pointer sz1, const_char_pointer prefix);
CLASS_DECL_ACME int                    case_insensitive_ansi_begins(const_char_pointer sz1, const_char_pointer prefix);
CLASS_DECL_ACME const_char_pointer ansi_begins_eat(const_char_pointer sz1, const_char_pointer prefix);
CLASS_DECL_ACME const_char_pointer case_insensitive_ansi_begins_eat(const_char_pointer sz1, const_char_pointer prefix);
CLASS_DECL_ACME int                    ansi_ends(const_char_pointer sz1, const_char_pointer suffix);
CLASS_DECL_ACME int                    case_insensitive_ansi_ends(const_char_pointer sz1, const_char_pointer suffix);
CLASS_DECL_ACME const_char_pointer ansi_find_char(const_char_pointer sz, ::ansi_character ch);
CLASS_DECL_ACME const_char_pointer ansi_find_char_reverse(const_char_pointer sz, ::ansi_character ch);
CLASS_DECL_ACME const_char_pointer ansi_concatenate_and_duplicate(const_char_pointer psz1, const_char_pointer psz2, int_bool iFree1 = false, int_bool iFree2 = false);

//CLASS_DECL_ACME void ansi_from_long_long(char* sz, long long i, int iBase, enum_digit_case edigitcase = e_digit_case_lower);
//CLASS_DECL_ACME void ansi_from_unsigned_long_long(char* sz, unsigned long long u, int iBase, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   ansi_from_unsigned_long_long(::ansi_character * psz, unsigned long long u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   ansi_from_long_long(::ansi_character * psz, long long i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME void                   ansi_from_ui(::ansi_character * psz, unsigned int u, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
CLASS_DECL_ACME void                   ansi_from_i(::ansi_character * psz, int i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);

CLASS_DECL_ACME long long                    ansi_to_long_long(const_char_pointer psz, const_char_pointer *ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned long long                    ansi_to_unsigned_long_long(const_char_pointer psz, const_char_pointer *ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME long long                    ansi_count_to_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase, character_count srclen);

CLASS_DECL_ACME int                    ansi_to_int(const_char_pointer psz, const_char_pointer *ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME unsigned int                    ansi_to_unsigned_int(const_char_pointer psz, const_char_pointer *ppszEnd = nullptr, int iBase = 10);
CLASS_DECL_ACME int                    ansi_count_to_int(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase, character_count srclen);


CLASS_DECL_ACME void                   ansi_reverse(::ansi_character * sz);
CLASS_DECL_ACME void                   ansi_reverse(::ansi_character * sz, character_count size);
CLASS_DECL_ACME void                   ansi_zero_pad(::ansi_character * sz, character_count lenPad);
CLASS_DECL_ACME const_char_pointer        _ansi_scan(const_char_pointer psz, const_char_pointer pszCharacters);
CLASS_DECL_ACME const_char_pointer        ansi_scan(const_char_pointer psz, const_char_pointer pszCharacters);
//CLASS_DECL_ACME const_char_pointer        ansi_token(const_char_pointer psz, const_char_pointer pszSeparators);
CLASS_DECL_ACME ::ansi_character *             ansi_first_token(::ansi_character * psz, const_char_pointer delimiters, ::ansi_character ** action_context);
CLASS_DECL_ACME ::ansi_character *             ansi_next_token(const_char_pointer delimiters, ::ansi_character ** action_context);


CLASS_DECL_ACME ::ansi_character * ansi_lower(::ansi_character * pch);
CLASS_DECL_ACME ::ansi_character * ansi_upper(::ansi_character * pch);


CLASS_DECL_ACME int_bool matches_wildcard_criteria(const_char_pointer pszCriteria, const_char_pointer pszValue);
CLASS_DECL_ACME int_bool case_insensitive_matches_wildcard_criteria(const_char_pointer pszCriteria, const_char_pointer pszValue);


CLASS_DECL_ACME void ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, int * numargs, int * numchars);




CLASS_DECL_ACME const void * memory_find_memory(const void * src, character_count srclen, const void * find, character_count findlen);


CLASS_DECL_ACME const_char_pointer wildcard_next_stop(const_char_pointer pszCriteria);


CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const_char_pointer pszCriteria, const_char_pointer pszValue);
CLASS_DECL_ACME int_bool               case_insensitive_wildcard_matches_criteria(const_char_pointer pszCriteria, const_char_pointer pszValue);


//CLASS_DECL_ACME const_char_pointer eol();


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



