#include "framework.h"


CLASS_DECL_ACME void sleep(const ::duration& duration)
{

   auto millis = duration.u32_millis();

   ::millis_sleep(millis);

}





CLASS_DECL_ACME void secs_sleep(const ::secs & secs)
{

   ::Sleep((DWORD) (secs.m_iSeconds * 1'000));

}


CLASS_DECL_ACME void millis_sleep(const millis & millis)
{

   ::Sleep((DWORD) millis.m_iMilliseconds);

}


CLASS_DECL_ACME void micros_sleep(const micros & micros)
{

   ::Sleep(1);

}


CLASS_DECL_ACME void nanos_sleep(const nanos & nanos)
{

   ::Sleep(1);

}



