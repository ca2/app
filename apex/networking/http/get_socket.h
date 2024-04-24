#pragma once


#include "apex/networking/sockets/http/get_socket.h"


namespace http
{


   class CLASS_DECL_APEX get_socket : 
      virtual public ::sockets::http_get_socket
   {
   public:


      string               m_strHeaderLocation;
      ::http::cookies *    m_pcookies;

      get_socket();
      ~get_socket() override;

      virtual void initialize_get_socket(const string & url);
      virtual void initialize_get_socket(const string & host, ::networking::port_t port, const string & url);

      void OnDataArrived(const char *, memsize len) override;
      void OnHeader(atom idKey, const string & value) override;



   };


} // namespace http


