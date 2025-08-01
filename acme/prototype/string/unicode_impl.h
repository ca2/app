// Refactored by camilo on 2022-11-04 05:43 <3ThomasBorregaardSorensen!!
#pragma once


inline int get_utf8_char_length(const_char_pointer psz)
{

   int len = utf8_unicode_length(*psz);
   if (len == 0) return 0;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 1) return 1;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 2) return 2;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 3) return 3;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 4) return 4;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 5) return 5;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 6) return 6;

   {
      return -1;
   }
   return -1;
}




//inline int unicode_index(const_char_pointer &input, character_count * psrclen)
//{
//
//   if (*input == 0)
//   {
//
//      return 0;
//
//   }
//
//   if (*psrclen < 1)
//   {
//
//      return -1;
//
//   }
//
//   ::wd32_character unsigned int;
//
//   character_count used_len = ansi_to_wd32_char(&unsigned int, input, *psrclen);
//
//   if (used_len < 0)
//   {
//
//      return -1;
//
//   }
//
//   input += used_len;
//
//   *psrclen -= used_len;
//
//   return unsigned int;
//
//}
//
//
//inline int unicode_index(const ::wd16_character *& input, character_count * psrclen)
//{
//
//   if (*input == 0)
//   {
//
//      return 0;
//
//   }
//
//   if (*psrclen < 1)
//   {
//
//      return -1;
//
//   }
//
//   int i = *input;
//
//   ::wd32_character unsigned int;
//
//   character_count used_len = wd16_to_wd32_char(&unsigned int, input, *psrclen);
//
//   input += used_len;
//
//   *psrclen -= used_len;
//
//   return i;
//
//}


inline int unicode_index_length(const ::wd32_character *& input, character_count * psrclen)
{

   if (*input == 0)
   {

      return 0;

   }

   if (*psrclen < 1)
   {

      return -1;

   }

   int i = *input;

   input++;

   (*psrclen)--;

   return i;

}


inline int unicode_index_length(const_char_pointer pszUtf8, int & len)
{

   if (is_empty(pszUtf8))
   {

      len = 0;

      return 0;

   }

   int ch = 0;

   unsigned char c;

   len = 0;

   char extraBytesToRead = utf8_e(*pszUtf8);

   switch (extraBytesToRead)
   {
   case 5:
      ch += c = pszUtf8[len++]; ch <<= 6;
      if (c == '\0') { return -1; }
   case 4:
      ch += c = pszUtf8[len++]; ch <<= 6;
      if (c == '\0') { return -1; }
   case 3:
      ch += c = pszUtf8[len++]; ch <<= 6;
      if (c == '\0') { return -1; }
   case 2:
      ch += c = pszUtf8[len++]; ch <<= 6;
      if (c == '\0') { return -1; }
   case 1:
      ch += c = pszUtf8[len++]; ch <<= 6;
      if (c == '\0') { return -1; }
   case 0:
      ch += c = pszUtf8[len++];
      if (c == '\0') { return -1; }
   }

   ch -= utf8_o(extraBytesToRead);

   return ch;

}


inline int consume_unicode_index(const_char_pointer &pszUtf8)
{

   int len = 0;

   auto i = unicode_index_length(pszUtf8, len);

   if(i < 0)
   {

      throw_parsing_exception("end of string or not valid character to parse");

   }

   pszUtf8 += len;

   return i;

}


inline int unicode_index_length(const ::wd16_character * input, int & len)
{

   if (input[0] == 0)
   {

      len = 0;

      return 0;

   }

   if (utf16_is_2nd_surrogate(input[0]))
   {

      len = -1;

      return -1;

   }
   else if (utf16_is_1st_surrogate(input[0]))
   {

      if (utf16_is_2nd_surrogate(input[1]))
      {

         len = 2;

         return utf16_surrogate_to_utf32(input[0], input[1]);

      }
      else
      {

         len = -1;

         return -1;

      }

   }
   else
   {

      len = 1;

      return input[0];

   }

}


inline bool is_legal_unicode_index(int iUnicodeIndex)
{

   return iUnicodeIndex >= 0 && iUnicodeIndex < 65536 ? true : false;

   //return ca >= ((unsigned long long) 0xffffffffu) ? false : true;

}


