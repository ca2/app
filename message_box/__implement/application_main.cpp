#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_message_box::application g_appmessageboxapplication;



void application_main()
{

   auto papplication = __new app_message_box::application();

   papplication->application_main();

}



