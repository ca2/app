#pragma once


#include "acme/prototype/collection/string_map.h"

//#include "acme/prototype/prototype/payload.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING session :
      virtual public ::particle
   {
   public:


      string                                             m_strSessid;
      ::property_set                                       m_set;
      ::earth::time                                      m_timeExpiry;
      ::dynamic_source::script_manager *                 m_pmanager;


      session();
      ~session() override;

      
#ifdef _DEBUG
      
      
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
      
#endif

      
      virtual void initialize_dynamic_source_session(const ::scoped_string & scopedstrId, ::dynamic_source::script_manager* pmanager);


   };


   class CLASS_DECL_APP_PROGRAMMING session_map :
      virtual public string_map < ::pointer<session >>
   {
   public:


   };


} // namespace dynamic_source



