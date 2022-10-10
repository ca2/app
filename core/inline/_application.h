#pragma once


#include "aura/_.h"
#include "aura/platform/app_core.h"


class CLASS_DECL_CORE application :
   public aura_main_struct
{
public:


   class aura_aura                  m_aura;
   ::pointer<aura_main_data>        m_pmaindata;
   ::pointer<::aura::application>   m_pacmeapplication;


   //static application *             s_papp;


   application();
   ~application() override;


   void application_boot();

};
