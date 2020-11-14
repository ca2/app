#include "framework.h"


//extern thread_pointer < os_thread > t_posthread;



//string & get_command_line_string()
//{
//   static string g_strCommandLine;
//   return g_strCommandLine;
//}
//
//wstring & get_command_line_wstring()
//{
//   static wstring g_wstrCommandLine;
//   return g_wstrCommandLine;
//}


//void SetCommandLineA(const char * psz)
//{
//
//   get_command_line_string()     = psz;
//   get_command_line_wstring()    = psz;
//
//}
//
//void SetCommandLineW(const unichar * pwsz)
//{
//
//   get_command_line_string()     = pwsz;
//      get_command_line_wstring()     = pwsz;
//
//}

//
//char * GetCommandLineA()
//{
//
//   return (char *) (const char *) get_command_line_string();
//
//}
//
//LPWSTR GetCommandLineW()
//{
//
//   return (LPWSTR) (const widechar *)    get_command_line_wstring() ;
//
//}
//



//void output_debug_string(const char * psz)
//{
//
//   output_debug_string(psz);
//
//}






CLASS_DECL_ACME bool __node_aura_pre_init()
{

//   ace_set_alloc(ace_memory_alloc, &ace_memory_realloc, &ace, <#size_t s#>, <#PFN_MEMORY_REALLOC prealloc#>, <#PFN_MEMORY_FREE pfree#>, <#PFN_MEMORY_SIZE psize#>)
//
   return true;

}



CLASS_DECL_ACME bool __node_pos_init()
{

   //t_posthread = new os_thread(nullptr, nullptr);

   //t_posthread->m_bRun = true;

   return true;

}





CLASS_DECL_ACME bool __node_pre_term()
{

   /*   if(t_posthread != nullptr)
      {

         try
         {

            delete t_posthread;

         }
         catch(...)
         {

         }

         t_posthread = nullptr;

      }*/


   return true;

}

void ui_app_terminate();


CLASS_DECL_ACME bool __node_pos_term()
{
   //#elif defined(APPLEIOS)
   //
   ui_app_terminate();
   //
   //#endif

   return true;

}


void ui_app_terminate()
{

// does nothing, remains in memory

}

unsigned int m_sleep(unsigned int seconds);


extern "C"
unsigned int sleep(unsigned int seconds)
{

   return m_sleep(seconds);

}







//CLASS_DECL_ACME bool __node_aura_pre_init()
//{
//
//
//   return true;
//
//}



CLASS_DECL_ACME bool __node_aura_pos_init()
{

   //   t_posthread = new os_thread(nullptr, nullptr);
   //
   //   t_posthread->m_bRun = true;

   return true;

}





CLASS_DECL_ACME bool __node_aura_pre_term()
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



CLASS_DECL_ACME bool __node_aura_pos_term()
{



   return true;

}



//int _get_exe_path_len();
//void _get_exe_path(char * pszPath, int size);
//
//
//string get_exe_path()
//{
//
//   string str;
//
//   int len = _get_exe_path_len();
//
//   char * psz = str.get_string_buffer(len);
//
//   _get_exe_path(psz, len);
//
//   str.ReleaseBuffer(len);
//
//   return str;
//
//}
//


//class ios_aura_init
//{
//public:
//   ios_aura_init()
//   {
//
//      ace_set_alloc(&memory_alloc, &memory_realloc, &memory_free, &memory_size);
//
//   }
//
//
//};
//
//ios_aura_init g_ios_aura_init;
//
