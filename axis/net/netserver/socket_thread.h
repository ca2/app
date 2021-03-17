#pragma once


namespace netserver
{


   class CLASS_DECL_AXIS socket_thread_base :
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


      socket_thread_base();
      virtual ~socket_thread_base();


      virtual ::e_status     run() override;

      virtual ::netserver::socket_handler * new_socket_handler();
      virtual ::sockets::listen_socket_base * new_listen_socket();

      virtual bool initialize_listen_socket();

      ::netserver::socket_handler * socket_handler();


   };


   template < typename SOCKET >
   class socket_thread :
      virtual public socket_thread_base
   {
   public:


      virtual ::sockets::listen_socket_base * new_listen_socket() override
      {

         auto psocket = new ::sockets::listen_socket < SOCKET >;

         psocket->m_phandler = m_psockethandler;

         return psocket;

      }


   };



} // namespace netserver




