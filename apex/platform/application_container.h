#pragma once



class CLASS_DECL_APEX application_container :
   virtual public ::object
{
public:


   application_array                m_applicationa;

   bool                             m_bFinalizeIfNoApplicationSetting;
   bool                             m_bFinalizeIfNoApplication;

   __pointer(::apex::application)   m_papplicationCurrent;




   application_container();
   virtual ~application_container();


   virtual ::apex::application * application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, ::create * pcreate = nullptr);


   virtual __pointer(::apex::application) instantiate_application(const char * pszAppId, ::create * pcreate);
   virtual __pointer(::apex::application) create_application(const char * pszAppId, bool bSynch, ::create * pcreate);
   virtual __pointer(::apex::application) create_platform(::apex::session * psession);
   virtual __pointer(::apex::application) start_application(const char * pszAppId, ::create * pcreate, const string & strLocale, const string & strSchema);

   virtual void request_exit();

   application_array & applicationa();

   application_array get_applicationa();

   virtual void app_add(::apex::application * papp);
   virtual void app_remove(::apex::application * papp);


   __pointer(::apex::application) assert_running(const char * pszAppId, const string & strLocale, const string & strSchema);


   virtual void on_instantiate_application(::apex::application* papp);


};