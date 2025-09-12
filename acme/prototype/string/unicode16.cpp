#include "framework.h"
//#include "string.h"
#include "international.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/string/sz/_template.h"
#include <string.h>
#include <wchar.h>


character_count wd16_to_ansi_len(const ::wd16_character * pwsz, character_count inputsize)
{

   if (pwsz == nullptr)
   {

      return -1;

   }

   character_count len = 0;

   character_count n;

   while (*pwsz != L'\0' && inputsize != 0)
   {

      n = wd16_to_ansi_char_len(&pwsz, &inputsize);

      if(inputsize < 0)
      {

         // input UTF-16 is malformed

         break;

      }

      if (n <= 0)
      {

         break;

      }

      len += n;

   }

   return len;

}


character_count wd16_to_ansi_len2(const ::wd16_character *pwsz, character_count & srclen)
{

   character_count count = 0;

   auto remainingSrc = srclen;

   while (remainingSrc > 0 && *pwsz != L'\0')
   {

      auto len = wd16_to_ansi_char_len(&pwsz, &remainingSrc);

      if (len == 0)
      {

         break;

      }
      else if (len < 0)
      {

         throw_encoding_exception("wd16_to_ansi_len2 bad wd16 character encoding");

         break;

      }

      count += len;

   }

   return count;

}


character_count utf16_len(const ::wd16_character *pwsz)
{

   if (pwsz == nullptr)
   {

      return 0;

   }

   auto pwszEnd = pwsz;

   while (*pwszEnd != 0)
   {

      pwszEnd++;

   }

   return pwszEnd - pwsz;

}


character_count wd16_to_ansi(char* psz, const ::wd16_character* pwsz, character_count srclen)
{

   character_count c = 0;

   character_count n;

   while (srclen != 0 && *pwsz != L'\0')
   {

      n = wd16_to_ansi_char(psz, &pwsz, &srclen);

      if (n <= 0)
      {

         break;

      }

      c += n;

      psz += n;

   }

   *psz = L'\0';

   return c;

}


//character_count ansi_to_wd16_len_len(const_char_pointer psz, character_count srclen)
//{
//
//   character_count len;
//
//   character_count utf16len = 0;
//
//   while (srclen > 0 && psz != nullptr && *psz != '\0')
//   {
//
//      len = unicode_len(psz);
//
//      if (len > srclen)
//      {
//
//         throw ::exception(error_invalid_character, "reached maximum source length");
//
//         break;
//
//      }
//
//      psz += len;
//
//      utf16len++;
//
//      srclen -= len;
//
//   }
//
//   return utf16len;
//
//}


//character_count ansi_to_wd16(::wd16_character* pwsz, const_char_pointer psz, character_count srclen)
//{
//
//   character_count len;
//
//   while (srclen != 0 && psz != nullptr && *psz != '\0')
//   {
//
//      *pwsz++ = (::wd16_character) unicode_index_length(psz, len);
//
//      psz += len;
//
//      srclen -= len;
//
//   }
//
//   if (psz != nullptr)
//   {
//
//      *pwsz = L'\0';
//
//   }
//
//   return len;
//
//}




//::wd16_character* ansi_to_wd16_dup(const_char_pointer input, character_count input_size)
//{
//
//   character_count s = ansi_to_wd16_len_len(input, input_size);
//
//   ::wd16_character* v = (::wd16_character*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(::wd16_character) * (s + 1));
//
//   ansi_to_wd16(v, input, s);
//
//   v[s] = 0;
//
//   return v;
//
//}



