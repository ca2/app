#include "framework.h"
#include "aura/os/_.h"
#include "aura/os/_os.h"


#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <spawn.h>
#include <mach-o/dyld.h>

::file::path macos_app_path(string strApp)
{

   ::file::path path =          auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->home() / "Library/papp Support/ca2/mypath" / (strApp + ".txt");

   return m_psystem->m_pacmefile->as_string(path);

}

extern char ** environ;

string_array get_c_args_for_c(const ::string & psz);

string transform_to_c_arg(const ::string & psz);

int create_process2(const ::string & _cmd_line, int * pprocessId);

i32 create_process(const ::string & pszCommandLine, i32 * pprocessId)
{

   string_array stra;
   
   stra = get_c_args_for_c(pszCommandLine);

   char * argv[1024 + 1];

   int argc = 0;

   for(auto & str : stra)
   {

      argv[argc] = (char *) str.c_str();

      argc++;

   }

   argv[argc] = nullptr;

   pid_t pid = 0;

   int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, environ);

   int iError = errno;

   char * pszError = strerror(iError);

   if (status == 0)
   {

      if(pprocessId != nullptr)
      {

         *pprocessId = pid;

      }

      return 1;

   }
   else
   {

      return 0;

   }

}



int create_process2(const ::string & _cmd_line, int * pprocessId)
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
      const char		*pArg, *pPtr;
      const char		*argv[1024 + 1];
      int		 argc;
      exec_path_name = cmd_line;
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


CLASS_DECL_CORE int call_async(
const char * pszPath,
const char * pszParam,
const char * pszDir,
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

   int processId;

   chdir(pszDir);

   if(!create_process(strCmdLine, &processId))
   {

      return -1;

   }

   if(puiPid != nullptr)
   {

      *puiPid = processId;

   }

   return 0;

}


CLASS_DECL_CORE u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
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
   {
      
      return -1;

   }

   set["pid"] = processId;

   while(true)
   {

      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;

      sleep(1_ms);

   }

   return 0;

}












bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, ::duration durationTimeout )
{
   
   property_set set;

   return call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), e_display_none, durationTimeout, set);

}

string apple_app_module_path()
{

   string str;

   char * psz = str.get_string_buffer(1024);


   u32 size = 1024;

   if(_NSGetExecutablePath(psz, &size) == 0)

   {

      str.release_string_buffer();

   }
   else
   {

      psz = str.get_string_buffer(size);


      if(_NSGetExecutablePath(psz, &size) == 0)

      {

         str.release_string_buffer();

      }
      else
      {

         return "";

      }

   }


   return str;

}

CLASS_DECL_CORE bool is_shared_library_busy(u32 processid, const string_array & stra)
{

   return false;

}


CLASS_DECL_CORE bool is_shared_library_busy(const string_array & stra)
{

   return false;

}

//
//void os_term_application()
//{
////
////   ns_app_terminate();
////
//}
//

CLASS_DECL_CORE ::file::path core_app_path(string strApp)
{

   ::file::path path = getenv("HOME");

   path /= "Library/papp Support/ca2/mypath" / strApp;

   path += ".txt";

   return m_psystem->m_pacmefile->as_string(path);

}


bool launch_command(const ::string & const pszCommand)
{
   
   if (!pszCommand)
   {
      
      return false;
      
   }
   
   string strParams;
   
   string strCommand(pszCommand);
   
   strCommand.replace("\"", "\\\"");
   
   strParams.format("-c \"screen -d -m %s\"", strCommand.c_str());
   
   if (call_async("/bin/bash", strParams,          auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->home(), e_display_none, false) != 0)
   {
      
      return false;
      
   }
   
   return true;
   
}


bool launch_macos_app(const ::string & pszAppFolder)
{
   
   if (!pszAppFolder)
   {
      
      return false;
      
   }
   
   string strCommand;
   
   strCommand.format("open \"%s\"", pszAppFolder);
   
   return ::launch_command(strCommand);
   
}


bool launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs)
{
   
   if (!pszAppFolder)
   {
      
      return false;
      
   }
   
   string strCommand;
   
   strCommand.format("open \"%s\" --args %s", pszAppFolder, pszArgs);
   
   return ::launch_command(strCommand);
   
}



