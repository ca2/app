//
//  macos_main.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 8/2/15.
//
//

#pragma once



struct main_param
{
   int argc;
   char * *argv;
   
};

u32 __run_system_main_param(struct main_param * point_i32);
