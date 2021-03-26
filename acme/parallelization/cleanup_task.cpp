// Created by camilo on 2021-03-24 15:03 BRT <3ThomasBS_!!
#include "framework.h"
#include "cleanup_task.h"


namespace parallelization
{


   void cleanup_task::remove(matter* pmatter)
   {

      synchronization_lock lock(mutex());

      m_mattera.remove(pmatter);

   }


   void cleanup_task::add(matter* pmatter)
   {

      synchronization_lock lock(mutex());

      m_mattera.add_unique(pmatter);

   }


   ::e_status cleanup_task::on_task()
   {

      while (task_get_run())
      {

         {

            ::index i = 0;

            bool bShouldSleep = false;

            while (!bShouldSleep)
            {

               bShouldSleep = true;

               synchronization_lock lock(mutex());

               for (; i < m_mattera.get_count(); )
               {

                  auto pmatter = m_mattera[i];

                  lock.unlock();

                  auto estatus = pmatter->set_finish();

                  if (estatus != error_pending)
                  {

                     m_mattera.remove_at(i);

                     bShouldSleep = false;

                  }
                  else
                  {

                     i++;

                  }

                  lock.lock();

               }

            }

         }

         sleep(500_ms);

      }

      return ::success;

   }


} // namespace parallelization



