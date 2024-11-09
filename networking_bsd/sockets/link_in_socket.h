#pragma once


namespace networking_bsd
{


   class link_out_socket;


   class CLASS_DECL_NETWORKING_BSD link_in_socket : public tcp_socket
   {
   public:

      socket *             m_in;
      link_out_socket *    m_out;
      happening                m_happeningFinished;


      link_in_socket();
      ~link_in_socket();


      using ::networking_bsd::tcp_socket::OnRead;
      void OnRead( char *buf, memsize n );
      void link_write(void * p, memsize size);


      static link_in_socket * from_server(httpd_socket * psocket);


      void server_to_link_in(httpd_socket * psocket);


   };

   
   using in_link_map = map < link_out_socket *, link_in_socket * >;


} // namespace networking_bsd


