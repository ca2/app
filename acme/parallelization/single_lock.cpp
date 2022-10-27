#include "framework.h"
#include "single_lock.h"
#include "acme/exception/exception.h"


single_lock::single_lock(::particle * pparticleSynchronization, bool bInitialLock)
{

   m_pparticleSynchronization = pparticleSynchronization;

   if (::is_set(m_pparticleSynchronization))
   {

      m_pparticleSynchronization->increment_reference_count();

   }

   set_own_synchronization();

   if (bInitialLock)
   {

      lock();

   }

}


single_lock::~single_lock()
{

   if (is_acquired())
   {

      unlock();

   }

   ::release(m_pparticleSynchronization);

   unset_own_synchronization();

}


void single_lock::_wait()
{

   //::e_status estatus(signaled_base);
   if (m_pparticleSynchronization == nullptr)
   {

      return;
      //return estatus;

   }


   if (is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   //try
   //{

      /*estatus =*/ m_pparticleSynchronization->_wait();

   //}
   //catch (...)
   //{

      /*estatus = error_failed; */

   //}

   //m_bAcquired = estatus.signaled();

      set_acquired();

   //return estatus;

}


bool single_lock::_wait(const class ::wait& wait)
{

   //::e_status estatus(signaled_base);

   if (is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   if (m_pparticleSynchronization == nullptr)
   {

      return true;

   }

   //try
   //{

      bool bOk= m_pparticleSynchronization->_wait(wait);

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


   set_acquired();



//   return estatus;

   return true;

}


::e_status single_lock::wait()
{

   if(is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   if(m_pparticleSynchronization == nullptr)
   {

      return ::success;

   }

   ::e_status estatus = error_failed;

   try
   {

      estatus = m_pparticleSynchronization->wait();

   }
   catch(...)
   {

      estatus = error_failed;

   }

   if(estatus)
   {

      set_acquired();

   }

   return estatus;

}


::e_status single_lock::wait(const class ::wait & wait)
{

   if(is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   if(m_pparticleSynchronization == nullptr)
   {

      return ::success;

   }

   ::e_status estatus = error_failed;

   try
   {

      estatus = m_pparticleSynchronization->wait(wait);

   }
   catch(...)
   {

      estatus = error_failed;

   }

   if (estatus)
   {

      set_acquired();

   }

   return estatus;

}


void single_lock::unlock()
{

   if(m_pparticleSynchronization == nullptr)
   {

      return;

   }

   if (!is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   m_pparticleSynchronization->unlock();

   unset_acquired();

   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


void single_lock::unlock(::i32 lCount, ::i32 * pPrevCount /* = nullptr */)
{

   ASSERT(m_pparticleSynchronization != nullptr);

   if (!is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   //m_bAcquired = m_psync->unlock(lCount, pPrevCount);

   m_pparticleSynchronization->unlock(lCount, pPrevCount);

   set_acquired();

   //}

   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


bool single_lock::is_locked() const
{

   return is_acquired();

}


_single_lock::_single_lock(::particle * pparticleSynchronization, bool bInitialLock)
{

   m_pparticleSynchronization = pparticleSynchronization;

   if (::is_set(m_pparticleSynchronization))
   {

      m_pparticleSynchronization->increment_reference_count();

   }

   if (bInitialLock)
   {

      _lock();

   }

}


_single_lock::~_single_lock()
{

   unlock();

   ::release(m_pparticleSynchronization);

}


void _single_lock::_wait()
{

   //::e_status estatus(signaled_base);

   if (is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   if (m_pparticleSynchronization == nullptr)
   {

      //throw ::exception(error_wrong_state);

      return;

   }

   try
   {

      /*estatus =*/ m_pparticleSynchronization->_wait();

   }
   catch (...)
   {

      //estatus = error_failed;

   }

   ///m_bAcquired = estatus.signaled();

   //throw ::exception(

   set_acquired();

   ///return estatus;

}


bool _single_lock::_wait(const class ::wait & wait)
{

   //::e_status estatus(signaled_base);

   if (is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

   if (m_pparticleSynchronization == nullptr)
   {

      //return estatus;

      //throw ::exception(error_invalid_empty_argument);

      return true;


   }

   //try
   //{

      /*estatus = */

      bool bOk = m_pparticleSynchronization->_wait(wait);

   //}
   //catch (...)
   //{

   //   estatus = error_failed;

   //}

   //m_bAcquired = estatus.signaled();

   if(bOk)
   {

      set_acquired();

   }

   //return estatus;

   return bOk;

}


void _single_lock::unlock()
{

   if (m_pparticleSynchronization == nullptr)
   {

      return;
      //return true;

   }

   if (!is_acquired())
   {

      return;

   }

   //try
   //{

      //if (m_psync->unlock())

   m_pparticleSynchronization->unlock();
      //{

         unset_acquired();

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

   if (is_acquired())
   {

      throw ::exception(error_wrong_state);

   }

      //m_bAcquired = !m_psync->unlock(lCount, pPrevCount);

   m_pparticleSynchronization->unlock(lCount, pPrevCount);

   set_acquired();

//   }


   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;
}


bool _single_lock::is_locked() const
{

   return is_acquired();

}



