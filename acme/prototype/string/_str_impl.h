#pragma once


template < prototype_character CHAR_TYPE >
inline string_base < const CHAR_TYPE * > str::repeat(const CHAR_TYPE * psz, character_count c)
{

   auto itemLen = string_safe_length(psz);

   auto itemByteCount = itemLen * sizeof(CHAR_TYPE);

   auto len = itemLen * c;

   string str;

   if (len > 0)
   {

      auto p = str.get_buffer(len);

      while (c > 0)
      {

         auto psource = psz;

         auto ptarget = p;

         auto copyLength = itemLen;

         while (copyLength > 0)
         {

            *ptarget++ = *psource++;

            copyLength--;

         }

         p += itemLen;

         c--;

      }

      str.release_buffer(len);

   }

   return str;

}



