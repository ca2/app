#include "framework.h"

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


//extern thread_pointer < os_thread > t_posthread;

namespace acme
{

   namespace ios
   {

::e_status node::create_process(const char * _cmd_line, int * pprocessId)
{
   char *   exec_path_name;
   char *	cmd_line;

   cmd_line = (char *) memory_allocate(strlen(_cmd_line ) + 1 );

   if(cmd_line == nullptr)
      return 0;

   ansi_copy(cmd_line, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {
      // child
      char		*pArg, *pPtr;
      char		*argv[1024 + 1];
      int		 argc;
      exec_path_name = cmd_line;
      if( ( pArg = (char * ) ansi_find_char_reverse( exec_path_name, '/' ) ) != nullptr )
         pArg++;
      else
         pArg = exec_path_name;
      argv[0] = pArg;
      argc = 1;

      if( cmd_line != nullptr && *cmd_line != '\0' )
      {
         pArg = ansi_tok_r(cmd_line, " ", &pPtr);
         while( pArg != nullptr )
         {
            argv[argc] = pArg;
            argc++;
            if( argc >= 1024 )
               break;
            pArg = ansi_tok_r(nullptr, " ", &pPtr);
         }
      }
      argv[argc] = nullptr;

      execv(exec_path_name, argv);
      free(cmd_line);
      exit( -1 );
   }
   else if(*pprocessId == -1)
   {
      // in parent, but error
      *pprocessId = 0;
      free(cmd_line);
      return 0;
   }
   // in parent, success
   return 1;
}

CLASS_DECL_ACME int call_async(
const char * pszPath,
const char * pszParam,
const char * pszDir,
int iShow)
{
   string strCmdLine;

   strCmdLine = pszPath;
   if(ansi_length(pszParam) > 0)
   {
      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }

   int processId;

   if(!create_process(strCmdLine, &processId))
      return -1;

   return 0;

}

CLASS_DECL_ACME int call_async(
const char * pszPath,
const char * pszParam,
const char * pszDir,
edisplay edisplay,
bool bPrivileged,
unsigned int * puiPid)
{

   string strCmdLine;

   strCmdLine = pszPath;
   if(ansi_length(pszParam) > 0)
   {
      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }

   int processId;

   if(!create_process(strCmdLine, &processId))
      return -1;

   if(puiPid != nullptr)
   {

      *puiPid = processId;


   }

   return 0;

}

CLASS_DECL_ACME u32 call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
{

   string strCmdLine;

   strCmdLine = pszPath;

   if(ansi_length(pszParam) > 0)
   {

      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }

   int processId;

   if(!create_process(strCmdLine, &processId))
      return -1;


   set["pid"] = processId;

   while(true)
   {

      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;

      sleep(1_ms);

   }

   return 0;

}







int get_current_process_affinity_order()
{

   int numCPU = (int) sysconf(_SC_NPROCESSORS_ONLN);

   return numCPU;
}






bool shell_execute_sync(const char * pszFile, const char * pszParams,  ::duration durationTimeout )
{
   
   ::property_set set;

   return call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), ::e_display_none, durationTimeout, set);

}




CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra)
{

   return false;

}


CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra)
{

   return false;

}


void os_post_quit()
{



}


////
//void os_term_application()
//{
////
//   //ui_app_terminate();
////
//}
//
//


CLASS_DECL_ACME ::file::path core_app_path(string strApp)
{

   throw todo();

}


namespace process
{


   CLASS_DECL_ACME bool set_priority(::enum_priority epriority)
   {

      return true;

   }


} // namespace process
