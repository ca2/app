#pragma once


namespace apex
{


   class CLASS_DECL_APEX assert_running_task:
      virtual public ::thread
   {
   public:


      string                                    m_strAppId;
      string                                    m_strLocale;
      string                                    m_strSchema;
      ::duration                                m_durationCheckPeriod;
      __pointer(::apex::application_container)  m_pcontainer;


      assert_running_task(::apex::application_container * pcontainer,const ::string & strAppId, const ::string & strLocale, const ::string & strSchema);
      virtual ~assert_running_task();


      virtual void     run() override;


   };


} // namespace apex



















