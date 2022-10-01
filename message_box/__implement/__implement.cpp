#include "framework.h"
#include "application.h"
#include "__implement.h"


int __implement()
{

   auto papp = memory_new app_message_box::application();

   int iExitCode = papp->__implement();

   return iExitCode;

}



