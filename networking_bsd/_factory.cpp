#include "framework.h"
#include "address.h"
#include "networking.h"
#include "sockets/basic/socket_handler.h"
#include "sockets/basic/tcp_socket.h"
#include "sockets/basic/listen_socket.h"


__FACTORY_EXPORT void networking_bsd_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::networking_bsd::address, ::networking::address >();

   pfactory->add_factory_item < ::networking_bsd::networking, ::networking::networking >();

   pfactory->add_factory_item < ::sockets_bsd::socket_handler, ::sockets::socket_handler >();

   pfactory->add_factory_item < ::sockets_bsd::listen_socket, ::sockets::listen_socket_base >();

   pfactory->add_factory_item < ::sockets_bsd::tcp_socket, ::sockets::tcp_socket >();

   
}



