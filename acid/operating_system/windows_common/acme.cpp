#include "framework.h"
#include "acid/platform/acid.h"


namespace acid
{


   //#if defined(WINDOWS)  && defined(UNICODE)
#if defined(UNICODE)


   void acid::initialize(int argc, wchar_t * argv[], wchar_t * envp[])
   {

      m_pplatform->initialize(argc, argv, envp);

   }


   void acid::initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow)
   {

      m_pplatform->initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

   }

#endif // defined(UNICODE)


} // namespace acid




