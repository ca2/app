//
//  mac_main.cpp
//  Hello AXIS!!
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 8/2/15.
//  Copyright (c) 2015 ca2 Desenvolvimento de Software Ltdal. All rights reserved.
//




//
//  main.m
//  app
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 1/19/13.
//  Copyright (c) 2013 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

//#include "aura/_.h"
#include "aura/os/macos/macos.h"


int main(int argc, char *argv[])
{
   
   if(!defer_core_init())
      return -1;


   int iResult = base_main_command_line(": app=app-core/helloAXIS", argc, argv);
   
   try
   {
      
      defer_core_term();
      
   }
   catch(...)
   {
      
   }
   
   return iResult;
   
}


