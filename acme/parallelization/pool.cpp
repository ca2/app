#include "framework.h"


task_pool::task_pool()
{

   defer_create_mutex();

   set_layer(LAYERED_TASK_POOL, this);

}


task_pool::~task_pool()
{


}


::task * task_pool::defer_fork(const ::id& id, const ::promise::routine & routine)
{

   auto & ptask = task(id);

   auto estatus = __defer_construct(ptask);

   if (!estatus)
   {

      ptask = __create_new < ::task >();

   }

   if (ptask->m_bitIsRunning)
   {

      return ptask;

   }

   ptask->start(routine);

   return ptask;

}


void task_pool::start_clock(enum_clock eclock, const duration & duration)
{

   defer_fork(eclock, __routine([&, eclock, duration]()
      {

         _task_clock(eclock, duration);

      }));

}


void task_pool::on_clock(enum_clock eclock)
{

}


void task_pool::_task_clock(enum_clock eclock, const duration & duration)
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

         on_clock(eclock);

      }
      catch (...)
      {

      }

   }

}



