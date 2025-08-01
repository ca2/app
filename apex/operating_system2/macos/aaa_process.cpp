#include "framework.h"
//#include "apex/os/_.h"
#include "apex/os/_os.h"


#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <spawn.h>
#include <mach-o/dyld.h>

::file::path macos_app_path(string strApp)
{

   ::file::path path =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->home() / "Library/papp Support/ca2/mypath" / (strApp + ".txt");

   return file_system()->as_string(path);

}

extern char ** environ;

string_array get_c_args_for_c(const ::scoped_string & scopedstr);

string transform_to_c_arg(const ::scoped_string & scopedstr);

int create_process2(const char * _cmd_line, int * pprocessId);

int create_process(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
{

   string_array stra;
   
   stra = get_c_args_for_c(scopedstrCommandLine);

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



int create_process2(const char * _cmd_line, int * pprocessId)
{
   char *   exec_path_name;
   char *	cmd_line;

   cmd_line = (char *) ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(strlen(_cmd_line ) + 1 );

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


CLASS_DECL_APEX int call_async(
const ::file::path & path,
const ::scoped_string & scopedstrParam,
const ::scoped_string & scopedstrDir,
::e_display edisplay,
bool bPrivileged,
unsigned int * puiPid)
{

   string strCmdLine;

   strCmdLine = pszPath;

   if(ansi_length(scopedstrParam) > 0)
   {

      strCmdLine +=  " ";

      strCmdLine += pszParam;

   }

   int processId;

   chdir(scopedstrDir);

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


CLASS_DECL_APEX unsigned int call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
{

   string strCmdLine;

   strCmdLine = pszPath;

   if(ansi_length(scopedstrParam) > 0)
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












bool shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::duration durationTimeout )
{
   
   ::property_set set;

   return call_sync(scopedstrFile, pszParams, ::file::path(scopedstrFile).folder(), e_display_none, durationTimeout, set);

}

string apple_app_module_path()
{

   string str;

   char * psz = str.get_buffer(1024);


   unsigned int size = 1024;

   if(_NSGetExecutablePath(scopedstr, &size) == 0)

   {

      str.release_buffer();

   }
   else
   {

      psz = str.get_buffer(size);


      if(_NSGetExecutablePath(scopedstr, &size) == 0)

      {

         str.release_buffer();

      }
      else
      {

         return "";

      }

   }


   return str;

}

CLASS_DECL_APEX bool is_shared_library_busy(unsigned int processid, const string_array & stra)
{

   return false;

}


CLASS_DECL_APEX bool is_shared_library_busy(const string_array & stra)
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


CLASS_DECL_APEX ::file::path core_app_path(string strApp)
{

   ::file::path path = getenv("HOME");

   path /= "Library/papp Support/ca2/mypath" / strApp;

   path += ".txt";

   return file_system()->as_string(path);

}


bool launch_command(const char * const pszCommand)
{
   
   if (!pszCommand)
   {
      
      return false;
      
   }
   
   string strParams;
   
   string strCommand(scopedstrCommand);
   
   strCommand.replace("\"", "\\\"");
   
   strParams.formatf("-c \"screen -d -m %s\"", strCommand.c_str());
   
   if (call_async("/bin/bash", strParams,          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->home(), e_display_none, false) != 0)
   {
      
      return false;
      
   }
   
   return true;
   
}


bool launch_macos_app(const ::scoped_string & scopedstrAppFolder)
{
   
   if (!pszAppFolder)
   {
      
      return false;
      
   }
   
   string strCommand;
   
   strCommand.formatf("open \"%s\"", pszAppFolder);
   
   return ::launch_command(strCommand);
   
}


bool launch_macos_app_args(const ::scoped_string & scopedstrAppFolder, const ::scoped_string & scopedstrArgs)
{
   
   if (!pszAppFolder)
   {
      
      return false;
      
   }
   
   string strCommand;
   
   strCommand.formatf("open \"%s\" --args %s", pszAppFolder, pszArgs);
   
   return ::launch_command(strCommand);
   
}



