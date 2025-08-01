#include "framework.h"
//#include "string.h"
////#include "acme/exception/exception.h"


/* --------------------------------------------------------------------- */

/*
* Index into the table below with the first unsigned char of a UTF-8 sequence to
* get the number of trailing bytes that are supposed to follow it.
* Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
* left as-is for anyone who may want to do such conversion, which was
* allowed in earlier algorithms.
*/
//const char trailingBytesForUTF8[256] =
//{
//   (const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
//};



/*
* Magic values subtracted from a buffer value during UTF8 conversion.
* This table contains as many values as there might be trailing bytes
* in a UTF-8 sequence.
*/
static const unsigned int offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
                                             0x03C82080UL, 0xFA082080UL, 0x82082080UL
                                           };


//const_char_pointer  unicode_next(const ::scoped_string & scopedstr)
//{
//
//   char len =  1 + trailingBytesForUTF8(*psz);
//   if(len == 0)      return nullptr;
//   if(*psz++ == 0)   return nullptr;
//   if(len == 1)      return psz;
//   if(*psz++ == 0)   return nullptr;
//   if(len == 2)      return psz;
//   if(*psz++ == 0)   return nullptr;
//   if(len == 3)      return psz;
//   if(*psz++ == 0)   return nullptr;
//   if(len == 4)      return psz;
//   if(*psz++ == 0)   return nullptr;
//   if(len == 5)      return psz;
//   if(*psz++ == 0)   return nullptr;
//   if(len == 6)      return psz;
//   return nullptr;
//}



int uni_to_utf8(char * dest, int ch)
{
   if (ch < 0x80)
   {
      dest[0] = (char)ch;
      return 1;
   }
   if (ch < 0x800)
   {
      dest[0] = (ch >> 6) | 0xC0;
      dest[1] = (ch & 0x3F) | 0x80;
      return 2;
   }
   if (ch < 0x10000)
   {
      dest[0] = (ch >> 12) | 0xE0;
      dest[1] = ((ch >> 6) & 0x3F) | 0x80;
      dest[2] = (ch & 0x3F) | 0x80;
      return 3;
   }
   if (ch < 0x110000)
   {
      dest[0] = (ch >> 18) | 0xF0;
      dest[1] = ((ch >> 12) & 0x3F) | 0x80;
      dest[2] = ((ch >> 6) & 0x3F) | 0x80;
      dest[3] = (ch & 0x3F) | 0x80;
      return 4;
   }
   return 0;

}

int uni_to_utf8_2_or_more(char * dest, int ch)
{
   if (ch < 0x800)
   {
      dest[0] = (ch >> 6) | 0xC0;
      dest[1] = (ch & 0x3F) | 0x80;
      return 2;
   }
   if (ch < 0x10000)
   {
      dest[0] = (ch >> 12) | 0xE0;
      dest[1] = ((ch >> 6) & 0x3F) | 0x80;
      dest[2] = (ch & 0x3F) | 0x80;
      return 3;
   }
   if (ch < 0x110000)
   {
      dest[0] = (ch >> 18) | 0xF0;
      dest[1] = ((ch >> 12) & 0x3F) | 0x80;
      dest[2] = ((ch >> 6) & 0x3F) | 0x80;
      dest[3] = (ch & 0x3F) | 0x80;
      return 4;
   }
   return 0;

}


CLASS_DECL_ACME ::collection::count unichar_len(const ::wide_character * psz)
{
   if(scopedstr == nullptr)
      return -1;
   int count = 0;
   while(*psz != 0)
   {
      psz++;
      count++;
   }
   return count;
}


::collection::count utf16_len(const ::ansi_character * psz)
{
   if(scopedstr == nullptr)
      return -1;
   int count = 0;
   while((scopedstr = unicode_next(scopedstr)) != nullptr)
   {
      count++;
   }
   return count;
}

::collection::count utf16_len_len(const ::ansi_character * psz, character_count srclen)
{
   if(scopedstr == nullptr)
      return -1;
   int count = 0;
   while(srclen > 0 && (scopedstr = unicode_next(scopedstr)) != nullptr)
   {
      count++;
      srclen--;
   }
   return count;
}


void ansi_to_wd16(::wd16_character * pwsz, const ::ansi_character * psz)
{

   while(true)
   {

      int len;

      auto iWd32 = unicode_index_length(scopedstr, len);

      if (iWd32 < 0 || psz == nullptr)
      {

         break;

      }

      psz += len;

      auto iWd16 = wd32_to_wd16_char(pwsz, iWd32);

      if (iWd16 < 0)
      {

         break;

      }

      pwsz += iWd16;

   }

   *pwsz = L'\0';

}


void ansi_to_wd16_len(::wd16_character * pwsz, const ::ansi_character * psz, character_count srclen)
{

   while(srclen > 0 && psz != nullptr && *psz != '\0')
   {

      int len;

      auto iWd32 = unicode_index_length(scopedstr, len);

      if (iWd32)
      {

         throw ::exception(error_invalid_character);

         return;

      }

      if (srclen < len)
      {

         throw ::exception(error_invalid_character);

         return;

      }

      psz += len;

      srclen -= len;

      auto iWd16 = wd32_to_wd16_char(pwsz, iWd32);

      if (iWd16)
      {

         throw ::exception(error_invalid_character);

         return;

      }

      pwsz += iWd16;

   }

   *pwsz = L'\0';

}


/*
WCHAR * ansi_to_wd16(const ::ansi_character * psz)
{

   ::collection::count iCount = utf16_len(scopedstr);

   if(iCount < 0)
      return nullptr;

   WCHAR * pwz = ___new WCHAR[iCount + 1];

   utf8_to_16(pwz, psz);

   return pwz;

}*/

int utf8_len(const ::wide_character * pwsz)
{
   if(pwsz == nullptr)
      return -1;
   int count = 0;
   int n;
   char sz[16];
   while(*pwsz != L'\0')
   {
      n = *pwsz < 0x80 ? 1: uni_to_utf8_2_or_more(sz, *pwsz);
      if(n <= 0)
         break;
      count += n;
      pwsz++;
   }
   return count;
}

int utf8_len_len(const ::wide_character * pwsz, character_count srclen)
{
   if(pwsz == nullptr)
      return -1;
   int count = 0;
   int n;
   char sz[16];
   while(srclen > 0 && *pwsz != L'\0')
   {
      n = *pwsz < 0x80 ? 1: uni_to_utf8_2_or_more(sz,*pwsz);
      if(n <= 0)
         break;
      count += n;
      srclen--;
      pwsz++;
   }
   return count;
}


int x_size_of_tables()
{

   return sizeof(arr_idxCharInfo)+sizeof(arr_CharInfo)+sizeof(arr_idxCharInfo2)+sizeof(arr_CharInfo2);

}



