#pragma once


namespace aura
{


   class CLASS_DECL_AURA assert_running_task:
      virtual public ::thread
   {
   public:


      string                              m_strAppId;
      string                              m_strLocale;
      string                              m_strSchema;
      ::duration                          m_durationCheckPeriod;
      ::pointer<::application_container> m_pcontainer;


      assert_running_task(::application_container * pcontainer, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      virtual ~assert_running_task();


      virtual void     run() override;


   };


} // namespace aura



















