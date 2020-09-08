#include "framework.h"


os_history::os_history(::generic * pobject) //:
   //::generic(pobject)//,
   //::acme::history(pobject)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(_UWP)

   ::acme::shell_launcher launcher(nullptr, "open", psz, "", "", display_normal);

   launcher.execute();

#endif

   return true;

}


