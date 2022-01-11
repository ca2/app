#pragma once


class ftpnet :
   virtual public object
{
public:


   string_map < __pointer(::ftp::output) >            m_mapOutput;
   string_map < __pointer(::ftp::client_socket) >     m_mapClient;
   __pointer(::sockets::socket_handler)               m_psockethandler;


   ftpnet();
   virtual ~ftpnet();


   virtual void initialize(::object * pobject) override;


};



