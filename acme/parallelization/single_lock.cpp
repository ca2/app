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


::e_status single_lock::wait()
{

   ::e_status estatus(signaled_base);

   if(m_bAcquired)
   {

      return estatus;

   }

   if(m_psync == nullptr)
   {

      return estatus;

   }

   try
   {

      estatus = m_psync->wait();

   }
   catch(...)
   {

      estatus = error_failed;

   }

   m_bAcquired = estatus.signaled();

   return estatus;

}


::e_status single_lock::wait(const duration & durationTimeOut)
{

   ::e_status estatus(signaled_base);

   if(m_bAcquired)
   {

      return estatus;

   }

   if(m_psync == nullptr)
   {

      return estatus;

   }

   try
   {

      estatus = m_psync->wait(durationTimeOut);

   }
   catch(...)
   {

      estatus = error_failed;

   }

   m_bAcquired = estatus.signaled();

   return estatus;

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


::e_status _single_lock::_wait()
{

   ::e_status estatus(signaled_base);

   if (m_bAcquired)
   {

      return estatus;

   }

   if (m_psync == nullptr)
   {

      return estatus;

   }

   try
   {

      estatus = m_psync->_wait();

   }
   catch (...)
   {

      estatus = error_failed;

   }

   m_bAcquired = estatus.signaled();

   return estatus;

}


::e_status _single_lock::_wait(const duration & durationTimeOut)
{

   ::e_status estatus(signaled_base);

   if (m_bAcquired)
   {

      return estatus;

   }

   if (m_psync == nullptr)
   {

      return estatus;

   }

   try
   {

      estatus = m_psync->_wait(durationTimeOut);

   }
   catch (...)
   {

      estatus = error_failed;

   }

   m_bAcquired = estatus.signaled();

   return estatus;

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


