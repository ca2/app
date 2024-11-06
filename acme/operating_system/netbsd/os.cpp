#include "framework.h"
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>


CLASS_DECL_ACME bool _istlead(int ch)
{

   return false;

}


//void sleep(unsigned int dwMillis)
//{
//   timespec t;
//   t.tv_sec = dwMillis / 1000;
//   t.tv_nsec = (dwMillis % 1000) * 1'000'000;
//   nanosleep(&t, nullptr);
//}


string get_current_login_name()
{

   uid_t uid = geteuid ();

   struct passwd *pw = getpwuid (uid);

   if (!pw)
   {

      return "";

   }

   return pw->pw_name;

}



