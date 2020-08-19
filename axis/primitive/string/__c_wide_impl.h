#pragma once





inline widechar wide_char_lowered(i32 i) { return __MID_CHARBIT(wd, _char_lowered)(i); }
inline widechar wide_char_uppered(i32 i) { return __MID_CHARBIT(wd, _char_uppered)(i); }


inline i32 wide_char_is_digit(i32 i) { return __MID_CHARBIT(wd, _char_is_digit)(i); }
inline i32 wide_char_is_hexadecimal(i32 i) { return __MID_CHARBIT(wd, _char_is_hexadecimal)(i); }
inline i32 wide_char_is_alphabetic(i32 i) { return __MID_CHARBIT(wd, _char_is_alphabetic)(i); }
inline i32 wide_char_is_alphanumeric(i32 i) { return __MID_CHARBIT(wd, _char_is_alphanumeric)(i); }
inline i32 wide_char_is_space(i32 i) { return __MID_CHARBIT(wd, _char_is_space)(i); }

inline const widechar * wide_const_last_char(const widechar * psz)
{

   return c_is_null(psz) ? nullptr : psz + wcslen(psz);

}


inline widechar * wide_last_char(widechar * psz)
{

   return (widechar *)wide_const_last_char(psz);

}


inline widechar * wide_concatenate(widechar * psz, const widechar * cat)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cat)) return nullptr;

   return wcscat(psz, cat);

}


inline widechar * wide_copy(widechar * psz, const widechar * cpy)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   return wcscpy(psz, cpy);

}


inline widechar * wide_count_copy(widechar * psz, const widechar * cpy, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return wcsncpy(psz, cpy, len);

}


inline strsize wide_length(const widechar * psz)
{

   if (c_is_null(psz)) return 0;

   return wcslen(psz);

}


inline widechar * wide_duplicate(const widechar * psz)
{

   if (c_is_null(psz)) return nullptr;

   auto pszDup = (widechar *)memory_alloc(wcslen(psz) + 1);

   wcscpy(pszDup, psz);

   return pszDup;

}


inline widechar * wide_count_duplicate(const widechar * psz, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (widechar *)memory_alloc(len + 1);

   wcsncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


inline const widechar * wide_find_string(const widechar * psz, const widechar * find)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(find)) return nullptr;

   return wcsstr(psz, find);

}


inline const widechar * wide_find_string_case_insensitive(const widechar * psz, const widechar * find)
{

   if (c_is_null(psz)) return nullptr;

   auto len = wcslen(find);

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


inline const widechar * wide_count_find_string(const widechar * psz, const widechar * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len > (strsize) wcslen(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wcsncmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


inline const widechar * wide_count_find_string_case_insensitive(const widechar * psz, const widechar * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len > (strsize) wcslen(find)) return nullptr;

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


inline i32 wide_compare(const widechar * psz, const widechar * sz2)
{

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wcscmp(psz, sz2);

   }

}


inline i32 wide_compare_case_insensitive(const widechar * psz, const widechar * sz2)
{

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wide_compare_case_insensitive(psz, sz2);

   }

}


inline i32 wide_count_compare(const widechar * psz, const widechar * sz2, strsize len)
{

   if (len < 0)
   {

      return 0;

   }

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wcsncmp(psz, sz2, len);

   }

}


inline i32 wide_count_compare_case_insensitive(const widechar * psz, const widechar * sz2, strsize len)
{

   if (len < 0)
   {

      return 0;

   }

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wide_nicmp(psz, sz2, len);

   }

}


inline i32 wide_collate(const widechar * psz, const widechar * sz2)
{

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wide_coll(psz, sz2);

   }

}


inline i32 wide_collate_case_insensitive(const widechar * psz, const widechar * sz2)
{

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wide_collate_case_insensitive(psz, sz2);

   }

}


inline i32 wide_count_collate(const widechar * psz, const widechar * sz2, strsize len)
{

   if (len < 0)
   {

      return 0;

   }

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wide_ncoll(psz, sz2, len);

   }

}


inline i32 wide_count_collate_case_insensitive(const widechar * psz, const widechar * sz2, strsize len)
{

   if (len < 0)
   {

      return 0;

   }

   if (c_is_null(psz))
   {

      if (c_is_null(sz2))
      {

         return 0;

      }
      else
      {

         return -1;

      }

   }
   else if (c_is_null(sz2))
   {

      return 1;

   }
   else
   {

      return wide_nicoll(psz, sz2, len);

   }

}

