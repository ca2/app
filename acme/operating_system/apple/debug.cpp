//
//  apple_debug.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/01/18.
//
#include "debug.h"
#include "ns_exception.h"

void throw_ns_exception(enum_status estatus, const char * pszName, const char * pszDescription, const property_set & setUserInfo)
{

   throw ns_exception(estatus, pszName, pszDescription, setUserInfo);

}


#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

#define user user_struct
#include <sys/sysctl.h>

int __node_is_debugger_attached()
// Returns true if the current process is being debugged (either
// running under the debugger or has a debugger attached post facto).
{
   int                 junk;
   int                 mib[4];
   struct kinfo_proc   info;
   size_t              size;

   // Initialize the flags so that, if sysctl fails for some bizarre
   // reason, we get a predictable result.

   info.kp_proc.p_flag = 0;

   // Initialize mib, which tells sysctl the info we want, in this case
   // we're looking for information about a specific process ID.

   mib[0] = CTL_KERN;
   mib[1] = KERN_PROC;
   mib[2] = KERN_PROC_PID;
   mib[3] = getpid();

   // Call sysctl.

   size = sizeof(info);
   junk = sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, nullptr, 0);
   assert(junk == 0);

   // We're being debugged if the P_TRACED flag is set.

   return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
}




void output_debug_string(const char * pszOutputString)
{
   
   printf("%s", pszOutputString);

//   string strOutputString(pszOutputString);
//
//   strOutputString.find_replace("\r\n", "\n");
//
//   strOutputString.find_replace("\n", "\r");
//
//   wd32char * pusz = ansi_to_wd32_dup(strOutputString);
//
//   wprintf(L"%S", pusz);
//
//   memory_free(pusz);

}
