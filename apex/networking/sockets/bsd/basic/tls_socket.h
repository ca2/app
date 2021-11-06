#pragma once


namespace sockets
{

   class CLASS_DECL_APEX tls_socket :
      virtual public tcp_socket
   {
   public:


      tls_socket();
      ~tls_socket();


      virtual void InitSSLClient();

   };



} // namespace sockets




