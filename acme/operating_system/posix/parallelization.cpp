#include "framework.h"
//#include "ansios.h"
#include <fcntl.h>
//#ifdef FREEBSD
//#define __XSI_VISIBLE 1
//#endif
#include <sys/time.h>

//void __clear_mq(const ::scoped_string & scopedstrDebug, bool bClose);

namespace ansios
{

   unsigned long timeCounter()
   {
      timeval tv;
      gettimeofday(&tv, 0);
      return tv.tv_sec * 1000 + tv.tv_usec / 1000;
   }


} // namespace macos










// void __end_thread_impl(acme::application*, unsigned int, bool)

// {

// }


// void __term_thread_impl(acme::application*, HINSTANCE__*)
// {
// }











void CLASS_DECL_ACME __init_thread()
{

}






void CLASS_DECL_ACME __term_thread()
{

}








CLASS_DECL_ACME class ::time default_run_timeout()
{

   class ::time timeDefaultTimeout;

#ifdef DEBUG

   timeDefaultTimeout = 5_min;

#else

   timeDefaultTimeout = 15_s;

#endif

   return timeDefaultTimeout;

}