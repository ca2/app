#pragma once


#include "apex/networking/sockets/basic/listen_socket.h"


namespace netserver
{


   class CLASS_DECL_APEX socket_thread_base :
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

      __pointer(::netserver::socket_handler)       m_psockethandler;
      __pointer(::sockets::listen_socket_base)     m_plistensocket;


      socket_thread_base();
      ~socket_thread_base() override;


      virtual void     run() override;

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

         auto psocket = __create_new< ::sockets::listen_socket < SOCKET > >();

         psocket->increment_reference_count();

         //psocket->m_psockethandler = m_psockethandler;

         return psocket;

      }


   };



} // namespace netserver




