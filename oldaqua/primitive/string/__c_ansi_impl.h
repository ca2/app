#pragma once





inline ansichar ansi_char_lowered(i32 i) { return __ansitolower(i); }
inline ansichar ansi_char_uppered(i32 i) { return __ansitoupper(i); }


inline i32 ansi_char_is_digit(i32 i) { return __ansicharisdigit(i); }
inline i32 ansi_char_is_hexadecimal(i32 i) { return __ansicharishexadecimal(i); }
inline i32 ansi_char_is_alphabetic(i32 i) { return __ansicharisalphabetic(i); }
inline i32 ansi_char_is_alphanumeric(i32 i) { return __ansicharisalphanumeric(i); }
inline i32 ansi_char_is_space(i32 i) { return __ansicharisspace(i); }


inline const ansichar * ansi_const_last_char(const ansichar * psz)
{

   return c_is_null(psz) ? nullptr : psz + strlen(psz);

}


inline ansichar * ansi_last_char(ansichar * psz)
{

   return (ansichar *)ansi_const_last_char(psz);

}


inline ansichar * ansi_concatenate(ansichar * psz, const ansichar * cat)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cat)) return nullptr;

   return strcat(psz, cat);

}


inline ansichar * ansi_copy(ansichar * psz, const ansichar * cpy)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   return strcpy(psz, cpy);

}


inline ansichar * ansi_count_copy(ansichar * psz, const ansichar * cpy, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(cpy)) return nullptr;

   if (len < 0) return nullptr;

   return strncpy(psz, cpy, len);

}


inline strsize ansi_length(const ansichar * psz)
{

   if (c_is_null(psz)) return 0;

   return strlen(psz);

}


inline ansichar * ansi_duplicate(const ansichar * psz)
{

   if (c_is_null(psz)) return nullptr;

   auto pszDup = (ansichar *) memory_alloc(strlen(psz) + 1);

   strcpy(pszDup, psz);

   return pszDup;

}


inline ansichar * ansi_count_duplicate(const ansichar * psz, strsize len)
{

   if (c_is_null(psz)) return nullptr;

   if (len < 0) return nullptr;

   auto pszDup = (ansichar *)memory_alloc(len + 1);

   strncpy(pszDup, psz, len);

   pszDup[len] = '\0';

   return pszDup;

}


inline const ansichar * ansi_find_string(const ansichar * psz, const ansichar * find)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(find)) return nullptr;

   return strstr(psz, find);

}



inline const ansichar * ansi_find_string_ci(const ansichar * psz, const ansichar * find)
{

   if (c_is_null(psz)) return nullptr;

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


inline const ansichar * ansi_count_find_string(const ansichar * psz, const ansichar * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

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


inline const ansichar * ansi_count_find_string_ci(const ansichar * psz, const ansichar * find, strsize len)
{

   if (c_is_null(psz)) return nullptr;

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


inline i32 ansi_compare(const ansichar * psz, const ansichar * sz2)
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

      return strcmp(psz, sz2);

   }

}


inline i32 ansi_compare_ci(const ansichar * psz, const ansichar * sz2)
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

      return ansi_icmp(psz, sz2);

   }

}


inline i32 ansi_count_compare(const ansichar * psz, const ansichar * sz2, strsize len)
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

      return strncmp(psz, sz2, len);

   }

}


inline i32 ansi_count_compare_ci(const ansichar * psz, const ansichar * sz2, strsize len)
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

      return ansi_nicmp(psz, sz2, len);

   }

}



inline i32 ansi_collate(const ansichar * psz, const ansichar * sz2)
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

      return strcoll(psz, sz2);

   }

}


inline i32 ansi_collate_ci(const ansichar * psz, const ansichar * sz2)
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

      return ansi_icoll(psz, sz2);

   }

}


inline i32 ansi_count_collate(const ansichar * psz, const ansichar * sz2, strsize len)
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

      return ansi_ncoll(psz, sz2, len);

   }

}


