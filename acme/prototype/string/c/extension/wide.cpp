#include "platform.h"

#include <wchar.h>
#include <errno.h>

CLASS_DECL_ACME ::wide_character wide_char_tolower(::i32 i) { return __widetolower(i); }
CLASS_DECL_ACME ::wide_character wide_char_toupper(::i32 i) { return __widetoupper(i); }


CLASS_DECL_ACME ::i32 wide_char_isdigit(::i32 i) { return __widecharisdigit(i); }
CLASS_DECL_ACME ::i32 wide_char_isalpha(::i32 i) { return __widecharisalpha(i); }
CLASS_DECL_ACME ::i32 wide_char_isalnum(::i32 i) { return __widecharisalnum(i); }
CLASS_DECL_ACME ::i32 wide_char_isspace(::i32 i) { return __widecharisspace(i); }


CLASS_DECL_ACME ::i32 wide_char_isxdigit(::i32 i) { return __widecharisxdigit(i); }


CLASS_DECL_ACME const ::wide_character * wide_const_last_char(const ::wide_character * psz)
{

   return ::is_null(psz) ? nullptr : psz + wide_len(psz);

}


CLASS_DECL_ACME ::wide_character * wide_last_char(::wide_character * psz)
{

   return (::wide_character *)wide_const_last_char(psz);

}


CLASS_DECL_ACME ::wide_character * wide_concatenate(::wide_character * psz, const ::wide_character * cat)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cat)) return nullptr;

   return wide_cat(psz, cat);

}


CLASS_DECL_ACME ::wide_character * wide_copy(::wide_character * psz, const ::wide_character * cpy)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   return wide_cpy(psz, cpy);

}


CLASS_DECL_ACME ::wide_character * wide_count_copy(::wide_character * psz, const ::wide_character * cpy, character_count len)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return wide_ncpy(psz, cpy, len);

}


CLASS_DECL_ACME character_count wide_length(const ::wide_character * psz)
{

   if (::is_null(psz)) return 0;

   return wide_len(psz);

}


CLASS_DECL_ACME ::wide_character * wide_duplicate(const ::wide_character * psz)
{

   if (::is_null(psz)) return nullptr;

   auto pszDup = (::wide_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(wide_len(psz) + 1, nullptr);

   wide_cpy(pszDup, psz);

   return pszDup;

}


CLASS_DECL_ACME ::wide_character * wide_count_duplicate(const ::wide_character * psz, character_count len)
{

   if (::is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (::wide_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len + 1, nullptr);

   wide_ncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


CLASS_DECL_ACME const ::wide_character * wide_find_string(const ::wide_character * psz, const ::wide_character * find)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(find)) return nullptr;

   return wide_str(psz, find);

}


CLASS_DECL_ACME const ::wide_character * wide_find_string_case_insensitive(const ::wide_character * psz, const ::wide_character * find)
{

   if (::is_null(psz)) return nullptr;

   auto len = wide_len(find);

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wide_nicmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME const ::wide_character * wide_count_find_string(const ::wide_character * psz, const ::wide_character * find, character_count len)
{

   if (::is_null(psz)) return nullptr;

   if (len > (character_count) wide_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wide_ncmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME const ::wide_character * wide_count_find_string_case_insensitive(const ::wide_character * psz, const ::wide_character * find, character_count len)
{

   if (::is_null(psz)) return nullptr;

   if (len > (character_count) wide_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wide_nicmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME ::i32 wide_compare(const ::wide_character * psz, const ::wide_character * sz2)
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

      return wide_cmp(psz, sz2);

   }

}


CLASS_DECL_ACME ::i32 wide_compare_case_insensitive(const ::wide_character * psz, const ::wide_character * sz2)
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

      return wide_compare_case_insensitive(psz, sz2);

   }

}


CLASS_DECL_ACME ::i32 wide_count_compare(const ::wide_character * psz, const ::wide_character * sz2, character_count len)
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

      return wide_ncmp(psz, sz2, len);

   }

}


CLASS_DECL_ACME ::i32 wide_count_compare_case_insensitive(const ::wide_character * psz, const ::wide_character * sz2, character_count len)
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

      return wide_nicmp(psz, sz2, len);

   }

}


