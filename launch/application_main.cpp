// Created by camilo on 2023-11-07 00:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#define FACTORY console_application_build_helper
#define __APP_ID "console/application_build_helper"
#define NO_NETWORKING
#include "acme/console.h"



void application_main()
{

   auto papplication = __new launch::application ();

   auto iExitCode = papplication->application_main();

   return iExitCode;

}



