#include "framework.h"


void get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority);


i32 create_process(const char * _cmd_line, i32 * pprocessId)
{

   char *   exec_path_name = nullptr;

   char *   cmd_line;

   cmd_line = (char *) ::heap::management::memory(::heap::e_memory_main)->allocate(strlen(_cmd_line ) + 1 );

   if (cmd_line == nullptr)
   {

      return 0;

   }

   ansi_copy(cmd_line, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {

      // child
      const char     *pArg, *pPtr;
      const char     *argv[1024 + 1];
      i32      argc;
      if( ( pArg = ansi_find_char_reverse( exec_path_name, '/' ) ) != nullptr )
         pArg++;
      else
         pArg = exec_path_name;
      argv[0] = pArg;
      argc = 1;

      if( cmd_line != nullptr && *cmd_line != '\0' )
      {
         pArg = strtok_r(cmd_line, " ", (char **) &pPtr);
         while( pArg != nullptr )
         {
            argv[argc] = pArg;
            argc++;
            if( argc >= 1024 )
               break;
            pArg = strtok_r(nullptr, " ", (char **) &pPtr);
         }
      }
      argv[argc] = nullptr;

      execv(exec_path_name, (char * const *) argv);
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


CLASS_DECL_APEX i32 call_async(
const ::file::path & path,
const ::scoped_string & scopedstrParam,
const ::scoped_string & scopedstrDir,
::e_display edisplay,
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

   i32 processId;

   if(!create_process(strCmdLine, &processId))
      return -1;

   if (puiPid != nullptr)
   {

      *puiPid = processId;

   }

   return 0;

}

CLASS_DECL_APEX u32 call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
{
   string strCmdLine;

   strCmdLine = pszPath;
   if(ansi_length(pszParam) > 0)
   {
      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }

   i32 processId;

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










CLASS_DECL_APEX bool main_initialize()
{

//   t_posthread = aaa_primitive_new os_thread(nullptr,nullptr);

   //t_posthread->m_bRun = true;

   return true;

}


CLASS_DECL_APEX bool main_finalize()
{

   //if(t_posthread != nullptr)
   //{

   //   try
   //   {

   //      delete t_posthread;

   //   }
   //   catch(...)
   //   {

   //   }

   //   t_posthread = nullptr;

   //}

//   os_thread::stop_all((5000) * 49);

   //finalize_primitive_trace();

   return true;

}








namespace process
{


   CLASS_DECL_APEX bool set_priority(::enum_priority epriority)
   {

      i32 iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, epriority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

   }




} // namespace process

//wideh * g_pwszCommandLine = nullptr;
//
//CLASS_DECL_APEX unichar * GetCommandLineW()
//{
//
//   return g_pwszCommandLine;
//
//}


CLASS_DECL_APEX bool shell_execute_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, ::duration durationTimeout)
{

   string strCmdLine;

   strCmdLine = pszPath;

   if (ansi_length(pszParam) > 0)
   {

      strCmdLine += " ";

      strCmdLine += pszParam;

   }

   i32 processId;

   if (!create_process(strCmdLine, &processId))
      return -1;

   ::earth::time timeEnd = ::earth::time::now() + durationTimeout;

   while (::earth::time::now() < timeEnd)
   {

      if (kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         return true;

      sleep(1_ms);

   }

   return true;

}


CLASS_DECL_APEX bool is_shared_library_busy(const string_array & stra)
{

   return true;

}


CLASS_DECL_APEX ::file::path core_app_path(string strApp)
{

   throw todo();

}
