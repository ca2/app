#include "framework.h"



char g_strDebugPuts[1024];
int g_iDebugPuts;
// GCC 4.8 doesn't know that puts() is nothrow; we must give it a hint.
void debug_puts(const_char_pointer psz) noexcept
{
   while(*psz)
   {
      g_strDebugPuts[g_iDebugPuts] = *psz;
      psz++;
      g_iDebugPuts++;
   }
   g_strDebugPuts[g_iDebugPuts] = '\n';
   g_iDebugPuts++;
   g_strDebugPuts[g_iDebugPuts] = '\0';
}

//void foo()
//{
//   throw ::exception(::exception());
//}


void teste_acme_cmp();


void acme_auto_debug_teste()
{

   output_debug_string("\n\nvoid acme_auto_debug_teste()\n\n");

   {

      wd16_string wstr1;

      wd16_string wstr2;

      wd16_string wstr3;

      {

         string str1("aaaa");

         string str2("aaaabbbbccccdddd");

         string str3("aaaabbbbccccddddaaaabbbbccccddddaaaabbbbccccddddaaaabbbbccccdddd");

         output_debug_string_formatf("str1 %s", str1.c_str());

         output_debug_string_formatf("str2 %s", str2.c_str());

         output_debug_string_formatf("str3 %s", str3.c_str());

         wstr1 = str1;

         wstr2 = str2;

         wstr3 = str3;

         informationf("strstr");

      }

      /*

      ::OutputDebugString(wstr1);

      ::OutputDebugString(wstr2);

      ::OutputDebugString(wstr3);

      ::OutputDebugString(L"wstrwstr");

      */

   }

   //string str()

//   teste_acme_cmp();

//   if(!file_system()->exists("/ca2/debug_test"))
//   {
//
//      return;
//
//   }
//
//   try
//   {
//      if(true)
//      {
//         AUTO(debug_puts("two"));
//         debug_puts("one"); // compiler knows this doesn't throw ::exception(
//      }
//      if(true)
//      {
//         AUTO(debug_puts("three"));
////         foo(); // might throw ::exception( an exception
//      }
//   }
//   catch(...)
//   {
//   }
//   ::information(g_strDebugPuts);

}



void teste_acme_cmp()
{
   //auto a = MAKE(PARAMETER);

   //return std::SPACESHIP(a,a);
}
