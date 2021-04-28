#pragma once


namespace simpledb
{


   class socket;
   class service;


   class CLASS_DECL_AURA socket_thread : 
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


      socket_thread(::object * pobject);
      virtual ~socket_thread();


      virtual bool initialize_thread() override;


      void install_message_routing(::channel * pchannel);


      DECLARE_MESSAGE_HANDLER(OnApp);


   };


} // namespace simpledb


