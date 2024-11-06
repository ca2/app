#pragma once


#include "apex/networking/sockets/httpd/socket.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING httpd_socket :
      virtual public ::httpd::socket
   {
   public:


      int                                          m_iCa2FetchMode;
      string                                       m_strLocale;
      ::pointer < script_interface >               m_pscript;


      httpd_socket();
      ~httpd_socket() override;


      void Reset() override;


      void finalize() override;


   };


} // namespace netnode



