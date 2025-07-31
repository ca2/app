#pragma once


#include "apex/networking/sockets/httpd/incoming_socket.h"


namespace netserver
{


   class CLASS_DECL_APEX incoming_socket :
      virtual public ::httpd::incoming_socket
   {
   public:


      //bool                             m_bSetCookie;

      
      incoming_socket();
      ~incoming_socket();


      //virtual void OnExecute();
      //virtual void OnResponseComplete();

      //virtual void send_response();

      //virtual void on_send_response();

      //virtual void simple_file_server(const ::scoped_string & scopedstrPath, bool bMatter = false);

      //virtual bool http_filter_response_header(atom key, string_array & straValue);


   };


} // namespace netserver

