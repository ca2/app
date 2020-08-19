#include "framework.h"





strsize wd16_to_ansi_len(const wd16char * pwsz, strsize inputsize)
{

   if (pwsz == nullptr)
   {

      return -1;

   }

   strsize len = 0;

   strsize n;

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


strsize utf16_len(const wd16char* pwsz)
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


strsize wd16_to_ansi(char* psz, const wd16char* pwsz, strsize srclen)
{

   strsize c = 0;

   strsize n;

   while (srclen != 0 && *pwsz != L'\0')
   {

      n = wd16_to_ansi_char(psz, &pwsz, &srclen);

      if (n == 0)
      {

         break;

      }

      c += n;

      psz += n;

   }

   *psz = L'\0';

   return c;

}


strsize ansi_to_wd16_len_len(const char* psz, strsize srclen)
{

   strsize len;

   strsize utf16len = 0;

   while (srclen > 0 && psz != nullptr && *psz != '\0')
   {

      len = __uni_len(psz);

      if (len > srclen)
      {

         __throw(invalid_character("reached maximum source length"));

         break;

      }

      psz += len;

      utf16len++;

      srclen -= len;

   }

   return utf16len;

}


//strsize ansi_to_wd16(wd16char* pwsz, const char* psz, strsize srclen)
//{
//
//   strsize len;
//
//   while (srclen != 0 && psz != nullptr && *psz != '\0')
//   {
//
//      *pwsz++ = (wd16char) ::str::ch::uni_index_len(psz, len);
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




//wd16char* ansi_to_wd16_dup(const char* input, strsize input_size)
//{
//
//   strsize s = ansi_to_wd16_len_len(input, input_size);
//
//   wd16char* v = (wd16char*)memory_alloc(sizeof(wd16char) * (s + 1));
//
//   ansi_to_wd16(v, input, s);
//
//   v[s] = 0;
//
//   return v;
//
//}



//strsize utf16_to_utf16_len(const wd16char* codepoints, strsize input_size)
//{
//
//   strsize len = 0;
//
//   while (input_size != 0)
//   {
//
//      u32 cp = *codepoints++;
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
//         __throw(::exception::exception("utf16_to_utf16_len :: invalid code_point, do something ! "));
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
//strsize utf16_to_utf16(wd16char* point, const wd16char* codepoints, strsize input_size)
//{
//
//   strsize len = 0;
//
//   while (input_size != 0)
//   {
//
//      u32 cp = *codepoints++;
//
//      input_size--;
//
//      if (cp == 0)
//         break;
//
//      if (cp < 0x10000)
//      {
//
//         *point++ = static_cast<wd16char>(cp);
//
//      }
//      else if (cp <= 0x10FFFF)
//      {
//
//         cp -= 0x10000;
//
//         *point++ = static_cast<wd16char>((cp >> 10) + 0xD800);
//
//         *point++ = static_cast<wd16char>((cp & 0x3FF) + 0xDC00);
//
//      }
//      else
//      {
//
//         *point++ = static_cast<wd16char>(0xFFFD);
//
//      }
//
//   }
//
//   return len;
//
//}
//

//wstring utf16_to_utf16(const wd16char* input, strsize input_size)
//{
//
//   strsize s = utf16_to_utf16_len(input, input_size);
//
//   wstring wstr;
//
//   wd16char* point = wstr.get_buffer(s);
//
//   utf16_to_utf16(point, input, s);
//
//   point[s] = 0;
//
//   return wstr;
//
//}
//



extern "C"
{

   char* c_utf8_str(const wchar_t* str)
   {
      return strdup(::str::international::unicode_to_utf8(str));
   }

   wchar_t* c_wide_str(const char* str)
   {
#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
      wchar_t* point = ansi_to_wd32_dup(str);
      wchar_t* point2 = wcsdup(point);
      memory_free(point);
      return point2;
#else
      return wcsdup(::str::international::utf8_to_unicode(str));
#endif

   }



} // extern "C"





// CLASS_DECL_AURA const char* yoshi_strcat(const char* psz1, const char* psz2, bool bFree2)
// {

//    strsize iLen1 = psz1 == nullptr ? 0 : strlen(psz1);

//    strsize iLen2 = psz2 == nullptr ? 0 : strlen(psz2);

//    strsize iLen = iLen1 + iLen2 + 1;

//    char* psz = (char*)memory_alloc(iLen);

//    strcpy(psz, "");

//    if (psz1 != nullptr)
//    {

//       ansi_concatenate(psz, psz1);

//       memory_free((void*)psz1);

//    }

//    if (psz2 != nullptr)
//    {

//       ansi_concatenate(psz, psz2);

//       if (bFree2)
//       {

//          memory_free((void*)psz2);

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





wd16char surrogate_to_utf16(wd16char _1st, wd16char _2nd)
{

   return (_1st << 10) + _2nd - 0x35fdc00;

}


//strsize utf16_to_utf16(wd16char* output, const unichar* input, strsize input_size)
//{
//
//   wd16char* start = output;
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
//            __throw(::exception::exception("utf16_to_utf16_len"));
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


//strsize utf16_to_utf16_len(const unichar* input, strsize input_size)
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
//            __throw(::exception::exception("utf16_to_utf16_len"));
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



//wd16char* utf16_to_utf16(const unichar* input, strsize input_size)
//{
//
//   strsize s = utf16_to_utf16_len(input, input_size);
//
//   wd16char* v = (wd16char*)memory_alloc(sizeof(wd16char) * (s + 1));
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
//Anime & Manga 178 178 5
//Science Fiction & Fantasy 173 173 6
//Meta Stack Exchange 121 121 5
//Cryptography 108 108 4
//
//Top Network Posts
//
//5Is it possible for a genin to become a jonin?
//View more network posts →



// on Windows, wchar_t is 2 bytes, suitable for UTF-16
//std::wstring Utf32ToUtf16(const std::vector<u32> &codepoints)
//{
//   std::wstring result;
//   int len = 0;
//
//   for (std::vector<u32>::iterator iter = codepoints.begin(); iter != codepoints.end(); ++iter)
//   {
//      u32 cp = *iter;
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
//      for (std::vector<u32>::iterator iter = codepoints.begin(); iter != codepoints.end(); ++iter)
//      {
//         u32 cp = *iter;
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

//strsize wd16_to_ansi_len(const wd16char* pwsz, strsize input_size)
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


//strsize utf16_len(const wd16char* pwsz)
//{
//
//   if (pwsz == nullptr)
//   {
//      return 0;
//   }
//   strsize s = 0;
//   while (*pwsz != 0)
//   {
//      s++;
//      pwsz++;
//   }
//   return s;
//}


//strsize wd16_to_ansi(char* psz, const wd16char* pwsz, strsize srclen)
//{
//   //unsigned short * pwsz = (unsigned short *)pwszParam;
//   strsize c = 0;
//   i32 n;
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


//string wd16_to_ansi(const wd16char* pwszUni32, strsize iUni32Len)
//{
//
//   strsize iUtf8Len = wd16_to_ansi_len(pwszUni32, iUni32Len);
//
//   string str;
//
//   char* psz = str.get_string_buffer(iUtf8Len);
//
//   wd16_to_ansi(psz, pwszUni32, iUni32Len);
//
//   str.release_string_buffer(iUtf8Len);
//
//   return str;
//
//}


strsize ansi_to_wd16_len(const char* psz, strsize srclen)
{

   strsize utf16len = 0;

   wd16char * pwsz = nullptr;

   while (srclen != 0 && psz != nullptr && *psz != '\0')
   {

      ::i32 len;

      ::i32 iChar = ::str::ch::uni_index_len(psz, len);

      if (iChar < 0)
      {

         return -1;

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

   }

   return utf16len;

}


strsize ansi_to_wd16(wd16char* pwsz, const char* psz, strsize srclen)
{

   strsize len = 0;

   while (srclen != 0 && psz != nullptr && *psz != '\0')
   {

      wd32char u32;

      auto used_len = ansi_to_wd32_char(&u32, psz, srclen);

      if(used_len <= 0)
      {

         return -1;

      }

      psz += used_len;

      srclen -= used_len;

      auto u16len = wd32_to_wd16_char(pwsz, u32);

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




wd16char* ansi_to_wd16_dup(const char* input, strsize input_size)
{

   strsize s = ansi_to_wd16_len(input, input_size);

   wd16char* v = (wd16char*)memory_alloc(sizeof(wd16char) * (s + 1));

   ansi_to_wd16(v, input, s);

   v[s] = 0;

   return v;

}



strsize utf16_to_utf16_len(const wd16char* codepoints, strsize input_size)
{

   strsize len = 0;

   while (input_size != 0)
   {

      u32 cp = *codepoints++;

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
         __throw(::exception::exception("utf16_to_utf16_len :: invalid code_point, do something ! "));

         //++len;

      }

   }

   return len;

}


strsize utf16_to_utf16(wd16char * point, const wd16char* codepoints, strsize input_size)
{

   strsize len = 0;

   while (input_size != 0)
   {

      u32 cp = *codepoints++;

      input_size--;

      if (cp == 0)
         break;

      if (cp < 0x10000)
      {

         *point++ = static_cast<wd16char>(cp);

      }
      else if (cp <= 0x10FFFF)
      {

         cp -= 0x10000;

         *point++ = static_cast<wd16char>((cp >> 10) + 0xD800);

         *point++ = static_cast<wd16char>((cp & 0x3FF) + 0xDC00);

      }
      else
      {

         *point++ = static_cast<wd16char>(0xFFFD);

      }

   }

   return len;

}


//wstring utf16_to_utf16(const wd16char* input, strsize input_size)
//{
//
//   strsize s = utf16_to_utf16_len(input, input_size);
//
//   wstring wstr;
//
//   unichar* point = wstr.get_buffer(s);
//
//   utf16_to_utf16(point, input, s);
//
//   point[s] = 0;
//
//   return wstr;
//
//}
//
//
//












//string wd16_to_ansi(const wd16char * pwszUni32, strsize iUni32Len)
//{
//
//   strsize iUtf8Len = wd16_to_ansi_len(pwszUni32, iUni32Len);
//
//   string str;
//
//   char * psz = str.get_string_buffer(iUtf8Len);
//
//   wd16_to_ansi(psz, pwszUni32, iUni32Len);
//
//   str.release_string_buffer(iUtf8Len);
//
//   return str;
//
//}


const wd16char * utf16_inc(const wd16char * psz)
{

   auto len = wd16_to_wd32_len(psz, 2);

   if(len > 0)
   {

      return psz + len;

   }

   return nullptr;

}












string wd16_to_ansi_str(const wd16char * pwsz, strsize srclen)
{

   strsize iUtf8Len = wd16_to_ansi_len(pwsz, srclen);

   string str;

   char * psz = str.get_string_buffer(iUtf8Len);

   wd16_to_ansi(psz, pwsz, srclen);

   str.release_string_buffer(iUtf8Len);

   return str;

}



