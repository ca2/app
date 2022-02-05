#include "framework.h"
#include "acme/node/operating_system/_os.h"


#undef new

#define new ACME_NEW

multi_lock::multi_lock(const synchronization_array & synca,bool bInitialLock)
{

   ASSERT(synca.sync_count() > 0 && synca.sync_count() <= MAXIMUM_WAIT_OBJECTS);

   if(synca.sync_count() <= 0)
   {

      __throw(error_bad_argument);

   }

   for (index i = 0; i < synca.sync_count(); i++)
   {

      m_synchronizationa.add_item(synca.m_synchronizationa[i]);

   }

   //m_baLocked.set_size(m_hsyncaCache.get_size());

   if(bInitialLock)
   {

      lock();

   }

}


multi_lock::multi_lock(::count c, const synchronization_array & synca, bool bInitialLock)
{

   ASSERT(synca.m_hsyncaCache.has_element() && c > 0 && c <= synca.m_hsyncaCache.get_size() && c <= MAXIMUM_WAIT_OBJECTS);

   if (synca.m_hsyncaCache.is_empty() || c <= 0 || c > synca.m_hsyncaCache.get_size())
   {

      __throw(error_bad_argument);

   }

   m_synchronizationa.add(synca);

   __zero(m_byteaLocked);

   if (bInitialLock)
   {

      lock();

   }

}


multi_lock::~multi_lock()
{

   unlock();

}


synchronization_result multi_lock::lock(const duration & duration, bool bWaitForAll, u32 dwWakeMask)
{

   if (m_synchronizationa.m_hsyncaCache.is_empty())
   {

      return synchronization_result(e_synchronization_result_error);

   }

   ::i32 iResult;

   if (dwWakeMask == 0)
   {

      iResult = ::WaitForMultipleObjectsEx((u32) m_synchronizationa.m_hsyncaCache.get_count(), m_synchronizationa.m_hsyncaCache.get_data(), bWaitForAll, duration.u32_millis(), false);

   }
   else
   {

      iResult = ::MsgWaitForMultipleObjects((u32)m_synchronizationa.m_hsyncaCache.get_count(), m_synchronizationa.m_hsyncaCache.get_data(), bWaitForAll, duration.u32_millis(), dwWakeMask);

   }

   ::i32 iUpperBound = WAIT_OBJECT_0 + (::i32) m_synchronizationa.m_hsyncaCache.get_count();

   if(iResult == WAIT_FAILED)
   {

      ::e_status estatus = ::get_last_status();

      // TRACELASTERROR();

   }
   else if (iResult >= WAIT_OBJECT_0 && iResult < iUpperBound)
   {

      if (bWaitForAll)
      {

         for (index j = 0, i = 0; j < m_synchronizationa.m_hsyncaCache.size(); j++)
         {

            m_byteaLocked[i] = true;

         }

      }
      else
      {

         m_byteaLocked[(iResult - WAIT_OBJECT_0)] = true;

      }

   }

   return synchronization_result(iResult, m_synchronizationa.m_hsyncaCache.get_count());

}


bool multi_lock::unlock()
{

   for (index i=0; i < m_synchronizationa.m_hsyncaCache.get_count(); i++)
   {

      if (m_byteaLocked[i] && m_synchronizationa.m_synchronizationa[i]->m_hsync)
      {

         m_byteaLocked[i] = !m_synchronizationa.m_synchronizationa[i]->unlock();

      }

   }

   return true;

}


bool multi_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* =nullptr */)
{

   bool bGotOne = false;

   for (index i=0; i < m_synchronizationa.m_hsyncaCache.get_count(); i++)
   {

      if (m_byteaLocked[i] && m_synchronizationa.m_synchronizationa[i]->m_hsync)
      {

         semaphore * pSemaphore = m_synchronizationa.sync_at(i).cast < semaphore >();

         if (pSemaphore != nullptr)
         {

            bGotOne = true;

            m_byteaLocked[i] = !m_synchronizationa.m_synchronizationa[i]->unlock(lCount, pPrevCount);

         }

      }

   }

   return bGotOne;

}


bool multi_lock::IsLocked(index dwObject)
{

   ASSERT(dwObject < m_synchronizationa.size());

   return m_byteaLocked[dwObject];

}



