#pragma once


#include "aura/_.h"
#include "aura/platform/app_core.h"


class CLASS_DECL_AXIS console :
   public aura_main_struct
{
public:

   class aura_aura                  m_aura;
   __pointer(::aura::system)        m_psystem;
   //__pointer(::aura::application)   m_pacmeapplication;

   console(int argc, wchar_t * argv[]);
   console(int argc, char * argv[]);
   virtual ~console();


};
