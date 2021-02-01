#pragma once


#define const_ansichar_trigger const ansichar *


namespace str
{


   inline  constexpr auto     char_length_to_byte_length(const_ansichar_trigger, strsize nCharLength);
   inline  constexpr auto     byte_length_to_char_length(const_ansichar_trigger, memsize nByteLength);

   inline  ansichar *         char_next(const ansichar * point_i32) noexcept;
   inline  bool               isalpha(ansichar ch) noexcept;
   inline  bool               isdigit(ansichar ch) noexcept;
   inline  bool               isspace(ansichar ch) noexcept;
   inline  ansichar           tolower(ansichar ch) noexcept;
   inline  ansichar           toupper(ansichar ch) noexcept;
   inline  i32                string_compare(const ansichar * pszA, const ansichar * pszB) noexcept;
   inline  i32                string_compare_ci(const ansichar * pszA, const ansichar * pszB) noexcept;
   inline  i32                string_n_compare(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept;
   inline  i32                string_n_compare_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept;
   inline  i32                string_collate(const ansichar * pszA, const ansichar * pszB) noexcept;
   inline  i32                string_collate_ci(const ansichar * pszA, const ansichar * pszB) noexcept;
   inline  const ansichar * string_find_string(const ansichar * pszBlock, const ansichar * pszMatch) noexcept;
   inline  const ansichar * string_find_string_ci(const ansichar * pszBlock, const ansichar * pszMatch) noexcept;
   inline  const ansichar * string_find_char(const ansichar * pszBlock, ansichar chMatch) noexcept;
   inline  const ansichar * string_find_char_reverse(const ansichar * psz, ansichar ch, strsize iStart) noexcept;
   inline  const ansichar * string_find_string_reverse(const ansichar * psz, const ansichar * pszFind, strsize iStart) noexcept;
   inline  const ansichar * string_scan_set(const ansichar * pszBlock, const ansichar * pszMatch) noexcept;
   inline  strsize            string_span_including(const ansichar * pszBlock, const ansichar * pszSet) noexcept;
   inline  strsize            string_span_excluding(const ansichar * pszBlock, const ansichar * pszSet) noexcept;
   inline  ansichar * string_uppercase(ansichar * psz) noexcept;
   inline  ansichar * string_lowercase(ansichar * psz) noexcept;
   inline  ansichar * string_uppercase(ansichar * psz, strsize size) noexcept;
   inline  ansichar * string_lowercase(ansichar * psz, strsize size) noexcept;
   inline  ansichar * string_reverse(ansichar * psz) noexcept;
   inline  strsize            string_get_length(const ansichar * psz) noexcept;
   inline  strsize            get_char_length(const ansichar * psz) noexcept { return string_get_length(psz); }
   inline  strsize            get_formatted_length(const ansichar * pszFormat, va_list args) noexcept;
   inline  strsize            string_format(ansichar * pszBuffer, const ansichar * pszFormat, va_list args) noexcept;
   inline  strsize            string_format(ansichar * pszBuffer, strsize nlength, const ansichar * pszFormat, va_list args) noexcept;
   inline  void               flood_characters(ansichar * pwsz, ansichar wch, strsize len) noexcept;

   inline  u32                format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, ansichar * pszBuffer, u32 nSize, va_list * pArguments) noexcept;
   inline  strsize            string_safe_length(const ansichar * psz) noexcept;
   CLASS_DECL_ACME u32        get_environment_variable(const ansichar * pszVar, ansichar * pszBuffer, u32 dwSize);

   inline  void               copy_string(ansichar * pszDst, const ansichar * pszSrc);
   inline  void               copy_chars(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept;
   inline  void               copy_chars(ansichar * pchDest, size_t nDestLen, const ansichar * pchSrc, strsize nChars) noexcept;
   inline  void               copy_chars_overlapped(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept;

} // namespace str



