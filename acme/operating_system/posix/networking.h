// From windows_common/networking.h by camilo on 2025-10-02 20:49 <3ThomasBorregaardSørensen!!
#pragma once


#include <sys/socket.h>


CLASS_DECL_ACME int _open_socket(int af, int type, int protocol);
CLASS_DECL_ACME int _close_socket(int s);
CLASS_DECL_ACME int _accept_socket(int s, sockaddr* addr, int* addrlen);



