//
//  macos_main.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 8/2/15.
//
//

#pragma once



struct main_param
{
   ::i32 argc;
   char_pointer *argv;
   
};

::u32 __run_system_main_param(struct main_param * i32_point);
