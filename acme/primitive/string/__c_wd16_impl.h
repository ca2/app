#pragma once





inline wd16char wd16_char_lowered(i32 i) { return __wd16tolower(i); }
inline wd16char wd16_char_uppered(i32 i) { return __wd16toupper(i); }


inline i32 wd16_char_is_digit(i32 i) { return __wd16charisdigit(i); }
inline i32 wd16_char_is_hexadecimal(i32 i) { return __wd16charishexadecimal(i); }
inline i32 wd16_char_is_alphabetic(i32 i) { return __wd16charisalphabetic(i); }
inline i32 wd16_char_is_alphanumeric(i32 i) { return __wd16charisalphanumeric(i); }
inline i32 wd16_char_is_space(i32 i) { return __wd16charisspace(i); }





inline const wd16char * wd16_const_last_char(const wd16char * psz)
{

   return c_is_null(psz) ? nullptr : psz + wd16_len(psz);

}


inline wd16char * wd16_last_char(wd16char * psz)
{

   return (wd16char *)wd16_const_last_char(psz);

}


inline wd16char * wd16_concatenate(wd16char * psz, const wd16char * cat)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cat)) return nullptr;

   return wd16_cat(psz, cat);

}


inline wd16char * wd16_copy(wd16char * psz, const wd16char * cpy)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   return wd16_cpy(psz, cpy);

}


inline wd16char * wd16_count_copy(wd16char * psz, const wd16char * cpy, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return wd16_ncpy(psz, cpy, len);

}


inline strsize wd16_length(const wd16char * psz)
{

   if (c_is_null(psz)) return 0;

   return wd16_len(psz);

}


inline wd16char * wd16_duplicate(const wd16char * psz)
{

   if (c_is_null(psz)) return nullptr;

   auto pszDup = (wd16char *)memory_alloc(wd16_len(psz) + 1);

   wd16_cpy(pszDup, psz);

   return pszDup;

}


inline wd16char * wd16_count_duplicate(const wd16char * psz, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (wd16char *)memory_alloc(len + 1);

   wd16_ncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


inline const wd16char * wd16_find_string(const wd16char * psz, const wd16char * find)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(find)) return nullptr;

   return wd16_str(psz, find);

}


inline const wd16char * wd16_find_string_case_insensitive(const wd16char * psz, const wd16char * find)
{

   if (c_is_null(psz)) return nullptr;

   auto len = wd16_len(find);

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd16_nicmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


inline const wd16char * wd16_count_find_string(const wd16char * psz, const wd16char * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len > (strsize) wd16_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd16_ncmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


inline const wd16char * wd16_count_find_string_case_insensitive(const wd16char * psz, const wd16char * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len > (strsize) wd16_len(find)) return nullptr;

   if (len <= 0)
   {

      return psz;

   }

   while (*psz != '\0')
   {

      if (!wd16_nicmp(psz, find, len))
      {

         return psz;

      }

      psz++;

   }

   return nullptr;

}


inline i32 wd16_compare(const wd16char * psz, const wd16char * sz2)
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

      return wd16_cmp(psz, sz2);

   }

}


inline i32 wd16_compare_case_insensitive(const wd16char * psz, const wd16char * sz2)
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

      return wd16_compare_case_insensitive(psz, sz2);

   }

}


inline i32 wd16_count_compare(const wd16char * psz, const wd16char * sz2, strsize len)
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

      return wd16_ncmp(psz, sz2, len);

   }

}


inline i32 wd16_count_compare_case_insensitive(const wd16char * psz, const wd16char * sz2, strsize len)
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

      return wd16_nicmp(psz, sz2, len);

   }

}


inline i32 wd16_collate(const wd16char * psz, const wd16char * sz2)
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

      return wd16_coll(psz, sz2);

   }

}


inline i32 wd16_collate_case_insensitive(const wd16char * psz, const wd16char * sz2)
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

      return wd16_collate_case_insensitive(psz, sz2);

   }

}


inline i32 wd16_count_collate(const wd16char * psz, const wd16char * sz2, strsize len)
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

      return wd16_ncoll(psz, sz2, len);

   }

}


inline i32 wd16_count_collate_case_insensitive(const wd16char * psz, const wd16char * sz2, strsize len)
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

      return wd16_nicoll(psz, sz2, len);

   }

}

inline const wd16char * wd16_scan(const wd16char * psz, const wd16char * find)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(find)) return nullptr;

   return wd16_pbrk((wd16char * ) psz, find);

}


