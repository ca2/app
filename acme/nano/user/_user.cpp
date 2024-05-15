//
// Created by camilo on 31/01/2022.
//
#include "framework.h"
#include "acme/primitive/primitive/factory.h"


void operating_system_initialize_nano_user(::factory::factory * pfactory);


bool g_bNanoUserInitialize = false;


CLASS_DECL_ACME void initialize_nano_user(::factory::factory * pfactory)
{

   if(g_bNanoUserInitialize)
   {

      return;

   }

   operating_system_initialize_nano_user(pfactory);

   g_bNanoUserInitialize = true;

}