inline int unicode_to_lower_case(int i)
{
   if (!is_legal_unicode_index(i))
      return -1;
   unsigned int c1 = CHAR_PROP(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return (::wd32_character)i;
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return (::wd32_character)(i + 1);
   return ::wd32_character(i - (c1 >> 16));
}


inline int unicode_to_upper_case(int i)
{
   if (!is_legal_unicode_index(i))
      return -1;
   unsigned int c1 = CHAR_PROP(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return ::wd32_character(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return ::wd32_character(i - 1);
   return ::wd32_character(i - (c1 >> 16));
}


//template < primitive_character CHARACTER >
//inline const CHARACTER * string_scan(const ::range < CHARACTER > & block, const ::range < CHARACTER > & blockCharacters) noexcept
//{
//
//   const CHARACTER * psz;
//
//   if (_string_scan_prefix(scopedstr, block, blockCharacters))
//   {
//
//      return psz;
//
//   }
//
//   return _string_scan(block, blockCharacters);
//
//}


//inline const_char_pointer _string_scan(const array_range < ::ansi_character > & block, const array_range < ::ansi_character > & blockCharacters) noexcept
//{
//
//   return ansi_scan(block, blockCharacters);
//
//}
//
//
//inline const ::wd16_character * _string_scan(const ::array_range < ::wd16_character > & block, const ::array_range < ::wd16_character > & blockCharacters) noexcept
//{
//
//   return wd16_scan(block, blockCharacters);
//
//}


inline const ::wd32_character * wd32_find_first_character_in(const ::const_wd32_range & block, const ::const_wd32_range & blockCharacters)
{

   //if (block.is_null_terminated() && blockCharacters.is_null_terminated())
   //{

   //   return wd32_pbrk((::wd32_character *)block.data(), blockCharacters.data());

   //}
   //else
   //{

      return block.find_first_character_in(blockCharacters, ::comparison::comparison < ::wd32_character >());

//   }

}


inline int unicode_to_title_case(int i)
{
   if (!is_legal_unicode_index(i))
      return -1;
   unsigned int c1 = CHAR_PROP(i);
   if (TITLE_CASE(c1))  // titlecase exists
   {
      if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return ::wd32_character(i + 1);
      if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return ::wd32_character(i - 1);
      return ::wd32_character(i);
   }
   else  // has no titlecase form
      if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll)
         return ::wd32_character(i - (c1 >> 16));
   return ::wd32_character(i);
}


inline int unicode_to_numeric_value(int i, float * f)
{
   if (!is_legal_unicode_index(i))
      return false;
   unsigned int c1 = CHAR_PROP(i);
   if (!NUMBER(c1)) return false;
   *f = CHAR_PROP2(i);
   return true;
}


inline bool unicode_is_lower_case(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Ll;
}


inline bool unicode_is_upper_case(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Lu;
}


inline bool unicode_is_title_case(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Lt;
}


inline bool unicode_is_letter(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   unsigned int c1 = CHAR_CATEGORY(CHAR_PROP(i));
   return ((((1 << CHAR_CATEGORY_Lu) |
      (1 << CHAR_CATEGORY_Ll) |
      (1 << CHAR_CATEGORY_Lt) |
      (1 << CHAR_CATEGORY_Lm) |
      (1 << CHAR_CATEGORY_Lo)
      ) >> c1) & 1) != 0;
}


inline bool unicode_is_letter_or_digit(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   unsigned int c1 = CHAR_CATEGORY(CHAR_PROP(i));
   return ((((1 << CHAR_CATEGORY_Lu) |
      (1 << CHAR_CATEGORY_Ll) |
      (1 << CHAR_CATEGORY_Lt) |
      (1 << CHAR_CATEGORY_Lm) |
      (1 << CHAR_CATEGORY_Lo) |
      (1 << CHAR_CATEGORY_Nd)
      ) >> c1) & 1) != 0;
}


inline bool unicode_is_digit(int i)
{

   if (!is_legal_unicode_index(i))
      return false;

   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Nd;

}


inline bool unicode_is_assigned(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) != CHAR_CATEGORY_Cn;
}


inline bool unicode_is_space_char(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return  ((((1 << CHAR_CATEGORY_Zs) |
      (1 << CHAR_CATEGORY_Zl) |
      (1 << CHAR_CATEGORY_Zp)
      ) >> CHAR_CATEGORY(CHAR_PROP(i))) & 1) != 0;
}


inline bool unicode_is_whitespace(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return  (i == 0x20)
      ||
      ((i <= 0x0020) &&
         (((((1 << 0x0009) |
            (1 << 0x000A) |
            (1 << 0x000C) |
            (1 << 0x000D)) >> i) & 1) != 0))
      ||
      (((((1 << CHAR_CATEGORY_Zs) |
         (1 << CHAR_CATEGORY_Zl) |
         (1 << CHAR_CATEGORY_Zp)
         ) >> CHAR_CATEGORY(CHAR_PROP(i))) & 1) != 0);
}


inline bool unicode_is_number(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return NUMBER(CHAR_PROP(i)) != 0;
}


inline ECharCategory unicode_get_category(int i)
{
   if (!is_legal_unicode_index(i))
      return CHAR_CATEGORY_LAST;
   return ECharCategory(CHAR_CATEGORY(CHAR_PROP(i)));
}


inline int unicode_get_combining_class(int i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return COMBINING_CLASS(CHAR_PROP(i));
}


inline bool unicode_is_mirrored(int i)
{

   if (!is_legal_unicode_index(i))
      return false;

   return MIRRORED(CHAR_PROP(i)) != 0;

}


inline int unicode_size_of_tables()
{
   return sizeof(arr_idxCharInfo) + sizeof(arr_CharInfo) + sizeof(arr_idxCharInfo2) + sizeof(arr_CharInfo2);
}

inline const_char_pointer unicode_next(const_char_pointer psz)
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   if (*psz == '\0')
   {

      return psz;

   }

   char len = 1 + trailingBytesForUTF8(*psz);

   if (len == 0) return psz;

   if (*psz++ == 0)
   {

      throw_encoding_exception("premature end of utf8 encoded string (1)");

      return nullptr;

   }

   if (len == 1) return psz;

   if (*psz++ == 0)
   {

      throw_encoding_exception("premature end of utf8 encoded string (2)");

      return nullptr;

   }

   if (len == 2) return psz;

   if (*psz++ == 0)
   {

      throw_encoding_exception("premature end of utf8 encoded string (3)");

      return nullptr;

   }

   if (len == 3) return psz;

   if (*psz++ == 0)
   {

      throw_encoding_exception("premature end of utf8 encoded string (4)");

      return nullptr;

   }

   if (len == 4) return psz;

   if (*psz++ == 0)
   {

      throw_encoding_exception("premature end of utf8 encoded string (5)");

      return nullptr;

   }

   if (len == 5) return psz;

   if (*psz++ == 0)
   {

      throw_encoding_exception("premature end of utf8 encoded string (6)");

      return nullptr;

   }

   if (len == 6) return psz;

   throw_encoding_exception("premature end of utf8 encoded string (7)");

   return nullptr;

}


