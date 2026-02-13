// Created by camilo on 2025-09-11 03:04 <3ThomasBorregaardSorensen!!
#pragma once


template < prototype_character CHARACTER >
inline character_count _string_get_length2(const CHARACTER * psz, character_count lengthMax) noexcept 
{ 
   
   character_count size = 0;

   while (lengthMax > 0 && *psz) 
   { 
      
      psz++; 
      
      size++; 
      
      lengthMax--; 
   
   }

   return size;

}


template<typename CHARACTER>
inline character_count __utftype_to_utftype_len(const CHARACTER *psz)
{

   auto p = psz;

   while (*p)
   {

      p = unicode_next(p);

      if (!p)
      {

         throw_encoding_exception("__utftype_to_utftype_len");

      }

   }

   return p - psz;

}


template<typename CHARACTER, typename CHARACTER_COUNT>
inline character_count __utftype_to_utftype_len2(const CHARACTER *psz, CHARACTER_COUNT & srclen)
{

   if (srclen < 0)
   {

      return __utftype_to_utftype_len(psz);

   }

   auto p = psz;

   character_count countSrc = 0;

   auto remainingSrc = srclen;

   while (countSrc < srclen && *p)
   {

      auto pNext = unicode_next(p, &remainingSrc);

      auto len = pNext - p;

      if (countSrc + len > srclen)
      {

         throw_encoding_exception("__utftype_to_utftype_len2");

      }

      p = pNext;

      countSrc += len;

   }

   return countSrc;

}



