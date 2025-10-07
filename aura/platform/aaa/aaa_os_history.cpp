#include "framework.h"


os_history::os_history(::particle * pparticle) :
   ::object(pparticle)//,
   //::aura::history(pparticle)
{
}


bool os_history::hist(const ::scoped_string & scopedstr)
{

#if !defined(UNIVERSAL_WINDOWS)

   ::aura::shell_launcher launcher(nullptr, "open", psz, "", "", e_display_normal);

   launcher.execute();

#endif

   return true;

}


