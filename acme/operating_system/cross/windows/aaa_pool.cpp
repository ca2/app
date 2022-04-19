#include "framework.h"


task_pool::task_pool()
{

   defer_create_mutex();

   set_layer(LAYERED_TASK_POOL, this);

}


task_pool::~task_pool()
{


}


task_pointer & task_pool::defer_start(const ::atom& atom, const ::procedure & procedure)
{

   auto& pthread = task(atom);

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


void task_pool::start_clock(enum_timer etimer, const duration & duration)
{

   defer_start(etimer, __routine([&, etimer, duration]()
      {

         _task_clock(etimer, duration);

      }));

}


void task_pool::on_clock(enum_timer etimer)
{

}


void task_pool::_task_clock(enum_timer etimer, const duration & duration)
{

   ::duration ::duration = duration.::duration();

   while (true)
   {

      if (!task_sleep(::duration))
      {

         break;

      }

      try
      {

         on_clock(etimer);

      }
      catch (...)
      {

      }

   }

}



