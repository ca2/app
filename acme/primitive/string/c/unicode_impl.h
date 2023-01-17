﻿// Created from _unicode by camilo on 2022-11-07 09:23 <3ThomasBorregaardSørensen!!
#pragma once


//inline bool _str_safe_precmp(int & i, const ::ansi_character * pszA, const ::ansi_character * pszB)
//{
//
//   if (::is_null(pszA))
//   {
//
//      if (::is_null(pszB))
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
//   else if (::is_null(pszB))
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


inline strsize utf_to_utf_length(const ::ansi_character *, const ::ansi_character * psource, strsize srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}


// template <  >
inline strsize utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource, strsize srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}



inline strsize utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource, strsize srclen)
{

   return wd32_to_wd16_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource, strsize srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}



inline strsize utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource, strsize srclen)
{

   return wd16_to_wd32_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ::ansi_character *, const ::wd16_character * psource, strsize srclen)
{

   return wd16_to_ansi_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ::wd16_character *, const ::ansi_character * psource, strsize srclen)
{

   return ansi_to_wd16_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ::ansi_character *, const ::wd32_character * psource, strsize srclen)
{

   return wd32_to_ansi_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ::wd32_character *, const ::ansi_character * psource, strsize srclen)
{

   return ansi_to_wd32_len(psource, srclen);

}


inline strsize utf_to_utf_length(const ::ansi_character *, const ::ansi_character * psource)
{

   return strlen(psource);

}



inline strsize utf_to_utf_length(const ::wd16_character *, const ::wd16_character * psource)
{

   return wd16_len(psource);

}



inline strsize utf_to_utf_length(const ::wd16_character *, const ::wd32_character * psource)
{

   return wd32_to_wd16_len(psource);

}



inline strsize utf_to_utf_length(const ::wd32_character *, const ::wd32_character * psource)
{

   return wd32_len(psource);

}



inline strsize utf_to_utf_length(const ::wd32_character *, const ::wd16_character * psource)
{

   return wd16_to_wd32_len(psource);

}



inline strsize utf_to_utf_length(const ::ansi_character *, const ::wd16_character * psource)
{

   return wd16_to_ansi_len(psource);

}



inline strsize utf_to_utf_length(const ::ansi_character *, const ::wd32_character * psource)
{

   return wd32_to_ansi_len(psource);

}



inline strsize utf_to_utf_length(const ::wd16_character *, const ::ansi_character * psource)
{

   return ansi_to_wd16_len(psource);

}



inline strsize utf_to_utf_length(const ::wd32_character *, const ::ansi_character * psource)
{

   return ansi_to_wd32_len(psource);

}


inline void utf_to_utf(::ansi_character * ptarget, const ::ansi_character * psource, strsize srclen)
{

   overlap_safe_ansincpy(ptarget, psource, srclen);

}



inline void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource, strsize srclen)
{

   overlap_safe_wd16ncpy(ptarget, psource, srclen);

}



inline void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource, strsize srclen)
{

   wd32_to_wd16(ptarget, psource, srclen);

}



inline void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource, strsize srclen)
{

   overlap_safe_wd32ncpy(ptarget, psource, srclen);

}



inline void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource, strsize srclen)
{

   wd16_to_wd32(ptarget, psource, srclen);

}



inline void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource, strsize srclen)
{

   wd16_to_ansi(ptarget, psource, srclen);

}



inline void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource, strsize srclen)
{

   wd32_to_ansi(ptarget, psource, srclen);

}



inline void utf_to_utf(::wd16_character * ptarget, const ::ansi_character * psource, strsize srclen)
{

   ansi_to_wd16(ptarget, psource, srclen);

}



inline void utf_to_utf(::wd32_character * ptarget, const ::ansi_character * psource, strsize srclen)
{

   ansi_to_wd32(ptarget, psource, srclen);

}



inline void utf_to_utf(::ansi_character * ptarget, const ::ansi_character * psource)
{

   strcpy(ptarget, psource);

}



inline void utf_to_utf(::wd16_character * ptarget, const ::wd16_character * psource)
{

   wd16_cpy(ptarget, psource);

}



inline void utf_to_utf(::wd32_character * ptarget, const ::wd16_character * psource)
{

   wd16_to_wd32(ptarget, psource);

}



inline void utf_to_utf(::wd32_character * ptarget, const ::wd32_character * psource)
{

   wd32_cpy(ptarget, psource);

}



inline void utf_to_utf(::wd16_character * ptarget, const ::wd32_character * psource)
{

   wd32_to_wd16(ptarget, psource);

}



inline void utf_to_utf(::ansi_character * ptarget, const ::wd16_character * psource)
{

   wd16_to_ansi(ptarget, psource);

}



inline void utf_to_utf(::ansi_character * ptarget, const ::wd32_character * psource)
{

   wd32_to_ansi(ptarget, psource);

}



inline void utf_to_utf(::wd16_character * ptarget, const ::ansi_character * psource)
{

   ansi_to_wd16(ptarget, psource);

}



inline void utf_to_utf(::wd32_character * ptarget, const ::ansi_character * psource)
{

   ansi_to_wd32(ptarget, psource);

}




