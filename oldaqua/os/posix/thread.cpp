#include "framework.h"
//#include "ansios.h"
#include <fcntl.h>
#include <sys/time.h>

//void __clear_mq(const char * pszDebug, bool bClose);

namespace ansios
{

   unsigned long MillisecondCounter()
   {
      timeval tv;
      gettimeofday(&tv, 0);
      return tv.tv_sec * 1000 + tv.tv_usec / 1000;
   }


} // namespace macos










// void __end_thread_impl(aqua::application*, unsigned int, bool)

// {

// }


// void __term_thread_impl(aqua::application*, HINSTANCE__*)
// {
// }











void CLASS_DECL_AQUA __init_thread()
{

}






void CLASS_DECL_AQUA __term_thread()
{

}






