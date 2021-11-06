#include "framework.h"
#include "idpool.h"


namespace base
{

   
   idpool* idpool::g_pthis = nullptr;


   idpool::idpool()
   {

      g_pthis = this;

   }


} // namespace base



