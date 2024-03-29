//
// Created by camilo on 31/01/2022.
//
#include "framework.h"
#include "acme/primitive/primitive/factory.h"


void operating_system_initialize_nano(::factory::factory * pfactory);


bool g_bNanoInitialize = false;


CLASS_DECL_ACME void initialize_nano_window(::factory::factory * pfactory)
{

   if(g_bNanoInitialize)
   {

      return;

   }

   operating_system_initialize_nano(pfactory);

   g_bNanoInitialize = true;

}