inline const_char_pointer unicode_next(const_char_pointer psz, int * piError)
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   if (*psz == '\0')
   {

      return psz;

   }

   *piError = 0;

   char len = 1 + trailingBytesForUTF8(*psz);

   if (len == 0) return psz;

   if (*psz++ == 0)
   {

      *piError = 1;

      return nullptr;

   }

   if (len == 1) return psz;

   if (*psz++ == 0)
   {

      *piError = 2;

      return nullptr;

   }

   if (len == 2) return psz;

   if (*psz++ == 0)
   {

      *piError = 3;

      return nullptr;

   }

   if (len == 3) return psz;

   if (*psz++ == 0)
   {

      *piError = 4;

      return nullptr;

   }

   if (len == 4) return psz;

   if (*psz++ == 0)
   {

      *piError = 5;

      return nullptr;

   }

   if (len == 5) return psz;

   if (*psz++ == 0)
   {

      *piError = 6;

      return nullptr;

   }

   if (len == 6) return psz;

   *piError = 7;

   return nullptr;

}


inline const ::wd16_character * unicode_next(const ::wd16_character * psz)
{

   auto len = wd16_to_wd32_len(psz, 2);

   if (len > 0)
   {

      return psz + len;

   }

   return nullptr;

}


inline const ::wd32_character * unicode_next(const ::wd32_character * psz)
{

   return psz + 1;

}


