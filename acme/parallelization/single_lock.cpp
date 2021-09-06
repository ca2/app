#include "framework.h"


single_lock::single_lock(synchronization_object * psync, bool bInitialLock)
{

   m_psync = psync;

   if (::is_set(m_psync))
   {

      m_psync->increment_reference_count();

   }

   m_bAcquired = false;

   if (bInitialLock)
   {

      lock();

   }

}


single_lock::~single_lock()
{

   unlock();

   ::release(m_psync);

}


synchronization_result single_lock::wait()
{

   ::synchronization_result result(e_synchronization_result_signaled_base);

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

      result = ::synchronization_result(e_synchronization_result_error);

   }

   m_bAcquired = result.succeeded();

   return result;

}


::synchronization_result single_lock::wait(const duration & durationTimeOut)
{

   ::synchronization_result result(e_synchronization_result_signaled_base);

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

      result = ::synchronization_result(e_synchronization_result_error);

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


bool single_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* = nullptr */)
{

   ASSERT(m_psync != nullptr);

   if (m_bAcquired)
   {

      m_bAcquired = !m_psync->unlock(lCount, pPrevCount);

   }


   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}




bool single_lock::IsLocked()
{

   return m_bAcquired;

}




_single_lock::_single_lock(synchronization_object * psync, bool bInitialLock)
{

   m_psync = psync;

   if (::is_set(m_psync))
   {

      m_psync->increment_reference_count();

   }

   m_bAcquired = false;

   if (bInitialLock)
   {

      _lock();

   }

}


_single_lock::~_single_lock()
{

   unlock();

   ::release(m_psync);

}


synchronization_result _single_lock::_wait()
{

   ::synchronization_result result(e_synchronization_result_signaled_base);

   if (m_bAcquired)
   {

      return result;

   }

   if (m_psync == nullptr)
   {

      return result;

   }

   try
   {

      result = m_psync->_wait();

   }
   catch (...)
   {

      result = ::synchronization_result(e_synchronization_result_error);

   }

   m_bAcquired = result.succeeded();

   return result;

}


::synchronization_result _single_lock::_wait(const duration & durationTimeOut)
{

   ::synchronization_result result(e_synchronization_result_signaled_base);

   if (m_bAcquired)
   {

      return result;

   }

   if (m_psync == nullptr)
   {

      return result;

   }

   try
   {

      result = m_psync->_wait(durationTimeOut);

   }
   catch (...)
   {

      result = ::synchronization_result(e_synchronization_result_error);

   }

   m_bAcquired = result.succeeded();

   return result;

}


bool _single_lock::unlock()
{

   if (m_psync == nullptr)
   {

      return true;

   }

   if (m_bAcquired)
   {

      try
      {

         if (m_psync->unlock())
         {

            m_bAcquired = false;

         }

      }
      catch (...)
      {

      }

   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;

}


bool _single_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* = nullptr */)
{

   ASSERT(m_psync != nullptr);

   if (m_bAcquired)
   {

      m_bAcquired = !m_psync->unlock(lCount, pPrevCount);

   }


   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}




bool _single_lock::IsLocked()
{

   return m_bAcquired;

}


