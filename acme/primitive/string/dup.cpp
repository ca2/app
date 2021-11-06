#include "framework.h"


//char * ansi_copy(char * dest, const char * cpy)
//{
//   if(cpy != nullptr && dest != nullptr)
//   {
//      return strcpy(dest, cpy);
//   }
//   //*dest = '\0';
//   return nullptr;
//}

//char * ansi_count_copy(char * dest, const char * cpy, ::count iLen)
//{
//   if (::is_null(dest)) return nullptr;
//   if (::is_null(cpy)) return nullptr;
//   return strncpy(dest, cpy, (size_t) iLen);
//   //while(*cpy != 0 && iLen-- > 0)
//     // *dest++ = *cpy++;
//}
//
//unichar * wide_count_copy(unichar * dest, const unichar * cpy, ::count iLen)
//{
//   if (::is_null(dest)) return nullptr;
//   if (::is_null(cpy)) return nullptr;
//   #ifdef WINDOWS
//   return wcsncpy(dest, cpy, (size_t)iLen);
//   #else
//   unichar * destParam = dest;
//   while(*cpy != 0 && iLen-- > 0)
//      *dest++ = *cpy++;
//      return destParam;
//      #endif
//}

//::count ansi_length(const char * str)
//{
//
//   if (::is_null(str))
//   {
//
//      return 0;
//
//   }
//
//   return strlen(str);
//
//}


//char * ansi_duplicate(const char * src)
//{
//   if (::is_null(src)) return nullptr;
//   ::count iLen = ansi_length(src);
//
//   char * dup = (char *) memory_allocate(iLen + 1);
//
//   ansi_copy(dup, src);
//
//   return dup;
//
//}

//char * ansi_count_copy(const char * src, ::count iLen)
//{
//   if (::is_null(src)) return nullptr;
//   char * dup = (char *) memory_allocate(iLen + 1);
//   ansi_count_copy(dup, src, iLen);
//   dup[iLen] = '\0';
//   return dup;
//}


//unichar * wide_copy(unichar * dest, const unichar * cpy)
//{
//
//   if (::is_null(dest)) return nullptr;
//   if (::is_null(cpy)) return nullptr;
//
//   #ifdef WINDOWS
//
//   return wcscpy(dest, cpy);
//
//#else
//unichar * destParam = dest;
//   while(*cpy != 0)
//      *dest++ = *cpy++;
//   *dest = L'\0';
//   return destParam;
//   #endif
//}

