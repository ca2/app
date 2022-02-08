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

   if (m_bAcquired)
   {

      unlock();

   }

   ::release(m_psync);

}


void single_lock::_wait()
{

   //::e_status estatus(signaled_base);

   if (m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   if (m_psync == nullptr)
   {

      return;
      //return estatus;

   }

   //try
   //{

      /*estatus =*/ m_psync->_wait();

   //}
   //catch (...)
   //{

      /*estatus = error_failed; */

   //}

   //m_bAcquired = estatus.signaled();

      m_bAcquired = true;

   //return estatus;

}


bool single_lock::_wait(const class ::wait& wait)
{

   //::e_status estatus(signaled_base);

   if (m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   if (m_psync == nullptr)
   {

      return true;

   }

   //try
   //{

      bool bOk= m_psync->_wait(wait);

   //}
   //catch (...)
   //{

   //   /* estatus = error_failed; */

   //}

   ///m_bAcquired = estatus.signaled();

      if (!bOk)
      {

         return false;

      }


   m_bAcquired = true;



//   return estatus;

   return true;

}


void single_lock::wait()
{

   //::e_status estatus(signaled_base);

   if(m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   if(m_psync == nullptr)
   {

      return;

   }

   try
   {

      /* estatus = */ m_psync->wait();

   }
   catch(...)
   {

      ///estatus = error_failed;

   }

   //m_bAcquired = estatus.signaled();

   m_bAcquired = true;

   //return estatus;

}


bool single_lock::wait(const class ::wait & wait)
{

   //::e_status estatus(signaled_base);

   if(m_bAcquired)
   {

      throw_status(error_wrong_state);
      //return estatus;

   }

   if(m_psync == nullptr)
   {

      return true;

   }

   //try
   //{

     bool bOk= /*estatus = */ m_psync->wait(wait);

   //}
   //catch(...)
   //{

   //   //estatus = error_failed;

   //}

   //m_bAcquired = estatus.signaled();

     if (!bOk)
     {

        return false;

     }

   m_bAcquired = true;

   ///return estatus;

   return true;

}


void single_lock::unlock()
{

   if(m_psync == nullptr)
   {

      return;

   }

   if (!m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   m_psync->unlock();

   m_bAcquired = false;

   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


void single_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* = nullptr */)
{

   ASSERT(m_psync != nullptr);

   if (!m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   //m_bAcquired = m_psync->unlock(lCount, pPrevCount);

   m_psync->unlock(lCount, pPrevCount);

   m_bAcquired = true;

   //}

   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


bool single_lock::is_locked() const
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


void _single_lock::_wait()
{

   //::e_status estatus(signaled_base);

   if (m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   if (m_psync == nullptr)
   {

      //throw_status(error_wrong_state);

      return;

   }

   try
   {

      /*estatus =*/ m_psync->_wait();

   }
   catch (...)
   {

      //estatus = error_failed;

   }

   ///m_bAcquired = estatus.signaled();

   //throw_status(

   m_bAcquired = true;

   ///return estatus;

}


bool _single_lock::_wait(const class ::wait & wait)
{

   //::e_status estatus(signaled_base);

   if (m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

   if (m_psync == nullptr)
   {

      //return estatus;

      //throw_status(error_invalid_empty_argument);

      return true;


   }

   //try
   //{

      /*estatus = */

      bool bOk = m_psync->_wait(wait);

   //}
   //catch (...)
   //{

   //   estatus = error_failed;

   //}

   //m_bAcquired = estatus.signaled();

   if(bOk)
   {

      m_bAcquired = true;

   }

   //return estatus;

   return bOk;

}


void _single_lock::unlock()
{

   if (m_psync == nullptr)
   {

      return;
      //return true;

   }

   if (!m_bAcquired)
   {

      return;

   }

   //try
   //{

      //if (m_psync->unlock())

   m_psync->unlock();
      //{

         m_bAcquired = false;

      //}

   //}
   //catch (...)
   //{

   //}

   //}

   //// successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


void _single_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* = nullptr */)
{

   //ASSERT(m_psync != nullptr);

   if (m_bAcquired)
   {

      throw_status(error_wrong_state);

   }

      //m_bAcquired = !m_psync->unlock(lCount, pPrevCount);

   m_psync->unlock(lCount, pPrevCount);

   m_bAcquired = true;

//   }


   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;
}


bool _single_lock::is_locked() const
{

   return m_bAcquired;

}



