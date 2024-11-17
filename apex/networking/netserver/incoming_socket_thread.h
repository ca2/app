#pragma once


#include "apex/networking/netserver/socket_handler.h"
#include "apex/networking/sockets/httpd/incoming_socket_thread.h"
#include "apex/networking/sockets/base/socket_thread.h"
#include "apex/networking/sockets/basic/listen_socket.h"
#include "apex/parallelization/thread.h"


namespace netserver
{


   class CLASS_DECL_APEX incoming_socket_thread :
      virtual public ::httpd::incoming_socket_thread
   {
   public:



      //string                                       m_strIp;
      //int                                          m_iSsl;
      //int                                          m_iCurrentPort;
      //int                                          m_iPortMinimum;
      //int                                          m_iPortMaximum;
      //int                                          m_iConnectPort;

      ////SOCKET                                     m_hsocket;
      //string                                       m_strCat;
      //string                                       m_strCipherList;


      //::pointer < ::netserver::socket_handler >    m_psockethandlerIncoming;
      //::pointer < ::httpd::incoming_socket >       m_pincomingsocket;

      //::type_atom                                  m_typeIncomingSocket;


      incoming_socket_thread();
      ~incoming_socket_thread() override;


      void run() override;

      ::pointer < ::sockets::socket_handler > create_socket_handler() override;
      //virtual ::pointer < ::sockets::listen_socket > create_listen_socket();
      bool initialize_listen_socket() override;

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




