// Refactored by camilo on 2022-11-04 05:43 <3ThomasBorregaardSorensen!!
#pragma once


inline int get_utf8_char_length(const char * psz)
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




//inline i32 unicode_index(const char *& input, strsize * psrclen)
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
//   ::wd32char u32;
//
//   strsize used_len = ansi_to_wd32_char(&u32, input, *psrclen);
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
//   return u32;
//
//}
//
//
//inline i32 unicode_index(const wd16char *& input, strsize * psrclen)
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
//   ::i32 i = *input;
//
//   ::wd32char u32;
//
//   strsize used_len = wd16_to_wd32_char(&u32, input, *psrclen);
//
//   input += used_len;
//
//   *psrclen -= used_len;
//
//   return i;
//
//}


inline i32 unicode_index_length(const wd32char *& input, strsize * psrclen)
{

   if (*input == 0)
   {

      return 0;

   }

   if (*psrclen < 1)
   {

      return -1;

   }

   ::i32 i = *input;

   input++;

   (*psrclen)--;

   return i;

}


inline i32 unicode_index_length(const ansichar * pszUtf8, ::i32 & len)
{

   if (is_empty(pszUtf8))
   {

      len = 0;

      return 0;

   }

   i32 ch = 0;

   byte c;

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


inline i32 consume_unicode_index(const ansichar *& pszUtf8)
{

   ::i32 len = 0;

   auto i32 = unicode_index_length(pszUtf8, len);

   if(i32 < 0)
   {

      throw_parsing_exception("end of string or not valid character to parse");

   }

   pszUtf8 += len;

   return i32;

}


inline i32 unicode_index_length(const wd16char * input, i32 & len)
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


inline bool is_legal_unicode_index(i32 iUnicodeIndex)
{

   return iUnicodeIndex >= 0 && iUnicodeIndex < 65536 ? true : false;

   //return ca >= ((u64) 0xffffffffu) ? false : true;

}


inline ::i32 unicode_to_lower_case(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return -1;
   ::u32 c1 = CHAR_PROP(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return (wd32char)i;
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return (wd32char)(i + 1);
   return wd32char(i - (c1 >> 16));
}


inline ::i32 unicode_to_upper_case(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return -1;
   u32 c1 = CHAR_PROP(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return wd32char(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return wd32char(i - 1);
   return wd32char(i - (c1 >> 16));
}


inline const ansichar * string_scan(const ansichar * pszBlock, const ansichar * pszMatch) noexcept
{

   if (pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
      return nullptr;

   return ansi_scan(pszBlock, pszMatch);

}


inline const wd16char * string_scan(const wd16char * pszBlock, const wd16char * pszMatch) noexcept
{

   if (pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
      return nullptr;

   return wd16_scan(pszBlock, pszMatch);

}


inline const wd32char * string_scan(const wd32char * pszBlock, const wd32char * pszMatch) noexcept
{

   if (pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
      return nullptr;

   return wd32_scan(pszBlock, pszMatch);

}




inline ::i32 unicode_to_title_case(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return -1;
   u32 c1 = CHAR_PROP(i);
   if (TITLE_CASE(c1))  // titlecase exists
   {
      if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return wd32char(i + 1);
      if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return wd32char(i - 1);
      return wd32char(i);
   }
   else  // has no titlecase form
      if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll)
         return wd32char(i - (c1 >> 16));
   return wd32char(i);
}


inline i32 unicode_to_numeric_value(i32 i, float * f)
{
   if (!is_legal_unicode_index(i))
      return false;
   u32 c1 = CHAR_PROP(i);
   if (!NUMBER(c1)) return false;
   *f = CHAR_PROP2(i);
   return true;
}


inline bool unicode_is_lower_case(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Ll;
}


inline bool unicode_is_upper_case(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Lu;
}


inline bool unicode_is_title_case(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Lt;
}


inline bool unicode_is_letter(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   u32 c1 = CHAR_CATEGORY(CHAR_PROP(i));
   return ((((1 << CHAR_CATEGORY_Lu) |
      (1 << CHAR_CATEGORY_Ll) |
      (1 << CHAR_CATEGORY_Lt) |
      (1 << CHAR_CATEGORY_Lm) |
      (1 << CHAR_CATEGORY_Lo)
      ) >> c1) & 1) != 0;
}


inline bool unicode_is_letter_or_digit(::i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   u32 c1 = CHAR_CATEGORY(CHAR_PROP(i));
   return ((((1 << CHAR_CATEGORY_Lu) |
      (1 << CHAR_CATEGORY_Ll) |
      (1 << CHAR_CATEGORY_Lt) |
      (1 << CHAR_CATEGORY_Lm) |
      (1 << CHAR_CATEGORY_Lo) |
      (1 << CHAR_CATEGORY_Nd)
      ) >> c1) & 1) != 0;
}


inline bool unicode_is_digit(i32 i)
{

   if (!is_legal_unicode_index(i))
      return false;

   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Nd;

}


inline bool unicode_is_assigned(i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) != CHAR_CATEGORY_Cn;
}


inline bool unicode_is_space_char(i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return  ((((1 << CHAR_CATEGORY_Zs) |
      (1 << CHAR_CATEGORY_Zl) |
      (1 << CHAR_CATEGORY_Zp)
      ) >> CHAR_CATEGORY(CHAR_PROP(i))) & 1) != 0;
}


inline bool unicode_is_whitespace(i32 i)
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


inline bool unicode_is_number(i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return NUMBER(CHAR_PROP(i)) != 0;
}


inline ECharCategory unicode_get_category(i32 i)
{
   if (!is_legal_unicode_index(i))
      return CHAR_CATEGORY_LAST;
   return ECharCategory(CHAR_CATEGORY(CHAR_PROP(i)));
}


inline i32 unicode_get_combining_class(i32 i)
{
   if (!is_legal_unicode_index(i))
      return false;
   return COMBINING_CLASS(CHAR_PROP(i));
}


inline bool unicode_is_mirrored(i32 i)
{

   if (!is_legal_unicode_index(i))
      return false;

   return MIRRORED(CHAR_PROP(i)) != 0;

}


inline i32 unicode_size_of_tables()
{
   return sizeof(arr_idxCharInfo) + sizeof(arr_CharInfo) + sizeof(arr_idxCharInfo2) + sizeof(arr_CharInfo2);
}

inline const ansichar * unicode_next(const ansichar * psz)
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


inline const ansichar * unicode_next(const ansichar * psz, int * piError)
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


inline const wd16char * unicode_next(const wd16char * psz)
{

   auto len = wd16_to_wd32_len(psz, 2);

   if (len > 0)
   {

      return psz + len;

   }

   return nullptr;

}


inline const wd32char * unicode_next(const wd32char * psz)
{

   return psz + 1;

}


inline const char * unicode_prior(const char * psz, const char * pszBeg)
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


inline const wd16char * unicode_prior(const wd16char * psz, const wd16char * pszBeg)
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


inline const wd32char * unicode_prior(const wd32char * psz, const wd32char * pszBeg)
{

   if (psz <= pszBeg)
   {

      return nullptr;

   }

   return psz - 1;

}


//inline i32 unicode_index(const ansichar *& pszUtf8)
//{
//
//   if (*pszUtf8 == '\0')
//   {
//
//      return 0;
//
//   }
//
//   i32 ch = 0;
//
//   byte c;
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
//inline i32 unicode_index(const wd16char *& input)
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


inline i32 ansichar_unicode_len(wd32char i)
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
inline i32 compare(const TYPE1 & str1, const TYPE2 & str2)
{

   return string_compare(str1, str2);

}


template < typename TYPE1, typename TYPE2 >
inline i32 compare_ci(const TYPE1 & str1, const TYPE2 & str2)
{

   return string_compare_ci(str1, str2);

}




template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent)
{

   return equals(str1, str2) ? strOnEqual : strOnDifferent;

}


template < typename TYPE1, typename TYPE2 >
inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent)
{

   return equals_ci(str1, str2) ? strOnEqual : strOnDifferent;

}


template < typename TYPE_CHAR >
inline bool string_begins(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszPrefix, strsize lenPrefix)
{

   if (lenPrefix > len)
   {

      return false;

   }

   return string_count_compare(psz, pszPrefix, lenPrefix) == 0;

}



template < typename TYPE_CHAR >
inline bool string_ends(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszSuffix, strsize lenSuffix)
{

   auto offset = len - lenSuffix;

   if (offset < 0)
   {

      return false;

   }

   auto pszCompare = psz + offset;

   return string_count_compare(pszCompare, pszSuffix, lenSuffix) == 0;

}


template < typename TYPE_CHAR >
inline bool string_begins_ci(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszPrefix, strsize lenPrefix)
{

   if (lenPrefix > len)
   {

      return false;

   }

   return string_count_compare_ci(psz, pszPrefix, lenPrefix) == 0;

}


template < typename TYPE_CHAR >
inline bool string_ends_ci(const TYPE_CHAR * psz, strsize len, const TYPE_CHAR * pszSuffix, strsize lenSuffix)
{

   auto offset = len - lenSuffix;

   if (offset < 0)
   {

      return false;

   }

   auto pszCompare = psz + offset;

   return string_count_compare_ci(pszCompare, pszSuffix, lenSuffix) == 0;

}


template < typename CHAR_TYPE >
bool string_eat_before(string_base < CHAR_TYPE > & strBefore, const string_base < CHAR_TYPE > & strSeparator, string_base < CHAR_TYPE > & str, bool bEatEverythingIfNotFound)
{

   ASSERT(&str != &strBefore);

   if (&str == &strBefore)
   {

      return false;

   }

   index iFind = str.find(strSeparator);

   if (iFind < 0)
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = str;

         str.Empty();

      }

      return false;

   }

   strBefore = str.Left(iFind);

   str = str.Mid(iFind + strSeparator.length());

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

   index iFind = str.find(strSeparator);

   if (iFind < 0)
   {

      if (bEatEverythingIfNotFound)
      {

         strBefore = str;

         str = strSeparator;

      }

      return false;

   }

   strBefore = str.Left(iFind);

   str = str.Mid(iFind);

   return true;

}





inline i32 unicode_len(const ansichar * pszUtf8)
{

   ::i32 len;

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


