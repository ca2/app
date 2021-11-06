#pragma once


namespace simpledb
{

   
   class socket;


   class CLASS_DECL_CORE manager :
      virtual public thread
   {
   public:


      u32                         m_dwBuildTimeWindow;
      u32                         m_dwBuildTimeRandomWindow;

      string_to_string          m_strmapFunUserKey;

      string                        m_strPersistentError;

      critical_section              m_csPersistentStr;
      critical_section              m_csUiRedir;
      ::mutex                         m_mutexTagId;
      string_to_string          m_tagid;
      string_to_string          m_usersecuretagid;
      ::mutex                         m_mutexTagName;
      string_to_string          m_tagname;

      i64                       m_iDatabaseWaitTimeOut;

      ::mutex                         m_mutexSession;
      string_map < ::simpledb::session * >      m_mapSession;


      manager(::object * pobject);
      ~manager();

      
      virtual bool init_thread() override;

      ::simpledb::session * & get_session(const ::string & pszId);

      using thread::handle;
      bool handle(socket * psocket);
      bool get_output_internal(const ::string & lpcszGet, memory & memeory);

      virtual void message_queue_message_handler(::message::message * pmessage);


   };


} // namespace simpledb















