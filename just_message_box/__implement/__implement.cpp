#include "framework.h"
#include "application.h"
#include "__implement.h"


int __implement()
{

   auto papp = memory_new app_just_message_box::application();

   papp->m_bNetworking = false;

   papp->m_strAppId = "app/just_message_box";

   papp->m_strAppName = "Just Message Box";

   int iExitCode = papp->__implement();

   return iExitCode;

}



