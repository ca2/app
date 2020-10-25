#include "framework.h"


task_pool::task_pool()
{

   defer_create_mutex();

   set_layer(LAYERED_TASK_POOL, this);

}


task_pool::~task_pool()
{


}


task_pointer & task_pool::defer_start(const ::id& id, const ::method & method)
{

   auto& pthread = task(id);

   auto estatus = __construct(pthread);

   if (!estatus)
   {

      pthread = __create_new < ::task >();

   }

   pthread->start(method);

   return pthread;

}


void task_pool::start_clock(enum_clock eclock, duration duration)
{

   defer_start(eclock, __method([&, eclock, duration]()
      {

         _task_clock(eclock, duration);

      }));

}


void task_pool::on_clock(enum_clock eclock)
{

}





void task_pool::_task_clock(enum_clock eclock, duration duration)
{

   auto timeout = duration.get_total_milliseconds();

   while (true)
   {

      if (!task_sleep((u32)timeout))
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


