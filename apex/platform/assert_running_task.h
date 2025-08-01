#pragma once


#include "apex/parallelization/thread.h"


namespace apex
{


   class CLASS_DECL_APEX assert_running_task:
      virtual public ::thread
   {
   public:


      string                                       m_strAppId;
      string                                       m_strLocale;
      string                                       m_strSchema;
      class ::time                                 m_timeCheckPeriod;
      ::pointer<::platform::application_container>     m_pcontainer;


      assert_running_task(::platform::application_container * pcontainer,const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      ~assert_running_task() override;


      virtual void run() override;


   };


} // namespace apex



















