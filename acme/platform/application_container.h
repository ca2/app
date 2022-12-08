#pragma once


#include "application_exit.h"
#include "application_array.h"


namespace acme
{


   class CLASS_DECL_ACME application_container :
      virtual public ::application_exit
   {
   public:



      application_array                m_applicationa;

      bool                             m_bFinalizeIfNoApplicationSetting;
      bool                             m_bFinalizeIfNoApplication;

      ::pointer<::apex::application>  m_pappCurrent;




      application_container();
      ~application_container() override;


      virtual ::acme::application * get_application(const ::string & strAppId, bool bCreate = true, ::request * prequest = nullptr);


      //virtual ::pointer<::apex::application>create_application(const char * pszAppId, bool bSynch, ::request * prequest);
      //virtual ::pointer<::apex::application>create_platform(::apex::session * psession);
      
      
      virtual ::pointer<::acme::application > instantiate_application(const::string& strAppIdd);
      virtual ::pointer<::acme::application > create_application(const ::string & strAppId, ::request * prequest);


      virtual void exit_application();


      application_array & applicationa();

      application_array get_applicationa();

      virtual void add_application(::acme::application * papplication);
      virtual void erase_application(::acme::application * papplication);


      ::pointer<::acme::application>assert_running(const ::string & strAppId);


      virtual void on_instantiate_application(::acme::application * papplication);


   };


} // namespace apex