inline i32 ansi_count_collate_ci(const ansichar * psz, const ansichar * sz2, strsize len)
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

      return ansi_nicoll(psz, sz2, len);

   }

}



inline const ansichar * ansi_scan(const ansichar * psz, const ansichar * find)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(find)) return FALSE;

   return strpbrk(psz, find);

}


inline ansichar * ansi_first_token(ansichar * psz, const ansichar * delimiters, ansichar ** action_context)
{

   return ansi_tok_r(psz, delimiters, action_context);

}



inline ansichar * ansi_next_token(const ansichar * delimiters, ansichar ** action_context)
{

   return ansi_tok_r(nullptr, delimiters, action_context);

}


inline i32 ansi_begins(const ansichar * psz, const ansichar * prefix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(prefix)) return FALSE;

   strsize len = strlen(prefix);

   if (len > (strsize)strlen(psz))
   {

      return FALSE;

   }

   return !strncmp(psz, prefix, len);

}


inline i32 ansi_begins_ci(const ansichar * psz, const ansichar * prefix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(prefix)) return FALSE;

   return !ansi_nicmp(psz, prefix, strlen(prefix));

}


inline const ansichar * ansi_begins_eat(const ansichar * psz, const ansichar * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   strsize len = strlen(prefix);

   if (strncmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline const ansichar * ansi_begins_eat_ci(const ansichar * psz, const ansichar * prefix)
{

   if (c_is_null(psz)) return nullptr;

   if (c_is_null(prefix)) return nullptr;

   strsize len = strlen(prefix);

   if (ansi_nicmp(psz, prefix, len))
   {

      return nullptr;

   }

   return psz + len;

}


inline i32 ansi_ends(const ansichar * psz, const ansichar * suffix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(suffix)) return FALSE;

   strsize len = strlen(suffix);

   strsize end = strlen(psz) - len;

   if(end < 0)
   {

      return FALSE;

   }

   return !strncmp(psz + end, suffix, len);

}


inline i32 ansi_ends_ci(const ansichar * psz, const ansichar * suffix)
{

   if (c_is_null(psz)) return FALSE;

   if (c_is_null(suffix)) return FALSE;

   strsize len = strlen(suffix);

   strsize end = strlen(psz) - len;

   if (end < 0)
   {

      return FALSE;

   }

   return !ansi_nicmp(psz + end, suffix, len);

}


inline const ansichar * ansi_find_char(const ansichar * psz, ansichar ch)
{

   if (c_is_null(psz)) return nullptr;

   return strchr(psz, ch);

}


inline const ansichar * ansi_find_char_reverse(const ansichar * psz, ansichar ch)
{

   if (c_is_null(psz)) return nullptr;

   return strrchr(psz, ch);

}


//inline const ansichar * ansi_concatenate_and_duplicate(const ansichar * psz1, const ansichar * psz2);
//inline const ansichar * ansi_concatenate_duplicate_and_free(const ansichar * psz1, ansichar * psz2);


inline void ansi_from_u64(ansichar * sz, u64 u, i32 iBase)
{

   __u64toansi(u, sz, iBase);

}


inline void ansi_from_i64(ansichar * sz, i64 i, i32 iBase)
{

   __i64toansi(i, sz, iBase);

}


inline void ansi_from_u32(ansichar * sz, u32 u, i32 iBase)
{

   __u64toansi(u, sz, iBase);

}


inline void ansi_from_i32(ansichar * sz, i32 i, i32 iBase)
{

   __i64toansi(i, sz, iBase);

}




inline i64 ansi_count_to_i64(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase, strsize srclen)
{

   auto len = ansi_length(psz);

   if (len <= 0)
   {

      return 0;

   }

   if (srclen < len)
   {

      if (!ansi_char_is_digit(*(psz + len - 1)))
      {

         auto pszDup = ansi_count_duplicate(psz, srclen);

         auto i = ansi_to_i64(pszDup, ppszEnd, iBase);

         if (ppszEnd)
         {

            *ppszEnd = (ansichar *)psz + (*ppszEnd - pszDup);

         }

         memory_free(pszDup);

         return i;

      }

   }

   return ansi_to_i64(psz, ppszEnd, iBase);

}


inline i64 ansi_to_i64(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase)
{

   return strtoll(psz, (ansichar **) ppszEnd, iBase);

}

inline u64 ansi_to_u64(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase)
{

   return strtoull(psz, (ansichar **) ppszEnd, iBase);

}


inline i32 ansi_to_i32(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS
   
   return strtol(psz, (ansichar **) ppszEnd, iBase);
   
#else
   
   long l = strtol(psz, (ansichar **) ppszEnd, iBase);
   
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


inline u32 ansi_to_u32(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS
   
   return strtoul(psz, (ansichar **) ppszEnd, iBase);
   
#else

   unsigned long ul = strtoul(psz, (ansichar **) ppszEnd, iBase);

   if(ul > UINT_MAX)
   {
      
      errno = ERANGE;
      
      return UINT_MAX;
      
   }

   return (::u32) ul;
   
#endif

}


inline i32 ansi_count_to_i32(const ansichar * psz, const ansichar ** ppszEnd, i32 iBase, strsize srclen)
{

   auto len = ansi_length(psz);

   if (len <= 0)
   {

      return 0;

   }

   if (srclen < len)
   {

      if (!ansi_char_is_digit(*(psz + len - 1)))
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


inline void ansi_reverse(ansichar * psz)
{

   reverse_memory(psz, strlen(psz));

}


inline void ansi_zero_pad(ansichar * psz, strsize lenPad)
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


inline ansichar * ansi_lower(ansichar * pch)
{

   ansichar * p = pch;

   while (*p != '\0')
   {

      *p = ansi_char_lowered(*p);

      p++;

   }

   return pch;

}


inline ansichar * ansi_upper(ansichar * pch)
{

   ansichar * p = pch;

   while (*p != '\0')
   {

      *p = ansi_char_uppered(*p);

      p++;

   }

   return pch;

}


inline const ansichar * ansi_concatenate_and_duplicate(const ansichar * psz1, const ansichar * psz2, int iFree1, int iFree2)
{

   strsize len1 = ansi_length(psz1);

   strsize len2 = ansi_length(psz2);

   strsize len = len1 + len2 + 1;

   auto * psz = (ansichar *)memory_alloc(len);

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


//CLASS_DECL_AQUA const ansichar * ansi_concatenate_duplicate_and_free(const ansichar * psz1, ansichar * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (ansichar *)memory_alloc(len);
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



//CLASS_DECL_AQUA const ansichar * ansi_concatenate_free_and_duplicate(ansichar * psz1, const ansichar * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (ansichar *)memory_alloc(len);
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



//CLASS_DECL_AQUA const ansichar * ansi_concatenat_free_duplicate_and_free(ansichar * psz1, ansichar * psz2)
//{
//
//   strsize len1 = strlen(psz1);
//
//   strsize len2 = strlen(psz2);
//
//   strsize len = len1 + len2 + 1;
//
//   auto * psz = (ansichar *)memory_alloc(len);
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



//inline void                   ansi_parse_command_line(ansichar * cmdstart, ansichar ** argv, ansichar * args, i32 * numargs, i32 * numchars);



inline const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen)
{

   if (c_is_null(src)) return nullptr;

   if (srclen <= 0) return nullptr;

   if (c_is_null(find)) return src;

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




inline const ansichar *       wildcard_next_stop(const ansichar * pszCriteria);

inline int_bool               wildcard_matches_criteria(const ansichar * pszCriteria, const ansichar * pszValue);
inline int_bool               wildcard_matches_criteria_ci(const ansichar * pszCriteria, const ansichar * pszValue);










