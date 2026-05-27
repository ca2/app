#include "framework.h"
#include "acme/platform/acme.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include <sys/wait.h>
#undef USE_MISC

#include "acme/operating_system/ansi/_pthread.h"



string ca2_module_folder_dup();


//struct chldstatus
//{
//
//   bool m_bRet;
//   ::i32  m_iExitCode;
//
//
//};


//typedef iptr_map < chldstatus > chldstatus_map;
//
//
//critical_section * g_pcsPid2 = nullptr;
//
//
//chldstatus_map * g_ppid = nullptr;
//
//
//critical_section * get_pid_cs()
//{
//
//   critical_section_lock cs(::acme::g_pcsGlobal);
//
//   if(g_pcsPid2 == nullptr)
//   {
//
//      g_pcsPid2 = allocateø critical_section();
//
//      g_ppid = allocateø chldstatus_map();
//
//
//   }
//
//   return g_pcsPid2;
//
//}
//
//
//chldstatus get_chldstatus(::i32 iPid)
//{
//
//   critical_section_lock synchronouslock(get_pid_cs());
//
//   return g_ppid->operator[](iPid);
//
//}
//
// must be called under get_pid_cs lock
//void init_chldstatus(::i32 iPid)
//{
//
//   auto & s = g_ppid->operator[](iPid);
//
//   s.m_bRet = false;
//
//   s.m_iExitCode = 0;
//
//}
//
//
//void ansios_sigchld_handler(::i32 sig)
//{
//
//   ::i32 saved_errno = errno;
//
//   ::i32 iExitCode;
//
//   ::i32 iPid;
//
//   while((iPid = waitpid(-1, &iExitCode,
//                         WUNTRACED
//#ifdef WNOHANG
//                         | WNOHANG
//#endif
//#ifdef WCONTINUED
//                         | WCONTINUED
//#endif
//                        )) > 0)
//   {
//
//      {
//
//         critical_section_lock synchronouslock(get_pid_cs());
//
//         auto iterator = g_ppid->find(iPid);
//
//         if(iterator != nullptr)
//         {
//
//            iterator->element2().m_bRet = true;
//
//            iterator->element2().m_iExitCode = iExitCode;
//
//         }
//
//      }
//
//   }
//
//   errno = saved_errno;
//
//}
//
//
//void install_sigchld_handler()
//{
//
//   struct sigaction sa;
//
//   zero(sa);
//
//   sa.sa_handler = &ansios_sigchld_handler;
//
//   sigemptyset(&sa.sa_mask);
//
//   sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
//
//   sigaction(SIGCHLD, &sa, nullptr);
//
//}


CLASS_DECL_ACME void process_get_os_priority(::i32 * piOsPolicy, sched_param * pparam, ::i32 iCa2Priority);


