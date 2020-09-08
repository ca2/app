#pragma once


class CLASS_DECL_ACME retry_multi_lock
{
public:


   sync_array     m_synca;
   hsync_array    m_hsynca;
   bool_array     m_baLocked;
   duration       m_durationLock;
   duration       m_durationSleep;
   i32            m_iRetry;


   retry_multi_lock(const sync_array & synca, duration durationLock, duration durationSleep, i32 iRetry = -1, bool bInitialLock = true);
   ~retry_multi_lock();


   void construct(const sync_array & synca, duration durationLock, duration durationSleep, i32 iRetry = -1, bool bInitialLock = true);


   sync_result lock(bool bWaitForAll = TRUE, u32 dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = nullptr);
   bool IsLocked(index dwItem);


};



