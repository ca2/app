#pragma once


inline i32 str::ch::parse_unicode(const wd16char *& input)
{

   if (input[0] == 0)
   {

      return 0;

   }

   if (utf16_is_2nd_surrogate(input[0]))
   {

      return -1;

   }
   else if (utf16_is_1st_surrogate(input[0]))
   {

      if (utf16_is_2nd_surrogate(input[1]))
      {

         auto iUnicode = utf16_surrogate_to_utf32(input[0], input[1]);

         input += 2;

         return iUnicode;

      }
      else
      {

         return -1;

      }

   }
   else
   {

      auto iUnicode = input[0];

      input++;

      return iUnicode;

   }

}


inline i32 str::ch::uni_index_len(const wd16char * input, i32 & len)
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


//   } // namespace ch
