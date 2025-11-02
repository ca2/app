// From windows_common/networking.h by camilo on 2025-10-02 20:49 <3ThomasBorregaardSørensen!!
#pragma once


#include <sys/socket.h>


CLASS_DECL_ACME int _open_socket(int af, int type, int protocol);
CLASS_DECL_ACME int _close_socket(int s);
#if defined(__BSD__) || defined(__ANDROID__) || defined(__APPLE__) || defined(LINUX)
CLASS_DECL_ACME int _accept_socket(int s, sockaddr* addr, socklen_t* addrlen);
#else
CLASS_DECL_ACME int _accept_socket(int s, sockaddr* addr, int* addrlen);
#endif




