#include "framework.h"

#include <wchar.h>
#include <errno.h>

CLASS_DECL_ACME ::wd32_character wd32_char_tolower(i32 i) { return __wd32tolower(i); }
CLASS_DECL_ACME ::wd32_character wd32_char_toupper(i32 i) { return __wd32toupper(i); }


CLASS_DECL_ACME i32 wd32_char_isdigit(i32 i) { return __wd32charisdigit(i); }
CLASS_DECL_ACME i32 wd32_char_isalpha(i32 i) { return __wd32charisalpha(i); }
CLASS_DECL_ACME i32 wd32_char_isalnum(i32 i) { return __wd32charisalnum(i); }
CLASS_DECL_ACME i32 wd32_char_isspace(i32 i) { return __wd32charisspace(i); }


CLASS_DECL_ACME i32 wd32_char_is_hexadecimal(i32 i) { return __wd32charishexadecimal(i); }


CLASS_DECL_ACME const ::wd32_character * wd32_const_last_char(const ::wd32_character * psz)
{

   return ::is_null(psz) ? nullptr : psz + wd32_len(psz);

}


CLASS_DECL_ACME ::wd32_character * wd32_last_char(::wd32_character * psz)
{

   return (::wd32_character *)wd32_const_last_char(psz);

}


CLASS_DECL_ACME ::wd32_character * wd32_concatenate(::wd32_character * psz, const ::wd32_character * cat)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cat)) return nullptr;

   return wd32_cat(psz, cat);

}


CLASS_DECL_ACME ::wd32_character * wd32_copy(::wd32_character * psz, const ::wd32_character * cpy)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   return wd32_cpy(psz, cpy);

}


CLASS_DECL_ACME ::wd32_character * wd32_count_copy(::wd32_character * psz, const ::wd32_character * cpy, strsize len)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return wd32_ncpy(psz, cpy, len);

}


CLASS_DECL_ACME strsize wd32_length(const ::wd32_character * psz)
{

   if (::is_null(psz)) return 0;

   return wd32_len(psz);

}


CLASS_DECL_ACME ::wd32_character * wd32_duplicate(const ::wd32_character * psz)
{

   if (::is_null(psz)) return nullptr;

   auto pszDup = (::wd32_character *)memory_allocate(wd32_len(psz) + 1);

   wd32_cpy(pszDup, psz);

   return pszDup;

}


CLASS_DECL_ACME ::wd32_character * wd32_count_duplicate(const ::wd32_character * psz, strsize len)
{

   if (::is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (::wd32_character *)memory_allocate(len + 1);

   wd32_ncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


CLASS_DECL_ACME const ::wd32_character * wd32_find_string(const ::wd32_character * psz, const ::wd32_character * find)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(find)) return nullptr;

   return wd32_str(psz, find);

}


CLASS_DECL_ACME const ::wd32_character * wd32_find_string_case_insensitive(const ::wd32_character * psz, const ::wd32_character * find)
{

   if (::is_null(psz)) return nullptr;

   auto len = wd32_len(find);

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd32_nicmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME const ::wd32_character * wd32_count_find_string(const ::wd32_character * psz, const ::wd32_character * find, strsize len)
{

   if (::is_null(psz)) return nullptr;

   if (len > (strsize) wd32_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd32_ncmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME const ::wd32_character * wd32_count_find_string_case_insensitive(const ::wd32_character * psz, const ::wd32_character * find, strsize len)
{

   if (::is_null(psz)) return nullptr;

   if (len > (strsize) wd32_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd32_nicmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


CLASS_DECL_ACME i32 wd32_compare(const ::wd32_character * psz, const ::wd32_character * sz2)
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

      return wd32_cmp(psz, sz2);

   }

}


CLASS_DECL_ACME i32 wd32_compare_case_insensitive(const ::wd32_character * psz, const ::wd32_character * sz2)
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

      return wd32_compare_case_insensitive(psz, sz2);

   }

}


CLASS_DECL_ACME i32 wd32_count_compare(const ::wd32_character * psz, const ::wd32_character * sz2, strsize len)
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

      return wd32_ncmp(psz, sz2, len);

   }

}


CLASS_DECL_ACME i32 wd32_count_compare_case_insensitive(const ::wd32_character * psz, const ::wd32_character * sz2, strsize len)
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

      return wd32_nicmp(psz, sz2, len);

   }

}


