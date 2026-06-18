//
//  mac_main.cpp
//  Hello Base!!
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 8/2/15.
//  Copyright (c) 2015 ca2 Desenvolvimento de Software Ltdal. All rights reserved.
//




//
//  main.m
//  app
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 1/19/13.
//  Copyright (c) 2013 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

//#include "aura/_.h"
#include "aura/os/macos/macos.h"


::i32 main(::i32 argc, char_pointer argv[])
{
   
   if(!defer_core_init())
      return -1;


   ::i32 iResult = base_main_command_line(": app=app-core/hellobase", argc, argv);
   
   try
   {
      
      defer_core_term();
      
   }
   catch(...)
   {
      
   }
   
   return iResult;
   
}


