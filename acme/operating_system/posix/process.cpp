//
// Created by camilo on 2020-11-19. <3Thomas Boregaard SoerensenCamilo SasukeThomas Boregaard Soerensen!! DOMAS_16-09-0.1989
//
#include "framework.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/single_lock.h"
////#include "acme/exception/exception.h"
#include "acme/platform/_synchronization.h"
#include "acme/platform/acme.h"
#include "acme/prototype/string/str.h"
#include <sys/wait.h>
#include <unistd.h>
#if !defined(OPENBSD) && !defined(__ANDROID__)
#include <wordexp.h>
#endif
#include <fcntl.h>


#if !defined(APPLE_IOS)


//void command_system(string_array & straOutput, int& iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem, const class time & timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLog)
//{
//
//   single_lock singlelock(pparticleSynchronization);
//
//   ::e_status estatus = success;
//
//   int stdout_fds[2] = {};
//
//   int iError = pipe(stdout_fds);
//
//   if(iError != 0)
//   {
//
//      auto cerrornumber = c_error_number();
//
//      estatus = errno_status(iErrNo);
//
//      throw ::exception(estatus);
//
//   }
//
//   int stderr_fds[2] = {};
//
//   iError = pipe(stderr_fds);
//
//   if(iError != 0)
//   {
//
//      auto cerrornumber = c_error_number();
//
//      estatus = errno_status(iErrNo);
//
//      throw ::exception(estatus);
//
//   }
//
//   string strOutput;
//
//   string strError;
//
//   auto pszCommandLine = strdup(scopedstr);
//
//   const pid_t pid = fork();
//
//   if (!pid)
//   {
//
//      while((dup2(stdout_fds[1], STDOUT_FILENO) == -1) && (errno==EINTR)){}
//
//      while((dup2(stderr_fds[1], STDERR_FILENO) == -1) && (errno==EINTR)){}
//
//      close(stdout_fds[0]);
//
//      close(stdout_fds[1]);
//
//      close(stderr_fds[0]);
//
//      close(stderr_fds[1]);
//
//      wordexp_t we{};
//
//      wordexp(scopedstrCommandLine, &we, 0);
//
//      char ** argv = __allocate_array< char * >(we.we_wordc+1);
//
//      ::memory_copy(argv, we.we_wordv, we.we_wordc * sizeof(char*));
//
//      int iErrNo = 0;
//
//      int iChildExitCode = execvp(argv[0], &argv[0]);
//
//      if(iChildExitCode == -1)
//      {
//
//         iErrNo = errno;
//
//      }
//
//      delete []argv;
//
//      wordfree(&we);
//
//      free(scopedstrCommandLine);
//
//      _exit(iErrNo);
//
//   }
//
//   close(stdout_fds[1]);
//
//   close(stderr_fds[1]);
//
//   fcntl(stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);
//
//   fcntl(stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);
//
//   const int buf_size = 4096;
//
//   char buffer[buf_size];
//
//   char chExitCode = 0;
//
//   while(true)
//   {
//
//      if(!::task_get_run())
//      {
//
//         close(stdout_fds[0]);
//
//         close(stderr_fds[0]);
//
//         kill(pid, SIGKILL);
//
//         int iStatus = 0;
//
//         waitpid(pid, &iStatus, 0);
//
//         break;
//
//      }
//
//      bool bRead = false;
//
//      while(true)
//      {
//
//         const ssize_t iOutRead = read(stdout_fds[0], buffer, buf_size);
//
//         if (iOutRead > 0)
//         {
//
//            bRead = true;
//
//            string strMessage(buffer, iOutRead);
//
//            strOutput += strMessage;
//
//            if(ecommandsystem & e_command_system_inline_log)
//            {
//
//               printf("%s", strMessage.c_str());
//
//            }
//
//            ::str::get_lines(straOutput, strOutput, "I: ", false, &singlelock, pfileLog);
//
//         }
//
//         const ssize_t iErrRead = read(stderr_fds[0], buffer, buf_size);
//
//         if (iErrRead > 0)
//         {
//
//            bRead = true;
//
//            string strMessage(buffer, iErrRead);
//
//            strError += strMessage;
//
//            if(ecommandsystem & e_command_system_inline_log)
//            {
//
//               fprintf(stderr, "%s", strMessage.c_str());
//
//            }
//
//            ::str::get_lines(straOutput, strError, "E: ", false, &singlelock, pfileLog);
//
//         }
//
//         if(iOutRead > 0 || iErrRead > 0)
//         {
//
//            bRead = true;
//
//         }
//         else
//         {
//
//            break;
//
//         }
//
//      }
//
//      {
//
//         int status = 0;
//
//         int iWaitPid = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);
//
//         if(iWaitPid == -1)
//         {
//
//            int iErrorNo = errno;
//
//            if(iErrorNo != ECHILD)
//            {
//
//               break;
//
//            }
//
//         }
//         else if(iWaitPid == pid)
//         {
//
//            if (WIFEXITED(status))
//            {
//
//               chExitCode = WEXITSTATUS(status);
//
//               iExitCode = chExitCode;
//
//               break;
//
//            }
//
//         }
//
//      }
//
//      if(!bRead)
//      {
//
//         preempt(25_ms);
//
//      }
//
//   }
//
//   close(stdout_fds[0]);
//
//   close(stderr_fds[0]);
//
////   if(iExitCode != 0)
////   {
////
////      auto estatus = failed_errno_status(iExitCode);
////
////      throw ::exception(estatus);
////
////   }
//
//   ::str::get_lines(straOutput, strOutput, "I: ", true, &singlelock, pfileLog);
//
//   ::str::get_lines(straOutput, strError, "E: ", true, &singlelock, pfileLog);
//
//}


#endif


critical_section * g_pcsPid2 = nullptr;


namespace acme
{


   extern critical_section * g_pcsGlobal;


} // namespace acme


critical_section * get_pid_cs()
{

   critical_section_lock cs(::platform::get()->globals_critical_section());

   if(g_pcsPid2 == nullptr)
   {

      g_pcsPid2 = ___new critical_section();

   }

   return g_pcsPid2;

}


string get_current_directory_name();

::file::path deduct_module_path_from_current_directory(const_char_pointer pszOptionalExecutableRelativePath)
{
	
   ::string strName(scopedstrOptionalExecutableRelativePath);
	
   if(strName.is_empty())
   {
      
      strName = ::system()->m_args[0];
      
   }
  
   auto pathCurrentFolder = get_current_directory_name();
   
   auto path = pathCurrentFolder / strName;
   
   informationf("deduct_module_path_from_current_directory (1): %s", path.c_str());
   
   if(!file_exists(path))
   {

      return {};

   }
   
   informationf("deduct_module_path_from_current_directory : OK!!: %s", path.c_str());
   
   return path;
   
}
