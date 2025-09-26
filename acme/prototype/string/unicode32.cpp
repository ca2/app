#include "framework.h"
#include "acme/prototype/string/sz/_template.h"
//#include "string.h"
////#include "acme/exception/exception.h"


character_count wd32_to_ansi_len(const ::wd32_character* pwsz, character_count srclen)
{

   if (pwsz == nullptr)
   {

      return -1;

   }

   character_count len = 0;

   character_count n;

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


character_count wd32_to_ansi_len2(const ::wd32_character *pwsz, character_count & srclen)
{

   if (pwsz == nullptr)
   {

      return -1;
   }

   character_count len = 0;

   character_count n;

   character_count count = 0;

   // char sz[16];

   while (count < srclen && *pwsz != L'\0')
   {

      n = wd32_to_ansi_char_len(*pwsz);

      if (n <= 0)
      {

         break;

      }

      len += n;

      pwsz++;

      count++;

   }

   srclen = count;

   return len;

}



//character_count wd32_to_ansi_len_len(const ::wd32_character* pwsz, character_count input_size)
//{
//
//   if (pwsz == nullptr)
//   {
//
//      return -1;
//
//   }
//
//   character_count len = 0;
//
//   character_count n;
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


character_count utf32_len(const ::wd32_character* pwsz)
{

   if (pwsz == nullptr)
   {
      return 0;
   }
   character_count s = 0;
   while (*pwsz != 0)
   {
      s++;
      pwsz++;
   }
   return s;
}
character_count wd32_to_ansi(char* psz, const ::wd32_character* pwsz, character_count srclen)
{

   character_count c = 0;

   character_count n;

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


character_count ansi_to_wd32_len(const_char_pointer psz, character_count srclen)
{

   character_count len;

   character_count utf32len = 0;

   while (psz != nullptr && *psz != '\0')
   {
      
      if(srclen == 0)
      {
         
         break;
         
      }

      len = unicode_len(psz);

      if (srclen > 0 && len > srclen)
      {

         throw ::exception(error_invalid_character, "reached maximum string length");

         break;

      }

      psz += len;

      utf32len++;

      srclen -= len;

   }

   return utf32len;

}


character_count ansi_to_wd32_len2(const_char_pointer psz, character_count & srclen)
{

   character_count len;

   character_count utf32len = 0;

   character_count count = 0;

   while (count < srclen && *psz != '\0')
   {

      len = unicode_len(psz);

      if (count + len > srclen)
      {

         throw ::exception(error_invalid_character, "reached maximum string length");

         break;
      }

      psz += len;

      utf32len++;

      count += len;

   }

   srclen = count;

   return utf32len;

}




character_count ansi_to_wd32(::wd32_character* pwsz, const_char_pointer psz, character_count srclen)
{

   int dstlen = 0;

   int len = 0;

   while (srclen != 0 && psz != nullptr && *psz != '\0')
   {

      auto iWd32 = unicode_index_length(psz, len);

      if (iWd32 < 0)
      {

         return -1;

      }

      psz += len;

      dstlen += len;

      *pwsz++ = iWd32;

      srclen -= len;

   }

   if (psz != nullptr)
   {

      *pwsz = L'\0';

   }

   return dstlen;

}




::wd32_character* ansi_to_wd32_dup(const_char_pointer input, character_count input_size)
{

   character_count s = ansi_to_wd32_len(input, input_size);

   ::wd32_character* v = (::wd32_character*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(::wd32_character) * (s + 1), nullptr);

   ansi_to_wd32(v, input, s);

   v[s] = 0;

   return v;

}








string wd32_to_ansi_str(const ::wd32_character * pwszUni32, character_count iUni32Len)
{

   character_count iUtf8Len = wd32_to_ansi_len(pwszUni32, iUni32Len);

   string str;

   char * psz = str.get_buffer(iUtf8Len);

   wd32_to_ansi(psz, pwszUni32, iUni32Len);

   str.release_buffer(iUtf8Len);

   return str;

}









CLASS_DECL_ACME character_count wd32_to_wd32_len(const wd32_character * psz, character_count srclen)
{

   return __utftype_to_utftype_len2(psz, srclen);

   //if (input_size < 0)
   //{

   //   auto p = psz;

   //   int iError = 0;

   //   while (*p)
   //   {

   //      p = unicode_next(p, &iError);

   //      if (iError > 0)
   //      {

   //         throw ::exception(error_invalid_character, "wd32_to_wd32_len");
   //      }
   //   }

   //   return p - psz;
   //}
   //else
   //{

   //   return wd32_to_wd32_len2(psz, input_size);
   //}
}


CLASS_DECL_ACME character_count wd32_to_wd32_len2(const wd32_character * psz, character_count &srclen)
{

   return __utftype_to_utftype_len2(psz, srclen);

   //if (input_size < 0)
   //{

   //   return wd32_to_wd32_len(psz, -1);
   //}
   //else
   //{

   //   auto p = psz;

   //   auto count = 0;

   //   int iError = 0;

   //   while (count < input_size && *p)
   //   {

   //      auto pNext = unicode_next(p, &iError);

   //      if (iError > 0)
   //      {

   //         throw ::exception(error_invalid_character, "wd32_to_wd32_len2");
   //      }

   //      auto len = pNext - p;

   //      if (count + len > input_size)
   //      {

   //         throw ::exception(error_index_out_of_bounds, "wd32_to_wd32_len2 (b)");
   //      }

   //      p = pNext;

   //      count += len;
   //   }

   //   return count;
   //}
}


CLASS_DECL_ACME character_count wd32_to_wd32(wd32_character *psz, const wd32_character *pcsz,
                                             character_count input_size)
{

   if (input_size < 0)
   {

      auto pSrc = pcsz;

      auto pDst = psz;

      int iError = 0;

      while (*pSrc)
      {

         auto pSrcNext = unicode_next(pSrc, &iError);

         if (iError > 0)
         {

            throw ::exception(error_invalid_character, "wd32_to_wd32_len (a)");

         }

         while (pSrc < pSrcNext)
         {

            *pDst = *pSrc;

            pSrc++;

            pDst++;

         }

      }

      return pDst - psz;

   }
   else
   {

      auto pSrc = pcsz;

      auto pDst = psz;

      auto count = 0;

      int iError = 0;

      while (count < input_size && *pSrc)
      {

         auto pSrcNext = unicode_next(pSrc, &iError);

         if (iError > 0)
         {

            throw ::exception(error_invalid_character, "wd32_to_wd32 (b1)");
         }

         auto len = pSrcNext - pSrc;

         if (count + len > input_size)
         {

            throw ::exception(error_index_out_of_bounds, "wd32_to_wd32 (b2)");
         }

         while (pSrc < pSrcNext)
         {

            *pDst = *pSrc;

            pSrc++;

            pDst++;

            count++;
         }
      }

      return count;
   }
}
