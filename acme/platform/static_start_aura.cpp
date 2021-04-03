#include "framework.h"
#include "static_start.h"


namespace acme
{

   
   ::acme::static_start static_start::g_staticstart;


} // namespace acme

//#pragma comment (linker, "/export:_g_acme")

// _ACME_LINKER_FORCE_INCLUDE(g_acme);



