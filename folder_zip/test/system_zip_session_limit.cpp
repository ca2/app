#include "acme/framework.h"
#include "acme/platform/system.h"


int main()
{

   ::platform::system system;

   if (system.zip_file_session_maximum() != 8)
   {

      return 1;

   }

   system.set_zip_file_session_maximum(3);

   if (system.zip_file_session_maximum() != 3)
   {

      return 2;

   }

   system.set_zip_file_session_maximum(0);

   if (system.zip_file_session_maximum() != 1)
   {

      return 3;

   }

   return 0;

}
