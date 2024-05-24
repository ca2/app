//
// Created by camilo on 2024-04-19
//
#include "framework.h"
#include "acid/parallelization/synchronous_lock.h"
#include "acid/platform/node.h"
#include "acid/platform/system.h"
#include "acid/nano/user/user.h"
#include "acid/parallelization/synchronous_lock.h"






#if defined(WITH_X11)


namespace acid
{



         ::particle* system::x11_synchronization()
         {

            _synchronous_lock sl(this->synchronization());

            auto psynchronization = m_pmutexXlib;

            if (!psynchronization)
            {

               psynchronization = node()->create_mutex();

               m_pmutexXlib = psynchronization;

            }

            return psynchronization;

         }


         void system::x11_async(const ::procedure &procedure)
         {

            node()->x11_async(procedure);

         }


         void system::x11_sync(const ::procedure &procedure)
         {

            node()->x11_sync(procedure);

         }
} // namespace acid


namespace x11
{
   namespace nano
   {
      namespace user
      {
         void x11_sync(const ::procedure & procedure)
         {

            ::platform::get()->system()->x11_sync(procedure);

         }


         void x11_async(const ::procedure & procedure)
         {

            ::platform::get()->system()->x11_async(procedure);

         }
      } // namespace user
   } // namespace nano
} // namespace x11


#endif



