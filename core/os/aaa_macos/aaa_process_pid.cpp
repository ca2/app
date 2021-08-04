#include <sys/types.h>
#include <sys/param.h>
#define user user_struct
#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdio.h>

#include <libproc.h>


extern int ansi_count_compare(const ::string & sz1, const ::string & sz2, iptr iLen);

///************************************************************************
// *
// * Returns the pid of the process name which is given as the function
// * argument.
// * In case no process found with the given name -1 will be returned.
// *
// *************************************************************************/
///*=======================================================================*/
//int get_process_pid(const ::string & csProcessName)
//{
///*=======================================================================*/
//
//        struct kinfo_proc *sProcesses = nullptr, *sNewProcesses;
//        pid_t  iCurrentPid;
//        int    aiNames[4];
//        size_t iNamesLength;
//        int    i, iRetCode, iNumProcs;
//        size_t iSize;
//
//        iSize = 0;
//        aiNames[0] = CTL_KERN;
//        aiNames[1] = KERN_PROC;
//        aiNames[2] = KERN_PROC_ALL;
//        aiNames[3] = 0;
//        iNamesLength = 3;
//
//        iRetCode = sysctl(aiNames, (u_int) iNamesLength, nullptr, &iSize, nullptr, 0);
//
//        /*
//         * Allocate memory and populate info in the  processes structure
//         */
//
//        do {
//                iSize += iSize / 10;
//                sNewProcesses = (struct kinfo_proc *) realloc(sProcesses, iSize);
//
//                if (sNewProcesses == 0) {
//                        if (sProcesses)
//                                free(sProcesses);
//                                __throw(::exception::exception("could not reallocate memory"));
//                }
//                sProcesses = sNewProcesses;
//                iRetCode = sysctl(aiNames, (u_int) iNamesLength, sProcesses, &iSize, nullptr, 0);
//        } while (iRetCode == -1 && errno == ENOMEM);
//
//        iNumProcs = (int) (iSize / sizeof(struct kinfo_proc));
//      /*
//         * Search for the given process name and return its pid.
//         */
//
//        for (i = 0; i < iNumProcs; i++) {
//                iCurrentPid = sProcesses[i].kp_proc.p_pid;
//                if( ansi_count_compare(csProcessName, sProcesses[i].kp_proc.p_comm, MAXCOMLEN) == 0 ) {
//                        free(sProcesses);
//                        return iCurrentPid;
//                }
//        }
//
//        /*
//         * Clean up and return -1 because the given proc name was not found
//         */
//
//        free(sProcesses);
//        return (-1);
//} /* end of getProcessId() */
//

// http://stackoverflow.com/questions/3018054/retrieve-names-of-running-processes
// http://stackoverflow.com/users/115730/dave-delong
// http://stackoverflow.com/users/237188/v%C3%A1clav-slav%C3%ADk
// https://github.com/vslavik/

id_array get_pids()
{

   id_array pids;

   array < pid_t > pida;

   int numberOfProcesses = proc_listpids(PROC_ALL_PIDS, 0, nullptr, 0);

   pida.set_size(numberOfProcesses);

   proc_listpids(PROC_ALL_PIDS, 0, pida.get_data(), (int) (pida.get_size()));

   for(auto pid : pida)
   {
      if(pid == 0)
      {

         continue;

      }

      pids.add(pid);

   }

   return pids;

}


id_array module_path_get_pid(const ::string & csProcessName)
{

   id_array iaPid;

   id_array pids = get_pids();

   string strPath;

   for(auto & iCurrentPid : pids)
   {

      strPath = module_path_from_pid(iCurrentPid.i32());

      if(strPath.compare_ci(csProcessName) == 0 )
      {

         iaPid.add(iCurrentPid);

      }

   }

   return iaPid;

}


// https://astojanov.wordpress.com/2011/11/16/mac-os-x-resolve-absolute-path-using-process-pid/


string module_path_from_pid(unsigned int uiPid)
{


   pid_t pid = uiPid;

   int ret;

   char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

   ret = proc_pidpath (pid, pathbuf, sizeof(pathbuf));

   if ( ret <= 0 )
   {

      fprintf(stderr, "PID %d: proc_pidpath ();\n", pid);

      fprintf(stderr,	"    %s\n", strerror(errno));

      return "";

   }
   else
   {

      return pathbuf;

   }

}


id_array app_get_pid(const ::string & psz)
{

   id_array ia;

   id_array pids = get_pids();

   ::file::path path1;

   path1 = get_last_run_application_path_file(psz);

   if(file_exists(path1))
   {

      path1 = file_as_string(path1);

   }

   string str(psz);

   str = "app=" + str;
   
   string strApp(psz);

   strApp.replace("-", "_");

   strApp.replace("/", "_");
   
   for(auto & pid : pids)
   {

      if(pid <= 0)
      {

         continue;

      }

      ::file::path path = module_path_from_pid(pid.i32());

      if(path.title() == strApp || path == path1)
      {

         ia.add(pid);

      }
      else
      {

         string_array straCmdLine = cmdline_from_pid(pid.i32());

         string strCmdLine;

         strCmdLine = straCmdLine.implode(" ");

         if(straCmdLine.find_first(str) > 0)
         {

            ia.add(pid);

         }

      }

   }

   return ia;

}



