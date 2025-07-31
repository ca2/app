#pragma once


#include "application_exit.h"
#include "application_array.h"


namespace platform
{


   class CLASS_DECL_ACME application_container :
      virtual public ::application_exit
   {
   public:



      application_array                m_applicationa;

      bool                             m_bFinalizeIfNoApplicationSetting;
      bool                             m_bFinalizeIfNoApplication;

      ::pointer<::platform::application>   m_pappCurrent;




      application_container();
      ~application_container() override;


      virtual ::platform::application * get_application(const ::scoped_string & scopedstrAppId, bool bCreate = true, ::request * prequest = nullptr);


      //virtual ::pointer<::apex::application>create_application(const ::scoped_string & scopedstrAppId, bool bSynch, ::request * prequest);
      //virtual ::pointer<::apex::application>create_platform(::apex::session * psession);
      
      
      virtual ::pointer<::platform::application > instantiate_application(const::string& strAppIdd);
      virtual ::pointer<::platform::application > create_application(const ::scoped_string & scopedstrAppId);


      virtual void exit_application() override;


      application_array & applicationa();

      application_array get_applicationa();

      virtual void add_application(::platform::application * papplication);
      virtual void erase_application(::platform::application * papplication);


      ::pointer<::platform::application>assert_running(const ::scoped_string & scopedstrAppId);


      virtual void on_instantiate_application(::platform::application * papplication);


   };


} // namespace platform



