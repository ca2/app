#pragma once


class ftpnet :
   virtual public object
{
public:


   string_map < ::pointer<::ftp::output >>            m_mapOutput;
   string_map < ::pointer<::ftp::client_socket >>     m_mapClient;
   ::pointer<::sockets::socket_handler>               m_psockethandler;


   ftpnet();
   virtual ~ftpnet();


   virtual void initialize(::particle * pparticle) override;


};



