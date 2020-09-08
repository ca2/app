#include "framework.h"


//sync::sync(const char * lpszName)
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
//sync::sync(HSYNC hsyncobject, const char * lpszName) :
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


sync::~sync()
{

#ifdef WINDOWS

   if (m_bOwner && m_hsync != nullptr)
   {

      ::CloseHandle(m_hsync);

      m_hsync = nullptr;

   }

#endif

   //if (m_pszName != nullptr)
   //{

   //   ::free(m_pszName);

   //}

}


bool sync::lock()
{

   return wait().succeeded();

}


bool sync::lock(const duration & durationTimeout)
{

   return wait(durationTimeout).succeeded();

}


sync_result sync::wait()
{

   return wait(::duration::infinite());

}


//sync_result sync::wait(const duration & durationTimeout)
//{
//
//   return wait();
//
//}


//bool sync::is_locked() const
//{
//
//   return false;
//
//}


bool sync::unlock()
{

   return false;

}


bool sync::unlock(LONG /* lCount */, LPLONG /* pPrevCount=nullptr */)

{

   return false;

}


sync_result sync::wait(const duration & durationTimeout)
{

   if (m_hsync)
   {

#ifdef WINDOWS

      return sync_result((u32) ::WaitForSingleObjectEx(m_hsync, durationTimeout.lock_duration(), FALSE));

#endif

   }

   return sync_result(sync_result::result_error);

}


void sync::acquire_ownership()
{

   m_bOwner = true;

}


void sync::release_ownership()
{

   m_bOwner = false;

}


//void sync::assert_valid() const
//{
//
//   generic::assert_valid();
//
//}


//void sync::dump(dump_context & dumpcontext) const
//{
//
//#ifdef WINDOWS
//   dumpcontext << "Object ";
//   dumpcontext << m_hsync;
//#endif
//
//   dumpcontext << " named " << m_pszName << "\n";
//
//   generic::dump(dumpcontext);
//
//}


//HSYNC sync::hsync() const
//{
//
//#ifdef WINDOWS
//
//   return m_hsync;
//
//#else
//
//   return (sync *) this;
//
//#endif
//
//}


//bool sync::unlock(LONG /* lCount */, LPLONG /* pPrevCount=nullptr */)
//
//{
//
//   return true;
//
//}


//bool sync::unlock()
//{
//
//   return true;
//
//}




void sync::init_wait()
{


}


void sync::exit_wait()
{


}




//sync_result sync::wait()
//{
//
//   return wait(duration::infinite());
//
//}


//sync_callback::~sync_callback()
//{
//}


bool sync::is_locked() const
{

   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
   ASSERT(dynamic_cast <critical_section *> (const_cast <sync *> (this)) == nullptr);

   single_lock sl(const_cast <sync *> (this));

   bool bWasLocked = !sl.lock(duration::zero());

   if (!bWasLocked)
   {

      sl.unlock();

   }

   return bWasLocked;

}



