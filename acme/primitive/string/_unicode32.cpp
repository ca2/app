#include "framework.h"





strsize wd32_to_ansi_len(const wd32char* pwsz, strsize srclen)
{

   if (pwsz == nullptr)
   {

      return -1;

   }

   strsize len = 0;

   strsize n;

   //char sz[16];

   while (*pwsz != L'\0' && srclen != 0)
   {

      n = wd32_to_ansi_char_len(*pwsz);

      if (n <= 0)
      {

         break;

      }

      len += n;

      pwsz++;

      srclen--;

   }

   return len;

}


//strsize wd32_to_ansi_len_len(const wd32char* pwsz, strsize input_size)
//{
//
//   if (pwsz == nullptr)
//   {
//
//      return -1;
//
//   }
//
//   strsize len = 0;
//
//   strsize n;
//
//   char sz[16];
//
//   while (input_size != 0 && *pwsz != L'\0')
//   {
//
//      n = wd32_to_ansichar(sz, *pwsz);
//
//      if (n <= 0)
//      {
//
//         break;
//
//      }
//
//      len += n;
//
//      input_size--;
//
//      pwsz++;
//
//   }
//
//   return len;
//
//}


strsize utf32_len(const wd32char* pwsz)
{

   if (pwsz == nullptr)
   {
      return 0;
   }
   strsize s = 0;
   while (*pwsz != 0)
   {
      s++;
      pwsz++;
   }
   return s;
}
strsize wd32_to_ansi(char* psz, const wd32char* pwsz, strsize srclen)
{

   strsize c = 0;

   strsize n;

   if (srclen < 0)
   {

      srclen = utf32_len(pwsz);

   }
   while (srclen != 0 && *pwsz != L'\0')
   {
      n = wd32_to_ansi_char(psz, *pwsz);
      if (n <= 0)
         break;
      c += n;
      pwsz++;
      psz += n;
      srclen--;
   }

   *psz = L'\0';
   return c;
}


strsize ansi_to_wd32_len(const char* psz, strsize srclen)
{

   strsize len;

   strsize utf32len = 0;

   while (psz != nullptr && *psz != '\0')
   {
      
      if(srclen == 0)
      {
         
         break;
         
      }

      len = __uni_len(psz);

      if (srclen > 0 && len > srclen)
      {

         __throw(error_invalid_character, "reached maximum string length");

         break;

      }

      psz += len;

      utf32len++;

      srclen -= len;

   }

   return utf32len;

}

strsize ansi_to_wd32(wd32char* pwsz, const char* psz, strsize srclen)
{

   ::i32 dstlen = 0;

   ::i32 len = 0;

   while (srclen != 0 && psz != nullptr && *psz != '\0')
   {

      auto iWd32 = ::str::ch::uni_index_len(psz, len);

      if (iWd32 < 0)
      {

         return -1;

      }

      psz += len;

      dstlen += len;

      *pwsz++ = iWd32;

   }

   if (psz != nullptr)
   {

      *pwsz = L'\0';

   }

   return dstlen;

}




wd32char* ansi_to_wd32_dup(const char* input, strsize input_size)
{

   strsize s = ansi_to_wd32_len(input, input_size);

   wd32char* v = (wd32char*)memory_allocate(sizeof(wd32char) * (s + 1));

   ansi_to_wd32(v, input, s);

   v[s] = 0;

   return v;

}








string wd32_to_ansi_str(const wd32char * pwszUni32, strsize iUni32Len)
{

   strsize iUtf8Len = wd32_to_ansi_len(pwszUni32, iUni32Len);

   string str;

   char * psz = str.get_string_buffer(iUtf8Len);

   wd32_to_ansi(psz, pwszUni32, iUni32Len);

   str.release_string_buffer(iUtf8Len);

   return str;

}



const wd32char * utf32_inc(const wd32char * psz)
{

   return psz + 1;

}




