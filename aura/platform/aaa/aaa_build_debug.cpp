#include "framework.h"


char g_strDebugPuts[1024];
int g_iDebugPuts;
// GCC 4.8 doesn't know that puts() is nothrow; we must give it a hint.
void debug_puts(const ::string &psz) noexcept
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


void teste_aura_cmp();


void aura_auto_debug_teste()
{

   printf("\n\nvoid aura_auto_debug_teste()\n\n");
   {

      wd16string wstr1;

      wd16string wstr2;

      wd16string wstr3;

      {

         string str1("aaaa");

         string str2("aaaabbbbccccdddd");

         string str3("aaaabbbbccccddddaaaabbbbccccddddaaaabbbbccccddddaaaabbbbccccdddd");

         printf("str1 %s", str1.c_str());

         printf("str2 %s", str2.c_str());

         printf("str3 %s", str3.c_str());

         wstr1 = str1;

         wstr2 = str2;

         wstr3 = str3;

         output_debug_string("strstr");

      }

      /*

      ::OutputDebugString(wstr1);

      ::OutputDebugString(wstr2);

      ::OutputDebugString(wstr3);

      ::OutputDebugString(L"wstrwstr");

      */

   }

   //string str()

//   teste_aura_cmp();

//   if(!m_psystem->m_pacmefile->exists("/ca2/debug_test"))
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
//         debug_puts("one"); // compiler knows this doesn't throw ::exception(memory_new
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
//   ::output_debug_string(g_strDebugPuts);

}



void teste_aura_cmp()
{
   //auto a = MAKE(PARAMETER);

   //return std::SPACESHIP(a,a);
}
