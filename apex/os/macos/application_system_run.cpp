//
//  macos_main.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 8/2/15.
//
//

//
//  main.cpp
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


::e_status os_application_system_run(::apex::system * psystem)
{

   psystem->application_main(psystem->m_argc, psystem->m_argv, psystem->m_strCommandLine);
   
   return ::success;
   
}


void os_system_start()
{

   System->begin();
   
}



