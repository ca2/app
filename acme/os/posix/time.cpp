#include "framework.h"
#include <time.h>


CLASS_DECL_ACME void millis_sleep(const millis & millis)
{

   struct timespec ts;
   ts.tv_sec = millis.m_iMilliseconds / 1000;
   ts.tv_nsec = (millis.m_iMilliseconds % 1000) * 1000000;
   nanosleep(&ts, NULL);

}



