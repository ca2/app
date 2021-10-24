#include "framework.h"
#include <dirent.h>



i32 get_process_pid(const ::string & procNameParam)
{

   vsstring procName(procNameParam);

   i32 pid = -1;

   // Open the /proc directory
   DIR *dp = opendir("/proc");
   if (dp != nullptr)
   {
      // Enumerate all entries in directory until process found
      struct dirent *dirp;
      while (pid < 0 && (dirp = readdir(dp)))
      {
         // Skip non-numeric entries
         i32 id = atoi(dirp->d_name);
         if (id > 0)
         {
            // Read contents of virtual /proc/{pid}/cmdline file
            vsstring cmdPath = vsstring("/proc/") + dirp->d_name + "/cmdline";
            FILE * cmdFile = fopen(cmdPath, "rb");
            vsstring cmdLine;
            fgets(cmdLine.alloc(1024 * 256), 1024 * 256, cmdFile);
            if(cmdLine.has_char())
            {
               // Keep first cmdline item which contains the program path
               strsize pos = cmdLine.find('\0');
               if(pos >= 0)
                  cmdLine = cmdLine.substr(0, pos);
               // Keep program name only, removing the path
               pos = cmdLine.rfind('/');
               if (pos >= 0)
                  cmdLine = cmdLine.substr(pos + 1);
               // compare against requested process name
               if (procName == cmdLine)
                  pid = id;
            }
            fclose(cmdFile);
         }
      }
   }

   closedir(dp);

   return pid;

}


