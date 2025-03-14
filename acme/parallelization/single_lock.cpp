#include "framework.h"
#include "single_lock.h"
#include "manual_reset_happening.h"
#include "acme/handler/sequence.h"
////#include "acme/exception/exception.h"


single_lock::single_lock(::subparticle * psubparticleSynchronization, bool bInitialLock) :
   m_psubparticleSynchronization(psubparticleSynchronization),
   m_bLocked(false)
{

   //m_pparticleSynchronization = pparticleSynchronization;

   //if (::is_set(m_pparticleSynchronization))
   //{

   //   m_pparticleSynchronization->increment_reference_count();

   //}

   //set_own_synchronization_flag();

   if (bInitialLock)
   {

      lock();

   }

}


single_lock::~single_lock()
{

   if (m_bLocked)
   {

      unlock();

   }

   // ::release(m_pparticleSynchronization);

   //clear_own_synchronization_flag();

}


void single_lock::_lock()
{ 
   
   _wait(); 

}


bool single_lock::lock(const class ::time & timeWait)
{ 
   
   return this->wait(timeWait).failed(); 

}


void single_lock::_wait()
{

   //::e_status estatus(signaled_base);
   if (m_psubparticleSynchronization == nullptr)
   {

      return;
      //return estatus;

   }


   if (m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   //try
   //{

      /*estatus =*/ m_psubparticleSynchronization->_wait();

   //}
   //catch (...)
   //{

      /*estatus = error_failed; */

   //}

   //m_bAcquired = estatus.signaled();

      m_bLocked = true;

   //return estatus;

}


bool single_lock::_wait(const class time & timeWait)
{

   //::e_status estatus(signaled_base);

   if (m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   if (m_psubparticleSynchronization == nullptr)
   {

      return true;

   }

   //try
   //{

      bool bOk= m_psubparticleSynchronization->_wait(timeWait);

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


   //m_bLocked = true;

      m_bLocked = true;



//   return estatus;

   return true;

}


::e_status single_lock::wait()
{

   if(m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   if(m_psubparticleSynchronization == nullptr)
   {

      return ::success;

   }

   ::e_status estatus = error_failed;

   try
   {

      estatus = m_psubparticleSynchronization->wait();

   }
   catch(...)
   {

      estatus = error_failed;

   }

   if(estatus)
   {

      m_bLocked = true;

   }

   return estatus;

}




::e_status single_lock::wait(const class time & timeWait)
{

   if(m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   if(m_psubparticleSynchronization == nullptr)
   {

      return ::success;

   }

   ::e_status estatus = error_failed;

   try
   {

      estatus = m_psubparticleSynchronization->wait(timeWait);

   }
   catch(...)
   {

      estatus = error_failed;

   }

   if (estatus)
   {

      m_bLocked = true;

   }

   return estatus;

}


void single_lock::unlock()
{

   if(m_psubparticleSynchronization == nullptr)
   {

      return;

   }

   if (!m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   m_psubparticleSynchronization->unlock();

   m_bLocked = false;

   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


void single_lock::unlock(int lCount, int * pPrevCount /* = nullptr */)
{

   ASSERT(m_psubparticleSynchronization != nullptr);

   if (!m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   //m_bAcquired = m_psync->unlock(lCount, pPrevCount);

   m_psubparticleSynchronization->unlock(lCount, pPrevCount);

   m_bLocked = true;

   //}

   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


bool single_lock::is_locked() const
{

   return m_bLocked;

}




_single_lock::_single_lock(::subparticle * psubparticleSynchronization, bool bInitialLock) :
   m_psubparticleSynchronization(psubparticleSynchronization),
   m_bLocked(false)
{

   //if (::is_set(m_pparticleSynchronization))
   //{

   //   ::allocator::defer_get_referer()

   //   m_pparticleSynchronization->increment_reference_count();

   //}

   if (bInitialLock)
   {

      _lock();

   }

}


_single_lock::~_single_lock()
{

   unlock();

   //::release(m_pparticleSynchronization);

}



void _single_lock::_lock() { _wait(); }
//bool _single_lock::lock() { return wait().failed(); }



void _single_lock::_wait()
{

   //::e_status estatus(signaled_base);

   if (m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   if (m_psubparticleSynchronization == nullptr)
   {

      //throw ::exception(error_wrong_state);

      return;

   }

   try
   {

      /*estatus =*/ m_psubparticleSynchronization->_wait();

   }
   catch (...)
   {

      //estatus = error_failed;

   }

   ///m_bAcquired = estatus.signaled();

   //throw ::exception(

   m_bLocked = true;

   ///return estatus;

}


bool _single_lock::_wait(const class time & timeWait)
{

   //::e_status estatus(signaled_base);

   if (m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

   if (m_psubparticleSynchronization == nullptr)
   {

      //return estatus;

      //throw ::exception(error_invalid_empty_argument);

      return true;


   }

   //try
   //{

      /*estatus = */

      bool bOk = m_psubparticleSynchronization->_wait(timeWait);

   //}
   //catch (...)
   //{

   //   estatus = error_failed;

   //}

   //m_bAcquired = estatus.signaled();

   if(bOk)
   {

      m_bLocked = true;

   }

   //return estatus;

   return bOk;

}


void _single_lock::unlock()
{

   if (m_psubparticleSynchronization == nullptr)
   {

      return;
      //return true;

   }

   if (!m_bLocked)
   {

      return;

   }

   //try
   //{

      //if (m_psync->unlock())

   m_psubparticleSynchronization->unlock();
      //{

         m_bLocked = false;

      //}

   //}
   //catch (...)
   //{

   //}

   //}

   //// successfully unlocking means it isn't acquired
   //return !m_bAcquired;

}


void _single_lock::unlock(int lCount, int * pPrevCount /* = nullptr */)
{

   //ASSERT(m_psync != nullptr);

   if (m_bLocked)
   {

      throw ::exception(error_wrong_state);

   }

      //m_bAcquired = !m_psync->unlock(lCount, pPrevCount);

   m_psubparticleSynchronization->unlock(lCount, pPrevCount);

   m_bLocked = true;

//   }


   // successfully unlocking means it isn't acquired
   //return !m_bAcquired;
}


bool _single_lock::is_locked() const
{

   return m_bLocked;

}



