#pragma once


#include "apex/networking/sockets/base/socket_thread.h"


namespace httpd
{


   class CLASS_DECL_APEX socket_thread :
      virtual public ::sockets::socket_thread
   {
   public:


      ::pointer < ::httpd::socket >                m_psocket;

      
      socket_thread();
      ~socket_thread() override;


      void initialize_socket_thread(::sockets::base_socket* psocket) override;


      void run() override;


      //virtual ::pointer < ::sockets::socket_handler > create_socket_handler();


      void finalize() override;


   };



} // namespace httpd




