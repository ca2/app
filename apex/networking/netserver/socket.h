#pragma once


#include "apex/networking/sockets/httpd/socket.h"


namespace netserver
{


   class CLASS_DECL_APEX socket :
      virtual public ::httpd::socket
   {
   public:


      socket();
      ~socket();


   };


} // namespace netserver

