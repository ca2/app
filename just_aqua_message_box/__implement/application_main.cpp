#include "framework.h"
#include "application.h"
#include "acme/application.h"

//app_just_message_box::application g_appjustmessageboxapplication;

void application_main()
{

   auto papplication = __new app_just_aqua_message_box::application();

   papplication->application_main(pplatform);

}



