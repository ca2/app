#pragma once


#include "apex/networking/sockets/httpd/socket_thread.h"


namespace netserver
{


   class CLASS_DECL_APEX socket_thread :
      virtual public ::httpd::socket_thread
   {
   public:


      //string                                       m_strIp;
      //int                                          m_iSsl;
      //i32                                          m_iCurrentPort;
      //i32                                          m_iPortMinimum;
      //i32                                          m_iPortMaximum;
      //i32                                          m_iConnectPort;

      //string                                       m_strCat;
      //string                                       m_strCipherList;


      ::pointer < ::sockets::socket_handler >      m_psockethandler;
      ::pointer < ::httpd::socket >                m_psocket;


      socket_thread();
      ~socket_thread() override;


      void run() override;


      virtual ::pointer < ::sockets::socket_handler > create_socket_handler();




   };



} // namespace netserver




