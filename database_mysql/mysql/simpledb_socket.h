#pragma once


namespace simpledb
{


   class manager;
   class session;
   class socket_thread;

   class socket : 
      public ::sockets::httpd_socket
   {
   public:


      string                        m_strLocale;
      ::simpledb::session *         m_psession;
      socket_thread *               m_pthreadParent;


      socket();
      virtual ~socket();

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void OnSSLAccept();

      void send_response();

      class manager & manager();

      virtual void simple_file_server(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrRelative = nullptr);
      virtual bool read_file(const ::scoped_string & scopedstr, pointer_array < ::int_array > * prangea = nullptr, const ::scoped_string & scopedstrContentType = nullptr);

      //virtual bool http_filter_response_header(atom key, string & strValue);
   };



} // namespace simpledb
