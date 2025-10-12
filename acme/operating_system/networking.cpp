// Created by camilo on 2025-10-02 06:03 <3ThomasBorregaardSørensen!!
#include "framework.h"


::interlocked_count g_interlockcountOpenedSockets;


CLASS_DECL_ACME::collection::count get_count_of_opened_sockets()
{

   return g_interlockcountOpenedSockets;

}

CLASS_DECL_ACME::collection::count increment_count_of_opened_sockets()
{

   return ++g_interlockcountOpenedSockets;

}

CLASS_DECL_ACME::collection::count decrement_count_of_opened_sockets()
{

   return --g_interlockcountOpenedSockets;

}