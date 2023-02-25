#include "framework.h"
//#include "hex.h"
//#include "string.h"
#include "acme/exception/parsing.h"


i32 alphadigit_weight(char ch)
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


   i64 to_i64(const ::scoped_string & scopedstr)
   {

      i64 r = 0, num = 0;
      if (scopedstr.is_empty())
      {

         return -1;

      }
      auto pcsz = scopedstr.begin();
      for(i64 i = strlen(pcsz)-1; i >= 0; i--)
      {

         i64 d = alphadigit_weight(pcsz[i]);

         if(d == -1)
            return -1;
         num += d << r;
         r += 4;
      }
      return num;
   }

   u32 to_u32(const ::string & str)
   {
      u32 r = 0;
      for (i32 i = 0; i < str.length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }
      return r;
   }

   u64 to_u64(const ::string & str)
   {
      u64 r = 0;
      for(i32 i = 0; i < str.length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }

      return r;

   }


} // namespace str










namespace hex
{


   u16 parse_u16_exc(::const_ansi_range & range)
   {
      
      string strUni;
      
      const char * pszNext = range.m_begin;

      for (index i = 0; i < 4; i++)
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

      return ::hex::to_u32(strUni);

   }

}



