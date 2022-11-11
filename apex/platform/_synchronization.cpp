// Created by camilo on 2022-11-07 11:36 <3ThomasBorregaardSorensen!!
#include "framework.h"


static critical_section g_criticalsectionChannel;


CLASS_DECL_APEX::critical_section * channel_critical_section()
{

   return &g_criticalsectionChannel;

}


static critical_section g_criticalsectionMessageDispatch;


CLASS_DECL_APEX::critical_section * message_dispatch_critical_section()
{

   return &g_criticalsectionMessageDispatch;

}



