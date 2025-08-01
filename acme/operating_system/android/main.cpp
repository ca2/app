#include "framework.h"


CLASS_DECL_ACME int ca2_main();

void CLASS_DECL_ACME __cdecl _ca2_purecall()
{
   throw ::exception(::exception());
}


#ifdef WINDOWS

void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);

#endif



//int CLASS_DECL_ACME __android_main(::platform::system * psystem, int argc, char * argv[])
//{
//
//   if(!defer_au_init())
//      return -1;
//
//   int nReturnCode = 0;
//
//
//   ::android::main_init_data * pinitmaindata  = __allocate ::android::main_init_data();
//
//
//   pinitmaindata->m_hInstance             = nullptr;
//   pinitmaindata->m_hPrevInstance         = nullptr;
//   if(argc > 0)
//   {
//      pinitmaindata->m_strCommandLine     = argv[0];
//   }
//   bool bColon = false;
//   for(int i = 1; i < argc; i++)
//   {
//      if(bColon || (bColon = (strcmp(argv[i], ":") == 0)))
//      {
//         pinitmaindata->m_strCommandLine     += " ";
//         pinitmaindata->m_strCommandLine     += argv[i];
//
//      }
//      else
//      {
//         pinitmaindata->m_strCommandLine     += " \"";
//         pinitmaindata->m_strCommandLine     += argv[i];
//         pinitmaindata->m_strCommandLine     += "\"";
//      }
//   }
//   pinitmaindata->m_nCmdShow              = e_display_normal;
//
//
//   psystem->init_main_data(pinitmaindata);
//
//   //message_box(nullptr, "box1", "box1", e_message_box_icon_information);
//
//   nReturnCode = psystem->main();
//
//   try
//   {
//      delete psystem;
//   }
//   catch(...)
//   {
//   }
//
//   psystem = nullptr;
//
//
//
//   return nReturnCode;
//
//}
//
//
//int CLASS_DECL_ACME ca2_main(::platform::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, const_char_pointer  lpCmdLine, int nCmdShow)
//{
//   try
//   {
//
//      ASSERT(hPrevInstance == nullptr);
//
//      int nReturnCode = 0;
//
//      ::android::main_init_data * pinitmaindata  = __allocate ::android::main_init_data();
//
//      pinitmaindata->m_hInstance             = hInstance;
//      pinitmaindata->m_hPrevInstance         = hPrevInstance;
//      pinitmaindata->m_strCommandLine        = lpCmdLine;
//      pinitmaindata->m_nCmdShow              = nCmdShow;
//
//      psystem->init_main_data(pinitmaindata);
//
//      nReturnCode = psystem->main();
//
//      __android_term();
//
//      try
//      {
//
//         delete psystem;
//
//      }
//      catch(...)
//      {
//
//      }
//
//      psystem = nullptr;
//
//      return nReturnCode;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return -1;
//
//}


#ifdef WINDOWS


void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{

   __UNREFERENCED_PARAMETER(uiCode);
   __UNREFERENCED_PARAMETER(ppointers);

}


#endif





