// http://stackoverflow.com/questions/31500821/get-process-cmdline-in-mac-os-from-another-c-based-executable
// http://stackoverflow.com/users/823872/dan

#define SHOW_ZOMBIES 0

string get_cmdline(unsigned int uiPid)
{

   struct proc_taskallinfo info = {};

   //int ret = proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));

   proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));

   return info.pbsd.pbi_comm;

}


string_array cmdline_from_pid(unsigned int uiPid)
{

   string strCmdLine = get_cmdline(uiPid);

   string_array stra;

   string strArg;

   const char * psz = strCmdLine;

   string strChar;

   while(*psz != '\0')
   {

      strChar = ::str::get_utf8_char(psz);

      if(strChar.is_empty())
      {

         break;

      }

      psz += strChar.get_length();

      if(strChar == "\"")
      {

         while(*psz != '\0')
         {

            strChar = ::str::get_utf8_char(psz);

            if(strChar.is_empty())
            {

               goto end;

            }
            else if(strChar == "\"")
            {

               break;

            }

            psz += strChar.get_length();


            if(strChar == "\\")
            {

               strChar = ::str::get_utf8_char(psz);

               if(strChar.is_empty())
               {

                  goto end;

               }

               psz += strChar.get_length();

               if(strChar == "n")
               {

                  strArg += "\n";

               }
               else
               {

                  strArg += strChar;

               }

            }
            else
            {

               strArg += strChar;

            }

         }

         stra.add(strArg);

         strArg.Empty();

      }
      else if(strChar == " ")
      {

         stra.add(strArg);

         strArg.Empty();

      }
      else if(strChar == "\\")
      {

         strChar = ::str::get_utf8_char(psz);

         if(strChar.is_empty())
         {

            goto end;

         }

         psz += strChar.get_length();

         if(strChar == "n")
         {

            strArg += "\n";

         }
         else
         {

            strArg += strChar;

         }

      }
      else
      {

         strArg += strChar;

      }


   }

end:

   if(strArg.has_char())
   {

      stra.add(strArg);

   }

   return stra;

}





#include <sys/types.h>
#include <sys/param.h>
#define user user_struct
#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdio.h>



extern int ansi_count_compare(const ::string & sz1, const ::string & sz2, iptr iLen);

/************************************************************************
 *
 * Returns the pid of the process name which is given as the function
 * argument.
 * In case no process found with the given name -1 will be returned.
 *
 *************************************************************************/
/*=======================================================================*/
int get_process_pid(const ::string & csProcessName)
{
   /*=======================================================================*/

   struct kinfo_proc *sProcesses = nullptr, *sNewProcesses;
   pid_t  iCurrentPid;
   int    aiNames[4];
   size_t iNamesLength;
   int    i, iRetCode, iNumProcs;
   size_t iSize;

   iSize = 0;
   aiNames[0] = CTL_KERN;
   aiNames[1] = KERN_PROC;
   aiNames[2] = KERN_PROC_ALL;
   aiNames[3] = 0;
   iNamesLength = 3;

   iRetCode = sysctl(aiNames, (u_int) iNamesLength, nullptr, &iSize, nullptr, 0);

   if(iRetCode == -1)
   {

      return -1;

   }

   /*
    * Allocate memory and populate info in the  processes structure
    */

   do
   {
      iSize += iSize / 10;
      sNewProcesses = (struct kinfo_proc *) realloc(sProcesses, iSize);

      if (sNewProcesses == 0)
      {
         if (sProcesses)
            free(sProcesses);
         throw ::exception::exception("could not reallocate memory");
      }
      sProcesses = sNewProcesses;
      iRetCode = sysctl(aiNames, (u_int) iNamesLength, sProcesses, &iSize, nullptr, 0);
   }
   while (iRetCode == -1 && errno == ENOMEM);

   iNumProcs = (int) (iSize / sizeof(struct kinfo_proc));
   /*
    * Search for the given process name and return its pid.
    */

   for (i = 0; i < iNumProcs; i++)
   {
      iCurrentPid = sProcesses[i].kp_proc.p_pid;
      if( ansi_count_compare(csProcessName, sProcesses[i].kp_proc.p_comm, MAXCOMLEN) == 0 )
      {
         free(sProcesses);
         return iCurrentPid;
      }
   }

   /*
    * Clean up and return -1 because the given proc name was not found
    */

   free(sProcesses);
   return (-1);
} /* end of getProcessId() */


#undef user



int get_current_process_affinity_order()
{

   int numCPU = (int) (sysconf(_SC_NPROCESSORS_ONLN));

   return numCPU;
}
