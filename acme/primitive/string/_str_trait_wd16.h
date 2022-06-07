#pragma once


#define const_wd16char_trigger const wd16char *



   inline  constexpr strsize     char_length_to_byte_length(const_wd16char_trigger, strsize nCharLength);
   inline  constexpr strsize     byte_length_to_char_length(const_wd16char_trigger, memsize nByteLength);

   inline  wd16char * char_next(const wd16char * point_i32) noexcept;
   inline  bool               isalpha(wd16char ch) noexcept;
   inline  bool               isdigit(wd16char ch) noexcept;
   inline  bool               isspace(wd16char ch) noexcept;
   inline  wd16char           tolower(wd16char ch) noexcept;
   inline  wd16char           toupper(wd16char ch) noexcept;
   inline  i32                string_compare(const wd16char * pszA, const wd16char * pszB) noexcept;
   inline  i32                string_compare_ci(const wd16char * pszA, const wd16char * pszB) noexcept;
   inline  i32                string_n_compare(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept;
   inline  i32                string_n_compare_ci(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept;
   inline  i32                string_collate(const wd16char * pszA, const wd16char * pszB) noexcept;
   inline  i32                string_collate_ci(const wd16char * pszA, const wd16char * pszB) noexcept;
   inline  i32                string_n_collate(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept;
   inline  i32                string_n_collate_ci(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept;
   inline  const wd16char * string_find_string(const wd16char * pszBlock, const wd16char * pszMatch) noexcept;
   inline  const wd16char * string_find_string_ci(const wd16char * pszBlock, const wd16char * pszMatch) noexcept;
   inline  const wd16char * string_find_char(const wd16char * pszBlock, wd16char chMatch) noexcept;
   inline  const wd16char * string_find_char_reverse(const wd16char * psz, wd16char ch, strsize iStart) noexcept;
   inline  const wd16char * string_find_string_reverse(const wd16char * psz, const wd16char * pszFind, strsize iStart) noexcept;
   inline  const wd16char * string_scan_set(const wd16char * pszBlock, const wd16char * pszMatch) noexcept;
   inline  strsize            string_span_including(const wd16char * pszBlock, const wd16char * pszSet) noexcept;
   inline  strsize            string_span_excluding(const wd16char * pszBlock, const wd16char * pszSet) noexcept;
   inline  wd16char * string_uppercase(wd16char * psz) noexcept;
   inline  wd16char * string_lowercase(wd16char * psz) noexcept;
   inline  wd16char * string_uppercase(wd16char * psz, strsize size) noexcept;
   inline  wd16char * string_lowercase(wd16char * psz, strsize size) noexcept;
   inline  wd16char * string_reverse(wd16char * psz) noexcept;
   inline  strsize            string_get_length(const wd16char * psz) noexcept;
   inline  strsize            get_char_length(const wd16char * psz) noexcept { return string_get_length(psz); }
   inline  strsize            get_formatted_length(const wd16char * pszFormat, va_list args) noexcept;
   inline  strsize            string_format(wd16char * pszBuffer, const wd16char * pszFormat, va_list args) noexcept;
   inline  strsize            string_format(wd16char * pszBuffer, strsize nlength, const wd16char * pszFormat, va_list args) noexcept;
   inline  void               flood_characters(wd16char * pwsz, wd16char wch, strsize len) noexcept;

   inline  u32                format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, wd16char * pszBuffer, u32 nSize, va_list * pArguments) noexcept;
   inline  strsize            string_safe_length(const wd16char * psz) noexcept;
   //CLASS_DECL_ACME u32        xxxget_environment_variable(const wd16char * pszVar, wd16char * pszBuffer, u32 dwSize);

   inline  void               copy_string(wd16char * pszDst, const wd16char * pszSrc);
   inline  void               copy_chars(wd16char * pchDest, const wd16char * pchSrc, strsize nChars) noexcept;
   inline  void               copy_chars(wd16char * pchDest, size_t nDestLen, const wd16char * pchSrc, strsize nChars) noexcept;
   inline  void               copy_chars_overlapped(wd16char * pchDest, const wd16char * pchSrc, strsize nChars) noexcept;



//} // namespace str



