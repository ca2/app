#include "framework.h"
//#include "_linux.h"
////#include "acme/platform/app_core.h"
//#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
//#include <signal.h>
//#undef USE_MISC
//
//#include <sys/wait.h>
//#include <spawn.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include "node.h"
//
//int create_process6(const_char_pointer _cmd_line, int * pprocessId);
//
//CLASS_DECL_ACME void dll_processes(unsigned_int_array & dwa, string_array & straProcesses, const ::scoped_string & scopedstrDll)
//{
//
//   __UNREFERENCED_PARAMETER(dwa);
//   __UNREFERENCED_PARAMETER(straProcesses);
//   __UNREFERENCED_PARAMETER(scopedstrDll);
//
//}
//
//
//
//
//int create_process(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(scopedstrCommandLine);
//
//   address_array < char * > argv;
//
//   for(auto & str : stra)
//   {
//
//      argv.add((char *) str.c_str());
//
//   }
//
//   argv.add(nullptr);
//
//   pid_t pid = 0;
//
//   string strExe = argv[0];
//
//   int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv.get_data(), environ);
//
//   if (status == 0)
//   {
//
//      if(strExe.case_insensitive_ends("_app_core_clockverse"))
//      {
//
//         informationf("app-core/clockverse");
//
//      }
//
//      if(pprocessId != nullptr)
//      {
//
//         *pprocessId = pid;
//
//      }
//
//      return 1;
//
//   }
//   else
//   {
//
//      if(strExe.case_insensitive_ends("_app_core_clockverse"))
//      {
//
//         informationf("app-core/clockverse");
//
//      }
//
//      return 0;
//
//   }
//
//}
//
//
//int create_process3(const_char_pointer _cmd_line, int * pprocessId)
//{
//
//   char *   exec_path_name;
//
//   char *	cmd_line;
//
//   char *	cmd_line2;
//
//   cmd_line = strdup(_cmd_line);
//
//   if(cmd_line == nullptr)
//   {
//
//      return 0;
//
//   }
//
//   char *      argv[1024 + 1];
//
//   int		argc = 0;
//
//   prepare_argc_argv(argc, argv, cmd_line);
//
//   pid_t pid;
//
//   int status;
//
//   status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, environ);
//
//   free(cmd_line);
//
//   if (status == 0)
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return 0;
//
//   }
//
//}
//
//
//int daemonize_process(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(scopedstrCommandLine);
//
//   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));
//
//   int argc = 0;
//
//   for(auto & str : stra)
//   {
//
//      argv[argc] = strdup((char *) str.c_str());
//
//      argc++;
//
//   }
//
//   argv[argc] = nullptr;
//
//   pid_t pid;
//
//   pid = fork();
//
//   if (pid == -1)
//   {
//
//      printf("fork error\n");
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      return 0;
//
//   }
//   else if(pid > 0)
//   {
//
//      return 1;
//
//   }
//
//   daemon(0, 0);
//
////   signal(SIGCHLD, SIG_IGN);
////
////   umask(0);
////
////   int sid = setsid();
////
////   if (sid < 0)
////   {
////
////      exit(EXIT_FAILURE);
////
////   }
////
////    /* Change the current working directory.  This prevents the current
////       directory from being locked; hence not being able to erase it. */
////   if ((chdir("/")) < 0)
////   {
////
////      exit(EXIT_FAILURE);
////
////   }
////
////   /* Redirect standard files to /dev/null */
////   freopen( "/dev/null", "r", stdin);
////   freopen( "/dev/null", "w", stdout);
////   freopen( "/dev/null", "w", stderr);
//
//   int iExitCode = execv(argv[0], argv);
//
//   char ** pargv = argv;
//
//   while(*pargv != nullptr)
//   {
//
//      free(*pargv);
//
//      pargv++;
//
//   }
//
//   free(argv);
//
//   exit(iExitCode);
//
//
//   return 0;
//
//}
//
//
//int create_process4(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(scopedstrCommandLine);
//
//   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));
//
//   int argc = 0;
//
//   for(auto & str : stra)
//   {
//
//      argv[argc] = strdup((char *) str.c_str());
//
//      argc++;
//
//   }
//
//   argv[argc] = nullptr;
//
//   if((*pprocessId = fork()) == 0)
//   {
//
//      execv(argv[0], argv);
//
//      int status = 0;
//
//      wait(&status);
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      exit(status);
//
//   }
//   else if(*pprocessId == -1)
//   {
//
//      *pprocessId = 0;
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      return 0;
//
//   }
//
//   return 1;
//
//}
//
//
//CLASS_DECL_ACME void call_async(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
//{
//
//   string strCmdLine;
//
//   strCmdLine = pszPath;
//
//   if(ansi_length(scopedstrParam) > 0)
//   {
//
//      strCmdLine +=  " ";
//
//      strCmdLine += pszParam;
//
//   }
//
//   int processId;
//
//   if(!create_process(strCmdLine, &processId))
//   {
//
//      if(puiPid != nullptr)
//      {
//
//         *puiPid = -1;
//
//      }
//
//      return -1;
//
//   }
//
//   if(puiPid != nullptr)
//   {
//
//      *puiPid = processId;
//
//   }
//
//   return 0;
//
//}
//
//
//CLASS_DECL_ACME void call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
//{
//
//   string strCmdLine;
//
//   strCmdLine = pszPath;
//
//   if(ansi_length(scopedstrParam) > 0)
//   {
//
//      strCmdLine +=  " ";
//
//      strCmdLine += pszParam;
//
//   }
//
//   int processId;
//
//   if(!create_process(strCmdLine, &processId))
//   {
//
//      set["pid"] = processId;
//
//      return -1;
//
//   }
//
//
//   while(true)
//   {
//
//      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
//      {
//
//         break;
//
//      }
//
//      sleep(1_ms);
//
//   }
//
//   set["pid"] = processId;
//
//   return 0;
//
//}
//
//
//string module_path_from_pid(unsigned int iPid)
//{
//
//   struct stat sb;
//
//   int iSize;
//
//   string str;
//
//   str = "/proc/" + as_string(iPid) + "/exe";
//
//   memory mem;
//
//   ssize_t s;
//
//   bool iTry;
//
//   if(lstat(str, &sb) == -1)
//   {
//
//retry:
//
//      iSize = 1024 * 4;
//
//      iTry = 1;
//
//      sb.st_size = iSize - 1;
//
//   }
//   else
//   {
//
//      iSize = sb.st_size + 1;
//
//      iTry = 0;
//
//   }
//#if MEMDLEAK
//   mem.m_strTag = "memory://function=module_path_from_pid";
//#endif
//   mem.set_size(iSize);
//
//   s = readlink (str, (char *) mem.get_data(), iSize);
//
//   if(s > sb.st_size)
//   {
//
//      if(iTry <= 0)
//      {
//
//         goto retry;
//
//      }
//      else
//      {
//
//         return "";
//
//      }
//
//   }
//
//   mem.get_data()[s] = '\0';
//
//   return (const_char_pointer )mem.get_data();
//
//}
//
//
//::int_array module_path_get_pid(const ::file::path & path)
//{
//
//   ::int_array ia;
//
//   ::file::path_array stra;
//
//   ::dir::ls_dir(stra, "/proc/");
//
//   for(auto & strPid : stra)
//   {
//
//      int iPid = atoi(strPid.title());
//
//      if(iPid > 0)
//      {
//
//         string strPath =module_path_from_pid(iPid);
//
//         if(strPath	 == pszPath)
//         {
//
//            ia.add(iPid);
//
//         }
//
//      }
//
//   }
//
//   return ia;
//
//}
//
//namespace acme
//{
//
//
//   namespace posix
//   {
//
//
//      atom_array node::module_path_get_pid(const ::scoped_string & scopedstr)
//      {
//
//         informationf("os/linux_process.cpp app_get_pid (" + string(scopedstr) + ")");
//
//         atom_array ia;
//
//         ::file::path_array stra;
//
//         ::dir::ls_dir(stra, "/proc/");
//
//         string str(scopedstr);
//
//         str = "app=" + str;
//
//         string strApp(scopedstr);
//
//         strApp.replace("-", "_");
//
//         strApp.replace("/", "_");
//
//         string strApp2;
//
//         strApp2 = "_" + strApp;
//
//         for (auto & strPid : stra)
//         {
//
//            int iPid = atoi(strPid.title());
//
//            if (iPid > 0)
//            {
//
//               //if(iPid == 22912)
//               //{
//               //informationf("22912");
//               //}
//               ::file::path path = module_path_from_pid(iPid);
//
//               if (path.has_character())
//               {
//
//                  //information(path + "\n");
//
//               }
//
//               string strTitle = path.title();
//
//               strTitle.case_insensitive_ends_eat(" (deleted)");
//
//               if (strTitle == strApp ||
//                   strTitle == strApp2)
//               {
//
//                  ia.add(iPid);
//
//               } else
//               {
//
//                  string_array straCmdLine = cmdline_from_pid(iPid);
//
//                  string strCmdLine;
//
//                  strCmdLine = straCmdLine.implode(" ");
//
//                  if (straCmdLine.find_first(str) > 0)
//                  {
//
//                     ia.add(iPid);
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         return ia;
//
//      }
//
//
//      string node::command_line_from_pid(unsigned int iPid)
//      {
//
//         string_array stra;
//
//         string str;
//
//         str = "/proc/" + as_string(iPid) + "/cmdline";
//
//         memory mem = file_as_memory(str);
//
//         string strArg;
//
//         char ch;
//
//         for (int i = 0; i < mem.get_size(); i++)
//         {
//
//            ch = (char) mem.get_data()[i];
//
//            if (ch == '\0')
//            {
//
//               stra.add(strArg);
//
//               strArg.empty();
//
//            } else
//            {
//
//               strArg += ch;
//
//            }
//
//
//         }
//
//         if (strArg.has_character())
//         {
//
//            stra.add(strArg);
//
//         }
//
//         return stra;
//
//         /* the easiest case: we are in linux */
////    ssize_t s = readlink (str, path, iSize);
//
//         //  if(s == -1)
//         //{
//         // return "";
//         //}
//
//         //path[s] = '\0';
//
//         //return path;
//
//      }
//
//
//      bool node::is_shared_library_busy(unsigned int processid, const string_array & stra)
//      {
//
//         return false;
//
//      }
//
//
//      bool node::is_shared_library_busy(const string_array & stra)
//      {
//
//         return false;
//
//      }
//
//
//
//   } // namespace posix
//
//
//} // namespace acme
//
//bool shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::time timeTimeout )
//{
//
//   ::property_set set;
//
//   return call_sync(scopedstrFile, pszParams, ::file::path(scopedstrFile).folder(), e_display_none, timeTimeout, set);
//
//}
//
//
//
//
//
//
//CLASS_DECL_ACME int ca2_main();
//
//
//
//int create_process2(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(scopedstrCommandLine);
//
//   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));
//
//   int argc = 0;
//
//   for(auto & str : stra)
//   {
//
//      argv[argc] = strdup((char *) str.c_str());
//
//      argc++;
//
//   }
//
//   argv[argc] = nullptr;
//
//   pid_t pid = 0;
//
//   if((pid = fork()) == 0) // child
//   {
//
//      int iExitCode = execv(argv[0], argv);
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      exit(iExitCode);
//
//   }
//   else if(pid == -1) // in parent, but error
//   {
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      return 0;
//
//   }
//
//   if(pprocessId != nullptr)
//   {
//
//      *pprocessId = pid;
//
//   }
//
//   return 1;
//
//}
//
//
//
//
//CLASS_DECL_ACME ::file::path core_app_path(const ::scoped_string & scopedstrApp)
//{
//
//   strApp.replace("-", "_");
//
//   strApp.replace("/", "_");
//
//   return "/xcore/time/x64/basis/" + strApp;
//
//}
//
//


