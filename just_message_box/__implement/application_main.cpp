#include "framework.h"
#include "application.h"
#include "acme/application.h"

//app_just_message_box::application g_appjustmessageboxapplication;

::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = __allocate< app_just_message_box::application >();

   int iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}



