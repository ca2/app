// Created by camilo on 2022-09-10 16:52 <3ThomasBorregaardSorensen!!
#pragma once


#include <sys/socket.h>


using SOCKET = int;


#if defined(FREEBSD)


#include <netinet/in.h>


#endif


#if defined(__arm__)


#if !defined(RASPBIAN)

#include <sys/endian.h>


#endif


#include <arpa/inet.h>


#endif



