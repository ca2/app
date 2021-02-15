#include "framework.h"
//#include "acme/operating_system.h"
//
//
//retry_multi_lock::retry_multi_lock(const synchronization_array & synca, duration durationLock, duration durationSleep, i32 iRetry, bool bInitialLock)
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
//   m_baLocked.set_size(m_synchronizationa.synchronization_object_count());
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
//synchronization_result retry_multi_lock::lock(bool bWaitForAll, u32 dwWakeMask /* = 0 */)
//{
//
//#ifdef WINDOWS
//
//   if (m_hsynca.is_empty())
//   {
//
//      return e_synchronization_result_error;
//
//   }
//
//#endif
//
//   i32 iResult;
//
//   i32 iRetry = 0;
//
//   while (true)
//   {
//
//      if (dwWakeMask == 0)
//      {
//
//         iResult = ::WaitForMultipleObjectsEx((u32)m_hsynca.get_count(), m_hsynca.get_data(), bWaitForAll, m_durationLock.u32_millis(), false);
//
//      }
//#ifdef _UWP
//      else
//      {
//
//         __throw(not_supported_exception());
//
//      }
//#else
//      else
//      {
//
//         iResult = ::MsgWaitForMultipleObjects((u32)m_hsynca.get_count(), m_hsynca.get_data(), bWaitForAll, m_durationLock.u32_millis(), dwWakeMask);
//
//      }
//#endif
//
//      index iIndex = iResult - WAIT_OBJECT_0;
//
//      if (iResult >= WAIT_OBJECT_0 && iIndex < m_hsynca.get_count())
//      {
//
//         if (bWaitForAll)
//         {
//
//            for (index i = 0; i < m_hsynca.get_count(); i++)
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
//   for (index i=0; i < m_hsynca.get_count(); i++)
//   {
//
//      if (m_baLocked[i])
//      {
//
//         m_baLocked[i] = !m_synchronizationa.synchronization_object_at(i)->unlock();
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
//bool retry_multi_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* =nullptr */)
//{
//
//   bool bGotOne = false;
//
//   for (index i=0; i < m_hsynca.get_count(); i++)
//   {
//
//      if (m_baLocked[i])
//      {
//
//         semaphore* pSemaphore = m_synchronizationa.synchronization_object_at(i).cast < semaphore >();
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
//bool retry_multi_lock::IsLocked(index dwObject)
//{
//
//   ASSERT(dwObject < m_hsynca.get_count());
//
//   return m_baLocked[dwObject];
//
//}
//
//
//
