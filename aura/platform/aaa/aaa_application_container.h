#pragma once



class CLASS_DECL_AURA application_container :
   virtual public ::object
{
public:


   application_array             m_applicationa;

   bool                          m_bFinalizeIfNoApplicationSetting;
   bool                          m_bFinalizeIfNoApplication;

   ::aura::application *         m_papplicationCurrent;




   application_container();
   virtual ~application_container();


   virtual ::aura::application * application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, ::create * pcreate = nullptr);


   virtual __pointer(::aura::application) instantiate_application(const char * pszAppId, ::create * pcreate);
   virtual __pointer(::aura::application) create_application(const char * pszAppId, bool bSynch, ::create * pcreate);
   virtual __pointer(::aura::application) create_platform(::aura::session * psession);
   virtual __pointer(::aura::application) start_application(const char * pszAppId, ::create * pcreate, const string & strLocale, const string & strSchema);

   virtual void request_exit();

   application_array & applicationa();

   application_array get_applicationa();

   virtual void app_add(::aura::application * papp);
   virtual void app_erase(::aura::application * papp);


   __pointer(::aura::application) assert_running(const char * pszAppId, const string & strLocale, const string & strSchema);


};