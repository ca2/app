#include "framework.h"
//#include "ansios.h"
#include <fcntl.h>
#ifdef FREEBSD
#define __XSI_VISIBLE 1
#endif
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










// void __end_thread_impl(acid::application*, unsigned int, bool)

// {

// }


// void __term_thread_impl(acid::application*, HINSTANCE__*)
// {
// }











void CLASS_DECL_ACID __init_thread()
{

}






void CLASS_DECL_ACID __term_thread()
{

}






