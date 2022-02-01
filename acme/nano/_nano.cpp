//
// Created by camilo on 31/01/2022.
//


void operating_system_initialize_nano();


bool g_bNanoInitialize = false;

CLASS_DECL_ACME void initialize_nano()
{

   if(g_bNanoInitialize)
   {

      return;

   }

   operating_system_initialize_nano();

   g_bNanoInitialize = true;

}