//character_count utf16_to_utf16_len(const ::wd16_character* codepoints, character_count input_size)
//{
//
//   character_count len = 0;
//
//   while (input_size != 0)
//   {
//
//      unsigned int cp = *codepoints++;
//
//      input_size--;
//
//      if (cp == 0)
//         break;
//
//      if (cp < 0x10000)
//      {
//
//         ++len;
//
//      }
//      else if (cp <= 0x10FFFF)
//      {
//
//         len += 2;
//
//      }
//      else
//      {
//
//         // invalid code_point, do something !
//         throw ::exception(::exception("utf16_to_utf16_len :: invalid code_point, do something ! "));
//
//         //++len;
//
//      }
//
//   }
//
//   return len;
//
//}
//
//
//character_count utf16_to_utf16(::wd16_character* p, const ::wd16_character* codepoints, character_count input_size)
//{
//
//   character_count len = 0;
//
//   while (input_size != 0)
//   {
//
//      unsigned int cp = *codepoints++;
//
//      input_size--;
//
//      if (cp == 0)
//         break;
//
//      if (cp < 0x10000)
//      {
//
//         *p++ = static_cast<::wd16_character>(cp);
//
//      }
//      else if (cp <= 0x10FFFF)
//      {
//
//         cp -= 0x10000;
//
//         *p++ = static_cast<::wd16_character>((cp >> 10) + 0xD800);
//
//         *p++ = static_cast<::wd16_character>((cp & 0x3FF) + 0xDC00);
//
//      }
//      else
//      {
//
//         *p++ = static_cast<::wd16_character>(0xFFFD);
//
//      }
//
//   }
//
//   return len;
//
//}
//

//wstring utf16_to_utf16(const ::wd16_character* input, character_count input_size)
//{
//
//   character_count s = utf16_to_utf16_len(input, input_size);
//
//   wstring wstr;
//
//   ::wd16_character* p = wstr.get_buffer(s);
//
//   utf16_to_utf16(p, input, s);
//
//   p[s] = 0;
//
//   return wstr;
//
//}
//



extern "C"
{

   char* c_utf8_str(const wchar_t* str)
   {
      return strdup(unicode_to_utf8(str));
   }

   wchar_t* c_wide_str(const_char_pointer str)
   {
#if defined(__APPLE__) || defined(LINUX) || defined(__ANDROID__)
      wchar_t* p = ansi_to_wd32_dup(str);
      wchar_t* point2 = wcsdup(p);
      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(p);
      return point2;
#else
      return wcsdup(utf8_to_unicode(str));
#endif

   }



} // extern "C"





// CLASS_DECL_ACME const_char_pointer yoshi_strcat(const_char_pointer psz1, const_char_pointer psz2, bool bFree2)
// {

//    character_count iLen1 = psz1 == nullptr ? 0 : strlen(scopedstr1);

//    character_count iLen2 = psz2 == nullptr ? 0 : strlen(scopedstr2);

//    character_count iLen = iLen1 + iLen2 + 1;

//    char* psz = (char*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(iLen);

//    strcpy(psz, "");

//    if (scopedstr1 != nullptr)
//    {

//       ansi_concatenate(psz, psz1);

//       ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void*)psz1);

//    }

//    if (scopedstr2 != nullptr)
//    {

//       ansi_concatenate(psz, psz2);

//       if (bFree2)
//       {

//          ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free((void*)psz2);

//       }

//    }

//    return psz;

// }







// http://stackoverflow.com/questions/23919515/how-to-convert-from-utf-16-to-utf-32-on-linux-with-std-library

// peppe
// http://stackoverflow.com/users/1873944/peppe

//peppe top 3% this year
//
//Software engineer at KDAB, the Qt experts.
//
//Qt and Linux hacker.
//
//Free Software advocate.
//
//Refined chef.
//





::wd16_character surrogate_to_utf16(::wd16_character _1st, ::wd16_character _2nd)
{

   return (_1st << 10) + _2nd - 0x35fdc00;

}


//character_count utf16_to_utf16(::wd16_character* output, const unichar* input, character_count input_size)
//{
//
//   ::wd16_character* start = output;
//
//   const unichar* const end = input + input_size;
//
//   while (input < end)
//   {
//
//      const unichar uc = *input++;
//
//      if (!is_surrogate(uc))
//      {
//
//         *output++ = uc;
//
//      }
//      else
//      {
//
//         if (is_high_surrogate(uc) && input < end && is_low_surrogate(*input))
//         {
//
//            *output++ = surrogate_to_utf16(uc, *input++);
//
//         }
//         else
//         {
//
//            throw ::exception(::exception("utf16_to_utf16_len"));
//
//         }
//
//      }
//
//   }
//
//   return output - start;
//
//}


