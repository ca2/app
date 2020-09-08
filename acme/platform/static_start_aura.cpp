#include "framework.h"
#include "static_start.h"


namespace acme
{

   ::acme::acme acme::g_acme;

} // namespace acme

//#pragma comment (linker, "/export:_g_acme")

// _AURA_LINKER_FORCE_INCLUDE(g_acme);



