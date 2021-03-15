// cs<3tbs!! 2020-11-28 21:25 BRT
#pragma once


#include "apex/net/_net.h"


namespace net
{

   
   class address_department;


} // namespace net


#include "logger.h"
#include "trace_interface.h"


#ifdef BSD_STYLE_SOCKETS


CLASS_DECL_APEX string bsd_socket_error(i32 x);


#endif


namespace net
{


   CLASS_DECL_APEX i32 family_len(i32 family);


};


#include "sockets_base.h"


#if defined(BSD_STYLE_SOCKETS)

#include "bsd/_.h"

#if defined(LINUX)

extern "C"
CLASS_DECL_APEX const SSL_METHOD * TLS_client_method();

extern "C"
CLASS_DECL_APEX const SSL_METHOD * TLS_server_method();

#endif

#elif defined(WINRT_SOCKETS)

#include "winrt/_.h"

#else

#error "Unknown Sockets Type?"

#endif


#include "http_batch_buffer.h"


#include "transfer_socket.h"


#include "http/_.h"


#include "apex/net/ip_enum.h"
#include "apex/net/port_forward.h"


#include "websocket_client.h"


CLASS_DECL_APEX string ip_reverse(string str);


#include "apex/net/address_department.h"


#include "apex/net/_net_impl.h"



