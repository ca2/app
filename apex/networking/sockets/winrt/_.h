#pragma once


using port_t = u16;


#include "apex/networking/address.h"


#include "apex/networking/sockets/base/base_socket.h"


#include "basic/socket.h"
#include "basic/stream_socket.h"
#include "basic/sctp_socket.h"
#include "basic/tcp_socket.h"
#include "basic/udp_socket.h"


#include "basic/tls_socket.h"


#include "apex/networking/sockets/base/base_socket_handler.h"
#include "basic/socket_handler.h"
#include "basic/listen_socket.h"


#include "apex/networking/sockets/http/_.h"


//#include "webserver/webserver_ajp_base_socket.h"
//#include "webserver/webserver_ajp13_socket.h"
//#include "webserver/webserver_ajp13.h"
//#include "webserver/http_base_socket.h"
#include "webserver/httpd_socket.h"

//#include "sip/sip_base.h"
//
//#include "sip/sip_transaction.h"
//#include "sip/sip_request.h"
//#include "sip/sip_response.h"
//
//#include "sip/sip_base_client_socket.h"
//#include "sip/sip_tcp_client_socket.h"
//#include "sip/sip_udp_client_socket.h"
//#include "sip/sip_client.h"
//#include "sip/sip_server.h"


//#include "axis/net/net_email_address.h"
//#include "axis/net/net_email.h"

//#include "smtp/smtp_socket.h"
//#include "smtp/smtpd_socket.h"

//#include "timer/sockets_event_time.h"
//#include "timer/sockets_event.h"
//
//#include "timer/sockets_ievent_handler.h"
//#include "timer/sockets_ievent_owner.h"
//#include "timer/sockets_event_handler.h"

#include "asynch_dns/resolv_socket.h"
#include "asynch_dns/resolv_server.h"


#include "basic/sync_socket_handler.h"


#include "apex/networking/sockets/link_out_socket.h"
#include "apex/networking/sockets/link_in_socket.h"

//#include "sockets_link_out_socket.h"
//#include "sockets_link_in_socket.h"

#include "basic/net.h"

#include "sockets.h"

