#include "framework.h"
#include "acme/platform/acme.h"


namespace acme
{


   //#if defined(WINDOWS)  && defined(UNICODE)
#if defined(UNICODE)


   void acme::initialize_system(int argc, wchar_t * argv[], wchar_t * envp[])
   {

      //initialize(argc, argv, envp);

   }


   void acme::initialize_system(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow)
   {

      //initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

   }

#endif // defined(UNICODE)


   void acme::initialize_system(int argc, char* argv[], char* envp[])
   {

      //initialize(argc, argv, envp);

   }




} // namespace acme




