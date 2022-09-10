// cs<3tbs!! 2020-11-28 21:25 BRT
#pragma once


#include "apex/networking/_networking.h"


namespace net
{

   
   class address_department;


} // namespace net


inline bool thread_has_sockets() { return task_flag().is_set(e_task_flag_using_sockets); }
//
//
//#include "logger.h"
////#include "trace_interface.h"
//

#ifdef BSD_STYLE_SOCKETS


CLASS_DECL_APEX const char * bsd_socket_error(i32 x);


#endif




//#include "sockets_base.h"


//#if defined(BSD_STYLE_SOCKETS)
//
//#include "bsd/_component.h"
//
//#if defined(LINUX) || defined(_UWP)
//
//extern "C"
//CLASS_DECL_APEX const SSL_METHOD * TLS_client_method();
//
//extern "C"
//CLASS_DECL_APEX const SSL_METHOD * TLS_server_method();
//
//#endif
//
//#elif defined(WINRT_SOCKETS)
//
//
//#include "winrt/_.h"
//
//#else
//
//#error "Unknown Sockets Type?"
//
//#endif
//
//
//#include "http_batch_buffer.h"
//
//
//#include "transfer_socket.h"

//
//#include "http/_.h"


//#include "apex/networking/ip_enum.h"
//#include "apex/networking/port_forward.h"
//
//
//#include "websocket_client.h"
//

CLASS_DECL_APEX string ip_reverse(string str);


#include "apex/networking/networking.h"


#include "apex/networking/_networking_impl.h"



