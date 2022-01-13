#include "framework.h"
#include "acme/operating_system.h"
#include "multiple_lock.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


#undef new

#define new ACME_NEW


multiple_lock::multiple_lock()
{

}


multiple_lock::multiple_lock(const synchronization_array & synchronizationa,bool bInitialLock)
{

   ASSERT(synchronizationa.synchronization_object_count() > 0 && synchronizationa.synchronization_object_count() <= MAXIMUM_WAIT_OBJECTS);

   if(synchronizationa.synchronization_object_count() <= 0)
   {

      __throw(error_invalid_argument);

   }

   for (index i = 0; i < synchronizationa.synchronization_object_count(); i++)
   {

      m_synchronizationa.add_item(synchronizationa.m_synchronizationa[i]);

   }

   //m_baLocked.set_size(m_hsyncaCache.get_size());

   if(bInitialLock)
   {

      lock();

   }

}


multiple_lock::multiple_lock(::count c, const synchronization_array & synchronizationa, bool bInitialLock)
{

   ASSERT(synchronizationa.has_synchronization_object() && c > 0 && c <= synchronizationa.synchronization_object_count() && c <= MAXIMUM_WAIT_OBJECTS);

   if (synchronizationa.has_no_synchronization_object() || c <= 0 || c > synchronizationa.synchronization_object_count() || c > MAXIMUM_WAIT_OBJECTS)
   {

      __throw(error_invalid_argument);

   }

   m_synchronizationa.add(synchronizationa);

   __zero(m_bitsLocked);

   if (bInitialLock)
   {

      lock();

   }

}


multiple_lock::~multiple_lock()
{

   unlock();

}


void multiple_lock::lock(const duration & duration, bool bWaitForAll, u32 dwWakeMask)
{

   if (m_synchronizationa.has_no_synchronization_object())
   {

      return;

   }

   //auto estatus = m_synchronizationa.wait(duration, bWaitForAll, dwWakeMask);
   auto iSignaled = m_synchronizationa.wait(duration, bWaitForAll, dwWakeMask);



   //if (dwWakeMask == 0)
   //{

   //   iResult = ::WaitForMultipleObjectsEx((u32) m_synchronizationa.synchronization_object_count(), m_synchronizationa.sync_data(), bWaitForAll, duration.u32_millis(), false);

   //}
   //else
   //{

   //   iResult = ::MsgWaitForMultipleObjects((u32)m_synchronizationa.synchronization_object_count(), m_synchronizationa.sync_data(), bWaitForAll, duration.u32_millis(), dwWakeMask);

   //}

   //::i32 iUpperBound = WAIT_OBJECT_0 + (::i32) m_synchronizationa.synchronization_object_count();

   //auto iSignaled = estatus.signaled_index();

   if(iSignaled < 0)
   {

      ::e_status estatus = ::get_last_status();

      // TRACELASTERROR();

   }
   else if (iSignaled >= 0)
   {

      if (bWaitForAll)
      {

         for (byte j = 0, i = 0; j < m_synchronizationa.synchronization_object_count(); j++)
         {

            m_bitsLocked.set(i);

         }

      }
      else
      {

         m_bitsLocked.set(iSignaled);

      }

   }

   //return estatus;

}


void multiple_lock::unlock()
{

   for (index i=0; i < m_synchronizationa.synchronization_object_count(); i++)
   {

      if (m_bitsLocked.is_set(i) && m_synchronizationa.m_synchronizationa[i])
      {

         m_synchronizationa.m_synchronizationa[i]->unlock();

         m_bitsLocked.set(i, false);

      }

   }

   //return true;

}


void multiple_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* =nullptr */)
{

   bool bGotOne = false;

   for (index i=0; i < m_synchronizationa.synchronization_object_count(); i++)
   {

      if (m_bitsLocked.is_set(i) && m_synchronizationa.m_synchronizationa[i])
      {

         semaphore * pSemaphore = m_synchronizationa.synchronization_object_at(i).cast < semaphore >();

         if (pSemaphore != nullptr)
         {

            bGotOne = true;

            //if (m_synchronizationa.m_synchronizationa[i]->unlock(lCount, pPrevCount))
            m_synchronizationa.m_synchronizationa[i]->unlock(lCount, pPrevCount);
            {

               m_bitsLocked.unset(i);

            }

         }

      }

   }

   //return bGotOne;

}


bool multiple_lock::is_locked(index dwObject)
{

   //ASSERT(dwObject < m_synchronizationa.size());

   return m_bitsLocked[dwObject];

}



