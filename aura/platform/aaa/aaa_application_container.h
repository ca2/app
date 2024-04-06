#pragma once



class CLASS_DECL_AURA application_container :
   virtual public ::object
{
public:


   application_array             m_applicationa;

   bool                          m_bFinalizeIfNoApplicationSetting;
   bool                          m_bFinalizeIfNoApplication;

   ::aura::application *         m_pappCurrent;




   application_container();
   virtual ~application_container();


   virtual ::aura::application * application_get(const ::string & pszAppId, bool bCreate = true, bool bSynch = true, ::request * prequest = nullptr);


   virtual ::pointer<::aura::application>instantiate_application(const ::string & pszAppId, ::request * prequest);
   virtual ::pointer<::aura::application>create_application(const ::string & pszAppId, bool bSynch, ::request * prequest);
   virtual ::pointer<::aura::application>create_platform(::aura::session * psession);
   virtual ::pointer<::aura::application>start_application(const ::string & pszAppId, ::request * prequest, const ::string & strLocale, const ::string & strSchema);

   virtual void request_exit();

   application_array & applicationa();

   application_array get_applicationa();

   virtual void app_add(::aura::application * papp);
   virtual void app_erase(::aura::application * papp);


   ::pointer<::aura::application>assert_running(const ::string & pszAppId, const ::string & strLocale, const ::string & strSchema);


};
