#pragma once


#include "acme/prototype/mathematics/scalar.h"
#include "apex/networking/sockets/basic/tcp_socket.h"
#include "apex/networking/http/request.h"
#include "apex/networking/http/response.h"
#include "apex/networking/http/listener.h"


namespace sockets
{

   class CLASS_DECL_APEX http_callback :
      virtual public ::particle
   {
   public:

      
      http_callback();
      ~http_callback() override;

      
      virtual void on_websocket_text(const ::scoped_string & scopedstrText);
      virtual void on_websocket_data(const ::block & blockData);


   };



} // namespace sockets



