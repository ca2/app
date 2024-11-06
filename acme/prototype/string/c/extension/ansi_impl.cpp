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


CLASS_DECL_ACME const ::ansi_character * ansi_const_last_char(const ::ansi_character * psz);

CLASS_DECL_ACME ::ansi_character * ansi_last_char(::ansi_character * psz)
{

  return (::ansi_character *)ansi_const_last_char(psz);

}


CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cat)) return nullptr;

   return ansi_cat(psz, cat);

}



//CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat, strsize n)
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

CLASS_DECL_ACME ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat, strsize n)
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


CLASS_DECL_ACME ::ansi_character * ansi_copy(::ansi_character * psz, const ::ansi_character * cpy)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(cpy)) return nullptr;

  return strcpy(psz, cpy);

}


CLASS_DECL_ACME ::ansi_character * ansi_count_copy(::ansi_character * psz, const ::ansi_character * cpy, strsize len)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(cpy)) return nullptr;

  if (len < 0) return nullptr;

  return strncpy(psz, cpy, len);

}


CLASS_DECL_ACME strsize ansi_length(const ::ansi_character * psz)
{

  if (::is_null(psz)) return 0;

  return strlen(psz);

}


CLASS_DECL_ACME ::ansi_character * ansi_duplicate(const ::ansi_character * psz)
{

  if (::is_null(psz)) return nullptr;

  auto pszDup = (::ansi_character *) ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(strlen(psz) + 1, nullptr);

  strcpy(pszDup, psz);

  return pszDup;

}


CLASS_DECL_ACME ::ansi_character * ansi_count_duplicate(const ::ansi_character * psz, strsize len)
{

  if (::is_null(psz)) return nullptr;

  if (len < 0) return nullptr;

  auto pszDup = (::ansi_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len + 1, nullptr);

  strncpy(pszDup, psz, len);

  pszDup[len] = '\0';

  return pszDup;

}


CLASS_DECL_ACME const ::ansi_character * ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(find)) return nullptr;

  return strstr(psz, find);

}



CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find)
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


