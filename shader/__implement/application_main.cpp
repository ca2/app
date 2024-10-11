#include "framework.h"
#include "application.h"
#include "__implement.h"


//app_shader::application g_appshaderapplication;







::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = __new app_shader::application();

   int iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}
