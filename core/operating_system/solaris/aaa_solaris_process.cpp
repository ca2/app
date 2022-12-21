#include "framework.h"


#include <signal.h>
#undef USE_MISC



extern thread_int_ptr < os_thread > t_posthread;


i32 create_process(const ::string & _cmd_line, i32 * pprocessId)
{
   char *   exec_path_name;
   char *	cmd_line;

   cmd_line = (char *) ca2_alloc(strlen(_cmd_line ) + 1 );

   if(cmd_line == nullptr)
      return 0;

   ansi_copy(cmd_line, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {
      // child
      char		*pArg, *pPtr;
      char		*argv[1024 + 1];
      i32		 argc;
      if( ( pArg = ansi_find_char_reverse( exec_path_name, '/' ) ) != nullptr )
         pArg++;
      else
         pArg = exec_path_name;
      argv[0] = pArg;
      argc = 1;

      if( cmd_line != nullptr && *cmd_line != '\0' )
      {
         pArg = strtok_r_dup(cmd_line, " ", &pPtr);
         while( pArg != nullptr )
         {
            argv[argc] = pArg;
            argc++;
            if( argc >= 1024 )
               break;
            pArg = strtok_r_dup(nullptr, " ", &pPtr);
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

CLASS_DECL_CORE i32 call_async(
const ::file::path & path,
const ::scoped_string & scopedstrParam,
const ::scoped_string & scopedstrDir,
i32 iShow)
{
   vsstring strCmdLine;

   strCmdLine = pszPath;
   if(ansi_length(pszParam) > 0)
   {
      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }

   i32 processId;

   if(!create_process(strCmdLine, &processId))
      return -1;

   return 0;

}

CLASS_DECL_CORE u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
{
   vsstring strCmdLine;

   strCmdLine = pszPath;
   if(ansi_length(pszParam) > 0)
   {
      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }

   i32 processId;

   if(!create_process(strCmdLine, &processId))
      return -1;


   while(true)
   {

      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;
      sleep(1_ms);
   }

   return 0;
}










CLASS_DECL_CORE bool main_initialize()
{

   initialize_primitive_heap();

   if(!os_initialize())
      return false;

   return true;

}


CLASS_DECL_CORE bool main_finalize()
{

   bool bOk = true;

   if(!os_finalize())
      bOk = false;

   finalize_primitive_trace();

   return bOk;

}




bool os_initialize()
{


   if(!initialize_primitive_trace())
      return false;

   t_posthread = memory_new os_thread(nullptr, nullptr);

   t_posthread->m_bRun = true;

   return true;

}


bool os_finalize()
{

   if(t_posthread != nullptr)
   {

      try
      {

         delete t_posthread;

      }
      catch(...)
      {

      }

      t_posthread = nullptr;

   }

   os_thread::stop_all((5000) * 49);

   finalize_primitive_trace();

   return true;

}
