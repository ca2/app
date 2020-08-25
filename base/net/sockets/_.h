#pragma once


#include "logger.h"
#include "trace_interface.h"





namespace net
{


   CLASS_DECL_BASE i32 family_len(i32 family);


};


#include "sockets_base.h"



#if defined(BSD_STYLE_SOCKETS)

#include "bsd/_.h"

#if defined(_UWP) || defined(LINUX)

extern "C"
CLASS_DECL_BASE const SSL_METHOD * TLS_client_method();

extern "C"
CLASS_DECL_BASE const SSL_METHOD * TLS_server_method();

#endif

#elif defined(_UWP)

#include "winrt/_.h"

#else

#error "Unknown Sockets Type?"

#endif


#include "http_batch_buffer.h"


#include "transfer_socket.h"


#include "http/_.h"


#include "aura/net/ip_enum.h"
#include "aura/net/port_forward.h"


#include "websocket_client.h"



CLASS_DECL_BASE string ip_reverse(string str);