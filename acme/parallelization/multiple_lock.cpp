#include "framework.h"
#include "multiple_lock.h"
#include "semaphore.h"
#include "acme/parallelization/synchronization_array.h"
////#include "acme/exception/exception.h"
#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


multiple_lock::multiple_lock(synchronization_array & synchronizationa,bool bInitialLock) :
   m_synchronizationa(synchronizationa)
{

   ASSERT(m_synchronizationa.size() > 0 && m_synchronizationa.size() <= MAXIMUM_WAIT_OBJECTS);

   if(bInitialLock)
   {

      lock();

   }

}

//
//multiple_lock::multiple_lock(::collection::count c, const synchronization_array & synchronizationa, bool bInitialLock)
//{
//
//   ASSERT(synchronizationa.has_synchronization() && c > 0 && c <= synchronizationa.synchronization_count() && c <= MAXIMUM_WAIT_OBJECTS);
//
//   if (synchronizationa.has_no_synchronization() || c <= 0 || c > synchronizationa.synchronization_count() || c > MAXIMUM_WAIT_OBJECTS)
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   m_synchronizationa.add(synchronizationa);
//
//   memory_set(&m_bitsLocked, 0, sizeof(m_bitsLocked));
//
//   if (bInitialLock)
//   {
//
//      lock();
//
//   }
//
//}


multiple_lock::~multiple_lock()
{

   unlock();

}


::e_status multiple_lock::lock(const class time & time, bool bWaitForAll, u32 dwWakeMask)
{

   //if (m_synchronizationa.has_no_synchronization())
   //{

   //   throw ::exception(error_invalid_empty_argument);

   //}

   //auto estatus = m_synchronizationa.wait(time, bWaitForAll, dwWakeMask);
   auto estatus = m_synchronizationa.wait(time, bWaitForAll, dwWakeMask);



   //if (dwWakeMask == 0)
   //{

   //   iResult = ::WaitForMultipleObjectsEx((u32) m_synchronizationa.synchronization_count(), m_synchronizationa.sync_data(), bWaitForAll, time.u32_millis(), false);

   //}
   //else
   //{

   //   iResult = ::MsgWaitForMultipleObjects((u32)m_synchronizationa.synchronization_count(), m_synchronizationa.sync_data(), bWaitForAll, time.u32_millis(), dwWakeMask);

   //}

   //int iUpperBound = WAIT_OBJECT_0 + (int) m_synchronizationa.synchronization_count();

   //auto iSignaled = estatus.signaled_index();

   //if(iSignaled < 0)
   //{

   //   ::e_status estatus = ::get_last_status();

   //   // TRACELASTERROR();

   //}
   //else if (iSignaled >= 0)
   //{

   //   if (bWaitForAll)
   //   {

   //      for (unsigned char j = 0, i = 0; j < m_synchronizationa.size(); j++)
   //      {

   //         m_bitsLocked.set(i);

   //      }

   //   }
   //   else
   //   {

   //      m_bitsLocked.set(iSignaled);

   //   }

   //}

   //return estatus;

   //return iSignaled;

   return estatus;

}


void multiple_lock::unlock()
{

   for (::collection::index i=0; i < m_synchronizationa.size(); i++)
   {

      if (m_bitsLocked.is_set(i))
      {

         m_synchronizationa.unlock_item(i);

         m_bitsLocked.set(i, false);

      }

   }

   //return true;

}


void multiple_lock::unlock(int lCount, int * pPrevCount /* =nullptr */)
{

   //bool bGotOne = false;

   for (::collection::index i=0; i < m_synchronizationa.size(); i++)
   {

      if (m_bitsLocked.is_set(i))
      {

         m_synchronizationa.unlock_item(i,lCount, pPrevCount);

         m_bitsLocked.unset(i);

      }

   }

   //return bGotOne;

}


bool multiple_lock::is_locked(::collection::index iObject)
{

   //ASSERT(dwObject < m_synchronizationa.size());

   return m_bitsLocked[iObject];

}



