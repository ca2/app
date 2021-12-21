//
// Created by camilo on 2020-11-19. <3Thomas Boregaard SørensenCamilo SasukeThomas Boregaard Sørensen!! DOMAS_16-09-0.1989
//


// CLASS_DECL_ACME string xxxget_environment_variable(const char * pszEnvironmentVariable)
// {

//    string str = getenv(pszEnvironmentVariable);

//    return str;

// }





#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <wordexp.h>
#include <fcntl.h>

CLASS_DECL_ACME::e_status command_system(string& strOutput, string& strError, int& iExitCode, const char* psz, const ::duration& durationTimeout)
{
   int stdout_fds[2];
   pipe(stdout_fds);

   int stderr_fds[2];
   pipe(stderr_fds);

   fcntl( stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);
   fcntl( stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);

   string strCommandLine(psz);

   const pid_t pid = fork();
   if (!pid) {
      close(stdout_fds[0]);
      dup2(stdout_fds[1], 1);
      close(stdout_fds[1]);

      close(stderr_fds[0]);
      dup2(stderr_fds[1], 2);
      close(stderr_fds[1]);

      wordexp_t  we{};

      wordexp(strCommandLine, &we, 0);

      char ** argv = new char *[we.we_wordc+1];

      memcpy(argv, we.we_wordv, we.we_wordc * sizeof(char*));

      int iExitCode = execvp(argv[0], &argv[0]);

      delete []argv;

      wordfree(&we);

      exit(iExitCode);

   }

   close(stdout_fds[1]);


   int r, status;


   const int buf_size = 4096;

   char buffer[buf_size];

   while(true)
   {

      preempt(100_ms);

      {

         const ssize_t r = read(stdout_fds[0], buffer, buf_size);

         if (r > 0)
         {

            strOutput += string(buffer, r);

         }

      }

      {

         const ssize_t r = read(stderr_fds[0], buffer, buf_size);

         if (r > 0)
         {

            strError += string(buffer, r);

         }

      }

      {

         r = waitpid(pid, &status, 0);

         int iError = errno;

         if(r != -1 || iError != EINTR)
         {

            break;

         }

      }

   };

   close(stdout_fds[0]);

   close(stderr_fds[1]);

   close(stderr_fds[0]);

   return ::success;

}
