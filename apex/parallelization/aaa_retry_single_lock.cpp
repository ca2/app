#include "framework.h"

/////////////////////////////////////////////////////////////////////////////
// retry_single_lock

retry_single_lock::retry_single_lock(class synchronization_object * psync, duration durationLock, duration durationSleep, i32 iRetry, bool bInitialLock)
{

   m_psync     = psync;
   m_bAcquired       = false;
   m_durationLock    = durationLock;
   m_durationSleep   = durationSleep;
   m_iRetry          = iRetry;

   if(bInitialLock)
   {

      lock();

   }

}


bool retry_single_lock::lock()
{

   if(m_psync == nullptr)
      return false;

   i32 iRetry = 0;

   try
   {
      while(!(m_bAcquired = m_psync->lock(m_durationLock)))
      {

         sleep(m_durationSleep);

         iRetry++;

         if(m_iRetry >= 0 && iRetry >= m_iRetry)
            break;
      }
   }
   catch(...)
   {
      m_bAcquired = false;
   }

   return m_bAcquired;

}

bool retry_single_lock::unlock()
{

   if(m_psync == nullptr)
      return false;

   if (m_bAcquired)
   {
      try
      {
         m_bAcquired = !m_psync->unlock();
      }
      catch(...)
      {
         m_bAcquired = true;
      }
   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}


retry_single_lock::~retry_single_lock()
{
   unlock();
}

bool retry_single_lock::IsLocked()
{
   return m_bAcquired;
}
