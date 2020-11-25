#include "framework.h"


task_pool::task_pool()
{

   defer_create_mutex();

   set_layer(LAYERED_TASK_POOL, this);

}


task_pool::~task_pool()
{


}


task_pointer & task_pool::defer_start(const ::id& id, const ::promise::routine & routine)
{

   auto& pthread = task(id);

   auto estatus = __defer_construct(pthread);

   if (!estatus)
   {

      pthread = __create_new < ::task >();

   }

   if (pthread->m_bitIsRunning)
   {

      return pthread;

   }

   pthread->start(routine);

   return pthread;

}


void task_pool::start_clock(enum_clock eclock, const duration & duration)
{

   defer_start(eclock, __routine([&, eclock, duration]()
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



