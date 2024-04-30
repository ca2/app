#include "framework.h"
#include "multiple_lock.h"
#include "semaphore.h"
#include "acme/parallelization/synchronization_array.h"
////#include "acme/exception/exception.h"
#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif







multiple_lock::multiple_lock()
{

}


multiple_lock::multiple_lock(const synchronization_array & synchronizationa,bool bInitialLock)
{

   ASSERT(synchronizationa.synchronization_count() > 0 && synchronizationa.synchronization_count() <= MAXIMUM_WAIT_OBJECTS);

   if(synchronizationa.synchronization_count() <= 0)
   {

      throw ::exception(error_bad_argument);

   }

   for (::raw::index i = 0; i < synchronizationa.synchronization_count(); i++)
   {

      m_synchronizationa.add_item(synchronizationa.m_synchronizationa[i]);

   }

   //m_baLocked.set_size(m_hsyncaCache.get_size());

   if(bInitialLock)
   {

      lock();

   }

}


multiple_lock::multiple_lock(::raw::count c, const synchronization_array & synchronizationa, bool bInitialLock)
{

   ASSERT(synchronizationa.has_synchronization() && c > 0 && c <= synchronizationa.synchronization_count() && c <= MAXIMUM_WAIT_OBJECTS);

   if (synchronizationa.has_no_synchronization() || c <= 0 || c > synchronizationa.synchronization_count() || c > MAXIMUM_WAIT_OBJECTS)
   {

      throw ::exception(error_bad_argument);

   }

   m_synchronizationa.add(synchronizationa);

   memory_set(&m_bitsLocked, 0, sizeof(m_bitsLocked));

   if (bInitialLock)
   {

      lock();

   }

}


multiple_lock::~multiple_lock()
{

   unlock();

}


::raw::index multiple_lock::lock(const class time & time, bool bWaitForAll, u32 dwWakeMask)
{

   if (m_synchronizationa.has_no_synchronization())
   {

      throw ::exception(error_invalid_empty_argument);

   }

   //auto estatus = m_synchronizationa.wait(time, bWaitForAll, dwWakeMask);
   auto iSignaled = m_synchronizationa.wait(time, bWaitForAll, dwWakeMask);



   //if (dwWakeMask == 0)
   //{

   //   iResult = ::WaitForMultipleObjectsEx((u32) m_synchronizationa.synchronization_count(), m_synchronizationa.sync_data(), bWaitForAll, time.u32_millis(), false);

   //}
   //else
   //{

   //   iResult = ::MsgWaitForMultipleObjects((u32)m_synchronizationa.synchronization_count(), m_synchronizationa.sync_data(), bWaitForAll, time.u32_millis(), dwWakeMask);

   //}

   //::i32 iUpperBound = WAIT_OBJECT_0 + (::i32) m_synchronizationa.synchronization_count();

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

         for (::u8 j = 0, i = 0; j < m_synchronizationa.synchronization_count(); j++)
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

   return iSignaled;

}


void multiple_lock::unlock()
{

   for (::raw::index i=0; i < m_synchronizationa.synchronization_count(); i++)
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

   //bool bGotOne = false;

   for (::raw::index i=0; i < m_synchronizationa.synchronization_count(); i++)
   {

      if (m_bitsLocked.is_set(i) && m_synchronizationa.m_synchronizationa[i])
      {

         semaphore * pSemaphore = m_synchronizationa.synchronization_at(i).cast < semaphore >();

         if (pSemaphore != nullptr)
         {

            //bGotOne = true;

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


bool multiple_lock::is_locked(::raw::index iObject)
{

   //ASSERT(dwObject < m_synchronizationa.size());

   return m_bitsLocked[iObject];

}



