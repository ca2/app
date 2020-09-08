#include "framework.h"
#include "static_start.h"


namespace acme
{

   ::acme::acme acme::g_ace;

} // namespace acme

//#pragma comment (linker, "/export:_g_ace")

// _ace_LINKER_FORCE_INCLUDE(g_ace);