CLASS_DECL_ACME ::i32 wide_collate(const ::wide_character * psz, const ::wide_character * sz2)
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

      return wide_coll(psz, sz2);

   }

}


CLASS_DECL_ACME ::i32 wide_collate_case_insensitive(const ::wide_character * psz, const ::wide_character * sz2)
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

      return wide_collate_case_insensitive(psz, sz2);

   }

}


CLASS_DECL_ACME ::i32 wide_count_collate(const ::wide_character * psz, const ::wide_character * sz2, character_count len)
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

      return wide_ncoll(psz, sz2, len);

   }

}


CLASS_DECL_ACME ::i32 wide_count_collate_case_insensitive(const ::wide_character * psz, const ::wide_character * sz2, character_count len)
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

      return wide_nicoll(psz, sz2, len);

   }

}


CLASS_DECL_ACME const ::wide_character * _wide_scan(const ::wide_character * psz, const ::wide_character * find)
{

   return wide_pbrk((::wide_character *)psz, find);

}


CLASS_DECL_ACME const ::wide_character * wide_scan(const ::wide_character * psz, const ::wide_character * find)
{

   if (::is_empty(psz)) return psz;

   if (::is_empty(find)) return psz;

   return wide_scan(psz, find);

}


//CLASS_DECL_ACME const ::wide_character * wide_token(const ::wide_character * psz, const ::wide_character * pszSeparators)
//{
//
//   return string_token(psz, pszSeparators);
//
//}


//CLASS_DECL_ACME const ::wide_character * _wide_token(const ::wide_character * psz, const ::wide_character * pszSeparators)
//{
//
//   return _string_token(psz, pszSeparators);
//
//}



CLASS_DECL_ACME ::wide_character * wide_first_token(::wide_character * psz, const ::wide_character * delimiters, ::wide_character ** action_context)
{

   return wide_tok_r(psz, delimiters, action_context);

}



CLASS_DECL_ACME ::wide_character * wide_next_token(const ::wide_character * delimiters, ::wide_character ** action_context)
{

   return wide_tok_r(nullptr, delimiters, action_context);


}


CLASS_DECL_ACME ::i32 wide_begins(const ::wide_character * psz, const ::wide_character * prefix)
{

   if (::is_null(psz)) return false;

   if (::is_null(prefix)) return false;

   auto len = wide_len(prefix);

   if (len > wide_len(psz))
   {

      return false;

   }

   return !wide_ncmp(psz, prefix, len);

}


CLASS_DECL_ACME ::i32 wide_begins_case_insensitive(const ::wide_character * psz, const ::wide_character * prefix)
{

   if (::is_null(psz)) return false;

   if (::is_null(prefix)) return false;

   return !wide_nicmp(psz, prefix, wide_len(prefix));

}


