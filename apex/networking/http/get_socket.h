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

      virtual void initialize_get_socket(const ::url::url & url);
      virtual void initialize_get_socket(const ::scoped_string & scopedstrProtocol, const ::scoped_string & scopedstrHost, ::networking::port_t port, const ::url::request & request);

      void OnDataArrived(const char *, memsize len) override;
      void OnHeader(atom idKey, const string & value) override;



   };


} // namespace http


