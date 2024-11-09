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
      int                     m_iPort;

      ::happening                 m_happeningCanInit;
      ::happening                 m_happeningInitialized;
      bool                    m_bInitialized;

#ifdef BSD_STYLE_SOCKETS

      SOCKET                  m_hsocket;

#endif

      socket *                m_psocket;


      socket_thread(::particle * pparticle);
      virtual ~socket_thread();


      virtual bool init_thread() override;


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(OnApp);


   };


} // namespace simpledb


