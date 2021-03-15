#pragma once


class ftpnet
{
public:


   string_map < __pointer(::ftp::output) > m_mapOutput;
   string_map < __pointer(::ftp::client_socket) > m_mapClient;
   ::sockets::socket_handler     m_sockethandler;



   ftpnet(::context_object * pcontextobject) :
      m_sockethandler(pobject)
   {


   }

   ~ftpnet()
   {


   }

};