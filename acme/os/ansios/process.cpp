#include "framework.h"


CLASS_DECL_ACME int_bool is_process_running(DWORD pid)
{


   int i = kill(pid, 0);

   return (i == 0) || (i == -1 && errno == EPERM);

}
