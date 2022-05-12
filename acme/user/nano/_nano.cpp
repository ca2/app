//
// Created by camilo on 31/01/2022.
//
#include "framework.h"


void operating_system_initialize_nano(::factory::factory * pfactory);


bool g_bNanoInitialize = false;


CLASS_DECL_ACME void initialize_nano_window()
{

   if(g_bNanoInitialize)
   {

      return;

   }

   operating_system_initialize_nano(::factory::get_factory());

   g_bNanoInitialize = true;

}