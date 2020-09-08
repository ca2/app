#pragma once

#if WCHAR_T_SIZE == 16

CLASS_DECL_APEX wstring wd32_to_wd16_str(const wd32char * pcwsz, strsize input_size = -1);

#endif

CLASS_DECL_APEX string wd16_to_ansi_str(const wd16char * pwsz, strsize srclen = -1);

CLASS_DECL_APEX string wd32_to_ansi_str(const wd32char * pwsz, strsize srclen = -1);


inline const ansichar * uni_inc(const ansichar * psz) { return utf8_inc(psz); }
inline const wd16char * uni_inc(const wd16char * pwsz) { return utf16_inc(pwsz); }
inline const wd32char * uni_inc(const wd32char * pwsz) { return utf32_inc(pwsz); }



inline i32 __uni_index(const ansichar *& input, strsize * psrclen)
{

   if (*input == 0)
   {

      return 0;

   }

   if (*psrclen < 1)
   {

      return -1;

   }

   ::wd32char u32;

   strsize used_len = ansi_to_wd32_char(&u32, input, *psrclen);

   if (used_len < 0)
   {

      return -1;

   }

   input += used_len;

   *psrclen -= used_len;

   return u32;

}


inline i32 __uni_index(const wd16char *& input, strsize * psrclen)
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

   ::wd32char u32;

   strsize used_len = wd16_to_wd32_char(&u32, input, *psrclen);

   input += used_len;

   *psrclen -= used_len;

   return i;

}


inline i32 __uni_index(const wd32char *& input, strsize * psrclen)
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

   return i;

}



