// Created by camilo on 2025-10-02 06:18 <3ThomasBorregaardSørensen!!
#pragma once


#include <winsock2.h>
#include <ws2tcpip.h>


CLASS_DECL_ACME SOCKET _open_socket(int af, int type, int protocol);
CLASS_DECL_ACME int _close_socket(SOCKET s);
CLASS_DECL_ACME SOCKET _accept_socket(SOCKET s, sockaddr* addr, int* addrlen);