inline wd16char * wd16_first_token(wd16char * psz, const wd16char * delimiters, wd16char ** action_context)
{

   return wd16_tok_r(psz, delimiters, action_context);

}



inline wd16char * wd16_next_token(const wd16char * delimiters, wd16char ** action_context)
{

   return wd16_tok_r(nullptr, delimiters, action_context);

}


inline i32 wd16_begins(const wd16char * psz, const wd16char * prefix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(prefix)) return false;

   auto len = wd16_len(prefix);

   if (len > wd16_len(psz))
   {

      return false;

   }

   return !wd16_ncmp(psz, prefix, len);

}


inline i32 wd16_begins_case_insensitive(const wd16char * psz, const wd16char * prefix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(prefix)) return false;

   return !wd16_nicmp(psz, prefix, wd16_len(prefix));

}


inline const wd16char * wd16_begins_eat(const wd16char * psz, const wd16char * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   auto len = wd16_len(prefix);

   if (wd16_ncmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline const wd16char * wd16_begins_eat_case_insensitive(const wd16char * psz, const wd16char * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   auto len = wd16_len(prefix);

   if (wd16_nicmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline i32 wd16_ends(const wd16char * psz, const wd16char * suffix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(suffix)) return false;

   auto len = wd16_len(suffix);

   auto end = wd16_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd16_ncmp(psz + end, suffix, len);

}


inline i32 wd16_ends_case_insensitive(const wd16char * psz, const wd16char * suffix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(suffix)) return false;

   auto len = wd16_len(suffix);

   auto end = wd16_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd16_nicmp(psz + end, suffix, len);

}


inline const wd16char * wd16_find_char(const wd16char * psz, wd16char ch)
{

   if (c_is_null(psz)) return nullptr;

   return wd16_chr(psz, ch);

}


inline const wd16char * wd16_find_char_reverse(const wd16char * psz, wd16char ch)
{

   if (c_is_null(psz)) return nullptr;

   return wd16_rchr(psz, ch);

}


//inline const wd16char * wd16_concatenate_and_duplicate(const wd16char * psz1, const wd16char * psz2);
//inline const wd16char * wd16_concatenate_duplicate_and_free(const wd16char * psz1, wd16char * psz2);


inline void wd16_from_u64_base(wd16char * sz, u64 u, i32 iBase)
{

   u64towd16(u, sz, iBase);

}


inline void wd16_from_i64_base(wd16char * sz, i64 i, i32 iBase)
{

   i64towd16(i, sz, iBase);

}


#ifdef WINDOWS


inline i64 wd16_to_i64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return wcstoll(psz, (wd16char **) ppszEnd, iBase);

}


inline u64 wd16_to_u64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return wcstoull(psz, (wd16char **) ppszEnd, iBase);

}


inline i32 wd16_to_i32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return wcstol(psz, (wd16char **) ppszEnd, iBase);

}


inline u32 wd16_to_u32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return wcstoul(psz, (wd16char **) ppszEnd, iBase);

}


#else



inline i64 wd16_to_i64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return __wd16toi64(psz, (wd16char **) ppszEnd, iBase);

}


inline u64 wd16_to_u64(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return __wd16tou64(psz, (wd16char **) ppszEnd, iBase);

}


inline i32 wd16_to_i32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return __wd16toi32(psz, (wd16char **) ppszEnd, iBase);

}


inline u32 wd16_to_u32(const wd16char * psz, const wd16char ** ppszEnd, i32 iBase)
{

   return __wd16tou32(psz, (wd16char **) ppszEnd, iBase);

}


#endif



inline void wd16_reverse(wd16char * psz)
{

   reverse_memory(psz, wd16_len(psz));

}

