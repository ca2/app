#include "framework.h"
#include "application.h"
#include "acme/application.h"


int application_main()
{

   auto papplication = __new(app_app::application());

   int iExitCode = papplication->application_main();

   return iExitCode;

}



