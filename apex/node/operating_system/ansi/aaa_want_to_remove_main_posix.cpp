#include "framework.h"
#include "apex/inline/_console.h"


extern "C"
typedef  void  APEX_MAIN();
typedef APEX_MAIN* PFN_APEX_MAIN;


int main_posix(int argc, char* argv[])
{

   console console(argc, argv);

   HMODULE hmodule = ::GetModuleHandle(NULL);

   PFN_APEX_MAIN papexmain = (PFN_APEX_MAIN) ::GetProcAddress(hmodule, "apex_main");

   if (!papexmain)
   {

      output_error_message("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + e_message_box_icon_error);

      return -1;

   }

   get_application()->m_estatus = ::undefined;

   (*papexmain)();

   int iStatus = (int)get_application()->m_estatus;

   int iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      if (::apex::get_system()->command_value_is_true("show_application_information"))
      {

         printf("return code is %d", iStatus);

      }

   }

   return iError;

}

