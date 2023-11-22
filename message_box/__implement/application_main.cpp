#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_message_box::application g_appmessageboxapplication;



int application_main()
{

   auto papplication = __new(app_message_box::application());

   int iExitCode = papplication->application_main();

   return iExitCode;

}



