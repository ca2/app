#include "framework.h"


single_lock::single_lock(sync * psync, bool bInitialLock)
{

   m_psync = psync;

   m_bAcquired = FALSE;

   if (bInitialLock)
   {

      lock();

   }

}


sync_result single_lock::wait()
{

   ::sync_result result(::sync_result::result_event0);

   if(m_bAcquired)
   {

      return result;

   }

   if(m_psync == nullptr)
   {

      return result;

   }

   try
   {

      result = m_psync->wait();

   }
   catch(...)
   {

      result = ::sync_result(::sync_result::result_error);

   }

   m_bAcquired = result.succeeded();

   return result;

}


::sync_result single_lock::wait(const duration & durationTimeOut)
{

   ::sync_result result(::sync_result::result_event0);

   if(m_bAcquired)
   {

      return result;

   }

   if(m_psync == nullptr)
   {

      return result;

   }

   try
   {

      result = m_psync->wait(durationTimeOut);

   }
   catch(...)
   {

      result = ::sync_result(::sync_result::result_error);

   }

   m_bAcquired = result.succeeded();

   return result;

}


bool single_lock::unlock()
{

   if(m_psync == nullptr)
   {

      return true;

   }

   if (m_bAcquired)
   {

      try
      {

         if(m_psync->unlock())
         {

            m_bAcquired = false;

         }

      }
      catch(...)
      {

      }

   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;

}


bool single_lock::unlock(LONG lCount, LPLONG pPrevCount /* = nullptr */)

{
   ASSERT(m_psync != nullptr);
   if (m_bAcquired)
      m_bAcquired = !m_psync->unlock(lCount, pPrevCount);


   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}


single_lock::~single_lock()
{

   unlock();

   /*if(::get_task() != nullptr)
   {

      if(::get_task()->m_pslUser == this)
      {
         ::get_task()->m_pslUser = nullptr;
      }

   }*/

}


bool single_lock::IsLocked()
{

   return m_bAcquired;

}


