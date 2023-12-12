#pragma once


#include "apex/networking/netserver/socket_handler.h"
#include "apex/networking/sockets/base/socket_thread.h"
#include "apex/networking/sockets/basic/listen_socket.h"
#include "apex/parallelization/thread.h"


namespace netserver
{


   class CLASS_DECL_APEX socket_thread :
      virtual public ::thread
   {
   public:



      string                                       m_strIp;
      int                                          m_iSsl;
      i32                                          m_iCurrentPort;
      i32                                          m_iPortMinimum;
      i32                                          m_iPortMaximum;
      i32                                          m_iConnectPort;

      //SOCKET                                       m_hsocket;
      string                                       m_strCat;
      string                                       m_strCipherList;


      ::pointer<::netserver::socket_handler>       m_psockethandler;
      ::pointer<::sockets::listen_socket_base>     m_plistensocket;

      ::type_atom                                  m_typeatomSocket;


      socket_thread();
      ~socket_thread() override;


      void run() override;

      virtual ::pointer< ::netserver::socket_handler >create_socket_handler();
      virtual ::pointer<::sockets::listen_socket_base > create_listen_socket();

      virtual bool initialize_listen_socket();

      ::netserver::socket_handler * socket_handler();


   };


   //class socket_thread :
   //   virtual public socket_thread_base
   //{
   //public:


   //   ::type_atom m_typeatomSocket;

   //   virtual ::pointer<::sockets::listen_socket_base > new_listen_socket() override
   //   {

   //      auto psocket = __id_create(m_typeatomSocket);

   //      //psocket->increment_reference_count();

   //      //psocket->m_psockethandler = m_psockethandler;

   //      return psocket;

   //   }


   //};



} // namespace netserver




