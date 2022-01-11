#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING session :
      virtual public ::object
   {
   public:


      string                                             m_strSessid;
      property_set                                       m_set;
      ::datetime::time                                   m_timeExpiry;
      __reference(::dynamic_source::script_manager)      m_pmanager;


      session();
      ~session() override;

      
#ifdef _DEBUG
      
      
      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      
#endif

      
      virtual void initialize_dynamic_source_session(const string& strId, ::dynamic_source::script_manager* pmanager);


   };


   class CLASS_DECL_APP_PROGRAMMING session_map :
      virtual public string_map < __pointer(session) >
   {
   public:


   };


} // namespace dynamic_source



