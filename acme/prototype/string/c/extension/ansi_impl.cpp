#include "framework.h"
#include <string.h>


CLASS_DECL_ACME ::ansi_character ansi_char_tolower(int i) { return __ansitolower(i); }
CLASS_DECL_ACME ::ansi_character ansi_char_toupper(int i) { return __ansitoupper(i); }


CLASS_DECL_ACME int ansi_char_isdigit(int i) { return __ansicharisdigit(i); }
CLASS_DECL_ACME int ansi_char_isalpha(int i) { return __ansicharisalpha(i); }
CLASS_DECL_ACME int ansi_char_isalnum(int i) { return __ansicharisalnum(i); }
CLASS_DECL_ACME int ansi_char_isspace(int i) { return __ansicharisspace(i); }
CLASS_DECL_ACME int ansi_char_isxdigit(int i) { return __ansicharisxdigit(i); }


CLASS_DECL_ACME int ansi_char_is_hexadecimal(int i) { return __ansicharishexadecimal(i); }


CLASS_DECL_ACME const_char_pointer ansi_const_last_char(const_char_pointer psz);

CLASS_DECL_ACME ::ansi_character * ansi_last_char(::ansi_character * psz)
{

  return (::ansi_character *)ansi_const_last_char(psz);

}


CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const_char_pointer cat)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cat)) return nullptr;

   return ansi_cat(psz, cat);

}



//CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const_char_pointer cat, character_count n)
//{
//
//   auto destination = psz;
//
//   if (::is_null(psz)) return nullptr;
//
//   if (::is_null(cat)) return nullptr;
//
//   psz += strlen(psz);
//
//   while(n > 0)
//   {
//
//      *psz = *cat;
//
//      psz++;
//
//      cat++;
//
//      n--;
//
//   }
//
//   *psz = '\0';
//
//   return destination;
//
//}
//

CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const_char_pointer cat, character_count n)
{

  auto destination = psz;

  if (::is_null(psz)) return nullptr;

  if (::is_null(cat)) return nullptr;

  psz += strlen(psz);

  while(n > 0)
  {

     *psz = *cat;

     psz++;

     cat++;

     n--;

  }

  *psz = '\0';

  return destination;

}


CLASS_DECL_ACME ::ansi_character * ansi_copy(::ansi_character * psz, const_char_pointer cpy)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(cpy)) return nullptr;

  return strcpy(psz, cpy);

}


CLASS_DECL_ACME ::ansi_character * ansi_count_copy(::ansi_character * psz, const_char_pointer cpy, character_count len)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(cpy)) return nullptr;

  if (len < 0) return nullptr;

  return strncpy(psz, cpy, len);

}


CLASS_DECL_ACME character_count ansi_length(const_char_pointer psz)
{

  if (::is_null(psz)) return 0;

  return strlen(psz);

}


CLASS_DECL_ACME ::ansi_character * ansi_duplicate(const_char_pointer psz)
{

  if (::is_null(psz)) return nullptr;

  auto pszDup = (::ansi_character *) ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(strlen(psz) + 1, nullptr);

  strcpy(pszDup, psz);

  return pszDup;

}


CLASS_DECL_ACME ::ansi_character * ansi_count_duplicate(const_char_pointer psz, character_count len)
{

  if (::is_null(psz)) return nullptr;

  if (len < 0) return nullptr;

  auto pszDup = (::ansi_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len + 1, nullptr);

  strncpy(pszDup, psz, len);

  pszDup[len] = '\0';

  return pszDup;

}


CLASS_DECL_ACME const_char_pointer ansi_find_string(const_char_pointer psz, const_char_pointer find)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(find)) return nullptr;

  return strstr(psz, find);

}



CLASS_DECL_ACME const_char_pointer case_insensitive_ansi_find_string(const_char_pointer psz, const_char_pointer find)
{

  if (::is_null(psz)) return nullptr;

  auto len = strlen(find);

  if (len <= 0)
  {

     return psz;

  }

  while (*psz != '\0')
  {

     if (!ansi_nicmp(psz, find, len))
     {

        return psz;

     }

     psz++;

  }

  return nullptr;

}


