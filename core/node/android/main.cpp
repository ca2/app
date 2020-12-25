#include "framework.h"


CLASS_DECL_CORE i32 ca2_main();

void CLASS_DECL_CORE __cdecl _ca2_purecall()
{
   __throw(::exception::exception());
}


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);





//i32 CLASS_DECL_CORE __android_main(::aura::system * psystem, i32 argc, char * argv[])
//{
//
//   if(!defer_au_init())
//      return -1;
//
//   i32 nReturnCode = 0;
//
//
//   ::android::main_init_data * pinitmaindata  = new ::android::main_init_data;
//
//
//   pinitmaindata->m_hInstance             = nullptr;
//   pinitmaindata->m_hPrevInstance         = nullptr;
//   if(argc > 0)
//   {
//      pinitmaindata->m_strCommandLine     = argv[0];
//   }
//   bool bColon = false;
//   for(i32 i = 1; i < argc; i++)
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
//i32 CLASS_DECL_CORE ca2_main(::aura::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, i32 nCmdShow)
//{
//   try
//   {
//
//      ASSERT(hPrevInstance == nullptr);
//
//      i32 nReturnCode = 0;
//
//      ::android::main_init_data * pinitmaindata  = new ::android::main_init_data;
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


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{

   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);

}
























