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

   ::e_status3 estatus = success;

   int stdout_fds[2] = {};

   int iError = pipe(stdout_fds);

   if(iError != 0)
   {

      int iErrNo = errno;

      estatus = errno_to_status(iErrNo);

      return estatus;

   }

   int stderr_fds[2] = {};

   iError = pipe(stderr_fds);

   if(iError != 0)
   {

      int iErrNo = errno;

      estatus = errno_to_status(iErrNo);

      return estatus;

   }

   string strCommandLine(psz);

   const pid_t pid = fork();

   if (!pid)
   {

      while((dup2(stdout_fds[1], STDOUT_FILENO) == -1) && (errno==EINTR)){}
      while((dup2(stderr_fds[1], STDERR_FILENO) == -1) && (errno==EINTR)){}

      close(stdout_fds[0]);
      close(stdout_fds[1]);
      close(stderr_fds[0]);
      close(stderr_fds[1]);


      //sleep(20);

      wordexp_t we{};

      wordexp(strCommandLine, &we, 0);

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

      {

         int status = 0;

         int iWaitPid = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

         if(iWaitPid == -1)
         {

            int iErrorNo = errno;

            if(iErrorNo != ECHILD)
            {

               break;
               // No child with specified pid

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


      preempt(100_ms);

      {

         const ssize_t iOutRead = read(stdout_fds[0], buffer, buf_size);

         if (iOutRead > 0)
         {

            string strMessage(buffer, iOutRead);

            strOutput += strMessage;

            if(ecommandsystem & e_command_system_inline_log)
            {

               printf("%s", strMessage.c_str());

            }

         }

      }

      {

         const ssize_t iErrRead = read(stderr_fds[0], buffer, buf_size);

         if (iErrRead > 0)
         {

            string strMessage(buffer, iErrRead);

            strError += strMessage;

            if(ecommandsystem & e_command_system_inline_log)
            {

               fprintf(stderr, "%s", strMessage.c_str());

            }

         }

      }


   }

   close(stdout_fds[0]);

   close(stderr_fds[0]);

   if(iExitCode != 0)
   {

      auto estatus = failed_errno_to_status(iExitCode);

      return estatus;

   }

   return ::success;

}



