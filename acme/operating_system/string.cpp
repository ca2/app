//
// Created by camilo on Jul/4/2023.
//
#include "framework.h"
#include <string.h>
#if defined(__APPLE__) || defined(__BSD__)
#include <errno.h>
#endif
#if defined(__BSD__)
#include <strings.h>
#endif

CLASS_DECL_ACME int ansi_icmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(scopedstr1, psz2);
#else
   return strcasecmp(scopedstr1, psz2);
#endif
}

CLASS_DECL_ACME int ansi_nicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s)
{
#ifdef WINDOWS
   return _strnicmp(scopedstr1, psz2, s);
#else
   return strncasecmp(scopedstr1, psz2, s);
#endif
}


CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(scopedstr1, psz2);
#else
   return strcasecmp(scopedstr1, psz2);
#endif
}

CLASS_DECL_ACME int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s)
{
#ifdef WINDOWS
   return _strnicmp(scopedstr1, psz2, s);
#else
   return strncasecmp(scopedstr1, psz2, s);
#endif
}


CLASS_DECL_ACME long long ansi_to_long_long(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase)
{

   return strtoll(scopedstr, (::ansi_character **)ppszEnd, iBase);

}


CLASS_DECL_ACME unsigned long long ansi_to_unsigned_long_long(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase)
{

   return strtoull(scopedstr, (::ansi_character **)ppszEnd, iBase);

}


CLASS_DECL_ACME int ansi_to_int(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase)
{

#ifdef WINDOWS

   return strtol(scopedstr, (::ansi_character **) ppszEnd, iBase);

#else

   long l = strtol(scopedstr, (::ansi_character **) ppszEnd, iBase);

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

   return (int) l;

#endif

}







CLASS_DECL_ACME unsigned int ansi_to_unsigned_int(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase)
{

#ifdef WINDOWS

   return strtoul(scopedstr, (::ansi_character **) ppszEnd, iBase);

#else

   unsigned long ul = strtoul(scopedstr, (::ansi_character **) ppszEnd, iBase);

   if(ul > 0xffffffffu)
   {

      errno = ERANGE;

      return 0xffffffffu;

   }

   return (unsigned int) ul;

#endif

}










CLASS_DECL_ACME character_count string_get_length(const ::ansi_character* psz) noexcept
{
   
   return strlen(scopedstr);
   
   
}



CLASS_DECL_ACME character_count utf8_len(const ::ansi_character * psz)
{
   if (::is_null(scopedstr)) return 0;
   
   return strlen(scopedstr);
   
   
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

   auto p = strpbrk(scopedstr, sep);

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



CLASS_DECL_ACME int compare_ignore_case(const char * left, const char * right, size_t len)
{

if (len)
{

#if defined(WIN32) || defined(WIN64)

return _strnicmp(left, right, len);

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

return case_insensitive_ansi_count_compare(left, right, len);

#else

return strncasecmp(left, right, len);

#endif

}
else
{

#if defined(WIN32) || defined(WIN64)

return _stricmp(left, right);

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

return case_insensitive_ansi_compare(left, right);

#else

return strcasecmp(left, right);

#endif

}

}


CLASS_DECL_ACME int compare_ignore_case(const string & left, const string & right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left.c_str(), right.c_str(), len);

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      return case_insensitive_ansi_count_compare(left.c_str(), right.c_str(), len);

#else

      return strncasecmp(left.c_str(), right.c_str(), len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left.c_str(), right.c_str());

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      return case_insensitive_ansi_compare(left.c_str(), right.c_str());

#else

      return strcasecmp(left.c_str(), right.c_str());

#endif

   }

}



CLASS_DECL_ACME int compare_ignore_case(const char * left, const string & right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left, right.c_str(), len);

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      return case_insensitive_ansi_count_compare(left, right.c_str(), len);

#else

      return strncasecmp(left, right.c_str(), len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left, right.c_str());

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      return case_insensitive_ansi_compare(left, right.c_str());

#else

      return strcasecmp(left, right.c_str());

