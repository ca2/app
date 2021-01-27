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


      session(const string & strId, ::dynamic_source::script_manager * pmanager);
      virtual ~session();

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);


   };


   class CLASS_DECL_APP_PROGRAMMING session_map :
      virtual public string_map < __pointer(session) >
   {
   public:


   };


} // namespace dynamic_source




