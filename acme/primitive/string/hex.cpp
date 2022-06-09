#include "framework.h"


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


   i64 to_i64(const char * pcsz)
   {

      i64 r = 0, num = 0;
      if (pcsz == nullptr)
      {

         return -1;

      }
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
      for (i32 i = 0; i < str.get_length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }
      return r;
   }

   u64 to_u64(const ::string & str)
   {
      u64 r = 0;
      for(i32 i = 0; i < str.get_length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }

      return r;

   }


} // namespace str





bool ishexdigit(char ch)
{
   if(ch >= '0' && ch <= '9')
      return true;
   if(ch >= 'a' && ch <= 'f')
      return true;
   if(ch >= 'A' && ch <= 'F')
      return true;
   return false;
}





namespace hex
{


   u16 parse_u16_exc(const char *& psz, const char * pszEnd)
   {
      string strUni;
      const char * pszNext = psz;
      for (index i = 0; i < 4; i++)
      {
         psz = pszNext;
         pszNext = ::str().next(psz);
         if (pszNext > pszEnd)
         {
            throw ::exception(error_parsing, "hexadecimal digit expected, premature end");
            return -1;
         }
         if ((pszNext - psz == 1) && ((*psz >= '0' && *psz <= '9') || (*psz >= 'A' && *psz <= 'F') || (*psz >= 'a' && *psz <= 'f')))
         {
            strUni += *psz;
         }
         else
         {
            throw ::exception(error_parsing, "hexadecimal digit expect expected here");
            return -1;
         }
      }
      psz = pszNext;
      return ::hex::to_u32(strUni);

   }

}
