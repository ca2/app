#pragma once


#include "apex/networking/sockets/basic/socket_handler.h"


namespace netserver
{


   class CLASS_DECL_APEX socket_handler :
      virtual public ::sockets::socket_handler
   {
   public:


      socket_handler();
      ~socket_handler() override;

      void add(const ::sockets::socket_pointer & psocket) override;
      //void move2(::sockets::socket_pointer && psocket) override;
      void erase(const ::sockets::socket_pointer & psocket) override;
      bool contains(::sockets::base_socket *) override;


   };


} // namespace netserver


