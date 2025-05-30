// Created by camilo on 2022-09-10 16:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "networking.h"


//#include <string.h>

#include "acme/operating_system/shared_posix/c_error_number.h"


int networking_last_error()
{

   return c_error_number().m_iErrorNumber;

}


namespace networking_bsd
{


bool networking::defer_initialize_operating_system_networking()
{

   return true;

}


bool networking::defer_finalize_operating_system_networking()
{



   return true;

}


string networking::_last_error_message(long long llError)
{

   return strerror((int) llError);

}

   long long networking::last_error()
   {

   return networking_last_error();

   }



} // namespace networking_bsd


string bsd_socket_error(int iBsdSocketError)
{

   return c_error_number({c_error_number_t{}, iBsdSocketError}).get_error_description();

}


namespace networking_bsd
{

//
//   ::pointer < ::item_array > networking::list_computers()
//   {
//
//      return {};
//
//   }
//
//
//   ::pointer < ::item_array > networking::list_network_interfaces()
//   {
//
//      return {};
//
//   }


} // namespace networking_bsd



