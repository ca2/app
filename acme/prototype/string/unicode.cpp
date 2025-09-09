#include "framework.h"
////#include "acme/exception/exception.h"


CLASS_DECL_ACME int is_surrogated(unsigned int character)
{

   return 0x10000 <= character && character <= 0x10FFFF;

}


::wd32_character surrogate_to_utf32(::wd16_character high, ::wd16_character low)
{

   return (high << 10) + low - 0x35fdc00;

}


character_count wd16_to_wd32(::wd32_character* output, const ::wd16_character* input, character_count input_size)
{

   ::wd32_character* start = output;

   const ::wd16_character * const end = input + input_size;

   while (input < end)
   {

      const ::wd16_character uc = *input++;

      if (!utf16_is_surrogate(uc))
      {

         *output++ = uc;

      }
      else
      {

         if (utf16_is_1st_surrogate(uc) && input < end && utf16_is_2nd_surrogate(*input))
         {

            *output++ = surrogate_to_utf32(uc, *input++);

         }
         else
         {

            throw ::exception(error_not_supported, "wd16_to_wd32_len");

         }

      }

   }

   return output - start;

}


character_count wd16_to_wd32_len(const ::wd16_character * input, character_count input_size)
{

   const ::wd16_character * const end = input + input_size;

   int c = 0;

   while (((input_size < 0) && *input) || ((input_size >= 0) && input < end))
   {

      const ::wd16_character uc = *input++;

      if (!utf16_is_surrogate(uc))
      {

         c++;

      }
      else
      {

         if (utf16_is_1st_surrogate(uc) && input < end && utf16_is_2nd_surrogate(*input))
         {

            c++;

         }
         else
         {

            throw ::exception(error_invalid_buffer, "wd16_to_wd32_len");

         }

      }

   }

   return c;

}



::wd32_character* wd16_to_wd32(const ::wd16_character * input, character_count input_size)
{

   character_count s = wd16_to_wd32_len(input, input_size);

   ::wd32_character* v = (::wd32_character*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(::wd32_character) * (s + 1), nullptr);

   wd16_to_wd32(v, input, s);

   v[s] = 0;

   return v;

}

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
//Impact more network posts ...>



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

// character_count wd32_to_ansi_len(const ::wd32_character* pwsz, character_count input_size)
// {

//    if (pwsz == nullptr)
//    {

//       return -1;

//    }

//    character_count len = 0;

//    character_count n;

//    char sz[16];

//    while (input_size != 0 && *pwsz != L'\0')
//    {

//       n = unichar_to_utf8_char(sz, *pwsz);

//       if (n <= 0)
//       {

//          break;

//       }

//       len += n;

//       input_size--;

//       pwsz++;

//    }

//    return len;

// }


// character_count utf32_len(const ::wd32_character* pwsz)
// {

//    if (pwsz == nullptr)
//    {
//       return 0;
//    }
//    character_count s = 0;
//    while (*pwsz != 0)
//    {
//       s++;
//       pwsz++;
//    }
//    return s;
// }







// CLASS_DECL_ACME character_count __utf_to_utf_length(const ::ansi_character* p, const ::wd16_character* s, character_count n)
// {
//
//
//    return utf_to_utf_length(p, s, n);
// }