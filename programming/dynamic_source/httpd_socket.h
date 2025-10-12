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

      class ::time                                 m_timeMainRunStart;
      class ::time                                 m_timeMainRunEnd;
      class ::time                                 m_timeWaitingToBuild;

      class ::time                                 m_timeStartHandRootPrefix;
      class ::time                                 m_timeLastHandRootPrefix;

      httpd_socket();
      ~httpd_socket() override;


      void Reset() override;


      void destroy() override;


   };


} // namespace netnode



