#include "framework.h"
#include "static_start.h"


namespace acme
{

   ::acme::acme acme::g_aura;

} // namespace acme

//#pragma comment (linker, "/export:_g_aura")

// _AURA_LINKER_FORCE_INCLUDE(g_aura);



