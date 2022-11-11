// Created from _unicode by camilo on 2022-11-07 09:23 <3ThomasBorregaardSorensen!!
#pragma once


inline bool _str_safe_precmp(int & i, const ansichar * pszA, const ansichar * pszB)
{

   if (::is_null(pszA))
   {

      if (::is_null(pszB))
      {

         i = 0;

         return true;

      }
      else
      {

         i = 1;

         return true;

      }

   }
   else if (::is_null(pszB))
   {

      i = -1;

      return true;

   }

   return false;

}


inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource, strsize srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}


// template <  >
inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource, strsize srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}



inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource, strsize srclen)
{

   return wd32_to_wd16_len(psource, srclen);

}



inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource, strsize srclen)
{

   return srclen >= 0 ? srclen : string_safe_length(psource) + srclen + 1;

}



inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource, strsize srclen)
{

   return wd16_to_wd32_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource, strsize srclen)
{

   return wd16_to_ansi_len(psource, srclen);

}



inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource, strsize srclen)
{

   return ansi_to_wd16_len(psource, srclen);

}



inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource, strsize srclen)
{

   return wd32_to_ansi_len(psource, srclen);

}



inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource, strsize srclen)
{

   return ansi_to_wd32_len(psource, srclen);

}


inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource)
{

   return strlen(psource);

}



inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource)
{

   return wd16_len(psource);

}



inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource)
{

   return wd32_to_wd16_len(psource);

}



inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource)
{

   return wd32_len(psource);

}



inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource)
{

   return wd16_to_wd32_len(psource);

}



inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource)
{

   return wd16_to_ansi_len(psource);

}



inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource)
{

   return wd32_to_ansi_len(psource);

}



inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource)
{

   return ansi_to_wd16_len(psource);

}



inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource)
{

   return ansi_to_wd32_len(psource);

}


inline void utf_to_utf(ansichar * ptarget, const ansichar * psource, strsize srclen)
{

   overlap_safe_ansincpy(ptarget, psource, srclen);

}



inline void utf_to_utf(wd16char * ptarget, const wd16char * psource, strsize srclen)
{

   overlap_safe_wd16ncpy(ptarget, psource, srclen);

}



inline void utf_to_utf(wd16char * ptarget, const wd32char * psource, strsize srclen)
{

   wd32_to_wd16(ptarget, psource, srclen);

}



inline void utf_to_utf(wd32char * ptarget, const wd32char * psource, strsize srclen)
{

   overlap_safe_wd32ncpy(ptarget, psource, srclen);

}



inline void utf_to_utf(wd32char * ptarget, const wd16char * psource, strsize srclen)
{

   wd16_to_wd32(ptarget, psource, srclen);

}



inline void utf_to_utf(ansichar * ptarget, const wd16char * psource, strsize srclen)
{

   wd16_to_ansi(ptarget, psource, srclen);

}



inline void utf_to_utf(ansichar * ptarget, const wd32char * psource, strsize srclen)
{

   wd32_to_ansi(ptarget, psource, srclen);

}



inline void utf_to_utf(wd16char * ptarget, const ansichar * psource, strsize srclen)
{

   ansi_to_wd16(ptarget, psource, srclen);

}



inline void utf_to_utf(wd32char * ptarget, const ansichar * psource, strsize srclen)
{

   ansi_to_wd32(ptarget, psource, srclen);

}



inline void utf_to_utf(ansichar * ptarget, const ansichar * psource)
{

   strcpy(ptarget, psource);

}



inline void utf_to_utf(wd16char * ptarget, const wd16char * psource)
{

   wd16_cpy(ptarget, psource);

}



inline void utf_to_utf(wd32char * ptarget, const wd16char * psource)
{

   wd16_to_wd32(ptarget, psource);

}



inline void utf_to_utf(wd32char * ptarget, const wd32char * psource)
{

   wd32_cpy(ptarget, psource);

}



inline void utf_to_utf(wd16char * ptarget, const wd32char * psource)
{

   wd32_to_wd16(ptarget, psource);

}



inline void utf_to_utf(ansichar * ptarget, const wd16char * psource)
{

   wd16_to_ansi(ptarget, psource);

}



inline void utf_to_utf(ansichar * ptarget, const wd32char * psource)
{

   wd32_to_ansi(ptarget, psource);

}



inline void utf_to_utf(wd16char * ptarget, const ansichar * psource)
{

   ansi_to_wd16(ptarget, psource);

}



inline void utf_to_utf(wd32char * ptarget, const ansichar * psource)
{

   ansi_to_wd32(ptarget, psource);

}




