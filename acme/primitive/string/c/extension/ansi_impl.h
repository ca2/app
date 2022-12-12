﻿#pragma once





inline ::ansi_character ansi_char_tolower(i32 i) { return __ansitolower(i); }
inline ::ansi_character ansi_char_toupper(i32 i) { return __ansitoupper(i); }


inline i32 ansi_char_isdigit(i32 i) { return __ansicharisdigit(i); }
inline i32 ansi_char_isalpha(i32 i) { return __ansicharisalpha(i); }
inline i32 ansi_char_isalnum(i32 i) { return __ansicharisalnum(i); }
inline i32 ansi_char_isspace(i32 i) { return __ansicharisspace(i); }


inline i32 ansi_char_is_hexadecimal(i32 i) { return __ansicharishexadecimal(i); }


inline const ::ansi_character * ansi_const_last_char(const ::ansi_character * psz)
{

   return ::is_null(psz) ? nullptr : psz + strlen(psz);

}


inline ::ansi_character * ansi_last_char(::ansi_character * psz)
{

   return (::ansi_character *)ansi_const_last_char(psz);

}


inline ::ansi_character * ansi_concatenate(::ansi_character * psz, const ::ansi_character * cat)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cat)) return nullptr;

   return strcat(psz, cat);

}


inline ::ansi_character * ansi_copy(::ansi_character * psz, const ::ansi_character * cpy)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   return strcpy(psz, cpy);

}


inline ::ansi_character * ansi_count_copy(::ansi_character * psz, const ::ansi_character * cpy, strsize len)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return strncpy(psz, cpy, len);

}


inline strsize ansi_length(const ::ansi_character * psz)
{

   if (::is_null(psz)) return 0;

   return strlen(psz);

}


inline ::ansi_character * ansi_duplicate(const ::ansi_character * psz)
{

   if (::is_null(psz)) return nullptr;

   auto pszDup = (::ansi_character *) memory_allocate(strlen(psz) + 1);

   strcpy(pszDup, psz);

   return pszDup;

}


inline ::ansi_character * ansi_count_duplicate(const ::ansi_character * psz, strsize len)
{

   if (::is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (::ansi_character *)memory_allocate(len + 1);

   strncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


inline const ::ansi_character * ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find)
{

   if (::is_null(psz)) return nullptr;

   if (::is_null(find)) return nullptr;

   return strstr(psz, find);

}



inline const ::ansi_character * ansi_find_string_ci(const ::ansi_character * psz, const ::ansi_character * find)
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


inline const ::ansi_character * ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len)
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


inline const ::ansi_character * ansi_count_find_string_ci(const ::ansi_character * psz, const ::ansi_character * find, strsize len)
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


inline i32 ansi_compare(const ::ansi_character * psz, const ::ansi_character * sz2)
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


inline i32 ansi_compare_ci(const ::ansi_character * psz, const ::ansi_character * sz2)
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


