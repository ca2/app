#pragma once


namespace simpledb
{

   
   class socket;


   class CLASS_DECL_AURA manager :
      virtual public thread,
      virtual public ::user::message_queue_listener
   {
   public:


      ::user::message_queue_pointer           m_spqueue;
      unsigned int                         m_dwBuildTimeWindow;
      unsigned int                         m_dwBuildTimeRandomWindow;

      string_to_string          m_strmapFunUserKey;

      string                        m_strPersistentError;

      critical_section              m_csPersistentStr;
      critical_section              m_csUiRedir;
      ::pointer < ::mutex >                         m_pmutexTagId;
      string_to_string          m_tagid;
      string_to_string          m_usersecuretagid;
      ::pointer < ::mutex >                         m_pmutexTagName;
      string_to_string          m_tagname;

      long long                       m_iDatabaseWaitTimeOut;

      ::pointer < ::mutex >                         m_pmutexSession;
      string_map < ::simpledb::session * >      m_mapSession;


      manager(::particle * pparticle);
      ~manager();

      bool initialize_thread() override;


      ::simpledb::session * & get_session(const ::scoped_string & scopedstrId);


      using thread::handle;
      bool handle(socket * psocket);
      bool get_output_internal(const ::string & lpcszGet, memory & memeory);

      virtual void message_queue_message_handler(::message::message * pmessage);


   };


} // namespace simpledb















