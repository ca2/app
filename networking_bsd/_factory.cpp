#include "framework.h"
#include "address.h"
#include "networking.h"
#include "apex/networking/http/message.h"
#include "sockets/basic/socket_handler.h"
#include "sockets/basic/tcp_socket.h"
#include "sockets/basic/listen_socket_impl.h"


IMPLEMENT_FACTORY(networking_bsd)
{

   pfactory->add_factory_item < ::networking_bsd::address, ::networking::address >();

   pfactory->add_factory_item < ::networking_bsd::networking, ::networking::networking >();

   pfactory->add_factory_item < ::sockets_bsd::socket_handler, ::sockets::socket_handler >();

   pfactory->add_factory_item < ::sockets_bsd::listen_socket_impl, ::sockets::listen_socket_impl >();

   pfactory->add_factory_item < ::sockets_bsd::tcp_socket, ::sockets::tcp_socket >();

   pfactory->add_factory_item < ::http::message, ::nano::http::get >();

   
}



