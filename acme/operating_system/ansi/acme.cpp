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


//   //#if defined(WINDOWS)  && defined(UNICODE)
//#if defined(UNICODE)
//
//
//   void acme::initialize(::i32 argc, wchar_t * argv[], wchar_t * envp[])
//   {
//
//      initialize(argc, argv, envp);
//
//   }
//
//
//   void acme::initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, ::i32 nCmdShow)
//   {
//
//      initialize(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);
//
//   }
//
//#else


   void acme::initialize_system(::i32 argc, char_pointer argv[], char_pointer envp[])
   {

///      initialize_system(argc, argv, envp);

   }


//#endif // defined(UNICODE)


} // namespace acme




