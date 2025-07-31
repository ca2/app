#include "framework.h"


CLASS_DECL_ACME ::wd16_character wd16_char_tolower(int i) { return __wd16tolower(i); }
CLASS_DECL_ACME ::wd16_character wd16_char_toupper(int i) { return __wd16toupper(i); }


CLASS_DECL_ACME int wd16_char_isdigit(int i) { return __wd16charisdigit(i); }
CLASS_DECL_ACME int wd16_char_isalpha(int i) { return __wd16charisalpha(i); }
CLASS_DECL_ACME int wd16_char_isalnum(int i) { return __wd16charisalnum(i); }
CLASS_DECL_ACME int wd16_char_isspace(int i) { return __wd16charisspace(i); }


CLASS_DECL_ACME int wd16_char_isxdigit(int i) { return __wd16charisxdigit(i); }



CLASS_DECL_ACME const ::wd16_character * wd16_const_last_char(const ::wd16_character * psz)
{

   return ::is_null(scopedstr) ? nullptr : psz + wd16_len(scopedstr);

}


CLASS_DECL_ACME ::wd16_character * wd16_last_char(::wd16_character * psz)
{

   return (::wd16_character *)wd16_const_last_char(scopedstr);

}


CLASS_DECL_ACME ::wd16_character * wd16_concatenate(::wd16_character * psz, const ::wd16_character * cat)
{

   if (::is_null(scopedstr)) return nullptr;

   if (::is_null(cat)) return nullptr;

   return wd16_cat(scopedstr, cat);

}


