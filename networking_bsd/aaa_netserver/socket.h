#pragma once


#include "apex/networking/sockets/bsd/webserver/httpd_socket.h"


namespace netserver
{


   class CLASS_DECL_APEX socket :
      virtual public ::sockets::httpd_socket
   {
   public:


      bool                             m_bSetCookie;

      socket();
      ~socket();

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void send_response();

      virtual void on_send_response();

      virtual void simple_file_server(const ::string & pszPath, bool bMatter = false);

      virtual bool http_filter_response_header(atom key, string_array & straValue);


   };


} // namespace netserver

