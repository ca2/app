#include "framework.h"
#include "acme/inline/_console.h"


extern "C"
typedef  void  ACME_MAIN();
typedef ACME_MAIN* PFN_ACME_MAIN;


int main_posix(int argc, char* argv[])
{

   console console(argc, argv);

   HMODULE hmodule = ::GetModuleHandle(NULL);

   PFN_ACME_MAIN pauramain = (PFN_ACME_MAIN) ::GetProcAddress(hmodule, "aura_main");

   if (!pauramain)
   {

      output_error_message("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + e_message_box_icon_error);

      return -1;

   }

   papplication->m_estatus = ::undefined;

   (*pauramain)();

   int iStatus = (int)papplication->m_estatus;

   int iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      if (::acme::get_system()->command_value_is_true("show_application_information"))
      {

         printf("return code is %d", iStatus);

      }

   }

   return iError;

}