inline const widechar * wide_scan(const widechar * psz, const widechar * find)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(find)) return FALSE;

   return wcspbrk(psz, find);

}


inline widechar * wide_first_token(widechar * psz, const widechar * delimiters, widechar ** action_context)
{

   return wide_tok_r(psz, delimiters, action_context);

}



inline widechar * wide_next_token(const widechar * delimiters, widechar ** action_context)
{

   return wide_tok_r(nullptr, delimiters, action_context);

}


inline i32 wide_begins(const widechar * psz, const widechar * prefix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(prefix)) return FALSE;

   strsize len = wcslen(prefix);

   if (len > (strsize)wcslen(psz))
   {

      return FALSE;

   }

   return !wcsncmp(psz, prefix, len);

}


inline i32 wide_begins_case_insensitive(const widechar * psz, const widechar * prefix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(prefix)) return FALSE;

   return !wide_nicmp(psz, prefix, wcslen(prefix));

}


inline const widechar * wide_begins_eat(const widechar * psz, const widechar * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   strsize len = wcslen(prefix);

   if (wcsncmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline const widechar * wide_begins_eat_case_insensitive(const widechar * psz, const widechar * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   strsize len = wcslen(prefix);

   if (wide_nicmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline i32 wide_ends(const widechar * psz, const widechar * suffix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(suffix)) return FALSE;

   strsize len = wcslen(suffix);

   strsize end = wcslen(psz) - len;

   if (end < 0)
   {

      return FALSE;

   }

   return !wcsncmp(psz + end, suffix, len);

}


inline i32 wide_ends_case_insensitive(const widechar * psz, const widechar * suffix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(suffix)) return FALSE;

   strsize len = wcslen(suffix);

   strsize end = wcslen(psz) - len;

   if (end < 0)
   {

      return FALSE;

   }

   return !wide_nicmp(psz + end, suffix, len);

}


inline const widechar * wide_find_char(const widechar * psz, widechar ch)
{

   if (c_is_null(psz)) return nullptr;

   return wcschr(psz, ch);

}


inline const widechar * wide_find_char_reverse(const widechar * psz, widechar ch)
{

   if (c_is_null(psz)) return nullptr;

   return wcsrchr(psz, ch);

}


//inline const widechar * wide_concatenate_and_duplicate(const widechar * psz1, const widechar * psz2);
//inline const widechar * wide_concatenate_duplicate_and_free(const widechar * psz1, widechar * psz2);


inline void wide_from_u64_base(widechar * sz, u64 u, i32 iBase)
{

   __u64towide(u, sz, iBase);

}


inline void wide_from_i64_base(widechar * sz, i64 i, i32 iBase)
{

   __i64towide(i, sz, iBase);

}




inline void wide_reverse(widechar * psz)
{

   reverse_memory(psz, wcslen(psz));

}

inline void wide_zero_pad(widechar * psz, strsize lenPad)
{

   strsize len = wcslen(psz);

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


inline widechar * wide_lower(widechar * pch)
{

   widechar * p = pch;

   while (*p != '\0')
   {

      *p = wide_char_lowered(*p);

      p++;

   }

   return pch;

}


inline widechar * wide_upper(widechar * pch)
{

   widechar * p = pch;

   while (*p != '\0')
   {

      *p = wide_char_uppered(*p);

      p++;

   }

   return pch;

}


inline const widechar * wide_concatenate_and_duplicate(const widechar * psz1, const widechar * psz2, int iFree1, int iFree2)
{

   strsize len1 = wide_length(psz1);

   strsize len2 = wide_length(psz2);

   strsize len = len1 + len2 + 1;

   auto * psz = (widechar *)memory_alloc(len);

   *psz = '\0';

   if (len1 > 0)
   {

      wcscat(psz, psz1);

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

      wcscat(psz, psz2);

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

inline i64 wide_to_i64(const widechar * psz, const widechar ** ppszEnd, i32 iBase) { return __MID_CHARBIT(wd, _to_i64)(psz, ppszEnd, iBase); }
inline u64 wide_to_u64(const widechar * psz, const widechar ** ppszEnd, i32 iBase) { return __MID_CHARBIT(wd, _to_u64)(psz, ppszEnd, iBase); }
inline i32 wide_to_i32(const widechar * psz, const widechar ** ppszEnd, i32 iBase) { return __MID_CHARBIT(wd, _to_i32)(psz, ppszEnd, iBase); }
inline u32 wide_to_u32(const widechar * psz, const widechar ** ppszEnd, i32 iBase) { return __MID_CHARBIT(wd, _to_u32)(psz, ppszEnd, iBase); }








