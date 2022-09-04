#pragma once


#include "apex/networking/sockets/basic/socket_handler.h"


namespace netserver
{


   class CLASS_DECL_APEX socket_handler :
      virtual public ::sockets::socket_handler
   {
   public:


      socket_handler(::apex::log * plogger = nullptr);
      ~socket_handler() override;


   };


} // namespace netserver


