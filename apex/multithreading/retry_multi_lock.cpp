#include "framework.h"
#include "apex/os/_c.h"
#include "apex/os/_.h"
#include "apex/os/_os.h"


retry_multi_lock::retry_multi_lock(const sync_array & synca, duration durationLock, duration durationSleep, i32 iRetry, bool bInitialLock)
{

   if (synca.is_empty())
   {

      return;

   }

   m_durationLock    = durationLock;

   m_durationSleep   = durationSleep;

   m_synca           = synca;

   m_baLocked.set_size(m_synca.sync_count());

   if (bInitialLock)
   {

      lock();

   }
}


retry_multi_lock::~retry_multi_lock()
{

   unlock();

}


sync_result retry_multi_lock::lock(bool bWaitForAll, u32 dwWakeMask /* = 0 */)
{

   if (m_hsynca.is_empty())
   {

      return sync_result(sync_result::result_error);

   }

   i32 iResult;

   i32 iRetry = 0;

   while (true)
   {

      if (dwWakeMask == 0)
      {

         iResult = ::WaitForMultipleObjectsEx((u32)m_hsynca.get_count(), m_hsynca.get_data(), bWaitForAll, m_durationLock.lock_duration(), FALSE);

      }
#ifdef _UWP
      else
      {

         __throw(not_supported_exception());

      }
#else
      else
      {

         iResult = ::MsgWaitForMultipleObjects((u32)m_hsynca.get_count(), m_hsynca.get_data(), bWaitForAll, m_durationLock.lock_duration(), dwWakeMask);

      }
#endif

      index iIndex = iResult - WAIT_OBJECT_0;

      if (iResult >= WAIT_OBJECT_0 && iIndex < m_hsynca.get_count())
      {

         if (bWaitForAll)
         {

            for (index i = 0; i < m_hsynca.get_count(); i++)
            {

               m_baLocked[i] = TRUE;

            }

            break;

         }
         else
         {

            m_baLocked[iIndex] = TRUE;

            break;

         }

      }

      sleep(m_durationSleep);

      iRetry++;

      if (m_iRetry >= 0 && iRetry >= m_iRetry)
      {

         break;

      }

   }

   return sync_result(iResult);

}

bool retry_multi_lock::unlock()
{

   for (index i=0; i < m_hsynca.get_count(); i++)
   {

      if (m_baLocked[i])
      {

         m_baLocked[i] = !m_synca.sync_at(i)->unlock();

      }

   }

   return TRUE;

}


bool retry_multi_lock::unlock(LONG lCount, LPLONG pPrevCount /* =nullptr */)
{

   bool bGotOne = false;

   for (index i=0; i < m_hsynca.get_count(); i++)
   {
      
      if (m_baLocked[i])
      {
         
         semaphore* pSemaphore = m_synca[i].cast < semaphore >();
         
         if (pSemaphore != nullptr)
         {
            
            bGotOne = true;

            m_baLocked[i] = !m_synca.m_synca[i]->unlock(lCount, pPrevCount);

         }

      }

   }

   return bGotOne;

}


bool retry_multi_lock::IsLocked(index dwObject)
{

   ASSERT(dwObject < m_hsynca.get_count());

   return m_baLocked[dwObject];

}



