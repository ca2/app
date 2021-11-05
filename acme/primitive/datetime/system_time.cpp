//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"



//namespace acme
//{
//
//
//   ::e_status node::system_time_to_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
//   {
//
//      return error_interface_only;
//
//   }
//
//
//   ::e_status node::time_to_system_time(system_time_t * psystemtime, const time_t * ptime)
//   {
//
//      return error_interface_only;
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

   ppayload->set_type(e_type_time, false);

   system_time_to_time((time_t *)&ppayload->m_time.m_i, psystemtime);

}
