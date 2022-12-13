#include <sys/types.h>
#include <sys/param.h>
#define user user_struct
//#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdio.h>



//extern int ansi_count_compare(const ::string & sz1, const ::string & sz2, iptr iLen);
//
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
//                                throw ::exception(::exception("could not reallocate memory"));
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



//#include <sys/types.h>
//#include <sys/param.h>
//#define user user_struct
//#include <sys/user.h>
//#include <sys/sysctl.h>
//#include <stdio.h>
//
//#include <libproc.h>


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
//                                throw ::exception(::exception("could not reallocate memory"));
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

//https://stackoverflow.com/questions/9342578/how-to-get-the-active-processes-running-in-ios

#import <mach/mach.h>
#import <mach/mach_host.h>
#import <sys/sysctl.h>


atom_array get_pids()
{

   return atom_array();

//   int_array pids;
//
//   array < pid_t > pida;
//
//   memory m;
//
//   int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
//
//   u_int miblen = 4;
//
//   size_t size;
//
//   int st = sysctl(mib, miblen, nullptr, &size, nullptr, 0);
//
//   struct kinfo_proc * process = nullptr;
//
//   struct kinfo_proc * newprocess = nullptr;
//
//   do
//   {
//
//      size += size / 10;
//
//      m.set_size(size);
//
//      newprocess = (kinfo_proc *) m.get_data();
//
//      if (!newprocess)
//      {
//
//         return int_array();
//
//      }
//
//      process = newprocess;
//
//      st = sysctl(mib, miblen, process, &size, nullptr, 0);
//
//   } while (st == -1 && errno == ENOMEM);
//
//   if (st == 0)
//   {
//
//      if (size % sizeof(struct kinfo_proc) == 0)
//      {
//
//         size_t nprocess = size / sizeof(struct kinfo_proc);
//
//         if (nprocess)
//         {
//
//            for (size_t i = 0; i < nprocess; i++)
//            {
//
//               pids.add(process[i].kp_proc.p_pid);
////               NSString * processID = [[NSString alloc] initWithFormat:@"%d", process[i].kp_proc.p_pid];
////               NSString * processName = [[NSString alloc] initWithFormat:@"%s", process[i].kp_proc.p_comm];
////
////               NSDictionary * dict = [[NSDictionary alloc] initWithObjects:[NSArray arrayWithObjects:processID, processName, nil]
////                                                                   forKeys:[NSArray arrayWithObjects:@"ProcessID", @"ProcessName", nil]];
////               [array addObject:dict];
//            }
//
//         }
//
//      }
//
//   }
//
//   return pids;

}


int_array module_path_get_pid(const ::string & csProcessName)
{

   return int_array();

//   int_array iaPid;
//
//   int_array pids = get_pids();
//
//   string strPath;
//
//   for(auto iCurrentPid : pids)
//   {
//
//      strPath = module_path_from_pid(iCurrentPid);
//
//      if(strPath.case_insensitive_order(csProcessName) == 0 )
//      {
//
//         iaPid.add(iCurrentPid);
//
//      }
//
//   }
//
//   return iaPid;

}

// https://astojanov.wordpress.com/2011/11/16/mac-os-x-resolve-absolute-path-using-process-pid/


string module_path_from_pid(unsigned int uiPid)
{

   return "";
//   pid_t pid = uiPid;
//
//   int ret;
//
//   char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
//
//   ret = proc_pidpath (pid, pathbuf, sizeof(pathbuf));
//
//   if ( ret <= 0 )
//   {
//
//      fprintf(stderr, "PID %d: proc_pidpath ();\n", pid);
//
//      fprintf(stderr,   "    %s\n", strerror(errno));
//
//      return "";
//
//   }
//   else
//   {
//
//      return pathbuf;
//
//   }

}



atom_array app_get_pid(const ::string & psz)
{

   return atom_array();

}



// http://stackoverflow.com/questions/31500821/get-process-cmdline-in-mac-os-from-another-c-based-executable
// http://stackoverflow.com/users/823872/dan

#define SHOW_ZOMBIES 0

string get_cmdline(unsigned int uiPid)
{

   return "";
//   struct proc_taskallinfo info = {};
//
//   int ret = proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));
//
//   return info.pbsd.pbi_comm;

}


string_array cmdline_from_pid(unsigned int uiPid)
{

//   string strCmdLine = get_cmdline(uiPid);
//
//   string_array stra;
//
//   string strArg;
//
//   const char * psz = strCmdLine;
//
//   string strChar;
//
//   while(*psz != '\0')
//   {
//
//      strChar = ::str().get_utf8_char(psz);
//
//      if(strChar.is_empty())
//      {
//
//         break;
//
//      }
//
//      psz += strChar.get_length();
//
//      if(strChar == "\"")
//      {
//
//         while(*psz != '\0')
//         {
//
//            strChar = ::str().get_utf8_char(psz);
//
//            if(strChar.is_empty())
//            {
//
//               goto end;
//
//            }
//            else if(strChar == "\"")
//            {
//
//               break;
//
//            }
//
//            psz += strChar.get_length();
//
//
//            if(strChar == "\\")
//            {
//
//               strChar = ::str().get_utf8_char(psz);
//
//               if(strChar.is_empty())
//               {
//
//                  goto end;
//
//               }
//
//               psz += strChar.get_length();
//
//               if(strChar == "n")
//               {
//
//                  strArg += "\n";
//
//               }
//               else
//               {
//
//                  strArg += strChar;
//
//               }
//
//            }
//            else
//            {
//
//               strArg += strChar;
//
//            }
//
//         }
//
//         stra.add(strArg);
//
//         strArg.Empty();
//
//      }
//      else if(strChar == " ")
//      {
//
//         stra.add(strArg);
//
//         strArg.Empty();
//
//      }
//      else if(strChar == "\\")
//      {
//
//         strChar = ::str().get_utf8_char(psz);
//
//         if(strChar.is_empty())
//         {
//
//            goto end;
//
//         }
//
//         psz += strChar.get_length();
//
//         if(strChar == "n")
//         {
//
//            strArg += "\n";
//
//         }
//         else
//         {
//
//            strArg += strChar;
//
//         }
//
//      }
//      else
//      {
//
//         strArg += strChar;
//
//      }
//
//
//   }
//
//end:
//
//   if(strArg.has_char())
//   {
//
//      stra.add(strArg);
//
//   }
//
//   return stra;

   return string_array();

}