#endif

   }

}


CLASS_DECL_ACME int compare_ignore_case(const string & left, const char * right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left.c_str(), right, len);

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      return case_insensitive_ansi_count_compare(left.c_str(), right, len);

#else

      return strncasecmp(left.c_str(), right, len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left.c_str(), right);

#elif defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      return case_insensitive_ansi_compare(left.c_str(), right);

#else

      return strcasecmp(left.c_str(), right);

#endif

   }

}



CLASS_DECL_ACME ::ansi_character * ansi_dup(const ::ansi_character * psz) { return _strdup(scopedstr); }

CLASS_DECL_ACME character_count ansi_len(const ::ansi_character * psz) { return strlen(scopedstr); }

CLASS_DECL_ACME character_count ansi_nlen(const ::ansi_character * psz, memsize len) { return strnlen(scopedstr, len); }

CLASS_DECL_ACME ::ansi_character * ansi_cat(::ansi_character * pszDst, const ::ansi_character * psz) { return strcat(scopedstrDst, psz); }

CLASS_DECL_ACME ::ansi_character * ansi_cpy(::ansi_character * pszDst, const ::ansi_character * psz) { return strcpy(scopedstrDst, psz); }

CLASS_DECL_ACME ::ansi_character * ansi_ncpy(::ansi_character * pszDst, const ::ansi_character * psz, character_count len) { return strncpy(scopedstrDst, psz, len); }

CLASS_DECL_ACME const ::ansi_character * ansi_chr(const ::ansi_character * psz1, ::ansi_character ch) { return strchr(scopedstr1, ch); }

CLASS_DECL_ACME const ::ansi_character * ansi_pbrk(const ::ansi_character * psz, const ::ansi_character * pszCharsToFind) { return strpbrk(scopedstr, pszCharsToFind); }


CLASS_DECL_ACME ::ansi_character * ansi_tok_r(::ansi_character * psz, const ::ansi_character * sep, ::ansi_character ** state)
{

#if defined(WINDOWS)

    return strtok_s(scopedstr, sep, state);

#else

    return strtok_r(scopedstr, sep, state);

#endif

}

CLASS_DECL_ACME const ::ansi_character * ansi_rchr(const ::ansi_character * psz1, ::ansi_character ch) { return strrchr(scopedstr1, ch); }

CLASS_DECL_ACME int ansi_cmp(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcmp(scopedstr1, psz2); }

CLASS_DECL_ACME int ansi_ncmp(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s) { return strncmp(scopedstr1, psz2, s); }

CLASS_DECL_ACME const ::ansi_character * ansi_str(const ::ansi_character * psz, const ::ansi_character * pszFind) { return strstr(scopedstr, pszFind); }



CLASS_DECL_ACME int ansi_coll(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcmp(scopedstr1, psz2); }

CLASS_DECL_ACME int ansi_ncoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s) { return strncmp(scopedstr1, psz2, s); }

CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2);

CLASS_DECL_ACME int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, character_count s);

CLASS_DECL_ACME character_count ansi_spn(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strspn(scopedstr1, psz2); }

CLASS_DECL_ACME character_count ansi_cspn(const ::ansi_character * psz1, const ::ansi_character * psz2) { return strcspn(scopedstr1, psz2); }



CLASS_DECL_ACME const ::ansi_character * ansi_const_last_char(const ::ansi_character * psz)
{

   return ::is_null(scopedstr) ? nullptr : psz + strlen(scopedstr);

}


