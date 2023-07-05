//
// Created by camilo on Jul/4/2023.
//
#include "framework.h"
#include <string.h>
#if defined(__APPLE__)
#include <errno.h>
#endif

CLASS_DECL_ACME int ansi_icmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

CLASS_DECL_ACME int ansi_nicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}


CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

CLASS_DECL_ACME int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}


CLASS_DECL_ACME i64 ansi_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

   return strtoll(psz, (::ansi_character **)ppszEnd, iBase);

}


CLASS_DECL_ACME u64 ansi_to_u64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

   return strtoull(psz, (::ansi_character **)ppszEnd, iBase);

}


CLASS_DECL_ACME i32 ansi_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS

   return strtol(psz, (::ansi_character **) ppszEnd, iBase);

#else

   long l = strtol(psz, (::ansi_character **) ppszEnd, iBase);

   if(l > I32_MAXIMUM)
   {

      errno = ERANGE;

      return I32_MAXIMUM;

   }
   else if(l < I32_MINIMUM)
   {

      errno = ERANGE;

      return I32_MINIMUM;

   }

   return (::i32) l;

#endif

}







CLASS_DECL_ACME ::u32 ansi_to_u32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS

   return strtoul(psz, (::ansi_character **) ppszEnd, iBase);

#else

   unsigned long ul = strtoul(psz, (::ansi_character **) ppszEnd, iBase);

   if(ul > 0xffffffffu)
   {

      errno = ERANGE;

      return 0xffffffffu;

   }

   return (::u32) ul;

#endif

}










CLASS_DECL_ACME strsize string_get_length(const ::ansi_character* psz) noexcept
{
   
   return strlen(psz);
   
   
}



CLASS_DECL_ACME strsize utf8_len(const ::ansi_character * psz)
{
   if (::is_null(psz)) return 0;
   
   return strlen(psz);
   
   
}



CLASS_DECL_ACME ::ansi_character * __ansitok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state)
{

   if (!psz)
   {

      psz = *state;

      if (!psz)
      {

         return nullptr;

      }

   }

   auto p = strpbrk(psz, sep);

   if (p)
   {

      *p = (::ansi_character)(0);

      *state = p + 1;

   }
   else
   {

      *state = nullptr;

   }

   return psz;

}



CLASS_DECL_ACME i32 compare_ignore_case(const char * left, const char * right, size_t len)
{

if (len)
{

#if defined(WIN32) || defined(WIN64)

return _strnicmp(left, right, len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

return ansi_count_compare_ci(left, right, len);

#else

return strncasecmp(left, right, len);

#endif

}
else
{

#if defined(WIN32) || defined(WIN64)

return _stricmp(left, right);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

return ansi_compare_ci(left, right);

#else

return strcasecmp(left, right);

#endif

}

}


CLASS_DECL_ACME i32 compare_ignore_case(const string & left, const string & right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left.c_str(), right.c_str(), len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_count_compare_ci(left.c_str(), right.c_str(), len);

#else

      return strncasecmp(left.c_str(), right.c_str(), len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left.c_str(), right.c_str());

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_compare_ci(left.c_str(), right.c_str());

#else

      return strcasecmp(left.c_str(), right.c_str());

#endif

   }

}



CLASS_DECL_ACME i32 compare_ignore_case(const char * left, const string & right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left, right.c_str(), len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_count_compare_ci(left, right.c_str(), len);

#else

      return strncasecmp(left, right.c_str(), len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left, right.c_str());

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_compare_ci(left, right.c_str());

#else

      return strcasecmp(left, right.c_str());

#endif

   }

}


CLASS_DECL_ACME i32 compare_ignore_case(const string & left, const char * right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left.c_str(), right, len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_count_compare_ci(left.c_str(), right, len);

#else

      return strncasecmp(left.c_str(), right, len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left.c_str(), right);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_compare_ci(left.c_str(), right);

#else

      return strcasecmp(left.c_str(), right);

#endif

   }

}



