//
//  macos_main.h
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 8/2/15.
//
//

#pragma once



struct main_param
{
   int argc;
   char * *argv;
   
};

u32 __run_system_main_param(struct main_param * point);
