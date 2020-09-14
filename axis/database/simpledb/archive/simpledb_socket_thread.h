#pragma once


#include "aura/net/sockets/bsd/basic/sockets_socket_handler.h"


namespace simpledb
{


   class socket;
   class service;


   class CLASS_DECL_CORE socket_thread :
      public thread,
      public ::sockets::socket_handler
   {
   public:


      HANDLE                  m_hChildThreadId;

#ifdef WINDOWS_DESKTOP

      PROCESS_INFORMATION     m_pi;

#endif

      service *               m_pservice;

      string                  m_strIp;
      i32                     m_iPort;

      ::event                 m_evCanInit;
      ::event                 m_evInitialized;
      bool                    m_bInitialized;

#ifdef BSD_STYLE_SOCKETS

      SOCKET                  m_hsocket;

#endif

      socket *                m_psocket;


      socket_thread(::layered * pobjectContext);
      virtual ~socket_thread();


      virtual bool init_thread() override;


      void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(OnApp);


   };


} // namespace simpledb


