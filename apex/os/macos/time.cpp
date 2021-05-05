#include "framework.h"

CLASS_DECL_APEX void sleep(unsigned int dwMillis)
{

   usleep(dwMillis * 1000);

}
