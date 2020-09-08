#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA assert_running_task:
      virtual public ::thread
   {
   public:


      string                              m_strAppId;
      string                              m_strLocale;
      string                              m_strSchema;
      ::duration                          m_durationCheckPeriod;
      __pointer(::application_container)  m_pcontainer;


      assert_running_task(::application_container * pcontainer,const string & strAppId, const string & strLocale, const string & strSchema);
      virtual ~assert_running_task();


      virtual ::estatus     run() override;


   };


} // namespace aqua



