CLASS_DECL_ACME const ::wide_character * wide_begins_eat(const ::wide_character * psz, const ::wide_character * prefix)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(prefix)) return nullptr;

   auto len = wide_len(prefix);

   if (wide_ncmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


CLASS_DECL_ACME const ::wide_character * wide_begins_eat_case_insensitive(const ::wide_character * psz, const ::wide_character * prefix)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(prefix)) return nullptr;

   auto len = wide_len(prefix);

   if (wide_nicmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


CLASS_DECL_ACME ::i32 wide_ends(const ::wide_character * psz, const ::wide_character * suffix)
{

   if (::is_null(psz)) return false;

   if (::is_null(suffix)) return false;

   auto len = wide_len(suffix);

   auto end = wide_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wide_ncmp(psz + end, suffix, len);

}


CLASS_DECL_ACME ::i32 wide_ends_case_insensitive(const ::wide_character * psz, const ::wide_character * suffix)
{

   if (::is_null(psz)) return false;

   if (::is_null(suffix)) return false;

   auto len = wide_len(suffix);

   auto end = wide_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wide_nicmp(psz + end, suffix, len);

}


CLASS_DECL_ACME const ::wide_character * wide_find_char(const ::wide_character * psz, ::wide_character ch)
{

   if (::is_null(psz)) return nullptr;

   return wide_chr(psz, ch);

}


CLASS_DECL_ACME const ::wide_character * wide_find_char_reverse(const ::wide_character * psz, ::wide_character ch)
{

   if (::is_null(psz)) return nullptr;

   return wide_rchr(psz, ch);

}


//CLASS_DECL_ACME const ::wide_character * wide_concatenate_and_duplicate(const ::wide_character * psz1, const ::wide_character * psz2);
//CLASS_DECL_ACME const ::wide_character * wide_concatenate_duplicate_and_free(const ::wide_character * psz1, ::wide_character * psz2);


CLASS_DECL_ACME void wide_from_u64_base(::wide_character * sz, ::u64 u, ::i32 iBase, enum_digit_case edigitcase)
{

   wide_character * pend = nullptr;

   __u64towide(u, sz, iBase, edigitcase, pend);

}


CLASS_DECL_ACME void wide_from_i64_base(::wide_character * sz, ::i64 i, ::i32 iBase, enum_digit_case edigitcase)
{

   wide_character * pend = nullptr;

   __i64towide(i, sz, iBase, edigitcase, pend);

}


#ifdef WINDOWS


CLASS_DECL_ACME ::i64 wide_to_i64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

   return __widetoi64(psz, (::wide_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME ::u64 wide_to_u64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

   return __widetou64(psz, (::wide_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME ::i32 wide_to_int(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

   return __widetoi32(psz, (::wide_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME ::u32 wide_to_u32(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

   return __widetou32(psz, (::wide_character **) ppszEnd, iBase);

}
#else


CLASS_DECL_ACME ::i64 wide_to_i64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

   return wcstoll(psz, (::wide_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME ::u64 wide_to_u64(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

   return wcstoull(psz, (::wide_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME ::i32 wide_to_int(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{
   
#ifdef WINDOWS

   return wcstol(psz, (::wide_character **) ppszEnd, iBase);
   
#else
   
   long l = wcstol(psz, (::wide_character **) ppszEnd, iBase);
   
   if(l > INT_MAX)
   {
      
      errno = ERANGE;
      
      return INT_MAX;
      
   }
   else if(l < INT_MIN)
   {
      
      errno = ERANGE;
      
      return INT_MIN;
      
   }

   return (::i32) l;
   
#endif
}


CLASS_DECL_ACME ::u32 wide_to_u32(const ::wide_character * psz, const ::wide_character ** ppszEnd, ::i32 iBase)
{

#ifdef WINDOWS
   
   return wcstoul(psz, (::wide_character **) ppszEnd, iBase);
   
#else

   ulong ul = wcstoul(psz, (::wide_character **) ppszEnd, iBase);

   if(ul > UINT_MAX)
   {
      
      errno = ERANGE;
      
      return UINT_MAX;
      
   }

   return (::u32) ul;
   
#endif

}




#endif


CLASS_DECL_ACME void wide_reverse(::wide_character * psz)
{

   reverse_memory(psz, wide_len(psz));

}

CLASS_DECL_ACME void wide_zero_pad(::wide_character * psz, character_count lenPad)
{

   character_count len = wide_len(psz);

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


CLASS_DECL_ACME ::wide_character * wide_lower(::wide_character * pch)
{

   ::wide_character * p = pch;

   while (*p != '\0')
   {

      *p = wide_char_tolower(*p);

      p++;

   }

   return pch;

}


CLASS_DECL_ACME ::wide_character * wide_upper(::wide_character * pch)
{

   ::wide_character * p = pch;

   while (*p != '\0')
   {

      *p = wide_char_toupper(*p);

      p++;

   }

   return pch;

}


CLASS_DECL_ACME const ::wide_character * wide_concatenate_and_duplicate(const ::wide_character * psz1, const ::wide_character * psz2, ::i32 iFree1, ::i32 iFree2)
{

   character_count len1 = wide_length(psz1);

   character_count len2 = wide_length(psz2);

   character_count len = len1 + len2 + 1;

   auto * psz = (::wide_character *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len, nullptr);

   *psz = '\0';

   if (len1 > 0)
   {

      wide_cat(psz, psz1);

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

      wide_cat(psz, psz2);

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