//character_count utf16_to_utf16_len(const unichar* input, character_count input_size)
//{
//
//   const unichar* const end = input + input_size;
//
//   int c = 0;
//
//   while (((input_size < 0) && *input) || ((input_size >= 0) && input < end))
//   {
//
//      const unichar uc = *input++;
//
//      if (!is_surrogate(uc))
//      {
//
//         c++;
//
//      }
//      else
//      {
//
//         if (is_high_surrogate(uc) && input < end && is_low_surrogate(*input))
//         {
//
//            c++;
//
//         }
//         else
//         {
//
//            throw ::exception(::exception("utf16_to_utf16_len"));
//
//         }
//
//      }
//
//   }
//
//   return c;
//
//}



//::wd16_character* utf16_to_utf16(const unichar* input, character_count input_size)
//{
//
//   character_count s = utf16_to_utf16_len(input, input_size);
//
//   ::wd16_character* v = (::wd16_character*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(::wd16_character) * (s + 1));
//
//   utf16_to_utf16(v, input, s);
//
//   v[s] = 0;
//
//   return v;
//
//}

// http://stackoverflow.com/questions/29433124/how-to-convert-a-codepoint-32bit-integer-array-utf-32-to-windows-native-strin

// http://stackoverflow.com/users/65863/remy-lebeau
//Remy Lebeau
//
//I am a highly visible member of the Embarcadero developer forums, which are public forums for software developers who use Borland/CodeGear/Embarcadero development tools (Delphi, C++Builder, RAD Studio, etc) to talk to each other, help each other out with problems in their projects and source code, and to provide expert advise to each other.
//
//I am a primary member of the development and admin teams for the Internet Direct (Indy) open source project and its support forums and newsgroups.
//
//I am a contributing author to the C++Builder Developer's Journal and its support forums. BCBJ is a monthly online magazine devoted to all things related to the Borland/CodeGear/Embarcadero C++Builder development IDE and compiler.
//6,121 answers
//4 questions
//~5.0m people reached
//
//United States
//lebeausoftware.org
//Member for 6 years, 5 months
//12,656 profile views
//Last seen 2 hours ago
//
//Communities (5)
//
//Stack Overflow 175.2k 175.2k 896198
//Animation & Manga 178 178 5
//Science Fiction & Fantasy 173 173 6
//Meta Stack Exchange 121 121 5
//Cryptography 108 108 4
//
//Top Network Posts
//
//5Is it possible for a genin to become a jonin?
//Impact more network posts -->



// on Windows, wchar_t is 2 bytes, suitable for UTF-16
//std::wstring Utf32ToUtf16(const std::vector<unsigned int> &codepoints)
//{
//   std::wstring result;
//   int len = 0;
//
//   for (std::vector<unsigned int>::iterator iter = codepoints.begin(); iter != codepoints.end(); ++iter)
//   {
//      unsigned int cp = *iter;
//      if (cp < 0x10000) {
//         ++len;
//      }
//      else if (cp <= 0x10FFFF) {
//         len += 2;
//      }
//      else {
//         // invalid code_point, do something !
//         ++len;
//      }
//   }
//
//   if (len > 0)
//   {
//      result.resize(len);
//      len = 0;
//
//      for (std::vector<unsigned int>::iterator iter = codepoints.begin(); iter != codepoints.end(); ++iter)
//      {
//         unsigned int cp = *iter;
//         if (cp < 0x10000) {
//            result[len++] = static_cast<wchar_t>(cp);
//         }
//         else if (cp <= 0x10FFFF) {
//            cp -= 0x10000;
//            result[len++] = static_cast<wchar_t>((cp >> 10) + 0xD800);
//            result[len++] = static_cast<wchar_t>((cp & 0x3FF) + 0xDC00);
//         }
//         else {
//            result[len++] = static_cast<wchar_t>(0xFFFD);
//         }
//      }
//   }
//
//   return result;
//}

