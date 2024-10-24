#pragma once


#include "aura/_.h"
#include "aura/platform/app_core.h"


class CLASS_DECL_AURA application :
   public aura_main_struct
{
public:


   class aura_aura                  m_aura;
   ::pointer<aura_main_data>        m_pmaindata;
   ::pointer<::aura::application>   m_papplication;


   //static application *             s_papp;


   application();
   ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



   void application_boot();

};
