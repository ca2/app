#pragma once


#include "aura/_.h"
#include "aura/platform/app_core.h"


class CLASS_DECL_AURA application :
   public aura_main_struct
{
public:


   class aura_aura                  m_aura;
   __pointer(aura_main_data)        m_pmaindata;
   __pointer(::aura::application)   m_papp;


   //static application *             s_papplication;


   application();
   virtual ~application();


   void application_boot();

};
