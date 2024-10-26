#include "framework.h"
#include "acme/platform/acme.h"


namespace acme
{


   //#if defined(WINDOWS)  && defined(UNICODE)
#if defined(UNICODE)


   void acme::initialize(int argc, wchar_t * argv[], wchar_t * envp[])
   {

      //m_pplatform->initialize(argc, argv, envp);

   }


   void acme::initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow)
   {

      //m_pplatform->initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

   }

#endif // defined(UNICODE)


} // namespace acme




