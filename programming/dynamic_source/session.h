#pragma once


#include "acme/primitive/collection/string_map.h"

//#include "acme/primitive/primitive/payload.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING session :
      virtual public ::particle
   {
   public:


      string                                             m_strSessid;
      property_set                                       m_set;
      ::earth::time                                   m_timeExpiry;
      ::pointer<::dynamic_source::script_manager>     m_pmanager;


      session();
      ~session() override;

      
#ifdef _DEBUG
      
      
      i64 increment_reference_count() override;
      i64 decrement_reference_count() override;
      
#endif

      
      virtual void initialize_dynamic_source_session(const string& strId, ::dynamic_source::script_manager* pmanager);


   };


   class CLASS_DECL_APP_PROGRAMMING session_map :
      virtual public string_map < ::pointer<session >>
   {
   public:


   };


} // namespace dynamic_source



