#pragma once


#include "apex/_.h"
#include "apex/platform/app_core.h"


class CLASS_DECL_APEX application :
   public apex_main_struct
{
public:


   class apex_apex                  m_apex;
   __pointer(apex_main_data)        m_pmaindata;
   __pointer(::application)   m_papp;


   //static application *             s_papp;


   application();
   ~application() override;


   void application_boot();

};
