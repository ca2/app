#pragma once


namespace netserver
{


   class CLASS_DECL_BASE socket_thread :
      virtual public ::thread
   {
   public:



      string                                       m_strIp;
      i32                                          m_iPort;
      int                                          m_iSsl;

      SOCKET                                       m_hsocket;
      string                                       m_strCat;
      string                                       m_strCipherList;

      __pointer(::netserver::socket_handler)       m_psockethandler;
      __pointer(::sockets::listen_socket_base)     m_plistensocket;


      socket_thread();
      virtual ~socket_thread();


      virtual ::estatus     run() override;

      virtual ::netserver::socket_handler * create_socket_handler();
      virtual ::sockets::listen_socket_base * create_listen_socket();

      virtual bool initialize_listen_socket();

      ::netserver::socket_handler * socket_handler();


   };


} // namespace netserver