//character_count wd16_to_ansi_len(const ::wd16_character* pwsz, character_count input_size)
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
//      n = unichar_to_utf8char(sz, *pwsz);
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


//character_count utf16_len(const ::wd16_character* pwsz)
//{
//
//   if (pwsz == nullptr)
//   {
//      return 0;
//   }
//   character_count s = 0;
//   while (*pwsz != 0)
//   {
//      s++;
//      pwsz++;
//   }
//   return s;
//}


//character_count wd16_to_ansi(char* psz, const ::wd16_character* pwsz, character_count srclen)
//{
//   //unsigned short * pwsz = (unsigned short *)pwszParam;
//   character_count c = 0;
//   int n;
//   if (srclen < 0)
//   {
//
//      srclen = utf16_len(pwsz);
//
//   }
//   while (srclen > 0 && *pwsz != L'\0')
//   {
//      n = wd16_to_ansichar(psz, *pwsz);
//      if (n <= 0)
//         break;
//      c += n;
//      pwsz++;
//      psz += n;
//      srclen--;
//   }
//
//   *psz = L'\0';
//   return c;
//}


//string wd16_to_ansi(const ::wd16_character* pwszUni32, character_count iUni32Len)
//{
//
//   character_count iUtf8Len = wd16_to_ansi_len(pwszUni32, iUni32Len);
//
//   string str;
//
//   char* psz = str.get_buffer(iUtf8Len);
//
//   wd16_to_ansi(psz, pwszUni32, iUni32Len);
//
//   str.release_buffer(iUtf8Len);
//
//   return str;
//
//}


character_count ansi_to_wd16_len(const_char_pointer psz, character_count srclen)
{

   character_count utf16len = 0;

   ::wd16_character * pwsz = nullptr;

   while (srclen != 0 && psz != nullptr && *psz != '\0')
   {

      int len;

      int iChar = unicode_index_length(psz, len);

      if (iChar < 0)
      {

         // Invalid char 0xFFFD

         utf16len++;
         len = 1;

      }
      else if (utf32_is_surrogated(iChar))
      {

         utf16len += 2;

      }
      else
      {

         utf16len++;

      }

      psz += len;

      srclen -= len;

   }

   return utf16len;

}


character_count ansi_to_wd16_len2(const_char_pointer psz, character_count & srclen)
{

   character_count utf16len = 0;

   ::wd16_character * pwsz = nullptr;

   character_count count = 0;

   while (count < srclen && *psz != '\0')
   {

      int len;

      int iChar = unicode_index_length(psz, len);

      if (iChar < 0)
      {

         // Invalid char 0xFFFD

         utf16len++;

         len = 1;

      }
      else if (utf32_is_surrogated(iChar))
      {

         utf16len += 2;

      }
      else
      {

         utf16len++;

      }

      psz += len;

      count += len;

   }

   return utf16len;

}


character_count ansi_to_wd16(::wd16_character *pwsz, const_char_pointer psz, character_count srclen)
{

   character_count len = 0;

   while (srclen != 0 && psz != nullptr && *psz != '\0')
   {

      ::wd32_character wd32ch;

      auto used_len = ansi_to_wd32_char(&wd32ch, psz, srclen);

      if(wd32ch & I32_MINIMUM || used_len < 0)
      {

         used_len = 1;

         wd32ch = 0xfffd;

      }

      psz += used_len;

      srclen -= used_len;

      auto u16len = wd32_to_wd16_char(pwsz, wd32ch);

      if(u16len < 0)
      {

         return -1;

      }

      pwsz += u16len;

      len += u16len;

   }

   if (pwsz != nullptr)
   {

      *pwsz = L'\0';

   }

   return len;

}


::wd16_character* ansi_to_wd16_dup(const_char_pointer input, character_count input_size)
{

   character_count s = ansi_to_wd16_len(input, input_size);

   ::wd16_character* v = (::wd16_character*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(::wd16_character) * (s + 1), nullptr);

   ansi_to_wd16(v, input, s);

   v[s] = 0;

   return v;

}



