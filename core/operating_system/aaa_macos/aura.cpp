#include "framework.h"
#include "aura/update.h"



void ns_app_run();

//void ns_app_terminate();





CLASS_DECL_CORE bool __node_aura_pre_init()
{

   setlocale(LC_ALL,"");

   return true;

}



CLASS_DECL_CORE bool __node_aura_pos_init()
{

//   t_posthread = memory_new os_thread(nullptr, nullptr);
//
//   t_posthread->m_bRun = true;

   return true;

}





CLASS_DECL_CORE bool __node_aura_pre_term()
{

//   if(t_posthread != nullptr)
//   {
//
//      try
//      {
//
//         delete t_posthread;
//
//      }
//      catch(...)
//      {
//
//      }
//
//      t_posthread = nullptr;
//
//   }

   return true;

}



CLASS_DECL_CORE bool __node_aura_pos_term()
{

//#ifdef MACOS
//
   //ns_app_terminate();
//
//#elif defined(APPLEIOS)
//
//   ui_app_terminate();
//
//#endif


   return true;

}





//char * mm_ca2_command_line();
//
//string ca2_command_line()
//{
//
//   char * psz = mm_ca2_command_line();
//
//   string str(psz);
//
//   free(psz);
//
//   return str;
//
//}





