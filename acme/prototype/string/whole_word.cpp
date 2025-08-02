#include "framework.h"
#include "string.h"
//#include "acme/prototype/collection/string_array.h"


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


//namespace str
//{
//

   bool whole_word_contains(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrFind)
   {

      ::collection::index iFind = 0;

      while ((iFind = scopedstr(iFind).case_insensitive_find_index(scopedstrFind)) >= 0)
      {

         bool bLowerBound1 = iFind == 0;
         bool bLowerBound = bLowerBound1 || !ansi_char_isalpha(scopedstr[iFind - 1]);
         character_count iUpperBound = iFind + scopedstrFind.length();
         bool bUpperBound1 = iUpperBound == scopedstr.length();
         bool bUpperBound = bUpperBound1 || !ansi_char_isalpha(scopedstr[iUpperBound]);

         if (bLowerBound && bUpperBound)
         {

            return true;

         }

         iFind++;

      }

      return false;

   }


   bool whole_word_find(string_array & stra, const ::scoped_string & scopedstr)
   {

      for (auto & strFind : stra)
      {

         if (whole_word_contains(scopedstr, strFind))
         {

            return true;

         }

      }

      return false;

   }

   /// [Idee:ChrifRachid@liveedutv] erase http:// and https:// from resident speech

   void whole_word_erase(string & str, const ::scoped_string & scopedstrFind)
   {

      ::collection::index iFind = 0;

      while ((iFind = str(iFind).case_insensitive_find_index(scopedstrFind)) >= 0)
      {

         if (iFind == 0 || !ansi_char_isalpha(str[iFind - 1]))
         {

            str = str(0, iFind) + str.substr(iFind + scopedstrFind.length());

         }
         else
         {

            iFind++;

         }

      }

   }
//
//
//} // namespace str



