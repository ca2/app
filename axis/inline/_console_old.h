#pragma once


#include "aura/_.h"
#include "aura/platform/app_core.h"


class CLASS_DECL_AXIS console :
   public aura_main_struct
{
public:

   class aura_aura                  m_aura;
   ::pointer<::aura::system>        system();
   //::pointer<::aura::application>   m_papplication;

   console(::i32 argc, wchar_t * argv[]);
   console(::i32 argc, char_pointer argv[]);
   virtual ~console();


};