CLASS_DECL_ACME ::wd16_character * wd16_copy(::wd16_character * psz, const ::wd16_character * cpy)
{

   if (::is_null(scopedstr)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   return wd16_cpy(scopedstr, cpy);

}


CLASS_DECL_ACME ::wd16_character * wd16_count_copy(::wd16_character * psz, const ::wd16_character * cpy, character_count len)
{

   if (::is_null(scopedstr)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return wd16_ncpy(scopedstr, cpy, len);

}


CLASS_DECL_ACME character_count wd16_length(const ::wd16_character * psz)
{

   if (::is_null(scopedstr)) return 0;

   return wd16_len(scopedstr);

}


CLASS_DECL_ACME ::wd16_character * wd16_duplicate(const ::wd16_character * psz)
{

   if (::is_null(scopedstr)) return nullptr;

   auto pszDup = (::wd16_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(wd16_len(scopedstr) + 1, nullptr);

   wd16_cpy(scopedstrDup, psz);

   return pszDup;

}


CLASS_DECL_ACME ::wd16_character * wd16_count_duplicate(const ::wd16_character * psz, character_count len)
{

   if (::is_null(scopedstr)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (::wd16_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len + 1, nullptr);

   wd16_ncpy(scopedstrDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


CLASS_DECL_ACME const ::wd16_character * wd16_find_string(const ::wd16_character * psz, const ::wd16_character * find)
{

   if (::is_null(scopedstr)) return nullptr;

   if (::is_null(find)) return nullptr;

   return wd16_str(scopedstr, find);

}


CLASS_DECL_ACME const ::wd16_character * wd16_find_string_case_insensitive(const ::wd16_character * psz, const ::wd16_character * find)
{

   if (::is_null(scopedstr)) return nullptr;

   auto len = wd16_len(find);

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd16_nicmp(scopedstr, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME const ::wd16_character * wd16_count_find_string(const ::wd16_character * psz, const ::wd16_character * find, character_count len)
{

   if (::is_null(scopedstr)) return nullptr;

   if (len > (character_count) wd16_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd16_ncmp(scopedstr, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME const ::wd16_character * wd16_count_find_string_case_insensitive(const ::wd16_character * psz, const ::wd16_character * find, character_count len)
{

   if (::is_null(scopedstr)) return nullptr;

   if (len > (character_count) wd16_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd16_nicmp(scopedstr, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME int wd16_compare(const ::wd16_character * psz, const ::wd16_character * sz2)
{

   if (::is_null(scopedstr))
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

      return wd16_cmp(scopedstr, sz2);

   }

}


CLASS_DECL_ACME int wd16_compare_case_insensitive(const ::wd16_character * psz, const ::wd16_character * sz2)
{

   if (::is_null(scopedstr))
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

      return wd16_compare_case_insensitive(scopedstr, sz2);

   }

}


CLASS_DECL_ACME int wd16_count_compare(const ::wd16_character * psz, const ::wd16_character * sz2, character_count len)
{

   if (len < 0)
   {

      return 0;

   }

   if (::is_null(scopedstr))
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

      return wd16_ncmp(scopedstr, sz2, len);

   }

}


CLASS_DECL_ACME int wd16_count_compare_case_insensitive(const ::wd16_character * psz, const ::wd16_character * sz2, character_count len)
{

   if (len < 0)
   {

      return 0;

   }

   if (::is_null(scopedstr))
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

      return wd16_nicmp(scopedstr, sz2, len);

   }

}


CLASS_DECL_ACME int wd16_collate(const ::wd16_character * psz, const ::wd16_character * sz2)
{

   if (::is_null(scopedstr))
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

      return wd16_coll(scopedstr, sz2);

   }

}


CLASS_DECL_ACME int wd16_collate_case_insensitive(const ::wd16_character * psz, const ::wd16_character * sz2)
{

   if (::is_null(scopedstr))
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

      return wd16_collate_case_insensitive(scopedstr, sz2);

   }

}


CLASS_DECL_ACME int wd16_count_collate(const ::wd16_character * psz, const ::wd16_character * sz2, character_count len)
{

   if (len < 0)
   {

      return 0;

   }

   if (::is_null(scopedstr))
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

      return wd16_ncoll(scopedstr, sz2, len);

   }

}


CLASS_DECL_ACME int wd16_count_collate_case_insensitive(const ::wd16_character * psz, const ::wd16_character * sz2, character_count len)
{

   if (len < 0)
   {

      return 0;

   }

   if (::is_null(scopedstr))
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

      return wd16_nicoll(scopedstr, sz2, len);

   }

}


CLASS_DECL_ACME const ::wd16_character * _wd16_scan(const ::wd16_character * psz, const ::wd16_character * find)
{

   return wd16_pbrk((::wd16_character *)psz, find);

}



CLASS_DECL_ACME const ::wd16_character * wd16_scan(const ::wd16_character * psz, const ::wd16_character * find)
{

   if (::is_empty(scopedstr)) return psz;

   if (::is_empty(find)) return psz;

   return wd16_scan(scopedstr, find);

}


//CLASS_DECL_ACME const ::wd16_character * wd16_token(const ::wd16_character * psz, const ::wd16_character * pszSeparators)
//{
//
//   return string_token(scopedstr, pszSeparators);
//
//}
//
//
//CLASS_DECL_ACME const ::wd16_character * _wd16_token(const ::wd16_character * psz, const ::wd16_character * pszSeparators)
//{
//
//   return _string_token(scopedstr, pszSeparators);
//
//}



CLASS_DECL_ACME ::wd16_character * wd16_first_token(::wd16_character * psz, const ::wd16_character * delimiters, ::wd16_character ** action_context)
{

   return wd16_tok_r(scopedstr, delimiters, action_context);

}



CLASS_DECL_ACME ::wd16_character * wd16_next_token(const ::wd16_character * delimiters, ::wd16_character ** action_context)
{

   return wd16_tok_r(nullptr, delimiters, action_context);

}


CLASS_DECL_ACME int wd16_begins(const ::wd16_character * psz, const ::wd16_character * prefix)
{

   if (::is_null(scopedstr)) return false;

   if (::is_null(prefix)) return false;

   auto len = wd16_len(prefix);

   if (len > wd16_len(scopedstr))
   {

      return false;

   }

   return !wd16_ncmp(scopedstr, prefix, len);

}


CLASS_DECL_ACME int wd16_begins_case_insensitive(const ::wd16_character * psz, const ::wd16_character * prefix)
{

   if (::is_null(scopedstr)) return false;

   if (::is_null(prefix)) return false;

   return !wd16_nicmp(scopedstr, prefix, wd16_len(prefix));

}


CLASS_DECL_ACME const ::wd16_character * wd16_begins_eat(const ::wd16_character * psz, const ::wd16_character * prefix)
{

   if (::is_null(scopedstr)) return nullptr;

   if (::is_null(prefix)) return nullptr;

   auto len = wd16_len(prefix);

   if (wd16_ncmp(scopedstr, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


CLASS_DECL_ACME const ::wd16_character * wd16_begins_eat_case_insensitive(const ::wd16_character * psz, const ::wd16_character * prefix)
{

   if (::is_null(scopedstr)) return nullptr;

   if (::is_null(prefix)) return nullptr;

   auto len = wd16_len(prefix);

   if (wd16_nicmp(scopedstr, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


CLASS_DECL_ACME int wd16_ends(const ::wd16_character * psz, const ::wd16_character * suffix)
{

   if (::is_null(scopedstr)) return false;

   if (::is_null(suffix)) return false;

   auto len = wd16_len(suffix);

   auto end = wd16_len(scopedstr) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd16_ncmp(scopedstr + end, suffix, len);

}


CLASS_DECL_ACME int wd16_ends_case_insensitive(const ::wd16_character * psz, const ::wd16_character * suffix)
{

   if (::is_null(scopedstr)) return false;

   if (::is_null(suffix)) return false;

   auto len = wd16_len(suffix);

   auto end = wd16_len(scopedstr) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd16_nicmp(scopedstr + end, suffix, len);

}


CLASS_DECL_ACME const ::wd16_character * wd16_find_char(const ::wd16_character * psz, ::wd16_character ch)
{

   if (::is_null(scopedstr)) return nullptr;

   return wd16_chr(scopedstr, ch);

}


CLASS_DECL_ACME const ::wd16_character * wd16_find_char_reverse(const ::wd16_character * psz, ::wd16_character ch)
{

   if (::is_null(scopedstr)) return nullptr;

   return wd16_rchr(scopedstr, ch);

}


//CLASS_DECL_ACME const ::wd16_character * wd16_concatenate_and_duplicate(const ::wd16_character * psz1, const ::wd16_character * psz2);
//CLASS_DECL_ACME const ::wd16_character * wd16_concatenate_duplicate_and_free(const ::wd16_character * psz1, ::wd16_character * psz2);


CLASS_DECL_ACME void wd16_from_u64_base(::wd16_character * sz, unsigned long long u, int iBase, enum_digit_case edigitcase)
{

   wd16_character * pend = nullptr;

   __u64towd16(u, sz, iBase, edigitcase, pend);

}


CLASS_DECL_ACME void wd16_from_long_long_base(::wd16_character * sz, long long i, int iBase, enum_digit_case edigitcase)
{

   wd16_character * pend = nullptr;

   __long_longtowd16(i, sz, iBase, edigitcase, pend);

}


#ifdef WINDOWS


CLASS_DECL_ACME long long wd16_to_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return wcstoll(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME unsigned long long wd16_to_unsigned_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return wcstoull(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME int wd16_to_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return wcstol(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME unsigned int wd16_to_unsigned_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return wcstoul(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


#else



CLASS_DECL_ACME long long wd16_to_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return __wd16toi64(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME unsigned long long wd16_to_unsigned_long_long(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return __wd16tou64(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME int wd16_to_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return __wd16toi32(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME unsigned int wd16_to_unsigned_int(const ::wd16_character * psz, const ::wd16_character ** ppszEnd, int iBase)
{

   return __wd16tou32(scopedstr, (::wd16_character **) ppszEnd, iBase);

}


#endif



CLASS_DECL_ACME void wd16_reverse(::wd16_character * psz)
{

   reverse_memory(scopedstr, wd16_len(scopedstr));

}

CLASS_DECL_ACME void wd16_zero_pad(::wd16_character * psz, character_count lenPad)
{

   character_count len = wd16_len(scopedstr);

   character_count countZero = lenPad - len;

   if (countZero <= 0)
   {

      return;

   }

   character_count end = len - 1;

   character_count endFinal = len + countZero;

   psz[endFinal + 1] = '\0';

   for (; end >= 0; end--, endFinal--)
   {

      psz[endFinal] = psz[end];

   }

   for (; endFinal >= 0; endFinal--)
   {

      psz[endFinal] = '0';

   }

}


CLASS_DECL_ACME ::wd16_character * wd16_lower(::wd16_character * pch)
{

   ::wd16_character * p = pch;

   while (*p != '\0')
   {

      *p = wd16_char_tolower(*p);

      p++;

   }

   return pch;

}


CLASS_DECL_ACME ::wd16_character * wd16_upper(::wd16_character * pch)
{

   ::wd16_character * p = pch;

   while (*p != '\0')
   {

      *p = wd16_char_toupper(*p);

      p++;

   }

   return pch;

}


CLASS_DECL_ACME const ::wd16_character * wd16_concatenate_and_duplicate(const ::wd16_character * psz1, const ::wd16_character * psz2, int iFree1, int iFree2)
{

   character_count len1 = wd16_length(scopedstr1);

   character_count len2 = wd16_length(scopedstr2);

   character_count len = len1 + len2 + 1;

   auto * psz = (::wd16_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len, nullptr);

   *psz = '\0';

   if (len1 > 0)
   {

      wd16_cat(scopedstr, psz1);

      if (iFree1 > 0)
      {

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void *)psz1);

      }
      else if (iFree1 < 0)
      {

         free((void *)psz1);

      }

   }

   if (len2)
   {

      wd16_cat(scopedstr, psz2);

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


//CLASS_DECL_ACME const ::wd16_character * wd16_concatenate_duplicate_and_free(const ::wd16_character * psz1, ::wd16_character * psz2)
//{
//
//   character_count len1 = wd16_len(scopedstr1);
//
//   character_count len2 = wd16_len(scopedstr2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::wd16_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(scopedstr, psz1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(scopedstr, psz2);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME const ::wd16_character * wd16_concatenate_free_and_duplicate(::wd16_character * psz1, const ::wd16_character * psz2)
//{
//
//   character_count len1 = wd16_len(scopedstr1);
//
//   character_count len2 = wd16_len(scopedstr2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::wd16_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(scopedstr, psz1);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(scopedstr, psz2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME const ::wd16_character * wd16_concatenat_free_duplicate_and_free(::wd16_character * psz1, ::wd16_character * psz2)
//{
//
//   character_count len1 = wd16_len(scopedstr1);
//
//   character_count len2 = wd16_len(scopedstr2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::wd16_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(scopedstr, psz1);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(scopedstr, psz2);
//
//      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME void                   ansi_parse_command_line(::wd16_character * cmdstart, ::wd16_character ** argv, ::wd16_character * args, int * numargs, int * numchars);



//CLASS_DECL_ACME const void * memory_find_memory(const void * src, character_count srclen, const void * find, character_count findlen)
//{
//
//   if (::is_null(src)) return nullptr;
//
//   if (srclen <= 0) return nullptr;
//
//   if (::is_null(find)) return src;
//
//   if (findlen <= 0) return src;
//
//#ifdef WINDOWS
//
//   for (const unsigned char * p = (const unsigned char *)src; srclen >= findlen; p++, srclen--)
//   {
//
//      if (!memcmp(p, find, findlen))
//      {
//
//         return p;
//
//      }
//
//   }
//
//   return nullptr;
//
//#else
//
//   return memory_find(src, srclen, find, findlen);
//
//#endif
//
//}



//CLASS_DECL_ACME ::wd16_character * wd16_next_token(::wd16_character * s1, const ::wd16_character * s2, ::wd16_character ** lasts);

//CLASS_DECL_ACME const ::wd16_character * wildcard_next_stop(const ::wd16_character * pszCriteria);
//
//CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const ::wd16_character * pszCriteria, const ::wd16_character * pszValue);
//CLASS_DECL_ACME int_bool               wildcard_matches_criteria_case_insensitive(const ::wd16_character * pszCriteria, const ::wd16_character * pszValue);


//CLASS_DECL_ACME unichar * wd16_concatenate(unichar * dest, const unichar * cat);
//CLASS_DECL_ACME unichar * wd16_copy(unichar * dest, const unichar * src);
//CLASS_DECL_ACME unichar * wd16_count_copy(unichar * dest, const unichar * src, character_count n);
//CLASS_DECL_ACME int wd16_char_is_alnum(int wch);
//CLASS_DECL_ACME count wd16_length(const unichar * pwsz);
//CLASS_DECL_ACME count wd16_32len_dup(const wchar_t * pwsz);
//CLASS_DECL_ACME unichar * wd16_find_char(const unichar * sz, unichar ch);
//CLASS_DECL_ACME int wd16_compare(const unichar * psz, const unichar * sz2);
//CLASS_DECL_ACME int wd16_compare_case_insensitive(const unichar * psz, const unichar * sz2);
//CLASS_DECL_ACME ::wd16_character * wd16_find_string_case_insensitive(const unichar * src, const unichar * find);

//CLASS_DECL_ACME void wd16_from_u64_base(unichar * sz, unsigned long long i, int iBase);
//CLASS_DECL_ACME void wd16_from_int_base(unichar * sz, long long i, int iBase);


//CLASS_DECL_ACME void l64toa_dup(::wd16_character * sz, long long i, long long iBase);
//CLASS_DECL_ACME void i64toa_dup(::wd16_character * sz, long long i);
//CLASS_DECL_ACME void wd16_reverse(unichar * sz);
//CLASS_DECL_ACME void w_zero_pad(::wd16_character * sz, character_count iPad);


//CLASS_DECL_ACME unichar wd16_char_lower(int wch);
//CLASS_DECL_ACME unichar wd16_char_upper(int wch);

//CLASS_DECL_ACME errno_t wd16_lower(unichar * sz, character_count size);
//CLASS_DECL_ACME errno_t wd16_upper(unichar * sz, character_count size);

//CLASS_DECL_ACME int wd16_char_isalpha(int ch);
//CLASS_DECL_ACME int wd16_char_isdigit(int ch);
//CLASS_DECL_ACME int wd16_char_isspace(int ch);


//CLASS_DECL_ACME void __cdecl wparse_cmdline(WCHAR *cmdstart, WCHAR **argv, WCHAR *args, int * numargs, int * numchars);

//CLASS_DECL_ACME void ansi_to_wd16(unichar * pwsz, const ::wd16_character * psz);
//CLASS_DECL_ACME unichar * utf8_to_unicode(const ::wd16_character * psz);
//CLASS_DECL_ACME ::wd16_character * unicode_to_utf8(const unichar * psz);


//namespace str
//{
//
//
//   namespace ch
//   {

//
//      CLASS_DECL_ACME int unicode_parse_unicode(const ::wd16_character *& input)
//      {
//
//         if (input[0] == 0)
//         {
//
//            return 0;
//
//         }
//
//         if (utf16_is_2nd_surrogate(input[0]))
//         {
//
//            return -1;
//
//         }
//         else if (utf16_is_1st_surrogate(input[0]))
//         {
//
//            if (utf16_is_2nd_surrogate(input[1]))
//            {
//
//               auto iUnicode = utf16_surrogate_to_utf32(input[0], input[1]);
//
//               input+=2;
//
//               return iUnicode;
//
//            }
//            else
//            {
//
//               return -1;
//
//            }
//
//         }
//         else
//         {
//
//            auto iUnicode = input[0];
//
//            input++;
//
//            return iUnicode;
//
//         }
//
//      }
//
//
//      CLASS_DECL_ACME int unicode_index_length(const ::wd16_character * input, int & len)
//      {
//
//         if (input[0] == 0)
//         {
//
//            len = 0;
//
//            return 0;
//
//         }
//
//         if (utf16_is_2nd_surrogate(input[0]))
//         {
//
//            len = -1;
//
//            return -1;
//
//         }
//         else if (utf16_is_1st_surrogate(input[0]))
//         {
//
//            if (utf16_is_2nd_surrogate(input[1]))
//            {
//
//               len = 2;
//
//               return utf16_surrogate_to_utf32(input[0], input[1]);
//
//            }
//            else
//            {
//
//               len = -1;
//
//               return -1;
//
//            }
//
//         }
//         else
//         {
//
//            len = 1;
//
//            return input[0];
//
//         }
//
//      }
//
//
////   } // namespace ch
//
//} // namespace str
//
//
