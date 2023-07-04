//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"
#include "acme/operating_system/time.h"
//#include "acme/primitive/primitive/payload.h"

//namespace acme
//{
//
//
//   void node::system_time_to_earth_time(posix_time * ptime, const system_time_t * psystemtime, i32 nDST)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   void node::time_to_system_time(system_time_t * psystemtime, const posix_time * ptime)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//} // namespace acme
//
//
//
//


void copy(payload * ppayload, const system_time_t * psystemtime)
{

   ppayload->set_type(e_type_earth_time, false);

   ppayload->set_type(e_type_time, false);

   posix_time time;

   system_time_to_earth_time(&time, psystemtime);

   ppayload->m_time.m_posixtime.m_iSecond = time;
   ppayload->m_time.m_nanosecond.m_iNanosecond = 0;

}
