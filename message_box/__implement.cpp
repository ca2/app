#include "framework.h"
#include "application.h"
#include "__implement.h"


::i32 __implement()
{

   auto papp = ___new app_message_box::application ();

   ::i32 iExitCode = papp->__implement();

   return iExitCode;

}