unsigned int get_current_process_id()
{

   return getpid();

}


//
//
//



void sigchld_handler(int signum) {
    int saved_errno = errno;
    int status;
    pid_t pid;
    
    printf_line("Child exited!!");
    
    preempt(5_s);

    // Reap all dead children
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child %d terminated by signal %d (%s)\n", pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
        }
    }

    errno = saved_errno;
}


void sigpipe_handler(int signum) 
{
	
}


void install_operating_system_default_signal_handlers()
{      
      
   //// Create an empty signal set
   //sigset_t set;

   //// Initialize the signal set to include all signals
   //if (sigfillset(&set) == -1) 
   //{
   //errf_line("sigfillset");
   ////exit(1);
   //}

   //// Unblock all signals by setting the signal mask
   //if (sigprocmask(SIG_UNBLOCK, &set, NULL) == -1)
   //{
   //errf_line("sigprocmask");
   ////exit(1);
   //}

   //// Now, all signals are unblocked and can be delivered
   //printf_line("All signals unblocked.\n");


   //struct sigaction sa;
   //sa.sa_handler = ::sigchld_handler;
   //sigemptyset(&sa.sa_mask);
   //sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

   //if (sigaction(SIGCHLD, &sa, NULL) == -1) 
   //{

   //errf_line("sigaction for SIGCHLD failed");

   //}
   //else
   //{

   //printf_line("Installed sigaction for SIGCHLD");

   //}
   
   {

      struct sigaction sa{};
      sa.sa_handler = SIG_IGN;  // Ignore the signal
      sigemptyset(&sa.sa_mask);
      sa.sa_flags = 0;

      if (sigaction(SIGCHLD, &sa, NULL) == -1) 
      {

         errf_line("sigaction failed to ignore sigchld");
         
         //return 1;
         
      }
      else
      {

         printf_line("Ignoring SIGCHLD");

      }

   }
	
   {

      struct sigaction sa{};
      sa.sa_handler = SIG_IGN;  // Ignore the signal
      sigemptyset(&sa.sa_mask);
      //sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
      sa.sa_flags = 0;

      if (sigaction(SIGPIPE, &sa, NULL) == -1) 
      {

         errf_line("sigaction failed to ignore sigpipe");
         
         //return 1;
         
      }
      else
      {

         printf_line("Ignoring SIGPIPE");

      }

   }

   //preempt(5_s);

}


