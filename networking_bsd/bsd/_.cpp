// Created by camilo on 2022-09-10 16:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "networking.h"



::i32 networking_last_error()
{

   return errno;

}




CLASS_DECL_NETWORKING_BSD bool defer_initialize_operating_system_networking()
{


   return true;

}


CLASS_DECL_NETWORKING_BSD bool defer_finalize_operating_system_networking()
{



   return true;

}


string bsd_socket_error(int iBsdSocketError)
{

   return strerror(iBsdSocketError);

}


namespace networking_bsd{

::pointer_array < ::networking::address > networking::list_computers()
{
   
   return {};
   
}


::pointer_array < ::networking::address > networking::list_network_interfaces()
{
   
   return {};
   
}

} // namespace networking_bsd
