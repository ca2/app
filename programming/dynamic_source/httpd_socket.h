#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING httpd_socket :
      virtual public ::netserver::socket
   {
   public:


      i32                                          m_iCa2FetchMode;

      string                                       m_strLocale;

      void *                                       m_posdataNetnodeSocket;


      httpd_socket();
      virtual ~httpd_socket();


      virtual void Reset();


   };


} // namespace netnode