//namespace ansios
//{
//
//
//   operating_system::process()
//   {
//
//   }
//
//
//   process::~process()
//   {
//
//   }
//
//
//   bool process::create_child_process(const ::scoped_string & scopedstrCmdLine,bool bPiped,const ::scoped_string & scopedstrDir,::i32 iCa2Priority)
//   {
//
//      if(!::operating_system::process::create_child_process(scopedstrCmdLine,bPiped,pszDir,iCa2Priority))
//         return false;
//
//      string_array_base straParam;
//
//      address_array < char_pointer > argv;
//
//      straParam.explode_command_line(scopedstrCmdLine, &argv);
//
//      char_pointer cmd_line;
//
//      cmd_line = strdup(scopedstrCmdLine);
//
//      if(cmd_line == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      //ansi_copy(cmd_line, pszCmdLine);
//
//      char_pointer exec_path_name = cmd_line;
//
//      critical_section_lock synchronouslock(get_pid_cs());
//
//      if((m_iPid = ::fork()) == 0)
//      {
//
//         if(bPiped)
//         {
//
//            dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);
//
//            dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);
//
//            dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);
//
//         }
//
//
//
//         char_pointer argv[1024 + 1];
//
//         ::i32		argc = 0;
//
//         prepare_argc_argv(argc, argv, cmd_line);
//
//         ::i32 iExitCode = execv(exec_path_name, argv);
//
//         free(cmd_line);
//
//         exit(iExitCode);
//
//      }
//      else if(m_iPid == -1)
//      {
//
//         // in parent, but error
//
//         m_iPid = 0;
//
//         free(cmd_line);
//
//         return 0;
//
//      }
//
//      // in parent, success
//
//      init_chldstatus(m_iPid);
//
//      return 1;
//
//   }
//
//
//   bool process::has_exited()
//   {
//
//      ::i32 iExitCode;
//
//#if 0
//
//      {
//
//         ::i32 iPid;
//
//         iPid = waitpid(m_iPid, &iExitCode,
//                        WUNTRACED
//#ifdef WNOHANG
//                        | WNOHANG
//#endif
//#ifdef WCONTINUED
//                        | WCONTINUED
//#endif
//                       );
//
//         if(iPid == 0)
//         {
//
//            return false;
//
//         }
//         else if(iPid == -1)
//         {
//
//            return true;
//
//         }
//
//      }
//
//#else
//
//      {
//
//         auto chldstatus = get_chldstatus(m_iPid);
//
//         if(!chldstatus.m_bRet)
//         {
//
//            return false;
//
//         }
//
//         iExitCode = chldstatus.m_iExitCode;
//
//      }
//
//#endif
//
//      if(WIFEXITED(iExitCode))
//      {
//
//         m_exitstatus.m_iExitCode = WEXITSTATUS(iExitCode);
//
//         return true;
//
//      }
//      else if(WIFSIGNALED(iExitCode))
//      {
//
//         m_exitstatus.m_iExitSignal = WTERMSIG(iExitCode);
//
//         m_exitstatus.m_iExitCode = I32_MINIMUM;
//
//         return true;
//
//      }
//      else if(WIFSTOPPED(iExitCode))
//      {
//
//         m_exitstatus.m_iExitStop = WSTOPSIG(iExitCode);
//
//         m_exitstatus.m_iExitCode = I32_MINIMUM;
//
//         return true;
//
//      }
//#ifdef WIFCONTINUED
//      else if(WIFCONTINUED(iExitCode))
//      {
//
//         return false;
//
//      }
//#endif
//
//      return true;
//
//   }
//
//
//   bool process::synch_elevated(const ::scoped_string & scopedstrCmdLineParam,::i32 iShow,const class time & timeTimeOut,bool * pbTimeOut)
//   {
//
//
//      string_array_base straParam;
//
//      address_array < char_pointer > argv;
//
//      if (access("/usr/bin/gksu", X_OK) != 0)
//      {
//
//         m_exitstatus.m_iExitCode = -1;
//
//         ::message_box(nullptr,"gksu is not installed, please install gksu.","Please, install gksu.",::user::e_message_box_icon_information);
//
//         return false;
//
//      }
//
//      string pszCmdLine = "/usr/bin/gksu " + string(scopedstrCmdLineParam);
//
//      straParam.explode_command_line(scopedstrCmdLine, &argv);
//
//      char_pointer cmd_line;
//
//      cmd_line = (char_pointer ) ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(strlen(scopedstrCmdLine ) + 1 );
//
//      if(cmd_line == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ansi_copy(cmd_line, pszCmdLine);
//
//      char_pointer exec_path_name = cmd_line;
//
//
//      critical_section_lock synchronouslock(get_pid_cs());
//
//      if((m_iPid = ::fork()) == 0)
//      {
//
//         //if(bPiped)
//         //{
//         //   dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);
//         //   dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);
//         //   dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);
//         //}
//
//
//         // child
//         char_pointer pArg, *pPtr;
//         char_pointer argv[1024 + 1];
//         ::i32      argc;
//         if( ( pArg = ansi_find_char_reverse( exec_path_name, '/' ) ) != nullptr )
//            pArg++;
//         else
//            pArg = exec_path_name;
//         argv[0] = pArg;
//         argc = 1;
//
//         if( cmd_line != nullptr && *cmd_line != '\0' )
//         {
//            pArg = strtok_r_dup(cmd_line, " ", &pPtr);
//            while( pArg != nullptr )
//            {
//               argv[argc] = pArg;
//               argc++;
//               if( argc >= 1024 )
//                  break;
//               pArg = strtok_r_dup(nullptr, " ", &pPtr);
//            }
//         }
//         argv[argc] = nullptr;
//
//         execv(exec_path_name, argv);
//         free(cmd_line);
//         exit( -1 );
//      }
//      else if(m_iPid == -1)
//      {
//         // in parent, but error
//         m_iPid = 0;
//         free(cmd_line);
//         return false;
//      }
//
//      init_chldstatus(m_iPid);
//
//      // in parent, success
//      return true;
//
//   }
//
//} // namespace ansios



::u32 get_current_process_id()
{

   return getpid();

}


char_pointer _android_get_executable_path_dup()
{
   ::i8 exe_path[PATH_MAX *8];
   ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
   if (len != -1) {
      exe_path[len] = '\0';
      return strdup(exe_path);
   } else {
      return strdup("");
   }
}