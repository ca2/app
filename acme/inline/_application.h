#pragma once


#include "acme/_.h"
#include "acme/platform/app_core.h"


class CLASS_DECL_ACME application :
   public aura_main_struct
{
public:


   class aura_aura                  m_aura;
   __pointer(aura_main_data)        m_pmaindata;
   __pointer(::acme::application)   m_papp;


   //static application *             s_papplication;


   application();
   virtual ~application();


   void application_boot();

};