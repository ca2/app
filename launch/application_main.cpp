// Created by camilo on 2023-11-07 00:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#define FACTORY console_application_build_helper
#define __APP_ID "console/application_build_helper"
#define NO_NETWORKING
#include "acme/console.h"



void application_main(::platform::system * psystem)
{

   launch::application  application;

   auto iExitCode = application.application_main();

   return iExitCode;

}



