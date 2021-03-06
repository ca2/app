#include "framework.h"


task_pool::task_pool()
{

   defer_create_mutex();

   //set_layer(LAYERED_TASK_POOL, this);

}


task_pool::~task_pool()
{


}


__composite(::task) task_pool::defer_branch(const ::id& id, const ::routine & routine)
{

   auto & ptask = task(id);

   auto estatus = __defer_compose_new(ptask);

   if (!estatus)
   {

      return ptask;

   }

   if (ptask->m_bIsRunning)
   {

      return ptask;

   }

   ptask->m_pmatter = routine;

   ptask->branch();

   return ptask;

}


void task_pool::set_timer(enum_timer etimer, const duration & duration)
{

   defer_branch(etimer, __routine([&, etimer, duration]()
      {

         _timer_task(etimer, duration);

      }));

}


void task_pool::on_timer(enum_timer etimer)
{

}


void task_pool::_timer_task(enum_timer etimer, const duration & duration)
{

   ::millis millis = duration.millis();

   while (true)
   {

      if (!task_sleep(millis))
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



