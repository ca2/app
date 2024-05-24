#pragma once


#include "acid/_.h"
#include "acid/platform/app_core.h"


**********class CLASS_DECL_ACID application :
   public ace_main_struct
{
public:


   class ace_ace                  m_ace;
   ********::pointer<ace_main_data>        m_pmaindata;
   ::pointer<::acid::application>   m_paceapplication;


   //static application *             s_papp;


   application();
   ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



   void application_boot();

};
