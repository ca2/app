#include "framework.h"
#include "application.h"
#include "__implement.h"


//app_shader::application g_appshaderapplication;







int application_main()
{

   auto papplication = __new(app_shader::application());

   int iExitCode = papplication->application_main();

   return iExitCode;

}