CLASS_DECL_ACME i32 wd32_collate(const ::wd32_character * psz, const ::wd32_character * sz2)
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

      return wd32_coll(psz, sz2);

   }

}


CLASS_DECL_ACME i32 wd32_collate_case_insensitive(const ::wd32_character * psz, const ::wd32_character * sz2)
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

      return wd32_collate_case_insensitive(psz, sz2);

   }

}


CLASS_DECL_ACME i32 wd32_count_collate(const ::wd32_character * psz, const ::wd32_character * sz2, strsize len)
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

      return wd32_ncoll(psz, sz2, len);

   }

}


CLASS_DECL_ACME i32 wd32_count_collate_case_insensitive(const ::wd32_character * psz, const ::wd32_character * sz2, strsize len)
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

      return wd32_nicoll(psz, sz2, len);

   }

}


CLASS_DECL_ACME const ::wd32_character * _wd32_scan(const ::wd32_character * psz, const ::wd32_character * find)
{

   return wd32_pbrk((::wd32_character *)psz, find);

}


CLASS_DECL_ACME const ::wd32_character * wd32_scan(const ::wd32_character * psz, const ::wd32_character * find)
{

   if (::is_empty(psz)) return psz;

   if (::is_empty(find)) return psz;

   return wd32_scan(psz, find);

}


//CLASS_DECL_ACME const ::wd32_character * wd32_token(const ::wd32_character * psz, const ::wd32_character * pszSeparators)
//{
//
//   return string_token(psz, pszSeparators);
//
//}


//CLASS_DECL_ACME const ::wd32_character * _wd32_token(const ::wd32_character * psz, const ::wd32_character * pszSeparators)
//{
//
//   return _string_token(psz, pszSeparators);
//
//}



CLASS_DECL_ACME ::wd32_character * wd32_first_token(::wd32_character * psz, const ::wd32_character * delimiters, ::wd32_character ** action_context)
{

   return wd32_tok_r(psz, delimiters, action_context);

}



CLASS_DECL_ACME ::wd32_character * wd32_next_token(const ::wd32_character * delimiters, ::wd32_character ** action_context)
{

   return wd32_tok_r(nullptr, delimiters, action_context);


}


CLASS_DECL_ACME i32 wd32_begins(const ::wd32_character * psz, const ::wd32_character * prefix)
{

   if (::is_null(psz)) return false;

   if (::is_null(prefix)) return false;

   auto len = wd32_len(prefix);

   if (len > wd32_len(psz))
   {

      return false;

   }

   return !wd32_ncmp(psz, prefix, len);

}


CLASS_DECL_ACME i32 wd32_begins_case_insensitive(const ::wd32_character * psz, const ::wd32_character * prefix)
{

   if (::is_null(psz)) return false;

   if (::is_null(prefix)) return false;

   return !wd32_nicmp(psz, prefix, wd32_len(prefix));

}


