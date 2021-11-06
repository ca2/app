#include "framework.h"
#include "idpool.h"
#include "aura/platform/static_start.h"


namespace core
{


   idpool* idpool::g_pthis = nullptr;


   idpool::idpool()
   {

      g_pthis = this;

   }


} // namespace core


