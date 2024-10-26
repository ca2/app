#include "framework.h"
#include "application.h"
#include "acme/application.h"

//app_just_message_box::application g_appjustmessageboxapplication;

void application_main()
{

   __check_refdbg

   app_just_acme_message_box::application application;

   application.application_main();

}



