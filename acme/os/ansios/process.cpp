#include "framework.h"


#ifndef WINDOWS

CLASS_DECL_ACME int_bool is_process_running(::u32 pid)
{


   int i = kill(pid, 0);

   return (i == 0) || (i == -1 && errno == EPERM);

}


#endif