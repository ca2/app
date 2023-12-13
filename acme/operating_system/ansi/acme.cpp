//
//  acme.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/12/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "acme/platform/acme.h"


namespace acme
{


   //#if defined(WINDOWS)  && defined(UNICODE)
#if defined(UNICODE)


   void acme::initialize(int argc, wchar_t * argv[], wchar_t * envp[])
   {

      m_pplatform->initialize(argc, argv, envp);

   }


   void acme::initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow)
   {

      m_pplatform->initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);

   }

#else


   void acme::initialize(int argc, char * argv[], char * envp[])
   {

      m_pplatform->initialize(argc, argv, envp);

   }


#endif // defined(UNICODE)


} // namespace acme