CLASS_DECL_ACME const ::wd32_character * wd32_begins_eat(const ::wd32_character * psz, const ::wd32_character * prefix)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(prefix)) return nullptr;

   auto len = wd32_len(prefix);

   if (wd32_ncmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


CLASS_DECL_ACME const ::wd32_character * wd32_begins_eat_case_insensitive(const ::wd32_character * psz, const ::wd32_character * prefix)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(prefix)) return nullptr;

   auto len = wd32_len(prefix);

   if (wd32_nicmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


CLASS_DECL_ACME i32 wd32_ends(const ::wd32_character * psz, const ::wd32_character * suffix)
{

   if (::is_null(psz)) return false;

   if (::is_null(suffix)) return false;

   auto len = wd32_len(suffix);

   auto end = wd32_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd32_ncmp(psz + end, suffix, len);

}


CLASS_DECL_ACME i32 wd32_ends_case_insensitive(const ::wd32_character * psz, const ::wd32_character * suffix)
{

   if (::is_null(psz)) return false;

   if (::is_null(suffix)) return false;

   auto len = wd32_len(suffix);

   auto end = wd32_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd32_nicmp(psz + end, suffix, len);

}


CLASS_DECL_ACME const ::wd32_character * wd32_find_char(const ::wd32_character * psz, ::wd32_character ch)
{

   if (::is_null(psz)) return nullptr;

   return wd32_chr(psz, ch);

}


CLASS_DECL_ACME const ::wd32_character * wd32_find_char_reverse(const ::wd32_character * psz, ::wd32_character ch)
{

   if (::is_null(psz)) return nullptr;

   return wd32_rchr(psz, ch);

}


//CLASS_DECL_ACME const ::wd32_character * wd32_concatenate_and_duplicate(const ::wd32_character * psz1, const ::wd32_character * psz2);
//CLASS_DECL_ACME const ::wd32_character * wd32_concatenate_duplicate_and_free(const ::wd32_character * psz1, ::wd32_character * psz2);


CLASS_DECL_ACME void wd32_from_u64_base(::wd32_character * sz, u64 u, i32 iBase, enum_digit_case edigitcase)
{

   wd32_character * pend = nullptr;

   __u64towd32(u, sz, iBase, edigitcase, pend);

}


CLASS_DECL_ACME void wd32_from_i64_base(::wd32_character * sz, i64 i, i32 iBase, enum_digit_case edigitcase)
{

   wd32_character * pend = nullptr;

   __i64towd32(i, sz, iBase, edigitcase, pend);

}


#ifdef WINDOWS


CLASS_DECL_ACME i64 wd32_to_i64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

   return __wd32toi64(psz, (::wd32_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME u64 wd32_to_u64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

   return __wd32tou64(psz, (::wd32_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME i32 wd32_to_i32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

   return __wd32toi32(psz, (::wd32_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME u32 wd32_to_u32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

   return __wd32tou32(psz, (::wd32_character **) ppszEnd, iBase);

}
#else


CLASS_DECL_ACME i64 wd32_to_i64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

   return wcstoll(psz, (::wd32_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME u64 wd32_to_u64(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

   return wcstoull(psz, (::wd32_character **) ppszEnd, iBase);

}


CLASS_DECL_ACME i32 wd32_to_i32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{
   
#ifdef WINDOWS

   return wcstol(psz, (::wd32_character **) ppszEnd, iBase);
   
#else
   
   long l = wcstol(psz, (::wd32_character **) ppszEnd, iBase);
   
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


CLASS_DECL_ACME u32 wd32_to_u32(const ::wd32_character * psz, const ::wd32_character ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS
   
   return wcstoul(psz, (::wd32_character **) ppszEnd, iBase);
   
#else

   unsigned long ul = wcstoul(psz, (::wd32_character **) ppszEnd, iBase);

   if(ul > UINT_MAX)
   {
      
      errno = ERANGE;
      
      return UINT_MAX;
      
   }

   return (::u32) ul;
   
#endif

}




#endif


CLASS_DECL_ACME void wd32_reverse(::wd32_character * psz)
{

   reverse_memory(psz, wd32_len(psz));

}

CLASS_DECL_ACME void wd32_zero_pad(::wd32_character * psz, strsize lenPad)
{

   strsize len = wd32_len(psz);

   strsize countZero = lenPad - len;

   if (countZero <= 0)
   {

      return;

   }

   strsize end = len - 1;

   strsize endFinal = len + countZero;

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


CLASS_DECL_ACME ::wd32_character * wd32_lower(::wd32_character * pch)
{

   ::wd32_character * p = pch;

   while (*p != '\0')
   {

      *p = wd32_char_tolower(*p);

      p++;

   }

   return pch;

}


CLASS_DECL_ACME ::wd32_character * wd32_upper(::wd32_character * pch)
{

   ::wd32_character * p = pch;

   while (*p != '\0')
   {

      *p = wd32_char_toupper(*p);

      p++;

   }

   return pch;

}


CLASS_DECL_ACME const ::wd32_character * wd32_concatenate_and_duplicate(const ::wd32_character * psz1, const ::wd32_character * psz2, int iFree1, int iFree2)
{

   strsize len1 = wd32_length(psz1);

   strsize len2 = wd32_length(psz2);

   strsize len = len1 + len2 + 1;

   auto * psz = (::wd32_character *)memory_allocate(len);

   *psz = '\0';

   if (len1 > 0)
   {

      wd32_cat(psz, psz1);

      if (iFree1 > 0)
      {

         memory_free((void *)psz1);

      }
      else if (iFree1 < 0)
      {

         free((void *)psz1);

      }

   }

   if (len2)
   {

      wd32_cat(psz, psz2);

      if (iFree2 > 0)
      {

         memory_free((void *)psz2);

      }
      else if (iFree2 < 0)
      {

         free((void *)psz2);

      }

   }

   return psz;

}









