#include "framework.h"
#include "application.h"
#include "__implement.h"


int __implement()
{

   auto papp = new app_just_message_box::application();

   int iExitCode = papp->__implement();

   return iExitCode;

}



