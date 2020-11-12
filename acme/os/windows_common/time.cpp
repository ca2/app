#include "framework.h"


CLASS_DECL_ACME void sleep(const ::duration& dur)
{

   Sleep((::u32)dur.total_milliseconds());

}



