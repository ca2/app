#include "framework.h"


// CLASS_DECL_ACME const char g_ptrailingBytesForUTF8[256] =
// {
//    (const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
// };


namespace str
{


   bool x_contains(string str, string strFind)
   {

      strsize iFind = 0;

      while ((iFind = str.find_ci(strFind, iFind)) >= 0)
      {

         bool bLowerBound1 = iFind == 0;
         bool bLowerBound = bLowerBound1 || !ansi_char_is_alphabetic(str[iFind - 1]);
         strsize iUpperBound = iFind + strFind.get_length();
         bool bUpperBound1 = iUpperBound == str.get_length();
         bool bUpperBound = bUpperBound1 || !ansi_char_is_alphabetic(str[iUpperBound]);

         if (bLowerBound && bUpperBound)
         {

            return true;

         }

         iFind++;

      }

      return false;

   }

   bool x_find(string_array & stra, string str)
   {

      for (auto & strFind : stra)
      {

         if (x_contains(str, strFind))
         {

            return true;

         }

      }

      return false;

   }

   /// [Idee:ChrifRachid@liveedutv] remove http:// and https:// from resident speech

   void x_left_remove(string & str, string strFind)
   {

      strsize iFind = 0;

      while ((iFind = str.find_ci(strFind, iFind)) >= 0)
      {

         if (iFind == 0 || !ansi_char_is_alphabetic(str[iFind - 1]))
         {

            str = str.Left(iFind) + str.Mid(iFind + strFind.get_length());

         }
         else
         {

            iFind++;

         }

      }

   }


} // namespace str



