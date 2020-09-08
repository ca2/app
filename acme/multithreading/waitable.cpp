/**
* \brief	Session independent waitables
* \author	Thomas Hoefer
*/

#include "framework.h"


//generic::generic()
//{
//
//   mutex() = nullptr;
//
//}
//
//generic::generic(const generic & objectSrc)
//{
//
//   UNREFERENCED_PARAMETER(objectSrc);
//
//   mutex() = nullptr;
//
//}
//
//
/////  \brief		destructor
//generic::~generic()
//{
//
//   if(mutex() != nullptr)
//   {
//
//      delete mutex();
//
//      mutex() = nullptr;
//
//   }
//
//}
//
/////  \brief		abstract function to initialize a waiting action without a timeout
//void generic::wait()
//{
//
//   wait(duration::infinite());
//
//}
//
//	///  \brief		abstract function to initialize a waiting action with a timeout
//	///  \lparam		duration time period to wait for item
//	///  \return	waiting action result as sync_result
//sync_result generic::wait(const duration & duration )
//{
//
//
//   if(mutex() == nullptr)
//   {
//
//      ((generic *)this)->mutex() = new ::mutex();
//
//   }
//
//   try
//   {
//      return mutex()->wait(duration);
//   }
//   catch(...)
//   {
//   }
//
//   return sync_result(sync_result::Failure);
//
//}
//
//
//
//
//// forward declaration
////class event_base;
//
///// This class represents a virtual interface for a callback method for WaitableItems in a
///// event_collection.
//
//waitable_callback::~waitable_callback()
//{
//}
//
//	/// called on signalization of a event_base
//	/// \lparam signaling event_base
////	virtual void callback(const event_base& waitItem) = 0;
////};
//
//
/////  \brief		pauses generic for specified time
/////  \lparam		duration sleeping time of generic
///*CLASS_DECL_ACME void sleep(const duration & duration)
//{
//   Sleep((u32)duration.total_milliseconds());
//}*/
//
//CLASS_DECL_ACME void sleep(const duration & duration)
//{
//   ::Sleep(static_cast<u32>(duration.total_milliseconds()));
//}
//
//
//
//
//
//void * generic::get_os_data() const
//{
//
//   if(mutex() == nullptr)
//   {
//
//      ((generic *)this)->mutex() = new ::mutex();
//
//   }
//
//   return mutex();
//
//}
//
//void generic::lock()
//{
//
//   if(!lock(duration::infinite()))
//      if(!lock(duration::infinite()))
//         __throw(::exception::exception("failure to lock generic"));
//
//}
//
//bool generic::lock(const duration & duration)
//{
//
//   if(mutex() == nullptr)
//   {
//
//      ((generic *)this)->mutex() = new ::mutex();
//
//   }
//
//   bool bLocked = false;
//
//   try
//   {
//
//      bLocked = mutex()->lock(duration);
//
//   }
//   catch(...)
//   {
//
//      bLocked = false;
//
//   }
//
//   if(!bLocked)
//      return false;
//
//   return true;
//
//}
//
//
//bool generic::unlock()
//{
//
//   if(mutex() == nullptr)
//      return false;
//
//   bool bUnlocked = false;
//
//   try
//   {
//
//      bUnlocked = mutex()->unlock();
//
//   }
//   catch(...)
//   {
//
//      bUnlocked = false;
//
//   }
//
//   if(!bUnlocked)
//      return false;
//
//   return true;
//
//}
//
//bool generic::unlock(LONG lCount, LPLONG pPrevCount)

//{
//   UNREFERENCED_PARAMETER(lCount);
//   UNREFERENCED_PARAMETER(pPrevCount);

//   return true;
//}
//
//
//bool generic::is_locked() const
//{
//
//   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
//   ASSERT(dynamic_cast < critical_section * > ( const_cast < generic * > (this)) == nullptr);
//
//   single_lock sl(const_cast < generic * > (this));
//
//   bool bWasLocked = !sl.lock(duration::zero());
//
//   if(!bWasLocked)
//      sl.unlock();
//
//   return bWasLocked;
//
//}
//
