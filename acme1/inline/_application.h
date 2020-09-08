#pragma once


#include "acme/_.h"
#include "acme/platform/app_core.h"


class CLASS_DECL_ACME application :
   public ace_main_struct
{
public:


   class ace_ace                  m_ace;
   __pointer(ace_main_data)        m_pmaindata;
   __pointer(::acme::application)   m_papp;


   //static application *             s_papplication;


   application();
   virtual ~application();


   void application_boot();

};