CLASS_DECL_ACME ::ansi_character * ansi_dup(const ::ansi_character * psz) { return _strdup(psz); }

CLASS_DECL_ACME strsize ansi_len(const ::ansi_character * psz) { return strlen(psz); }

CLASS_DECL_ACME ::ansi_character * ansi_cat(::ansi_character * pszDst, const ::ansi_character * psz) { return strcat(pszDst, psz); }

CLASS_DECL_ACME ::ansi_character * ansi_cpy(::ansi_character * pszDst, const ::ansi_character * psz) { return strcpy(pszDst, psz); }

CLASS_DECL_ACME ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const ::ansi_character * psz, strsize len) { return strncpy(pszDst, psz, len); }

CLASS_DECL_ACME const ::ansi_character * ansi_chr(const ::ansi_character * psz1, ::ansi_character ch) { return strchr(psz1, ch); }

CLASS_DECL_ACME ::ansi_character * ansi_pbrk(const ::ansi_character * psz, const ::ansi_character * pszCharsToFind) { return strpbrk(psz, pszCharsToFind); }


CLASS_DECL_ACME ::ansi_character * ansi_tok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state)
{

#if defined(WINDOWS)

    return strtok_s(psz, sep, state);

#else

    return strtok_r(psz, sep, state);

#endif

}

CLASS_DECL_ACME const ::ansi_character * ansi_rchr(const ::ansi_character * psz1, ::ansi_character ch) { return strrchr(psz1, ch); }

CLASS_DECL_ACME int ansi_cmp(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcmp(psz1, psz2); }

CLASS_DECL_ACME int ansi_ncmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s) { return strncmp(psz1, psz2, s); }

CLASS_DECL_ACME const ::ansi_character * ansi_str(const ::ansi_character * psz, const ::ansi_character * pszFind) { return strstr(psz, pszFind); }



CLASS_DECL_ACME int ansi_coll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcmp(psz1, psz2); }

CLASS_DECL_ACME int ansi_ncoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s) { return strncmp(psz1, psz2, s); }

CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s);

CLASS_DECL_ACME strsize ansi_spn(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strspn(psz1, psz2); }

CLASS_DECL_ACME strsize ansi_cspn(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcspn(psz1, psz2); }



CLASS_DECL_ACME const ::ansi_character * ansi_const_last_char(const ::ansi_character * psz)
{

   return ::is_null(psz) ? nullptr : psz + strlen(psz);

}


