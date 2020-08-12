//
//  mac_main.cpp
//  Hello World!!
//
//  Created by Camilo Sasuke Tsumanuma on 8/2/15.
//  Copyright (c) 2015 ca2 Desenvolvimento de Software Ltdal. All rights reserved.
//




//
//  main.m
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 1/19/13.
//  Copyright (c) 2013 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "aura/_.h"
#include "aura/os/macos/macos.h"


int main(int argc, char *argv[])
{
   
   if(!defer_core_init())
      return -1;


   int iResult = base_main_command_line(": app=app-core/helloworld", argc, argv);
   
   try
   {
      
      defer_core_term();
      
   }
   catch(...)
   {
      
   }
   
   return iResult;
   
}


