#include "framework.h"
#include "tools.h"
#include "pool.h"


task_pool::task_pool()
{

   defer_create_synchronization();

   //set_layer(LAYERED_TASK_POOL, this);

}


task_pool::~task_pool()
{


}


::pointer<::task>task_pool::defer_branch(const ::atom& atom, const ::procedure & procedure)
{

   auto & ptask = task(atom);

   __defer_construct_new(ptask);

   if (ptask->m_bIsRunning)
   {

      return ptask;

   }

   ptask->m_procedure = procedure;

   ptask->branch();

   return ptask;

}


void task_pool::set_timer(enum_timer etimer, const class time & timeWait)
{

   defer_branch(etimer, [&, etimer, timeWait]()
      {

         _timer_task(etimer, timeWait);

      });

}


void task_pool::on_timer(enum_timer etimer)
{

}


void task_pool::_timer_task(enum_timer etimer, const class time & timeWait)
{

   while (true)
   {

      if (!task_sleep(timeWait))
      {

         break;

      }

      try
      {

         on_timer(etimer);

      }
      catch (...)
      {

      }

   }

}



