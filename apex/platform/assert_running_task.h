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
      ::pointer<::acme::application_container>     m_pcontainer;


      assert_running_task(::acme::application_container * pcontainer,const ::string & strAppId, const ::string & strLocale, const ::string & strSchema);
      ~assert_running_task() override;


      virtual void run() override;


   };


} // namespace apex



