inline const_char_pointer unicode_prior(const_char_pointer psz, const_char_pointer pszBeg)
{

   if (psz <= pszBeg)
   {

      return nullptr;

   }

   if ((*(psz - 1) & 0x80) == 0x00)
   {

      if ((psz - 1) < pszBeg)
      {

         return nullptr;

      }

      return psz - 1;

   }
   else if ((*(psz - 2) & 0xE0) == 0xC0)
   {

      if ((psz - 2) < pszBeg)
      {

         return nullptr;

      }

      return psz - 2;

   }
   else if ((*(psz - 3) & 0xF0) == 0xE0)
   {

      if ((psz - 3) < pszBeg)
      {

         return nullptr;

      }

      return psz - 3;

   }
   else if ((*(psz - 4) & 0xF8) == 0xF0)
   {

      if ((psz - 4) < pszBeg)
      {

         return nullptr;

      }

      return psz - 4;

   }
   else if ((*(psz - 5) & 0xFC) == 0xF8)
   {

      if ((psz - 5) < pszBeg)
      {

         return nullptr;

      }

      return psz - 5;

   }
   else if ((*(psz - 6) & 0xFE) == 0xFC)
   {

      if ((psz - 6) < pszBeg)
      {

         return nullptr;

      }

      return psz - 6;

   }

   if ((psz - 1) < pszBeg)
   {

      return nullptr;

   }

   return psz - 1;

}


inline const ::wd16_character * unicode_prior(const ::wd16_character * psz, const ::wd16_character * pszBeg)
{

   if (psz <= pszBeg)
   {

      return nullptr;

   }

   if (utf16_is_2nd_surrogate(*(psz - 1)))
   {

      if (psz - 1 <= pszBeg)
      {

         return nullptr;

      }

      return psz - 2;

   }

   return psz - 1;

}


inline const ::wd32_character * unicode_prior(const ::wd32_character * psz, const ::wd32_character * pszBeg)
{

   if (psz <= pszBeg)
   {

      return nullptr;

   }

   return psz - 1;

}


//inline int unicode_index(const_char_pointer &pszUtf8)
//{
//
//   if (*pszUtf8 == '\0')
//   {
//
//      return 0;
//
//   }
//
//   int ch = 0;
//
//   unsigned char c;
//
//   char extraBytesToRead = utf8_e(*pszUtf8);
//
//   switch (extraBytesToRead)
//   {
//   case 5:
//      ch += c = *pszUtf8++; ch <<= 6;
//      if (c == '\0') { return -1; }
//   case 4:
//      ch += c = *pszUtf8++; ch <<= 6;
//      if (c == '\0') { return -1; }
//   case 3:
//      ch += c = *pszUtf8++; ch <<= 6;
//      if (c == '\0') { return -1; }
//   case 2:
//      ch += c = *pszUtf8++; ch <<= 6;
//      if (c == '\0') { return -1; }
//   case 1:
//      ch += c = *pszUtf8++; ch <<= 6;
//      if (c == '\0') { return -1; }
//   case 0:
//      ch += c = *pszUtf8++;
//      if (c == '\0') { return -1; }
//   }
//
//   ch -= utf8_o(extraBytesToRead);
//
//   return ch;
//
//}
//
//
//inline int unicode_index(const ::wd16_character *& input)
//{
//
//   if (input[0] == 0)
//   {
//
//      return 0;
//
//   }
//
//   if (utf16_is_2nd_surrogate(input[0]))
//   {
//
//      return -1;
//
//   }
//   else if (utf16_is_1st_surrogate(input[0]))
//   {
//
//      if (utf16_is_2nd_surrogate(input[1]))
//      {
//
//         auto iUnicode = utf16_surrogate_to_utf32(input[0], input[1]);
//
//         input += 2;
//
//         return iUnicode;
//
//      }
//      else
//      {
//
//         return -1;
//
//      }
//
//   }
//   else
//   {
//
//      auto iUnicode = input[0];
//
//      input++;
//
//      return iUnicode;
//
//   }
//
//}


