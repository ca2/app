#include "framework.h"
////#include "acme/exception/exception.h"


::wd32_character* wd16_to_wd32_dup(const ::wd16_character* input, strsize input_size)
{

   strsize s = wd16_to_wd32_len(input, input_size);

   ::wd32_character* v = (::wd32_character*)memory_allocate(sizeof(::wd32_character) * (s + 1));

   wd16_to_wd32(v, input, s);

   v[s] = 0;

   return v;

}




strsize wd32_to_wd16_len(const ::wd32_character* codepoints, strsize input_size)
{

   strsize len = 0;

   while (input_size != 0)
   {

      u32 cp = *codepoints++;

      input_size--;

      if (cp == 0)
         break;

      if (cp < 0x10000)
      {

         ++len;

      }
      else if (cp <= 0x10FFFF)
      {

         len += 2;

      }
      else
      {

         // invalid code_point, do something !
         throw ::exception(error_invalid_character, "wd32_to_wd16_len :: invalid code_point, do something ! ");

         //++len;

      }

   }

   return len;

}


strsize wd32_to_wd16(::wd16_character* psz16, const ::wd32_character* codepoints, strsize input_size)
{

   strsize len = 0;

   while (input_size != 0)
   {

      u32 cp = *codepoints++;

      if (cp == 0)
      {

         break;

      }

      input_size--;

      if (cp < 0x10000)
      {

         *psz16++ = static_cast<::wd16_character>(cp);

      }
      else if (cp <= 0x10FFFF)
      {

         cp -= 0x10000;

         *psz16++ = static_cast<::wd16_character>((cp >> 10) + 0xD800);

         *psz16++ = static_cast<::wd16_character>((cp & 0x3FF) + 0xDC00);

      }
      else
      {

         *psz16++ = static_cast<::wd16_character>(0xFFFD);

      }

   }

   return len;

}


//wstring wd32_to_wd16(const ::wd32_character* input, strsize input_size)
//{
//
//   strsize s = wd32_to_wd16_len(input, input_size);
//
//   wstring wstr;
//
//   ::wd16_character* point = wstr.get_buffer(s);
//
//   wd32_to_wd16(point, input, s);
//
//   point_i32[s] = 0;
//
//   return wstr;
//
//}








