#include "framework.h"
#include "acme/constant/id.h"


#include "acme/_operating_system.h"



void __node_acme_pre_init()
{


}


void CLASS_DECL_ACME __cdecl _ca2_purecall();


void __node_acme_pos_init()
{

   _set_purecall_handler(_ca2_purecall);

}


void __node_acme_pre_term()
{


}


void __node_acme_pos_term()
{

   WSACleanup();

}


CLASS_DECL_ACME string get_command_line()
{

   return GetCommandLineW();

}





