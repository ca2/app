#pragma once


class CLASS_DECL_APEX application_container :
   virtual public ::application_exit
{
public:



   application_array                m_applicationa;

   bool                             m_bFinalizeIfNoApplicationSetting;
   bool                             m_bFinalizeIfNoApplication;

   __pointer(::application)   m_papplicationCurrent;




   application_container();
   virtual ~application_container();


   virtual ::application * application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, ::create * pcreate = nullptr);


   virtual __pointer(::application) instantiate_application(const char * pszAppId, ::create * pcreate);
   virtual __pointer(::application) create_application(const char * pszAppId, bool bSynch, ::create * pcreate);
   virtual __pointer(::application) create_platform(::apex::session * psession);
   virtual __pointer(::application) start_application(const char * pszAppId, ::create * pcreate, const ::string & strLocale, const ::string & strSchema);


   virtual ::e_status exit_application();


   application_array & applicationa();

   application_array get_applicationa();

   virtual void add_application(::application * papp);
   virtual void erase_application(::application * papp);


   __pointer(::application) assert_running(const char * pszAppId, const ::string & strLocale, const ::string & strSchema);


   virtual void on_instantiate_application(::application* papp);


};
