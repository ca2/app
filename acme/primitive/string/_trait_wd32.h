#pragma once


#define const_wd32char_trigger const wd32char *


namespace str
{


   inline  constexpr auto     char_length_to_byte_length(const_wd32char_trigger, strsize nCharLength);
   inline  constexpr auto     byte_length_to_char_length(const_wd32char_trigger, memsize nByteLength);

   inline  wd32char * char_next(const wd32char * point_i32) noexcept;
   inline  bool               isalpha(wd32char ch) noexcept;
   inline  bool               isdigit(wd32char ch) noexcept;
   inline  bool               isspace(wd32char ch) noexcept;
   inline  wd32char           tolower(wd32char ch) noexcept;
   inline  wd32char           toupper(wd32char ch) noexcept;
   inline  i32                string_compare(const wd32char * pszA, const wd32char * pszB) noexcept;
   inline  i32                string_compare_ci(const wd32char * pszA, const wd32char * pszB) noexcept;
   inline  i32                string_n_compare(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept;
   inline  i32                string_n_compare_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept;
   inline  i32                string_collate(const wd32char * pszA, const wd32char * pszB) noexcept;
   inline  i32                string_collate_ci(const wd32char * pszA, const wd32char * pszB) noexcept;
   inline  const wd32char * string_find_string(const wd32char * pszBlock, const wd32char * pszMatch) noexcept;
   inline  const wd32char * string_find_string_ci(const wd32char * pszBlock, const wd32char * pszMatch) noexcept;
   inline  const wd32char * string_find_char(const wd32char * pszBlock, wd32char chMatch) noexcept;
   inline  const wd32char * string_find_char_reverse(const wd32char * psz, wd32char ch, strsize iStart) noexcept;
   inline  const wd32char * string_find_string_reverse(const wd32char * psz, const wd32char * pszFind, strsize iStart) noexcept;
   inline  const wd32char * string_scan_set(const wd32char * pszBlock, const wd32char * pszMatch) noexcept;
   inline  strsize            string_span_including(const wd32char * pszBlock, const wd32char * pszSet) noexcept;
   inline  strsize            string_span_excluding(const wd32char * pszBlock, const wd32char * pszSet) noexcept;
   inline  wd32char * string_uppercase(wd32char * psz) noexcept;
   inline  wd32char * string_lowercase(wd32char * psz) noexcept;
   inline  wd32char * string_uppercase(wd32char * psz, strsize size) noexcept;
   inline  wd32char * string_lowercase(wd32char * psz, strsize size) noexcept;
   inline  wd32char * string_reverse(wd32char * psz) noexcept;
   inline  strsize            string_get_length(const wd32char * psz) noexcept;
   inline  strsize            get_char_length(const wd32char * psz) noexcept;
   inline  strsize            get_formatted_length(const wd32char * pszFormat, va_list args) noexcept;
   inline  strsize            string_format(wd32char * pszBuffer, const wd32char * pszFormat, va_list args) noexcept;
   inline  strsize            string_format(wd32char * pszBuffer, strsize nlength, const wd32char * pszFormat, va_list args) noexcept;
   inline  void               flood_characters(wd32char * pwsz, wd32char wch, strsize len) noexcept;

   inline  u32                format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, wd32char * pszBuffer, u32 nSize, va_list * pArguments) noexcept;
   inline  strsize            string_safe_length(const wd32char * psz) noexcept;
   //CLASS_DECL_ACME u32        xxxget_environment_variable(const wd32char * pszVar, wd32char * pszBuffer, u32 dwSize);

   inline  void               copy_string(wd32char * pszDst, const wd32char * pszSrc);
   inline  void               copy_chars(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept;
   inline  void               copy_chars(wd32char * pchDest, size_t nDestLen, const wd32char * pchSrc, strsize nChars) noexcept;
   inline  void               copy_chars_overlapped(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept;



} // namespace str



