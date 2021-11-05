#include "framework.h"
#include "idpool.h"


namespace bred
{

   
   idpool* idpool::g_pthis = nullptr;


   idpool::idpool()
   {

      g_pthis = this;

   }


} // namespace bred



