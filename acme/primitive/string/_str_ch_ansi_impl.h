#pragma once



inline i32 str::ch::parse_unicode(const ansichar *& pszUtf8)
{

   if (*pszUtf8 == '\0')
   {

      return 0;

   }

   i32 ch = 0;

   byte c;

   char extraBytesToRead = utf8_e(*pszUtf8);

   switch (extraBytesToRead)
   {
   case 5:
      ch += c = *pszUtf8++; ch <<= 6;
      if (c == '\0') { return -1; }
   case 4:
      ch += c = *pszUtf8++; ch <<= 6;
      if (c == '\0') { return -1; }
   case 3:
      ch += c = *pszUtf8++; ch <<= 6;
      if (c == '\0') { return -1; }
   case 2:
      ch += c = *pszUtf8++; ch <<= 6;
      if (c == '\0') { return -1; }
   case 1:
      ch += c = *pszUtf8++; ch <<= 6;
      if (c == '\0') { return -1; }
   case 0:
      ch += c = *pszUtf8++;
      if (c == '\0') { return -1; }
   }

   ch -= utf8_o(extraBytesToRead);

   return ch;

}


inline i32 str::ch::uni_index_len(const ansichar * pszUtf8, ::i32 & len)
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


inline i32 str::ch::uni_len(const ansichar * pszUtf8)
{

   ::i32 len;

   if (uni_index_len(pszUtf8, len) < 0)
   {

      return -1;

   }

   return len;

}


inline i32 str::ch::uni_index(const ansichar * pszUtf8)
{

   ::i32 len;

   return uni_index_len(pszUtf8, len);

}


inline ::i32 str::ch::to_lower_case(::i32 i)
{
   if (!str::ch::is_legal_uni_index(i))
      return -1;
   ::u32 c1 = CHAR_PROP(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return (wd32char)i;
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return (wd32char)(i + 1);
   return wd32char(i - (c1 >> 16));
}


inline ::i32 str::ch::to_upper_case(::i32 i)
{
   if (!is_legal_uni_index(i))
      return -1;
   u32 c1 = CHAR_PROP(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return wd32char(i);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return wd32char(i - 1);
   return wd32char(i - (c1 >> 16));
}

inline ::i32 str::ch::to_title_case(::i32 i)
{
   if (!is_legal_uni_index(i))
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


inline i32 str::ch::to_numeric_value(i32 i, float * f)
{
   if (!is_legal_uni_index(i))
      return false;
   u32 c1 = CHAR_PROP(i);
   if (!NUMBER(c1)) return false;
   *f = CHAR_PROP2(i);
   return true;
}


inline bool str::ch::is_lower_case(::i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Ll;
}


inline bool str::ch::is_upper_case(::i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Lu;
}


inline bool str::ch::is_title_case(::i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Lt;
}


inline bool str::ch::is_letter(::i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   u32 c1 = CHAR_CATEGORY(CHAR_PROP(i));
   return ((((1 << CHAR_CATEGORY_Lu) |
      (1 << CHAR_CATEGORY_Ll) |
      (1 << CHAR_CATEGORY_Lt) |
      (1 << CHAR_CATEGORY_Lm) |
      (1 << CHAR_CATEGORY_Lo)
      ) >> c1) & 1) != 0;
}


inline bool str::ch::is_letter_or_digit(::i32 i)
{
   if (!is_legal_uni_index(i))
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


inline bool str::ch::is_digit(i32 i)
{

   if (!is_legal_uni_index(i))
      return false;

   return CHAR_CATEGORY(CHAR_PROP(i)) == CHAR_CATEGORY_Nd;

}


inline bool str::ch::is_assigned(i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return CHAR_CATEGORY(CHAR_PROP(i)) != CHAR_CATEGORY_Cn;
}


inline bool str::ch::is_space_char(i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return  ((((1 << CHAR_CATEGORY_Zs) |
      (1 << CHAR_CATEGORY_Zl) |
      (1 << CHAR_CATEGORY_Zp)
      ) >> CHAR_CATEGORY(CHAR_PROP(i))) & 1) != 0;
}


inline bool str::ch::is_whitespace(i32 i)
{
   if (!is_legal_uni_index(i))
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


inline bool str::ch::is_number(i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return NUMBER(CHAR_PROP(i)) != 0;
}


inline ECharCategory str::ch::get_category(i32 i)
{
   if (!is_legal_uni_index(i))
      return CHAR_CATEGORY_LAST;
   return ECharCategory(CHAR_CATEGORY(CHAR_PROP(i)));
}


inline i32 str::ch::get_combining_class(i32 i)
{
   if (!is_legal_uni_index(i))
      return false;
   return COMBINING_CLASS(CHAR_PROP(i));
}


inline bool str::ch::is_mirrored(i32 i)
{

   if (!is_legal_uni_index(i))
      return false;

   return MIRRORED(CHAR_PROP(i)) != 0;

}


inline i32 str::ch::size_of_tables()
{
   return sizeof(arr_idxCharInfo) + sizeof(arr_CharInfo) + sizeof(arr_idxCharInfo2) + sizeof(arr_CharInfo2);
}
