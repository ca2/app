#pragma once



class CLASS_DECL_ACME multi_lock
{
public:


   sync_array          m_synca;
   byte                m_byteaLocked[MAXIMUM_WAIT_OBJECTS];


   multi_lock(const sync_array & synca,bool bInitialLock = FALSE);
   multi_lock(::count c, const sync_array & synca, bool bInitialLock = FALSE);
   ~multi_lock();


   void construct(const sync_array & synca,bool bInitialLock = FALSE);


   sync_result lock(const duration & tickTimeout = duration::infinite(), bool bWaitForAll = TRUE, u32 dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = nullptr);
   bool IsLocked(index dwItem);

};
