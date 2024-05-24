#pragma once


#include "application_exit.h"
#include "application_array.h"


namespace acid
{


   class CLASS_DECL_ACID application_container :
      virtual public ::application_exit
   {
   public:



      application_array                m_applicationa;

      bool                             m_bFinalizeIfNoApplicationSetting;
      bool                             m_bFinalizeIfNoApplication;

      ::pointer<::apex::application>  m_pappCurrent;




      application_container();
      ~application_container() override;


      virtual ::acid::application * get_application(const ::string & strAppId, bool bCreate = true, ::request * prequest = nullptr);


      //virtual ::pointer<::apex::application>create_application(const ::scoped_string & scopedstrAppId, bool bSynch, ::request * prequest);
      //virtual ::pointer<::apex::application>create_platform(::apex::session * psession);
      
      
      virtual ::pointer<::acid::application > instantiate_application(const::string& strAppIdd);
      virtual ::pointer<::acid::application > create_application(const ::string & strAppId, ::request * prequest);


      virtual void exit_application() override;


      application_array & applicationa();

      application_array get_applicationa();

      virtual void add_application(::acid::application * papplication);
      virtual void erase_application(::acid::application * papplication);


      ::pointer<::acid::application>assert_running(const ::string & strAppId);


      virtual void on_instantiate_application(::acid::application * papplication);


   };


} // namespace apex



