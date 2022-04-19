//
//  parallelization.cpp
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 18:00 BRT <3ThomasBS_!!
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include <unistd.h>

#undef user


int get_current_process_affinity_order()
{

   int numCPU = (int) (sysconf(_SC_NPROCESSORS_ONLN));

   return numCPU;
}


void main_asynchronous(::procedure function)
{
  
   ns_main_async(^{
      
      function();
      
   });
   
}


void system::windowing_post(const ::procedure & function)
{
   
   main_asynchronous(function);
   
}



