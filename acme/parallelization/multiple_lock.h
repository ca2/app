#pragma once


#include "acme/primitive/primitive/bits.h"


class CLASS_DECL_ACME multiple_lock
{
public:


   synchronization_array          m_synchronizationa;
   bits < ::u64 >      m_bitsLocked;


   multiple_lock();
   multiple_lock(const synchronization_array & synca,bool bInitialLock = false);
   multiple_lock(::count c, const synchronization_array & synca, bool bInitialLock = false);
   ~multiple_lock();


   void construct(const synchronization_array & synca,bool bInitialLock = false);


   void lock(const duration & tickTimeout = duration::infinite(), bool bWaitForAll = true, u32 dwWakeMask = 0);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked(index dwItem);


};



