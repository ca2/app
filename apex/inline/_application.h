#pragma once


#include "apex/_.h"
#include "apex/platform/app_core.h"


class CLASS_DECL_APEX application :
   public apex_main_struct
{
public:


   class apex_apex                  m_apex;
   ::pointer<apex_main_data>        m_pmaindata;
   ::pointer<::apex::application>   m_pacmeapplication;


   //static application *             s_papp;


   application();
   ~application() override;


   void application_boot();

};
