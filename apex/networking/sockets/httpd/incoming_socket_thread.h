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
      int                                          m_iCurrentPort;
      int                                          m_iPortMinimum;
      int                                          m_iPortMaximum;
      int                                          m_iConnectPort;

      string                                       m_strCat;
      string                                       m_strCipherList;


      ::pointer < ::sockets::socket_handler >      m_psockethandlerIncoming;
      ::pointer < ::httpd::incoming_socket >       m_pincomingsocket;

      ::pointer < ::factory::factory >             m_pfactoryIncomingSocket;
      ::type_atom                                  m_typeIncomingSocket;


      incoming_socket_thread();
      ~incoming_socket_thread() override;


      void run() override;


      void destroy() override;
      
      
      virtual ::pointer < ::sockets::socket_handler > create_socket_handler();


      virtual bool initialize_listen_socket();


   };



} // namespace httpd




