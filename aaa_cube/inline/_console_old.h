#pragma once


#include "aura/_.h"
#include "aura/platform/app_graphics3d.h"


class CLASS_DECL_AURA console :
   public aura_main_struct
{
public:

   class aura_aura                  m_aura;
   ::pointer<::aura::system>        system();
   //::pointer<::aura::application>   m_papplication;

   console(int argc, wchar_t * argv[]);
   console(int argc, char * argv[]);
   virtual ~console();


};
