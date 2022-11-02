#include "framework.h"


CLASS_DECL_APEX void sleep(const duration & duration)
{

   usleep(duration.get_total_microseconds());

}
