// Created from _unicode by camilo on 2022-11-07 09:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#if defined(FREEBSD) || defined(OPENBSD)
#define _POSIX_C_SOURCE 200809L
#define _ANSI_SOURCE
#endif
#include <string.h>
#include <wchar.h>

//CLASS_DECL_ACME bool _str_safe_precmp(int & i, const_char_pointer pszA, const_char_pointer pszB)
//{
//
//   if (::is_null(scopedstrA))
//   {
//
//      if (::is_null(scopedstrB))
//      {
//
//         i = 0;
//
//         return true;
//
//      }
//      else
//      {
//
//         i = 1;
//
//         return true;
//
//      }
//
//   }
//   else if (::is_null(scopedstrB))
//   {
//
//      i = -1;
//
//      return true;
//
//   }
//
//   return false;
//
//}



CLASS_DECL_ACME character_count _utf_to_utf_length(const ::ansi_character*, const ::ansi_character* psource, character_count srclen)
{

   return srclen >= 0 ? srclen : string_get_length(psource) + srclen + 1;

}


CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const_char_pointer psource, character_count srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}


// template <  >
CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource, character_count srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource, character_count srclen)
{

   return wd32_to_wd16_len(psource, srclen);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource, character_count srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource, character_count srclen)
{

   return wd16_to_wd32_len(psource, srclen);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const ::wd16_character * psource, character_count srclen)
{

   return wd16_to_ansi_len(psource, srclen);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const_char_pointer psource, character_count srclen)
{

   return ansi_to_wd16_len(psource, srclen);

}



// CLASS_DECL_ACME character_count __utf_to_utf_length(const ::wd16_character*, const ::ansi_character* psource, character_count srclen)
// {
//
//    return ansi_to_wd16_len(psource, srclen);
//
// }


CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const ::wd32_character * psource, character_count srclen)
{

   return wd32_to_ansi_len(psource, srclen);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const_char_pointer psource, character_count srclen)
{

   return ansi_to_wd32_len(psource, srclen);

}


CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const_char_pointer psource)
{

   return strlen(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource)
{

   return wd16_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource)
{

   return wd32_to_wd16_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource)
{

   return wd32_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource)
{

   return wd16_to_wd32_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const ::wd16_character * psource)
{

   return wd16_to_ansi_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const_char_pointer ,const ::wd32_character * psource)
{

   return wd32_to_ansi_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd16_character *, const_char_pointer psource)
{

   return ansi_to_wd16_len(psource);

}



CLASS_DECL_ACME character_count utf_to_utf_length(const ::wd32_character *, const_char_pointer psource)
{

   return ansi_to_wd32_len(psource);

}


CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const_char_pointer psource, character_count srclen)
{

   overlap_safe_ansincpy(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource, character_count srclen)
{

   overlap_safe_wd16ncpy(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource, character_count srclen)
{

   wd32_to_wd16(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource, character_count srclen)
{

   overlap_safe_wd32ncpy(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource, character_count srclen)
{

   wd16_to_wd32(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource, character_count srclen)
{

   wd16_to_ansi(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource, character_count srclen)
{

   wd32_to_ansi(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const_char_pointer psource, character_count srclen)
{

   ansi_to_wd16(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const_char_pointer psource, character_count srclen)
{

   ansi_to_wd32(ptarget, psource, srclen);

}



CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const_char_pointer psource)
{

   strcpy(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource)
{

   wd16_cpy(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource)
{

   wd16_to_wd32(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource)
{

   wd32_cpy(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource)
{

   wd32_to_wd16(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource)
{

   wd16_to_ansi(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource)
{

   wd32_to_ansi(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::wd16_character * ptarget, const_char_pointer psource)
{

   ansi_to_wd16(ptarget, psource);

}



CLASS_DECL_ACME void utf_to_utf(::wd32_character * ptarget, const_char_pointer psource)
{

   ansi_to_wd32(ptarget, psource);

}




