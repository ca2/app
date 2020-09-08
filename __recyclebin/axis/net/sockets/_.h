#pragma once


#include "aura/net/sockets/_.h"


#if defined(BSD_STYLE_SOCKETS)

#include "bsd/_.h"

#if defined(_UWP) || defined(LINUX)

extern "C"
CLASS_DECL_AXIS const SSL_METHOD * TLS_client_method();

extern "C"
CLASS_DECL_AXIS const SSL_METHOD * TLS_server_method();

#endif

#elif defined(_UWP)

#include "winrt/_.h"

#else

#error "Unknown Sockets Type?"

#endif


