//
//  parallelization.cpp
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 18:00 BRT <3ThomasBS_!!
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include <unistd.h>

#undef user


//int get_current_process_affinity_order()
//{
//
//   int numCPU = (int) (sysconf(_SC_NPROCESSORS_ONLN));
//
//   return numCPU;
//}
//
//
//




bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}

void _ns_do_tasks(double dSeconds);

void _do_tasks()
{
   
   _ns_do_tasks(0.005);
   
}


