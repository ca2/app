#pragma once


#include "acme/_.h"
#include "acme/platform/app_core.h"


**********class CLASS_DECL_ACME application :
   public acme_main_struct
{
public:


   class acme_acme                  m_acme;
   ********::pointer<acme_main_data>        m_pmaindata;
   ::pointer<::platform::application>   m_papplication;


   //static application *             s_papp;


   application();
   ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



   void application_boot();

};
