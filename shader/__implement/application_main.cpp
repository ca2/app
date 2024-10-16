#include "framework.h"
#include "application.h"
#include "__implement.h"


//app_shader::application g_appshaderapplication;







void application_main()
{

   auto papplication = __new app_shader::application();

   papplication->application_main(pplatform);

}
