#pragma once


namespace sockets
{


   class link_out_socket;


   class CLASS_DECL_APEX link_in_socket : public tcp_socket
   {
   public:

      socket *             m_in;
      link_out_socket *    m_out;
      event                m_eventFinished;


      link_in_socket();
      ~link_in_socket();


      using ::sockets::tcp_socket::OnRead;
      void OnRead( char *buf, memsize n );
      void link_write(void * p, memsize size);


      static link_in_socket * from_server(httpd_socket * psocket);


      void server_to_link_in(httpd_socket * psocket);


   };

   
   using in_link_map = map < link_out_socket *, link_in_socket * >;


} // namespace sockets


