// Created by camilo on 2025-10-02 06:18 <3ThomasBorregaardSørensen!!
#pragma once


#include <winsock2.h>
#include <ws2tcpip.h>


CLASS_DECL_ACME SOCKET _open_socket(::i32 af, ::i32 type, ::i32 protocol);
CLASS_DECL_ACME ::i32 _close_socket(SOCKET s);
CLASS_DECL_ACME SOCKET _accept_socket(SOCKET s, sockaddr* addr, ::i32* addrlen);



