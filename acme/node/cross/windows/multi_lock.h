#pragma once


class CLASS_DECL_ACME multi_lock
{
public:


   sync_array          m_synca;
   bits < u64 >        m_bitsLocked;


   multi_lock(const sync_array & synca,bool bInitialLock = false);
   multi_lock(::count c, const sync_array & synca, bool bInitialLock = false);
   ~multi_lock();


   void construct(const sync_array & synca,bool bInitialLock = false);


   sync_result lock(const duration & tickTimeout = duration::infinite(), bool bWaitForAll = true, u32 dwWakeMask = 0);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked(index dwItem);

};
