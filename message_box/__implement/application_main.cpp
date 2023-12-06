#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_message_box::application g_appmessageboxapplication;



::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = __allocate< app_message_box::application >();

   int iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}



