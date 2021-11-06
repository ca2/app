#pragma once


class CLASS_DECL_ACME multi_lock
{
public:


   synchronization_array          m_synchronizationa;
   bits < u64 >        m_bitsLocked;


   multi_lock(const synchronization_array & synca,bool bInitialLock = false);
   multi_lock(::count c, const synchronization_array & synca, bool bInitialLock = false);
   ~multi_lock();


   void construct(const synchronization_array & synca,bool bInitialLock = false);


   synchronization_result lock(const duration & tickTimeout = duration::infinite(), bool bWaitForAll = true, u32 dwWakeMask = 0);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked(index dwItem);

};
