#include "framework.h"

#include "acme/_operating_system.h"


int debug_string_iterator()
{

   string str = "This is a phrase this is a link http://test.com/test_file?test_parameter=test_value";

   int iLinkLen = 0;

   int iColon = 0;

   for(auto character : str)
   {

      if (character_isalpha(character)
          || character == L'.'
          || character == L'/'
          || character == L'?'
          || character == L'&'
          || (character == L':' && iColon++ == 0))
      {

         iLinkLen++;

      }
      else
      {

         break;

      }

   }

   return iLinkLen;

}




//string string_format(const ::scoped_string & scopedstrFormat, ...)
//{
//
//   string str;
//
//   va_list argList;
//
//   va_start(argList, pszFormat);
//
//   str.formatf_arguments(scopedstrFormat, argList);
//
//   va_end(argList);
//
//   return ::transfer(str);
//
//}
//

CLASS_DECL_ACME inline character_count safe_strlen(void * p, character_count n)
{

   if (p == nullptr)
   {

      return 0;

   }

   auto psz = (const_char_pointer )p;

   character_count i = 0;

   for (; i < n; i++)
   {

      if (psz[i] == '\0')
      {

         break;

      }

   }

   return i;

}


CLASS_DECL_ACME string type_name(const ::std::type_info& typeinfo);


//CLASS_DECL_ACME string demangle_name(const_char_pointer pszMangledName);

//CLASS_DECL_ACME void copy(::string & str, const subparticle & subparticle)
//{
//
//   str = demangle_name(typeid((::subparticle &)subparticle).name());
//
//}






CLASS_DECL_ACME void erase_sharp_comment(::string& str)
{

   auto sharp = str.find_first('#');

   if (sharp)
   {

      str.truncate(sharp);

   }

}


CLASS_DECL_ACME void erase_sharp_comment(::string_array_base& stra)
{

   for (auto& str : stra)
   {

      erase_sharp_comment(str);

   }

}

void assert_atom_with_e_range_string_literal(const ::atom& atom)
{
   
   if (!(atom.m_str.m_erange & e_range_string_literal))
   {

      throw "assert_scoped_string_with_e_range_string failed";

   }


}


//void assert_scoped_string_ok2(const ::scoped_string& scopedstr)
//{
//
/////   if (scopedstr.m_erange & e_range_scoped_ownership)
////   {
//
//      if (!scopedstr.m_pbasedata)
//      {
//
//         throw "assert_scoped_string_with_e_range_string failed";
//
//      }
//
//   ///}
//
//}
//
//
//void assert_scoped_string_ok(const ::scoped_string& scopedstr)
//{
//
//   // if (scopedstr.m_erange != e_range_string)
//   // {
//   //
//   //    //throw "assert_scoped_string_with_e_range_string failed";
//   //
//   // }
//   assert_scoped_string_ok2(scopedstr);
//
//}

CLASS_DECL_ACME void log_const_ansi_range_literal(int n)
{

   printf_line("ansi=%d", n);

}

CLASS_DECL_ACME void string_short_test()
{


#if 0

   const_char_pointer pszStdSchema = strdup("_std");

   ::atom idSchema;

   idSchema = pszStdSchema;

   assert_atom_with_e_range_string_literal("a"_ansi);

   assert_scoped_string_with_e_range_string(idSchema);

   free((void*)pszStdSchema);


   ::string strTest;


   strTest = "abcdefghijklmnopqrstuvwxyz\r\n";

   strTest = strTest.left(strTest.length() - 2);

   print_line(strTest);

#endif

}
