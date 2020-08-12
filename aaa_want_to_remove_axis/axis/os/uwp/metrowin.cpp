#include "framework.h"

WSADATA g_wsadata;
int g_iWsaStartup;


CLASS_DECL_AXIS WSADATA get_wsadata()
{

   return g_wsadata;

}

bool __node_axis_pre_init()
{

   g_iWsaStartup = WSAStartup(0x101, &g_wsadata);

   if (g_iWsaStartup != 0)
   {

      LOG(trace_level_error, "__node_axis_pre_init") << "Failed to Initialize Windows Sockets : WSAStartup";

      return false;

   }


   return true;

}


bool __node_axis_pos_init()
{

   return true;

}


bool __node_axis_pre_term()
{

   return true;

}


bool __node_axis_pos_term()
{

   return true;

}







