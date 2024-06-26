// Created by camilo on 2023-11-07 00:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#define FACTORY console_application_build_helper
#define __APP_ID "console/application_build_helper"
#define NO_NETWORKING
#include "acme/console.h"



::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = __allocate < launch::application >();

   auto iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}



