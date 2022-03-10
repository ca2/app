//
// Created by camilo on 2020-11-19. <3Thomas Boregaard SørensenCamilo SasukeThomas Boregaard Sørensen!! DOMAS_16-09-0.1989
//
#include "framework.h"
// CLASS_DECL_ACME string xxxget_environment_variable(const char * pszEnvironmentVariable)
// {

//    string str = getenv(pszEnvironmentVariable);

//    return str;

// }
#include <sys/wait.h>
#include <unistd.h>
#include <wordexp.h>
#include <fcntl.h>


void command_system(string& strOutput, string& strError, int& iExitCode, const char* psz, enum_command_system ecommandsystem, const ::duration& durationTimeout)
{

   ::e_status estatus = success;

   int stdout_fds[2] = {};

   int iError = pipe(stdout_fds);

   if(iError != 0)
   {

      int iErrNo = errno;

      estatus = errno_to_status(iErrNo);

      throw ::exception(estatus);

   }

   int stderr_fds[2] = {};

   iError = pipe(stderr_fds);

   if(iError != 0)
   {

      int iErrNo = errno;

      estatus = errno_to_status(iErrNo);

      throw ::exception(estatus);

   }

   auto pszCommandLine = strdup(psz);

   const pid_t pid = fork();

   if (!pid)
   {

      while((dup2(stdout_fds[1], STDOUT_FILENO) == -1) && (errno==EINTR)){}
      while((dup2(stderr_fds[1], STDERR_FILENO) == -1) && (errno==EINTR)){}

      close(stdout_fds[0]);
      close(stdout_fds[1]);
      close(stderr_fds[0]);
      close(stderr_fds[1]);


      sleep(20);

      wordexp_t we{};

      wordexp(pszCommandLine, &we, 0);

      char ** argv = new char *[we.we_wordc+1];

      memcpy(argv, we.we_wordv, we.we_wordc * sizeof(char*));

      int iErrNo = 0;

      int iChildExitCode = execvp(argv[0], &argv[0]);

      if(iChildExitCode == -1)
      {

         iErrNo = errno;

      }

      delete []argv;

      wordfree(&we);

      free(pszCommandLine);

      _exit(iErrNo);

   }

   close(stdout_fds[1]);
   close(stderr_fds[1]);

   fcntl( stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);
   fcntl( stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);

   const int buf_size = 4096;

   char buffer[buf_size];

   char chExitCode = 0;

   while(true)
   {

      bool bRead = false;

      while(true)
      {

         const ssize_t iOutRead = read(stdout_fds[0], buffer, buf_size);

         if (iOutRead > 0)
         {

            bRead = true;

            string strMessage(buffer, iOutRead);

            strOutput += strMessage;

            if(ecommandsystem & e_command_system_inline_log)
            {

               printf("%s", strMessage.c_str());

            }

         }

         const ssize_t iErrRead = read(stderr_fds[0], buffer, buf_size);

         if (iErrRead > 0)
         {

            bRead = true;

            string strMessage(buffer, iErrRead);

            strError += strMessage;

            if(ecommandsystem & e_command_system_inline_log)
            {

               fprintf(stderr, "%s", strMessage.c_str());

            }

         }

         if(iOutRead > 0 || iErrRead > 0)
         {

            bRead = true;

         }
         else
         {

            break;

         }

      }

      {

         int status = 0;

         int iWaitPid = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

         if(iWaitPid == -1)
         {

            int iErrorNo = errno;

            if(iErrorNo != ECHILD)
            {

               // No child with specified pid

               break;

            }

         }
         else if(iWaitPid == pid)
         {

            if (WIFEXITED(status))
            {

               chExitCode = WEXITSTATUS(status);

               iExitCode = chExitCode;

               break;

            }

         }

      }

      if(!bRead)
      {

         preempt(25_ms);

      }

   }

   close(stdout_fds[0]);

   close(stderr_fds[0]);

   if(iExitCode != 0)
   {

      auto estatus = failed_errno_to_status(iExitCode);

      throw ::exception(estatus);

   }

   //return ::success;

}



