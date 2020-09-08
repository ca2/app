#pragma once



class CLASS_DECL_ACME application_container :
   virtual public ::generic
{
public:


   application_array             m_applicationa;

   bool                          m_bFinalizeIfNoApplicationSetting;
   bool                          m_bFinalizeIfNoApplication;

   ::acme::application *         m_pappCurrent;




   application_container();
   virtual ~application_container();


   virtual ::acme::application * application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, ::create * pcreate = nullptr);


   virtual __pointer(::acme::application) instantiate_application(const char * pszAppId, ::create * pcreate);
   virtual __pointer(::acme::application) create_application(const char * pszAppId, bool bSynch, ::create * pcreate);
   virtual __pointer(::acme::application) create_platform(::acme::session * psession);
   virtual __pointer(::acme::application) start_application(const char * pszAppId, ::create * pcreate, const string & strLocale, const string & strSchema);

   virtual void request_exit();

   application_array & applicationa();

   application_array get_applicationa();

   virtual void app_add(::acme::application * papp);
   virtual void app_remove(::acme::application * papp);


   __pointer(::acme::application) assert_running(const char * pszAppId, const string & strLocale, const string & strSchema);


};