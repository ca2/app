#pragma once


namespace dynamic_source
{


   class CLASS_DECL_PROGRAMMING session :
      virtual public ::object
   {
   public:


      string                              m_strSessid;
      property_set                        m_set;
      ::datetime::time                    m_timeExpiry;
      ::dynamic_source::script_manager *  m_pmanager;


      session(const string & strId, ::dynamic_source::script_manager * pmanager);
      virtual ~session();

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release();


   };


   class CLASS_DECL_PROGRAMMING session_map :
      virtual public strsp(session)
   {
   public:


   };


} // namespace dynamic_source




