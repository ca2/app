//
// Created by camilo on Jul/4/2023.
//
#include "framework.h"


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

inline int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
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
