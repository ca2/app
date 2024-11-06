#pragma once


class CLASS_DECL_APEX retry_single_lock
{
public:


   synchronization *               m_psync;
   hsynchronization                m_hsync;
   bool                 m_bAcquired;
   duration             m_durationLock;
   duration             m_durationSleep;
   i32                  m_iRetry;


   retry_single_lock(synchronization * pparticle, duration durationLock, duration durationSleep, i32 iRetry = -1, bool bInitialLock = true);
   ~retry_single_lock();

   bool lock();
   bool unlock();
   bool IsLocked();


};
