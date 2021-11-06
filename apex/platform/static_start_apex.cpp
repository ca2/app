#include "framework.h"
#include "static_start.h"




namespace apex
{

   static_start static_start::g_staticstart;

} // namespace apex

//#pragma comment (linker, "/export:_g_apex")

// _APEX_LINKER_FORCE_INCLUDE(g_apex);



