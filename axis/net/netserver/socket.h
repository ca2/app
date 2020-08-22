#pragma once


#include "aura/net/sockets/bsd/webserver/httpd_socket.h"



namespace netserver
{


   class CLASS_DECL_AXIS socket :
      virtual public ::sockets::httpd_socket
   {
   public:


      bool                             m_bSetCookie;

      socket(::sockets::base_socket_handler & h);
      ~socket();

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void send_response();

      virtual void on_send_response();

      virtual void simple_file_server(const char * pszPath, bool bMatter = false);

      virtual bool http_filter_response_header(id key, string_array & straValue);


   };


} // namespace netserver

