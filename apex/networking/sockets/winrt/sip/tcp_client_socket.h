#pragma once


namespace sockets
{


   class CLASS_DECL_APEX sip_tcp_client_socket :
      virtual public tcp_socket,
      virtual public sip_base_client_socket
   {
   public:


      sip_tcp_client_socket();


      void OnRawData(char *, memsize);
      void OnLine(const string & line);


   };


} // namespace sockets