//
//CLASS_DECL_ACME ::ansi_character * ansi_copy(::ansi_character * psz, const ::ansi_character * cpy)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (::is_null(cpy)) return nullptr;
//
//   return strcpy(psz, cpy);
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_count_copy(::ansi_character * psz, const ::ansi_character * cpy, strsize len)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (::is_null(cpy)) return nullptr;
//
//   if (len < 0) return nullptr;
//
//   return strncpy(psz, cpy, len);
//
//}
//
//
//CLASS_DECL_ACME strsize ansi_length(const ::ansi_character * psz)
//{
//
//   if (::is_null(psz)) return 0;
//
//   return strlen(psz);
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_duplicate(const ::ansi_character * psz)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   auto pszDup = (::ansi_character *) memory_allocate(strlen(psz) + 1);
//
//   strcpy(pszDup, psz);
//
//   return pszDup;
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_count_duplicate(const ::ansi_character * psz, strsize len)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (len < 0) return nullptr;
//
//   auto pszDup = (::ansi_character *)memory_allocate(len + 1);
//
//   strncpy(pszDup, psz, len);
//
//   pszDup[len] = '\0';
//
//   return pszDup;
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (::is_null(find)) return nullptr;
//
//   return strstr(psz, find);
//
//}
//
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_find_string_ci(const ::ansi_character * psz, const ::ansi_character * find)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   auto len = strlen(find);
//
//   if (len <= 0)
//   {
//
//      return psz;
//
//   }
//
//   while (*psz != '\0')
//   {
//
//      if (!ansi_nicmp(psz, find, len))
//      {
//
//         return psz;
//
//      }
//
//      psz++;
//
//   }
//
//   return nullptr;
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, strsize len)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (len > (strsize) strlen(find)) return nullptr;
//
//   if (len <= 0)
//   {
//
//      return psz;
//
//   }
//
//   while (*psz != '\0')
//   {
//
//      if (!strncmp(psz, find, len))
//      {
//
//         return psz;
//
//      }
//
//      psz++;
//
//   }
//
//   return nullptr;
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_count_find_string_ci(const ::ansi_character * psz, const ::ansi_character * find, strsize len)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (len > (strsize)strlen(find)) return nullptr;
//
//   if (len <= 0)
//   {
//
//      return psz;
//
//   }
//
//   while (*psz != '\0')
//   {
//
//      if (!ansi_nicmp(psz, find, len))
//      {
//
//         return psz;
//
//      }
//
//      psz++;
//
//   }
//
//   return nullptr;
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_compare(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return strcmp(psz, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_compare_ci(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return ansi_icmp(psz, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_count_compare(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return strncmp(psz, sz2, len);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_count_compare_ci(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return ansi_nicmp(psz, sz2, len);
//
//   }
//
//}
//
//
//
//CLASS_DECL_ACME i32 ansi_collate(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return strcoll(psz, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_collate_ci(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return ansi_icoll(psz, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_count_collate(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return ansi_ncoll(psz, sz2, len);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_count_collate_ci(const ::ansi_character * psz, const ::ansi_character * sz2, strsize len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(psz))
//   {
//
//      if (::is_null(sz2))
//      {
//
//         return 0;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else if (::is_null(sz2))
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return ansi_nicoll(psz, sz2, len);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * _ansi_scan(const ::ansi_character * psz, const ::ansi_character * find)
//{
//
//   return ansi_pbrk((::ansi_character *) psz, find);
//
//}
//
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_scan(const ::ansi_character * psz, const ::ansi_character * find)
//{
//
//   if (::is_empty(psz)) return psz;
//
//   if (::is_empty(find)) return psz;
//   
//   while(*psz)
//   {
//      
//      if(strchr(find, *psz))
//      {
//         
//         return psz;
//         
//      }
//      
//      psz++;
//      
//   }
//
//   return nullptr;
//
//}
//

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
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_first_token(::ansi_character * psz, const ::ansi_character * delimiters, ::ansi_character ** action_context)
//{
//
//   return ansi_tok_r(psz, delimiters, action_context);
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_next_token(const ::ansi_character * delimiters, ::ansi_character ** action_context)
//{
//
//   return ansi_tok_r(nullptr, delimiters, action_context);
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_begins(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(psz)) return false;
//
//   if (::is_null(prefix)) return false;
//
//   strsize len = strlen(prefix);
//
//   if (len > (strsize)strlen(psz))
//   {
//
//      return false;
//
//   }
//
//   return !strncmp(psz, prefix, len);
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_begins_ci(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(psz)) return false;
//
//   if (::is_null(prefix)) return false;
//
//   return !ansi_nicmp(psz, prefix, strlen(prefix));
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_begins_eat(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (::is_null(prefix)) return nullptr;
//
//   strsize len = strlen(prefix);
//
//   if (strncmp(psz, prefix, len))
//   {
//
//      return nullptr;
//
//   }
//
//   return psz + len;
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_begins_eat_ci(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   if (::is_null(prefix)) return nullptr;
//
//   strsize len = strlen(prefix);
//
//   if (ansi_nicmp(psz, prefix, len))
//   {
//
//      return nullptr;
//
//   }
//
//   return psz + len;
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_ends(const ::ansi_character * psz, const ::ansi_character * suffix)
//{
//
//   if (::is_null(psz)) return false;
//
//   if (::is_null(suffix)) return false;
//
//   strsize len = strlen(suffix);
//
//   strsize end = strlen(psz) - len;
//
//   if(end < 0)
//   {
//
//      return false;
//
//   }
//
//   return !strncmp(psz + end, suffix, len);
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_ends_ci(const ::ansi_character * psz, const ::ansi_character * suffix)
//{
//
//   if (::is_null(psz)) return false;
//
//   if (::is_null(suffix)) return false;
//
//   strsize len = strlen(suffix);
//
//   strsize end = strlen(psz) - len;
//
//   if (end < 0)
//   {
//
//      return false;
//
//   }
//
//   return !ansi_nicmp(psz + end, suffix, len);
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_find_char(const ::ansi_character * psz, ::ansi_character ch)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   return strchr(psz, ch);
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_find_char_reverse(const ::ansi_character * psz, ::ansi_character ch)
//{
//
//   if (::is_null(psz)) return nullptr;
//
//   return strrchr(psz, ch);
//
//}
//
//
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2);
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_duplicate_and_free(const ::ansi_character * psz1, ::ansi_character * psz2);
//
//
//CLASS_DECL_ACME void ansi_from_u64(::ansi_character * sz, u64 u, i32 iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __u64toansi(u, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME void ansi_from_i64(::ansi_character * sz, i64 i, i32 iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __i64toansi(i, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME void ansi_from_u32(::ansi_character * sz, u32 u, i32 iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __u64toansi(u, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME void ansi_from_i32(::ansi_character * sz, i32 i, i32 iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __i64toansi(i, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME i64 ansi_count_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase, strsize srclen)
//{
//
//   auto len = ansi_length(psz);
//
//   if (len <= 0)
//   {
//
//      return 0;
//
//   }
//
//   if (srclen < len)
//   {
//
//      if (!ansi_char_isdigit(*(psz + len - 1)))
//      {
//
//         auto pszDup = ansi_count_duplicate(psz, srclen);
//
//         auto i = ansi_to_i64(pszDup, ppszEnd, iBase);
//
//         if (ppszEnd)
//         {
//
//            *ppszEnd = (::ansi_character *)psz + (*ppszEnd - pszDup);
//
//         }
//
//         memory_free(pszDup);
//
//         return i;
//
//      }
//
//   }
//
//   return ansi_to_i64(psz, ppszEnd, iBase);
//
//}
//
//
//CLASS_DECL_ACME i32 ansi_count_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase, strsize srclen)
//{
//
//   auto len = ansi_length(psz);
//
//   if (len <= 0)
//   {
//
//      return 0;
//
//   }
//
//   if (srclen < len)
//   {
//
//      if (!ansi_char_isdigit(*(psz + len - 1)))
//      {
//
//         auto pszDup = ansi_count_duplicate(psz, srclen);
//
//         auto i = ansi_to_i32(pszDup, ppszEnd, iBase);
//
//         if (ppszEnd)
//         {
//
//            *ppszEnd = psz + (*ppszEnd - pszDup);
//
//         }
//
//         memory_free(pszDup);
//
//         return i;
//
//      }
//
//   }
//
//   return ansi_to_i32(psz, ppszEnd, iBase);
//
//}
//
//
//CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz)
//{
//
//   reverse_memory(psz, string_safe_length(psz));
//
//}
//
//
//CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz, strsize size)
//{
//
//   reverse_memory(psz, size);
//
//}
//
//
//CLASS_DECL_ACME void ansi_zero_pad(::ansi_character * psz, strsize lenPad)
//{
//
//   strsize len = strlen(psz);
//
//   strsize countZero = lenPad - len;
//
//   if (countZero <= 0)
//   {
//
//      return;
//
//   }
//
//   for (strsize i = len; i >= 0; i--)
//   {
//
//      psz[countZero + i] = psz[i];
//
//   }
//
//   for(strsize i = 0; i < countZero; i++)
//   {
//
//      psz[i] = '0';
//
//   }
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_lower(::ansi_character * pch)
//{
//
//   ::ansi_character * p = pch;
//
//   while (*p != '\0')
//   {
//
//      *p = ansi_char_tolower(*p);
//
//      p++;
//
//   }
//
//   return pch;
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_upper(::ansi_character * pch)
//{
//
//   ::ansi_character * p = pch;
//
//   while (*p != '\0')
//   {
//
//      *p = ansi_char_toupper(*p);
//
//      p++;
//
//   }
//
//   return pch;
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2, int iFree1, int iFree2)
//{
//
//   strsize len1 = ansi_length(psz1);
//
//   strsize len2 = ansi_length(psz2);
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
//      if (iFree1 > 0)
//      {
//
//         memory_free((void *) psz1);
//
//      }
//      else if (iFree1 < 0)
//      {
//
//         free((void *)psz1);
//
//      }
//
//   }
//
//   if (len2)
//   {
//
//      strcat(psz, psz2);
//
//      if (iFree2 > 0)
//      {
//
//         memory_free((void *)psz2);
//
//      }
//      else if (iFree2 < 0)
//      {
//
//         free((void *)psz2);
//
//      }
//
//   }
//
//   return psz;
//
//}
//
//
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_duplicate_and_free(const ::ansi_character * psz1, ::ansi_character * psz2)
////{
////
////   strsize len1 = strlen(psz1);
////
////   strsize len2 = strlen(psz2);
////
////   strsize len = len1 + len2 + 1;
////
////   auto * psz = (::ansi_character *)memory_allocate(len);
////
////   *psz = '\0';
////
////   if (len1 > 0)
////   {
////
////      strcat(psz, psz1);
////
////   }
////
////   if (len2)
////   {
////
////      strcat(psz, psz2);
////
////      memory_free(psz2);
////
////   }
////
////   return psz;
////
////}
//
//
//
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_free_and_duplicate(::ansi_character * psz1, const ::ansi_character * psz2)
////{
////
////   strsize len1 = strlen(psz1);
////
////   strsize len2 = strlen(psz2);
////
////   strsize len = len1 + len2 + 1;
////
////   auto * psz = (::ansi_character *)memory_allocate(len);
////
////   *psz = '\0';
////
////   if (len1 > 0)
////   {
////
////      strcat(psz, psz1);
////
////      memory_free(psz1);
////
////   }
////
////   if (len2)
////   {
////
////      strcat(psz, psz2);
////
////   }
////
////   return psz;
////
////}
//
//
//
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenat_free_duplicate_and_free(::ansi_character * psz1, ::ansi_character * psz2)
////{
////
////   strsize len1 = strlen(psz1);
////
////   strsize len2 = strlen(psz2);
////
////   strsize len = len1 + len2 + 1;
////
////   auto * psz = (::ansi_character *)memory_allocate(len);
////
////   *psz = '\0';
////
////   if (len1 > 0)
////   {
////
////      strcat(psz, psz1);
////
////      memory_free(psz1);
////
////   }
////
////   if (len2)
////   {
////
////      strcat(psz, psz2);
////
////      memory_free(psz2);
////
////   }
////
////   return psz;
////
////}
//
//
//
////CLASS_DECL_ACME void                   ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, i32 * numargs, i32 * numchars);
//
//
//
//CLASS_DECL_ACME const void * memory_find_memory(const void * src, strsize srclen, const void * find, strsize findlen)
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
//#if defined(WINDOWS) || defined(__APPLE__)
//
//   for (const ::u8 * p = (const ::u8 *) src; srclen >= findlen;  p++, srclen--)
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
//
//
//
//
//CLASS_DECL_ACME const ::ansi_character *       wildcard_next_stop(const ::ansi_character * pszCriteria);
//
//CLASS_DECL_ACME int_bool               wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
//CLASS_DECL_ACME int_bool               wildcard_matches_criteria_ci(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
//
//
//
//
CLASS_DECL_ACME strsize string_safe_length(const ::ansi_character * psz) noexcept
{
   
   if (::is_null(psz)) return 0; return string_get_length(psz); 

}
//
//
//
//
