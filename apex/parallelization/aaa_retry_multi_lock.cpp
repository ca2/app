#include "framework.h"
//#include "acme/operating_system.h"
//
//
//retry_multi_lock::retry_multi_lock(const synchronization_array & synca, duration durationLock, duration durationSleep, int iRetry, bool bInitialLock)
//{
//
//   if (synca.is_empty())
//   {
//
//      return;
//
//   }
//
//   m_durationLock    = durationLock;
//
//   m_durationSleep   = durationSleep;
//
//   m_synchronizationa           = synca;
//
//   m_baLocked.set_size(m_synchronizationa.synchronization_count());
//
//   if (bInitialLock)
//   {
//
//      lock();
//
//   }
//}
//
//
//retry_multi_lock::~retry_multi_lock()
//{
//
//   unlock();
//
//}
//
//
//synchronization_result retry_multi_lock::lock(bool bWaitForAll, unsigned int dwWakeMask /* = 0 */)
//{
//
//#ifdef WINDOWS
//
//   if (m_hsynchronizationa.is_empty())
//   {
//
//      return e_synchronization_result_error;
//
//   }
//
//#endif
//
//   int iResult;
//
//   int iRetry = 0;
//
//   while (true)
//   {
//
//      if (dwWakeMask == 0)
//      {
//
//         iResult = ::WaitForMultipleObjectsEx((unsigned int)m_hsynchronizationa.get_count(), m_hsynchronizationa.get_data(), bWaitForAll, m_durationLock.u32_millis(), false);
//
//      }
//#ifdef UNIVERSAL_WINDOWS
//      else
//      {
//
//         throw ::exception(error_not_supported);
//
//      }
//#else
//      else
//      {
//
//         iResult = ::MsgWaitForMultipleObjects((unsigned int)m_hsynchronizationa.get_count(), m_hsynchronizationa.get_data(), bWaitForAll, m_durationLock.u32_millis(), dwWakeMask);
//
//      }
//#endif
//
//      index iIndex = iResult - WAIT_OBJECT_0;
//
//      if (iResult >= WAIT_OBJECT_0 && iIndex < m_hsynchronizationa.get_count())
//      {
//
//         if (bWaitForAll)
//         {
//
//            for (::collection::index i = 0; i < m_hsynchronizationa.get_count(); i++)
//            {
//
//               m_baLocked[i] = true;
//
//            }
//
//            break;
//
//         }
//         else
//         {
//
//            m_baLocked[iIndex] = true;
//
//            break;
//
//         }
//
//      }
//
//      sleep(m_durationSleep);
//
//      iRetry++;
//
//      if (m_iRetry >= 0 && iRetry >= m_iRetry)
//      {
//
//         break;
//
//      }
//
//   }
//
//   return (enum_synchronization_result) (e_synchronization_result_signaled_base + iResult);
//
//}
//
//
//bool retry_multi_lock::unlock()
//{
//
//   for (::collection::index i=0; i < m_hsynchronizationa.get_count(); i++)
//   {
//
//      if (m_baLocked[i])
//      {
//
//         m_baLocked[i] = !m_synchronizationa.synchronization_at(i)->unlock();
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//bool retry_multi_lock::unlock(int lCount, int * pPrevCount /* =nullptr */)
//{
//
//   bool bGotOne = false;
//
//   for (::collection::index i=0; i < m_hsynchronizationa.get_count(); i++)
//   {
//
//      if (m_baLocked[i])
//      {
//
//         semaphore* pSemaphore = m_synchronizationa.synchronization_at(i).cast < semaphore >();
//
//         if (pSemaphore != nullptr)
//         {
//
//            bGotOne = true;
//
//            m_baLocked[i] = !m_synchronizationa.m_synchronizationa[i]->unlock(lCount, pPrevCount);
//
//         }
//
//      }
//
//   }
//
//   return bGotOne;
//
//}
//
//
//bool retry_multi_lock::IsLocked(::collection::index iObject)
//{
//
//   ASSERT(dwObject < m_hsynchronizationa.get_count());
//
//   return m_baLocked[dwObject];
//
//}
//
//
//
