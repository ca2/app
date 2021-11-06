#pragma once





inline wd32char wd32_char_lowered(i32 i) { return __wd32tolower(i); }
inline wd32char wd32_char_uppered(i32 i) { return __wd32toupper(i); }


inline i32 wd32_char_is_digit(i32 i) { return __wd32charisdigit(i); }
inline i32 wd32_char_is_hexadecimal(i32 i) { return __wd32charishexadecimal(i); }
inline i32 wd32_char_is_alphabetic(i32 i) { return __wd32charisalphabetic(i); }
inline i32 wd32_char_is_alphanumeric(i32 i) { return __wd32charisalphanumeric(i); }
inline i32 wd32_char_is_space(i32 i) { return __wd32charisspace(i); }



inline const wd32char * wd32_const_last_char(const wd32char * psz)
{

   return c_is_null(psz) ? nullptr : psz + wd32_len(psz);

}


inline wd32char * wd32_last_char(wd32char * psz)
{

   return (wd32char *)wd32_const_last_char(psz);

}


inline wd32char * wd32_concatenate(wd32char * psz, const wd32char * cat)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cat)) return nullptr;

   return wd32_cat(psz, cat);

}


inline wd32char * wd32_copy(wd32char * psz, const wd32char * cpy)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   return wd32_cpy(psz, cpy);

}


inline wd32char * wd32_count_copy(wd32char * psz, const wd32char * cpy, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return wd32_ncpy(psz, cpy, len);

}


inline strsize wd32_length(const wd32char * psz)
{

   if (c_is_null(psz)) return 0;

   return wd32_len(psz);

}


inline wd32char * wd32_duplicate(const wd32char * psz)
{

   if (c_is_null(psz)) return nullptr;

   auto pszDup = (wd32char *)memory_allocate(wd32_len(psz) + 1);

   wd32_cpy(pszDup, psz);

   return pszDup;

}


inline wd32char * wd32_count_duplicate(const wd32char * psz, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (wd32char *)memory_allocate(len + 1);

   wd32_ncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


inline const wd32char * wd32_find_string(const wd32char * psz, const wd32char * find)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(find)) return nullptr;

   return wd32_str(psz, find);

}


inline const wd32char * wd32_find_string_case_insensitive(const wd32char * psz, const wd32char * find)
{

   if (c_is_null(psz)) return nullptr;

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


inline const wd32char * wd32_count_find_string(const wd32char * psz, const wd32char * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

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


inline const wd32char * wd32_count_find_string_case_insensitive(const wd32char * psz, const wd32char * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

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


inline i32 wd32_compare(const wd32char * psz, const wd32char * sz2)
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

      return wd32_cmp(psz, sz2);

   }

}


inline i32 wd32_compare_case_insensitive(const wd32char * psz, const wd32char * sz2)
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

      return wd32_compare_case_insensitive(psz, sz2);

   }

}


inline i32 wd32_count_compare(const wd32char * psz, const wd32char * sz2, strsize len)
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

      return wd32_ncmp(psz, sz2, len);

   }

}


inline i32 wd32_count_compare_case_insensitive(const wd32char * psz, const wd32char * sz2, strsize len)
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

      return wd32_nicmp(psz, sz2, len);

   }

}


inline i32 wd32_collate(const wd32char * psz, const wd32char * sz2)
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

      return wd32_coll(psz, sz2);

   }

}


inline i32 wd32_collate_case_insensitive(const wd32char * psz, const wd32char * sz2)
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

      return wd32_collate_case_insensitive(psz, sz2);

   }

}


inline i32 wd32_count_collate(const wd32char * psz, const wd32char * sz2, strsize len)
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

      return wd32_ncoll(psz, sz2, len);

   }

}


inline i32 wd32_count_collate_case_insensitive(const wd32char * psz, const wd32char * sz2, strsize len)
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

      return wd32_nicoll(psz, sz2, len);

   }

}

inline const wd32char * wd32_scan(const wd32char * psz, const wd32char * find)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(find)) return nullptr;

   return wd32_pbrk((wd32char* )psz, find);

}


inline wd32char * wd32_first_token(wd32char * psz, const wd32char * delimiters, wd32char ** action_context)
{

   return wd32_tok_r(psz, delimiters, action_context);

}



inline wd32char * wd32_next_token(const wd32char * delimiters, wd32char ** action_context)
{

   return wd32_tok_r(nullptr, delimiters, action_context);


}


inline i32 wd32_begins(const wd32char * psz, const wd32char * prefix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(prefix)) return false;

   auto len = wd32_len(prefix);

   if (len > wd32_len(psz))
   {

      return false;

   }

   return !wd32_ncmp(psz, prefix, len);

}


