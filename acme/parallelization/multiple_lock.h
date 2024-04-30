#pragma once


#include "acme/primitive/primitive/bits.h"
#include "synchronization_array.h"


class CLASS_DECL_ACME multiple_lock
{
public:


   synchronization_array          m_synchronizationa;
   bits < ::u64 >      m_bitsLocked;


   multiple_lock();
   multiple_lock(const synchronization_array & synca,bool bInitialLock = false);
   multiple_lock(::raw::count c, const synchronization_array & synca, bool bInitialLock = false);
   ~multiple_lock();


   void construct(const synchronization_array & synca,bool bInitialLock = false);


   ::raw::index lock(const class time & tickTimeout = ::time::infinity(), bool bWaitForAll = true, u32 dwWakeMask = 0);
   void unlock();
   void unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool is_locked(::raw::index iItem);


};



