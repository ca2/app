#pragma once


class CLASS_DECL_APEX retry_multi_lock
{
public:


   synchronization_array     m_synchronizationa;
   hsync_array    m_hsynca;
   bool_array     m_baLocked;
   duration       m_durationLock;
   duration       m_durationSleep;
   i32            m_iRetry;


   retry_multi_lock(const synchronization_array & synca, duration durationLock, duration durationSleep, i32 iRetry = -1, bool bInitialLock = true);
   ~retry_multi_lock();


   void construct(const synchronization_array & synca, duration durationLock, duration durationSleep, i32 iRetry = -1, bool bInitialLock = true);


   synchronization_result lock(bool bWaitForAll = true, u32 dwWakeMask = 0);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked(index dwItem);


};



