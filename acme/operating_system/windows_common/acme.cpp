#include "framework.h"
#include "acme/platform/acme.h"


namespace acme
{


   //#if defined(WINDOWS)  && defined(UNICODE)
#if defined(UNICODE)


   void acme::initialize_system(::i32 argc, wchar_t * argv[], wchar_t * envp[])
   {

      //initialize(argc, argv, envp);

   }


   void acme::initialize_system(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, ::i32 nCmdShow)
   {

      //initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

   }

#endif // defined(UNICODE)


   void acme::initialize_system(::i32 argc, char_pointer argv[], char_pointer envp[])
   {

      //initialize(argc, argv, envp);

   }




} // namespace acme




