#include "framework.h"
#include <dirent.h>



int get_process_pid(const char * procNameParam)
{

   vsstring procName(procNameParam);

   int pid = -1;

   // Open the /proc directory
   DIR *dp = opendir("/proc");
   if (dp != nullptr)
   {
      // Enumerate all entries in directory until process found
      struct dirent *dirp;
      while (pid < 0 && (dirp = readdir(dp)))
      {
         // Skip non-numeric entries
         int atom = atoi(dirp->d_name);
         if (atom > 0)
         {
            // Read contents of virtual /proc/{pid}/cmdline file
            vsstring cmdPath = vsstring("/proc/") + dirp->d_name + "/cmdline";
            FILE * cmdFile = fopen(cmdPath, "rb");

            string cmdLine;

            auto estatus = fgets_string(cmdLine, cmdFile, 1024 * 256);

            if(estatus && cmdLine.has_char())
            {
               // Keep first cmdline item which contains the program path
               strsize pos = cmdLine.find('\0');
               if(pos >= 0)
                  cmdLine = cmdLine.substr(0, pos);
               // Keep program name only, removing the path
               pos = cmdLine.rear_find('/');
               if (pos >= 0)
                  cmdLine = cmdLine.substr(pos + 1);
               // compare against requested process name
               if (procName == cmdLine)
                  pid = atom;
            }
            fclose(cmdFile);
         }
      }
   }

   closedir(dp);

   return pid;

}


