#include "framework.h"


CLASS_DECL_ACME void sleep(const ::duration& dur)
{

   Sleep((DWORD)dur.total_milliseconds());

}



