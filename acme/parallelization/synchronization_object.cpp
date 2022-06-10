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


::e_status synchronization_object::lock()
{

   return wait();
   
}


::e_status synchronization_object::lock(const class ::wait & wait)
{

   return this->wait(wait);

}


void synchronization_object::_lock()
{

   _wait();

}


bool synchronization_object::_lock(const class ::wait & wait)
{

   return this->_wait(wait);

}


void synchronization_object::_wait()
{

   _wait(::duration::infinite());

}


::e_status synchronization_object::wait()
{

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = m_psystem;

   }

   if (::is_null(ptask))
   {

      _wait();

      return ::success;

   }

   while (true)
   {

      auto bOk =  _wait(100_ms);

      if(bOk)
      {

         return ::success;

      }

      if (!ptask->task_get_run())
      {

         return error_failed;

      }

   }

}


::e_status synchronization_object::wait(const class ::wait & wait)
{
   
   if (wait < 200_ms)
   {

      auto bOk = this->_wait(wait);

      if(!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   if(wait.is_infinite())
   {

      return this->wait();

   }

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = m_psystem;

   }

   if (::is_null(ptask))
   {

      auto bOk = this->_wait(wait);

      if(!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   auto waitStart = ::wait::now();

   while(true)
   {

      auto waitElapsed = waitStart.elapsed();

      if (waitElapsed > wait)
      {

         return error_wait_timeout;

      }

      auto waitNow = ::minimum(waitElapsed, 100_ms);

      bool bOk = _wait(waitNow);

      if (bOk)
      {

         return ::success;

      }

      if(!ptask->task_get_run())
      {

         return error_failed;

      }

   }

}


void synchronization_object::unlock()
{

   ///return false;

}


void synchronization_object::unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */)
{

   //return false;

}


bool synchronization_object::_wait(const class ::wait & wait)
{

#ifdef WINDOWS

   if (!m_hsync)
   {

      return true;

   }

   //auto milliseconds = wait.operator u32();
   //unsigned int ui;
   //if (wait.m_d <= 0.)
   //{
   //   ui = 0;

   //}
   //else if (wait.m_d >= 0xffffffffu)
   //{

   //   ui = 0xffffffffu;
   //}
   //else
   //{

   //   ui = (::u32) (wait.m_d * 1'000.0);

   //}

   ////return (::u32)m_d <= 0. ? 0 : (m_d >= 0xffffffffu ? 0xffffffffu : (::u32)(m_d * 1'000.0));
   //if (milliseconds < 1'000'000'000)
   //{

   //   output_debug_string("milliseconds < 1'000'000'000");

   //}

   auto windowsWaitResult = ::WaitForSingleObjectEx(m_hsync, wait, false);

   auto estatus = windows_wait_result_to_status(windowsWaitResult);

   if (estatus == error_wait_timeout)
   {

      return false;

   }
   else if (estatus == signaled_base)
   {

#ifdef _DEBUG

      auto pmutex = dynamic_cast < ::mutex *> (this);

      if (::is_set(pmutex))
      {

         pmutex->m_strThread = ::task_get_name();
         pmutex->m_itask = ::get_current_itask();
         ::output_debug_string("");

      }

#endif

      return true;

   }
   else
   {

      throw ::exception(estatus);

      return false;

   }

#endif

   throw ::exception(error_interface_only);

   return false;

}


void synchronization_object::acquire_ownership()
{

   m_bOwner = true;

}


[[maybe_unused]] void synchronization_object::release_ownership()
{

   m_bOwner = false;

}


//void synchronization_object::assert_ok() const
//{
//
//   matter::assert_ok();
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

   bool bWasLocked = false;
   
   try
   {
      
      synchronouslock.lock(duration::zero());

   }
   catch (...)
   {

      bWasLocked = true;

   }

   if (!bWasLocked)
   {

      synchronouslock.unlock();

   }

   return bWasLocked;

}



