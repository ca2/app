#pragma once



class CLASS_DECL_AQUA application_container :
   virtual public ::object
{
public:


   application_array             m_applicationa;

   bool                          m_bFinalizeIfNoApplicationSetting;
   bool                          m_bFinalizeIfNoApplication;

   ::aqua::application *         m_pappCurrent;




   application_container();
   virtual ~application_container();


   virtual ::aqua::application * application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, ::create * pcreate = nullptr);


   virtual __pointer(::aqua::application) instantiate_application(const char * pszAppId, ::create * pcreate);
   virtual __pointer(::aqua::application) create_application(const char * pszAppId, bool bSynch, ::create * pcreate);
   virtual __pointer(::aqua::application) create_platform(::aqua::session * psession);
   virtual __pointer(::aqua::application) start_application(const char * pszAppId, ::create * pcreate, const string & strLocale, const string & strSchema);

   virtual void request_exit();

   application_array & applicationa();

   application_array get_applicationa();

   virtual void app_add(::aqua::application * papp);
   virtual void app_remove(::aqua::application * papp);


   __pointer(::aqua::application) assert_running(const char * pszAppId, const string & strLocale, const string & strSchema);


};