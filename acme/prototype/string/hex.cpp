#include "framework.h"
//#include "hex.h"
//#include "string.h"
#include "acme/exception/parsing.h"


::i32 alphadigit_weight(::i8 ch)
{

   if (ch >= '0' && ch <= '9')
   {

      return ch - '0';

   }
   else if (ch >= 'a' && ch <= 'z')
   {

      return ch - 'a' + 10;

   }
   else if (ch >= 'A' && ch <= 'Z')
   {

      return ch - 'Z' + 10;

   }
   else
   {

      return -1;

   }


}

namespace hex
{


   ::i64 to_long_long(const ::scoped_string & scopedstr)
   {

      ::i64 r = 0, num = 0;
      if (scopedstr.is_empty())
      {

         return -1;

      }
      auto pcsz = scopedstr.begin();
      for(::i64 i = ansi_len(pcsz)-1; i >= 0; i--)
      {

         ::i64 d = alphadigit_weight(pcsz[i]);

         if(d == -1)
            return -1;
         num += d << r;
         r += 4;
      }
      return num;
   }

   ::u32 to_unsigned_int(const ::scoped_string & scopedstr)
   {
      ::u32 r = 0;
      for (::i32 i = 0; i < scopedstr.length(); i++)
      {
         r = r * 16 + scopedstr[i] - 48 - ((scopedstr[i] >= 'A') ? 7 : 0) - ((scopedstr[i] >= 'a') ? 32 : 0);
      }
      return r;
   }

   ::u64 to_unsigned_long_long(const ::scoped_string & scopedstr)
   {
      ::u64 r = 0;
      for(::i32 i = 0; i < scopedstr.length(); i++)
      {
         r = r * 16 + scopedstr[i] - 48 - ((scopedstr[i] >= 'A') ? 7 : 0) - ((scopedstr[i] >= 'a') ? 32 : 0);
      }

      return r;

   }


} // namespace str










namespace hex
{


   ::u16 parse_u16_exc(::const_ansi_range & range)
   {
      
      string strUni;
      
      const_char_pointer pszNext = range.m_begin;

      for (::collection::index i = 0; i < 4; i++)
      {
         
         range.m_begin = pszNext;

         pszNext = unicode_next(range.m_begin);

         if (range.is_empty())
         {
            
            throw ::parsing_exception("hexadecimal digit expected, premature end");
            
            return -1;

         }

         if ((pszNext - range.m_begin == 1) &&
            ((*range.m_begin >= '0' && *range.m_begin <= '9') 
               || (*range.m_begin >= 'A' && *range.m_begin <= 'F')
               || (*range.m_begin >= 'a' && *range.m_begin <= 'f')))
         {

            strUni += *range.m_begin;

         }
         else
         {

            throw ::parsing_exception("hexadecimal digit expect expected here");

            return -1;

         }

      }

      return ::hex::to_unsigned_int(strUni);

   }

}



