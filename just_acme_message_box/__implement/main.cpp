#include "framework.h"
#define APPLICATION_NAMESPACE app_core_
#include "acme/inline/application/main.inl"

//app_just_message_box::application g_appjustmessageboxapplication;

void application_main(::platform::system * psystem)
{

   __check_refdbg

   app_just_acme_message_box::application application;

   application.application_main();

}



