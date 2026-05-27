// From windows_common/networking.h by camilo on 2025-10-02 20:49 <3ThomasBorregaardSørensen!!
#pragma once


#include <sys/socket.h>


CLASS_DECL_ACME ::i32 _open_socket(::i32 af, ::i32 type, ::i32 protocol);
CLASS_DECL_ACME ::i32 _close_socket(::i32 s);
#if defined(__BSD__) || defined(__ANDROID__) || defined(__APPLE__) || defined(LINUX)
CLASS_DECL_ACME ::i32 _accept_socket(::i32 s, sockaddr* addr, socklen_t* addrlen);
#else
CLASS_DECL_ACME ::i32 _accept_socket(::i32 s, sockaddr* addr, ::i32* addrlen);
#endif




