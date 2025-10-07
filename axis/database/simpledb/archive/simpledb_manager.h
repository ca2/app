#pragma once


namespace simpledb
{

   
   class socket;


   class CLASS_DECL_CORE manager :
      virtual public thread
   {
   public:


      unsigned int                         m_dwBuildTimeWindow;
      unsigned int                         m_dwBuildTimeRandomWindow;

      string_to_string_base          m_strmapFunUserKey;

      string                        m_strPersistentError;

      critical_section              m_csPersistentStr;
      critical_section              m_csUiRedir;
      ::pointer < ::mutex >                         m_pmutexTagId;
      string_to_string_base          m_tagid;
      string_to_string_base          m_usersecuretagid;
      ::pointer < ::mutex >                         m_pmutexTagName;
      string_to_string_base          m_tagname;

      long long                       m_iDatabaseWaitTimeOut;

      ::pointer < ::mutex >                         m_pmutexSession;
      string_map_base < ::simpledb::session * >      m_mapSession;


      manager(::particle * pparticle);
      ~manager();

      
      virtual bool init_thread() override;

      ::simpledb::session * & get_session(const ::scoped_string & scopedstrId);

      using thread::handle;
      bool handle(socket * psocket);
      bool get_output_internal(const ::scoped_string & scopedstrGet, memory & memeory);

      virtual void message_queue_message_handler(::message::message * pmessage);


   };


} // namespace simpledb