CLASS_DECL_ACME const_char_pointer ansi_count_find_string(const_char_pointer psz, const_char_pointer find, character_count len)
{

  if (::is_null(psz)) return nullptr;

  if (len > (character_count) strlen(find)) return nullptr;

  if (len <= 0)
  {

     return psz;

  }

  while (*psz != '\0')
  {

     if (!strncmp(psz, find, len))
     {

        return psz;

     }

     psz++;

  }

  return nullptr;

}


CLASS_DECL_ACME const_char_pointer case_insensitive_ansi_count_find_string(const_char_pointer psz, const_char_pointer find, character_count len)
{

  if (::is_null(psz)) return nullptr;

  if (len > (character_count)strlen(find)) return nullptr;

  if (len <= 0)
  {

     return psz;

  }

  while (*psz != '\0')
  {

     if (!ansi_nicmp(psz, find, len))
     {

        return psz;

     }

     psz++;

  }

  return nullptr;

}


CLASS_DECL_ACME int ansi_compare(const_char_pointer psz, const_char_pointer sz2)
{

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return strcmp(psz, sz2);

  }

}


CLASS_DECL_ACME int case_insensitive_ansi_compare(const_char_pointer psz, const_char_pointer sz2)
{

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return ansi_icmp(psz, sz2);

  }

}


CLASS_DECL_ACME int ansi_count_compare(const_char_pointer psz, const_char_pointer sz2, character_count len)
{

  if (len < 0)
  {

     return 0;

  }

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return strncmp(psz, sz2, len);

  }

}


CLASS_DECL_ACME int case_insensitive_ansi_count_compare(const_char_pointer psz, const_char_pointer sz2, character_count len)
{

  if (len < 0)
  {

     return 0;

  }

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return ansi_nicmp(psz, sz2, len);

  }

}



CLASS_DECL_ACME int ansi_collate(const_char_pointer psz, const_char_pointer sz2)
{

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return strcoll(psz, sz2);

  }

}


CLASS_DECL_ACME int case_insensitive_ansi_collate(const_char_pointer psz, const_char_pointer sz2)
{

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return ansi_icoll(psz, sz2);

  }

}


CLASS_DECL_ACME int ansi_count_collate(const_char_pointer psz, const_char_pointer sz2, character_count len)
{

  if (len < 0)
  {

     return 0;

  }

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return ansi_ncoll(psz, sz2, len);

  }

}


CLASS_DECL_ACME int case_insensitive_ansi_count_collate(const_char_pointer psz, const_char_pointer sz2, character_count len)
{

  if (len < 0)
  {

     return 0;

  }

  if (::is_null(psz))
  {

     if (::is_null(sz2))
     {

        return 0;

     }
     else
     {

        return -1;

     }

  }
  else if (::is_null(sz2))
  {

     return 1;

  }
  else
  {

     return ansi_nicoll(psz, sz2, len);

  }

}


CLASS_DECL_ACME const_char_pointer _ansi_scan(const_char_pointer psz, const_char_pointer find)
{

  return ansi_pbrk((::ansi_character *) psz, find);

}



CLASS_DECL_ACME const_char_pointer ansi_scan(const_char_pointer psz, const_char_pointer find)
{

  if (::is_empty(psz)) return psz;

  if (::is_empty(find)) return psz;
  
  while(*psz)
  {
     
     if(strchr(find, *psz))
     {
        
        return psz;
        
     }
     
     psz++;
     
  }

  return nullptr;

}


//CLASS_DECL_ACME const_char_pointer ansi_token(const_char_pointer psz, const_char_pointer pszSeparators)
//{
//
//   return string_find_first_in(psz, pszSeparators);
//
//}
//
//
//CLASS_DECL_ACME const_char_pointer _ansi_find_first_in(const_char_pointer psz, const_char_pointer pszSeparators)
//{
//
//   return _string_find_first_in(psz, pszSeparators);
//
//}


CLASS_DECL_ACME ::ansi_character * ansi_first_token(::ansi_character * psz, const_char_pointer delimiters, ::ansi_character ** action_context)
{

  return ansi_tok_r(psz, delimiters, action_context);

}


