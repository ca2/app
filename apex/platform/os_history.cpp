#include "framework.h"


os_history::os_history(::object * pobject) :
   ::object(pobject)//,
   //::apex::history(pobject)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(_UWP)

   ::apex::shell_launcher launcher(nullptr, "open", psz, "", "", display_normal);

   launcher.execute();

#endif

   return true;

}


