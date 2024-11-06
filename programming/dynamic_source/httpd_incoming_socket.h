#pragma once


#include "apex/networking/sockets/httpd/incoming_socket.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING httpd_incoming_socket :
      virtual public ::httpd::incoming_socket
   {
   public:


      int                                          m_iCa2FetchMode;

      string                                       m_strLocale;

      //::pointer < script_interface >               m_pscript;


      httpd_incoming_socket();
      ~httpd_incoming_socket() override;


      void Reset() override;


      void finalize() override;


   };


} // namespace netnode



