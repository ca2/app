#include "framework.h"
#include "acme/os/_os.h"


#undef new

#define new ACME_NEW

multi_lock::multi_lock(const sync_array & synca,bool bInitialLock)
{

   ASSERT(synca.sync_count() > 0 && synca.sync_count() <= MAXIMUM_WAIT_OBJECTS);

   if(synca.sync_count() <= 0)
   {

      __throw(invalid_argument_exception());

   }

   for (index i = 0; i < synca.sync_count(); i++)
   {

      m_synca.add_item(synca.m_synca[i]);

   }

   //m_baLocked.set_size(m_hsyncaCache.get_size());

   if(bInitialLock)
   {

      lock();

   }

}


multi_lock::multi_lock(::count c, const sync_array & synca, bool bInitialLock)
{

   ASSERT(synca.m_hsyncaCache.has_element() && c > 0 && c <= synca.m_hsyncaCache.get_size() && c <= MAXIMUM_WAIT_OBJECTS);

   if (synca.m_hsyncaCache.is_empty() || c <= 0 || c > synca.m_hsyncaCache.get_size())
   {

      __throw(invalid_argument_exception());

   }

   m_synca.add(synca);

   ·zero(m_byteaLocked);

   if (bInitialLock)
   {

      lock();

   }

}


multi_lock::~multi_lock()
{

   unlock();

}


sync_result multi_lock::lock(const duration & duration, bool bWaitForAll, u32 dwWakeMask)
{

   if (m_synca.m_hsyncaCache.is_empty())
   {

      return sync_result(sync_result::result_error);

   }

   ::i32 iResult;

   if (dwWakeMask == 0)
   {

      iResult = ::WaitForMultipleObjectsEx((u32) m_synca.m_hsyncaCache.get_count(), m_synca.m_hsyncaCache.get_data(), bWaitForAll, duration.u32_millis(), FALSE);

   }
   else
   {

      iResult = ::MsgWaitForMultipleObjects((u32)m_synca.m_hsyncaCache.get_count(), m_synca.m_hsyncaCache.get_data(), bWaitForAll, duration.u32_millis(), dwWakeMask);

   }

   ::u32 iUpperBound = WAIT_OBJECT_0 + (::u32) m_synca.m_hsyncaCache.get_count();

   if(iResult == WAIT_FAILED)
   {

      ::estatus estatus = ::get_last_status();

      // TRACELASTERROR();

   }
   else if (iResult >= WAIT_OBJECT_0 && iResult < iUpperBound)
   {

      if (bWaitForAll)
      {

         for (index j = 0, i = 0; j < m_synca.m_hsyncaCache.size(); j++)
         {

            m_byteaLocked[i] = TRUE;

         }

      }
      else
      {

         m_byteaLocked[(iResult - WAIT_OBJECT_0)] = TRUE;

      }

   }

   return sync_result(iResult, m_synca.m_hsyncaCache.get_count());

}


bool multi_lock::unlock()
{

   for (index i=0; i < m_synca.m_hsyncaCache.get_count(); i++)
   {

      if (m_byteaLocked[i] && m_synca.m_synca[i]->m_hsync)
      {

         m_byteaLocked[i] = !m_synca.m_synca[i]->unlock();

      }

   }

   return TRUE;

}


bool multi_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* =nullptr */)
{

   bool bGotOne = false;

   for (index i=0; i < m_synca.m_hsyncaCache.get_count(); i++)
   {

      if (m_byteaLocked[i] && m_synca.m_synca[i]->m_hsync)
      {

         semaphore * pSemaphore = m_synca.sync_at(i).cast < semaphore >();

         if (pSemaphore != nullptr)
         {

            bGotOne = true;

            m_byteaLocked[i] = !m_synca.m_synca[i]->unlock(lCount, pPrevCount);

         }

      }

   }

   return bGotOne;

}


bool multi_lock::IsLocked(index dwObject)
{

   ASSERT(dwObject < m_synca.size());

   return m_byteaLocked[dwObject];

}



