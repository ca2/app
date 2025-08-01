#pragma once


//  OS ANCIENT          strcpy
//  OS ANCIENT WIDE     wcscpy

//  ancient
//  scaffold implementation: sometimes OS doesn't implement a OS ancient function or
//                           whole certain wd16/32 version, the scaffold implementation
//                           supplies a "local"/alternative implementation (even if the
//                           OS already implements it)
//  scaffold-1          __ansicpy
//  scaffold-2          __wd16cpy
//  scaffold-3          __wd32cpy


//  coupling
//  ready-to-use :      inlined version of either OS version (default) or scaffold version
//                      (when there is no OS version).
//  ready-to-use-1      ansi_cpy
//  ready-to-use-2      wd16_cpy
//  ready-to-use-3      wd32_cpy


//inline character_count strlen_s_dup(const ::scoped_string & scopedstr, character_count nsize);


template < primitive_character CHARACTER >
inline const CHARACTER * _unicode_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
{

   int len1;

   int len2;

   while (*psz)
   {

      auto index = unicode_index_length(psz, len1);

      auto pszCharactersScan = pszCharacters;

      do
      {

         if (index == unicode_index_length(pszCharactersScan, len2))
         {

            return psz;

         }

         pszCharactersScan += len2;

      } while (*pszCharactersScan);

      psz += len1;

   }

   return psz;

}


template < primitive_character CHARACTER >
const CHARACTER * unicode_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
{

   if (::is_empty(psz))
   {

      return psz;

   }

   if (::is_empty(pszCharacters))
   {

      return psz;

   }

   return _unicode_scan(psz, pszCharacters);

}


template < primitive_character CHARACTER >
const CHARACTER * _string_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
{

   //int len1;

   while (*psz)
   {

      auto ch = *psz;

      auto pszCharactersScan = pszCharacters;

      do
      {

         if (ch == *pszCharactersScan)
         {

            return psz;

         }

         pszCharactersScan++;

      } while (*pszCharactersScan);

      psz++;

   }

   return psz;

}


template < primitive_character CHARACTER >
const CHARACTER * string_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
{

   if (::is_empty(psz))
   {

      return psz;

   }

   if (::is_empty(pszCharacters))
   {

      return psz;

   }

   return _string_scan(psz, pszCharacters);

}


//template < primitive_character CHARACTER >
//inline const CHARACTER * _unicode_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
//{
//
//   int len1;
//
//   int len2;
//
//   while (*psz)
//   {
//
//      auto index = unicode_index_length(psz, len1);
//
//      auto pszCharactersScan = pszCharacters;
//
//      do
//      {
//
//         if (index == unicode_index_length(pszCharactersScan, len2))
//         {
//
//            return psz;
//
//         }
//
//         pszCharactersScan += len2;
//
//      } while (*pszCharactersScan);
//
//      psz += len1;
//
//   }
//
//   return psz;
//
//}
//
//
//template < primitive_character CHARACTER >
//const CHARACTER * unicode_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
//{
//
//   if (::is_empty(psz))
//   {
//
//      return psz;
//
//   }
//
//   if (::is_empty(pszCharacters))
//   {
//
//      return psz;
//
//   }
//
//   return _unicode_scan(psz, pszCharacters);
//
//}


//template < primitive_character CHARACTER >
//const CHARACTER * _string_rear_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
//{
//
//   a
//
//   int len1;
//
//   while (*psz)
//   {
//
//      auto ch = *psz;
//
//      auto pszCharactersScan = pszCharacters;
//
//      do
//      {
//
//         if (ch == *pszCharactersScan)
//         {
//
//            return psz;
//
//         }
//
//         pszCharactersScan++;
//
//      } while (*pszCharactersScan);
//
//      psz++;
//
//   }
//
//   return psz;
//
//}
//
//
//template < primitive_character CHARACTER >
//const CHARACTER * string_rear_scan(const CHARACTER * psz, const CHARACTER * pszCharacters)
//{
//
//   if (::is_empty(psz))
//   {
//
//      return psz;
//
//   }
//
//   if (::is_empty(pszCharacters))
//   {
//
//      return psz;
//
//   }
//
//   return _string_rear_scan(psz, pszCharacters);
//
//}


consteval auto string_order_folder_first()
{

   return [](const_char_pointer pszA, const_char_pointer pszB)
   {

      int i = 0;

      while (*pszA && *pszB && ((i = *pszA - *pszB) == 0))
      {

         pszA++;
         pszB++;

      }

      if (i == 0)
      {

         return false;

      }
      else if (*pszA == '\0')
      {

         return true;

      }
      else if (*pszB == '\0')
      {


         return false;

      }
      else if (*pszA == '/')
      {

         return true;

      }
      else if (*pszB == '/')
      {

         return false;

      }
      else if (i >= 0)
      {

         return false;

      }

      return true;

   };

}


#include "ancient/_.h"
#include "coupling.h"
#include "encoding.h"
#include "extension/_.h"
#include "unicode.h"


