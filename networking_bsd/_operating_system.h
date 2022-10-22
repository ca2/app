// Created by camilo on 2022-09-10 13:41 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/operating_system.h"


CLASS_DECL_NETWORKING_BSD string bsd_socket_error(int iBsdSocketError);


#ifdef WINDOWS


#include "winsock2/_.h"


#else


#include "bsd/_.h"


#endif