CLASS_DECL_ACME ::ansi_character * ansi_next_token(const_char_pointer delimiters, ::ansi_character ** action_context)
{

  return ansi_tok_r(nullptr, delimiters, action_context);

}


CLASS_DECL_ACME int ansi_begins(const_char_pointer psz, const_char_pointer prefix)
{

  if (::is_null(psz)) return false;

  if (::is_null(prefix)) return false;

  character_count len = strlen(prefix);

  if (len > (character_count)strlen(psz))
  {

     return false;

  }

  return !strncmp(psz, prefix, len);

}


CLASS_DECL_ACME int case_insensitive_ansi_begins(const_char_pointer psz, const_char_pointer prefix)
{

  if (::is_null(psz)) return false;

  if (::is_null(prefix)) return false;

  return !ansi_nicmp(psz, prefix, strlen(prefix));

}


CLASS_DECL_ACME const_char_pointer ansi_begins_eat(const_char_pointer psz, const_char_pointer prefix)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(prefix)) return nullptr;

  character_count len = strlen(prefix);

  if (strncmp(psz, prefix, len))
  {

     return nullptr;

  }

  return psz + len;

}


CLASS_DECL_ACME const_char_pointer case_insensitive_ansi_begins_eat(const_char_pointer psz, const_char_pointer prefix)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(prefix)) return nullptr;

  character_count len = strlen(prefix);

  if (ansi_nicmp(psz, prefix, len))
  {

     return nullptr;

  }

  return psz + len;

}


CLASS_DECL_ACME int ansi_ends(const_char_pointer psz, const_char_pointer suffix)
{

  if (::is_null(psz)) return false;

  if (::is_null(suffix)) return false;

  character_count len = strlen(suffix);

  character_count end = strlen(psz) - len;

  if(end < 0)
  {

     return false;

  }

  return !strncmp(psz + end, suffix, len);

}


CLASS_DECL_ACME int case_insensitive_ansi_ends(const_char_pointer psz, const_char_pointer suffix)
{

  if (::is_null(psz)) return false;

  if (::is_null(suffix)) return false;

  character_count len = strlen(suffix);

  character_count end = strlen(psz) - len;

  if (end < 0)
  {

     return false;

  }

  return !ansi_nicmp(psz + end, suffix, len);

}


CLASS_DECL_ACME const_char_pointer ansi_find_char(const_char_pointer psz, ::ansi_character ch)
{

  if (::is_null(psz)) return nullptr;

  return strchr(psz, ch);

}


CLASS_DECL_ACME const_char_pointer ansi_find_char_reverse(const_char_pointer psz, ::ansi_character ch)
{

  if (::is_null(psz)) return nullptr;

  return strrchr(psz, ch);

}


//CLASS_DECL_ACME const_char_pointer ansi_concatenate_and_duplicate(const_char_pointer psz1, const_char_pointer psz2);
//CLASS_DECL_ACME const_char_pointer ansi_concatenate_duplicate_and_free(const_char_pointer psz1, ::ansi_character * psz2);


