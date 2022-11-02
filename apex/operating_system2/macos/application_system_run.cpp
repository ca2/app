//
//  macos_main.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 8/2/15.
//
//

//
//  main.cpp
//  app
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"


void os_application_system_run(::apex::system * psystem)
{

   psystem->application_main(psystem->m_argc, psystem->m_argv, psystem->m_strCommandLine);
   
   return ::success;
   
}


//void os_system_start()
//{
//
//   ::apex::get_system()->begin();
//   
//}
//
//

