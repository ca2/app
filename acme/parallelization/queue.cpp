// Created on 2024-04-28 by camilo <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "manual_reset_happening.h"
#include "queue.h"
#include "synchronous_lock.h"
#include "acme/platform/application.h"


namespace parallelization
{


   queue::queue()
   {

      defer_create_synchronization();

   }


   queue::~queue()
   {


   }


   void queue::async(const ::procedure& procedure)
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_procedurea.add(procedure);

      }

      defer_run();

   }


   void queue::sync(const ::procedure& procedure, const class ::time& timeTimeout)
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_ptask == ::get_task())
         {

            synchronouslock.unlock();

            procedure();

            return;

         }

      }


      auto phappening = øcreate_new < manual_reset_happening >();

      async([procedure, phappening]()
         {

            procedure();

            phappening->set_happening();

         });

      phappening->_wait(timeTimeout);

   }


   void queue::defer_run()   
   {

      _synchronous_lock synchronouscock(this->synchronization());

      if (m_procedurea.is_empty())
      {

         return;

      }

      if (!m_ptask)
      {

         m_ptask = m_pobjectFork->fork([this]()
            {

               _synchronous_lock synchronouslock(this->synchronization());

               while (m_procedurea.has_element())
               {

                  auto procedure = m_procedurea.pick_first();

                  synchronouslock.unlock();

                  try
                  {

                     procedure();

                  }
                  catch (...)
                  {


                  }

                  synchronouslock._lock();

               }

               m_ptask.release();

            });

      }

   }

}