character_count utf16_to_utf16_len(const ::wd16_character* codepoints, character_count input_size)
{

   character_count len = 0;

   while (input_size != 0)
   {

      unsigned int cp = *codepoints++;

      input_size--;

      if (cp == 0)
         break;

      if (cp < 0x10000)
      {

         ++len;

      }
      else if (cp <= 0x10FFFF)
      {

         len += 2;

      }
      else
      {

         // invalid code_point, do something !
         throw ::exception(error_invalid_character, "utf16_to_utf16_len :: invalid code_point, do something ! ");

         //++len;

      }

   }

   return len;

}


character_count utf16_to_utf16(::wd16_character * p, const ::wd16_character* codepoints, character_count input_size)
{

   character_count len = 0;

   while (input_size != 0)
   {

      unsigned int cp = *codepoints++;

      input_size--;

      if (cp == 0)
      {

         break;

      }

      if (cp < 0x10000)
      {

         *p++ = static_cast<::wd16_character>(cp);

      }
      else if (cp <= 0x10FFFF)
      {

         cp -= 0x10000;

         *p++ = static_cast<::wd16_character>((cp >> 10) + 0xD800);

         *p++ = static_cast<::wd16_character>((cp & 0x3FF) + 0xDC00);

      }
      else
      {

         *p++ = static_cast<::wd16_character>(0xFFFD);

      }

   }

   return len;

}


//wstring utf16_to_utf16(const ::wd16_character* input, character_count input_size)
//{
//
//   character_count s = utf16_to_utf16_len(input, input_size);
//
//   wstring wstr;
//
//   unichar* p = wstr.get_buffer(s);
//
//   utf16_to_utf16(p, input, s);
//
//   p[s] = 0;
//
//   return wstr;
//
//}
//
//
//












//string wd16_to_ansi(const ::wd16_character * pwszUni32, character_count iUni32Len)
//{
//
//   character_count iUtf8Len = wd16_to_ansi_len(pwszUni32, iUni32Len);
//
//   string str;
//
//   char * psz = str.get_buffer(iUtf8Len);
//
//   wd16_to_ansi(psz, pwszUni32, iUni32Len);
//
//   str.release_buffer(iUtf8Len);
//
//   return str;
//
//}














string wd16_to_ansi_str(const ::wd16_character * pwsz, character_count srclen)
{

   character_count iUtf8Len = wd16_to_ansi_len(pwsz, srclen);

   string str;

   char * psz = str.get_buffer(iUtf8Len);

   wd16_to_ansi(psz, pwsz, srclen);

   str.release_buffer(iUtf8Len);

   return str;

}


CLASS_DECL_ACME character_count wd16_to_wd16_len(const wd16_character * psz, character_count srclen)
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

   //         throw ::exception(error_invalid_character, "wd16_to_wd16_len");
   //      }
   //   }

   //   return p - psz;
   //}
   //else
   //{

   //   return wd16_to_wd16_len2(psz, input_size);
   //}
}


CLASS_DECL_ACME character_count wd16_to_wd16_len2(const wd16_character * psz, character_count & srclen)
{

   return __utftype_to_utftype_len2(psz, srclen);

   //if (input_size < 0)
   //{

   //   return wd16_to_wd16_len(psz, -1);

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

   //         throw ::exception(error_invalid_character, "wd16_to_wd16_len2");

   //      }

   //      auto len = pNext - p;

   //      if (count + len > input_size)
   //      {

   //         throw ::exception(error_index_out_of_bounds, "wd16_to_wd16_len2 (b)");

   //      }

   //      p = pNext;

   //      count += len;

   //   }

   //   return count;

   //}

}


CLASS_DECL_ACME character_count wd16_to_wd16(wd16_character *psz, const const wd16_character * pcsz,
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

            throw ::exception(error_invalid_character, "wd16_to_wd16_len (a)");

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

            throw ::exception(error_invalid_character, "wd16_to_wd16 (b1)");

         }

         auto len = pSrcNext - pSrc;

         if (count + len > input_size)
         {

            throw ::exception(error_index_out_of_bounds, "wd16_to_wd16 (b2)");

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


