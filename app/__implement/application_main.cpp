#include "framework.h"
#include "application.h"
#include "acme/application.h"


::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = __allocate< app_app::application >();

   int iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}