inline i32 wd32_begins_case_insensitive(const wd32char * psz, const wd32char * prefix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(prefix)) return false;

   return !wd32_nicmp(psz, prefix, wd32_len(prefix));

}


inline const wd32char * wd32_begins_eat(const wd32char * psz, const wd32char * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   auto len = wd32_len(prefix);

   if (wd32_ncmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline const wd32char * wd32_begins_eat_case_insensitive(const wd32char * psz, const wd32char * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   auto len = wd32_len(prefix);

   if (wd32_nicmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline i32 wd32_ends(const wd32char * psz, const wd32char * suffix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(suffix)) return false;

   auto len = wd32_len(suffix);

   auto end = wd32_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd32_ncmp(psz + end, suffix, len);

}


inline i32 wd32_ends_case_insensitive(const wd32char * psz, const wd32char * suffix)
{

   if (c_is_null(psz)) return false;

   if (c_is_null(suffix)) return false;

   auto len = wd32_len(suffix);

   auto end = wd32_len(psz) - len;

   if (end < 0)
   {

      return false;

   }

   return !wd32_nicmp(psz + end, suffix, len);

}


inline const wd32char * wd32_find_char(const wd32char * psz, wd32char ch)
{

   if (c_is_null(psz)) return nullptr;

   return wd32_chr(psz, ch);

}


inline const wd32char * wd32_find_char_reverse(const wd32char * psz, wd32char ch)
{

   if (c_is_null(psz)) return nullptr;

   return wd32_rchr(psz, ch);

}


//inline const wd32char * wd32_concatenate_and_duplicate(const wd32char * psz1, const wd32char * psz2);
//inline const wd32char * wd32_concatenate_duplicate_and_free(const wd32char * psz1, wd32char * psz2);


inline void wd32_from_u64_base(wd32char * sz, u64 u, i32 iBase)
{

   u64towd32(u, sz, iBase);

}


inline void wd32_from_i64_base(wd32char * sz, i64 i, i32 iBase)
{

   i64towd32(i, sz, iBase);

}


#ifdef WINDOWS




inline i64 wd32_to_i64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

   return __wd32toi64(psz, (wd32char **) ppszEnd, iBase);

}


inline u64 wd32_to_u64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

   return __wd32tou64(psz, (wd32char **) ppszEnd, iBase);

}


inline i32 wd32_to_i32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

   return __wd32toi32(psz, (wd32char **) ppszEnd, iBase);

}


inline u32 wd32_to_u32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

   return __wd32tou32(psz, (wd32char **) ppszEnd, iBase);

}
#else


inline i64 wd32_to_i64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

   return wcstoll(psz, (wd32char **) ppszEnd, iBase);

}


inline u64 wd32_to_u64(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

   return wcstoull(psz, (wd32char **) ppszEnd, iBase);

}


inline i32 wd32_to_i32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{
   
#ifdef WINDOWS

   return wcstol(psz, (wd32char **) ppszEnd, iBase);
   
#else
   
   long l = wcstol(psz, (wd32char **) ppszEnd, iBase);
   
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


inline u32 wd32_to_u32(const wd32char * psz, const wd32char ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS
   
   return wcstoul(psz, (wd32char **) ppszEnd, iBase);
   
#else

   unsigned long ul = wcstoul(psz, (wd32char **) ppszEnd, iBase);

   if(ul > UINT_MAX)
   {
      
      errno = ERANGE;
      
      return UINT_MAX;
      
   }

   return (::u32) ul;
   
#endif

}




#endif


inline void wd32_reverse(wd32char * psz)
{

   reverse_memory(psz, wd32_len(psz));

}

inline void wd32_zero_pad(wd32char * psz, strsize lenPad)
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


inline wd32char * wd32_lower(wd32char * pch)
{

   wd32char * p = pch;

   while (*p != '\0')
   {

      *p = wd32_char_lowered(*p);

      p++;

   }

   return pch;

}


inline wd32char * wd32_upper(wd32char * pch)
{

   wd32char * p = pch;

   while (*p != '\0')
   {

      *p = wd32_char_uppered(*p);

      p++;

   }

   return pch;

}


inline const wd32char * wd32_concatenate_and_duplicate(const wd32char * psz1, const wd32char * psz2, int iFree1, int iFree2)
{

   strsize len1 = wd32_length(psz1);

   strsize len2 = wd32_length(psz2);

   strsize len = len1 + len2 + 1;

   auto * psz = (wd32char *)memory_allocate(len);

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









