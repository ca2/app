#pragma once


#include "acme/prototype/prototype/bits.h"
#include "synchronization_array.h"


class CLASS_DECL_ACME multiple_lock
{
public:


   synchronization_array &       m_synchronizationa;
   bits < ::u64 >                m_bitsLocked;


   multiple_lock(synchronization_array & synchronizationa, bool bInitialLock = false);
   //multiple_lock(const synchronization_array & synca,bool bInitialLock = false);
   //multiple_lock(::collection::count c, const synchronization_array & synca, bool bInitialLock = false);
   ~multiple_lock();


   //void construct(const synchronization_array & synca,bool bInitialLock = false);


   ::e_status lock(const class time & tickTimeout = ::time::infinity(), bool bWaitForAll = true, unsigned int dwWakeMask = 0);
   void unlock();
   void unlock(int lCount, int * lPrevCount = nullptr);
   bool is_locked(::collection::index iItem);


};



