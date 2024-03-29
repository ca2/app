#pragma once


#include "apex/parallelization/thread.h"


namespace httpd
{


   class CLASS_DECL_APEX incoming_socket_thread :
      virtual public ::thread
   {
   public:


      string                                       m_strIp;
      int                                          m_iSsl;
      i32                                          m_iCurrentPort;
      i32                                          m_iPortMinimum;
      i32                                          m_iPortMaximum;
      i32                                          m_iConnectPort;

      string                                       m_strCat;
      string                                       m_strCipherList;


      ::pointer < ::sockets::socket_handler >      m_psockethandlerIncoming;
      ::pointer < ::httpd::incoming_socket >       m_pincomingsocket;

      ::pointer < ::factory::factory >             m_pfactoryIncomingSocket;
      ::type_atom                                  m_typeIncomingSocket;


      incoming_socket_thread();
      ~incoming_socket_thread() override;


      void run() override;
      
      
      virtual ::pointer < ::sockets::socket_handler > create_socket_handler();


      virtual bool initialize_listen_socket();


   };



} // namespace httpd




