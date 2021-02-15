//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"



namespace acme
{


   time_t node::system_time_to_time(const system_time_t &systemtime, i32 nDST)
   {

      __throw(interface_only_exception());

      return 0;

   }


   system_time_t node::time_to_system_time(const ::datetime::time & time)
   {

      __throw(interface_only_exception());

      return {};

   }


} // namespace acme






void copy(payload * ppayload, const system_time_t * psystemtime)
{

   ppayload->set_type(type_time, false);

   auto pnode = Node;

   ppayload->m_time = pnode->system_time_to_time(*psystemtime);

}