inline int ansichar_unicode_len(::wd32_character i)
{
   if (i < 0)
   {
      return -1;
   }
   else if (i < 0x0080)
   {
      return 1;
   }
   else if (i < 0x0800)
   {
      return 2;
   }
   else
   {
      return 3;
   }
}





template < typename TYPE1, typename TYPE2 >
inline ::std::strong_ordering compare(const TYPE1 & str1, const TYPE2 & str2)
{

   return string_compare(str1, str2);

}


template < typename TYPE1, typename TYPE2 >
inline ::std::strong_ordering case_insensitive_order(const TYPE1 & str1, const TYPE2 & str2)
{

   return case_insensitive_string_order(str1, str2);

}




template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent)
{

   return equals(str1, str2) ? strOnEqual : strOnDifferent;

}


template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent)
{

   return case_insensitive_equals(str1, str2) ? strOnEqual : strOnDifferent;

}


//template < typename TYPE_CHAR >
//inline bool string_begins(const TYPE_CHAR * psz, character_count len, const TYPE_CHAR * pszPrefix, character_count lenPrefix)
//{
//
//   if (lenPrefix > len)
//   {
//
//      return false;
//
//   }
//
//   return string_count_compare(psz, pszPrefix, lenPrefix) == 0;
//
//}



//template < typename TYPE_CHAR >
//inline bool string_ends(const TYPE_CHAR * psz, character_count len, const TYPE_CHAR * pszSuffix, character_count lenSuffix)
//{
//
//   auto offset = len - lenSuffix;
//
//   if (offset < 0)
//   {
//
//      return false;
//
//   }
//
//   auto pszCompare = psz + offset;
//
//   return string_count_compare(scopedstrCompare, pszSuffix, lenSuffix) == 0;
//
//}


//template < typename TYPE_CHAR >
//inline bool case_insensitive_string_begins(const TYPE_CHAR * psz, character_count len, const TYPE_CHAR * pszPrefix, character_count lenPrefix)
//{
//
//   if (lenPrefix > len)
//   {
//
//      return false;
//
//   }
//
//   return case_insensitive_string_count_compare(scopedstr, pszPrefix, lenPrefix) == 0;
//
//}


//template < typename TYPE_CHAR >
//inline bool case_insensitive_string_ends(const TYPE_CHAR * psz, character_count len, const TYPE_CHAR * pszSuffix, character_count lenSuffix)
//{
//
//   auto offset = len - lenSuffix;
//
//   if (offset < 0)
//   {
//
//      return false;
//
//   }
//
//   auto pszCompare = psz + offset;
//
//   return case_insensitive_string_count_compare(scopedstrCompare, pszSuffix, lenSuffix) == 0;
//
//}


template < typename CHAR_TYPE >
bool string_eat_before(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound)
{

   ASSERT(&str != &strBefore);

   if (&str == &strBefore)
   {

      return false;

   }

   auto pFind = str.find(strSeparator);

   if (::is_null(pFind))
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = str;

         str.empty();

      }

      return false;

   }

   strBefore = str(0, pFind);

   str = str(pFind + strSeparator.length());

   return true;

}


template < typename CHAR_TYPE >
bool string_eat_before_let_separator(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound)
{

   ASSERT(&str != &strBefore);

   if (&str == &strBefore)
   {

      return false;

   }

   auto pFind = str.find(strSeparator);

   if (::is_null(pFind))
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = str;

         str = strSeparator;

      }

      return false;

   }

   strBefore = str(0, pFind);

   str = str(pFind);

   return true;

}





inline int unicode_len(const_char_pointer pszUtf8)
{

   int len;

   if (unicode_index_length(pszUtf8, len) < 0)
   {

      return -1;

   }

   return len;

}






template < typename CHAR_STRING >
inline bool is_trimmed_string_empty(CHAR_STRING p)
{

   if (::is_null(p))
   {

      return true;

   }

   while (*p)
   {

      if (!unicode_is_whitespace(p))
      {

         return false;

      }

      unicode_increment(p);

   }

   return true;

}


