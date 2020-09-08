#include "framework.h"


CLASS_DECL_AQUA void sleep(const duration & duration)
{

   usleep(duration.get_total_microseconds());

}
