#pragma once





inline i32 __uni_index(const char *& input, strsize * psrclen)
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

   *psrclen--;

   return i;

}



