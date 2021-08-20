#include "framework.h"
#include "acme/operating_system.h"


//synchronization_object::synchronization_object(const char * lpszName)
//{
//
//   m_bOwner = true;
//
//#ifdef WINDOWS
//
//   m_hsync = nullptr;
//
//#endif
//
//   if (lpszName == nullptr)
//   {
//
//      m_pszName = nullptr;
//
//   }
//   else
//   {
//
//      m_pszName = strdup(lpszName);
//
//   }
//
//}


//#ifdef WINDOWS
//
//
//synchronization_object::synchronization_object(HSYNC hsyncobject, const char * lpszName) :
//   m_hsync(hsyncobject)
//{
//
//   m_bOwner = false;
//
//   if (lpszName == nullptr)
//   {
//
//      m_pszName = nullptr;
//
//   }
//   else
//   {
//
//      m_pszName = strdup(lpszName);
//
//   }
//
//}
//
//
//#endif


synchronization_object::~synchronization_object()
{

#ifdef WINDOWS

   if (m_bOwner && m_hsync != nullptr)
   {

      ::CloseHandle((HANDLE) m_hsync);

      m_hsync = nullptr;

   }

#endif

   //if (m_pszName != nullptr)
   //{

   //   ::free(m_pszName);

   //}

}


bool synchronization_object::lock()
{

   return wait().succeeded();

}


bool synchronization_object::lock(const duration & durationTimeout)
{

   return wait(durationTimeout).succeeded();

}


synchronization_result synchronization_object::wait()
{

   return wait(::duration::infinite());

}


synchronization_result synchronization_object::wait()
{

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = m_psystem;

   }

   if (::is_null(ptask))
   {

      __throw(error_null_pointer);

   }

   while (ptask->task_get_run())
   {

      auto result = _wait(100_ms);

      if (!result.timed_out())
      {

         return result;

      }

   }

   return e_synchronization_result_thread_set_finish;

}


synchronization_result synchronization_object::wait(const ::duration & durationTimeout)
{
   
   if (durationTimeout < 200_ms)
   {

      return _wait(durationTimeout);

   }

   ::millis millisEnd = ::millis::now() + durationTimeout;

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = m_psystem;

   }

   if (::is_null(ptask))
   {

      __throw(error_null_pointer);

   }

   while (ptask->task_get_run())
   {

      auto millisWait = millisEnd - ::millis::now();

      if (millisWait < 0)
      {

         return e_synchronization_result_timed_out;

      }

      auto result = _wait(millisWait);

      if (!result.timed_out())
      {

         return result;

      }

   }

   return e_synchronization_result_thread_set_finish;

}


//synchronization_result synchronization_object::wait(const duration & durationTimeout)
//{
//
//   return wait();
//
//}


//bool synchronization_object::is_locked() const
//{
//
//   return false;
//
//}


bool synchronization_object::unlock()
{

   return false;

}


bool synchronization_object::unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */)
{

   return false;

}


synchronization_result synchronization_object::wait(const duration & durationTimeout)
{

#ifdef WINDOWS

   if (m_hsync)
   {

      auto windowsWaitResult = ::WaitForSingleObjectEx(m_hsync, durationTimeout.u32_millis(), false);

      return windows_wait_result_to_synchronization_result(windowsWaitResult);

   }

#endif

   return e_synchronization_result_error;

}


void synchronization_object::acquire_ownership()
{

   m_bOwner = true;

}


[[maybe_unused]] void synchronization_object::release_ownership()
{

   m_bOwner = false;

}


//void synchronization_object::assert_valid() const
//{
//
//   matter::assert_valid();
//
//}


//void synchronization_object::dump(dump_context & dumpcontext) const
//{
//
//#ifdef WINDOWS
//   dumpcontext << "Object ";
//   dumpcontext << m_hsync;
//#endif
//
//   dumpcontext << " named " << m_pszName << "\n";
//
//   matter::dump(dumpcontext);
//
//}


//HSYNC synchronization_object::hsync() const
//{
//
//#ifdef WINDOWS
//
//   return m_hsync;
//
//#else
//
//   return (synchronization_object *) this;
//
//#endif
//
//}


//bool synchronization_object::unlock(::i32 /* lCount */, LPLONG /* pPrevCount=nullptr */)
//
//{
//
//   return true;
//
//}


//bool synchronization_object::unlock()
//{
//
//   return true;
//
//}




void synchronization_object::init_wait()
{


}


void synchronization_object::exit_wait()
{


}




//synchronization_result synchronization_object::wait()
//{
//
//   return wait(duration::infinite());
//
//}


//sync_callback::~sync_callback()
//{
//}


bool synchronization_object::is_locked() const
{

   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
   ASSERT(dynamic_cast <critical_section *> (const_cast <synchronization_object *> (this)) == nullptr);

   single_lock synchronouslock(const_cast <synchronization_object *> (this));

   bool bWasLocked = !synchronouslock.lock(duration::zero());

   if (!bWasLocked)
   {

      synchronouslock.unlock();

   }

   return bWasLocked;

}



