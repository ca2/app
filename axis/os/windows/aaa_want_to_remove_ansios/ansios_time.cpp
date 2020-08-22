#include "framework.h"


CLASS_DECL_AXIS void sleep(const duration & duration)
{

   usleep(duration.get_total_microseconds());

}
