#include "framework.h"
#include "application.h"
#include "acme/application.h"

//app_just_message_box::application g_appjustmessageboxapplication;

int application_main()
{

   auto papplication = __new(app_just_message_box::application());

   int iExitCode = papplication->application_main();

   return iExitCode;

}



