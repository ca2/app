#include "framework.h"
#include "acme/inline/_console.h"


extern "C"
typedef  void  ace_MAIN();
typedef ace_MAIN* PFN_ace_MAIN;


int main_posix(int argc, char* argv[])
{

   console console(argc, argv);

   HMODULE hmodule = ::GetModuleHandle(NULL);

   PFN_ace_MAIN pacemain = (PFN_ace_MAIN) ::GetProcAddress(hmodule, "ace_main");

   if (!pacemain)
   {

      message_box("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + message_box_icon_error);

      return -1;

   }

   Application.m_estatus = ::undefined;

   (*pacemain)();

   int iStatus = (int)Application.m_estatus;

   int iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      if (::get_context_system()->command_value_is_true("show_application_information"))
      {

         printf("return code is %d", iStatus);

      }

   }

   return iError;

}