CLASS_DECL_ACME void ansi_from_unsigned_long_long(::ansi_character * sz, unsigned long long u, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __u64toansi(u, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME void ansi_from_long_long(::ansi_character * sz, long long i, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __long_longtoansi(i, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME void ansi_from_ui(::ansi_character * sz, unsigned int u, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __u64toansi(u, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME void ansi_from_i(::ansi_character * sz, int i, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __long_longtoansi(i, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME long long ansi_count_to_long_long(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase, character_count srclen)
{

  auto len = ansi_length(psz);

  if (len <= 0)
  {

     return 0;

  }

  if (srclen < len)
  {

     if (!ansi_char_isdigit(*(psz + len - 1)))
     {

        auto pszDup = ansi_count_duplicate(psz, srclen);

        auto i = ansi_to_long_long(pszDup, ppszEnd, iBase);

        if (ppszEnd)
        {

           *ppszEnd = (::ansi_character *)psz + (*ppszEnd - pszDup);

        }

        ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pszDup);

        return i;

     }

  }

  return ansi_to_long_long(psz, ppszEnd, iBase);

}


CLASS_DECL_ACME int ansi_count_to_int(const_char_pointer psz, const_char_pointer *ppszEnd, int iBase, character_count srclen)
{

  auto len = ansi_length(psz);

  if (len <= 0)
  {

     return 0;

  }

  if (srclen < len)
  {

     if (!ansi_char_isdigit(*(psz + len - 1)))
     {

        auto pszDup = ansi_count_duplicate(psz, srclen);

        auto i = ansi_to_int(pszDup, ppszEnd, iBase);

        if (ppszEnd)
        {

           *ppszEnd = psz + (*ppszEnd - pszDup);

        }

        ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pszDup);

        return i;

     }

  }

  return ansi_to_int(psz, ppszEnd, iBase);

}


CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz)
{

  reverse_memory(psz, string_safe_length(psz));

}


CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz, character_count size)
{

  reverse_memory(psz, size);

}


CLASS_DECL_ACME void ansi_zero_pad(::ansi_character * psz, character_count lenPad)
{

  character_count len = strlen(psz);

  character_count countZero = lenPad - len;

  if (countZero <= 0)
  {

     return;

  }

  for (character_count i = len; i >= 0; i--)
  {

     psz[countZero + i] = psz[i];

  }

  for(character_count i = 0; i < countZero; i++)
  {

     psz[i] = '0';

  }

}


CLASS_DECL_ACME ::ansi_character * ansi_lower(::ansi_character * pch)
{

  ::ansi_character * p = pch;

  while (*p != '\0')
  {

     *p = ansi_char_tolower(*p);

     p++;

  }

  return pch;

}


CLASS_DECL_ACME ::ansi_character * ansi_upper(::ansi_character * pch)
{

  ::ansi_character * p = pch;

  while (*p != '\0')
  {

     *p = ansi_char_toupper(*p);

     p++;

  }

  return pch;

}


CLASS_DECL_ACME const_char_pointer ansi_concatenate_and_duplicate(const_char_pointer psz1, const_char_pointer psz2, int iFree1, int iFree2)
{

  character_count len1 = ansi_length(psz1);

  character_count len2 = ansi_length(psz2);

  character_count len = len1 + len2 + 1;

  auto * psz = (::ansi_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len, nullptr);

  *psz = '\0';

  if (len1 > 0)
  {

     strcat(psz, psz1);

     if (iFree1 > 0)
     {

        ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void *) psz1);

     }
     else if (iFree1 < 0)
     {

        free((void *)psz1);

     }

  }

  if (len2)
  {

     strcat(psz, psz2);

     if (iFree2 > 0)
     {

        ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void *)psz2);

     }
     else if (iFree2 < 0)
     {

        free((void *)psz2);

     }

  }

  return psz;

}


//CLASS_DECL_ACME const_char_pointer ansi_concatenate_duplicate_and_free(const_char_pointer psz1, ::ansi_character * psz2)
//{
//
//   character_count len1 = strlen(psz1);
//
//   character_count len2 = strlen(psz2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::ansi_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(psz, psz1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(psz, psz2);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(psz2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME const_char_pointer ansi_concatenate_free_and_duplicate(::ansi_character * psz1, const_char_pointer psz2)
//{
//
//   character_count len1 = strlen(psz1);
//
//   character_count len2 = strlen(psz2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::ansi_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(psz, psz1);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(psz1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(psz, psz2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME const_char_pointer ansi_concatenat_free_duplicate_and_free(::ansi_character * psz1, ::ansi_character * psz2)
//{
//
//   character_count len1 = strlen(psz1);
//
//   character_count len2 = strlen(psz2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::ansi_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(psz, psz1);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(psz1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(psz, psz2);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(psz2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME void                   ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, int * numargs, int * numchars);



CLASS_DECL_ACME const void * memory_find_memory(const void * src, character_count srclen, const void * find, character_count findlen);



CLASS_DECL_ACME const_char_pointer        wildcard_next_stop(const_char_pointer pszCriteria);

CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const_char_pointer pszCriteria, const_char_pointer pszValue);
CLASS_DECL_ACME int_bool               case_insensitive_wildcard_matches_criteria(const_char_pointer pszCriteria, const_char_pointer pszValue);










