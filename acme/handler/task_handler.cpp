//
// Created by camilo on 1/25/25. <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "task_handler.h"


task_handler::task_handler()
{


}


task_handler::~task_handler()
{


}


void task_handler::__task_prefix(::task * ptask)
{


}


void task_handler::__task_handle()
{

   {

      auto ptask = ::transfer(m_ptask);

      __task_prefix(ptask);

      ptask->__task_main();

      ptask->release();

   }

   printf_line("Going to call task suffix for task \"%s\" (%llu)", ::current_task_name().c_str(), ::current_task_index());
   
   __task_suffix();

}


void task_handler::__task_suffix()
{


}


