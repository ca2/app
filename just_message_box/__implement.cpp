#include "framework.h"
#include "application.h"
#include "__implement.h"


int __implement()
{

   auto papp = __new< app_just_message_box::application >();

   papp->m_strAppId = "app/just_message_box";

   papp->m_strAppName = "Just Message Box";

   int iExitCode = papp->__implement();

   return iExitCode;

}



