//
//  apple_debug.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 06/01/18.
//
#include "debug.h"
#include "ns_exception.h"

void throw_ns_exception(enum_status estatus, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrDescription, const ::property_set & setUserInfo)
{

   throw ns_exception(estatus, scopedstrName, scopedstrDescription, setUserInfo);

}


#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
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




//void output_debug_string(const ::scoped_string & scopedstrOutputString)
//{
//   
////   if(scopedstrOutputString.size() > 1024)
////   {
////   
////      fwrite(scopedstrOutputString.begin(), 1, 128, stdout);
////      
////      if(scopedstrOutputString[scopedstrOutputString.size() -1] =='\n')
////      {
////         
////         printf("...line with %llid bytes truncated to 128 bytes...", scopedstrOutputString.size() );
////         
////      }
////      
////      fwrite("\n", 1, 1, stdout);
////      
////   }
////   else
//   {
//      fwrite(scopedstrOutputString.begin(), 1, scopedstrOutputString.size(), stdout);
//   }
//
////   string strOutputString(scopedstrOutputString);
////
////   strOutputString.find_replace("\r\n", "\n");
////
////   strOutputString.find_replace("\n", "\r");
////
////   ::wd32_character * pusz = ansi_to_wd32_dup(strOutputString);
////
////   wprintf(L"%S", pusz);
////
////   ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pusz);
//
//}
//
//
//void output_debug_string_flush()
//{
//   
//   fflush(stdout);
//   
//}
//
//