inline i32 ansi_count_compare(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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


inline i32 ansi_count_compare_ci(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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



inline i32 ansi_collate(const ::ansi_character * psz, const ::ansi_character * sz2)
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


inline i32 ansi_collate_ci(const ::ansi_character * psz, const ::ansi_character * sz2)
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


inline i32 ansi_count_collate(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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


inline i32 ansi_count_collate_ci(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
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


inline const ::ansi_character * _ansi_scan(const ::ansi_character * psz, const ::ansi_character * find)
{

   return ansi_pbrk((::ansi_character *) psz, find);

}



inline const ::ansi_character * ansi_scan(const ::ansi_character * psz, const ::ansi_character * find)
{

   if (::is_empty(psz)) return psz;

   if (::is_empty(find)) return psz;

   return ansi_scan(psz, find);

}


//inline const ::ansi_character * ansi_token(const ::ansi_character * psz, const ::ansi_character * pszSeparators)
//{
//
//   return string_find_first_in(psz, pszSeparators);
//
//}
//
//
//inline const ::ansi_character * _ansi_find_first_in(const ::ansi_character * psz, const ::ansi_character * pszSeparators)
//{
//
//   return _string_find_first_in(psz, pszSeparators);
//
//}


inline ::ansi_character * ansi_first_token(::ansi_character * psz, const ::ansi_character * delimiters, ::ansi_character ** action_context)
{

   return ansi_tok_r(psz, delimiters, action_context);

}


inline ::ansi_character * ansi_next_token(const ::ansi_character * delimiters, ::ansi_character ** action_context)
{

   return ansi_tok_r(nullptr, delimiters, action_context);

}


inline i32 ansi_begins(const ::ansi_character * psz, const ::ansi_character * prefix)
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


inline i32 ansi_begins_ci(const ::ansi_character * psz, const ::ansi_character * prefix)
{

   if (::is_null(psz)) return false;

   if (::is_null(prefix)) return false;

   return !ansi_nicmp(psz, prefix, strlen(prefix));

}


inline const ::ansi_character * ansi_begins_eat(const ::ansi_character * psz, const ::ansi_character * prefix)
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


inline const ::ansi_character * ansi_begins_eat_ci(const ::ansi_character * psz, const ::ansi_character * prefix)
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


inline i32 ansi_ends(const ::ansi_character * psz, const ::ansi_character * suffix)
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


inline i32 ansi_ends_ci(const ::ansi_character * psz, const ::ansi_character * suffix)
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


inline const ::ansi_character * ansi_find_char(const ::ansi_character * psz, ::ansi_character ch)
{

   if (::is_null(psz)) return nullptr;

   return strchr(psz, ch);

}


inline const ::ansi_character * ansi_find_char_reverse(const ::ansi_character * psz, ::ansi_character ch)
{

   if (::is_null(psz)) return nullptr;

   return strrchr(psz, ch);

}


//inline const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2);
//inline const ::ansi_character * ansi_concatenate_duplicate_and_free(const ::ansi_character * psz1, ::ansi_character * psz2);


inline void ansi_from_u64(::ansi_character * sz, u64 u, i32 iBase, enum_digit_case edigitcase)
{

   ::ansi_character * end;

   __u64toansi(u, sz, iBase, edigitcase, end);

}


inline void ansi_from_i64(::ansi_character * sz, i64 i, i32 iBase, enum_digit_case edigitcase)
{

   ::ansi_character * end;

   __i64toansi(i, sz, iBase, edigitcase, end);

}


inline void ansi_from_u32(::ansi_character * sz, u32 u, i32 iBase, enum_digit_case edigitcase)
{

   ::ansi_character * end;

   __u64toansi(u, sz, iBase, edigitcase, end);

}


inline void ansi_from_i32(::ansi_character * sz, i32 i, i32 iBase, enum_digit_case edigitcase)
{

   ::ansi_character * end;

   __i64toansi(i, sz, iBase, edigitcase, end);

}


inline i64 ansi_count_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase, strsize srclen)
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

         memory_free(pszDup);

         return i;

      }

   }

   return ansi_to_i64(psz, ppszEnd, iBase);

}


inline i32 ansi_count_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase, strsize srclen)
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

         memory_free(pszDup);

         return i;

      }

   }

   return ansi_to_i32(psz, ppszEnd, iBase);

}


inline void ansi_reverse(::ansi_character * psz)
{

   reverse_memory(psz, string_safe_length(psz));

}


inline void ansi_reverse(::ansi_character * psz, strsize size)
{

   reverse_memory(psz, size);

}


inline void ansi_zero_pad(::ansi_character * psz, strsize lenPad)
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


inline ::ansi_character * ansi_lower(::ansi_character * pch)
{

   ::ansi_character * p = pch;

   while (*p != '\0')
   {

      *p = ansi_char_tolower(*p);

      p++;

   }

   return pch;

}


inline ::ansi_character * ansi_upper(::ansi_character * pch)
{

   ::ansi_character * p = pch;

   while (*p != '\0')
   {

      *p = ansi_char_toupper(*p);

      p++;

   }

   return pch;

}


inline const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2, int iFree1, int iFree2)
{

   strsize len1 = ansi_length(psz1);

   strsize len2 = ansi_length(psz2);

   strsize len = len1 + len2 + 1;

   auto * psz = (::ansi_character *)memory_allocate(len);

   *psz = '\0';

   if (len1 > 0)
   {

      strcat(psz, psz1);

      if (iFree1 > 0)
      {

         memory_free((void *) psz1);

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

         memory_free((void *)psz2);

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
//   auto * psz = (::ansi_character *)memory_allocate(len);
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



//CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_free_and_duplicate(::ansi_character * psz1, const ::ansi_character * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (::ansi_character *)memory_allocate(len);
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



//CLASS_DECL_ACME const ::ansi_character * ansi_concatenat_free_duplicate_and_free(::ansi_character * psz1, ::ansi_character * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (::ansi_character *)memory_allocate(len);
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



//inline void                   ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, i32 * numargs, i32 * numchars);



inline const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen)
{

   if (::is_null(src)) return nullptr;

   if (srclen <= 0) return nullptr;

   if (::is_null(find)) return src;

   if (findlen <= 0) return src;

#if defined(WINDOWS) || defined(__APPLE__)

   for (const byte * p = (const byte *) src; srclen >= findlen;  p++, srclen--)
   {

      if (!memcmp(p, find, findlen))
      {

         return p;

      }

   }

   return nullptr;

#else

   return memmem(src, srclen, find, findlen);

#endif

}




inline const ::ansi_character *       wildcard_next_stop(const ::ansi_character * pszCriteria);

inline int_bool               wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
inline int_bool               wildcard_matches_criteria_ci(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);










