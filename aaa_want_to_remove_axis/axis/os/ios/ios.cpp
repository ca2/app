#include "framework.h"


//extern thread_pointer < os_thread > t_posthread;
//
//
//
//string & get_command_line_string()
//{
//   //static string g_strCommandLine;
//   return g_strCommandLine;
//}
//
//wstring & get_command_line_wstring()
//{
//   //static wstring g_wstrCommandLine;
//   return g_wstrCommandLine;
//}
//
//
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
//
//LPSTR GetCommandLineA()
//{
//
//   return (LPSTR) (LPCSTR) get_command_line_string();
//
//}
//
//LPWSTR GetCommandLineW()
//{
//
//   return (LPWSTR) (LPCWSTR)    get_command_line_wstring() ;
//
//}
//
//
//
//
//void output_debug_string(const char * psz)
//{
//
//   output_debug_string(psz);
//
//}
//
//
//
//
//
//
//CLASS_DECL_AXIS bool __node_pre_init()
//{
//   
//   
//   return true;
//   
//}
//
//
//
//CLASS_DECL_AXIS bool __node_pos_init()
//{
//   
//   t_posthread = new os_thread(nullptr, nullptr);
//   
//   t_posthread->m_bRun = true;
//   
//   return true;
//   
//}
//
//
//
//
//
//CLASS_DECL_AXIS bool __node_pre_term()
//{
//   
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
//   
//   
//   return true;
//   
//}
//
//
//
//CLASS_DECL_AXIS bool __node_pos_term()
//{
//   
//   return true;
//   
//}



CLASS_DECL_AXIS bool __node_axis_pre_init()
{
   
   
   return true;
   
}



CLASS_DECL_AXIS bool __node_axis_pos_init()
{
   
   
   return true;
   
}





CLASS_DECL_AXIS bool __node_axis_pre_term()
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



CLASS_DECL_AXIS bool __node_axis_pos_term()
{
   
   
   
   return true;
   
}