inline void wd16_zero_pad(wd16char * psz, strsize lenPad)
{

   strsize len = wd16_len(psz);

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


inline wd16char * wd16_lower(wd16char * pch)
{

   wd16char * p = pch;

   while (*p != '\0')
   {

      *p = wd16_char_lowered(*p);

      p++;

   }

   return pch;

}


inline wd16char * wd16_upper(wd16char * pch)
{

   wd16char * p = pch;

   while (*p != '\0')
   {

      *p = wd16_char_uppered(*p);

      p++;

   }

   return pch;

}


inline const wd16char * wd16_concatenate_and_duplicate(const wd16char * psz1, const wd16char * psz2, int iFree1, int iFree2)
{

   strsize len1 = wd16_length(psz1);

   strsize len2 = wd16_length(psz2);

   strsize len = len1 + len2 + 1;

   auto * psz = (wd16char *)memory_alloc(len);

   *psz = '\0';

   if (len1 > 0)
   {

      wd16_cat(psz, psz1);

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

      wd16_cat(psz, psz2);

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


//CLASS_DECL_ACME const wd16char * wd16_concatenate_duplicate_and_free(const wd16char * psz1, wd16char * psz2)
//{
//
//   strsize len1 = wd16_len(psz1);
//
//   strsize len2 = wd16_len(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (wd16char *)memory_alloc(len);
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
//      memory_free(psz2);
//
//   }
//
//   return psz;
//
//}



//CLASS_DECL_ACME const wd16char * wd16_concatenate_free_and_duplicate(wd16char * psz1, const wd16char * psz2)
//{
//
//   strsize len1 = wd16_len(psz1);
//
//   strsize len2 = wd16_len(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (wd16char *)memory_alloc(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(psz, psz1);
//
//      memory_free(psz1);
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



//CLASS_DECL_ACME const wd16char * wd16_concatenat_free_duplicate_and_free(wd16char * psz1, wd16char * psz2)
//{
//
//   strsize len1 = wd16_len(psz1);
//
//   strsize len2 = wd16_len(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (wd16char *)memory_alloc(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(psz, psz1);
//
//      memory_free(psz1);
//
//   }
//
//   if (len2)
//   {
//
//      strcat(psz, psz2);
//
//      memory_free(psz2);
//
//   }
//
//   return psz;
//
//}



//inline void                   ansi_parse_command_line(wd16char * cmdstart, wd16char ** argv, wd16char * args, i32 * numargs, i32 * numchars);



//CLASS_DECL_ACME const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen)
//{
//
//   if (c_is_null(src)) return nullptr;
//
//   if (srclen <= 0) return nullptr;
//
//   if (c_is_null(find)) return src;
//
//   if (findlen <= 0) return src;
//
//#ifdef WINDOWS
//
//   for (const byte * p = (const byte *)src; srclen >= findlen; p++, srclen--)
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
//   return memmem(src, srclen, find, findlen);
//
//#endif
//
//}



//inline wd16char * wd16_next_token(wd16char * s1, const wd16char * s2, wd16char ** lasts);

//inline const wd16char * wildcard_next_stop(const wd16char * pszCriteria);
//
//inline int_bool               wildcard_matches_criteria(const wd16char * pszCriteria, const wd16char * pszValue);
//inline int_bool               wildcard_matches_criteria_case_insensitive(const wd16char * pszCriteria, const wd16char * pszValue);


//inline unichar * wd16_concatenate(unichar * dest, const unichar * cat);
//inline unichar * wd16_copy(unichar * dest, const unichar * src);
//inline unichar * wd16_count_copy(unichar * dest, const unichar * src, strsize n);
//inline i32 wd16_char_is_alphanumeric(i32 wch);
//inline count wd16_length(const unichar * pwsz);
//inline count wd16_32len_dup(const wchar_t * pwsz);
//inline unichar * wd16_find_char(const unichar * sz, unichar ch);
//inline i32 wd16_compare(const unichar * psz, const unichar * sz2);
//inline i32 wd16_compare_case_insensitive(const unichar * psz, const unichar * sz2);
//inline wd16char * wd16_find_string_case_insensitive(const unichar * src, const unichar * find);

//inline void wd16_from_u64_base(unichar * sz, u64 i, i32 iBase);
//inline void wd16_from_i32_base(unichar * sz, i64 i, i32 iBase);


//inline void l64toa_dup(wd16char * sz, i64 i, i64 iBase);
//inline void i64toa_dup(wd16char * sz, i64 i);
//inline void wd16_reverse(unichar * sz);
//inline void w_zero_pad(wd16char * sz, strsize iPad);


//inline unichar wd16_char_lower(i32 wch);
//inline unichar wd16_char_upper(i32 wch);

//inline errno_t wd16_lower(unichar * sz, strsize size);
//inline errno_t wd16_upper(unichar * sz, strsize size);

//inline i32 wd16_char_is_alphabetic(i32 ch);
//inline i32 wd16_char_is_digit(i32 ch);
//inline i32 wd16_char_is_space(i32 ch);


//inline void __cdecl wparse_cmdline(WCHAR *cmdstart, WCHAR **argv, WCHAR *args, i32 * numargs, i32 * numchars);

//inline void ansi_to_wd16(unichar * pwsz, const wd16char * psz);
//inline unichar * ::str::international::utf8_to_unicode(const wd16char * psz);
//inline wd16char * ::str::international::unicode_to_utf8(const unichar * psz);












