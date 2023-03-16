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
//   void node::system_time_to_earth_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   void node::time_to_system_time(system_time_t * psystemtime, const time_t * ptime)
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

   time_t time;

   system_time_to_earth_time(&time, psystemtime);

   ppayload->m_time.m_iSecond = time;
   ppayload->m_time.m_iNanosecond = 0;

}