CLASS_DECL_ACME const ::ansi_character * ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len)
{

  if (::is_null(psz)) return nullptr;

  if (len > (strsize) strlen(find)) return nullptr;

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


CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len)
{

  if (::is_null(psz)) return nullptr;

  if (len > (strsize)strlen(find)) return nullptr;

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


CLASS_DECL_ACME int ansi_compare(const ::ansi_character * psz, const ::ansi_character * sz2)
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


CLASS_DECL_ACME int case_insensitive_ansi_compare(const ::ansi_character * psz, const ::ansi_character * sz2)
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


CLASS_DECL_ACME int ansi_count_compare(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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


CLASS_DECL_ACME int case_insensitive_ansi_count_compare(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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



CLASS_DECL_ACME int ansi_collate(const ::ansi_character * psz, const ::ansi_character * sz2)
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


CLASS_DECL_ACME int case_insensitive_ansi_collate(const ::ansi_character * psz, const ::ansi_character * sz2)
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


CLASS_DECL_ACME int ansi_count_collate(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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


CLASS_DECL_ACME int case_insensitive_ansi_count_collate(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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


CLASS_DECL_ACME const ::ansi_character * _ansi_scan(const ::ansi_character * psz, const ::ansi_character * find)
{

  return ansi_pbrk((::ansi_character *) psz, find);

}



CLASS_DECL_ACME const ::ansi_character * ansi_scan(const ::ansi_character * psz, const ::ansi_character * find)
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


//CLASS_DECL_ACME const ::ansi_character * ansi_token(const ::ansi_character * psz, const ::ansi_character * pszSeparators)
//{
//
//   return string_find_first_in(psz, pszSeparators);
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * _ansi_find_first_in(const ::ansi_character * psz, const ::ansi_character * pszSeparators)
//{
//
//   return _string_find_first_in(psz, pszSeparators);
//
//}


CLASS_DECL_ACME ::ansi_character * ansi_first_token(::ansi_character * psz, const ::ansi_character * delimiters, ::ansi_character ** action_context)
{

  return ansi_tok_r(psz, delimiters, action_context);

}


CLASS_DECL_ACME ::ansi_character * ansi_next_token(const ::ansi_character * delimiters, ::ansi_character ** action_context)
{

  return ansi_tok_r(nullptr, delimiters, action_context);

}


CLASS_DECL_ACME int ansi_begins(const ::ansi_character * psz, const ::ansi_character * prefix)
{

  if (::is_null(psz)) return false;

  if (::is_null(prefix)) return false;

  strsize len = strlen(prefix);

  if (len > (strsize)strlen(psz))
  {

     return false;

  }

  return !strncmp(psz, prefix, len);

}


CLASS_DECL_ACME int case_insensitive_ansi_begins(const ::ansi_character * psz, const ::ansi_character * prefix)
{

  if (::is_null(psz)) return false;

  if (::is_null(prefix)) return false;

  return !ansi_nicmp(psz, prefix, strlen(prefix));

}


CLASS_DECL_ACME const ::ansi_character * ansi_begins_eat(const ::ansi_character * psz, const ::ansi_character * prefix)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(prefix)) return nullptr;

  strsize len = strlen(prefix);

  if (strncmp(psz, prefix, len))
  {

     return nullptr;

  }

  return psz + len;

}


CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_begins_eat(const ::ansi_character * psz, const ::ansi_character * prefix)
{

  if (::is_null(psz)) return nullptr;

  if (::is_null(prefix)) return nullptr;

  strsize len = strlen(prefix);

  if (ansi_nicmp(psz, prefix, len))
  {

     return nullptr;

  }

  return psz + len;

}


CLASS_DECL_ACME int ansi_ends(const ::ansi_character * psz, const ::ansi_character * suffix)
{

  if (::is_null(psz)) return false;

  if (::is_null(suffix)) return false;

  strsize len = strlen(suffix);

  strsize end = strlen(psz) - len;

  if(end < 0)
  {

     return false;

  }

  return !strncmp(psz + end, suffix, len);

}


CLASS_DECL_ACME int case_insensitive_ansi_ends(const ::ansi_character * psz, const ::ansi_character * suffix)
{

  if (::is_null(psz)) return false;

  if (::is_null(suffix)) return false;

  strsize len = strlen(suffix);

  strsize end = strlen(psz) - len;

  if (end < 0)
  {

     return false;

  }

  return !ansi_nicmp(psz + end, suffix, len);

}


CLASS_DECL_ACME const ::ansi_character * ansi_find_char(const ::ansi_character * psz, ::ansi_character ch)
{

  if (::is_null(psz)) return nullptr;

  return strchr(psz, ch);

}


CLASS_DECL_ACME const ::ansi_character * ansi_find_char_reverse(const ::ansi_character * psz, ::ansi_character ch)
{

  if (::is_null(psz)) return nullptr;

  return strrchr(psz, ch);

}


//CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2);
//CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_duplicate_and_free(const ::ansi_character * psz1, ::ansi_character * psz2);


CLASS_DECL_ACME void ansi_from_u64(::ansi_character * sz, u64 u, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __u64toansi(u, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME void ansi_from_i64(::ansi_character * sz, i64 i, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __i64toansi(i, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME void ansi_from_u32(::ansi_character * sz, unsigned int u, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __u64toansi(u, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME void ansi_from_i32(::ansi_character * sz, int i, int iBase, enum_digit_case edigitcase)
{

  ::ansi_character * end;

  __i64toansi(i, sz, iBase, edigitcase, end);

}


CLASS_DECL_ACME i64 ansi_count_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase, strsize srclen)
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

        auto i = ansi_to_i64(pszDup, ppszEnd, iBase);

        if (ppszEnd)
        {

           *ppszEnd = (::ansi_character *)psz + (*ppszEnd - pszDup);

        }

        ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pszDup);

        return i;

     }

  }

  return ansi_to_i64(psz, ppszEnd, iBase);

}


CLASS_DECL_ACME int ansi_count_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase, strsize srclen)
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

        auto i = ansi_to_i32(pszDup, ppszEnd, iBase);

        if (ppszEnd)
        {

           *ppszEnd = psz + (*ppszEnd - pszDup);

        }

        ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pszDup);

        return i;

     }

  }

  return ansi_to_i32(psz, ppszEnd, iBase);

}


CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz)
{

  reverse_memory(psz, string_safe_length(psz));

}


CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz, strsize size)
{

  reverse_memory(psz, size);

}


CLASS_DECL_ACME void ansi_zero_pad(::ansi_character * psz, strsize lenPad)
{

  strsize len = strlen(psz);

  strsize countZero = lenPad - len;

  if (countZero <= 0)
  {

     return;

  }

  for (strsize i = len; i >= 0; i--)
  {

     psz[countZero + i] = psz[i];

  }

  for(strsize i = 0; i < countZero; i++)
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


CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2, int iFree1, int iFree2)
{

  strsize len1 = ansi_length(psz1);

  strsize len2 = ansi_length(psz2);

  strsize len = len1 + len2 + 1;

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


//CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_duplicate_and_free(const ::ansi_character * psz1, ::ansi_character * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
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



//CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_free_and_duplicate(::ansi_character * psz1, const ::ansi_character * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
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



//CLASS_DECL_ACME const ::ansi_character * ansi_concatenat_free_duplicate_and_free(::ansi_character * psz1, ::ansi_character * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
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



CLASS_DECL_ACME const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen);



CLASS_DECL_ACME const ::ansi_character *       wildcard_next_stop(const ::ansi_character * pszCriteria);

CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
CLASS_DECL_ACME int_bool               case_insensitive_wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);










