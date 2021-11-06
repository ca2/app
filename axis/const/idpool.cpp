#include "framework.h"
#include "idpool.h"


namespace axis
{


   idpool* idpool::g_pthis = nullptr;


   idpool::idpool()
   {

      g_pthis = this;

   }


} // namespace axis



