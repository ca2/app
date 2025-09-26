#pragma once


#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"


class ftpnet :
   virtual public object
{
public:


   string_map_base < ::pointer<::ftp::output >>            m_mapOutput;
   string_map_base < ::pointer<::ftp::client_socket >>     m_mapClient;
   ::pointer<::sockets::socket_handler>               m_psockethandler;


   ftpnet();
   virtual ~ftpnet();


   virtual void initialize(::particle * pparticle) override;


};



