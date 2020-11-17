#include "framework.h"


CLASS_DECL_ACME void sleep(const ::duration& duration)
{

   auto millis = duration.u32_millis();

   ::Sleep(millis);

}