//
//CLASS_DECL_ACME ::ansi_character * ansi_copy(::ansi_character * psz, const ::ansi_character * cpy)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (::is_null(cpy)) return nullptr;
//
//   return strcpy(scopedstr, cpy);
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_count_copy(::ansi_character * psz, const ::ansi_character * cpy, character_count len)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (::is_null(cpy)) return nullptr;
//
//   if (len < 0) return nullptr;
//
//   return strncpy(scopedstr, cpy, len);
//
//}
//
//
//CLASS_DECL_ACME character_count ansi_length(const ::ansi_character * psz)
//{
//
//   if (::is_null(scopedstr)) return 0;
//
//   return strlen(scopedstr);
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_duplicate(const ::ansi_character * psz)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   auto pszDup = (::ansi_character *) ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(strlen(scopedstr) + 1);
//
//   strcpy(scopedstrDup, psz);
//
//   return pszDup;
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_count_duplicate(const ::ansi_character * psz, character_count len)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (len < 0) return nullptr;
//
//   auto pszDup = (::ansi_character *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len + 1);
//
//   strncpy(scopedstrDup, psz, len);
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
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (::is_null(find)) return nullptr;
//
//   return strstr(scopedstr, find);
//
//}
//
//
//
//CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_find_string(const ::ansi_character * psz, const ::ansi_character * find)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
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
//      if (!ansi_nicmp(scopedstr, find, len))
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
//CLASS_DECL_ACME const ::ansi_character * ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, character_count len)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (len > (character_count) strlen(find)) return nullptr;
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
//      if (!strncmp(scopedstr, find, len))
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
//CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_count_find_string(const ::ansi_character * psz, const ::ansi_character * find, character_count len)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (len > (character_count)strlen(find)) return nullptr;
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
//      if (!ansi_nicmp(scopedstr, find, len))
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
//CLASS_DECL_ACME int ansi_compare(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(scopedstr))
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
//      return strcmp(scopedstr, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME int case_insensitive_ansi_compare(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(scopedstr))
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
//      return ansi_icmp(scopedstr, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME int ansi_count_compare(const ::ansi_character * psz, const ::ansi_character * sz2, character_count len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(scopedstr))
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
//      return strncmp(scopedstr, sz2, len);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME int case_insensitive_ansi_count_compare(const ::ansi_character * psz, const ::ansi_character * sz2, character_count len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(scopedstr))
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
//      return ansi_nicmp(scopedstr, sz2, len);
//
//   }
//
//}
//
//
//
//CLASS_DECL_ACME int ansi_collate(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(scopedstr))
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
//      return strcoll(scopedstr, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME int case_insensitive_ansi_collate(const ::ansi_character * psz, const ::ansi_character * sz2)
//{
//
//   if (::is_null(scopedstr))
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
//      return ansi_icoll(scopedstr, sz2);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME int ansi_count_collate(const ::ansi_character * psz, const ::ansi_character * sz2, character_count len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(scopedstr))
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
//      return ansi_ncoll(scopedstr, sz2, len);
//
//   }
//
//}
//
//
//CLASS_DECL_ACME int case_insensitive_ansi_count_collate(const ::ansi_character * psz, const ::ansi_character * sz2, character_count len)
//{
//
//   if (len < 0)
//   {
//
//      return 0;
//
//   }
//
//   if (::is_null(scopedstr))
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
//      return ansi_nicoll(scopedstr, sz2, len);
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
//   if (::is_empty(scopedstr)) return psz;
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
//   return string_find_first_in(scopedstr, pszSeparators);
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * _ansi_find_first_in(const ::ansi_character * psz, const ::ansi_character * pszSeparators)
//{
//
//   return _string_find_first_in(scopedstr, pszSeparators);
//
//}
//
//
//CLASS_DECL_ACME ::ansi_character * ansi_first_token(::ansi_character * psz, const ::ansi_character * delimiters, ::ansi_character ** action_context)
//{
//
//   return ansi_tok_r(scopedstr, delimiters, action_context);
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
//CLASS_DECL_ACME int ansi_begins(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(scopedstr)) return false;
//
//   if (::is_null(prefix)) return false;
//
//   character_count len = strlen(prefix);
//
//   if (len > (character_count)strlen(scopedstr))
//   {
//
//      return false;
//
//   }
//
//   return !strncmp(scopedstr, prefix, len);
//
//}
//
//
//CLASS_DECL_ACME int case_insensitive_ansi_begins(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(scopedstr)) return false;
//
//   if (::is_null(prefix)) return false;
//
//   return !ansi_nicmp(scopedstr, prefix, strlen(prefix));
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_begins_eat(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (::is_null(prefix)) return nullptr;
//
//   character_count len = strlen(prefix);
//
//   if (strncmp(scopedstr, prefix, len))
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
//CLASS_DECL_ACME const ::ansi_character * case_insensitive_ansi_begins_eat(const ::ansi_character * psz, const ::ansi_character * prefix)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   if (::is_null(prefix)) return nullptr;
//
//   character_count len = strlen(prefix);
//
//   if (ansi_nicmp(scopedstr, prefix, len))
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
//CLASS_DECL_ACME int ansi_ends(const ::ansi_character * psz, const ::ansi_character * suffix)
//{
//
//   if (::is_null(scopedstr)) return false;
//
//   if (::is_null(suffix)) return false;
//
//   character_count len = strlen(suffix);
//
//   character_count end = strlen(scopedstr) - len;
//
//   if(end < 0)
//   {
//
//      return false;
//
//   }
//
//   return !strncmp(scopedstr + end, suffix, len);
//
//}
//
//
//CLASS_DECL_ACME int case_insensitive_ansi_ends(const ::ansi_character * psz, const ::ansi_character * suffix)
//{
//
//   if (::is_null(scopedstr)) return false;
//
//   if (::is_null(suffix)) return false;
//
//   character_count len = strlen(suffix);
//
//   character_count end = strlen(scopedstr) - len;
//
//   if (end < 0)
//   {
//
//      return false;
//
//   }
//
//   return !ansi_nicmp(scopedstr + end, suffix, len);
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_find_char(const ::ansi_character * psz, ::ansi_character ch)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   return strchr(scopedstr, ch);
//
//}
//
//
//CLASS_DECL_ACME const ::ansi_character * ansi_find_char_reverse(const ::ansi_character * psz, ::ansi_character ch)
//{
//
//   if (::is_null(scopedstr)) return nullptr;
//
//   return strrchr(scopedstr, ch);
//
//}
//
//
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_and_duplicate(const ::ansi_character * psz1, const ::ansi_character * psz2);
////CLASS_DECL_ACME const ::ansi_character * ansi_concatenate_duplicate_and_free(const ::ansi_character * psz1, ::ansi_character * psz2);
//
//
//CLASS_DECL_ACME void ansi_from_unsigned_long_long(::ansi_character * sz, unsigned long long u, int iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __u64toansi(u, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME void ansi_from_long_long(::ansi_character * sz, long long i, int iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __long_longtoansi(i, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME void ansi_from_ui(::ansi_character * sz, unsigned int u, int iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __u64toansi(u, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME void ansi_from_i(::ansi_character * sz, int i, int iBase, enum_digit_case edigitcase)
//{
//
//   ::ansi_character * end;
//
//   __long_longtoansi(i, sz, iBase, edigitcase, end);
//
//}
//
//
//CLASS_DECL_ACME long long ansi_count_to_long_long(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase, character_count srclen)
//{
//
//   auto len = ansi_length(scopedstr);
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
//      if (!ansi_char_isdigit(*(scopedstr + len - 1)))
//      {
//
//         auto pszDup = ansi_count_duplicate(scopedstr, srclen);
//
//         auto i = ansi_to_long_long(scopedstrDup, ppszEnd, iBase);
//
//         if (ppszEnd)
//         {
//
//            *ppszEnd = (::ansi_character *)psz + (*ppszEnd - pszDup);
//
//         }
//
//         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstrDup);
//
//         return i;
//
//      }
//
//   }
//
//   return ansi_to_long_long(scopedstr, ppszEnd, iBase);
//
//}
//
//
//CLASS_DECL_ACME int ansi_count_to_int(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, int iBase, character_count srclen)
//{
//
//   auto len = ansi_length(scopedstr);
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
//      if (!ansi_char_isdigit(*(scopedstr + len - 1)))
//      {
//
//         auto pszDup = ansi_count_duplicate(scopedstr, srclen);
//
//         auto i = ansi_to_int(scopedstrDup, ppszEnd, iBase);
//
//         if (ppszEnd)
//         {
//
//            *ppszEnd = psz + (*ppszEnd - pszDup);
//
//         }
//
//         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstrDup);
//
//         return i;
//
//      }
//
//   }
//
//   return ansi_to_int(scopedstr, ppszEnd, iBase);
//
//}
//
//
//CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz)
//{
//
//   reverse_memory(scopedstr, string_safe_length(scopedstr));
//
//}
//
//
//CLASS_DECL_ACME void ansi_reverse(::ansi_character * psz, character_count size)
//{
//
//   reverse_memory(scopedstr, size);
//
//}
//
//
//CLASS_DECL_ACME void ansi_zero_pad(::ansi_character * psz, character_count lenPad)
//{
//
//   character_count len = strlen(scopedstr);
//
//   character_count countZero = lenPad - len;
//
//   if (countZero <= 0)
//   {
//
//      return;
//
//   }
//
//   for (character_count i = len; i >= 0; i--)
//   {
//
//      psz[countZero + i] = psz[i];
//
//   }
//
//   for(character_count i = 0; i < countZero; i++)
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
//   character_count len1 = ansi_length(scopedstr1);
//
//   character_count len2 = ansi_length(scopedstr2);
//
//   character_count len = len1 + len2 + 1;
//
//   auto * psz = (::ansi_character *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
//
//   *psz = '\0';
//
//   if (len1 > 0)
//   {
//
//      strcat(scopedstr, psz1);
//
//      if (iFree1 > 0)
//      {
//
//         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void *) psz1);
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
//      strcat(scopedstr, psz2);
//
//      if (iFree2 > 0)
//      {
//
//         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void *)psz2);
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
////   character_count len1 = strlen(scopedstr1);
////
////   character_count len2 = strlen(scopedstr2);
////
////   character_count len = len1 + len2 + 1;
////
////   auto * psz = (::ansi_character *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
////
////   *psz = '\0';
////
////   if (len1 > 0)
////   {
////
////      strcat(scopedstr, psz1);
////
////   }
////
////   if (len2)
////   {
////
////      strcat(scopedstr, psz2);
////
////      ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr2);
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
////   character_count len1 = strlen(scopedstr1);
////
////   character_count len2 = strlen(scopedstr2);
////
////   character_count len = len1 + len2 + 1;
////
////   auto * psz = (::ansi_character *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
////
////   *psz = '\0';
////
////   if (len1 > 0)
////   {
////
////      strcat(scopedstr, psz1);
////
////      ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr1);
////
////   }
////
////   if (len2)
////   {
////
////      strcat(scopedstr, psz2);
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
////   character_count len1 = strlen(scopedstr1);
////
////   character_count len2 = strlen(scopedstr2);
////
////   character_count len = len1 + len2 + 1;
////
////   auto * psz = (::ansi_character *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(len);
////
////   *psz = '\0';
////
////   if (len1 > 0)
////   {
////
////      strcat(scopedstr, psz1);
////
////      ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr1);
////
////   }
////
////   if (len2)
////   {
////
////      strcat(scopedstr, psz2);
////
////      ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(scopedstr2);
////
////   }
////
////   return psz;
////
////}
//
//
//
////CLASS_DECL_ACME void                   ansi_parse_command_line(::ansi_character * cmdstart, ::ansi_character ** argv, ::ansi_character * args, int * numargs, int * numchars);
//
//
//
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
//#if defined(WINDOWS) || defined(__APPLE__)
//
//   for (const unsigned char * p = (const unsigned char *) src; srclen >= findlen;  p++, srclen--)
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
//CLASS_DECL_ACME int_bool               case_insensitive_wildcard_matches_criteria(const ::ansi_character * pszCriteria, const ::ansi_character * pszValue);
//
//
//
//
CLASS_DECL_ACME character_count string_safe_length(const ::ansi_character * psz) noexcept
{
   
   if (::is_null(scopedstr)) return 0; return string_get_length(scopedstr); 

}
//
//
//
//






