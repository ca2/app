#pragma once


#include "apex/networking/netserver/socket.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING httpd_socket :
      virtual public ::netserver::socket
   {
   public:


      i32                                          m_iCa2FetchMode;

      string                                       m_strLocale;

      ::pointer < script_interface >               m_pscript;
      //void *                                       m_posdataNetnodeSocket;


      httpd_socket();
      ~httpd_socket() override;


      virtual void Reset();


   };


} // namespace netnode



