#include "framework.h"
#include "acme/platform/acme.h"


namespace acme
{


   //#if defined(WINDOWS)  && defined(UNICODE)
#if defined(UNICODE)


   void acme::initialize(int argc, wchar_t * argv[], wchar_t * envp[])
   {

      //initialize(argc, argv, envp);

   }


   void acme::initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow)
   {

      //initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

   }

#endif // defined(UNICODE)


} // namespace acme




