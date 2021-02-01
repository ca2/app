#include "framework.h"
#include "acme/platform/static_start.h"


#include <sys/wait.h>
#undef USE_MISC

#include <pthread.h>



string ca2_module_folder_dup();


struct chldstatus
{

   bool m_bRet;
   int  m_iExitCode;


};


typedef int_ptr_map < chldstatus > chldstatus_map;


critical_section * g_pcsPid2 = nullptr;


chldstatus_map * g_ppid = nullptr;


critical_section * get_pid_cs()
{

   critical_section_lock cs(::acme::g_pcsGlobal);

   if(g_pcsPid2 == nullptr)
   {

      g_pcsPid2 = new critical_section();

      g_ppid = new chldstatus_map();


   }

   return g_pcsPid2;

}


chldstatus get_chldstatus(int iPid)
{

   critical_section_lock sl(get_pid_cs());

   return g_ppid->operator[](iPid);

}

// must be called under get_pid_cs lock
void init_chldstatus(int iPid)
{

   auto & s = g_ppid->operator[](iPid);

   s.m_bRet = false;

   s.m_iExitCode = 0;

}


void ansios_sigchld_handler(int sig)
{

   int saved_errno = errno;

   int iExitCode;

   int iPid;

   while((iPid = waitpid(-1, &iExitCode,
                         WUNTRACED
#ifdef WNOHANG
                         | WNOHANG
#endif
#ifdef WCONTINUED
                         | WCONTINUED
#endif
                        )) > 0)
   {

      {

         critical_section_lock sl(get_pid_cs());

         auto ppair = g_ppid->plookup(iPid);

         if(ppair != nullptr)
         {

            ppair->element2().m_bRet = true;

            ppair->element2().m_iExitCode = iExitCode;

         }

      }

   }

   errno = saved_errno;

}


void install_sigchld_handler()
{

   struct sigaction sa;

   __zero(sa);

   sa.sa_handler = &ansios_sigchld_handler;

   sigemptyset(&sa.sa_mask);

   sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

   sigaction(SIGCHLD, &sa, nullptr);

}


CLASS_DECL_ACME void process_get_os_priority(i32 * piOsPolicy, sched_param * pparam, i32 iCa2Priority);


//namespace ansios
//{
//
//
//   process::process()
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
//   bool process::create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir,i32 iCa2Priority)
//   {
//
//      if(!::process::process::create_child_process(pszCmdLine,bPiped,pszDir,iCa2Priority))
//         return false;
//
//      string_array straParam;
//
//      address_array < char * > argv;
//
//      straParam.explode_command_line(pszCmdLine, &argv);
//
//      char *   cmd_line;
//
//      cmd_line = strdup(pszCmdLine);
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
//      char *   exec_path_name = cmd_line;
//
//      critical_section_lock sl(get_pid_cs());
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
//         char *      argv[1024 + 1];
//
//         i32		argc = 0;
//
//         prepare_argc_argv(argc, argv, cmd_line);
//
//         int iExitCode = execv(exec_path_name, argv);
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
//      int iExitCode;
//
//#if 0
//
//      {
//
//         int iPid;
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
//         m_exitstatus.m_iExitCode = 0x80000000;
//
//         return true;
//
//      }
//      else if(WIFSTOPPED(iExitCode))
//      {
//
//         m_exitstatus.m_iExitStop = WSTOPSIG(iExitCode);
//
//         m_exitstatus.m_iExitCode = 0x80000000;
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
//   bool process::synch_elevated(const char * pszCmdLineParam,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
//   {
//
//
//      string_array straParam;
//
//      address_array < char * > argv;
//
//      if (access("/usr/bin/gksu", X_OK) != 0)
//      {
//
//         m_exitstatus.m_iExitCode = -1;
//
//         ::message_box(nullptr,"gksu is not installed, please install gksu.","Please, install gksu.",e_message_box_icon_information);
//
//         return false;
//
//      }
//
//      string pszCmdLine = "/usr/bin/gksu " + string(pszCmdLineParam);
//
//      straParam.explode_command_line(pszCmdLine, &argv);
//
//      char *   cmd_line;
//
//      cmd_line = (char *) memory_alloc(strlen(pszCmdLine ) + 1 );
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
//      char *   exec_path_name = cmd_line;
//
//
//      critical_section_lock sl(get_pid_cs());
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
//         char     *pArg, *pPtr;
//         char     *argv[1024 + 1];
//         i32      argc;
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
//
//
//
//
