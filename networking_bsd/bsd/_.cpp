// Created by camilo on 2022-09-10 16:51 <3ThomasBorregaardSørensen!!
#include "framework.h"
// #include "acme/primitive/string/string.h"


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
