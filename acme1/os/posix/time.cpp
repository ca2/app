#include "framework.h"
#include <unistd.h>


CLASS_DECL_ACME void sleep(const duration & duration)
{

   usleep((useconds_t)duration.get_total_microseconds());

}
